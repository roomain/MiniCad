#pragma once
/***********************************************
* @headerfile TMCadVector.h
* @date 20 / 09 / 2023
* @author Roomain
************************************************/
#include <algorithm>
#include <vector>
#include <execution>
#include "MCadMemory.h"
#include "TIMCadContainer.h"
#include "TMCadCell.h"
#include "TMCadRecordContainerCell.h"
#include "TMCadRecordContainerEmptyCell.h"

template<typename Type> requires std::is_base_of_v<MCadObject, Type>
class TMCadVector : public TIMCadContainer<size_t>, private std::vector<TMCadCell<Type>>
{
private:
    using VectorBase = std::vector<TMCadCell<Type>>;
    Assert_ContentChange<Type> m_onChangeContentCallback;   /*!< callback cell contant change*/
    bool m_bActiveCallback = true;                          /*!< callback enable*/

protected:
    void do_replace(const size_t& a_key, const MCadObjectPtr& a_object)final
    {
        if ( VectorBase::size( ) > a_key )
        {
            VectorBase::operator[](a_key) = MStatic_pointer_cast< Type >( a_object );
        }
        else
        {
            VectorBase::push_back(TMCadCell<Type>(MStatic_pointer_cast< Type >( a_object ), m_onChangeContentCallback));
        }
    }

    void do_insert(const size_t& a_key, const MCadObjectPtr& a_object)final
    {
        if ( VectorBase::size( ) > a_key )
        {
            VectorBase::insert(begin( ) + a_key, TMCadCell<Type>(MStatic_pointer_cast< Type >( a_object ), m_onChangeContentCallback));
        }
        else
        {
            VectorBase::push_back(TMCadCell<Type>(MStatic_pointer_cast< Type >( a_object ), m_onChangeContentCallback));
        }
    }

    void do_eraseAt(const size_t& a_index) final
    {
        if ( VectorBase::size( ) > a_index )
            VectorBase::erase(begin( ) + a_index);
    }

    void assert_ItemChanged(const TMCadCell<Type>* a_pCell, const MCadShared_ptr<Type>& a_pBefore, const MCadShared_ptr<Type>& a_pAfter)
    {
        if ( auto pDoc = MCadDocumentManager::Instance( ).currentDocument( ).lock( ) )
        {
            if ( pDoc->undoRedo( ).active( ) )
            {
                auto& session = pDoc->undoRedo( ).currentSession( );
                if ( a_pBefore )
                {
                    session.append(std::make_shared<TMCadRecordContainerCellChanged<size_t>>(this, 
                        a_pCell - VectorBase::data( ), a_pBefore, a_pAfter));
                }
                else
                {
                    session.append(std::make_shared<TMCadRecordContainerEmptyCellChanged<size_t>>(this,
                        a_pCell - VectorBase::data( ),
                        a_pAfter));
                }
            }
        }
    }
public:
    TMCadVector( )
    {
        m_onChangeContentCallback = std::bind_front(&TMCadVector<Type>::assert_ItemChanged, this);
    }
    explicit TMCadVector(const size_t& size) : std::vector<TMCadCell<Type>>(size) {
        m_onChangeContentCallback = std::bind_front(&TMCadVector<Type>::assert_ItemChanged, this);
        std::for_each(std::execution::par, VectorBase::begin( ), VectorBase::end( ),
            [ this ] (auto& a_cell)
            {
                a_cell.setChangeCallback(m_onChangeContentCallback);
            });
    }


    void clear( )
    {
        size_t index = 0;
        for ( const auto& obj : *this )
        {
            assert_ItemRemoved(obj, index);
            ++index;
        }
        VectorBase::clear( );
    }

    template<typename ...Args>
    TMCadVector& emplace_back(Args&& ...a_args)
    {
        VectorBase::emplace_back(m_onChangeContentCallback, a_args...);
        TMCadCell<Type>& pt = VectorBase::back( );
        assert_ItemInsert(pt, size( ) - 1);
        return *this;
    }

    TMCadVector& push_back(const MCadShared_ptr<Type>& a_pointer)
    {
        VectorBase::emplace_back(a_pointer, m_onChangeContentCallback);
        assert_ItemInsert(a_pointer, size( ) - 1);
        return *this;
    }

