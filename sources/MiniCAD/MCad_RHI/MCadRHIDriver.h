#pragma once
/***********************************************
* @headerfile MCadRHIDriver.h
* @date 17 / 01 / 2024
* @author Roomain
************************************************/
#include <memory>
#include "MCadEvent.h"
#include "MCad_RHI_globals.h"

class MCadRHISwapChain;
class MCadRHIShader;
class MCadRHITextureManager;

enum class ImageFormat
{
	RGB_8,
	RGBA_8
	// TODO
};

/*@brief driver interface*/
class MCAD_RHI_EXPORT MCadRHIDriver
{
public:
	/*@brief check hardware compatibility*/
	static bool checkCompatibility(/*extra data*/);


	MCadRHIDriver(/**/);
	virtual ~MCadRHIDriver( );

	// event
	virtual void resize(const MCadResizeEvent& a_event) = 0;

	// factory
	virtual std::weak_ptr<MCadRHISwapChain> createSwapChain(const ImageFormat a_format) = 0;
};