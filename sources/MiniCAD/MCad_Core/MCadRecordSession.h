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
#include "IMCadContainer.h"
#include "IMCadMap.h"

using SessionTimePoint = std::chrono::time_point<std::chrono::system_clock>;

/*
* Have a realoc global map for undoredo => ex: modify > delete => modifcation need recreated pointer 
*/

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
	[[nodiscard]] size_t size()const noexcept { return m_lRecordUndo.size() + m_lRecordRedo.size(); }
	void undo(std::unordered_map<ObjectUID, MCadObject*>& a_realocmap);
	void redo(std::unordered_map<ObjectUID, MCadObject*>& a_realocmap);
	void undo(std::unordered_map<ObjectUID, MCadObject*>& a_realocmap, IMCadRecord::RecordFilter& a_filterFun);
	void redo(std::unordered_map<ObjectUID, MCadObject*>& a_realocmap, IMCadRecord::RecordFilter& a_filterFun);

	void record(MCadObject* a_pObject, IMCadRecord::RecordAction a_action);

	template<typename Contained>
	void record(IMCadContainer<Contained>* a_pObject, IMCadRecord::RecordAction a_action)
	{
		// find object record
		auto iter = std::ranges::find_if(m_lRecordUndo, [a_pObject](const auto& a_record)
			{
				return a_pObject->uid() == a_record->objectUID();
			});

		//
	}

	template<typename Contained>
	void record(IMCadMap<Contained>* a_pObject, IMCadRecord::RecordAction a_action)
	{
		// find object record
		auto iter = std::ranges::find_if(m_lRecordUndo, [a_pObject](const auto& a_record)
			{
				return a_pObject->uid() == a_record->objectUID();
			});

		//
	}

	/*template<typename RecordObject, typename Record, typename ...Args> requires std::is_base_of_v<IMCadRecord, Record>
	void record(std::unordered_map<ObjectUID, MCadObject*>& a_realocmap, IMCadRecord::RecordAction a_action, RecordObject* const a_object, Args... a_arguments)
	{
		// find object record
		auto iter = std::ranges::find_if(m_lUndoRecord, [a_object](const auto& a_record)
			{
				return a_object->uid() == a_record.m_objectId;
			});

		bool bSaveRecord = true;

		// if record already exists for object
		if (iter != m_lUndoRecord.end())
		{
			bSaveRecord = iter->recordAction() != a_action;
			switch (a_action)
			{
			case IMCadRecord::RecordAction::Record_delete:
				bSaveRecord = iter->recordAction() == IMCadRecord::RecordAction::Record_create;
				break;

			default:
				break;
			}
		}
		
		if (m_outputStream.hasBuffer() && bSaveRecord)
		{
			//m_lRecordUndo.emplace_front(std::make_unique<Record>(a_action, a_object->uid(), m_outputStream, a_arguments));
		}
	}*/
};
