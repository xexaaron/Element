// WindowDLL.h
#pragma once
#include "windows.h"
#include "Enums.h"
#include "Logger.h"
#include <iostream>
#include <tuple>
#include <iostream>
#include <stdint.h>
#ifdef WINDOWDLL_EXPORTS
#define WINDOWDLL_API __declspec(dllexport)
#else
#define WINDOWDLL_API __declspec(dllimport)
#endif

extern "C" WINDOWDLL_API int WIN32_CreateAndRunWindow();
extern "C" WINDOWDLL_API int8_t WIN32_SetWindowTitle(const char* title);
extern "C" WINDOWDLL_API int8_t WIN32_TestMessage(std::string msg);
extern "C" WINDOWDLL_API int8_t WIN32_SetWindowState(EWindowState state);
extern "C" WINDOWDLL_API int8_t WIN32_SetWindowColor(uint32_t Red, uint32_t Green, uint32_t Blue);
extern "C" WINDOWDLL_API int8_t WIN32_SetWindowSize(int x, int y);
extern "C" WINDOWDLL_API int8_t WIN32_SetWindowPosition(int x, int y);
