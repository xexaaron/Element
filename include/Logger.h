#pragma once
#include "Enums.h"
#include <cstdio>
#include <cstdarg>
#include "../config.h"
#include "Structs.h"
#include <sstream>
namespace Logger {
    namespace LogStyles {
        static const std::string LOG_STYLE_RESET = "\033[0m";
        namespace LogColors {
            static const std::string LOG_RED = "\033[31m";
            static const std::string LOG_GREEN = "\033[32m";
            static const std::string LOG_YELLOW = "\033[33m";
            static const std::string LOG_BLUE = "\033[34m";
            static const std::string LOG_MAGENTA = "\033[35m";
            static const std::string LOG_CYAN = "\033[36m";
            static const std::string LOG_WHITE = "\033[37m";
        }
        namespace LogAttributes {
            static const std::string LOG_UNDERLINE = "\033[4m";
            static const std::string LOG_BOLD = "\033[1m";
            static const std::string LOG_ITALIC = "\033[3m";
            static const std::string LOG_INVERSE = "\033[7m";
            static const std::string LOG_STRIKETHROUGH = "\033[9m";
            static const std::string LOG_HIDDEN = "\033[8m";
            static const std::string LOG_BLINK_SLOW = "\033[5m";
            static const std::string LOG_BLINK_FAST = "\033[6m";

