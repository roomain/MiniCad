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
using IMCadRecordPtr = std::shared_ptr<IMCadRecord>;

/*@brief interface for creating redo records by Visitor design pattern*/
class IMCadRecordVisitor
{
public:
	virtual IMCadRecordPtr genRedoRecord(const MCadObjectRecord* a_pUndoRecord) = 0;
	virtual IMCadRecordPtr genRedoRecord(const MCadIndexedContainerRecord* a_pUndoRecord) = 0;
	virtual IMCadRecordPtr genRedoRecord(const MCadRecorDictionary* a_pUndoRecord) = 0;
};