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
class  MCadIndexedContainerRecord : public IMCadRecord
{
private:
	IndexedItem m_item;
	IMCadIndexedContainerWPtr m_pContainer;

public:
	MCadIndexedContainerRecord(const RecordAction a_action, const IMCadIndexedContainerWPtr& a_pObject, const IndexedItem& a_data);
	~MCadIndexedContainerRecord() = default;
	
	void process(ObjectRealocMap& a_realocMap, ObjectNextRealocMap& a_realocNextMap, MCadInputBinStream& a_inputStream)final;

	inline [[nodiscard]] IndexedItem indexedItem()const noexcept { return m_item; }

	inline [[nodiscard]] IMCadIndexedContainerWPtr container()const noexcept { return m_pContainer; }

	[[nodiscard]] bool itemWillDeleted()const;

	/*@brief apply filter on record*/
	[[nodiscard]] bool invokeFilter(RecordFilter& filter)const final;

	[[nodiscard]] void genReverseRecord(IMCadRecordVisitor& a_visitor, std::list<IMCadRecordPtr>& a_recList)const final;
};
