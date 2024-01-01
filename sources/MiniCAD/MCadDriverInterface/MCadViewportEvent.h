#pragma once
/***********************************************
* @headerfile MCadDriverWindow.h
* @date 01 / 01 / 2024
* @author Roomain
************************************************/
#include <vector>
#include "glm/glm.hpp"

class MCadViewport;


enum class Border
{
	None,
	Top,
	Bottom,
	Left,
	Right
};

struct MCadViewportEvent
{
	Border m_selectedBoder = Border::None;
	glm::fvec2 m_lastPos;							/*!< last position*/
	glm::fvec2 m_movement;							/*!< movement*/
	std::vector<const MCadViewport*> m_exception;	/*!< not considered by event*/
};