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
#include <functional>
#include <mutex> // for concurent undo buffer writing
#include "MCadInputBinStream.h"
#include "MCadOutputBinStream.h"

using ObjectMap = std::unordered_map< ObjectUID, MCadObjectPtr>;
using UndoRedoTimePoint = std::chrono::time_point<std::chrono::system_clock>;
using ObjectDefWPtr = std::weak_ptr<RTTIDefinition>;




// class regrouping all change during a command call
class MCadRecordSession
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

	/*filter undo redo records*/
	using UndoRedoFilter = std::function<bool(RTTIDefinitionPtr, RecordAction)>;

private:
	struct Record
	{
		RecordAction m_action;			/*!< record action*/
		ObjectUID m_objectId;			/*!< object id concerned*/
		ObjectUID m_ownerObject;		/*!< object id od owner*/
		ObjectDefWPtr m_objectDef;		/*!< definition of concerned object*/
		size_t m_offset;				/*!< data offset in undeo buffer*/
	};

	std::mutex m_readWriteMutex;
	UndoRedoTimePoint m_timePoint;									/*!< time of undo session*/
	MCadBinaryBufferPtr m_pBinBuffer;								/*!< saving buffer*/
	std::list<Record> m_lUndoRecord;								/*!< list of undo record*/
	std::list<Record> m_lRedoRecord;								/*!< list of redo record*/
	MCadInputBinStream m_inputStream;								/*!< input stream*/
	MCadOutputBinStream m_outputStream;								/*!< output stream*/

	// keep objects during restore
	/*@brief undo records*/
	void undo(ObjectMap& a_realocMap, const Record& a_record);
	/*@brief redo record*/
	void redo(ObjectMap& a_realocMap, const Record& a_record);

public:
	MCadRecordSession();
	virtual ~MCadRecordSession() = default;
	void startSession();
	[[nodiscard]] UndoRedoTimePoint timepoint()const noexcept { return m_timePoint; }
	void record(const MCadObject* a_pUndoObject, const RecordAction a_action);
	/*@brief undo records*/
	void undo();
	/*@brief redo record*/
	void redo();
	/*@brief undo filtered records*/
	void undoFiltered(UndoRedoFilter a_filter);
	/*@brief redo filtered records*/
	void redoFiltered(UndoRedoFilter a_filter);
};


class MCadUndoRedo
{
private:
	bool m_active = true;										/*!< undo redo activation*/
	bool m_sessionActive = false;								/*!< flag indicating an active session*/
	std::deque<MCadRecordSession> m_sessionList;				/*!< list of undoredo session*/
	/**/
	std::deque<MCadRecordSession>::iterator m_currentSession;	/*!< iterator on current session*/
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