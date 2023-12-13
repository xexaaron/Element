#include "include/Window.h"

#include <iostream>
#include <string>




int main() {
#ifdef LOGGING // Clear Console
    for (int i = 0; i < 20; ++i) {
        std::cout << std::endl;
    }
    std::cout << "LOG                  : Console Flushed" << std::endl;
    std::cout << "LOG                  : Program Start" << std::endl;
    std::cout << std::endl;
#endif // LOGGING
    SWindowData Data;
    Data.Size = Vector2D<int>{800, 600};
    Data.Position = Vector2D<int>{0, 0};
    Data.State = EWindowState::FULLSCREEN;
    Window* m_Window = new Window(Data);
    ThreadManager::GetInstance().ExecuteTasks(WINDOW_PROCESS);
    auto TestTask = [](){
       std::cout << "---- ASYNC TASK [3]  : Task Begin" << std::endl; 
    };

    auto TestLogLambda = [](){
        using L_TYPE = int;           /**  Use L_TYPE  modify the function */
        constexpr char L_SIGN = '-';  /**  Use L_SIGN modify the function */
        const L_TYPE a = 100;
        const L_TYPE b = 50;
        L_TYPE c = 50;
        std::string mode;
        size_t taskID = ThreadManager::GetInstance().GetTaskCount(MAIN_PROCESS);
        printf("---- ASYNC TASK [%zu]  : Pre Task Log\n", taskID);
        printf("---- ASYNC TASK [%zu]  : Name              [Int {%d %c %d} Test]\n", taskID, a, L_SIGN, b);
        printf("---- ASYNC TASK [%zu]  : Expected Result   [%d]\n", taskID, c);
        printf("---- ASYNC TASK [%zu]  : Result            [%d]\n", taskID, (L_SIGN == '+') ? (a + b) : (L_SIGN == '-') ? (a - b) : (L_SIGN == '*') ? (a * b) : (a / b));
    };
    
    m_Window->SetBackgroundColor(Vector3D<uint32_t>(250, 0, 0));
    m_Window->SetPosition(Vector2D<int>(50, 50));
    m_Window->SendTestMessageToWindow("Testing Message");

    ThreadManager::GetInstance().AddTask(TestTask, MAIN_PROCESS, TestLogLambda);
    ThreadManager::GetInstance().ExecuteTasks(MAIN_PROCESS);
    
    return 0;
}
