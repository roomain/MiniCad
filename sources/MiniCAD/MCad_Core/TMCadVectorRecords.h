#pragma once
/***********************************************
* @headerfile TMCadVectorRecords.h
* @date 28 / 01 / 2024
* @author Roomain
************************************************/
#include "IMCadRecord.h"
#include "MCadLogger.h"
#include "MCadObjectUID.h"
#include "TMCadVector.h"

template<typename ContainedType>
class TMCadVectorInsert : public IMCadRecord
{
private:
    MCadRef<TMCadVector<ContainedType>> m_container;
    std::weak_ptr<RTTIDefinition> m_objectDef;
    size_t m_index = -1;                                /*!< index of object*/
    size_t m_dataOffset = 0;                            /*!< data redo offset of record*/
    MCadObjectUID m_recorded;                           /*!< recorded object*/

    template<typename Type>
    static void open(MCadShared_ptr<Type>& a_pointer, MCadObjectUID& a_objUid)
    {
        a_pointer = a_objUid.open<Type>( );
    }

protected:
    void prepareRedo(MCadReallocMemory& a_realocMem, IMCadOutputStream& a_stream) override
    {
        m_dataOffset = a_stream.offset( );
        m_recorded.open<MCadObject>( )->save(a_stream);
    }

    void do_undo(IMCadInputStream& a_stream, MCadReallocMemory& a_realocMem) override
    {
        if ( m_container.valid( ) )
        {
            m_container->erase(m_container->begin( ) + m_index);
        }
        else
        {
            MCadLogger::Instance( ) << LogMode::LOG_WARNING << "Can't undo/redo";
        }
    }

    void do_redo(IMCadInputStream& a_stream, MCadReallocMemory& a_realocMem) override
    {
        if ( m_container.valid( ) )
        {
            auto pObject = a_realocMem.realloc(m_recorded, m_pObjectDef);
            if ( pObject )
            {
                m_recorded = pObject->objectUID( );
                a_stream.setPos(a_offset);
                pObject->load(a_stream);
            }
            m_container->insert(m_container->begin( ) + m_index);
        }
        else
        {
            MCadLogger::Instance( ) << LogMode::LOG_WARNING << "Can't undo/redo";
        }
    }

public:
    TMCadVectorInsert( ) = delete;
    TMCadVectorInsert(const MCadRef<MCadVector<Type>>& a_vRef, const size_t& a_index, const MCadObjectUID& a_objuid) :
        m_container{ a_vRef }, m_index{ a_index }, m_recorded{ a_objuid }
    {
        m_objectDef = a_objuid.open<MCadObject>( )->isA( );
    }
};
