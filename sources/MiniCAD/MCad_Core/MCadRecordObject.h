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
	//
public:

	bool hasReverse()const noexcept final;
	std::shared_ptr<IMCadRecord> generateReverse(MCadInputStream& a_stream, MCadRealocMemory& a_realocMem)const final;
	void apply(MCadOutputStream& a_stream, MCadRealocMemory& a_realocMem) final;
};