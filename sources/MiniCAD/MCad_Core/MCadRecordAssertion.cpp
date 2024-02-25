#include "pch.h"
#include "MCadRecordAssertion.h"
#include "MCadObject.h"
#include "MCadObjectRecord.h"
#include <variant>

namespace UndoRedo
{

	void assertModification(MCadObject* const a_object)
	{
		if ( auto pDoc = a_object->document( ).lock( ) )
		{
			if ( pDoc->undoRedo( ).active( ) )
			{
				auto& session = pDoc->undoRedo( ).currentSession( );
				session.append(std::make_shared<MCadObjectRecord>(a_object->objectUID( ), session.outputStream( ), a_object->isA()));
			}
		}
	}

	void assertDeletion(const MCadObject* a_object)
	{
		if ( auto pDoc = a_object->document( ).lock( ) )
		{
			if ( pDoc->undoRedo( ).active( ) )
			{
				auto& session = pDoc->undoRedo( ).currentSession( );
				session.append(std::make_shared<MCadObjectRecord>(a_object->objectUID( ), session.outputStream( ), a_object->isA( )));
			}
		}
	}

}