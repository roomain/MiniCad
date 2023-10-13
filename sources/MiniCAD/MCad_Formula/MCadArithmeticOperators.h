#pragma once
/***********************************************
* @headerfile MCadArithmeticOperators.h
* @date 13 / 10 / 2023
* @author Roomain
************************************************/
#include "MCadOperator.h"



struct UnaryLessOperator : MCadOperator
{
	MCadValue operator()(const float a_value)const
	{
		return MCadValue(-a_value);
	}

	MCadValue operator()(const double& a_value)const
	{
		return MCadValue(-a_value);
	}

	MCadValue operator()(const int a_value)const
	{
		return MCadValue(-a_value);
	}

	MCadValue operator()(const glm::dvec2& a_value)const
	{
		return -a_value;
	}

	MCadValue operator()(const glm::dvec3& a_value)const
	{
		return -a_value;
	}

	MCadValue operator()(const glm::dvec4& a_value)const
	{
		return -a_value;
	}

	MCadValue operator()(...)const
	{
		throw;
	}
};


struct LessOperator : MCadOperator
{
	MCadValue operator()(const float a_first, const int a_second)const
	{
		return a_first - static_cast<float>(a_second);
	}

	MCadValue operator()(const float a_first, const float a_second)const
	{
		return a_first - a_second;
	}

	MCadValue operator()(const float a_first, const double a_second)const
	{
		return static_cast<double>(a_first) - a_second;
	}

	//--------------------------------------------------------------------------
	MCadValue operator()(const double& a_first, const int a_second)const
	{
		return a_first - static_cast<double>(a_second);
	}

	MCadValue operator()(const double& a_first, const float a_second)const
	{
		return a_first - static_cast< double >( a_second );
	}

	MCadValue operator()(const double& a_first, const double& a_second)const
	{
		return a_first - a_second;
	}
	//--------------------------------------------------------------------------

	MCadValue operator()(const int a_first, const int a_second)const
	{
		return a_first - a_second;
	}

	MCadValue operator()(const int a_first, const float a_second)const
	{
		return static_cast< float >( a_first ) - a_second;
	}
	MCadValue operator()(const int a_first, const double& a_second)const
	{
		return static_cast<double>( a_first ) - a_second;
	}
	//------------------------------------------------------------
	MCadValue operator()(const glm::dvec2& a_first, const glm::dvec2& a_second)const
	{
		return a_first - a_second;
	}

	MCadValue operator()(const glm::dvec3& a_first, const glm::dvec3& a_second)const
	{
		return a_first - a_second;
	}

	MCadValue operator()(const glm::dvec4& a_first, const glm::dvec4& a_second)const
	{
		return a_first - a_second;
	}

	MCadValue operator()(...)const
	{
		throw;
	}
};

struct AddOperator : MCadOperator
{
	MCadValue operator()(const float a_first, const int a_second)const
	{
		return a_first + static_cast< float >( a_second );
	}

	MCadValue operator()(const float a_first, const float a_second)const
	{
		return a_first + a_second;
	}

	MCadValue operator()(const float a_first, const double a_second)const
	{
		return static_cast< double >( a_first ) + a_second;
	}

	//----------------------------------------------------------------------------
	MCadValue operator()(const double& a_first, const int a_second)const
	{
		return a_first + static_cast< double >( a_second );
	}

	MCadValue operator()(const double& a_first, const float a_second)const
	{
		return a_first + static_cast< double >( a_second );
	}

	MCadValue operator()(const double& a_first, const double& a_second)const
	{
		return a_first + a_second;
	}
	//----------------------------------------------------------------------------

	MCadValue operator()(const int a_first, const int a_second)const
	{
		return a_first + a_second;
	}

	MCadValue operator()(const int a_first, const float a_second)const
	{
		return static_cast< float >( a_first ) + a_second;
	}
	MCadValue operator()(const int a_first, const double& a_second)const
	{
		return static_cast< double >( a_first ) + a_second;
	}
	//----------------------------------------------------------------------------
	MCadValue operator()(const glm::dvec2& a_first, const glm::dvec2& a_second)const
	{
		return a_first + a_second;
	}

