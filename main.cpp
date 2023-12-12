#include "include/Window.h"
#include "include/ThreadManager.h"
#include <iostream>
#include <cstdlib> // Include for rand() function

int main() {
    SWindowData Data;
    Data.Size = Vector2D<int>{800, 600};
    Data.Position = Vector2D<int>{0, 0};
    Data.State = EWindowState::FULLSCREEN;
    Window* m_Window = new Window(Data);
    CallModuleFuncWithArgs<void, std::string>(WINDOW_DLL, "WIN32_TestMessage", "Hi"); 
    ThreadManager::GetInstance().ExecuteProcesses();
    return 0;
}
