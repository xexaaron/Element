#pragma once
#include "Platform.h"
#include "Structs.h"
#include "../config.h"
#include <cstdint>
#include <future>
#include "Logger.h"

class Window final {
public:
    Window(SWindowData data);
    ~Window();
    

    void SetPixelColor(Vector2D<int> Coord, Vector3D<uint32_t> Color);
    void SendTestMessageToWindow(std::string Message);
    void SetState(EWindowState State);
    void SetPosition(Vector2D<int> Position);
    void SetSize(Vector2D<int> Size);
    void SetData(SWindowData Data);
    void SetTitle(const char* Title);
    void SetBackgroundColor(Vector3D<uint32_t> Color); 
    
    Vector3D<uint32_t> GetBackgroundColor();
    const char* GetTitle();
    Vector2D<int> GetPosition();
    Vector2D<int> GetSize();
    Vector2D<uint16_t> GetDeviceSize();
    EWindowState GetWindowState();
    SWindowData GetData();
private:
    SWindowData Data;
    
};
