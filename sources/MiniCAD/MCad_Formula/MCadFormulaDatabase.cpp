#include "pch.h"
#include "MCadFormulaDatabase.h"

MCadFormulaDatabase& MCadFormulaDatabase::Instance( )
{
	static MCadFormulaDatabase instance;
	return instance;
}

MCadFormulaDatabase::MCadFormulaDatabase( )
{
	// load
}

MCadFormulaDatabase::~MCadFormulaDatabase( )
{
	// save
}