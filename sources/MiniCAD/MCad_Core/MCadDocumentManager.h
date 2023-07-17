#pragma once
/***********************************************
* @headerfile MCadDocumentManager.h
* @date 16 / 07 / 2023
* @author Roomain
************************************************/
#include <vector>
#include <memory>

class MCadDocumentManagetReactor;
using MCadDocumentManagetReactorPtr = std::shared_ptr<MCadDocumentManagetReactor>;

class MCadDocument;
using MCadDocumentPtr = std::shared_ptr<MCadDocument>;
using MCadDocumentWPtr = std::weak_ptr<MCadDocument>;


/*@brief Manage opened documents*/
class MCadDocumentManager
{
private:
	std::vector<MCadDocumentPtr> m_vDocument;	/*!< opened documents*/
	MCadDocumentWPtr m_pCurrentDocument;		/*!< current document*/
	
	MCadDocumentManager() = default;

public:
	~MCadDocumentManager() = default;
	MCadDocumentManager(const MCadDocumentManager&) = delete;
	MCadDocumentManager(MCadDocumentManager&&) = delete;
	MCadDocumentManager& operator = (const MCadDocumentManager&) = delete;
	MCadDocumentManager& operator = (MCadDocumentManager&&) = delete;

	static [[nodiscard]] MCadDocumentManager& Instance();
	[[nodiscard]] MCadDocumentWPtr currentDocument();
	[[nodiscard]] size_t count()const noexcept;
	void setCurrentDocument(const MCadDocumentPtr& a_pDoc);
	using MCadDocumentIter = std::vector<MCadDocumentPtr>::iterator;
	[[nodiscard]] MCadDocumentIter begin();
	[[nodiscard]] MCadDocumentIter end();

	using MCadDocumentConst_Iter = std::vector<MCadDocumentPtr>::const_iterator;
	[[nodiscard]] MCadDocumentConst_Iter cbegin();
	[[nodiscard]] MCadDocumentConst_Iter cend();
};

