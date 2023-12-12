#pragma once
#include "Platform.h"
#define WINDOW_ENUMS
#define WINDOW_STRUCTS
#include "Structs.h"
#include "ThreadManager.h"

class Window final {
public:
    Window(SWindowData data)  : Data(data), TargetPlatform(TARGET_PLATFORM) {
        if (TargetPlatform == "Windows") {
            TargetPlatform = "WIN32_";
        } else if (TargetPlatform == "Linux") {
            TargetPlatform = "UNIX_";
        }
        LoadModule(WINDOW_DLL);
        CallModuleFuncAsync<void>(WINDOW_DLL, "CreateAndRunWindow", WINDOW_PROCESS);
    }
    ~Window() {
        UnloadModule(WINDOW_DLL);
    }
    
    bool SetState(EWindowState State);
    bool SetPosition(Vector2D<int> Position);
    bool SetSize(Vector2D<int> Size);
    bool SetData(SWindowData Data);

    Vector2D<int> GetPosition();
    Vector2D<int> GetSize();
    EWindowState GetWindowState();
    SWindowData GetData();
private:
    SWindowData Data;
    std::string TargetPlatform;
    const char* AppendPlatform(std::string stringToAppend);
};
