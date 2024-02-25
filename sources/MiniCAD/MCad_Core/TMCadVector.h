#pragma once
/***********************************************
* @headerfile TMCadVector.h
* @date 27 / 01 / 2024
* @author Roomain
************************************************/
#include <vector>
#include <ranges>
#include <functional>
#include "MCad_traits.h"
#include "MCadRef.h"
#include "TMCadVectorRecords.h"
#include "MCadDocumentManager.h"

namespace UndoRedo
{
    template<typename Type> requires ( is_MCadShared_base_of<MCadObject, Type>::value )
        class TMCadVector : public MCadRefObject, private std::vector<Type>
    {
    private:
        using VectorBase = std::vector<Type>;

        // callback called if item changes => MCadShared callback
        void assertChange(const Type* a_old)
        {   
            if ( auto pDoc = MCadDocumentManager::Instance().currentDocument( ).lock( ) )
            {
                if ( pDoc->undoRedo( ).active( ) )
                {
                    auto iter = std::ranges::find_if(*this, [ a_old ] (const Type& a_cur)
                        {
                                return a_old == &a_cur;
                        });
                    if ( iter != cend( ) )
                    {
                        const size_t index = std::distance(begin( ), iter);
                        auto& session = pDoc->undoRedo( ).currentSession( );

                        session.append(std::make_shared<TMCadVectorChangeRecord<Type>>(make_ref(*this), index, ( *a_old ) ? ( *a_old )->objectUID( ) : MCadObjectUID( ), a_old->objectDef( )));
                    }
                }
            }
        }

        void assertInsert(Type& a_object, const size_t& a_key)
        {
            if ( auto pDoc = a_object->document( ).lock( ) )
            {
                if ( pDoc->undoRedo( ).active( ) )
                {
                    a_object.setCallback(std::bind_front(&TMCadVector<Type>::assertChange, this));
                    auto& session = pDoc->undoRedo( ).currentSession( );
                    session.append(std::make_shared<TMCadVectorInsertRecord<Type>>(make_ref(*this), a_key, a_object ? a_object->objectUID( ) : MCadObjectUID( ), a_object.objectDef( )));
                }
            }
        }

        void assertErase(const Type& a_object, const size_t& a_key)
        {
            if ( auto pDoc = a_object->document( ).lock( ) )
            {
                if ( pDoc->undoRedo( ).active( ) )
                {
                    auto& session = pDoc->undoRedo( ).currentSession( );
                    session.append(std::make_shared<TMCadVectorEraseRecord<Type>>(make_ref(*this), a_key, a_object ? a_object->objectUID( ) : MCadObjectUID( ), a_object.objectDef( )));
                }
            }
        }

        void sort( )
        {
            // pas de if constexpr car requires
        }

    public:
        TMCadVector( ) = default;

        explicit TMCadVector(const size_t& a_size) : std::vector<Type>(a_size)
        {
            for ( auto& obj : *this )
                obj.setCallback(std::bind_front(&TMCadVector<Type>::assertChange, this));
        }

        ~TMCadVector( )override
        {
            for ( auto& obj : *this )
                obj.setCallback(nullptr);
        }

        void clear( )
        {
            size_t index = 0;
            for ( const auto& obj : *this )
            {
                assertErase(obj, index);
                ++index;
            }
            VectorBase::clear( );
        }

        void sort(const std::function<bool(const Type&, const Type&)>& a_sort)
        {
            //assertSort( );
            std::ranges::sort(*this, a_sort);
        }

        template<typename ...Args>
        TMCadVector<Type>& emplace_back(Args&& ...a_args)
        {
            VectorBase::emplace_back(assertInsert, a_args...);
            assertInsert(VectorBase::back( ), size( ) - 1);
            return *this;
        }

        TMCadVector<Type>& push_back(const Type& a_object)
        {
            VectorBase::emplace_back(a_object);
            assertInsert(VectorBase::back( ), size( ) - 1);
            return *this;
        }

        constexpr TMCadVector<Type>& push_back(Type&& a_object) noexcept
        {
            VectorBase::push_back(a_object);
            assertInsert(VectorBase::back( ), size( ) - 1);
            return *this;
        }

        using std::vector<Type>::operator [];
        using std::vector<Type>::at;
        using std::vector<Type>::begin;
        using std::vector<Type>::end;
        using std::vector<Type>::cbegin;
        using std::vector<Type>::cend;
        using std::vector<Type>::rbegin;
        using std::vector<Type>::rend;
        using std::vector<Type>::crbegin;
        using std::vector<Type>::crend;
        using std::vector<Type>::size;
        using std::vector<Type>::empty;
        //using std::vector<Type>::reserve;

        void reserve(const size_t& a_size)
        {
            for ( auto& obj : *this )
                obj.setCallback(std::bind_front(&TMCadVector<Type>::assertChange, this));
        }

        using iterator = std::vector<Type>::iterator;
        using const_iterator = std::vector<Type>::const_iterator;

        iterator insert(const_iterator a_pos, const Type& a_object)
        {
            auto iter = VectorBase::insert(a_pos, a_object);
            assertInsert(( *iter ), iter - begin( ));
            return iter;
        }

        constexpr iterator insert(const_iterator a_pos, Type&& a_object)
        {
            auto iter = VectorBase::insert(a_pos, a_object);
            assertInsert(( *iter ), std::distance(iter, begin( )));
            return iter;
        }

        template<typename ...Args>
        TMCadVector& emplace(const_iterator a_iter, Args&& ...args)
        {
            VectorBase::emplace(a_iter, args);
            assertInsert(( *a_iter ), std::distance(a_iter, begin( )));
            return *this;
        }

        iterator erase(iterator a_pos)
        {
            assertErase(( *a_pos ), std::distance(a_pos, begin( )));
            auto iter = VectorBase::erase(a_pos);
            return iter;
        }

        constexpr iterator erase(const_iterator a_pos)
        {
            assertErase(( *a_pos ), std::distance(a_pos, cbegin( )));
            auto iter = VectorBase::erase(a_pos);
            return iter;
        }

        iterator erase(iterator  a_first, iterator a_last)
        {
            size_t index = 0;
            std::for_each(a_first, a_last - 1, [ this, &index ] (auto&& a_obj)
                {
                        assertErase(a_obj, index);
                        ++index;
                });
            auto iter = VectorBase::erase(a_first, a_last);
            return iter;
        }

        constexpr iterator erase(const_iterator a_first, const_iterator a_last)
        {
            size_t index = 0;
            std::for_each(a_first, a_last - 1, [ this ] (auto&& a_obj)
                {
                        assertErase(a_obj, index);
                        ++index;
                });
            auto iter = VectorBase::erase(a_first, a_last);
            return iter;
        }

        constexpr void pop_back( )
        {
            assertErase(VectorBase::back( ), VectorBase::size( ) - 1);
            VectorBase::pop_back( );
        }
    };

}