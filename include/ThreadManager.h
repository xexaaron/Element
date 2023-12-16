#pragma once
#include <thread>
#include <functional>
#include <vector>
#include <mutex>
#include <map>
#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include "Logger.h"



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
    inline void ExecuteTasks(size_t Process) {
        int i = 0;
    #ifdef LOGGING
        std::string processIDName;
        processIDName = Logger::ProcessToName(Process);
        std::string processLogMessage = Logger::LogStyles::LogColorAttributes::LOG_WHITE_BOLD + 
        "Executing Process " + Logger::LogStyles::LOG_STYLE_RESET + Logger::LogStyles::LogColorAttributes::LOG_CYAN_BOLD + "[" + Logger::LogStyles::LOG_STYLE_RESET + 
        processIDName + Logger::LogStyles::LogColorAttributes::LOG_CYAN_BOLD + "]" + 
        Logger::LogStyles::LOG_STYLE_RESET;
        Logger::Log(stdout, LogType::STATUS, 0, "%s", processLogMessage.c_str());
    #endif // LOGGING
        auto& taskVec = taskInfos[Process];
        for (auto& taskInfo : taskVec) {
            auto& taskFunc = taskInfo.first;
            auto& lambda = taskInfo.second;
    #ifdef LOGGING
            std::string TaskLogMessage = Logger::LogStyles::LogColorAttributes::LOG_WHITE_BOLD + 
            "Executing Task    " + Logger::LogStyles::LOG_STYLE_RESET + Logger::LogStyles::LogColorAttributes::LOG_BLUE_BOLD + "[" + Logger::LogStyles::LOG_STYLE_RESET +
            Logger::LogStyles::LogColors::LOG_BLUE + std::to_string(i) + Logger::LogStyles::LogColorAttributes::LOG_BLUE_BOLD + "]" + 
            Logger::LogStyles::LOG_STYLE_RESET;
            Logger::Log(stdout, LogType::SUBSTATUS, 0, "%s", TaskLogMessage.c_str());
    #endif // LOGGING
            lambda(); // CALL LAMBDA
            processThreads[Process].emplace_back(taskFunc);
            i++;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Add Delay for Process variables to become initialized.
    }

    inline void WaitProcess(size_t Process) {
        std::vector<std::future<void>> asyncTasks;

        // Launch other processes asynchronously
        for (const auto& [processId, tasks] : this->tasks) {
            if (processId != Process) {
                asyncTasks.emplace_back(std::async(std::launch::async, [this, processId] {
                    ExecuteTasks(processId);
                }));
            }
        }

        // Wait for the specified Process to complete
        for (auto& thread : processThreads[Process]) {
            if (thread.joinable()) {
                thread.join();
            }
        }
        processThreads[Process].clear();

        // Wait for the other processes to complete asynchronously
        for (auto& task : asyncTasks) {
            task.get();
        }
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
    }

    inline void AddProcessNoLog(size_t Process, std::function<void()>&& func) {
        std::lock_guard<std::mutex> lock(mutex);
        auto& taskVec = taskInfos[Process];
        taskVec.emplace_back(std::move(func), [](){}); // An empty lambda as placeholder for no logging
        tasks[Process] = { taskVec.back().first };
    }

    void IncrementTaskCount(size_t Process) {
        std::lock_guard<std::mutex> lock(mutex);
        taskProcessMap[Process]++;
    }

//  size_t = Process , vector of lambda logging task info to log pre execution.
    std::map<size_t, std::vector<std::pair<std::function<void()>, std::function<void()>>>> taskInfos;
//  size_t = Process , vector of lambda tasks associated with process.
    std::map<size_t, std::vector<std::function<void()>>> tasks;
//  size_t = Process , vector of processes.
    std::map<size_t, std::vector<std::thread>> processThreads;
//  szie_t = Process, size_t TaskID = order added;
    std::map<size_t, size_t> taskProcessMap;
    std::mutex mutex;
    std::mutex logMutex;
};


