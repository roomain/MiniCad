#pragma once
/***********************************************
* @headerfile IMCadRecord.h
* @date 03 / 08 / 2023
* @author Roomain
************************************************/
#include "IMCadRecord.h"
#include "TMCadObjectProxy.h"


class IMCadObjectRecord : public IMCadRecord
{

protected:
	using RecordObjProxy = TMCadObjectProxy<MCadObject>;
	mutable RecordObjProxy m_objectProxy;/*!< proxy on recorded object*/

public:
	IMCadObjectRecord(MCadObject* const a_pObject);
	virtual ~IMCadObjectRecord( ) = default;
	const ObjectUID recordedObject( )const noexcept final { return m_objectProxy.objectUID(); }
	RTTIDefinitionWPtr recordedObjectDefinition( )const noexcept final { return m_objectProxy.objectDef(); }
};


/*@brief record object modification*/
class MCadRecordModification : public IMCadObjectRecord
{
private:
	size_t m_dataOffset;				/*!< offset of recorded data*/
	
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
	ObjectUID m_objectUID;
	std::weak_ptr<RTTIDefinition> m_pObjectDef;

public:
	MCadRecordDeletion(const MCadObject* a_pObject, IMCadOutputStream& a_stream);
	virtual ~MCadRecordDeletion() = default;
	bool hasReverse()const noexcept final { return false; }
	std::shared_ptr<IMCadRecord> generateReverse(IMCadOutputStream& a_stream, MCadRealocMemory& a_realocMem)const final;
	void apply(IMCadInputStream& a_stream, MCadRealocMemory& a_realocMem) final;

	const ObjectUID recordedObject( )const noexcept final { return m_objectUID; }
	RTTIDefinitionWPtr recordedObjectDefinition( )const noexcept final { return m_pObjectDef; }
};