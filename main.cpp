#include "include/Window.h"
#include "include/Logger.h"
#include "include/Structs.h"
#include <iostream>
#include <string>
#include <cmath> 
#include <chrono> 


void LogProgramBegin() {
    for (int i = 0; i < 100; ++i) {
        std::cout << std::endl;
    }
    std::string flush = Logger::LogStyles::LogColorAttributes::LOG_WHITE_BOLD + "Flushed Console" + Logger::LogStyles::LOG_STYLE_RESET;
    std::string exec = Logger::LogStyles::LogColorAttributes::LOG_WHITE_BOLD + "Program Execute" + Logger::LogStyles::LOG_STYLE_RESET;
    Logger::Log(stdout, LogType::LOG, 0, "%s", flush.c_str());
    Logger::Log(stdout, LogType::LOG, 0, exec.c_str());
}

void TestAsyncTasks() {
    auto TestTask = [](){
        Logger::Log(stdout, LogType::ASYNC_TASK, ThreadManager::GetInstance().GetTaskCount(MAIN_PROCESS), "I am test task 1");
    };
    auto TestTaskLog = []() {
         Logger::Log(stdout, LogType::ASYNC_TASK, ThreadManager::GetInstance().GetTaskCount(MAIN_PROCESS), "I am test task log 1");
    };
    ThreadManager::GetInstance().AddTask(TestTask, MAIN_PROCESS, TestTaskLog);
    auto TestTask2 = [](){
        Logger::Log(stdout, LogType::ASYNC_TASK, ThreadManager::GetInstance().GetTaskCount(MAIN_PROCESS), "I am test task 2");
    };
    auto TestTaskLog2 = [](){
        Logger::Log(stdout, LogType::ASYNC_TASK, ThreadManager::GetInstance().GetTaskCount(MAIN_PROCESS), "I am test task log 2");
    };
    ThreadManager::GetInstance().AddTask(TestTask2, MAIN_PROCESS, TestTaskLog2);
    auto TestTask3 = [](){
        Logger::Log(stdout, LogType::ASYNC_TASK, ThreadManager::GetInstance().GetTaskCount(MAIN_PROCESS), "I am test task 3");
    };
    auto TestTaskLog3 = [](){
        Logger::Log(stdout, LogType::ASYNC_TASK, ThreadManager::GetInstance().GetTaskCount(MAIN_PROCESS), "I am test task log 3");
    };
    ThreadManager::GetInstance().AddTask(TestTask3, MAIN_PROCESS, TestTaskLog3);
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
        AppWindow->SetSize(Vector2D<int>(500, 500));
        AppWindow->SetBackgroundColor(Vector3D<uint32_t>());
        AppWindow->SetPosition(Vector2D<int>(950, 500));
        AppWindow->SetTitle("Window");
    }
    TestAsyncTasks();
    ThreadManager::GetInstance().ExecuteTasks(WINDOW_PROCESS);
    ThreadManager::GetInstance().ExecuteTasks(RENDER_PROCESS);
    ThreadManager::GetInstance().ExecuteTasks(MAIN_PROCESS);
    ThreadManager::GetInstance().WaitProcess(WINDOW_PROCESS);
    return 0;
}

