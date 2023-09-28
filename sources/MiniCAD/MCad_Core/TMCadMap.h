#pragma once
/***********************************************
* @headerfile TMCadMap.h
* @date 26 / 09 / 2023
* @author Roomain
************************************************/
#include <map>
#include "MCadMemory.h"
#include "TIMCadContainer.h"
#include "MCadCell.h"
#include "TMCadRecordContainer.h"

template<typename Key, typename Type> requires std::is_base_of_v<MCadObject, Type>
class TMCadMap : public TIMCadContainer<size_t>, private std::map<Key, MCadCell<Type>>
{
    DECLARE_RTTI_DERIVED(1, TMCadMap<Key, Type>, MCadObject)
private:
    using MapBase = std::map<Key, MCadCell<Type>>;
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

    void assert_ItemChanged(const MCadCell<Type>* a_pCell, const MCadShared_ptr<Type>& a_pBefore, const MCadShared_ptr<Type>& a_pAfter)
    {
        if ( auto pDoc = document().lock() )
        {
            if ( pDoc->undoRedo( ).active( ) )
            {
                auto& session = pDoc->undoRedo( ).currentSession( );
                //session.append(std::make_shared<TMCadRecordContainerChanged<Key>>(this, a_pCell - MapBase::data( ), a_pBefore, a_pAfter));
            }
        }
    }
public:
    TMCadMap( )
    {
        // TODO
    }

    using std::map<Key, MCadCell<Type>>::operator [];
    using std::map<Key, MCadCell<Type>>::at;
    using std::map<Key, MCadCell<Type>>::begin;
    using std::map<Key, MCadCell<Type>>::end;
    using std::map<Key, MCadCell<Type>>::cbegin;
    using std::map<Key, MCadCell<Type>>::cend;
    using std::map<Key, MCadCell<Type>>::rbegin;
    using std::map<Key, MCadCell<Type>>::rend;
    using std::map<Key, MCadCell<Type>>::crbegin;
    using std::map<Key, MCadCell<Type>>::crend;

    using std::map<Key, MCadCell<Type>>::size;
    using std::map<Key, MCadCell<Type>>::max_size;
    using std::map<Key, MCadCell<Type>>::empty;
};