#pragma once
/***********************************************
* @headerfile MCadMath.h
* @date 26 / 10 / 2023
* @author Roomain
************************************************/
#include <numbers>

/*@brief Mathematical configuration*/

enum class AngleUnit
{
	unit_degree,
	unit_radian,
	unit_grad
};

constexpr double RADIAN_TO_DEGREE = 180.0 / std::numbers::pi;
constexpr double DEGREE_TO_RADIAN = std::numbers::pi / 180.0;
constexpr double RADIAN_TO_GRAD = 100.0 / std::numbers::pi;
constexpr double GRAD_TO_RADIAN = std::numbers::pi / 100.0;
constexpr double DEGREE_TO_GRAD = 100.0 / 180.0;
constexpr double GRAD_TO_DEGREE = 180.0 / 100.0;

constexpr float RADIAN_TO_DEGREE_F = 180.0f / static_cast<float>(std::numbers::pi);
constexpr float DEGREE_TO_RADIAN_F = static_cast< float >( std::numbers::pi ) / 180.0f;
constexpr float RADIAN_TO_GRAD_F = 100.0f / static_cast< float >( std::numbers::pi );
constexpr float GRAD_TO_RADIAN_F = static_cast< float >( std::numbers::pi ) / 100.0f;
constexpr float DEGREE_TO_GRAD_F = 100.0f / 180.0f;
constexpr float GRAD_TO_DEGREE_F = 180.0f / 100.0f;

template<AngleUnit From>
inline double convertToRadian(const double& a_from)
{
	switch ( From )
	{
	case AngleUnit::unit_degree:
		return a_from * DEGREE_TO_RADIAN;
	case AngleUnit::unit_grad:
		return a_from * GRAD_TO_RADIAN;
	default:
		return a_from;
	}
}

template<AngleUnit From>
inline double convertToDegree(const double& a_from)
{
	switch ( From )
	{
	case AngleUnit::unit_radian:
		return a_from * RADIAN_TO_DEGREE;
	case AngleUnit::unit_grad:
		return a_from * GRAD_TO_DEGREE;
	default:
		return a_from;
	}
}

template<AngleUnit From>
inline double convertToGrad(const double& a_from)
{
	switch ( From )
	{
	case AngleUnit::unit_degree:
		return a_from * DEGREE_TO_GRAD;
	case AngleUnit::unit_radian:
		return a_from * RADIAN_TO_GRAD;
	default:
		return a_from;
	}
}

template<AngleUnit From, AngleUnit To>
inline double convert(const double& a_from)
{
	switch ( To )
	{
	case AngleUnit::unit_degree:
		return convertToDegree<From>(a_from);
	case AngleUnit::unit_grad:
		return convertToGrad<From>(a_from);
	default:
		return convertToRadian<From>(a_from);
	}
}

template<AngleUnit From>
inline float convertToRadianf(const float a_from)
{
	switch ( From )
	{
	case AngleUnit::unit_degree:
		return a_from * DEGREE_TO_RADIAN_F;
	case AngleUnit::unit_grad:
		return a_from * GRAD_TO_RADIAN_F;
	default:
		return a_from;
	}
}

template<AngleUnit From>
inline float convertToDegreef(const float a_from)
{
	switch ( From )
	{
	case AngleUnit::unit_radian:
		return a_from * RADIAN_TO_DEGREE_F;
	case AngleUnit::unit_grad:
		return a_from * GRAD_TO_DEGREE_F;
	default:
		return a_from;
	}
}

template<AngleUnit From>
inline float convertToGradf(const float a_from)
{
	switch ( From )
	{
	case AngleUnit::unit_degree:
		return a_from * DEGREE_TO_GRAD_F;
	case AngleUnit::unit_radian:
		return a_from * RADIAN_TO_GRAD_F;
	default:
		return a_from;
	}
}

template<AngleUnit From, AngleUnit To>
inline float convertf(const float a_from)
{
	switch ( To )
	{
	case AngleUnit::unit_degree:
		return convertToDegreef<From>(a_from);
	case AngleUnit::unit_grad:
		return convertToGradf<From>(a_from);
	default:
		return convertToRadianf<From>(a_from);
	}
}
