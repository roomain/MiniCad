#pragma once
/***********************************************
* @headerfile MCadObject.h
* @date 16 / 07 / 2023
* @author Roomain
************************************************/
#include <atomic>
#include "RTTIDefinition_macros.h"
#include "IMCadObjectReactor.h"
#include "MCadReactive.h"
#include "MCad_Core_globals.h"
#include "defines.h"
#include "MCadMemory.h"
#include "MCadRef.h"

class MCadDocument;
class MCadObject;
class IMCadInputStream;
class IMCadOutputStream;




#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)

/*@brief base MCad object*/
class MCAD_CORE_EXPORT MCadObject : public MCadRefObject, public MCadReactive<IMCadObjectReactor>,
	public MCadShared_from_this<MCadObject>
{
	DECLARE_RTTI_DERIVED(1, MCadObject, MCadReactive<IMCadObjectReactor>)
private:
	std::atomic_bool m_bErased = false;				/*!< erased flag (object is no more usable)*/
	std::weak_ptr<MCadDocument> m_pDoc;				/*!< document container*/
	ObjectUID m_ObjectUID;							/*!< unique object identifier*/

protected:
	static std::atomic_bool m_sEnableUIDGen;	/*!< enable identifier generator*/
	static std::atomic_ullong m_UIDGen;			/*!< unique identifier generator*/


	/*@brief is uid generator enabled*/
	static bool isUIDGeneratorEnabled() { return m_sEnableUIDGen; }
	/*@brief enabling uid genrator*/
	static void enableUIDGenerator(bool a_bEnable) { m_sEnableUIDGen = a_bEnable; }

	void setUID(const ObjectUID& a_uid) { m_ObjectUID = a_uid; }

public:
	MCadObject();
	virtual ~MCadObject() = default;
	inline std::weak_ptr<MCadDocument> document()const noexcept { return m_pDoc; }
		
	/*@brief get object uid*/
	constexpr ObjectUID uid()const noexcept { return m_ObjectUID; }
	/*
	* @brief load object from stream
	* @return version number of object
	*/
	virtual unsigned short load(IMCadInputStream& a_stream) = 0;

	/*@brief save object to stream*/
	virtual bool save(IMCadOutputStream& a_stream)const = 0;

	/*@brief set erase flag */
	void erase();
	/*@return flag is erased*/
	inline bool isErased()const noexcept { return m_bErased; }
	
};
#pragma warning(pop)
