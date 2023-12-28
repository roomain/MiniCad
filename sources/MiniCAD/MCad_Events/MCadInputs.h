#pragma once
/***********************************************
* @headerfile MCadInputs.h
* @date 03 / 12 / 2023
* @author Roomain
************************************************/
#include <vector>
#include <string>
#include <string_view>
#include <optional>
#include <functional>
#include "not_copiable.h"
#include "glm/glm.hpp"

using MCadArgList = std::vector<std::string>;
using MCadArgIterator = MCadArgList::iterator;

template<typename KeywordType> requires( std::is_enum_v<KeywordType> )
using KeywordChecker = std::function< bool( const std::string_view, KeywordType& )>;


class MCadInputs
{
	NOT_COPIABLE(MCadInputs)
private:
	MCadArgList m_argList;								/*!< list of command arguments*/
	mutable std::optional<MCadArgIterator> m_argIter;	/*!< current iterator*/
	static void init_internal(const std::string& a_cmdArgs, MCadArgList& a_arg);

public:
	MCadInputs( ) = default;
	explicit MCadInputs(const std::string& a_cmdArgs);
	~MCadInputs( ) = default;
	void init(const std::string& a_cmdArgs);
	/*@brief return true if argument exists and has a compatible type*/
	template<typename Type>
	[[nodiscard]] bool nextArg(Type& a_arg) const noexcept
	{
		// need to define function: bool fromString(const std::string&, Type&)
		if ( m_argIter.has_value( ) && fromString(*( m_argIter.value( ) ), a_arg) )
		{
			( *m_argIter )++;
			return true;
		}
		return false;
	}

	template<typename KeywordType> requires( std::is_enum_v<KeywordType> )
	[[nodiscard]] bool nextArg(KeywordType& a_arg, KeywordChecker<KeywordType>& a_check) const noexcept
	{
		// need to define function: bool fromString(const std::string&, Type&)
		if ( m_argIter.has_value( ) && a_check && a_check(*(m_argIter.value( )), a_arg))
		{
			( *m_argIter )++;
			return true;
		}
		return false;
	}
};
