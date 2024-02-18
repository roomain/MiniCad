#pragma once

/***********************************************
* @headerfile MCadViewport_stub.h
* @date 06 / 01 / 2024
* @author Roomain
************************************************/
#include "MCadViewport.h"

class MCadViewport_stub : public MCadViewport
{
public:
	MCadViewport::MCadViewport;
	virtual void writeMousePosition(MCadMouseEvent& a_event) override {}
};