#include "../../include/Window.h"

const char* Window::AppendPlatform(std::string stringToAppend) {
    std::string temp = TargetPlatform + stringToAppend; 
    char* value = new char[temp.length() + 1]; 
    std::strcpy(value, temp.c_str()); 
    return value;
}

bool Window::SetState(EWindowState state) {
    Data.State = state;
    return true;
} 
bool Window::SetPosition(Vector2D<int> position) {
    uint8_t result = CallModuleFuncWithArgs<uint8_t, int, int>(WINDOW_DLL, AppendPlatform("SetWindowPosition"), position.x, position.y);
    if (result = 0) {
        Data.Position = position;
        return true;
    } else if (result = -1) {
        return false;
    }
}
bool Window::SetSize(Vector2D<int> size) {
    uint8_t result = CallModuleFuncWithArgs<uint8_t, int, int>(WINDOW_DLL, AppendPlatform("SetWindowSize"), size.x, size.y);
    if (result = 0) {
        Data.Size = size;
        return true;
    } else if (result = -1) {
        return false;
    }
}
bool Window::SetData(SWindowData data) {
    if (this->SetPosition(data.Position) && this->SetSize(data.Size) && this->SetState(data.State)) {
        return true;
    } else {
        return false;
    }
}

Vector2D<int> Window::GetPosition() {
    return Data.Position;
}
Vector2D<int> Window::GetSize() {
    return Data.Size;
}
EWindowState Window::GetWindowState() {
    return Data.State;
}
SWindowData Window::GetData() {
    return Data;
}