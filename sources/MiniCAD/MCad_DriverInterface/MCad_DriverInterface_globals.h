#pragma once

#ifndef BUILD_STATIC
# if defined(MCAD_DRIVER_INTERFACE_LIB)
#  define MCAD_DRIVER_INTERFACE_EXPORT __declspec(dllexport)
# else
#  define MCAD_DRIVER_INTERFACE_EXPORT __declspec(dllimport)
# endif
#else
# define MCAD_DRIVER_INTERFACE_EXPORT
#endif#pragma once
