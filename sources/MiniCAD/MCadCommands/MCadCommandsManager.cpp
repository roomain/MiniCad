#include "pch.h"
#include <ranges>
#include "MCadCommandsManager.h"
#include "MCadCommand.h"
#include "MCadStringTools.h"
#include "MCadCommandException.h"
#include "MCadCommandReactor.h"

MCadCommandPtr MCadCommandsManager::find(const std::string& a_cmdName)const
{
	auto iter = std::ranges::find_if(m_vCommands, [ &a_cmdName ] (const MCadCommandPtr& a_command)
		{
			return equivalent(a_cmdName, a_command->commandName()) || 
				equivalent(a_cmdName, a_command->commandGlobalName( )) ||
				equivalent(a_cmdName, a_command->commandLocalName( ));
		});

	if ( iter != m_vCommands.cend( ) )
		return *iter;

	return MCadCommandPtr();
}


void MCadCommandsManager::registerCommand(const MCadCommandPtr& a_command)
{
	// find if command exists
	auto iter = std::ranges::find_if(m_vCommands, [ a_command ] (const MCadCommandPtr& a_localCommand)
		{
			return equivalent(a_localCommand->commandName( ), a_command->commandName( )) ||
				equivalent(a_localCommand->commandName( ), a_command->commandGlobalName( )) ||
				equivalent(a_localCommand->commandName( ), a_command->commandLocalName( )) ||
				
				equivalent(a_localCommand->commandGlobalName( ), a_command->commandName( )) ||
				equivalent(a_localCommand->commandGlobalName( ), a_command->commandGlobalName( )) ||
				equivalent(a_localCommand->commandGlobalName( ), a_command->commandLocalName( )) ||

				equivalent(a_localCommand->commandLocalName( ), a_command->commandName( )) ||
				equivalent(a_localCommand->commandLocalName( ), a_command->commandGlobalName( )) ||
				equivalent(a_localCommand->commandLocalName( ), a_command->commandLocalName( ));
		});

	if ( iter != m_vCommands.end( ) )
		throw MCadCommandException(MCadCommandException::ExceptType::Command_except_CmdAlreadyExist, 
			std::source_location::current());

	m_vCommands.emplace_back(a_command);
}

void MCadCommandsManager::releaseCommand(const std::string& a_cmdName)
{
	auto iter = std::ranges::find_if(m_vCommands, [ &a_cmdName ] (const MCadCommandPtr& a_command)
		{
			return equivalent(a_cmdName, a_command->commandName( )) ||
				equivalent(a_cmdName, a_command->commandGlobalName( )) ||
				equivalent(a_cmdName, a_command->commandLocalName( ));
		});

	if ( iter != m_vCommands.cend( ) )
		m_vCommands.erase(iter);
}

std::optional<MCadResult> MCadCommandsManager::execute(const std::string& a_cmd, IMCadIO& a_inputInterface, const std::string& arguments)
{
	std::optional<MCadResult> result;
	foreach_reactor<MCadCommandReactor>(&MCadCommandReactor::onSearchCommand, a_cmd);
	MCadCommandPtr pCmd = find(a_cmd);
	if ( pCmd )
	{
		foreach_reactor<MCadCommandReactor>(&MCadCommandReactor::onStartCommand, a_cmd, arguments);
		m_executedCommand.emplace(pCmd);
		result = pCmd->execute(arguments, a_inputInterface);
		m_executedCommand.pop( );
		foreach_reactor<MCadCommandReactor>(&MCadCommandReactor::onEndCommand, a_cmd);
	}
	else
	{
		throw MCadCommandException(MCadCommandException::ExceptType::Command_except_CmdNotFound,
			std::source_location::current( ));
	}
	return result;
}


