@echo off

if not exist "msvc2015-X86-Debug" mkdir msvc2015-X86-Debug
if not exist "msvc2015-X64-Debug" mkdir msvc2015-X64-Debug 


echo Generate 32 bit Debug
echo =====================
cd msvc2015-X86-Debug
cmake -G "Visual Studio 14 2015" --config Debug -DDEBUG_BUILD:BOOL=TRUE ..\cmake 
echo Generate 64 bit Debug
echo =====================
cd ..\msvc2015-X64-Debug                                
cmake -G "Visual Studio 14 2015 Win64" --config Debug -DUSE_64_BIT:BOOL=TRUE -DDEBUG_BUILD:BOOL=TRUE ..\cmake 
cd ..
pause
