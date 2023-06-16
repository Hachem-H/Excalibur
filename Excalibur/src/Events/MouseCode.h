#pragma once

#include <stdint.h>

typedef enum MouseCode_t
{
	MouseCode_Button0 = 0,
	MouseCode_Button1 = 1,
	MouseCode_Button2 = 2,
	MouseCode_Button3 = 3,
	MouseCode_Button4 = 4,
	MouseCode_Button5 = 5,
	MouseCode_Button6 = 6,
	MouseCode_Button7 = 7,

	MouseCode_ButtonLast   = MouseCode_Button7,
	MouseCode_ButtonLeft   = MouseCode_Button0,
	MouseCode_ButtonRight  = MouseCode_Button1,
	MouseCode_ButtonMiddle = MouseCode_Button2
} MouseCode;

#define MOUSE_BUTTON_0      MouseCode_Button0
#define MOUSE_BUTTON_1      MouseCode_Button1
#define MOUSE_BUTTON_2      MouseCode_Button2
#define MOUSE_BUTTON_3      MouseCode_Button3
#define MOUSE_BUTTON_4      MouseCode_Button4
#define MOUSE_BUTTON_5      MouseCode_Button5
#define MOUSE_BUTTON_6      MouseCode_Button6
#define MOUSE_BUTTON_7      MouseCode_Button7
#define MOUSE_BUTTON_LAST   MouseCode_ButtonLast
#define MOUSE_BUTTON_LEFT   MouseCode_ButtonLeft
#define MOUSE_BUTTON_RIGHT  MouseCode_ButtonRight
#define MOUSE_BUTTON_MIDDLE MouseCode_ButtonMiddle
