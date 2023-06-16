#pragma once

#include "Event.h"

typedef struct WindowResizeEvent_t
{
	int width;
	int height;
} WindowResizeEvent;

EVENT_CLASS_TYPE(WindowResize)
EVENT_CLASS_CATEGORY(WindowResize, EventCategory_Application)

EVENT_CLASS_TYPE(WindowClose)
EVENT_CLASS_CATEGORY(WindowClose, EventCategory_Application)

EVENT_CLASS_TYPE(AppTick)
EVENT_CLASS_CATEGORY(AppTick, EventCategory_Application)

EVENT_CLASS_TYPE(AppUpdate)
EVENT_CLASS_CATEGORY(AppUpdate, EventCategory_Application)

EVENT_CLASS_TYPE(AppRender)
EVENT_CLASS_CATEGORY(AppRender, EventCategory_Application)
