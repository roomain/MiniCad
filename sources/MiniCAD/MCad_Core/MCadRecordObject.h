#pragma once
/***********************************************
* @headerfile MCadRecordObject.h
* @date 08 / 08 / 2023
* @author Roomain
************************************************/
#include "IMCadRecord.h"
#include "MCadRecordExtra.h"


/*@brief record for simple object*/
class MCadRecordObject : public IMCadRecord
{
private:
	size_t m_dataOffset;	/*!< offset of recorded data in stream*/
	size_t m_dataSize;		/*!< datasize*/

public:
	MCadRecordObject(const RecordAction a_action, const MCadObject* a_pObject,
		const size_t& a_offset, const size_t& a_size);
	~MCadRecordObject() = default;

	virtual void undo(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream)const;

	/*@brief redo record return undo record*/
	virtual void redo(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream)const;

	/*@brief apply filter on record*/
	virtual [[nodiscard]] bool invokeFilter(RecordFilter& filter)const;

	std::unique_ptr<IMCadRecord> genReverseRecord(IMCadRecordVisitor& a_visitor)const final;
};
