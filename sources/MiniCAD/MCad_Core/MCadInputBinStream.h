#pragma once
/***********************************************
* @headerfile MCadInputBinStream.h
* @date 29 / 07 / 2023
* @author Roomain
************************************************/
#include "MCad_Core_globals.h"
#include "IMCadInputStream.h"
#include <memory>
#include "MCadBinaryBuffer.h"

using MCadBinaryBufferPtr = std::shared_ptr<MCadBinaryBuffer>;

#pragma warning(push)
#pragma warning(disable : 4251)

class MCAD_CORE_EXPORT MCadInputBinStream : public IMCadInputStream
{
private:
	MCadBinaryBufferPtr m_inputBuffer;	/*!< input buffer*/
	size_t m_offset = 0;				/*!< buffer offset*/

public:
	MCadInputBinStream() = default;
	explicit MCadInputBinStream(const MCadBinaryBufferPtr& a_buffer);
	virtual ~MCadInputBinStream() = default;
	constexpr size_t offset()const { return m_inputBuffer ? m_inputBuffer->size() : 0; }
	IMCadInputStream& setPos(const size_t& a_offset) final;
	IMCadInputStream& shift(const size_t& a_offset) final;
	void atStart()final;
	void setBuffer(const MCadBinaryBufferPtr& a_buffer);
	[[nodiscard]] bool hasBuffer()const noexcept { return m_inputBuffer.get() != nullptr; }
	//-----------------------------------------------------------------
	IMCadInputStream& operator >> (unsigned long long& a_value) final;
	IMCadInputStream& operator >> (long long& a_value) final;
	IMCadInputStream& operator >> (bool& a_value) final;
	IMCadInputStream& operator >> (char& a_value) final;
	IMCadInputStream& operator >> (unsigned char& a_value) final;
	IMCadInputStream& operator >> (short& a_value) final;
	IMCadInputStream& operator >> (unsigned short& a_value) final;
	IMCadInputStream& operator >> (unsigned int& a_value) final;
	IMCadInputStream& operator >> (int& a_value) final;
	IMCadInputStream& operator >> (double& a_value) final;
	IMCadInputStream& operator >> (float& a_value) final;
	IMCadInputStream& operator >> (std::string& a_value) final;
	IMCadInputStream& operator >> (std::wstring& a_value) final;
};

#pragma warning(pop)
