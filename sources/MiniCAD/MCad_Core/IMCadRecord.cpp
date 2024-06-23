#include "pch.h"
#include "IMCadRecord.h"

namespace UndoRedo
{

    void IMCadRecord::undo(IMCadInputStream& a_stream, MCadReallocMemory& a_reallocMem, IMCadOutputStream& a_outStream)
    {
        if ( m_bPrepareRedo )
        {
            prepareRedo(a_reallocMem, a_outStream);
            m_bPrepareRedo = false;
        }
        do_undo(a_stream, a_reallocMem);
    }

    void IMCadRecord::redo(IMCadInputStream& a_stream, MCadReallocMemory& a_reallocMem)
    {
        do_redo(a_stream, a_reallocMem);
    }
}