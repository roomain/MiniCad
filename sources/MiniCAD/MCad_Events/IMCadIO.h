#pragma once
/***********************************************
* @headerfile IMCadIO.h
* @date 20 / 12 / 2023
* @author Roomain
************************************************/
#include "TMCadIOOption.h"
#include "TMCadIOResult.h"
#include "FlagMacros.h"
#include "TMCadSelectionSet.h"
#include "glm/glm.hpp"

/*entry option flag*/
enum class MCadEntryOption
{
    Option_None = 0,
    Option_CancelOnNone = 1 << 0,
    Option_NoCancel = 1 << 1,
    // TODO
};

ENUM_FLAG_OPERATORS(MCadEntryOption)

/*@brief interface for comman IO*/
class IMCadIO
{
protected:
    enum class InternalStatus
    {
        status_OK,
        status_NOK,
        status_Keyword,
        status_NoValue,
        status_Cancel
    };
    std::string m_currentCommand;           /*!< currend command*/
    std::string m_currentTitle;             /*!< current entry title*/
    std::vector<std::string> m_keywords;    /*!< current available keywords*/
    MCadEntryOption m_currentOption;        /*!< entry options*/

    virtual InternalStatus getInternal_Int(std::optional<int>& a_retValue, std::string& a_entry) = 0;
    virtual InternalStatus getInternal_Double(std::optional<double>& a_retValue, std::string& a_entry) = 0;
    virtual InternalStatus getInternal_Distance(std::optional<double>& a_retValue, std::string& a_entry) = 0;
    virtual InternalStatus getInternal_Vec2d(std::optional<glm::dvec2>& a_retValue, std::string& a_entry) = 0;
    virtual InternalStatus getInternal_Vec3d(std::optional<glm::dvec3>& a_retValue, std::string& a_entry) = 0;
    virtual InternalStatus getInternal_Selection(std::optional<IMCadSelectionSet>& a_retValue, std::string& a_entry) = 0;
    
    void setup(const std::string& a_title, const IMCadIOOption& a_option, const MCadEntryOption a_entryOption)
    {
        m_currentTitle = a_title;
        m_currentOption = a_entryOption;
        a_option.getAutocompletionKeywords(m_keywords);
    }

public:
    template<typename KeywordType> requires( std::is_enum_v<KeywordType> )
    TMCadIOResult<int, KeywordType> getInt(const std::string& a_title, const TMCadIOOption<int, KeywordType>& a_option, const MCadEntryOption a_entryOption)
    {
        TMCadIOResult<int, KeywordType> result;
        setup(a_title, a_option, a_entryOption);
        bool bActionFinished = false;
        std::string entry;
        while ( !bActionFinished )
        {
            switch ( getInternal_Int(result.m_retType, entry) )
            {
            case InternalStatus::status_OK:
                result.m_status = ResultStatus::status_OK;
                bActionFinished = true;
                break;

            case InternalStatus::status_NOK:
                break;

            case InternalStatus::status_Keyword:
            {
                KeywordType keyw;
                if ( keywordValue(entry, keyw) )
                {
                    result.m_keyword = keyw;
                    result.m_status = ResultStatus::status_OK;
                    bActionFinished = true;
                }
            }
            break;

            case InternalStatus::status_NoValue:
                if ( a_option.defaultValue( ).has_value( ) )
                {
                    result.m_status = ResultStatus::status_OK;
                    result.m_retType = a_option.defaultValue( ).value( );
                    bActionFinished = true;
                }
                else if ( ( MCadEntryOption::Option_CancelOnNone & a_entryOption ) == MCadEntryOption::Option_CancelOnNone )
                {
                    result.m_status = ResultStatus::status_Ignore;
                    bActionFinished = true;
                }
                break;

            case InternalStatus::status_Cancel:
                if ( ( MCadEntryOption::Option_NoCancel & a_entryOption ) != MCadEntryOption::Option_NoCancel )
                {
                    result.m_status = ResultStatus::status_Cancel;
                    bActionFinished = true;
                }
                break;

            default:
                break;
            }
        }
        return result;
    }
    
