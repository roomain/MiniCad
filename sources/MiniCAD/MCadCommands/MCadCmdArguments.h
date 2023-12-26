#pragma once
/***********************************************
* @headerfile MCadCmdArguments.h
* @date 03 / 12 / 2023
* @author Roomain
************************************************/
#include <vector>
#include <string>
#include <optional>
#include "not_copiable.h"
#include "glm/glm.hpp"

using MCadArgList = std::vector<std::string>;
using MCadArgIterator = MCadArgList::iterator;

class MCadCmArguments
{
	NOT_COPIABLE(MCadCmArguments)
private:
	MCadArgList m_argList;								/*!< list of command arguments*/
	mutable std::optional<MCadArgIterator> m_argIter;	/*!< current iterator*/

public:
	MCadCmArguments( );
	explicit MCadCmArguments(const std::string& a_cmdArgs);
	~MCadCmArguments( ) = default;
	/*@brief return true if argument exists and has a compatible type*/
	template<typename Type>
	[[nodiscard]] bool nextArg(Type& a_arg) const noexcept
	{
		// need to define function: bool fromString(const std::string&, Type&)
		if ( m_argIter.has_value( ) && fromString(*( m_argIter.value( ) ), a_arg) )
		{
			(*m_argIter)++;
			return true;
		}
		return false;
	}
};

