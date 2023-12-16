#define WINDOWDLL_EXPORTS
#include "dllmain.h"


// Global variables for the window
HINSTANCE hInst;
HWND hWnd;
COLORREF BackgroundColor;
const wchar_t szTitle[] = L"Window from DLL";
const wchar_t szWindowClass[] = L"WindowClassFromDLL";
int WindowPosX = 0;
int WindowPosY = 0;
int WindowSizeX = 800;
int WindowSizeY = 600;



#define WM_USER_MESSAGES_BASE (WM_USER + 100)
#define WM_SET_WINDOW_POSITION (WM_USER_MESSAGES_BASE + 1)
#define WM_SET_WINDOW_SIZE (WM_USER_MESSAGES_BASE + 2)
#define WM_SET_WINDOW_COLOR (WM_USER_MESSAGES_BASE + 3)
#define WM_SET_WINDOW_STATE (WM_USER_MESSAGES_BASE + 4)
#define WM_SET_WINDOW_TITLE (WM_USER_MESSAGES_BASE + 5)


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

WINDOWDLL_API int8_t WIN32_TestMessage(std::string msg) {
    if (!msg.empty()) {
        MessageBoxA(NULL, msg.c_str(), "Test Message", MB_OK);
        return 1;
    }
    else { 
        return -1;
    }
    return 0;
}

WINDOWDLL_API int8_t WIN32_SetWindowTitle(const char* Title) {
    if (hWnd) {
        PostMessage(hWnd, WM_SET_WINDOW_TITLE, 0, (LPARAM)Title);
        return 1;
    }
    else {
        return -1;
    }
    return 0;
}
WINDOWDLL_API int8_t WIN32_SetWindowPosition(int x, int y) {
    if (hWnd) {
        LPARAM Pos = MAKELPARAM(static_cast<WORD>(x), static_cast<WORD>(y));
        PostMessage(hWnd, WM_SET_WINDOW_POSITION, 0, Pos);
        return 1;
    }
    else {
        return -1;
    }
    return 0;
}

WINDOWDLL_API int8_t WIN32_SetWindowSize(int x, int y) {
    if (hWnd) {
        LPARAM Size = MAKELPARAM(static_cast<WORD>(x), static_cast<WORD>(y));
        PostMessage(hWnd, WM_SET_WINDOW_SIZE, 0, Size);
        return 1;
    } else {
        return -1;
    }               
    return 0;
}

WINDOWDLL_API int8_t WIN32_SetWindowColor(uint32_t Red, uint32_t Green, uint32_t Blue) {
    if (hWnd) {
        COLORREF Color = RGB(Red, Green, Blue);
        BackgroundColor = Color;
        return 1;
    } else {
        return -1;
    }
    return 0;
}



WINDOWDLL_API int8_t WIN32_SetWindowState(EWindowState state) {
    if (hWnd) {
        PostMessage(hWnd, WM_SET_WINDOW_STATE, 0, (LPARAM)state);
        return 1;
    }
    else {
        return -1;
    }
    return 0;
}



WINDOWDLL_API int WIN32_CreateAndRunWindow() {
   
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
        return NULL;
    }
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
    MSG msg;
    BOOL bRet;
    while ((bRet = GetMessage(&msg, hWnd, 0, 0)) != 0) {
        if (bRet == -1) {
        } else {
            TranslateMessage(&msg);
            DispatchMessage(&msg); // This line sends messages to WndProc
        }
    }
    return (int)msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        std::exit(0);
    case WM_SET_WINDOW_POSITION: {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        SetWindowPos(hWnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        break;
    }
    case WM_SET_WINDOW_SIZE: {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        SetWindowPos(hWnd, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
        break;
    }
    case WM_ERASEBKGND: {
        HDC hdc = (HDC)wParam; // Get the device context
        HBRUSH hBrush = CreateSolidBrush(BackgroundColor);
        RECT rect;
        GetClientRect(hWnd, &rect);
        FillRect(hdc, &rect, hBrush);
        DeleteObject(hBrush);
    }
    case WM_SET_WINDOW_TITLE: {
        const char* utf8Title = reinterpret_cast<const char*>(lParam);

        if (utf8Title != nullptr) {
            const size_t cSize = strlen(utf8Title) + 1;
            size_t convertedChars = 0;

            // Allocate memory for the wide character string
            wchar_t* wc = new (std::nothrow) wchar_t[cSize];

            if (wc != nullptr) {
                // Perform the conversion
                if (mbstowcs_s(&convertedChars, wc, cSize, utf8Title, cSize - 1) == 0) {
                    SetWindowText(hWnd, wc);
                }
                else {
                }

                // Free allocated memory
                delete[] wc;
            }
        }
        break;
    }
    case WM_SET_WINDOW_STATE: {
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


