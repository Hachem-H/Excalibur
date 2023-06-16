#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t EventType;
typedef uint8_t EventCategory;

#define __CONCATENATE(x, y) x##y

#define EVENT_CLASS_TYPE(type) \
	static EventType __##type##_GetType() { return EventType_##type; }

#define EVENT_CLASS_CATEGORY(type, category) \
	static EventCategory __##type##_GetCategoryFlags() { return category; }

#define SET_EVENT(name, type)                            \
	name.GetType = __##type##_GetType;                   \
	name.GetCategoryFlags = __##type##_GetCategoryFlags; \

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
} EVENT_TYPE;

typedef enum EVENT_CATEGORY_t
{
    None,

    EventCategory_Application = 1 << 0,
    EventCategory_Input       = 2 << 0,
    EventCategory_Keyboard    = 3 << 0,
    EventCategory_Mouse       = 4 << 0,
    EventCategory_MouseButton = 5 << 0,
} EVENT_CATEGORY;

typedef struct Event_t
{
    bool handled;

    void* eventData;
    EventType(*GetType)();
    EventCategory(*GetCategoryFlags)();
} Event;

typedef struct EventDispatcher_t
{
    Event* event;
} EventDispatcher;

static bool EventInCategory(const Event* event, const EventCategory category) 
{ 
    return event->GetCategoryFlags(event) & category; 
}

static bool DispatchEvent(EventDispatcher* dispatcher, void* eventData, Event* event, void* callback(void* eventData, Event* event))
{
	if (dispatcher->event->GetType(dispatcher->event) == event->GetType(event))
	{
		dispatcher->event->handled = callback(eventData, event);
		return true;
	}

	return false;
}
