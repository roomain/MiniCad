#pragma once


#ifndef BUILD_STATIC
# if defined(MCAD_EVENTS_LIB)
#  define MCAD_EVENTS_EXPORT __declspec(dllexport)
# else
#  define MCAD_EVENTS_EXPORT __declspec(dllimport)
# endif
#else
# define MCAD_EVENTS_EXPORT
#endif#pragma once
