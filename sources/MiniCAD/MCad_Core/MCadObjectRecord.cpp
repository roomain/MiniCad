#include "pch.h"
#include "MCadObjectRecord.h"
#include "IMCadOutputStream.h"
#include "IMCadInputStream.h"
#include "MCadReallocMemory.h"

namespace UndoRedo
{

    MCadObjectRecord::MCadObjectRecord(const MCadObjectUID& a_object, IMCadOutputStream& a_stream, const std::weak_ptr<RTTIDefinition>& a_def) :
        m_dataUndoOffset{ m_dataUndoOffset = a_stream.offset( ) }, m_recorded{ a_object }, m_pObjectDef{ a_def }
    {
        m_recorded.open<MCadObject>( )->save(a_stream);
    }

    void MCadObjectRecord::prepareRedo(MCadReallocMemory& a_reallocMem, IMCadOutputStream& a_stream)
    {
        auto pObject = a_reallocMem.realloc(m_recorded, m_pObjectDef);
        if ( pObject )
        {
            m_dataRedoOffset = a_stream.offset( );
            pObject->save(a_stream);
            m_recorded = pObject->objectUID( );
        }
        else
        {
            MCadLogger::Instance( ) << LogMode::LOG_WARNING << "Can't prepare redo";
        }
    }

    void MCadObjectRecord::do_undo(IMCadInputStream& a_stream, MCadReallocMemory& a_reallocMem)
    {
        loadObject(m_dataUndoOffset, a_stream, a_reallocMem);
    }

    void MCadObjectRecord::do_redo(IMCadInputStream& a_stream, MCadReallocMemory& a_reallocMem)
    {
        loadObject(m_dataRedoOffset, a_stream, a_reallocMem);
    }

    void MCadObjectRecord::loadObject(const size_t& a_offset, IMCadInputStream& a_stream, MCadReallocMemory& a_reallocMem)
    {
        auto pObject = a_reallocMem.realloc(m_recorded, m_pObjectDef);
        if ( pObject )
        {
            m_recorded = pObject->objectUID( );
            a_stream.setPos(a_offset);
            pObject->load(a_stream);
        }
        else
        {
            MCadLogger::Instance( ) << LogMode::LOG_WARNING << "Can't undo/redo";
        }
    }

}