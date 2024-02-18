#pragma once
/***********************************************
* @headerfile MCadRef.h
* @date 06 / 09 / 2023
* @author Roomain
************************************************/
#include <type_traits>


class MCadRefObject;

template<typename Type>  requires std::is_base_of_v<MCadRefObject, Type>
class MCadRef;

/*@brief interface of reference*/
/*@brief IMCadRef is used as a double linked list*/
class IMCadRef
{
    friend class MCadRefObject;

    template<typename Type>  requires std::is_base_of_v<MCadRefObject, Type>
    friend class MCadRef;

private:
    mutable IMCadRef* m_prevRef = nullptr;	/*!< previous reference*/
    mutable IMCadRef* m_nextRef = nullptr;	/*!< next reference*/

protected:
    /*@brief release reference*/
    virtual void releaseRef( ) = 0;

    [[nodiscard]] inline IMCadRef* const prev( )const { return m_prevRef; }
    [[nodiscard]] inline IMCadRef* const next( )const { return m_nextRef; }

    virtual void updateRefPointer(MCadRefObject* const) = 0;

    virtual void updateRef(MCadRefObject* const a_pRef)
    {
        updateRefPointer(a_pRef);
        m_nextRef->updateRef(a_pRef);
    }

    /*@brief remove from list*/
    void selfRemove( )const
    {
        if ( m_prevRef )
        {
            m_prevRef->m_nextRef = m_nextRef;
            if ( m_nextRef )
                m_nextRef->m_prevRef = m_prevRef;
        }
    }

    void insertToRef(IMCadRef* const a_ref)const
    {
        m_nextRef = a_ref;
        m_prevRef = a_ref->m_prevRef;
        a_ref->m_prevRef = const_cast< IMCadRef* >( this );
    }

    /*@brief append reference*/
    void appendRef(IMCadRef* const a_ref)const
    {
        IMCadRef* pCurRef = const_cast< IMCadRef* >( this );
        IMCadRef* pLastRef = m_nextRef;
        while ( pLastRef )
        {
            pCurRef = pLastRef;
            pLastRef = pLastRef->m_nextRef;
        }
        pCurRef->m_nextRef = a_ref;
        a_ref->m_prevRef = pCurRef;
    }

    /*@brief referenced object will be deleted*/
    void unref( )
    {
        releaseRef( );
        IMCadRef* pLastRef = m_nextRef;
        while ( pLastRef )
        {
            pLastRef->releaseRef( );
            pLastRef = pLastRef->m_nextRef;
        }
    }

public:
    IMCadRef( ) = default;
    virtual ~IMCadRef( ) = default;
};


template<typename Type>  requires std::is_base_of_v<MCadRefObject, Type>
class MCadRef : public IMCadRef
{
    template<typename T> requires std::is_base_of_v<MCadRefObject, T>
    friend MCadRef<T> make_ref(const T&);

private:
    Type* m_RefObject = nullptr;

protected:
    void updateRefPointer(MCadRefObject* const a_pRef) final
    {
        m_RefObject = static_cast< Type* >( a_pRef );
    }

    void releaseRef( ) final
    {
        m_RefObject = nullptr;
    }

    explicit MCadRef(const Type& a_referenced) : m_RefObject{ const_cast<Type*>( &a_referenced ) }
    {
        if ( m_RefObject->m_referenceList == nullptr )
        {
            m_RefObject->m_referenceList = this;
        }
        else
        {
            static_cast<IMCadRef*>(m_RefObject->m_referenceList)->appendRef(this);
        }
    }

    explicit MCadRef(Type* const a_referenced) : m_RefObject{ a_referenced }
    {
        if ( m_RefObject->m_referenceList == nullptr )
        {
            m_RefObject->m_referenceList = this;
        }
        else
        {
            m_RefObject->m_referenceList->appendRef(this);
        }
    }

public:
    MCadRef( ) = default;