	MCadValue operator()(const glm::dvec3& a_first, const glm::dvec3& a_second)const
	{
		return a_first + a_second;
	}

	MCadValue operator()(const glm::dvec4& a_first, const glm::dvec4& a_second)const
	{
		return a_first + a_second;
	}

	MCadValue operator()(...)const
	{
		throw;
	}
};

struct MultOperator : MCadOperator
{
	MCadValue operator()(const float a_first, const int a_second)const
	{
		return a_first * static_cast< float >( a_second );
	}

	MCadValue operator()(const float a_first, const float a_second)const
	{
		return a_first * a_second;
	}

	MCadValue operator()(const float a_first, const double a_second)const
	{
		return static_cast< double >( a_first ) * a_second;
	}

	//----------------------------------------------------------------------------
	MCadValue operator()(const double& a_first, const int a_second)const
	{
		return a_first * static_cast< double >( a_second );
	}

	MCadValue operator()(const double& a_first, const float a_second)const
	{
		return a_first * static_cast< double >( a_second );
	}

	MCadValue operator()(const double& a_first, const double& a_second)const
	{
		return a_first * a_second;
	}
	//----------------------------------------------------------------------------

	MCadValue operator()(const int a_first, const int a_second)const
	{
		return a_first * a_second;
	}

	MCadValue operator()(const int a_first, const float a_second)const
	{
		return static_cast< float >( a_first ) * a_second;
	}
	MCadValue operator()(const int a_first, const double& a_second)const
	{
		return static_cast< double >( a_first ) * a_second;
	}

	//----------------------------------------------------------------------------
	MCadValue operator()(const double& a_first, const glm::dvec2& a_second)const
	{
		return a_first * a_second;
	}

	MCadValue operator()(const double& a_first, const glm::dvec3& a_second)const
	{
		return a_first * a_second;
	}

	MCadValue operator()(const double& a_first, const glm::dvec4& a_second)const
	{
		return a_first * a_second;
	}
	//----------------------------------------------------------------------------
	MCadValue operator()(const float a_first, const glm::dvec2& a_second)const
	{
		return static_cast< double >( a_first ) * a_second;
	}

	MCadValue operator()(const float a_first, const glm::dvec3& a_second)const
	{
		return static_cast< double >( a_first ) * a_second;
	}

	MCadValue operator()(const float a_first, const glm::dvec4& a_second)const
	{
		return static_cast<double>(a_first) * a_second;
	}
	//----------------------------------------------------------------------------
	MCadValue operator()(const int a_first, const glm::dvec2& a_second)const
	{
		return static_cast< double >( a_first ) * a_second;
	}

	MCadValue operator()(const int a_first, const glm::dvec3& a_second)const
	{
		return static_cast< double >( a_first ) * a_second;
	}

	MCadValue operator()(const int a_first, const glm::dvec4& a_second)const
	{
		return static_cast< double >( a_first ) * a_second;
	}

	//----------------------------------------------------------------------------
	MCadValue operator()(const glm::dvec2& a_first, const double& a_second)const
	{
		return a_second * a_first;
	}

	MCadValue operator()(const glm::dvec3& a_first, const double& a_second)const
	{
		return a_second * a_first;
	}

	MCadValue operator()(const glm::dvec4& a_first, const double& a_second)const
	{
		return a_second * a_first;
	}
	//----------------------------------------------------------------------------
	MCadValue operator()(const glm::dvec2& a_first, const float a_second)const
	{
		return static_cast< double >( a_second ) * a_first;
	}

	MCadValue operator()(const glm::dvec3& a_first, const float a_second)const
	{
		return static_cast< double >( a_second ) * a_first;
	}

