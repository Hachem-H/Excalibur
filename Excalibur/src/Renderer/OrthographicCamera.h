#pragma once

#include <string.h>
#include <cglm/cglm.h>

#include "Shader.h"

typedef struct OrthographicCamera_t
{
    mat4 projectionMatrix;
    mat4 modelMatrix;
    mat4 viewMatrix;
    mat4 mvp;

    vec2 bounds;
    vec3 position;
    float rotation;
} OrthographicCamera;

void InitializeOrthographicCamera(OrthographicCamera* camera);
void SetOrthographicCameraShader(OrthographicCamera* camera, Shader* shader);

void UpdateOrthographicCameraProjectionMatrix(OrthographicCamera* camera);
void UpdateOrthographicCameraModelMatrix(OrthographicCamera* camera);
void UpdateOrthographicCameraViewMatrix(OrthographicCamera* camera);
void UpdateOrthographicCameraMVP(OrthographicCamera* camera);
