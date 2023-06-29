#include "Application.h"

static Application* s_ApplicationInstance;
Application* GetApplication() { return s_ApplicationInstance; }

void Application_OnEvent(void* application, Event* event)
{
    DispatchEvent(event, EventType_WindowClose, &Application_OnWindowClose, application);
}

bool Application_OnWindowClose(Event* event, void* application)
{
    (void)application;
    (void)event;
    
    s_ApplicationInstance->isRunning = false;
    return true;
}

Application* CreateApplication()
{
    Application* application = (Application*) malloc(sizeof(Application));
    s_ApplicationInstance = application;

    application->window = CreateWindow((WindowOptions)
    {
        .title  = "Excalibur",
        .width  = 1280,
        .height = 720,

        .eventCallbackData = (void*) application,
        .eventCallback     = &Application_OnEvent,
    });

    application->framesPerSecond = 0.0f;
    application->lastFrameTime   = 0.0f;
    application->timeStep        = 0.0f;
    application->isRunning       = true;
    application->game            = (Excalibur*)malloc(sizeof(Excalibur));

    InitializeGame(application->game);
    InitializeRenderer();

    return application;
}

void UpdateApplicationTimeStep(Application* application)
{
    float time = (float)glfwGetTime();
    application->timeStep = time-application->lastFrameTime;
    application->framesPerSecond = (uint32_t)(1/application->timeStep);
    application->lastFrameTime = time;
}

void RunApplication(Application* application)
{
    while (application->isRunning)
    {
        SetRendererClearColor(0.1f, 0.1f, 0.1f);
        ClearRenderer();
        
        RenderGame(application->game);
        UpdateGame(application->game, application->timeStep);

        UpdateApplicationTimeStep(application);
        UpdateWindow(application->window);
    }
}

void DestroyApplication(Application* application)
{
    DestroyGame(application->game);
    DestroyRenderer();
    ShutdownWindow(application->window);

    free(application->game);
    free(application);
}
