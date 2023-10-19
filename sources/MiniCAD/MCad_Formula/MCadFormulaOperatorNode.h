#pragma once

/***********************************************
* @headerfile MCadFormulaOperatorNode.h
* @date 15 / 10 / 2023
* @author Roomain
************************************************/
#include <memory>
#include <vector>
#include <limits>
#include "MCadValue.h"
#include "MCadTreeNode.h"
#include "MCadFormulaOperatorNode.h"
#include "MCadArithmeticOperators.h"
#include "MCadTrigonometricOperators.h"
#include "MCadVArithmeticOperators.h"


enum class OperatorType
{
	Op_Add = 0,			/*!< operator +*/
	Op_Minus,			/*!< operator -*/
	Op_Mult,			/*!< operator **/
	Op_Div,				/*!< operator /*/
	Op_EuclidDiv,		/*!< operator div*/
	Op_Modul,			/*!< operator %*/
	Op_Cross,			/*!< operator cross*/
	Op_Norm,			/*!< operator norm*/
	Op_Dot,				/*!< operator dot*/
	Op_Cos,				/*!< operator cos*/
	Op_Sin,				/*!< operator sin*/
	Op_Tan,				/*!< operator tan*/
	Op_Acos,			/*!< operator acos*/
	Op_Asin,			/*!< operator asin*/
	Op_Atan,			/*!< operator atan*/
	Op_Function			/*!< for advanded use (TODO)*/
};

class IMCadFormulaNode : public MCadTreeNode
{
private:
	int m_nodePriority;	/*!< operator priority*/

public:
	IMCadFormulaNode() = delete;
	IMCadFormulaNode(const int a_priority) : m_nodePriority{ a_priority } {}
	[[nodiscard]] int priority()const { return m_nodePriority; }
	virtual [[nodiscard]] MCadValue compute()const = 0;
};

using IMCadFormulaNodePtr = std::shared_ptr<IMCadFormulaNode>;

template<OperatorType Type>
class MCadFormulaOperatorNode : public IMCadFormulaNode
{
private:
	template<typename Operator>
	[[nodiscard]] static MCadValue do_compute(const int a_formulaIndex, const MCadValue& a_value)
	{
		static Operator sOperator;
		sOperator.m_position = a_formulaIndex;
		return std::visit(sOperator, a_value);
	}

	template<typename Operator>
	[[nodiscard]] static MCadValue do_compute(const int a_formulaIndex, const MCadValue& a_first, const MCadValue& a_second)
	{
		static Operator sOperator;
		sOperator.m_position = a_formulaIndex;
		return std::visit(sOperator, a_first, a_second);
	}

	int m_formulaIndex;

public:
	MCadFormulaOperatorNode( ) = delete;
	MCadFormulaOperatorNode(const int a_priority, const int a_formulaIndex) : 
		IMCadFormulaOperatorNode(a_priority),
		m_formulaIndex{ a_formulaIndex }
	{
		//
	}

	[[nodiscard]] bool isUnary( )const noexcept
	{
		switch ( Type )
		{
		case OperatorType::Op_Minus:
		case OperatorType::Op_Norm:
		case OperatorType::Op_Cos:
		case OperatorType::Op_Sin:
		case OperatorType::Op_Tan:
		case OperatorType::Op_Acos:
		case OperatorType::Op_Asin:
		case OperatorType::Op_Atan:
			return true;

		default:
			return false
		}
		return false;
	}

	[[nodiscard]] MCadValue compute()const final
	{
		switch ( childCount() )
		{
		case 1:
			return compute(m_formulaIndex, std::static_pointer_cast<IMCadFormulaOperatorNode >(at(0))->compute());
		case 2:
			return compute(m_formulaIndex, std::static_pointer_cast<IMCadFormulaOperatorNode>(at(0))->compute(),
				std::static_pointer_cast<IMCadFormulaOperatorNode>(at(1))->compute());
		default:
			throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_WrongOperandCount, std::source_location::current( ), m_formulaIndex);
		}
	}

	[[nodiscard]] MCadValue compute(const int a_formulaIndex, const MCadValue& a_value)
	{
		switch ( Type )
		{
		case OperatorType::Op_Minus:
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

	[[nodiscard]] MCadValue compute(const int a_formulaIndex, const MCadValue& a_first, const MCadValue& a_second)
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

template<OperatorType Type>
using MCadFormulaOperatorNodePtr = std::shared_ptr<MCadFormulaOperatorNode<Type>>;


class MCadFormulaValueNode : public IMCadFormulaNode
{
private:
	MCadValue m_value;

public:
	MCadFormulaValueNode(const MCadValue& a_value) : IMCadFormulaNode(std::numeric_limits<int>::max()), m_value{a_value} {}
	MCadFormulaValueNode(const MCadValue&& a_value) : IMCadFormulaNode(std::numeric_limits<int>::max( )), m_value{ a_value } {}
	
	[[nodiscard]] MCadValue compute()const
	{
		return m_value;
	}
};

using MCadFormulaValueNodePtr = std::shared_ptr<MCadFormulaValueNode>;