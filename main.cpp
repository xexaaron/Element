#include "include/Window.h"
#include "include/Logger.h"
#include <iostream>
#include <string>
#include <cmath> 
#include <chrono> 


void LogProgramBegin() {
    for (int i = 0; i < 100; ++i) {
        std::cout << std::endl;
    }
    Logger::Log(stdout, LogType::LOG, 0, "Console Flushed");
    Logger::Log(stdout, LogType::LOG, 0, "Program Start");
    std::cout << std::endl;
}

Window* CreateBasicWindow() {
    SWindowData Data;
    Data.Size = Vector2D<int>{800, 600};
    Data.Position = Vector2D<int>{0, 0};
    Data.State = EWindowState::FULLSCREEN;
    return new Window(Data); 
}

void SetWindowDefaults(Window* window) {
    window->SetBackgroundColor(Vector3D<uint32_t>(250, 0, 0));
    
}

int main() {
#ifdef LOGGING // Clear Console
    LogProgramBegin();
#endif // LOGGING
    Window* ProgramWindow = CreateBasicWindow();
    ThreadManager::GetInstance().ExecuteTasks(WINDOW_PROCESS);
    SetWindowDefaults(ProgramWindow);
    
    ThreadManager::GetInstance().ExecuteTasks(MAIN_PROCESS);
    printf("test"); 
    return 0;
}

