#include "pch.h"
#include <utility>
#include "MCadRecordSession.h"

namespace UndoRedo
{

	//--------------------------------------------------------------------------------------------

	void MCadRecordSession::compact( )
	{
		size_t offset = 0; // offset if remove useless records
		//
	}

	MCadRecordSession::MCadRecordSession(const std::string& a_title) : m_title{ a_title }
	{
		m_timePoint = std::chrono::system_clock::now( );
		m_pBinBuffer = std::make_shared<MCadBinaryBuffer>( );
		m_inputStream.setBuffer(m_pBinBuffer);
		m_outputStream.setBuffer(m_pBinBuffer);
	}

	void MCadRecordSession::append(const IMCadRecordPtr& a_record)
	{
		m_lRecords.emplace_front(a_record);
	}

	void MCadRecordSession::undo(MCadReallocMemory& a_realocMemory)
	{
		for ( const auto& pRecord : m_lRecords )
			pRecord->undo(m_inputStream, a_realocMemory, m_outputStream);
	}

	void MCadRecordSession::redo(MCadReallocMemory& a_realocMemory)
	{
		for ( auto&& pRecord : m_lRecords )
			pRecord->redo(m_inputStream, a_realocMemory);
	}

}