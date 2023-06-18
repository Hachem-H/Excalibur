#pragma once

#include "OrthographicCamera.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Shader.h"

typedef struct RenderData_t
{
    Vertex* vertices;
    uint32_t* indices;

    uint32_t index;
} RenderData;

typedef struct Renderer
{
    OrthographicCamera camera;
    RenderData renderData;
    Shader shader;
} Renderer;

Renderer* GetRenderer();

void InitalizeRenderer();
void DestoryRenderer();

void BeginRendering();
void EndRendering();
