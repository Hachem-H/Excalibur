#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct Vertex_t
{
    float position[2];
    float color[4];
} Vertex;

typedef struct VertexBuffer_t
{
    bool isBound;
    uint32_t rendererID;

    Vertex* buffer;
    size_t count;
} VertexBuffer;

typedef struct IndexBuffer_t
{
    bool isBound;
    uint32_t rendererID;

    uint32_t* buffer;
    size_t count;
} IndexBuffer;

void InitializeVertexBufferFromData(VertexBuffer* vertexBuffer, Vertex* buffer, const size_t count);
void InitializeVertexBufferFromSize(VertexBuffer* vertexBuffer, const size_t count);
void InitializeIndexBuffer(IndexBuffer* indexBuffer, uint32_t* buffer, const size_t count);

void BindVertexBuffer(VertexBuffer* vertexBuffer);
void BindIndexBuffer(IndexBuffer* indexBuffer);

void UnBindVertexBuffer(VertexBuffer* vertexBuffer);
void UnBindIndexBuffer(IndexBuffer* indexBuffer);

void SetVertexBufferData(VertexBuffer* vertexBuffer, Vertex* buffer, const size_t count);

void DeleteVertexBuffer(VertexBuffer* vertexBuffer);
void DeleteIndexBuffer(IndexBuffer* indexBuffer);
