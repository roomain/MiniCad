#pragma once
/***********************************************
* @headerfile MCadSelectionSet.h
* @date 23 / 12 / 2023
* @author Roomain
************************************************/
#include <set>
#include <memory>
#include <functional>
#include <type_traits>
#include "MCadObject.h"
#include "MCadMemory.h"


class IMCadSelectionSet
{
public:
	virtual bool append(const MCadShared_ptr<MCadObject>& a_pObject) = 0;
};

template<typename Type>
using SelectionFilter = std::function<bool(const std::shared_ptr<Type>&)>;

/*@brief object selection*/
template <typename Type>
class TMCadSelectionSet : public IMCadSelectionSet
{
private:
	std::set<std::weak_ptr<Type>> m_selection;	/*!< selection onject*/
	SelectionFilter m_filter;					/*!< selection filter*/

public:
	using SelectionIter = std::set<std::weak_ptr<Type>>::const_iterator;

	TMCadSelectionSet( ) = default;
	~TMCadSelectionSet( ) = default;
	void clear( ) { m_selection.clear( ); }
	void setFilter(const SelectionFilter& a_filter)
	{
		m_filter = a_filter;
	}

	inline SelectionIter cbegin( )const { return m_selection.cbegin( ); }
	inline SelectionIter cend( )const { return m_selection.cend( ); }

	virtual bool append(const MCadShared_ptr<MCadObject>& a_pObject)override
	{
		if ( a_pObject->isKindOf<Type>( ) )
		{
			auto pObject = std::static_pointer_cast< Type >( a_pObject );
			if ( m_filter )
			{
				if ( m_filter(pObject) )
				{
					m_selection.emplace(pObject);
					return true;
				}
			}
			else
			{
				m_selection.emplace(pObject);
				return true;
			}
		}
		return false;
	}
};
