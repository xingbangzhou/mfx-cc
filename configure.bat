set rootDir=%~dp0
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
call G:\qt\6.2.3\msvc2019_64\bin\qtenv2.bat

cd /d %rootDir%

python build.py

pause