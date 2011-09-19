//---------------------------------------------------------------------------
#ifndef SftpFileSystemH
#define SftpFileSystemH

#include <FileSystems.h>
//---------------------------------------------------------------------------
class TSFTPPacket;
class TOverwriteFileParams;
struct TSFTPSupport;
class TSecureShell;
//---------------------------------------------------------------------------
enum TSFTPOverwriteMode { omOverwrite, omAppend, omResume };
//---------------------------------------------------------------------------
class TSFTPFileSystem : public TCustomFileSystem
{
friend class TSFTPPacket;
friend class TSFTPQueue;
friend class TSFTPAsynchronousQueue;
friend class TSFTPUploadQueue;
friend class TSFTPDownloadQueue;
friend class TSFTPLoadFilesPropertiesQueue;
friend class TSFTPCalculateFilesChecksumQueue;
friend class TSFTPBusy;
public:
  TSFTPFileSystem(TTerminal * ATerminal, TSecureShell * SecureShell);
  virtual ~TSFTPFileSystem();

  virtual void Open();
  virtual void Close();
  virtual bool GetActive();
  virtual void Idle();
  virtual std::wstring AbsolutePath(std::wstring Path, bool Local);
  virtual void AnyCommand(const std::wstring Command,
    const captureoutput_slot_type *OutputEvent);
  virtual void ChangeDirectory(const std::wstring Directory);
  virtual void CachedChangeDirectory(const std::wstring Directory);
  virtual void AnnounceFileListOperation();
  virtual void ChangeFileProperties(const std::wstring FileName,
    const TRemoteFile * File, const TRemoteProperties * Properties,
    TChmodSessionAction & Action);
  virtual bool LoadFilesProperties(TStrings * FileList);
  virtual void CalculateFilesChecksum(const std::wstring & Alg,
    TStrings * FileList, TStrings * Checksums,
    TCalculatedChecksumEvent OnCalculatedChecksum);
  virtual void CopyToLocal(TStrings * FilesToCopy,
    const std::wstring TargetDir, const TCopyParamType * CopyParam,
    int Params, TFileOperationProgressType * OperationProgress,
    TOnceDoneOperation & OnceDoneOperation);
  virtual void CopyToRemote(TStrings * FilesToCopy,
    const std::wstring TargetDir, const TCopyParamType * CopyParam,
    int Params, TFileOperationProgressType * OperationProgress,
    TOnceDoneOperation & OnceDoneOperation);
  virtual void CreateDirectory(const std::wstring DirName);
  virtual void CreateLink(const std::wstring FileName, const std::wstring PointTo, bool Symbolic);
  virtual void DeleteFile(const std::wstring FileName,
    const TRemoteFile * File, int Params, TRmSessionAction & Action);
  virtual void CustomCommandOnFile(const std::wstring FileName,
    const TRemoteFile * File, std::wstring Command, int Params, const captureoutput_slot_type &OutputEvent);
  virtual void DoStartup();
  virtual void HomeDirectory();
  virtual bool IsCapable(int Capability) const;
  virtual void LookupUsersGroups();
  virtual void ReadCurrentDirectory();
  virtual void ReadDirectory(TRemoteFileList * FileList);
  virtual void ReadFile(const std::wstring FileName,
    TRemoteFile *& File);
  virtual void ReadSymlink(TRemoteFile * SymlinkFile,
    TRemoteFile *& File);
  virtual void RenameFile(const std::wstring FileName,
    const std::wstring NewName);
  virtual void CopyFile(const std::wstring FileName,
    const std::wstring NewName);
  virtual std::wstring FileUrl(const std::wstring FileName);
  virtual TStrings * GetFixedPaths();
  virtual void SpaceAvailable(const std::wstring Path,
    TSpaceAvailable & ASpaceAvailable);
  virtual const TSessionInfo & GetSessionInfo();
  virtual const TFileSystemInfo & GetFileSystemInfo(bool Retrieve);
  virtual bool TemporaryTransferFile(const std::wstring & FileName);
  virtual bool GetStoredCredentialsTried();
  virtual std::wstring GetUserName();

protected:
  TSecureShell * FSecureShell;
  TFileSystemInfo FFileSystemInfo;
  bool FFileSystemInfoValid;
  int FVersion;
  std::wstring FCurrentDirectory;
  std::wstring FDirectoryToChangeTo;
  std::wstring FHomeDirectory;
  std::wstring FEOL;
  TList * FPacketReservations;
  // Variant FPacketNumbers;
  std::vector<unsigned int> FPacketNumbers;
  char FPreviousLoggedPacket;
  int FNotLoggedPackets;
  int FBusy;
  bool FAvoidBusy;
  TStrings * FExtensions;
  TSFTPSupport * FSupport;
  bool FUtfStrings;
  bool FUtfNever;
  bool FSignedTS;
  bool FOpenSSH;
  TStrings * FFixedPaths;
  unsigned long FMaxPacketSize;
  TSFTPFileSystem *Self;

