#include "pch.h"
#include "MCadRecordObject.h"

MCadRecordObject::MCadRecordObject(const RecordAction a_action, MCadObjectWPtr a_pObject,
	const size_t& a_offset, const size_t& a_size) :
	IMCadRecord(a_action, a_pObject.lock()->uid()), m_dataOffset{a_offset}, m_dataSize{a_size}, m_pObject{a_pObject},
	m_objDef{ a_pObject.lock()->isA() }
{
}

void MCadRecordObject::process(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream)const
{
	switch (m_action)
	{

	case IMCadRecord::RecordAction::Record_delete:
		// recreate object
		break;

	case IMCadRecord::RecordAction::Record_modify:	
		// unmodify
		break;

	case IMCadRecord::RecordAction::Record_create:
		break;

	default:
		break;
	}
}


bool MCadRecordObject::invokeFilter(RecordFilter& filter)const
{
	//
	return true;
}
std::unique_ptr<IMCadRecord> MCadRecordObject::genReverseRecord(IMCadRecordVisitor& a_visitor)const
{
	//
	return nullptr;
}