#include "pch.h"
#include "MCadRecordAssertion.h"
#include "MCadObject.h"
#include "MCadObjectRecords.h"
#include <variant>


void assertModification(MCadObject* const a_object)
{
	if (auto pDoc = a_object->document().lock())
	{
		if (pDoc->undoRedo().active())
		{
			auto& session = pDoc->undoRedo( ).currentSession( );
			session.append(std::make_shared<MCadRecordModification>(a_object, session.outputStream()));
		}
	}
}

void assertDeletion(const MCadObject* a_object)
{
	if (auto pDoc = a_object->document().lock())
	{
		if (pDoc->undoRedo().active())
		{
			auto& session = pDoc->undoRedo( ).currentSession( );
			session.append(std::make_shared<MCadRecordDeletion>(a_object, session.outputStream( )));
		}
	}
}