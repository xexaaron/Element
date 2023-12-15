@echo off
setlocal enabledelayedexpansion

REM Using the 'date' command to get the current date (MM/DD/YYYY format)
for /F "usebackq tokens=1-3" %%A in (`powershell Get-Date -Format "yyyy-MM-dd"`) do (
    set "year=%%A"
    set "month=%%B"
    set "day=%%C"
)
set "currentDate=!year!-!month!-!day!"
set "currentDate=!currentDate:~0,-2!"

rem Process all .txt files in the script directory
for %%F in (*.txt-%currentDate%) do (
    set "inputFile=%%~nF.txt-%currentDate%"
    set "outputFile=%%~nF.txt-%currentDate%"

    powershell -Command "$content = Get-Content -Path '!inputFile!' -Raw; $content -replace '\x1B\[[0-9;]*[A-Za-z]', '' | Set-Content -Path '!outputFile!'"

    echo ANSI escape codes removed from %%F and saved to !outputFile!
)