echo CREATING PACKAGE DIR

echo OUTDIR=%_OUTDIR%
echo PROJECTDIR=%_PROJECTDIR%
echo TARGETNAME=%_TARGETNAME%
echo CONFIGURATION=%_CONFIGURATION%

set SCRIPTDIR=%CD%\scripts
cd "%_OUTDIR%"
cd ..
rmdir /S /Q "%_TARGETNAME%"
mkdir "%_TARGETNAME%"
cd "%_TARGETNAME%"
set PACKAGEDIR=%CD%

echo COPYING RUNTIME FILES

copy "%_OUTDIR%\%_TARGETNAME%.exe" "%PACKAGEDIR%\" > nul
xcopy /E "%_PROJECTDIR%\..\..\runtime\*" . > nul

echo COPYING BASS LIBRARY
copy "%BASSDIR%\bass.dll" "%PACKAGEDIR%\"

if not "%_CONFIGURATION%"=="Release" goto notrelease
rem pack the release exes
echo PACKING EXE WITH UPX
"%SCRIPTDIR%\upx.exe" -9 "%PACKAGEDIR%\%_TARGETNAME%.exe"
:notrelease
