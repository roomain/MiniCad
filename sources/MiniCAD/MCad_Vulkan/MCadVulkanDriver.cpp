#include "pch.h"
#include <vector>
#include "MCadVulkanDriver.h"
#include "MCadVulkanException.h"
#include "vk_structs.h"



void MCadVulkanDriver::enumerateDevices( )
{
	uint32_t devCount = 0;
	std::vector<VkPhysicalDevice> vDevices;
	VK_CHECK(vkEnumeratePhysicalDevices(m_vulkanInstance, &devCount, nullptr));
	vDevices.reserve(devCount);
	VK_CHECK(vkEnumeratePhysicalDevices(m_vulkanInstance, &devCount, vDevices.data( )));
	//
}

MCadVulkanDriver::MCadVulkanDriver( )
{
	VkApplicationInfo appInfo = applicationInfo("MiniCad", 1, "MCadEngine", 1);
	//
}