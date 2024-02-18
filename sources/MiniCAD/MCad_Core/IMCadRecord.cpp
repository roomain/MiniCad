#include "pch.h"
#include "IMCadRecord.h"

void IMCadRecord::undo(IMCadInputStream& a_stream, MCadReallocMemory& a_realocMem, IMCadOutputStream& a_outStream)
{
    if ( m_bPrepareRedo )
    {
        prepareRedo(a_realocMem, a_outStream);
        m_bPrepareRedo = false;
    }
    do_undo(a_stream, a_realocMem);
}

void IMCadRecord::redo(IMCadInputStream& a_stream, MCadReallocMemory& a_realocMem)
{
    do_redo(a_stream, a_realocMem);
}