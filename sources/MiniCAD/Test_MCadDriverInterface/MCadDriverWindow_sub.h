#pragma once
/***********************************************
* @headerfile MCadDriverWindow_stub.h
* @date 06 / 01 / 2024
* @author Roomain
************************************************/
#include "MCadDriverWindow.h"
#include "MCadViewport_stub.h"

class MCadDriverWindow_stub : public MCadDriverWindow
{
protected:
	virtual MCadViewportPtr viewportFactory(const float a_top, const float a_bottom, const float a_left, const float a_right)
	{
		return std::make_shared< MCadViewport_stub>(a_top, a_bottom, a_left, a_right);
	}

public:
	MCadDriverWindow::MCadDriverWindow;
};