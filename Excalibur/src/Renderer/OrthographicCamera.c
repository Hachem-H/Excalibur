#include "OrthographicCamera.h"

#include "Core/Application.h"

void InitializeOrthographicCamera(OrthographicCamera* camera)
{
    camera->rotation = 0.0f;
    glm_vec3_zero(camera->position);

    float bounds[] = { (float)GetApplication()->window->options.width,
                       (float)GetApplication()->window->options.height };
    glm_vec2(bounds, camera->bounds);

    glm_ortho(-camera->bounds[0], camera->bounds[0],
              -camera->bounds[1], camera->bounds[1],
              -1.0f, 1.0f, camera->projectionMatrix);

    glm_mat4_identity(camera->modelMatrix);

    mat4 rotation;    glm_mat4_identity(rotation);
    mat4 translation; glm_mat4_identity(translation);

    glm_rotate(rotation, camera->rotation, (vec3){1.0f, 1.0f, 1.0f});
    glm_translate(translation, camera->position);
 
    glm_mat4_mul(translation, rotation, camera->viewMatrix);
    UpdateOrthographicCameraMVP(camera);
}

void SetOrthographicCameraShader(OrthographicCamera* camera, Shader* shader)
{
    SetShaderUniformMat4(shader, "u_ModelViewProjection", camera->mvp); 
}

void UpdateOrthographicCameraProjectionMatrix(OrthographicCamera* camera)
{
    glm_ortho(-camera->bounds[0], camera->bounds[0],
              -camera->bounds[1], camera->bounds[1],
              -1.0f, 1.0f, camera->projectionMatrix);
    UpdateOrthographicCameraMVP(camera);
}

void UpdateOrthographicCameraModelMatrix(OrthographicCamera* camera)
{
    glm_mat4_identity(camera->modelMatrix);
    UpdateOrthographicCameraMVP(camera);
}

void UpdateOrthographicCameraViewMatrix(OrthographicCamera* camera)
{
    mat4 rotation;    glm_mat4_identity(rotation);
    mat4 translation; glm_mat4_identity(translation);

    glm_rotate(rotation, camera->rotation, (vec3){1.0f, 1.0f, 1.0f});
    glm_translate(translation, camera->position);

    glm_mat4_mul(translation, rotation, camera->viewMatrix);
    UpdateOrthographicCameraMVP(camera);
}

void UpdateOrthographicCameraMVP(OrthographicCamera* camera)
{
    mat4 MV; glm_mat4_identity(MV);
    glm_mat4_mul(camera->modelMatrix, camera->viewMatrix, MV);
    glm_mat4_mul(camera->projectionMatrix, MV, camera->mvp);
}
