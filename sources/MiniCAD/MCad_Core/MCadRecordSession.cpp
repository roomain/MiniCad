#include "pch.h"
#include <utility>
#include "MCadRecordSession.h"
#include "MCadRecordObject.h"


MCadRecordFactory::MCadRecordFactory(MCadOutputBinStream* const a_stream, DefinitionMap* const a_defMap) 
	: m_stream{ a_stream }, m_defMap{ a_defMap }
{
	//
}

void MCadRecordFactory::setup(MCadObjectWPtr a_pObject, IMCadRecord::RecordAction a_action)
{
	m_pObject = a_pObject;
	m_recordAction = a_action;
}

IMCadRecordUPtr MCadRecordFactory::operator()(const IndexedItem& a_item)const
{
	switch (m_recordAction)
	{
	case IMCadRecord::RecordAction::Record_modify:			/*!< object modified*/
		break;

	case IMCadRecord::RecordAction::Record_create:			/*!< object created*/
		break;

	case IMCadRecord::RecordAction::Record_delete:			/*!< object deleted*/
		break;

	case IMCadRecord::RecordAction::Record_add:				/*!< (for container) object added*/
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

IMCadRecordUPtr MCadRecordFactory::operator()(const KeyItem& a_item)const
{
	switch (m_recordAction)
	{
	case IMCadRecord::RecordAction::Record_modify:			/*!< object modified*/
		break;

	case IMCadRecord::RecordAction::Record_create:			/*!< object created*/
		break;

	case IMCadRecord::RecordAction::Record_delete:			/*!< object deleted*/
		break;

	case IMCadRecord::RecordAction::Record_add:				/*!< (for container) object added*/
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

IMCadRecordUPtr MCadRecordFactory::operator()()const
{
	switch (m_recordAction)
	{

	case IMCadRecord::RecordAction::Record_delete:			/*!< object deleted*/
	case IMCadRecord::RecordAction::Record_modify:			/*!< object modified*/
	{
		const size_t offset = m_stream->offset();
		m_pObject.lock()->save(*m_stream);
		return std::make_unique<MCadRecordObject>(m_recordAction, m_pObject, offset, m_stream->offset() - offset);
	}

	case IMCadRecord::RecordAction::Record_create:			/*!< object created*/
		break;


	case IMCadRecord::RecordAction::Record_add:				/*!< (for container) object added*/
		break;

	case IMCadRecord::RecordAction::Record_remove:
		break;

	default:
		break;
	}

	return nullptr;
}

IMCadRecordUPtr MCadRecordFactory::genRedoRecord(const MCadRecordObject* a_pUndoRecord)
{
	//
	return nullptr;
}

IMCadRecordUPtr MCadRecordFactory::genRedoRecord(const MCadRecordContainer* a_pUndoRecord)
{
	//
	return nullptr;
}

IMCadRecordUPtr MCadRecordFactory::genRedoRecord(const MCadRecorDictionary* a_pUndoRecord)
{
	//
	return nullptr;
}

//--------------------------------------------------------------------------------------------

void MCadRecordSession::compact()
{
	size_t offset = 0; // offset if remove useless records
	//
}

MCadRecordSession::MCadRecordSession(const std::string& a_title) : m_title{ a_title }, 
m_recordFactory{ &m_outputStream, &m_definitionByObject }
{
	m_timePoint = std::chrono::system_clock::now();
	m_pBinBuffer = std::make_shared<MCadBinaryBuffer>();
	m_inputStream.setBuffer(m_pBinBuffer);
	m_outputStream.setBuffer(m_pBinBuffer);
}

void MCadRecordSession::undo(ObjectMap& a_realocmap)
{
	bool bPrepareRedo = m_lRecordRedo.empty();
	for (const auto& record : m_lRecordUndo)
	{
		if (bPrepareRedo)
		{
			//
		}
		record->undo(a_realocmap, m_inputStream);
	}
}

void MCadRecordSession::redo(ObjectMap& a_realocmap)
{
	// TODO
}

void MCadRecordSession::undo(ObjectMap& a_realocmap, IMCadRecord::RecordFilter& a_filterFun)
{
	// TODO
}

void MCadRecordSession::redo(ObjectMap& a_realocmap, IMCadRecord::RecordFilter& a_filterFun)
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
			// object not treated
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
			// object not treated
		}
	}
}
