#include "pch.h"

MCadDocumentManager& MCadDocumentManager::Instance()
{
	static MCadDocumentManager s_instance;
	return s_instance;
}

MCadDocumentWPtr MCadDocumentManager::currentDocument()
{
	return m_pCurrentDocument;
}

size_t MCadDocumentManager::count()const noexcept
{
	return m_vDocument.size();
}

void MCadDocumentManager::setCurrentDocument(const MCadDocumentPtr& a_pDoc)
{
	m_pCurrentDocument = a_pDoc;
	// TODO
}