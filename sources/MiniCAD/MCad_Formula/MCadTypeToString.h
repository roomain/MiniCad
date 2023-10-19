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
		return "Unknown type";
	}
};

constexpr MCadTypeToString GMCadTypeToString;

template<typename Type>
[[nodiscard]] std::string typeToString(const Type& a_value)
{
	return GMCadTypeToString::operator()(a_value);
}

template<>
[[nodiscard]] inline std::string typeToString(const MCadValue& a_value)
{
	return std::visit(GMCadTypeToString, a_value);
}


[[nodiscard]] constexpr std::string printTypes()
{
	return "";
}

template<typename Type, typename ...Others>
[[nodiscard]] std::string printTypes(const Type& a_first, const Others&... a_others)
{
	std::string sType = typeToString(a_first) + ", " + typeToString(a_others...);
	return sType;
}
