#pragma once
/***********************************************
* @headerfile TMCadMapRecords.h
* @date 18 / 02 / 2024
* @author Roomain
************************************************/
#include "IMCadRecord.h"
#include "MCadLogger.h"
#include "MCadObjectUID.h"
#include "RTTIDefinition.h"

namespace UndoRedo
{
    template<typename Key, typename Type,  class Compare = std::less<Key>>  
        requires ( is_MCadShared_base_of<MCadObject, Type>::value )
    class TMCadMap;

    template<typename Key, typename ContainedType, class Compare = std::less<Key>>
    class TMCadMapInsertRecord : public IMCadRecord
    {
    public:
        using RecordedMap = TMCadMap<Key, ContainedType, Compare>;

    private:
        MCadRef<RecordedMap> m_container;
        std::weak_ptr<RTTIDefinition> m_pObjectDef;
        Key m_key;                                          /*!< key of object*/
        MCadObjectUID m_recorded;                           /*!< recorded object*/

        template<typename Type>
        static void open(MCadShared_ptr<Type>& a_pointer, MCadObjectUID& a_objUid)
        {
            a_pointer = a_objUid.open<Type>( );
        }

    protected:
        void prepareRedo(MCadReallocMemory& a_realocMem, IMCadOutputStream& a_stream) override
        {
            // nothing todo
        }

        void do_undo(IMCadInputStream& a_stream, MCadReallocMemory& a_realocMem) override
        {
            if ( m_container.valid( ) )
            {
                m_container->erase(m_key);
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
                    (*m_container.pointer())[m_key] = pObject;
                }
                else
                {
                    MCadLogger::Instance( ) << LogMode::LOG_WARNING << "Can't undo/redo object not recored";
                }
            }
            else
            {
                MCadLogger::Instance( ) << LogMode::LOG_WARNING << "Can't undo/redo";
            }
        }

    public:
        TMCadMapInsertRecord( ) = delete;
        explicit TMCadMapInsertRecord(const MCadRef<RecordedMap>& a_vRef, const Key& a_key, const MCadObjectUID& a_objuid) :
            m_container{ a_vRef }, m_key{ a_key }, m_recorded{ a_objuid }
        {
            m_pObjectDef = a_objuid.open<MCadObject>( )->isA( );
        }