    explicit MCadRef(const MCadRef<Type>& a_other) : m_RefObject{ a_other.m_RefObject }
    {
        if ( m_RefObject )
        {
            if ( m_RefObject->m_referenceList == nullptr )
            {
                m_RefObject->m_referenceList = this;
            }
            else
            {
                a_other.appendRef(this);
            }
        }
    }

    /*explicit ctor here cause a compilation error*/
    MCadRef(MCadRef<Type>&& a_other)noexcept : m_RefObject{ a_other.m_RefObject }
    {
        if ( m_RefObject )
        {
            if ( m_RefObject->m_referenceList == nullptr )
            {
                m_RefObject->m_referenceList = this;
            }
            else
            {
                a_other.appendRef(this);
            }
        }
    }

    ~MCadRef( )override
    {
        if ( m_RefObject )
        {
            if ( m_RefObject->m_referenceList == this )
            {
                m_RefObject->m_referenceList = next();
            }
            else
            {
                selfRemove( );
            }
        }
    }

    Type* operator -> ()
    {
        return static_cast<Type*>(m_RefObject);
    }

    [[nodiscard]] Type* const pointer( )const
    {
        return static_cast< Type* >( m_RefObject );
    }

    [[nodiscard]] bool operator == (const MCadRef<Type>& a_other) const noexcept
    {
        return m_RefObject == a_other.m_RefObject;
    }

    MCadRef<Type>& operator = (const MCadRef<Type>& a_other)
    {
        if ( m_RefObject == a_other.m_RefObject )
            return *this;

        if ( m_RefObject )
        {
            if ( m_RefObject->m_referenceList == this )
            {
                m_RefObject->m_referenceList = m_nextRef;
            }
            else
            {
                selfRemove();
            }
        }

        m_RefObject = a_other.m_RefObject;
        if ( m_RefObject )
        {
            if ( m_RefObject->m_referenceList == nullptr )
            {
                m_RefObject->m_referenceList = this;
            }
            else
            {
                a_other.appendRef(this);
            }
        }
        return *this;
    }

    MCadRef<Type>& operator = (MCadRef<Type>&& a_other)noexcept
    {
        if ( m_RefObject == a_other.m_RefObject )
            return *this;

        if ( m_RefObject )
        {
            if ( m_RefObject->m_referenceList == this )
            {
                m_RefObject->m_referenceList = m_nextRef;
            }
            else
            {
                selfRemove( );
            }
        }

        m_RefObject = a_other.m_RefObject;
        if ( m_RefObject )
        {
            if ( m_RefObject->m_referenceList == nullptr )
            {
                m_RefObject->m_referenceList = this;
            }
            else
            {
                a_other.appendRef(this);
            }
        }
        return *this;
    }

    [[nodiscard]] size_t use_count( )const noexcept
    {
        size_t counter = 0;
        if ( m_RefObject )
        {
            IMCadRef* pLastRef = m_RefObject->m_referenceList;
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
        return m_RefObject != nullptr;
    }

};

class MCadRefObject
{
    template<typename Type> requires std::is_base_of_v<MCadRefObject, Type>
    friend  class MCadRef;

private:
    mutable IMCadRef* m_referenceList = nullptr;

public:
    MCadRefObject( ) = default;

    MCadRefObject(const MCadRefObject& a_other)
    {
       // nothing todo
    }

    MCadRefObject(MCadRefObject&& a_other)noexcept
    {
        m_referenceList = a_other.m_referenceList;
        if ( m_referenceList )
            m_referenceList->updateRef(this);
    }

    virtual ~MCadRefObject( )
    {
        if ( m_referenceList )
            m_referenceList->unref( );
    }

    inline void operator = (MCadRefObject& a_other)
    {
        // nothing to do but function must be declared to enable std::swap
    }

    inline void operator = (MCadRefObject&& a_other)noexcept
    {
        m_referenceList = a_other.m_referenceList;
        if ( m_referenceList )
            m_referenceList->updateRef(this);
    }
};

template<typename T> requires std::is_base_of_v<MCadRefObject, T>
MCadRef<T> make_ref(const T& a_object)
{
    return MCadRef<T>(a_object);
}