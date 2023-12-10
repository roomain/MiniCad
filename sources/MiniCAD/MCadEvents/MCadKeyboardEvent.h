#pragma once
/***********************************************
* @headerfile MCadKeyboardEvent.h
* @date 25 / 11 / 2023
* @author Roomain
************************************************/

enum class MCadKeyboardModifier
{
	Modifier_None		= 0,
	Modifier_Alt		= 1,
	Modifier_AltGr		= 1 << 1,
	Modifier_Maj		= 1 << 2,
	Modifier_CtrlLeft	= 1 << 3,
	Modifier_CtrlRight	= 1 << 4,
	Modifier_Fn			= 1 << 5
};

constexpr MCadKeyboardModifier operator |(const MCadKeyboardModifier a_first, const MCadKeyboardModifier a_second)
{
	return static_cast< MCadKeyboardModifier >( static_cast< int >( a_first ) | static_cast< int >( a_second ) );
}

constexpr MCadKeyboardModifier operator &(const MCadKeyboardModifier a_first, const MCadKeyboardModifier a_second)
{
	return static_cast< MCadKeyboardModifier >( static_cast< int >( a_first ) & static_cast< int >( a_second ) );
}

enum class MCadKey
{
	Key_None = 0, Key_A,
	Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H, Key_I, Key_J,
	Key_K, Key_L, Key_M, Key_N, Key_O, Key_P, Key_Q, Key_R, Key_S, 
	Key_T, Key_U, Key_V, Key_W, Key_X, Key_Y, Key_Z,
	Key_F1, Key_F2, Key_F3, Key_F4, Key_F5, Key_F6, Key_F7, Key_F8,
	Key_F9, Key_F10, Key_F11, Key_F12, Key_F13, Key_F14, Key_F15, Key_F16,
	Key_0, Key_1, Key_2, Key_3, Key_4, Key_5, Key_6, Key_7, Key_8, Key_9,
	Key_Up, Key_Down, Key_Left, Key_Right
};

struct MCadKeyboardEvent
{
	MCadKeyboardModifier m_modifier;
	MCadKey m_key;
};
