#pragma once
/***********************************************
* @headerfile MCadFormulaEvaluator.h
* @date 15 / 10 / 2023
* @author Roomain
************************************************/
#include<unordered_map>
#include "MCadValue.h"
#include "MCadTreeNode.h"
#include "MCadFormulaOperatorNode.h"
#include "MCad_Formula_globals.h"
#include "MCadFormulaException.h"
#include "MCadFormulaRegEx.h"


#pragma warning(push)
#pragma warning(disable : 4251)

class MCadFormulaDatabase;

/*@brief used to parse and evaluate formula*/
class MCAD_FORMULA_EXPORT MCadFormulaEvaluator
{
private:
	struct FormulaData
	{
		int m_formulaParsingLocation;					/*!< current location in formula*/
		int m_currentPriorityOffset;					/*!< priority offset due to parenthesis*/
		MCadFormulaValueNodePtr m_lastVariable;			/*!< last parsed variable node*/
		IMCadFormulaNodePtr m_lastOperator;				/*!< last parsed operator node*/
		IMCadFormulaNodePtr m_formulaRootNode;			/*!< formula root node*/
	};

	char m_decimalSeparator = '.';					/*!< decimal separator*/
	char m_valueSeparator = ',';					/*!< value separator for vector*/
	VRegExReactor<FormulaData&> m_regexReact;		/*!< action per regular expression*/
	static constexpr int PRIORITY_OFFSET = 10;		/*!< priority offset for parenthesis*/

	// operator token
	static constexpr char Token_Space = ' ';
	static constexpr char Token_IncPriority = '(';
	static constexpr char Token_DecPriority = ')';
	static constexpr char Token_Op_Add = '+';
	static constexpr char Token_Op_Minus = '-';
	static constexpr char Token_Op_Mult = '*';
	static constexpr char Token_Op_Div = '/';
	static constexpr char Token_Op_Modul = '%';


	void processDouble(const std::string_view& a_value, FormulaData& a_formulaData)const;
	void processInt(const std::string_view& a_value, FormulaData& a_formulaData)const;
	void processVariable(const std::string_view& a_value, FormulaData& a_formulaData)const;

	template<int Size>
	void processVector(const std::string_view& a_formula, FormulaData& a_formulaData)const
	{
		if ( !a_formulaData.m_lastVariable )
		{
			a_formulaData.m_formulaParsingLocation += static_cast< int >( a_formula.size() ) - 1;
			a_formulaData.m_lastVariable = std::make_shared<MCadFormulaValueNode>(getVector<Size>(a_formula));

			if ( a_formulaData.m_lastOperator )
				a_formulaData.m_lastOperator->appendChild(a_formulaData.m_lastVariable);
		}
		else
		{
			throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_MissingOperator,
				std::source_location::current( ), a_formulaData.m_formulaParsingLocation);
		}
	}


	template<int Size>
	void processRelativeVector(const std::string_view& a_formula, FormulaData& a_formulaData)const
	{
		if ( !a_formulaData.m_lastVariable )
		{
			a_formulaData.m_formulaParsingLocation += static_cast< int >( a_formula.size( ) ) - 1;
			a_formulaData.m_lastVariable = std::make_shared<MCadFormulaValueNode>(getRelative<Size>(a_formula));

			if ( a_formulaData.m_lastOperator )
				a_formulaData.m_lastOperator->appendChild(a_formulaData.m_lastVariable);
		}
		else
		{
			throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_MissingOperator,
				std::source_location::current( ), a_formulaData.m_formulaParsingLocation);
		}
	}
	//-----------------------------------------------------------------------------------------


	template<int Size>
	bool checkVector(const std::string& a_formula, FormulaData& a_formulaData)const
	{
		std::regex regularExp;
		switch ( Size )
		{
		case 2:
			regularExp = MCadConfiguration::Instance().VEC2_REGEX;
			break;
		case 3:
			regularExp = MCadConfiguration::Instance( ).VEC3_REGEX;
			break;
		case 4:
			regularExp = MCadConfiguration::Instance( ).VEC4_REGEX;
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
			a_formulaData.m_formulaParsingLocation += static_cast< int >( match.str( ).size( ) ) - 1;
			a_formulaData.m_lastVariable = std::make_shared<MCadFormulaValueNode>(getVector<Size>(match.str( ), m_decimalSeparator, m_valueSeparator));

			if ( a_formulaData.m_lastOperator )
				a_formulaData.m_lastOperator->appendChild(a_formulaData.m_lastVariable);
		}
		else
		{
			throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_MissingOperator,
				std::source_location::current( ), a_formulaData.m_formulaParsingLocation);
		}
		return bRet;
	}

	template<OperatorType Type>
	static void createOperatorNode(FormulaData& a_data)
	{
		if ( isUnary<Type>( ) && a_data.m_lastVariable && ( Type != OperatorType::Op_Minus ) )
		{
			throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_IllFormed,
			std::source_location::current( ), a_data.m_formulaParsingLocation);
		}

		auto pOperator = std::make_shared< MCadFormulaOperatorNode<Type>>(a_data.m_currentPriorityOffset,
				a_data.m_formulaParsingLocation);

		if ( !a_data.m_formulaRootNode )
		{
			// first node
			a_data.m_formulaRootNode = pOperator;

			if ( a_data.m_lastVariable )
				pOperator->appendChild(a_data.m_lastVariable);
		}
		else if ( a_data.m_lastOperator )
		{
			// find higher operator
			const int priority = pOperator->priority( );
			
			MCadFormulaNodeTransition transitionPriority;
			if ( a_data.m_lastOperator->priority( ) >= priority )
			{
				transitionPriority = findTransition(a_data.m_lastOperator,
					[ priority ] (const IMCadFormulaNodePtr& a_node)
					{
							return a_node->priority( ) >= priority;
					});
			}

			if ( transitionPriority.m_child )
			{
				pOperator->appendChild(transitionPriority.m_child);
				if ( transitionPriority.m_parent )
				{
					transitionPriority.m_parent->appendChild(pOperator);
				}
				else
				{
					a_data.m_formulaRootNode = pOperator;
				}
			}
			else
			{
				pOperator->appendChild(a_data.m_lastVariable);
				// last operator has alread higher priority
				a_data.m_lastOperator->appendChild(pOperator);
			}
		}
		else
		{
			throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_ParseError,
			std::source_location::current( ), a_data.m_formulaParsingLocation);
		}
		a_data.m_lastOperator = pOperator;
		a_data.m_lastVariable.reset( );
	}

	void parseFormula(const std::string_view& a_formula, FormulaData& a_data)const;

public:
	MCadFormulaEvaluator( );
	virtual ~MCadFormulaEvaluator( ) = default;
	[[nodiscard]] MCadValue evaluate(const std::string_view& a_formula)const;
};


#pragma warning(pop)