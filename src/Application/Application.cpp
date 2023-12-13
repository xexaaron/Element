#include "../../include/Application.h"

Application::Application() : IsRunning(true) {
    CreateDefaultWindow();

}

Application::~Application() {

}

Window* Application::GetWindow() {
    return AppWindow;
}

void Application::ApplicationLoop() {
    auto log = []() {
        
    };
    auto task = [this](){
        int i = 0;
        while (IsRunning) {
                 
        }

    };
    
    ThreadManager::GetInstance().AddTask(task, APP_PROCESS, log);
}

void Application::CreateDefaultWindow() {
   
}