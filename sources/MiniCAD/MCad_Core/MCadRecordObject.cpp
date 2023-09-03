#include "pch.h"
#include "MCadRecordObject.h"
#include "IMCadOutputStream.h"
#include "IMCadInputStream.h"
#include "UndoRedoException.h"
#include "MCadLogger.h"


MCadRecordModification::MCadRecordModification(MCadObject* const a_pObject, IMCadOutputStream& a_stream) : 
	IMCadRecord(a_pObject->uid(), a_pObject->isA()), m_dataOffset{ m_dataOffset = a_stream.offset() }, m_object { a_pObject->weak_from_this() }
{
	a_pObject->save(a_stream);
}

std::shared_ptr<IMCadRecord> MCadRecordModification::generateReverse(IMCadOutputStream& a_stream, MCadRealocMemory& a_realocMem)const
{
	if (auto pObj = m_object.lock())
		return std::make_shared<MCadRecordModification>(pObj.get(), a_stream);

	UNDO_REDO_TROW(UndoRedoException::ExceptionType::Except_Deleted)
}

void MCadRecordModification::apply(IMCadInputStream& a_stream, MCadRealocMemory& a_realocMem)
{
	MCadShared_ptr<MCadObject> pObj = m_object.lock();
	if (!pObj)
	{
		pObj = a_realocMem.realoc(m_recordedObjectUID, m_pObjectDef);
		m_object = pObj;
	}

	if (pObj)
	{
		a_stream.setPos(m_dataOffset);
		pObj->load(a_stream);
	}
	else
	{
		// log
		MCadLogger::Instance() << LogMode::LOG_ERROR << "Can't realocate object";
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------
MCadRecordDeletion::MCadRecordDeletion(const MCadObject* a_pObject, IMCadOutputStream& a_stream) :
	IMCadRecord(a_pObject->uid(), a_pObject->isA()), m_dataOffset{ m_dataOffset = a_stream.offset() }
{
	a_pObject->save(a_stream);
}

std::shared_ptr<IMCadRecord> MCadRecordDeletion::generateReverse(IMCadOutputStream& a_stream, MCadRealocMemory& a_realocMem)const
{
	UNDO_REDO_TROW(UndoRedoException::ExceptionType::Except_No_Reverse_record)
}

void MCadRecordDeletion::apply(IMCadInputStream& a_stream, MCadRealocMemory& a_realocMem)
{
	MCadShared_ptr<MCadObject> pObject = a_realocMem.realoc(m_recordedObjectUID, m_pObjectDef);
	if (pObject)
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