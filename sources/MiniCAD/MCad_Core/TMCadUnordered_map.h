#pragma once
/***********************************************
* @headerfile TMCadUnordered_map.h
* @date 28 / 01 / 2024
* @author Roomain
************************************************/
#include <unordered_map>
#include <ranges>
#include "MCad_traits.h"
#include "MCadRef.h"
#include "TMCadUnordered_mapRecords.h"

namespace UndoRedo
{
    template<typename Key, typename Type> requires ( is_MCadShared_base_of<MCadObject, Type>::value )
        class TMCadUnordered_map : public MCadRefObject, private std::unordered_map<Key, Type>
    {
    private:
        using unordered_mapBase = std::unordered_map<Key, Type>;

        // callback called if item changes
        void assertChange(const Type* a_object)
        {
            if ( auto pDoc = MCadDocumentManager::Instance( ).currentDocument( ).lock( ) )
            {
                if ( pDoc->undoRedo( ).active( ) )
                {
                    auto& session = pDoc->undoRedo( ).currentSession( );
                    auto iter = std::ranges::find_if(*this, [ a_object ] (const auto& a_iter)
                       {
                          return a_object == &a_iter.second;
                       });

                    if ( iter != cend( ) )
                        session.append(std::make_shared<TMCadUnordered_mapChangeRecord<Key, Type>>(make_ref(*this), iter.first, (*a_object) ? (*a_object)->objectUID( ) : MCadObjectUID( ), a_object->objectDef( )));
                }
            }
        }

        void assertInsert(const Type& a_object, const Key& a_key)
        {
            if ( auto pDoc = a_object->document( ).lock( ) )
            {
                if ( pDoc->undoRedo( ).active( ) )
                {
                    a_object->setCallback(std::bind_front(&TMCadVector<Type>::assertChange, this, a_key));
                    auto& session = pDoc->undoRedo( ).currentSession( );
                    //session.append(std::make_shared<TMCadVectorInsertRecord<Type>>(make_ref(*this), a_key, a_object->objectUID( )));
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
        using iterator = std::unordered_map <Key, Type, Compare>::iterator;
        using const_iterator = std::unordered_map < Key, Type, Compare>::const_iterator;

        template< class... Args >
        std::pair<iterator, bool> try_emplace(const Key& a_key, Args&&... args)
        {
            //
            return unordered_mapBase::try_emplace(a_key, args);
        }

        template< class... Args >
        std::pair<iterator, bool> try_emplace(Key&& a_key, Args&&... args)
        {
            //
            return unordered_mapBase::try_emplace(a_key, args);
        }

        template< class... Args >
        std::pair<iterator, bool> emplace(const Key& a_key, Args&&... args)
        {
            //
            return unordered_mapBase::emplace(a_key, args);
        }

        template< class... Args >
        std::pair<iterator, bool> emplace(Key&& a_key, Args&&... args)
        {
            //
            return unordered_mapBase::emplace(a_key, args);
        }

        iterator erase(iterator a_pos)
        {
            //
            return unordered_mapBase::erase(a_pos);
        }

        iterator erase(const_iterator a_pos)
        {
            //
            return unordered_mapBase::erase(a_pos);
        }

        iterator erase(const_iterator a_first, const_iterator a_last)
        {
            //
            return unordered_mapBase::erase(a_first, a_last);
        }

        size_t erase(const Key& a_key)
        {
            //
            return unordered_mapBase::erase(a_key);
        }

        using std::unordered_map<Key, Type, Compare>::operator [];
        using std::unordered_map<Key, Type, Compare>::at;
        using std::unordered_map<Key, Type, Compare>::begin;
        using std::unordered_map<Key, Type, Compare>::end;
        using std::unordered_map<Key, Type, Compare>::cbegin;
        using std::unordered_map<Key, Type, Compare>::cend;
        using std::unordered_map<Key, Type, Compare>::rbegin;
        using std::unordered_map<Key, Type, Compare>::rend;
        using std::unordered_map<Key, Type, Compare>::crbegin;
        using std::unordered_map<Key, Type, Compare>::crend;

        using std::unordered_map<Key, Type, Compare>::size;
        using std::unordered_map<Key, Type, Compare>::max_size;
        using std::unordered_map<Key, Type, Compare>::empty;
    };

}