#include "pch.h"
#include "IMCadIndexedContainer.h"


void IMCadIndexedContainer::assertItem(const MCadObjectPtr& a_pBefore, const MCadObjectPtr& a_pAfter, const size_t& a_index)
{
    if (auto pDoc = document().lock())
    {
        RecordExtra extra = IndexedItem{
            a_pBefore ? a_pBefore->uid() : 0,a_pAfter ? a_pAfter->uid() : 0,a_pBefore,a_pAfter,a_index };
        pDoc->undoRedo().currentSession().record(this, IMCadRecord::RecordAction::Record_changed, extra);
    }
}

void IMCadIndexedContainer::assertObjectAdded(const MCadObjectPtr& a_objAdd, const size_t& a_index)
{
    if (auto pDoc = document().lock())
    {
        RecordExtra extra = IndexedItem{ 0, a_objAdd->uid(), MCadObjectWPtr(), a_objAdd, a_index };
        pDoc->undoRedo().currentSession().record(this, IMCadRecord::RecordAction::Record_add, extra);
    }
}

void IMCadIndexedContainer::assertObjectRemoved(std::shared_ptr<MCadObject>& a_object, const size_t& a_index)
{
    if (auto pDoc = document().lock())
    {
        RecordExtra extra = IndexedItem{ a_object->uid(), 0, a_object, MCadObjectWPtr(), a_index };
        pDoc->undoRedo().currentSession().record(this, IMCadRecord::RecordAction::Record_add, extra);
    }
}