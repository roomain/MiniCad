#include "CppUnitTest.h"
#include <string>
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
			MCadReactive<IMCadObjectReactor>::initDef( );
			MCadObject::initDef( );
			IMCadDocumentReactor::initDef( );
			MCadReactive<IMCadDocumentReactor>::initDef( );
			MCadDocument::initDef( );
			MCadTestObject::initDef( );
			auto pDoc = MCadDocumentManager::Instance( ).createDocument( );
		}

		TEST_CLASS_CLEANUP(CleanupClass)
		{
			MCadDocumentManager::Instance( ).closeAllDocument( );
			MCadTestObject::releaseDef( );
			MCadDocument::releaseDef( );
			MCadReactive<IMCadDocumentReactor>::releaseDef( );
			IMCadDocumentReactor::releaseDef( );
			MCadObject::releaseDef( );
			MCadReactive<IMCadObjectReactor>::releaseDef( );
			IMCadObjectReactor::releaseDef( );
		}

		TEST_METHOD_CLEANUP(Test_cleanup)
		{
			auto pDoc = MCadDocumentManager::Instance( ).createDocument( );
			pDoc->undoRedo( ).clear( );
		}
		//-------------------------------------------------------------------------
		
		TEST_METHOD(Test_operator)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			TMCadMap<std::string, MCadTestObject> map;
			auto ptr = MCadTestObject::createObject( );
			auto ptr1 = MCadTestObject::createObject( );
			map [ "test" ] = ptr;
			map [ "test" ] = ptr1;
		}

		TEST_METHOD(Test_undo_add)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			TMCadMap<std::string, MCadTestObject> map;
			auto ptr = MCadTestObject::createObject( );
			ptr->setValue(1);

			Assert::AreEqual(0, static_cast< int >( map.size( ) ), L"Wrong size");
			pWDoc.lock( )->undoRedo( ).startUndoRecord("Test_Add");
			map [ "test" ] = ptr;
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );
			Assert::AreEqual(1, static_cast< int >( map.size( ) ), L"Wrong size");
			Assert::IsTrue(pWDoc.lock( )->undoRedo( ).hasUndo( ), L"No undo");
			pWDoc.lock( )->undoRedo( ).undo( );
			Assert::AreEqual(0, static_cast< int >( map.size( ) ), L"Wrong size");
		}

		TEST_METHOD(Test_undo_redo_add)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			TMCadMap<std::string, MCadTestObject> map;
			auto ptr = MCadTestObject::createObject( );
			ptr->setValue(1);

			Assert::AreEqual(0, static_cast< int >( map.size( ) ), L"Wrong size");
			pWDoc.lock( )->undoRedo( ).startUndoRecord("Test_Add");
			map [ "test" ] = ptr;
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );
			Assert::AreEqual(1, static_cast< int >( map.size( ) ), L"Wrong size");
			Assert::IsTrue(pWDoc.lock( )->undoRedo( ).hasUndo( ), L"No undo");
			pWDoc.lock( )->undoRedo( ).undo( );
			Assert::AreEqual(0, static_cast< int >( map.size( ) ), L"Wrong size");
			pWDoc.lock( )->undoRedo( ).redo( );
			Assert::AreEqual(1, static_cast< int >( map.size( ) ), L"Wrong size");

			Assert::AreEqual(1, map.at("test")->value( ), L"Wrong int");

			// test same pointer
			Assert::IsTrue(map.at("test") == ptr, L"Not same pointer");
		}

		TEST_METHOD(Test_undo_change_stack)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			TMCadMap<std::string, MCadTestObject> map;
			auto ptr = MCadTestObject::createObject( );
			ptr->setValue(1);


			auto ptr2 = MCadTestObject::createObject( );
			ptr2->setValue(8);


			map [ "test" ] = ptr;
			Assert::IsTrue(map.at("test") == ptr, L"Not same pointer");
			pWDoc.lock( )->undoRedo( ).startUndoRecord("Test_change");
			map [ "test" ] = ptr2;
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );

			Assert::IsTrue(map.at("test") == ptr2, L"Not same pointer");
			Assert::IsTrue(pWDoc.lock( )->undoRedo( ).hasUndo( ), L"No undo");

			pWDoc.lock( )->undoRedo( ).undo( );
			Assert::IsTrue(map.at("test") == ptr, L"Not same pointer");
		}

		TEST_METHOD(Test_undo_redo_change_stack)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			TMCadMap<std::string, MCadTestObject> map;
			auto ptr = MCadTestObject::createObject( );
			ptr->setValue(1);


			auto ptr2 = MCadTestObject::createObject( );
			ptr2->setValue(8);


			map [ "test" ] = ptr;
			Assert::IsTrue(map.at("test") == ptr, L"Not same pointer");
			pWDoc.lock( )->undoRedo( ).startUndoRecord("Test_change");
			map [ "test" ] = ptr2;
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );

			Assert::IsTrue(map.at("test") == ptr2, L"Not same pointer");
			Assert::IsTrue(pWDoc.lock( )->undoRedo( ).hasUndo( ), L"No undo");

			pWDoc.lock( )->undoRedo( ).undo( );
			Assert::IsTrue(map.at("test") == ptr, L"Not same pointer");

			pWDoc.lock( )->undoRedo( ).redo( );
			Assert::IsTrue(map.at("test") == ptr2, L"Not same pointer");
		}

		TEST_METHOD(Test_undo_erase_stack)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			TMCadMap<std::string, MCadTestObject> map;

			{
				auto ptr = MCadTestObject::createObject( );
				ptr->setValue(1);
				map [ "test" ] = ptr;
			}

			Assert::AreEqual(1, static_cast< int >( map.size( ) ), L"Wrong size");
			pWDoc.lock( )->undoRedo( ).startUndoRecord("Test_erase");
			map.erase("test");
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );
			Assert::AreEqual(0, static_cast< int >( map.size( ) ), L"Wrong size");

			pWDoc.lock( )->undoRedo( ).undo( );
			Assert::AreEqual(1, static_cast< int >( map.size( ) ), L"Wrong size");

			Assert::AreEqual(1, map.at("test")->value( ), L"Wrong int");
		}

		TEST_METHOD(Test_undo_redo_erase_stack)
		{
			auto pWDoc = MCadDocumentManager::Instance( ).currentDocument( );
			TMCadMap<std::string, MCadTestObject> map;

			{
				auto ptr = MCadTestObject::createObject( );
				ptr->setValue(1);
				map [ "test" ] = ptr;
			}

			Assert::AreEqual(1, static_cast< int >( map.size( ) ), L"Wrong size");
			pWDoc.lock( )->undoRedo( ).startUndoRecord("Test_erase");
			map.erase("test");
			pWDoc.lock( )->undoRedo( ).endUndoRecord( );
			Assert::AreEqual(0, static_cast< int >( map.size( ) ), L"Wrong size");

			pWDoc.lock( )->undoRedo( ).undo( );
			Assert::AreEqual(1, static_cast< int >( map.size( ) ), L"Wrong size");

			Assert::AreEqual(1, map.at("test")->value( ), L"Wrong int");

			pWDoc.lock( )->undoRedo( ).redo( );
			Assert::AreEqual(0, static_cast< int >( map.size( ) ), L"Wrong size");
		}

	};
}
