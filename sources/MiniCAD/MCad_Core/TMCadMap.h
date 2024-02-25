#pragma once
/***********************************************
* @headerfile TMCadMap.h
* @date 28 / 01 / 2024
* @author Roomain
************************************************/
#include <map>
#include <ranges>
#include "MCad_traits.h"
#include "MCadRef.h"
#include "TMCadMapRecords.h"

namespace UndoRedo
{

    template<typename Key, typename Type, class Compare>  requires ( is_MCadShared_base_of<MCadObject, Type>::value )
        class TMCadMap : public MCadRefObject, private std::map<Key, Type, Compare>
    {
    private:
        using MapBase = std::map<Key, Type, Compare>;

        // callback called if item changes
        void assertChange(const Type* a_object)
        {
            if ( auto pDoc = MCadDocumentManager::Instance( ).currentDocument( ).lock( ) )
            {
                if ( pDoc->undoRedo( ).active( ) )
                {
                    // TODO
                }
            }
        }

        void assertInsert(const Type& a_object, const Key& a_key)
        {
            if ( auto pDoc = a_object->document( ).lock( ) )
            {
                if ( pDoc->undoRedo( ).active( ) )
                {
                    // TODO
                }
            }
        }

        void assertErase(const Type& a_object, const Key& a_key)
        {
            if ( auto pDoc = a_object->document( ).lock( ) )
            {
                if ( pDoc->undoRedo( ).active( ) )
                {
                    // TODO
                }
            }
        }

    public:
        //
        using iterator = std::map <Key, Type, Compare>::iterator;
        using const_iterator = std::map < Key, Type, Compare>::const_iterator;

        template< class... Args >
        std::pair<iterator, bool> try_emplace(const Key& a_key, Args&&... args)
        {
            //
            return MapBase::try_emplace(a_key, args);
        }

        template< class... Args >
        std::pair<iterator, bool> try_emplace(Key&& a_key, Args&&... args)
        {
            //
            return MapBase::try_emplace(a_key, args);
        }

        template< class... Args >
        std::pair<iterator, bool> emplace(const Key& a_key, Args&&... args)
        {
            //
            return MapBase::emplace(a_key, args);
        }

        template< class... Args >
        std::pair<iterator, bool> emplace(Key&& a_key, Args&&... args)
        {
            //
            return MapBase::emplace(a_key, args);
        }

        iterator erase(iterator a_pos)
        {
            //
            return MapBase::erase(a_pos);
        }

        iterator erase(const_iterator a_pos)
        {
            //
            return MapBase::erase(a_pos);
        }

        iterator erase(const_iterator a_first, const_iterator a_last)
        {
            //
            return MapBase::erase(a_first, a_last);
        }

        size_t erase(const Key& a_key)
        {
            //
            return MapBase::erase(a_key);
        }

        using std::map<Key, Type, Compare>::operator [];
        using std::map<Key, Type, Compare>::at;
        using std::map<Key, Type, Compare>::begin;
        using std::map<Key, Type, Compare>::end;
        using std::map<Key, Type, Compare>::cbegin;
        using std::map<Key, Type, Compare>::cend;
        using std::map<Key, Type, Compare>::rbegin;
        using std::map<Key, Type, Compare>::rend;
        using std::map<Key, Type, Compare>::crbegin;
        using std::map<Key, Type, Compare>::crend;

        using std::map<Key, Type, Compare>::size;
        using std::map<Key, Type, Compare>::max_size;
        using std::map<Key, Type, Compare>::empty;
    };

}