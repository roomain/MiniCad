#pragma once
/***********************************************
* @headerfile IMCadRecord.h
* @date 05 / 09 / 2023
* @author Roomain
************************************************/
#include <memory>
#include "MCadReferencedObject.h"

class IMCadRecord;
using IMCadRecordPtr = std::shared_ptr<IMCadRecord>;

template<typename Key>
class TMCadRecordContainerInsert;

template<typename Key>
class TMCadRecordContainerRemoved;


template<typename Key>
class TMCadRecordContainerChanged;

/*@brief base class for container having undo redo capabililty*/
template<typename Key>
class TIMCadContainer : public MCadReferencedObject<TIMCadContainer<Key>>
{
	friend class TMCadRecordContainerInsert<Key>;
	friend class TMCadRecordContainerRemoved<Key>;
	friend class TMCadRecordContainerChanged<Key>;

protected:
	/*@brief replace container item during record processing (=> undo/redo)*/
	virtual void do_replace(const size_t& a_key, const IMCadRecordPtr& a_record) = 0;
	/*@brief insert container item during record processing (=> undo/redo)*/
	virtual void do_insert(const Key& a_key, const IMCadRecordPtr& a_record) = 0;
	/*@brief erase container item during record processing (=> undo/redo)*/
	virtual void do_eraseAt(const Key& a_key) = 0;
};