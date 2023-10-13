#pragma once
/***********************************************
* @headerfile MCadVArithmeticOperators.h
* @date 11 / 10 / 2023
* @author Roomain
************************************************/
#include "MCadOperator.h"


struct DotOperator : MCadOperator
{
	//
	MCadValue operator()(...)const
	{
		throw;
	}
};

struct CrossOperator : MCadOperator
{
	//
	MCadValue operator()(...)const
	{
		throw;
	}
};


struct NormalOperator : MCadOperator
{
	//
	MCadValue operator()(...)const
	{
		throw;
	}
};