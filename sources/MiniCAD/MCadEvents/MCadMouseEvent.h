#pragma once
/***********************************************
* @headerfile MCadMouseEvent.h
* @date 28 / 11 / 2023
* @author Roomain
************************************************/
#include <glm/glm.hpp>

enum class MCadMouseButton
{
	Button_None		= 0,
	Button_Left		= 1,
	Button_Middle	= 1 << 1,
	Button_Right	= 1 << 2,
	Button_3		= 1 << 3,
	Button_4		= 1 << 4,
	Button_5		= 1 << 5,
	Button_6		= 1 << 6
};

constexpr MCadMouseButton operator |(const MCadMouseButton a_first, const MCadMouseButton a_second)
{
	return static_cast< MCadMouseButton >( static_cast< int >( a_first ) | static_cast< int >( a_second ) );
}

constexpr MCadMouseButton operator &(const MCadMouseButton a_first, const MCadMouseButton a_second)
{
	return static_cast< MCadMouseButton >( static_cast< int >( a_first ) & static_cast< int >( a_second ) );
}

struct MCadMouseEvent
{
	bool m_doubleClick;			/*!< flag double click*/
	int m_posX;					/*!< position in pixel in widget */
	int m_posY;					/*!< position in pixel in widget */	
	glm::vec2 m_percentPos;		/*!< position in percentage of screen [0,1]*/
	glm::dvec2 m_projectedPos;	/*!< position in projection plane*/
	glm::dvec3 m_pos3D;			/*!< position in world*/
	MCadMouseButton m_buttons;	/*!< mouse buttons*/
};