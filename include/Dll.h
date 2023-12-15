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
#include "Structs.h"

// Just wanted to try out concepts



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
            Logger::MassLogAsync(MODULE, TaskID, Process, FUNCTION_NAME);
        };
    #else
        auto lambda = [](){};
    #endif // LOGGING
        ThreadManager::GetInstance().AddTask(function, Process, lambda);
        return RetType{};
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
    Logger::MassLogArguments(MODULE, FUNCTION_NAME, args...);
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
            Logger::MassLogArgumentsAsync(MODULE, TaskID, Process, FUNCTION_NAME, args...);
        };
    #else
        auto lambda = [](){};
    #endif // LOGGING
        ThreadManager::GetInstance().AddTask(function, Process, lambda,  args...);
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
                    Logger::MassLogArguments(MODULE, FUNCTION_NAME, args...);
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


