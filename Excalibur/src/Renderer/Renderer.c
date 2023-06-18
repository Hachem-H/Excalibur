#include "Renderer.h"

#include <stb_ds.h>

static Renderer* s_Renderer;
Renderer* GetRenderer() { return s_Renderer; }

const char* vertexShaderSource   = ""
    "#version 330 core\n"
    ""
    "layout (location = 0) in vec4 a_Position;"
    "layout (location = 1) in vec4 a_Colour;"
    ""
    "out vec4 OutColor;"
    "uniform mat4 a_ModelViewProjection;"
    ""
    "void main()"
    "{"
    "   gl_Position = a_Position * u_MVP;"
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

void InitalizeRenderer()
{
    Renderer* renderer = (Renderer*) malloc(sizeof(Renderer));

    InitializeShader(&renderer->shader, vertexShaderSource, fragmentShaderSource);
    InitializeOrthographicCamera(&renderer->camera);

    renderer->renderData.vertices = NULL;
    renderer->renderData.indices  = NULL;
    renderer->renderData.index    = 0;

    s_Renderer = renderer;
}

void DestoryRenderer()
{
    DeleteShader(&s_Renderer->shader);

    arrfree(s_Renderer->renderData.vertices);
    arrfree(s_Renderer->renderData.indices);
    free(s_Renderer);
}

void BeginRendering()
{
    
}

void EndRendering()
{

}
