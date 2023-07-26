#pragma once
/***********************************************
* @headerfile MCadUndoRedo.h
* @date 22 / 07 / 2023
* @author Roomain
************************************************/
#include "MCadBinaryBuffer.h"
#include "MCadObject.h"
#include <chrono>
#include <map>
#include <deque>
#include <mutex> // for concurent undo buffer writing

class IMCaInputStream;
class IMCaOutputStream;
using IMCadInputStreamPtr = std::shared_ptr<IMCadInputStream>;
using IMCadOutputStreamPtr = std::shared_ptr<IMCadOutputStream>;

// class regrouping all change during a command call
class Session
{
public:
	/*@brief undo/redo action*/
	enum class RecordAction
	{
		Undo_create = 0,			/*!< object created*/
		Redo_create = Undo_create,
		Undo_modify,				/*!< object modified*/
		Redo_modify = Undo_modify,
		Undo_delete,				/*!< object deleted*/
		Redo_delete = Undo_delete
	};

private:
	struct Record
	{
		RecordAction m_action;			/*!< record action*/
		ObjectUID m_objectId;			/*!< object id concerned*/
		ObjectUID m_ownerObject;		/*!< object id od owner*/
		RTTIDefinitionWPtr m_objectDef;	/*!< definition of concerned object*/
		size_t m_offset;				/*!< data offset in undeo buffer*/
	};

	std::mutex m_readWriteMutex;
	std::chrono::time_point<std::chrono::system_clock> m_timePoint;	/*!< time of undo session*/
	MCadBinaryBuffer m_undoBuffer;									/*!< saving buffer*/
	std::list<Record> m_mpRecord;									/*!< list of record*/
	std::map<ObjectUID, MCadObjectWPtr> m_PointerRelocMap;			/*!< Pointer Relocation Map (for deleted object)*/
	// For container: retrieve deleted contained objects in relocMap

public:
	// TODO
	void record(const MCadObjectPtr& a_undoObject, RecordAction&& a_action);
	void restore();
};


class MCadUndoRedo
{
private:
	bool m_active = true;							/*!< undo redo activation*/
	bool m_sessionActive = false;					/*!< flag indicating an active session*/
	std::deque<Session> m_sessionList;				/*!< list of undoredo session*/
	/**/
	std::deque<Session>::iterator m_currentSession;	/*!< iterator on current session*/
public:
	MCadUndoRedo(const MCadUndoRedo&) = delete;
	MCadUndoRedo();
	virtual ~MCadUndoRedo();
	void enableUndo(const bool a_enable) { m_active = a_enable; }
	[[nodiscard]] bool undoEnabled()const noexcept { return m_active; }
	/*@brief start undo recording (automatically enable)*/
	void startUndoRecord();
	/*@brief end endo record, flush to undo file*/
	void endUndoRecord();
	/*@brief cancel current*/
	void cancel();
	/*@brief redo*/
	void redo();
	/*@brief undo*/
	void undo();
	/*@brief is undo possible*/
	bool hasUndo()const noexcept;
	/*@brief is redo possible*/
	bool hasRedo()const noexcept;
};