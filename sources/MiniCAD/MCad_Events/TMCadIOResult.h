#pragma once
/***********************************************
* @headerfile TMCadIOResult.h
* @date 20 / 12 / 2023
* @author Roomain
************************************************/
#include <type_traits>
#include <optional>

enum class ResultStatus
{
    status_OK,
    status_Cancel,
    status_Ignore
};

/*@brief result of command IO*/
template<typename ReturnType, typename KeywordType> requires( std::is_enum_v<KeywordType> )
struct TMCadIOResult
{
    ResultStatus m_status = ResultStatus::status_Cancel;    /*!< result status*/
    std::optional<KeywordType> m_keyword;                   /*!< keyword value*/
    std::optional<ReturnType>  m_retType;                   /*!< return type*/
};
