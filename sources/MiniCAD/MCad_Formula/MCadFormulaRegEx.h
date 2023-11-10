#pragma once
/***********************************************
* @headerfile MCadFormulaRegEx.h
* @date 15 / 10 / 2023
* @author Roomain
************************************************/
#include <string>
#include <regex>
#include <vector>
#include <functional>
#include "glm/glm.hpp"
#include "MCadStringTools.h"
#include "MCad_Formula_globals.h"

/*
* @brief this file provide regular expression functions for entry parsing
*/

////////////////////////////////////////////////////////////////////////////////
/* @brief
TYPE PARSE METHODS FOR CONSOLE ENTRY => User Command Interface is base on (more possibilities)

value separator is ; or ,

VARIABLE:
    * ${variable} variable name is only composed of letters

INT:
    * value (ex: 3)

DOUBLE:
    * value (ex: 3.2)

DISTANCE:
    * same as DOUBLE but only positive

ANGLE:
    * same as DOUBLE

POINT:
    * (X,Y) with X and Y are DOUBLE (Y is optional <=> Y = 0)
    * @(X,Y) with X and Y are DOUBLE (Y is optional <=> Y = 0) = translation from last 2D point

VECTOR:
    * <X,Y> with X and Y are DOUBLE (Y is optional <=> Y = 0)
    * @ANGLE<DISTANCE = polar coordinates

*/
////////////////////////////////////////////////////////////////////////////////

/*@brief configuration structure for parsing*/
struct MCadFormulaRegEx
{
    static inline const std::regex m_dotProdRegex{ "^<dot>" };                                /*!< dot prod operator regex*/
    static inline const std::regex m_crossProdRegex{ "^<cross>" };                            /*!< cross prod operator regex*/
    static inline const std::regex m_intRegex{ "^-?([1-9]+[0-9]*)|0" };                       /*!< int regex*/
    static inline const std::regex m_variableRegex{ "^\\$\\{[a-zA-Z]+(_ | [a-zA-Z])*\\}" };   /*!< variable name regex*/

    // depends on decimal and values separators
    std::regex m_doubleRegex{ "^$" };       /*!< double regex*/
    std::regex m_vec2DRegex{ "^$" };        /*!< vector 2d regex*/
    std::regex m_vec3DRegex{ "^$" };        /*!< vector 3d regex*/
    std::regex m_vec4DRegex{ "^$" };        /*!< vector 4d regex*/
    std::regex m_pt2DRegex{ "^$" };         /*!< point 2d regex*/
    std::regex m_pt3DRegex{ "^$" };         /*!< point 3d regex*/

    // specific vector data
    std::regex m_polarCoordRegex{ "^$" };        /*!< polar coord regex*/
    std::regex m_relCartesian3DRegex{ "^$" };    /*!< relative cartesian 3d regex*/
    std::regex m_relCartesian2DRegex{ "^$" };    /*!< relative cartesian 2d regex*/
    std::regex m_relPolarRegex{ "^$" };          /*!< relative polar regex*/

    // trigo regex and functions
    std::regex m_cosRegex{ R"(cos\()" };                             /*!<cos regex*/
    std::regex m_sinRegex{ R"(sin\()" };                             /*!<sin regex*/
    std::regex m_tanRegex{ R"(tan\()" };                             /*!<tan regex*/
    std::regex m_acosRegex{ R"(acos\()" };                           /*!<acos regex*/
    std::regex m_asinRegex{ R"(asin\()" };                           /*!<asin regex*/
    std::regex m_atanRegex{ R"(atan\()" };                           /*!<atan regex*/
    std::regex m_functionRegex{ R"([a-zA-Z]+(_ | [a-zA-Z])*\()" };   /*!<function regex*/

    static constexpr char PolarSeparator = '<';
};

