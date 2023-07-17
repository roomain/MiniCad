#pragma once
/***********************************************
* @headerfile ProtocolExtension.h
* @date 16 / 07 / 2023
* @author Roomain
************************************************/
#include "RTTIDefinition_macros.h"

/*@brief base class for protocole extension*/
class ProtocolExtension
{
    DECLARE_RTTI(1, ProtocolExtension)
public:
    ProtocolExtension() = default;
    virtual ~ProtocolExtension() = default;
};