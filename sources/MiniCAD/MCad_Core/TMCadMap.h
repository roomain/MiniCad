#pragma once
/***********************************************
* @headerfile TMCadMap.h
* @date 26 / 09 / 2023
* @author Roomain
************************************************/
#include <map>
#include "MCadMemory.h"
#include "TIMCadContainer.h"
#include "TMCadKeyCell.h"
#include "TMCadRecordContainerEmptyCell.h"

template<typename Key, typename Type,
    class Compare = std::less<Key>> requires std::is_base_of_v<MCadObject, Type>
class TMCadMap : public TIMCadContainer<Key>, private std::map<Key, TMCadKeyCell<Key, Type>, Compare>
{
private:
    using MapBase = std::map<Key, TMCadKeyCell<Key, Type>, Compare>;
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

    void assert_EmptyItemInsert(const Key& a_index)
    {
        if ( auto pDoc = document( ).lock( ) )
        {
            if ( pDoc->undoRedo( ).active( ) )
            {
                auto& session = pDoc->undoRedo( ).currentSession( );
                session.append(std::make_shared<TMCadRecordContainerEmptyCellInsert<Key>>(this, a_index));
            }
        }
    }

    void assert_EmptyItemRemoved(const Key& a_index)
    {
        if ( auto pDoc = document( ).lock( ) )
        {
            if ( pDoc->undoRedo( ).active( ) )
            {
                auto& session = pDoc->undoRedo( ).currentSession( );
                session.append(std::make_shared<TMCadRecordContainerEmptyCellRemoved<Key>>(this, a_index));
            }
        }
    }

    void assert_ItemChanged(const TMCadKeyCell<Key, Type>* a_pItem, const MShared_ptr<Type>& a_pBefore, const MShared_ptr<Type>& a_pAfter)
    {
        if ( auto pDoc = document( ).lock( ) )
        {
            if ( pDoc->undoRedo( ).active( ) )
            {
                auto& session = pDoc->undoRedo( ).currentSession( );
               if ( a_pBefore )
                {
                    curSession.addRecord(std::make_shared<TMCadRecordContainerCellChanged<Key>>(TRecordObjectProxy<TIContainer<Key>>(this),
                        a_pItem->key( ),
                        a_pAfter, a_pBefore));
                }
                else
                {
                    curSession.addRecord(std::make_shared<TMCadRecordContainerEmptyCellChanged<Key>>(TRecordObjectProxy<TIContainer<Key>>(this),
                        a_pItem->key( ),
                        a_pAfter));
                }
            }
        }
    }
public:
    TMCadMap( )
    {
        m_onChangeContentCallback = std::bind_front(&TMCadMap<Key, Type, Compare>::assert_ItemChanged, this);
    }


    using iterator = std::map <Key, TMCadKeyCell<Key, Type>, Compare>::iterator;
    using const_iterator = std::map < Key, TMCadKeyCell<Key, Type>, Compare>::const_iterator;

    template< class... Args >
    std::pair<iterator, bool> try_emplace(const Key& a_key, Args&&... args)
    {
        auto [iter, ok] = MapBase::try_emplace(a_key, a_key, m_itemCallback);
        if ( ok )
        {
            if ( *iter )
            {
                // item empty
                this->assert_EmptyCreate(a_key);
            }
            else
            {
                this->assert_ItemAdd(*iter, a_key);
            }
        }
        return pair;
    }

    template< class... Args >
    std::pair<iterator, bool> try_emplace(Key&& a_key, Args&&... args)
    {
        auto [iter, ok] = MapBase::try_emplace(std::move(a_key), a_key, m_itemCallback);
        if ( ok )
        {
            if ( *iter )
            {
                // item empty
                this->assert_EmptyCreate(a_key);
            }
            else
            {
                this->assert_ItemAdd(*iter, a_key);
            }
        }
        return pair;
    }

    template< class... Args >
    std::pair<iterator, bool> emplace(const Key& a_key, Args&&... args)
    {
        auto [iter, ok] = MapBase::emplace(a_key, a_key, m_itemCallback);
        if ( ok )
        {
            if ( *iter )
            {
                // item empty
                this->assert_EmptyCreate(a_key);
            }
            else
            {
                this->assert_ItemAdd(*iter, a_key);
            }
        }
        return pair;
    }

    template< class... Args >
    std::pair<iterator, bool> emplace(Key&& a_key, Args&&... args)
    {
        auto[iter, ok]  = MapBase::emplace(std::move(a_key), a_key, m_itemCallback);
        if ( ok )
        {
            if ( *iter )
            {
                // item empty
                this->assert_EmptyCreate(a_key);
            }
            else
            {
                this->assert_ItemAdd(*iter, a_key);
            }
        }
        return pair;
    }


    TMCadKeyCell<Key, Type>& operator[](const Key& a_key)
    {
        std::pair<iterator, bool> pair = MapBase::try_emplace(a_key, a_key, m_itemCallback);
        if ( pair.second )
        {
            // item empty
            this->assert_EmptyItemInsert(a_key);
        }
        return iter->second;
    }

    iterator erase(iterator a_pos)
    {
        if ( *a_pos.second )
        {
            this->assert_ItemRemoved(*a_pos.second, a_pos.first);
        }
        else
        {
            this->assert_EmptyItemRemoved(a_pos.first);
        }
        return MapBase::erase(a_pos);
    }

    iterator erase(const_iterator a_pos)
    {
        if ( *a_pos.second )
        {
            this->assert_ItemRemoved(*a_pos.second, a_pos.first);
        }
        else
        {
            this->assert_EmptyItemRemoved(a_pos.first);
        }
        return MapBase::erase(a_pos);
    }

    iterator erase(const_iterator a_first, const_iterator a_last)
    {
        std::for_each(a_first, a_last, [ ] (auto a_iterator)
            {
                if ( *a_iterator.second )
                {
                    this->assert_ItemRemoved(*a_iterator.second, a_iterator.first);
                }
                else
                {
                    this->assert_EmptyItemRemoved(a_iterator.first);
                }
            });
        return MapBase::erase(a_first, a_last);
    }

    size_t erase(const Key& a_key)
    {
        auto iter = MapBase::find(a_key);
        if ( iter != end( ) )
        {
            if ( iter->second )
            {
                this->assert_ItemRemoved(iter->second, iter->first);
            }
            else
            {
                this->assert_EmptyItemRemoved(iter->first);
            }
        }
        return MapBase::erase(a_key);
    }

    using std::map<Key, TMCadKeyCell<Key, Type>, Compare>::at;
    using std::map<Key, TMCadKeyCell<Key, Type>, Compare>::begin;
    using std::map<Key, TMCadKeyCell<Key, Type>, Compare>::end;
    using std::map<Key, TMCadKeyCell<Key, Type>, Compare>::cbegin;
    using std::map<Key, TMCadKeyCell<Key, Type>, Compare>::cend;
    using std::map<Key, TMCadKeyCell<Key, Type>, Compare>::rbegin;
    using std::map<Key, TMCadKeyCell<Key, Type>, Compare>::rend;
    using std::map<Key, TMCadKeyCell<Key, Type>, Compare>::crbegin;
    using std::map<Key, TMCadKeyCell<Key, Type>, Compare>::crend;

    using std::map<Key, TMCadKeyCell<Key, Type>, Compare>::size;
    using std::map<Key, TMCadKeyCell<Key, Type>, Compare>::max_size;
    using std::map<Key, TMCadKeyCell<Key, Type>, Compare>::empty;
};