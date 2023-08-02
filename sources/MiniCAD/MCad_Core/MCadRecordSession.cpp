#include "pch.h"
#include <utility>
#include "MCadRecordSession.h"

MCadRecordSession::MCadRecordSession(const std::string& a_title) : m_title{ a_title }
{
	m_pBinBuffer = std::make_shared<MCadBinaryBuffer>();
	m_inputStream.setBuffer(m_pBinBuffer);
	m_outputStream.setBuffer(m_pBinBuffer);
}

void MCadRecordSession::undo()
{
	// TODO
}

void MCadRecordSession::redo()
{
	// TODO
}

void MCadRecordSession::undo(IMCadRecord::RecordFilter& a_filterFun)
{
	// TODO
}

void MCadRecordSession::redo(IMCadRecord::RecordFilter& a_filterFun)
{
	// TODO
}
