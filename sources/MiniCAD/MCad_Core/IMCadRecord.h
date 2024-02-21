#pragma once
/***********************************************
* @headerfile IMCadRecord.h
* @date 02 / 08 / 2023
* @author Roomain
************************************************/
#include <memory>
#include "MCadReallocMemory.h"
#include "RTTIDefinition.h"

class MCadObject;
class IMCadOutputStream;
class IMCadInputStream;

namespace UndoRedo
{

    /*@brief Base class for recording comands*/
    class IMCadRecord
    {
    private:
        bool m_bErased = false;	    /*!< indicate erase record*/
        bool m_bPrepareRedo = true; /*!< indicate redo need to be prepared*/

    protected:
        virtual void prepareRedo(MCadReallocMemory& a_realocMem, IMCadOutputStream& a_stream) = 0;
        virtual void do_undo(IMCadInputStream& a_stream, MCadReallocMemory& a_realocMem) = 0;
        virtual void do_redo(IMCadInputStream& a_stream, MCadReallocMemory& a_realocMem) = 0;

    public:
        IMCadRecord( ) = default;
        virtual ~IMCadRecord( ) = default;
        void erase(bool a_bErase) { m_bErased = a_bErase; }
        bool isErased( )const { return m_bErased; }

        void undo(IMCadInputStream& a_stream, MCadReallocMemory& a_realocMem, IMCadOutputStream& a_outStream);
        void redo(IMCadInputStream& a_stream, MCadReallocMemory& a_realocMem);
    };


    using IMCadRecordPtr = std::shared_ptr<IMCadRecord>;
}
