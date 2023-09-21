#pragma once
/***********************************************
* @headerfile IMCadRecord.h
* @date 02 / 08 / 2023
* @author Roomain
************************************************/
#include <memory>
#include "MCadRealocMemory.h"
#include "RTTIDefinition.h"

class MCadObject;
class IMCadOutputStream;
class IMCadInputStream;

/*@brief Base class for recording comands*/
class IMCadRecord
{
protected:
	bool m_bErased = false;	/*!< indicate erase record*/

public:
	IMCadRecord() = default;
	virtual ~IMCadRecord() = default;
	void erase(bool a_bErase) { m_bErased = a_bErase; }
	bool isErased()const { return m_bErased; }
	/*@brief A reverse record can be generated*/
	virtual bool hasReverse()const noexcept = 0;
	/*@brief generate reverse record*/
	virtual std::shared_ptr<IMCadRecord> generateReverse(IMCadOutputStream& a_stream, MCadRealocMemory& a_realocMem)const = 0;
	/*@brief apply record for undo*/
	virtual void apply(IMCadInputStream& a_stream, MCadRealocMemory& a_realocMem) = 0;

	// functions used for filtering
	/*@brief object uid concerned by this record*/
	virtual const ObjectUID recordedObject( )const noexcept = 0;
	/*@brief definition of recorded object*/
	virtual RTTIDefinitionWPtr recordedObjectDefinition( )const noexcept = 0;
};

using IMCadRecordPtr = std::shared_ptr<IMCadRecord>;
