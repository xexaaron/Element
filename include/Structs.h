#pragma once

#include "Enums.h"
#include "Vector.h"
#include <iostream>
#include <string>
#include <codecvt>
#include <cstdint>

struct Name {
    Name() : m_Name("") {}
    Name(const char* name) : m_Name(name) {}
    Name(const std::string& name) : m_Name(name) {}
    Name(const std::wstring& name) : m_Name(wideToNarrow(name)) {}

    const char* c_str() const {
        return m_Name.c_str();
    }

    operator std::string() const {
        return m_Name;
    }
private:
    std::string m_Name;

    static std::string wideToNarrow(const std::wstring& wideString) {
        // Convert wide string to narrow string
        return std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(wideString);
    }
};


struct SWindowData {
    Name Title;
    Vector3D<uint32_t> BackgroundColor;
    Vector2D<int> Size;
    Vector2D<int> Position;
    EWindowState State;
};


