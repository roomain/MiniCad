#pragma once
/***********************************************
* @headerfile MCadDocument.h
* @date 19 / 07 / 2023
* @author Roomain
************************************************/
#include <vector>
#include <memory>
#include "MCadReactive.h"
#include "MCad_Core_globals.h"

class MCadDocumentReactor;
class IMCadFileInputStream;
class IMCadFileOutputStream;


#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)

/*@brief base class for document*/
class MCadDocument : public MCadReactive<MCadDocumentReactor>
{
	DECLARE_RTTI_DERIVED(1, MCadDocument, MCadReactive<MCadDocumentReactor>)
private:
	std::string	m_sFilePath;					/*@brief file path of document*/

public:
	MCadDocument() = default;
	virtual ~MCadDocument() = default;

	/*@brief load file*/
	virtual bool load(IMCadFileInputStream& stream) = 0;

	/*@brief save file*/
	virtual bool save(IMCadFileOutputStream& stream)const = 0;

	/*@brief return document file full path*/
	std::string fullpath()const noexcept;

	/*@brief return the path of document file*/
	std::string filePath()const noexcept;

	/*@brief return the filename of document*/
	std::string filename()const noexcept;

	/*@brief return the extension of document file (without dot)*/
	std::string fileExtension()const noexcept;
};

using MCadDocumentPtr = std::shared_ptr<MCadDocument>;
#pragma warning(pop)