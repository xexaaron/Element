#include "../../include/Window.h"

Window::Window(SWindowData data)  : Data(data), TargetPlatform(TARGET_PLATFORM) {
        if (TargetPlatform == "Windows") {
            TargetPlatform = "WIN32_";
        } else if (TargetPlatform == "Linux") {
            TargetPlatform = "UNIX_";
        }
        LoadModule(WINDOW_DLL);
        CallModuleFuncAsync<void>(WINDOW_DLL, AppendPlatform("CreateAndRunWindow"), WINDOW_PROCESS);
}

Window::~Window() {
    UnloadModule(WINDOW_DLL);
}

const char* Window::AppendPlatform(std::string stringToAppend) {
    std::string temp = TargetPlatform + stringToAppend; 
    char* value = new char[temp.length() + 1]; 
    std::strcpy(value, temp.c_str()); 
    return value;
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