#pragma once
/***********************************************
* @headerfile MCadReference.h
* @date 06 / 09 / 2023
* @author Roomain
************************************************/
#include "MCadReferencedObject.h"

/*@brief only for internal uses*/

template<typename Type>
class MCadReference
{
    friend MCadReferencedObject<Type>;

    template<typename T>
    friend MCadReference<T> make_ref(const T&);

private:
    mutable MCadReference<Type>* m_prevRef = nullptr;
    mutable MCadReference<Type>* m_nextRef = nullptr;
    MCadReferencedObject<Type>* m_referenced = nullptr;

    void appendRef(Reference<Type>* const a_ref)const
    {
        Reference<Type>* pCurRef = const_cast< Reference<Type>* >( this );
        Reference<Type>* pLastRef = m_nextRef;
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
        Reference<Type>* pLastRef = m_nextRef;
        while ( pLastRef )
        {
            pLastRef->m_referenced = nullptr;
            pLastRef = pLastRef->m_nextRef;
        }
    }

    MCadReference(const Type& a_referenced) : m_referenced{ a_referenced.getRefPointer( ) }
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

    MCadReference(Type* const a_referenced) : m_referenced{ a_referenced->getRefPointer( ) }
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
    MCadReference( ) = default;

    MCadReference(const MCadReference<Type>& a_other) : m_referenced{ a_other.m_referenced }
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

    ~MCadReference( )
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

    [[nodiscard]] bool operator == (const MCadReference<Type>& a_other) const noexcept
    {
        return m_referenced == a_other.m_referenced;
    }

    MCadReference<Type> operator = (const MCadReference<Type>& a_other)
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