#pragma once


#ifndef BUILD_STATIC
# if defined(MCAD_FORMULA_LIB)
#  define MCAD_FORMULA_EXPORT __declspec(dllexport)
# else
#  define MCAD_FORMULA_EXPORT __declspec(dllimport)
# endif
#else
# define MCAD_FORMULA_EXPORT
#endif#pragma once
