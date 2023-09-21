#include "pch.h"

MCadLogger& MCadLogger::Instance()
{
	static MCadLogger s_instance;
	return s_instance;
}

void MCadLogger::setInternal(const InternalLoggerPtr& a_internal)
{
	m_internal = a_internal;
}

MCadLogger& MCadLogger::operator << (const LogMode& a_mode)
{
	m_mode = a_mode;
	return *this;
}

MCadLogger& MCadLogger::operator << (const std::string& a_value)
{
	if (m_bEnable && m_internal && m_internal->m_log_text)
		m_internal->m_log_text(m_mode, a_value);
	return *this;
}

MCadLogger& MCadLogger::operator << (const std::string_view& a_value)
{
	if (m_bEnable && m_internal && m_internal->m_log_text_view)
		m_internal->m_log_text_view(m_mode, a_value);
	return *this;
}

MCadLogger& MCadLogger::operator << (const int a_value)
{
	if (m_bEnable && m_internal && m_internal->m_log_int)
		m_internal->m_log_int(m_mode, a_value);
	return *this;
}

MCadLogger& MCadLogger::operator << (const float a_value)
{
	if (m_bEnable && m_internal && m_internal->m_log_float)
		m_internal->m_log_float(m_mode, a_value);
	return *this;
}

MCadLogger& MCadLogger::operator << (const double& a_value)
{
	if (m_bEnable && m_internal && m_internal->m_log_double)
		m_internal->m_log_double(m_mode, a_value);
	return *this;
}

MCadLogger& MCadLogger::operator << (const bool a_value)
{
	if (m_bEnable && m_internal && m_internal->m_log_bool)
		m_internal->m_log_bool(m_mode, a_value);
	return *this;
}

MCadLogger& MCadLogger::operator << (std::source_location&& a_value)
{
	if (m_bEnable && m_internal && m_internal->m_log_location)
		m_internal->m_log_location(m_mode, std::move(a_value));
	return *this;
}