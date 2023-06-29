#include "Window.h"

static uint32_t s_GLFWWindowCount = 0;

static void s_SizeCallback(GLFWwindow* window, int width, int height)
{
    WindowOptions* windowOptions = (WindowOptions*) glfwGetWindowUserPointer(window);
    windowOptions->width = width;
    windowOptions->height = height;

    Event event = { .handled  = false,
                    .type     = EventType_WindowResize,
                    .category = EventCategory_Application };
    event.data.width  = width;
    event.data.height = height;

    windowOptions->eventCallback(windowOptions->eventCallbackData, &event);
}

static void s_CloseCallback(GLFWwindow* window)
{
	WindowOptions* windowOptions = (WindowOptions*) glfwGetWindowUserPointer(window);
	Event event = { .handled  = false,
                    .type     = EventType_WindowClose,
                    .category = EventCategory_Application };
	windowOptions->eventCallback(windowOptions->eventCallbackData, &event);
}

static void s_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	WindowOptions* windowOptions = (WindowOptions*) glfwGetWindowUserPointer(window);
	
	Event event = { .handled  = false,
                    .category = EventCategory_Input 
                              | EventCategory_Keyboard }; 
    event.data.keyCode = key;

	switch (action)
	{
	case GLFW_PRESS:   { event.data.keyRepeatCount = 0;
					     event.type = EventType_KeyPressed;  break; }
	case GLFW_RELEASE: { event.type = EventType_KeyReleased; break; }
	case GLFW_REPEAT:  { event.data.keyRepeatCount = 1;
				 		 event.type = EventType_KeyPressed;  break; }
	}

	windowOptions->eventCallback(windowOptions->eventCallbackData, &event);

    (void)scancode;
    (void)mods;
}

static void s_TypedCallback(GLFWwindow* window, uint32_t code)
{
	WindowOptions* windowOptions = (WindowOptions*) glfwGetWindowUserPointer(window);
	Event event = { .handled  = false,
                    .type     = EventType_KeyTyped,
                    .category = EventCategory_Input 
                              | EventCategory_Keyboard }; 
    event.data.keyCode = code;
	windowOptions->eventCallback(windowOptions->eventCallbackData, &event);
}

static void s_MouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	WindowOptions* windowOptions = (WindowOptions*) glfwGetWindowUserPointer(window);
	Event event = { .handled = false,
                    .category = EventCategory_Input 
                               | EventCategory_Mouse
                               | EventCategory_MouseButton }; 
    event.data.mouseButton = button;

	switch (action)
	{
	case GLFW_PRESS:   { event.type = EventType_MouseButtonPressed;  break; }
	case GLFW_RELEASE: { event.type = EventType_MouseButtonReleased; break; }
	}

	windowOptions->eventCallback(windowOptions->eventCallbackData, &event);
    (void) mods;
}

static void s_ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	WindowOptions* windowOptions = (WindowOptions*)glfwGetWindowUserPointer(window);
	Event event = { .handled = false,
                    .type = EventType_MouseScrolled,
                    .category = EventCategory_Mouse 
                              | EventCategory_Input };
	event.data.xOffset = (float)xOffset;
	event.data.yOffset = (float)yOffset;
	windowOptions->eventCallback(windowOptions->eventCallbackData, &event);
}

static void s_MouseMovedCallback(GLFWwindow* window, double x, double y)
{
	WindowOptions* windowOptions = (WindowOptions*)glfwGetWindowUserPointer(window);
    Event event = { .handled = false,
                    .type = EventType_MouseMoved,
                    .category = EventCategory_Mouse 
                              | EventCategory_Input }; 
    event.data.mouseX = (float)x;
    event.data.mouseY = (float)y;
    windowOptions->eventCallback(windowOptions->eventCallbackData, &event);
}

Window* CreateWindow(const WindowOptions options)
{
    Window* window = (Window*) malloc(sizeof(Window));
    
    if (s_GLFWWindowCount == 0)
        if (!glfwInit())
        {
            LOG_ERROR("GLFW could not be initialized.");
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
