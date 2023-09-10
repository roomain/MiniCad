#pragma once
/***********************************************
* @headerfile MCadRefObject.h
* @date 07 / 09 / 2023
* @author Roomain
************************************************/

template<typename Type>
class MCadRef;

/*referenced object*/
template<typename Type>
class MCadRefObject
{
    friend  MCadReference<Type>;

private:
    mutable MCadRef<Type>* m_referenceList = nullptr;

    MCadRefObject<Type>* const getRefPointer( ) const
    {
        return const_cast< MCadRefObject<Type>*const >( this );
    }
public:
    MCadRefObject() = default;

    MCadRefObject(MCadRefObject<Type>&& a_other)noexcept
    {
        m_referenceList = a_other.m_referenceList;
        if ( m_referenceList )
            m_referenceList->updateRef(this);
    }

    virtual ~MCadRefObject()
    {
        if ( m_referenceList )
            m_referenceList->unref( );
    }

    void operator = (Referenced<T>& a_other)
    {
        // nothing to do but function must be declared to enable std::swap
    }

    void operator = (Referenced<T>&& a_other)noexcept
    {
        m_referenceList = a_other.m_referenceList;
        if ( m_referenceList )
            m_referenceList->updateRef(this);
    }
};