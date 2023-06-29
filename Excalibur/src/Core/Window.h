#pragma once

#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "Log.h"

#include "Events/Event.h"

typedef struct WindowOptions_t
{
    char* title;
    uint32_t width;
    uint32_t height;
    bool vsync;

    void* eventCallbackData;
    void(*eventCallback)(void*, Event*);
} WindowOptions;

typedef struct Window_t
{
    WindowOptions options;
    GLFWwindow* baseWindow;
} Window;

Window* CreateWindow(const WindowOptions options);
void ShutdownWindow(Window* window);

void UpdateWindow(Window* window);
void ShutdownWindow(Window* window);
void SetVSync(Window* window, const bool vsync);
