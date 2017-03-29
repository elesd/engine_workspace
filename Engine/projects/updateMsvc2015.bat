if not exist "msvc2015-X32-Debug" mkdir msvc2015-X32-Debug
if not exist "msvc2015-X32-Release" mkdir msvc2015-X32-Release
if not exist "msvc2015-X64-Debug" mkdir msvc2015-X64-Debug
if not exist "msvc2015-X64-Release" mkdir msvc2015-X64-Release

cd msvc2015-X32-Debug
cmake -G "Visual Studio 14 2015" --config Debug -DDEBUG_BUILD:BOOL=TRUE ..\cmake 
cd ..\msvc2015-X32-Release                              
cmake -G "Visual Studio 14 2015" --config Release -DDEBUG_BUILD:BOOL=FALSE ..\cmake 
cd ..\msvc2015-X64-Debug                                
cmake -G "Visual Studio 14 2015 Win64" --config Debug -DUSE_64_BIT:BOOL=TRUE -DDEBUG_BUILD:BOOL=TRUE ..\cmake 
cd ..\msvc2015-X64-Release                              
cmake -G "Visual Studio 14 2015 Win64" --config Release -DUSE_64_BIT:BOOL=TRUE -DDEBUG_BUILD:BOOL=FALSE ..\cmake 
cd ..