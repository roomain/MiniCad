#pragma once
/***********************************************
* @headerfile MCadDriverWindow.h
* @date 23 / 11 / 2023
* @author Roomain
************************************************/
#include <memory>
#include <vector>
#include "MCadEvent.h"
#include "MCadViewportEvent.h"
#include "MCad_DriverInterface_globals.h"



#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)

class MCadViewport;
using MCadViewportPtr = std::shared_ptr<MCadViewport>;
struct MCadViewportSeparator;

/*@brief represents a window*/
class MCAD_DRIVER_INTERFACE_EXPORT  MCadDriverWindow
{
private:
	float m_windowWidth;			/*!< window width in pixels*/
	float m_windowHeight;			/*!< window height in pixels*/
	MCadViewportEvent m_vpEvnt;		/*!< event to transmit to viewport*/
	MCadViewportPtr m_currentViewport;

	glm::vec2 m_epsylon;
	std::vector<MCadViewportPtr> m_viewportList;
	
	void writeMousePosition(MCadMouseEvent& a_event);

	virtual void onMouseEvent(MCadMouseEvent& a_event);
	MCadViewportPtr getviewport(const glm::vec2& a_pos);
	void updateViewportOrganisation( );

	virtual void onKeyboardEvent(MCadKeyboardEvent& a_event);
	virtual void onResizeEvent(MCadResizeEvent& a_event);

	virtual MCadViewportPtr viewportFactory(const float a_top, const float a_bottom, const float a_left, const float a_right) = 0;

	void setup_OneViewport( );
	void setup_OneLeftTwoRight( );
	void setup_TwoLeftTwoRight( );
	void setup_TwoLeftOneRight( );
	void setup_OneTopTwoBottom( );
	void setup_TwoTopOneBottom( );

public:
	MCadDriverWindow(const float a_width, const float a_height);
	virtual ~MCadDriverWindow( ) = default;

	void onEvent(MCadEvent& m_event);

	// viewport management
	enum class ViewportMapping
	{
		OneViewport,			/*!< only one viewport*/
		OneLeftTwoRight,
		TwoLeftTwoRight,
		TwoLeftOneRight,
		OneTopTwoBottom,
		TwoTopOneBottom
	};

	void setupViewport(const ViewportMapping a_mapping);
	[[nodiscard]] inline MCadViewportPtr currentViewport( )const { return m_currentViewport; }
	[[nodiscard]] constexpr int viewportCount( )const { return static_cast< int >( m_viewportList.size() ); }
	[[nodiscard]] inline MCadViewportPtr viewportAt(const int a_index)const {return m_viewportList[ a_index ];}
};


#pragma warning(pop)