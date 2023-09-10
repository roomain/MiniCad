#pragma once
/***********************************************
* @headerfile MCadRef.h
* @date 06 / 09 / 2023
* @author Roomain
************************************************/
#include "MCadRefObject.h"

/*@brief only for internal uses*/

template<typename Type>
class MCadRef
{
    friend MCadRefObject<Type>;

    template<typename T>
    friend MCadRef<T> make_ref(const T&);

private:
    mutable MCadRef<Type>* m_prevRef = nullptr;
    mutable MCadRef<Type>* m_nextRef = nullptr;
    MCadRefObject<Type>* m_referenced = nullptr;

    void appendRef(MCadRef<Type>* const a_ref)const
    {
        MCadRef<Type>* pCurRef = const_cast< MCadRef<Type>* >( this );
        MCadRef<Type>* pLastRef = m_nextRef;
        while ( pLastRef )
        {
            pCurRef = pLastRef;
            pLastRef = pLastRef->m_nextRef;
        }
        pCurRef->m_nextRef = a_ref;
        a_ref->m_prevRef = pCurRef;
    }

    void unref( )
    {
        m_referenced = nullptr;
        MCadRef<Type>* pLastRef = m_nextRef;
        while ( pLastRef )
        {
            pLastRef->m_referenced = nullptr;
            pLastRef = pLastRef->m_nextRef;
        }
    }

    MCadRef(const Type& a_referenced) : m_referenced{ a_referenced.getRefPointer( ) }
    {
        if ( m_referenced->m_referenceList == nullptr )
        {
            m_referenced->m_referenceList = this;
        }
        else
        {
            m_referenced->m_referenceList->appendRef(this);
        }
    }

    MCadRef(Type* const a_referenced) : m_referenced{ a_referenced->getRefPointer( ) }
    {
        if ( m_referenced->m_referenceList == nullptr )
        {
            m_referenced->m_referenceList = this;
        }
        else
        {
            m_referenced->m_referenceList->appendRef(this);
        }
    }

public:
    MCadRef( ) = default;

    MCadRef(const MCadRef<Type>& a_other) : m_referenced{ a_other.m_referenced }
    {
        if ( m_referenced->m_referenceList == nullptr )
        {
            m_referenced->m_referenceList = this;
        }
        else
        {
            a_other.appendRef(this);
        }
    }

    ~MCadRef( )
    {
        if ( m_referenced )
        {
            if ( m_referenced->m_referenceList == this )
            {
                m_referenced->m_referenceList = m_nextRef;
            }
            else
            {
                m_prevRef->m_nextRef = m_nextRef;
            }
        }
    }

    Type* operator -> ()
    {
        return static_cast<Type*>(m_referenced);
    }

    [[nodiscard]] bool operator == (const MCadRef<Type>& a_other) const noexcept
    {
        return m_referenced == a_other.m_referenced;
    }

    MCadRef<Type> operator = (const MCadRef<Type>& a_other)
    {
        if ( m_referenced )
        {
            if ( m_referenced->m_referenceList == this )
            {
                m_referenced->m_referenceList = m_nextRef;
            }
            else
            {
                m_prevRef->m_nextRef = m_nextRef;
            }
        }

        m_referenced = a_other.m_referenced;
        if ( m_referenced->m_referenceList == nullptr )
        {
            m_referenced->m_referenceList = this;
        }
        else
        {
            a_other.appendRef(this);
        }
        return *this;
    }

    [[nodiscard]] size_t use_count( )const noexcept
    {
        size_t counter = 0;
        if ( m_referenced )
        {
            Reference<Type>* pLastRef = m_referenced->m_referenceList;
            while ( pLastRef )
            {
                counter++;
                pLastRef = pLastRef->m_nextRef;
            }
        }
        return counter;
    }

    [[nodiscard]] bool valid( )const noexcept
    {
        return m_referenced != nullptr;
    }

};

template<typename T>
MCadReference<T> make_ref(const T& a_object)
{
    return MCadReference<T>(a_object);
}