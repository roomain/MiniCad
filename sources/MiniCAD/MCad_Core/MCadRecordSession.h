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
#include "MCadInputBinStream.h"
#include "MCadOutputBinStream.h"

#pragma warning(push)
#pragma warning(disable : 4251)

using SessionTimePoint = std::chrono::time_point<std::chrono::system_clock>;


/*@brief represents all object modification for during a command*/
class MCAD_CORE_EXPORT MCadRecordSession
{
private:
	std::list<IMCadRecordPtr> m_lRecords;		/*!< records for undo*/
	SessionTimePoint m_timePoint;				/*!< time of undo session*/
	std::string m_title;						/*!< session title*/
	MCadBinaryBufferPtr m_pBinBuffer;			/*!< saving buffer*/
	mutable MCadInputBinStream m_inputStream;	/*!< input stream*/
	mutable MCadOutputBinStream m_outputStream;	/*!< output stream*/

	/*@brief compact records*/
	void compact();

public:
	MCadRecordSession(const std::string& a_title);
	virtual ~MCadRecordSession() = default;
	[[nodiscard]] MCadInputBinStream& inputStream( )const { return m_inputStream; }
	[[nodiscard]] MCadOutputBinStream& outputStream( )const { return m_outputStream; }
	[[nodiscard]] constexpr SessionTimePoint time()const noexcept { return m_timePoint; }
	[[nodiscard]] constexpr std::string title()const noexcept { return m_title; }
	[[nodiscard]] size_t size()const noexcept { return m_lRecords.size(); }
	void append(const IMCadRecordPtr& a_record);
	void undo(MCadReallocMemory& a_realocMemory);
	void redo(MCadReallocMemory& a_realocMemory);

};

using MCadRecordSessionPtr = std::shared_ptr<MCadRecordSession>;
using MCadRecordSessionWPtr = std::weak_ptr<MCadRecordSession>;

#pragma warning(pop)