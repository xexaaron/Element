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
    ((result += LogArgument(args) + " "), ...); // Concatenate arguments with spaces
    return result;
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
template<typename... Args>
inline std::string LogArgumentTypes(const Args&... args) {
    std::string result;
    ((result += LogArgumentType(args) + " "), ...); 
    return result;
}
template<typename... Args>
inline void MassLogArguments(const char* moduleName, const char* functionName, Args... args) {
    // Log the function call
    size_t lastSlashPos = std::string(moduleName).find_last_of('/');
    if (lastSlashPos != std::string::npos) {
        std::string moduleNameSubstring = std::string(moduleName).substr(lastSlashPos + 1);
        std::cerr << "Function Call   : WIN32_CALL_MODULE_FUNCTION_ARGS("
                << moduleNameSubstring << ", " << functionName << ", " << LogArguments(args...) << ")" << std::endl;
    } else {
        std::cerr << "Function Call   : WIN32_CALL_MODULE_FUNCTION_ARGS("
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
#ifdef _WIN32
#include <windows.h>
inline static std::map<const char*, HINSTANCE> LoadedModules;
inline void WIN32_LOAD_MODULE(const char* libPath) {
    HINSTANCE handle = LoadLibraryA(libPath);
    if (!handle) {
        std::cerr << "Failed to load the DLL: " << GetLastError() << std::endl;
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
[[nodiscard]] inline HINSTANCE WIN32_FIND_MODULE(const char* MODULE) {
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
        std::cerr << "Error: Trouble unloading module " << MODULE << std::endl;
    }
}

template<typename RetType>
inline RetType WIN32_CALL_MODULE_FUNCTION(const char* MODULE, const char* FUNCTION_NAME) {
    HMODULE moduleHandle = LoadedModules[MODULE];
    using FunctionType = RetType(*)();
    FunctionType function = reinterpret_cast<FunctionType>(GetProcAddress(moduleHandle, FUNCTION_NAME));
    if (function != nullptr) {
        return function();
    } else {
        std::cerr << "Failed to find the function '" << FUNCTION_NAME << "' in the module '" << MODULE << "'." << std::endl;
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
        
        ThreadManager::GetInstance().AddTask(function, Process);
        return RetType(0);
    } else {
        std::cerr << "Failed to find the function '" << FUNCTION_NAME << "' in the module '" << MODULE << "'." << std::endl;
        // Return a default value for RetType in case of failure
        return RetType(0);
    }
}
template<typename RetType, typename... Args>
inline RetType WIN32_CALL_MODULE_FUNCTION_ARGS(const char* MODULE, const char* FUNCTION_NAME, Args... args) {
    HMODULE moduleHandle = LoadedModules[MODULE];
    using FunctionType = RetType(*)(Args...);
    FunctionType function = reinterpret_cast<FunctionType>(GetProcAddress(moduleHandle, FUNCTION_NAME));
#ifdef LOGGING // Use #define VERBOSE to log verbose types
    MassLogArguments(MODULE, FUNCTION_NAME, args...);
#endif // LOG_ARGS
    if (function != nullptr) {
        return function(args...);
    } else {
        std::cerr << "Failed to find the function '" << FUNCTION_NAME << "' in the module '" << MODULE << "'." << std::endl;
        // Return a default value for RetType in case of failure
        return RetType(0);
    }
}
template<typename RetType, typename... Args>
inline RetType WIN32_CALL_MODULE_FUNCTION_ARGS_ASYNC(const char* MODULE, const char* FUNCTION_NAME, size_t Process, Args... args) {
    HMODULE moduleHandle = LoadedModules[MODULE];
    using FunctionType = RetType(*)(Args...);
    FunctionType function = reinterpret_cast<FunctionType>(GetProcAddress(moduleHandle, FUNCTION_NAME));
#ifdef LOGGING // Use #define VERBOSE to log verbose types
    MassLogArguments(MODULE, FUNCTION_NAME, args...);
#endif // LOG_ARGS
    if (function != nullptr) {
        ThreadManager::GetInstance().AddTask(function, Process, args...);
        return RetType(0);
    } else {
        std::cerr << "Failed to find the function '" << FUNCTION_NAME << "' in the module '" << MODULE << "'." << std::endl;
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
            std::cerr << "Failed to load the shared library: " << dlerror() << std::endl;
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
            std::cerr << "Error: Trouble unloading module " << MODULE << std::endl;
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
                std::cerr << "Failed to find the function '" << FUNCTION_NAME << "' in the module '" << MODULE << "'." << std::endl;
            }
        } else {
            std::cerr << "Module '" << MODULE << "' not found." << std::endl;
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
                std::cerr << "Failed to find the function '" << FUNCTION_NAME << "' in the module '" << MODULE << "'." << std::endl;
            }
        } else {
            std::cerr << "Module '" << MODULE << "' not found." << std::endl;
        }
        return RetType{};
    }
#endif // _WIN32


