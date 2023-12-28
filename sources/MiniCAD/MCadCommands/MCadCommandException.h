#pragma once
/***********************************************
* @headerfile MCadCommandException.h
* @date 14 / 10 / 2023
* @author Roomain
************************************************/
#include <exception>
#include <string>
#include "MCadException.h"
#include "MCad_Command_globals.h"

#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)

/*@brief Special exception for Formula*/
class MCAD_CMD_EXPORT MCadCommandException : public MCadException
{
public:
	enum class ExceptType : int
	{
#define CMD_EXCEPT(Type, Message) Type,
#include "CommandException_macro.h"
#undef CMD_EXCEPT
		Except_Unknown
	};

	MCadCommandException( ) = delete;
	MCadCommandException(ExceptType a_type, const std::source_location& a_loc);
	virtual ~MCadCommandException( ) = default;
	[[nodiscard]] ExceptType type( )const noexcept { return m_exceptType; }
	[[nodiscard]] std::string message( )const noexcept override;
	[[deprecated]] const char* what( )const override;

private:
	ExceptType m_exceptType;		/*!< exception type (determine the error message)*/
};

#pragma warning(pop)
