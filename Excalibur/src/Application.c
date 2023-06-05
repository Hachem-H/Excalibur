#include <GLFW/glfw3.h>

#include <stddef.h>

#define WINDOW_WIDTH 1270
#define WINDOW_HEIGHT 720

int main()
{
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
