#pragma once


#ifndef BUILD_STATIC
# if defined(MCAD_CORE_LIB)
#  define MCAD_CORE_EXPORT __declspec(dllexport)
# else
#  define MCAD_CORE_EXPORT __declspec(dllimport)
# endif
#else
# define MCAD_CORE_EXPORT
#endif