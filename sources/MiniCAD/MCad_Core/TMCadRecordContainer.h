#pragma once
/***********************************************
* @headerfile TMCadRecordContainer.h
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
class TMCadRecordContainer : public IMCadRecord
{
protected:
	TContainerRecordProxy m_Container;		/*!< container*/
	Key m_objectKey;						/*!< contained object Key*/
	ObjectUID m_ObjectUID;					/*!< contained object unique identifier*/
	std::weak_ptr<MCadObject> m_pObject;	/*!< contained object weak pointer*/
	
public:
	TMCadRecordContainer( ) = delete;
	TMCadRecordContainer(TIMCadContainer<Key>* const a_container,
		const Key& a_key, const std::weak_ptr<MCadObject>& a_pObject) : m_Container{ a_container },
		m_objectKey, { a_key }, m_pObject{ a_pObject }
	{
		if ( auto pSharedObj = m_pObject.lock( ) )
		{
			m_ObjectUID = pSharedObj->uid( );
		}
		else
		{
			UNDO_REDO_TROW(UndoRedoException::ExceptionType::Except_Deleted)
		}
	}

	TMCadRecordContainer(const TContainerRecordProxy& a_container,
		const Key& a_key, const std::weak_ptr<MCadObject>& a_pObject) :
		m_Container{ a_container }, m_objectKey, { a_key }, m_pObject{ a_pObject }
	{
		//
	}

	explicit TMCadRecordContainer(const TMCadRecordContainer<Key>& a_other) : 
		m_Container{ a_other.m_Container },	m_objectKey, { a_other.m_objectKey }, m_pObject{ a_other.m_pObject }
	{
		//
	}

	explicit TMCadRecordContainer(TMCadRecordContainer<Key>&& a_other)noexcept :
		m_Container{ a_other.m_Container }, m_objectKey, { a_other.m_objectKey }, m_pObject{ a_other.m_pObject }
	{
		//
	}

	const ObjectUID recordedObject( )const noexcept final { return m_Container.objectUID( ); }
	RTTIDefinitionWPtr recordedObjectDefinition( )const noexcept final { return m_Container.objectDef( ); }
};

template<typename Key>
class TMCadRecordContainerInsert : public TMCadRecordContainer<Key>
{
public:
	TMCadRecordContainerInsert(TIMCadContainer<Key>* const a_container,
		const Key& a_key, const std::weak_ptr<MCadObject>& a_pObject) : 
		TMCadRecordContainer<Key>{ a_container, a_key, a_pObject }
	{
		//
	}

	TMCadRecordContainerInsert(const TContainerRecordProxy& a_container,
		const Key& a_key, const std::weak_ptr<MCadObject>& a_pObject) :
		TMCadRecordContainer<Key>{ a_container, a_key, a_pObject }
	{
		//
	}

	bool hasReverse( )const noexcept { return true; }
	
	/*@brief generate reverse record*/
	std::shared_ptr<IMCadRecord> generateReverse(IMCadOutputStream& a_stream, MCadRealocMemory& a_realocMem)const final
	{
		return std::make_shared<TMCadRecordContainerRemoved<Key>>(m_Container, m_objectKey, m_pObject);
	}
	
	/*@brief apply record for undo*/
	virtual void apply([maybe_unused]IMCadInputStream& a_stream, MCadRealocMemory& a_realocMem) final
	{
		if ( m_Container.realocate(a_memory) )
		{
			m_Container->do_eraseAt(m_objectKey);
		}
		else
		{
			UNDO_REDO_TROW(UndoRedoException::ExceptionType::Except_Deleted)
		}
	}

};

template<typename Key>
class TMCadRecordContainerRemoved : public TMCadRecordContainer<Key>
{
public:
	TMCadRecordContainerRemoved(TIMCadContainer<Key>* const a_container,
		const Key& a_key, const std::weak_ptr<MCadObject>& a_pObject) :
		TMCadRecordContainer<Key>{ a_container, a_key, a_pObject }
	{
		//
	}

	TMCadRecordContainerRemoved(const TContainerRecordProxy& a_container,
		const Key& a_key, const std::weak_ptr<MCadObject>& a_pObject) :
		TMCadRecordContainer<Key>{ a_container, a_key, a_pObject }
	{
		//
	}

	bool hasReverse( )const noexcept { return true; }

	/*@brief generate reverse record*/
	std::shared_ptr<IMCadRecord> generateReverse(IMCadOutputStream& a_stream, MCadRealocMemory& a_realocMem)const final
	{
		return std::make_shared<TMCadRecordContainerRemoved<Key>>(m_Container, m_objectKey, m_pObject);
	}

	/*@brief apply record for undo*/
	virtual void apply([ maybe_unused ]IMCadInputStream& a_stream, MCadRealocMemory& a_realocMem) final
	{
		if ( m_Container.realocate(a_memory) )
		{
			auto pObj = m_pNewObject.lock( );
			if ( !pObj )
				pObj = a_realocMem.realoc(m_newObjectUID);

			if ( pObj )
			{
				m_Container->do_insert(m_objectKey, pObj);
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
class TMCadRecordContainerChanged : public TMCadRecordContainer<Key>
{
private:
	ObjectUID m_newObjectUID;				/*!< new object uid at Key*/
	std::weak_ptr<MCadObject> m_pNewObject;	/*!< new object at Key*/

public:
	TMCadRecordContainerChanged(TIMCadContainer<Key>* const a_container,
		const Key& a_key, const std::weak_ptr<MCadObject>& a_pObject, 
		const std::weak_ptr<MCadObject>& a_pNewObject) :
		TMCadRecordContainer<Key>{ a_container, a_key, a_pObject }, m_pNewObject{ a_pNewObject }
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

	TMCadRecordContainerChanged(const TContainerRecordProxy& a_container,
		const Key& a_key, const std::weak_ptr<MCadObject>& a_pObject,
		const std::weak_ptr<MCadObject>& a_pNewObject) :
		TMCadRecordContainer<Key>{ a_container, a_key, a_pObject }, m_pNewObject{ a_pNewObject }
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
		return std::make_shared<TMCadRecordContainerChanged<Key>>(m_Container, m_objectKey, m_pObject, m_pNewObject);
	}

	/*@brief apply record for undo*/
	virtual void apply([ maybe_unused ]IMCadInputStream& a_stream, MCadRealocMemory& a_realocMem) final
	{
		if ( m_Container.realocate(a_memory) )
		{
			auto pObj = m_pNewObject.lock( );
			if ( !pObj )
				pObj = a_realocMem.realoc(m_newObjectUID);

			if ( pObj )
			{
				m_Container->do_replace(m_objectKey, pObj);
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