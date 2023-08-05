#pragma once
/***********************************************
* @headerfile MCadDocument.h
* @date 19 / 07 / 2023
* @author Roomain
************************************************/
#include <vector>
#include <memory>
#include <map>
#include "MCadReactive.h"
#include "MCadUndoRedo.h"
#include "MCad_Core_globals.h"

class MCadObject;
class IMCadDocumentReactor;
class IMCadFileInputStream;
class IMCadFileOutputStream;
using MCadObjectWPtr = std::weak_ptr<MCadObject>;

#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)

/*@brief base class for document*/
class MCadDocument : public MCadReactive<IMCadDocumentReactor>
{
	DECLARE_RTTI_DERIVED(1, MCadDocument, MCadReactive<IMCadDocumentReactor>)
private:
	std::string	m_sFilePath;												/*!< file path of document*/
	MCadUndoRedo m_undoRedo;												/*!< tool of undo redo*/
	std::unordered_map<ObjectUID, MCadObjectWPtr> m_objectDatabase;

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