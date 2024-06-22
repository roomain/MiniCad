#include "CppUnitTest.h"
#include "MCadRecordSession.h"
#include "MCadDocumentManager.h"
#include "MCadDocument.h"
#include "IMCadDocumentReactor.h"
#include "TestUndoRedo_Resources.h"
#include "TMCadUnordered_map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMCadCore
{
	TEST_CLASS(TestMCadCore_Unordered_map)
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
		TEST_METHOD(Test_TMCadUnordered_map_createObject_Undo)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			UndoRedo::TMCadUnordered_map<std::string, MCadTestObjectPtr> umap;
			
			Assert::IsTrue(umap.empty( ), L"Unordered_map Not empty");
			pWDoc.lock( )->undoRedo( ).startUndoRecord("Create object");
			umap.emplace("test", MCadTestObject::createObject());
			Assert::AreEqual(1, static_cast< int >( umap.size( ) ), L"Wrong Unordered_map size after push_back");
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );

			pWDoc.lock( )->undoRedo( ).undo( );
			Assert::IsTrue(umap.empty( ), L"Unordered_map Not empty after undo");
		}

		TEST_METHOD(Test_TMCadUnordered_map_createObject_Redo)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			UndoRedo::TMCadUnordered_map<std::string, MCadTestObjectPtr> umap;
			Assert::IsTrue(umap.empty( ), L"Vector Not empty");
			pWDoc.lock( )->undoRedo( ).startUndoRecord("Create object");
			auto pTestObj = MCadTestObject::createObject( );
			umap.emplace("test", pTestObj);
			Assert::AreEqual(1, static_cast< int >( umap.size( ) ), L"Wrong vector size after push_back");
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );

			pWDoc.lock( )->undoRedo( ).undo( );
			Assert::IsTrue(umap.empty( ), L"Vector Not empty after undo");
			pWDoc.lock( )->undoRedo( ).redo( );
			Assert::AreEqual(1, static_cast< int >( umap.size( ) ), L"Vector empty after redo");
		}

		TEST_METHOD(Test_TMCadUnordered_map_createAndDeleteObject_Redo)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			UndoRedo::TMCadUnordered_map<std::string, MCadTestObjectPtr> umap;
			Assert::IsTrue(umap.empty( ), L"Vector Not empty");
			pWDoc.lock( )->undoRedo( ).startUndoRecord("Create object");
			umap.emplace("test", MCadTestObject::createObject( ));
			Assert::AreEqual(1, static_cast< int >( umap.size( ) ), L"Wrong vector size after push_back");
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );

			pWDoc.lock( )->undoRedo( ).undo( );
			Assert::IsTrue(umap.empty( ), L"Vector Not empty after undo");
			pWDoc.lock( )->undoRedo( ).redo( );
			Assert::AreEqual(1, static_cast< int >( umap.size( ) ), L"Vector empty after redo");
		}

		TEST_METHOD(Test_TMCadUnordered_map_DeleteObject_Redo)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			UndoRedo::TMCadUnordered_map<std::string, MCadTestObjectPtr> umap;
			Assert::IsTrue(umap.empty( ), L"Vector Not empty");
			pWDoc.lock( )->undoRedo( ).startUndoRecord("Create object");
			umap.emplace("test", MCadTestObject::createObject( ));
			Assert::AreEqual(1, static_cast< int >( umap.size( ) ), L"Wrong vector size after push_back");
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );

			pWDoc.lock( )->undoRedo( ).startUndoRecord("Remove object");
			umap.erase("test");
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );
			Assert::IsTrue(umap.empty( ), L"Vector Not empty");

			pWDoc.lock( )->undoRedo( ).undo( );
			Assert::AreEqual(1, static_cast< int >( umap.size( ) ), L"Vector empty after redo");
		}

		TEST_METHOD(Test_TMCadUnordered_map_DeleteObject_Redo_Ex)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			UndoRedo::TMCadUnordered_map<std::string, MCadTestObjectPtr> umap;
			Assert::IsTrue(umap.empty( ), L"Vector Not empty");
			pWDoc.lock( )->undoRedo( ).startUndoRecord("Create object");
			umap [ "test" ] = MCadTestObject::createObject( );
			Assert::AreEqual(1, static_cast< int >( umap.size( ) ), L"Wrong vector size after push_back");
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );

			pWDoc.lock( )->undoRedo( ).startUndoRecord("Remove object");
			umap.erase("test");
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );
			Assert::IsTrue(umap.empty( ), L"Vector Not empty");

			pWDoc.lock( )->undoRedo( ).undo( );
			Assert::AreEqual(1, static_cast< int >( umap.size( ) ), L"Vector empty after redo");
		}


		TEST_METHOD(Test_ChangeByNull)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			UndoRedo::TMCadUnordered_map<std::string, MCadTestObjectPtr> umap;
			auto ptr = MCadTestObject::createObject( );
			pWDoc.lock( )->undoRedo( ).startUndoRecord("Create");
			umap["test" ] = ptr;
			pWDoc.lock( )->undoRedo( ).startUndoRecord("change empty object");
			umap [ "test" ] = MCadTestObjectPtr( );
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );
			pWDoc.lock( )->undoRedo( ).undo( );
			Assert::IsTrue(umap [ "test" ] == ptr, L"Not same pointer redo");
			pWDoc.lock( )->undoRedo( ).redo( );
			Assert::IsNull(umap [ "test" ].get( ), L"pointer is not null");
		}


	};
}
