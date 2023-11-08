#pragma once
/***********************************************
* @headerfile MCadTrigonometricOperators.h
* @date 11 / 10 / 2023
* @author Roomain
************************************************/
#include "MCadOperator.h"
#include "MCadConfiguration.h"
#include "MCadFormulaException.h"

inline double toRadian(const double& a_value)
{
	switch ( MCadConfiguration::Instance( ).ANGLE_UNIT.value( ) )
	{
	case AngleUnit::unit_degree:
		return convertToRadian<AngleUnit::unit_degree>(a_value);

	case AngleUnit::unit_grad:
		return convertToRadian<AngleUnit::unit_grad>(a_value);
	}
	return a_value;
}

inline float toRadian(const float a_value)
{
	switch ( MCadConfiguration::Instance().ANGLE_UNIT.value() )
	{
	case AngleUnit::unit_degree:
		return convertToRadianf<AngleUnit::unit_degree>(a_value);

	case AngleUnit::unit_grad:
		return convertToRadianf<AngleUnit::unit_grad>(a_value);
	}
	return a_value;
}

inline double toAngle(const double& a_value)
{
	switch ( MCadConfiguration::Instance( ).ANGLE_UNIT.value( ) )
	{
	case AngleUnit::unit_degree:
		return convertToDegree<AngleUnit::unit_radian>(a_value);

	case AngleUnit::unit_grad:
		return convertToGrad<AngleUnit::unit_radian>(a_value);
	}
	return a_value;
}

inline float toAngle(const float a_value)
{
	switch ( MCadConfiguration::Instance( ).ANGLE_UNIT.value( ) )
	{
	case AngleUnit::unit_degree:
		return convertToDegreef<AngleUnit::unit_radian>(a_value);

	case AngleUnit::unit_grad:
		return convertToGradf<AngleUnit::unit_radian>(a_value);
	}
	return a_value;
}

struct CosOperator : MCadOperator
{
	MCadValue operator()(const int a_value)const
	{
		return cosf(toRadian(static_cast<float>(a_value)));
	}

	MCadValue operator()(const double& a_value)const
	{
		return cos(toRadian(a_value));
	}

	MCadValue operator()(const float a_value)const
	{
		return cosf(toRadian(a_value));
	}

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_Incompatible_type, std::source_location::current(), m_position,  a_values...);
	}
};

struct SinOperator : MCadOperator
{
	MCadValue operator()(const int a_value)const
	{
		return sinf(toRadian(static_cast< float >( a_value )));
	}

	MCadValue operator()(const double& a_value)const
	{
		return sin(toRadian(a_value));
	}

	MCadValue operator()(const float a_value)const
	{
		return sinf(toRadian(a_value));
	}

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_Incompatible_type, std::source_location::current(), m_position,  a_values...);
	}
};

struct TanOperator : MCadOperator
{
	MCadValue operator()(const int a_value)const
	{
		return tanf(toRadian(static_cast< float >( a_value )));
	}

	MCadValue operator()(const double& a_value)const
	{
		return tan(toRadian(a_value));
	}

	MCadValue operator()(const float a_value)const
	{
		return tanf(toRadian(a_value));
	}

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_Incompatible_type, std::source_location::current(), m_position,  a_values...);
	}
};


struct ACosOperator : MCadOperator
{
	MCadValue operator()(const int a_value)const
	{
		return toAngle(acosf(static_cast< float >( a_value )));
	}

	MCadValue operator()(const double& a_value)const
	{
		return toAngle(acos(a_value));
	}

	MCadValue operator()(const float a_value)const
	{
		return toAngle(acosf(a_value));
	}

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_Incompatible_type, std::source_location::current(), m_position,  a_values...);
	}
};

struct ASinOperator : MCadOperator
{
	MCadValue operator()(const int a_value)const
	{
		return toAngle(asinf(static_cast< float >( a_value )));
	}

	MCadValue operator()(const double& a_value)const
	{
		return toAngle(asin(a_value));
	}

	MCadValue operator()(const float a_value)const
	{
		return toAngle(asinf(a_value));
	}

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_Incompatible_type, std::source_location::current(), m_position,  a_values...);
	}
};

struct ATanOperator : MCadOperator
{
	MCadValue operator()(const int a_value)const
	{
		return toAngle(atanf(static_cast< float >( a_value )));
	}

	MCadValue operator()(const double& a_value)const
	{
		return toAngle(atan(a_value));
	}

	MCadValue operator()(const float a_value)const
	{
		return toAngle(atanf(a_value));
	}

	template<typename ...Types>
	MCadValue operator()(const Types&... a_values)const
	{
		throw MCadFormulaException(MCadFormulaException::ExceptType::Formula_except_Incompatible_type, std::source_location::current(), m_position,  a_values...);
	}
};