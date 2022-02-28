set rootDir=%~dp0

call F:\qt\6.2.3\msvc2019_64\bin\qtenv2.bat

cd /d %rootDir%

python build.py

pause