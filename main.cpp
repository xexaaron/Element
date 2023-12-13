#include "include/Window.h"

int main() {
    for (int i = 0; i < 20; ++i) {
        std::cout << std::endl; // Clear console
    }
    SWindowData Data;
    Data.Size = Vector2D<int>{800, 600};
    Data.Position = Vector2D<int>{0, 0};
    Data.State = EWindowState::FULLSCREEN;
    Window* m_Window = new Window(Data);
    auto TestTask = [](){
        using L_TYPE = int;
        constexpr char L_SIGN = '-'; // Assuming L_SIGN represents an arithmetic operation
        L_TYPE a = 100;
        L_TYPE b = 50;
        L_TYPE c;
        std::string mode;
        if (L_SIGN == '+') {
            c = a + b;
            mode = "Addition";
        } else if (L_SIGN == '-') {
            c = a - b;
            mode = "Subtraction";
        } else if (L_SIGN == '*') {
            c = a * b;
            mode = "Multiplication";
        } else if (L_SIGN == '/') {
            c = a / b;
            mode = "Division";
        }
        printf("\nTASK   : [Type : %s %s] [a = %i] %c [b = %i] = [c = %i]\n", typeid(c).name(), mode.c_str(), a, L_SIGN,  b, c);
    };
    ThreadManager::GetInstance().AddTask(TestTask, MAIN_PROCESS);
    ThreadManager::GetInstance().ExecuteProcesses();
    m_Window->SetPosition(Vector2D<int>(500, 500));
    return 0;
}
