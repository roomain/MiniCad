#pragma once
/***********************************************
* @headerfile IMCadRecord.h
* @date 05 / 09 / 2023
* @author Roomain
************************************************/
#include <memory>
#include "MCadRefObject.h"
#include "MCadCell.h"

class IMCadRecord;
using IMCadRecordPtr = std::shared_ptr<IMCadRecord>;

template<typename Key, typename ContainerLnk>
class TMCadRecordContainerInsert;

template<typename Key, typename ContainerLnk>
class TMCadRecordContainerRemoved;


template<typename Key, typename ContainerLnk>
class TMCadRecordContainerChanged;

/*@brief base class for container having undo redo capabililty*/
template<typename Key, typename Type>
class TIMCadContainer : public MCadObject, public MCadRefObject<TIMCadContainer<Key>>
{
	template<typename ContainerLnk>
	friend class TMCadRecordContainerInsert<Key, ContainerLnk>;

	template<typename ContainerLnk>
	friend class TMCadRecordContainerRemoved<Key, ContainerLnk>;

	template<typename ContainerLnk>
	friend class TMCadRecordContainerChanged<Key, ContainerLnk>;

protected:
	/*@brief replace container item during record processing (=> undo/redo)*/
	virtual void do_replace(const size_t& a_key, const IMCadRecordPtr& a_record) = 0;
	/*@brief insert container item during record processing (=> undo/redo)*/
	virtual void do_insert(const Key& a_key, const IMCadRecordPtr& a_record) = 0;
	/*@brief erase container item during record processing (=> undo/redo)*/
	virtual void do_eraseAt(const Key& a_key) = 0;

	//-------------------------------------------------------------------------------------
    void assert_ItemInsert(const MShared_ptr<Type>& a_pItem, const size_t a_index)
    {
        if ( auto pDoc = document( ).lock( ) )
        {
            if ( pDoc->undoRedo( ).active( ) )
            {
                auto& session = pDoc->undoRedo( ).currentSession( );
                if ( isShared( ) )
                {
                    //
                }
                else
                {
                    //
                }
                // TODO
                //session.append(std::make_shared<TMCadRecordContainerInsert>(a_object, session.outputStream( )));
            }
        }
    }

    void assert_ItemRemoved(const MShared_ptr<Type>& a_pItem, const size_t a_index)
    {
        if ( auto pDoc = document( ).lock( ) )
        {
            if ( pDoc->undoRedo( ).active( ) )
            {
                auto& session = pDoc->undoRedo( ).currentSession( );
                if ( isShared( ) )
                {
                    //
                }
                else
                {
                    //
                }
                //session.append(std::make_shared<TMCadRecordContainerInsert>(a_object, session.outputStream( )));
            }
        }
    }

    void assert_ItemChanged(const MCadCell<Type>* a_pCell, const MShared_ptr<Type>& a_pBefore, const MShared_ptr<Type>& a_pAfter)
    {
        if ( auto pDoc = document( ).lock( ) )
        {
            if ( pDoc->undoRedo( ).active( ) )
            {
                auto& session = pDoc->undoRedo( ).currentSession( );
                if ( isShared( ) )
                {
                    //
                }
                else
                {
                    //
                }
                //session.append(std::make_shared<TMCadRecordContainerInsert>(a_object, session.outputStream( )));
            }
        }
    }

};