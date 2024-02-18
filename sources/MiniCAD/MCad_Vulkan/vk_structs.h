#pragma once
#include <string>
#include "vulkan/vulkan.h"

[[nodiscard]] constexpr VkExtent2D extent2D(const uint32_t a_width, const uint32_t a_height)
{
	return VkExtent2D{ a_width, a_height };
}

[[nodiscard]] constexpr VkOffset2D offset2D(const int32_t a_x, const int32_t a_y)
{
	return VkOffset2D{ a_x, a_y };
}

[[nodiscard]] constexpr VkRect2D rect2D(const int32_t a_x, const int32_t a_y, const uint32_t a_width, const uint32_t a_height)
{
	return VkRect2D{ offset2D(a_x, a_y), extent2D(a_width, a_height) };
}

[[nodiscard]] constexpr VkExtent3D extent3D(const uint32_t a_width, const uint32_t a_height, const uint32_t a_depth)
{
	return VkExtent3D{ a_width, a_height, a_depth };
}

[[nodiscard]] constexpr VkOffset3D offset3D(const int32_t a_x, const int32_t a_y, const int32_t a_z)
{
	return VkOffset3D{ a_x, a_y, a_z };
}

//----------------------------------------------------------------------------------------------------------------
[[nodiscard]] constexpr VkApplicationInfo applicationInfo(const std::string& a_appName, 
	const uint32_t& a_appVersion,
	const std::string& a_engineName,
	const uint32_t& a_engineVersion)
{
	return VkApplicationInfo{ .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = nullptr,
		.pApplicationName = a_appName.c_str( ),
		.applicationVersion = a_appVersion,
		.pEngineName = a_engineName.c_str( ),
		.engineVersion = a_engineVersion,
		.apiVersion = VK_API_VERSION_1_3
	};
}

[[nodiscard]] constexpr VkInstanceCreateInfo instanceCreateInfo( )
{
	return VkInstanceCreateInfo{ .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, .pNext = nullptr, .flags = 0 };
}

[[nodiscard]] constexpr VkDebugReportCallbackCreateInfoEXT debugCallbackCreateInfo( )
{
	return VkDebugReportCallbackCreateInfoEXT{ .sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT };
}