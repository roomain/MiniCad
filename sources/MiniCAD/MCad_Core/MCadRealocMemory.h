#pragma once
/***********************************************
* @headerfile MCadRealocMemory.h
* @date 02 / 09 / 2023
* @author Roomain
************************************************/
#include <unordered_map>
#include "MCadMemory.h"
#include "Defines.h"
#include "RTTIDefinition.h"

#pragma warning(push)
#pragma warning(disable : 4251)

class MCadObject;

using RealocMap = std::unordered_map<ObjectUID, MCadShared_ptr<MCadObject>>;
using RealocWMap = std::unordered_map<ObjectUID, std::weak_ptr<MCadObject>>;

/*@brief realocation memory object*/
class MCadRealocMemory
{
private:
	RealocWMap m_undoRedoRealoc;	/*!< realocated pointer for all sessions*/
	RealocMap m_sessionRealoc;		/*!< realocated pointer for session*/

public:
	MCadRealocMemory() = default;
	MCadShared_ptr<MCadObject> realoc(const ObjectUID& a_uid);
	MCadShared_ptr<MCadObject> realoc(const ObjectUID& a_uid, const std::weak_ptr<RTTIDefinition>& a_objectDef);
	void endSession();
};

#pragma warning(pop)