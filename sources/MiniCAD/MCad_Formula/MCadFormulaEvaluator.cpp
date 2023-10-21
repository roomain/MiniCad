#include "pch.h"
#include "MCadFormulaEvaluator.h"


MCadFormulaEvaluator::MCadFormulaEvaluator( )
{
	initialize(m_decimalSeparator, m_valueSeparator, m_parser);
	//m_regexReact.emplace_back(m_parser.m_doubleRegex, [this])
}

void MCadFormulaEvaluator::processDouble(const std::string_view& a_value, FormulaData& a_formulaData)
{
	// check if last token is not a variable
	if ( !a_formulaData.m_lastVariable )
	{
		a_formulaData.m_formulaParsingLocation += static_cast< int >( a_value.size( ) ) - 1;
		a_formulaData.m_lastVariable = std::make_shared<MCadFormulaValueNode>(getDouble(a_value, m_decimalSeparator));

		if ( a_formulaData.m_lastOperator )
			a_formulaData.m_lastOperator->appendChild(a_formulaData.m_lastVariable);
	}
	else
	{
		throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_MissingOperator,
			std::source_location::current( ), a_formulaData.m_formulaParsingLocation);
	}
}

void MCadFormulaEvaluator::processInt(const std::string_view& a_value, FormulaData& a_formulaData)
{
	// check if last token is not a variable
	if ( !a_formulaData.m_lastVariable )
	{
		a_formulaData.m_formulaParsingLocation += static_cast< int >( a_value.size( ) ) - 1;
		a_formulaData.m_lastVariable = std::make_shared<MCadFormulaValueNode>(std::atoi(a_value.data( )));

		if ( a_formulaData.m_lastOperator )
			a_formulaData.m_lastOperator->appendChild(a_formulaData.m_lastVariable);
	}
	else
	{
		throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_MissingOperator,
			std::source_location::current( ), a_formulaData.m_formulaParsingLocation);
	}
}

void MCadFormulaEvaluator::processVariable(const std::string_view& a_value, const MCadVariableDatabase& a_database, FormulaData& a_formulaData)
{
	// check if last token is not a variable
	if ( !a_formulaData.m_lastVariable )
	{
		auto iter = a_database.find(std::string(a_value));
		if ( iter == a_database.end( ) )
		{
			throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_UnknownVariable,
			std::source_location::current( ), a_formulaData.m_formulaParsingLocation);
		}
		else
		{
			a_formulaData.m_formulaParsingLocation += static_cast< int >( a_value.size( ) ) - 1;
			a_formulaData.m_lastVariable = std::make_shared<MCadFormulaValueNode>(iter->second);
		}
	}
	else
	{
		throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_MissingOperator,
			std::source_location::current( ), a_formulaData.m_formulaParsingLocation);
	}
}

void MCadFormulaEvaluator::parseFormula(const std::string_view& a_formula, FormulaData& a_data)
{
	const auto formulaLenght = static_cast<int>(a_formula.size());
	a_data.m_currentPriorityOffset = 0;
	a_data.m_formulaParsingLocation = 0;


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