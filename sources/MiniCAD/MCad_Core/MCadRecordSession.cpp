#include "pch.h"
#include <utility>
#include "MCadRecordSession.h"
#include "MCadObjectRecord.h"
#include "MCadIndexedContainerRecord.h"


MCadRecordFactory::MCadRecordFactory(MCadOutputBinStream* const a_stream) 
	: m_stream{ a_stream }
{
	//
}

void MCadRecordFactory::setup(MCadObjectWPtr a_pObject, IMCadRecord::RecordAction a_action)
{
	m_pObject = a_pObject;
	m_recordAction = a_action;
}

IMCadRecordPtr MCadRecordFactory::operator()(const IndexedItem& a_item)const
{
	switch (m_recordAction)
	{
	case IMCadRecord::RecordAction::Record_add:
	case IMCadRecord::RecordAction::Record_remove:	
	case IMCadRecord::RecordAction::Record_changed:
		return std::make_shared<MCadIndexedContainerRecord>(m_recordAction, std::static_pointer_cast<IMCadIndexedContainer>(m_pObject.lock()), a_item);

	default:
		break;
	}

	return nullptr;
}

IMCadRecordPtr MCadRecordFactory::operator()(const KeyItem& a_item)const
{
	switch (m_recordAction)
	{
	case IMCadRecord::RecordAction::Record_add:

	case IMCadRecord::RecordAction::Record_remove:

	case IMCadRecord::RecordAction::Record_changed:

	default:
		break;
	}
	return nullptr;
}

IMCadRecordPtr MCadRecordFactory::operator()()const
{
	switch (m_recordAction)
	{
	case IMCadRecord::RecordAction::Record_delete:
	case IMCadRecord::RecordAction::Record_modify:
	{
		const size_t offset = m_stream->offset();
		m_pObject.lock()->save(*m_stream);
		return std::make_shared<MCadObjectRecord>(m_recordAction, m_pObject, offset, m_stream->offset() - offset);
	}

	case IMCadRecord::RecordAction::Record_create:
		return std::make_shared<MCadObjectRecord>(m_recordAction, m_pObject, 0, 0);

	default:
		break;
	}

	return nullptr;
}

IMCadRecordPtr MCadRecordFactory::genRedoRecord(const MCadObjectRecord* a_pUndoRecord)
{
	switch (a_pUndoRecord->recordAction())
	{
	case IMCadRecord::RecordAction::Record_delete:// objet is deleted
		return std::make_shared<MCadObjectRecord>(IMCadRecord::RecordAction::Record_create, a_pUndoRecord->definition(), a_pUndoRecord->objectUID());

	case IMCadRecord::RecordAction::Record_modify:
	{
		auto pObj = a_pUndoRecord->object().lock();
		if (pObj)
		{
			const size_t offset = m_stream->offset();
			pObj->save(*m_stream);
			return std::make_shared<MCadObjectRecord>(IMCadRecord::RecordAction::Record_modify, pObj, offset, m_stream->offset() - offset);
		}
		else
		{
			// log
			MCadLogger::Instance() << LogMode::LOG_ERROR << std::source_location::current() << "no pointer to create redo record";
		}
		break;
	}

	case IMCadRecord::RecordAction::Record_create:// object is created
	{
		auto pObj = a_pUndoRecord->object().lock();
		if (pObj)
		{
			const size_t offset = m_stream->offset();
			pObj->save(*m_stream);
			return std::make_shared<MCadObjectRecord>(IMCadRecord::RecordAction::Record_delete, pObj, offset, m_stream->offset() - offset);
		}
		else
		{
			// log
			MCadLogger::Instance() << LogMode::LOG_ERROR << std::source_location::current() << "no pointer to create redo record";
		}
		break;
	}

	default:
		break;
	}
	return nullptr;
}

IMCadRecordPtr MCadRecordFactory::genRedoRecord(const MCadIndexedContainerRecord* a_pUndoRecord)
{
	switch (m_recordAction)
	{
	case IMCadRecord::RecordAction::Record_add:
		return std::make_shared<MCadIndexedContainerRecord>(IMCadRecord::RecordAction::Record_remove, a_pUndoRecord->container(), swapItem(a_pUndoRecord->indexedItem()));

	case IMCadRecord::RecordAction::Record_remove:
		return std::make_shared<MCadIndexedContainerRecord>(IMCadRecord::RecordAction::Record_add, a_pUndoRecord->container(), swapItem(a_pUndoRecord->indexedItem()));

	case IMCadRecord::RecordAction::Record_changed:
		return std::make_shared<MCadIndexedContainerRecord>(m_recordAction, a_pUndoRecord->container(), swapItem(a_pUndoRecord->indexedItem()));

	default:
		break;
	}
	return nullptr;
}

