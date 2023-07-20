#include "pch.h"
#include <filesystem>


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
