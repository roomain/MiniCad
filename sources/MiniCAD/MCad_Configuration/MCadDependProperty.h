#pragma once
/***********************************************
* @headerfile MCadDependProperty.h
* @date 26 / 10 / 2023
* @author Roomain
************************************************/
#include "MCadProperty.h"


/*Compute function that modify first parameter and return it*/
template<typename Type, typename DependType>
using ComputeFun = std::function<Type(Type&, const DependType&)>;


template<typename Type, typename DependTypeFirst, typename DependTypeSecond>
using ComputeFunEx = std::function<Type(Type&, const DependTypeFirst&, const DependTypeSecond&)>;


/*@property wich depends of one other property*/
template<typename Type, typename DependType>
class MCadDependProperty : public MCadBaseProperty<Type>
{
protected:
	ComputeFun<Type, DependType> m_dependsFun;	/*!< callback of depend change*/

public:
	MCadDependProperty( ) = delete;
	explicit MCadDependProperty(const std::string_view& a_name) : MCadBaseProperty<Type>{ a_name } {}
	explicit MCadDependProperty(const std::string_view& a_name, Type&& a_defaultValue) : MCadBaseProperty<Type>{ a_name, std::move(a_defaultValue) }{}
	void setDependancy(const ComputeFun<Type, DependType>& a_callback, MCadBaseProperty<DependType>& a_depends)
	{
		// initialize
		m_dependsFun = a_callback;
		m_dependsFun(MCadBaseProperty<Type>::m_propertyValue, a_depends.value( ));

		// setup callback
		a_depends.addReactor([ this ] (const std::string&, const Type&, const Type& a_newValue)
			{
				this->callRactors(MCadBaseProperty<Type>::m_propertyValue, m_dependsFun(MCadBaseProperty<Type>::m_propertyValue, a_newValue));
			});
	}
};

/*@property wich depends of two other properties*/
template<typename Type, typename DependTypeFirst, typename DependTypeSecond>
class MCadDependPropertyEx : public MCadBaseProperty<Type>
{
protected:
	ComputeFunEx<Type, DependTypeFirst, DependTypeSecond> m_dependsFun;	/*!< callback of depend change*/

	struct
	{
		DependTypeFirst m_firstDependancyValue;
		DependTypeSecond m_secondDependancyValue;
	}m_dependingValues;			/*!< depending values*/

public:
	MCadDependPropertyEx( ) = delete;
	explicit MCadDependPropertyEx(const std::string_view& a_name) : MCadBaseProperty<Type>{ a_name } {}
	explicit MCadDependPropertyEx(const std::string_view& a_name, Type&& a_defaultValue) : MCadBaseProperty<Type>{ a_name, std::move(a_defaultValue) } {}
	void setDependancies(const ComputeFunEx<Type, DependTypeFirst, DependTypeSecond>& a_callback, MCadBaseProperty<DependTypeFirst>& a_dependFirst, MCadBaseProperty<DependTypeSecond>& a_dependSecond)
	{
		// initialize
		m_dependsFun = a_callback;
		m_dependingValues.m_firstDependancyValue = a_dependFirst.value( );
		m_dependingValues.m_secondDependancyValue = a_dependSecond.value( );
		m_dependsFun(MCadBaseProperty<Type>::m_propertyValue, a_dependFirst.value( ), a_dependSecond.value( ));

		// setup callbacks
		a_dependFirst.addReactor([ this ] (const std::string&, const DependTypeFirst&, const DependTypeFirst& a_newValue)
			{
				this->callReactors(MCadBaseProperty<Type>::m_propertyValue, m_dependsFun(MCadBaseProperty<Type>::m_propertyValue, a_newValue, m_dependingValues.m_secondDependancyValue));
				m_dependingValues.m_firstDependancyValue = a_newValue;
			});
		a_dependSecond.addReactor([ this ] (const std::string&, const DependTypeSecond&, const DependTypeSecond& a_newValue)
			{
				this->callReactors(MCadBaseProperty<Type>::m_propertyValue, m_dependsFun(MCadBaseProperty<Type>::m_propertyValue, m_dependingValues.m_firstDependancyValue, a_newValue));
				m_dependingValues.m_secondDependancyValue = a_newValue;
			});
	}
};