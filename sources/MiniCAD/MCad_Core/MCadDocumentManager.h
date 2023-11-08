#pragma once
/***********************************************
* @headerfile MCadDocumentManager.h
* @date 16 / 07 / 2023
* @author Roomain
************************************************/
#include <vector>
#include <memory>
#include "MCadReactive.h"

#include "MCadSingletonMacro.h"
#include "MCad_Core_globals.h"



class MCadDocument;

class IMCadDocManagerReactor;


#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)

/*@brief Manage opened documents*/
class MCAD_CORE_EXPORT MCadDocumentManager : public MCadReactive<IMCadDocManagerReactor>
{
	DECLARE_RTTI_DERIVED(1, MCadDocumentManager, MCadReactive<IMCadDocManagerReactor>)

	NOT_COPIABLE(MCadDocumentManager)
private:

	std::vector<std::shared_ptr<MCadDocument>> m_vDocument;		/*!< opened documents*/
	std::weak_ptr<MCadDocument> m_pCurrentDocument;				/*!< current document*/
	
	MCadDocumentManager() = default;

public:
	virtual ~MCadDocumentManager() = default;

	/*@brief document manager instance*/
	static [[nodiscard]] MCadDocumentManager& Instance();

	[[nodiscard]] std::shared_ptr<MCadDocument> createDocument();

	/*@brief current document*/
	[[nodiscard]] std::weak_ptr<MCadDocument> currentDocument();

	/*@brief number of documents*/
	[[nodiscard]] size_t count()const noexcept;

	/*@brief set document as current*/
	void setCurrentDocument(const std::shared_ptr<MCadDocument>& a_pDoc);

	void closeDocument(const std::shared_ptr<MCadDocument>& a_pDoc);
	void closeAllDocument();

	/*@brief iterator on opened documents*/
	using MCadDocumentIter = std::vector<std::shared_ptr<MCadDocument>>::iterator;
	[[nodiscard]] constexpr MCadDocumentIter begin() { return m_vDocument.begin(); }
	[[nodiscard]] constexpr MCadDocumentIter end() {return m_vDocument.end();	}

	using MCadDocumentConst_Iter = std::vector<std::shared_ptr<MCadDocument>>::const_iterator;
	[[nodiscard]] MCadDocumentConst_Iter cbegin()const { return m_vDocument.cbegin(); }
	[[nodiscard]] MCadDocumentConst_Iter cend()const { return m_vDocument.cend(); }

};

#pragma warning(pop)