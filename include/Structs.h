#pragma once

#include "Enums.h"
#include "Vector.h"
#include <iostream>
#include <string>
#include <codecvt>
#include <locale>
#include <cstdint>
#include <cstdio>
#include <string>
#include <type_traits>

template<typename T>
concept StringType = std::is_convertible_v<T, std::string>;
struct Name {
public:
    // Constructors
    template <StringType S>
    Name(S&& str) : data(std::forward<S>(str)) {}

    Name() : data("") {}

    // Conversion operators
    explicit operator std::string() const {
        return data;
    }

    operator const char*() const {
        return data.c_str();
    }

    operator std::wstring() const {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(data);
    }

    // Comparison operators
    template <StringType S>
    bool operator==(S other) const {
        return data == std::string(other);
    }

    template <StringType S>
    bool operator!=(S other) const {
        return data != std::string(other);
    }

    // Assignment operator
    template <StringType S>
    Name& operator=(S&& other) {
        data = std::forward<S>(other);
        return *this;
    }

    // Concatenation operators
    template <StringType S>
    Name operator+(S&& other) const {
        return data + std::string(other);
    }

    template <StringType S>
    Name operator<<(S&& other) const {
        return std::string(other) + data;
    }

    // Subtraction operator (remove first occurrence)
    template <StringType S>
    Name operator-(S&& other) const {
        size_t foundPos = data.find(std::string(other));
        if (foundPos != std::string::npos) {
            return data.substr(0, foundPos) + data.substr(foundPos + other.length());
        }
        return data;
    }

    // Right-shift operator (remove last occurrence)
    template <StringType S>
    Name operator>>(S&& other) const {
        size_t foundPos = data.rfind(std::string(other));
        if (foundPos != std::string::npos) {
            return data.substr(0, foundPos) + data.substr(foundPos + other.length());
        }
        return data;
    }
private:
    std::string data;
};

struct SWindowData {
    Name Title;
    Vector3D<uint32_t> BackgroundColor;
    Vector2D<int> Size;
    Vector2D<int> Position;
    EWindowState State;
};


