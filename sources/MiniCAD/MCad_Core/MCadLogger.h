#pragma once
/***********************************************
* @headerfile MCadLogger.h
* @date 13 / 08 / 2023
* @author Roomain
************************************************/
#include <string>
#include <string_view>
#include <functional>
#include <memory>
#include <source_location>
#include "MCad_Core_globals.h"

#pragma warning(push)
#pragma warning(disable : 4251)

/*@brief log mode*/
enum class LogMode
{
	LOG_INFO,
	LOG_SUCCESS,
	LOG_WARNING,
	LOG_ERROR,
	LOG_CRITICAL
};

using Log_text = std::function<void(const LogMode& a_mode, const std::string&)>;
using Log_text_view = std::function<void(const LogMode& a_mode, const std::string_view&)>;
using Log_int = std::function<void(const LogMode& a_mode, const int)>;
using Log_float = std::function<void(const LogMode& a_mode, const float)>;
using Log_double = std::function<void(const LogMode& a_mode, const double&)>;
using Log_bool = std::function<void(const LogMode& a_mode, const bool)>;
using Log_location = std::function<void(const LogMode& a_mode, std::source_location&&)>;

struct InteralLogger
{
	Log_text m_log_text = nullptr;
	Log_text_view m_log_text_view = nullptr;
	Log_int m_log_int = nullptr;
	Log_float m_log_float = nullptr;
	Log_double m_log_double = nullptr;
	Log_bool m_log_bool = nullptr;
	Log_location m_log_location = nullptr;
};

using InternalLoggerPtr = std::shared_ptr<InteralLogger>;



/*@brief singleton interface for log*/
class MCAD_CORE_EXPORT MCadLogger
{
private:
	bool m_bEnable = true;					/*!< log is enable*/
	LogMode m_mode = LogMode::LOG_INFO;		/*!< display mode*/
	InternalLoggerPtr m_internal;			/*!< intenal log callbacks*/

	MCadLogger() = default;
public:
	MCadLogger(const MCadLogger&) = delete;
	MCadLogger(MCadLogger&&) = delete;
	MCadLogger& operator = (const MCadLogger&) = delete;
	MCadLogger& operator = (MCadLogger&&) = delete;

	~MCadLogger() = default;
	static [[nodiscard]] MCadLogger& Instance();
	void setInternal(const InternalLoggerPtr& a_internal);
	inline [[nodiscard]] bool isEnabled()const noexcept { return m_bEnable; }
	inline void enable(const bool a_bEnable) { m_bEnable = a_bEnable; }
	MCadLogger& operator << (const LogMode& a_mode);
	MCadLogger& operator << (const std::string& a_value);
	MCadLogger& operator << (const std::string_view& a_value);
	MCadLogger& operator << (const int a_value);
	MCadLogger& operator << (const float a_value);
	MCadLogger& operator << (const double& a_value);
	MCadLogger& operator << (const bool a_value);
	MCadLogger& operator << (std::source_location&& a_value);
};

#pragma warning(pop)