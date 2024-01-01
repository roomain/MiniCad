#pragma once
/***********************************************
* @headerfile MCadCoord.h
* @date 26 / 12 / 2023
* @author Roomain
************************************************/
#include "glm/glm.hpp"

/*@brief represents mouse coordinates in different system*/
struct MCadCoord
{
	glm::vec2 m_windowCoords;	/*!< window coordinate*/
	glm::ivec2 m_screenCoords;	/*!< screen coordinate (reverse Y axis from window coordinates)*/
	glm::dvec3 m_worldCoords;	/*!< word coordinates*/
	glm::dvec3 m_localCoords;	/*!< local coordinates*/
};