    template<typename KeywordType> requires( std::is_enum_v<KeywordType> )
    TMCadIOResult<double, KeywordType> getDouble(const std::string& a_title, const TMCadIOOption<double, KeywordType>& a_option, const MCadEntryOption a_entryOption)
    {
        TMCadIOResult<int, KeywordType> result;
        setup(a_title, a_option, a_entryOption);
        bool bActionFinished = false;
        std::string entry;
        while ( !bActionFinished )
        {
            switch ( getInternal_Double(result.m_retType, entry) )
            {
            case InternalStatus::status_OK:
                result.m_status = ResultStatus::status_OK;
                bActionFinished = true;
                break;

            case InternalStatus::status_NOK:
                break;

            case InternalStatus::status_Keyword:
            {
                KeywordType keyw;
                if ( keywordValue(entry, keyw) )
                {
                    result.m_keyword = keyw;
                    result.m_status = ResultStatus::status_OK;
                    bActionFinished = true;
                }
            }
            break;

            case InternalStatus::status_NoValue:
                if ( a_option.defaultValue( ).has_value( ) )
                {
                    result.m_status = ResultStatus::status_OK;
                    result.m_retType = a_option.defaultValue( ).value( );
                    bActionFinished = true;
                }
                else if ( ( MCadEntryOption::Option_CancelOnNone & a_entryOption ) == MCadEntryOption::Option_CancelOnNone )
                {
                    result.m_status = ResultStatus::status_Ignore;
                    bActionFinished = true;
                }
                break;

            case InternalStatus::status_Cancel:
                if ( ( MCadEntryOption::Option_NoCancel & a_entryOption ) != MCadEntryOption::Option_NoCancel )
                {
                    result.m_status = ResultStatus::status_Cancel;
                    bActionFinished = true;
                }
                break;

            default:
                break;
            }
        }
        return result;
    }

    template<typename KeywordType> requires( std::is_enum_v<KeywordType> )
    TMCadIOResult<glm::dvec3, KeywordType> getVec2(const std::string& a_title, const TMCadIOOption<glm::dvec2, KeywordType>& a_option, const MCadEntryOption a_entryOption)
    {
        TMCadIOResult<int, KeywordType> result;
        setup(a_title, a_option, a_entryOption);
        bool bActionFinished = false;
        std::string entry;
        while ( !bActionFinished )
        {
            switch ( getInternal_Vec2d(result.m_retType, entry) )
            {
            case InternalStatus::status_OK:
                result.m_status = ResultStatus::status_OK;
                bActionFinished = true;
                break;

            case InternalStatus::status_NOK:
                break;

            case InternalStatus::status_Keyword:
            {
                KeywordType keyw;
                if ( keywordValue(entry, keyw) )
                {
                    result.m_keyword = keyw;
                    result.m_status = ResultStatus::status_OK;
                    bActionFinished = true;
                }
            }
            break;

            case InternalStatus::status_NoValue:
                if ( a_option.defaultValue( ).has_value( ) )
                {
                    result.m_status = ResultStatus::status_OK;
                    result.m_retType = a_option.defaultValue( ).value( );
                    bActionFinished = true;
                }
                else if ( ( MCadEntryOption::Option_CancelOnNone & a_entryOption ) == MCadEntryOption::Option_CancelOnNone )
                {
                    result.m_status = ResultStatus::status_Ignore;
                    bActionFinished = true;
                }
                break;

            case InternalStatus::status_Cancel:
                if ( ( MCadEntryOption::Option_NoCancel & a_entryOption ) != MCadEntryOption::Option_NoCancel )
                {
                    result.m_status = ResultStatus::status_Cancel;
                    bActionFinished = true;
                }
                break;

            default:
                break;
            }
        }
        return result;
    }

    template<typename KeywordType> requires( std::is_enum_v<KeywordType> )
    TMCadIOResult<glm::dvec3, KeywordType> getVec3(const std::string& a_title, const TMCadIOOption<glm::dvec3, KeywordType>& a_option, const MCadEntryOption a_entryOption)
    {
        TMCadIOResult<int, KeywordType> result;
        setup(a_title, a_option, a_entryOption);
        bool bActionFinished = false;
        std::string entry;
        while ( !bActionFinished )
        {
            switch ( getInternal_Vec2d(result.m_retType, entry) )
            {
            case InternalStatus::status_OK:
                result.m_status = ResultStatus::status_OK;
                bActionFinished = true;
                break;

            case InternalStatus::status_NOK:
                break;

            case InternalStatus::status_Keyword:
            {
                KeywordType keyw;
                if ( keywordValue(entry, keyw) )
                {
                    result.m_keyword = keyw;
                    result.m_status = ResultStatus::status_OK;
                    bActionFinished = true;
                }
            }
            break;

            case InternalStatus::status_NoValue:
                if ( a_option.defaultValue( ).has_value( ) )
                {
                    result.m_status = ResultStatus::status_OK;
                    result.m_retType = a_option.defaultValue( ).value( );
                    bActionFinished = true;
                }
                else if ( ( MCadEntryOption::Option_CancelOnNone & a_entryOption ) == MCadEntryOption::Option_CancelOnNone )
                {
                    result.m_status = ResultStatus::status_Ignore;
                    bActionFinished = true;
                }
                break;

            case InternalStatus::status_Cancel:
                if ( ( MCadEntryOption::Option_NoCancel & a_entryOption ) != MCadEntryOption::Option_NoCancel )
                {
                    result.m_status = ResultStatus::status_Cancel;
                    bActionFinished = true;
                }
                break;

            default:
                break;
            }
        }
        return result;
    }

