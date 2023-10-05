#pragma once
/***********************************************
* @headerfile TMCadRecordContainerCell.h
* @date 07 / 09 / 2023
* @author Roomain
************************************************/
#include <variant>
#include "MCadMemory.h"
#include "MCadRef.h"
#include "TIMCadContainer.h"
#include "IMCadRecord.h"
#include "TMCadObjectProxy.h"
#include "MCadLogger.h"

template<typename Key>
using TContainerRecordProxy = TMCadObjectProxy<TIMCadContainer<Key>>;


template<typename Key>
class TMCadRecordContainerCell : public IMCadRecord
{
protected:
	TContainerRecordProxy<Key> m_Container;		/*!< container*/
	Key m_objectKey;							/*!< contained object Key*/
	ObjectUID m_ObjectUID;						/*!< contained object unique identifier*/
	std::weak_ptr<MCadObject> m_pObject;		/*!< contained object weak pointer*/
	RTTIDefinitionWPtr m_pDef;					/*!< object definition*/

public:
	TMCadRecordContainerCell( ) = delete;
	TMCadRecordContainerCell(TIMCadContainer<Key>* const a_container,
		const Key& a_key, const std::weak_ptr<MCadObject>& a_pObject) : m_Container{ a_container },
		m_objectKey{ a_key }, m_pObject{ a_pObject }
	{
		if ( auto pSharedObj = m_pObject.lock( ) )
		{
			m_pDef = pSharedObj->isA( );
			m_ObjectUID = pSharedObj->uid( );
		}
		else
		{
			UNDO_REDO_TROW(UndoRedoException::ExceptionType::Except_Deleted)
		}
	}

	TMCadRecordContainerCell(const TContainerRecordProxy<Key>& a_container,
		const Key& a_key, const std::weak_ptr<MCadObject>& a_pObject, const ObjectUID& a_uid, RTTIDefinitionWPtr a_pDef) :
		m_Container{ a_container }, m_objectKey{ a_key }, m_pObject{ a_pObject }, m_ObjectUID{ a_uid }, m_pDef{ a_pDef }
	{
		//
	}

	explicit TMCadRecordContainerCell(const TMCadRecordContainerCell<Key>& a_other) : 
		m_Container{ a_other.m_Container },	m_objectKey{ a_other.m_objectKey }, m_pObject{ a_other.m_pObject }
	{
		//
	}

	explicit TMCadRecordContainerCell(TMCadRecordContainerCell<Key>&& a_other)noexcept :
		m_Container{ a_other.m_Container }, m_objectKey{ a_other.m_objectKey }, m_pObject{ a_other.m_pObject }
	{
		//
	}

	const ObjectUID recordedObject( )const noexcept final { return m_Container.objectUID( ); }
	RTTIDefinitionWPtr recordedObjectDefinition( )const noexcept final { return m_Container.objectDef( ); }
};

template<typename Key>
class TMCadRecordContainerCellInsert : public TMCadRecordContainerCell<Key>
{
public:
	TMCadRecordContainerCellInsert(TIMCadContainer<Key>* const a_container,
		const Key& a_key, const std::weak_ptr<MCadObject>& a_pObject) : 
		TMCadRecordContainerCell<Key>{ a_container, a_key, a_pObject }
	{
		//
	}

	TMCadRecordContainerCellInsert(const TContainerRecordProxy<Key>& a_container,
		const Key& a_key, const std::weak_ptr<MCadObject>& a_pObject, const ObjectUID& a_uid, RTTIDefinitionWPtr a_pDef) :
		TMCadRecordContainerCell<Key>{ a_container, a_key, a_pObject, a_uid, a_pDef }
	{
		//
	}

	bool hasReverse( )const noexcept { return true; }
	
	/*@brief generate reverse record*/
	std::shared_ptr<IMCadRecord> generateReverse(IMCadOutputStream& a_stream, MCadRealocMemory& a_realocMem)const final
	{
		return std::make_shared<TMCadRecordContainerCellRemoved<Key>>(this->m_Container, this->m_objectKey, this->m_pObject, this->m_ObjectUID, this->m_pDef);
	}
	
	/*@brief apply record for undo*/
	virtual void apply([[maybe_unused]] IMCadInputStream& a_stream, MCadRealocMemory& a_realocMem) final
	{
		if ( this->m_Container.realocate(a_realocMem) )
		{
			this->m_Container->do_eraseAt(this->m_objectKey);
		}
		else
		{
			UNDO_REDO_TROW(UndoRedoException::ExceptionType::Except_Deleted)
		}
	}

};

template<typename Key>
class TMCadRecordContainerCellRemoved : public TMCadRecordContainerCell<Key>
{
public:
	TMCadRecordContainerCellRemoved(TIMCadContainer<Key>* const a_container,
		const Key& a_key, const std::weak_ptr<MCadObject>& a_pObject) :
		TMCadRecordContainerCell<Key>{ a_container, a_key, a_pObject }
	{
		//
	}


