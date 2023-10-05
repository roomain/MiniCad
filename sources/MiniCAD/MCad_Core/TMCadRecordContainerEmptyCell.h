#pragma once
/***********************************************
* @headerfile TMCadRecordContainerEmptyCell.h
* @date 03 / 10 / 2023
* @author Roomain
************************************************/
#include <variant>
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

	/*@brief generate reverse record*/
	virtual std::shared_ptr<IMCadRecord> generateReverse(IMCadOutputStream& a_stream, 
		MCadRealocMemory& a_realocMem)const override
	{
		return nullptr;
	}
};

template<typename Key>
class TMCadRecordContainerEmptyCellInsert : public TMCadRecordContainerEmptyCell<Key>
{
public:
	TMCadRecordContainerEmptyCellInsert(TIMCadContainer<Key>* const a_container,
		const Key& a_key, const std::weak_ptr<MCadObject>& a_pObject) :
		TMCadRecordContainerEmptyCell<Key>{ a_container, a_key, a_pObject }
	{
		//
	}

	TMCadRecordContainerEmptyCellInsert(const TContainerRecordProxy<Key>& a_container,
		const Key& a_key) :
		TMCadRecordContainerEmptyCell<Key>{ a_container, a_key }
	{
		//
	}

	bool hasReverse( )const noexcept { return false; }


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

	bool hasReverse( )const noexcept { return false; }


	/*@brief apply record for undo*/
	virtual void apply([[maybe_unused]] IMCadInputStream& a_stream, MCadRealocMemory& a_realocMem) final
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

};

template<typename Key>
class TMCadRecordContainerEmptyCellChanged : public TMCadRecordContainerEmptyCell<Key>
{
private:
	ObjectUID m_newObjectUID;				/*!< new object uid at Key*/
	std::weak_ptr<MCadObject> m_pNewObject;	/*!< new object at Key*/

public:
	TMCadRecordContainerEmptyCellChanged(TIMCadContainer<Key>* const a_container,
		const Key& a_key,
		const std::weak_ptr<MCadObject>& a_pNewObject) :
		TMCadRecordContainerEmptyCell<Key>{ a_container, a_key }, m_pNewObject{ a_pNewObject }
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

	TMCadRecordContainerEmptyCellChanged(const TContainerRecordProxy<Key>& a_container,
		const Key& a_key,
		const std::weak_ptr<MCadObject>& a_pNewObject) :
		TMCadRecordContainerEmptyCell<Key>{ a_container, a_key }, m_pNewObject{ a_pNewObject }
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
		return std::make_shared<TMCadRecordContainerEmptyCellChanged<Key>>(this->m_Container, this->m_objectKey, this->m_pNewObject, this->m_pObject, pObj->uid( ), pObj->isA( ));
	}

	/*@brief apply record for undo*/
	virtual void apply([[ maybe_unused ]] IMCadInputStream& a_stream, MCadRealocMemory& a_realocMem) final
	{
		if ( this->m_Container.realocate(a_realocMem) )
		{
			m_proxy->record_replace(m_objectKey, nullptr);
		}
		else
		{
			UNDO_REDO_TROW(UndoRedoException::ExceptionType::Except_Deleted)
		}
	}

};