#pragma once
/***********************************************
* @headerfile MCadVulkanDevice.h
* @date 20 / 01 / 2024
* @author Roomain
************************************************/
#include "vulkan/vulkan.hpp"
#include "MCadRHIDevice.h"

class MCadVulkanDevice : public MCadRHIDevice
{
private:
	VkDevice m_logicalDevice;			/*!< vulkan logical device*/
	VkPhysicalDevice m_physicalDevice;	/*!< vulkan physical device*/
	// TODO

public:
	//
};
