#pragma once
/***********************************************
* @headerfile MCadCommandReactor.h
* @date 28 / 12 / 2023
* @author Roomain
************************************************/
#include <string>
#include "RTTIDefinition_macros.h"

class MCadCommandReactor
{
	DECLARE_RTTI(1, MCadCommandReactor)
public:
	MCadCommandReactor( ) = default;
	virtual ~MCadCommandReactor( ) = default;
	virtual void onSearchCommand(const std::string& a_cmd) = 0;
	virtual void onStartCommand(const std::string& a_cmd, const std::string& a_args) = 0;
	virtual void onEndCommand(const std::string& a_cmd) = 0;
	/*@brief is active*/
	virtual bool enabled( )const noexcept = 0;
};
