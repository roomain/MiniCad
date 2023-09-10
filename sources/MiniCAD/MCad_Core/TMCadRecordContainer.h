#pragma once
/***********************************************
* @headerfile TMCadRecordContainer.h
* @date 07 / 09 / 2023
* @author Roomain
************************************************/
#include <variant>
#include "MCadMemory.h"
#include "MCadRef.h"
#include "TIMCadContainer.h"
#include "IMCadRecord.h"



template<typename Key, typename ContainerLnk>
class TMCadRecordContainerInsert : public IMCadRecord
{
	//
};

template<typename Key, typename ContainerLnk>
class TMCadRecordContainerRemoved : public IMCadRecord
{
	//
};

template<typename Key, typename ContainerLnk>
class TMCadRecordContainerChanged : public IMCadRecord
{
	//
};