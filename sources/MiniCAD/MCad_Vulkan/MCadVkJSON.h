#pragma once
/***********************************************
* @headerfile MCadVkJSON.h
* @date 20 / 01 / 2024
* @author Roomain
************************************************/
#include <string>
#include <vector>

using StringVector = std::vector<std::string>;

/*Read vulkan configuration*/
class MCadVkJSON
{
private:
	StringVector m_instanceLayers;
	StringVector m_instanceExtensions;
	StringVector m_deviceLayers;
	StringVector m_deviceExtensions;

	static constexpr std::string INSTANCE_EXTENSIONS{ "INSTANCE_EXTENSIONS" };
	static constexpr std::string INSTANCE_LAYERS{ "INSTANCE_LAYERS" };

	static constexpr std::string DEVICE_EXTENSIONS{ "DEVICE_EXTENSIONS" };
	static constexpr std::string DEVICE_LAYERS{ "DEVICE_LAYERS" };

public:
	MCadVkJSON( );
	virtual ~MCadVkJSON( ) = default;
	bool load(const std::string& a_filepath);

	StringVector instanceLayers( )const;
	StringVector instanceExtensions( )const;

	StringVector deviceLayers( )const;
	StringVector deviceExtensions( )const;
};
