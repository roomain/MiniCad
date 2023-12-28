#pragma once


#ifndef BUILD_STATIC
# if defined(MCAD_CMD_LIB)
#  define MCAD_CMD_EXPORT __declspec(dllexport)
# else
#  define MCAD_CMD_EXPORT __declspec(dllimport)
# endif
#else
# define MCAD_CMD_EXPORT
#endif#pragma once
