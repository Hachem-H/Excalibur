#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define WINDOW_WIDTH 1270
#define WINDOW_HEIGHT 720

typedef struct Vertex_t
{
    float position[2];
    float color[3];
} Vertex;

static const char* VERTEX_SHADER_SOURCE = 
    "#version 450 core\n"
    ""
    "layout (location = 0) in vec4 a_Position;"
    "layout (location = 1) in vec4 a_Color;"
    ""
    "out vec4 InColor;"
    ""
    "void main()"
    "{"
    "    gl_Position = a_Position;"
    "    InColor = a_Color;"
    "}";

static const char* FRAGMENT_SHADER_SOURCE = 
    "#version 450 core\n"
    ""
    "out vec4 OutColor;"
    "in vec4 InColor;"
    ""
    "void main()"
    "{"
    "    OutColor = InColor;"
    "    OutColor.a = 1.0;"
    "}";

int main()
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                                          "Excalibur", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    Vertex vertices[] =
    {
        (Vertex) { .position = { -0.5f, -0.5f }, .color = { 1.0f, 0.0f, 0.0f } },
        (Vertex) { .position = { -0.5f,  0.5f }, .color = { 0.0f, 1.0f, 0.0f } },
        (Vertex) { .position = {  0.5f,  0.5f }, .color = { 0.0f, 0.0f, 1.0f } },
        (Vertex) { .position = {  0.5f, -0.5f }, .color = { 1.0f, 1.0f, 1.0f } },
    };

    uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };

    uint32_t vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    uint32_t vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    uint32_t indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), (void*) (offsetof(Vertex, position)));
    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*) (offsetof(Vertex, color)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, (const char* const*) &VERTEX_SHADER_SOURCE, 0);
    glShaderSource(fragmentShader, 1, (const char* const*) &FRAGMENT_SHADER_SOURCE, 0);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    uint32_t shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vertexArray);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);

    glfwDestroyWindow(window);
    glfwTerminate();
}
