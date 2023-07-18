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

void MCadDocumentManager::add_reactor(const MCadDocManagerReactorPtr& a_pReactor)
{
	m_vReactors.emplace_back(a_pReactor);
}

void MCadDocumentManager::remove_reactor(const MCadDocManagerReactorPtr& a_pReactor)
{
	std::remove(m_vReactors.begin(), m_vReactors.end(), a_pReactor);
}

size_t MCadDocumentManager::count_reactor()const
{
	return m_vReactors.size();
}

void MCadDocumentManager::remove_allReactor()
{
	m_vReactors.clear();
}