        explicit TMCadMapInsertRecord(const MCadRef<RecordedMap>& a_vRef, const Key& a_key, const MCadObjectUID& a_objuid, const std::weak_ptr<RTTIDefinition>& a_def) :
            m_container{ a_vRef }, m_key{ a_key }, m_recorded{ a_objuid }, m_pObjectDef{ a_def }
        {
            //
        }
    };

    template<typename Key, typename ContainedType, class Compare = std::less<Key>>
    class TMCadMapEraseRecord : public IMCadRecord
    {
    public:
        using RecordedMap = TMCadMap<Key, ContainedType, Compare>;

    private:
        MCadRef<RecordedMap> m_container;
        std::weak_ptr<RTTIDefinition> m_pObjectDef;
        Key m_key;                                          /*!< key of object*/
        MCadObjectUID m_recorded;                           /*!< recorded object*/

        template<typename Type>
        static void open(MCadShared_ptr<Type>& a_pointer, MCadObjectUID& a_objUid)
        {
            a_pointer = a_objUid.open<Type>( );
        }

    protected:
        void prepareRedo(MCadReallocMemory& a_realocMem, IMCadOutputStream& a_stream) override
        {
            // nothing todo
        }

        void do_undo(IMCadInputStream& a_stream, MCadReallocMemory& a_realocMem) override
        {
            if ( m_container.valid( ) )
            {
                auto pObject = a_realocMem.realloc(m_recorded, m_pObjectDef);
                if ( pObject )
                {
                    m_recorded = pObject->objectUID( );
                    ( *m_container.pointer( ) ) [ m_key ] = pObject;
                }
                else
                {
                    MCadLogger::Instance( ) << LogMode::LOG_WARNING << "Can't undo/redo object not recored";
                }
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
                m_container->erase(m_key);
            }
            else
            {
                MCadLogger::Instance( ) << LogMode::LOG_WARNING << "Can't undo/redo";
            }
        }

    public:
        TMCadMapEraseRecord( ) = delete;
        explicit TMCadMapEraseRecord(const MCadRef<RecordedMap>& a_vRef, const Key& a_key, const MCadObjectUID& a_objuid) :
            m_container{ a_vRef }, m_key{ a_key }, m_recorded{ a_objuid }
        {
            m_pObjectDef = a_objuid.open<MCadObject>( )->isA( );
        }
        explicit TMCadMapEraseRecord(const MCadRef<RecordedMap>& a_vRef, const Key& a_key, const MCadObjectUID& a_objuid, const std::weak_ptr<RTTIDefinition>& a_def) :
            m_container{ a_vRef }, m_key{ a_key }, m_recorded{ a_objuid }, m_pObjectDef{ a_def }
        {
            //
        }
    };

    template<typename Key, typename ContainedType, class Compare = std::less<Key>>
    class TMCadMapChangeRecord : public IMCadRecord
    {
    public:
        using RecordedMap = TMCadMap<Key, ContainedType, Compare>;

    private:
        MCadRef<RecordedMap> m_container;
        std::weak_ptr<RTTIDefinition> m_pObjectDef;
        Key m_key;                                          /*!< key of object*/
        MCadObjectUID m_modified;                           /*!< recorded object*/
        MCadObjectUID m_modifier;                           /*!< recorded object*/

        template<typename Type>
        static void open(MCadShared_ptr<Type>& a_pointer, MCadObjectUID& a_objUid)
        {
            a_pointer = a_objUid.open<Type>( );
        }

    protected:
        void prepareRedo(MCadReallocMemory& a_realocMem, IMCadOutputStream& a_stream) override
        {
            m_modifier = (*m_container.pointer) [ m_key ];
        }

        void do_undo(IMCadInputStream& a_stream, MCadReallocMemory& a_realocMem) override
        {
            if ( m_container.valid( ) )
            {
                auto pObject = a_realocMem.realloc(m_modified, m_pObjectDef);
                if ( pObject )
                {
                    m_modified = pObject->objectUID( );
                    ( *m_container.pointer ) [ m_key ] = m_modified;
                }
                else
                {
                    MCadLogger::Instance( ) << LogMode::LOG_WARNING << "Can't undo/redo object not recored";
                }
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
                auto pObject = a_realocMem.realloc(m_modifier, m_pObjectDef);
                if ( pObject )
                {
                    m_modifier = pObject->objectUID( );
                    ( *m_container.pointer ) [ m_key ] = m_modifier;
                }
                else
                {
                    MCadLogger::Instance( ) << LogMode::LOG_WARNING << "Can't undo/redo object not recored";
                }
            }
            else
            {
                MCadLogger::Instance( ) << LogMode::LOG_WARNING << "Can't undo/redo";
            }
        }

    public:
        TMCadMapChangeRecord( ) = delete;
        explicit TMCadMapChangeRecord(const MCadRef<RecordedMap>& a_vRef, const Key& a_key, const MCadObjectUID& a_objuid) :
            m_container{ a_vRef }, m_key{ a_key }, m_modified{ a_objuid }
        {
            m_pObjectDef = a_objuid.open<MCadObject>( )->isA( );
        }
        explicit TMCadMapChangeRecord(const MCadRef<RecordedMap>& a_vRef, const Key& a_key, const MCadObjectUID& a_objuid, const std::weak_ptr<RTTIDefinition>& a_def) :
            m_container{ a_vRef }, m_key{ a_key }, m_modified{ a_objuid }, m_pObjectDef{ a_def }
        {
            //
        }
    };
}