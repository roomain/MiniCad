#pragma once
/***********************************************
* @headerfile MCadTypeToString.h
* @date 16 / 07 / 2023
* @author Roomain
************************************************/
#include <string>
#include "MCadValue.h"


struct MCadTypeToString
{
	std::string operator()(const float a_value)const
	{
		return "Float";
	}

	std::string operator()(const double& a_value)const
	{
		return "Double";
	}

	std::string operator()(const int a_value)const
	{
		return "Integer";
	}

	std::string operator()(const glm::dvec2& a_value)const
	{
		return "Vector 2D";
	}

	std::string operator()(const glm::dvec3& a_value)const
	{
		return "Vector 3D";
	}

	std::string operator()(const glm::dvec4& a_value)const
	{
		return "Vector 4D";
	}

	std::string operator()(...)const
	{
		// TODO
		throw;
	}
};

constexpr MCadTypeToString GMCadTypeToString;

template<typename Type>
[[nodiscard]] std::string typeToString(const Type& a_value)
{
	return GMCadTypeToString::operator()(a_value);
}

template<>
[[nodiscard]] std::string typeToString(const MCadValue& a_value)
{
	return std::visit(GMCadTypeToString, a_value);
}

/*
void printTypes()
{
	std::cout << "That's all folks!" << std::endl;
}

template<typename Type, typename ...Others>
void printTypes(const Type& a_first, const Others&... a_others)
{
	std::cout << typeid(a_first).name() << std::endl;
	printTypes(a_others...);
}
*/