IMCadRecordPtr MCadRecordFactory::genRedoRecord(const MCadRecorDictionary* a_pUndoRecord)
{
	switch (m_recordAction)
	{
	case IMCadRecord::RecordAction::Record_add:
		break;

	case IMCadRecord::RecordAction::Record_remove:
		break;

	case IMCadRecord::RecordAction::Record_changed:
		break;

	default:
		break;
	}
	return nullptr;
}

//--------------------------------------------------------------------------------------------

void MCadRecordSession::compact()
{
	size_t offset = 0; // offset if remove useless records
	//
}

MCadRecordSession::MCadRecordSession(const std::string& a_title) : m_title{ a_title }, 
m_recordFactory{ &m_outputStream }
{
	m_timePoint = std::chrono::system_clock::now();
	m_pBinBuffer = std::make_shared<MCadBinaryBuffer>();
	m_inputStream.setBuffer(m_pBinBuffer);
	m_outputStream.setBuffer(m_pBinBuffer);
}

void MCadRecordSession::undo(ObjectNextRealocMap& a_realocNextMap)
{
	ObjectRealocMap realocmap;
	bool bPrepareRedo = m_lRecordRedo.empty();
	for (const auto& record : m_lRecordUndo)
	{
		if (bPrepareRedo)
			m_lRecordRedo.push_back(record->genReverseRecord(m_recordFactory));

		record->process(realocmap, a_realocNextMap, m_inputStream);
	}
	realocmap.clear();
}

void MCadRecordSession::redo(ObjectNextRealocMap& a_realocNextMap)
{
	ObjectRealocMap realocmap;
	for (const auto& record : m_lRecordRedo)
		record->process(realocmap, a_realocNextMap, m_inputStream);
	realocmap.clear();
}

void MCadRecordSession::undo(ObjectNextRealocMap& a_realocNextMap, IMCadRecord::RecordFilter& a_filterFun)
{
	// TODO
}

void MCadRecordSession::redo(ObjectNextRealocMap& a_realocNextMap, IMCadRecord::RecordFilter& a_filterFun)
{
	// TODO
}



bool MCadRecordSession::checkRecord(MCadObject* const a_pObject, const IMCadRecord::RecordAction a_recordAction)const
{
	// find object record for same objects
	auto iter = std::ranges::find_if(m_lRecordUndo, [a_pObject](const auto& a_record)
		{
			return a_pObject->uid() == a_record->objectUID();
		});

	bool bCreateRecord = true;

	if (iter != m_lRecordUndo.end())
	{
		bCreateRecord = false;
		switch ((*iter)->recordAction())
		{
		case IMCadRecord::RecordAction::Record_modify:			/*!< object modified*/
			break;

		case IMCadRecord::RecordAction::Record_create:			/*!< object created*/
			if (a_recordAction == IMCadRecord::RecordAction::Record_delete)
				(*iter)->erase();
			break;

		case IMCadRecord::RecordAction::Record_delete:			/*!< object deleted*/
			break;

		case IMCadRecord::RecordAction::Record_add:				/*!< (for container) object added*/
		case IMCadRecord::RecordAction::Record_remove:
			bCreateRecord = true;
			break;

		default:
			break;
		}
	}
	return bCreateRecord;
}


void MCadRecordSession::record(MCadObject* const a_pObject, const IMCadRecord::RecordAction a_recordAction)
{
	if (a_pObject != nullptr && checkRecord(a_pObject, a_recordAction))
	{
		try
		{
			m_recordFactory.setup(a_pObject->weak_from_this(), a_recordAction);
			m_lRecordUndo.push_back(m_recordFactory());
		}
		catch (std::bad_weak_ptr&)
		{
			// log
			MCadLogger::Instance() << LogMode::LOG_ERROR << std::source_location::current() << "Object is not a shared pointer";
		}
	}
}

void MCadRecordSession::record(MCadObject* const a_pObject, const IMCadRecord::RecordAction a_recordAction, const RecordExtra& a_data)
{	
	if (a_pObject != nullptr && checkRecord(a_pObject, a_recordAction))
	{
		try
		{
			m_recordFactory.setup(a_pObject->weak_from_this(), a_recordAction);
			m_lRecordUndo.push_back(std::visit(m_recordFactory, a_data));
		}
		catch (std::bad_weak_ptr&)
		{
			// log
			MCadLogger::Instance() << LogMode::LOG_ERROR << std::source_location::current() << "Object is not a shared pointer";
		}
	}
}
