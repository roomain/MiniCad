#pragma once
/***********************************************
* @headerfile MCadVector.h
* @date 01 / 08 / 2023
* @author Roomain
************************************************/
#include <vector>
#include <memory>
#include <functional>
#include <type_traits>
#include <iterator>
#include "IMCadIndexedContainer.h"

/*@brief vector contained derivated MCadObject can be used in undo/redo*/

template<typename T>
class ContainerItem : private std::shared_ptr<T>
{
public:
    using ChangeCallback = std::function<void(const ContainerItem<T>*, const MCadObjectPtr&, const MCadObjectPtr&)>;

private:
    ChangeCallback m_callback;

public:
    ContainerItem() = default;

    template<typename ...Args>
    ContainerItem(ChangeCallback a_cb, Args&& ...a_args) : std::shared_ptr<T>(std::make_shared<T>(a_args...)), m_callback{a_cb} {}

    ContainerItem(const ContainerItem<T>& a_other) : std::shared_ptr<T>(a_other)
    {
        m_callback = a_other.m_callback;
    }

    ContainerItem(ContainerItem<T>&& a_other) : std::shared_ptr<T>(std::move(a_other))
    {
        m_callback = a_other.m_callback;
    }

    ContainerItem(const std::shared_ptr<T>& a_other) : std::shared_ptr<T>(a_other)
    {
    }

    ContainerItem(std::shared_ptr<T>&& a_other) : std::shared_ptr<T>(std::move(a_other))
    {
    }

    ContainerItem(ChangeCallback a_cb, const std::shared_ptr<T>& a_other) : std::shared_ptr<T>(a_other)
    {
        m_callback = a_cb;
    }

    ContainerItem(ChangeCallback a_cb, std::shared_ptr<T>&& a_other) : std::shared_ptr<T>(std::move(a_other))
    {
        m_callback = a_cb;
    }

    virtual ~ContainerItem() = default;

    void setCallback(ChangeCallback a_cb)
    {
        m_callback = a_cb;
    }

    ContainerItem<T>& operator = (const std::shared_ptr<T>& a_other)
    {
        if (m_callback)
            m_callback(this, *this, a_other);
        std::shared_ptr<T>::operator = (a_other);
        return *this;
    }

    ContainerItem<T>& operator = (std::shared_ptr<T>&& a_other)
    {
        if (m_callback)
            m_callback(this, *this, a_other);
        std::shared_ptr<T>::operator = (a_other);
        return *this;
    }

    ContainerItem<T>& operator = (const ContainerItem<T>& a_other)
    {
        if (m_callback)
            m_callback(this, *this, a_other);
        std::shared_ptr<T>::operator = (a_other);
        return *this;
    }

    ContainerItem<T>& operator = (ContainerItem<T>&& a_other)noexcept
    {
        if (m_callback)
            m_callback(this, *this, static_cast<const std::shared_ptr<T>>(a_other));
        std::shared_ptr<T>::operator = (a_other);
        return *this;
    }

    std::shared_ptr<T> toPointer()const
    {
        return *this;
    }

    operator std::shared_ptr<T>() {
        return (std::shared_ptr<T>) * this;
    }

    operator std::shared_ptr<T>& () {
        return (std::shared_ptr<T>) * this;
    }
    
    operator const std::shared_ptr<T>& ()const {
        return (std::shared_ptr<T>) * this;
    }

    const T* get()const
    {
        return std::shared_ptr<T>::get();
    }

    const int use_count()const
    {
        return std::shared_ptr<T>::use_count();
    }

    T* operator->() { return std::shared_ptr<T>::operator->(); }
};


template<typename Type>
class MCadVector : private std::vector<ContainerItem<Type>>, public IMCadIndexedContainer
{
    DECLARE_RTTI_DERIVED(1, MCadVector<Type>, IMCadIndexedContainer)

private:
    using VectorBase = std::vector<ContainerItem<Type>>;
    ContainerItem<Type>::ChangeCallback m_itemCallback;

protected:
    void undoRedo_RemoveObject(const size_t& a_index)final
    {
        if (VectorBase::size() > a_index)
            VectorBase::erase(begin() + a_index);
    }

    void undoRedo_InsertObject(MCadObjectPtr& a_object, const size_t& a_index)final
    {
        if (VectorBase::size() > a_index)
        {
            VectorBase::insert(begin() + a_index, ContainerItem<Type>(m_itemCallback, std::static_pointer_cast<Type>(a_object)));
        }
        else
        {
            VectorBase::push_back(ContainerItem<Type>(m_itemCallback, std::static_pointer_cast<Type>(a_object)));
        }
    }

    virtual void assertItem(const ContainerItem<Type>* a_pItem, const MCadObjectPtr& a_pBefore, const MCadObjectPtr& a_pAfter)
    {
        if (m_bActiveCallback)
        {
            size_t index = a_pItem - VectorBase::data();
            IMCadIndexedContainer::assertItem(a_pBefore, a_pAfter, index);
        }
    }

