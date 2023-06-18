#include "VertexArray.h"

#define STB_DS_IMPLEMENTATION
#include <stb_ds.h>

#include <glad/glad.h>

void InitalizeVertexArray(VertexArray* vertexArray)
{
    vertexArray->currentIndex = 0;
    vertexArray->isBound      = 1;
    vertexArray->stride       = 0;

    vertexArray->vertexBuffers = NULL;
    vertexArray->indexBuffers  = NULL;

    glGenVertexArrays(1, &vertexArray->rendererID);
    glBindVertexArray(vertexArray->rendererID);
}

void DeleteVertexArray(VertexArray* vertexArray)
{
    glDeleteVertexArrays(1, &vertexArray->rendererID);
    
    arrfree(vertexArray->vertexBuffers);
    arrfree(vertexArray->indexBuffers);
}

void BindVertexArray(VertexArray* vertexArray)
{
    if (vertexArray->isBound)
        return;

    for (int i = 0; i < arrlen(vertexArray->vertexBuffers); i++)
        BindVertexBuffer(&vertexArray->vertexBuffers[i]);
    for (int i = 0; i < arrlen(vertexArray->indexBuffers); i++)
        BindIndexBuffer(&vertexArray->indexBuffers[i]);

    glBindVertexArray(vertexArray->rendererID);
    vertexArray->isBound = true;
}

void UnBindVertexArray(VertexArray* vertexArray)
{
    if (!vertexArray->isBound)
        return;
    
    for (int i = 0; i < arrlen(vertexArray->vertexBuffers); i++)
        UnBindVertexBuffer(&vertexArray->vertexBuffers[i]);
    for (int i = 0; i < arrlen(vertexArray->indexBuffers); i++)
        UnBindIndexBuffer(&vertexArray->indexBuffers[i]);

    glBindVertexArray(0);
    vertexArray->isBound = false;
}

void SetVertexArrayLayout(VertexArray* vertexArray, const VertexBufferLayoutElement* elements, const size_t count)
{
    for (size_t i = 0; i < count; i++)
        vertexArray->stride += elements[i].count * sizeof(float);
    BindVertexArray(vertexArray);

    uint64_t offset = 0;
    for (uint32_t i = 0; i < count; i++)
    {
        const VertexBufferLayoutElement* element = &elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element->count, GL_FLOAT, element->normalized, vertexArray->stride, (const void*) offset);

        offset += element->count * sizeof(float);
    }
}

void PushBuffersToVertexArray(VertexArray* vertexArray, VertexBuffer vertexBuffer, IndexBuffer indexBuffer)
{
    arrput(vertexArray->vertexBuffers, vertexBuffer);
    arrput(vertexArray->indexBuffers,  indexBuffer);
}
