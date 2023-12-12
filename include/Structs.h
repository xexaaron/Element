#ifndef STRUCTS_H
#define STRUCTS_H
    #ifdef WINDOW_STRUCTS
        #include "Enums.h"
        #include "Vector.h"
        #define WINDOW_ENUMS
        struct SWindowData {
            std::string Title;
            Vector3D<uint8_t> BackgroundColor;
            Vector2D<int> Size;
            Vector2D<int> Position;
            EWindowState State;
        };
    #endif // WINDOW_STRUCTS
#endif // STRUCTS_H