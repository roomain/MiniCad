#pragma once
/***********************************************
* @headerfile TMCadRHIManager.h
* @date 18 / 01 / 2024
* @author Roomain
************************************************/
#include <string>
#include <unordered_map>
#include <functional>
#include <ranges>

template<typename Type>
class TMCadRHIRHIShared_ptr;

template<typename Type>
using ResourceProcess = std::function<void(const std::string&, TMCadRHIRHIShared_ptr<Type>)>;

template<typename Type>
class TMCadRHIResourceManager
{
protected:
	std::unordered_map<std::string, TMCadRHIRHIShared_ptr<Type>> m_ResourceDatabase; /*!< resource database*/

public:
	TMCadRHIManager( ) = default;
	virtual ~TMCadRHIManager( ) = default;
	TMCadRHIRHIShared_ptr<Type> at(const std::string& a_key)const noexcept
	{
		if ( m_ResourceDatabase.contains(a_key) )
			return m_ResourceDatabase.at(a_key);
		return TMCadRHIRHIShared_ptr<Type>;
	}

	void processAll(const ResourceProcess& a_processFun)
	{
		for ( auto [key, resource] : m_ResourceDatabase )
		{
			a_processFun(key, resource);
		}
	}

	virtual void erase(const MCadRHIRHIShared_ptr<Type>& a_resource)
	{
		std::erase_if(m_ResourceDatabase, [ & ] (auto&& a_iter)
			{
				return a_iter.second == a_resource;
			});
	}
};