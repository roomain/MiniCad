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

#pragma warning(push)
#pragma warning(disable : 4251)

class MCadObject;
class MCadObjectUID;

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
	void endSession();
};

#pragma warning(pop)