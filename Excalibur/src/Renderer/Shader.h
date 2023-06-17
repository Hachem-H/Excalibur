#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <Core/Log.h>

typedef struct Shader_t
{
    uint32_t vertexShader;
    uint32_t fragmentShader;

    uint32_t program;
    bool isBound;
} Shader;

void InitializeShader(Shader* shader, const char* vertexShaderSource, const char* fragmentShaderSource);
void DeleteShader(Shader* shader);

void BindShader(Shader* shader);
void UnBindShader(Shader* shader);
