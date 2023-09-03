#include "pch.h"
#include "MCadUndoRedo.h"
#include <ranges>
#include <algorithm>
#include <functional>



MCadUndoRedo::MCadUndoRedo()
{
	//
}

MCadUndoRedo::~MCadUndoRedo()
{
	//
}

void MCadUndoRedo::startUndoRecord(const std::string& a_title)
{
	m_sessionActive = true;
	if (!m_sessionList.empty() && m_SessionUndo != m_sessionList.end() - 1)
	{
		// TODO erase
	}
	m_sessionList.emplace_back(a_title);
	m_SessionUndo = m_sessionList.end() - 1;
	m_SessionRedo.reset();
	
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
		m_SessionRedo.value()->redo(m_realocationMap);
		if (m_SessionRedo.value() == m_sessionList.end()-1)
		{
			m_SessionRedo.reset();
			m_SessionUndo = m_sessionList.end() - 1;
		}
		else
		{
			m_SessionUndo = m_SessionRedo.value();
			m_SessionRedo.value()++;
		}
	}
}

void MCadUndoRedo::undo()
{
	if (hasUndo() && !m_sessionActive)
	{
		m_SessionUndo.value()->undo(m_realocationMap);
		if (m_SessionUndo.value() == m_sessionList.begin())
		{
			m_SessionUndo.reset();
			m_SessionRedo = m_sessionList.begin();
		}
		else
		{
			m_SessionRedo = m_SessionUndo.value();
			m_SessionUndo.value()--;
		}
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
	return m_SessionUndo.has_value();
}

bool MCadUndoRedo::hasRedo()const noexcept
{
	return m_SessionRedo.has_value();
}

void MCadUndoRedo::clear()
{
	m_SessionUndo.reset();
	m_SessionRedo.reset();
	m_sessionActive = false;
	m_sessionList.clear();
}