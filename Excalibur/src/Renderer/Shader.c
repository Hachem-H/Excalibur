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

void SetShaderUniformMat4(Shader* shader, const char* key, mat4 value)
{
	int uniformLocation = glGetUniformLocation(shader->program, key);

	if (!uniformLocation)
	{
        glUniformMatrix4fv(uniformLocation, 1, false, value[0]);
		BindShader(shader);
	}
	else 
        LOG_ERROR("Could Not Find Uniform: %s", key);
}

void SetShaderUniformVec2f(Shader* shader, const char* key, vec2 value)
{
	int uniformLocation = glGetUniformLocation(shader->program, key);

	if (!uniformLocation)
	{
        glUniform2f(uniformLocation, value[0], value[1]);
		BindShader(shader);
	}
	else 
        LOG_ERROR("Could Not Find Uniform: %s", key);
}

void SetShaderUniformVec3f(Shader* shader, const char* key, vec3 value)
{
	int uniformLocation = glGetUniformLocation(shader->program, key);

	if (!uniformLocation)
	{
        glUniform3f(uniformLocation, value[0], value[1], value[2]);
		BindShader(shader);
	}
	else 
        LOG_ERROR("Could Not Find Uniform: %s", key);
}

void SetShaderUniformVec4f(Shader* shader, const char* key, vec4 value)
{
	int uniformLocation = glGetUniformLocation(shader->program, key);

	if (!uniformLocation)
	{
        glUniform4f(uniformLocation, value[0], value[1], value[2], value[3]);
		BindShader(shader);
	}
	else 
        LOG_ERROR("Could Not Find Uniform: %s", key);
}
