#pragma once

#ifndef BUILD_STATIC
# if defined(MCAD_RHI_LIB)
#  define MCAD_RHI_EXPORT __declspec(dllexport)
# else
#  define MCAD_RHI_EXPORT __declspec(dllimport)
# endif
#else
# define MCAD_RHI_EXPORT
#endif#pragma once
