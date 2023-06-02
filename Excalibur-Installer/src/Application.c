#include <windows.h>
#include <commctrl.h>

#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 450
#define WINDOW_HEIGHT 138

static HWND installButton;
static HWND closeButton;

static HWND shortcutCheckbox;
static HWND launchCheckbox;

static HWND pathTextfield;
static HWND progressBar;

static HFONT defaultFont;

LRESULT CALLBACK WindowProc(HWND windowHandle, UINT message, WPARAM wordParam, LPARAM longParam)
{
    switch (message)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
        } return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT paint;
            HDC handleDeviceContext = BeginPaint(windowHandle, &paint);
            FillRect(handleDeviceContext, &paint.rcPaint, (HBRUSH)(COLOR_WINDOW));
            EndPaint(windowHandle, &paint);
        } return 0;

        default: goto closeWindow;
    }

closeWindow:
    return DefWindowProc(windowHandle, message, wordParam, longParam);
}

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE previousInstanceHandle, LPSTR argv, int argc)
{
    WNDCLASS windowClass = {};
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = instanceHandle;
    windowClass.lpszClassName = "Excalibur";
    RegisterClass(&windowClass);

    HWND windowHandle = CreateWindowEx(0, "Excalibur", "Excalibur Installer", WS_OVERLAPPEDWINDOW,
                                       CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
                                       NULL, NULL, instanceHandle, NULL);
    if (windowHandle == NULL)
        return 0;

    pathTextfield = CreateWindowEx(0, "EDIT", "C:\\Program Files\\Excalibur",
                                   WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                                   8, 8, 265, 23, windowHandle, NULL, instanceHandle, NULL);

    progressBar = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_CHILD | WS_VISIBLE,
                                 8, 37, 265, 25, windowHandle, NULL, instanceHandle, NULL);

    installButton = CreateWindow("BUTTON", "Install", WS_CHILD | WS_VISIBLE,
                                 8, 68, 75, 25, windowHandle, NULL, instanceHandle, NULL);

    closeButton = CreateWindow("BUTTON", "Close", WS_CHILD | WS_VISIBLE,
                               89, 68, 75, 25, windowHandle, NULL, instanceHandle, NULL);

    shortcutCheckbox = CreateWindow("BUTTON", "Create Desktop shortcut", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
                                    278, 14, 150, 17, windowHandle, NULL, instanceHandle, NULL);

    launchCheckbox = CreateWindow("BUTTON", "Launch after install", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
                                  278, 45, 150, 17, windowHandle, NULL, instanceHandle, NULL);

    defaultFont = CreateFont(16, 0, 0, 0, FW_NORMAL, false, false, false, 
                             DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                             DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Segoe UI");

    SendMessage(shortcutCheckbox, WM_SETFONT, (WPARAM)defaultFont, true);
    SendMessage(launchCheckbox, WM_SETFONT, (WPARAM)defaultFont, true);
    SendMessage(pathTextfield, WM_SETFONT, (WPARAM)defaultFont, true);
    SendMessage(installButton, WM_SETFONT, (WPARAM)defaultFont, true);
    SendMessage(closeButton, WM_SETFONT, (WPARAM)defaultFont, true);

    ShowWindow(windowHandle, argc);
    
    MSG message = {};
    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    (void)previousInstanceHandle;
    (void)argv;

    return message.wParam;
}
