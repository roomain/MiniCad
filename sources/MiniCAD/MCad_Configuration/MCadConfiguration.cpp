#include "pch.h"
#include "MCadConfiguration.h"

MCadConfiguration& MCadConfiguration::Instance( )
{
	static MCadConfiguration s_instance;
	return s_instance;
}

MCadConfigurationModulePtr MCadConfiguration::operator [](const std::string& a_module)const
{
	return m_modulesConfigurations.at(a_module);
}

MCadConfiguration::MCadConfiguration( )
{
	//
}