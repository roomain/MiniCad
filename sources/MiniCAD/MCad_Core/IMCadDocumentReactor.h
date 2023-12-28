#pragma once
/***********************************************
* @headerfile IMCadDocumentReactor.h
* @date 22 / 07 / 2023
* @author Roomain
************************************************/
#include "RTTIDefinition_macros.h"

/*@brief base document reactor*/
class IMCadDocumentReactor
{
	DECLARE_RTTI(1, IMCadDocumentReactor)
public:
	/*@brief is active*/
	virtual bool enabled( )const noexcept = 0;
};
