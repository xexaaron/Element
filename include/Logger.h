#pragma once
#include "Enums.h"
#include <cstdio>
#include <cstdarg>
#include <sstream>


#define LOG_COLOR_RESET   "\033[0m"
#define LOG_RED           "\033[31m"
#define LOG_GREEN         "\033[32m"
#define LOG_YELLOW        "\033[33m"
#define LOG_BLUE          "\033[34m"
#define LOG_MAGENTA       "\033[35m"
#define LOG_CYAN          "\033[36m"
#define LOG_WHITE         "\033[37m"


namespace Logger {
    inline static size_t HEADER_BUFFER_LENGTH = 20;
    inline static std::string LOG_COLOR = LOG_COLOR_RESET;
    inline std::string ComputeHeader(LogType type, size_t id) {
        std::string Header;
        switch (type) {
            case LogType::LOG:
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
                break;
            case LogType::SUBSTATUS:
                Header = "-- SUBSTATUS         ";
                break;
            case LogType::ASYNC_TASK:
                Header = "---- ASYNC TASK [" + std::to_string(id) + "] ";
                break;
            case LogType::NON_ASYNC_TASK:
                Header = "---- NON_ASYNC_TASK  ";
                break;
            default:
                Header = "UNKNOWN              ";
                break;
        }
        return Header;
    }

    inline size_t CalculateHeaderLength(const std::string& header) {
        return header.length();
    }

    inline void Log(FILE* stream, LogType type, size_t id, const char* format, ...) {
        std::string Header = ComputeHeader(type, id);
        size_t headerLength = Header.length();

        // Adjust HEADER_BUFFER_LENGTH if necessary
        if (headerLength > HEADER_BUFFER_LENGTH) {
            HEADER_BUFFER_LENGTH = headerLength;
        }

        std::ostringstream logStream;
        logStream << Header;

        // Calculate the number of spaces needed for padding
        size_t spacesNeeded = HEADER_BUFFER_LENGTH - headerLength;

        logStream << std::string(spacesNeeded, ' ') << " : ";

        va_list args;
        va_start(args, format);

        logStream.str().insert(0, LOG_COLOR)
        vfprintf(stream, logStream.str().c_str(), args); // Print the log header
        vfprintf(stream, format, args); // Print the log message
        fprintf(stream, "\n");
        va_end(args);
    }
}

