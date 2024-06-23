#pragma once
/***********************************************
* @headerfile TMCadUnordered_mapRecords.h
* @date 24 / 02 / 2024
* @author Roomain
************************************************/
#include "IMCadRecord.h"
#include "MCadLogger.h"
#include "MCadObjectUID.h"
#include "RTTIDefinition.h"

namespace UndoRedo
{
    template<typename Key, typename Type>
        requires ( is_MCadShared_base_of<MCadObject, Type>::value )
    class TMCadUnordered_map;

    template<typename Key, typename ContainedType>
    class TMCadUnordered_mapInsertRecord : public IMCadRecord
    {
    public:
        using RecordedUnordered_map = TMCadUnordered_map<Key, ContainedType>;

    private:
        MCadRef<RecordedUnordered_map> m_container;
        std::weak_ptr<RTTIDefinition> m_pObjectDef;
        Key m_key;                                          /*!< key of object*/
        MCadObjectUID m_recorded;                           /*!< recorded object*/

        template<typename Type>
        static void open(MCadShared_ptr<Type>& a_pointer, MCadObjectUID& a_objUid)
        {
            a_pointer = a_objUid.open<Type>( );
        }

    protected:
        void prepareRedo(MCadReallocMemory& a_reallocMem, IMCadOutputStream& a_stream) override
        {
            // nothing todo
        }

        void do_undo(IMCadInputStream& a_stream, MCadReallocMemory& a_reallocMem) override
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

        void do_redo(IMCadInputStream& a_stream, MCadReallocMemory& a_reallocMem) override
        {
            if ( m_container.valid( ) )
            {
                ContainedType pObject;
                a_reallocMem.realloc(pObject, m_recorded, m_pObjectDef);
                if ( pObject )
                {
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

    public:
        TMCadUnordered_mapInsertRecord( ) = delete;
        explicit  TMCadUnordered_mapInsertRecord(const MCadRef<RecordedUnordered_map>& a_vRef, const Key& a_key, const MCadObjectUID& a_objuid) :
            m_container{ a_vRef }, m_key{ a_key }, m_recorded{ a_objuid }
        {
            m_pObjectDef = a_objuid.open<MCadObject>( )->isA( );
        }

        explicit TMCadUnordered_mapInsertRecord(const MCadRef<RecordedUnordered_map>& a_vRef, const Key& a_key, const MCadObjectUID& a_objuid, const std::weak_ptr<RTTIDefinition>& a_def) :
            m_container{ a_vRef }, m_key{ a_key }, m_recorded{ a_objuid }, m_pObjectDef{ a_def }
        {
            //
        }
    };

    template<typename Key, typename ContainedType>
    class TMCadUnordered_mapEraseRecord : public IMCadRecord
    {
    public:
        using RecordedUnordered_map = TMCadUnordered_map<Key, ContainedType>;

    private:
        MCadRef<RecordedUnordered_map> m_container;
        std::weak_ptr<RTTIDefinition> m_pObjectDef;
        Key m_key;                                          /*!< key of object*/
        MCadObjectUID m_recorded;                           /*!< recorded object*/

        template<typename Type>
        static void open(MCadShared_ptr<Type>& a_pointer, MCadObjectUID& a_objUid)
        {
            a_pointer = a_objUid.open<Type>( );
        }

    protected:
        void prepareRedo(MCadReallocMemory& a_reallocMem, IMCadOutputStream& a_stream) override
        {
            // nothing todo
        }

        void do_undo(IMCadInputStream& a_stream, MCadReallocMemory& a_reallocMem) override
        {
            if ( m_container.valid( ) )
            {
                ContainedType pObject;
                a_reallocMem.realloc(pObject, m_recorded, m_pObjectDef);
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

        void do_redo(IMCadInputStream& a_stream, MCadReallocMemory& a_reallocMem) override
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
        TMCadUnordered_mapEraseRecord( ) = delete;
        explicit TMCadUnordered_mapEraseRecord(const MCadRef<RecordedUnordered_map>& a_vRef, const Key& a_key, const MCadObjectUID& a_objuid) :
            m_container{ a_vRef }, m_key{ a_key }, m_recorded{ a_objuid }
        {
            m_pObjectDef = a_objuid.open<MCadObject>( )->isA( );
        }

        explicit TMCadUnordered_mapEraseRecord(const MCadRef<RecordedUnordered_map>& a_vRef, const Key& a_key, const MCadObjectUID& a_objuid, const std::weak_ptr<RTTIDefinition>& a_def) :
            m_container{ a_vRef }, m_key{ a_key }, m_recorded{ a_objuid }, m_pObjectDef{ a_def }
        {
            //
        }
    };

    template<typename Key, typename ContainedType>
    class TMCadUnordered_mapChangeRecord : public IMCadRecord
    {
    public:
        using RecordedUnordered_map = TMCadUnordered_map<Key, ContainedType>;

    private:
        MCadRef<RecordedUnordered_map> m_container;
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
        void prepareRedo(MCadReallocMemory& a_reallocMem, IMCadOutputStream& a_stream) override
        {
            if ( ( *m_container.pointer( ) ) [ m_key ] )
                m_modifier = ( *m_container.pointer( ) ) [ m_key ]->objectUID( );
        }

        void do_undo(IMCadInputStream& a_stream, MCadReallocMemory& a_reallocMem) override
        {
            if ( m_container.valid( ) )
            {
                ContainedType pObject;
                a_reallocMem.realloc(pObject, m_modified, m_pObjectDef);
                if ( pObject )
                {
                    m_modified = pObject->objectUID( );
                }
                ( *m_container.pointer( ) ) [ m_key ] = pObject;
            }
            else
            {
                MCadLogger::Instance( ) << LogMode::LOG_WARNING << "Can't undo/redo";
            }
        }

        void do_redo(IMCadInputStream& a_stream, MCadReallocMemory& a_reallocMem) override
        {
            if ( m_container.valid( ) )
            {
                ContainedType pObject;
                a_reallocMem.realloc(pObject, m_modifier, m_pObjectDef);
                if ( pObject )
                {
                    m_modifier = pObject->objectUID( );
                }
                ( *m_container.pointer( ) ) [ m_key ] = pObject;
            }
            else
            {
                MCadLogger::Instance( ) << LogMode::LOG_WARNING << "Can't undo/redo";
            }
        }

    public:
        TMCadUnordered_mapChangeRecord( ) = delete;
        explicit TMCadUnordered_mapChangeRecord(const MCadRef<RecordedUnordered_map>& a_vRef, const Key& a_key, const MCadObjectUID& a_objuid) :
            m_container{ a_vRef }, m_key{ a_key }, m_modified{ a_objuid }
        {
            m_pObjectDef = a_objuid.open<MCadObject>( )->isA( );
        }

        explicit TMCadUnordered_mapChangeRecord(const MCadRef<RecordedUnordered_map>& a_vRef, const Key& a_key, const MCadObjectUID& a_objuid, const std::weak_ptr<RTTIDefinition>& a_def) :
            m_container{ a_vRef }, m_key{ a_key }, m_modified{ a_objuid }, m_pObjectDef{ a_def }
        {
            //
        }
    };
}