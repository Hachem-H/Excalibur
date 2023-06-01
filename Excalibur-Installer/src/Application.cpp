#include <windows.h>

#include <iostream>

#define WINDOW_WIDTH 360
#define WINDOW_HEIGHT 640

#define BUTTON_WIDTH  80
#define BUTTON_HEIGHT 30
#define BUTTON_MARGIN 10

LRESULT CALLBACK WindowProc(HWND windowHandle, UINT message, WPARAM wordParam, LPARAM longParam)
{

    HWND installButtonHandle;
    HWND closeButtonHandle;

    switch (message)
    {
        case WM_CREATE:
        {
            closeButtonHandle   = CreateWindow("BUTTON", "Close", WS_VISIBLE | WS_CHILD,
                                               (WINDOW_WIDTH - BUTTON_WIDTH * 2 - BUTTON_MARGIN) / 2, WINDOW_HEIGHT - BUTTON_HEIGHT*2 - BUTTON_MARGIN*2,
                                               BUTTON_WIDTH, BUTTON_HEIGHT, windowHandle, (HMENU)1, NULL, NULL);
            installButtonHandle = CreateWindow("BUTTON", "Install", WS_VISIBLE | WS_CHILD,
                                              (WINDOW_WIDTH + BUTTON_MARGIN) / 2, WINDOW_HEIGHT - BUTTON_HEIGHT*2 - BUTTON_MARGIN*2,
                                              BUTTON_WIDTH, BUTTON_HEIGHT, windowHandle, (HMENU)2, NULL, NULL);
        } break;

        case WM_DESTROY:
        {
            PostQuitMessage(0);
        } return 0;

        case WM_COMMAND:
        {
            switch (LOWORD(wordParam))
            {
                case 1:
                {
                    SendMessage(windowHandle, WM_CLOSE, 0, 0);
                } break;

                case 2:
                {
                    std::cout << "Install Started" << std::endl;
                } break;
            }
        } break;

        case WM_PAINT:
        {
            PAINTSTRUCT paint;
            HDC handleDeviceContext = BeginPaint(windowHandle, &paint);

            FillRect(handleDeviceContext, &paint.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(windowHandle, &paint);
        } return 0;

        default: return DefWindowProc(windowHandle, message, wordParam, longParam);
    }

    (void)installButtonHandle;
    (void)closeButtonHandle;

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

    ShowWindow(windowHandle, argc);

    MSG message = {};
    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    (void)previousInstanceHandle;
    (void)argv;

    return 0;
}