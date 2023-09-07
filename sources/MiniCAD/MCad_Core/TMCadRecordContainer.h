#pragma once
/***********************************************
* @headerfile TMCadRecordContainer.h
* @date 07 / 09 / 2023
* @author Roomain
************************************************/
#include <variant>
#include "MCadMemory.h"
#include "MCadReference.h"
#include "TIMCadContainer.h"
#include "IMCadRecord.h"

template<typename Key>
using ContainerLnk = std::variant<std::weak_ptr<TIMCadContainer<Key>>, Reference<TIMCadContainer<Key>>>;

class ContainerLnkMng
{
	//
};

template<typename Key>
class TMCadRecordContainerInsert : public IMCadRecord, private ContainerLnkMng
{
	//
};

template<typename Key>
class TMCadRecordContainerRemoved : public IMCadRecord, private ContainerLnkMng
{
	//
};

template<typename Key>
class TMCadRecordContainerChanged : public IMCadRecord, private ContainerLnkMng
{
	//
};