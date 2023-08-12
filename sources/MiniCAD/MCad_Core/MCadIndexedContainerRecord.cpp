#include "pch.h"
#include "MCadIndexedContainerRecord.h"



MCadIndexedContainerRecord::MCadIndexedContainerRecord(const RecordAction a_action, const IMCadIndexedContainerWPtr& a_pObject, const IndexedItem& a_data) : 
	IMCadRecord(a_action, a_pObject.lock()->uid()), m_item{ a_data }, m_pContainer{ a_pObject }
{
	//
}

void MCadIndexedContainerRecord::process(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream)const
{
	//
}

/*@brief apply filter on record*/
bool MCadIndexedContainerRecord::invokeFilter(RecordFilter& filter)const
{
	//
	return true;
}

std::unique_ptr<IMCadRecord> MCadIndexedContainerRecord::genReverseRecord(IMCadRecordVisitor& a_visitor)const
{
	//
	return nullptr;
}