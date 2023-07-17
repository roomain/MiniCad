#include "pch.h"

MCadDocumentManager& MCadDocumentManager::Instance()
{
	static MCadDocumentManager s_instance;
	return s_instance;
}

MCadDocumentWPtr MCadDocumentManager::currentDocument()
{
	//
}

size_t MCadDocumentManager::count()const noexcept
{
	//
}

void MCadDocumentManager::setCurrentDocument(const MCadDocumentPtr& pDoc)
{
	//
}

MCadDocumentManager::MCadDocumentIter MCadDocumentManager::begin()
{
	//
}

MCadDocumentManager::MCadDocumentIter MCadDocumentManager::end()
{
	//
}

MCadDocumentManager::MCadDocumentConst_Iter MCadDocumentManager::cbegin()
{
	//
}

MCadDocumentManager::MCadDocumentConst_Iter MCadDocumentManager::cend()
{
	//
}
