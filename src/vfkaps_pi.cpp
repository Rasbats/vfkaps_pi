/******************************************************************************
 *
 * Project:  vfkaps
 * Purpose:  vfkaps Plugin
 * Author:   Mike Rossiter
 *
 ***************************************************************************
 *   Copyright (C) 2017 by Mike Rossiter                                *
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

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include "vfkaps_pi.h"
#include "vfkapsgui_impl.h"
#include "vfkapsgui.h"
#include <wx/statbox.h>


//class vfkaps_pi;

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return new vfkaps_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}

//---------------------------------------------------------------------------------------------------------
//
//    vfkaps PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

#include "icons.h"

//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

vfkaps_pi::vfkaps_pi(void *ppimgr)
      :opencpn_plugin_113 (ppimgr)
{
      // Create the PlugIn icons
      initialize_images();
	  m_bShowvfkaps = false;
}

vfkaps_pi::~vfkaps_pi(void)
{
     delete _img_vfkaps_pi;
     delete _img_vfkaps; 
}

int vfkaps_pi::Init(void)
{
      AddLocaleCatalog( _T("opencpn-vfkaps_pi") );

      // Set some default private member parameters
      m_route_dialog_x = 0;
      m_route_dialog_y = 0;
      ::wxDisplaySize(&m_display_width, &m_display_height);

      //    Get a pointer to the opencpn display canvas, to use as a parent for the POI Manager dialog
      m_parent_window = GetOCPNCanvasWindow();

      //    Get a pointer to the opencpn configuration object
      m_pconfig = GetOCPNConfigObject();

      //    And load the configuration items
      LoadConfig();

      //    This PlugIn needs a toolbar icon, so request its insertion
	if(m_bvfkapsShowIcon)
      m_leftclick_tool_id  = InsertPlugInTool(_T(""), _img_vfkaps, _img_vfkaps, wxITEM_CHECK,
            _("VentureFarther Satellite Charts"), _T(""), NULL,
             CALCULATOR_TOOL_POSITION, 0, this);

      m_pDialog = NULL;

      return (WANTS_OVERLAY_CALLBACK	|
              WANTS_OPENGL_OVERLAY_CALLBACK |	
			  WANTS_ONPAINT_VIEWPORT	|
			  WANTS_CURSOR_LATLON		|
              WANTS_TOOLBAR_CALLBACK    |
              INSTALLS_TOOLBAR_TOOL     |
			  INSTALLS_PLUGIN_CHART		|
			  INSTALLS_PLUGIN_CHART_GL	|
			  WANTS_CONFIG				|
			  WANTS_PREFERENCES 
           );
}

bool vfkaps_pi::DeInit(void)
{
      //    Record the dialog position
      if (NULL != m_pDialog)
      {
            //Capture dialog position
            wxPoint p = m_pDialog->GetPosition();
            SetCalculatorDialogX(p.x);
            SetCalculatorDialogY(p.y);
            m_pDialog->Close();
            delete m_pDialog;
            m_pDialog = NULL;

			m_bShowvfkaps = false;
			SetToolbarItemState( m_leftclick_tool_id, m_bShowvfkaps );

      }	
    
    SaveConfig();

    RequestRefresh(m_parent_window); // refresh main window

    return true;
}

int vfkaps_pi::GetAPIVersionMajor()
{
      return MY_API_VERSION_MAJOR;
}

int vfkaps_pi::GetAPIVersionMinor()
{
      return MY_API_VERSION_MINOR;
}

int vfkaps_pi::GetPlugInVersionMajor()
{
      return PLUGIN_VERSION_MAJOR;
}

int vfkaps_pi::GetPlugInVersionMinor()
{
      return PLUGIN_VERSION_MINOR;
}

wxBitmap *vfkaps_pi::GetPlugInBitmap()
{
      return _img_vfkaps_pi;
}

wxString vfkaps_pi::GetCommonName()
{
      return _T("vfkaps");
}


wxString vfkaps_pi::GetShortDescription()
{
      return _T("VF KAP");
}

wxString vfkaps_pi::GetLongDescription()
{
      return _("Download Satellite Charts from VentureFarther.com");
}

int vfkaps_pi::GetToolbarToolCount(void)
{
      return 1;
}

void vfkaps_pi::SetColorScheme(PI_ColorScheme cs)
{
      if (NULL == m_pDialog)
            return;

      DimeWindow(m_pDialog);
}

void vfkaps_pi::ShowPreferencesDialog(wxWindow* parent)
{
	VFKapsPrefsDialog *Pref = new VFKapsPrefsDialog(parent);

	Pref->m_dirKaps->SetInitialDirectory(m_sCopyUseDirectory);
	wxFileName fn = m_sCopyUseDirectory + _T("\\");
	Pref->m_dirKaps->SetDirName(fn);
	Pref->m_tApiKey->SetValue(m_sCopyUseKey);
	if (m_sCopyUseMultiKap == _T("1")){
		Pref->m_cbUseMultiKap->SetValue(true);
	}
	else{
		Pref->m_cbUseMultiKap->SetValue(false);
	}
	

	if (Pref->ShowModal() == wxID_OK) {		

		wxString copyDirectory = Pref->m_dirKaps->GetPath();
		wxString copyKey = Pref->m_tApiKey->GetValue();
		
		wxString copyMultiKap;
		
		bool mk = Pref->m_cbUseMultiKap->IsChecked();
		if (mk){
			copyMultiKap = _T("1");
		}
		else {
			copyMultiKap = _T("0");
		}	

		if (m_sCopyUseDirectory != copyDirectory) {
			m_sCopyUseDirectory = copyDirectory;
		}

		if (m_sCopyUseKey != copyKey) {
			m_sCopyUseKey = copyKey;
		}

		if (m_sCopyUseMultiKap != copyMultiKap) {
			m_sCopyUseMultiKap = copyMultiKap;
		}
		
		if (m_pDialog)
		{		
			//wxMessageBox(m_sCopyUseMultiKap);
			
			m_pDialog->m_sUseDirectory = m_sCopyUseDirectory;
			m_pDialog->m_sUseKey = m_sCopyUseKey;
			m_pDialog->m_sUseMultiKap = m_sCopyUseMultiKap;

			if (m_sCopyUseMultiKap == _T("0")){
				m_pDialog->m_buttonGenerate->SetLabel(_("Generate Chart"));
				m_pDialog->m_stVFDownloadInfo->SetLabel(_("Waiting for chart download"));
			}
			else if (m_sCopyUseMultiKap == _T("1")){
				m_pDialog->m_buttonGenerate->SetLabel(_("Generate Multi-Charts"));
				m_pDialog->m_stVFDownloadInfo->SetLabel(_("Waiting for multi-chart download"));
			}
			m_pDialog->Fit();
		}				

		SaveConfig();

		RequestRefresh(m_parent_window); // refresh main window
	}

}


void vfkaps_pi::OnToolbarToolCallback(int id)
{
    
	if(NULL == m_pDialog)
      {
            m_pDialog = new Dlg(m_parent_window, this);          
            m_pDialog->Move(wxPoint(m_route_dialog_x, m_route_dialog_y));

			// Create the drawing factory
			m_pOverlayFactory = new MyOverlayFactory(*m_pDialog);
			m_pOverlayFactory->SetParentSize(m_display_width, m_display_height);
      }

	  m_pDialog->Fit();
	  //Toggle 
	  m_bShowvfkaps = !m_bShowvfkaps;	  

      //    Toggle dialog? 
      if(m_bShowvfkaps) {
          m_pDialog->Show();   		    
      } else
          m_pDialog->Hide();
     
      // Toggle is handled by the toolbar but we must keep plugin manager b_toggle updated
      // to actual status to ensure correct status upon toolbar rebuild
      SetToolbarItemState( m_leftclick_tool_id, m_bShowvfkaps );

      RequestRefresh(m_parent_window); // refresh main window
}

bool vfkaps_pi::LoadConfig(void)
{
      wxFileConfig *pConf = (wxFileConfig *)m_pconfig;  

      if(pConf)
      {
            pConf->SetPath ( _T( "/Settings/vfkaps_pi" ) );
			pConf->Read ( _T( "showvfkapsIcon" ), &m_bvfkapsShowIcon, 1 );

			wxString tempSat;
			pConf->Read(_T("satsource"), &tempSat);
			m_iChoiceSat = wxAtoi(tempSat);
			
		    pConf->Read(_T("kapdirectory"), &m_sCopyUseDirectory);
			pConf->Read(_T("apikey"), &m_sCopyUseKey);
			pConf->Read(_T("multikap"), &m_sCopyUseMultiKap);
           
            m_route_dialog_x =  pConf->Read ( _T ( "DialogPosX" ), 20L );
            m_route_dialog_y =  pConf->Read ( _T ( "DialogPosY" ), 20L );
         
            if((m_route_dialog_x < 0) || (m_route_dialog_x > m_display_width))
                  m_route_dialog_x = 5;
            if((m_route_dialog_y < 0) || (m_route_dialog_y > m_display_height))
                  m_route_dialog_y = 5;
            return true;
      }
      else
            return false;
}

bool vfkaps_pi::SaveConfig(void)
{
	  
      
	  wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

      if(pConf)
      {
            pConf->SetPath ( _T ( "/Settings/vfkaps_pi" ) );
			pConf->Write ( _T ( "ShowvfkapsIcon" ), m_bvfkapsShowIcon );

			
			wxString tempSat;
			tempSat = wxString::Format(wxT("%i"), m_iChoiceSat);

			pConf->Write(_T("satsource"), tempSat);			
			pConf->Write(_T("kapdirectory"), m_sCopyUseDirectory);
			pConf->Write(_T("apikey"), m_sCopyUseKey);
			pConf->Write(_T("multikap"), m_sCopyUseMultiKap);			
          
            pConf->Write ( _T ( "DialogPosX" ),   m_route_dialog_x );
            pConf->Write ( _T ( "DialogPosY" ),   m_route_dialog_y );
            
            return true;
      }
      else
            return false;
}

void vfkaps_pi::OnvfkapsDialogClose()
{
    m_bShowvfkaps = false;
    SetToolbarItemState( m_leftclick_tool_id, m_bShowvfkaps );
    m_pDialog->Hide();
    SaveConfig();

    RequestRefresh(m_parent_window); // refresh main window

}

bool vfkaps_pi::RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp)
{
	if (!m_pDialog ||
		!m_pDialog->IsShown() ||
		!m_pOverlayFactory)
		return false;

	m_pDialog->SetViewPort(vp);
	m_pDialog->MakeBoxPoints();
	m_pOverlayFactory->RenderMyOverlay(dc, vp);

	return true;
}

bool vfkaps_pi::RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp)
{
	if (!m_pDialog ||
		!m_pDialog->IsShown() ||
		!m_pOverlayFactory)
		return false;	

	m_pDialog->SetViewPort(vp);	
	m_pDialog->MakeBoxPoints();
	m_pOverlayFactory->RenderMyGLOverlay(pcontext, vp);

	return true;

	
}

