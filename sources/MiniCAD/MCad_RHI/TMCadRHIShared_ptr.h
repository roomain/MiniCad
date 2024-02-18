#pragma once
/***********************************************
* @headerfile TMCadRHIRHIShared_ptr.h
* @date 20 / 01 / 2024
* @author Roomain
************************************************/
#include <memory>

template<typename Type>
class MCadRHIResourceManager;

template<typename Type>
using MCadRHIResourceManagerPtr = std::shared_ptr<MCadRHIResourceManager<Type>>;

/*@brief specific shared pointer*/
template<typename Type>
class TMCadRHIRHIShared_ptr : private std::shared_ptr<Type>
{
	friend MCadRHIResourceManager<Type>;

private:
	MCadRHIResourceManagerPtr<Type> m_pManager;

	explicit TMCadRHIRHIShared_ptr(const MCadRHIResourceManagerPtr& a_manager, std::shared_ptr<Type>&& a_other) :
		std::shared_ptr<Type>(a_other), m_pManager{ a_manager }
	{
	}

public:
	TMCadRHIRHIShared_ptr( ) = default;
	
	explicit TMCadRHIRHIShared_ptr(const TMCadRHIRHIShared_ptr<Type>& a_other) :
		std::shared_ptr<Type>(a_other), m_pManager{ a_other.m_pManager }
	{
	}


	virtual ~TMCadRHIRHIShared_ptr( )
	{
		if ( m_pManager && ( std::shared_ptr<Type>::use_count() == 1))
		{
			m_pManager->erase(*this);
		}
	}

	bool operator == (const TMCadRHIRHIShared_ptr<Type>& a_other)
	{
		return std::shared_ptr<Type>::operator == (a_other);
	}
};