#pragma once
/***********************************************
* @headerfile MCadBinaryBuffer.h
* @date 17 / 07 / 2023
* @author Roomain
************************************************/
#include <vector>
#include <utility>
#include <memory>
#include <iterator>

/*@brief class to store binary data*/
class  MCadBinaryBuffer
{
private:
	static constexpr size_t MIN_SIZE = 1000;
	std::vector<unsigned char> m_vBuffer;	/*!< data buffer*/	
	
public:

	MCadBinaryBuffer(const MCadBinaryBuffer&) = delete;
	MCadBinaryBuffer& operator = (const MCadBinaryBuffer&) = delete;

	MCadBinaryBuffer() 
	{
		m_vBuffer.reserve(MIN_SIZE);
	}
	~MCadBinaryBuffer() = default;
	[[nodiscard]] constexpr size_t size()const noexcept { return m_vBuffer.size(); }

	void clear() { m_vBuffer.clear(); }
	
	template<typename Type>
	size_t write(const Type& a_data)
	{
		auto pTempBuffer = reinterpret_cast<const unsigned char*>(&a_data);
		std::copy(pTempBuffer, pTempBuffer + sizeof(Type), std::back_inserter(m_vBuffer));
		return m_vBuffer.size();
	}

	template<typename Type>
	size_t write(const Type* a_data, const size_t& a_dataCount)
	{
		auto pTempBuffer = reinterpret_cast<const unsigned char*>(a_data);
		std::copy(pTempBuffer, pTempBuffer + sizeof(Type) * a_dataCount, std::back_inserter(m_vBuffer));
		return m_vBuffer.size();
	}

	template<typename Type>
	[[nodiscard]] size_t read(Type& a_data, const size_t& from = 0)const
	{
		size_t endIndex = from + sizeof(Type);
		if (endIndex > m_vBuffer.size())
			return 0;

		auto pData = m_vBuffer.data() + from;
		auto pDataBuffer = reinterpret_cast<unsigned char*>(&a_data);
		std::copy(pData, pData + sizeof(Type), pDataBuffer);
		return endIndex;
	}

	template<typename Type>
	[[nodiscard]] size_t read(Type* a_data, const size_t& a_Size, const size_t& from = 0)const
	{
		size_t endIndex = from + sizeof(Type) * a_Size;
		if (endIndex > m_vBuffer.size())
			return 0;

		auto pData = m_vBuffer.data() + from;
		auto pDataBuffer = reinterpret_cast<unsigned char*>(a_data);
		std::copy(pData, pData + sizeof(Type) * a_Size, pDataBuffer);
		return endIndex;
	}

	template<typename Type, typename ForwardIter> 
	[[nodiscard]] size_t read(const size_t& a_Size, ForwardIter a_iterator, const size_t& from = 0)const
	{
		std::copy(reinterpret_cast<const Type*>(m_vBuffer.data() + from),
			reinterpret_cast<const Type*>(m_vBuffer.data() + from) + a_Size, a_iterator);

		return from + sizeof(Type) * a_Size;
	}
};
