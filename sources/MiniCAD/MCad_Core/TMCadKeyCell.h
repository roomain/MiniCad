#pragma once
/***********************************************
* @headerfile TMCadKeyCell.h
* @date 03 / 10 / 2023
* @author Roomain
************************************************/
#include <functional>
#include "MCadMemory.h"

template<typename Key, typename Type>
class TMCadKeyCell;

template<typename Key, typename Type>
using ChangeAssertionKey = std::function<void(const TMCadKeyCell<Key, Type>*, const MCadShared_ptr<Type>&, const MCadShared_ptr<Type>&)>;


template<typename Key, typename Type>
class TMCadKeyCell : public MCadShared_ptr<Type>
{
private:
	Key m_key;
	ChangeAssertionKey<Key, Type> m_changeAssert;

public:
	TMCadKeyCell( ) = default;

	Key key( )const { return m_key; }

	explicit TMCadKeyCell(const Key& a_key, TMCadKeyCell<Key, Type>&& a_other)noexcept : MCadShared_ptr<Type>(std::move(a_other)),
		m_key{ a_key }, m_changeAssert{ a_other.m_changeAssert }, m_key{ std::move(a_other.key) }
	{
	}

	explicit TMCadKeyCell(const Key& a_key, TMCadKeyCell<Key, Type>& a_other)noexcept : MCadShared_ptr<Type>(a_other),
		m_key{ a_key }, m_changeAssert{ a_other.m_changeAssert }, m_key{ a_other.key }
	{
	}

	explicit TMCadKeyCell(const Key& a_key, const ChangeAssertionKey<Key, Type>& a_assert) : m_key{ a_key }, m_changeAssert{ a_assert } {}

	explicit TMCadKeyCell(const Key& a_key, const MCadShared_ptr<Type>& a_ptr, const ChangeAssertionKey<Key, Type>& a_assert) :
		MCadShared_ptr<Type>(a_ptr), m_key{ a_key }, m_changeAssert{ a_assert } {}

	explicit TMCadKeyCell(const Key& a_key, MCadShared_ptr<Type>&& a_ptr, const ChangeAssertionKey<Key, Type>& a_assert)noexcept :
		MCadShared_ptr<Type>(std::move(a_ptr)), m_key{ a_key }, m_changeAssert{ a_assert } {}

	template<typename ...Args>
	TMCadKeyCell(const Key& a_key, const ChangeAssertionKey<Key, Type>& a_cb, Args&& ...a_args) :
		MCadShared_ptr<Type>(make_MShared<Type>(a_args...)), m_key{ a_key }, m_changeAssert{ a_cb } {}

	TMCadKeyCell<Key, Type>& operator = (const MCadShared_ptr<Type>& a_other)
	{
		if ( this->get( ) != a_other.get( ) )
		{
			if ( m_changeAssert )
				m_changeAssert(this, *this, a_other);
			MCadShared_ptr<Type>::operator = (a_other);
		}
		return *this;
	}

	TMCadKeyCell<Key, Type>& operator = (MCadShared_ptr<Type>&& a_other)
	{
		if ( this->get( ) != a_other.get( ) )
		{
			if ( m_changeAssert )
				m_changeAssert(this, *this, a_other);
			MCadShared_ptr<Type>::operator = (a_other);
		}
		return *this;
	}

	TMCadKeyCell<Key, Type>& operator = (const TMCadKeyCell<Key, Type>& a_other)
	{
		if ( this->get( ) != a_other.get( ) )
		{
			if ( m_changeAssert )
				m_changeAssert(*this, a_other);
			MCadShared_ptr<Type>::operator = (a_other);
		}
		return *this;
	}

	TMCadKeyCell<Key, Type>& operator = (TMCadKeyCell<Key, Type>&& a_other)
	{
		if ( this->get( ) != a_other.get( ) )
		{
			if ( m_changeAssert )
				m_changeAssert(this, *this, a_other);
			MCadShared_ptr<Type>::operator = (a_other);
		}
		return *this;
	}

	virtual ~TMCadKeyCell( )
	{
		//
	}
};