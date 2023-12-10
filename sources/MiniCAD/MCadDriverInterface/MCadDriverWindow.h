#pragma once
/***********************************************
* @headerfile MCadDriverWindow.h
* @date 23 / 11 / 2023
* @author Roomain
************************************************/
#include <memory>
#include <vector>
#include "MCadEvent.h"

class MCadDriverViewport;
using MCadDriverViewportPtr = std::shared_ptr<MCadDriverViewport>;
struct MCadViewportSeparator;

/*@brief represents a window*/
class MCadDriverWindow
{
private:
	int m_windowWidth;			/*!< window width in pixels*/
	int m_windowHeight;			/*!< window height in pixels*/

	//viewport manager + separator manager
	
	// TODO Separator callbacks (hoover, move, selection)
	void onMouseEvent(/*TODO*/);
	void onKeyboardEvent(/*TODO*/);
	void onResizeEvent(/*TODO*/);

public:
	// separator management
	// imgui
	void onEvent(const MCadEvent& m_event);

};

