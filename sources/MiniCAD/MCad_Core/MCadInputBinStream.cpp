#include "pch.h"
#include "MCadInputBinStream.h"
#include "MCadBinaryBuffer.h"

MCadInputBinStream::MCadInputBinStream(const MCadBinaryBufferPtr& a_buffer) : m_inputBuffer{ a_buffer }
{
	//
}

void MCadInputBinStream::setBuffer(const MCadBinaryBufferPtr& a_buffer)
{
	m_inputBuffer = a_buffer;
}

IMCadInputStream& MCadInputBinStream::setPos(const size_t& a_offset)
{
	m_offset = a_offset;
	return *this;
}

IMCadInputStream& MCadInputBinStream::shift(const size_t& a_offset)
{
	m_offset += a_offset;
	return *this;
}

void MCadInputBinStream::atStart()
{
	m_offset = 0;
}

//-----------------------------------------------------------------
IMCadInputStream& MCadInputBinStream::operator >> (unsigned long long& a_value)
{
	if (m_inputBuffer)
		m_offset = m_inputBuffer->read(a_value, m_offset);
	
	return *this;
}

IMCadInputStream& MCadInputBinStream::operator >> (long long& a_value)
{
	if (m_inputBuffer)
		m_offset = m_inputBuffer->read(a_value, m_offset);

	return *this;
}

IMCadInputStream& MCadInputBinStream::operator >> (bool& a_value)
{
	if (m_inputBuffer)
		m_offset = m_inputBuffer->read(a_value, m_offset);

	return *this;
}

IMCadInputStream& MCadInputBinStream::operator >> (char& a_value)
{
	if (m_inputBuffer)
		m_offset = m_inputBuffer->read(a_value, m_offset);

	return *this;
}

IMCadInputStream& MCadInputBinStream::operator >> (unsigned char& a_value)
{
	if (m_inputBuffer)
		m_offset = m_inputBuffer->read(a_value, m_offset);

	return *this;
}

IMCadInputStream& MCadInputBinStream::operator >> (short& a_value)
{
	if (m_inputBuffer)
		m_offset = m_inputBuffer->read(a_value, m_offset);

	return *this;
}

IMCadInputStream& MCadInputBinStream::operator >> (unsigned short& a_value)
{
	if (m_inputBuffer)
		m_offset = m_inputBuffer->read(a_value, m_offset);

	return *this;
}

IMCadInputStream& MCadInputBinStream::operator >> (unsigned int& a_value)
{
	if (m_inputBuffer)
		m_offset = m_inputBuffer->read(a_value, m_offset);

	return *this;
}

IMCadInputStream& MCadInputBinStream::operator >> (int& a_value)
{
	if (m_inputBuffer)
		m_offset = m_inputBuffer->read(a_value, m_offset);

	return *this;
}

IMCadInputStream& MCadInputBinStream::operator >> (double& a_value)
{
	if (m_inputBuffer)
		m_offset = m_inputBuffer->read(a_value, m_offset);

	return *this;
}

IMCadInputStream& MCadInputBinStream::operator >> (float& a_value)
{
	if (m_inputBuffer)
		m_offset = m_inputBuffer->read(a_value, m_offset);

	return *this;
}

IMCadInputStream& MCadInputBinStream::operator >> (std::string& a_value)
{
	if (m_inputBuffer)
	{
		size_t stringLen = 0;
		m_offset = m_inputBuffer->read(stringLen, m_offset);
		if (stringLen > 0)
		{
			m_offset = m_inputBuffer->read<char>(stringLen, std::back_inserter(a_value), m_offset);
		}
	}

	return *this;
}


IMCadInputStream& MCadInputBinStream::operator >> (std::wstring& a_value)
{
	if (m_inputBuffer)
	{
		size_t stringLen = 0;
		m_offset = m_inputBuffer->read(stringLen, m_offset);
		if (stringLen > 0)
		{
			m_offset = m_inputBuffer->read<wchar_t>(stringLen, std::back_inserter(a_value), m_offset);
		}
	}

	return *this;
}

