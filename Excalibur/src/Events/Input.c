#include "Input.h"

#include "Core/Window.h"
#include "Core/Application.h"

bool IsKeyPressed(KeyCode key)
{
    Application* application = GetApplication();
	GLFWwindow* window = (GLFWwindow*)(application->window->baseWindow);
	int state = glfwGetKey(window, (int32_t)(key));
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool IsMouseButtonPressed(MouseCode button)
{
	Application* application = GetApplication();
	GLFWwindow* window = (GLFWwindow*)(application->window->baseWindow);
	int state = glfwGetMouseButton(window, (int32_t)(button));
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

void GetMousePosition(double* x, double* y)
{
	Application* application = GetApplication();
	GLFWwindow* window = (GLFWwindow*)(application->window->baseWindow);
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

    *x = xpos;
    *y = ypos;
}