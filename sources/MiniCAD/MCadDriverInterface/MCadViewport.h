#pragma once
/***********************************************
* @headerfile MCadDriverWindow.h
* @date 29 / 11 / 2023
* @author Roomain
************************************************/
#include <memory>
#include "glm/glm.hpp"
#include "MCadViewportEvent.h"

class MCadViewport;
using MCadViewportWPtr = std::weak_ptr<MCadViewport>;
using MCadViewportPtr = std::shared_ptr<MCadViewport>;



/*@brief viewport is a part of non directional graph*/
class MCadViewport
{
private:
	static constexpr float EPSYLON = 0.01f;

	float m_top;		/*!<top coordinate in percentage [0, 1]*/
	float m_bottom;		/*!<bottom coordinate in percentage [0, 1]*/
	float m_left;		/*!<left coordinate in percentage [0, 1]*/
	float m_right;		/*!<right coordinate in percentage [0, 1]*/

	std::vector<MCadViewportWPtr> m_topViewports;
	std::vector<MCadViewportWPtr> m_bottomViewports;
	std::vector<MCadViewportWPtr> m_leftViewports;
	std::vector<MCadViewportWPtr> m_rightViewports;

	virtual void moveFromTop(MCadViewportEvent& a_event);
	virtual void moveFromBottom(MCadViewportEvent& a_event);
	virtual void moveFromLeft(MCadViewportEvent& a_event);
	virtual void moveFromRight(MCadViewportEvent& a_event);

	static void remove(std::vector<MCadViewportWPtr>& a_vector, const MCadViewportWPtr& a_pviewport);

public:
	MCadViewport( );
	explicit MCadViewport(const float a_top, const float a_bottom, const float a_left, const float a_right);
	virtual ~MCadViewport( );

	[[nodiscard]] Border selectedBorder(const glm::vec2& a_pos, const glm::vec2& a_epsylon)const;

	[[nodiscard]] constexpr bool contains(const glm::vec2& a_pos)const
	{
		return (a_pos.x > m_left) && (a_pos.x < m_right) && (a_pos.y > m_bottom) && (a_pos.y < m_top);
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

	void onEvent(MCadViewportEvent& a_event);

	void updateOrganisation(const std::vector<MCadViewportPtr>& a_vViewports);
};