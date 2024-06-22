#pragma once
/***********************************************
* @headerfile TMCadUnordered_map.h
* @date 28 / 01 / 2024
* @author Roomain
************************************************/
#include <unordered_map>
#include <utility>
#include <ranges>
#include "MCad_traits.h"
#include "MCadRef.h"
#include "TMCadUnordered_mapRecords.h"
#include "MCadDocumentManager.h"

namespace UndoRedo
{
	template<typename Key, typename Type> requires ( is_MCadShared_base_of<MCadObject, Type>::value )
		class TMCadUnordered_map : public MCadRefObject, private std::unordered_map<Key, Type>
	{

	public:
		using unordered_mapBase = std::unordered_map<Key, Type>;

	private:
		// callback called if item changes
		void assertChange(const Key& a_key, const Type* a_object)
		{
			if ( auto pDoc = MCadDocumentManager::Instance( ).currentDocument( ).lock( ) )
			{
				if ( pDoc->undoRedo( ).active( ) )
				{
					auto& session = pDoc->undoRedo( ).currentSession( );
					auto iter = unordered_mapBase::find(a_key);

					if ( iter != cend( ) )
						session.append(std::make_shared<TMCadUnordered_mapChangeRecord<Key, Type>>(make_ref(*this), a_key, ( *a_object ) ? ( *a_object )->objectUID( ) : MCadObjectUID( ), a_object->objectDef( )));
				}
			}
		}

		void assertInsert(Type& a_object, const Key& a_key)
		{
			a_object.setCallback(std::bind_front(&TMCadUnordered_map<Key, Type>::assertChange, this, a_key));

			if ( auto pDoc = MCadDocumentManager::Instance( ).currentDocument( ).lock( ) )
			{
				if ( pDoc->undoRedo( ).active( ) )
				{
					auto& session = pDoc->undoRedo( ).currentSession( );
					session.append(std::make_shared<TMCadUnordered_mapInsertRecord<Key, Type>>(make_ref(*this), a_key, a_object ? a_object->objectUID( ) : MCadObjectUID( ), a_object.objectDef( )));
				}
			}
		}

		void assertErase(Type& a_object, const Key& a_key)
		{
			if ( auto pDoc = MCadDocumentManager::Instance( ).currentDocument( ).lock( ) )
			{
				if ( pDoc->undoRedo( ).active( ) )
				{
					a_object.setCallback(std::bind_front(&TMCadUnordered_map<Key, Type>::assertChange, this, a_key));
					auto& session = pDoc->undoRedo( ).currentSession( );
					session.append(std::make_shared<TMCadUnordered_mapEraseRecord<Key, Type>>(make_ref(*this), a_key, a_object ? a_object->objectUID( ) : MCadObjectUID( ), a_object.objectDef( )));
				}
			}
		}

	public:
		TMCadUnordered_map( ) = default;
		explicit TMCadUnordered_map(const size_t& a_size) : unordered_mapBase(a_size)
		{
			for ( auto& obj : *this )
				obj.setCallback(std::bind_front(&TMCadUnordered_map<Type>::assertChange, this));
		}

		explicit TMCadUnordered_map(const unordered_mapBase& a_other) : unordered_mapBase(a_other)
		{
			for ( auto& obj : *this )
				obj.setCallback(std::bind_front(&TMCadUnordered_map<Type>::assertChange, this));
		}

		explicit TMCadUnordered_map(const TMCadUnordered_map& a_other) : unordered_mapBase(a_other)
		{
			for ( auto& obj : *this )
				obj.setCallback(std::bind_front(&TMCadUnordered_map<Type>::assertChange, this));
		}

		explicit TMCadUnordered_map(TMCadUnordered_map&& a_other)noexcept : unordered_mapBase(a_other)
		{
			for ( auto& obj : *this )
				obj.setCallback(std::bind_front(&TMCadUnordered_map<Type>::assertChange, this));
		}

		using iterator = std::unordered_map <Key, Type>::iterator;
		using const_iterator = std::unordered_map < Key, Type>::const_iterator;

		template< class... Args >
		std::pair<iterator, bool> try_emplace(const Key& a_key, Args&&... args)
		{
			auto emplaced = unordered_mapBase::try_emplace(a_key, args...);

			if ( emplaced.second )
				assertInsert(emplaced.first->second, a_key);

			return emplaced;
		}

		template< class... Args >
		std::pair<iterator, bool> try_emplace(Key&& a_key, Args&&... args)
		{
			auto emplaced = unordered_mapBase::emplace(a_key, args...);

			if ( emplaced.second )
				assertInsert(emplaced.first->second, a_key);

			return emplaced;
		}


		template< class... Args >
		std::pair<iterator, bool> emplace(Args&&... args)
		{
			auto emplaced = unordered_mapBase::emplace(args...);

			if ( emplaced.second )
				assertInsert(emplaced.first->second, emplaced.first->first);

			return emplaced;
		}

		iterator erase(iterator a_pos)
		{
			assertErase(a_pos->second, a_pos->first);
			return unordered_mapBase::erase(a_pos);
		}

		iterator erase(const_iterator a_pos)
		{
			assertErase(a_pos->second, a_pos->first);
			return unordered_mapBase::erase(a_pos);
		}

		iterator erase(const_iterator a_first, const_iterator a_last)
		{
			std::for_each(a_first, a_last, [ this ] (const auto& a_Iter)
				{
					assertErase(a_Iter->second, a_Iter->first);
				});
			return unordered_mapBase::erase(a_first, a_last);
		}

		size_t erase(const Key& a_key)
		{
			auto iter = unordered_mapBase::find(a_key);
			if(iter != end())
				assertErase(iter->second, iter->first);
			return unordered_mapBase::erase(a_key);
		}

		Type& operator [] (const Key& a_key)
		{
			return try_emplace(a_key, Type{}).first->second;
		}

		Type& operator [] (const Key&& a_key)
		{
			return try_emplace(std::move(a_key), Type{}).first->second;
		}

		using std::unordered_map<Key, Type>::at;
		using std::unordered_map<Key, Type>::begin;
		using std::unordered_map<Key, Type>::end;
		using std::unordered_map<Key, Type>::cbegin;
		using std::unordered_map<Key, Type>::cend;

		using std::unordered_map<Key, Type>::size;
		using std::unordered_map<Key, Type>::max_size;
		using std::unordered_map<Key, Type>::empty;
	};

}