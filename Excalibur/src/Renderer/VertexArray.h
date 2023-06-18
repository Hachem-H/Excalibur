#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "Buffer.h"

typedef struct VertexBufferLayoutElement_t
{
    uint32_t count;
    bool normalized;
} VertexBufferLayoutElement;

typedef struct VertexArray_t
{
    uint32_t stride;
    uint32_t currentIndex;

    uint32_t rendererID;
    bool isBound;

    VertexBuffer* vertexBuffers;
    IndexBuffer* indexBuffers;
} VertexArray;

void InitializeVertexArray(VertexArray* vertexArray);
void DeleteVertexArray(VertexArray* vertexArray);

void BindVertexArray(VertexArray* vertexArray);
void UnBindVertexArray(VertexArray* vertexArray);

void SetVertexArrayLayout(VertexArray* vertexArray, const VertexBufferLayoutElement* elements, const size_t count);
void PushBuffersToVertexArray(VertexArray* vertexArray, VertexBuffer vertexBuffer, IndexBuffer indexBuffer);
