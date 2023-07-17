#include "pch.h"

std::atomic_ullong MCadObject::m_UIDGen = 0;

MCadObject::MCadObject() : m_pDoc{ MCadDocumentManager::Instance().currentDocument() }, m_ObjectUID{ ++MCadObject::m_UIDGen }
{
	//
}

MCadObject::~MCadObject()
{
	//
}

void MCadObject::erase()
{
	m_bErased = true;
}