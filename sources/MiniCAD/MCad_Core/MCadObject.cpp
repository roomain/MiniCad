#include "pch.h"

std::atomic_bool MCadObject::m_sEnableUIDGen = true;
std::atomic_ullong MCadObject::m_UIDGen = 0;

MCadObject::MCadObject()
{
	m_ObjectUID = m_sEnableUIDGen ? ++MCadObject::m_UIDGen : 0;
	m_pDoc = MCadDocumentManager::Instance().currentDocument();
}

MCadObject::~MCadObject()
{
	assertDeletetion();

	// remove from owner
	for (const auto pReact : m_vReactors)
		pReact->onObjectDeleted(this);
}


void MCadObject::erase()
{
	m_bErased = true;
	for (const auto pReact : m_vReactors)
		pReact->onObjectErased(this);
}


void MCadObject::assertModification()
{
	if (auto pDoc = document().lock())
		pDoc->undoRedo().currentSession().record(this, IMCadRecord::RecordAction::Record_modify);
}

void MCadObject::assertDeletetion()
{
	if (auto pDoc = document().lock())
		pDoc->undoRedo().currentSession().record(this, IMCadRecord::RecordAction::Record_delete);

}
