#include "pch.h"
#include <utility>
#include "MCadRecordSession.h"
#include "IMCadContainer.h"

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


void MCadRecordSession::record(MCadObject* a_pObject, IMCadRecord::RecordAction a_action)
{
	// find object record
	auto iter = std::ranges::find_if(m_lRecordUndo, [a_pObject](const auto& a_record)
		{
			return a_pObject->uid() == a_record->objectUID();
		});

}
