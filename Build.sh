#!/bin/bash

projName="Element"
scriptDir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CMProjName="$projName"
toolsDir="$scriptDir/Tools"
buildConfig="Release"

if [ -d "$toolsDir/Super" ]; then
    (
    cd "$toolsDir/Super" || exit
    python3 SuperGen.py
    python3 SuperImpl.py
  )
fi

if [ "$1" == "-r" ]; then
    buildConfig="Release"
elif [ "$1" == "-d" ]; then
    buildConfig="Debug"
fi

# Build Core Module and the Core Module dependencies
echo ""
echo "Building Executable: $projName [$buildConfig]"
echo ""

cmake -S . -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="$buildConfig"
cmake --build build --config "$buildConfig"

# Determine post-build state
if [ $? -eq 0 ]; then
    echo ""
    echo "Build successful"
    mv "$scriptDir/build/$projName" "$scriptDir"
    if [ -d "$toolsDir/Super" ]; then
      (
      cd "$toolsDir/Super" || exit
      python3 SuperLog.py
      )
    fi
else
    echo "Build failed!"
fi

if [ -d "$toolsDir/Super" ]; then
    (
    cd "$toolsDir/Super" || exit
    python3 SuperDestruct.py
  )
fi

