#!/bin/bash

projName="Element"
scriptDir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
buildConfig="Release"
loggingFlag="false"
verboseFlag="false"
consoleLoggingFlag="false"
fileLoggingFlag="false"

usage() {
    echo "Usage: $0 [-r | -d] [-l] [-v]"
    echo "  -r    Set build configuration to Release (default)"
    echo "  -d    Set build configuration to Debug"
    echo "  -l    Enable logging"
    echo "  -v    Enable verbosity"
    exit 1
}

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
            shift
            if [ "$1" == "console" ]; then
                consoleLoggingFlag="true"
            elif [ "$1" == "file" ]; then
                fileLoggingFlag="true"
            elif [ "$1" == "both" ]; then
                consoleLoggingFlag="true"
                fileLoggingFlag="true"
            else
                echo. 
                echo "Invalid logging option: $1. Use 'console', 'file', or 'both'."
                echo. 
                usage
                exit 1
            fi
            ;;
        -v)
            verboseFlag="true"
            ;;
        *)
            echo. 
            echo "Invalid argument"
            echo.
            usage
            ;;
    esac
    shift
done

echo "[Build - $buildConfig] [true]"
echo "[Flag - Verbose] [$verboseFlag]"
echo "[Flag - Logging] [$loggingFlag]"
echo "-- [Console Logging] [$consoleLoggingFlag]"
echo "-- [File Logging] [$fileLoggingFlag]"

# Build Core Module and the Core Module dependencies
echo ""
echo "Building Executable: $projName [$buildConfig]"
echo ""

cmake -S . -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="$buildConfig" -DLOGGING="$loggingFlag" -DVERBOSE="$verboseFlag" -DFILE_LOGGING="$fileLoggingFlag" -DCONSOLE_LOGGING="$consoleLoggingFlag"
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
