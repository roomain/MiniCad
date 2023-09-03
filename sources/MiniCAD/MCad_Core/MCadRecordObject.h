#pragma once
/***********************************************
* @headerfile IMCadRecord.h
* @date 03 / 08 / 2023
* @author Roomain
************************************************/
#include "IMCadRecord.h"

/*@brief record object modification*/
class MCadRecordModification : public IMCadRecord
{
private:
	size_t m_dataOffset;				/*!< offset of recorded data*/
	std::weak_ptr<MCadObject> m_object;	/*!< recorded object pointer*/
	
public:
	MCadRecordModification(MCadObject* const a_pObject, IMCadOutputStream& a_stream);
	virtual ~MCadRecordModification() = default;
	bool hasReverse()const noexcept final { return true; }
	std::shared_ptr<IMCadRecord> generateReverse(IMCadOutputStream& a_stream, MCadRealocMemory& a_realocMem)const final;
	void apply(IMCadInputStream& a_stream, MCadRealocMemory& a_realocMem) final;
};


/*@brief record object deletetion*/
class MCadRecordDeletion : public IMCadRecord
{
private:
	size_t m_dataOffset;				/*!< offset of recorded data*/

public:
	MCadRecordDeletion(const MCadObject* a_pObject, IMCadOutputStream& a_stream);
	virtual ~MCadRecordDeletion() = default;
	bool hasReverse()const noexcept final { return false; }
	std::shared_ptr<IMCadRecord> generateReverse(IMCadOutputStream& a_stream, MCadRealocMemory& a_realocMem)const final;
	void apply(IMCadInputStream& a_stream, MCadRealocMemory& a_realocMem) final;
};