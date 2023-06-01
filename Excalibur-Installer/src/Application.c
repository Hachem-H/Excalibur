#include <windows.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 360

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

            FillRect(handleDeviceContext, &paint.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(windowHandle, &paint);
        } return 0;

        default: return DefWindowProc(windowHandle, message, wordParam, longParam);
    }
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