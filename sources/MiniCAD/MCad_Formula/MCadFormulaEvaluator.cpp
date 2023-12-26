#include "pch.h"
#include "MCadFormulaEvaluator.h"
#include "MCadFormulaDatabase.h"


MCadFormulaEvaluator::MCadFormulaEvaluator( )
{
	using namespace std::placeholders;
	m_regexReact.emplace_back(MCadConfiguration::Instance( ).DOUBLE_REGEX.value(), std::bind_front(&MCadFormulaEvaluator::processDouble, this));
	m_regexReact.emplace_back(MCadConfiguration::Instance( ).INT_REGEX.value( ), std::bind_front(&MCadFormulaEvaluator::processInt, this));
	m_regexReact.emplace_back(MCadConfiguration::Instance( ).VEC2_REGEX.value( ), std::bind_front(&MCadFormulaEvaluator::processVector<2>, this));
	m_regexReact.emplace_back(MCadConfiguration::Instance( ).VEC3_REGEX.value( ), std::bind_front(&MCadFormulaEvaluator::processVector<3>, this));
	m_regexReact.emplace_back(MCadConfiguration::Instance( ).VEC4_REGEX.value( ), std::bind_front(&MCadFormulaEvaluator::processVector<4>, this));


	m_regexReact.emplace_back(MCadConfiguration::Instance( ).REL_2D_CARTESIAN_REGEX.value( ), std::bind_front(&MCadFormulaEvaluator::processRelativeVector<2>, this));
	m_regexReact.emplace_back(MCadConfiguration::Instance( ).REL_3D_CARTESIAN_REGEX.value( ), std::bind_front(&MCadFormulaEvaluator::processRelativeVector<3>, this));
	m_regexReact.emplace_back(MCadConfiguration::Instance( ).COS_REGEX.value( ), [] (const std::string_view&, FormulaData& a_formula)
		{
			MCadFormulaEvaluator::createOperatorNode<OperatorType::Op_Cos>(a_formula);
			a_formula.m_formulaParsingLocation += static_cast< int >( std::string_view("cos(").length( ));
			a_formula.m_currentPriorityOffset += PRIORITY_OFFSET;
		});
	m_regexReact.emplace_back(MCadConfiguration::Instance( ).SIN_REGEX.value( ), [] (const std::string_view&, FormulaData& a_formula)
		{
			MCadFormulaEvaluator::createOperatorNode<OperatorType::Op_Sin>(a_formula);
			a_formula.m_formulaParsingLocation += static_cast< int >( std::string_view("sin(").length( ));
			a_formula.m_currentPriorityOffset += PRIORITY_OFFSET;
		});
	m_regexReact.emplace_back(MCadConfiguration::Instance( ).TAN_REGEX.value( ), [] (const std::string_view&, FormulaData& a_formula)
		{
			MCadFormulaEvaluator::createOperatorNode<OperatorType::Op_Tan>(a_formula);
			a_formula.m_formulaParsingLocation += static_cast< int >( std::string_view("tan(").length( ));
			a_formula.m_currentPriorityOffset += PRIORITY_OFFSET;
		}
	);
	m_regexReact.emplace_back(MCadConfiguration::Instance( ).ACOS_REGEX.value( ), [] (const std::string_view&, FormulaData& a_formula)
		{
			MCadFormulaEvaluator::createOperatorNode<OperatorType::Op_Acos>(a_formula);
			a_formula.m_formulaParsingLocation += static_cast< int >( std::string_view("acos(").length( ));
			a_formula.m_currentPriorityOffset += PRIORITY_OFFSET;
		}
	);
	m_regexReact.emplace_back(MCadConfiguration::Instance( ).ASIN_REGEX.value( ), [] (const std::string_view&, FormulaData& a_formula)
		{
			MCadFormulaEvaluator::createOperatorNode<OperatorType::Op_Asin>(a_formula);
			a_formula.m_formulaParsingLocation += static_cast< int >( std::string_view("asin(").length( ));
			a_formula.m_currentPriorityOffset += PRIORITY_OFFSET;
		}
	);
	m_regexReact.emplace_back(MCadConfiguration::Instance( ).ATAN_REGEX.value( ), [] (const std::string_view&, FormulaData& a_formula)
		{
			MCadFormulaEvaluator::createOperatorNode<OperatorType::Op_Atan>(a_formula);
			a_formula.m_formulaParsingLocation += static_cast<int>(std::string_view("atan(").length( ));
			a_formula.m_currentPriorityOffset += PRIORITY_OFFSET;
		}
	);
	// TODO variable + function
	m_regexReact.emplace_back(MCadConfiguration::Instance( ).VAR_REGEX.value(), std::bind_front(&MCadFormulaEvaluator::processVariable, this));

}

