@echo off
echo "Creating directory"
if not exist "build" mkdir build
if not exist "build\data" mkdir build\data

echo "Copy files"
xcopy /y data\* build\data

pause