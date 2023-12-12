@echo off

SET VERSION=Release
SET SOURCE=x64\%VERSION%\Window.dll
SET DESTINATION=..\..\Modules\Windows\%VERSION%\Window.dll
COPY "%SOURCE%" "%DESTINATION%"

echo File copied from %SOURCE% to %DESTINATION%

SET VERSION=Debug
SET SOURCE=x64\%VERSION%\Window.dll
SET DESTINATION=..\..\Modules\Windows\%VERSION%\Window.dll
COPY "%SOURCE%" "%DESTINATION%"

echo File copied from %SOURCE% to %DESTINATION%