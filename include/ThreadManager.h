#pragma once
#include <thread>
#include <functional>
#include <vector>
#include <mutex>
#include <map>
#include <iostream>

class ThreadManager {
public:
    inline static ThreadManager& GetInstance() {
        static ThreadManager instance; // Singleton pattern to ensure only one instance
        return instance;
    }

    template<typename Function, typename... Args>
    inline void AddTask(Function&& func, size_t Process, Args&&... args) {
        auto taskFunc = [func, args...]() { func(args...); };
        AddProcess(Process, taskFunc);
    }
    
    
    inline void ExecuteTasks(size_t Process) {
        int i = 0;
    #ifdef LOGGING
        printf("STATUS : Executing Process [%zu]\n", Process);    
    #endif // LOGGING
        for (auto& task : tasks[Process]) {
        #ifdef LOGGING
            printf("STATUS : Executing Task    [%i]\n", i); 
        #endif // LOGGING
            processThreads[Process].emplace_back(task);
            i++;
        }
    }

    inline void ExecuteProcesses() {
        int i = 0;
        for (auto& process : tasks) {
            ExecuteTasks(process.first);
            i++;
        }

        for (auto& process : tasks) {
            WaitProcess(process.first);
        }

        for (auto& process : tasks) {
            process.second.clear();
            processThreads[process.first].clear();
        }
    }

    // Wait for all tasks in a specific process to complete
    inline void WaitProcess(size_t Process) {
        for (auto& thread : processThreads[Process]) {
            if (thread.joinable()) {
                thread.join();
            }
        }
        processThreads[Process].clear();
    }

    // Wait for all tasks in all processes to complete
    inline void WaitAll() {
        for (auto& process : tasks) {
            WaitProcess(process.first);
        }
    }


private:
    ThreadManager() {
        
    }
    ~ThreadManager() {
        WaitAll(); 
    }

    inline void AddProcess(size_t Process, std::function<void()> func) {
        std::lock_guard<std::mutex> lock(mutex);
        auto processIterator = tasks.find(Process);
        if (processIterator != tasks.end()) {
            processIterator->second.emplace_back(func);
        } else {
            // If the process does not exist, create a new process and add the task
            tasks[Process] = { func };
            
        }
    }
    std::map<size_t, std::vector<std::function<void()>>> tasks;
    std::map<size_t, std::vector<std::thread>> processThreads;
    std::mutex mutex;
};


