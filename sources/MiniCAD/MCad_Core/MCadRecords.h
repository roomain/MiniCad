#pragma once
/***********************************************
* @headerfile MCadRecords.h
* @date 08 / 08 / 2023
* @author Roomain
************************************************/
#include "IMCadRecord.h"
#include "IMCadIndexedContainer.h"
#include "MCadRecordExtra.h"


/*@brief record for simple object*/
class MCadRecordObject : public IMCadRecord
{
private:
	size_t m_dataOffset;	/*!< offset of recorded data in stream*/
	size_t m_dataSize;		/*!< datasize*/

public:
	MCadRecordObject(const RecordAction a_action, const MCadObject* a_pObject);
	~MCadRecordObject() = default;

	/*@brief first undo record return redo record*/
	virtual std::unique_ptr<IMCadRecord> undo(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream, 
		MCadOutputBinStream& a_outputStream)const;

	virtual void undo(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream)const;

	/*@brief redo record return undo record*/
	virtual void redo(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream)const;

	/*@brief apply filter on record*/
	virtual [[nodiscard]] bool invokeFilter(RecordFilter& filter)const;
};



/*@brief record for undo/redo-able container*/
class MCadRecordContainer : public IMCadRecord
{
private:
	IndexedItem m_item;

public:
	template<typename T>
	MCadRecordContainer(const RecordAction a_action, const IMCadIndexedContainer<T>* a_pObject, const IndexedItem& a_data);
	~MCadRecordContainer() = default;
	/*@brief first undo record return redo record*/
	virtual std::unique_ptr<IMCadRecord> undo(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream,
		MCadOutputBinStream& a_outputStream)const;

	virtual void undo(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream)const;

	/*@brief redo record return undo record*/
	virtual void redo(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream)const;

	/*@brief apply filter on record*/
	virtual [[nodiscard]] bool invokeFilter(RecordFilter& filter)const;
};



/*@brief record for undo/redo-able dictionary*/
class MCadRecordDictionary : public IMCadRecord
{
	//
};