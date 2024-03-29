#include "pch.h"
#include <ranges>
#include <execution>
#include "MCadDriverWindow.h"
#include "MCadViewport.h"

void MCadDriverWindow::updateViewportOrganisation( )
{
	std::for_each(std::execution::par, m_viewportList.begin( ), m_viewportList.end( ), [ this ] (auto&& a_pViewport)
		{
			a_pViewport->updateOrganisation(m_viewportList);
		});
}

void MCadDriverWindow::onMouseEvent(MCadMouseEvent& a_event)
{
	// get mouse position
	writeMousePosition(a_event);
	m_vpEvnt.m_movement = glm::vec2(0, 0);
	switch ( a_event.m_type )
	{
	case MouseEventType::Mouse_Press:
	{
		for ( auto pViewport : m_viewportList )
		{
			if ( pViewport->contains(a_event.m_mouseCoords.m_windowCoords) )
			{
				m_currentViewport = pViewport;
				break;
			}
		}

		if ( m_currentViewport )
			m_currentViewport->setSelected(false);

		m_vpEvnt.m_lastPos = a_event.m_mouseCoords.m_windowCoords;
		if ( m_currentViewport = getviewport(a_event.m_mouseCoords.m_windowCoords) )
		{
			m_currentViewport->writeMousePosition(a_event);
			m_vpEvnt.m_selectedBorder = m_currentViewport->selectedBorder(a_event.m_mouseCoords.m_windowCoords, m_epsylon);
			m_currentViewport->setSelected(true);
		}
	}
		break;
	case MouseEventType::Mouse_Release:
	{
		if ( m_currentViewport )
			m_currentViewport->setSelected(false);

		m_vpEvnt.m_lastPos = a_event.m_mouseCoords.m_windowCoords;
		if ( m_currentViewport = getviewport(a_event.m_mouseCoords.m_windowCoords) )
		{
			m_currentViewport->writeMousePosition(a_event);
			// TODO
			m_currentViewport->setSelected(true);
		}
	}
		break;
	case MouseEventType::Mouse_DoubleClick:
	{
		//
	}
		break;
	case MouseEventType::Mouse_Move:
	{
		m_vpEvnt.m_movement = a_event.m_mouseCoords.m_windowCoords - m_vpEvnt.m_lastPos;
		m_vpEvnt.m_lastPos = a_event.m_mouseCoords.m_windowCoords;
		if ( m_currentViewport )
		{
			m_currentViewport->writeMousePosition(a_event);
			m_currentViewport->onEvent(m_vpEvnt);
			updateViewportOrganisation( );
		}
	}
		break;
	}
}

MCadViewportPtr MCadDriverWindow::getviewport(const glm::vec2& a_pos)
{
	auto iter = std::ranges::find_if(m_viewportList, [ a_pos ] (auto& a_pViewport)
		{
			return a_pViewport->contains(a_pos);
		});
	
	if ( iter != m_viewportList.cend( ) )
		return *iter;

	return MCadViewportPtr();
}

void MCadDriverWindow::onKeyboardEvent(MCadKeyboardEvent& a_event)
{
	// TODO
}

void MCadDriverWindow::onResizeEvent(MCadResizeEvent& a_event)
{
	m_windowWidth = static_cast<float>(a_event.m_newWidth);
	m_windowHeight = static_cast< float >(a_event.m_newHeight);
	if ( m_windowWidth > 0 && m_windowHeight > 0 )
	{
		m_epsylon.x = 5.0f / m_windowWidth;
		m_epsylon.y = 5.0f / m_windowHeight;
	}
}

MCadDriverWindow::MCadDriverWindow(const float a_width, const float a_height) :
	m_windowWidth{ a_width }, m_windowHeight{ a_height }
{
	if ( m_windowWidth > 0 && m_windowHeight > 0 )
	{
		m_epsylon.x = 5.0f / m_windowWidth;
		m_epsylon.y = 5.0f / m_windowHeight;
	}
}

void MCadDriverWindow::onEvent(MCadEvent& m_event)
{
	switch ( m_event.m_type )
	{
	case MCadEvent::EventType::Keyboard_event:
		onKeyboardEvent(std::get<MCadKeyboardEvent>(m_event.m_internalEvent));
		break;
	case MCadEvent::EventType::Mouse_event:
		onMouseEvent(std::get<MCadMouseEvent>(m_event.m_internalEvent));
		break;
	case MCadEvent::EventType::Selection_event:
		// TODO
		break;
	case MCadEvent::EventType::Resize_event:
		onResizeEvent(std::get<MCadResizeEvent>(m_event.m_internalEvent));
		break;
	default:
		break;
	}
}

void MCadDriverWindow::writeMousePosition(MCadMouseEvent& a_event)
{
	if ( m_windowWidth > 0 && m_windowHeight > 0 )
	{
		a_event.m_mouseCoords.m_windowCoords.x = static_cast< float >( a_event.m_mouseCoords.m_screenCoords.x ) / m_windowWidth;
		a_event.m_mouseCoords.m_windowCoords.y = 1.0f - static_cast< float >( a_event.m_mouseCoords.m_screenCoords.y ) / m_windowHeight;
	}
}

void MCadDriverWindow::setup_OneViewport( )
{
	m_viewportList.emplace_back(viewportFactory(1.0f, 0.0f, 0.0f, 1.0f));
}

