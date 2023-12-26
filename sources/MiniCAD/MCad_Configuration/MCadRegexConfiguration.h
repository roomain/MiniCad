#pragma once
/***********************************************
* @headerfile MCadRegexConfiguration.h
* @date 10 / 12 / 2023
* @author Roomain
************************************************/
#include <string>
#include <regex>
#include <vector>
#include <functional>
#include "glm/glm.hpp"
#include "MCadProperty.h"
#include "MCad_Configuration_globals.h"

#pragma warning(push)
#pragma warning(disable : 4251)
#pragma warning(disable : 4275)

/*@brief contains regular expressions for parsing*/
/*need to be exported due to link error on MCadValidProperty<char, &MCadRegexConfiguration::valid>*/
class MCAD_CONFIGURATION_EXPORT MCadRegexConfiguration
{
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
private:
    static constexpr char PolarSeparator = '<';

    static bool valid(const char& a_separator);
    void updateRegex(const char& a_separator);

public:
    MCadRegexConfiguration( );
    virtual ~MCadRegexConfiguration( ) = default;

    MCadProperty<std::regex, true, MCadRegexConfiguration> DOT_PROD_REGEX{ "DOT_PROD_REGEX", std::regex{ "^<dot>" } };                      /*!< dot prod operator regex*/
    MCadProperty<std::regex, true, MCadRegexConfiguration> CROSS_PROD_REGEX{ "CROSS_PROD_REGEX", std::regex{ "^<cross>" } };                /*!< cross prod operator regex*/
    MCadProperty<std::regex, true, MCadRegexConfiguration> INT_REGEX{ "INT_REGEX", std::regex{ "^-?([1-9]+[0-9]*)|0" } };                   /*!< int regex*/
    MCadProperty<std::regex, true, MCadRegexConfiguration> VAR_REGEX{ "VAR_REGEX", std::regex{ "^\\$\\{[a-zA-Z]+(_ | [a-zA-Z])*\\}" } };    /*!< variable name regex*/


    // trigo regex and functions
    MCadProperty<std::regex, true, MCadRegexConfiguration> COS_REGEX{ "COS_REGEX", std::regex{ R"(cos\()" } };                              /*!<cos regex*/
    MCadProperty<std::regex, true, MCadRegexConfiguration> SIN_REGEX{ "SIN_REGEX", std::regex{ R"(sin\()" } };                              /*!<sin regex*/
    MCadProperty<std::regex, true, MCadRegexConfiguration> TAN_REGEX{ "TAN_REGEX", std::regex{ R"(tan\()" } };                              /*!<tan regex*/
    MCadProperty<std::regex, true, MCadRegexConfiguration> ACOS_REGEX{ "ACOS_REGEX", std::regex{ R"(acos\()" } };                           /*!<acos regex*/
    MCadProperty<std::regex, true, MCadRegexConfiguration> ASIN_REGEX{ "ASIN_REGEX", std::regex{ R"(asin\()" } };                           /*!<asin regex*/
    MCadProperty<std::regex, true, MCadRegexConfiguration> ATAN_REGEX{ "ATAN_REGEX", std::regex{ R"(atan\()" } };                           /*!<atan regex*/
    MCadProperty<std::regex, true, MCadRegexConfiguration> FUN_REGEX{ "FUN_REGEX", std::regex{ R"([a-zA-Z]+(_ | [a-zA-Z])*\()" } };         /*!<function regex*/

    MCadProperty<std::regex, true, MCadRegexConfiguration> DOUBLE_REGEX{ "DOUBLE_REGEX", std::regex{ "^$" } };      /*!< double regex*/

    MCadProperty<std::regex, true, MCadRegexConfiguration> VEC2_REGEX{ "VEC2_REGEX", std::regex{ "^$" } };          /*!< vector 2d regex*/
    MCadProperty<std::regex, true, MCadRegexConfiguration> VEC3_REGEX{ "VEC3_REGEX", std::regex{ "^$" } };          /*!< vector 3d regex*/
    MCadProperty<std::regex, true, MCadRegexConfiguration> VEC4_REGEX{ "VEC4_REGEX", std::regex{ "^$" } };          /*!< vector 4d regex*/
    MCadProperty<std::regex, true, MCadRegexConfiguration> PT2_REGEX{ "PT2_REGEX", std::regex{ "^$" } };            /*!< point 2d regex*/
    MCadProperty<std::regex, true, MCadRegexConfiguration> PT3_REGEX{ "PT3_REGEX", std::regex{ "^$" } };            /*!< point 3d regex*/

    MCadProperty<std::regex, true, MCadRegexConfiguration> POLAR_COORD_REGEX{ "POLAR_COORD_REGEX", std::regex{ "^$" } };                 /*!< polar coord regex*/
    MCadProperty<std::regex, true, MCadRegexConfiguration> REL_3D_CARTESIAN_REGEX{ "REL_3D_CARTESIAN_REGEX", std::regex{ "^$" } };      /*!< relative cartesian 3d regex*/
    MCadProperty<std::regex, true, MCadRegexConfiguration> REL_2D_CARTESIAN_REGEX{ "REL_2D_CARTESIAN_REGEX", std::regex{ "^$" } };      /*!< relative cartesian 2d regex*/
    MCadProperty<std::regex, true, MCadRegexConfiguration> REL_POLAR_REGEX{ "REL_POLAR_REGEX", std::regex{ "^$" } };                    /*!< relative polar regex*/
    MCadProperty<char, true> POLAR_SEPARATOR{ "POLAR_SEPARATOR", '<' };
    MCadProperty<char, true, MCadRegexConfiguration> VALUE_SEPARATOR{ "VALUE_SEPARATOR", ',' };
    MCadValidProperty<char, &MCadRegexConfiguration::valid> DECIMAL_SEPARATOR{ "DECIMAL_SEPARATOR", '.' };
};
#pragma warning(pop)