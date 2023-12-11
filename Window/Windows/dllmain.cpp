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

WINDOWDLL_API void WIN32_TestMessage(std::string msg) {
    if (!msg.empty()) {
        std::cout << "Testing Message : " << msg << std::endl;
    }
    
}

WINDOWDLL_API void WIN32_SetWindowTitle(const char* Title) {
    if (hWnd) {
        size_t length = strlen(Title) + 1; // Calculate the length of the string including null terminator
        // Allocate memory for wide character string
        wchar_t* l_Title = new wchar_t[(int)length];
        // Convert narrow character string to wide character string
        MultiByteToWideChar(CP_ACP, 0, Title, -1, l_Title, (int)length);
        SetWindowText(hWnd, l_Title);
        delete[] l_Title;
    }
    else {
        std::cerr << "ERROR: Window handle is not valid." << std::endl;
    }
}

WINDOWDLL_API void WIN32_SetWindowPosition(int x, int y) {
    if (hWnd) {
        UINT Flags = SWP_NOSIZE;
        WindowPosX = x;
        WindowPosY = y;
        if (!SetWindowPos(hWnd, hWnd, WindowPosX, WindowPosY, WindowSizeX, WindowSizeY, Flags)) {
            DWORD error = GetLastError();
            std::cerr << "ERROR: SetWindowPos failed with error code " << error << std::endl;
        }
        else {
            RECT rect;
            GetWindowRect(hWnd, &rect);
            int windowWidth = rect.right - rect.left;
            int windowHeight = rect.bottom - rect.top;
            // Check Function Success
            if (windowWidth != x || windowHeight != y) {
                std::cerr << "ERROR: Window resizing failed! Window Position: (" << windowWidth << ", " << windowHeight
                    << ") != WIN32_SetWindowPosition(" << x << ", " << y << ")" << std::endl;
            }
        }
    }
    else {
        std::cerr << "ERROR: Window handle is not valid." << std::endl;
    }
}

WINDOWDLL_API void WIN32_SetWindowSize(int width, int height) {
    if (hWnd) {
        UINT Flags = SWP_NOMOVE;
        WindowSizeX = width;
        WindowSizeY = height;
        if (!SetWindowPos(hWnd, NULL, WindowPosX, WindowPosY, WindowSizeX, WindowSizeY, Flags)) {
            DWORD error = GetLastError();
            std::cerr << "ERROR: SetWindowPos failed with error code " << error << std::endl;
        }
    }
    else {
        std::cerr << "ERROR: Window handle is not valid." << std::endl;
    }
}

WINDOWDLL_API void WIN32_SetWindowColor(UINT32 Red, UINT32 Green, UINT32 Blue) {
    if (hWnd) {
        // ... (Remaining code remains unchanged)
    }
    else {
        std::cerr << "ERROR: Window handle is not valid." << std::endl;
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

