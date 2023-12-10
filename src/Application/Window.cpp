#include "../../include/Window.h"

bool Window::SetState(EWindowState state) {
    if (true) {
        Data.State = state;
        return true;
    } else {
        return false;
    }
} 
bool Window::SetPosition(Vector2D<int> position) {
    if (true) {
        Data.Position = position;
        return true;
    } else {
        return false;
    }
}
bool Window::SetSize(Vector2D<int> size) {
    if (true) {
        Data.Size = size;
        return true;
    } else {
        return false;
    }
}
bool Window::SetData(SWindowData data) {
    if (true) {
        Data = data;
        return true;
    } else {
        return false;
    }
}

Vector2D<int> Window::GetPosition() {
    return Data.Position;
}

Vector2D<int> Window::GetSize() {
    return Data.Size;
}

EWindowState Window::GetWindowState() {
    return Data.State;
}

SWindowData Window::GetData() {
    return Data;
}