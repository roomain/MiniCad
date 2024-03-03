#include "pch.h"
#include "MCadVkJSON.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


MCadVkJSON::MCadVkJSON( )
{
	//
}

bool MCadVkJSON::load(const std::string& a_filepath)
{
	boost::property_tree::ptree jsonTree;
	boost::property_tree::json_parser::read_json(a_filepath, jsonTree);
	if ( !jsonTree.empty() )
	{
		for ( const auto& [key, value] : jsonTree.get_child(INSTANCE_EXTENSIONS) )
			m_instanceExtensions.emplace_back(value.get_value<std::string>( ));
		
		for ( const auto& [key, value] : jsonTree.get_child(INSTANCE_LAYERS) )
			m_instanceLayers.emplace_back(value.get_value<std::string>( ));

		//jsonTree.get<int>("height", 0)
		//jsonTree.
	}
	else
	{
		return false;
	}
}

StringVector MCadVkJSON::instanceLayers( )const
{
	return m_instanceLayers;
}

StringVector MCadVkJSON::instanceExtensions( )const
{
	return m_instanceExtensions;
}


StringVector MCadVkJSON::deviceLayers( )const
{
	return m_deviceLayers;
}

StringVector MCadVkJSON::deviceExtensions( )const
{
	return m_deviceExtensions;
}