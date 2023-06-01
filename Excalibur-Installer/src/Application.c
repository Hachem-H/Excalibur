#include <stdio.h>

#include "Binaries/ExcaliburBinary.h"
#include "Binaries/BootBinary.h"

int main()
{
    FILE* file = fopen("Excalibur.exe", "wb");
    fwrite(bin_Excalibur_exe, sizeof(unsigned char), bin_Excalibur_exe_len, file);
    fclose(file);
}