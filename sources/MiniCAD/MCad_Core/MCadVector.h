#pragma once
/***********************************************
* @headerfile MCadVector.h
* @date 01 / 08 / 2023
* @author Roomain
************************************************/
#include <vector>
#include <memory>
#include <type_traits>
#include "MCadObject.h"

/*@brief vector contained derivated MCadObject can be used in undo/redo*/

// REVOIR: Object pouvant être undo/redo
template<typename Contained> requires std::is_base_of<MCadObject, Contained>::Value
class MCadVector : public MCadObject
{
	DECLARE_RTTI_DERIVED(1, MCadVector<Contained>, MCadObject)
private:
	std::vector<std::shared_ptr<Contained>> m_container;	/*!< vector container*/

public:
	using iterator = std::vector<std::shared_ptr<Contained>>::iterator;
	using const_iterator = std::vector<std::shared_ptr<Contained>>::const_iterator;
	MCadVector() = default;
	virtual ~MCadVector()
	{
		// TODO
	}


	void clear()
	{
		//TODO
		m_container.clear();
	}
	template< class... Args >
	iterator emplace(const_iterator pos, Args&&... args)
	{
		// TODO
		m_container.emplace(pos, args...);
	}
	template< class... Args >
	constexpr iterator emplace(const_iterator pos, Args&&... args)
	{
		// TODO
		m_container.emplace(pos, args...);
	}
	[[nodiscard]] constexpr bool empty()const { return m_container.empty(); }
	void reserve(const size_t& a_size) { m_container.reserve(a_size); }
	[[nodiscard]] constexpr size_t size()const { return m_container.size(); }
	constexpr iterator begin() { return m_container.begin(); }
	constexpr iterator end() { return m_container.end(); }
	constexpr const_iterator cbegin()const { return m_container.cbegin(); }
	constexpr const_iterator cend()const { return m_container.cend(); }
};