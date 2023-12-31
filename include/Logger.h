#pragma once
#include "Enums.h"
#include <cstdio>
#include <cstdarg>
#include "../config.h"
#include "Structs.h"
#include <sstream>
#include <fstream>
#include <regex>

#ifdef FILE_LOGGING
#include <ctime>
    static std::ofstream fileStream;
    constexpr char DATE[80] = "-%Y-%m-%d";
#endif // FILE_LOGGING



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
            static const std::string LOG_GRAY = "\033[90m";
            static const std::string LOG_GREY = "\033[90m";
            static const std::string LOG_COLOR_STRING = "\033[31m";
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
    
    static constexpr int ASYC_RESULT_BUFFER_SIZE = 6;
    static std::string AsyncResultBuffer[ASYC_RESULT_BUFFER_SIZE];
    static int bufferIndex = 0;

   
    
    inline std::string ColorText(const char* Text, const std::string Color) {
        return Color + std::string(Text) + Logger::LogStyles::LOG_STYLE_RESET;
    }
    inline std::string BoldText(const char* Text, const std::string Color) {
        return Color + LogStyles::LogAttributes::LOG_BOLD + std::string(Text) + Logger::LogStyles::LOG_STYLE_RESET;
    }
    inline std::string ULBoldColorText(const char* Text, const std::string Color, const std::string ResetType) {
        return Color + LogStyles::LogAttributes::LOG_UNDERLINE + LogStyles::LogAttributes::LOG_BOLD + std::string(Text) + ResetType;
        
    }
    inline std::string ColonPrependWhitespace(int spaces, bool Semi) {
        std::string temp;
        for (int i = 0; i < spaces; i++) {
            temp += " ";
        }
        return temp + (Semi ? "; " : ": ");
    }
    inline std::string ColorAndBracketText(const char* Text, const std::string Color) {
        const std::string Bold = LogStyles::LogAttributes::LOG_BOLD;
        return Color + Bold + "[" + Logger::LogStyles::LOG_STYLE_RESET + 
        Color + std::string(Text) +
        Logger::LogStyles::LOG_STYLE_RESET + Color + Bold + "]" + Logger::LogStyles::LOG_STYLE_RESET;
    }
    inline std::string ProcessToName(size_t process) {
        const std::string Color = Logger::LogStyles::LogColors::LOG_CYAN;
        std::string processIDName;
        switch(process) {
            case 0:
                processIDName = ColorAndBracketText("WINDOW_PROCESS", Color);
                break;
            case 1:
                processIDName = ColorAndBracketText("APP_PROCESS", Color);
                break;
            case 2:
                processIDName = ColorAndBracketText("RENDER_PROCESS", Color);
                break;
            case 3:
                processIDName = ColorAndBracketText("EVENT_PROCESS", Color);
                break;
            case 65534:
                processIDName = ColorAndBracketText("LOG_PROCESS", Color);
                break;
            case 65535:
                processIDName = ColorAndBracketText("MAIN_PROCESS", Color);
                break;
            default:
                processIDName = ColorAndBracketText("UNKOWN_PROCESS", Color);
                break;
        }
        return processIDName;
    }
    inline std::string int8_tToResultType(int8_t result) {
        const std::string Color = Logger::LogStyles::LogColors::LOG_BLUE;
        switch (result) {
            case -1:
                return ColorAndBracketText("FUNCTION_FAILURE", Color);      
                break;
            case 0:
                return ColorAndBracketText("FUNCTION_RESULT_UNDEFINED", Color);
                break;
            case 1: 
                return ColorAndBracketText("FUNCTION_SUCCESS", Color);
                break;
            default:
                return ColorAndBracketText("FUNCTION_RESULT_UNDEFINED", Color);
                break;
        }
    }
    inline ELogType int8_tToELogType(int8_t result) {
        switch (result) {
            case -1:
                return ELogType::RESULT_ERROR;
                break;
            case 0:
                return ELogType::RESULT_ERROR;
                break;
            case 1:
                return ELogType::RESULT_VALID;
                break;
            default:
                return ELogType::RESULT_ERROR;
                break;
        }
    }
    inline FILE* int8_tToStream(int8_t result) {
        switch (result) {
            case -1:
                return stderr;
                break;
            case 0:
                return stderr;
                break;
            case 1:
                return stdout;
                break;
            default:
                return nullptr;
                break;
        }
    }
    inline std::string ComputeHeader(ELogType type, size_t id) {
        std::string Header;
        std::string LOG_COLOR;
        const std::string LOG_RESET = LogStyles::LogAttributes::LOG_RESET_UNDERLINE;
        switch (type) {
            case ELogType::LOG:
                LOG_COLOR = LogStyles::LogColors::LOG_YELLOW;
                Header = ULBoldColorText("LOG" ,LOG_COLOR, LOG_RESET) + ColonPrependWhitespace(18, false);
                break;
            case ELogType::STATUS:
                LOG_COLOR = LogStyles::LogColors::LOG_CYAN;
                Header = ULBoldColorText("STATUS" ,LOG_COLOR, LOG_RESET) + ColonPrependWhitespace(15, false);
                break;
            case ELogType::LOG_WARNING:
                LOG_COLOR = LogStyles::LogColors::LOG_YELLOW;
                Header = ULBoldColorText("LOG_WARNING" ,LOG_COLOR, LOG_RESET) + ColonPrependWhitespace(14, false);
                break;
            case ELogType::LOG_ERROR:
                LOG_COLOR = LogStyles::LogColors::LOG_RED;
                Header = ULBoldColorText("LOG_WARNING" ,LOG_COLOR, LOG_RESET) + ColonPrependWhitespace(16, false);
                break;
            case ELogType::SUBSTATUS:
                LOG_COLOR = LogStyles::LogColorAttributes::LOG_BLUE_BOLD;
                Header = "-- SUBSTATUS         : ";
                break;
            case ELogType::ASYNC_TASK:
                LOG_COLOR = LogStyles::LogColors::LOG_MAGENTA;
                Header = "----- ASYNC TASK " + ColorAndBracketText(std::to_string(id).c_str(), LOG_COLOR) + " : ";
                //Header = "----- ASYNC TASK [" + std::to_string(id) + "] : ";
                break;
            case ELogType::NON_ASYNC_TASK:
                LOG_COLOR = LogStyles::LogColors::LOG_MAGENTA;
                Header = "----- NON_ASYNC_TASK " + ColorAndBracketText(std::to_string(id).c_str(), LOG_COLOR) + " : ";
                break;
            case ELogType::RESULT_VALID:
                LOG_COLOR = LogStyles::LogColors::LOG_GREEN;
                Header = "----- RESULT     " + ColorAndBracketText(std::to_string(id).c_str(), LOG_COLOR) + " : ";
                break;
            case ELogType::RESULT_ERROR:
                Header = "----- RESULT     " + ColorAndBracketText(std::to_string(id).c_str(), LOG_COLOR) + " : ";
                break;
            default:
                LOG_COLOR = LogStyles::LogColors::LOG_RED;
                Header = "UNKNOWN              : ";
                break;
        }
        return LOG_COLOR + Header + LogStyles::LOG_STYLE_RESET;
    }
    inline std::string LogTask(size_t taskID) {
        const std::string BracketsColor = Logger::LogStyles::LogColors::LOG_BLUE;
        const std::string TextColor = Logger::LogStyles::LogColorAttributes::LOG_WHITE_BOLD;
        const std::string Reset = Logger::LogStyles::LOG_STYLE_RESET; 
        return TextColor + "Task " + Reset + ColorAndBracketText(std::to_string(taskID).c_str(), BracketsColor);
        
    }
    inline void Log(FILE* stream, ELogType type, size_t id, const char* format, ...) {
        std::string Header = ComputeHeader(type, id);
        va_list args;
        va_start(args, format);
    #ifdef CONSOLE_LOGGING
        if (type == ELogType::RESULT_VALID) {
            char logMessage[256];
            vsnprintf(logMessage, sizeof(logMessage), format, args);
            AsyncResultBuffer[bufferIndex++] = Header + logMessage;
        } else {
            fprintf(stream, "%s", Header.c_str());
            vfprintf(stream, format, args);
            fprintf(stream, "\n");
        }
    #endif // CONSOLE_LOGGING
    #ifdef FILE_LOGGING
        if (!fileStream.is_open()) {
            char dateBuffer[80];
            std::time_t currentTime = std::time(nullptr);
            std::tm* localTime = std::localtime(&currentTime);
            std::strftime(dateBuffer, sizeof(dateBuffer), DATE, localTime);
            std::string filepath = std::string(LOG_DIRECTORY) + std::string(PROJECT_NAME) + "-" + std::string(TARGET_PLATFORM) + "-log.txt" + (dateBuffer);     
            fileStream.open(filepath, std::ios::out | std::ios::trunc); 
            if (!fileStream.is_open()) {
                #undef FILE_LOGGING
                Logger::Log(stderr, ELogType::LOG_ERROR, LOG_PROCESS, "Could not perform write operation on %s", filepath);
                return;
            }
        }
        fileStream << "\n" << Header;
        fileStream << format; // Write the log message
        fileStream << "\n";
        #endif // FILE_LOGGING
        va_end(args);
    }
    template<typename T>
    inline std::string LogArgument(const T& arg) {
        if constexpr (Concepts::StringType<T>) {
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
            return Logger::LogStyles::LogColors::LOG_BLUE + std::string(typeid(T).name()) + Logger::LogStyles::LOG_STYLE_RESET;
        #else // BASIC
            if constexpr (std::is_same_v<T, std::string>) {
                return Logger::LogStyles::LogColors::LOG_GREEN + "std::string" + Logger::LogStyles::LOG_STYLE_RESET;
            } else if constexpr (std::is_same_v<T, int>) {
                return Logger::LogStyles::LogColors::LOG_BLUE + "int" + Logger::LogStyles::LOG_STYLE_RESET;
            } else if constexpr (std::is_same_v<T, float>) {
                return Logger::LogStyles::LogColors::LOG_BLUE + "float" + Logger::LogStyles::LOG_STYLE_RESET;
            } else if constexpr (std::is_same_v<T, double>) {
                return Logger::LogStyles::LogColors::LOG_BLUE + "double" + Logger::LogStyles::LOG_STYLE_RESET;
            } else if constexpr (std::is_same_v<T, char>) {
                return Logger::LogStyles::LogColors::LOG_BLUE + "char" + Logger::LogStyles::LOG_STYLE_RESET;
            } else if constexpr (std::is_same_v<T, bool>) {
                return Logger::LogStyles::LogColors::LOG_BLUE + "bool" + Logger::LogStyles::LOG_STYLE_RESET;
            } else if constexpr (std::is_same_v<T, const char*>) {
                return Logger::LogStyles::LogColors::LOG_BLUE + "const char*" + Logger::LogStyles::LOG_STYLE_RESET;
            } else if constexpr (std::is_same_v<T, size_t>){
                return Logger::LogStyles::LogColors::LOG_GREEN + "size_t" + Logger::LogStyles::LOG_STYLE_RESET;
            } else {
                return Logger::LogStyles::LogColors::LOG_BLUE + std::string(typeid(T).name()) + Logger::LogStyles::LOG_STYLE_RESET;
            }
        #endif // VERBOSE
    }
    template<>
    inline std::string LogArgumentType<EWindowState>(const EWindowState&) {
       const std::string Color = Logger::LogStyles::LogColors::LOG_GREEN;
        return ColorText("enum ", Logger::LogStyles::LogColors::LOG_BLUE) + ColorText("EWindowState", Color);
    }
    template<>
    inline std::string LogArgumentType<ELogType>(const ELogType&) {
       const std::string Color = Logger::LogStyles::LogColors::LOG_GREEN;
        return ColorText("enum ", Logger::LogStyles::LogColors::LOG_BLUE) + ColorText("EWindowState", Color);
    }
    template<>
    inline std::string LogArgumentType<uint8_t>(const uint8_t&) {
       const std::string Color = Logger::LogStyles::LogColors::LOG_GREEN;
        return ColorText("uint8_t", Color);
    }
    template<>
    inline std::string LogArgumentType<uint16_t>(const uint16_t&) {
        const std::string Color = Logger::LogStyles::LogColors::LOG_GREEN;
        return ColorText("unit16_t", Color);
    }
    template<>
    inline std::string LogArgumentType<uint32_t>(const uint32_t&) {
        const std::string Color = Logger::LogStyles::LogColors::LOG_GREEN;
        return ColorText("uint32_t", Color);
    }
    template<>
    inline std::string LogArgumentType<int8_t>(const int8_t&) {
        const std::string Color = Logger::LogStyles::LogColors::LOG_GREEN;
        return ColorText("int8_t", Color);
    }
    template<>
    inline std::string LogArgumentType<int16_t>(const int16_t&) {
        const std::string Color = Logger::LogStyles::LogColors::LOG_GREEN;
        return ColorText("int16_t", Color);
    }
    template<>
    inline std::string LogArgumentType<int32_t>(const int32_t&) {
        const std::string Color = Logger::LogStyles::LogColors::LOG_GREEN;
        return ColorText("int32_t", Color);
    }
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
    inline std::string CMakeTargetPlatformToSystemPlatform(const char* platform) {
        if (platform == "Windows") {
            return std::string("WIN32_");
        } else if(platform == "Linux") {
            return std::string("UNIX_");
        } else if(platform == "Darwin") {
            return std::string("DARWIN_");
        } else {
            Logger::Log(stderr, ELogType::LOG_ERROR, LOG_PROCESS, "We do not support your platform. How you made it this far im not sure.");
            std::exit(-1);
        }
    }
    template<typename... Args>
    inline void MassLogArgumentsAsync(const char* moduleName, size_t TaskID, size_t process, const char* functionName, Args... args) {
        std::ostringstream logStream;
    #ifdef VERBOSE 
        logStream << Logger::LogStyles::LogColors::LOG_YELLOW << CMakeTargetPlatformToSystemPlatform(TARGET_PLATFORM) << "CALL_MODULE_FUNCTION_ARGS_ASYNC"
        << Logger::LogStyles::LOG_STYLE_RESET << Logger::LogStyles::LogColors::LOG_MAGENTA << "("
        << Logger::LogStyles::LOG_STYLE_RESET << Logger::LogStyles::LogColors::LOG_COLOR_STRING
        << moduleName << Logger::LogStyles::LOG_STYLE_RESET << ", "
        << Logger::LogStyles::LogColors::LOG_YELLOW << functionName
        << Logger::LogStyles::LOG_STYLE_RESET << ", " << Logger::ProcessToName(process) << ", " ;
    #else 
        size_t lastSlashPos = std::string(moduleName).find_last_of('/');
        if (lastSlashPos != std::string::npos) {
            std::string moduleNameSubstring = std::string(moduleName).substr(lastSlashPos + 1);
            logStream << Logger::LogStyles::LogColors::LOG_YELLOW << CMakeTargetPlatformToSystemPlatform(TARGET_PLATFORM) << "CALL_MODULE_FUNCTION_ARGS_ASYNC" <<
            Logger::LogStyles::LOG_STYLE_RESET << Logger::LogStyles::LogColors::LOG_MAGENTA << "(" <<
            Logger::LogStyles::LOG_STYLE_RESET << Logger::LogStyles::LogColors::LOG_COLOR_STRING << 
            moduleNameSubstring << Logger::LogStyles::LOG_STYLE_RESET << ", " << 
            Logger::LogStyles::LogColors::LOG_YELLOW << functionName << Logger::LogStyles::LOG_STYLE_RESET << 
            ", " << Logger::ProcessToName(process) << ", " ;
        } else {
            logStream << Logger::LogStyles::LogColors::LOG_YELLOW << CMakeTargetPlatformToSystemPlatform(TARGET_PLATFORM)
            << "CALL_MODULE_FUNCTION_ARGS_ASYNC"
            << Logger::LogStyles::LOG_STYLE_RESET << Logger::LogStyles::LogColors::LOG_MAGENTA << "("
            << Logger::LogStyles::LOG_STYLE_RESET << Logger::LogStyles::LogColors::LOG_COLOR_STRING
            << moduleName << Logger::LogStyles::LOG_STYLE_RESET << ", "
            << Logger::LogStyles::LogColors::LOG_YELLOW << functionName
            << Logger::LogStyles::LOG_STYLE_RESET << ", " << Logger::LogStyles::LOG_STYLE_RESET
            << ", " << Logger::ProcessToName(process) << ", " ;
        }
    #endif // VERBOSE
        size_t argCount = sizeof...(Args);
        size_t i = 0;
        ((logStream << Logger::LogStyles::LogColorAttributes::LOG_BLUE_BOLD << 
        "(" << Logger::LogStyles::LOG_STYLE_RESET <<  Logger::LogArgumentType(args) <<
        Logger::LogStyles::LogColorAttributes::LOG_BLUE_BOLD << ")" <<
        Logger::LogStyles::LOG_STYLE_RESET << Logger::LogStyles::LogColors::LOG_GREY << args <<
        Logger::LogStyles::LOG_STYLE_RESET << (i != argCount - 1 ? ", " : ""), ++i), ...);
        logStream << Logger::LogStyles::LogColors::LOG_MAGENTA << ")";
        Logger::Log(stdout, ELogType::ASYNC_TASK, TaskID, logStream.str().c_str());
    }
    inline void MassLogAsync(const char* moduleName, size_t TaskID, size_t process, const char* functionName) {
        std::ostringstream logStream;
    #ifdef VERBOSE 
        logStream << Logger::LogStyles::LogColors::LOG_YELLOW << CMakeTargetPlatformToSystemPlatform(TARGET_PLATFORM) << "CALL_MODULE_FUNCTION_ASYNC"
        << Logger::LogStyles::LOG_STYLE_RESET << Logger::LogStyles::LogColors::LOG_MAGENTA << "("
        << Logger::LogStyles::LOG_STYLE_RESET << Logger::LogStyles::LogColors::LOG_COLOR_STRING
        << moduleName << Logger::LogStyles::LOG_STYLE_RESET << ", "
        << Logger::LogStyles::LogColors::LOG_YELLOW << functionName
        << Logger::LogStyles::LOG_STYLE_RESET << ", " << Logger::ProcessToName(process) ;
    #else 
        size_t lastSlashPos = std::string(moduleName).find_last_of('/');
        if (lastSlashPos != std::string::npos) {
            std::string moduleNameSubstring = std::string(moduleName).substr(lastSlashPos + 1);
            logStream << Logger::LogStyles::LogColors::LOG_YELLOW << CMakeTargetPlatformToSystemPlatform(TARGET_PLATFORM) << "CALL_MODULE_FUNCTION_ASYNC" <<
            Logger::LogStyles::LOG_STYLE_RESET << Logger::LogStyles::LogColors::LOG_MAGENTA << "(" <<
            Logger::LogStyles::LOG_STYLE_RESET << Logger::LogStyles::LogColors::LOG_COLOR_STRING << 
            moduleNameSubstring << Logger::LogStyles::LOG_STYLE_RESET << ", " << 
            Logger::LogStyles::LogColors::LOG_YELLOW << functionName << Logger::LogStyles::LOG_STYLE_RESET << 
            ", " << Logger::ProcessToName(process);
        } else {
            logStream << Logger::LogStyles::LogColors::LOG_YELLOW << CMakeTargetPlatformToSystemPlatform(TARGET_PLATFORM) << "CALL_MODULE_FUNCTION_ASYNC"
            << Logger::LogStyles::LOG_STYLE_RESET << Logger::LogStyles::LogColors::LOG_MAGENTA << "("
            << Logger::LogStyles::LOG_STYLE_RESET << Logger::LogStyles::LogColors::LOG_COLOR_STRING
            << moduleName << Logger::LogStyles::LOG_STYLE_RESET << ", "
            << Logger::LogStyles::LogColors::LOG_YELLOW << functionName
            << Logger::LogStyles::LOG_STYLE_RESET << ", " << Logger::LogStyles::LOG_STYLE_RESET
            << ", " << Logger::ProcessToName(process);
        }
    #endif // VERBOSE
        logStream << Logger::LogStyles::LogColors::LOG_MAGENTA << ")";
        Logger::Log(stdout, ELogType::ASYNC_TASK, TaskID, logStream.str().c_str());
    }
    inline void DumpAsyncBuffer() {
        if (bufferIndex == ASYC_RESULT_BUFFER_SIZE) {
            std::string LogMessage = Logger::BoldText("Dumping Async Buffer ", Logger::LogStyles::LogColors::LOG_WHITE) + 
            Logger::ColorAndBracketText(std::to_string(bufferIndex).c_str(), Logger::LogStyles::LogColors::LOG_GREEN);
            Logger::Log(stdout, ELogType::SUBSTATUS, LOG_PROCESS, "%s", LogMessage.c_str());
            for (int i = 0; i < ASYC_RESULT_BUFFER_SIZE; ++i) {
                if (!(AsyncResultBuffer[i].empty())) {
                    std::cout << AsyncResultBuffer[i] << "\n";
                    AsyncResultBuffer[i].clear();
                }
            }
            bufferIndex = 0; 
        }
    }
    inline void ForceDumpAsyncBuffer() {
        std::string LogMessage = Logger::BoldText("Force Dumping Async Buffer ", Logger::LogStyles::LogColors::LOG_WHITE) + 
        Logger::ColorAndBracketText(std::to_string(bufferIndex).c_str(), Logger::LogStyles::LogColors::LOG_GREEN);
        Logger::Log(stdout, ELogType::SUBSTATUS, LOG_PROCESS, "%s", LogMessage.c_str());
        for (int i = 0; i < ASYC_RESULT_BUFFER_SIZE; ++i) {
            if (!(AsyncResultBuffer[i].empty())) {
                std::cout << AsyncResultBuffer[i] << "\n";
                AsyncResultBuffer[i].clear();
            }
        }
        bufferIndex = 0; 
    }
}

