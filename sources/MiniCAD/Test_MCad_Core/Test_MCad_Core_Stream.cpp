#include "CppUnitTest.h"
#include "MCadBinaryBuffer.h"
#include "MCadOutputBinStream.h"
#include "MCadInputBinStream.h"
#include <array>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMCadCore
{
	TEST_CLASS(TestMCadCore_Stream)
	{
	private:
		static MCadBinaryBufferPtr m_pBuffer;

	public:
		TEST_CLASS_INITIALIZE(InitClass)
		{
			m_pBuffer = std::make_shared<MCadBinaryBuffer>();
		}

		TEST_CLASS_CLEANUP(CleanupClass)
		{
			m_pBuffer.reset();
		}

		TEST_METHOD_INITIALIZE(InitTestMethod)
		{
			if(m_pBuffer)
				m_pBuffer->clear();
		}

		TEST_METHOD(Test_WriteLongLong)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			constexpr long long llVal = 5897;
			outStream << llVal;
			Assert::AreEqual(sizeof(llVal), m_pBuffer->size(), L"Wrong buffer size long long");
		}

		TEST_METHOD(Test_WriteChar)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			constexpr char cVal = 'a';
			outStream << cVal;
			Assert::AreEqual(sizeof(cVal), m_pBuffer->size(), L"Wrong buffer size char");
		}

		TEST_METHOD(Test_WriteInt)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			constexpr int iVal = 1;
			outStream << iVal;
			Assert::AreEqual(sizeof(iVal), m_pBuffer->size(), L"Wrong buffer size int");
		}

		TEST_METHOD(Test_WriteDouble)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			constexpr double dVal = 0.5;
			outStream << dVal;
			Assert::AreEqual(sizeof(dVal), m_pBuffer->size(), L"Wrong buffer size double");
		}

		TEST_METHOD(Test_WriteFloat)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			constexpr float fVal = 0.4f;
			outStream << fVal;
			Assert::AreEqual(sizeof(fVal), m_pBuffer->size(), L"Wrong buffer size float");
		}

		TEST_METHOD(Test_WriteShort)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			constexpr short sVal = 1;
			outStream << sVal;
			Assert::AreEqual(sizeof(sVal), m_pBuffer->size(), L"Wrong buffer size short");
		}

		TEST_METHOD(Test_WriteIntDoubleFloat)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			constexpr int iVal = 1;
			outStream << iVal;
			Assert::AreEqual(sizeof(iVal), m_pBuffer->size(), L"Wrong buffer size int");
			constexpr double dVal = 0.5;
			outStream << dVal;
			Assert::AreEqual(sizeof(iVal) + sizeof(dVal), m_pBuffer->size(), L"Wrong buffer size int + double");
			constexpr float fVal = 0.4f;
			outStream << fVal;
			Assert::AreEqual(sizeof(iVal) + sizeof(fVal) + sizeof(dVal), m_pBuffer->size(), L"Wrong buffer size int + double + float");
		}

		TEST_METHOD(Test_WriteString)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			const std::string text = "azerty";
			outStream << text;
			Assert::AreEqual(sizeof(size_t) + sizeof(char) * text.length(), m_pBuffer->size(), L"Wrong buffer size string");
		}

		TEST_METHOD(Test_WriteWString)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			const std::wstring text = L"azerty";
			outStream << text;
			Assert::AreEqual(sizeof(size_t) + sizeof(wchar_t) * text.length(), m_pBuffer->size(), L"Wrong buffer size string");
		}

		//--------------------------------------------------------------------------------------------------------------
		TEST_METHOD(Test_ReadLongLong)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			constexpr long long llVal = 5897;
			outStream << llVal;
			MCadInputBinStream inStream(m_pBuffer);
			long long llValRet = 0;
			inStream >> llValRet;
			Assert::AreEqual(llVal, llValRet, L"Wrong read");
		}

		TEST_METHOD(Test_ReadChar)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			constexpr char cVal = 'a';
			outStream << cVal;
			MCadInputBinStream inStream(m_pBuffer);
			char cValRet = 0;
			inStream >> cValRet;
			Assert::AreEqual(cVal, cValRet, L"Wrong read");
		}

		TEST_METHOD(Test_ReadInt)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			constexpr int iVal = 1;
			outStream << iVal;
			MCadInputBinStream inStream(m_pBuffer);
			int iValRet = 0;
			inStream >> iValRet;
			Assert::AreEqual(iVal, iValRet, L"Wrong read");
		}

		TEST_METHOD(Test_ReadDouble)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			constexpr double dVal = 0.5;
			outStream << dVal;
			MCadInputBinStream inStream(m_pBuffer);
			double dValRet = 0;
			inStream >> dValRet;
			Assert::AreEqual(dVal, dValRet, L"Wrong read");
		}

		TEST_METHOD(Test_ReadFloat)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			constexpr float fVal = 0.4f;
			outStream << fVal;
			MCadInputBinStream inStream(m_pBuffer);
			float fValRet = 0;
			inStream >> fValRet;
			Assert::AreEqual(fVal, fValRet, L"Wrong read");
		}

		TEST_METHOD(Test_ReadShort)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			constexpr short sVal = 1;
			outStream << sVal;
			MCadInputBinStream inStream(m_pBuffer);
			short sValRet = 0;
			inStream >> sValRet;
			Assert::AreEqual(sVal, sValRet, L"Wrong read");
		}

		TEST_METHOD(Test_ReadIntDoubleFloat)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			constexpr int iVal = 1;
			outStream << iVal;
			constexpr double dVal = 0.5;
			outStream << dVal;
			constexpr float fVal = 0.4f;
			outStream << fVal;
			MCadInputBinStream inStream(m_pBuffer);
			float fValRet = 0;
			double dValRet = 0;
			int iValRet = 0;
			inStream >> iValRet >> dValRet >> fValRet;
			Assert::AreEqual(iVal, iValRet, L"Wrong read int");
			Assert::AreEqual(dVal, dValRet, L"Wrong read double");
			Assert::AreEqual(fVal, fValRet, L"Wrong read float");
		}

		TEST_METHOD(Test_ReadString)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			const std::string text = "azerty";
			outStream << text;
			MCadInputBinStream inStream(m_pBuffer);
			std::string textRet;
			inStream >> textRet;
			Assert::AreEqual(text, textRet, L"Wrong read");
		}

		TEST_METHOD(Test_ReadWString)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			const std::wstring text = L"azerty";
			outStream << text;
			MCadInputBinStream inStream(m_pBuffer);
			std::wstring textRet;
			inStream >> textRet;
			Assert::AreEqual(text, textRet, L"Wrong read");
		}

		TEST_METHOD(Test_ReadStringdoubleString)
		{
			MCadOutputBinStream outStream(m_pBuffer);
			const std::string text = "azerty";
			const double dValue = 2.3;
			const std::string text1 = "qsdfg";
			outStream << text << dValue << text1;
			MCadInputBinStream inStream(m_pBuffer);
			std::string textRet;
			double dValRet = 0;
			std::string text1Ret;
			inStream >> textRet >> dValRet >> text1Ret;
			Assert::AreEqual(text, textRet, L"Wrong read");
			Assert::AreEqual(dValue, dValRet, L"Wrong read double");
			Assert::AreEqual(text1, text1Ret, L"Wrong read text");
		}
		
	};

	MCadBinaryBufferPtr TestMCadCore_Stream::m_pBuffer;
}
