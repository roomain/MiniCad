#include "pch.h"
#include <utility>
#include "MCadRecordSession.h"


//--------------------------------------------------------------------------------------------

void MCadRecordSession::compact()
{
	size_t offset = 0; // offset if remove useless records
	//
}

MCadRecordSession::MCadRecordSession(const std::string& a_title) : m_title{ a_title }
{
	m_timePoint = std::chrono::system_clock::now();
	m_pBinBuffer = std::make_shared<MCadBinaryBuffer>();
	m_inputStream.setBuffer(m_pBinBuffer);
	m_outputStream.setBuffer(m_pBinBuffer);
}

