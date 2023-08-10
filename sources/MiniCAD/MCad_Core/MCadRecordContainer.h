#pragma once
/***********************************************
* @headerfile MCadRecordContainer.h
* @date 09/ 08 / 2023
* @author Roomain
************************************************/
#include "IMCadRecord.h"
#include "IMCadIndexedContainer.h"
#include "MCadRecordExtra.h"

/*@brief record for undo/redo-able container*/
class MCadRecordContainer : public IMCadRecord
{
private:
	IndexedItem m_item;
	IMCadIndexedContainerWPtr m_pContainer;

public:
	template<typename T>
	MCadRecordContainer(const RecordAction a_action, const IMCadIndexedContainerWPtr& a_pObject, const IndexedItem& a_data)
	{
		//
	}

	~MCadRecordContainer() = default;
	
	virtual void undo(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream)const;

	/*@brief redo record return undo record*/
	virtual void redo(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream)const;

	/*@brief apply filter on record*/
	virtual [[nodiscard]] bool invokeFilter(RecordFilter& filter)const;

	std::unique_ptr<IMCadRecord> genReverseRecord(IMCadRecordVisitor& a_visitor)const final;
};
