#include "pch.h"
#include "MCadResultException.h"

MCadResultException::MCadResultException(const std::source_location& a_loc,
	const std::string_view& a_extra) : MCadException(a_loc, a_extra) {}

std::string MCadResultException::message( )const noexcept
{
	return "Invalid result";
}
