#include <glad/glad.h>
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
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.0f,  0.5f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }    

    glfwDestroyWindow(window);
    glfwTerminate();
}
