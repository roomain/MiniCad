#include "pch.h"
#include "MCadInputs.h"
#include "MCadStringTools.h"

void MCadInputs::init_internal(const std::string& a_cmdArgs, MCadArgList& a_arg)
{
	split(a_cmdArgs, ' ', a_arg);
	std::vector<int> vIndexToDelete;
	int index = 0;
	int iCounter = 0;
	int iStartIndex = -1;
	bool bToRemove = false;
	for ( const auto& arg : a_arg )
	{
		if ( arg.starts_with('\"') )
			++iCounter;

		if ( arg.ends_with('\"') )
			--iCounter;

		if ( bToRemove )
		{
			vIndexToDelete.emplace_back(index);
			a_arg [ iStartIndex ] += " " + arg;
			if ( 0 == iCounter )
				bToRemove = false;
		}
		else if ( iCounter == 1 )
		{
			bToRemove = true;
			iStartIndex = index;
		}

		++index;
	}

	int offset = 0;
	for ( const int delIndex : vIndexToDelete )
	{
		a_arg.erase(a_arg.begin( ) + delIndex + offset);
		offset--;
	}
}

MCadInputs::MCadInputs(const std::string& a_cmdArgs)
{
	init_internal(a_cmdArgs, m_argList);
}


void MCadInputs::init(const std::string& a_cmdArgs)
{
	init_internal(a_cmdArgs, m_argList);
}