#pragma once
/***********************************************
* @headerfile MCadCommandsManager.h
* @date 26 / 12 / 2023
* @author Roomain
************************************************/
#include <vector>
#include <memory>
#include <string>
#include <optional>
#include <stack>
#include "TMCadReactive.h"
#include "MCadResult.h"
#include "MCad_Command_globals.h"

class MCadCommand;
class IMCadIO;

using MCadCommandPtr = std::shared_ptr<MCadCommand>;

class MCadCommandReactor;

/*@brief commands database*/
class MCAD_CMD_EXPORT MCadCommandsManager : public TMCadReactive<MCadCommandReactor>
{
private:
	std::vector<MCadCommandPtr> m_vCommands;

	std::stack<MCadCommandPtr> m_executedCommand;
	//
	MCadCommandPtr find(const std::string& a_cmdName)const;

public:
	MCadCommandsManager( ) = default;
	virtual ~MCadCommandsManager( );
	void registerCommand(const MCadCommandPtr& a_command);
	void releaseCommand(const std::string& a_cmdName);

	[[nodiscard]] inline size_t stackSize( )const { return m_executedCommand.size( ); }

	std::optional<MCadResult> execute(const std::string& a_cmd, IMCadIO& a_inputInterface, const std::string& arguments = "");
	
	using const_iterator = std::vector<MCadCommandPtr>::const_iterator;
	constexpr const_iterator cbegin( )const { return m_vCommands.cbegin( ); }
	constexpr const_iterator cend( )const { return m_vCommands.cend( ); }
};
