@echo off
if not exist "msvc2015-X86-Debug" mkdir msvc2015-X86-Debug
if not exist "msvc2015-X86-Release" mkdir msvc2015-X86-Release
if not exist "msvc2015-X64-Debug" mkdir msvc2015-X64-Debug
if not exist "msvc2015-X64-Release" mkdir msvc2015-X64-Release

echo Generate 32 bit Debug
echo =====================
cd msvc2015-X86-Debug
cmake -G "Visual Studio 14 2015" --config Debug -DDEBUG_BUILD:BOOL=TRUE ..\cmake 
echo Generate 32 bit Release
echo =======================
cd ..\msvc2015-X86-Release                              
cmake -G "Visual Studio 14 2015" --config Release -DDEBUG_BUILD:BOOL=FALSE ..\cmake 
echo Generate 64 bit Debug
echo =====================
cd ..\msvc2015-X64-Debug                                
cmake -G "Visual Studio 14 2015 Win64" --config Debug -DUSE_64_BIT:BOOL=TRUE -DDEBUG_BUILD:BOOL=TRUE ..\cmake 
echo Generate 64 bit Release
echo =======================
cd ..\msvc2015-X64-Release                              
cmake -G "Visual Studio 14 2015 Win64" --config Release -DUSE_64_BIT:BOOL=TRUE -DDEBUG_BUILD:BOOL=FALSE ..\cmake 
cd ..
pause