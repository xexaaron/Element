#pragma once
#include <cstdarg>
#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <thread>
#include <type_traits>
#include <string>
#include "ThreadManager.h"
#include <concepts>
#include <sstream>
#include "Logger.h"
#include "Enums.h"
// Just wanted to try out concepts
template<typename T>
concept StringType = std::is_convertible_v<T, std::string>;
template<typename T>
inline std::string LogArgument(const T& arg) {
    if constexpr (StringType<T>) {
        return std::string("\"") + std::string(arg) + std::string("\"");
    } else {
        return std::to_string(arg);
    }
}
template<typename T>
inline std::string LogArgument(const std::basic_string<T>& arg) {
    return std::string("\"") + std::string(arg.begin(), arg.end()) + std::string("\"");
}
template<typename... Args>
inline std::string LogArguments(const Args&... args) {
    std::string result;
    size_t count = 0;
    size_t argumentsCount = sizeof...(Args);
    ((result += LogArgument(args) + (++count != argumentsCount ? ", " : "")), ...);
    return result;
}
template<typename... Args>
void LogArgumentsAndTypes(const Args&... args) {  
    int dummy[] = {0, ((void)(std::cerr << "(" << LogArgumentType(args) << ")" << args << " "), 0)...};
    (void)dummy;
    
}
template<typename T>
inline std::string LogArgumentType(const T&) {
    #ifdef VERBOSE
        return std::string(typeid(T).name());
    #else // BASIC
        if constexpr (std::is_same_v<T, std::string>) {
            return "std::string";
        } else if constexpr (std::is_same_v<T, int>) {
            return "int";
        } else if constexpr (std::is_same_v<T, float>) {
            return "float";
        } else if constexpr (std::is_same_v<T, double>) {
            return "double";
        } else if constexpr (std::is_same_v<T, char>) {
            return "char";
        } else if constexpr (std::is_same_v<T, bool>) {
            return "bool";
        } else {
            return std::string(typeid(T).name()); // Return verbose definiton
        }
    #endif // VERBOSE
}
#ifdef VERBOSE
        template<>
    inline std::string LogArgumentType<uint8_t>(const uint8_t&) {
        return "uint8_t";
    }

    template<>
    inline std::string LogArgumentType<uint16_t>(const uint16_t&) {
        return "uint16_t";
    }

    template<>
    inline std::string LogArgumentType<uint32_t>(const uint32_t&) {
        return "uint32_t";
    }

    // Specializations for signed integers
    template<>
    inline std::string LogArgumentType<int8_t>(const int8_t&) {
        return "int8_t";
    }

    template<>
    inline std::string LogArgumentType<int16_t>(const int16_t&) {
        return "int16_t";
    }

    template<>
    inline std::string LogArgumentType<int32_t>(const int32_t&) {
        return "int32_t";
    }
