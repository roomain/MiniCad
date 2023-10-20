#include "MCadFormulaRegEx.h"

/*@brief Get polar value*/
PolarCoord getPolar(const std::string_view& a_toParse, const char a_decimalSeparator)
{
    std::vector<std::string> vdata;
    split(a_toParse, MCadFormulaRegEx::PolarSeparator, vdata);
    return PolarCoord{ getDouble(vdata [ 0 ], a_decimalSeparator), getDouble(vdata [ 1 ], a_decimalSeparator) };
}

/*@brief Get relative polar value*/
PolarCoord getRelativePolar(const std::string_view& a_toParse, const char a_decimalSeparator)
{
    return getPolar(a_toParse.substr(1, a_toParse.size( ) - 1), a_decimalSeparator);
}

bool parseAndReact(const std::string& a_toParse, const VRegExReactor& a_vReactor)
{
    bool bRet = false;
    for ( auto&& regReac : a_vReactor )
    {
        if (std::regex_match(a_toParse, regReac.m_regularExp))
        {
            regReac.m_reaction(a_toParse);
            break;
        }
    }
    return bRet;
}