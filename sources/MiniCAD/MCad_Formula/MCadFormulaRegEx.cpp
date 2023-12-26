#include "pch.h"
#include "MCadFormulaRegEx.h"

/*@brief Get polar value*/
PolarCoord getPolar(const std::string_view& a_toParse)
{
    std::vector<std::string> vdata;
    split(a_toParse, MCadConfiguration::Instance( ).POLAR_SEPARATOR.value( ), vdata);
    return PolarCoord{ getDouble(vdata [ 0 ]), getDouble(vdata [ 1 ]) };
}

/*@brief Get relative polar value*/
PolarCoord getRelativePolar(const std::string_view& a_toParse)
{
    return getPolar(a_toParse.substr(1, a_toParse.size( ) - 1));
}
