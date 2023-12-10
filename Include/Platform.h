#ifndef PLATFORM_HPP
#define PLATFORM_HPP
#include "../config.h"
#include "Dll.h"
    #ifdef _WIN32  
        #include <windows.h>
        #define Super __super
        #define LoadModule(module) WINDOWS_LOAD_MODULE(module)
        #define LoadModules(modules, quantity) WINDOWS_LOAD_MODULES(modules, quantity)
        #define UnloadModule(module) WINDOWS_UNLOAD_MODULE(module)
        #define FindModule(module) WINDOWS_FIND_MODULE(module)
        #define CallModuleFunc(module, function) WINDOWS_CALL_MODULE_FUNCTION(module, function) 
    #else 
        #define Super Class
        #define LoadModule(module) UNIX_LOAD_MODULE(module)
        #define LoadModules(modules, quantity) UNIX_LOAD_MODULES(modules, quantity)
        #define UnloadModule(module) UNIX_UNLOAD_MODULE(module)
        #define FindModule(module) UNIX_FIND_MODULE(module)
        #define CallModuleFunc(module, function) UNIX_CALL_MODULE_FUNCTION(module, function) 
    #endif // _WIN32 
#endif // PLATFORM_HPP


