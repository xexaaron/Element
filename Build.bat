@echo off
set "projName=Element"
set "scriptDir=%~dp0"

REM Set default build configuration to Release
set "buildConfig=Release"

REM Set default logging and verbose flags to OFF
set "loggingFlag=false"
set "verboseFlag=false"
set "consoleLoggingFlag=false"
set "fileLoggingFlag=false"


cd "Window/Windows"
call Build.bat
cd ".."
cd ".."


:ProcessArgs
if "%~1" == "" goto :ContinueBuild 

if "%~1" == "-r" (
    set "buildConfig=Release"
) else if "%~1" == "-d" (
    set "buildConfig=Debug"
) else if "%~1" == "-v" (
    set "verboseFlag=true"
) else if "%~1" == "-l" (
    if not "%~3" == "" (
        echo.
        echo Invalid Usage. Ensure -l ^<file^|console^|both^> is the last flag passed.
        echo.
        echo Usage  ./Build.bat [-d ^| -r] [-v] [-l ^<file^|console^|both^>]
        echo        [-d ^| -r]                 [Build Type]  Optional, default : release  
        echo        [-v]                      [Verbose]     Optional, default : false 
        echo        [-l ^<file^|console^|both^>]  [Logging]     Optional, default : false
        echo                                                Provide logging output destination.
        echo                                                Must be the last argument passed.
        exit /b 1
    )
    set "loggingFlag=true"
    if "%~2" == "file" (
        set "fileLoggingFlag=true"
        shift
    ) else if "%~2" == "console" (
        set "consoleLoggingFlag=true"
        shift
    ) else if "%~2" == "both" (
        set "consoleLoggingFlag=true"
        set "fileLoggingFlag=true"
        shift
    ) else (
                echo.
        echo Invalid Usage. Ensure a value is passed to flag -l ^<file^|console^|both^>.
        echo.
        echo Usage  ./Build.bat [-d ^| -r] [-v] [-l ^<file^|console^|both^>]
        echo        [-d ^| -r]                 [Build Type]  Optional, default : release  
        echo        [-v]                      [Verbose]     Optional, default : false 
        echo        [-l ^<file^|console^|both^>]  [Logging]     Optional, default : false
        echo                                                Provide logging output destination.
        echo                                                Must be the last argument passed.
        exit /b 1
    )
    shift
)  

shift
goto :ProcessArgs

:ContinueBuild

REM Align spaces depending on build type.
if "%buildConfig%"=="Release" (
    echo [Build - Release]     [true]
    echo [Flag - Verbose]      [%verboseFlag%]
    echo [Flag - Logging]      [%loggingFlag%]
    echo  -- [Console Logging] [%consoleLoggingFlag%]
    echo  -- [File Logging]    [%fileLoggingFlag%]
) else if "%buildConfig%"=="Debug" (
    echo [Build - Debug]        [true]
    echo [Flag - Verbose]       [%verboseFlag%]
    echo [Flag - Logging]       [%loggingFlag%]
    echo  -- [Console Logging]  [%consoleLoggingFlag%]
    echo  -- [File Logging]     [%fileLoggingFlag%]
)


echo.
echo Building Executable: %projName% [%buildConfig%]
echo.

cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=%buildConfig% -DLOGGING=%loggingFlag% -DVERBOSE=%verboseFlag% -DFILE_LOGGING=%fileLoggingFlag% -DCONSOLE_LOGGING=%consoleLoggingFlag%
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