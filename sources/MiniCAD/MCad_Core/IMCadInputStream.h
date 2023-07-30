#pragma once

/***********************************************
* @headerfile IMCadInputStream.h
* @date 17 / 07 / 2023
* @author Roomain
************************************************/
#include <string>
#include <memory>

/*@brief Base of input stream*/
class IMCadInputStream
{
public:
	virtual IMCadInputStream& setPos(const size_t& a_offset) = 0;
	virtual IMCadInputStream& shift(const size_t& a_offset) = 0;
	virtual void atStart() = 0;
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
	virtual IMCadInputStream& operator >> (std::wstring&) = 0;
};

using IMCadInputStreamPtr = std::shared_ptr<IMCadInputStream>;