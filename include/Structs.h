#pragma once
#include "Enums.h"
#include "Vector.h"
#define WINDOW_ENUMS
struct SWindowData {
    std::string Title;
    Vector3D<UINT32> BackgroundColor;
    Vector2D<int> Size;
    Vector2D<int> Position;
    EWindowState State;
};

