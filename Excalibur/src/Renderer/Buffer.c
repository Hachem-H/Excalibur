#include "Buffer.h"

#include <glad/glad.h>

void InitializeVertexBufferFromData(VertexBuffer* vertexBuffer, Vertex* buffer, const size_t count)
{
    vertexBuffer->isBound = true;
    vertexBuffer->buffer  = buffer;
    vertexBuffer->count   = count;

    glGenBuffers(1, &vertexBuffer->rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->rendererID);
    glBufferData(GL_ARRAY_BUFFER, count*sizeof(Vertex), buffer, GL_STATIC_DRAW);
}

void InitializeVertexBufferFromSize(VertexBuffer* vertexBuffer, const size_t count)
{
    vertexBuffer->isBound = true;
    vertexBuffer->buffer  = NULL;
    vertexBuffer->count   = count;

    glGenBuffers(1, &vertexBuffer->rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->rendererID);
    glBufferData(GL_ARRAY_BUFFER, count*sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);
}

void InitializeIndexBuffer(IndexBuffer* indexBuffer, uint32_t* buffer, const size_t count)
{
    indexBuffer->isBound = true;
    indexBuffer->buffer  = buffer;
    indexBuffer->count   = count;

    glGenBuffers(1, &indexBuffer->rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(uint32_t), buffer, GL_STATIC_DRAW);
}

void BindVertexBuffer(VertexBuffer* vertexBuffer)
{
    if (vertexBuffer->isBound)
        return;

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->rendererID);
    vertexBuffer->isBound = true;
}

void BindIndexBuffer(IndexBuffer* indexBuffer)
{
    if (indexBuffer->isBound)
        return;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->rendererID);
    indexBuffer->isBound = true;
}

void UnBindVertexBuffer(VertexBuffer* vertexBuffer)
{
    if (!vertexBuffer->isBound)
        return;
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    vertexBuffer->isBound = false;
}

void UnBindIndexBuffer(IndexBuffer* indexBuffer)
{
    if (!indexBuffer->isBound)
        return;
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    indexBuffer->isBound = false;
}

void SetVertexBufferData(VertexBuffer* vertexBuffer, Vertex* buffer, const size_t count)
{
    BindVertexBuffer(vertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, count*sizeof(Vertex), buffer);
}

void DeleteVertexBuffer(VertexBuffer* vertexBuffer)
{
    glDeleteBuffers(1, &vertexBuffer->rendererID);
}

void DeleteIndexBuffer(IndexBuffer* indexBuffer)
{
    glDeleteBuffers(1, &indexBuffer->rendererID);
}

