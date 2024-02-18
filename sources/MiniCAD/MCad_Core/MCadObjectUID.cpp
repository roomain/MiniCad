#include "pch.h"
#include "MCadObjectUID.h"

MCadObjectUID::MCadObjectUID(const MCadObject* a_pObject, const unsigned long long& a_uid)noexcept : m_uniqueId{ a_uid }
{
    if ( a_pObject )
        m_object = a_pObject->weak_from_this( );
}