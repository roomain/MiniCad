#pragma once
/***********************************************
* @headerfile UndoRedoException.h
* @date 02 / 08 / 2023
* @author Roomain
************************************************/
#include "MCadException.h"

#pragma warning(push)
#pragma warning(disable : 4251)
#pragma warning(disable : 4275)


class MCAD_CORE_EXPORT UndoRedoException : public MCadException
{
public:
	enum class ExceptionType
	{
#define UNDO_REDO_EXCEPT_DEF(enumerate, message) enumerate,
#include "UndoRedoExceptionDefines.h"
#undef UNDO_REDO_EXCEPT_DEF
	};

private:
	ExceptionType m_type;
	std::string m_message;

public:
	UndoRedoException(const std::source_location& a_loc, const ExceptionType a_type, const std::string_view& a_extra = "");
	virtual ~UndoRedoException() = default;
	[[nodiscard]] const ExceptionType type()const noexcept { return m_type; }
	[[nodiscard]] std::string message()const noexcept override { return m_message; }
};

#define UNDO_REDO_TROW(enumerate) \
	throw UndoRedoException(std::source_location::current(), enumerate);


#define UNDO_REDO_TROW_EXTRA(enumerate, extra) \
	throw UndoRedoException(std::source_location::current(), enumerate, #extra);


#pragma warning(pop)