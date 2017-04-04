if not exist "msvc2015-X86" mkdir msvc2015-X86
if not exist "msvc2015-X64" mkdir msvc2015-X64

cd msvc2015-X86
cmake -G "Visual Studio 14 2015" -DUSE_64_BIT:BOOL=FALSE ..\cmake 
cd ..\msvc2015-X64
cmake -G "Visual Studio 14 2015 Win64" -DUSE_64_BIT:BOOL=TRUE ..\cmake 
cd ..