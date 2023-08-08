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


/*@brief interface for MCad indexed containers */
template<typename Contained> requires std::is_base_of_v<MCadObject, Contained>
class IMCadIndexedContainer : public MCadObject
{
	DECLARE_RTTI_DERIVED(1, IMCadIndexedContainer<Contained>, MCadObject)
protected:
	/*@brief function used in undo/redo*/
	virtual void undoRedo_RemoveObject(const size_t& a_index) = 0;
	virtual void undoRedo_InsertObject(std::shared_ptr<MCadObject>& a_object, const size_t& a_index) = 0;
};
