#!/bin/bash

projName="Window"
scriptDir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CMProjName="$projName"


# Build Core Module and the Core Module dependencies
echo ""
echo "Building DLL : Window"
echo ""
cmake -S . -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

# Determine post-build state
if [ $? -eq 0 ]; then
    echo ""
    echo "Build successful"
else
    echo "Build failed!"
fi