MCadValue MCadFormulaEvaluator::evaluate(const std::string_view& a_formula)const
{
	FormulaData formulaData;
	parseFormula(a_formula, formulaData);
	if(formulaData.m_formulaRootNode )
		return formulaData.m_formulaRootNode->compute( );
	return MCadValue();
}

void MCadFormulaEvaluator::processDouble(const std::string_view& a_value, FormulaData& a_formulaData)const
{
	// check if last token is not a variable
	if ( !a_formulaData.m_lastVariable )
	{
		a_formulaData.m_formulaParsingLocation += static_cast< int >( a_value.size( ) ) - 1;
		a_formulaData.m_lastVariable = std::make_shared<MCadFormulaValueNode>(getDouble(a_value));

		if ( a_formulaData.m_lastOperator )
			a_formulaData.m_lastOperator->appendChild(a_formulaData.m_lastVariable);
	}
	else
	{
		throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_MissingOperator,
			std::source_location::current( ), a_formulaData.m_formulaParsingLocation);
	}
}

void MCadFormulaEvaluator::processInt(const std::string_view& a_value, FormulaData& a_formulaData)const
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

void MCadFormulaEvaluator::processVariable(const std::string_view& a_value, FormulaData& a_formulaData)const
{
	// check if last token is not a variable
	if ( !a_formulaData.m_lastVariable )
	{
		std::string varName(a_value);
		if ( MCadFormulaDatabase::Instance().hasVariable(varName) )
		{
			throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_UnknownVariable,
			std::source_location::current( ), a_formulaData.m_formulaParsingLocation);
		}
		else
		{
			a_formulaData.m_formulaParsingLocation += static_cast< int >( a_value.size( ) ) - 1;
			a_formulaData.m_lastVariable = std::make_shared<MCadFormulaValueNode>(MCadFormulaDatabase::Instance().getVariableValue(varName));
		}
	}
	else
	{
		throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_MissingOperator,
			std::source_location::current( ), a_formulaData.m_formulaParsingLocation);
	}
}

void MCadFormulaEvaluator::parseFormula(const std::string_view& a_formula, FormulaData& a_data)const
{
	const auto formulaLenght = static_cast<int>(a_formula.size());
	a_data.m_currentPriorityOffset = 0;
	a_data.m_formulaParsingLocation = 0;

	while ( a_data.m_formulaParsingLocation < formulaLenght )
	{

		int matchLen = 1;
		// check simple operators
		switch ( a_formula [ a_data.m_formulaParsingLocation ] )
		{
		case Token_Space:
			break;

		case Token_IncPriority:
			a_data.m_currentPriorityOffset+= PRIORITY_OFFSET;
			a_data.m_lastVariable.reset( );// to forbid operator just next
			break;

		case Token_DecPriority:
			a_data.m_currentPriorityOffset-= PRIORITY_OFFSET;
			break;

		case Token_Op_Add:
			createOperatorNode<OperatorType::Op_Add>(a_data);
			break;

		case Token_Op_Minus:
			createOperatorNode<OperatorType::Op_Minus>(a_data);
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
			if ( !parseAndReact(std::string(a_formula.substr(a_data.m_formulaParsingLocation, a_formula.size() - a_data.m_formulaParsingLocation)), m_regexReact, matchLen, a_data) )
			{
				throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_UnknownVariable,
					std::source_location::current( ), a_data.m_formulaParsingLocation);
			}
			break;
		}

		if( matchLen == 0)
			throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_IllFormed,
					std::source_location::current( ), a_data.m_formulaParsingLocation);
		
		a_data.m_formulaParsingLocation += matchLen;
	}

	if( a_data.m_currentPriorityOffset != 0 )
		throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_MissingClose,
				std::source_location::current( ), a_data.m_formulaParsingLocation);
}