  void SendCustomReadFile(TSFTPPacket * Packet, TSFTPPacket * Response,
    const std::wstring FileName, unsigned long Flags);
  void CustomReadFile(const std::wstring FileName,
    TRemoteFile *& File, char Type, TRemoteFile * ALinkedByFile = NULL,
    int AllowStatus = -1);
  virtual std::wstring GetCurrentDirectory();
  std::wstring GetHomeDirectory();
  unsigned long GotStatusPacket(TSFTPPacket * Packet, int AllowStatus);
  bool inline IsAbsolutePath(const std::wstring Path);
  bool RemoteFileExists(const std::wstring FullPath, TRemoteFile ** File = NULL);
  TRemoteFile * LoadFile(TSFTPPacket * Packet,
    TRemoteFile * ALinkedByFile, const std::wstring FileName,
    TRemoteFileList * TempFileList = NULL, bool Complete = true);
  void LoadFile(TRemoteFile * File, TSFTPPacket * Packet,
    bool Complete = true);
  std::wstring LocalCanonify(const std::wstring & Path);
  std::wstring Canonify(std::wstring Path);
  std::wstring RealPath(const std::wstring Path);
  std::wstring RealPath(const std::wstring Path, const std::wstring BaseDir);
  void ReserveResponse(const TSFTPPacket * Packet,
    TSFTPPacket * Response);
  int ReceivePacket(TSFTPPacket * Packet, int ExpectedType = -1,
    int AllowStatus = -1);
  bool PeekPacket();
  void RemoveReservation(int Reservation);
  void SendPacket(const TSFTPPacket * Packet);
  int ReceiveResponse(const TSFTPPacket * Packet,
    TSFTPPacket * Response, int ExpectedType = -1, int AllowStatus = -1);
  int SendPacketAndReceiveResponse(const TSFTPPacket * Packet,
    TSFTPPacket * Response, int ExpectedType = -1, int AllowStatus = -1);
  void UnreserveResponse(TSFTPPacket * Response);
  void TryOpenDirectory(const std::wstring Directory);
  bool SupportsExtension(const std::wstring & Extension) const;
  void ResetConnection();
  void DoCalculateFilesChecksum(const std::wstring & Alg,
    TStrings * FileList, TStrings * Checksums,
    TCalculatedChecksumEvent OnCalculatedChecksum,
    TFileOperationProgressType * OperationProgress, bool FirstLevel);
  void DoDeleteFile(const std::wstring FileName, char Type);

  void SFTPSourceRobust(const std::wstring FileName,
    const std::wstring TargetDir, const TCopyParamType * CopyParam, int Params,
    TFileOperationProgressType * OperationProgress, unsigned int Flags);
  void SFTPSource(const std::wstring FileName,
    const std::wstring TargetDir, const TCopyParamType * CopyParam, int Params,
    TFileOperationProgressType * OperationProgress, unsigned int Flags,
    TUploadSessionAction & Action, bool & ChildError);
  std::wstring SFTPOpenRemoteFile(const std::wstring & FileName,
    unsigned int OpenType, __int64 Size = -1);
  int SFTPOpenRemote(void * AOpenParams, void * Param2);
  void SFTPCloseRemote(const std::wstring Handle,
    const std::wstring FileName, TFileOperationProgressType * OperationProgress,
    bool TransferFinished, bool Request, TSFTPPacket * Packet);
  void SFTPDirectorySource(const std::wstring DirectoryName,
    const std::wstring TargetDir, int Attrs, const TCopyParamType * CopyParam,
    int Params, TFileOperationProgressType * OperationProgress, unsigned int Flags);
  void SFTPConfirmOverwrite(std::wstring & FileName,
    int Params, TFileOperationProgressType * OperationProgress,
    TSFTPOverwriteMode & Mode, const TOverwriteFileParams * FileParams);
  bool SFTPConfirmResume(const std::wstring DestFileName, bool PartialBiggerThanSource,
    TFileOperationProgressType * OperationProgress);
  void SFTPSinkRobust(const std::wstring FileName,
    const TRemoteFile * File, const std::wstring TargetDir,
    const TCopyParamType * CopyParam, int Params,
    TFileOperationProgressType * OperationProgress, unsigned int Flags);
  void SFTPSink(const std::wstring FileName,
    const TRemoteFile * File, const std::wstring TargetDir,
    const TCopyParamType * CopyParam, int Params,
    TFileOperationProgressType * OperationProgress, unsigned int Flags,
    TDownloadSessionAction & Action, bool & ChildError);
  void SFTPSinkFile(std::wstring FileName,
    const TRemoteFile * File, void * Param);
  char * GetEOL() const;
  inline void BusyStart();
  inline void BusyEnd();
  inline unsigned long TransferBlockSize(unsigned long Overhead,
    TFileOperationProgressType * OperationProgress, unsigned long MaxPacketSize = 0);
  inline unsigned long UploadBlockSize(const std::wstring & Handle,
    TFileOperationProgressType * OperationProgress);
  inline unsigned long DownloadBlockSize(
    TFileOperationProgressType * OperationProgress);
  inline int PacketLength(char * LenBuf, int ExpectedType);

  static std::wstring DecodeUTF(const std::wstring UTF);
  static std::wstring EncodeUTF(const std::wstring Source);
};
//---------------------------------------------------------------------------
#endif // SftpFileSystemH
