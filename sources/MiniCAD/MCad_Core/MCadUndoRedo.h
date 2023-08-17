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
#include <optional>
#include <mutex> // for concurent undo buffer writing
#include "MCadRecordSession.h"
#include "MCad_Core_globals.h"

#pragma warning(push)
#pragma warning(disable : 4251)

using ObjectRealocMap = std::unordered_map< ObjectUID, MCadObjectPtr>;
using UndoRedoTimePoint = std::chrono::time_point<std::chrono::system_clock>;
using ObjectDefWPtr = std::weak_ptr<RTTIDefinition>;

using SessionList = std::deque<MCadRecordSession>;

using SessionIterator = std::optional< SessionList::iterator>;


class MCAD_CORE_EXPORT MCadUndoRedo
{
private:
	bool m_active = true;					/*!< undo redo activation*/
	bool m_sessionActive = false;			/*!< flag indicating an active session*/
	SessionList m_sessionList;				/*!< list of undoredo session*/
	ObjectNextRealocMap m_realocationMap;	/*!< undeo redo level of realocation map*/
	SessionIterator m_SessionUndo;			/*!< iterator on undo session*/
	SessionIterator m_SessionRedo;			/*!< iterator on redo session*/
public:
	MCadUndoRedo(const MCadUndoRedo&) = delete;
	MCadUndoRedo();
	virtual ~MCadUndoRedo();
	void enableUndo(const bool a_enable) { m_active = a_enable; }
	[[nodiscard]] bool undoEnabled()const noexcept { return m_active; }
	/*@brief start undo recording (automatically enable)*/
	void startUndoRecord(const std::string& a_title);
	/*@brief end endo record, flush to undo file*/
	void endUndoRecord();
	/*@brief cancel current*/
	void cancel();
	/*@brief redo*/
	void redo();
	/*@brief undo*/
	void undo();

	[[nodiscard]] bool active()const noexcept { return m_active && m_sessionActive; }

	/*@brief is undo possible*/
	bool hasUndo()const noexcept;
	/*@brief is redo possible*/
	bool hasRedo()const noexcept;
	MCadRecordSession& currentSession()const
	{
		if(m_SessionUndo.has_value())
			return *m_SessionUndo.value();
		throw;// TODO
	}

	/*@brief clear all sessions*/
	void clear();
};

#pragma warning(pop)