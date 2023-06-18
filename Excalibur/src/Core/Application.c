#include "Application.h"

static Application* s_ApplicationInstance;
Application* GetApplication() { return s_ApplicationInstance; }

void Application_OnEvent(void* application, Event* event)
{
    EventDispatcher eventDispatcher = { event };

    Event windowCloseEvent;
    windowCloseEvent.eventData = event->eventData;
    SET_EVENT(windowCloseEvent, WindowClose);

    DispatchEvent(&eventDispatcher, application, &windowCloseEvent, (void*) &Application_OnWindowClose);
}

void Application_OnWindowClose(void* application, Event* event)
{
    ((Application*) application)->isRunning = false;
    
    (void)event;
}

Application* CreateApplication()
{
    Application* application = (Application*) malloc(sizeof(Application));

    application->window = CreateWindow((WindowOptions)
    {
        .title  = "Excalibur",
        .width  = 1280,
        .height = 720,

        .eventCallbackData = (void*) application,
        .eventCallback = &Application_OnEvent,
    });

    application->isRunning = true;
    s_ApplicationInstance = application;

    InitializeRenderer();

    return application;
}

void RunApplication(Application* application)
{
    while (application->isRunning)
    {
        SetRendererClearColor(0.1f, 0.1f, 0.1f);
        ClearRenderer();

        UpdateWindow(application->window);
    }
}

void DestroyApplication(Application* application)
{
    DestroyRenderer();
    ShutdownWindow(application->window);
    free(application);
}
