#pragma once
/***********************************************
* @headerfile MCadFormulaException.h
* @date 14 / 10 / 2023
* @author Roomain
************************************************/
#include <exception>
#include <string>
#include "MCadException.h"
#include "MCadTypeToString.h"
#include "MCad_Formula_globals.h"

#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)

/*@brief Special exception for Formula*/
class MCAD_FORMULA_EXPORT MCadFormulaException : public MCadException
{
public:
	enum class ExceptType : int
	{
#define FORMULA_EXCEPT(Type, Message) Type,
#include "FormulaException_macro.h"
#undef FORMULA_EXCEPT
		Except_Unknown
	};

	MCadFormulaException( ) = delete;
	MCadFormulaException(ExceptType a_Type, const std::source_location& a_loc, const int a_location);

	template<typename ...Args>
	MCadFormulaException(ExceptType a_Type, const std::source_location& a_loc, const int a_location, const Args&&... a_arg):
		MCadException(a_loc, ""), m_formulaLocation{ a_location }, m_exceptType { a_Type	}
	{
		m_extra += " " + printTypes(a_arg...);
		m_extra = m_extra.substr(0, m_extra.size( ) - 1);
	}
	virtual ~MCadFormulaException( ) = default;
	[[nodiscard]] int formulaLocation( )const noexcept { return m_formulaLocation; }
	[[nodiscard]] ExceptType type( )const noexcept { return m_exceptType; }
	[[nodiscard]] std::string message( )const noexcept override;
	[[deprecated]] const char* what( )const override;

private:
	int m_formulaLocation;			/*!< location in formula*/
	ExceptType m_exceptType;		/*!< exception type (determine the error message)*/
};

#pragma warning(pop)
