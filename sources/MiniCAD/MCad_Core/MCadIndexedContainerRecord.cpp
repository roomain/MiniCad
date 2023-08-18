#include "pch.h"
#include "MCadIndexedContainerRecord.h"



MCadIndexedContainerRecord::MCadIndexedContainerRecord(const RecordAction a_action, const IMCadIndexedContainerWPtr& a_pObject, const IndexedItem& a_data) : 
	IMCadRecord(a_action, a_pObject.lock()->uid()), m_item{ a_data }, m_pContainer{ a_pObject }
{
	//
}

void MCadIndexedContainerRecord::process(ObjectRealocMap& a_realocMap, ObjectNextRealocMap& a_realocNextMap, MCadInputBinStream& a_inputStream)
{
	switch (m_action)
	{
	case IMCadRecord::RecordAction::Record_add:
		if(!m_pContainer.lock())
			m_pContainer = std::static_pointer_cast<IMCadIndexedContainer>(IMCadRecord::findRealocObject(m_objectID, a_realocMap, a_realocNextMap).lock());
		
		if (m_pContainer.lock())
		{
			m_pContainer.lock()->undoRedo_RemoveObject(m_item.m_index);
		}
		else
		{
			// log
			MCadLogger::Instance() << LogMode::LOG_ERROR << std::source_location::current() << "no realoc pointer";
		}
		break;

	case IMCadRecord::RecordAction::Record_remove:
		if (!m_pContainer.lock())
			m_pContainer = std::static_pointer_cast<IMCadIndexedContainer>(IMCadRecord::findRealocObject(m_objectID, a_realocMap, a_realocNextMap).lock());

		if (m_pContainer.lock())
		{
			if (!m_item.m_pOld.lock())
			{
				m_item.m_pOld = IMCadRecord::findRealocObject(m_item.m_oldID, a_realocMap, a_realocNextMap);
			}
			
			if (m_item.m_pOld.lock())
			{
				m_pContainer.lock()->undoRedo_InsertObject(m_item.m_pOld.lock(), m_item.m_index);
			}
			else
			{
				// log
				MCadLogger::Instance() << LogMode::LOG_ERROR << std::source_location::current() << "no realoc pointer";
			}
		}
		else
		{
			// log
			MCadLogger::Instance() << LogMode::LOG_ERROR << std::source_location::current() << "no realoc pointer";
		}
		break;

	case IMCadRecord::RecordAction::Record_changed:
		break;

	default:
		break;
	}
}

bool MCadIndexedContainerRecord::itemWillDeleted()const
{
	bool bRet = false;
	if (m_pContainer.lock())
		return m_pContainer.lock()->itemRefCount(m_item.m_index) == 1;
	return bRet;
}

/*@brief apply filter on record*/
bool MCadIndexedContainerRecord::invokeFilter(RecordFilter& filter)const
{
	//
	return true;
}

void MCadIndexedContainerRecord::genReverseRecord(IMCadRecordVisitor& a_visitor, std::list<IMCadRecordPtr>& a_recList)const
{
	a_visitor.genRedoRecord(this, a_recList);
}