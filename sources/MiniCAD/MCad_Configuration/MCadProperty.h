#pragma once
/***********************************************
* @headerfile MCadProperty.h
* @date 26 / 10 / 2023
* @author Roomain
************************************************/
#include <string>
#include <functional>
#include <string_view>
#include "TMCadScoped.h"

template<typename Type>
using ReactorFun = std::function<void(const std::string&, const Type&, const Type&)>;



template<typename Type, bool ReadOnly = false>
class MCadProperty
{
private:
	Type m_propertyValue;		/*!< property value*/
	std::string m_propertyName;	/*!< property name*/
	ReactorFun<Type> m_reactor;	/*!< reactor callback*/

public:
	MCadProperty( ) = delete;
	explicit MCadProperty(const std::string_view& a_name) :
		m_propertyName{ a_name } {}
	explicit MCadProperty(const std::string_view& a_name, const Type& a_defaultValue) :
		m_propertyName{a_name}, m_propertyValue{a_defaultValue}{}
	virtual ~MCadProperty( ) = default;
	[[nodiscard]] constexpr Type value()const { return m_propertyValue; }
	[[nodiscard]] explicit operator Type( )const { return m_propertyValue; }
	[[nodiscard]] const std::string& name( )const noexcept { return m_propertyName; }
	void setReactor(const ReactorFun<Type>& a_react) { m_reactor = a_react; }
	MCadProperty<Type, ReadOnly>& operator = (const Type& a_value) requires( !ReadOnly )
	{
		if ( m_reactor )
			m_reactor(m_propertyName, m_propertyValue, a_value);
		m_propertyValue = a_value;
		return *this;
	}
	MCadProperty<Type, ReadOnly>& operator = (Type&& a_value)noexcept requires( !ReadOnly )
	{
		if ( m_reactor )
			m_reactor(m_propertyName, m_propertyValue, a_value);
		m_propertyValue = a_value;
		return *this;
	}
	[[nodiscard]] TMCadScoped<Type> getScoped() requires( !ReadOnly )
	{
		return TMCadScoped<Type>(m_propertyValue);
	}
};


template<typename Type, bool Valid(const Type&)>
class MCadValidProperty
{
private:
	Type m_propertyValue;		/*!< property value*/
	std::string m_propertyName;	/*!< property name*/
	ReactorFun<Type> m_reactor;	/*!< reactor callback*/

public:
	MCadValidProperty( ) = delete;
	explicit MCadValidProperty(const std::string_view& a_name, const Type& a_defaultValue) :
		m_propertyName{ a_name }, m_propertyValue{ a_defaultValue } {}
	virtual ~MCadValidProperty( ) = default;
	[[nodiscard]] constexpr Type value( )const { return m_propertyValue; }
	[[nodiscard]] explicit operator Type( )const { return m_propertyValue; }
	[[nodiscard]] const std::string& name( )const noexcept { return m_propertyName; }
	void setReactor(const ReactorFun<Type>& a_react) { m_reactor = a_react; }
	MCadValidProperty<Type, Valid>& operator = (const Type& a_value)
	{
		if ( Valid(a_value) )
		{
			if ( m_reactor )
				m_reactor(m_propertyName, m_propertyValue, a_value);
			m_propertyValue = a_value;
		}
		return *this;
	}
	MCadValidProperty<Type, Valid>& operator = (Type&& a_value)noexcept
	{
		if ( Valid(a_value) )
		{
			if ( m_reactor )
				m_reactor(m_propertyName, m_propertyValue, a_value);
			m_propertyValue = a_value;
		}
		return *this;
	}
	[[nodiscard]] TMCadScoped<Type> getScoped( )
	{
		return TMCadScoped<Type>(m_propertyValue);
	}
};
