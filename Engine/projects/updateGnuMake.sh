#!/bin/sh
mkdir -p GnuMake-X86-Debug
mkdir -p GnuMake-X86-Release

echo Generate 32 bit Debug
echo =====================
cd GnuMake-X86-Debug
cmake -G "Unix Makefiles" --config Debug -DDEBUG_BUILD:BOOL=TRUE ../cmake 
echo Generate 32 bit Release
echo =======================
cd ../GnuMake-X86-Release                              
cmake -G "Unix Makefiles" --config Release -DDEBUG_BUILD:BOOL=FALSE ../cmake 
cd ../

