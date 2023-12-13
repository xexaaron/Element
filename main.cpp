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



int main() {
#ifdef LOGGING // Clear Console
    LogProgramBegin();
#endif // LOGGING
   
    SWindowData Data;
    Data.Size = Vector2D<int>{800, 600};
    Data.Position = Vector2D<int>{0, 0};
    Data.State = EWindowState::FULLSCREEN;
    Window* AppWindow = new Window(Data);
   
    if (AppWindow) {
        AppWindow->SetTitle("Title");
        AppWindow->SetPosition(Vector2D<int>(0, 0));
        AppWindow->SetSize(Vector2D<int>(5, 5));
    }
     
    ThreadManager::GetInstance().ExecuteProcesses();
    ThreadManager::GetInstance().WaitAll();
    return 0;
}

