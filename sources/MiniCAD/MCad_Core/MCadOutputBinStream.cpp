#include "pch.h"
#include "MCadOutputBinStream.h"
#include "MCadBinaryBuffer.h"

MCadOutputBinStream::MCadOutputBinStream(const MCadBinaryBufferPtr& a_buffer) : m_inputBuffer{ a_buffer }
{
	//
}

IMCadOutputStream& MCadOutputBinStream::operator << (const unsigned long long& a_value)
{
	if (m_inputBuffer)
		m_inputBuffer->write(a_value);
	return *this;
}

IMCadOutputStream& MCadOutputBinStream::operator << (const long long& a_value)
{
	if (m_inputBuffer)
		m_inputBuffer->write(a_value);
	return *this;
}

IMCadOutputStream& MCadOutputBinStream::operator << (const bool a_value)
{
	if (m_inputBuffer)
		m_inputBuffer->write(a_value);
	return *this;
}

IMCadOutputStream& MCadOutputBinStream::operator << (const char a_value)
{
	if (m_inputBuffer)
		m_inputBuffer->write(a_value);
	return *this;
}

IMCadOutputStream& MCadOutputBinStream::operator << (const unsigned char a_value)
{
	if (m_inputBuffer)
		m_inputBuffer->write(a_value);
	return *this;
}

IMCadOutputStream& MCadOutputBinStream::operator << (const short a_value)
{
	if (m_inputBuffer)
		m_inputBuffer->write(a_value);
	return *this;
}

IMCadOutputStream& MCadOutputBinStream::operator << (const unsigned short a_value)
{
	if (m_inputBuffer)
		m_inputBuffer->write(a_value);
	return *this;
}

IMCadOutputStream& MCadOutputBinStream::operator << (const unsigned int a_value)
{
	if (m_inputBuffer)
		m_inputBuffer->write(a_value);
	return *this;
}

IMCadOutputStream& MCadOutputBinStream::operator << (const int a_value)
{
	if (m_inputBuffer)
		m_inputBuffer->write(a_value);
	return *this;
}

IMCadOutputStream& MCadOutputBinStream::operator << (const double& a_value)
{
	if (m_inputBuffer)
		m_inputBuffer->write(a_value);
	return *this;
}

IMCadOutputStream& MCadOutputBinStream::operator << (const float a_value)
{
	if (m_inputBuffer)
		m_inputBuffer->write(a_value);
	return *this;
}

IMCadOutputStream& MCadOutputBinStream::operator << (const std::string& a_value)
{
	if (m_inputBuffer)
	{
		m_inputBuffer->write(a_value.length());
		m_inputBuffer->write(a_value.c_str(), a_value.length());
	}
	return *this;
}
