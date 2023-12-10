#!/bin/bash

projName="Element"
scriptDir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CMProjName="$projName"
toolsDir="$scriptDir/Tools"

if [ -d "$toolsDir/Super" ]; then
    (
    cd "$toolsDir/Super" || exit
    python3 SuperGen.py
    python3 SuperImpl.py
  )
fi

# Build Core Module and the Core Module dependencies
echo ""
echo "Building Executable: Engine"
echo ""
cmake -S . -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

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

