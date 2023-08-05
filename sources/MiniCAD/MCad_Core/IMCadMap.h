#pragma once
/***********************************************
* @headerfile IMCadMap.h
* @date 04 / 08 / 2023
* @author Roomain
************************************************/
#include <string>
#include <memory>
#include <functional>
#include <list>

/*@brief interface for map*/
template<typename Contained>
class IMCadMap
{
public:
	using ContainedPtr = std::shared_ptr<Contained>;
	using Predicate = std::function<bool(ContainedPtr&&)>;
	struct ItemInfo
	{
		ObjectUID m_objRemoved;
		std::string m_key;
	};

protected:
	virtual void do_emplace(const std::string& a_key, ContainedPtr& a_object) = 0;
	virtual void do_emplace(const std::string_view& a_key, ContainedPtr& a_object) = 0;
	virtual bool do_remove(const std::string& a_key, ItemInfo& a_data) = 0;
	virtual bool do_remove(const std::string_view& a_key, ItemInfo& a_data) = 0;
	virtual void do_Remove_if(Predicate& a_predicate, std::list<ItemInfo>& a_lErased) = 0;
	virtual void do_clear(std::list<ItemInfo>& a_lErased) = 0;

	inline void assertObjectAdded(const ItemInfo& a_itemInfo)const
	{
		// only in container
	}

	inline void assertObjectRemoved(const ItemInfo& a_itemInfo)const
	{
		// only in container
	}

public:

	inline void emplace(const std::string& a_key, ContainedPtr& a_object)
	{
		remove(a_key);
		do_emplace(a_key, a_object);
		assertObjectAdded(ItemInfo{ a_key, a_object->uid() });
	}

	inline void emplace(const std::string_view& a_key, ContainedPtr& a_object)
	{
		remove(a_key);
		do_emplace(a_key, a_object);
		assertObjectAdded(ItemInfo{ a_key, a_object->uid() });
	}

	inline void remove(const std::string& a_key)
	{
		ItemInfo data;
		if (do_Remove(a_key, data))
			assertObjectRemoved(data);
	}

	inline void remove(const std::string_view& a_key)
	{
		ItemInfo data;
		if (do_Remove(a_key, data))
			assertObjectRemoved(data);
	}

	inline void remove_if(Predicate& a_predicate)
	{
		std::list<ItemInfo> lErased;
		do_Remove_if(a_predicate, lErased);

		for (const auto& info : lErased)
			assertObjectRemoved(info);
	}

	inline void clear()
	{
		std::list<ItemInfo> lErased;
		do_Clear(lErased);

		for (const auto& info : lErased)
			assertObjectRemoved(info);
	}

	virtual const ContainedPtr& at(const std::string& a_key)const = 0;
	virtual const ContainedPtr& at(const std::string_view& a_key)const = 0;

	virtual [[nodiscard]] size_t size()const = 0;
	virtual [[nodiscard]] bool empty()const noexcept = 0;

	virtual [[nodiscard]] bool contains(const std::string& a_key)const = 0;
	virtual [[nodiscard]] bool contains(const std::string_view& a_key)const = 0;
	virtual [[nodiscard]] bool contains(const ContainedPtr& a_value)const = 0;
};