    bool m_bActiveCallback = true; /*!< active the assertItem callback*/

public:
    MCadVector()
    {
        m_itemCallback = std::bind_front(&MCadVector<Type>::assertItem, this);
    }
    explicit MCadVector(const size_t& size) : std::vector<ContainerItem<Type>>(size) {
        m_itemCallback = std::bind_front(&MCadVector<Type>::assertItem, this);
    }

    size_t size() const noexcept { return VectorBase::size(); }
    constexpr void reserve(const size_t& a_cap) { VectorBase::reserve(a_cap); }
    bool empty()const noexcept { return VectorBase::empty(); }

    void clear()
    {
        size_t index = 0;
        for (const auto& obj : *this)
        {
            assertObjectRemoved(obj, index);
            ++index;
        }
        VectorBase::clear();
    }

    template<typename ...Args>
    MCadVector& emplace_back(Args&& ...a_args)
    {
        VectorBase::emplace_back(m_itemCallback, a_args...);
        assertObjectAdded(VectorBase::back(), size() - 1);
        return *this;
    }


    MCadVector& push_back(const std::shared_ptr<Type>& a_pointer)
    {
        VectorBase::push_back(ContainerItem<Type>(m_itemCallback, a_pointer));
        assertObjectAdded(a_pointer, size() - 1);
        return *this;
    }

    constexpr MCadVector& push_back(std::shared_ptr<Type>&& a_pointer)
    {
        VectorBase::push_back(ContainerItem<Type>(m_itemCallback, std::move(a_pointer)));
        ContainerItem<Type>& pt = VectorBase::back();
        assertObjectAdded(pt.toPointer(), size() - 1);
        return *this;
    }

    ContainerItem<Type>& operator[](const size_t& a_index)
    {
        return VectorBase::operator[](a_index);
    }

    using iterator = std::vector<ContainerItem<Type>>::iterator;
    iterator begin() { return VectorBase::begin(); }
    iterator end() { return VectorBase::end(); }


    using reverse_iterator = std::vector<ContainerItem<Type>>::reverse_iterator;
    reverse_iterator  rbegin() { return VectorBase::rbegin(); }
    reverse_iterator  rend() { return VectorBase::rend(); }

    using const_iterator = std::vector<ContainerItem<Type>>::const_iterator;
    const_iterator cbegin()const { return VectorBase::cbegin(); }
    const_iterator cend()const { return VectorBase::cend(); }
    iterator insert(const_iterator a_pos, const std::shared_ptr<Type>& a_object)
    {
        auto iter = VectorBase::insert(a_pos, ContainerItem<Type>(m_itemCallback, a_object)); 
        assertObjectAdded((*iter), iter - begin());
        return iter;
    }

    constexpr iterator insert(const_iterator a_pos, std::shared_ptr<Type>&& a_object)
    {
        auto iter = VectorBase::insert(a_pos, ContainerItem<Type>(m_itemCallback, std::move( a_object)));
        assertObjectAdded((*iter), std::distance(iter, begin()));
        return iter;
    }

    using const_reverse_iterator = std::vector<ContainerItem<Type>>::const_reverse_iterator;
    const_reverse_iterator crbegin()const { return VectorBase::crbegin(); }
    const_reverse_iterator crend()const { return VectorBase::crend(); }

    template<typename ...Args>
    MCadVector& emplace(const_iterator a_iter, Args&& ...args)
    {
        VectorBase::emplace(a_iter, m_itemCallback, std::make_shared<Type>(args...));
        assertObjectAdded((*a_iter), std::distance(a_iter, begin()));
        return *this;
    }

    iterator erase(iterator a_pos)
    {
        assertObjectRemoved((*a_pos), std::distance(a_pos, begin()));
        m_bActiveCallback = false;
        auto iter =  VectorBase::erase(a_pos);
        m_bActiveCallback = true;
        return iter;
    }

    constexpr iterator erase(const_iterator a_pos)
    {
        m_bActiveCallback = false;
        assertObjectRemoved((*a_pos), std::distance(a_pos, cbegin()));
        m_bActiveCallback = false;
        auto iter = VectorBase::erase(a_pos);
        m_bActiveCallback = true;
        return iter;
    }

    iterator erase(iterator  a_first, iterator a_last)
    {
        size_t index = 0;
        std::for_each(a_first, a_last - 1, [this, &index](auto&& a_obj)
            {
                assertObjectRemoved(a_obj, index);
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
        std::for_each(a_first, a_last - 1, [this](auto&& a_obj)
            {
                assertObjectRemoved(a_obj, index);
                ++index;
            });
        m_bActiveCallback = false;
        auto iter = VectorBase::erase(a_first, a_last);
        m_bActiveCallback = true;
        return iter;
    }

    virtual unsigned short load(IMCadInputStream& a_stream)override
    {
        //MCadObject::load(a_stream);
        size_t size;
        a_stream >> size;
        VectorBase::reserve(size);
        for (size_t i = 0; i < size; ++i)
        {
            // TODO
        }
        
        return definition()->version();
    }

    /*@brief save object to stream*/
    virtual bool save(IMCadOutputStream& a_stream)const override
    {
        //MCadObject::save(a_stream);
        a_stream << size();
        for (const auto& obj : (const VectorBase)*this)
            a_stream << obj.get()->uid();
        return true;
    }
};
