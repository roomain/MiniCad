#pragma once
/***********************************************
* @headerfile MCadUndoRedo.h
* @date 22 / 07 / 2023
* @author Roomain
************************************************/
#include <chrono>
#include <map>
#include <deque>
#include <functional>
#include <mutex> // for concurent undo buffer writing

#include "MCadRecordSession.h"

using ObjectMap = std::unordered_map< ObjectUID, MCadObjectPtr>;
using UndoRedoTimePoint = std::chrono::time_point<std::chrono::system_clock>;
using ObjectDefWPtr = std::weak_ptr<RTTIDefinition>;




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