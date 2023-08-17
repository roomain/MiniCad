#include "pch.h"
#include "IMCadDocManagerReactor.h"


MCadDocumentManager& MCadDocumentManager::Instance()
{
	static MCadDocumentManager s_instance;
	return s_instance;
}

std::shared_ptr<MCadDocument> MCadDocumentManager::createDocument()
{
	auto pDoc = std::make_shared<MCadDocument>();
	for (auto& pReac : m_vReactors)
		pReac->onNewDocument(pDoc.get());
	m_vDocument.push_back(pDoc);
	setCurrentDocument(pDoc);
	return pDoc;
}

std::weak_ptr<MCadDocument> MCadDocumentManager::currentDocument()
{
	return m_pCurrentDocument;
}

size_t MCadDocumentManager::count()const noexcept
{
	return m_vDocument.size();
}

void MCadDocumentManager::setCurrentDocument(const std::shared_ptr<MCadDocument>& a_pDoc)
{
	m_pCurrentDocument = a_pDoc;
	for (auto& pReac : m_vReactors)
		pReac->onCurrentDocument(a_pDoc.get());
}

void MCadDocumentManager::closeDocument(const std::shared_ptr<MCadDocument>& a_pDoc)
{
	auto iter = std::find(m_vDocument.begin(), m_vDocument.end(), a_pDoc);
	if (iter != m_vDocument.end())
		m_vDocument.erase(iter);
}

void MCadDocumentManager::closeAllDocument()
{
	m_vDocument.clear();
}