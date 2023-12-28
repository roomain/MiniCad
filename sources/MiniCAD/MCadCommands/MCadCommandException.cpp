#include "pch.h"
#include "MCadCommandException.h"

MCadCommandException::MCadCommandException(MCadCommandException::ExceptType a_type, const std::source_location& a_loc) :
	MCadException(a_loc), m_exceptType{ a_type }
{
	//
}

std::string MCadCommandException::message( )const noexcept
{
	std::string message;
	switch ( m_exceptType )
	{
#define CMD_EXCEPT(ExType, Message)\
	case ExceptType::ExType: \
		message = #Message;\
		break;

#include "CommandException_macro.h"

#undef CMD_EXCEPT
	default:
		message = "Unknown";

	}

	return message;
}

const char* MCadCommandException::what( )const
{
	return message( ).c_str( );
}