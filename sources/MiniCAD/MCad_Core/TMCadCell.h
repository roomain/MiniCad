#pragma once
/***********************************************
* @headerfile TMCadCell.h
* @date 10 / 09 / 2023
* @author Roomain
************************************************/
#include <functional>
#include "MCadMemory.h"

template<typename Type>
class TMCadCell;


/*@brief assertion when cell content is changing*/
template<typename Type>
using Assert_ContentChange = std::function<void(const TMCadCell<Type>*, const MCadShared_ptr<Type>&, const MCadShared_ptr<Type>&)>;

/*@brief cell of container*/
template<typename Type>
class TMCadCell : public MCadShared_ptr<Type>
{
private:
	Assert_ContentChange<Type> m_onContentChange;	/*!< content change callback*/

public:
	TMCadCell( ) = default;


	void setChangeCallback(const Assert_ContentChange<Type>& a_assertCB)
	{
		m_onContentChange = a_assertCB;
	}

	explicit TMCadCell(TMCadCell<Type>&& a_other)noexcept : MCadShared_ptr<Type>(std::move(a_other)),
		m_onContentChange{ a_other.m_onContentChange }
	{
	}

	explicit TMCadCell(TMCadCell<Type>& a_other)noexcept : MCadShared_ptr<Type>(a_other),
		m_onContentChange{ a_other.m_onContentChange }
	{
	}

	explicit TMCadCell(const Assert_ContentChange<Type>& a_assert) : m_onContentChange{ a_assert } {}

	explicit TMCadCell(const MCadShared_ptr<Type>& a_ptr, const Assert_ContentChange<Type>& a_assert) :
		MCadShared_ptr<Type>(a_ptr), m_onContentChange{ a_assert } {}

	explicit TMCadCell(MCadShared_ptr<Type>&& a_ptr, const Assert_ContentChange<Type>& a_assert)noexcept :
		MCadShared_ptr<Type>(std::move(a_ptr)), m_onContentChange{ a_assert } {}

	template<typename ...Args>
	TMCadCell(const Assert_ContentChange<Type>& a_cb, Args&& ...a_args) :
		MCadShared_ptr<Type>(make_MShared<Type>(a_args...)), m_onContentChange{ a_cb } {}

	TMCadCell<Type>& operator = (const MCadShared_ptr<Type>& a_other)
	{
		if ( this->get( ) != a_other.get( ) )
		{
			if ( m_onContentChange )
				m_onContentChange(this, *this, a_other);
			MCadShared_ptr<Type>::operator = (a_other);
		}
		return *this;
	}

	TMCadCell<Type>& operator = (MCadShared_ptr<Type>&& a_other)
	{
		if ( this->get( ) != a_other.get( ) )
		{
			if ( m_onContentChange )
				m_onContentChange(this, *this, a_other);
			MCadShared_ptr<Type>::operator = (a_other);
		}
		return *this;
	}

	TMCadCell<Type>& operator = (const TMCadCell<Type>& a_other)
	{
		if ( this->get( ) != a_other.get( ) )
		{
			if ( m_onContentChange )
				m_onContentChange(*this, a_other);
			MCadShared_ptr<Type>::operator = (a_other);
		}
		return *this;
	}

	TMCadCell<Type>& operator = (TMCadCell<Type>&& a_other)
	{
		if ( this->get( ) != a_other.get( ) )
		{
			if ( m_onContentChange )
				m_onContentChange(this, *this, a_other);
			MCadShared_ptr<Type>::operator = (a_other);
		}
		return *this;
	}

	virtual ~TMCadCell( ) = default;
};