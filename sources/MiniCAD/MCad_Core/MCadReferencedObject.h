#pragma once
/***********************************************
* @headerfile MCadReferencedObject.h
* @date 07 / 09 / 2023
* @author Roomain
************************************************/

template<typename Type>
class MCadReference;

/*referenced object*/
template<typename Type>
class MCadReferencedObject
{
    friend  MCadReference<Type>;

private:
    mutable MCadReference<Type>* m_referenceList = nullptr;

    MCadReference<Type>* const getRefPointer( ) const
    {
        return const_cast< MCadReference<Type>*const >( this );
    }
public:
    MCadReferencedObject( ) = default;

    ~MCadReferencedObject( )
    {
        if ( m_referenceList )
            m_referenceList->unref( );
    }

};