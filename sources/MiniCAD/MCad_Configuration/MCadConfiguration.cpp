#include "pch.h"
#include "MCadConfiguration.h"
#include "glm/gtc/quaternion.hpp"

glm::mat4 computeMat(glm::mat4& a_mat, const glm::vec3& a_origin, const glm::quat& a_orient)
{
	a_mat = glm::translate(glm::mat4_cast(a_orient), a_origin);
	return a_mat;
}

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
	USER_TRANSFORM.setDependancies(&computeMat, USER_ORIGIN, USER_ORIENTATION);
}