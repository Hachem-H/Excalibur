#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <Core/Log.h>

#include <cglm/cglm.h>

typedef struct Shader_t
{
    uint32_t vertexShader;
    uint32_t fragmentShader;

    uint32_t program;
    bool isBound;
} Shader;

void InitializeShader(Shader* shader, const char* vertexShaderSource, const char* fragmentShaderSource);
void DeleteShader(Shader* shader);

void SetShaderUniformMat4(Shader* shader, const char* key, mat4 value);
void SetShaderUniformVec2f(Shader* shader, const char* key, vec2 value);
void SetShaderUniformVec3f(Shader* shader, const char* key, vec3 value);
void SetShaderUniformVec4f(Shader* shader, const char* key, vec4 value);

void BindShader(Shader* shader);
void UnBindShader(Shader* shader);
