@echo off
msbuild Window.sln /p:Configuration=Release
msbuild Window.sln /p:Configuration=Debug


./Export.bat
