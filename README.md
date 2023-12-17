# README.md

## Build Scripts

### [Windows](./Build.bat) 
<details closed>

<summary>Details</summary>

- Windows Batch Script
- Build Project Executable using [CMake](./CMakeLists.txt) (Visual Studio 17 2022)
- Flags [ -d | -r ] [ -v ] [ -l <console|file|both> ]

  <details closed>
  <summary>Flags</summary>

  - [ -d | -r ]:<pre>Specifies the cmake build type. Relase | Debug. Defaults to release.</pre>
  - [ -v ]:<pre>Defines preprocessor condition VERBOSE (logging). e.g. base types, full file paths.</pre>
  - [ -l <console|file|both> ]:<pre>Defines preprocessor condition LOGGING.</br><pre>Ensure this is the last flag passed to the build script</pre></br><pre>Ensure you pass a value such as console, file, or both to the -l flag.</pre></br><pre>File logging outputs to the [Log Directory](./build/Logs/) with files named {project name}-{system platform}-log.txt-{date}</pre></pre><pre></br><pre>Run CleanupAnsi.bat to strip the ansi text attributes from the log files.</pre></br></pre>

  </details>

- Additional Tasks
  - Build Module dlls using [Batch](./Window/Windows/Build.bat) with [MSBuild](https://learn.microsoft.com/en-us/visualstudio/msbuild/msbuild-command-line-reference?view=vs-2022)
</details>

### [Linux](./Build.sh)

<details closed>

<summary>Details</summary>

- Linux Shell Script
  -  Build Project Executable using cmake (Unix Makefiles)
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



