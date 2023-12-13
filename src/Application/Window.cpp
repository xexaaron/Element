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

bool Window::SendTestMessageToWindow(std::string Message) {
    int8_t result = CallModuleFuncWithArgsAsync<int8_t, std::string>(WINDOW_DLL, AppendPlatform("TestMessage"), MAIN_PROCESS, Message);
    if (result != 0) {
        std::cerr << "ERROR          : " << "Message [`" << Message << "`]" << " was not sent" << std::endl; 
        return false;
    } else {
        return true;
    }
    return true;
}

bool Window::SetBackgroundColor(Vector3D<uint32_t> color) {
    int8_t result = CallModuleFuncWithArgsAsync<int8_t, uint32_t, uint32_t, uint32_t>(
    WINDOW_DLL, AppendPlatform("SetWindowColor"), MAIN_PROCESS, color.x, color.y, color.z);
    if (result == FUNCTION_SUCCESS) {
        Data.BackgroundColor = color;
    
        return true;
    } else if (result == FUNCTION_FAILURE) {
    #ifdef LOGGING
        printf("ERROR :    Function : Window::SetBackgroundColor(%u,%u,%u)\n                  %s\n                 Window Manager is NULL\n",
               color.x, color.y, color.z, WINDOW_DLL);
    #endif // LOGGING
        return false;
    }
   
    return true; 
}
bool Window::SetTitle(const char* title) {
    int8_t result = CallModuleFuncWithArgsAsync<int8_t, const char*>(WINDOW_DLL, AppendPlatform("SetWindowTitle"), MAIN_PROCESS, title);
    if (result == FUNCTION_SUCCESS) {
        Data.Title = title;
        return true;
    } else if (result == FUNCTION_FAILURE) {
    #ifdef LOGGING
        printf("ERROR :\n    Function : Window::SetTitle(%s)\n    %s\n    Window Manager is NULL\n", title, WINDOW_DLL);
    #endif // LOGGING
        return false;
    }
    return true;
}
bool Window::SetState(EWindowState state) {
    int8_t result = 0;
    result = CallModuleFuncWithArgsAsync<int8_t, EWindowState>(WINDOW_DLL, AppendPlatform("SetWindowState"), MAIN_PROCESS, state);
    if (result == FUNCTION_SUCCESS) {
        Data.State = state;
        return true;
    } else if (result == FUNCTION_FAILURE) {
    #ifdef LOGGING
        printf("ERROR :\n    Function : Window::SetState(%i)\n    %s\n    Window Manager is NULL\n", state, WINDOW_DLL);
    #endif // LOGGING
        return false;
    }
    return true;
} 

bool Window::SetPosition(Vector2D<int> position) {
    int8_t result = CallModuleFuncWithArgsAsync<int8_t, int, int>(WINDOW_DLL, AppendPlatform("SetWindowPosition"), MAIN_PROCESS, position.x, position.y);
    if (result == FUNCTION_SUCCESS) {
        Data.Position == position;
        return true;
    } else if (result = FUNCTION_FAILURE) {
    #ifdef LOGGING
        printf("ERROR :\n    Function : Window::SetPosition(%i,%i)\n    %s\n    Window Manager is NULL\n", position.x, position.y, WINDOW_DLL);
    #endif // LOGGING
        return false;
    }
    return true;
}
bool Window::SetSize(Vector2D<int> size) {
    int8_t result = CallModuleFuncWithArgsAsync<int8_t, int, int>(WINDOW_DLL, AppendPlatform("SetWindowSize"), MAIN_PROCESS, size.x, size.y);
    if (result == FUNCTION_SUCCESS) {
        Data.Size = size;
        return true;
    } else if (result == FUNCTION_FAILURE) {
    #ifdef LOGGING
        printf("ERROR :\n    Function : Window::SetSize(%d,%d)\n    %s\n    Window Manager is NULL\n", size.x, size.y, WINDOW_DLL);
    #endif // LOGGING
        return false;
    }
    return true;
}
bool Window::SetData(SWindowData data) {
    if (!(this->SetPosition(data.Position) && this->SetSize(data.Size) && this->SetState(data.State))) {
    #ifdef LOGGING
        printf("ERROR :\n    Function : Window::SetData(%s,%i,{%u,%u,%u},{%i,%i},{%i,%i})\n    %s\n    Window Manager is NULL\n",
        data.Title.c_str(), Data.State, Data.BackgroundColor.x, Data.BackgroundColor.y, Data.BackgroundColor.z,
        Data.Position.x, Data.Position.y, Data.Size.x, Data.Size.y, WINDOW_DLL);
    #endif // LOGGING
        return false;
    }
    return true;
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