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

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw;
	}
};

struct CrossOperator : MCadOperator
{
	//

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw;
	}
};


struct NormalOperator : MCadOperator
{
	//

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw;
	}
};