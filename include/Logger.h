#pragma once
#include "Enums.h"
#include <cstdio>
#include <sstream>

namespace Logger {
    const size_t HEADER_BUFFER_LENGTH = 20;
    size_t CalculateHeaderLength(size_t id, const std::string& message, const std::string& additionalInfo) {
        std::string header = "[" + std::to_string(id) + "] " + message + additionalInfo;
        return header.length();
    }

    void LogMyString(FILE* stream, size_t id, const std::string& message, size_t headerBufferLength, const std::string& additionalInfo = "") {
        size_t headerLength = CalculateHeaderLength(id, message, additionalInfo);
        size_t spacesNeeded = 0;

        if (headerLength > headerBufferLength) {
            spacesNeeded = headerLength - headerBufferLength;
        }

        std::string spaces(spacesNeeded, ' ');
        fprintf(stream, "[%s%s] : %s\n", spaces.c_str(), std::to_string(id).c_str(), message.c_str());
    }
}


