#pragma once
/***********************************************
* @headerfile MCadFormulaEvaluator.h
* @date 15 / 10 / 2023
* @author Roomain
************************************************/
#include<unordered_map>
#include "MCadValue.h"
#include "MCadFormulaRegEx.h"
#include "MCadTreeNode.h"
#include "MCadFormulaOperatorNode.h"
#include "MCad_Formula_globals.h"
#include "McadFormulaException.h"

using MCadVariableDatabase = std::unordered_map<std::string, MCadValue>;


/*@brief used to parse and evaluate formula*/
class MCAD_FORMULA_EXPORT MCadFormulaEvaluator
{
protected:
	static char m_decimalSeparator;		/*!< decimal separator*/
	static char m_valueSeparator;		/*!< value separator for vector*/	
	static MCadFormulaRegEx m_parser;	/*!< regex parsing*/

	// operator token
	static constexpr char Token_Space = ' ';
	static constexpr char Token_IncPriority = '(';
	static constexpr char Token_DecPriority = ')';
	static constexpr char Token_Op_Add = '+';
	static constexpr char Token_Op_Minus = '-';
	static constexpr char Token_Op_Mult = '*';
	static constexpr char Token_Op_Div = '/';
	static constexpr char Token_Op_Modul = '%';

	enum class OperatorPriority : int
	{
		OP_ADD	 = 1,	/*!< operator add*/
		OP_MINUS = 1,	/*!< operator minus*/
		OP_MULT	 = 2,	/*!< operator mult*/
		OP_DIV	 = 2,	/*!< operator div (euclidian and normal)*/
		OP_CROSS = 2,	/*!< operator cross prod*/
		OP_DOT	 = 2,	/*!< operator dot prod*/
		OP_REV	 = 3,	/*!< operator reverse */
		OP_FUNCT = 4	/*!< operator function*/
	};

	struct FormulaData
	{
		int m_formulaParsingLocation;					/*!< current location in formula*/
		int m_currentPriorityOffset;					/*!< priority offset due to parenthesis*/
		MCadFormulaValueNodePtr m_lastVariable;			/*!< last parsed variable node*/
		OperatorType m_lastOperatorType;				/*!< last operator type*/
		IMCadFormulaNodePtr m_lastOperator;				/*!< last parsed operator node*/
		IMCadFormulaNodePtr m_formulaRootNode;			/*!< formula root node*/
	};


	static bool checkDouble(const std::string& a_formula, FormulaData& a_formulaData);
	static bool checkInt(const std::string& a_formula, FormulaData& a_formulaData);
	static bool checkVariable(const std::string& a_formula, const MCadVariableDatabase& a_database, FormulaData& a_formulaData);

	template<int Size>
	static bool checkVector(const std::string& a_formula, FormulaData& a_formulaData)
	{
		std::regex regularExp;
		switch ( Size )
		{
		case 2:
			regularExp = m_parser.m_vec2DRegex;
			break;
		case 3:
			regularExp = m_parser.m_vec3DRegex;
			break;
		case 4:
			regularExp = m_parser.m_vec4DRegex;
			break;
		default:
			throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_NotSupported,
				std::source_location::current( ), a_formulaData.m_formulaParsingLocation);
		}

		std::smatch match;
		bool bRet = std::regex_search(a_formula, match, regularExp);

		// check if last token is not a variable
		if ( !a_formulaData.m_lastVariable )
		{
			a_formulaData.m_formulaParsingLocation += static_cast<int>(match.str().size()) - 1;
			a_formulaData.m_lastVariable = std::make_shared<MCadFormulaValueNode>(getVector<Size>(match.str( ), m_decimalSeparator, m_valueSeparator));
		}
		else
		{
			throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_MissingOperator,
				std::source_location::current( ), a_formulaData.m_formulaParsingLocation);
		}
		return bRet;
	}

	static void parseFormula(const std::string_view& a_formula, FormulaData& a_data);

	template<OperatorType Type>
	void createOperatorNode(FormulaData& a_data)
	{
		auto pOperator = std::make_shared< MCadFormulaOperatorNode<Type>>(a_data.m_currentPriorityOffset,
				a_data.m_formulaParsingLocation);

		if ( pOperator->isUnary( ) && a_data.m_lastVariable && (Type != OperatorType::Op_Minus) )
		{
			throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_IllFormed,
			std::source_location::current( ), a_data.m_formulaParsingLocation);
		}


		if ( !a_data.m_formulaRootNode)
		{
			// first node
			a_data.m_formulaRootNode = pOperator;

			if ( a_data.m_lastVariable )
				pOperator->appendChild(a_data.m_lastVariable);
		}
		else
		{
			//
		}

		a_data.m_lastVariable.reset( );
	}

};