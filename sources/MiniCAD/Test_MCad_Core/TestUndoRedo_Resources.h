#pragma once
#include "MCadObject.h"
#include "IMCadInputStream.h"
#include "IMCadOutputStream.h"
#include "MCadMemory.h"

class MCadTestObject : public MCadObject
{
	DECLARE_RTTI_DERIVED(1, MCadTestObject, MCadObject)
private:
	int m_value = 0;

public:
	using MCadObject::MCadObject;

	inline void setValue(const int a_value)
	{
		UndoRedo::assertModification(this);
		m_value = a_value;
	}

	inline int value()const { return m_value; }

	unsigned short load(IMCadInputStream& a_stream) override
	{
		a_stream >> m_value;
		return 1;
	}

	/*@brief save object to stream*/
	bool save(IMCadOutputStream& a_stream)const override
	{
		a_stream << m_value;
		return true;
	}
};

using MCadTestObjectPtr = MCadShared_ptr<MCadTestObject>;