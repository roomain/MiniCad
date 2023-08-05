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
#include "IMCadContainer.h"

/*@brief vector contained derivated MCadObject can be used in undo/redo*/

template<typename T>
class ContainerItem : private std::shared_ptr<T>
{
private:
    std::function<void(const ContainerItem<T>*, const ObjectUID&, const ObjectUID&)> m_callback;

public:
    ContainerItem() = default;

    template<typename Args...>
    ContainerItem(std::function<void()> a_cb, Args&& ...a_args) : std::shared_ptr<T>(std::make_shared<T>(a_args)), m_callback{a_cb} {}

    ContainerItem(const ContainerItem<T>& other) : std::shared_ptr<T>(other)
    {
        m_callback = other.m_callback;
    }

    ContainerItem(ContainerItem<T>&& other) : std::shared_ptr<T>(std::move(other))
    {
        m_callback = other.m_callback;
    }

    ContainerItem(const std::shared_ptr<T>& other) : std::shared_ptr<T>(other)
    {
    }

    ContainerItem(std::shared_ptr<T>&& other) : std::shared_ptr<T>(std::move(other))
    {
    }

    ContainerItem(std::function<void()> a_cb, const std::shared_ptr<T>& other) : std::shared_ptr<T>(other)
    {
        m_callback = a_cb;
    }

    ContainerItem(std::function<void()> a_cb, std::shared_ptr<T>&& other) : std::shared_ptr<T>(std::move(other))
    {
        m_callback = a_cb;
    }

    virtual ~ContainerItem() = default;

    void setCallback(std::function<void()> a_cb)
    {
        m_callback = a_cb;
    }

    ContainerItem<T>& operator = (const std::shared_ptr<T>& other)
    {
        std::shared_ptr<T>::operator = (other);
        if (m_callback)
            m_callback();
        return *this;
    }

    ContainerItem<T>& operator = (std::shared_ptr<T>&& other)
    {
        std::shared_ptr<T>::operator = (other);
        if (m_callback)
            m_callback();
        return *this;
    }

    ContainerItem<T>& operator = (const ContainerItem<T>& other)
    {
        std::shared_ptr<T>::operator = (other);
        if (m_callback)
            m_callback();
        return *this;
    }

    ContainerItem<T>& operator = (ContainerItem<T>&& other)
    {
        std::shared_ptr<T>::operator = (other);
        if (m_callback)
            m_callback();
        return *this;
    }

    operator std::shared_ptr<T>() {
        return (std::shared_ptr<T>) * this;
    }

    operator std::shared_ptr<T>& () {
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
};


template<typename Type>
class MCadVector : private std::vector<ContainerItem<Type>>, public MCadObject
{
    DECLARE_RTTI_DERIVED(1, MCadVector<Type>, MCadObject)

private:
    using VectorBase = std::vector<ContainerItem<Type>>;
protected:
    virtual void onItemChanged(const ContainerItem<T>* a_pItem, const ObjectUID& a_idBefore, const ObjectUID& a_idAfter)
    {
        size_t index = a_pItem - VectorBase::data();
        // TODO
    }

public:
    MCadVector() {}
    MCadVector(const size_t& size) : std::vector<ContainerItem<Type>>(size) {}

    size_t size() const noexcept { return VectorBase::size(); }
    constexpr void reserve(const size_t& a_cap) { VectorBase::reserve(a_cap); }
    bool empty()const noexcept { return VectorBase::empty(); }

    void clear()
    {
        // TODO
        VectorBase::clear();
    }

    template<typename ...Args>
    MCadVector& emplace_back(Args&& ...a_args)
    {
        VectorBase::emplace_back(, a_args);
        return *this;
    }


    MCadVector& push_back(const std::shared_ptr<Type>& a_pointer)
    {
        VectorBase::push_back(ContainerItem<Type>(, a_pointer));
        return *this;
    }

    MCadVector& push_back(std::shared_ptr<Type>&& a_pointer)
    {
        VectorBase::push_back(ContainerItem<Type>(, std::move(a_pointer)));
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

    using const_iterator = std::vector<ContainerItem<Type>>::const_reverse_iterator;
    const_reverse_iterator crbegin()const { return VectorBase::cbegin(); }
    const_reverse_iterator crend()const { return VectorBase::cend(); }

    template<typename ...Args>
    MCadVector& emplace(const_iterator a_iter, Args&& ...args)
    {
        VectorBase::emplace(a_iter, , std::make_shared<type>(args));
        return *this;
    }

    iterator erase(iterator a_pos)
    {
        //
        return VectorBase::erase(a_pos);
    }

    constexpr iterator erase(const_iterator a_pos)
    {
        //
        return VectorBase::erase(a_pos)
    }

    iterator erase(iterator  a_first, iterator a_last)
    {
        //
        return VectorBase::erase(a_first, a_last);
    }

    constexpr iterator erase(const_iterator a_first, const_iterator a_last)
    {
        //
        return VectorBase::erase(a_first, a_last);
    }
};

// REVOIR: Object pouvant être undo/redo
/*template<typename Contained>
class MCadVector : public IMCadContainer< Contained>
{
	DECLARE_RTTI_DERIVED(1, MCadVector<Contained>, IMCadContainer<Contained>)
public:
	using ContainedPtr = std::shared_ptr<Contained>;

private:
	std::vector<ContainedPtr> m_container;

protected:
	void do_Add(const ContainedPtr& a_Object) final
	{
		m_container.emplace_back(a_Object);
	}

	void do_Add(ContainedPtr&& a_Object) final
	{
		m_container.emplace_back(a_Object);
	}

	void do_Insert(const size_t& a_at, const ContainedPtr& a_Object) final
	{
		m_container.insert(a_at, a_Object);
	}

	void do_Insert(const size_t& a_at, ContainedPtr&& a_Object) final
	{
		m_container.insert(a_at, a_Object);
	}


	bool do_Remove(const ContainedPtr& a_Object, size_t& a_index) final
	{
		bool bRet = false;
		//
		return bRet;
	}

	bool do_Remove(const size_t& a_index, ObjectUID& a_objID) final
	{
		bool bRet = false;
		//
		return bRet;
	}

	void do_Remove_if(Predicate& a_predicate, std::list<ItemInfo>& a_lErased) final
	{
		//
	}

	void do_clear(std::list<ItemInfo>& a_lErased) final
	{
		size_t index = 0;
		for (const auto&& obj : m_container)
		{
			a_lErased.emplace(ItemInfo{ obj->uid(), index })
			++index;
		}
		m_container.clear();
	}


public:
	using iterator = std::vector<ContainedPtr>::iterator;
	using const_iterator = std::vector<ContainedPtr>::const_iterator;
	MCadVector() = default;
	virtual ~MCadVector() { clear(); }
	[[nodiscard]] constexpr bool empty()const final { return m_container.empty(); }
	[[nodiscard]] constexpr size_t count()const final { return m_container.size(); }


	void reserve(const size_t& a_size) { m_container.reserve(a_size); }
	constexpr iterator begin() { return m_container.begin(); }
	constexpr iterator end() { return m_container.end(); }
	constexpr const_iterator cbegin()const { return m_container.cbegin(); }
	constexpr const_iterator cend()const { return m_container.cend(); }
};*/