    constexpr TMCadVector& push_back(MCadShared_ptr<Type>&& a_pointer)
    {
        VectorBase::push_back(TMCadCell<Type>(std::move(a_pointer), m_onChangeContentCallback));
        TMCadCell<Type>& pt = VectorBase::back( );
        assert_ItemInsert(pt, size( ) - 1);
        return *this;
    }

    using std::vector<TMCadCell<Type>>::operator [];
    using std::vector<TMCadCell<Type>>::at;
    using std::vector<TMCadCell<Type>>::begin;
    using std::vector<TMCadCell<Type>>::end;
    using std::vector<TMCadCell<Type>>::cbegin;
    using std::vector<TMCadCell<Type>>::cend;
    using std::vector<TMCadCell<Type>>::rbegin;
    using std::vector<TMCadCell<Type>>::rend;
    using std::vector<TMCadCell<Type>>::crbegin;
    using std::vector<TMCadCell<Type>>::crend;
    using std::vector<TMCadCell<Type>>::size;
    using std::vector<TMCadCell<Type>>::empty;
    using std::vector<TMCadCell<Type>>::reserve;


    using iterator = std::vector<TMCadCell<Type>>::iterator;
    using const_iterator = std::vector<TMCadCell<Type>>::const_iterator;

    iterator insert(const_iterator a_pos, const MCadShared_ptr<Type>& a_object)
    {
        auto iter = VectorBase::insert(a_pos, TMCadCell<Type>(m_onChangeContentCallback, a_object));
        assert_ItemInsert(( *iter ), iter - begin( ));
        return iter;
    }

    constexpr iterator insert(const_iterator a_pos, MCadShared_ptr<Type>&& a_object)
    {
        auto iter = VectorBase::insert(a_pos, TMCadCell<Type>(m_onChangeContentCallback, std::move(a_object)));
        assert_ItemInsert(( *iter ), std::distance(iter, begin( )));
        return iter;
    }

    template<typename ...Args>
    TMCadVector& emplace(const_iterator a_iter, Args&& ...args)
    {
        VectorBase::emplace(a_iter, m_onChangeContentCallback, make_MShared<Type>(args...));
        assert_ItemInsert(( *a_iter ), std::distance(a_iter, begin( )));
        return *this;
    }

    iterator erase(iterator a_pos)
    {
        assert_ItemRemoved(( *a_pos ), std::distance(a_pos, begin( )));
        TMCadScoped<bool> scoped(m_bActiveCallback);
        scoped = false;
        auto iter = VectorBase::erase(a_pos);
        return iter;
    }

    constexpr iterator erase(const_iterator a_pos)
    {
        TMCadScoped<bool> scoped(m_bActiveCallback);
        scoped = false;
        assert_ItemRemoved(( *a_pos ), std::distance(a_pos, cbegin( )));
        auto iter = VectorBase::erase(a_pos);
        return iter;
    }

    iterator erase(iterator  a_first, iterator a_last)
    {
        size_t index = 0;
        std::for_each(a_first, a_last - 1, [ this, &index ] (auto&& a_obj)
            {
                assert_ItemRemoved(a_obj, index);
                ++index;
            });
        TMCadScoped<bool> scoped(m_bActiveCallback);
        scoped = false;
        auto iter = VectorBase::erase(a_first, a_last);
        return iter;
    }

    constexpr iterator erase(const_iterator a_first, const_iterator a_last)
    {
        TMCadScoped<bool> scoped(m_bActiveCallback);
        scoped = false;
        size_t index = 0;
        std::for_each(a_first, a_last - 1, [ this ] (auto&& a_obj)
            {
                assert_ItemRemoved(a_obj, index);
                ++index;
            });
        auto iter = VectorBase::erase(a_first, a_last);
        return iter;
    }

    constexpr void pop_back( )
    {
        TMCadCell<Type>& pt = VectorBase::back( );
        assert_ItemRemoved(pt, VectorBase::size( ) - 1);
        VectorBase::pop_back( );
    }

};