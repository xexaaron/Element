#pragma once
#include "Platform.h"
#define WINDOW_ENUMS
#define WINDOW_STRUCTS
#include "Structs.h"

class Window final {
public:
    Window(SWindowData data)  : Data(data), TargetPlatform(TARGET_PLATFORM) {
        LoadModule(WINDOW_DLL);
        WIN32_CALL_MODULE_FUNCTION_ARGS<void, std::string>(WINDOW_DLL, "WIN32_TestMessage", "Testing"); 
        CallModuleFunc(WINDOW_DLL, "CreateAndRunWindow"); 
        
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
