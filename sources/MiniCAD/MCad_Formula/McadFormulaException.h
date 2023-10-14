#pragma once
/***********************************************
* @headerfile MCadFormulaException.h
* @date 14 / 10 / 2023
* @author Roomain
************************************************/
#include <exception>
#include <string>
#include "MCadException.h"
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
	MCadFormulaException(ExceptType a_Type, const std::source_location& a_loc, const std::string_view& a_extra = "");

	template<typename ...Args>
	MCadFormulaException(ExceptType a_Type, const std::source_location& a_loc, const std::string_view& a_extra, const Args&&... a_arg):
		MCadException(a_loc, a_extra), m_exceptType{a_Type}
	{
		// TODO
	}
	virtual ~MCadFormulaException( ) = default;
	[[nodiscard]] ExceptType type( )const noexcept;
	[[nodiscard]] std::string message( )const noexcept override;
	[[deprecated]] const char* what( )const override;

private:
	ExceptType m_exceptType;		/*!< exception type (determine the error message)*/
};

#pragma warning(pop)
