// WindowDLL.cpp
#define WINDOWDLL_EXPORTS
#include "dllmain.h"
#include <iostream>

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

WINDOWDLL_API int8_t WIN32_TestMessage(std::string msg) {
    
    if (!msg.empty()) {
        std::cout << "Testing Message : " << msg << std::endl;
        return 0;
    }
    else {
        return -1;
    }
}

WINDOWDLL_API int8_t WIN32_SetWindowTitle(const char* Title) {
    if (hWnd) {
        size_t length = strlen(Title) + 1;
        wchar_t* l_Title = new wchar_t[(int)length];
        MultiByteToWideChar(CP_ACP, 0, Title, -1, l_Title, (int)length);
        SetWindowText(hWnd, l_Title);
        delete[] l_Title;
        return 0;
    }
    else {
        return -1;
    }
}

WINDOWDLL_API int8_t WIN32_SetWindowPosition(int x, int y) {
    if (hWnd) {
        UINT Flags = SWP_NOSIZE;
        WindowPosX = x;
        WindowPosY = y;
        if (!SetWindowPos(hWnd, hWnd, WindowPosX, WindowPosY, WindowSizeX, WindowSizeY, Flags)) {
            DWORD error = GetLastError();
            std::cerr << "ERROR: WIN32_SetWindowPosition() -> SetWindowPos() : failed with error code :"<< std::endl << "  " << error << std::endl;
            return -1;
        }
        else {
            RECT rect;
            GetWindowRect(hWnd, &rect);
            int windowWidth = rect.right - rect.left;
            int windowHeight = rect.bottom - rect.top;
            if (windowWidth != x || windowHeight != y) {
                return -1;
            }
            else {
                return 0;
            }
        }
    }
    else {
        return -1;
    }
}

WINDOWDLL_API int8_t WIN32_SetWindowSize(int width, int height) {
    if (hWnd) {
        UINT Flags = SWP_NOMOVE;
        WindowSizeX = width;
        WindowSizeY = height;
        if (!SetWindowPos(hWnd, NULL, WindowPosX, WindowPosY, WindowSizeX, WindowSizeY, Flags)) {
            DWORD error = GetLastError();
            std::cerr << "ERROR: WIN32_SetWindowSize() -> SetWindowPos() : failed with error code :" << std::endl << "    " << error << std::endl;
            return -1;
        }
    }
    else {
        return 0;
    }
}

WINDOWDLL_API int8_t WIN32_SetWindowColor(UINT32 Red, UINT32 Green, UINT32 Blue) {
    if (hWnd) {
        COLORREF newColor = RGB(Red, Green, Blue);
        LONG_PTR style = GetWindowLongPtr(hWnd, GWL_EXSTYLE);
        if (style != 0) {
            SetWindowLongPtr(hWnd, GWL_EXSTYLE, style | WS_EX_LAYERED);
            SetLayeredWindowAttributes(hWnd, RGB(255, 255, 255), 0, LWA_COLORKEY);
            SetLayeredWindowAttributes(hWnd, newColor, 0, LWA_COLORKEY);
            return 0;
        }
        else {
            std::cerr << "ERROR: WIN32_SetWindowColor() -> Failed to get window style." << std::endl;
            return -1;
        }
    }
    else {
        std::cerr << "ERROR: WIN32_SetWindowColor() -> Window handle is not valid." << std::endl;
        return -1;
    }
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
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

