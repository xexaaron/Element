@echo off

REM Set default values

SET DESTINATION=..\..\Modules\Windows\Window.dll
SET VERSION=Release

REM Check for command line options
IF "%~1"=="-r" (
    SET VERSION=Release
) ELSE IF "%~1"=="-d" (
    SET VERSION=Debug
)

SET SOURCE=x64\%VERSION%\Window.dll
REM Copy the file
COPY "%SOURCE%" "%DESTINATION%"

echo File copied from %SOURCE% to %DESTINATION%