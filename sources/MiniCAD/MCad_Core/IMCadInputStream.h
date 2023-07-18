#pragma once

/***********************************************
* @headerfile IMCadInputStream.h
* @date 17 / 07 / 2023
* @author Roomain
************************************************/
#include <string>

/*@brief Base of input stream*/
class IMCadInputStream
{
public:
	virtual IMCadInputStream& setPos(const size_t& offset) = 0;
	virtual IMCadInputStream& shift(const size_t& offset) = 0;
	virtual bool atEnd()const noexcept = 0;
	//-----------------------------------------------------------------
	virtual IMCadInputStream& operator >> (unsigned long long&) = 0;
	virtual IMCadInputStream& operator >> (long long&) = 0;
	virtual IMCadInputStream& operator >> (bool&) = 0;
	virtual IMCadInputStream& operator >> (char&) = 0;
	virtual IMCadInputStream& operator >> (unsigned char&) = 0;
	virtual IMCadInputStream& operator >> (short&) = 0;
	virtual IMCadInputStream& operator >> (unsigned short&) = 0;
	virtual IMCadInputStream& operator >> (unsigned int&) = 0;
	virtual IMCadInputStream& operator >> (int&) = 0;
	virtual IMCadInputStream& operator >> (double&) = 0;
	virtual IMCadInputStream& operator >> (float&) = 0;
	virtual IMCadInputStream& operator >> (std::string&) = 0;
	//virtual IMCadInputStream& operator >> (gp_Pnt&) = 0;
	//virtual IMCadInputStream& operator >> (gp_Vec&) = 0;
	//virtual IMCadInputStream& operator >> (glm::dvec2&) = 0;
	//virtual IMCadInputStream& operator >> (glm::dvec3&) = 0;
	//virtual IMCadInputStream& operator >> (glm::dvec4&) = 0;
	//virtual IMCadInputStream& operator >> (glm::dquat&) = 0;
	//virtual IMCadInputStream& operator >> (glm::dmat4&) = 0;
};