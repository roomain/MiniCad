#include "pch.h"
#include "MCadUndoRedo.h"
#include <ranges>
#include <algorithm>
#include <functional>



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
