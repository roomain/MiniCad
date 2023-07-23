#pragma once
/***********************************************
* @headerfile MCadException.h
* @date 20 / 07 / 2023
* @author Roomain
************************************************/
#include <exception>
#include <string>
#include <source_location>
#include "MCad_Core_globals.h"

#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)

/*@brief base class for exception*/
class MCadException : public std::exception
{
protected:
	std::source_location m_exceptLoc;	/*!< location of exception*/
	std::string	m_extra;				/*!< extra message*/

public:
	MCadException() = delete;
	explicit MCadException(const std::source_location& a_loc, const std::string_view& a_extra = "") :
		m_exceptLoc{ a_loc }, m_extra{ a_extra }{}
	virtual ~MCadException() = default;
	inline const std::source_location& location()const { return m_exceptLoc; }
	[[nodiscard]] virtual std::string message()const noexcept = 0;
};
#pragma warning(pop)