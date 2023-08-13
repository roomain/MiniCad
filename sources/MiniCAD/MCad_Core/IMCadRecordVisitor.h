#pragma once
/***********************************************
* @headerfile IMCadRecordVisitor.h
* @date 09 / 08 / 2023
* @author Roomain
************************************************/
#include <memory>

class IMCadRecord;
class MCadObjectRecord;
class MCadIndexedContainerRecord;
class MCadRecorDictionary;
using IMCadRecordUPtr = std::unique_ptr<IMCadRecord>;

/*@brief interface for creating redo records by Visitor design pattern*/
class IMCadRecordVisitor
{
public:
	virtual IMCadRecordUPtr genRedoRecord(const MCadObjectRecord* a_pUndoRecord) = 0;
	virtual IMCadRecordUPtr genRedoRecord(const MCadIndexedContainerRecord* a_pUndoRecord) = 0;
	virtual IMCadRecordUPtr genRedoRecord(const MCadRecorDictionary* a_pUndoRecord) = 0;
};