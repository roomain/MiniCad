#pragma once

/***********************************************
* @headerfile MCadFormulaOperatorNode.h
* @date 15 / 10 / 2023
* @author Roomain
************************************************/
#include "MCadValue.h"

class MCadFormulaOperatorNode
{
public:
	template<typename Operator>
	static MCadValue compute(const int a_formulaIndex, const MCadValue& a_value)
	{
		static Operator sOperator;
		sOperator.m_position = a_formulaIndex;
		return std::visit(sOperator, a_value);
	}

	template<typename Operator>
	static MCadValue compute(const int a_formulaIndex, const MCadValue& a_first, const MCadValue& a_second)
	{
		static Operator sOperator;
		sOperator.m_position = a_formulaIndex;
		return std::visit(sOperator, a_first, a_second);
	}
};
