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
	TEST_CLASS(TestMCadCore_Vector)
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
		TEST_METHOD(Test_TMCadVector_createObject_Undo)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			UndoRedo::TMCadVector<MCadTestObjectPtr> vector;
			Assert::IsTrue(vector.empty( ), L"Vector Not empty");
			pWDoc.lock( )->undoRedo( ).startUndoRecord("Create object");
			vector.push_back(MCadTestObject::createObject( ));
			Assert::AreEqual(1, static_cast< int >( vector.size( ) ), L"Wrong vector size after push_back");
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );
			
			pWDoc.lock( )->undoRedo( ).undo( );
			Assert::IsTrue(vector.empty( ), L"Vector Not empty after undo");
		}

		TEST_METHOD(Test_TMCadVector_createObject_Redo)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			UndoRedo::TMCadVector<MCadTestObjectPtr> vector;
			Assert::IsTrue(vector.empty( ), L"Vector Not empty");
			pWDoc.lock( )->undoRedo( ).startUndoRecord("Create object");
			auto pTestObj = MCadTestObject::createObject( );
			vector.push_back(pTestObj);
			Assert::AreEqual(1, static_cast< int >( vector.size( ) ), L"Wrong vector size after push_back");
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );
			
			pWDoc.lock( )->undoRedo( ).undo( );
			Assert::IsTrue(vector.empty( ), L"Vector Not empty after undo");
			pWDoc.lock( )->undoRedo( ).redo( );
			Assert::AreEqual(1, static_cast< int >( vector.size( ) ), L"Vector empty after redo");
		}

		TEST_METHOD(Test_TMCadVector_createAndDeleteObject_Redo)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			UndoRedo::TMCadVector<MCadTestObjectPtr> vector;
			Assert::IsTrue(vector.empty( ), L"Vector Not empty");
			pWDoc.lock( )->undoRedo( ).startUndoRecord("Create object");
			vector.push_back(MCadTestObject::createObject( ));
			Assert::AreEqual(1, static_cast< int >( vector.size( ) ), L"Wrong vector size after push_back");
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );
			
			pWDoc.lock( )->undoRedo( ).undo( );
			Assert::IsTrue(vector.empty( ), L"Vector Not empty after undo");
			pWDoc.lock( )->undoRedo( ).redo( );
			Assert::AreEqual(1, static_cast< int >( vector.size( ) ), L"Vector empty after redo");
		}

		TEST_METHOD(Test_TMCadVector_DeleteObject_Redo)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			UndoRedo::TMCadVector<MCadTestObjectPtr> vector;
			Assert::IsTrue(vector.empty( ), L"Vector Not empty");
			pWDoc.lock( )->undoRedo( ).startUndoRecord("Create object");
			vector.push_back(MCadTestObject::createObject( ));
			Assert::AreEqual(1, static_cast< int >( vector.size( ) ), L"Wrong vector size after push_back");
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );
			
			pWDoc.lock( )->undoRedo( ).startUndoRecord("Remove object");
			vector.pop_back( );
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );
			Assert::IsTrue(vector.empty( ), L"Vector Not empty");
			
			pWDoc.lock( )->undoRedo( ).undo( );
			Assert::AreEqual(1, static_cast< int >( vector.size( ) ), L"Vector empty after redo");
		}

		TEST_METHOD(Test_reserve)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			UndoRedo::TMCadVector<MCadTestObjectPtr> vec(5);
			auto ptr = MCadTestObject::createObject( );
			Assert::AreEqual(5, static_cast< int >( vec.size( ) ), L"Wrong size");
			
			pWDoc.lock( )->undoRedo( ).startUndoRecord("change empty object");
			vec[0] = ptr;
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );
			pWDoc.lock( )->undoRedo( ).undo( );
			Assert::AreEqual(5, static_cast< int >( vec.size( ) ), L"Wrong size undo");
			Assert::IsNull(vec.at(0).get( ), L"pointer is not null");
			pWDoc.lock( )->undoRedo( ).redo( );
			Assert::IsTrue(vec.at(0) == ptr, L"Not same pointer redo");
			Assert::AreEqual(5, static_cast< int >( vec.size( ) ), L"Wrong size redo");
		}

		TEST_METHOD(Test_ChangeByNull)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			UndoRedo::TMCadVector<MCadTestObjectPtr> vec;
			auto ptr = MCadTestObject::createObject( );
			pWDoc.lock( )->undoRedo( ).startUndoRecord("Create");
			vec.push_back(ptr);
			pWDoc.lock( )->undoRedo( ).startUndoRecord("change empty object");
			vec [ 0 ] = MCadTestObjectPtr();
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );
			pWDoc.lock( )->undoRedo( ).undo( );
			Assert::IsTrue(vec.at(0) == ptr, L"Not same pointer redo");
			pWDoc.lock( )->undoRedo( ).redo( );
			Assert::IsNull(vec.at(0).get( ), L"pointer is not null");
		}

		TEST_METHOD(Test_Resize)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			UndoRedo::TMCadVector<MCadTestObjectPtr> vec;
			auto ptr = MCadTestObject::createObject( );
			vec.push_back(ptr);
			Assert::IsTrue(vec [ 0 ].hasAffectationCallback( ), L"Callback is missing");
			vec.resize(2);
			Assert::IsTrue(vec [ 0 ].hasAffectationCallback( ), L"Callback is missing after resize");
		}

	};
}
