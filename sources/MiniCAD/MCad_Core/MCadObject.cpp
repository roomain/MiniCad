#include "pch.h"

std::atomic_ullong MCadObject::m_UIDGen = 0;

MCadObject::MCadObject()
{
	m_ObjectUID = ++MCadObject::m_UIDGen;
	m_pDoc = MCadDocumentManager::Instance().currentDocument();
}

MCadObject::~MCadObject()
{
	for (const auto pReact : m_vReactors)
		pReact->onObjectDeleted(this);
}

void MCadObject::add_reactor(const IMCadObjectReactorPtr& a_pReactor)
{
	m_vReactors.emplace_back(a_pReactor);
}

void MCadObject::remove_reactor(const IMCadObjectReactorPtr& a_pReactor)
{
	std::remove(m_vReactors.begin(), m_vReactors.end(), a_pReactor);
}

size_t MCadObject::count_reactor()const
{
	return m_vReactors.size();
}

void MCadObject::remove_allReactor()
{
	m_vReactors.clear();
}


void MCadObject::erase()
{
	// TODO UNDO
	m_bErased = true;
	for (const auto pReact : m_vReactors)
		pReact->onObjectErased(this);
}