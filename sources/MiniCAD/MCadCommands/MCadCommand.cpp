#include "pch.h"
#include "MCadCommand.h"

MCadCommand::MCadCommand(const std::string a_name, const std::string a_globalName,
		const std::string a_localName) : m_commandName{ a_name }, m_globalName{ a_globalName },
	m_localName{ a_localName }
{
	//
}