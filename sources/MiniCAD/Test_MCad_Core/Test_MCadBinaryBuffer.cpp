#include "pch.h"
#include "CppUnitTest.h"
#include "MCadBinaryBuffer.h"
#include <array>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMCadCore
{
	TEST_CLASS(TestMCadCore_BinaryBuffer)
	{
	public:

		TEST_METHOD(Test_WriteInt)
		{
			MCadBinaryBuffer buffer;
			auto size = buffer.write<int>(5);
			Assert::AreEqual(sizeof(int), size, L"Wrong size");
		}

		TEST_METHOD(Test_ReadInt)
		{
			MCadBinaryBuffer buffer;
			auto size = buffer.write<int>(5);
			int value = 0;
			auto nextSize = buffer.read<int>(value);
			Assert::AreEqual(5, value, L"Wrong value");
			Assert::AreEqual(size, nextSize, L"Wrong size");
		}

		TEST_METHOD(Test_WriteInt_Double)
		{
			MCadBinaryBuffer buffer;
			auto size = buffer.write<int>(5);
			size = buffer.write<double>(6.4);
			Assert::AreEqual(sizeof(int) + sizeof(double), size, L"Wrong size");
		}

		TEST_METHOD(Test_ReadInt_Double)
		{
			MCadBinaryBuffer buffer;
			auto size = buffer.write<int>(5);
			auto sizeAux = buffer.write<double>(6.4);
			int value = 0;
			auto nextSize = buffer.read<int>(value);
			Assert::AreEqual(5, value, L"Wrong int value");
			Assert::AreEqual(size, nextSize, L"Wrong int size");

			double dvalue = 0;
			auto nextSizeAux = buffer.read<double>(dvalue, nextSize);
			Assert::AreEqual(6.4, dvalue, L"Wrong double value");
			Assert::AreEqual(sizeAux, nextSizeAux, L"Wrong double size");
		}

		TEST_METHOD(Test_WriteIntTable)
		{
			std::array<int, 6> writeBuffer = { 0, 1, 2, 3, 4, 5 };
			MCadBinaryBuffer buffer;
			auto size = buffer.write<int>(writeBuffer.data(), 6);
			Assert::AreEqual(sizeof(int) *6, size, L"Wrong size");
		}

		TEST_METHOD(Test_readIntTable)
		{
			std::array<int, 6> writeBuffer = { 0, 1, 2, 3, 4, 5 };
			MCadBinaryBuffer buffer;
			auto writesize = buffer.write<int>(writeBuffer.data(), 6);
			std::array<int, 6> readBuffer = { -1, -1, -1, -1, -1, -1 };
			auto readsize = buffer.read<int>(readBuffer.data(), 6);
			Assert::AreEqual(writesize, readsize, L"Wrong size");
			for (int i = 0; i < 6; ++i)
				Assert::AreEqual(writeBuffer[i], readBuffer[i], L"Wrong data");
		}
	};
}
