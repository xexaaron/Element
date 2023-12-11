// WindowDLL.h
#pragma once
#include "windows.h"
#include <iostream>
#ifdef WINDOWDLL_EXPORTS
#define WINDOWDLL_API __declspec(dllexport)
#else
#define WINDOWDLL_API __declspec(dllimport)
#endif

extern "C" {
    WINDOWDLL_API int CreateAndRunWindow();
}
extern "C" {
    WINDOWDLL_API void WIN32_TestMessage(std::string msg);
}
extern "C" {
    WINDOWDLL_API void WIN32_SetWindowTitle(const wchar_t Title[]);

}
extern "C" {
    
    WINDOWDLL_API void WIN32_SetWindowPosition(int x, int y);
  
}
extern "C" {
    WINDOWDLL_API void WIN32_SetWindowSize(int x, int y);

}