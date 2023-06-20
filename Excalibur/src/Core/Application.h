#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Window.h"

#include "Renderer/Renderer.h"

#include "Events/Event.h"
#include "Events/Input.h"
#include "Events/ApplicationEvent.h"

typedef struct Application_t
{
    bool isRunning;
    Vec2 playerPosition;
    Window* window;
} Application;

Application* CreateApplication();
Application* GetApplication();

void RunApplication(Application* application);
void DestroyApplication(Application* application);

void Application_OnWindowClose(void* application, Event* event);
void Application_OnEvent(void* application, Event* event);
