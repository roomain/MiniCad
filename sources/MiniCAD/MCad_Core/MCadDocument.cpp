#include "pch.h"
#include <filesystem>
#include "MCadObject.h"

void MCadDocument::registerObject(const MCadObjectPtr& a_pObject)
{
	a_pObject->document().lock()->m_objectDatabase.emplace(a_pObject->uid(), a_pObject->objectUID());
}

void MCadDocument::unregisterObject(MCadDocument* const a_document, const ObjectUID& a_uid)
{
	auto iter = a_document->m_objectDatabase.find(a_uid);
	if(iter != a_document->m_objectDatabase.end())
		a_document->m_objectDatabase.erase(iter);
}

std::string MCadDocument::fullpath()const noexcept
{
	return m_sFilePath;
}

std::string MCadDocument::filePath()const noexcept
{
	std::filesystem::path path(m_sFilePath);
	return path.parent_path().string();
}

std::string MCadDocument::filename()const noexcept
{
	std::filesystem::path path(m_sFilePath);
	return path.filename().string();
}

std::string MCadDocument::fileExtension()const noexcept
{
	std::filesystem::path path(m_sFilePath);
	return path.extension().string();
}

MCadObjectUID MCadDocument::getObject(const ObjectUID& a_uid)const
{
	return m_objectDatabase.at(a_uid);
}