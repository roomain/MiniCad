#pragma once
/***********************************************
* @headerfile MCadRHITextureManager.h
* @date 18 / 01 / 2024
* @author Roomain
************************************************/
#include <memory>
#include <unordered_map>
#include <string>
#include "MCadSingletonMacro.h"
#include "TMCadRHIResourceManager.h"
#include "MCad_RHI_globals.h"

class MCadRHITexture;

using MCadRHITexturePtr = TMCadRHIRHIShared_ptr<MCadRHITexture>;

/*@brief interface for texture manager*/
class MCAD_RHI_EXPORT MCadRHITextureManager : public TMCadRHIResourceManager<MCadRHITexturePtr>
{
	NOT_COPIABLE(MCadRHITextureManager)

public:
	MCadRHITextureManager( );
	virtual ~MCadRHITextureManager( );
	MCadRHITexturePtr loadTexture(const std::string& a_filename);
};