/******************************************************************************
*
* Project:  vfkaps
* Purpose:  vfkaps plugin
* Author:   Mike Rossiter
*
***************************************************************************
*   Copyright (C) 2010 by David S. Register   *
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
*   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
***************************************************************************
*/

#include <map>
#include <wx/string.h>
#include "ocpn_plugin.h"

using namespace std;


//----------------------------------------------------------------------------------------------------------
//    otidalroute Overlay Factory Specification
//----------------------------------------------------------------------------------------------------------

class MyOverlayFactory
{
public:
	MyOverlayFactory(Dlg &gui);
	~MyOverlayFactory();

	bool RenderMyGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp);
	bool RenderMyOverlay(wxDC &dc, PlugIn_ViewPort *vp);

	void SetParentSize(int w, int h) { m_ParentSize.SetWidth(w); m_ParentSize.SetHeight(h); }
	void DrawAllLinesInViewPort(PlugIn_ViewPort *BBox);

	void DrawMyLine(int x, int y, int x1, int y1);
	void DrawGLLine(double x1, double y1, double x2, double y2, double width, wxColour myColour);

	void setData(Dlg *gui, double lat1, double lon1);

    bool m_bReadyToRender;

	void reset();


private:
	wxDC *m_pdc;
	wxGraphicsContext *m_gdc;
	Dlg &m_dlg;

	double myLat1;
	double myLon1;
	double myLat2;
	double myLon2;



	wxSize  m_ParentSize;


	//

};
