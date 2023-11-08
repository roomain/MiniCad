#include "pch.h"
#include "CppUnitTest.h"
#include "MCadFormulaEvaluator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMCadFormula
{
	TEST_CLASS(TestMCadFormula_Evaluator)
	{
	public:

		TEST_METHOD(Test_TestEval_Simple)
		{
			MCadFormulaEvaluator evaluator;
			try
			{
				auto result = evaluator.evaluate("1+1");
				Assert::AreEqual(2, std::get<int>(result), L"Wrong result");

				result = evaluator.evaluate("1-1");
				Assert::AreEqual(0, std::get<int>(result), L"Wrong result");
			}
			catch ( MCadFormulaException except )
			{
				Assert::Fail(L"Exception thrown");
			}
		}


		TEST_METHOD(Test_TestEval_Priority)
		{
			MCadFormulaEvaluator evaluator;
			try
			{
				auto result = evaluator.evaluate("1+1*3");
				Assert::AreEqual(4, std::get<int>(result), L"Wrong result 1+1*3");

				result = evaluator.evaluate("3*(1+2)");
				Assert::AreEqual(9, std::get<int>(result), L"Wrong result 3*(1+2)");

				result = evaluator.evaluate("(1-1)*3");
				Assert::AreEqual(0, std::get<int>(result), L"Wrong result (1-1)*3");
				
				result = evaluator.evaluate("4/2*3");
				Assert::AreEqual(6, std::get<int>(result), L"Wrong result 4/2*3");
			}
			catch ( MCadFormulaException except )
			{
				Assert::Fail(L"Exception thrown");
			}
		}

		TEST_METHOD(Test_TestEval_Trigo)
		{
			MCadFormulaEvaluator evaluator;
			try
			{
				/*auto result = evaluator.evaluate("1+1*3");
				Assert::AreEqual(4, std::get<double>(result), L"Wrong result 1+1*3");

				result = evaluator.evaluate("3*(1+2)");
				Assert::AreEqual(9, std::get<double>(result), L"Wrong result 3*(1+2)");

				result = evaluator.evaluate("(1-1)*3");
				Assert::AreEqual(0, std::get<double>(result), L"Wrong result (1-1)*3");

				result = evaluator.evaluate("4/2*3");
				Assert::AreEqual(6, std::get<double>(result), L"Wrong result 4/2*3");*/
			}
			catch ( MCadFormulaException except )
			{
				Assert::Fail(L"Exception thrown");
			}
		}
		
	};
}
