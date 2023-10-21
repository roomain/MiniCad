#include "pch.h"
#include "MCadFormulaEvaluator.h"

char MCadFormulaEvaluator::m_decimalSeparator = '.';
char MCadFormulaEvaluator::m_valueSeparator = ',';
MCadFormulaRegEx MCadFormulaEvaluator::m_parser;

bool MCadFormulaEvaluator::checkDouble(const std::string& a_formula, FormulaData& a_formulaData)
{
	std::smatch match;
	bool bRet = std::regex_search(a_formula, match, m_parser.m_doubleRegex);
	if ( bRet )
	{
		// check if last token is not a variable
		if ( !a_formulaData.m_lastVariable )
		{
			a_formulaData.m_formulaParsingLocation += static_cast< int >( match.str( ).size( ) ) - 1;
			a_formulaData.m_lastVariable = std::make_shared<MCadFormulaValueNode>(getDouble(match.str( ), m_decimalSeparator));

			if ( a_formulaData.m_lastOperator )
				a_formulaData.m_lastOperator->appendChild(a_formulaData.m_lastVariable);
		}
		else
		{
			throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_MissingOperator,
				std::source_location::current( ), a_formulaData.m_formulaParsingLocation);
		}
	}
	return bRet;
}

bool MCadFormulaEvaluator::checkInt(const std::string& a_formula, FormulaData& a_formulaData)
{
	std::smatch match;
	bool bRet = std::regex_search(a_formula, match, m_parser.m_intRegex);
	if ( bRet )
	{
		// check if last token is not a variable
		if ( !a_formulaData.m_lastVariable )
		{
			a_formulaData.m_formulaParsingLocation += static_cast< int >( match.str( ).size( ) ) - 1;
			a_formulaData.m_lastVariable = std::make_shared<MCadFormulaValueNode>(std::atoi(match.str().c_str()));

			if ( a_formulaData.m_lastOperator )
				a_formulaData.m_lastOperator->appendChild(a_formulaData.m_lastVariable);
		}
		else
		{
			throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_MissingOperator,
				std::source_location::current( ), a_formulaData.m_formulaParsingLocation);
		}
	}
	return bRet;
}

bool MCadFormulaEvaluator::checkVariable(const std::string& a_formula, const MCadVariableDatabase& a_database, FormulaData& a_formulaData)
{
	std::smatch match;
	bool bRet = std::regex_search(a_formula, match, m_parser.m_variableRegex);
	if ( bRet )
	{
		// check if last token is not a variable
		if ( !a_formulaData.m_lastVariable )
		{
			auto iter = a_database.find(match.str( ));
			if ( iter == a_database.end() )
			{
				throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_UnknownVariable,
				std::source_location::current( ), a_formulaData.m_formulaParsingLocation);
			}
			else
			{
				a_formulaData.m_formulaParsingLocation += static_cast< int >( match.str( ).size( ) ) - 1;
				a_formulaData.m_lastVariable = std::make_shared<MCadFormulaValueNode>(iter->second);
			}
		}
		else
		{
			throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_MissingOperator,
				std::source_location::current( ), a_formulaData.m_formulaParsingLocation);
		}
	}
	return bRet;
}

void MCadFormulaEvaluator::parseFormula(const std::string_view& a_formula, FormulaData& a_data)
{
	const int formulaLenght = static_cast<int>(a_formula.size());
	a_data.m_currentPriorityOffset = 0;
	a_data.m_formulaParsingLocation = 0;

	VRegExReactor parser;

	while ( a_data.m_formulaParsingLocation < formulaLenght )
	{
		bool bAllowInvert = true; // allow negative value

		// check simple operators
		switch ( a_formula [ a_data.m_formulaParsingLocation ] )
		{
		case Token_Space:
			break;

		case Token_IncPriority:
			a_data.m_currentPriorityOffset++;
			a_data.m_lastVariable.reset( );// to forbid operator just next
			break;

		case Token_DecPriority:
			a_data.m_currentPriorityOffset--;
			bAllowInvert = false;
			break;

		case Token_Op_Add:
			createOperatorNode<OperatorType::Op_Add>(a_data);
			break;

		case Token_Op_Minus:
			if ( bAllowInvert )
			{
				const std::string_view subFormula = a_formula.substr(a_data.m_formulaParsingLocation,
					static_cast< size_t >( formulaLenght - a_data.m_formulaParsingLocation ));
				//
			}
			else if ( a_data.m_lastVariable || a_data.m_lastOperator )
			{
				createOperatorNode<OperatorType::Op_Minus>(a_data);
			}
			else
			{
				// todo
				throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_IllFormed,
				std::source_location::current( ), a_data.m_formulaParsingLocation);
			}
			break;

		case Token_Op_Mult:
			createOperatorNode<OperatorType::Op_Mult>(a_data);
			break;

		case Token_Op_Div:
			createOperatorNode<OperatorType::Op_Div>(a_data);
			break;

		case Token_Op_Modul:
			createOperatorNode<OperatorType::Op_Modul>(a_data);
			break;

		default:
			break;
		}


		++a_data.m_formulaParsingLocation;
	}
}