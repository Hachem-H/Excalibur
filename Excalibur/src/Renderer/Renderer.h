#pragma once

#include "OrthographicCamera.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Shader.h"

#include "Ext/Vector.h"

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

void InitializeRenderer();
void DestroyRenderer();

void SetRendererClearColor(float r, float g, float b);
void ClearRenderer();

void DrawQuad(const Rect bounds, const Vec4 color);