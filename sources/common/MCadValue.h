#pragma once
/***********************************************
* @headerfile MCadValue.h
* @date 11 / 10 / 2023
* @author Roomain
************************************************/

#include <variant>
#include <string>
#include <memory>
#include "glm/glm.hpp"

class MCadSelectionSet;
using MCadSelectionSetPtr = std::shared_ptr<MCadSelectionSet>;

using Empty = char;// because void not accepted by std::variant
using KeywordId = unsigned short;   /*!< represents a keyword identifier in menu*/

using MCadValue = std::variant<Empty, int, double, std::string, glm::dvec2, glm::dvec3, glm::dvec4, MCadSelectionSetPtr, KeywordId>;

inline MCadValue convert(const glm::vec3& a_value)
{
	return glm::dvec3(a_value);
}

inline MCadValue convert(const glm::vec2& a_value)
{
	return glm::dvec2(a_value);
}

inline MCadValue convert(const glm::vec4& a_value)
{
	return glm::dvec4(a_value);
}