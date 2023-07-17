#pragma once
/***********************************************
* @headerfile RTTIException_macro.h
* @date 16 / 07 / 2023
* @author Roomain
************************************************/
#ifndef RTTI_EXCEPTION
#define RTTI_EXCEPTION
#endif

RTTI_EXCEPTION(Except_ParentNotDefined, "RTTI parent definition is not initialized")
RTTI_EXCEPTION(Except_NotDefined, "RTTI definition is not initialized")
RTTI_EXCEPTION(Except_AlreadyDefined, "RTTI definition is already initialized")
RTTI_EXCEPTION(Except_CantUnitialize, "RTTI definition is still used by inherited class")
