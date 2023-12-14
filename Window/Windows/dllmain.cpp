// WindowDLL.cpp
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

WINDOWDLL_API int8_t WINTestMessage(std::string msg) {
    if (!msg.empty()) {
        Logger::Log(stdout, LogType::RESULT_VALID, 0, "WINTestMessage(std::string msg) -> Window Manager (hWnd) is Valid");
        MessageBoxA(NULL, msg.c_str(), "Test Message", MB_OK);
        return 1;
    }
    else { 
        Logger::Log(stderr, LogType::RESULT_ERROR, 0, "WINTestMessage(std::string msg) -> Window Manager (hWnd) is NULL");
        return -1;
    }
    return 0;
}

WINDOWDLL_API int8_t WINSetWindowTitle(const char* Title) {
    if (hWnd) {
        PostMessage(hWnd, WM_SET_WINDOW_TITLE, 0, (LPARAM)Title);
        Logger::Log(stdout, LogType::RESULT_VALID, 0, "WINSetWindowTitle(const char* Title) -> Window Manager (hWnd) is Valid");
        return 1;
    }
    else {
        Logger::Log(stderr, LogType::RESULT_ERROR, 0, "WINSetWindowTitle(const char* Title) -> Window Manager (hWnd) is NULL");
        return -1;
    }
    return 0;
}
WINDOWDLL_API int8_t WINSetWindowPosition(int x, int y) {
    if (hWnd) {
        LPARAM Pos = MAKELPARAM(static_cast<WORD>(x), static_cast<WORD>(y));
        PostMessage(hWnd, WM_SET_WINDOW_POSITION, 0, Pos);
        Logger::Log(stdout, LogType::RESULT_VALID, 0, "WINSetWindowPosition(int x, int y) -> Window Manager (hWnd) is Valid");
        return 1;
    }
    else {
        Logger::Log(stderr, LogType::RESULT_ERROR, 0, "WINSetWindowPosition(int x, int y) ->Window Manager (hWnd) is NULL");
        return -1;
    }
    return 0;
}

WINDOWDLL_API int8_t WINSetWindowSize(int x, int y) {
    if (hWnd) {
        Logger::Log(stdout, LogType::RESULT_VALID, 0, "WINSetWindowSize(int x, int y) -> Window Manager (hWnd) is Valid");
        LPARAM Size = MAKELPARAM(static_cast<WORD>(x), static_cast<WORD>(y));
        PostMessage(hWnd, WM_SET_WINDOW_SIZE, 0, Size);
        return 1;
    } else {
        Logger::Log(stderr, LogType::RESULT_ERROR, 0, "WINSetWindowSize(int x, int y) -> Window Manager (hWnd) is NULL");
        return -1;
    }               
    Logger::Log(stderr, LogType::RESULT_ERROR, 0, "WINSetWindowSize(int x, int y) -> Internal function processes were skipped");
    return 0;
}

WINDOWDLL_API int8_t WINSetWindowColor(uint32_t Red, uint32_t Green, uint32_t Blue) {
    if (hWnd) {
        Logger::Log(stdout, LogType::RESULT_VALID, 0, "WINSetWindowColor(uint32_t Red, uint32_t Green, uint32_t Blue) -> Window Manager (hWnd) is Valid");
        COLORREF Color = RGB(Red, Green, Blue);
        BackgroundColor = Color;
        return 1;
    } else {
        return -1;
        Logger::Log(stderr, LogType::RESULT_ERROR, 0, "WINSetWindowColor(uint32_t Red, uint32_t Green, uint32_t Blue) -> Window Manager (hWnd) is NULL");
    }
    return 0;
}



WINDOWDLL_API int8_t WINSetWindowState(EWindowState state) {
    if (hWnd) {
        PostMessage(hWnd, WM_SET_WINDOW_STATE, 0, (LPARAM)state);
        return 1;
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
        Logger::Log(stderr, LogType::RESULT_ERROR, 0, "CreateAndRunWindow() -> hWnd = CreateWindowW(...) = NULL");
        return NULL;
    }
    Logger::Log(stdout, LogType::RESULT_VALID, 0, "CreateAndRunWindow() -> Succesfully Created window from Element.obj in Window.dll");
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
    MSG msg;
    BOOL bRet;
    while ((bRet = GetMessage(&msg, hWnd, 0, 0)) != 0) {
        if (bRet == -1) {
            Logger::Log(stderr, LogType::RESULT_ERROR, 0, "CreateAndRunWindow() -> Event Loop -> GetMessage == NULL"); 
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
        Logger::Log(stdout, LogType::RESULT_VALID, 0, "Event WM_SET_WINDOW_SIZE -> Succesfully called WndProc inside Window.dll from Element.obj");
        break;
    }
    case WM_SET_WINDOW_SIZE: {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        SetWindowPos(hWnd, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
        Logger::Log(stdout, LogType::RESULT_VALID, 0, "Event WM_SET_WINDOW_SIZE -> Succesfully called WndProc inside Window.dll from Element.obj");
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
                    Logger::Log(stdout, LogType::RESULT_VALID, 0, "WINSetWindowTitle(const char*) -> Title set successfully");
                    SetWindowText(hWnd, wc);
                }
                else {
                    Logger::Log(stderr, LogType::RESULT_ERROR, 0, "WINSetWindowTitle(const char*) -> Could not convert lparam to wchar_t");
                }

                // Free allocated memory
                delete[] wc;
            }
            else {
                Logger::Log(stderr, LogType::RESULT_ERROR, 0, "WINSetWindowTitle(const char*) -> Could not allocate memory sizeof(lparam) for wchar_t");
            }
        }
        break;
    }
    case WM_SET_WINDOW_STATE: {
        EWindowState state = static_cast<EWindowState>(lParam);
        Logger::Log(stdout, LogType::RESULT_VALID, 0, "Event WM_SET_WINDOW_STATE -> Succesfully called WndProc inside Window.dll from Element.obj");
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


