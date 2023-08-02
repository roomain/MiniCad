#pragma once
/***********************************************
* @headerfile MCadRecordSession.h
* @date 02 / 08 / 2023
* @author Roomain
************************************************/
#include <list>
#include <chrono>
#include <string>
#include "IMCadRecord.h"

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
	//
public:
	MCadRecordSession(const std::string& a_title);
	virtual ~MCadRecordSession() = default;
	[[nodiscard]] constexpr SessionTimePoint time()const noexcept { return m_timePoint; }
	[[nodiscard]] constexpr std::string title()const noexcept { return m_title; }
	[[nodiscard]] constexpr size_t size()const noexcept { return m_lRecordUndo.size() + m_lRecordRedo.size(); }
	void undo();
	void redo();
	void undo(IMCadRecord::RecordFilter& a_filterFun);
	void redo(IMCadRecord::RecordFilter& a_filterFun);


	template<typename RecordObject, typename ...Args>
	void record(IMCadRecord::RecordAction a_action, std::weak_ptr<RecordObject>& a_object, Args... a_arguments)
	{
		// find object record
		auto iter = std::ranges::find_if(m_lUndoRecord, [a_object](const auto& a_record)
			{
				return a_object.lock()->uid() == a_record.m_objectId;
			});
		// if record already exists for object
		if (iter != m_lUndoRecord.end())
		{
			//
		}
		else if (m_outputStream.hasBuffer())
		{
			//
		}
	}
};
