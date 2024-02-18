#pragma once
/***********************************************
* @headerfile MCadObjectID.h
* @date 03 / 02 / 2024
* @author Roomain
************************************************/
#include <memory>
#include "MCadMemory.h"
#include "MCad_Core_globals.h"
#include "MCadObject.h"

class MCAD_CORE_EXPORT MCadObjectUID
{
    friend class MCadObject;
    friend class MCadReallocMemory;

private:
    unsigned long long m_uniqueId;
    std::weak_ptr<MCadObject> m_object;

    MCadObjectUID(const MCadObject* a_pObject, const unsigned long long& a_uid)noexcept;

public:
    MCadObjectUID( ) = delete;

    inline [[nodiscard]] unsigned long long uniqueIdentifier( )const noexcept { return m_uniqueId; }

    inline [[nodiscard]] bool isValid( )const noexcept { return !m_object.expired( ); }

    inline bool operator < (const MCadObjectUID& a_other)const
    {
        return m_uniqueId < a_other.m_uniqueId;
    }

    inline bool operator < (MCadObjectUID&& a_other)const noexcept
    {
        return m_uniqueId < a_other.m_uniqueId;
    }

    inline bool operator > (const MCadObjectUID& a_other)const
    {
        return m_uniqueId > a_other.m_uniqueId;
    }

    inline bool operator > (MCadObjectUID&& a_other)const noexcept
    {
        return m_uniqueId > a_other.m_uniqueId;
    }

    inline [[nodiscard]] bool operator == (const MCadObjectUID& a_other)const
    {
        return m_uniqueId == a_other.m_uniqueId;
    }

    inline [[nodiscard]] bool operator == (const unsigned long long& a_uid)const
    {
        return m_uniqueId == a_uid;
    }

    template<typename Type>
    MCadShared_ptr<Type> open( )const
    {
        auto pObject = m_object.lock( );
        if ( pObject )
            return pObject->cast<Type>();
        return nullptr;
    }
};
