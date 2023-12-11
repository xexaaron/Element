// Window.h
#pragma once 
#ifdef WINDOWDLL_EXPORTS
#define WINDOWDLL_API __attribute__((visibility("default")))
#else
#define WINDOWDLL_API 
#endif

extern "C" {
    WINDOWDLL_API int CreateAndRunWindow();
}