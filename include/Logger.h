#pragma once
#include "Enums.h"
#include <cstdio>
#include <cstdarg>
#include <sstream>

namespace Logger {
    inline static size_t HEADER_BUFFER_LENGTH = 20;

    inline std::string ComputeHeader(LogType type, size_t id) {
        std::string Header;
        switch (type) {
            case LogType::LOG:
                Header = "LOG                 ";
                break;
            case LogType::STATUS:
                Header = "STATUS              ";
                break;
            case LogType::LOG_WARNING:
                Header = " WARNING             ";
                break;
            case LogType::LOG_ERROR:
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
        vfprintf(stream, logStream.str().c_str(), args); // Print the log header
        vfprintf(stream, format, args); // Print the log message
        fprintf(stream, "\n");
        va_end(args);
    }
}

