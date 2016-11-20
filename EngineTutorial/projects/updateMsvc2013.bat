if not exist "msvc2013-X32-Debug" mkdir msvc2013-X32-Debug
if not exist "msvc2013-X32-Release" mkdir msvc2013-X32-Release
if not exist "msvc2013-X64-Debug" mkdir msvc2013-X64-Debug
if not exist "msvc2013-X64-Release" mkdir msvc2013-X64-Release
cd msvc2013-X32-Debug
cmake -G "Visual Studio 12 2013" --config Debug -DDEBUG_BUILD:BOOL=TRUE ..\cmake 
cd ..\msvc2013-X32-Release                              
cmake -G "Visual Studio 12 2013" --config Release -DDEBUG_BUILD:BOOL=FALSE ..\cmake 
cd ..\msvc2013-X64-Debug                                
cmake -G "Visual Studio 12 2013 Win64" --config Debug -DUSE_64_BIT:BOOL=TRUE -DDEBUG_BUILD:BOOL=TRUE ..\cmake 
cd ..\msvc2013-X64-Release                              
cmake -G "Visual Studio 12 2013 Win64" --config Release -DUSE_64_BIT:BOOL=TRUE -DDEBUG_BUILD:BOOL=FALSE ..\cmake 
cd ..