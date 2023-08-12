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
#include "MCadReactive.h"
#include "MCad_Core_globals.h"

class MCadDocument;
class MCadObject;
class IMCadInputStream;
class IMCadOutputStream;
class MCadRecordObject;

using MCadObjectPtr = std::shared_ptr<MCadObject>;
using MCadObjectWPtr = std::weak_ptr<MCadObject>;


using const_MCadObjectPtr = std::shared_ptr<const MCadObject>;
using const_MCadObjectWPtr = std::weak_ptr<const MCadObject>;

using ObjectUID = unsigned long long;


#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)

/*@brief base MCad object*/
class MCAD_CORE_EXPORT MCadObject : public MCadReactive<IMCadObjectReactor>, public std::enable_shared_from_this<MCadObject>
{
	DECLARE_RTTI_DERIVED(1, MCadObject, MCadReactive<IMCadObjectReactor>)
		friend MCadRecordObject;
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

	/*@brief assertion for undo/redo: create record*/
	virtual void assertModification();
	virtual void assertDeletetion();

public:
	MCadObject();
	virtual ~MCadObject();
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
	/*@brief check if its a shared pointer*/
	inline bool isShared()noexcept { return weak_from_this().use_count() > 0; }
};
#pragma warning(pop)
