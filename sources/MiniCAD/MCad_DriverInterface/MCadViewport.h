#pragma once
/***********************************************
* @headerfile MCadDriverWindow.h
* @date 29 / 11 / 2023
* @author Roomain
************************************************/
#include <memory>
#include "glm/glm.hpp"
#include "MCadViewportEvent.h"
#include "MCad_DriverInterface_globals.h"

#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)

class MCadViewport;
using MCadViewportWPtr = std::weak_ptr<MCadViewport>;
using MCadViewportPtr = std::shared_ptr<MCadViewport>;

struct MCadMouseEvent;

/*@brief viewport is a part of non directional graph*/
class MCAD_DRIVER_INTERFACE_EXPORT MCadViewport
{
private:
	static constexpr float EPSYLON = 0.01f;
	bool m_bSelect = false;	/*!< selection flag*/
	float m_top;			/*!<top coordinate in percentage [0, 1]*/
	float m_bottom;			/*!<bottom coordinate in percentage [0, 1]*/
	float m_left;			/*!<left coordinate in percentage [0, 1]*/
	float m_right;			/*!<right coordinate in percentage [0, 1]*/

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
		return ( m_right - m_left ) > 0.2 && ( m_top - m_bottom ) > 0.2;
	}

	virtual void setSelected(const bool a_bSelect) { m_bSelect = a_bSelect; }
	constexpr bool selected( )const { return  m_bSelect; }

	virtual void addTop(const MCadViewportWPtr& a_pViewport);
	virtual void addBottom(const MCadViewportWPtr& a_pViewport);
	virtual void addLeft(const MCadViewportWPtr& a_pViewport);
	virtual void addRight(const MCadViewportWPtr& a_pViewport);
	
	virtual void removeFromTop(const MCadViewportWPtr& a_pViewport);
	virtual void removeFromBottom(const MCadViewportWPtr& a_pViewport);
	virtual void removeFromLeft(const MCadViewportWPtr& a_pViewport);
	virtual void removeFromRight(const MCadViewportWPtr& a_pViewport);

	void onEvent(MCadViewportEvent& a_event);
	virtual void writeMousePosition(MCadMouseEvent& a_event) = 0;
	void updateOrganisation(const std::vector<MCadViewportPtr>& a_vViewports);

	[[nodiscard]] constexpr float top( )const { return m_top; }
	[[nodiscard]] constexpr float bottom( )const { return m_bottom; }
	[[nodiscard]] constexpr float left( )const { return m_left; }
	[[nodiscard]] constexpr float right( )const { return m_right; }
};


#pragma warning(pop)