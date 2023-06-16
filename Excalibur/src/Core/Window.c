#include "Window.h"

static uint32_t s_GLFWWindowCount = 0;

static void s_SizeCallback(GLFWwindow* window, int width, int height)
{
    WindowOptions* windowOptions = (WindowOptions*) glfwGetWindowUserPointer(window);
    windowOptions->width = width;
    windowOptions->height = height;

    WindowResizeEvent eventData;
    eventData.width = width;
    eventData.height = height;

    Event event;
    event.eventData = (void*)&eventData;
    SET_EVENT(event, WindowResize);

    windowOptions->eventCallback(windowOptions->eventCallbackData, &event);
}

static void s_CloseCallback(GLFWwindow* window)
{
    WindowOptions* windowOptions = (WindowOptions*) glfwGetWindowUserPointer(window);

    Event event; 
    SET_EVENT(event, WindowClose);

    windowOptions->eventCallback(windowOptions->eventCallbackData, &event);
}

static void s_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    WindowOptions* windowOptions = (WindowOptions*) glfwGetWindowUserPointer(window);
    Event event;

    switch (action)
    {
    case GLFW_PRESS:
        {
            KeyPressedEvent eventData;
            eventData.keyCode = key;
            eventData.repeatCount = 0;

            event.eventData = (void*) &eventData;
            SET_EVENT(event, KeyPressed);
        } break;

    case GLFW_RELEASE:
        {
            KeyReleasedEvent eventData;
            eventData.keyCode = key;
            event.eventData = (void*) &eventData;
            SET_EVENT(event, KeyReleased);
        } break;
    
    case GLFW_REPEAT:
        {
            KeyPressedEvent eventData;
            eventData.keyCode = key;
            eventData.repeatCount = 1;

            event.eventData = (void*) &eventData;
            SET_EVENT(event, KeyPressed);
        } break;
    }

    windowOptions->eventCallback(windowOptions->eventCallbackData, &event);

    (void)scancode;
    (void)mods;
}

static void s_TypedCallback(GLFWwindow* window, uint32_t code)
{
    WindowOptions* windowOptions = (WindowOptions*) glfwGetWindowUserPointer(window);

    KeyTypedEvent eventData;
    eventData.keyCode = code;

    Event event;
    event.eventData = (void*) &eventData;
    SET_EVENT(event, KeyTyped);

    windowOptions->eventCallback(windowOptions->eventCallbackData, &event);
}

static void s_MouseCallback(GLFWwindow* window, int button, int action, int mods)
{
    WindowOptions* windowOptions = (WindowOptions*) glfwGetWindowUserPointer(window);
    Event event;

    switch (action)
    {
    case GLFW_PRESS:
        {
            MouseButtonPressedEvent eventData;
            eventData.button = button;

            event.eventData = (void*) &eventData;
            SET_EVENT(event, MouseButtonPressed);
        } break;

    case GLFW_RELEASE:
        {
            MouseButtonReleasedEvent eventData;
            eventData.button = button;

            event.eventData = (void*) &eventData;
            SET_EVENT(event, MouseButtonReleased);
        } break;
    }

    windowOptions->eventCallback(windowOptions->eventCallbackData, &event);
    (void) mods;
}

static void s_ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	WindowOptions* windowOptions = (WindowOptions*) glfwGetWindowUserPointer(window);
	
	MouseScrolledEvent eventData;
	eventData.offsetX = (float)xOffset;
	eventData.offsetY = (float)yOffset;

	Event event;
	event.eventData = (void*)&eventData;
	SET_EVENT(event, MouseScrolled);

	windowOptions->eventCallback(windowOptions->eventCallbackData, &event);
}

static void s_MouseMovedCallback(GLFWwindow* window, double x, double y)
{
   	WindowOptions* windowOptions = (WindowOptions*) glfwGetWindowUserPointer(window);
	
	MouseMovedEvent eventData;
	eventData.x = (float)x;
	eventData.y = (float)y;

	Event event;
	event.eventData = (void*)&eventData;
	SET_EVENT(event, MouseMoved);

	windowOptions->eventCallback(windowOptions->eventCallbackData, &event);
}

Window* CreateWindow(const WindowOptions options)
{
    Window* window = (Window*) malloc(sizeof(Window));
    
    if (s_GLFWWindowCount == 0)
        if (!glfwInit())
        {
            printf("[ERR]: GLFW could not be initialized.\n");
            free(window);
        }

    window->options = options;
    window->baseWindow = glfwCreateWindow(options.width, options.height, options.title, NULL, NULL);
    s_GLFWWindowCount++;

    glfwSetWindowUserPointer(window->baseWindow, &window->options);
    glfwMakeContextCurrent(window->baseWindow);
    glfwSwapInterval(options.vsync);

	glfwSetKeyCallback(window->baseWindow, &s_KeyCallback);
	glfwSetCharCallback(window->baseWindow, &s_TypedCallback);
	glfwSetScrollCallback(window->baseWindow, &s_ScrollCallback);
	glfwSetWindowSizeCallback(window->baseWindow, &s_SizeCallback);
	glfwSetWindowCloseCallback(window->baseWindow, &s_CloseCallback);
	glfwSetMouseButtonCallback(window->baseWindow, &s_MouseCallback);
	glfwSetCursorPosCallback(window->baseWindow, &s_MouseMovedCallback);
    
    return window;
}

void ShutdownWindow(Window* window)
{
    glfwDestroyWindow(window->baseWindow);
    free(window);

    s_GLFWWindowCount--;
    if (s_GLFWWindowCount == 0)
        glfwTerminate();
}

void UpdateWindow(Window* window)
{
    glfwPollEvents();
    glfwSwapBuffers(window->baseWindow);
}

void SetVSync(Window* window, const bool vsync)
{
    glfwSwapInterval(vsync);
    window->options.vsync = vsync;
}
