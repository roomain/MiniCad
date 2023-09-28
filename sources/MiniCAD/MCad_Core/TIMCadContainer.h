#pragma once
/***********************************************
* @headerfile IMCadRecord.h
* @date 05 / 09 / 2023
* @author Roomain
************************************************/
#include <memory>
#include "MCadRef.h"
#include "TMCadCell.h"

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
class TIMCadContainer : public MCadObject
{
	template<typename Key>
	friend class TMCadRecordContainerInsert;

	template<typename Key>
	friend class TMCadRecordContainerRemoved;

	template<typename Key>
	friend class TMCadRecordContainerChanged;

protected:
	/*@brief replace container item during record processing (=> undo/redo)*/
	virtual void do_replace(const Key& a_key, const MCadObjectPtr& a_record) = 0;
	/*@brief insert container item during record processing (=> undo/redo)*/
	virtual void do_insert(const Key& a_key, const MCadObjectPtr& a_record) = 0;
	/*@brief erase container item during record processing (=> undo/redo)*/
	virtual void do_eraseAt(const Key& a_key) = 0;

	//-------------------------------------------------------------------------------------
    template<typename Type>
    void assert_ItemInsert(const MCadShared_ptr<Type>& a_pItem, const Key& a_index)
    {
        if ( auto pDoc = document( ).lock( ) )
        {
            if ( pDoc->undoRedo( ).active( ) )
            {
                auto& session = pDoc->undoRedo( ).currentSession( );
                session.append(std::make_shared<TMCadRecordContainerInsert<Key>>(this, a_index, a_pItem));
            }
        }
    }
    template<typename Type>
    void assert_ItemRemoved(const MCadShared_ptr<Type>& a_pItem, const Key a_index)
    {
        if ( auto pDoc = document( ).lock( ) )
        {
            if ( pDoc->undoRedo( ).active( ) )
            {
                auto& session = pDoc->undoRedo( ).currentSession( );
                session.append(std::make_shared<TMCadRecordContainerRemoved<Key>>(this, a_index, a_pItem));
            }
        }
    }
    

};