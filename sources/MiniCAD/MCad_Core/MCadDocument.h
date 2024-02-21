#pragma once
/***********************************************
* @headerfile MCadDocument.h
* @date 19 / 07 / 2023
* @author Roomain
************************************************/
#include <vector>
#include <map>
#include "TMCadReactive.h"
#include "MCadUndoRedo.h"
#include "MCadMemory.h"
#include "MCadObjectUID.h"
#include "MCad_Core_globals.h"

class MCadObject;
class IMCadDocumentReactor;
class IMCadFileInputStream;
class IMCadFileOutputStream;

using MCadObjectWPtr = std::weak_ptr<MCadObject>;
using MCadObjectPtr = MCadShared_ptr<MCadObject>;

#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)

/*@brief base class for document*/
class MCAD_CORE_EXPORT MCadDocument : public TMCadReactive<IMCadDocumentReactor>
{
	friend class RTTIDefinition;
	DECLARE_RTTI_DERIVED(1, MCadDocument, TMCadReactive<IMCadDocumentReactor>)
private:
	std::string	m_sFilePath;												/*!< file path of document*/
	UndoRedo::MCadUndoRedo m_undoRedo;										/*!< tool of undo redo*/
	std::unordered_map<ObjectUID, MCadObjectUID> m_objectDatabase;

	static void registerObject(const MCadObjectPtr& a_pObject);
	static void unregisterObject(MCadDocument* const a_document, const ObjectUID& a_uid);

public:
	MCadDocument() = default;
	virtual ~MCadDocument() = default;

	/*@brief return document file full path*/
	std::string fullpath()const noexcept;

	/*@brief return the path of document file*/
	std::string filePath()const noexcept;

	/*@brief return the filename of document*/
	std::string filename()const noexcept;

	/*@brief return the extension of document file (without dot)*/
	std::string fileExtension()const noexcept;

	UndoRedo::MCadUndoRedo& undoRedo() { return m_undoRedo; }

	MCadObjectUID getObject(const ObjectUID& a_uid)const;

};

using MCadDocumentPtr = std::shared_ptr<MCadDocument>;
#pragma warning(pop)