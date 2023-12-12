@echo off

SET VERSION=Release

IF "%~1"=="-r" (
    SET VERSION=Release
) ELSE IF "%~1"=="-d" (
    SET VERSION=Debug
)

SET SOURCE=x64\%VERSION%\Window.dll
SET DESTINATION=..\..\Modules\Windows\%VERSION%\Window.dll
COPY "%SOURCE%" "%DESTINATION%"

echo File copied from %SOURCE% to %DESTINATION%