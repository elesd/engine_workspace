@echo off

set BUILD_DIR="..\build"
set DATA_DIR="%BUILD_DIR%\data"
set SHADER_DIR="%DATA_DIR%\shaders"

if not exist "%DATA_DIR%" mkdir %DATA_DIR%

echo "Copy shaders ..."
xcopy /E /Q /I /Y shaders "%DATA_DIR%\shaders"

pause
