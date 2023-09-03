#include "pch.h"
#include "MCadRealocMemory.h"
#include "MCadObject.h"


MCadShared_ptr<MCadObject> MCadRealocMemory::realoc(const ObjectUID& a_uid, const std::weak_ptr<RTTIDefinition>& a_objectDef)
{
	MCadShared_ptr<MCadObject> pRealocObject;
	auto iter = m_undoRedoRealoc.find(a_uid);
	if (iter != m_undoRedoRealoc.end())
	{
		pRealocObject = iter->second.lock();
		if (!pRealocObject)
			m_undoRedoRealoc.erase(a_uid);
		else
			return pRealocObject;
	}

	if (!pRealocObject && a_objectDef.lock())
	{
		pRealocObject = a_objectDef.lock()->create(a_uid);
		m_undoRedoRealoc.try_emplace(a_uid, pRealocObject);
		m_sessionRealoc.try_emplace(a_uid, pRealocObject);
	}
	else
	{
		// log
	}
	return pRealocObject;
}

MCadShared_ptr<MCadObject> MCadRealocMemory::realoc(const ObjectUID& a_uid)
{
	MCadShared_ptr<MCadObject> pRealocObject;
	auto iter = m_undoRedoRealoc.find(a_uid);
	if (iter != m_undoRedoRealoc.end())
	{
		pRealocObject = iter->second.lock();
		if (!pRealocObject)
			m_undoRedoRealoc.erase(a_uid);
	}

	return pRealocObject;
}


void MCadRealocMemory::endSession()
{
	m_sessionRealoc.clear();
}