#pragma once
/***********************************************
* @headerfile MCadReallocMemory.h
* @date 02 / 09 / 2023
* @author Roomain
************************************************/
#include <unordered_map>
#include "MCadMemory.h"
#include "defines.h"
#include "RTTIDefinition.h"
#include "MCad_Core_globals.h"
#include "MCadObject.h"
#include "MCadObjectUID.h"

#pragma warning(push)
#pragma warning(disable : 4251)

using ReallocMap = std::unordered_map<ObjectUID, MCadShared_ptr<MCadObject>>;
using ReallocWMap = std::unordered_map<ObjectUID, std::weak_ptr<MCadObject>>;

/*@brief realocation memory object*/
class MCAD_CORE_EXPORT MCadReallocMemory
{
private:
	ReallocWMap m_undoRedoRealloc;	/*!< realocated pointer for all sessions*/
	ReallocMap m_sessionRealoc;		/*!< realocated pointer for session*/

public:
	MCadReallocMemory() = default;
	MCadShared_ptr<MCadObject> realloc(MCadObjectUID& a_objUID);
	MCadShared_ptr<MCadObject> realloc(MCadObjectUID& a_objUID, const std::weak_ptr<RTTIDefinition>& a_objectDef);

	template<typename Type>
	void realloc(MCadShared_ptr<Type>& pCastType, MCadObjectUID& a_objUID)
	{
		if ( a_objUID.noReference( ) )
			return;

		auto pTemp = realloc(a_objUID);
		pCastType = MCadShared_ptr<Type>(std::dynamic_pointer_cast< Type >( pTemp ));//->cast<Type>( ));
	}

	template<typename Type>
	void realloc(MCadShared_ptr<Type>& pCastType,  MCadObjectUID& a_objUID, const std::weak_ptr<RTTIDefinition>& a_objectDef)
	{
		if ( a_objUID.noReference( ) )
			return;

		auto pTemp = realloc(a_objUID,a_objectDef);
		pCastType = MCadShared_ptr<Type>(std::dynamic_pointer_cast< Type >( pTemp ));// ->cast<Type>( ));
	}

	void endSession();
};

#pragma warning(pop)