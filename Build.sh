#!/bin/bash

projName="Element"
scriptDir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
buildConfig="Release"
loggingFlag="false"
verboseFlag="false"

if [ -d "$toolsDir/Super" ]; then
    (
    cd "$toolsDir/Super" || exit
    python3 SuperGen.py
    python3 SuperImpl.py
  )
fi

# Process arguments
while [ "$1" != "" ]; do
    case $1 in
        -r)
            buildConfig="Release"
            ;;
        -d)
            buildConfig="Debug"
            ;;
        -l)
            loggingFlag="true"
            ;;
        -v)
            verboseFlag="true"
            ;;
        *)
            echo "Invalid argument: $1"
            ;;
    esac
    shift
done

echo "[Build - %buildConf] [true]"
echo "[Flag - Logging]  [${loggingFlag}]"
echo "[Flag - Verbose]  [${verboseFlag}]"

# Build Core Module and the Core Module dependencies
echo ""
echo "Building Executable: $projName [$buildConfig]"
echo ""

cmake -S . -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="$buildConfig" -DLOGGING="$loggingFlag" -DVERBOSE="$verboseFlag"
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

