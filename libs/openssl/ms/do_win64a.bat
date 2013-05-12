perl util\mkfiles.pl >MINFO

cmd /c "nasm -f win64 -v" >NUL: 2>&1
if not %errorlevel% == 0 goto ml64

perl ms\uplink-x86_64.pl nasm > ms\uptable.asm
nasm -f win64 -o ms\uptable.obj ms\uptable.asm
goto proceed

:ml64
perl ms\uplink-x86_64.pl masm > ms\uptable.asm
ml64 -c -Foms\uptable.obj ms\uptable.asm

:proceed
perl util\mk1mf.pl no-cast no-err no-bf no-sctp no-ec2m no-rsax VC-WIN64A >ms\nt.mak
perl util\mk1mf.pl dll VC-WIN64A >ms\ntdll.mak

perl util\mkdef.pl 32 libeay > ms\libeay32.def
perl util\mkdef.pl 32 ssleay > ms\ssleay32.def
