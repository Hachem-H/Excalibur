#include "Excalibur.h"

#include "Renderer/Renderer.h"
#include "Events/Input.h"

void InitializeGame(Excalibur* game)
{
    game->player = (Rect) { 50, 50, 50, 50 };
}

void RenderGame(Excalibur* game)
{
    DrawQuad(game->player, (Vec4) { 0.4f, 0.8f, 0.2f, 1.0f });
}

void UpdateGame(Excalibur* game, float timeStep)
{
    if (IsKeyPressed(KEY_W)) game->player.y += 1000*timeStep;
    if (IsKeyPressed(KEY_S)) game->player.y -= 1000*timeStep;
    if (IsKeyPressed(KEY_A)) game->player.x -= 1000*timeStep;
    if (IsKeyPressed(KEY_D)) game->player.x += 1000*timeStep;
}

void DestroyGame(Excalibur* game)
{
    (void)game;
}
