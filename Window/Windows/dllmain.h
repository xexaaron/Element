// WindowDLL.h
#pragma once
#include "windows.h"
#include <iostream>
#include <stdint.h>
#ifdef WINDOWDLL_EXPORTS
#define WINDOWDLL_API __declspec(dllexport)
#else
#define WINDOWDLL_API __declspec(dllimport)
#endif

enum EWindowState {
    FULLSCREEN = 0,
    MAXIMIZED = 1,
    MINIMIZED = 2,
};

extern "C" {
    WINDOWDLL_API int CreateAndRunWindow();

    WINDOWDLL_API int8_t WIN32_SetWindowTitle(const char* title);
    WINDOWDLL_API int8_t WIN32_SetWindowPosition(int x, int y);
    WINDOWDLL_API int8_t WIN32_SetWindowSize(int x, int y);
    WINDOWDLL_API int8_t WIN32_SetWindowColor(uint32_t Red, uint32_t Green, uint32_t Blue);
    WINDOWDLL_API int8_t WIN32_SetWindowState(EWindowState state);
    WINDOWDLL_API int8_t WIN32_TestMessage(std::string msg);
}
