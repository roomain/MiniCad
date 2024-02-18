#pragma once
/***********************************************
* @headerfile TMCadRecordContainerEmptyCell.h
* @date 03 / 10 / 2023
* @author Roomain
************************************************/
#include <variant>
#include "IMCadRecord.h"
#include "TMCadRecordContainerCell.h"


template<typename Key>
class TMCadRecordContainerEmptyCell : public IMCadRecord
{
protected:
	TContainerRecordProxy<Key> m_Container;		/*!< container*/
	Key m_objectKey;							/*!< contained object Key*/

public:
	TMCadRecordContainerEmptyCell( ) = delete;
	TMCadRecordContainerEmptyCell(TIMCadContainer<Key>* const a_container,
		const Key& a_key) : m_Container{ a_container },
		m_objectKey{ a_key }
	{
		//
	}

	TMCadRecordContainerEmptyCell(const TContainerRecordProxy<Key>& a_container,
		const Key& a_key) :
		m_Container{ a_container }, m_objectKey{ a_key }
	{
		//
	}

	explicit TMCadRecordContainerEmptyCell(const TMCadRecordContainerEmptyCell<Key>& a_other) :
		m_Container{ a_other.m_Container }, m_objectKey{ a_other.m_objectKey }
	{
		//
	}

	explicit TMCadRecordContainerEmptyCell(TMCadRecordContainerEmptyCell<Key>&& a_other)noexcept :
		m_Container{ a_other.m_Container }, m_objectKey{ a_other.m_objectKey }
	{
		//
	}

	virtual [[nodiscard]]  bool hasReverse( )const noexcept override { return true; }
	[[nodiscard]] RTTIDefinitionWPtr recordedObjectDefinition( )const noexcept override { return RTTIDefinitionWPtr(); }
};

template<typename Key>
class TMCadRecordContainerEmptyCellInsert : public TMCadRecordContainerEmptyCell<Key>
{
public:
	TMCadRecordContainerEmptyCellInsert(TIMCadContainer<Key>* const a_container,
		const Key& a_key) :
		TMCadRecordContainerEmptyCell<Key>{ a_container, a_key }
	{
		//
	}

	TMCadRecordContainerEmptyCellInsert(const TContainerRecordProxy<Key>& a_container,
		const Key& a_key) :
		TMCadRecordContainerEmptyCell<Key>{ a_container, a_key }
	{
		//
	}

	/*@brief apply record for undo*/
	virtual void apply([[maybe_unused]] IMCadInputStream& a_stream, MCadReallocMemory& a_realocMem) final
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

	/*@brief generate reverse record*/
	std::shared_ptr<IMCadRecord> createReverseRecord(IMCadOutputStream& a_stream, MCadReallocMemory& a_realocMem)const final
	{
		return std::make_shared<TMCadRecordContainerEmptyCellRemoved<Key>>(this->m_Container, this->m_objectKey);
	}

	[[nodiscard]] const ObjectUID recordedObject( )const noexcept final { return 0; }
};

template<typename Key>
class TMCadRecordContainerEmptyCellRemoved : public TMCadRecordContainerEmptyCell<Key>
{
public:
	TMCadRecordContainerEmptyCellRemoved(TIMCadContainer<Key>* const a_container,
		const Key& a_key) :
		TMCadRecordContainerEmptyCell<Key>{ a_container, a_key}
	{
		//
	}


	TMCadRecordContainerEmptyCellRemoved(const TContainerRecordProxy<Key>& a_container,
		const Key& a_key) :
		TMCadRecordContainerEmptyCell<Key>{ a_container, a_key }
	{
		//
	}


	/*@brief apply record for undo*/
	virtual void apply([[maybe_unused]] IMCadInputStream& a_stream, MCadReallocMemory& a_realocMem) final
	{
		if ( this->m_Container.realocate(a_realocMem) )
		{
			this->m_Container->do_insert(this->m_objectKey, nullptr);
		}
		else
		{
			UNDO_REDO_TROW(UndoRedoException::ExceptionType::Except_Deleted)
		}
	}

	std::shared_ptr<IMCadRecord> createReverseRecord(IMCadOutputStream& a_stream, MCadReallocMemory& a_realocMem)const final
	{
		return std::make_shared<TMCadRecordContainerEmptyCellInsert<Key>>(this->m_Container, this->m_objectKey);
	}

	virtual [[nodiscard]] const ObjectUID recordedObject( )const noexcept final { return 0; }

};

template<typename Key>
class TMCadRecordContainerToEmptyCellChanged;

