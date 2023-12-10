@echo off
set "projName=Element"
set "scriptDir=%~dp0"

REM Build Core Module and the Core Module dependencies
echo.
echo Building Executable: Engine
echo.
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 
cmake --build build --config Release

REM Determine post-build state
if %errorlevel% equ 0 (
    echo.
    echo Build successful
    move "%scriptDir%\build\Release\%projName%.exe" "%scriptDir%"
    rmdir "%scriptDir%\build\Release"
) else (
    echo Build failed!
)