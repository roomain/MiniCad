#pragma once
#include "RTTIDefinition.h"

/*@brief template RTTI definition*/
template<typename DefinedClass>
class TRTTIDefinition : public RTTIDefinition
{
public:
	TRTTIDefinition() = delete;
	TRTTIDefinition(const std::string_view& a_name, const unsigned short a_version) :
		RTTIDefinition(a_name, a_version) {}
	TRTTIDefinition(const std::string_view& a_name, const unsigned short a_version,
		const std::vector<std::shared_ptr<RTTIDefinition>>& a_vParents) :
		RTTIDefinition(a_name, a_version, a_vParents) {}

	/*@brief size of described class*/
	[[nodiscard]] virtual size_t classSize()const noexcept override { return sizeof(DefinedClass); }

	/*@brief create class*/
	std::shared_ptr<DefinedClass> create()
	{
		return std::make_shared<DefinedClass>();
	}
};


template<typename DefinedClass>
using TRTTIDefinitionPtr = std::shared_ptr<TRTTIDefinition<DefinedClass>>;