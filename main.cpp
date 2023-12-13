#include "include/Window.h"

int main() {
    SWindowData Data;
    Data.Size = Vector2D<int>{800, 600};
    Data.Position = Vector2D<int>{0, 0};
    Data.State = EWindowState::FULLSCREEN;
    Window* m_Window = new Window(Data);
    ThreadManager::GetInstance().ExecuteProcesses();
    m_Window->SetBackgroundColor(Vector3D<uint32_t>(255, 0, 0));
    return 0;
}
