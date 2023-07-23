#pragma once
/***********************************************
* @headerfile IMCadDocManagerReactor.h
* @date 22 / 07 / 2023
* @author Roomain
************************************************/
#include "RTTIDefinition_macros.h"

class MCadDocument;

/*@brief interface for document manager reactor*/
class IMCadDocManagerReactor
{
	DECLARE_RTTI(1, IMCadDocManagerReactor)
public:
	IMCadDocManagerReactor() = default;
	virtual ~IMCadDocManagerReactor() = default;

	virtual void onNewDocument(const MCadDocument*) = 0;
	virtual void onCurrentDocument(const MCadDocument*) = 0;
};