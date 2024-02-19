#include "pch.h"
#include "MCadReallocMemory.h"
#include "MCadObject.h"
#include "MCadObjectUID.h"


MCadShared_ptr<MCadObject> MCadReallocMemory::realloc(MCadObjectUID& a_objUID)
{
	if ( a_objUID.isValid( ) )
		return a_objUID.open<MCadObject>( );

	MCadShared_ptr<MCadObject> pReallocObject;
	auto iter = m_undoRedoRealloc.find(a_objUID.m_uniqueId);
	if ( iter != m_undoRedoRealloc.end( ) )
	{
		pReallocObject = iter->second.lock( );
		if ( !pReallocObject )
		{
			m_undoRedoRealloc.erase(a_objUID.m_uniqueId);
		}
		else
		{
			a_objUID.m_object = pReallocObject;
		}
	}

	return pReallocObject;
}

MCadShared_ptr<MCadObject> MCadReallocMemory::realloc(MCadObjectUID& a_objUID, const std::weak_ptr<RTTIDefinition>& a_objectDef)
{
	if ( a_objUID.isValid( ) )
		return a_objUID.open<MCadObject>( );

	MCadShared_ptr<MCadObject> pReallocObject = realloc(a_objUID);

	if (!pReallocObject)
	{
		pReallocObject = a_objectDef.lock()->create(a_objUID.m_uniqueId);
		m_undoRedoRealloc.try_emplace(a_objUID.m_uniqueId, pReallocObject);
		m_sessionRealoc.try_emplace(a_objUID.m_uniqueId, pReallocObject);
		a_objUID.m_object = pReallocObject;
	}
	else
	{
		// log
	}
	return pReallocObject;
}

void MCadReallocMemory::endSession()
{
	m_sessionRealoc.clear();
}