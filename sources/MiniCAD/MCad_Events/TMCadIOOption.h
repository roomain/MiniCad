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

enum class EmptyEnum {};

class IMCadIOOption
{
public:
    virtual bool isKeyword(const std::string& a_toCheck) = 0;
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

    int keywordIndex(const std::string& a_toCheck)
    {
        int iRet = -1;

        for ( auto&& def : m_keywordSet )
        {
            ++iRet;
            if ( compare(def.m_globalName, a_toCheck) )
                return iRet;
            if ( compare(def.m_globalShortName, a_toCheck) )
                return iRet;
            if ( compare(def.m_localName, a_toCheck) )
                return iRet;
            if ( compare(def.m_localShortName, a_toCheck) )
                return iRet;
        }
        return -1;
    }

public:
    TMCadIOOption( ) = default;
    virtual ~TMCadIOOption( ) = default;
    std::optional<DefaultType> defaultValue( )const noexcept { return m_defaultValue; }
    bool isKeyword(const std::string_view a_toCheck)final
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


