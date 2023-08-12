#pragma once
/***********************************************
* @headerfile MCadRecordObject.h
* @date 08 / 08 / 2023
* @author Roomain
************************************************/
#include "IMCadRecord.h"


/*@brief record for simple object*/
class MCadRecordObject : public IMCadRecord
{
private:
	size_t m_dataOffset;					/*!< offset of recorded data in stream*/
	size_t m_dataSize;						/*!< datasize*/
	MCadObjectWPtr m_pObject;				/*!< recorded object*/
	RTTIDefinitionWPtr m_objDef;			/*!< definition of recorded object*/

public:
	MCadRecordObject(const RecordAction a_action, const MCadObjectWPtr a_pObject,
		const size_t& a_offset, const size_t& a_size);
	~MCadRecordObject() = default;

	virtual void process(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream)const;

	/*@brief apply filter on record*/
	virtual [[nodiscard]] bool invokeFilter(RecordFilter& filter)const;

	std::unique_ptr<IMCadRecord> genReverseRecord(IMCadRecordVisitor& a_visitor)const final;
};