    template<typename KeywordType> requires( std::is_enum_v<KeywordType> )
    TMCadIOResult<double, KeywordType> getDistance(const std::string& a_title, const TMCadIOOption<double, KeywordType>& a_option, const MCadEntryOption a_entryOption)
    {
        TMCadIOResult<int, KeywordType> result;
        setup(a_title, a_option, a_entryOption);
        bool bActionFinished = false;
        std::string entry;
        while ( !bActionFinished )
        {
            switch ( getInternal_Distance(result.m_retType, entry) )
            {
            case InternalStatus::status_OK:
                result.m_status = ResultStatus::status_OK;
                bActionFinished = true;
                break;

            case InternalStatus::status_NOK:
                break;

            case InternalStatus::status_Keyword:
            {
                KeywordType keyw;
                if ( keywordValue(entry, keyw) )
                {
                    result.m_keyword = keyw;
                    result.m_status = ResultStatus::status_OK;
                    bActionFinished = true;
                }
            }
            break;

            case InternalStatus::status_NoValue:
                if ( a_option.defaultValue( ).has_value( ) )
                {
                    result.m_status = ResultStatus::status_OK;
                    result.m_retType = a_option.defaultValue( ).value( );
                    bActionFinished = true;
                }
                else if ( ( MCadEntryOption::Option_CancelOnNone & a_entryOption ) == MCadEntryOption::Option_CancelOnNone )
                {
                    result.m_status = ResultStatus::status_Ignore;
                    bActionFinished = true;
                }
                break;

            case InternalStatus::status_Cancel:
                if ( ( MCadEntryOption::Option_NoCancel & a_entryOption ) != MCadEntryOption::Option_NoCancel )
                {
                    result.m_status = ResultStatus::status_Cancel;
                    bActionFinished = true;
                }
                break;

            default:
                break;
            }
        }
        return result;
    }

    template<typename Type, typename KeywordType> requires( std::is_enum_v<KeywordType> )
    TMCadIOResult<TMCadSelectionSet<Type>, KeywordType> getSelection(const std::string& a_title, const TMCadIOOption<TMCadSelectionSet<Type>, KeywordType>& a_option, const MCadEntryOption a_entryOption)
    {
        TMCadIOResult<int, KeywordType> result;
        setup(a_title, a_option, a_entryOption);
        bool bActionFinished = false;
        std::string entry;
        while ( !bActionFinished )
        {
            switch ( getInternal_Selection(result.m_retType, entry) )
            {
            case InternalStatus::status_OK:
                result.m_status = ResultStatus::status_OK;
                bActionFinished = true;
                break;

            case InternalStatus::status_NOK:
                break;

            case InternalStatus::status_Keyword:
            {
                KeywordType keyw;
                if ( keywordValue(entry, keyw) )
                {
                    result.m_keyword = keyw;
                    result.m_status = ResultStatus::status_OK;
                    bActionFinished = true;
                }
            }
            break;

            case InternalStatus::status_NoValue:
                if ( a_option.defaultValue( ).has_value( ) )
                {
                    result.m_status = ResultStatus::status_OK;
                    result.m_retType = a_option.defaultValue( ).value( );
                    bActionFinished = true;
                }
                else if ( ( MCadEntryOption::Option_CancelOnNone & a_entryOption ) == MCadEntryOption::Option_CancelOnNone )
                {
                    result.m_status = ResultStatus::status_Ignore;
                    bActionFinished = true;
                }
                break;

            case InternalStatus::status_Cancel:
                if ( ( MCadEntryOption::Option_NoCancel & a_entryOption ) != MCadEntryOption::Option_NoCancel )
                {
                    result.m_status = ResultStatus::status_Cancel;
                    bActionFinished = true;
                }
                break;

            default:
                break;
            }
        }
        return result;
    }

};