#pragma once


#ifndef BUILD_STATIC
# if defined(MCAD_CONFIGURATION_LIB)
#  define MCAD_CONFIGURATION_EXPORT __declspec(dllexport)
# else
#  define MCAD_CONFIGURATION_EXPORT __declspec(dllimport)
# endif
#else
# define MCAD_FORMULA_EXPORT
#endif#pragma once
