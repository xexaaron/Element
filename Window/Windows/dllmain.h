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

extern "C" WINDOWDLL_API int CreateAndRunWindow();
extern "C" WINDOWDLL_API int8_t WINSetWindowTitle(const char* title);
extern "C" WINDOWDLL_API int8_t WINTestMessage(std::string msg);
extern "C" WINDOWDLL_API int8_t WINSetWindowState(EWindowState state);
extern "C" WINDOWDLL_API int8_t WINSetWindowColor(uint32_t Red, uint32_t Green, uint32_t Blue);
extern "C" WINDOWDLL_API int8_t WINSetWindowSize(int x, int y);
extern "C" WINDOWDLL_API int8_t WINSetWindowPosition(int x, int y);