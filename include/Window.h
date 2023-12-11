#pragma once
#include "Platform.h"
#define WINDOW_ENUMS
#define WINDOW_STRUCTS
#include "Structs.h"

class Window final {
public:
    Window(SWindowData data)  : Data(data), TargetPlatform(TARGET_PLATFORM) {
        LoadModule(WINDOW_DLL);
        CallModuleFuncWithArgs(WINDOW_DLL, "CreateAndRunWindow"); // This Works
        CallModuleFuncWithArgs<std::string>(WINDOW_DLL, "WIN32_TestMessage", "Testing"); // This fails
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
};
