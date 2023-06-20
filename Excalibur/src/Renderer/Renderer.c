#include <glad/glad.h>

#include "Renderer.h"
#include "Core/Application.h"

#include <stb_ds.h>

static Renderer* s_Renderer;
Renderer* GetRenderer() { return s_Renderer; }

const char* vertexShaderSource   = ""
    "#version 330 core\n"
    ""
    "layout (location = 0) in vec4 a_Position;"
    "layout (location = 1) in vec4 a_Color;"
    ""
    "out vec4 OutColor;"
    "uniform mat4 u_ModelViewProjection;"
    ""
    "void main()"
    "{"
    "   gl_Position = a_Position * u_ModelViewProjection;"
    "   OutColor = a_Color;"
    "}";

const char* fragmentShaderSource = ""
    "#version 330 core\n"
    ""
    "in vec4 OutColor;"
    ""
    "void main()"
    "{"
    "   gl_FragColor = OutColor;"
    "}";

void InitializeRenderer()
{
    Renderer* renderer = (Renderer*) malloc(sizeof(Renderer));

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    InitializeShader(&renderer->shader, vertexShaderSource, fragmentShaderSource);
    InitializeOrthographicCamera(&renderer->camera);

    renderer->renderData.vertices = NULL;
    renderer->renderData.indices  = NULL;
    renderer->renderData.index    = 0;

    s_Renderer = renderer;
}

void DestroyRenderer()
{
    DeleteShader(&s_Renderer->shader);

    arrfree(s_Renderer->renderData.vertices);
    arrfree(s_Renderer->renderData.indices);
    free(s_Renderer);
}

void SetRendererClearColor(float r, float g, float b)
{
    glClearColor(r, g, b, 1.0f);
}

void ClearRenderer()
{
    glClear(GL_COLOR_BUFFER_BIT);

    RenderData* renderData = &s_Renderer->renderData;

    VertexArray vertexArray;
    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;

    InitializeVertexArray(&vertexArray);
    InitializeVertexBufferFromData(&vertexBuffer, renderData->vertices, arrlen(renderData->vertices));
    InitializeIndexBuffer(&indexBuffer, renderData->indices, arrlen(renderData->indices));

    VertexBufferLayoutElement layouts[2] = {{2, false}, 
                                            {4, false}};

    SetVertexArrayLayout(&vertexArray, layouts, 2);
    PushBuffersToVertexArray(&vertexArray, vertexBuffer, indexBuffer);

    SetOrthographicCameraShader(&s_Renderer->camera, &s_Renderer->shader);
    BindShader(&s_Renderer->shader);
    BindVertexArray(&vertexArray);

    glDrawElements(GL_TRIANGLES, arrlen(renderData->indices), GL_UNSIGNED_INT, NULL);

    DeleteVertexBuffer(&vertexBuffer);
    DeleteIndexBuffer(&indexBuffer);
    DeleteVertexArray(&vertexArray);

    arrfree(renderData->vertices);
    arrfree(renderData->indices);
    renderData->index = 0;
}


void DrawQuad(const Rect bounds, const Vec4 color)
{
    Renderer* renderer = GetRenderer();

    uint32_t index = renderer->renderData.index;

    Vertex vertices[4] = 
    {
        (Vertex) { .position = { bounds.x,          bounds.y},          .color = {color.r, color.g, color.b, color.a}},
        (Vertex) { .position = { bounds.x,          bounds.y-bounds.h}, .color = {color.r, color.g, color.b, color.a}},
        (Vertex) { .position = { bounds.x+bounds.w, bounds.y-bounds.h}, .color = {color.r, color.g, color.b, color.a}},
        (Vertex) { .position = { bounds.x+bounds.w, bounds.y},          .color = {color.r, color.g, color.b, color.a}},
    };

    uint32_t indices[6] = 
    {
        index,
        index + 1,
        index + 2,
        index + 2,
        index + 3,
        index,
    };


    for (int i = 0; i < 4; i++)
        arrpush(renderer->renderData.vertices, vertices[i]);
    for (int i = 0; i < 6; i++)
        arrpush(renderer->renderData.indices, indices[i]);

    renderer->renderData.index += 4;
}