#include "pch.h"
#include <algorithm>
#include "ProtocolExtension.h"


void RTTIDefinition::registerToDocument(const MCadShared_ptr<MCadObject> a_object)
{
	MCadDocument::registerObject(a_object);
}

RTTIDefinition::RTTIDefinition(const std::string_view& a_name, const unsigned short a_version) :
	m_defVersion{ a_version }, m_className{ a_name } {}

RTTIDefinition::RTTIDefinition(const std::string_view& a_name, const unsigned short a_version,
	const std::vector<std::shared_ptr<RTTIDefinition>>& a_vParents) :
	m_defVersion{ a_version }, m_className{ a_name }, m_vParent{ a_vParents } {}

bool RTTIDefinition::isKindOf(const std::shared_ptr<RTTIDefinition>& pDef)const noexcept
{
	bool bIsKindOf = isSame(pDef);
	if (!bIsKindOf)
		bIsKindOf = inheritFrom(pDef);
	return bIsKindOf;
}

void RTTIDefinition::registerProtocolExt(const std::shared_ptr<ProtocolExtension>& a_protocol)
{
	if (a_protocol)
	{
		std::erase_if(m_vExtensions, [&a_protocol](const auto& curProt)
			{
				return curProt->isKindOf(a_protocol->isA()) || a_protocol->isKindOf(curProt->isA());
			});

		m_vExtensions.emplace_back(a_protocol);
	}
}

bool RTTIDefinition::unregisterProtocolExt(const std::shared_ptr<RTTIDefinition>& a_pDef)
{
	return m_vExtensions.size() != std::erase_if(m_vExtensions, [&a_pDef](const auto& curProt)
		{
			return curProt->isKindOf(a_pDef);
		});
}

std::shared_ptr<ProtocolExtension> RTTIDefinition::getProtocolExt(const std::shared_ptr<RTTIDefinition>& a_pDef)const
{
	MCadShared_ptr<ProtocolExtension> pProtocolExt;
	auto iter = std::ranges::find_if(m_vExtensions, [&a_pDef ](auto a_pExt) {return a_pExt->isKindOf(a_pDef); });
	if (iter != m_vExtensions.end())
	{
		pProtocolExt = *iter;
	}
	else
	{
		for (const auto& pCurProtocol : m_vParent)
		{
			pProtocolExt = pCurProtocol->getProtocolExt(a_pDef);
			if (pProtocolExt)
				break;
		}
	}
	return pProtocolExt;
}

