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
	MCadOutputBinStream* m_stream;		/*!< reference to output stream of MCadRecordSession*/
public:
	MCadRecordFactory(MCadOutputBinStream* const a_stream);
	virtual	~MCadRecordFactory() = default;
	void setup(MCadObjectWPtr a_pObject, IMCadRecord::RecordAction a_action);
	// std::visitor doesn't work with &&
	IMCadRecordPtr operator()(const IndexedItem& a_item)const;
	IMCadRecordPtr operator()(const KeyItem& a_item)const;
	IMCadRecordPtr operator()()const;

	void genRedoRecord(const MCadObjectRecord* a_pUndoRecord, std::list<IMCadRecordPtr>& a_recList) final;
	void genRedoRecord(const MCadIndexedContainerRecord* a_pUndoRecord, std::list<IMCadRecordPtr>& a_recList) final;
	void genRedoRecord(const MCadRecorDictionary* a_pUndoRecord, std::list<IMCadRecordPtr>& a_recList) final;

};

/*@brief represents all object modification for during a command*/
class  MCadRecordSession
{
private:
	std::list<IMCadRecordPtr> m_lRecordUndo;	/*!< records for undo*/
	std::list<IMCadRecordPtr> m_lRecordRedo;	/*!< records for redo*/
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
	void undo(ObjectNextRealocMap& a_realocNextMap);
	void redo(ObjectNextRealocMap& a_realocNextMap);
	void undo(ObjectNextRealocMap& a_realocNextMap, IMCadRecord::RecordFilter& a_filterFun);
	void redo(ObjectNextRealocMap& a_realocNextMap, IMCadRecord::RecordFilter& a_filterFun);
	void record(MCadObject* const a_pObject, const IMCadRecord::RecordAction a_recordAction);
	void record(MCadObject* const a_pObject, const IMCadRecord::RecordAction a_recordAction, const RecordExtra& a_data);

};

using MCadRecordSessionPtr = std::shared_ptr<MCadRecordSession>;
using MCadRecordSessionWPtr = std::weak_ptr<MCadRecordSession>;