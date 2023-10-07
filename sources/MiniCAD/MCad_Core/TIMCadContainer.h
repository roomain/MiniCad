#pragma once
/***********************************************
* @headerfile IMCadRecord.h
* @date 05 / 09 / 2023
* @author Roomain
************************************************/
#include <memory>
#include "MCadRef.h"
#include "TMCadCell.h"
#include "MCadObject.h"
#include "MCadDocument.h"

class IMCadRecord;
using IMCadRecordPtr = std::shared_ptr<IMCadRecord>;

template<typename Key>
class TMCadRecordContainerCellInsert;

template<typename Key>
class TMCadRecordContainerCellRemoved;


template<typename Key>
class TMCadRecordContainerCellChanged;


template<typename Key>
class TMCadRecordContainerEmptyCellInsert;

template<typename Key>
class TMCadRecordContainerEmptyCellRemoved;


template<typename Key>
class TMCadRecordContainerEmptyCellChanged;

template<typename Key>
class TMCadRecordContainerToEmptyCellChanged;

/*@brief base class for container having undo redo capabililty*/
template<typename Key>
class TIMCadContainer : public MCadRefObject
{
    template<typename Key>
	friend class TMCadRecordContainerCellInsert;

    template<typename Key>
	friend class TMCadRecordContainerCellRemoved;

    template<typename Key>
	friend class TMCadRecordContainerCellChanged;

    template<typename Key>
    friend class TMCadRecordContainerEmptyCellInsert;

    template<typename Key>
    friend class TMCadRecordContainerEmptyCellRemoved;

    template<typename Key>
    friend class TMCadRecordContainerEmptyCellChanged;

    template<typename Key>
    friend class TMCadRecordContainerToEmptyCellChanged;

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
        if ( auto pDoc = a_pItem->document( ).lock( ) )
        {
            if ( pDoc->undoRedo( ).active( ) )
            {
                auto& session = pDoc->undoRedo( ).currentSession( );
                if ( a_pItem )
                {
                    session.append(std::make_shared<TMCadRecordContainerCellInsert<Key>>(this, a_index, a_pItem));
                }
                else
                {
                    session.append(std::make_shared<TMCadRecordContainerEmptyCellInsert<Key>>(this, a_index));
                }
            }
        }
    }
    
    template<typename Type>
    void assert_ItemRemoved(const MCadShared_ptr<Type>& a_pItem, const Key a_index)
    {
        if ( auto pDoc = a_pItem->document( ).lock( ) )
        {
            if ( pDoc->undoRedo( ).active( ) )
            {
                auto& session = pDoc->undoRedo( ).currentSession( );
                if ( a_pItem )
                {
                    session.append(std::make_shared<TMCadRecordContainerCellRemoved<Key>>(this, a_index, a_pItem));
                }
                else
                {
                    session.append(std::make_shared<TMCadRecordContainerEmptyCellRemoved<Key>>(this, a_index));
                }
            }
        }
    }
    
};