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

        DrawQuad((Rect){   0,    0, 150, 150}, (Vec4) {0.2, 0.3, 0.8, 1.0});
        DrawQuad((Rect){ -50,  -50,  25,  25}, (Vec4) {0.8, 0.4, 0.2, 1.0});
        DrawQuad((Rect){-200, -200, 100, 100}, (Vec4) {0.3, 0.8, 0.2, 1.0});

        UpdateWindow(application->window);
    }
}

void DestroyApplication(Application* application)
{
    DestroyRenderer();
    ShutdownWindow(application->window);
    free(application);
}
