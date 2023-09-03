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
	RTTIDefinitionWPtr m_pObjectDef;	/*!< definition of recorded object*/
	ObjectUID m_recordedObjectUID;		/*!< recorded object UID*/

public:
	IMCadRecord(const ObjectUID& a_objUID, const RTTIDefinitionWPtr& a_pDef) :
		m_pObjectDef{ a_pDef }, m_recordedObjectUID{ a_objUID } {}
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
	const ObjectUID& recordedObject()const noexcept { return m_recordedObjectUID; }
	/*@brief definition of recorded object*/
	RTTIDefinitionWPtr recordedObjectDefinition()const noexcept { return m_pObjectDef; }
};

using IMCadRecordPtr = std::shared_ptr<IMCadRecord>;
