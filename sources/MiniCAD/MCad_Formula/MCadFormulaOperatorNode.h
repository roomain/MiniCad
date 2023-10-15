#pragma once

/***********************************************
* @headerfile MCadFormulaOperatorNode.h
* @date 15 / 10 / 2023
* @author Roomain
************************************************/
#include "MCadValue.h"
#include "MCadFormulaOperatorNode.h"
#include "MCadArithmeticOperators.h"
#include "MCadTrigonometricOperators.h"
#include "MCadVArithmeticOperators.h"


enum class OperatorType
{
	Op_Add = 0,
	Op_Minus,
	Op_Mult,
	Op_Div,
	Op_EuclidDiv,
	Op_Modul,
	Op_Cross,
	Op_Norm,
	Op_Dot,
	Op_Rev,
	Op_Cos,
	Op_Sin,
	Op_Tan,
	Op_Acos,
	Op_Asin,
	Op_Atan,
};

template<OperatorType Type>
class MCadFormulaOperatorNode
{

private:
	template<typename Operator>
	static MCadValue do_compute(const int a_formulaIndex, const MCadValue& a_value)
	{
		static Operator sOperator;
		sOperator.m_position = a_formulaIndex;
		return std::visit(sOperator, a_value);
	}

	template<typename Operator>
	static MCadValue do_compute(const int a_formulaIndex, const MCadValue& a_first, const MCadValue& a_second)
	{
		static Operator sOperator;
		sOperator.m_position = a_formulaIndex;
		return std::visit(sOperator, a_first, a_second);
	}

public:
	MCadValue compute(const int a_formulaIndex, const MCadValue& a_value)
	{
		switch ( Type )
		{
		case OperatorType::Op_Minus:
		case OperatorType::Op_Rev:
			return do_compute<UnaryMinusOperator>(a_formulaIndex, a_value);
		case OperatorType::Op_Norm:
			return do_compute<NormalOperator>(a_formulaIndex, a_value);
		case OperatorType::Op_Cos:
			return do_compute<CosOperator>(a_formulaIndex, a_value);
		case OperatorType::Op_Sin:
			return do_compute<SinOperator>(a_formulaIndex, a_value);
		case OperatorType::Op_Tan:
			return do_compute<TanOperator>(a_formulaIndex, a_value);
		case OperatorType::Op_Acos:
			return do_compute<ACosOperator>(a_formulaIndex, a_value);
		case OperatorType::Op_Asin:
			return do_compute<ASinOperator>(a_formulaIndex, a_value);
		case OperatorType::Op_Atan:
			return do_compute<ATanOperator>(a_formulaIndex, a_value);
			
		default:
			throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_Incompatible_Op, std::source_location::current( ), a_formulaIndex);
		}
	}

	MCadValue compute(const int a_formulaIndex, const MCadValue& a_first, const MCadValue& a_second)
	{
		switch ( Type )
		{
		case OperatorType::Op_Add:
			return do_compute<AddOperator>(a_formulaIndex, a_first, a_second);
		case OperatorType::Op_Minus:
			return do_compute<MinusOperator>(a_formulaIndex, a_first, a_second);
		case OperatorType::Op_Mult:
			return do_compute<MultOperator>(a_formulaIndex, a_first, a_second);
		case OperatorType::Op_Div:
			return do_compute<DivideOperator>(a_formulaIndex, a_first, a_second);
		case OperatorType::Op_EuclidDiv:
			return do_compute<EuclidianDivideOperator>(a_formulaIndex, a_first, a_second);
		case OperatorType::Op_Modul:
			return do_compute<ModuleOperator>(a_formulaIndex, a_first, a_second);
		case OperatorType::Op_Cross:
			return do_compute<CrossOperator>(a_formulaIndex, a_first, a_second);
		case OperatorType::Op_Dot:
			return do_compute<DotOperator>(a_formulaIndex, a_first, a_second);

		default:
			throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_Incompatible_Op, std::source_location::current( ), a_formulaIndex);
		}
	}
};
