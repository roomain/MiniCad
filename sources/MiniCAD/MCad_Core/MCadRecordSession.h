#pragma once
/***********************************************
* @headerfile MCadRecordSession.h
* @date 02 / 08 / 2023
* @author Roomain
************************************************/
#include <list>
#include <chrono>
#include <string>
#include <type_traits>
#include "IMCadRecord.h"
#include "MCadBinaryBuffer.h"
#include "MCadRecordExtra.h"

using SessionTimePoint = std::chrono::time_point<std::chrono::system_clock>;


/*@brief represents all object modification for during a command*/
class MCadRecordSession
{
private:
	std::list<IMCadRecordUPtr> m_lRecordUndo;	/*!< records for undo*/
	std::list<IMCadRecordUPtr> m_lRecordRedo;	/*!< records for redo*/
	SessionTimePoint m_timePoint;				/*!< time of undo session*/
	std::string m_title;						/*!< session title*/
	MCadBinaryBufferPtr m_pBinBuffer;			/*!< saving buffer*/
	MCadInputBinStream m_inputStream;			/*!< input stream*/
	MCadOutputBinStream m_outputStream;			/*!< output stream*/
	std::list<ObjectUID> m_unused;				/*!< list of unsused objects*/
	/*@brief compact records*/
	void compact();

public:
	MCadRecordSession(const std::string& a_title);
	virtual ~MCadRecordSession() = default;
	[[nodiscard]] constexpr SessionTimePoint time()const noexcept { return m_timePoint; }
	[[nodiscard]] constexpr std::string title()const noexcept { return m_title; }
	[[nodiscard]] size_t size()const noexcept { return m_lRecordUndo.size() + m_lRecordRedo.size(); }
	void undo(std::unordered_map<ObjectUID, MCadObject*>& a_realocmap);
	void redo(std::unordered_map<ObjectUID, MCadObject*>& a_realocmap);
	void undo(std::unordered_map<ObjectUID, MCadObject*>& a_realocmap, IMCadRecord::RecordFilter& a_filterFun);
	void redo(std::unordered_map<ObjectUID, MCadObject*>& a_realocmap, IMCadRecord::RecordFilter& a_filterFun);

	void record(MCadObject* a_pObject, const IMCadRecord::RecordAction a_recordAction, const RecordExtra& a_data);

};
