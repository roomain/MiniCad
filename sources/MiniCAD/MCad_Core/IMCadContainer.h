#pragma once
/***********************************************
* @headerfile IMCadContainer.h
* @date 23 / 07 / 2023
* @author Roomain
************************************************/
#include <type_traits>
#include <functional>
#include <list>
#include "MCadObject.h"


/*@brief interface for MCad objects*/
template<typename Contained> requires std::is_base_of_v<MCadObject, Contained>
class IMCadContainer : public MCadObject
{
	DECLARE_RTTI_DERIVED(1, IMCadContainer<Contained>, MCadObject)
public:
	using ContainedPtr = std::shared_ptr<Contained>;
	using Predicate = std::function<bool(ContainedPtr&&)>;
	struct ItemInfo
	{
		ObjectUID m_objRemoved;
		size_t m_index;
	};

protected:

	/*@brief doAdd new object*/
	virtual void do_Add(const ContainedPtr& a_Object) = 0;
	virtual void do_Add(ContainedPtr&& a_Object) = 0;
	virtual void do_Insert(const size_t& a_at, const ContainedPtr& a_Object) = 0;
	virtual void do_Insert(const size_t& a_at, ContainedPtr&& a_Object) = 0;

	virtual bool do_Remove(const ContainedPtr& a_Object, size_t& a_index) = 0;
	virtual bool do_Remove(const size_t& a_index, ObjectUID& a_objID) = 0;
	virtual void do_Remove_if(Predicate& a_predicate, std::list<ItemInfo>& a_lErased) = 0;
	virtual void do_clear(std::list<ItemInfo>& a_lErased) = 0;


	inline void assertObjectAdded(const ItemInfo& a_itemInfo)const
	{
		// only in container
	}

	inline void assertObjectInserted(const ItemInfo& a_itemInfo)const
	{
		// only in container
	}

	inline void assertObjectRemoved(const ItemInfo& a_itemInfo)const
	{
		// only in container
	}

public:
	IMCadContainer() = default;
	virtual ~IMCadContainer() = default;

	/*@brief add object to container*/
	/*@return true if correctly added*/
	inline virtual bool add(const ContainedPtr& a_object)
	{
		do_Add(a_object);
		assertObjectAdded(ItemInfo{ a_object->uid(), count() - 1 });
		return true;
	}

	/*@brief add object to container*/
	/*@return true if correctly added*/
	inline virtual bool add(ContainedPtr&& a_object)
	{
		do_Add(a_object);
		assertObjectAdded(ItemInfo{ a_object->uid(), count() - 1 });
		return true;
	}

	inline virtual bool set(const size_t& index, const ContainedPtr& a_object)
	{
		removeAt(index);
		return insert(index, a_object);
	}

	/*@brief add object to container*/
	/*@return true if correctly added*/
	inline virtual bool set(const size_t& index, ContainedPtr&& a_object)
	{
		removeAt(index);
		return insert(index, a_object);
	}


	/*@brief insert object to container*/
	/*@return true if correctly added*/
	inline virtual bool insert(const size_t& a_at, const ContainedPtr& a_object)
	{
		do_Insert(a_at, a_object);
		assertObjectInserted(ItemInfo{ a_object->uid(), a_at });
		return true;
	}

	/*@brief insert object to container*/
	/*@return true if correctly added*/
	inline virtual bool insert(const size_t& a_at, ContainedPtr&& a_object)
	{
		do_Insert(a_at, a_object);
		assertObjectInserted(ItemInfo{ a_object->uid(), a_at });
		return true;
	}

	inline virtual void remove(const ContainedPtr& a_object)
	{
		size_t index = 0;
		if (do_Remove(a_object, index))
			assertObjectRemoved(ItemInfo{ a_object->uid(), index });
	}


	inline void remove(const std::weak_ptr<Contained>& a_object)
	{
		size_t index = 0;
		if (do_Remove(a_object.lock(), index))
			assertObjectRemoved(ItemInfo{ a_object.lock()->uid(), index });
	}


	inline void removeAt(const size_t& a_at)
	{
		ObjectUID objUID = 0;
		if (do_Remove(a_at, objUID))
			assertObjectRemoved(ItemInfo{ objUID, a_at });
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

	virtual [[nodiscard]] bool empty()const = 0;
	virtual [[nodiscard]] size_t count()const = 0;
};

template<typename Contained>
class IMCadFilterContainer : public IMCadContainer<Contained>
{
	DECLARE_RTTI_DERIVED(1, IMCadFilterContainer<Contained>, IMCadContainer<Contained>)
public:
	using ContainedPtr = std::shared_ptr<Contained>;

protected:
	virtual [[nodiscard]] bool filter(const ContainedPtr& a_Object) = 0;

public:
	IMCadFilterContainer() = default;
	virtual ~IMCadFilterContainer() = default;

	/*@brief add object to container*/
	/*@return true if correctly added*/
	virtual [[nodiscard]] bool add(const ContainedPtr& a_object) override
	{
		if (filter(a_object))
			return IMCadContainer<Contained>::add(a_object);

		return false;
	}

	/*@brief add object to container*/
	/*@return true if correctly added*/
	virtual [[nodiscard]] bool add(ContainedPtr&& a_object)override
	{
		if (filter(a_object))
			return IMCadContainer<Contained>::add(a_object);

		return false;
	}

	virtual [[nodiscard]] bool insert(const size_t& a_at, const ContainedPtr& a_object)override
	{
		if (filter(a_object))
			return insert<Contained>::add(a_at, a_object);

		return false;
	}

	/*@brief insert object to container*/
	/*@return true if correctly added*/
	virtual [[nodiscard]] bool insert(const size_t& a_at, ContainedPtr&& a_object)override
	{
		if (filter(a_object))
			return insert<Contained>::add(a_at, a_object);

		return false;
	}

};