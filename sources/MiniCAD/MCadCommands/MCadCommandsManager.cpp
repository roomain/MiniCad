#include "pch.h"
#include <ranges>
#include "MCadCommandsManager.h"
#include "MCadCommand.h"
#include "MCadStringTools.h"

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

MCadCommandsManager::~MCadCommandsManager( )
{
	//
}

bool MCadCommandsManager::registerCommand(const MCadCommandPtr& a_command)
{
	//
}

void MCadCommandsManager::releaseCommand(const std::string& a_command)
{
	//
}

void MCadCommandsManager::execute(const std::string& a_cmd, const MCadCmdArguments& a_arg)
{
	//
}

void MCadCommandsManager::execute(const std::string& a_cmd)
{
	//
}

void MCadCommandsManager::execute_async(const std::string& a_cmd, const MCadCmdArguments& a_arg)
{
	//
}

void MCadCommandsManager::execute_async(const std::string& a_cmd)
{
	//
}
