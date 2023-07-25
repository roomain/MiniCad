#pragma once
/***********************************************
* @headerfile MCadReactive.h
* @date 19 / 07 / 2023
* @author Roomain
************************************************/
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <ranges>
#include "RTTIDefinition_macros.h"
#include "MCad_Core_globals.h"

#pragma warning(push)
#pragma warning(disable : 4858)

/*@brief base class for reactive object*/
template<typename Reactor>
class MCadReactive
{
	DECLARE_RTTI(1, MCadReactive<Reactor>)
public:
	using ReactorPtr = std::shared_ptr<Reactor>;

protected:
	std::vector<ReactorPtr> m_vReactors;	/*!< reactors of object*/
	
	/*@brief function calling a function of all active reactor from type*/
	template<typename ReactorType, typename Function, typename ...Args>
	inline void foreach_reactor(Function&& a_fun, Args... arguments)
	{
		static auto filter = [](ReactorPtr& a_reac) {return a_reac->isKindOf<ReactorType>() && a_reac->enabled(); };
		static auto bindFun = std::bind_front(a_fun);
		for (auto& reactor : m_vReactors | std::views::filter(filter))
			std::invoke(bindFun, reactor->cast<ReactorType>(), arguments...);
	}

public:
	MCadReactive() = default;
	virtual ~MCadReactive() = default;

	/*@brief reactors management*/
	void add_reactor(const ReactorPtr& a_pReactor)
	{
		m_vReactors.emplace_back(a_pReactor);
	}

	void remove_reactor(const ReactorPtr& a_pReactor)
	{
		std::remove(m_vReactors.begin(), m_vReactors.end(), a_pReactor);
	}

	size_t count_reactor()const
	{
		return m_vReactors.size();
	}

	void remove_allReactor()
	{
		m_vReactors.clear();
	}


	/*@brief remove all reactor of type type*/
	template<typename Type>
	void remove_allReactor()
	{
		std::erase_if(m_vReactors, [](const auto& a_reac) {return a_reac->isKindOf<Type>(); });
	}

	/*@brief count reactor of type type*/
	template<typename Type>
	size_t count_reactor()const
	{
		return std::count_if(m_vReactors.begin(), m_vReactors.end(), [](ReactorPtr& a_reac) {return a_reac->isKindOf<Type>(); });
	}
};
#pragma warning(pop)