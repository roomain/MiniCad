#include "pch.h"
#include "MCadRegexConfiguration.h"


MCadRegexConfiguration::MCadRegexConfiguration( )
{
	DECIMAL_SEPARATOR.addReactor([ this ] (const std::string& a_property, const char& a_before, const char& a_after)
		{
			this->updateRegex(a_after);
		});
	updateRegex('.');
}

void MCadRegexConfiguration::updateRegex(const char& a_separator)
{
	const char valueSeparator = ( a_separator == ',' ) ? ';' : ',';
	VALUE_SEPARATOR.m_propertyValue = valueSeparator;
	std::string regExdecimalSeparator = ( a_separator == '.' ) ? std::string("\\.") : std::string("" + a_separator);
	std::string sDouble = std::string("-?(([1-9]+[0-9]*)|([0-9]))") + regExdecimalSeparator + std::string("[0-9]*");
	DOUBLE_REGEX.m_propertyValue = std::regex{ std::string("^") + sDouble };
	VEC2_REGEX.m_propertyValue = std::regex{ std::string("^<") + sDouble + valueSeparator + sDouble + ">" };
	VEC3_REGEX.m_propertyValue = std::regex{ std::string("^<") + sDouble + valueSeparator + sDouble + valueSeparator + sDouble + ">" };
	VEC4_REGEX.m_propertyValue = std::regex{ std::string("^<") + sDouble + valueSeparator + sDouble + valueSeparator + sDouble + valueSeparator + sDouble + ">" };
	PT2_REGEX.m_propertyValue = std::regex{ std::string("^\\(") + sDouble + valueSeparator + sDouble + "\\)" };
	PT3_REGEX.m_propertyValue = std::regex{ std::string("^\\(") + sDouble + valueSeparator + sDouble + valueSeparator + sDouble + "\\)" };

	POLAR_COORD_REGEX.m_propertyValue = std::regex{ std::string("^") + sDouble + "<" + sDouble };
	REL_3D_CARTESIAN_REGEX.m_propertyValue = std::regex{ std::string("^@\\(") + sDouble + valueSeparator + sDouble + "\\)" };
	REL_2D_CARTESIAN_REGEX.m_propertyValue = std::regex{ std::string("^@\\(") + sDouble + valueSeparator + sDouble + valueSeparator + sDouble + "\\)" };
	REL_POLAR_REGEX.m_propertyValue = std::regex{ std::string("^@") + sDouble + "<" + sDouble };
}

bool MCadRegexConfiguration::valid(const char& a_separator)
{
	return ( a_separator == ',' ) || ( a_separator == '.' );
}