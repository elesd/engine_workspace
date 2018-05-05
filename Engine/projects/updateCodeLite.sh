#!/bin/sh
mkdir -p CodeLite-X86-Debug
mkdir -p CodeLite-X86-Release

echo Generate 32 bit Debug
echo =====================
cd CodeLite-X86-Debug
cmake -G "CodeLite - Unix Makefiles" --config Debug -DDEBUG_BUILD:BOOL=TRUE ../cmake 
echo Generate 32 bit Release
echo =======================
cd ../CodeLite-X86-Release                              
cmake -G "CodeLite - Unix Makefiles" --config Release -DDEBUG_BUILD:BOOL=FALSE ../cmake 
cd ../

