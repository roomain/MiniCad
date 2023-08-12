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

class IMCadRecordVisitor;

// record by type
// using template class partial specialization for container

/*@brief represents an object modification during a command*/
class IMCadRecord
{
public:
	/*@brief undo/redo action*/
	enum class RecordAction
	{
		Record_modify = 0,			/*!< object modified*/
		Record_create,				/*!< object created*/
		Record_delete,				/*!< object deleted*/
		Record_add,					/*!< (for container) object added*/
		Record_remove,				/*!< (for container) object removed*/
		Record_changed
	};

	using RecordFilter = std::function<bool(RTTIDefinitionPtr, RecordAction)>;

protected:
	bool m_bErased = false;	/*!< indicate erase record*/
	RecordAction m_action;	/*!< recording action*/
	ObjectUID m_objectID;	/*!< uid of object recorded*/

public:
	IMCadRecord() = delete;
	IMCadRecord(const RecordAction a_action, const ObjectUID& a_objUID) : m_action{ a_action }, m_objectID{ m_objectID }
	{}

	virtual ~IMCadRecord() = default;

	[[nodiscard]] constexpr ObjectUID objectUID()const { return  m_objectID; }

	[[nodiscard]] constexpr RecordAction recordAction()const noexcept { return m_action; }

	/*@brief process record*/
	virtual void process(ObjectMap& a_realocMap, MCadInputBinStream& a_inputStream)const = 0;

	/*@brief apply filter on record*/
	virtual [[nodiscard]] bool invokeFilter(RecordFilter& filter)const = 0;

	void erase() { m_bErased = true; }
	constexpr bool isErased()const noexcept { return m_bErased; }

	virtual std::unique_ptr<IMCadRecord> genReverseRecord(IMCadRecordVisitor& a_visitor)const = 0;
};

using IMCadRecordUPtr = std::unique_ptr<IMCadRecord>;
