#pragma once
#include "Platform.h"
#include "Structs.h"
#include "../config.h"
#include <cstdint>

class Window final {
public:
    Window(SWindowData data)  : Data(data), TargetPlatform(TARGET_PLATFORM) {
        if (TargetPlatform == "Windows") {
            TargetPlatform = "WIN";
        } else if (TargetPlatform == "Linux") {
            TargetPlatform = "UNIX";
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
    bool SetTitle(const char* Title);
    bool SetBackgroundColor(Vector3D<uint32_t> Color); 

    Vector3D<uint32_t> GetBackgroundColor();
    const char* GetTitle();
    Vector2D<int> GetPosition();
    Vector2D<int> GetSize();
    EWindowState GetWindowState();
    SWindowData GetData();
private:
    SWindowData Data;
    std::string TargetPlatform;
    const char* AppendPlatform(std::string stringToAppend);
};
