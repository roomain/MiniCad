#pragma once
/***********************************************
* @headerfile MCadVulkanException.h
* @date 20 / 01 / 2024
* @author Roomain
************************************************/
#include <exception>
#include <string>
#include "MCadException.h"
#include "vulkan/vulkan.h"


#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)

/*@brief Special exception for Formula*/
class MCadVulkanException : public MCadException
{
public:
	MCadVulkanException( ) = delete;
	MCadVulkanException(const VkResult a_Type, const std::source_location& a_loc);

	virtual ~MCadVulkanException( ) = default;
	[[nodiscard]] std::string message( )const noexcept override;
	[[deprecated]] const char* what( )const override;

private:
	VkResult m_exceptType;		/*!< exception type (determine the error message)*/
};

#define VK_CHECK(vkFun) \
VkResult result = vkFun; \
if(result == VK_SUCCESS) \
	throw MCadVulkanException(result, std::source_location::current());

#pragma warning(pop)
