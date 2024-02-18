#pragma once
/***********************************************
* @headerfile TMCadObjectProxy.h
* @date 17 / 09 / 2023
* @author Roomain
************************************************/
#include <variant>
#include "MCadMemory.h"
#include "MCadRef.h"
#include "defines.h"

template<typename Type>
class TMCadObjectProxy
{
private:
	using Proxy = std::variant<std::weak_ptr<Type>, MCadRef<Type>>;
	
	Proxy m_proxyObj;
	ObjectUID m_objectUID;
	std::weak_ptr<RTTIDefinition> m_pObjectDef;

	struct ValidVisitor
	{
		bool operator ()(const std::weak_ptr<Type>& a_ptr)const
		{
			return !a_ptr.expired( );
		}

		bool operator ()(const MCadRef<Type>& a_ref)const
		{
			return a_ref.valid( );
		}
	};

	struct RealocableVisitor
	{
		bool operator ()([[maybe_unused]] const std::weak_ptr<Type>& a_ptr)const
		{
			return true;
		}

		bool operator ()([[maybe_unused]] const MCadRef<Type>& a_ref)const
		{
			return false;
		}
	};

	struct PointerVisitor
	{
		Type* const operator ()(const std::weak_ptr<Type>& a_ptr)const
		{
			return a_ptr.lock( ).get( );
		}

		Type* const operator ()(const MCadRef<Type>& a_ref)const
		{
			return a_ref.pointer( );
		}
	};

	struct RealocVisitor
	{
		MCadReallocMemory* const m_memory;
		ObjectUID m_objID;
		std::weak_ptr<RTTIDefinition> m_pDef;

		bool operator ()(std::weak_ptr<Type>& a_ptr)const
		{
			if constexpr ( std::is_base_of_v<MCadObject, Type> )
			{
				if ( a_ptr.expired( ) )
				{
					a_ptr = MStatic_pointer_cast< Type >( m_memory->realoc(m_objID, m_pDef) );
				}
			}
			return !a_ptr.expired( );
		}

		bool operator ()(const MCadRef<Type>& a_ref)const
		{
			return a_ref.valid( );
		}
	};

public:
	TMCadObjectProxy( ) = delete;
	explicit TMCadObjectProxy(Type* const a_object)
	{
		if ( a_object )
		{
			if constexpr ( std::is_base_of_v<MCadObject, Type> )
			{
				m_objectUID = a_object->uid( );
				m_pObjectDef = a_object->isA( );
				if ( a_object->isShared( ) )
				{
					m_proxyObj = std::dynamic_pointer_cast< Type >( a_object->shared_from_this( ) );
				}
				else
				{
					m_proxyObj = make_ref<Type>(*a_object);
				}
			}
			else
			{
				m_proxyObj = make_ref<Type>(*a_object);
			}
		}
	}
	
	explicit TMCadObjectProxy(const TMCadObjectProxy<Type>& a_other) :
		m_proxyObj{ a_other.m_proxyObj },
		m_objectUID{ a_other.m_objectUID },
		m_pObjectDef{ a_other.m_pObjectDef }
	{
		//
	}

	explicit TMCadObjectProxy(TMCadObjectProxy<Type>&& a_other)noexcept :
		m_proxyObj{ std::move(a_other.m_proxyObj) },
		m_objectUID{ std::move(a_other.m_objectUID) },
		m_pObjectDef{ std::move(a_other.m_pObjectDef) }
	{
		//
	}

	bool valid( )const
	{
		return  std::visit(ValidVisitor{}, m_proxyObj);
	}

	bool isRealocable( )
	{
		return  std::visit(RealocableVisitor{}, m_proxyObj);
	}

	bool realocate(MCadReallocMemory& a_memory)
	{
		return  std::visit(RealocVisitor{ &a_memory , m_objectUID , m_pObjectDef }, m_proxyObj);
	}

	Type* const operator -> ( )
	{
		return  std::visit(PointerVisitor{}, m_proxyObj);
	}

	Type* const pointer( )
	{
		return std::visit(PointerVisitor{}, m_proxyObj);
	}

	constexpr ObjectUID objectUID( )const { return m_objectUID; }

	std::weak_ptr<RTTIDefinition> objectDef( )const { return m_pObjectDef; }
};