template<typename Key>
class TMCadRecordContainerEmptyCellChanged : public TMCadRecordContainerEmptyCell<Key>
{
private:
	ObjectUID m_newObjectUID;				/*!< new object uid at Key*/
	std::weak_ptr<MCadObject> m_pNewObject;	/*!< new object at Key*/
	RTTIDefinitionWPtr m_pDef;				/*!< object definition*/

public:
	TMCadRecordContainerEmptyCellChanged(TIMCadContainer<Key>* const a_container,
		const Key& a_key,
		const std::weak_ptr<MCadObject>& a_pNewObject) :
		TMCadRecordContainerEmptyCell<Key>{ a_container, a_key }, m_pNewObject{ a_pNewObject }
	{
		if ( auto pObj = m_pNewObject.lock( ) )
		{
			m_pDef = pObj->isA( );
			m_newObjectUID = pObj->uid( );
		}
		else
		{
			UNDO_REDO_TROW(UndoRedoException::ExceptionType::Except_Deleted)
		}
	}

	TMCadRecordContainerEmptyCellChanged(const TContainerRecordProxy<Key>& a_container,
		const Key& a_key,
		const std::weak_ptr<MCadObject>& a_pNewObject) :
		TMCadRecordContainerEmptyCell<Key>{ a_container, a_key }, m_pNewObject{ a_pNewObject }
	{
		if ( auto pObj = m_pNewObject.lock( ) )
		{
			m_pDef = pObj->isA( );
			m_newObjectUID = pObj->uid( );
		}
		else
		{
			UNDO_REDO_TROW(UndoRedoException::ExceptionType::Except_Deleted)
		}
	}


	/*@brief generate reverse record*/
	std::shared_ptr<IMCadRecord> createReverseRecord(IMCadOutputStream& a_stream, MCadReallocMemory& a_realocMem)const final
	{
		return std::make_shared<TMCadRecordContainerToEmptyCellChanged<Key>>(this->m_Container, this->m_objectKey, this->m_pNewObject, m_newObjectUID, m_pDef);
	}

	/*@brief apply record for undo*/
	virtual void apply([[ maybe_unused ]] IMCadInputStream& a_stream, MCadReallocMemory& a_realocMem) final
	{
		if ( this->m_Container.realocate(a_realocMem) )
		{
			this->m_Container->do_replace(this->m_objectKey, nullptr);
		}
		else
		{
			UNDO_REDO_TROW(UndoRedoException::ExceptionType::Except_Deleted)
		}
	}

	[[nodiscard]] const ObjectUID recordedObject( )const noexcept final { return this->m_newObjectUID; }
	[[nodiscard]] RTTIDefinitionWPtr recordedObjectDefinition( )const noexcept final { return m_pDef; }
};


template<typename Key>
class TMCadRecordContainerToEmptyCellChanged : public TMCadRecordContainerEmptyCell<Key>
{
private:
	ObjectUID m_newObjectUID;				/*!< new object uid at Key*/
	std::weak_ptr<MCadObject> m_pNewObject;	/*!< new object at Key*/
	RTTIDefinitionWPtr m_pDef;				/*!< object definition*/

public:
	TMCadRecordContainerToEmptyCellChanged(const TContainerRecordProxy<Key>& a_container,
		const Key& a_key,
		const std::weak_ptr<MCadObject>& a_pNewObject, const ObjectUID& a_uid, const RTTIDefinitionWPtr& a_pDef) :
		TMCadRecordContainerEmptyCell<Key>{ a_container, a_key }, m_pNewObject{ a_pNewObject },
		m_newObjectUID{ a_uid }, m_pDef{ a_pDef }
	{
		//
	}

	virtual [[nodiscard]] bool hasReverse( )const noexcept override { return false; }

	/*@brief generate reverse record*/
	std::shared_ptr<IMCadRecord> createReverseRecord(IMCadOutputStream& a_stream, MCadReallocMemory& a_realocMem)const final
	{
		return nullptr;
	}

	/*@brief apply record for undo*/
	virtual void apply([[ maybe_unused ]] IMCadInputStream& a_stream, MCadReallocMemory& a_realocMem) final
	{
		if ( this->m_Container.realocate(a_realocMem) )
		{
			auto pObj = this->m_pNewObject.lock( );
			if ( !pObj )
				pObj = a_realocMem.realoc(this->m_newObjectUID, this->m_pDef);

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


	[[nodiscard]] const ObjectUID recordedObject( )const noexcept final { return this->m_newObjectUID; }
	[[nodiscard]] RTTIDefinitionWPtr recordedObjectDefinition( )const noexcept final { return m_pDef; }

};