            static const std::string LOG_RESET_UNDERLINE = "\033[24m"; 
            static const std::string LOG_RESET_BOLD = "\033[22m"; 
            static const std::string LOG_RESET_ITALIC = "\033[23m"; 
            static const std::string LOG_RESET_INVERSE = "\033[27m";
            static const std::string LOG_RESET_STRIKETHROUGH = "\033[29m"; 
            static const std::string LOG_RESET_HIDDEN = "\033[28m"; 
            static const std::string LOG_RESET_BLINK = "\033[25m";
        }
        namespace LogColorAttributes {
            /** BOLD */
            static const std::string LOG_RED_BOLD = LogColors::LOG_RED + LogAttributes::LOG_BOLD;
            static const std::string LOG_GREEN_BOLD = LogColors::LOG_GREEN + LogAttributes::LOG_BOLD;
            static const std::string LOG_YELLOW_BOLD = LogColors::LOG_YELLOW + LogAttributes::LOG_BOLD;
            static const std::string LOG_BLUE_BOLD = LogColors::LOG_BLUE + LogAttributes::LOG_BOLD;
            static const std::string LOG_MAGENTA_BOLD = LogColors::LOG_MAGENTA + LogAttributes::LOG_BOLD;
            static const std::string LOG_CYAN_BOLD = LogColors::LOG_CYAN + LogAttributes::LOG_BOLD;
            static const std::string LOG_WHITE_BOLD = LogColors::LOG_WHITE + LogAttributes::LOG_BOLD;
            /** UNDERLINE **/
            static const std::string LOG_RED_UNDERLINE = LogColors::LOG_RED + LogAttributes::LOG_UNDERLINE;
            static const std::string LOG_GREEN_UNDERLINE = LogColors::LOG_GREEN + LogAttributes::LOG_UNDERLINE;
            static const std::string LOG_YELLOW_UNDERLINE = LogColors::LOG_YELLOW + LogAttributes::LOG_UNDERLINE;
            static const std::string LOG_BLUE_UNDERLINE = LogColors::LOG_BLUE + LogAttributes::LOG_UNDERLINE;
            static const std::string LOG_MAGENTA_UNDERLINE = LogColors::LOG_MAGENTA + LogAttributes::LOG_UNDERLINE;
            static const std::string LOG_CYAN_UNDERLINE = LogColors::LOG_CYAN + LogAttributes::LOG_UNDERLINE;
            static const std::string LOG_WHITE_UNDERLINE = LogColors::LOG_WHITE + LogAttributes::LOG_UNDERLINE;
            /** ITALIC **/
            static const std::string LOG_RED_ITALIC = LogColors::LOG_RED + LogAttributes::LOG_ITALIC;
            static const std::string LOG_GREEN_ITALIC = LogColors::LOG_GREEN + LogAttributes::LOG_ITALIC;
            static const std::string LOG_YELLOW_ITALIC = LogColors::LOG_YELLOW + LogAttributes::LOG_ITALIC;
            static const std::string LOG_BLUE_ITALIC = LogColors::LOG_BLUE + LogAttributes::LOG_ITALIC;
            static const std::string LOG_MAGENTA_ITALIC = LogColors::LOG_MAGENTA + LogAttributes::LOG_ITALIC;
            static const std::string LOG_CYAN_ITALIC = LogColors::LOG_CYAN + LogAttributes::LOG_ITALIC;
            static const std::string LOG_WHITE_ITALIC = LogColors::LOG_WHITE + LogAttributes::LOG_ITALIC;
            /** INVERSE **/
            static const std::string LOG_RED_INVERSE = LogColors::LOG_RED + LogAttributes::LOG_INVERSE;
            static const std::string LOG_GREEN_INVERSE = LogColors::LOG_GREEN + LogAttributes::LOG_INVERSE;
            static const std::string LOG_YELLOW_INVERSE = LogColors::LOG_YELLOW + LogAttributes::LOG_INVERSE;
            static const std::string LOG_BLUE_INVERSE = LogColors::LOG_BLUE + LogAttributes::LOG_INVERSE;
            static const std::string LOG_MAGENTA_INVERSE = LogColors::LOG_MAGENTA + LogAttributes::LOG_INVERSE;
            static const std::string LOG_CYAN_INVERSE = LogColors::LOG_CYAN + LogAttributes::LOG_INVERSE;
            static const std::string LOG_WHITE_INVERSE = LogColors::LOG_WHITE + LogAttributes::LOG_INVERSE;
            /** STRIKETROUGH **/
            static const std::string LOG_RED_STRIKETHROUGH = LogColors::LOG_RED + LogAttributes::LOG_STRIKETHROUGH;
            static const std::string LOG_GREEN_STRIKETHROUGH = LogColors::LOG_GREEN + LogAttributes::LOG_STRIKETHROUGH;
            static const std::string LOG_YELLOW_STRIKETHROUGH = LogColors::LOG_YELLOW + LogAttributes::LOG_STRIKETHROUGH;
            static const std::string LOG_BLUE_STRIKETHROUGH = LogColors::LOG_BLUE + LogAttributes::LOG_STRIKETHROUGH;
            static const std::string LOG_MAGENTA_STRIKETHROUGH = LogColors::LOG_MAGENTA + LogAttributes::LOG_STRIKETHROUGH;
            static const std::string LOG_CYAN_STRIKETHROUGH = LogColors::LOG_CYAN + LogAttributes::LOG_STRIKETHROUGH;
            static const std::string LOG_WHITE_STRIKETHROUGH = LogColors::LOG_WHITE + LogAttributes::LOG_STRIKETHROUGH;
            /** BLINK SLOW **/
            static const std::string LOG_RED_HIDDEN = LogColors::LOG_RED + LogAttributes::LOG_HIDDEN;
            static const std::string LOG_GREEN_HIDDEN = LogColors::LOG_GREEN + LogAttributes::LOG_HIDDEN;
            static const std::string LOG_YELLOW_HIDDEN = LogColors::LOG_YELLOW + LogAttributes::LOG_HIDDEN;
            static const std::string LOG_BLUE_HIDDEN = LogColors::LOG_BLUE + LogAttributes::LOG_HIDDEN;
            static const std::string LOG_MAGENTA_HIDDEN = LogColors::LOG_MAGENTA + LogAttributes::LOG_HIDDEN;
            static const std::string LOG_CYAN_HIDDEN = LogColors::LOG_CYAN + LogAttributes::LOG_HIDDEN;
            static const std::string LOG_WHITE_HIDDEN = LogColors::LOG_WHITE + LogAttributes::LOG_HIDDEN;
            /** BLINK FAST **/
            static const std::string LOG_RED_BLINK_SLOW = LogColors::LOG_RED + LogAttributes::LOG_BLINK_SLOW;
            static const std::string LOG_GREEN_BLINK_SLOW = LogColors::LOG_GREEN + LogAttributes::LOG_BLINK_SLOW;
            static const std::string LOG_YELLOW_BLINK_SLOW = LogColors::LOG_YELLOW + LogAttributes::LOG_BLINK_SLOW;
            static const std::string LOG_BLUE_BLINK_SLOW = LogColors::LOG_BLUE + LogAttributes::LOG_BLINK_SLOW;
            static const std::string LOG_MAGENTA_BLINK_SLOW = LogColors::LOG_MAGENTA + LogAttributes::LOG_BLINK_SLOW;
            static const std::string LOG_CYAN_BLINK_SLOW = LogColors::LOG_CYAN + LogAttributes::LOG_BLINK_SLOW;
            static const std::string LOG_WHITE_BLINK_SLOW = LogColors::LOG_WHITE + LogAttributes::LOG_BLINK_SLOW;
            /** BLINK FAST **/
            static const std::string LOG_RED_BLINK_FAST = LogColors::LOG_RED + LogAttributes::LOG_BLINK_FAST;
            static const std::string LOG_GREEN_BLINK_FAST = LogColors::LOG_GREEN + LogAttributes::LOG_BLINK_FAST;
            static const std::string LOG_YELLOW_BLINK_FAST = LogColors::LOG_YELLOW + LogAttributes::LOG_BLINK_FAST;
            static const std::string LOG_BLUE_BLINK_FAST = LogColors::LOG_BLUE + LogAttributes::LOG_BLINK_FAST;
            static const std::string LOG_MAGENTA_BLINK_FAST = LogColors::LOG_MAGENTA + LogAttributes::LOG_BLINK_FAST;
            static const std::string LOG_CYAN_BLINK_FAST = LogColors::LOG_CYAN + LogAttributes::LOG_BLINK_FAST;
            static const std::string LOG_WHITE_BLINK_FAST = LogColors::LOG_WHITE + LogAttributes::LOG_BLINK_FAST;
            /** UNDERLINE + BOLD */
            static const std::string LOG_RED_UNDERLINE_BOLD = LogColors::LOG_RED + LogAttributes::LOG_UNDERLINE + LogAttributes::LOG_BOLD;
            static const std::string LOG_GREEN_UNDERLINE_BOLD = LogColors::LOG_GREEN + LogAttributes::LOG_UNDERLINE + LogAttributes::LOG_BOLD;
            static const std::string LOG_YELLOW_UNDERLINE_BOLD = LogColors::LOG_YELLOW + LogAttributes::LOG_UNDERLINE + LogAttributes::LOG_BOLD;
            static const std::string LOG_BLUE_UNDERLINE_BOLD = LogColors::LOG_BLUE + LogAttributes::LOG_UNDERLINE + LogAttributes::LOG_BOLD;
            static const std::string LOG_MAGENTA_UNDERLINE_BOLD = LogColors::LOG_MAGENTA + LogAttributes::LOG_UNDERLINE + LogAttributes::LOG_BOLD;
            static const std::string LOG_CYAN_UNDERLINE_BOLD = LogColors::LOG_CYAN + LogAttributes::LOG_UNDERLINE + LogAttributes::LOG_BOLD;
            static const std::string LOG_WHITE_UNDERLINE_BOLD = LogColors::LOG_WHITE + LogAttributes::LOG_UNDERLINE + LogAttributes::LOG_BOLD;
        }
   
    }
    
   
    static std::string LOG_COLOR;
    inline std::string ComputeHeader(LogType type, size_t id) {
        std::string Header;
        std::string LOG_COLOR;
        switch (type) {
            case LogType::LOG:
                LOG_COLOR = LogStyles::LogColors::LOG_YELLOW;
                Header = LogStyles::LogColorAttributes::LOG_YELLOW_UNDERLINE_BOLD + "LOG" + LogStyles::LogAttributes::LOG_RESET_UNDERLINE + "                  : ";
                break;
            case LogType::STATUS:
                LOG_COLOR = LogStyles::LogColors::LOG_CYAN;
                Header = LogStyles::LogColorAttributes::LOG_CYAN_UNDERLINE_BOLD + "STATUS" + LogStyles::LogAttributes::LOG_RESET_UNDERLINE + "               : ";
                break;
            case LogType::LOG_WARNING:
                LOG_COLOR = LogStyles::LogColors::LOG_YELLOW;
                Header = LogStyles::LogColorAttributes::LOG_YELLOW_UNDERLINE_BOLD + "WARNING" + LogStyles::LogAttributes::LOG_RESET_UNDERLINE + "              : ";
                break;
            case LogType::LOG_ERROR:
                LOG_COLOR = LogStyles::LogColors::LOG_RED;
                Header = LogStyles::LogColorAttributes::LOG_RED_UNDERLINE_BOLD + "ERROR" + LogStyles::LogAttributes::LOG_RESET_UNDERLINE + "                : ";
                break;
            case LogType::SUBSTATUS:
                LOG_COLOR = LogStyles::LogColorAttributes::LOG_BLUE_BOLD;
                Header = "-- SUBSTATUS         : ";
                break;
            case LogType::ASYNC_TASK:
                LOG_COLOR = LogStyles::LogColors::LOG_MAGENTA;
                Header = "----- ASYNC TASK " + LogStyles::LogColorAttributes::LOG_MAGENTA_BOLD + "[" + LogStyles::LogAttributes::LOG_RESET_BOLD + std::to_string(id) + 
                LogStyles::LogColorAttributes::LOG_MAGENTA_BOLD + "]" + LogStyles::LogAttributes::LOG_RESET_BOLD + " : ";
                //Header = "----- ASYNC TASK [" + std::to_string(id) + "] : ";
                break;
            case LogType::NON_ASYNC_TASK:
                LOG_COLOR = LogStyles::LogColors::LOG_MAGENTA;
                Header = "----- NON_ASYNC_TASK " + LogStyles::LogColorAttributes::LOG_MAGENTA_BOLD + "[" + LogStyles::LogAttributes::LOG_RESET_BOLD + std::to_string(id) + 
                LogStyles::LogColorAttributes::LOG_MAGENTA_BOLD + "]" + LogStyles::LogAttributes::LOG_RESET_BOLD + " : ";
                break;
            case LogType::RESULT_VALID:
                LOG_COLOR = LogStyles::LogColors::LOG_GREEN;
                Header = "----- RESULT " + LogStyles::LogColorAttributes::LOG_GREEN_BOLD + "[" + LogStyles::LogAttributes::LOG_RESET_BOLD + "VALID" + 
                LogStyles::LogColorAttributes::LOG_GREEN_BOLD + "]" + LogStyles::LogAttributes::LOG_RESET_BOLD + " : ";
                break;
            case LogType::RESULT_ERROR:
                Header = "----- RESULT " + LogStyles::LogColorAttributes::LOG_RED_BOLD + "[" + LogStyles::LogAttributes::LOG_RESET_BOLD + "ERROR" + 
                LogStyles::LogColorAttributes::LOG_RED_BOLD + "]" + LogStyles::LogAttributes::LOG_RESET_BOLD + " : ";
                break;
            default:
                LOG_COLOR = LogStyles::LogColors::LOG_RED;
                Header = "UNKNOWN              : ";
                break;
        }
        return LOG_COLOR + Header + LogStyles::LOG_STYLE_RESET;
    }
    inline void Log(FILE* stream, LogType type, size_t id, const char* format, ...) {
        

        std::string Header = ComputeHeader(type, id);
        va_list args;
        va_start(args, format);

        fprintf(stream, "%s", Header.c_str());
        vfprintf(stream, format, args);
        fprintf(stream, "\n");

        va_end(args);
    }
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
                    << moduleNameSubstring << ", " << functionName << ", " << Logger::LogArguments(args...) << ")" << std::endl;
        } else {
            std::cerr << "---- NON ASYNC TASK : WIN32_CALL_MODULE_FUNCTION_ARGS("
                    << moduleName << ", " << functionName << ", " << Logger::LogArguments(args...) << ")" << std::endl;
        }

        // Log Argument Types
        std::cerr << "Argument Types  : ";
        int dummy2[] = {0, ((void)(std::cerr << Logger::LogArgumentType(args) << " "), 0)...};
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
        ((logStream << "(" << Logger::LogArgumentType(args) << ")" << args << (i != argCount - 1 ? ", " : ""), ++i), ...);
        logStream << ")";
        Logger::Log(stdout, LogType::ASYNC_TASK, TaskID, logStream.str().c_str());
    }

}

