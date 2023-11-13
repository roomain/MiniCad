#include "pch.h"
#include <numbers>
#include "MCadFormulaDatabase.h"
#include "MCadConfiguration.h"
#include "MCadStringTools.h"
#include "MCadFormulaRegEx.h"

MCadFormulaDatabase& MCadFormulaDatabase::Instance( )
{
	static MCadFormulaDatabase instance;
	return instance;
}

bool MCadFormulaDatabase::formatName(const std::string& a_name, std::string& a_formatted)const
{
	if ( a_name.empty( ) )
		return false;

	std::string formatted = toUpper(a_name);
	if ( formatted [ 0 ] != '$' )
		formatted = "$" + formatted;
	
	if ( std::regex_match(formatted, MCadFormulaRegEx::m_variableRegex) )
	{
		a_formatted = formatted;
		return true;
	}

	return true;
}

MCadFormulaDatabase::MCadFormulaDatabase( )
{
	// load
}

MCadFormulaDatabase::~MCadFormulaDatabase( )
{
	// save
}

bool MCadFormulaDatabase::hasVariable(const std::string& a_name)const
{
	std::string key;
	if(formatName(a_name, key))
		return m_variables.contains(key);
	return false;
}

MCadValue MCadFormulaDatabase::getVariableValue(const std::string& a_name)const
{
	MCadValue valueRet;
	std::string key;
	if ( !formatName(a_name, key) )
		return valueRet;

	if ( key.compare(MCadFormulaDatabase::USER_ORIGIN) == 0)
	{
		valueRet = convert(MCadConfiguration::Instance( ).USER_ORIGIN.value());
	}
	else if ( key.compare(MCadFormulaDatabase::USER_XAXIS) == 0 )
	{
		//
	}
	else if ( key.compare(MCadFormulaDatabase::USER_YAXIS) == 0 )
	{
		//
	}
	else if ( key.compare(MCadFormulaDatabase::USER_ZAXIS) == 0 )
	{
		//
	}
	else if ( key.compare(MCadFormulaDatabase::PI) == 0 )
	{
		valueRet = std::numbers::pi;
	}
	else if ( m_variables.contains(key) )
		valueRet = m_variables.at(key);
	return valueRet;
}

bool MCadFormulaDatabase::hasFormula(const std::string& a_name)const
{
	std::string key;
	if ( formatName(a_name, key) )
		return m_formulas.contains(key);
	return false;
}

std::string MCadFormulaDatabase::getFormula(const std::string& a_name)const
{
	std::string key;
	if ( formatName(a_name, key) )
		return "";

	if ( m_formulas.contains(key) )
		return m_formulas.at(key);

	return "";
}

bool MCadFormulaDatabase::renameVariable(const std::string& a_oldName, const std::string& a_newName)
{
	std::string oldKey;
	if ( !formatName(a_oldName, oldKey) )
		return false;

	if ( m_variables.contains(oldKey) )
	{
		std::string newKey;
		if ( !formatName(a_newName, newKey) )
			return false;

		m_variables.emplace(newKey, m_variables[ oldKey ]);
		m_variables.erase(oldKey);
	}
	return false;
}

bool MCadFormulaDatabase::newVariable(const std::string& a_name, const MCadValue& a_value)
{
	std::string key;
	if ( !formatName(a_name, key) )
		return false;

	if ( m_variables.contains(key) )
		return false;

	m_variables.emplace(key, a_value);
	return true;
}

bool MCadFormulaDatabase::removeVariable(const std::string& a_name)
{
	std::string key;
	if ( !formatName(a_name, key) )
		return false;

	if ( m_variables.contains(key) )
	{
		m_variables.erase(key);
		return true;
	}
	return false;
}

bool MCadFormulaDatabase::renameFormula(const std::string& a_oldName, const std::string& a_newName)
{
	std::string oldKey;
	if ( !formatName(a_oldName, oldKey) )
		return false;

	if ( m_formulas.contains(oldKey) )
	{
		std::string newKey;
		if ( !formatName(a_newName, newKey) )
			return false;

		m_formulas.emplace(newKey, m_formulas [ oldKey ]);
		m_formulas.erase(oldKey);
	}
	return false;
}

bool MCadFormulaDatabase::newFormula(const std::string& a_name, const MCadValue& a_value)
{
	std::string key;
	if ( !formatName(a_name, key) )
		return false;

	if ( m_formulas.contains(key) )
		return false;

	m_formulas.emplace(key, a_value);
	return true;
}

bool MCadFormulaDatabase::removeFormula(const std::string& a_name)
{
	std::string key;
	if ( !formatName(a_name, key) )
		return false;

	if ( m_formulas.contains(key) )
	{
		m_formulas.erase(key);
		return true;
	}
	return false;
}
