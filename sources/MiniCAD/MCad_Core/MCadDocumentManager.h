#pragma once
/***********************************************
* @headerfile MCadDocumentManager.h
* @date 16 / 07 / 2023
* @author Roomain
************************************************/
#include <vector>
#include <memory>
#include "MCadReactive.h"
#include "MCad_Core_globals.h"



class MCadDocument;
using MCadDocumentPtr = std::shared_ptr<MCadDocument>;
using MCadDocumentWPtr = std::weak_ptr<MCadDocument>;

class MCadDocManagerReactor;


#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)

/*@brief Manage opened documents*/
class MCAD_CORE_EXPORT MCadDocumentManager : public MCadReactive<MCadDocManagerReactor>
{
	DECLARE_RTTI_DERIVED(1, MCadDocumentManager, MCadReactive<MCadDocManagerReactor>)
private:
	std::vector<MCadDocumentPtr> m_vDocument;			/*!< opened documents*/
	MCadDocumentWPtr m_pCurrentDocument;				/*!< current document*/
	
	MCadDocumentManager() = default;

public:
	~MCadDocumentManager() = default;
	MCadDocumentManager(const MCadDocumentManager&) = delete;
	MCadDocumentManager(MCadDocumentManager&&) = delete;
	MCadDocumentManager& operator = (const MCadDocumentManager&) = delete;
	MCadDocumentManager& operator = (MCadDocumentManager&&) = delete;

	/*@brief document manager instance*/
	static [[nodiscard]] MCadDocumentManager& Instance();

	/*@brief current document*/
	[[nodiscard]] MCadDocumentWPtr currentDocument();

	/*@brief number of documents*/
	[[nodiscard]] size_t count()const noexcept;

	/*@brief set document as current*/
	void setCurrentDocument(const MCadDocumentPtr& a_pDoc);

	/*@brief iterator on opened documents*/
	using MCadDocumentIter = std::vector<MCadDocumentPtr>::iterator;
	[[nodiscard]] constexpr MCadDocumentIter begin() { return m_vDocument.begin(); }
	[[nodiscard]] constexpr MCadDocumentIter end() {return m_vDocument.end();	}

	using MCadDocumentConst_Iter = std::vector<MCadDocumentPtr>::const_iterator;
	[[nodiscard]] MCadDocumentConst_Iter cbegin() { return m_vDocument.cbegin(); }
	[[nodiscard]] MCadDocumentConst_Iter cend() { return m_vDocument.cend(); }

};

#pragma warning(pop)