/*@brief initialize MCadFormulaRegEx structure*/
inline static void initialize(const char a_decimalSeparator, const char a_valueSeparator, MCadFormulaRegEx& a_formulaRegEx)
{
    std::string regExdecimalSeparator = ( a_decimalSeparator == '.' ) ? std::string("\\.") : std::string("" + a_decimalSeparator);
    std::string sDouble = std::string("-?(([1-9]+[0-9]*)|([0-9]))") + regExdecimalSeparator + std::string("[0-9]*");
    a_formulaRegEx.m_doubleRegex = std::regex{ std::string("^") + sDouble };
    a_formulaRegEx.m_vec2DRegex = std::regex{ std::string("^<") + sDouble + a_valueSeparator + sDouble + ">" };
    a_formulaRegEx.m_vec3DRegex = std::regex{ std::string("^<") + sDouble + a_valueSeparator + sDouble + a_valueSeparator + sDouble + ">" };
    a_formulaRegEx.m_vec4DRegex = std::regex{ std::string("^<") + sDouble + a_valueSeparator + sDouble + a_valueSeparator + sDouble + a_valueSeparator + sDouble + ">" };
    a_formulaRegEx.m_pt2DRegex = std::regex{ std::string("^\\(") + sDouble + a_valueSeparator + sDouble + "\\)" };
    a_formulaRegEx.m_pt3DRegex = std::regex{ std::string("^\\(") + sDouble + a_valueSeparator + sDouble + a_valueSeparator + sDouble + "\\)" };

    a_formulaRegEx.m_polarCoordRegex = std::regex{ std::string("^") + sDouble + "<" + sDouble };
    a_formulaRegEx.m_relCartesian2DRegex = std::regex{ std::string("^@\\(") + sDouble + a_valueSeparator + sDouble + "\\)" };
    a_formulaRegEx.m_relCartesian3DRegex = std::regex{ std::string("^@\\(") + sDouble + a_valueSeparator + sDouble + a_valueSeparator + sDouble + "\\)" };
    a_formulaRegEx.m_relPolarRegex = std::regex{ std::string("^@") + sDouble + "<" + sDouble };
}

/*@brief Get data from string. The string entries are supposed correct*/

/*@brief Get double from string taking account decimal separator*/
inline static double getDouble(const std::string_view& a_toParse, const char a_decimalSeparator)
{
    std::string result(a_toParse);
    auto iterator = result.find(a_decimalSeparator);
    if ( iterator != std::string::npos )
        return std::stod(result.replace(result.find(a_decimalSeparator), 1, "."));
    return std::stod(result);
}


/*@brief Get vector or point from string taking account decimal separator and value separator*/
template<int VecSize>
inline static glm::vec<VecSize, double, glm::defaultp> getVector(const std::string_view& a_toParse, const char a_decimalSeparator, const char a_valueSeparator)
{
    using VecType = glm::vec<VecSize, double, glm::defaultp>;
    
    // remove start and end symbols
    std::string workingData(a_toParse.substr(1, a_toParse.size( ) - 2));
    std::vector<std::string> vdata;
    split(workingData, a_valueSeparator, vdata);
    VecType vRet;
    int index = 0;
    for ( auto&& strValue : vdata )
    {
        vRet [ index ] = getDouble(strValue, a_decimalSeparator);
        ++index;
    }
    return vRet;
}

/*@brief Get relative point from string taking account decimal separator and value separator*/
template<int VecSize>
inline static glm::vec<VecSize, double, glm::defaultp> getRelative(const std::string_view& a_toParse, const char a_decimalSeparator, const char a_valueSeparator)
{
    return getVector<VecSize>(a_toParse.substr(1, a_toParse.size( ) - 1), a_decimalSeparator, a_valueSeparator);
}

struct PolarCoord
{
    double m_angle;     /*!< polar angle*/
    double m_distance;  /*!< distance*/
};

/*@brief Get polar value*/
MCAD_FORMULA_EXPORT PolarCoord getPolar(const std::string_view& a_toParse, const char a_decimalSeparator);

/*@brief Get relative polar value*/
MCAD_FORMULA_EXPORT PolarCoord getRelativePolar(const std::string_view& a_toParse, const char a_decimalSeparator);


template<typename ...Args>
struct RegExReactor
{
    std::regex m_regularExp;
    std::function<void(const std::string_view&, Args&&...)> m_reaction;
};

template<typename ...Args>
using VRegExReactor = std::vector<RegExReactor<Args...>>;

template<typename ...Args>
bool parseAndReact(const std::string& a_toParse, const VRegExReactor<Args...>& a_vReactor, int& a_matchLen, Args&&... a_arguments)
{
    for ( auto&& regReac : a_vReactor )
    {
        std::smatch match;
        if ( std::regex_search(a_toParse, match, regReac.m_regularExp) && match.prefix( ).length( ) == 0 )
        {
            a_matchLen = static_cast<int>(match.length());
            regReac.m_reaction(match.str(), a_arguments...);
            return true;
        }
    }
    return false;
}