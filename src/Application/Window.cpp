#include "../../include/Window.h"

Window::Window(SWindowData data)  : Data(data), TargetPlatform(TARGET_PLATFORM) {
        if (TargetPlatform == "Windows") {
            TargetPlatform = "WIN";
        } else if (TargetPlatform == "Linux") {
            TargetPlatform = "UNIX";
        }
        LoadModule(WINDOW_DLL);
        CallModuleFuncAsync<void>(WINDOW_DLL, "CreateAndRunWindow", WINDOW_PROCESS);
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
    int8_t result = CallModuleFuncWithArgsAsync<int8_t, std::string>(WINDOW_DLL, AppendPlatform("TestMessage"), MAIN_PROCESS, Message);
}

<<<<<<< HEAD
void Window::SetBackgroundColor(Vector3D<uint32_t> color) {
    int8_t result = CallModuleFuncWithArgsAsync<int8_t, uint32_t, uint32_t, uint32_t>(WINDOW_DLL, AppendPlatform("SetWindowColor"), MAIN_PROCESS, color.x, color.y, color.z);
    Data.BackgroundColor = color;
=======
bool Window::SetBackgroundColor(Vector3D<uint32_t> color) {
    int8_t result = CallModuleFuncWithArgsAsync<int8_t, uint32_t, uint32_t, uint32_t>(
    WINDOW_DLL, AppendPlatform("SetWindowColor"), MAIN_PROCESS, color.x, color.y, color.z);
    if (result == FUNCTION_SUCCESS) {
        Data.BackgroundColor = color;
    #ifdef LOGGING
        Logger::Log(stdout, LogType::ASYNC_TASK, MAIN_PROCESS, "Window::SetBackgroundColor(Vector3D<uint32_t>) -> FUNCTION_SUCCESS");
    #endif // LOGGING
        return true;
    } else if (result == FUNCTION_FAILURE) {
    #ifdef LOGGING
        Logger::Log(stderr, LogType::ASYNC_TASK, MAIN_PROCESS, "Window::SetBackgroundColor(Vector3D<uint32_t>) -> FUNCTION_FAILURE && WM_NULL ");  
    #endif // LOGGING
        return false;
    }
   
    return true; 
>>>>>>> 20e9b908268a7eefc57571943b7e9584651f2f86
}

void Window::SetTitle(const char* title) {
    int8_t result = CallModuleFuncWithArgsAsync<int8_t, const char*>(WINDOW_DLL, AppendPlatform("SetWindowTitle"), MAIN_PROCESS, title);
    Data.Title = title;
}
void Window::SetState(EWindowState state) {
    int8_t result = CallModuleFuncWithArgsAsync<int8_t, EWindowState>(WINDOW_DLL, AppendPlatform("SetWindowState"), MAIN_PROCESS, state);
    Data.State = state;
} 

void Window::SetPosition(Vector2D<int> position) {
    int8_t result = CallModuleFuncWithArgsAsync<int8_t, int, int>(WINDOW_DLL, AppendPlatform("SetWindowPosition"), MAIN_PROCESS, position.x, position.y);
    Data.Position = position;
}
void Window::SetSize(Vector2D<int> size) {
    int8_t result = CallModuleFuncWithArgsAsync<int8_t, int, int>(WINDOW_DLL, AppendPlatform("SetWindowSize"), MAIN_PROCESS, size.x, size.y);
    Data.Size = size;
}
void Window::SetData(SWindowData data) {
    SetBackgroundColor(data.BackgroundColor);
    SetTitle(data.Title.c_str());
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