#!/bin/bash

VERSION="Release"

if [ "$1" = "-r" ]; then
    VERSION="Release"
elif [ "$1" = "-d" ]; then
    VERSION="Debug"
fi

SOURCE="build/libWindow.so"
DESTINATION="../../Modules/Linux/$VERSION/libWindow.so"
cp "$SOURCE" "$DESTINATION"

echo "File copied from $SOURCE to $DESTINATION"