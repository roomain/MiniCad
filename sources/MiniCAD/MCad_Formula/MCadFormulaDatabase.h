#pragma once
/***********************************************
* @headerfile MCadFormulaDatabase.h
* @date 08 / 11 / 2023
* @author Roomain
************************************************/
#include <unordered_map>
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
	std::unordered_map<std::string, std::string> m_formula;	/*!< saved formula*/

public:
	~MCadFormulaDatabase( );
	static [[nodiscard]] MCadFormulaDatabase& Instance( );

};
#pragma warning(pop)