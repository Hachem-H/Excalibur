#pragma once

#include "Event.h"
#include "KeyCode.h"

typedef struct KeyPressedEvent_t
{
	uint32_t repeatCount;
	KeyCode keyCode;
} KeyPressedEvent;

typedef struct KeyReleasedEvent_t
{
	KeyCode keyCode;
} KeyReleasedEvent;

typedef struct KeyTypedEvent_t
{
	KeyCode keyCode;
} KeyTypedEvent;

EVENT_CLASS_TYPE(KeyPressed)
EVENT_CLASS_CATEGORY(KeyPressed, EventCategory_Keyboard | EventCategory_Input)

EVENT_CLASS_TYPE(KeyTyped)
EVENT_CLASS_CATEGORY(KeyTyped, EventCategory_Keyboard | EventCategory_Input)

EVENT_CLASS_TYPE(KeyReleased)
EVENT_CLASS_CATEGORY(KeyReleased, EventCategory_Keyboard | EventCategory_Input)
