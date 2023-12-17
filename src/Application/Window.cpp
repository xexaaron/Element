#include "../../include/Window.h"

Window::Window(SWindowData data)  : Data(data) {
        LoadModule(WINDOW_DLL);
        CallModuleFuncAsync<int>(WINDOW_DLL, AppendPlatform("CreateAndRunWindow"), WINDOW_PROCESS);
}

Window::~Window() {
    UnloadModule(WINDOW_DLL);
}

void Window::SetPixelColor(Vector2D<int> Coord, Vector3D<uint32_t> Color) {
    CallModuleFuncWithArgsAsync<int8_t, int, int, uint32_t, uint32_t, uint32_t>(WINDOW_DLL, AppendPlatform("SetWindowPixel"), RENDER_PROCESS,
    Coord.x, Coord.y, Color.x, Color.y, Color.z);
}

void Window::SendTestMessageToWindow(std::string Message) {
    CallModuleFuncWithArgsAsync<int8_t, std::string>(WINDOW_DLL, AppendPlatform("TestMessage"), RENDER_PROCESS, Message);
}

void Window::SetBackgroundColor(Vector3D<uint32_t> color) {
    CallModuleFuncWithArgsAsync<int8_t, uint32_t, uint32_t, uint32_t>(WINDOW_DLL, AppendPlatform("SetWindowColor"), RENDER_PROCESS, color.x, color.y, color.z);
    Data.BackgroundColor = color;
}


void Window::SetTitle(const char* title) {
    CallModuleFuncWithArgsAsync<int8_t, const char*>(WINDOW_DLL, AppendPlatform("SetWindowTitle"), RENDER_PROCESS, title);
    Data.Title = title;
}
void Window::SetState(EWindowState state) {
    CallModuleFuncWithArgsAsync<int8_t, EWindowState>(WINDOW_DLL, AppendPlatform("SetWindowState"), RENDER_PROCESS, state);
    Data.State = state;
} 

void Window::SetPosition(Vector2D<int> position) {
    CallModuleFuncWithArgsAsync<int8_t, int, int>(WINDOW_DLL, AppendPlatform("SetWindowPosition"), RENDER_PROCESS, position.x, position.y);
    Data.Position = position;
}
void Window::SetSize(Vector2D<int> size) {
    CallModuleFuncWithArgsAsync<int8_t, int, int>(WINDOW_DLL, AppendPlatform("SetWindowSize"), RENDER_PROCESS, size.x, size.y);
    Data.Size = size;
}
void Window::SetData(SWindowData data) {
    SetBackgroundColor(data.BackgroundColor);
    SetTitle(data.Title);
    SetState(data.State);
    SetPosition(data.Position);
    SetSize(data.Size);
    data = data;
}

Vector2D<uint16_t> Window::GetDeviceSize() {
    SYSAGN_WORD Word = CallModuleFunc<SYSAGN_WORD>(WINDOW_DLL, AppendPlatform("GetDeviceDimensions"));
    return UnpackSystemAgnosticNumericWord(Word);
} 

Vector2D<int> Window::GetPosition() {
    return Vector2D<int>(Data.Position.x, Data.Position.y);
}
Vector2D<int> Window::GetSize() {
    return Vector2D<int>(Data.Size.x, Data.Size.y);
}
EWindowState Window::GetWindowState() {
    return EWindowState(Data.State);
}
SWindowData Window::GetData() {
    return SWindowData(Data);
}