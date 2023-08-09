#include "pch.h"
#include <utility>
#include "MCadRecordSession.h"


MCadRecordSession::MCadRecordFactory::MCadRecordFactory(MCadOutputBinStream* const a_stream, DefinitionMap* const a_defMap) 
	: m_stream{ a_stream }, m_defMap{ a_defMap }
{
	//
}

void MCadRecordSession::MCadRecordFactory::setup(const MCadObject* a_pObject, IMCadRecord::RecordAction a_action)
{
	m_pObject = a_pObject;
	m_recordAction = a_action;
}

IMCadRecordUPtr MCadRecordSession::MCadRecordFactory::operator()(const IndexedItem& a_item)const
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

	default:
		break;
	}

	return nullptr;
}

IMCadRecordUPtr MCadRecordSession::MCadRecordFactory::operator()(const KeyItem& a_item)const
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

	default:
		break;
	}
	return nullptr;
}

IMCadRecordUPtr MCadRecordSession::MCadRecordFactory::operator()()const
{
	switch (m_recordAction)
	{

	case IMCadRecord::RecordAction::Record_delete:			/*!< object deleted*/
	case IMCadRecord::RecordAction::Record_modify:			/*!< object modified*/
		m_pObject->save(*m_stream);
		//
		break;

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

void MCadRecordSession::undo(std::unordered_map<ObjectUID, MCadObject*>& a_realocmap)
{
	// TODO
}

void MCadRecordSession::redo(std::unordered_map<ObjectUID, MCadObject*>& a_realocmap)
{
	// TODO
}

void MCadRecordSession::undo(std::unordered_map<ObjectUID, MCadObject*>& a_realocmap, IMCadRecord::RecordFilter& a_filterFun)
{
	// TODO
}

void MCadRecordSession::redo(std::unordered_map<ObjectUID, MCadObject*>& a_realocmap, IMCadRecord::RecordFilter& a_filterFun)
{
	// TODO
}



bool MCadRecordSession::checkRecord(const MCadObject* a_pObject, const IMCadRecord::RecordAction a_recordAction)const
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
			break;

		case IMCadRecord::RecordAction::Record_remove:
			break;

		default:
			break;
		}
	}
	return bCreateRecord;
}


void MCadRecordSession::record(const MCadObject* a_pObject, const IMCadRecord::RecordAction a_recordAction)
{
	if (checkRecord(a_pObject, a_recordAction))
	{
		m_recordFactory.setup(a_pObject, a_recordAction);
		m_lRecordUndo.push_back(m_recordFactory());
	}
}

void MCadRecordSession::record(const MCadObject* a_pObject, const IMCadRecord::RecordAction a_recordAction, const RecordExtra& a_data)
{	
	if (checkRecord(a_pObject, a_recordAction))
	{
		m_recordFactory.setup(a_pObject, a_recordAction);
		m_lRecordUndo.push_back(std::visit(m_recordFactory, a_data));
	}
}
