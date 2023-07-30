#include "pch.h"
#include "MCadUndoRedo.h"
#include <ranges>

void Session::record(const MCadObjectPtr& a_undoObject, RecordAction&& a_action)
{
	auto iter = m_umRecord.find(a_undoObject->uid());
	if (iter != m_umRecord.end())
	{
		if (iter->second.m_action < a_action)
			iter->second.m_action = a_action;
	}
	else
	{
		//a_undoObject->save();
		//m_umRecord.emplace(a_undoObject->uid(), Record{ a_action,
		//	a_undoObject->uid(),
		//	a_undoObject->owner().lock() ? a_undoObject->owner().lock()->uid() : 0,
		//	a_undoObject->isA(),
		//	// TODO
		//	});
	}
}

void Session::restore()
{
	//
}

//----------------------------------------------------------------------------------------------
MCadUndoRedo::MCadUndoRedo()
{
	m_currentSession = m_sessionList.begin();
}

MCadUndoRedo::~MCadUndoRedo()
{
	//
}

void MCadUndoRedo::startUndoRecord()
{
	m_sessionActive = true;
	//
}

void MCadUndoRedo::endUndoRecord()
{
	//
	m_sessionActive = false;
}

void MCadUndoRedo::redo()
{
	if (hasRedo() && !m_sessionActive)
	{
		//
	}
}

void MCadUndoRedo::undo()
{
	if (hasUndo() && !m_sessionActive)
	{
		//
	}
}

void MCadUndoRedo::cancel()
{
	if (m_sessionActive)
	{
		//
	}
}

bool MCadUndoRedo::hasUndo()const noexcept
{
	return (m_sessionList.begin() != m_currentSession) && !m_sessionList.empty();
}

bool MCadUndoRedo::hasRedo()const noexcept
{
	return (m_sessionList.end() != m_currentSession) && !m_sessionList.empty();
}
