#pragma once
/***********************************************
* @headerfile MCadTrigonometricOperators.h
* @date 11 / 10 / 2023
* @author Roomain
************************************************/
#include "MCadOperator.h"
#include "McadFormulaException.h"

struct CosOperator : MCadOperator
{
	//

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw McadFormulaException(MCadFormulaException::ExceptType::Formula_except_Incompatible_type, std::source_location::current(), m_position,  a_values...);
	}
};

struct SinOperator : MCadOperator
{
	//

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw McadFormulaException(MCadFormulaException::ExceptType::Formula_except_Incompatible_type, std::source_location::current(), m_position,  a_values...);
	}
};

struct TanOperator : MCadOperator
{
	//

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw McadFormulaException(MCadFormulaException::ExceptType::Formula_except_Incompatible_type, std::source_location::current(), m_position,  a_values...);
	}
};


struct ACosOperator : MCadOperator
{
	//

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw McadFormulaException(MCadFormulaException::ExceptType::Formula_except_Incompatible_type, std::source_location::current(), m_position,  a_values...);
	}
};

struct ASinOperator : MCadOperator
{
	//

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw McadFormulaException(MCadFormulaException::ExceptType::Formula_except_Incompatible_type, std::source_location::current(), m_position,  a_values...);
	}
};

struct ATanOperator : MCadOperator
{
	//

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw McadFormulaException(MCadFormulaException::ExceptType::Formula_except_Incompatible_type, std::source_location::current(), m_position,  a_values...);
	}
};