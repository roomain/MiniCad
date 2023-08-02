#include "pch.h"
#include "MCadUndoRedo.h"
#include <ranges>
#include <algorithm>
#include <functional>


void MCadRecordSession::undo(ObjectMap& a_realocMap, const Record& a_record)
{
	switch (a_record.m_action)
	{
	case RecordAction::Undo_create:
	{
		//
		break;
	}

	case RecordAction::Undo_modify:
	{
		//auto pObject = m_mpObjDatabase[a_record.m_objectId].lock();
		//const size_t offset = m_pBinBuffer->size();
		//pObject->save(m_outputStream);
		//m_lUndoRecord.emplace_back(RecordAction::Redo_modify,
		//	pObject->uid(),
		//	pObject->owner().lock() ? pObject->owner().lock()->uid() : 0,
		//	pObject->isA(),
		//	offset);
		//m_inputStream.setPos(a_record.m_offset);
		//pObject->load(m_inputStream);
		// TODO owner
		break;
	}

	case RecordAction::Undo_delete:
	{
		if (a_record.m_objectDef.lock())
		{
			//MCadObject::enableUIDGenerator(false);
			//auto pObject = a_record.m_objectDef.lock()->create();
			//MCadObject::enableUIDGenerator(true);
			//pObject->setUID(a_record.m_objectId);
			//m_mpObjDatabase[a_record.m_objectId] = pObject;
			//m_inputStream.setPos(a_record.m_offset);
			//pObject->load(m_inputStream);
			//m_lUndoRecord.emplace_back(RecordAction::Redo_create,
			//	a_record.m_objectId,
			//	a_record.m_ownerObject,
			//	a_record.m_objectDef,
			//	a_record.m_offset);
			//
			//a_realocMap[a_record.m_objectId] = pObject;
		}
		break;
	}

	default:
		break;
	}
}

void MCadRecordSession::redo(ObjectMap& a_realocMap, const Record& a_record)
{
	switch (a_record.m_action)
	{
	case RecordAction::Redo_create:
		break;

	case RecordAction::Redo_modify:
		break;

	case RecordAction::Redo_delete:
		break;

	default:
		break;
	}
}

MCadRecordSession::MCadRecordSession()
{
	m_pBinBuffer = std::make_shared<MCadBinaryBuffer>();
	m_inputStream.setBuffer(m_pBinBuffer);
	m_outputStream.setBuffer(m_pBinBuffer);
}

void MCadRecordSession::startSession()
{
	m_timePoint = std::chrono::system_clock::now();
}

void MCadRecordSession::record(const MCadObject* a_pUndoObject, const RecordAction a_action)
{
	auto iter = std::ranges::find_if(m_lUndoRecord, [a_pUndoObject](const auto& a_record)
		{
			return a_pUndoObject->uid() == a_record.m_objectId;
		});
	if (iter != m_lUndoRecord.end())
	{
		if (iter->m_action == RecordAction::Undo_create && a_action == RecordAction::Undo_delete)
			m_lUndoRecord.erase(iter);
		else if (iter->m_action < a_action)
			iter->m_action = a_action;
	}
	else if (m_pBinBuffer)// has buffer
	{
		const size_t offset = m_pBinBuffer->size();
		a_pUndoObject->save(m_outputStream);

		/*if (m_pBinBuffer)
		{
			
			const size_t offset = m_pBinBuffer->size();
			m_mpObjDatabase[a_undoObject->uid()] = a_undoObject;
			a_undoObject->save(m_outputStream);
			m_lUndoRecord.emplace_back(a_action,
				a_undoObject->uid(),
				a_undoObject->owner().lock() ? a_undoObject->owner().lock()->uid() : 0,
				std::dynamic_pointer_cast<TRTTIDefinition<MCadObject>>(a_undoObject->isA()),
				offset
				);
		}*/
	}
}

void MCadRecordSession::undo()
{
	ObjectMap realocMap;
	for (const auto& record : m_lUndoRecord | std::views::reverse)
	{
		//
	}
	realocMap.clear();
}

void MCadRecordSession::undoFiltered(UndoRedoFilter a_filter)
{
	ObjectMap realocMap;
	auto filterFun = [&a_filter](const Record& a_rec) {return a_filter(a_rec.m_objectDef.lock(), a_rec.m_action); };
	for (const auto& record : m_lUndoRecord | std::views::filter(filterFun))
	{
		//
	}
	realocMap.clear();
}


void MCadRecordSession::redo()
{
	ObjectMap realocMap;
	for (const auto& record : m_lRedoRecord | std::views::reverse)
	{
		//
	}
	realocMap.clear();
}


void MCadRecordSession::redoFiltered(UndoRedoFilter a_filter)
{
	ObjectMap realocMap;
	auto filterFun = [&a_filter](const Record& a_rec) {return a_filter(a_rec.m_objectDef.lock(), a_rec.m_action); };
	for (const auto& record : m_lRedoRecord | std::views::filter(filterFun))
	{
		//
	}
	realocMap.clear();
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
