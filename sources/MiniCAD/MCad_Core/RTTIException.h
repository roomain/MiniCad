#pragma once
/***********************************************
* @headerfile RTTIException.h
* @date 16 / 07 / 2023
* @author Roomain
************************************************/
#include <exception>
#include <string>
#include "MCad_Core_globals.h"

#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)
/*@brief Special exception for RTTI*/
class MCAD_CORE_EXPORT RTTIException : public std::exception
{
public:
	enum class ExceptType : int
	{
#define RTTI_EXCEPTION(Type, Message) Type,
#include "RTTIException_macro.h"
#undef RTTI_EXCEPTION
		Except_Unknown
	};

	explicit RTTIException(ExceptType a_Type, std::string_view a_extra = "");
	RTTIException() = delete;
	virtual ~RTTIException() = default;
	[[nodiscard]] ExceptType type()const noexcept;
	[[nodiscard]] std::string message()const noexcept;
	[[deprecated]] const char* what()const override;

private:
	ExceptType m_exceptType;		/*!< exception type (determine the error message)*/
	std::string	m_extra;			/*!< extra message*/
};

#pragma warning(pop)