#pragma once
/***********************************************
* @headerfile MCadCommandsManager.h
* @date 26 / 12 / 2023
* @author Roomain
************************************************/
#include <vector>
#include <memory>
#include <string>
#include <stack>
#include "TMCadReactive.h"

class MCadCommand;
class MCadCmdArguments;

using MCadCommandPtr = std::shared_ptr<MCadCommand>;

class MCadCommandReactor;

/*@brief commands database*/
class MCadCommandsManager : public TMCadReactive<MCadCommandReactor>
{
private:
	std::vector<MCadCommandPtr> m_vCommands;

	std::stack<MCadCommandPtr> m_executedCommand;
	//
	MCadCommandPtr find(const std::string& a_cmdName)const;

public:
	MCadCommandsManager( ) = default;
	virtual ~MCadCommandsManager( );
	bool registerCommand(const MCadCommandPtr& a_command);
	void releaseCommand(const std::string& a_command);

	constexpr size_t stackSize( )const { return m_executedCommand.size( ); }

	void execute(const std::string& a_cmd, const MCadCmdArguments& a_arg);
	void execute(const std::string& a_cmd);

	void execute_async(const std::string& a_cmd, const MCadCmdArguments& a_arg);
	void execute_async(const std::string& a_cmd);

	using const_iterator = std::vector<MCadCommandPtr>::const_iterator;
	constexpr const_iterator cbegin( )const { return m_vCommands.cbegin( ); }
	constexpr const_iterator cend( )const { return m_vCommands.cend( ); }
};
