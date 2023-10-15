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
#include "MCad_Formula_globals.h"

using MCadVariableDatabase = std::unordered_map<std::string, MCadValue>;


/*@brief used to parse and evaluate formula*/
class MCAD_FORMULA_EXPORT MCadFormulaEvaluator
{
private:
	static char m_decimalSeparator;		/*!< decimal separator*/
	static char m_valueSeparator;		/*!< value separator for vector*/	
	static MCadFormulaRegEx m_parser;	/*!< regex parsing*/

	enum class OperatorPriority : int
	{
		OP_ADD	 = 1,
		OP_MINUS = 1,
		OP_MULT	 = 2,
		OP_DIV	 = 2,
		OP_CROSS = 2,
		OP_DOT	 = 2,
		OP_REV	 = 3
	};

	struct FormulaData
	{
		size_t m_formulaParsingLocation;	/*!< current location in formula*/
		int m_currentPriorityOffset;		/*!< priority offset due to parenthesis*/

	};


	static bool checkDouble(const std::string_view& a_formula);
	static bool checkInt(const std::string_view& a_formula);
	static bool checkVariable(const std::string_view& a_formula, const MCadVariableDatabase& a_database);

	template<int Size>
	static bool checkVector(const std::string_view& a_formula)
	{
		// TODO
	}

};