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
    Logger::Log(stdout, LogType::LOG, 0, "Flushed Console");
    Logger::Log(stdout, LogType::LOG, 0, "Program Execute");
}


<<<<<<< HEAD
=======
void SetWindowDefaults(Window* window) {
    window->SetBackgroundColor(Vector3D<uint32_t>(250, 0, 0));
    
}
>>>>>>> 20e9b908268a7eefc57571943b7e9584651f2f86

int main() {
#ifdef LOGGING // Clear Console
    LogProgramBegin();
#endif // LOGGING
   
    SWindowData Data;
    Data.Size = Vector2D<int>{800, 600};
    Data.Position = Vector2D<int>{0, 0};
    Data.State = EWindowState::FULLSCREEN;
    Window* AppWindow = new Window(Data);
   
    ThreadManager::GetInstance().ExecuteTasks(WINDOW_PROCESS);
<<<<<<< HEAD
    
    if (AppWindow) {
        AppWindow->SetSize(Vector2D<int>(500, 500));
        AppWindow->SetBackgroundColor(Vector3D<uint32_t>(255, 0, 0));
        AppWindow->SetPosition(Vector2D<int>(950, 500));
        AppWindow->SetTitle("Testing Testing");
    }
=======
    SetWindowDefaults(ProgramWindow);
>>>>>>> 20e9b908268a7eefc57571943b7e9584651f2f86
    
    ThreadManager::GetInstance().ExecuteTasks(MAIN_PROCESS);
    printf("test"); 
    return 0;
}

