#pragma once
/***********************************************
* @headerfile IMCadRecord.h
* @date 05 / 09 / 2023
* @author Roomain
************************************************/
#include <memory>
#include "MCadRef.h"
#include "MCadCell.h"

class IMCadRecord;
using IMCadRecordPtr = std::shared_ptr<IMCadRecord>;

template<typename Key>
class TMCadRecordContainerInsert;

template<typename Key>
class TMCadRecordContainerRemoved;


template<typename Key>
class TMCadRecordContainerChanged;

/*@brief base class for container having undo redo capabililty*/
template<typename Key, typename Type>
class TIMCadContainer : public MCadObject
{
	template<typename Key>
	friend class TMCadRecordContainerInsert<Key>;

	template<typename Key>
	friend class TMCadRecordContainerRemoved<Key>;

	template<typename Key>
	friend class TMCadRecordContainerChanged<Key>;

protected:
	/*@brief replace container item during record processing (=> undo/redo)*/
	virtual void do_replace(const Key& a_key, const IMCadRecordPtr& a_record) = 0;
	/*@brief insert container item during record processing (=> undo/redo)*/
	virtual void do_insert(const Key& a_key, const IMCadRecordPtr& a_record) = 0;
	/*@brief erase container item during record processing (=> undo/redo)*/
	virtual void do_eraseAt(const Key& a_key) = 0;

	//-------------------------------------------------------------------------------------
    void assert_ItemInsert(const MShared_ptr<Type>& a_pItem, const Key& a_index)
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

    void assert_ItemRemoved(const MShared_ptr<Type>& a_pItem, const Key a_index)
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

    void assert_ItemChanged(const MCadCell<Type>* a_pCell, const MShared_ptr<Type>& a_pBefore, const MShared_ptr<Type>& a_pAfter, const Key a_index)
    {
        if ( auto pDoc = document( ).lock( ) )
        {
            if ( pDoc->undoRedo( ).active( ) )
            {
                auto& session = pDoc->undoRedo( ).currentSession( );
                session.append(std::make_shared<TMCadRecordContainerRemoved<Key>>(this, a_index, a_pBefore, a_pAfter));
            }
        }
    }

};