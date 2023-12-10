#pragma once
/***********************************************
* @headerfile MCadEvent.h
* @date 25 / 11 / 2023
* @author Roomain
************************************************/
#include <variant>
#include <chrono>
#include "MCadMouseEvent.h"
#include "MCadKeyboardEvent.h"
using InternalEvent = std::variant<MCadKeyboardEvent, MCadMouseEvent>;

/*@brief defines the event type*/
enum class MCadEventType
{
	Event_Unknown = 0,
	Event_KeyBoard,
	Event_Mouse,
	Event_Gamepad,
	Event_Window
	//
};

struct MCadEvent
{
	std::chrono::time_point<std::chrono::system_clock> m_time;	/*!< event time*/
	MCadEventType m_type;										/*!< event type*/
	InternalEvent m_internalEvent;								/*!< internal event type defined by m_type*/
};