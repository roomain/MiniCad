#pragma once
#pragma once
/***********************************************
* @headerfile MCadOutputBinStream.h
* @date 29 / 07 / 2023
* @author Roomain
************************************************/
#include "MCad_Core_globals.h"
#include "IMCadOutputStream.h"
#include <memory>

class MCadBinaryBuffer;
using MCadBinaryBufferPtr = std::shared_ptr<MCadBinaryBuffer>;

#pragma warning(push)
#pragma warning(disable : 4251)

class MCAD_CORE_EXPORT MCadOutputBinStream : public IMCadOutputStream
{
private:
	MCadBinaryBufferPtr m_outputBuffer;	/*!< input buffer*/
	size_t m_offset = 0;				/*!< buffer offset*/

public:
	MCadOutputBinStream() = default;
	explicit MCadOutputBinStream(const MCadBinaryBufferPtr& a_buffer);
	virtual ~MCadOutputBinStream() = default;
	void setBuffer(const MCadBinaryBufferPtr& a_buffer);
	[[nodiscard]] bool hasBuffer()const noexcept { return m_outputBuffer.get() != nullptr; }
	IMCadOutputStream& operator << (const unsigned long long& a_value)final;
	IMCadOutputStream& operator << (const long long& a_value)final;
	IMCadOutputStream& operator << (const bool a_value)final;
	IMCadOutputStream& operator << (const char a_value)final;
	IMCadOutputStream& operator << (const unsigned char a_value)final;
	IMCadOutputStream& operator << (const short a_value)final;
	IMCadOutputStream& operator << (const unsigned short a_value)final;
	IMCadOutputStream& operator << (const unsigned int a_value)final;
	IMCadOutputStream& operator << (const int a_value)final;
	IMCadOutputStream& operator << (const double& a_value)final;
	IMCadOutputStream& operator << (const float a_value)final;
	IMCadOutputStream& operator << (const std::string& a_value)final;
	IMCadOutputStream& operator << (const std::wstring& a_value)final;
};

#pragma warning(pop)
