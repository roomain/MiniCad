#include "CppUnitTest.h"
#include "MCadRecordSession.h"
#include "MCadDocumentManager.h"
#include "MCadDocument.h"
#include "IMCadDocumentReactor.h"
#include "TestUndoRedo_Resources.h"
#include "TMCadVector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMCadCore
{
	TEST_CLASS(TestMCadCore_Memory)
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
		TEST_METHOD(Test_MShared_from_this_cast)
		{
			MCadShared_ptr<MCadTestObject> pTest = make_MShared<MCadTestObject>( );
			MCadShared_ptr<MCadObject> pTestCast = pTest->shared_from_this<MCadObject>( );
			Assert::IsNotNull(pTestCast.get( ), L"Wrong shared_from_this");
		}

	};
}
