#pragma once
/***********************************************
* @headerfile MCadDriverWindow.h
* @date 29 / 11 / 2023
* @author Roomain
************************************************/
#include <memory>
#include <vector>

class MCadViewport;
using MCadViewportWPtr = std::weak_ptr<MCadViewport>;

/*@brief viewport is a part of non directional graph*/
class MCadViewport
{
private:
	float m_top;		/*!<top coordinate in percentage [0, 1]*/
	float m_bottom;		/*!<bottom coordinate in percentage [0, 1]*/
	float m_left;		/*!<left coordinate in percentage [0, 1]*/
	float m_right;		/*!<right coordinate in percentage [0, 1]*/
	std::vector<MCadViewportWPtr> m_topViewports;
	std::vector<MCadViewportWPtr> m_bottomViewports;
	std::vector<MCadViewportWPtr> m_leftViewports;
	std::vector<MCadViewportWPtr> m_rightViewports;

	virtual void moveFromTop(const float a_move);
	virtual void moveFromBottom(const float a_move);
	virtual void moveFromLeft(const float a_move);
	virtual void moveFromRight(const float a_move);

	static void remove(std::vector<MCadViewportWPtr>& a_vector, const MCadViewportWPtr& a_pviewport);

public:
	MCadViewport( );
	explicit MCadViewport(const float a_top, const float a_bottom, const float a_left, const float a_right);
	virtual ~MCadViewport( );
	[[nodiscard]] constexpr bool contains(const float a_x, const float a_y)const
	{
		return a_x > m_left && a_x < m_right && a_y > m_bottom && a_y < m_top;
	}
	[[nodiscard]] constexpr bool isValid( )const
	{
		return ( m_right - m_right ) > 0.2 && ( m_top - m_bottom ) > 0.2;
	}

	virtual void addTop(const MCadViewportWPtr& a_pViewport);
	virtual void addBottom(const MCadViewportWPtr& a_pViewport);
	virtual void addLeft(const MCadViewportWPtr& a_pViewport);
	virtual void addRight(const MCadViewportWPtr& a_pViewport);
	
	virtual void removeFromTop(const MCadViewportWPtr& a_pViewport);
	virtual void removeFromBottom(const MCadViewportWPtr& a_pViewport);
	virtual void removeFromLeft(const MCadViewportWPtr& a_pViewport);
	virtual void removeFromRight(const MCadViewportWPtr& a_pViewport);
	
	virtual void moveTop(const float a_move);
	virtual void moveBottom(const float a_move);
	virtual void moveLeft(const float a_move);
	virtual void moveRight(const float a_move);
};