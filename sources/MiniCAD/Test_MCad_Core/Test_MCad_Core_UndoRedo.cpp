#include "CppUnitTest.h"
#include "MCadRecordSession.h"
#include "MCadDocumentManager.h"
#include "MCadDocument.h"
#include "IMCadDocumentReactor.h"
#include "TestUndoRedo_Resources.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMCadCore
{
	TEST_CLASS(TestMCadCore_UndoRedo)
	{
	public:
		TEST_CLASS_INITIALIZE(InitClass)
		{
			IMCadObjectReactor::initDef();
			MCadReactive<IMCadObjectReactor>::initDef();
			MCadObject::initDef();
			IMCadDocumentReactor::initDef();
			MCadReactive<IMCadDocumentReactor>::initDef();
			MCadDocument::initDef();
			MCadTestObject::initDef();
			auto pDoc = MCadDocumentManager::Instance().createDocument();
		}

		TEST_CLASS_CLEANUP(CleanupClass)
		{
			MCadDocumentManager::Instance().closeAllDocument();
		}

		TEST_METHOD_CLEANUP(Test_cleanup)
		{
			auto pDoc = MCadDocumentManager::Instance().createDocument();
			pDoc->undoRedo().clear();
		}

		TEST_METHOD(Test_Undo)
		{
			auto pTestObject = MCadTestObject::createObject();
			auto pWDoc = MCadDocumentManager::Instance().currentDocument();
			Assert::AreEqual(0, pTestObject->value(), L"Value is not init");
			pWDoc.lock()->undoRedo().startUndoRecord("Test_Undo");
			pTestObject->setValue(5);
			Assert::AreEqual(5, pTestObject->value(), L"Value not set");
			pWDoc.lock()->undoRedo().endUndoRecord();

			pWDoc.lock()->undoRedo().undo();
			Assert::AreEqual(0, pTestObject->value(), L"Value not undo");
		}

		TEST_METHOD(Test_Undo_decrements)
		{
			auto pTestObject = MCadTestObject::createObject();
			auto pWDoc = MCadDocumentManager::Instance().currentDocument();
			Assert::AreEqual(0, pTestObject->value(), L"Value is not init");

			pWDoc.lock()->undoRedo().startUndoRecord("Test_Undo");
			pTestObject->setValue(5);
			Assert::AreEqual(5, pTestObject->value(), L"Value not set");
			pWDoc.lock()->undoRedo().endUndoRecord();

			pWDoc.lock()->undoRedo().startUndoRecord("Test_Undo_2");
			pTestObject->setValue(8);
			Assert::AreEqual(8, pTestObject->value(), L"Value not set");
			pWDoc.lock()->undoRedo().endUndoRecord();


			pWDoc.lock()->undoRedo().undo();
			Assert::AreEqual(5, pTestObject->value(), L"Value not undo 2");
			pWDoc.lock()->undoRedo().undo();
			Assert::AreEqual(0, pTestObject->value(), L"Value not undo");
		}

		TEST_METHOD(Test_Redo)
		{
			auto pTestObject = MCadTestObject::createObject();
			auto pWDoc = MCadDocumentManager::Instance().currentDocument();
			Assert::AreEqual(0, pTestObject->value(), L"Value is not init");
			pWDoc.lock()->undoRedo().startUndoRecord("Test_Redo");
			pTestObject->setValue(5);
			Assert::AreEqual(5, pTestObject->value(), L"Value not set");
			pWDoc.lock()->undoRedo().endUndoRecord();

			pWDoc.lock()->undoRedo().undo();
			Assert::AreEqual(0, pTestObject->value(), L"Value not undo");
			pWDoc.lock()->undoRedo().redo();
			Assert::AreEqual(5, pTestObject->value(), L"Value not redo");
		}

		TEST_METHOD(Test_Redo_increments)
		{
			auto pTestObject = MCadTestObject::createObject();
			auto pWDoc = MCadDocumentManager::Instance().currentDocument();
			Assert::AreEqual(0, pTestObject->value(), L"Value is not init");

			pWDoc.lock()->undoRedo().startUndoRecord("Test_Undo");
			pTestObject->setValue(5);
			Assert::AreEqual(5, pTestObject->value(), L"Value not set");
			pWDoc.lock()->undoRedo().endUndoRecord();

			pWDoc.lock()->undoRedo().startUndoRecord("Test_Undo_2");
			pTestObject->setValue(8);
			Assert::AreEqual(8, pTestObject->value(), L"Value not set");
			pWDoc.lock()->undoRedo().endUndoRecord();


			pWDoc.lock()->undoRedo().undo();
			Assert::AreEqual(5, pTestObject->value(), L"Value not undo 2");
			pWDoc.lock()->undoRedo().undo();
			Assert::AreEqual(0, pTestObject->value(), L"Value not undo");
			pWDoc.lock()->undoRedo().redo();
			Assert::AreEqual(5, pTestObject->value(), L"Value not redo");
			pWDoc.lock()->undoRedo().redo();
			Assert::AreEqual(8, pTestObject->value(), L"Value not redo 2");
		}
	};
}
