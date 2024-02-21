#pragma once
/***********************************************
* @headerfile MCadUndoAssertion.h
* @date 02 / 09 / 2023
* @author Roomain
************************************************/
#include "MCad_Core_globals.h"
#include "MCad_traits.h"

// forward declare
class MCadObject;

namespace UndoRedo
{
	/*@brief Assertion for simple object -----------------------------------------------------------*/
	/*@brief assertion on modification*/
	void MCAD_CORE_EXPORT assertModification(MCadObject* const a_object);

	/*@brief assertion on deletion*/
	void MCAD_CORE_EXPORT assertDeletion(const MCadObject* a_object);
}