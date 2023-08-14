#pragma once
/***********************************************
* @headerfile MCadObjectRecord.h
* @date 08 / 08 / 2023
* @author Roomain
************************************************/
#include "IMCadRecord.h"


/*@brief record for simple object*/
class MCadObjectRecord : public IMCadRecord
{
private:
	size_t m_dataOffset;					/*!< offset of recorded data in stream*/
	size_t m_dataSize;						/*!< datasize*/
	MCadObjectWPtr m_pObject;				/*!< recorded object*/
	RTTIDefinitionWPtr m_objDef;			/*!< definition of recorded object*/

public:
	MCadObjectRecord(const RecordAction a_action, const MCadObjectWPtr a_pObject,
		const size_t& a_offset, const size_t& a_size);
	MCadObjectRecord(const RecordAction a_action, const RTTIDefinitionWPtr a_pDef, const ObjectUID& a_uid);
	~MCadObjectRecord() = default;

	virtual void process(ObjectRealocMap& a_realocMap, ObjectNextRealocMap& a_realocNextMap, MCadInputBinStream& a_inputStream)final;

	inline MCadObjectWPtr object()const noexcept{ return m_pObject; }
	inline RTTIDefinitionWPtr definition()const noexcept { return m_objDef; }

	/*@brief apply filter on record*/
	[[nodiscard]] bool invokeFilter(RecordFilter& filter)const final;

	std::unique_ptr<IMCadRecord> genReverseRecord(IMCadRecordVisitor& a_visitor)const final;
};
