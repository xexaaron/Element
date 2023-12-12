@echo off
set "projName=Element"
set "scriptDir=%~dp0"

REM Set default build configuration to Release
set "buildConfig=Release"

REM Check for command-line arguments
if "%~1" == "-r" (
    set "buildConfig=Release"
) else if "%~1" == "-d" (
    set "buildConfig=Debug"
)

echo.
echo Building Executable: %projName% [%buildConfig%]
echo.

cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=%buildConfig%
cmake --build build --config %buildConfig%

REM Determine post-build state
if %errorlevel% equ 0 (
    echo.
    echo Build successful
    move /Y "%scriptDir%\build\%buildConfig%\%projName%.exe" "%scriptDir%" >nul
) else (
    echo Build failed!
    exit /b %errorlevel%
)