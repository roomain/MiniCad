#pragma once
/***********************************************
* @headerfile MCadConfiguration.h
* @date 26 / 10 / 2023
* @author Roomain
************************************************/
#include <unordered_map>
#include <memory>
#include <string>
#include "MCadProperty.h"
#include "MCadDependProperty.h"
#include "MCadAngle.h"
#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "MCadSingletonMacro.h"
#include "MCad_Configuration_globals.h"

#pragma warning(push)
#pragma warning(disable : 4251)

class MCadConfigurationModule;
using MCadConfigurationModulePtr = std::shared_ptr<MCadConfigurationModule>;
using ModulesConfigurations = std::unordered_map<std::string, MCadConfigurationModulePtr>;

/*@brief configuration singleton*/
class MCAD_CONFIGURATION_EXPORT MCadConfiguration
{
	NOT_COPIABLE(MCadConfiguration)
private:
	MCadConfiguration( );
	ModulesConfigurations m_modulesConfigurations; /*!< module configurations*/

public:
	static [[nodiscard]] MCadConfiguration& Instance( );
	virtual ~MCadConfiguration( ) = default;
	[[nodiscard]] MCadConfigurationModulePtr operator [](const std::string& a_module)const;

#define PROPERTY_DEF_DEFAULT_INIT(Type, Name) \
	MCadProperty<Type> Name{#Name};

#define PROPERTY_DEF(Type, Name, DefaultValue) \
	MCadProperty<Type> Name{#Name, DefaultValue};

#define PROPERTY_READ_ONLY_DEF(Type, Name, DefaultValue) \
	MCadProperty<Type, true> Name{#Name, DefaultValue};

#define PROPERTY_VALID_DEF(Type, Name, Valid, DefaultValue) \
	MCadValidProperty<Type, Valid> Name{#Name, DefaultValue};

#define PROPERTY_DEPENDANT_One_DEF(Type, dependType, Name) \
	MCadDependProperty<Type, dependType> Name{#Name, DefaultValue};

#define PROPERTY_DEPENDANT_Two_DEF(Type, dependType1, dependType2, Name) \
	MCadDependPropertyEx<Type, dependType1, dependType2> Name{#Name};

#include "MCadPropertiesDef.h"

#undef PROPERTY_VALID_DEF
#undef PROPERTY_READ_ONLY_DEF
#undef PROPERTY_DEF
};

#pragma warning(pop)