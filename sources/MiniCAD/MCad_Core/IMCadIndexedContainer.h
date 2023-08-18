#pragma once
/***********************************************
* @headerfile IMCadIndexedContainer.h
* @date 23 / 07 / 2023
* @author Roomain
************************************************/
#include <type_traits>
#include <functional>
#include <list>
#include "MCadObject.h"
#include "MCad_Core_globals.h"

#pragma warning(push)
#pragma warning(disable : 4251)

class MCadIndexedContainerRecord;

/*@brief interface for MCad indexed containers */
class MCAD_CORE_EXPORT IMCadIndexedContainer : public MCadObject
{
	DECLARE_RTTI_DERIVED(1, IMCadIndexedContainer, MCadObject)
		friend MCadIndexedContainerRecord;
protected:
	virtual unsigned int itemRefCount(const size_t& a_index)const = 0;

	/*@brief assertion object changed*/
	void assertItem(const MCadObjectPtr& a_pBefore, const MCadObjectPtr& a_pAfter, const size_t& a_index);

	/*@brief assertion object added*/
	void assertObjectAdded(const MCadObjectPtr& a_objAdd, const size_t& a_index);

	/*@brief assertion object removed*/
	void assertObjectRemoved(std::shared_ptr<MCadObject>& a_object, const size_t& a_index);

	/*@brief function used in undo/redo*/
	virtual void undoRedo_RemoveObject(const size_t& a_index) = 0;
	virtual void undoRedo_InsertObject(const std::shared_ptr<MCadObject>& a_object, const size_t& a_index) = 0;
};

using IMCadIndexedContainerWPtr = std::weak_ptr<IMCadIndexedContainer>;
#pragma warning(pop)
