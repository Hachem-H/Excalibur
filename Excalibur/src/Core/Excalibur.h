#pragma once

#include "Ext/Vector.h"

typedef struct Excalibur_t
{
    Rect player;
} Excalibur;

void InitializeGame(Excalibur* game);
void RenderGame(Excalibur* game);
void UpdateGame(Excalibur* game, float timeStep);
void DestroyGame(Excalibur* game);
