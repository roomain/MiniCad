#pragma once
/***********************************************
* @headerfile MCadOperator.h
* @date 11 / 10 / 2023
* @author Roomain
************************************************/

template<class... Ts> struct Operator : Ts... { using Ts::operator()...; };


struct MCadOperator
{	
	//
};


struct UnaryLessOperator
{
	//
};

struct CosOperator
{
	//
};