#endif // VERBOSE
template<typename... Args>
inline std::string LogArgumentTypes(const Args&... args) {
    std::string result;
    ((result += LogArgumentType(args) + ", "), ...); 
    return result;
}
template<typename... Args>
inline void MassLogArguments(const char* moduleName, const char* functionName, Args... args) {
    // Log the function call
    size_t lastSlashPos = std::string(moduleName).find_last_of('/');
    if (lastSlashPos != std::string::npos) {
        std::string moduleNameSubstring = std::string(moduleName).substr(lastSlashPos + 1);



        std::cerr << "---- NON ASYNC TASK : WIN32_CALL_MODULE_FUNCTION_ARGS("
                << moduleNameSubstring << ", " << functionName << ", " << LogArguments(args...) << ")" << std::endl;
    } else {
        std::cerr << "---- NON ASYNC TASK : WIN32_CALL_MODULE_FUNCTION_ARGS("
                << moduleName << ", " << functionName << ", " << LogArguments(args...) << ")" << std::endl;
    }

    // Log Argument Types
    std::cerr << "Argument Types  : ";
    int dummy2[] = {0, ((void)(std::cerr << LogArgumentType(args) << " "), 0)...};
    (void)dummy2;
    std::cerr << std::endl;

    // Log Arguments
    std::cerr << "Arguments       : ";
    int dummy3[] = {0, ((void)(std::cerr << args << " "), 0)...};
    (void)dummy3;
    std::cerr << std::endl;
}
template<typename... Args>
void MassLogArgumentsAsync(const char* moduleName, size_t TaskID, size_t process, const char* functionName, Args... args) {
    std::ostringstream logStream;
#ifdef VERBOSE 
     logStream << "WIN32_CALL_MODULE_FUNCTION_ARGS_ASYNC("
    << moduleName << ", " << functionName << ", ";
#else 
    size_t lastSlashPos = std::string(moduleName).find_last_of('/');
    if (lastSlashPos != std::string::npos) {
        std::string moduleNameSubstring = std::string(moduleName).substr(lastSlashPos + 1);
        logStream << "WIN32_CALL_MODULE_FUNCTION_ARGS_ASYNC("
                  << moduleNameSubstring << ", " << functionName << ", ";
    } else {
        logStream << "WIN32_CALL_MODULE_FUNCTION_ARGS_ASYNC("
                  << moduleName << ", " << functionName << ", ";
    }
#endif // VERBOSE
    size_t argCount = sizeof...(Args);
    size_t i = 0;
    ((logStream << "(" << LogArgumentType(args) << ")" << args << (i != argCount - 1 ? ", " : ""), ++i), ...);
    logStream << ")";
    Logger::Log(stdout, LogType::ASYNC_TASK, TaskID, logStream.str().c_str());
}
#ifdef _WIN32
#include <windows.h>
inline static std::map<const char*, HINSTANCE> LoadedModules;
inline void WIN32_LOAD_MODULE(const char* libPath) {
    HINSTANCE handle = LoadLibraryA(libPath);
    if (!handle) {
        Logger::Log(stderr, LogType::LOG_ERROR, 0, "Failed to load DLL : %s", GetLastError());
        // Handle error condition
    } else {
        LoadedModules[libPath] = handle;
    }
}
inline void WIN32_LOAD_MODULES(const char* modulePaths[], int numModules) {
    std::vector<std::thread> Threads;
    for (int i = 0; i < numModules; ++i) {
        Threads.emplace_back(WIN32_LOAD_MODULE, modulePaths[i]);
    }
    for (auto& thread : Threads) {
        thread.join();
    }
}
inline HINSTANCE WIN32_FIND_MODULE(const char* MODULE) {
    auto it = LoadedModules.find(MODULE);
    if (it != LoadedModules.end()) {
        return it->second;
    }
    return nullptr;
}
 
