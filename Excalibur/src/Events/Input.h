#pragma once

#include "KeyCode.h"
#include "MouseCode.h"

#include <stdbool.h>

bool IsKeyPressed(KeyCode key);
bool IsMouseButtonPressed(MouseCode button);
void GetMousePosition(double* x, double* y);
