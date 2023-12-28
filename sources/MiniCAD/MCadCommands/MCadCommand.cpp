#include "pch.h"
#include "MCadCommand.h"
#include "IMCadIO.h"

MCadCommand::MCadCommand(const std::string a_name, const std::string a_globalName,
		const std::string a_localName) : m_commandName{ a_name }, m_globalName{ a_globalName },
	m_localName{ a_localName }
{
	//
}

std::optional<MCadResult> MCadCommand::execute(const std::string a_arguments, IMCadIO& a_IOInterface)
{
	a_IOInterface.loadArguments(a_arguments);
	return execute_internal(a_IOInterface);
}