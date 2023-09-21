#pragma once
/***********************************************
* @headerfile TMCadVector.h
* @date 20 / 09 / 2023
* @author Roomain
************************************************/
#include <algorithm>
#include <vector>
#include "MCadMemory.h"
#include "TIMCadContainer.h"
#include "MCadCell.h"
#include "TMCadRecordContainer.h"

template<typename Type> requires std::is_base_of_v<MCadObject, Type>
class MCadVector : public TIMCadContainer<size_t>, private std::vector<MCadCell<Type>>
{
    DECLARE_RTTI_DERIVED(1, MCadVector<Type>, MCadObject)

};