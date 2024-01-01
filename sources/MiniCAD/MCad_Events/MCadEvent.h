#pragma once
/***********************************************
* @headerfile MCadEvent.h
* @date 26 / 12 / 2023
* @author Roomain
************************************************/
#include <variant>
#include <chrono>
#include "MCadCoord.h"
#include "FlagMacros.h"

using EventTime = std::chrono::time_point< std::chrono::system_clock>;

enum class MCadKeyModifier
{
	None			= 0,
	LeftMaj			= 1,
	RightMaj		= 1 << 1,
	LeftCtrl		= 1 << 2,
	RightCtrl		= 1 << 3,
	//
};

ENUM_FLAG_OPERATORS(MCadKeyModifier)

enum class MCadKeyFunction
{
	None	= 0,
	F1		= 1,
	F2		= 2,
	F3		= 3,
	F4		= 4,
	F5		= 5,
	F6		= 6,
	F7		= 7,
	F8		= 6,
	F7		= 7,
	F8		= 8,
	F9		= 9,
	F10		= 10,
	F11		= 11,
	F12		= 12,
	F13		= 13,
	F14		= 14,
	F15		= 15,
	F16		= 16
};

enum class MCadKey
{
	Key_None = 0,
	Key_A,
	Key_B,
	Key_C,
	Key_D,
	Key_E,
	Key_F,
	Key_G,
	Key_H,
	Key_I,
	Key_J,
	Key_K,
	Key_L,
	Key_M,
	Key_N,
	Key_O,
	Key_P,
	Key_Q,
	Key_R,
	Key_S,
	Key_T,
	Key_U,
	Key_V,
	Key_W,
	Key_X,
	Key_Y,
	Key_Z,
	Key_UP,
	Key_Down,
	Key_Left,
	Key_Right
};

enum class MCadMouseButton
{
	NoButton = 0,
	LeftButton = 1,
	RightButton = 1 << 1,
	MiddleButton = 1 << 2,
	//
};

ENUM_FLAG_OPERATORS(MCadMouseButton)

struct MCadResizeEvent
{
	int m_newWidth = 0;
	int m_newHeight = 0;
};

struct MCadKeyboardEvent
{
	MCadKeyModifier m_keyModifier = MCadKeyModifier::None;		/*!< key modifier*/
	MCadKeyFunction m_keyFunction = MCadKeyFunction::None;
	MCadKey m_key;
};


enum class MouseEventType
{
	Mouse_Press,
	Mouse_Release,
	Mouse_DoubleClick,
	Mouse_Move
};

struct MCadMouseEvent
{
	MouseEventType m_type;										/*!< mouse event type*/
	MCadKeyModifier m_keyModifier = MCadKeyModifier::None;		/*!< key modifier*/
	MCadMouseButton m_buttons = MCadMouseButton::NoButton;		/*!< mouse click button*/
	MCadCoord m_mouseCoords;									/*!< mouse coords*/
	EventTime m_eventTime;										/*!< time of emission*/
};

struct MCadSelectionEvent
{
	//
};


/*@brief base struct for event*/
struct MCadEvent
{
	enum class EventType : int
	{
		Keyboard_event,
		Mouse_event,
		Selection_event,
		Resize_event
	};


	using VariantEvent = std::variant<MCadKeyboardEvent, MCadMouseEvent, MCadSelectionEvent, MCadResizeEvent>;

	EventType m_type;	/*!< event type*/
	VariantEvent m_internalEvent;
};
