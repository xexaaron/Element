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

    
    template<typename Function, typename Lambda, typename... Args>
    inline void AddTask(Function&& func, size_t Process, Lambda&& lambda, Args&&... args) {
        auto taskFunc = [func, lambda, args...]() {
            func(args...);
        };
        AddProcess(Process, taskFunc, lambda);
        IncrementTaskCount(Process);
    }

    template<typename Function, typename Lambda>
    inline void AddTask(Function&& func, size_t Process, Lambda&& lambda) {
        auto taskFunc = [func, lambda]() {
            func();
        };
        AddProcess(Process, taskFunc, lambda);
    }
    template<typename Function>
    inline void AddTaskNoLog(Function&& func, size_t Process) {
        auto taskFunc = [func]() {
            func();
        };
        AddProcessNoLog(Process, taskFunc);
    }

    template<typename Function, typename... Args>
    inline void AddTaskNoLog(Function&& func, size_t Process, Args&&... args) {
        auto taskFunc = [func, args...]() {
            func(args...);
        };
        AddProcessNoLog(Process, taskFunc);
    }

    inline void ExecuteTasks(size_t Process) {
        int i = 0;
    #ifdef LOGGING
        printf("STATUS               : Executing Process [%zu]\n", Process);
    #endif // LOGGING
        for (auto& taskInfo : taskInfos[Process]) {
            auto& taskFunc = taskInfo.first;
            auto& lambda = taskInfo.second;
        #ifdef LOGGING
            printf("-- SUBSTATUS         : Executing Task    [%i]\n", i);
        #endif // LOGGING
            lambda(); // CALL LAMBDA
            processThreads[Process].emplace_back(taskFunc);
            i++;
        }
    }


    inline void ExecuteProcesses() {
        for (auto& process : tasks) {
            ExecuteTasks(process.first);
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
    
    size_t GetTaskCount(size_t Process) const {
        std::lock_guard<std::mutex> lock(const_cast<std::mutex&>(mutex));
        auto it = taskProcessMap.find(Process);
        return (it != taskProcessMap.end()) ? it->second : 0;
    }

private:
    ThreadManager() {
        
    }
    ~ThreadManager() {
        WaitAll(); 
    }

    inline void AddProcess(size_t Process, std::function<void()>&& func, std::function<void()>&& lambda) {
        std::lock_guard<std::mutex> lock(mutex);
        auto& taskVec = taskInfos[Process];
        taskVec.emplace_back(std::move(func), std::move(lambda));

        auto processIterator = tasks.find(Process);
        if (processIterator != tasks.end()) {
            processIterator->second.emplace_back(taskVec.back().first);
        } else {
            tasks[Process] = { taskVec.back().first };
        }
    }
    
    inline void AddProcessNoLog(size_t Process, std::function<void()>&& func) {
    std::lock_guard<std::mutex> lock(mutex);
        auto processIterator = tasks.find(Process);
        if (processIterator != tasks.end()) {
            processIterator->second.emplace_back(func);
        } else {
            tasks[Process] = { func };
        }
    }   

    void IncrementTaskCount(size_t Process) {
        std::lock_guard<std::mutex> lock(mutex);
        taskProcessMap[Process]++;
    }

    std::map<size_t, std::vector<std::pair<std::function<void()>, std::function<void()>>>> taskInfos;
    std::map<size_t, std::vector<std::function<void()>>> tasks;
    std::map<size_t, std::vector<std::thread>> processThreads;
    std::map<size_t, size_t> taskProcessMap;
    std::mutex mutex;
    std::mutex logMutex;
};