inline void WIN32_UNLOAD_MODULE(const char* MODULE) {
    HINSTANCE moduleHandle = WIN32_FIND_MODULE(MODULE);
    if (moduleHandle) {
        FreeLibrary(moduleHandle);
        LoadedModules.erase(MODULE);
    } else {
        Logger::Log(stderr, LogType::LOG_ERROR, 0, "Trouble unloading module : %s", MODULE);
        
    }
}
template<typename RetType>
inline RetType WIN32_CALL_MODULE_FUNCTION(const char* MODULE, const char* FUNCTION_NAME) {
    HMODULE moduleHandle = LoadedModules[MODULE];
    using FunctionType = RetType(*)();
    FunctionType function = reinterpret_cast<FunctionType>(GetProcAddress(moduleHandle, FUNCTION_NAME));
#ifdef LOGGING
    
    size_t lastSlashPos = std::string(MODULE).find_last_of('/');
    std::string moduleNameSubstring = std::string(MODULE).substr(lastSlashPos + 1);
    Logger::Log(stdout, LogType::NON_ASYNC_TASK, 0, "WIN32_CALL_MODULE_FUNCTION(%s, %s)", moduleNameSubstring.c_str(), FUNCTION_NAME);
#endif // LOGGING
    if (function != nullptr) {
        return function();
    } else {
        Logger::Log(stderr, LogType::LOG_ERROR, 0, "Failed to find function %s in module %s : %s", MODULE, FUNCTION_NAME, GetLastError());
        // Return a default value for RetType in case of failure
        return RetType(0);
    }
}
template<typename RetType>
inline RetType WIN32_CALL_MODULE_FUNCTION_ASYNC(const char* MODULE, const char* FUNCTION_NAME,  size_t Process) {
    HMODULE moduleHandle = LoadedModules[MODULE];
    using FunctionType = RetType(*)();
    FunctionType function = reinterpret_cast<FunctionType>(GetProcAddress(moduleHandle, FUNCTION_NAME));
    if (function != nullptr) {
    #ifdef LOGGING
        size_t TaskID = ThreadManager::GetInstance().GetTaskCount(Process);
        auto lambda = [MODULE, TaskID, FUNCTION_NAME, Process]() {
            size_t lastSlashPos = std::string(MODULE).find_last_of('/');
            std::string moduleNameSubstring = std::string(MODULE).substr(lastSlashPos + 1);
            Logger::Log(stdout, LogType::ASYNC_TASK, TaskID, "WIN32_CALL_MODULE_FUNCTION_ASYNC(%s, %s, %zu)", moduleNameSubstring.c_str(), FUNCTION_NAME, Process);
        };
        ThreadManager::GetInstance().AddTask(function, Process, lambda);
        return RetType{};
    #else 
        ThreadManager::GetInstance().AddTaskNoLog(function, Process);
        return RetType{};
    #endif // LOGGING
    } else {
        Logger::Log(stderr, LogType::LOG_ERROR, 0, "Failed to find function %s in module %s : %s", MODULE, FUNCTION_NAME, GetLastError());
        // Return a default value for RetType in case of failure
        return RetType();
    }
}
template<typename RetType, typename... Args>
inline RetType WIN32_CALL_MODULE_FUNCTION_ARGS(const char* MODULE, const char* FUNCTION_NAME, Args... args) {
    HMODULE moduleHandle = LoadedModules[MODULE];
    using FunctionType = RetType(*)(Args...);
    FunctionType function = reinterpret_cast<FunctionType>(GetProcAddress(moduleHandle, FUNCTION_NAME));
#ifdef LOGGING
    MassLogArguments(MODULE, FUNCTION_NAME, args...);
#endif // LOGGING
    if (function != nullptr) {
        return function(args...);
    } else {
        Logger::Log(stderr, LogType::LOG_ERROR, 0, "Failed to find function %s in module %s : %s", MODULE, FUNCTION_NAME, GetLastError());
        // Return a default value for RetType in case of failure
        return RetType(0);
    }
}
template<typename RetType, typename... Args>
inline RetType WIN32_CALL_MODULE_FUNCTION_ARGS_ASYNC(const char* MODULE, const char* FUNCTION_NAME, size_t Process, Args... args) {
    HMODULE moduleHandle = LoadedModules[MODULE];
    using FunctionType = RetType(*)(Args...);
    FunctionType function = reinterpret_cast<FunctionType>(GetProcAddress(moduleHandle, FUNCTION_NAME));

    if (function != nullptr) {
    #ifdef LOGGING
        size_t TaskID = ThreadManager::GetInstance().GetTaskCount(Process);
        auto lambda = [MODULE, TaskID, Process, FUNCTION_NAME, args...](){
            MassLogArgumentsAsync(MODULE, TaskID, Process, FUNCTION_NAME, args...);
        };
        ThreadManager::GetInstance().AddTask(function, Process, lambda,  args...);
    #else 
        ThreadManager::GetInstance().AddTaskNoLog(function, Process,  args...);
    #endif // LOGGING
       
        return RetType(0);
    } else {
        Logger::Log(stderr, LogType::LOG_ERROR, 0, "Failed to find function %s in module %s : %s", MODULE, FUNCTION_NAME, GetLastError());
        // Return a default value for RetType in case of failure
        return RetType(0);
    }
}
#else // Unix
    #include <dlfcn.h>
    static std::map<const char*, void*> LoadedModules;
    inline void UNIX_LOAD_MODULE(const char* libPath) {
        void* handle = dlopen(libPath, RTLD_NOW | RTLD_GLOBAL);
        if (!handle) {
            Logger::Log(stderr, LogType::LOG_ERROR, 0, "Failed to load the shared library : %s", dlerror());
            
            // Handle error condition
        } else {
            LoadedModules[libPath] = handle;
        }
    }
    inline void UNIX_LOAD_MODULES(const char* modulePaths[], int numModules) {
        std::vector<std::thread> Threads;
        for (int i = 0; i < numModules; ++i) {
            Threads.emplace_back(UNIX_LOAD_MODULE, modulePaths[i]);
        }
        for (auto& thread : Threads) {
            thread.join();
        }
    }
    [[nodiscard]] inline void* UNIX_FIND_MODULE(const char* MODULE) {
        auto it = LoadedModules.find(MODULE);
        if (it != LoadedModules.end()) {
            return it->second;
        }
        return nullptr;
    }
    inline void UNIX_UNLOAD_MODULE(const char* MODULE) {
        void* moduleHandle = UNIX_FIND_MODULE(MODULE);
        if (moduleHandle) {
            dlclose(moduleHandle);
            LoadedModules.erase(MODULE);
        } else {
            Logger::Log(stderr, LogType::LOG_ERROR, 0, "Trouble unloading module : %s", MODULE);
        }
    }
    inline void UNIX_CALL_MODULE_FUNCTION(const char* MODULE, const char* FUNCTION_NAME) {
        void* moduleHandle = LoadedModules[MODULE];
        if (moduleHandle) {
            // Get the function pointer
            void* function = dlsym(moduleHandle, FUNCTION_NAME);
            if (function != nullptr) {
                // Cast the function pointer to the appropriate type and call it
                using FunctionType = void(*)();
                FunctionType func = reinterpret_cast<FunctionType>(function);
                
                func(); 
            } else {
                Logger::Log(stderr, LogType::LOG_ERROR, 0, "Failed to find function %s in module %s : %s", MODULE, FUNCTION_NAME, GetLastError());
            }
        } else {
            Logger::Log(stderr, LogType::LOG_ERROR, 0, "Module : %s Could not be found", MODULE);
        }
    }
    template<typename RetType, typename... Args>
    inline RetType UNIX_CALL_MODULE_FUNCTION_ARGS(const char* MODULE, const char* FUNCTION_NAME, Args... args) {
        void* moduleHandle = LoadedModules[MODULE];
        if (moduleHandle) {
            // Get the function pointer
            void* function = dlsym(moduleHandle, FUNCTION_NAME);
            if (function != nullptr) {
                using FunctionType = RetType(*)(Args...);
                // Cast the function pointer to the appropriate type
                FunctionType func = reinterpret_cast<FunctionType>(function);
            #ifdef LOGGING // Use #define VERBOSE to log verbose types
                    MassLogArguments(MODULE, FUNCTION_NAME, args...);
            #endif // LOG_ARGS
                return func(args...);
            } else {
                Logger::Log(stderr, LogType::LOG_ERROR, 0, "Failed to find function %s in module %s : %s", MODULE, FUNCTION_NAME, GetLastError());
            }
        } else {
            Logger::Log(stderr, LogType::LOG_ERROR, 0, "Module : %s Could not be found", MODULE);
        }
        return RetType{};
    }
#endif // _WIN32