	TMCadRecordContainerCellRemoved(const TContainerRecordProxy<Key>& a_container,
		const Key& a_key, const std::weak_ptr<MCadObject>& a_pObject, const ObjectUID& a_uid, RTTIDefinitionWPtr a_pDef) :
		TMCadRecordContainerCell<Key>{ a_container, a_key, a_pObject, a_uid, a_pDef }
	{
		//
	}

	bool hasReverse( )const noexcept { return true; }

	/*@brief generate reverse record*/
	std::shared_ptr<IMCadRecord> generateReverse(IMCadOutputStream& a_stream, MCadRealocMemory& a_realocMem)const final
	{
		return std::make_shared<TMCadRecordContainerCellInsert<Key>>(this->m_Container, this->m_objectKey, this->m_pObject, this->m_ObjectUID, this->m_pDef);
	}

	/*@brief apply record for undo*/
	virtual void apply([[maybe_unused]]IMCadInputStream& a_stream, MCadRealocMemory& a_realocMem) final
	{
		if ( this->m_Container.realocate(a_realocMem) )
		{
			auto pObj = this->m_pObject.lock( );
			if ( !pObj )
				pObj = a_realocMem.realoc(this->m_ObjectUID, this->m_pDef);

			if ( pObj )
			{
				this->m_Container->do_insert(this->m_objectKey, pObj);
			}
			else
			{
				MCadLogger::Instance( ) << LogMode::LOG_ERROR << std::source_location::current( ) << "Can't realoc object.";
			}
		}
		else
		{
			UNDO_REDO_TROW(UndoRedoException::ExceptionType::Except_Deleted)
		}
	}

};

template<typename Key>
class TMCadRecordContainerCellChanged : public TMCadRecordContainerCell<Key>
{
private:
	ObjectUID m_newObjectUID;				/*!< new object uid at Key*/
	std::weak_ptr<MCadObject> m_pNewObject;	/*!< new object at Key*/

public:
	TMCadRecordContainerCellChanged(TIMCadContainer<Key>* const a_container,
		const Key& a_key, const std::weak_ptr<MCadObject>& a_pObject, 
		const std::weak_ptr<MCadObject>& a_pNewObject) :
		TMCadRecordContainerCell<Key>{ a_container, a_key, a_pObject }, m_pNewObject{ a_pNewObject }
	{
		if ( auto pObj = m_pNewObject.lock( ) )
		{
			m_newObjectUID = pObj->uid( );
		}
		else
		{
			UNDO_REDO_TROW(UndoRedoException::ExceptionType::Except_Deleted)
		}
	}

	TMCadRecordContainerCellChanged(const TContainerRecordProxy<Key>& a_container,
		const Key& a_key, const std::weak_ptr<MCadObject>& a_pObject,
		const std::weak_ptr<MCadObject>& a_pNewObject, const ObjectUID& a_curUID, RTTIDefinitionWPtr a_pDef) :
		TMCadRecordContainerCell<Key>{ a_container, a_key, a_pObject, a_curUID, a_pDef }, m_pNewObject{ a_pNewObject }
	{
		if ( auto pObj = m_pNewObject.lock( ) )
		{
			m_newObjectUID = pObj->uid( );
		}
		else
		{
			UNDO_REDO_TROW(UndoRedoException::ExceptionType::Except_Deleted)
		}
	}

	bool hasReverse( )const noexcept { return true; }

	/*@brief generate reverse record*/
	std::shared_ptr<IMCadRecord> generateReverse(IMCadOutputStream& a_stream, MCadRealocMemory& a_realocMem)const final
	{
		auto pObj = this->m_pNewObject.lock( );
		return std::make_shared<TMCadRecordContainerCellChanged<Key>>(this->m_Container, this->m_objectKey, this->m_pNewObject, this->m_pObject, pObj->uid(), pObj->isA());
	}

	/*@brief apply record for undo*/
	virtual void apply([[ maybe_unused ]]IMCadInputStream& a_stream, MCadRealocMemory& a_realocMem) final
	{
		if ( this->m_Container.realocate(a_realocMem) )
		{
			auto pObj = this->m_pObject.lock( );
			if ( !pObj )
				pObj = a_realocMem.realoc(this->m_ObjectUID, this->m_pDef);

			if ( pObj )
			{
				this->m_Container->do_replace(this->m_objectKey, pObj);
			}
			else
			{
				MCadLogger::Instance( ) << LogMode::LOG_ERROR << std::source_location::current( ) << "Can't realoc object.";
			}
		}
		else
		{
			UNDO_REDO_TROW(UndoRedoException::ExceptionType::Except_Deleted)
		}
	}

};