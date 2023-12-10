#ifndef DLL_H
#define DLL_H
    #ifdef _WIN32
        #include <iostream>
        #include <map>
        #include <vector>
        #include <thread>
        #include <Windows.h>
        static std::map<const char*, HINSTANCE> LoadedModules;
        void WINDOWS_LOAD_MODULE(const char* libPath) {
            HINSTANCE handle = LoadLibraryA(libPath);
            if (!handle) {
                std::cerr << "Failed to load the DLL: " << GetLastError() << std::endl;
                // Handle error condition
            } else {
                LoadedModules[libPath] = handle;
            }
        }
        void WINDOWS_LOAD_MODULES(const char* modulePaths[], int numModules) {
            std::vector<std::thread> Threads;
            for (int i = 0; i < numModules; ++i) {
                Threads.emplace_back(WINDOWS_LOAD_MODULE, modulePaths[i]);
            }
            for (auto& thread : Threads) {
                thread.join();
            }
        }
        HINSTANCE WINDOWS_FIND_MODULE(const char* MODULE) {
            auto it = LoadedModules.find(MODULE);
            if (it != LoadedModules.end()) {
                return it->second;
            }
            return nullptr;
        }
        void WINDOWS_UNLOAD_MODULE(const char* MODULE) {
            HINSTANCE moduleHandle = WINDOWS_FIND_MODULE(MODULE);
            if (moduleHandle) {
                FreeLibrary(moduleHandle);
                LoadedModules.erase(MODULE);
            } else {
                std::cerr << "Error: Trouble unloading module " << MODULE << std::endl;
            }
        }
        void WINDOWS_CALL_MODULE_FUNCTION(const char* MODULE, const char* FUNCTION_NAME) {
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
    #else // Unix
        #include <iostream>
        #include <map>
        #include <vector>
        #include <thread>
        #include <dlfcn.h>
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
    #endif // _WIN32
#endif // DLL_H

