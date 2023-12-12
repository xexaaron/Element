#ifndef DLL_H
#define DLL_H
#include <cstdarg>
#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <thread>
#include <type_traits>
#include <string>
template<typename T>
std::string LogArgument(const T& arg) {
    return std::to_string(arg);
}

template<typename T>
std::string LogArgument(const std::basic_string<T>& arg) {
    return std::string("\"") + std::string(arg.begin(), arg.end()) + std::string("\"");
}
template<typename... Args>
std::string LogArguments(const Args&... args) {
    std::string result;
    ((result += LogArgument(args) + " "), ...); // Concatenate arguments with spaces
    return result;
}
template<typename T>
std::string LogArgumentType(const T&) {
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
    std::string LogArgumentTypes(const Args&... args) {
    std::string result;
    ((result += LogArgumentType(args) + " "), ...); 
    return result;
}
template<typename... Args>
void MassLogArguments(const char* moduleName, const char* functionName, Args... args) {
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
        

        static std::map<const char*, HINSTANCE> LoadedModules;
        void WIN32_LOAD_MODULE(const char* libPath) {
            HINSTANCE handle = LoadLibraryA(libPath);
            if (!handle) {
                std::cerr << "Failed to load the DLL: " << GetLastError() << std::endl;
                // Handle error condition
            } else {
                LoadedModules[libPath] = handle;
            }
        }
        void WIN32_LOAD_MODULES(const char* modulePaths[], int numModules) {
            std::vector<std::thread> Threads;
            for (int i = 0; i < numModules; ++i) {
                Threads.emplace_back(WIN32_LOAD_MODULE, modulePaths[i]);
            }
            for (auto& thread : Threads) {
                thread.join();
            }
        }
        HINSTANCE WIN32_FIND_MODULE(const char* MODULE) {
            auto it = LoadedModules.find(MODULE);
            if (it != LoadedModules.end()) {
                return it->second;
            }
            return nullptr;
        }
        void WIN32_UNLOAD_MODULE(const char* MODULE) {
            HINSTANCE moduleHandle = WIN32_FIND_MODULE(MODULE);
            if (moduleHandle) {
                FreeLibrary(moduleHandle);
                LoadedModules.erase(MODULE);
            } else {
                std::cerr << "Error: Trouble unloading module " << MODULE << std::endl;
            }
        }
        void WIN32_CALL_MODULE_FUNCTION(const char* MODULE, const char* FUNCTION_NAME) {
            HMODULE moduleHandle = LoadedModules[MODULE];
            // Define the function pointer type based on the expected function signature
            using FunctionType = void(*)(); 
            // Get the address of the function from the loaded module
            FunctionType function = reinterpret_cast<FunctionType>(GetProcAddress(moduleHandle, FUNCTION_NAME));
            if (function != nullptr) {
                function();
            } else {
                std::cerr << "Failed to find the function '" << FUNCTION_NAME << "' in the module '" << MODULE << "'." << std::endl;
            }
        }
        template<typename RetType, typename... Args>
        RetType WIN32_CALL_MODULE_FUNCTION_ARGS(const char* MODULE, const char* FUNCTION_NAME, Args... args) {
            HMODULE moduleHandle = LoadedModules[MODULE];
            using FunctionType = RetType(*)(Args...);
            FunctionType function = reinterpret_cast<FunctionType>(GetProcAddress(moduleHandle, FUNCTION_NAME));
            MassLogArguments(MODULE, FUNCTION_NAME, args...);
            if (function != nullptr) {
                return function(args...);
            } else {
                std::cerr << "Failed to find the function '" << FUNCTION_NAME << "' in the module '" << MODULE << "'." << std::endl;
            }
        }
        
    #else // Unix
        #include <dlfcn.h>
        template<typename T>
        std::string LogArgument(const T& arg) {
            return std::to_string(arg);
        }

        template<typename T>
        std::string LogArgument(const std::basic_string<T>& arg) {
            return std::string("\"") + std::string(arg.begin(), arg.end()) + std::string("\"");
        }

        template<typename... Args>
        std::string LogArguments(const Args&... args) {
            std::string result;
            ((result += LogArgument(args) + " "), ...); 
            return result;
        }
        

        static std::map<const char*, void*> LoadedModules;
        void UNIX_LOAD_MODULE(const char* libPath) {
            void* handle = dlopen(libPath, RTLD_NOW | RTLD_GLOBAL);
            if (!handle) {
                std::cerr << "Failed to load the shared library: " << dlerror() << std::endl;
                // Handle error condition
            } else {
                LoadedModules[libPath] = handle;
            }
        }
        void UNIX_LOAD_MODULES(const char* modulePaths[], int numModules) {
            std::vector<std::thread> Threads;
            for (int i = 0; i < numModules; ++i) {
                Threads.emplace_back(UNIX_LOAD_MODULE, modulePaths[i]);
            }
            for (auto& thread : Threads) {
                thread.join();
            }
        }
        void* UNIX_FIND_MODULE(const char* MODULE) {
            auto it = LoadedModules.find(MODULE);
            if (it != LoadedModules.end()) {
                return it->second;
            }
            return nullptr;
        }
        void UNIX_UNLOAD_MODULE(const char* MODULE) {
            void* moduleHandle = UNIX_FIND_MODULE(MODULE);
            if (moduleHandle) {
                dlclose(moduleHandle);
                LoadedModules.erase(MODULE);
            } else {
                std::cerr << "Error: Trouble unloading module " << MODULE << std::endl;
            }
        }
        void UNIX_CALL_MODULE_FUNCTION(const char* MODULE, const char* FUNCTION_NAME) {
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
        template<typename... Args>
        void UNIX_CALL_MODULE_FUNCTION_ARGS(const char* MODULE, const char* FUNCTION_NAME, Args... args) {
            void* moduleHandle = LoadedModules[MODULE];
            if (moduleHandle) {
                // Get the function pointer
                void* function = dlsym(moduleHandle, FUNCTION_NAME);
                if (function != nullptr) {
                    using FunctionType = void(*)(Args...);
                    // Cast the function pointer to the appropriate type
                    FunctionType func = reinterpret_cast<FunctionType>(function);
                    // Call the function with the provided arguments
                    func(args...);
                } else {
                    std::cerr << "Failed to find the function '" << FUNCTION_NAME << "' in the module '" << MODULE << "'." << std::endl;
                }
            } else {
                std::cerr << "Module '" << MODULE << "' not found." << std::endl;
            }
        }

    #endif // _WIN32
#endif // DLL_H

