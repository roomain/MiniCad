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
#include <vector>
#include <ranges>
#include <algorithm>

template<typename Type>
using ReactorFun = std::function<void(const std::string&, const Type&, const Type&)>;

template<typename Type>
using ReactorVec = std::vector<ReactorFun<Type>>;


template<typename Type>
class MCadBaseProperty
{
protected:
	Type m_propertyValue;			/*!< property value*/
	std::string m_propertyName;		/*!< property name*/
	ReactorVec<Type> m_reactors;	/*!< reactor callback*/

	void callReactors(const Type& a_oldValue, const Type& a_newValue)const
	{
		for ( const auto& callback : m_reactors )
			callback(m_propertyName, a_oldValue, a_newValue);
	}

public:
	MCadBaseProperty( ) = delete;
	explicit MCadBaseProperty(const std::string_view& a_name) :
		m_propertyName{ a_name } {}
	explicit MCadBaseProperty(const std::string_view& a_name, Type&& a_defaultValue)noexcept :
		m_propertyName{ a_name }, m_propertyValue{ a_defaultValue } {}
	virtual ~MCadBaseProperty( ) = default;

	[[nodiscard]] constexpr Type value( )const { return m_propertyValue; }
	[[nodiscard]] explicit operator Type( )const { return m_propertyValue; }
	[[nodiscard]] const std::string& name( )const noexcept { return m_propertyName; }
	void addReactor(const ReactorFun<Type>& a_react)
	{
		m_reactors.emplace_back(a_react);
	}
	void removeReactor(const ReactorFun<Type>& a_react)
	{
		auto iter = std::ranges::find(m_reactors, a_react);
		if ( iter != m_reactors.end( ) )
			m_reactors.erase(iter);
	}

};

template<typename Type, bool ReadOnly = false, typename Friend = void>
class MCadProperty : public MCadBaseProperty<Type>
{
	friend Friend;

public:
	MCadProperty( ) = delete;
	explicit MCadProperty(const std::string_view& a_name) :
		MCadBaseProperty<Type>{ a_name } {}
	explicit MCadProperty(const std::string_view& a_name, Type&& a_defaultValue)noexcept :
		MCadBaseProperty<Type>{a_name, std::move(a_defaultValue)}{}
	virtual ~MCadProperty( )override = default;
	
	MCadProperty<Type, ReadOnly>& operator = (const Type& a_value) requires( !ReadOnly )
	{
		MCadBaseProperty<Type>::callReactors(MCadBaseProperty<Type>::m_propertyValue, a_value);
		MCadBaseProperty<Type>::m_propertyValue = a_value;
		return *this;
	}
	MCadProperty<Type, ReadOnly>& operator = (Type&& a_value)noexcept requires( !ReadOnly )
	{
		MCadBaseProperty<Type>::callReactors(MCadBaseProperty<Type>::m_propertyValue, a_value);
		MCadBaseProperty<Type>::m_propertyValue = a_value;
		return *this;
	}
	[[nodiscard]] TMCadScoped<Type> getScoped() requires( !ReadOnly )
	{
		return TMCadScoped<Type>(MCadBaseProperty<Type>::m_propertyValue);
	}
};


template<typename Type, bool Valid(const Type&)>
class MCadValidProperty : public MCadBaseProperty<Type>
{
public:
	MCadValidProperty( ) = delete;
	explicit MCadValidProperty(const std::string_view& a_name) :
		MCadBaseProperty<Type>{ a_name } {}
	explicit MCadValidProperty(const std::string_view& a_name, Type&& a_defaultValue)noexcept :
		MCadBaseProperty<Type>{ a_name, std::move(a_defaultValue) } {}
	virtual ~MCadValidProperty( )override = default;

	MCadValidProperty<Type, Valid>& operator = (const Type& a_value)
	{
		if ( Valid(a_value) )
		{
			MCadBaseProperty<Type>::callReactors(MCadBaseProperty<Type>::m_propertyValue, a_value);
			MCadBaseProperty<Type>::m_propertyValue = a_value;
		}
		return *this;
	}
	MCadValidProperty<Type, Valid>& operator = (Type&& a_value)noexcept
	{
		if ( Valid(a_value) )
		{
			MCadBaseProperty<Type>::callReactors(MCadBaseProperty<Type>::m_propertyValue, a_value);
			MCadBaseProperty<Type>::m_propertyValue = a_value;
		}
		return *this;
	}
	[[nodiscard]] TMCadScoped<Type> getScoped( )
	{
		return TMCadScoped<Type>(MCadBaseProperty<Type>::m_propertyValue);
	}
};
