#include "pch.h"
#include <ranges>
#include <algorithm>
#include <functional>
#include "MCadViewport.h"

void MCadViewport::moveFromTop(MCadViewportEvent& a_event)
{
	if ( std::ranges::find(a_event.m_exception, this) == a_event.m_exception.cend( ) )
	{
		m_top += a_event.m_movement.y;
		a_event.m_exception.emplace_back(this);
		std::ranges::for_each(m_topViewports, [ &a_event ] (auto& a_viewport)
			{
				a_viewport.lock()->moveFromBottom(a_event);
			});
	}
}

void MCadViewport::moveFromBottom(MCadViewportEvent& a_event)
{
	if ( std::ranges::find(a_event.m_exception, this) == a_event.m_exception.cend( ) )
	{
		m_bottom += a_event.m_movement.y;
		a_event.m_exception.emplace_back(this);
		std::ranges::for_each(m_topViewports, [ &a_event ] (auto& a_viewport)
			{
				a_viewport.lock( )->moveFromTop(a_event);
			});
	}
}

void MCadViewport::moveFromLeft(MCadViewportEvent& a_event)
{
	if ( std::ranges::find(a_event.m_exception, this) == a_event.m_exception.cend( ) )
	{
		m_left += a_event.m_movement.x;
		a_event.m_exception.emplace_back(this);
		std::ranges::for_each(m_topViewports, [ &a_event ] (auto& a_viewport)
			{
				a_viewport.lock( )->moveFromRight(a_event);
			});
	}
}

void MCadViewport::moveFromRight(MCadViewportEvent& a_event)
{
	if ( std::ranges::find(a_event.m_exception, this) == a_event.m_exception.cend( ) )
	{
		m_right += a_event.m_movement.x;
		a_event.m_exception.emplace_back(this);
		std::ranges::for_each(m_topViewports, [ &a_event ] (auto& a_viewport)
			{
				a_viewport.lock( )->moveFromLeft(a_event);
			});
	}
}


MCadViewport::MCadViewport( ) :
	m_top{ 0 }, m_bottom{ 0 }, m_left{ 0 }, m_right{ 0 }
{
	//
}

MCadViewport::MCadViewport(const float a_top, const float a_bottom, const float a_left, const float a_right):
	m_top{a_top}, m_bottom{a_bottom}, m_left{a_left}, m_right{a_right}
{
	//
}

MCadViewport::~MCadViewport( )
{
	// TODO
}

Border MCadViewport::selectedBorder(const glm::vec2& a_pos, const glm::vec2& a_epsylon)const
{
	if ( ( m_top - a_epsylon.y ) < a_pos.y )
	{
		return Border::Top;
	}
	else if ( ( m_bottom + a_epsylon.y ) > a_pos.y )
	{
		return Border::Bottom;
	}
	else if ( ( m_right - a_epsylon.x ) < a_pos.x )
	{
		return Border::Right;
	}
	else if ( ( m_left + a_epsylon.x ) > a_pos.x )
	{
		return Border::Left;
	}
	return Border::None;
}


void MCadViewport::addTop(const MCadViewportWPtr& a_pViewport)
{
	m_topViewports.emplace_back(a_pViewport);
}

void MCadViewport::addBottom(const MCadViewportWPtr& a_pViewport)
{
	m_bottomViewports.emplace_back(a_pViewport);
}

void MCadViewport::addLeft(const MCadViewportWPtr& a_pViewport)
{
	m_leftViewports.emplace_back(a_pViewport);
}

void MCadViewport::addRight(const MCadViewportWPtr& a_pViewport)
{
	m_rightViewports.emplace_back(a_pViewport);
}

void MCadViewport::remove(std::vector<MCadViewportWPtr>& a_vector, const MCadViewportWPtr& a_pviewport)
{
	auto iter = std::find(a_vector.begin( ), a_vector.end( ), a_pviewport);
	if ( iter != a_vector.end( ) )
		a_vector.erase(iter);
}

void MCadViewport::removeFromTop(const MCadViewportWPtr& a_pViewport)
{
	remove(m_topViewports, a_pViewport);
}

void MCadViewport::removeFromBottom(const MCadViewportWPtr& a_pViewport)
{
	remove(m_bottomViewports, a_pViewport);
}

void MCadViewport::removeFromLeft(const MCadViewportWPtr& a_pViewport)
{
	remove(m_leftViewports, a_pViewport);
}

void MCadViewport::removeFromRight(const MCadViewportWPtr& a_pViewport)
{
	remove(m_rightViewports, a_pViewport);
}


void MCadViewport::onEvent(MCadViewportEvent& a_event)
{
	switch ( a_event.m_selectedBorder )
	{
	case Border::None:
		break;
	case Border::Top:
		moveFromTop(a_event);
		break;
	case Border::Bottom:
		moveFromBottom(a_event);
		break;
	case Border::Left:
		moveFromLeft(a_event);
		break;
	case Border::Right:
		moveFromRight(a_event);
		break;
	}
}

void MCadViewport::updateOrganisation(const std::vector<MCadViewportPtr>& a_vViewports)
{
	m_topViewports.clear();
	m_bottomViewports.clear( );
	m_leftViewports.clear( );
	m_rightViewports.clear( );
	for ( auto& pViewport : a_vViewports )
	{
		if ( pViewport.get( ) != this )
		{
			if ( m_top - pViewport->m_bottom < EPSYLON )
			{
				// top
				m_topViewports.emplace_back(pViewport);
			}
			else if ( m_bottom - pViewport->m_top < EPSYLON )
			{
				// bottom
				m_bottomViewports.emplace_back(pViewport);
			}
			else if ( m_right - pViewport->m_left < EPSYLON )
			{
				// right
				m_rightViewports.emplace_back(pViewport);
			}
			else if ( m_left - pViewport->m_right < EPSYLON )
			{
				// left
				m_leftViewports.emplace_back(pViewport);
			}
		}
	}
}