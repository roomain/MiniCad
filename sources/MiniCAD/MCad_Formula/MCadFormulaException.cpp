#include "pch.h"
#include <format>
#include "MCadFormulaException.h"

MCadFormulaException::MCadFormulaException(ExceptType a_Type, const std::source_location& a_loc, const int a_location) :
	MCadException(a_loc, ""), m_formulaLocation{a_location}, m_exceptType{a_Type}
{
	//
}

#pragma warning(push)
#pragma warning(disable : 4065)

std::string MCadFormulaException::message( )const noexcept
{
	std::string message;
	switch ( m_exceptType )
	{
#define FORMULA_EXCEPT(ExType, Message)\
	case Type::ExType: \
		message = std::format("{} {}", std::string_view(#Message), m_extra);\
		break;

#include "FormulaException_macro.h"
#undef FORMULA_EXCEPT
	default:
		message = std::format("Unknown error {}", m_extra);

	}

	return message;
}

const char* MCadFormulaException::what( )const
{
	std::string message;
	switch ( m_exceptType )
	{
#define FORMULA_EXCEPT(ExType, Message)\
	case Type::ExType: \
		message = std::format("{} {}", std::string_view(#Message), m_extra);\
		break;

#include "FormulaException_macro.h"
#undef FORMULA_EXCEPT
	default:
		message = std::format("Unknown error {}", m_extra);
	}
	return message.c_str( );
}


#pragma warning(pop)