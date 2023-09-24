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

void MCadRecordSession::append(const IMCadRecordPtr& a_record)
{
	m_lRecordUndo.emplace_back(a_record);
}

void MCadRecordSession::undo(MCadRealocMemory& a_realocMemory)
{
	bool bGenRedoRecord = m_lRecordRedo.empty( );
	for ( auto&& pRecord : m_lRecordUndo )
	{
		if ( bGenRedoRecord && pRecord->hasReverse( ) && !pRecord->isErased( ) )
			m_lRecordRedo.push_back(pRecord->generateReverse(m_outputStream, a_realocMemory));

		if( !pRecord->isErased() )
			pRecord->apply(m_inputStream, a_realocMemory);
	}
}

void MCadRecordSession::redo(MCadRealocMemory& a_realocMemory)
{
	for ( auto&& pRecord : m_lRecordRedo )
	{
		if ( !pRecord->isErased( ) )
			pRecord->apply(m_inputStream, a_realocMemory);
	}
}