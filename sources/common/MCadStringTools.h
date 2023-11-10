#pragma once
/***********************************************
* @headerfile MCadStringTools.h
* @date 15 / 10 / 2023
* @author Roomain
************************************************/
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

/*@brief Provides tools for parsing string*/
constexpr std::string left(const std::string_view& a_toParse ,const int a_iSize)
{
    return std::string(a_toParse.substr(a_iSize));
}

constexpr std::string right(const std::string_view& a_toParse ,const int a_iSize)
{
    return std::string(a_toParse.substr(0, a_iSize));
}


/*@brief functions wich extract data from parsed string*/
constexpr void ltrim(std::string &a_string) 
{
    a_string.erase(a_string.begin(), std::ranges::find_if(a_string.begin(), a_string.end(), [](unsigned char a_char) {
        return !std::isspace(a_char);
    }));
}

constexpr void rtrim(std::string &a_string) 
{
    a_string.erase(std::ranges::find_if(a_string.rbegin(), a_string.rend(), [](unsigned char a_char) {
        return !std::isspace(a_char);
    }).base(), a_string.end());
}

constexpr void trim(std::string &a_string)
 {
    ltrim(a_string);
    rtrim(a_string);
}

constexpr void split(const std::string_view& a_data, const char a_separator, std::vector<std::string>& a_vData)
{
    std::string::size_type prev_pos = 0, pos = 0;
    while((pos = a_data.find(a_separator, pos)) != std::string::npos)
    {
        a_vData.emplace_back(a_data.substr(prev_pos, pos - prev_pos));
        prev_pos = ++pos;
    }
    a_vData.emplace_back(a_data.substr(prev_pos, pos - prev_pos));
}

constexpr std::string toUpper(const std::string& a_data)
{
    std::string upperString;
    std::ranges::transform(a_data, std::back_inserter(upperString), [] (const char a_character){return toupper(a_character);});
    return upperString;
}