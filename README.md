# README.md

# Build Scripts

## [Windows](./Build.bat)

<details closed>

<summary>Collapse</summary>

- Windows Batch Script
- Build "Visual Studio 17 2022"
- Flags [ -d | -r ] [ -v ] [ -l <console|file|both> ]
  - [ -d | -r ]: Specifies the cmake build type. Relase | Debug. Defaults to release.
  - [ -v ]: Defines preprocessor condition VERBOSE (logging). e.g. base types, full file paths.
  - [ -l <console|file|both> ]: Defines preprocessor condition LOGGING. 
    - Ensure this is the last flag passed to the build script
    - Ensure you pass a value such as console, file, or both to the -l flag.

</details>

## [Linux](./Build.sh)

<details closed>

<summary>Collapse</summary>

- Linux Shell Script
  - Build "Unix Makefiles"
  - Flags [ -d | -r ] [ -l ] [ -v ]
    - [ -d | -r ]: Specifies the cmake build type. Relase | Debug. Defaults to release.
    - [ -l ]: Defines preprocessor condition LOGGING.
    - [ -v ]: Defines preprocessor condition VERBOSE (logging). e.g. base types, full file paths.
  - Additional Tasks
    - Task : Super
        - [Super Documentation](./Tools/Super/README.md)
        - [Github Repository](https://Github.com/Xexaaron/CPP-Super-Keyword)
        - [SuperGen.py](./Tools/Super/SuperGen.py)
        - [SuperImpl.py](./Tools/Super/SuperImpl.py)
        - [SuperLog.py](./Tools/Super/SuperLog.py)
        - [SuperDestruct.py](./Tools/Super/SuperDestruct.py)

</details>



