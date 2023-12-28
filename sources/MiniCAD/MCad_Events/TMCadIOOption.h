#pragma once
/***********************************************
* @headerfile MCadIOOption.h
* @date 20 / 12 / 2023
* @author Roomain
************************************************/
#include <optional>
#include <string>
#include <exception>
#include <functional>
#include <vector>
#include "MCadStringTools.h"

enum class EmptyEnum {};

class IMCadIOOption
{
public:
    virtual ~IMCadIOOption( ) = default;
    virtual bool isKeyword(const std::string& a_toCheck)const = 0;
    virtual  void getAutocompletionKeywords(const std::vector<std::string>& a_autoCompete)const = 0;
};

template<typename EnumType>
struct KeyworldDef
{
    EnumType m_enumValue;               /*!< corresponding enum value*/
    std::string m_globalName;           /*!< keyworld global name*/
    std::string m_globalShortName;      /*!< keyworld global short name*/
    std::string m_localName;            /*!< keyworld local name*/
    std::string m_localShortName;       /*!< keyworld local short name*/
};

template<typename EnumType>
using KeywordSet = std::vector<KeyworldDef<EnumType>>;

/*@brief generic option for IO*/
template<typename DefaultType, typename EnumKeyword = EmptyEnum>
class TMCadIOOption : public IMCadIOOption
{
private:
    std::optional<DefaultType> m_defaultValue;  /*!< optional default value*/
    KeywordSet<EnumKeyword> m_keywordSet;       /*!< optional keywords*/

    constexpr int keywordIndex(const std::string& a_toCheck)const
    {
        int iRet = 0;

        for ( auto&& def : m_keywordSet )
        {
            if ( equivalent(def.m_globalName, a_toCheck) ||
                equivalent(def.m_globalShortName, a_toCheck) ||
                equivalent(def.m_localName, a_toCheck) ||
                equivalent(def.m_localShortName, a_toCheck) )
                return iRet;
            ++iRet;
        }
        return -1;
    }

public:
    TMCadIOOption( ) = default;
    virtual ~TMCadIOOption( )override = default;
    std::optional<DefaultType> defaultValue( )const noexcept { return m_defaultValue; }
    bool isKeyword(const std::string_view a_toCheck)const final
    {
        return keywordIndex(a_toCheck) > -1;
    }

    bool keywordValue(const std::string_view a_toCheck, EnumKeyword& a_value)
    {
        int index = keywordIndex(a_toCheck);
        if ( index > -1 )
        {
            a_value = m_keywordSet [ index ].m_enumValue;
            return true;
        }
        return false;
    }

    void getAutocompletionKeywords(const std::vector<std::string>& a_autoCompete)const final
    {
        for ( auto&& def : m_keywordSet )
        {
            a_autoCompete.emplace_back(def.m_globalName);
            a_autoCompete.emplace_back(def.m_globalShortName);
            a_autoCompete.emplace_back(def.m_localName);
            a_autoCompete.emplace_back(def.m_localShortName);
        }
    }

    TMCadIOOption<DefaultType, EnumKeyword>& setDefault(const DefaultType& a_default)
    {
        m_defaultValue = a_default;
        return *this;
    }

    TMCadIOOption<DefaultType, EnumKeyword>& resetDefault( )
    {
        m_defaultValue.reset( );
        return *this;
    }

    TMCadIOOption<DefaultType, EnumKeyword>& setKeywords(const KeywordSet<EnumKeyword>& a_keywords)
    {
        m_keywordSet.clear( );
        m_keywordSet = a_keywords;
        return *this;
    }

    TMCadIOOption<DefaultType, EnumKeyword>& resetKeywords( )
    {
        m_keywordSet.clear( );
        return *this;
    }
};


/*@brief generic option for IO*/
template<typename EnumKeyword>  requires( std::is_enum_v<EnumKeyword> )
class TMCadIOKeywordOption : public IMCadIOOption
{
private:
    std::optional<EnumKeyword> m_defaultValue;  /*!< optional default value*/
    KeywordSet<EnumKeyword> m_keywordSet;       /*!< optional keywords*/

    constexpr int keywordIndex(const std::string& a_toCheck)const
    {
        int iRet = 0;

        for ( auto&& def : m_keywordSet )
        {
            if ( equivalent(def.m_globalName, a_toCheck) ||
                equivalent(def.m_globalShortName, a_toCheck) ||
                equivalent(def.m_localName, a_toCheck) ||
                equivalent(def.m_localShortName, a_toCheck) )
                return iRet;
            ++iRet;
        }
        return -1;
    }

public:
    TMCadIOKeywordOption(const KeywordSet<EnumKeyword>& a_keywords)
    {
        m_keywordSet = a_keywords;
    }
    virtual ~TMCadIOKeywordOption( )override = default;
    std::optional<EnumKeyword> defaultValue( )const noexcept { return m_defaultValue; }
    bool isKeyword(const std::string_view a_toCheck)const final
    {
        return keywordIndex(a_toCheck) > -1;
    }

    bool keywordValue(const std::string_view a_toCheck, EnumKeyword& a_value)
    {
        int index = keywordIndex(a_toCheck);
        if ( index > -1 )
        {
            a_value = m_keywordSet [ index ].m_enumValue;
            return true;
        }
        return false;
    }

    void getAutocompletionKeywords(const std::vector<std::string>& a_autoCompete)const final
    {
        for ( auto&& def : m_keywordSet )
        {
            a_autoCompete.emplace_back(def.m_globalName);
            a_autoCompete.emplace_back(def.m_globalShortName);
            a_autoCompete.emplace_back(def.m_localName);
            a_autoCompete.emplace_back(def.m_localShortName);
        }
    }

    TMCadIOKeywordOption<EnumKeyword>& setDefault(const EnumKeyword& a_default)
    {
        m_defaultValue = a_default;
        return *this;
    }

    TMCadIOKeywordOption<EnumKeyword>& resetDefault( )
    {
        m_defaultValue.reset( );
        return *this;
    }

};
