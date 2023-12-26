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

class MCadIO;

/*@brief base class of command*/
class MCadCommand
{
	NOT_COPIABLE(MCadCommand)
private:
	std::string m_commandName;
	std::string m_globalName;
	std::string m_localName;

public:
	MCadCommand( ) = delete;
	explicit MCadCommand(const std::string a_name, const std::string a_globalName,
		const std::string a_localName);
	virtual ~MCadCommand( ) = default;
	virtual std::optional<MCadResult> execute(const std::string a_arguments, MCadIO& a_IOInterface) = 0;
	[[nodiscard]] std::string commandName( )const noexcept { return m_commandName; }
	[[nodiscard]] std::string commandGlobalName( )const noexcept { return m_globalName; }
	[[nodiscard]] std::string commandLocalName( )const noexcept { return m_localName; }
};