	MCadValue operator()(const glm::dvec4& a_first, const float a_second)const
	{
		return static_cast< double >( a_second ) * a_first;
	}
	//----------------------------------------------------------------------------
	MCadValue operator()(const glm::dvec2& a_first, const int a_second)const
	{
		return static_cast< double >( a_second ) * a_first;
	}

	MCadValue operator()(const glm::dvec3& a_first, const int a_second)const
	{
		return static_cast< double >( a_second ) * a_first;
	}

	MCadValue operator()(const glm::dvec4& a_first, const int a_second)const
	{
		return static_cast< double >( a_second ) * a_first;
	}

	MCadValue operator()(...)const
	{
		throw;
	}
};

struct DivideOperator : MCadOperator
{
	MCadValue operator()(const float a_first, const int a_second)const
	{
		return a_first / static_cast< float >( a_second );
	}

	MCadValue operator()(const float a_first, const float a_second)const
	{
		return a_first / a_second;
	}

	MCadValue operator()(const float a_first, const double a_second)const
	{
		return static_cast< double >( a_first ) / a_second;
	}

	//----------------------------------------------------------------------------
	MCadValue operator()(const double& a_first, const int a_second)const
	{
		return a_first / static_cast< double >( a_second );
	}

	MCadValue operator()(const double& a_first, const float a_second)const
	{
		return a_first / static_cast< double >( a_second );
	}

	MCadValue operator()(const double& a_first, const double& a_second)const
	{
		return a_first / a_second;
	}
	//----------------------------------------------------------------------------

	MCadValue operator()(const int a_first, const int a_second)const
	{
		return a_first / a_second;
	}

	MCadValue operator()(const int a_first, const float a_second)const
	{
		return static_cast< float >( a_first ) / a_second;
	}
	MCadValue operator()(const int a_first, const double& a_second)const
	{
		return static_cast< double >( a_first ) / a_second;
	}

	MCadValue operator()(const glm::dvec2& a_first, const double& a_second)const
	{
		return a_second / a_first;
	}

	MCadValue operator()(const glm::dvec3& a_first, const double& a_second)const
	{
		return a_second / a_first;
	}

	MCadValue operator()(const glm::dvec4& a_first, const double& a_second)const
	{
		return a_second / a_first;
	}
	//----------------------------------------------------------------------------
	MCadValue operator()(const glm::dvec2& a_first, const float a_second)const
	{
		return static_cast< double >( a_second ) / a_first;
	}

	MCadValue operator()(const glm::dvec3& a_first, const float a_second)const
	{
		return static_cast< double >( a_second ) / a_first;
	}

	MCadValue operator()(const glm::dvec4& a_first, const float a_second)const
	{
		return static_cast< double >( a_second ) / a_first;
	}
	//----------------------------------------------------------------------------
	MCadValue operator()(const glm::dvec2& a_first, const int a_second)const
	{
		return static_cast< double >( a_second ) / a_first;
	}

	MCadValue operator()(const glm::dvec3& a_first, const int a_second)const
	{
		return static_cast< double >( a_second ) / a_first;
	}

	MCadValue operator()(const glm::dvec4& a_first, const int a_second)const
	{
		return static_cast< double >( a_second ) / a_first;
	}

	MCadValue operator()(...)const
	{
		throw;
	}
};

struct EuclidianDivideOperator : MCadOperator
{
	MCadValue operator()(const int a_first, const int a_second)const
	{
		return a_first / a_second;
	}
	
	MCadValue operator()(const float a_first, const int a_second)const
	{
		return static_cast< int >( a_first ) / a_second;
	}

	MCadValue operator()(const double& a_first, const int a_second)const
	{
		return static_cast< int >( a_first ) / a_second;
	}

	MCadValue operator()(...)const
	{
		throw;
	}
};

struct ModuleOperator : MCadOperator
{
	MCadValue operator()(const int a_first, const int a_second)const
	{
		return a_first % a_second;
	}

	MCadValue operator()(...)const
	{
		throw;
	}
};