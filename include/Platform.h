#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "../config.h"
#include "Dll.h"

#ifdef _WIN32  
#include <windows.h>
#define Super __super
#define LoadModule(module) WIN32_LOAD_MODULE(module)
#define LoadModules(modules, quantity) WIN32_LOAD_MODULES(modules, quantity)
#define UnloadModule(module) WIN32_UNLOAD_MODULE(module)
#define FindModule(module) WIN32_FIND_MODULE(module)
#define CallModuleFunc(module, function) WIN32_CALL_MODULE_FUNCTION(module, function)
template<typename... Args>
void CallModuleFuncWithArgs(const char* MODULE, const char* FUNCTION_NAME, Args... ARGS) {
    WIN32_CALL_MODULE_FUNCTION_ARGS<Args...>(MODULE, FUNCTION_NAME, ARGS...);
}

#else // UNIX
#define Super Class
#define LoadModule(module) UNIX_LOAD_MODULE(module)
#define LoadModules(modules, quantity) UNIX_LOAD_MODULES(modules, quantity)
#define UnloadModule(module) UNIX_UNLOAD_MODULE(module)
#define FindModule(module) UNIX_FIND_MODULE(module)
#define CallModuleFunc(module, function) UNIX_CALL_MODULE_FUNCTION(module, function)
template<typename... Args>
void CallModuleFuncWithArgs(const char* MODULE, const char* FUNCTION_NAME, Args... ARGS) {
    UNIX_CALL_MODULE_FUNCTION_ARGS<Args...>(MODULE, FUNCTION_NAME, ARGS...);
}
#endif // _WIN32 

#endif // PLATFORM_HPP


