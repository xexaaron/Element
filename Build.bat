@echo off
set "projName=Element"
set "scriptDir=%~dp0"

REM Set default build configuration to Release
set "buildConfig=Release"

REM Set default logging and verbose flags to OFF
set "loggingFlag=false"
set "verboseFlag=false"

:ProcessArgs
if "%~1" == "" goto :ContinueBuild

if "%~1" == "-r" (
    set "buildConfig=Release"
) else if "%~1" == "-d" (
    set "buildConfig=Debug"
) else if "%~1" == "-l" (
    set "loggingFlag=true"
) else if "%~1" == "-v" (
    set "verboseFlag=true"
)

shift
goto :ProcessArgs

:ContinueBuild
echo [Build - %buildConfig%] [true]
echo [Flag - Logging]  [%loggingFlag%]
echo [Flag - Verbose]  [%verboseFlag%]
echo.
echo Building Executable: %projName% [%buildConfig%]
echo.

cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=%buildConfig% -DLOGGING=%loggingFlag% -DVERBOSE=%verboseFlag%
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