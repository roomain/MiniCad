#pragma once
/***********************************************
* @headerfile MCadIndexedContainerRecord.h
* @date 09/ 08 / 2023
* @author Roomain
************************************************/
#include "IMCadRecord.h"
#include "IMCadIndexedContainer.h"
#include "MCadRecordExtra.h"

/*@brief record for undo/redo-able container*/
class MCadIndexedContainerRecord : public IMCadRecord
{
private:
	IndexedItem m_item;
	IMCadIndexedContainerWPtr m_pContainer;

public:
	MCadIndexedContainerRecord(const RecordAction a_action, const IMCadIndexedContainerWPtr& a_pObject, const IndexedItem& a_data);
	~MCadIndexedContainerRecord() = default;
	
	virtual void process(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream)const;

	/*@brief apply filter on record*/
	virtual [[nodiscard]] bool invokeFilter(RecordFilter& filter)const;

	std::unique_ptr<IMCadRecord> genReverseRecord(IMCadRecordVisitor& a_visitor)const final;
};
