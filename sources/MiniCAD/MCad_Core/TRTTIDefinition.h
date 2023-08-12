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
	[[nodiscard]] std::shared_ptr<MCadObject> create(const unsigned long long& a_objectUID)const final
	{
		if constexpr(std::is_base_of_v<MCadObject, DefinedClass>  && !std::is_abstract_v<DefinedClass>)
		{
			MCadObject::enableUIDGenerator(false);
			auto ptrObj =  std::make_shared<DefinedClass>();
			ptrObj->setUID(a_objectUID);
			MCadObject::enableUIDGenerator(true);
			RTTIDefinition::registerToDocument(ptrObj);
			return ptrObj;
		}
		return nullptr;
	}

	/*@brief create class*/
	[[nodiscard]] std::shared_ptr<DefinedClass> create()const
	{
		if constexpr (std::is_base_of_v<MCadObject, DefinedClass> && !std::is_abstract_v<DefinedClass>)
		{
			auto ptrObj = std::make_shared<DefinedClass>();
			RTTIDefinition::registerToDocument(ptrObj);
			return ptrObj;
		}
		return nullptr;
	}
};


template<typename DefinedClass>
using TRTTIDefinitionPtr = std::shared_ptr<TRTTIDefinition<DefinedClass>>;