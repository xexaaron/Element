#ifndef PLATFORM_H
#define PLATFORM_H

#include "../config.h"
#include "DLL.h"


inline const char* AppendPlatform(std::string stringToAppend) {
    std::string temp;
    if (std::string(TARGET_PLATFORM) == "Windows") {
        temp = "WIN32_";
    } else if (std::string(TARGET_PLATFORM) == "Linux") {
        temp = "UNIX_";
    }
    temp += stringToAppend; 
    char* value = new char[temp.length() + 1]; 
    std::strcpy(value, temp.c_str()); 
    return value;
}

typedef uint32_t SYSAGN_WORD;
inline Vector2D<uint16_t> UnpackSystemAgnosticNumericWord(SYSAGN_WORD word) {
    Vector2D<uint16_t> result;
    result.x = static_cast<uint16_t>((word >> 16) & 0xFFFF); // Extract param x from the high 16 bits
    result.y = static_cast<uint16_t>(word & 0xFFFF);        // Extract param y from the low 16 bits
    return result;
}


#ifdef _WIN32  
#include <windows.h>
#define Super __super
#define LoadModule(module) WIN32_LOAD_MODULE(module)
#define LoadModules(modules, quantity) WIN32_LOAD_MODULES(modules, quantity)
#define UnloadModule(module) WIN32_UNLOAD_MODULE(module)
#define FindModule(module) WIN32_FIND_MODULE(module)
template<typename RetType>
inline RetType CallModuleFunc(const char* MODULE, const char* FUNCTION_NAME) {
   return WIN32_CALL_MODULE_FUNCTION<RetType>(MODULE, FUNCTION_NAME);
}
template<typename RetType>
inline void CallModuleFuncAsync(const char* MODULE, const char* FUNCTION_NAME, size_t PROCESS) {
    WIN32_CALL_MODULE_FUNCTION_ASYNC<RetType>(MODULE, FUNCTION_NAME, PROCESS);
}
template<typename RetType, typename... Args>
inline RetType CallModuleFuncWithArgs(const char* MODULE, const char* FUNCTION_NAME, Args... ARGS) {
   return WIN32_CALL_MODULE_FUNCTION_ARGS<RetType, Args...>(MODULE, FUNCTION_NAME, ARGS...);
}
template<typename RetType, typename... Args>
inline void CallModuleFuncWithArgsAsync(const char* MODULE, const char* FUNCTION_NAME,  size_t PROCESS, Args... ARGS) {
    WIN32_CALL_MODULE_FUNCTION_ARGS_ASYNC<RetType, Args...>(MODULE, FUNCTION_NAME, PROCESS, ARGS...);
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
template<typename RetType>
inline RetType CallModuleFunc(const char* MODULE, const char* FUNCTION_NAME) {
    return UNIX_CALL_MODULE_FUNCTION<RetType>(MODULE, FUNCTION_NAME);
}
template<typename RetType>
inline RetType CallModuleFuncAsync(const char* MODULE, const char* FUNCTION_NAME) {
    UNIX_CALL_MODULE_FUNCTION_ASYNC<RetType>(MODULE, FUNCTION_NAME);
}
template<typename RetType, typename... Args>
inline RetType CallModuleFuncWithArgs(const char* MODULE, const char* FUNCTION_NAME, Args... ARGS) {
    return UNIX_CALL_MODULE_FUNCTION_ARGS<RetType, Args...>(MODULE, FUNCTION_NAME, ARGS...);
}
template<typename RetType, typename... Args>
inline RetType CallModuleFuncWithArgsAsync(const char* MODULE, const char* FUNCTION_NAME, Args... ARGS) {
    UNIX_CALL_MODULE_FUNCTION_ARGS_ASYNC<RetType, Args...>(MODULE, FUNCTION_NAME, ARGS...);
}

#endif // _WIN32 

#endif // PLATFORM_H


