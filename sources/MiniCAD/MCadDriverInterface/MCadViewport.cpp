#include "pch.h"
#include <ranges>
#include <algorithm>
#include <functional>
#include "MCadViewport.h"

void MCadViewport::moveFromTop(const float a_move)
{
	m_top += a_move;
}

void MCadViewport::moveFromBottom(const float a_move)
{
	m_bottom += a_move;
}

void MCadViewport::moveFromLeft(const float a_move)
{
	m_left += a_move;
}

void MCadViewport::moveFromRight(const float a_move)
{
	m_right += a_move;
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


void MCadViewport::moveTop(const float a_move)
{
	moveFromTop(a_move);
	std::for_each(m_bottomViewports.begin( ), m_bottomViewports.end( ),
		std::bind_front(&MCadViewport::moveFromBottom));
}

void MCadViewport::moveBottom(const float a_move)
{
	moveFromBottom(a_move);
	std::for_each(m_bottomViewports.begin( ), m_bottomViewports.end( ),
		std::bind_front(&MCadViewport::moveFromTop));
}

void MCadViewport::moveLeft(const float a_move)
{
	moveFromLeft(a_move);
	std::for_each(m_leftViewports.begin( ), m_leftViewports.end( ),
		std::bind_front(&MCadViewport::moveFromRight));
}

void MCadViewport::moveRight(const float a_move)
{
	moveFromRight(a_move);
	std::for_each(m_rightViewports.begin( ), m_rightViewports.end( ),
		std::bind_front(&MCadViewport::moveFromLeft));
}
