#pragma once
/***********************************************
* @headerfile TMCadVector.h
* @date 20 / 09 / 2023
* @author Roomain
************************************************/
#include <algorithm>
#include <vector>
#include "MCadMemory.h"
#include "TIMCadContainer.h"
#include "MCadCell.h"
#include "TMCadRecordContainer.h"

template<typename Type> requires std::is_base_of_v<MCadObject, Type>
class TMCadVector : public TIMCadContainer<size_t>, private std::vector<MCadCell<Type>>
{
    DECLARE_RTTI_DERIVED(1, TMCadVector<Type>, MCadObject)
private:
    using VectorBase = std::vector<MCadCell<Type>>;
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
            VectorBase::push_back(MCadCell<Type>(MStatic_pointer_cast< Type >( a_object ), m_onChangeContentCallback));
        }
    }

    void do_insert(const size_t& a_key, const MCadObjectPtr& a_object)final
    {
        if ( VectorBase::size( ) > a_key )
        {
            VectorBase::insert(begin( ) + a_key, MCadCell<Type>(MStatic_pointer_cast< Type >( a_object ), m_onChangeContentCallback));
        }
        else
        {
            VectorBase::push_back(MCadCell<Type>(MStatic_pointer_cast< Type >( a_object ), m_onChangeContentCallback));
        }
    }

    void do_eraseAt(const size_t& a_index) final
    {
        if ( VectorBase::size( ) > a_index )
            VectorBase::erase(begin( ) + a_index);
    }

    void assert_ItemChanged(const MCadCell<Type>* a_pCell, const MCadShared_ptr<Type>& a_pBefore, const MCadShared_ptr<Type>& a_pAfter)
    {
        if ( auto pDoc = document( ).lock( ) )
        {
            if ( pDoc->undoRedo( ).active( ) )
            {
                auto& session = pDoc->undoRedo( ).currentSession( );
                session.append(std::make_shared<TMCadRecordContainerChanged<size_t>>(this, a_pCell - VectorBase::data( ), a_pBefore, a_pAfter));
            }
        }
    }
public:
    TMCadVector( )
    {
        m_onChangeContentCallback = std::bind_front(&TMCadVector<Type>::assert_ItemChanged, this);
    }
    explicit TMCadVector(const size_t& size) : std::vector<MCadCell<Type>>(size) {
        m_onChangeContentCallback = std::bind_front(&TMCadVector<Type>::assert_ItemChanged, this);
    }

    size_t size( ) const noexcept { return VectorBase::size( ); }
    constexpr void reserve(const size_t& a_cap) { VectorBase::reserve(a_cap); }
    bool empty( )const noexcept { return VectorBase::empty( ); }

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
        MCadCell<Type>& pt = VectorBase::back( );
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
        VectorBase::push_back(MCadCell<Type>(std::move(a_pointer), m_onChangeContentCallback));
        MCadCell<Type>& pt = VectorBase::back( );
        assert_ItemInsert(pt, size( ) - 1);
        return *this;
    }

    MCadCell<Type>& operator[](const size_t& a_index)
    {
        return VectorBase::operator[](a_index);
    }

    const MCadCell<Type>& at(const size_t& a_index)
    {
        return VectorBase::at(a_index);
    }

    using iterator = std::vector<MCadCell<Type>>::iterator;
    iterator begin( ) { return VectorBase::begin( ); }
    iterator end( ) { return VectorBase::end( ); }


    using reverse_iterator = std::vector<MCadCell<Type>>::reverse_iterator;
    reverse_iterator  rbegin( ) { return VectorBase::rbegin( ); }
    reverse_iterator  rend( ) { return VectorBase::rend( ); }

    using const_iterator = std::vector<MCadCell<Type>>::const_iterator;
    const_iterator cbegin( )const { return VectorBase::cbegin( ); }
    const_iterator cend( )const { return VectorBase::cend( ); }
    iterator insert(const_iterator a_pos, const MCadShared_ptr<Type>& a_object)
    {
        auto iter = VectorBase::insert(a_pos, MCadCell<Type>(m_onChangeContentCallback, a_object));
        assert_ItemInsert(( *iter ), iter - begin( ));
        return iter;
    }

    constexpr iterator insert(const_iterator a_pos, MCadShared_ptr<Type>&& a_object)
    {
        auto iter = VectorBase::insert(a_pos, MCadCell<Type>(m_onChangeContentCallback, std::move(a_object)));
        assert_ItemInsert(( *iter ), std::distance(iter, begin( )));
        return iter;
    }

    using const_reverse_iterator = std::vector<MCadCell<Type>>::const_reverse_iterator;
    const_reverse_iterator crbegin( )const { return VectorBase::crbegin( ); }
    const_reverse_iterator crend( )const { return VectorBase::crend( ); }

    template<typename ...Args>
    TMCadVector& emplace(const_iterator a_iter, Args&& ...args)
    {
        VectorBase::emplace(a_iter, m_onChangeContentCallback, std::make_shared<Type>(args...));
        assert_ItemInsert(( *a_iter ), std::distance(a_iter, begin( )));
        return *this;
    }

    iterator erase(iterator a_pos)
    {
        assert_ItemRemoved(( *a_pos ), std::distance(a_pos, begin( )));
        m_bActiveCallback = false;
        auto iter = VectorBase::erase(a_pos);
        m_bActiveCallback = true;
        return iter;
    }

    constexpr iterator erase(const_iterator a_pos)
    {
        m_bActiveCallback = false;
        assert_ItemRemoved(( *a_pos ), std::distance(a_pos, cbegin( )));
        m_bActiveCallback = false;
        auto iter = VectorBase::erase(a_pos);
        m_bActiveCallback = true;
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
        m_bActiveCallback = false;
        auto iter = VectorBase::erase(a_first, a_last);
        m_bActiveCallback = true;
        return iter;
    }

    constexpr iterator erase(const_iterator a_first, const_iterator a_last)
    {
        m_bActiveCallback = false;
        size_t index = 0;
        std::for_each(a_first, a_last - 1, [ this ] (auto&& a_obj)
            {
                assert_ItemRemoved(a_obj, index);
                ++index;
            });
        m_bActiveCallback = false;
        auto iter = VectorBase::erase(a_first, a_last);
        m_bActiveCallback = true;
        return iter;
    }

    constexpr void pop_back( )
    {
        MCadCell<Type>& pt = VectorBase::back( );
        assert_ItemRemoved(pt, VectorBase::size( ) - 1);
        VectorBase::pop_back( );
    }

    virtual unsigned short load(IMCadInputStream& a_stream)override
    {
        size_t size;
        a_stream >> size;
        VectorBase::reserve(size);
        for ( size_t i = 0; i < size; ++i )
        {
            // TODO
        }

        return isA( )->version( );
    }

    /*@brief save object to stream*/
    virtual bool save(IMCadOutputStream& a_stream)const override
    {
        a_stream << size( );
        for ( const auto& obj : ( const VectorBase ) *this )
            a_stream << obj.get( )->uid( );
        return true;
    }
};