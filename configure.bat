set rootDir=%~dp0

call D:\Qt\Qt5.14.2\5.14.2\msvc2015_64\bin\qtenv2.bat

cd /d %rootDir%

python3 build.py

pause