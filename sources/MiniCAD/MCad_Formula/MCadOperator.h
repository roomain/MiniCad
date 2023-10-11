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
	unsigned int m_position;	/*!< position in string formula*/
};


struct UnaryLessOperator : MCadOperator
{
	MCadValue operator()(const float a_value)const
	{
		return MCadValue(-a_value);
	}

	MCadValue operator()(const double& a_value)const
	{
		return MCadValue(-a_value);
	}

	MCadValue operator()(const int a_value)const
	{
		return MCadValue(-a_value);
	}

	MCadValue operator()(const glm::dvec2& a_value)const
	{
		//return -a_value;
	}

	MCadValue operator()(const glm::dvec3& a_value)const
	{
		//return -a_value;
	}

	MCadValue operator()(const glm::dvec4& a_value)const
	{
		//return -a_value;
	}

	MCadValue operator()(...)const
	{
		throw;
	}
};

struct CosOperator : MCadOperator
{
	//
	MCadValue operator()(...)const
	{
		throw;
	}
};