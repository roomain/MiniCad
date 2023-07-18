#pragma once
/***********************************************
* @headerfile IMCadObjectReactor.h
* @date 16 / 07 / 2023
* @author Roomain
************************************************/
#include "RTTIDefinition_macros.h"

class MCadObject;

/*@brief provide interface for object reactor*/
class IMCadObjectReactor
{
	DECLARE_RTTI(1, IMCadObjectReactor)
public:
	IMCadObjectReactor() = default;
	virtual ~IMCadObjectReactor() = default;

	/*@brief called when target object is modified*/
	virtual void onObjectModified(MCadObject* const a_pObject) = 0;
	/*@brief called when target object is modification are undone*/
	virtual void onObjectRestored(MCadObject* const a_pObject) = 0;
	/*@brief called when target object is deleted*/
	virtual void onObjectDeleted(MCadObject* const a_pObject) = 0;
	/*@brief called when target object is erased*/
	virtual void onObjectErased(MCadObject* const a_pObject) = 0;
	/*@brief called when target object owner has changed*/
	virtual void onOwnerChanged(MCadObject* const a_pObject, MCadObject* const a_pOldOwner, MCadObject* const a_pNewOwner) = 0;
	/*@brief is active*/
	virtual void enabled()const noexcept = 0;
};

using IMCadObjectReactorPtr = std::shared_ptr<IMCadObjectReactor>;