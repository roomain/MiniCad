#include "pch.h"
#include "MCadRecords.h"
#include "IMCadOutputStream.h"
#include "IMCadInputStream.h"
#include "UndoRedoException.h"
#include "MCadLogger.h"
#include "MCadObject.h"


IMCadObjectRecord::IMCadObjectRecord(MCadObject* const a_pObject) : 
	m_objectProxy{ a_pObject }
{
	if ( nullptr == a_pObject )
		UNDO_REDO_TROW(UndoRedoException::ExceptionType::Except_Deleted)
}

//---------------------------------------------------------------------------------------

MCadRecordModification::MCadRecordModification(MCadObject* const a_pObject, IMCadOutputStream& a_stream) : 
	IMCadObjectRecord(a_pObject), m_dataOffset{ m_dataOffset = a_stream.offset() }
{
	a_pObject->save(a_stream);
}

std::shared_ptr<IMCadRecord> MCadRecordModification::generateReverse(IMCadOutputStream& a_stream, MCadRealocMemory& a_realocMem)const
{
	if ( m_objectProxy.isRealocable( ) )
	{
		return std::make_shared<MCadRecordModification>(m_objectProxy.pointer( ), a_stream);
	}
	else
	{
		MCadLogger::Instance( ) << LogMode::LOG_WARNING << "Can't generate reverse record";
	}
	return nullptr;
}

void MCadRecordModification::apply(IMCadInputStream& a_stream, MCadRealocMemory& a_realocMem)
{

	if ( m_objectProxy.realocate(a_realocMem))
	{
		a_stream.setPos(m_dataOffset);
		m_objectProxy->load(a_stream);
	}
	else
	{
		// log
		MCadLogger::Instance() << LogMode::LOG_ERROR << "Can't realocate object";
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------
MCadRecordDeletion::MCadRecordDeletion(const MCadObject* a_pObject, IMCadOutputStream& a_stream) :
	IMCadRecord(), m_dataOffset{ m_dataOffset = a_stream.offset() }
{
	if ( a_pObject )
	{
		m_objectUID = a_pObject->uid( );
		m_pObjectDef = a_pObject->isA( );
		a_pObject->save(a_stream);
	}
	else
	{
		UNDO_REDO_TROW(UndoRedoException::ExceptionType::Except_Deleted)
	}
}

std::shared_ptr<IMCadRecord> MCadRecordDeletion::generateReverse(IMCadOutputStream& a_stream, MCadRealocMemory& a_realocMem)const
{
	UNDO_REDO_TROW(UndoRedoException::ExceptionType::Except_No_Reverse_record)
}

void MCadRecordDeletion::apply(IMCadInputStream& a_stream, MCadRealocMemory& a_realocMem)
{
	MCadShared_ptr<MCadObject> pObject = a_realocMem.realoc(m_objectUID, m_pObjectDef);
	if ( pObject )
	{
		a_stream.setPos(m_dataOffset);
		pObject->load(a_stream);
	}
	else
	{
		// log
		MCadLogger::Instance() << LogMode::LOG_ERROR << "Can't realocate object";
	}
}