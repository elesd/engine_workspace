cd msvc2013-X32
cmake -G "Visual Studio 12 2013" -DUSE_64_BIT:BOOL=FALSE ..\cmake 
cd ..\msvc2013-X64
cmake -G "Visual Studio 12 2013 Win64" -DUSE_64_BIT:BOOL=TRUE ..\cmake 
cd ..