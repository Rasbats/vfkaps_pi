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
#include "tinyxml.h"
#include <list>
#include <wx/textctrl.h>

using namespace std;



class Position{
public:

	wxString lat, lon, wpt_num;
	Position *prev, *next; /* doubly linked circular list of positions */
	int routepoint;

};

class vfkaps_pi;
class PlugIn_ViewPort;
class vfkapsOverlayFactory;


class Dlg : public m_dialog
{
public:
	Dlg(wxWindow *parent, vfkaps_pi *ppi);
	~Dlg();

		void SetViewPort(PlugIn_ViewPort *vp);

		Position m_position;
		list<Position> myPositions;

		double chartScale;
		double centreLat;
		double centreLon;

		wxWindow *pParent;
		vfkaps_pi *pPlugIn;

		//void AddPosition(double m_cursor_lat, double m_cursor_lon);

		bool cancelled;

		wxString             m_sUseSat;
		wxString             m_sUseDirectory;
		wxString             m_sUseKey;

		void DrawBox(double lat, double lon);

private:

		wxString sLat;
		wxString sLon;

		void OnCancel(wxCommandEvent& event);
		void OnGenerateKAP(wxCommandEvent& event);

	    void OnClose( wxCloseEvent& event );
        double lat1, lon1, lat2, lon2;
        bool error_found;
        bool dbg;

		bool m_bTransferComplete;
		bool m_bTransferSuccess;


		wxString OnPrepare(int zoom, double centerLat, double centerLon, int scale, wxString satType, wxString key);
		void onDLEvent(OCPN_downloadEvent &ev);
		int GetScale(double myChartScale);

		wxString        m_totalsize;
		wxString        m_transferredsize;

		bool m_bconnected;


		bool write_file;

		wxString     m_gpx_path;

		PlugIn_ViewPort  *m_vp;

};


#endif
