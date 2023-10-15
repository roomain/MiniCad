#include "pch.h"
#include "CppUnitTest.h"
#include "MCadFormulaRegEx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMCadFormula
{
	TEST_CLASS(TestMCadFormula_RegEx)
	{
	public:
		
		TEST_METHOD(Test_GetDouble_From_integer)
		{
			Assert::AreEqual(36.0, getDouble("36", '.'), L"Wrong value");
			Assert::AreEqual(62.0, getDouble("62", ','), L"Wrong value");
		}
		TEST_METHOD(Test_GetDouble_Dot_DecimalSeparator)
		{

			Assert::AreEqual(3.5, getDouble("3.5", '.'), L"Wrong value");
			Assert::AreEqual(0.1, getDouble("0.1", '.'), L"Wrong value");
			Assert::AreEqual(13.5, getDouble("13.5", '.'), L"Wrong value");
			Assert::AreEqual(35.0, getDouble("35.0", '.'), L"Wrong value");
		}

		TEST_METHOD(Test_GetDouble_Comma_DecimalSeparator)
		{
			Assert::AreEqual(3.5, getDouble("3,5", ','), L"Wrong value");
			Assert::AreEqual(0.1, getDouble("0,1", ','), L"Wrong value");
			Assert::AreEqual(13.5, getDouble("13,5", ','), L"Wrong value");
			Assert::AreEqual(35.0, getDouble("35,0", ','), L"Wrong value");
		}

		TEST_METHOD(Test_GetVector2)
		{
			auto vec = getVector<2>("<2.5,3.2>", '.', ',');
			Assert::AreEqual(2.5, vec.x, L"Wrong value");
			Assert::AreEqual(3.2, vec.y, L"Wrong value");

			vec = getVector<2>("<3,5;3,8>", ',', ';');
			Assert::AreEqual(3.5, vec.x, L"Wrong value");
			Assert::AreEqual(3.8, vec.y, L"Wrong value");

		}

		TEST_METHOD(Test_GetVector3)
		{
			auto vec = getVector<3>("<2.5,3.2,8.2>", '.', ',');
			Assert::AreEqual(2.5, vec.x, L"Wrong value");
			Assert::AreEqual(3.2, vec.y, L"Wrong value");
			Assert::AreEqual(8.2, vec.z, L"Wrong value");

			vec = getVector<3>("<3,5;3,8;9,5>", ',', ';');
			Assert::AreEqual(3.5, vec.x, L"Wrong value");
			Assert::AreEqual(3.8, vec.y, L"Wrong value");
			Assert::AreEqual(9.5, vec.z, L"Wrong value");
		}

		TEST_METHOD(Test_GetVector4)
		{
			auto vec = getVector<4>("<2.5,3.2,8.2, 10.2>", '.', ',');
			Assert::AreEqual(2.5, vec.x, L"Wrong value");
			Assert::AreEqual(3.2, vec.y, L"Wrong value");
			Assert::AreEqual(8.2, vec.z, L"Wrong value");
			Assert::AreEqual(8.2, vec.z, L"Wrong value");
			Assert::AreEqual(10.2, vec.w, L"Wrong value");

			vec = getVector<4>("<3,5;3,8;9,5;10,2>", ',', ';');
			Assert::AreEqual(3.5, vec.x, L"Wrong value");
			Assert::AreEqual(3.8, vec.y, L"Wrong value");
			Assert::AreEqual(9.5, vec.z, L"Wrong value");
			Assert::AreEqual(10.2, vec.w, L"Wrong value");
		}


		TEST_METHOD(Test_GetRelativeVector2)
		{

			auto vec = getRelative<2>("@<2.5,3.2>", '.', ',');
			Assert::AreEqual(2.5, vec.x, L"Wrong value");
			Assert::AreEqual(3.2, vec.y, L"Wrong value");

			vec = getRelative<2>("@<3,5;3,8>", ',', ';');
			Assert::AreEqual(3.5, vec.x, L"Wrong value");
			Assert::AreEqual(3.8, vec.y, L"Wrong value");
		}

		TEST_METHOD(Test_GetRelativeVector3)
		{
			auto vec = getRelative<3>("@<2.5,3.2,8.2>", '.', ',');
			Assert::AreEqual(2.5, vec.x, L"Wrong value");
			Assert::AreEqual(3.2, vec.y, L"Wrong value");
			Assert::AreEqual(8.2, vec.z, L"Wrong value");

			vec = getRelative<3>("@<3,5;3,8;9,5>", ',', ';');
			Assert::AreEqual(3.5, vec.x, L"Wrong value");
			Assert::AreEqual(3.8, vec.y, L"Wrong value");
			Assert::AreEqual(9.5, vec.z, L"Wrong value");
		}

		TEST_METHOD(Test_GetRelativeVector4)
		{
			auto vec = getRelative<4>("@<2.5,3.2,8.2, 10.2>", '.', ',');
			Assert::AreEqual(2.5, vec.x, L"Wrong value");
			Assert::AreEqual(3.2, vec.y, L"Wrong value");
			Assert::AreEqual(8.2, vec.z, L"Wrong value");
			Assert::AreEqual(8.2, vec.z, L"Wrong value");
			Assert::AreEqual(10.2, vec.w, L"Wrong value");

			vec = getRelative<4>("@<3,5;3,8;9,5;10,2>", ',', ';');
			Assert::AreEqual(3.5, vec.x, L"Wrong value");
			Assert::AreEqual(3.8, vec.y, L"Wrong value");
			Assert::AreEqual(9.5, vec.z, L"Wrong value");
			Assert::AreEqual(10.2, vec.w, L"Wrong value");
		}

		TEST_METHOD(Test_GetPolar)
		{
			auto polarValue = getPolar("20.3<5.2", '.');
			Assert::AreEqual(20.3, polarValue.m_angle, L"Wrong angle");
			Assert::AreEqual(5.2, polarValue.m_distance, L"Wrong distance");

			polarValue = getPolar("20,6<5,9", ',');
			Assert::AreEqual(20.6, polarValue.m_angle, L"Wrong angle");
			Assert::AreEqual(5.9, polarValue.m_distance, L"Wrong distance");
		}

		TEST_METHOD(Test_GetRelativePolar)
		{
			auto polarValue = getRelativePolar("@20.3<5.2", '.');
			Assert::AreEqual(20.3, polarValue.m_angle, L"Wrong angle");
			Assert::AreEqual(5.2, polarValue.m_distance, L"Wrong distance");

			polarValue = getRelativePolar("@20,6<5,9", ',');
			Assert::AreEqual(20.6, polarValue.m_angle, L"Wrong angle");
			Assert::AreEqual(5.9, polarValue.m_distance, L"Wrong distance");
		}
	};
}
