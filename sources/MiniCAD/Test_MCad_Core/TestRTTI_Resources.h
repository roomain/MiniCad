#pragma once
#include "RTTIDefinition_macros.h"

class VirtualClass
{
	DECLARE_RTTI(1, VirtualClass)
public:
	explicit VirtualClass() = default;
	virtual ~VirtualClass() = default;
	virtual float data()const = 0;
};

class DerivedFromVirtualClass : public VirtualClass
{
	DECLARE_RTTI_DERIVED(1, DerivedFromVirtualClass, VirtualClass)
public:
	explicit DerivedFromVirtualClass() = default;
	~DerivedFromVirtualClass() = default;
	float data()const final { return 1.5f; }
};

//-------------------------------------------------------------------------

class DerivedFromClass : public DerivedFromVirtualClass
{
	DECLARE_RTTI_DERIVED(1, DerivedFromClass, DerivedFromVirtualClass)
public:
	explicit DerivedFromClass() = default;
	~DerivedFromClass() = default;
};

class OtherClass
{
	DECLARE_RTTI(1, OtherClass)
public:
	explicit OtherClass() = default;
	virtual ~OtherClass() = default;
};

class MultiDerivativeClass : public DerivedFromClass, public OtherClass
{
	DECLARE_RTTI_DERIVED(1, MultiDerivativeClass, DerivedFromClass, OtherClass)
public:
	explicit MultiDerivativeClass() = default;
	~MultiDerivativeClass() = default;
};

template<typename T>
class TemplateClass
{
	DECLARE_RTTI(1, TemplateClass<T>)
public:
	explicit TemplateClass() = default;
	virtual ~TemplateClass() = default;
};

template<typename T>
class TemplateDerivatedClass : public OtherClass
{
	DECLARE_RTTI_DERIVED(1, TemplateDerivatedClass<T>, OtherClass)
public:
	explicit TemplateDerivatedClass() = default;
	virtual ~TemplateDerivatedClass() = default;
};

template<typename T>
class TemplateDerivatedClassAux : public OtherClass
{
	DECLARE_RTTI_DERIVED(1, TemplateDerivatedClassAux<T>, TemplateClass<T>)
public:
	explicit TemplateDerivatedClassAux() = default;
	virtual ~TemplateDerivatedClassAux() = default;
};
