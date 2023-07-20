#pragma once
/***********************************************
* @headerfile IMCadOutputStream.h
* @date 17 / 07 / 2023
* @author Roomain
************************************************/
#include <string>

/*@brief Base of input stream*/
class IMCadOutputStream
{
public:
	virtual IMCadOutputStream& operator << (const unsigned long long&) = 0;
	virtual IMCadOutputStream& operator << (const long long&) = 0;
	virtual IMCadOutputStream& operator << (const bool) = 0;
	virtual IMCadOutputStream& operator << (const char) = 0;
	virtual IMCadOutputStream& operator << (const char*) = 0;
	virtual IMCadOutputStream& operator << (const unsigned char) = 0;
	virtual IMCadOutputStream& operator << (const short) = 0;
	virtual IMCadOutputStream& operator << (const unsigned short) = 0;
	virtual IMCadOutputStream& operator << (const unsigned int) = 0;
	virtual IMCadOutputStream& operator << (const int) = 0;
	virtual IMCadOutputStream& operator << (const double&) = 0;
	virtual IMCadOutputStream& operator << (const float) = 0;
	virtual IMCadOutputStream& operator << (const std::string&) = 0;
	//virtual IMCadOutputStream& operator << (const gp_Pnt&) = 0;
	//virtual IMCadOutputStream& operator << (const gp_Vec&) = 0;
	//virtual IMCadOutputStream& operator << (const glm::dvec2&) = 0;
	//virtual IMCadOutputStream& operator << (const glm::dvec3&) = 0;
	//virtual IMCadOutputStream& operator << (const glm::dvec4&) = 0;
	//virtual IMCadOutputStream& operator << (const glm::dquat&) = 0;
	//virtual IMCadOutputStream& operator << (const glm::dmat4&) = 0;
};