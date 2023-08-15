#pragma once
/***********************************************
* @headerfile IMCadRecord.h
* @date 02 / 08 / 2023
* @author Roomain
************************************************/
#include <memory>
#include <unordered_map>
#include "MCadInputBinStream.h"
#include "MCadOutputBinStream.h"
#include "MCadObject.h"

/*@brief use for realocation of deleted pointers*/
using ObjectRealocMap = std::unordered_map<ObjectUID, MCadObjectPtr>;

/*@brief use for realocated pointer from next records*/
using ObjectNextRealocMap = std::unordered_map<ObjectUID, MCadObjectWPtr>;

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
	bool m_bErased = false;									/*!< indicate erase record*/
	RecordAction m_action = RecordAction::Record_create;	/*!< recording action*/
	ObjectUID m_objectID = 0;								/*!< uid of object recorded*/

	/*@brief find realocated object*/
	static inline [[nodiscard]] MCadObjectWPtr findRealocObject(const ObjectUID& a_uid, const ObjectRealocMap& a_realocMap, const ObjectNextRealocMap& a_realocNextMap)
	{
		if (a_realocMap.contains(a_uid))
			return a_realocMap.at(a_uid);

		if (a_realocNextMap.contains(a_uid))
			return a_realocNextMap.at(a_uid);

		return MCadObjectWPtr();
	}

public:
	IMCadRecord() = delete;
	IMCadRecord(const RecordAction a_action, const ObjectUID& a_objUID) : m_action{ a_action }, m_objectID{ m_objectID }
	{}

	virtual ~IMCadRecord() = default;

	[[nodiscard]] constexpr ObjectUID objectUID()const { return  m_objectID; }

	[[nodiscard]] constexpr RecordAction recordAction()const noexcept { return m_action; }

	/*@brief process record*/
	virtual void process(ObjectRealocMap& a_realocMap, ObjectNextRealocMap& a_realocNextMap, MCadInputBinStream& a_inputStream) = 0;

	/*@brief apply filter on record*/
	virtual [[nodiscard]] bool invokeFilter(RecordFilter& filter)const = 0;

	void erase() { m_bErased = true; }
	constexpr bool isErased()const noexcept { return m_bErased; }

	virtual std::shared_ptr<IMCadRecord> genReverseRecord(IMCadRecordVisitor& a_visitor)const = 0;
};

using IMCadRecordPtr = std::shared_ptr<IMCadRecord>;
