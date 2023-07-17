#include "pch.h"
#include "CppUnitTest.h"
#include "TestRTTI_Resources.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMCadCore
{
	TEST_CLASS(TestMCadCore_RTTI)
	{
	public:
		
		TEST_METHOD(Test_initDef)
		{
			Assert::IsNull(VirtualClass::definition().get(), L"Definition not null");
			VirtualClass::initDef();
			Assert::IsNotNull(VirtualClass::definition().get(), L"Definition null");
			VirtualClass::releaseDef();
			Assert::IsNull(VirtualClass::definition().get(), L"Released definition not null");
		}

		TEST_METHOD(Test_initDef_Except)
		{
			Assert::IsNull(DerivedFromVirtualClass::definition().get(), L"Definition not null");
			try
			{
				DerivedFromVirtualClass::initDef();
				Assert::Fail(L"No exception thrown");
			}
			catch (RTTIException& except)
			{
				Assert::IsTrue(except.type() == RTTIException::ExceptType::Except_ParentNotDefined, L"Wrong exception");
			}
		}

		TEST_METHOD(Test_releaseDef)
		{
			Assert::IsNull(VirtualClass::definition().get(), L"Definition not null");
			Assert::IsNull(DerivedFromVirtualClass::definition().get(), L"Derived definition not null");
			VirtualClass::initDef();
			DerivedFromVirtualClass::initDef();
			Assert::IsNotNull(VirtualClass::definition().get(), L"Definition null");
			Assert::IsNotNull(DerivedFromVirtualClass::definition().get(), L"Derived definition null");
			
			DerivedFromVirtualClass::releaseDef();
			Assert::IsNull(DerivedFromVirtualClass::definition().get(), L"Released definition not null");
			VirtualClass::releaseDef();
			Assert::IsNull(VirtualClass::definition().get(), L"Released derived definition not null");
		}

		TEST_METHOD(Test_releaseDef_Except)
		{
			VirtualClass::initDef();
			DerivedFromVirtualClass::initDef(); 
			try
			{
				VirtualClass::releaseDef();
				Assert::Fail(L"No exception thrown");
			}
			catch (RTTIException& except)
			{
				Assert::IsTrue(except.type() == RTTIException::ExceptType::Except_CantUnitialize, L"Wrong exception");
				DerivedFromVirtualClass::releaseDef();
				VirtualClass::releaseDef();
			}
		}

		TEST_METHOD(Test_notDefined)
		{
			VirtualClass::initDef();
			try
			{
				auto pTest = std::make_shared<DerivedFromVirtualClass>();
				Assert::IsNull(pTest->isA().get(), L"Definition not null");
				bool bRet = pTest->isKindOf(VirtualClass::definition());
				Assert::Fail(L"No exception thrown");
			}
			catch (RTTIException& except)
			{
				Assert::IsTrue(except.type() == RTTIException::ExceptType::Except_NotDefined, L"Wrong exception");
				VirtualClass::releaseDef();
			}

			try
			{
				auto pTest = std::make_shared<DerivedFromVirtualClass>();
				Assert::IsNull(pTest->isA().get(), L"Definition not null");
				bool bRet = pTest->isKindOf<VirtualClass>();
				Assert::Fail(L"No exception thrown");
			}
			catch (RTTIException& except)
			{
				Assert::IsTrue(except.type() == RTTIException::ExceptType::Except_NotDefined, L"Wrong exception");
				VirtualClass::releaseDef();
			}
		}

		TEST_METHOD(Test_IsSame)
		{
			VirtualClass::initDef();
			DerivedFromVirtualClass::initDef();

			Assert::IsFalse(DerivedFromVirtualClass::definition()->isSame(VirtualClass::definition()), L"Same");
			Assert::IsTrue(DerivedFromVirtualClass::definition()->isSame(DerivedFromVirtualClass::definition()), L"Not Same");

			DerivedFromVirtualClass::releaseDef();
			VirtualClass::releaseDef();
		}


		TEST_METHOD(Test_kindOf_Direct)
		{
			VirtualClass::initDef();
			DerivedFromVirtualClass::initDef();
			
			auto pTest = std::make_shared<DerivedFromVirtualClass>();
			Assert::IsTrue(pTest->isKindOf(VirtualClass::definition()), L"Wrong kindof 0");

			DerivedFromVirtualClass::releaseDef();
			VirtualClass::releaseDef();
		}

		TEST_METHOD(Test_kindOf_template_Direct)
		{
			VirtualClass::initDef();
			DerivedFromVirtualClass::initDef();

			auto pTest = std::make_shared<DerivedFromVirtualClass>();
			Assert::IsTrue(pTest->isKindOf<VirtualClass>(), L"Wrong kindof 0");

			DerivedFromVirtualClass::releaseDef();
			VirtualClass::releaseDef();
		}


		TEST_METHOD(Test_kindOf_indirect)
		{
			VirtualClass::initDef();
			DerivedFromVirtualClass::initDef();
			DerivedFromClass::initDef();

			auto pTest = std::make_shared<DerivedFromClass>();

			Assert::IsTrue(pTest->isKindOf(DerivedFromVirtualClass::definition()), L"Wrong kindof 1");
			Assert::IsTrue(pTest->isKindOf(VirtualClass::definition()), L"Wrong kindof 2");

			DerivedFromClass::releaseDef();
			DerivedFromVirtualClass::releaseDef();
			VirtualClass::releaseDef();
		}

		TEST_METHOD(Test_kindOf_template_indirect)
		{
			VirtualClass::initDef();
			DerivedFromVirtualClass::initDef();
			DerivedFromClass::initDef();

			auto pTest = std::make_shared<DerivedFromClass>();

			Assert::IsTrue(pTest->isKindOf<DerivedFromVirtualClass>(), L"Wrong kindof 1");
			Assert::IsTrue(pTest->isKindOf<VirtualClass>(), L"Wrong kindof 2");

			DerivedFromClass::releaseDef();
			DerivedFromVirtualClass::releaseDef();
			VirtualClass::releaseDef();
		}

		TEST_METHOD(Test_kindOf_multiple)
		{
			VirtualClass::initDef();
			DerivedFromVirtualClass::initDef();
			DerivedFromClass::initDef();
			OtherClass::initDef();
			MultiDerivativeClass::initDef();

			auto pTestMult = std::make_shared<MultiDerivativeClass>();
			Assert::IsTrue(pTestMult->isKindOf(OtherClass::definition()), L"Wrong kindof 1");
			Assert::IsTrue(pTestMult->isKindOf(VirtualClass::definition()), L"Wrong kindof 2");
			Assert::IsTrue(pTestMult->isKindOf(DerivedFromClass::definition()), L"Wrong kindof 3");
			Assert::IsTrue(pTestMult->isKindOf(DerivedFromVirtualClass::definition()), L"Wrong kindof 4");
			Assert::IsTrue(pTestMult->isKindOf(VirtualClass::definition()), L"Wrong kindof 5");


			MultiDerivativeClass::releaseDef();
			OtherClass::releaseDef();
			DerivedFromClass::releaseDef();
			DerivedFromVirtualClass::releaseDef();
			VirtualClass::releaseDef();
		}

		TEST_METHOD(Test_kindOf_template_multiple)
		{
			VirtualClass::initDef();
			DerivedFromVirtualClass::initDef();
			DerivedFromClass::initDef();
			OtherClass::initDef();
			MultiDerivativeClass::initDef();

			auto pTestMult = std::make_shared<MultiDerivativeClass>();
			Assert::IsTrue(pTestMult->isKindOf<OtherClass>(), L"Wrong kindof 1");
			Assert::IsTrue(pTestMult->isKindOf<VirtualClass>(), L"Wrong kindof 2");
			Assert::IsTrue(pTestMult->isKindOf<DerivedFromClass>(), L"Wrong kindof 3");
			Assert::IsTrue(pTestMult->isKindOf<DerivedFromVirtualClass>(), L"Wrong kindof 4");
			Assert::IsTrue(pTestMult->isKindOf<VirtualClass>(), L"Wrong kindof 5");


			MultiDerivativeClass::releaseDef();
			OtherClass::releaseDef();
			DerivedFromClass::releaseDef();
			DerivedFromVirtualClass::releaseDef();
			VirtualClass::releaseDef();
		}

		TEST_METHOD(Test_kindOf_not)
		{
			VirtualClass::initDef();
			DerivedFromVirtualClass::initDef();
			DerivedFromClass::initDef();
			OtherClass::initDef();
			MultiDerivativeClass::initDef();

			auto pTestOther = std::make_shared<OtherClass>();

			Assert::IsFalse(pTestOther->isKindOf(MultiDerivativeClass::definition()), L"Wrong kindof 1");
			Assert::IsFalse(pTestOther->isKindOf(VirtualClass::definition()), L"Wrong kindof 2");
			Assert::IsFalse(pTestOther->isKindOf(DerivedFromClass::definition()), L"Wrong kindof 3");
			Assert::IsFalse(pTestOther->isKindOf(DerivedFromVirtualClass::definition()), L"Wrong kindof 4");
			Assert::IsFalse(pTestOther->isKindOf(VirtualClass::definition()), L"Wrong kindof 5");

			MultiDerivativeClass::releaseDef();
			OtherClass::releaseDef();
			DerivedFromClass::releaseDef();
			DerivedFromVirtualClass::releaseDef();
			VirtualClass::releaseDef();
		}

		TEST_METHOD(Test_kindOf_template_not)
		{
			VirtualClass::initDef();
			DerivedFromVirtualClass::initDef();
			DerivedFromClass::initDef();
			OtherClass::initDef();
			MultiDerivativeClass::initDef();

			auto pTestOther = std::make_shared<OtherClass>();

			Assert::IsFalse(pTestOther->isKindOf<MultiDerivativeClass>(), L"Wrong kindof 1");
			Assert::IsFalse(pTestOther->isKindOf<VirtualClass>(), L"Wrong kindof 2");
			Assert::IsFalse(pTestOther->isKindOf<DerivedFromClass>(), L"Wrong kindof 3");
			Assert::IsFalse(pTestOther->isKindOf<DerivedFromVirtualClass>(), L"Wrong kindof 4");
			Assert::IsFalse(pTestOther->isKindOf<VirtualClass>(), L"Wrong kindof 5");

			MultiDerivativeClass::releaseDef();
			OtherClass::releaseDef();
			DerivedFromClass::releaseDef();
			DerivedFromVirtualClass::releaseDef();
			VirtualClass::releaseDef();
		}
	};
}
