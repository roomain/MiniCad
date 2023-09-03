#include "pch.h"
#include "UndoRedoException.h"

UndoRedoException::UndoRedoException(const std::source_location& a_loc, const ExceptionType a_type, const std::string_view& a_extra) :
	MCadException(a_loc, a_extra), m_type{a_type}
{
	switch (m_type)
	{
#define UNDO_REDO_EXCEPT_DEF(enumerate, message) \
		case ExceptionType::enumerate: \
			m_message = #message; \
			break;

#include "UndoRedoExceptionDefines.h"
#undef UNDO_REDO_EXCEPT_DEF
	}

	m_message += std::format("({})", a_extra);
}
