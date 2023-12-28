#include "pch.h"



RTTIException::RTTIException(ExceptType a_Type, const std::source_location& a_loc, const std::string_view& a_extra) :
	MCadException(a_loc, a_extra), m_exceptType{ a_Type }
{
	//
}

RTTIException::ExceptType RTTIException::type()const noexcept
{
	return m_exceptType;
}

#pragma warning(push)
#pragma warning(disable : 4065)

std::string RTTIException::message()const noexcept
{
	std::string message;
	switch (m_exceptType)
	{
#define RTTI_EXCEPTION(ExType, Message)\
	case ExceptType::ExType: \
		message = std::format("{} {}", std::string_view(#Message), m_extra);\
		break;

#include "RTTIException_macro.h"
#undef RTTI_EXCEPTION
	default:
		message = std::format("Unknown error {}", m_extra);
		
	}

	return message;
}

const char* RTTIException::what()const
{
	std::string message;
	switch (m_exceptType)
	{
#define RTTI_EXCEPTION(ExType, Message)\
	case Type::ExType: \
		message = std::format("{} {}", std::string_view(#Message), m_extra);\
		break;

#include "RTTIException_macro.h"
#undef RTTI_EXCEPTION
	default:
		message = std::format("Unknown error {}", m_extra);
	}
	return message.c_str();
}

#pragma warning(pop)
