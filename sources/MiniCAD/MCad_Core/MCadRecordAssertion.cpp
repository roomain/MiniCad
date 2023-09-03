#include "pch.h"
#include "MCadRecordAssertion.h"
#include "MCadObject.h"

void assertModification(MCadObject* const a_object)
{
	if (auto pDoc = a_object->document().lock())
	{
		if (pDoc->undoRedo().active())
		{
			//
		}
	}
}

void assertDeletion(const MCadObject* a_object)
{
	if (auto pDoc = a_object->document().lock())
	{
		if (pDoc->undoRedo().active())
		{
			//
		}
	}
}