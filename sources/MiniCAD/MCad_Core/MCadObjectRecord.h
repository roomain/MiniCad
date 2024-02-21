#pragma once
/***********************************************
* @headerfile MCadObjectRecord.h
* @date 18 / 02 / 2024
* @author Roomain
************************************************/
#include "IMCadRecord.h"
#include "MCadObjectUID.h"

namespace UndoRedo
{

    class MCadObjectRecord : public IMCadRecord
    {
    private:
        size_t m_dataUndoOffset = 0;                /*!< data undo offset of record*/
        size_t m_dataRedoOffset = 0;                /*!< data redo offset of record*/
        MCadObjectUID m_recorded;                   /*!< recorded object*/
        std::weak_ptr<RTTIDefinition> m_pObjectDef; /*!< recorded object definition*/

    protected:
        void prepareRedo(MCadReallocMemory& a_realocMem, IMCadOutputStream& a_stream) override;
        void do_undo(IMCadInputStream& a_stream, MCadReallocMemory& a_realocMem) override;
        void do_redo(IMCadInputStream& a_stream, MCadReallocMemory& a_realocMem) override;

        void loadObject(const size_t& a_offset, IMCadInputStream& a_stream, MCadReallocMemory& a_realocMem);

    public:
        MCadObjectRecord( ) = delete;
        MCadObjectRecord(const MCadObjectUID& a_object, IMCadOutputStream& a_stream);
    };

}