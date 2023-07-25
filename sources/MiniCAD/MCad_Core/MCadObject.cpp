#include "pch.h"

std::atomic_ullong MCadObject::m_UIDGen = 0;

MCadObject::MCadObject()
{
	m_ObjectUID = ++MCadObject::m_UIDGen;
	m_pDoc = MCadDocumentManager::Instance().currentDocument();
}

MCadObject::~MCadObject()
{
	// remove from owner
	auto pOwner = m_pOwner.lock();
	if (pOwner)
		pOwner->onChildDelete(this);

	for (const auto pReact : m_vReactors)
		pReact->onObjectDeleted(this);
}


void MCadObject::erase()
{
	// TODO UNDO
	m_bErased = true;
	for (const auto pReact : m_vReactors)
		pReact->onObjectErased(this);
}