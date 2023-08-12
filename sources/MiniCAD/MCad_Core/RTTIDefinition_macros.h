#pragma once

/***********************************************
* @headerfile RTTIDefinition_macro.h
* @date 16 / 07 / 2023
* @author Roomain
************************************************/

#include <format>
#include "TRTTIDefinition.h"
#include "RTTIException.h"
#include <source_location>


/*
* @warning The RTTI macro doesnt work with multi template!
*/

template<typename ...Types>
class DefinitionsStub {};

/*@brief check if RTTI definition classes are defined for Type and Other ... and get them definition*/
template<typename Type, typename ...Other>
constexpr void getAndCheckDefinition(std::vector<RTTIDefinitionPtr>& a_vDef, DefinitionsStub<Type, Other ...>&& a_trash)
{
	if (!Type::definition())
		throw RTTIException(RTTIException::ExceptType::Except_ParentNotDefined, 
			std::source_location::current(),
			std::format("Classname {}", typeid(Type).name()));
	a_vDef.push_back(Type::definition());
	getAndCheckDefinition(a_vDef, DefinitionsStub<Other ...>());
}

template<typename Type>
constexpr void getAndCheckDefinition(std::vector<RTTIDefinitionPtr>& a_vDef, DefinitionsStub<Type>&& a_trash)
{
	if (!Type::definition())
		throw RTTIException(RTTIException::ExceptType::Except_ParentNotDefined,
			std::source_location::current(), 
			std::format("Classname {}", typeid(Type).name()));
	a_vDef.push_back(Type::definition());
}

/*@brief Generate static member for RTTI*/
#define BASE_RTTI_STATIC(version, classname) \
	friend class TRTTIDefinition<classname>; \
private: \
	static inline TRTTIDefinitionPtr<classname> s_definition; \
\
public: \
\
	[[nodiscard]] static inline RTTIDefinitionPtr definition()noexcept { return s_definition; }\
	\
	static inline void releaseDef()\
	{\
		if(s_definition.use_count() > 1)\
			throw RTTIException(RTTIException::ExceptType::Except_CantUnitialize, std::source_location::current());\
		s_definition.reset(); \
	}\
	

//------------------------------------------------------------------------------------------------------------------------------------
/*@brief Generate base member functions for RTTI*/
#define BASE_DEFINITION_MACRO(version, classname) \
public:\
	template<typename Type>\
	[[nodiscard]] constexpr bool isTypeOf()const \
	{\
		return std::is_same<Type, classname>::value;\
	}\
\
	[[nodiscard]] virtual inline RTTIDefinitionPtr isA()const \
	{\
		if(!classname::s_definition)\
			throw RTTIException(RTTIException::ExceptType::Except_NotDefined, std::source_location::current()); \
		return classname::s_definition; \
	}\
\
	[[nodiscard]] virtual inline bool isKindOf(const RTTIDefinitionPtr& a_def)const \
	{\
		if(!classname::s_definition)\
			throw RTTIException(RTTIException::ExceptType::Except_NotDefined, std::source_location::current()); \
		return classname::s_definition->isKindOf(a_def); \
	}\
\
	template<typename KindType> \
	[[nodiscard]] inline bool isKindOf()const \
	{\
		if(!classname::s_definition)\
			throw RTTIException(RTTIException::ExceptType::Except_NotDefined, std::source_location::current()); \
		return classname::s_definition->isKindOf(KindType::definition()); \
	}\
\
	[[nodiscard]] inline ProtocolExtensionPtr getProtocolExt(const RTTIDefinitionPtr& a_def)const \
	{\
		if(!classname::s_definition)\
			throw RTTIException(RTTIException::ExceptType::Except_NotDefined, std::source_location::current()); \
		return classname::s_definition->getProtocolExt(a_def); \
	}\
\
	template<typename KindType> \
	[[nodiscard]] inline ProtocolExtensionPtr getProtocolExt()const \
	{\
		if(!classname::s_definition)\
			throw RTTIException(RTTIException::ExceptType::Except_NotDefined, std::source_location::current()); \
		return classname::s_definition->getProtocolExt(KindType::definition()); \
	}\
\
	template<typename Type>\
	[[nodiscard]] Type* const cast()const\
	{\
		Type* pRet = nullptr; \
		if (isKindOf(Type::definition()))\
		{\
			pRet = const_cast<Type*>(dynamic_cast<const Type*>(this));\
		}\
		return pRet;\
	}\

//------------------------------------------------------------------------------------------------------------------------------------
/*@brief define static ctor*/
#define STATIC_CTOR(classname)\
public:\
static std::shared_ptr<classname> createObject() \
{ \
	if(s_definition) \
		return s_definition->create(); \
	return nullptr; \
}

/*@brief declare RTTI for a simple class*/
#define DECLARE_RTTI(version, classname) \
STATIC_CTOR(classname) \
BASE_RTTI_STATIC(version, classname)\
BASE_DEFINITION_MACRO(version, classname)\
public: \
	static void initDef()\
	{\
		if(!s_definition) \
			s_definition = std::make_shared<TRTTIDefinition<classname>>(std::string(#classname), version); \
	}

/*@brief declare RTTI for a derived class: DECLARE_RTTI_DERIVED(version, classname, parents classes) */
#define DECLARE_RTTI_DERIVED(version, classname, ...) \
STATIC_CTOR(classname) \
BASE_RTTI_STATIC(version, classname)\
BASE_DEFINITION_MACRO(version, classname)\
public: \
	static void initDef()\
	{\
		std::vector<RTTIDefinitionPtr> vParentDefs;\
		getAndCheckDefinition(vParentDefs, DefinitionsStub<__VA_ARGS__>());\
		s_definition = std::make_shared< TRTTIDefinition<classname>>(std::string(#classname), version, vParentDefs); \
	}

