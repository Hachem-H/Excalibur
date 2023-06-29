#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "MouseCode.h"
#include "KeyCode.h"

typedef enum EVENT_TYPE_t
{
	EventType_None,

	EventType_WindowClose,
	EventType_WindowResize,
	EventType_WindowFocus,
	EventType_WindowLostFocus,
	EventType_WindowMoved,

	EventType_AppTick,
	EventType_AppUpdate,
	EventType_AppRender,

	EventType_KeyPressed,
	EventType_KeyReleased,
	EventType_KeyTyped,

	EventType_MouseButtonPressed,
	EventType_MouseButtonReleased,
	EventType_MouseMoved,
	EventType_MouseScrolled
} EventType;

typedef enum EVENT_CATEGORY_t
{
    None,

    EventCategory_Application = 1 << 0,
    EventCategory_Input       = 2 << 0,
    EventCategory_Keyboard    = 3 << 0,
    EventCategory_Mouse       = 4 << 0,
    EventCategory_MouseButton = 5 << 0,
} EventCategory;

typedef struct EventData_t
{
    int width;
    int height;

    float mouseX;
    float mouseY;
    float xOffset;
    float yOffset;

    uint32_t keyRepeatCount;
    MouseCode mouseButton;
    KeyCode keyCode;
} EventData;

typedef struct Event_t
{
    bool handled;
    
    EventData data;
    EventType type;
    EventCategory category;
} Event;

static bool DispatchEvent(Event* event, EventType type, bool (*callback)(Event*, void*), void* data)
{
	if (!event->handled)
        if (event->type == type)
        {
            event->handled = callback(event, data);
            return event->handled;
        }

	return false;
}
