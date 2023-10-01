#pragma once
/***********************************************
* @headerfile TMCadMap.h
* @date 26 / 09 / 2023
* @author Roomain
************************************************/
#include <map>
#include "MCadMemory.h"
#include "TIMCadContainer.h"
#include "TMCadCell.h"
#include "TMCadRecordContainer.h"

template<typename Key, typename Type> requires std::is_base_of_v<MCadObject, Type>
class TMCadMap : public TIMCadContainer<Key>, private std::map<Key, TMCadCell<Type>>
{
private:
    using MapBase = std::map<Key, TMCadCell<Type>>;
    Assert_ContentChange<Type> m_onChangeContentCallback;   /*!< callback cell contant change*/
    bool m_bActiveCallback = true;                          /*!< callback enable*/

protected:
    void do_replace(const Key& a_key, const MCadObjectPtr& a_object)final
    {
        MapBase::operator[](a_key) = a_object;
    }

    void do_insert(const Key& a_key, const MCadObjectPtr& a_object)final
    {
        MapBase::operator[]( a_key ) = a_object;
    }

    void do_eraseAt(const Key& a_index) final
    {
        MapBase::remove(a_index);
    }

    void assert_ItemChanged(const TMCadCell<Type>* a_pCell, const MCadShared_ptr<Type>& a_pBefore, const MCadShared_ptr<Type>& a_pAfter)
    {
        if ( auto pDoc = document().lock() )
        {
            if ( pDoc->undoRedo( ).active( ) )
            {
                auto& session = pDoc->undoRedo( ).currentSession( );
                auto iter = find(*a_pCell);// or create TMCadCell with key
                // TODO Special record using find when undo/redo?
                session.append(std::make_shared<TMCadRecordContainerChanged<Key>>(this, iter.first, a_pBefore, a_pAfter));
            }
        }
    }
    template< class... Args >
    TMCadCell<Type> createWithoutRecord(Args&&... args)
    {
        if ( auto pDoc = document( ).lock( ) )
        {
            //
        }
        else
        {
            //
        }
    }

public:
    TMCadMap( )
    {
        // TODO
    }


    /*using iterator = std::map<Key, TMCadCell<Type>::iterator;
    using const_iterator = std::map<Key, TMCadCell<Type>::const_iterator;

    template< class... Args >
    std::pair<iterator, bool> try_emplace(const Key& k, Args&&... args)
    {        
        // 
    }
        
    template< class... Args >
    std::pair<iterator, bool> try_emplace(Key&& k, Args&&... args)
    {
        //
    }
        
    template< class... Args >
    iterator try_emplace(const_iterator hint, const Key& k, Args&&... args)
    {
        //
    }
        
    template< class... Args >
    iterator try_emplace(const_iterator hint, Key&& k, Args&&... args)
    {
        //
    }*/

    using std::map<Key, TMCadCell<Type>>::operator[];

    using std::map<Key, TMCadCell<Type>>::at;
    using std::map<Key, TMCadCell<Type>>::begin;
    using std::map<Key, TMCadCell<Type>>::end;
    using std::map<Key, TMCadCell<Type>>::cbegin;
    using std::map<Key, TMCadCell<Type>>::cend;
    using std::map<Key, TMCadCell<Type>>::rbegin;
    using std::map<Key, TMCadCell<Type>>::rend;
    using std::map<Key, TMCadCell<Type>>::crbegin;
    using std::map<Key, TMCadCell<Type>>::crend;

    using std::map<Key, TMCadCell<Type>>::size;
    using std::map<Key, TMCadCell<Type>>::max_size;
    using std::map<Key, TMCadCell<Type>>::empty;
};