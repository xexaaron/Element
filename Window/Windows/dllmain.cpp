// WindowDLL.cpp
#define WINDOWDLL_EXPORTS
#include "dllmain.h"
#include <iostream>
#include <tuple>

// Global variables for the window
HINSTANCE hInst;
HWND hWnd;
const wchar_t szTitle[] = L"Window from DLL";
const wchar_t szWindowClass[] = L"WindowClassFromDLL";
int WindowPosX = 0;
int WindowPosY = 0;
int WindowSizeX = 800;
int WindowSizeY = 600;



#define WIN32_EVENT_SET_WINDOW_TITLE (WM_USER + 1)
#define WIN32_EVENT_SET_WINDOW_POSITION (WM_USER + 2)
#define WIN32_EVENT_SET_WINDOW_SIZE (WM_USER + 3)
#define WIN32_EVENT_SET_WINDOW_COLOR (WM_USER + 4)
#define WIN32_EVENT_SET_WINDOW_STATE (WM_USER + 5)

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

WINDOWDLL_API int8_t WIN32_TestMessage(std::string msg) {
    if (!msg.empty()) {
        MessageBoxA(NULL, msg.c_str(), "Test Message", MB_OK);
    }
    else {
        return -1;
    }
    return 0;
}

WINDOWDLL_API int8_t WIN32_SetWindowTitle(const char* Title) {
    if (hWnd) {
        PostMessage(hWnd, WIN32_EVENT_SET_WINDOW_TITLE, 0, (LPARAM)Title);
    }
    else {
        return -1;
    }
    return 0;
}
WINDOWDLL_API int8_t WIN32_SetWindowPosition(int x, int y) {
    if (hWnd) {
        LPARAM Pos = MAKELPARAM(static_cast<WORD>(x), static_cast<WORD>(y));
        PostMessage(hWnd, WIN32_EVENT_SET_WINDOW_POSITION, 0, Pos);
    }
    else {
        return -1;
    }
    return 0;
}

WINDOWDLL_API int8_t WIN32_SetWindowSize(int x, int y) {
    if (hWnd) {
        LPARAM Size = MAKELPARAM(static_cast<WORD>(x), static_cast<WORD>(y));
        PostMessage(hWnd, WIN32_EVENT_SET_WINDOW_SIZE, 0, Size);
    } else {
        return -1;
    }
    return 0;
}

WINDOWDLL_API int8_t WIN32_SetWindowColor(UINT32 Red, UINT32 Green, UINT32 Blue) {
    if (hWnd) {
        COLORREF Color = RGB(Red, Green, Blue);
        PostMessage(hWnd, WIN32_EVENT_SET_WINDOW_COLOR, 0, (LPARAM)Color);
    } else {
        return -1;
    }
    return 0;
}



WINDOWDLL_API int8_t WIN32_SetWindowState(EWindowState state) {
    if (hWnd) {
        PostMessage(hWnd, WIN32_EVENT_SET_WINDOW_STATE, 0, (LPARAM)state);
    }
    else {
        return -1;
    }
    return 0;
}

WINDOWDLL_API int CreateAndRunWindow() {
    hInst = GetModuleHandle(NULL);
    WNDCLASSEXW wcex = { sizeof(WNDCLASSEXW) };
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInst;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = szWindowClass;
    RegisterClassExW(&wcex);
    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        WindowSizeX, WindowSizeY, NULL, NULL, hInst, NULL);
    if (!hWnd) {
        return 0;
    }
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WIN32_EVENT_SET_WINDOW_POSITION: {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        SetWindowPos(hWnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        break;
    }
    case WIN32_EVENT_SET_WINDOW_SIZE: {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        SetWindowPos(hWnd, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
        break;
    }
    case WIN32_EVENT_SET_WINDOW_COLOR: {
        COLORREF color = static_cast<COLORREF>(lParam);
        HBRUSH hBrush = CreateSolidBrush(color);
        SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, reinterpret_cast<LONG_PTR>(hBrush));
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }
    case WIN32_EVENT_SET_WINDOW_STATE: {
        EWindowState state = static_cast<EWindowState>(lParam);
        switch (state) {
        case FULLSCREEN:
            ShowWindow(hWnd, SW_SHOWMAXIMIZED);
            break;
        case MAXIMIZED:
            ShowWindow(hWnd, SW_MAXIMIZE);
            break;
        case MINIMIZED:
            ShowWindow(hWnd, SW_MINIMIZE);
            break;
        default:
            ShowWindow(hWnd, SW_RESTORE);
            break;
        }
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

