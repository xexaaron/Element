#pragma once
#include "Window.h"
#include "../config.h"
#include <cstdlib>
class Application final {
public:
    Application();
    ~Application();
    void CreateDefaultWindow();
    Window* GetWindow();
    void ApplicationLoop();
    bool IsRunning;
private:
    
    Window* AppWindow;
};

