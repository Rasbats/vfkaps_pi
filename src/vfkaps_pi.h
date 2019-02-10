/******************************************************************************
 *
 * Project:  vfkaps
 * Purpose:  vfkaps Plugin
 * Author:   Mike Rossiter
 *
 ***************************************************************************
 *   Copyright (C) 2017 by Mike Rossiter                                   *
 *   $EMAIL$                                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 */

#ifndef _CALCULATOR_PI_H_
#define _CALCULATOR_PI_H_

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
  #include <wx/glcanvas.h>
#endif //precompiled headers

#include <wx/fileconf.h>

#include "ocpn_plugin.h" //Required for OCPN plugin functions
#include "vfkapsgui_impl.h"
#include "vfkapsOverlayFactory.h"

#define     MY_API_VERSION_MAJOR    1
#define     MY_API_VERSION_MINOR    13

#define     PLUGIN_VERSION_MAJOR    1
#define     PLUGIN_VERSION_MINOR    1



//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------

#define CALCULATOR_TOOL_POSITION    -1          // Request default positioning of toolbar tool

class vfkaps_pi : public opencpn_plugin_113
{
public:
      vfkaps_pi(void *ppimgr);
	   ~vfkaps_pi(void);

//    The required PlugIn Methods
      int Init(void);
      bool DeInit(void);

      int GetAPIVersionMajor();
      int GetAPIVersionMinor();
      int GetPlugInVersionMajor();
      int GetPlugInVersionMinor();
      wxBitmap *GetPlugInBitmap();
      wxString GetCommonName();
      wxString GetShortDescription();
      wxString GetLongDescription();

//    The required override PlugIn Methods
      int GetToolbarToolCount(void);
      void OnToolbarToolCallback(int id);
     

//    Optional plugin overrides
      void SetColorScheme(PI_ColorScheme cs);
	  void ShowPreferencesDialog(wxWindow* parent);


//    The override PlugIn Methods
	  bool RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp);
	  bool RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp);	  

//    Other public methods
      void SetCalculatorDialogX         (int x){ m_route_dialog_x = x;};
      void SetCalculatorDialogY         (int x){ m_route_dialog_y = x;};
      void SetCalculatorDialogWidth     (int x){ m_route_dialog_width = x;};
      void SetCalculatorDialogHeight    (int x){ m_route_dialog_height = x;};      
	  void OnvfkapsDialogClose(bool dbUpdate = false);

	  MyOverlayFactory *GetMyOverlayFactory(){ return m_pOverlayFactory; }
      MyOverlayFactory *m_pOverlayFactory; 
	  
	  // For preferences
	  int m_iChoiceSat; 	
	  wxString m_sCopyUseDirectory;
	  wxString m_sCopyUseKey;
	  wxString m_sCopyUseMultiKap;

	  wxWindow         *m_parent_window;
private:

	  void OnClose( wxCloseEvent& event );
	  
	  wxFileConfig     *m_pconfig;
      
      bool             LoadConfig(void);
      bool             SaveConfig(void);
      Dlg              *m_pDialog;
      int              m_route_dialog_x, m_route_dialog_y,m_route_dialog_width,m_route_dialog_height;
      int              m_display_width, m_display_height;      
      int              m_leftclick_tool_id;
      bool             m_ShowHelp,m_bCaptureCursor,m_bCaptureShip;
	  bool             m_bvfkapsShowIcon;
	  bool             m_bShowvfkaps;

	  int              m_position_menu_id;


};

#endif
