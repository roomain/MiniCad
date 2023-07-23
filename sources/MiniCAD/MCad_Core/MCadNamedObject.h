#pragma once
/***********************************************
* @headerfile MCadNamedObject.h
* @date 22 / 07 / 2023
* @author Roomain
************************************************/
#include "MCad_Core_globals.h"
#include "MCadObject.h"
#include <string>

/*@brief base class for named object*/
class MCAD_CORE_EXPORT MCadNamedObject : public MCadObject
{
	DECLARE_RTTI_DERIVED(1, MCadNamedObject, MCadObject)
private:
	std::string m_name = "no name";  /*!< object name*/

public:
	MCadNamedObject() = default;
	virtual ~MCadNamedObject() = default;
	inline std::string name()const noexcept { return m_name; }
	// container set the owner to his children
	// container has check function (Protocol extension), this check function is called in setName
	virtual[[nodiscard]] bool setName(const std::string_view& a_name);
	virtual [[nodiscard]] bool setName(const std::string& a_name);
};

