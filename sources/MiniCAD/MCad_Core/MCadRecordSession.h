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
#include "IMCadRecordVisitor.h"

using SessionTimePoint = std::chrono::time_point<std::chrono::system_clock>;

class MCadRecordFactory : public IMCadRecordVisitor
{
private:
	MCadObjectWPtr m_pObject;				/*!< recorded object*/
	IMCadRecord::RecordAction m_recordAction;	/*!< record action*/
	MCadOutputBinStream* const m_stream;		/*!< reference to output stream of MCadRecordSession*/
public:
	MCadRecordFactory(MCadOutputBinStream* const a_stream);
	virtual	~MCadRecordFactory() = default;
	void setup(MCadObjectWPtr a_pObject, IMCadRecord::RecordAction a_action);
	// std::visitor doesn't work with &&
	IMCadRecordUPtr operator()(const IndexedItem& a_item)const;
	IMCadRecordUPtr operator()(const KeyItem& a_item)const;
	IMCadRecordUPtr operator()()const;

	IMCadRecordUPtr genRedoRecord(const MCadRecordObject* a_pUndoRecord) final;
	IMCadRecordUPtr genRedoRecord(const MCadRecordContainer* a_pUndoRecord) final;
	IMCadRecordUPtr genRedoRecord(const MCadRecorDictionary* a_pUndoRecord) final;

};

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
	MCadRecordFactory m_recordFactory;			/*!< factory creating records*/

	/*@brief compact records*/
	void compact();
	/*@brief check if action must be recorded*/
	bool checkRecord(MCadObject* const a_pObject, const IMCadRecord::RecordAction a_recordAction)const;

public:
	MCadRecordSession(const std::string& a_title);
	virtual ~MCadRecordSession() = default;
	[[nodiscard]] constexpr SessionTimePoint time()const noexcept { return m_timePoint; }
	[[nodiscard]] constexpr std::string title()const noexcept { return m_title; }
	[[nodiscard]] size_t size()const noexcept { return m_lRecordUndo.size() + m_lRecordRedo.size(); }
	void undo(ObjectMap& a_realocmap);
	void redo(ObjectMap& a_realocmap);
	void undo(ObjectMap& a_realocmap, IMCadRecord::RecordFilter& a_filterFun);
	void redo(ObjectMap& a_realocmap, IMCadRecord::RecordFilter& a_filterFun);
	void record(MCadObject* const a_pObject, const IMCadRecord::RecordAction a_recordAction);
	void record(MCadObject* const a_pObject, const IMCadRecord::RecordAction a_recordAction, const RecordExtra& a_data);

};
