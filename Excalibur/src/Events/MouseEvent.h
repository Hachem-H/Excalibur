#pragma once

#include "Event.h"
#include "MouseCode.h"

typedef struct MouseMovedEvent_t
{
	float x;
	float y;
} MouseMovedEvent;

typedef struct MouseScrolledEvent_t
{
	float offsetX;
	float offsetY;
} MouseScrolledEvent;

typedef struct MouseButtonPressedEvent_t
{
	MouseCode button;
} MouseButtonPressedEvent;

typedef struct MouseButtonReleasedEvent_t
{
	MouseCode button;
} MouseButtonReleasedEvent;

EVENT_CLASS_TYPE(MouseMoved)
EVENT_CLASS_CATEGORY(MouseMoved, EventCategory_Mouse | EventCategory_Input)

EVENT_CLASS_TYPE(MouseScrolled)
EVENT_CLASS_CATEGORY(MouseScrolled, EventCategory_Mouse | EventCategory_Input)

EVENT_CLASS_TYPE(MouseButtonPressed)
EVENT_CLASS_CATEGORY(MouseButtonPressed, EventCategory_Mouse | EventCategory_Input)

EVENT_CLASS_TYPE(MouseButtonReleased)
EVENT_CLASS_CATEGORY(MouseButtonReleased, EventCategory_Mouse | EventCategory_Input)
