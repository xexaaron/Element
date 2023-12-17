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

struct Pixel {
    int x;
    int y;
    COLORREF color;
};
struct PixelRegion {
    std::vector<int> x;
    std::vector<int> y;
    COLORREF color;
};



#define WM_USER_MESSAGES_BASE (WM_USER + 100)
#define WM_SET_WINDOW_POSITION (WM_USER_MESSAGES_BASE + 1)
#define WM_SET_WINDOW_SIZE (WM_USER_MESSAGES_BASE + 2)
#define WM_SET_WINDOW_COLOR (WM_USER_MESSAGES_BASE + 3)
#define WM_SET_WINDOW_STATE (WM_USER_MESSAGES_BASE + 4)
#define WM_SET_WINDOW_TITLE (WM_USER_MESSAGES_BASE + 5)
#define WM_SET_WINDOW_PIXEL (WM_USER_MESSAGES_BASE + 6)

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




WINDOWDLL_API SYSAGN_WORD WIN32_GetDeviceDimensions() {
    HDC dc = GetDC(hWnd);
    if (dc) {
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        ReleaseDC(hWnd, dc);
        SYSAGN_WORD dimensionsWord = (static_cast<uint16_t>(screenWidth) << 16) | static_cast<uint16_t>(screenHeight);
        return dimensionsWord;
    } else {
        return 0;
    }
}

WINDOWDLL_API int8_t WIN32_SetWindowPixel(int x, int y, uint32_t Red, uint32_t Green, uint32_t Blue) {
    if (hWnd) {
        COLORREF Color = RGB(Red, Green, Blue);
        Pixel* PackedParams = new Pixel;
        if (PackedParams != nullptr) {
            PackedParams->x = x;
            PackedParams->y = y;
            PackedParams->color = Color;

            LPARAM lparam = reinterpret_cast<LPARAM>(PackedParams);
            PostMessage(hWnd, WM_SET_WINDOW_PIXEL, 0, lparam);
        
        // Do not forget to release allocated memory when done
        delete PackedParams;
            return 1;
        }
        return -1;
    } else {
        return -1;
    }
    return 0; // Unreachable FUNCTION_RESULT_UNDEFINED
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
    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, WindowPosX, WindowPosY,
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
        break;
    case WM_SET_WINDOW_POSITION: {
        WindowPosX = LOWORD(lParam);
        WindowPosY = HIWORD(lParam);
        SetWindowPos(hWnd, NULL, WindowPosX, WindowPosY, WindowSizeX, WindowSizeY, SWP_NOSIZE | SWP_NOZORDER);
        break;
    }
    case WM_SET_WINDOW_SIZE: {
        WindowSizeX = LOWORD(lParam);
        WindowSizeY = HIWORD(lParam);
        SetWindowPos(hWnd, NULL, WindowPosX, WindowPosY, WindowSizeX, WindowSizeY, SWP_NOMOVE | SWP_NOZORDER);
        break;
    }
    case WM_ERASEBKGND: {
        HDC hdc = (HDC)wParam; // Get the device context
        HBRUSH hBrush = CreateSolidBrush(BackgroundColor);
        RECT rect;
        GetClientRect(hWnd, &rect);
        FillRect(hdc, &rect, hBrush);
        DeleteObject(hBrush);
        break;
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
    case WM_SET_WINDOW_PIXEL: {
        Pixel* Pix = reinterpret_cast<Pixel*>(lParam);
        HDC hdc = (HDC)wParam;
        SetPixel(hdc, Pix->x, Pix->y, Pix->color);
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


