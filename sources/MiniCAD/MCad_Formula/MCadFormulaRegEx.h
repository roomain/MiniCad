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
#include "MCadConfiguration.h"
#include "MCad_Formula_globals.h"

/*@brief Get data from string. The string entries are supposed correct*/

/*@brief Get double from string taking account decimal separator*/
inline static double getDouble(const std::string_view& a_toParse)
{
    std::string result(a_toParse);
    auto iterator = result.find(MCadConfiguration::Instance( ).DECIMAL_SEPARATOR.value( ));
    if ( iterator != std::string::npos )
        return std::stod(result.replace(result.find(MCadConfiguration::Instance().DECIMAL_SEPARATOR.value()), 1, "."));
    return std::stod(result);
}


/*@brief Get vector or point from string taking account decimal separator and value separator*/
template<int VecSize>
inline static glm::vec<VecSize, double, glm::defaultp> getVector(const std::string_view& a_toParse)
{
    using VecType = glm::vec<VecSize, double, glm::defaultp>;
    
    // remove start and end symbols
    std::string workingData(a_toParse.substr(1, a_toParse.size( ) - 2));
    std::vector<std::string> vdata;
    split(workingData, MCadConfiguration::Instance( ).VALUE_SEPARATOR.value( ), vdata);
    VecType vRet;
    int index = 0;
    for ( const auto& strValue : vdata )
    {
        vRet [ index ] = getDouble(strValue);
        ++index;
    }
    return vRet;
}

/*@brief Get relative point from string taking account decimal separator and value separator*/
template<int VecSize>
inline static glm::vec<VecSize, double, glm::defaultp> getRelative(const std::string_view& a_toParse)
{
    return getVector<VecSize>(a_toParse.substr(1, a_toParse.size( ) - 1));
}

struct PolarCoord
{
    double m_angle;     /*!< polar angle*/
    double m_distance;  /*!< distance*/
};

/*@brief Get polar value*/
MCAD_FORMULA_EXPORT PolarCoord getPolar(const std::string_view& a_toParse);

/*@brief Get relative polar value*/
MCAD_FORMULA_EXPORT PolarCoord getRelativePolar(const std::string_view& a_toParse);


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