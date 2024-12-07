//========= Copyright OpenMod, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//

#ifndef BASEMENU_H
#define BASEMENU_H
#ifdef _WIN32
#pragma once
#endif

#include "vgui_controls/Panel.h"
#include "GameUI/IGameUI.h"
#include <vgui/VGUI.h>
#include <vgui_controls/HTML.h>
#include "steam/steamclientpublic.h"
#include "vgui/IVGui.h"

namespace vgui
{
	class Panel;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class CMapLoadBG : public vgui::EditablePanel
{
	DECLARE_CLASS_SIMPLE(CMapLoadBG, vgui::EditablePanel);

public:
	CMapLoadBG(char const* panelName);
	~CMapLoadBG();

	void SetEnable( bool enabled );

protected:
	void ApplySchemeSettings(vgui::IScheme* pScheme);

private:
	vgui::HTML *HHPanel;
};
 
//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class RootPanel : public vgui::Panel
{
	DECLARE_CLASS_SIMPLE( RootPanel, vgui::Panel );
public:
	RootPanel(vgui::VPANEL parent);
	virtual ~RootPanel();

	IGameUI*		GetGameUI();

    // elements
    vgui::HTML *m_pHTMLPanel;

protected:
	virtual void	ApplySchemeSettings(vgui::IScheme *pScheme);

private:
	bool			LoadGameUI();

	int				m_ExitingFrameCount;
	bool			m_bCopyFrameBuffer;

	IGameUI*		gameui;
};

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class IOverrideInterface
{
public:
	virtual void		Create( vgui::VPANEL parent ) = 0;
	virtual vgui::VPANEL	GetPanel( void ) = 0;
	virtual void		Destroy( void ) = 0;

    virtual RootPanel *GetMenuBase() = 0;
};

extern RootPanel *guiroot;
extern IOverrideInterface *OverrideUI;

void OverrideRootUI(void);

// spawnmenu
class SMLPanel
{
public:
	virtual void		Create(vgui::VPANEL parent) = 0;
	virtual void		Destroy(void) = 0;
	virtual void		Activate(void) = 0;
};

extern SMLPanel* smlmenu;

#endif