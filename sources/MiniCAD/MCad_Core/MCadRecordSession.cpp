#include "pch.h"
#include <utility>
#include "MCadRecordSession.h"


void MCadRecordSession::compact()
{
	size_t offset = 0; // offset if remove useless records
	//
}

MCadRecordSession::MCadRecordSession(const std::string& a_title) : m_title{ a_title }
{
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


void MCadRecordSession::record(MCadObject* a_pObject, const IMCadRecord::RecordAction a_recordAction, const RecordExtra& a_data)
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
	
	if (bCreateRecord)
	{
		switch (a_recordAction)
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
	}
}
