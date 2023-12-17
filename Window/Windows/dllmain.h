#pragma once
#include "windows.h"
#include "Enums.h"
#include <iostream>
#include <tuple>
#include <vector>
#include <iostream>
#include <stdint.h>
#ifdef WINDOWDLL_EXPORTS
#define WINDOWDLL_API __declspec(dllexport)
#else
#define WINDOWDLL_API __declspec(dllimport)
#endif

typedef uint32_t SYSAGN_WORD; // Platform agnostic Word 

extern "C" WINDOWDLL_API int WIN32_CreateAndRunWindow();
extern "C" WINDOWDLL_API int8_t WIN32_SetWindowTitle(const char* title);
extern "C" WINDOWDLL_API int8_t WIN32_TestMessage(std::string msg);
extern "C" WINDOWDLL_API int8_t WIN32_SetWindowState(EWindowState state);
extern "C" WINDOWDLL_API int8_t WIN32_SetWindowColor(uint32_t Red, uint32_t Green, uint32_t Blue);
extern "C" WINDOWDLL_API int8_t WIN32_SetWindowSize(int x, int y);
extern "C" WINDOWDLL_API SYSAGN_WORD WIN32_GetDeviceDimensions();
extern "C" WINDOWDLL_API int8_t WIN32_SetWindowPixel(int x, int y, uint32_t Red, uint32_t Green, uint32_t Blue);
extern "C" WINDOWDLL_API int8_t WIN32_SetWindowPosition(int x, int y);
