#ifndef PLATFORM_H
#define PLATFORM_H

#include "../config.h"
#include "Dll.h"

#ifdef _WIN32  
#include <windows.h>
#define Super __super
#define LoadModule(module) WIN32_LOAD_MODULE(module)
#define LoadModules(modules, quantity) WIN32_LOAD_MODULES(modules, quantity)
#define UnloadModule(module) WIN32_UNLOAD_MODULE(module)
#define FindModule(module) WIN32_FIND_MODULE(module)
template<typename RecType>
inline RecType CallModuleFunc(const char* MODULE, const char* FUNCTION_NAME) {
    return RecType(WIN32_CALL_MODULE_FUNCTION<RecType>(MODULE, FUNCTION_NAME));
}
template<typename RecType>
inline RecType CallModuleFuncAsync(const char* MODULE, const char* FUNCTION_NAME, size_t PROCESS) {
    return RecType(WIN32_CALL_MODULE_FUNCTION_ASYNC<RecType>(MODULE, FUNCTION_NAME, PROCESS));
}
template<typename RecType, typename... Args>
inline RecType CallModuleFuncWithArgs(const char* MODULE, const char* FUNCTION_NAME, Args... ARGS) {
    return RecType(WIN32_CALL_MODULE_FUNCTION_ARGS<RecType, Args...>(MODULE, FUNCTION_NAME, ARGS...));
}
template<typename RecType, typename... Args>
inline RecType CallModuleFuncWithArgsAsync(const char* MODULE, const char* FUNCTION_NAME,  size_t PROCESS, Args... ARGS) {
    return RecType(WIN32_CALL_MODULE_FUNCTION_ARGS_ASYNC<RecType, Args...>(MODULE, FUNCTION_NAME, PROCESS, ARGS...));
}
#else // UNIX
/** Keyword Super gets replaced with the correct
    namespace::parentclass pre build. 
    Using the macro definition below we do
    not have to deal with intellisense warnings.
    See Root/Tools/Super/README.md for more info.
*/
#define Super:: this-> 
#define LoadModule(module) UNIX_LOAD_MODULE(module)
#define LoadModules(modules, quantity) UNIX_LOAD_MODULES(modules, quantity)
#define UnloadModule(module) UNIX_UNLOAD_MODULE(module)
#define FindModule(module) UNIX_FIND_MODULE(module)
#define CallModuleFunc(module, function) UNIX_CALL_MODULE_FUNCTION(module, function)
template<typename RecType>
inline RecType CallModuleFunc(const char* MODULE, const char* FUNCTION_NAME) {
    UNIX_CALL_MODULE_FUNCTION<RecType>(MODULE, FUNCTION_NAME);
}
template<typename RecType>
inline RecType CallModuleFuncAsync(const char* MODULE, const char* FUNCTION_NAME) {
    UNIX_CALL_MODULE_FUNCTION_ASYNC<RecType>(MODULE, FUNCTION_NAME);
}
template<typename RecType, typename... Args>
inline RecType CallModuleFuncWithArgs(const char* MODULE, const char* FUNCTION_NAME, Args... ARGS) {
    UNIX_CALL_MODULE_FUNCTION_ARGS<RecType, Args...>(MODULE, FUNCTION_NAME, ARGS...);
}
template<typename RecType, typename... Args>
inline RecType CallModuleFuncWithArgsAsync(const char* MODULE, const char* FUNCTION_NAME, Args... ARGS) {
    UNIX_CALL_MODULE_FUNCTION_ARGS_ASYNC<RecType, Args...>(MODULE, FUNCTION_NAME, ARGS...);
}
#endif // _WIN32 

#endif // PLATFORM_H


