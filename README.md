NetBox: SFTP/FTP/FTPS/SCP/WebDAV client for Far Manager 2.0/3.0
==============

    Based on WinSCP: SFTP/FTP/SCP client for FAR version 1.6.2 Copyright (c) 2000-2009 Martin Prikryl  
    Based on WinSCP version 4.3.6 Copyright (c) 2000-2011 Martin Prikryl  
    SSH and SCP code based on PuTTY 0.62 Copyright (c) 1997-2011 Simon Tatham  
    FTP code based on FileZilla 2.2.32 Copyright (c) 2001-2007 Tim Kosse  

HOW TO INSTALL
==============

You can either download an appropriate binary package for your  
platform or build from source. Binaries can be obtained from  
[here](https://github.com/michaellukashov/Far-NetBox/downloads/). 

Unpack the archive in the plugin directory Far (... Far \ Plugins).

HOW TO BUILD FROM SOURCE
========================

1.  Download the source:

    You can either download a release source zip ball from the [tags
    page](https://github.com/michaellukashov/Far-NetBox/tags) and unpack it in your
    source directory say C:/src  
    or from git repository:

        cd C:/src
        git clone git://github.com/michaellukashov/Far-NetBox.git

    From now on, we assume that your source tree is C:/src/Far-NetBox

2.  Compile boost libraries:
    
    Boost 1.48.0 or later is required to build NetBox.  
    You can download the source code for boost  
    from [download page](http://sourceforge.net/projects/boost/files/boost/1.48.0/).

    Unpack archive to directory C:/src/Far-NetBox/libs

    Compile bjam:

        cd libs/boost/tools/build/v2/engine
        call build.bat

    Copy the resulting bjam.exe binary (located in libs/boost/tools/build/v2/engine/bin.ntx86)  
    to some directory which is listed in %PATH% variable, say C:/Windows

        mkdir libs/boost/stage

    Compile date_time:

        cd libs/boost/libs/date_time/build

        call bjam variant=debug link=static threading=multi runtime-debugging=on stage -j3
        cp -R libs/boost/libs/date_time/build/stage/* libs/boost/stage/

    Compile signals:

        cd libs/boost/libs/signals/build
        call bjam variant=debug link=static threading=multi runtime-debugging=on stage -j3
        cp -R libs/boost/libs/signals/build/stage/* libs/boost/stage/

3. Compile openssl:

        cd libs/openssl
        call src/NetBox/scripts/build_openssl.bat x86
        call src/NetBox/scripts/build_openssl.bat x64

4. Compile NetBox plugin:

        cmd /c %VS100COMNTOOLS%\vsvars32.bat && devenv NetBox.sln /Build "Debug|Win32" /USEENV /Project "NetBox"

DISCLAIMER
========================

This plugin is provided "as is". The authors are not responsible for the  
consequences of use of this software.

LINKS
========================

* Project main page: [https://github.com/michaellukashov/Far-NetBox/](https://github.com/michaellukashov/Far-NetBox/)
* Download page: [https://github.com/michaellukashov/Far-NetBox/downloads/](https://github.com/michaellukashov/Far-NetBox/downloads/)
* Far Manager forum: [http://forum.farmanager.com/](http://forum.farmanager.com/)
