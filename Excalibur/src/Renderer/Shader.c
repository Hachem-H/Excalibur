#include "Shader.h"

#include <glad/glad.h>

static uint32_t CompileShader(uint32_t type, const char* source)
{
    uint32_t shader = glCreateShader(type);
    glShaderSource(shader, 1, (const char* const*) &source, NULL);
    glCompileShader(shader);

    int compilationStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationStatus);
    if (!compilationStatus)
    {
        int bufferSize;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufferSize);
        char* buffer = (char*) malloc(bufferSize);
        glGetShaderInfoLog(shader, bufferSize, &bufferSize, buffer);
        LOG_WARN("Could not compile shader:\n%s", buffer);
        free(buffer);
    }

    return shader;
}

void InitializeShader(Shader* shader, const char* vertexShaderSource, const char* fragmentShaderSource)
{
    shader->vertexShader   = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    shader->fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    shader->program = glCreateProgram();
    glAttachShader(shader->program, shader->vertexShader);
    glAttachShader(shader->program, shader->fragmentShader);
    glLinkProgram(shader->program);
    glValidateProgram(shader->program);
    glUseProgram(shader->program);

    shader->isBound = true;
}

void DeleteShader(Shader* shader)
{
    glDeleteShader(shader->vertexShader);
    glDeleteShader(shader->fragmentShader);
    glDeleteProgram(shader->program);
}

void BindShader(Shader* shader)
{
    if (shader->isBound)
        return;

    glUseProgram(shader->program);
    shader->isBound = true;
}

void UnBindShader(Shader* shader)
{
    if (!shader->isBound)
        return;

    glUseProgram(0);
    shader->isBound = false;
}
