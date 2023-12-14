#pragma once
#include "Enums.h"
#include <cstdio>
#include <cstdarg>
#include "../config.h"
#include <sstream>
/**
// NORMAL COLORS
printf("\x1B[31mTexting\033[0m\t\t");       /// RED 
printf("\x1B[32mTexting\033[0m\t\t");       /// GREEN
printf("\x1B[33mTexting\033[0m\t\t");       /// YELLOW
printf("\x1B[34mTexting\033[0m\t\t");       /// PALE_DARK_BLUE
printf("\x1B[35mTexting\033[0m\n");         /// MAGENTA
// BOLD                                     
printf("\x1B[36mTexting\033[0m\t\t");       /// BOLD CYAN
printf("\x1B[36mTexting\033[0m\t\t");       /// BOLD CYAN
printf("\x1B[36mTexting\033[0m\t\t");       /// BOLD CYAN
printf("\x1B[37mTexting\033[0m\t\t");       /// BOLD WHITE
printf("\x1B[93mTexting\033[0m\n");
// ITALICEZD & HIGHLIGHTED
printf("\033[3;42;30mTexting\033[0m\t\t");  /// BOLD YELLOW ITALICIZE
printf("\033[3;43;30mTexting\033[0m\t\t");  /// GREEN HIGHLIGHT ITALICIZE
printf("\033[3;44;30mTexting\033[0m\t\t");  /// YELLOW HIGHLIGHT ITALICIZE
printf("\033[3;104;30mTexting\033[0m\t\t"); /// PALE_DARK_BLUE HIGHLIGHT ITALICIZE
printf("\033[3;100;30mTexting\033[0m\n");   /// CYAN HIGHLIGHT ITALICIZE
// HIGHLIGHTED                              
printf("\033[3;47;35mTexting\033[0m\t\t");  /// WHITE HIGHLIGHT PURPLE TEXT ITALICIZE
printf("\033[2;47;35mTexting\033[0m\t\t");  /// WHITE HIGLIGHT PINK TEXT 
printf("\033[1;47;35mTexting\033[0m\t\t");  /// WHITE HIGHLIGHT PURPLE TEXT
printf("\t\t");
*/


#define LOG_COLOR_RESET   "\033[0m"
#define LOG_RED           "\033[31m"
#define LOG_GREEN         "\033[32m"
#define LOG_YELLOW        "\033[33m"
#define LOG_BLUE          "\033[34m"
#define LOG_MAGENTA       "\033[35m"
#define LOG_CYAN          "\033[36m"
#define LOG_WHITE         "\033[37m"


namespace Logger {
<<<<<<< HEAD
    static const std::string LOG_COLOR_RESET = "\033[0m";
    static const std::string LOG_RED = "\033[31m";
    static const std::string LOG_GREEN = "\033[32m";
    static const std::string LOG_YELLOW = "\033[33m";
    static const std::string LOG_BLUE = "\033[34m";
    static const std::string LOG_MAGENTA = "\033[35m";
    static const std::string LOG_CYAN = "\033[36m";
    static const std::string LOG_WHITE = "\033[37m";
    static std::string LOG_COLOR;
=======
    inline static size_t HEADER_BUFFER_LENGTH = 20;
    inline static std::string LOG_COLOR = LOG_COLOR_RESET;
>>>>>>> 20e9b908268a7eefc57571943b7e9584651f2f86
    inline std::string ComputeHeader(LogType type, size_t id) {
        std::string Header;
        std::string LOG_COLOR;
        switch (type) {
            case LogType::LOG:
<<<<<<< HEAD
                LOG_COLOR = LOG_YELLOW;
                Header = "LOG                  : ";
                break;
            case LogType::STATUS:
                LOG_COLOR = LOG_CYAN;
                Header = "STATUS               : ";
                break;
            case LogType::LOG_WARNING:
                LOG_COLOR = LOG_YELLOW;
                Header = "WARNING              : ";
                break;
            case LogType::LOG_ERROR:
                LOG_COLOR = LOG_RED;
                Header = "ERROR                : ";
=======
                LOG_COLOR = LOG_COLOR_RESET;
                Header = "LOG                 ";
                break;
            case LogType::STATUS:
                LOG_COLOR = LOG_BLUE;
                Header = "STATUS              ";
                break;
            case LogType::LOG_WARNING:
                LOG_COLOR = LOG_YELLOW;
                Header = " WARNING             ";
                break;
            case LogType::LOG_ERROR:
                LOG_COLOR = LOG_RED;
                Header = " ERROR               ";
>>>>>>> 20e9b908268a7eefc57571943b7e9584651f2f86
                break;
            case LogType::SUBSTATUS:
                LOG_COLOR = LOG_BLUE;
                Header = "-- SUBSTATUS         : ";
                break;
            case LogType::ASYNC_TASK:
                LOG_COLOR = LOG_MAGENTA;
                Header = "----- ASYNC TASK [" + std::to_string(id) + "] : ";
                break;
            case LogType::NON_ASYNC_TASK:
                LOG_COLOR = LOG_MAGENTA;
                Header = "---- NON_ASYNC_TASK  : ";
                break;
            case LogType::RESULT_VALID:
                LOG_COLOR = LOG_GREEN;
                Header = "----- RESULT [VALID] : ";
                break;
            case LogType::RESULT_ERROR:
                LOG_COLOR = LOG_RED;
                Header = "----- RESULT [ERROR] : ";
                break;
            default:
                LOG_COLOR = LOG_RED;
                Header = "UNKNOWN              : ";
                break;
        }
        return LOG_COLOR + Header + LOG_COLOR_RESET;
    }


    

   inline void Log(FILE* stream, LogType type, size_t id, const char* format, ...) {
        

        std::string Header = ComputeHeader(type, id);
        va_list args;
        va_start(args, format);

<<<<<<< HEAD
        fprintf(stream, "%s", Header.c_str());
        vfprintf(stream, format, args);
=======
        logStream.str().insert(0, LOG_COLOR)
        vfprintf(stream, logStream.str().c_str(), args); // Print the log header
        vfprintf(stream, format, args); // Print the log message
>>>>>>> 20e9b908268a7eefc57571943b7e9584651f2f86
        fprintf(stream, "\n");

        va_end(args);
    }
}

