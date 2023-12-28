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
#include "MCadInputs.h"
#include "not_copiable.h"

class IMCadIO;

/*@brief base class of command*/
class MCadCommand
{
	NOT_COPIABLE(MCadCommand)
private:
	std::string m_commandName;
	std::string m_globalName;
	std::string m_localName;

protected:
	virtual std::optional<MCadResult> execute_internal(IMCadIO& a_IOInterface) = 0;
public:
	MCadCommand( ) = delete;
	explicit MCadCommand(const std::string a_name, const std::string a_globalName,
		const std::string a_localName);
	virtual ~MCadCommand( ) = default;
	std::optional<MCadResult> execute(const std::string a_arguments, IMCadIO& a_IOInterface);
	[[nodiscard]] constexpr std::string commandName( )const noexcept { return m_commandName; }
	[[nodiscard]] constexpr std::string commandGlobalName( )const noexcept { return m_globalName; }
	[[nodiscard]] constexpr std::string commandLocalName( )const noexcept { return m_localName; }
};

