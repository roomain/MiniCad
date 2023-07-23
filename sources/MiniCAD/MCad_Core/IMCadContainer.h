#pragma once
/***********************************************
* @headerfile IMCadContainer.h
* @date 23 / 07 / 2023
* @author Roomain
************************************************/
#include "MCadObject.h"

/*@brief interface for MCad objects*/
template<typename Contained, typename Container>
class IMCadContainer : public MCadObject
{
	DECLARE_RTTI_DERIVED(1, IMCadContainer<Contained, Container>, MCadObject)
protected:
	Container m_container;

	/*@brief emplace new object*/
	virtual void emplace(const Contained& a_Object) = 0;
	virtual void emplace(Contained&& a_Object) = 0;

public:
	IMCadContainer() = default;
	virtual ~IMCadContainer() = default;

	/*@brief add object to container*/
	/*@return true if correctly added*/
	virtual [[nodiscard]] bool add(const Contained& a_object)
	{
		emplace(a_object);
		return true;
	}

	/*@brief add object to container*/
	/*@return true if correctly added*/
	virtual [[nodiscard]] bool add(Contained&& a_object)
	{
		emplace(a_object);
		return true;
	}

	virtual [[nodiscard]] size_t count()const = 0;
	Container::iterator begin() { return m_container.begin(); }
	Container::iterator end() { return m_container.end(); }
	Container::const_iterator cbegin() { return m_container.cbegin(); }
	Container::const_iterator cend() { return m_container.cend(); }
};

template<typename Contained, typename Container>
class IMCadFilterContainer : public IMCadContainer<Contained, Container>
{
	DECLARE_RTTI_DERIVED(1, IMCadFilterContainer<Contained, Container>, IMCadContainer<Contained, Container>)
protected:
	virtual [[nodiscard]] bool filter(const Contained& a_Object) = 0;

public:
	IMCadFilterContainer() = default;
	virtual ~IMCadFilterContainer() = default;

	/*@brief add object to container*/
	/*@return true if correctly added*/
	virtual [[nodiscard]] bool add(const Contained& a_object)
	{
		if (filter(a_object))
		{
			emplace(a_object);
			return true;
		}
		return false;
	}

	/*@brief add object to container*/
	/*@return true if correctly added*/
	virtual [[nodiscard]] bool add(Contained&& a_object)
	{
		if (filter(a_object))
		{
			emplace(std::move(a_object));
			return true;
		}
		return false;
	}
};