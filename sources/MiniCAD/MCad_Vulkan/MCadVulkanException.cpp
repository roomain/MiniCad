#include "pch.h"
#include <format>
#include "MCadVulkanException.h"
#include "vk_enum_to_string.h"

MCadVulkanException::MCadVulkanException(const VkResult a_Type, const std::source_location& a_loc) :
	MCadException(a_loc, ""), m_exceptType{ a_Type }
{
	//
}

#pragma warning(push)
#pragma warning(disable : 4065)

std::string MCadVulkanException::message( )const noexcept
{
	return to_string(m_exceptType);
}

const char* MCadVulkanException::what( )const
{
	return to_string(m_exceptType).c_str( );
}


#pragma warning(pop)