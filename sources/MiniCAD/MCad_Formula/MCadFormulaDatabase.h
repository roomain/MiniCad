#pragma once
/***********************************************
* @headerfile MCadFormulaDatabase.h
* @date 08 / 11 / 2023
* @author Roomain
************************************************/
#include <unordered_map>
#include <string>
#include "MCadValue.h"
#include "MCadSingletonMacro.h"
#include "MCad_Formula_globals.h"

#pragma warning(push)
#pragma warning(disable : 4251)

/*@brief database of variable used for formula and formula*/
class MCAD_FORMULA_EXPORT MCadFormulaDatabase
{
	NOT_COPIABLE(MCadFormulaDatabase)
private:
	MCadFormulaDatabase( );

	std::unordered_map<std::string, MCadValue> m_variables;	/*!< formula variables*/
	std::unordered_map<std::string, std::string> m_formulas;	/*!< saved formula*/

	[[nodiscard]] bool formatName(const std::string& a_name, std::string& a_formatted)const;

public:
	/*@brief builtin variables*/
	static constexpr std::string USER_ORIGIN{ "USER_ORIGIN" };	/*!< current user origin*/
	static constexpr std::string USER_XAXIS{ "USER_XAXIS" };	/*!< current user x axis*/
	static constexpr std::string USER_YAXIS{ "USER_YAXIS" };	/*!< current user y axis*/
	static constexpr std::string USER_ZAXIS{ "USER_ZAXIS" };	/*!< current user z axis*/
	static constexpr std::string PI{ "PI" };					/*!< PI value*/

	~MCadFormulaDatabase( );
	static [[nodiscard]] MCadFormulaDatabase& Instance( );
	[[nodiscard]] bool hasVariable(const std::string& a_name)const;
	[[nodiscard]] MCadValue getVariableValue(const std::string& a_name)const;

	[[nodiscard]] bool renameVariable(const std::string& a_oldName, const std::string& a_newName);
	[[nodiscard]] bool newVariable(const std::string& a_name, const MCadValue& a_value);
	[[nodiscard]] bool removeVariable(const std::string& a_name);

	[[nodiscard]] bool hasFormula(const std::string& a_name)const;
	[[nodiscard]] std::string getFormula(const std::string& a_name)const;

	[[nodiscard]] bool renameFormula(const std::string& a_oldName, const std::string& a_newName);
	[[nodiscard]] bool newFormula(const std::string& a_name, const MCadValue& a_value);
	[[nodiscard]] bool removeFormula(const std::string& a_name);

};
#pragma warning(pop)