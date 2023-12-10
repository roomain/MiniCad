#pragma once
/***********************************************
* @headerfile MCadCmdArguments.h
* @date 03 / 12 / 2023
* @author Roomain
************************************************/
#include "MCadException.h"

class MCadResultException : public MCadException
{
public:
	explicit MCadResultException(const std::source_location& a_loc, const std::string_view& a_extra = "");
	virtual ~MCadResultException( ) = default;
	[[nodiscard]] virtual std::string message( )const noexcept final;
};

