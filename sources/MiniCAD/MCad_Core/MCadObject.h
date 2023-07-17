#pragma once
/***********************************************
* @headerfile MCadObject.h
* @date 16 / 07 / 2023
* @author Roomain
************************************************/
#include <memory>
#include <atomic>
#include "RTTIDefinition_macros.h"
#include "IMCadObjectReactor.h"
#include "MCad_Core_globals.h"

class MCadDocument;
class MCadObject;
class IMCadInputStream;
class IMCadOutputStream;

using MCadObjectPtr = std::shared_ptr<MCadObject>;
using MCadObjectWPtr = std::weak_ptr<MCadObject>;

using ObjectUID = unsigned long long;

/*@brief base MCad object*/
class MCAD_CORE_EXPORT MCadObject : public std::enable_shared_from_this<MCadObject>
{
	DECLARE_RTTI(1, MCadObject)
private:
	std::atomic_bool m_bErased = false;				/*!< erased flag (object is no more usable)*/
	std::weak_ptr<MCadDocument> m_pDoc;				/*!< document container*/
	ObjectUID m_ObjectUID;							/*!< unique object identifier*/

	std::vector<IMCadObjectReactorPtr> m_vReactors;	/*!< reactors of object*/

protected:
	MCadObjectWPtr m_pOwner;			/*!< pointer to owner*/
	static std::atomic_ullong m_UIDGen;	/*!< unique identifier generator*/

	/*@brief function calling a function of all active reactor from type*/
	template<typename ReactorType, typename Function, typename ...Args>		
	inline void foreach_reactor(Function&& a_fun, Args... arguments)
	{
		static auto filter = [](MCadReactorPtr& a_reac) {return a_reac->isKinOf<ReactorType>() && a_reac->enabled(); };
		static auto bindFun = std::bind_front(a_fun); 
		for (auto& reactor : m_vReactors | std::filter_view(filter))
			std::invoke(bindFun, reactor->cast<ReactorType>(), arguments...); 
	}

public:
	MCadObject();
	virtual ~MCadObject();
	inline std::weak_ptr<MCadDocument> document()const noexcept { return m_pDoc; }
	inline MCadObjectWPtr owner()const noexcept { return m_pOwner; }

	void add_reactor(const IMCadObjectReactorPtr& a_pReactor);

	/*@brief get object uid*/
	constexpr ObjectUID uid()const noexcept { return m_ObjectUID; }
	/*
	* @brief load object from stream
	* @return version number of object
	*/
	virtual unsigned short load(IMCadInputStream& a_stream) = 0;

	/*@brief save object to stream*/
	virtual bool save(IMCadOutputStream& a_stream)const = 0;

	/*@brief set erase fag */
	void erase();
	/*@return flag is erased*/
	constexpr bool isErased()const noexcept { return m_bErased; }
	/*@brief check if its a shared pointer*/
	inline bool isShared()noexcept { return weak_from_this().use_count() > 0; }
};

