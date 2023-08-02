#pragma once
/***********************************************
* @headerfile IMCadRecord.h
* @date 02 / 08 / 2023
* @author Roomain
************************************************/
#include <memory>
#include "MCadInputBinStream.h"
#include "MCadOutputBinStream.h"
#include "MCadObject.h"


using ObjectMap = std::unordered_map<ObjectUID, MCadObjectPtr>;

// record by type
// using template class partial specialization for container

/*@brief represents an object modification during a command*/
class IMCadRecord
{
public:
	/*@brief undo/redo action*/
	enum class RecordAction
	{
		Undo_modify = 0,			/*!< object modified*/
		Redo_modify = Undo_modify,
		Undo_create,				/*!< object created*/
		Redo_create = Undo_create,
		Undo_delete,				/*!< object deleted*/
		Redo_delete = Undo_delete
	};

	using RecordFilter = std::function<bool(RTTIDefinitionPtr, RecordAction)>;

private:
	RecordAction m_action;	/*!< recording action*/
	ObjectUID m_objectID;	/*!< uid of object recorded*/
	size_t m_dataOffset;	/*!< offset of recorded data in stream*/

public:
	IMCadRecord(RecordAction a_action, const ObjectUID& a_objUID) : m_action{ a_action }, m_objectID{ a_objUID } {}
	virtual ~IMCadRecord() = default;

	[[nodiscard]] constexpr RecordAction recordAction()const noexcept { return m_action; }
	/*@brief undo record return redo record*/
	virtual std::unique_ptr<IMCadRecord> undo(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream, MCadOutputBinStream& a_outputStream)const = 0;

	/*@brief redo record return undo record*/
	virtual std::unique_ptr<IMCadRecord> redo(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream, MCadOutputBinStream& a_outputStream)const = 0;

	/*@brief apply filter on record*/
	virtual [[nodiscard]] bool invokeFilter(RecordFilter& filter)const = 0;
};

using IMCadRecordUPtr = std::unique_ptr<IMCadRecord>;