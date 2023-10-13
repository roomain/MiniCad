#pragma once
/***********************************************
* @headerfile MCadOperator.h
* @date 11 / 10 / 2023
* @author Roomain
************************************************/
#include "MCadValue.h"

template<class... Ts> struct Operator : Ts... { using Ts::operator()...; };


struct MCadOperator
{	
	unsigned int m_position = -1;	/*!< position in string formula*/
};


