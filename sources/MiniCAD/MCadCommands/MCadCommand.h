#pragma once
/***********************************************
* @headerfile MCadCommand.h
* @date 03 / 12 / 2023
* @author Roomain
************************************************/
#include <string>
#include <optional>
#include <queue>
#include "MCadResult.h"
#include "not_copiable.h"



/*@brief base class of command*/
class MCadCommand
{
	NOT_COPIABLE(MCadCommand)
private:
	std::string m_commandName;

public:
	MCadCommand( ) = delete;
	explicit MCadCommand(const std::string a_name);
	virtual ~MCadCommand( );
	virtual std::optional<MCadResult> execute(const std::string a_arguments) = 0;
};

