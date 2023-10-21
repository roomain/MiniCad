#pragma once
/***********************************************
* @headerfile MCadVArithmeticOperators.h
* @date 11 / 10 / 2023
* @author Roomain
************************************************/
#include "MCadOperator.h"
#include "MCadFormulaException.h"


struct DotOperator : MCadOperator
{
	//

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_Incompatible_type, std::source_location::current(), m_position,  a_values...);
	}
};

struct CrossOperator : MCadOperator
{
	//

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_Incompatible_type, std::source_location::current(), m_position,  a_values...);
	}
};


struct NormalOperator : MCadOperator
{
	//

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_Incompatible_type, std::source_location::current(), m_position,  a_values...);
	}
};