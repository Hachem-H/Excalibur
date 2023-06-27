#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Window.h"
#include "Excalibur.h"

#include "Renderer/Renderer.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

typedef struct Application_t
{
    bool isRunning;

    float    timeStep;
    float    lastFrameTime;
    uint32_t framesPerSecond;

    Window* window;
    Excalibur* game;
} Application;

Application* CreateApplication();
Application* GetApplication();

void RunApplication(Application* application);
void UpdateApplicationTimeStep(Application* application);
void DestroyApplication(Application* application);

void Application_OnWindowClose(void* application, Event* event);
void Application_OnEvent(void* application, Event* event);
