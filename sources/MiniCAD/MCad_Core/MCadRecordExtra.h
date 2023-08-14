#pragma once
/***********************************************
* @headerfile MCadRecordExtra.h
* @date 06 / 08 / 2023
* @author Roomain
************************************************/
#include <variant>
#include <string>
#include <utility>
#include "MCadObject.h"


/*@brief Provides Extra data for recod used in Undo/Redo. These extras bring data from containers*/

/*@brief container item changed*/
struct ItemChanged
{
	ObjectUID m_oldID;	/*!< old object id*/
	ObjectUID m_newID;	/*!< new object id*/
	MCadObjectWPtr m_pOld;	/*!< pointer on old object*/
	MCadObjectWPtr m_pNew;	/*!< pointer on new object*/
};

/*@brief change on indexed item*/
struct IndexedItem : ItemChanged
{
	size_t m_index;		/*!< item index*/
};

/*@brief change on dictionary item*/
struct KeyItem : ItemChanged
{
	std::string m_key;		/*!< item key*/
};

using RecordExtra = std::variant<IndexedItem, KeyItem>;

inline ItemChanged swapItem(const ItemChanged& a_toSwap)
{
	ItemChanged swapped = a_toSwap;
	std::swap(swapped.m_newID, swapped.m_oldID);
	std::swap(swapped.m_pNew, swapped.m_pOld);
	return swapped;
}