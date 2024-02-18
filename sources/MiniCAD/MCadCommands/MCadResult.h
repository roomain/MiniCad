#pragma once
/***********************************************
* @headerfile MCadResult.h
* @date 03 / 12 / 2023
* @author Roomain
************************************************/
#include <variant>
#include "glm/glm.hpp"
#include "MCadResultException.h"

using MCadResult = std::variant<int, unsigned int, float, double,
	glm::ivec2, glm::ivec3, glm::ivec4, glm::vec2, glm::vec3, glm::vec4,
	glm::dvec2, glm::dvec3, glm::dvec4, glm::mat3, glm::dmat3, glm::mat4, 
	glm::dmat4, void*>;

/*@brief process result*/
class MCadResultProcess
{
public:
	virtual ~MCadResultProcess( ) = default;

	virtual void operator () (const int a_arg)
	{
		throw MCadResultException(std::source_location::current());
	}

	virtual void operator () (const unsigned int a_arg)
	{
		throw MCadResultException(std::source_location::current( ));
	}

	virtual void operator () (const float a_arg)
	{
		throw MCadResultException(std::source_location::current( ));
	}

	virtual void operator () (const double& a_arg)
	{
		throw MCadResultException(std::source_location::current( ));
	}

	virtual void operator () (const glm::ivec2& a_arg)
	{
		throw MCadResultException(std::source_location::current( ));
	}

	virtual void operator () (const glm::ivec3& a_arg)
	{
		throw MCadResultException(std::source_location::current( ));
	}

	virtual void operator () (const glm::ivec4& a_arg)
	{
		throw MCadResultException(std::source_location::current( ));
	}

	virtual void operator () (const glm::vec2& a_arg)
	{
		throw MCadResultException(std::source_location::current( ));
	}

	virtual void operator () (const glm::vec3& a_arg)
	{
		throw MCadResultException(std::source_location::current( ));
	}

	virtual void operator () (const glm::vec4& a_arg)
	{
		throw MCadResultException(std::source_location::current( ));
	}

	virtual void operator () (const glm::dvec2& a_arg)
	{
		throw MCadResultException(std::source_location::current( ));
	}

	virtual void operator () (const glm::dvec3& a_arg)
	{
		throw MCadResultException(std::source_location::current( ));
	}

	virtual void operator () (const glm::dvec4& a_arg)
	{
		throw MCadResultException(std::source_location::current( ));
	}

	virtual void operator () (const glm::mat3& a_arg)
	{
		throw MCadResultException(std::source_location::current( ));
	}

	virtual void operator () (const glm::dmat3& a_arg)
	{
		throw MCadResultException(std::source_location::current( ));
	}

	virtual void operator () (const glm::mat4& a_arg)
	{
		throw MCadResultException(std::source_location::current( ));
	}

	virtual void operator () (const glm::dmat4& a_arg)
	{
		throw MCadResultException(std::source_location::current( ));
	}

	virtual void operator () (...)
	{
		throw MCadResultException(std::source_location::current( ));
	}
};
