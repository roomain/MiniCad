#pragma once
/***********************************************
* @headerfile MCadVulkanDriver.h
* @date 20 / 01 / 2024
* @author Roomain
************************************************/
#include "MCadRHIDriver.h"
#include "vulkan/vulkan.h"

class MCadVulkanDriver : public MCadRHIDriver
{
private:
	VkInstance m_vulkanInstance;	/*!< vulkan instance*/

	/*debug callbacks*/
	static inline PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT = nullptr;
	static inline PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT = nullptr;

public:
	void enumerateDevices( );

	MCadVulkanDriver( );
};