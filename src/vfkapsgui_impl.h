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

#ifndef _CALCULATORGUI_IMPL_H_
#define _CALCULATORGUI_IMPL_H_

#ifdef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "vfkapsgui.h"
#include "ocpn_plugin.h"
#include <wx/textctrl.h>

#define PI 3.1415926535897931160E0 /* pi */

class vfkaps_pi;
class PlugIn_ViewPort;
class vfkapsOverlayFactory;

class Dlg : public m_dialog
{
public:
	Dlg(wxWindow *parent, vfkaps_pi *ppi);
	~Dlg();
			
		void SetViewPort(PlugIn_ViewPort *vp);
		
		double chartScale;
		double centreLat;
		double centreLon;

		wxWindow *pParent;
		vfkaps_pi *pPlugIn;

		wxString             m_sUseSat;
		wxString             m_sUseDirectory;
		wxString             m_sUseKey;
		wxString             m_sUseMultiKap;

		bool m_bMoveUpDownLeftRight;

		PlugIn_ViewPort  *m_vp, m_current_vp;	
		PlugIn_ViewPort &GetCurrentViewPort() { return m_current_vp; }

		wxPoint myPixArray[5];
		int myPixHeight;
		void MakeBoxPoints();
		
private:	
		int myZoom;
	    int sessionCount;
		

		wxString sLat;
		wxString sLon;
		wxString file_path;
		wxArrayString myChartFileNameArray;

		void OnGenerateKAP(wxCommandEvent& event);
		void OnDeleteLastDownload(wxCommandEvent& event);
		void OnChooseSat(wxCommandEvent& event);
		bool CheckForDuplicateFileName(wxString dirname, wxString filename); // Not used at present
		void ExtractData(wxString filename);
		bool ExtractZipFiles(const wxString& aZipFile, const wxString& aTargetDir);

		void OnButtonCentre(wxCommandEvent &event);

		void OnButtonUp(wxCommandEvent &event);
		void OnButtonRight(wxCommandEvent &event);
		void OnButtonDown(wxCommandEvent &event);
		void OnButtonLeft(wxCommandEvent &event);

	    void OnClose( wxCloseEvent& event );

        bool dbg;		
		
		wxString OnPrepare(int zoom, double centerLat, double centerLon, int scale, wxString satType, wxString key, wxString multikap);
		int GetScale(double myChartScale);
				
		

};


#endif
