#include "pch.h"
#include "MCadRecordContainer.h"

void MCadRecordContainer::undo(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream)const
{
	//
}

/*@brief redo record return undo record*/
void MCadRecordContainer::redo(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream)const
{
	//
}

/*@brief apply filter on record*/
bool MCadRecordContainer::invokeFilter(RecordFilter& filter)const
{
	//
}

std::unique_ptr<IMCadRecord> MCadRecordContainer::genReverseRecord(IMCadRecordVisitor& a_visitor)const
{
	//
	return nullptr;
}