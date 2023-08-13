#include "pch.h"
#include "MCadObjectRecord.h"

MCadObjectRecord::MCadObjectRecord(const RecordAction a_action, MCadObjectWPtr a_pObject,
	const size_t& a_offset, const size_t& a_size) :
	IMCadRecord(a_action, a_pObject.lock()->uid()), m_dataOffset{a_offset}, m_dataSize{a_size}, m_pObject{a_pObject},
	m_objDef{ a_pObject.lock()->isA() }
{
}

void MCadObjectRecord::process(ObjectRealocMap& a_realocMap, ObjectNextRealocMap& a_realocNextMap, MCadInputBinStream& a_inputStream)
{
	switch (m_action)
	{

	case IMCadRecord::RecordAction::Record_delete:
		// recreate object
		if (m_objDef.lock())
		{
			a_realocMap[m_objectID] = m_objDef.lock()->create(m_objectID);
			a_inputStream.setPos(m_dataOffset);
			a_realocMap[m_objectID]->load(a_inputStream);
			a_realocNextMap.emplace(m_objectID, a_realocMap[m_objectID]);
		}
		break;

	case IMCadRecord::RecordAction::Record_modify:	
		// unmodify
		if (!m_pObject.lock())
			m_pObject = IMCadRecord::findRealocObject(m_objectID, a_realocMap, a_realocNextMap);

		if (!m_pObject.lock())
		{
			a_inputStream.setPos(m_dataOffset);
			m_pObject.lock()->load(a_inputStream);
		}
		else
		{
			// log
			MCadLogger::Instance() << LogMode::LOG_ERROR << std::source_location::current() << "no realoc pointer";
		}
		break;

	case IMCadRecord::RecordAction::Record_create:
		// erase object
		a_realocMap.erase(m_objectID);
		a_realocNextMap.erase(m_objectID);
		break;

	default:
		break;
	}
}


bool MCadObjectRecord::invokeFilter(RecordFilter& filter)const
{
	//
	return true;
}
std::unique_ptr<IMCadRecord> MCadObjectRecord::genReverseRecord(IMCadRecordVisitor& a_visitor)const
{
	return a_visitor.genRedoRecord(this);
}