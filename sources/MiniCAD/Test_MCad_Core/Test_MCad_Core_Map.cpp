#include "CppUnitTest.h"
#include "MCadRecordSession.h"
#include "MCadDocumentManager.h"
#include "MCadDocument.h"
#include "IMCadDocumentReactor.h"
#include "TestUndoRedo_Resources.h"
#include "TMCadMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMCadCore
{
	TEST_CLASS(TestMCadCore_Map)
	{
	public:
		TEST_CLASS_INITIALIZE(InitClass)
		{
			IMCadObjectReactor::initDef( );
			TMCadReactive<IMCadObjectReactor>::initDef( );
			MCadObject::initDef( );
			IMCadDocumentReactor::initDef( );
			TMCadReactive<IMCadDocumentReactor>::initDef( );
			MCadDocument::initDef( );
			MCadTestObject::initDef( );
			auto pDoc = MCadDocumentManager::Instance( ).createDocument( );
		}

		TEST_CLASS_CLEANUP(CleanupClass)
		{
			MCadDocumentManager::Instance( ).closeAllDocument( );
			MCadTestObject::releaseDef( );
			MCadDocument::releaseDef( );
			TMCadReactive<IMCadDocumentReactor>::releaseDef( );
			IMCadDocumentReactor::releaseDef( );
			MCadObject::releaseDef( );
			TMCadReactive<IMCadObjectReactor>::releaseDef( );
			IMCadObjectReactor::releaseDef( );
		}

		TEST_METHOD_CLEANUP(Test_cleanup)
		{
			auto pDoc = MCadDocumentManager::Instance( ).createDocument( );
			pDoc->undoRedo( ).clear( );
		}
		//-------------------------------------------------------------------------
		TEST_METHOD(Test_TMCadMap_createObject_Undo)
		{
			//;
		}

		TEST_METHOD(Test_TMCadMap_createObject_Redo)
		{
			//
		}

		TEST_METHOD(Test_TMCadMap_createAndDeleteObject_Redo)
		{
			//
		}

		TEST_METHOD(Test_TMCadMap_DeleteObject_Redo)
		{
			//
		}


		TEST_METHOD(Test_ChangeByNull)
		{
			//
		}


	};
}
