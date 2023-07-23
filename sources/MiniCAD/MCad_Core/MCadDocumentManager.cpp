#include "pch.h"
#include "IMCadDocManagerReactor.h"


MCadDocumentManager& MCadDocumentManager::Instance()
{
	static MCadDocumentManager s_instance;
	return s_instance;
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