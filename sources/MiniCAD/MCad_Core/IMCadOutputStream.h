#pragma once
/***********************************************
* @headerfile IMCadOutputStream.h
* @date 17 / 07 / 2023
* @author Roomain
************************************************/
#include <string>
#include <memory>

/*@brief Base of input stream*/
class IMCadOutputStream
{
public:
	virtual const size_t offset()const = 0;
	virtual IMCadOutputStream& operator << (const unsigned long long&) = 0;
	virtual IMCadOutputStream& operator << (const long long&) = 0;
	virtual IMCadOutputStream& operator << (const bool) = 0;
	virtual IMCadOutputStream& operator << (const char) = 0;
	virtual IMCadOutputStream& operator << (const unsigned char) = 0;
	virtual IMCadOutputStream& operator << (const short) = 0;
	virtual IMCadOutputStream& operator << (const unsigned short) = 0;
	virtual IMCadOutputStream& operator << (const unsigned int) = 0;
	virtual IMCadOutputStream& operator << (const int) = 0;
	virtual IMCadOutputStream& operator << (const double&) = 0;
	virtual IMCadOutputStream& operator << (const float) = 0;
	virtual IMCadOutputStream& operator << (const std::string&) = 0;
	virtual IMCadOutputStream& operator << (const std::wstring&) = 0;
};