void MCadDriverWindow::setup_OneLeftTwoRight( )
{
	auto pViewportLeft = m_viewportList.emplace_back(viewportFactory(1.0f, 0.0f, 0.0f, 0.5f));
	auto pViewportRightTop = m_viewportList.emplace_back(viewportFactory(1.0f, 0.5f, 0.5f, 1.0f));
	auto pViewportRightBottom = m_viewportList.emplace_back(viewportFactory(0.5f, 0.0f, 0.5f, 1.0f));
	pViewportLeft->addRight(pViewportRightTop);
	pViewportLeft->addRight(pViewportRightBottom);

	pViewportRightTop->addBottom(pViewportRightBottom);
	pViewportRightTop->addLeft(pViewportLeft);

	pViewportRightBottom->addTop(pViewportRightTop);
	pViewportRightBottom->addLeft(pViewportLeft);
}

void MCadDriverWindow::setup_TwoLeftTwoRight( )
{
	auto pViewportLeftTop = m_viewportList.emplace_back(viewportFactory(1.0f, 0.5f, 0.0f, 0.5f));
	auto pViewportLeftBottom = m_viewportList.emplace_back(viewportFactory(0.5f, 0.0f, 0.0f, 0.5f));
	auto pViewportRightTop = m_viewportList.emplace_back(viewportFactory(1.0f, 0.5f, 0.5f, 1.0f));
	auto pViewportRightBottom = m_viewportList.emplace_back(viewportFactory(0.5f, 0.0f, 0.5f, 1.0f));

	pViewportLeftTop->addRight(pViewportRightTop);
	pViewportLeftTop->addBottom(pViewportLeftBottom);

	pViewportLeftBottom->addTop(pViewportLeftTop);
	pViewportLeftBottom->addRight(pViewportRightBottom);
	//-----------------------------------------------------
	pViewportRightTop->addBottom(pViewportRightBottom);
	pViewportRightTop->addLeft(pViewportLeftTop);

	pViewportRightBottom->addTop(pViewportRightTop);
	pViewportRightBottom->addLeft(pViewportLeftBottom);
}

void MCadDriverWindow::setup_TwoLeftOneRight( )
{
	auto pViewportLeftTop = m_viewportList.emplace_back(viewportFactory(1.0f, 0.5f, 0.0f, 0.5f));
	auto pViewportLeftBottom = m_viewportList.emplace_back(viewportFactory(0.5f, 0.0f, 0.0f, 0.5f));
	auto pViewportRight = m_viewportList.emplace_back(viewportFactory(1.0f, 0.0f, 0.5f, 1.0f));
	
	pViewportLeftTop->addRight(pViewportRight);
	pViewportLeftTop->addBottom(pViewportLeftBottom);

	pViewportLeftBottom->addTop(pViewportLeftTop);
	pViewportLeftBottom->addRight(pViewportRight);


	pViewportRight->addLeft(pViewportLeftTop);
	pViewportRight->addLeft(pViewportLeftBottom);
}

void MCadDriverWindow::setup_OneTopTwoBottom( )
{
	auto pViewportTop = m_viewportList.emplace_back(viewportFactory(1.0f, 0.5f, 0.0f, 1.f));
	auto pViewportLeftBottom = m_viewportList.emplace_back(viewportFactory(0.5f, 0.0f, 0.0f, 0.5f));
	auto pViewportRightBottom = m_viewportList.emplace_back(viewportFactory(0.5f, 0.0f, 0.5f, 1.0f));

	pViewportTop->addBottom(pViewportLeftBottom);
	pViewportTop->addBottom(pViewportRightBottom);

	pViewportLeftBottom->addTop(pViewportTop);
	pViewportRightBottom->addTop(pViewportTop);

	pViewportLeftBottom->addRight(pViewportRightBottom);
	pViewportRightBottom->addLeft(pViewportLeftBottom);
}

void MCadDriverWindow::setup_TwoTopOneBottom( )
{
	auto pViewportLeftTop = m_viewportList.emplace_back(viewportFactory(1.0f, 0.5f, 0.0f, 0.5f));
	auto pViewportRightTop = m_viewportList.emplace_back(viewportFactory(1.0f, 0.5f, 0.5f, 1.0f));
	auto pViewportBottom = m_viewportList.emplace_back(viewportFactory(0.5f, 0.0f, 0.0f, 1.f));

	pViewportLeftTop->addRight(pViewportRightTop);
	pViewportRightTop->addLeft(pViewportLeftTop);

	pViewportLeftTop->addBottom(pViewportBottom);
	pViewportRightTop->addBottom(pViewportBottom);

	pViewportBottom->addTop(pViewportLeftTop);
	pViewportBottom->addTop(pViewportRightTop);
}


void MCadDriverWindow::setupViewport(const ViewportMapping a_mapping)
{
	m_viewportList.clear( );
	switch ( a_mapping )
	{
	case ViewportMapping::OneViewport:
		setup_OneViewport( );
		break;

	case ViewportMapping::OneLeftTwoRight:
		setup_OneLeftTwoRight( );
		break;

	case ViewportMapping::TwoLeftTwoRight:
		setup_TwoLeftTwoRight( );
		break;

	case ViewportMapping::TwoLeftOneRight:
		setup_TwoLeftOneRight( );
		break;

	case ViewportMapping::OneTopTwoBottom:
		setup_OneTopTwoBottom( );
		break;

	case ViewportMapping::TwoTopOneBottom:
		setup_TwoTopOneBottom( );
		break;
	}
}