#pragma once
/***********************************************
* @headerfile MCadTrigonometricOperators.h
* @date 11 / 10 / 2023
* @author Roomain
************************************************/
#include "MCadOperator.h"

struct CosOperator : MCadOperator
{
	//

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw;
	}
};

struct SinOperator : MCadOperator
{
	//

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw;
	}
};

struct TanOperator : MCadOperator
{
	//

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw;
	}
};


struct ACosOperator : MCadOperator
{
	//

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw;
	}
};

struct ASinOperator : MCadOperator
{
	//

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw;
	}
};

struct ATanOperator : MCadOperator
{
	//

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw;
	}
};