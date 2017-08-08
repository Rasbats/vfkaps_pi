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
*
*/

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

#include <wx/glcanvas.h>
#include <wx/graphics.h>
#include <wx/progdlg.h>

#include "vfkapsgui_impl.h"
#include "vfkapsgui.h"
#include "vfkapsOverlayFactory.h"
#include <vector>


#ifdef __WXMSW__
#define snprintf _snprintf
#endif // __WXMSW__

using namespace std;

class Position;
class Dlg;
class PlugIn_ViewPort;
class wxBoundingBox;


/*
#define NUM_CURRENT_ARROW_POINTS 9
static wxPoint CurrentArrowArray[NUM_CURRENT_ARROW_POINTS] = { wxPoint(0, 0), wxPoint(0, -10),
wxPoint(55, -10), wxPoint(55, -25), wxPoint(100, 0), wxPoint(55, 25), wxPoint(55,
10), wxPoint(0, 10), wxPoint(0, 0)
};

*/

#define NUM_CURRENT_ARROW_POINTS 5
static wxPoint CurrentArrowArray[NUM_CURRENT_ARROW_POINTS] = {
	wxPoint(-320, -320), wxPoint(320, -320),
	wxPoint(320, 320), wxPoint(-320, 320), wxPoint(-320, -320)
};

//----------------------------------------------------------------------------------------------------------
//    otidalroute Overlay Factory Implementation
//-------------------------------------
MyOverlayFactory::MyOverlayFactory(Dlg &gui)
	: m_dlg(gui)
{
	m_bReadyToRender = false;
	
}

MyOverlayFactory::~MyOverlayFactory()
{

	m_bReadyToRender = false;
}

void MyOverlayFactory::reset()
{
	m_bReadyToRender = false;
}

void MyOverlayFactory::setData(Dlg *gui, double lat1, double lon1)
{
	myLat1 = lat1;
	myLon1 = lon1;
	
}

bool MyOverlayFactory::RenderMyGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp)
{
	
	m_dlg.chartScale = vp->chart_scale;

	m_pdc = NULL;  // inform lower layers that this is OpenGL render
    
	if (!m_bReadyToRender) return false;

	m_dlg.chartScale = vp->chart_scale;

	DrawAllLinesInViewPort(vp);

	return true;

}

bool MyOverlayFactory::RenderMyOverlay(wxDC &dc, PlugIn_ViewPort *vp)
{

	if (!m_bReadyToRender) return false;

	m_dlg.chartScale = vp->chart_scale;	

#if wxUSE_GRAPHICS_CONTEXT
	wxMemoryDC *pmdc;
	pmdc = wxDynamicCast(&dc, wxMemoryDC);
	wxGraphicsContext *pgc = wxGraphicsContext::Create(*pmdc);
	m_gdc = pgc;
	m_pdc = &dc;
#else
	m_pdc = &dc;
#endif

	DrawAllLinesInViewPort(vp);

	return true;
}

void MyOverlayFactory::DrawAllLinesInViewPort(PlugIn_ViewPort *BBox)
{

	wxPoint r;
	GetCanvasPixLL(BBox, &r, myLat1, myLon1);

	// Move to the first point
	int x = r.x;
	int y = r.y;

	float xt = CurrentArrowArray[0].x;
	float yt = CurrentArrowArray[0].y;

	int x1 = xt;
	int y1 = yt;

	// Walk thru the point list
	for (int ip = 1; ip < NUM_CURRENT_ARROW_POINTS; ip++) {
		xt = CurrentArrowArray[ip].x;
		yt = CurrentArrowArray[ip].y;
	
		int x2 = xt;
		int y2 = yt;

	    DrawMyLine(x1 + x, y1 + y, x2 + x, y2 + y);
		
		x1 = x2;
		y1 = y2;
	}
	
}


void MyOverlayFactory::DrawMyLine(int x, int y, int x1, int y1)
{	
	wxColour c_blue = wxColour(127, 0, 255);

	wxPen pen(c_blue, 2);
	wxBrush brush(c_blue);

	if (m_pdc) {
		m_pdc->SetPen(pen);
		m_pdc->SetBrush(brush);
	}

	
	if (m_pdc){
		m_pdc->DrawLine(x, y, x1, y1);
	}
	else{
		DrawGLLine(x, y, x1, y1, 2, c_blue);
	}

}

void MyOverlayFactory::DrawGLLine(double x1, double y1, double x2, double y2, double width, wxColour myColour)
{
	{
		wxColour isoLineColor = myColour;
		glColor4ub(isoLineColor.Red(), isoLineColor.Green(), isoLineColor.Blue(),
			255/*isoLineColor.Alpha()*/);

		glPushAttrib(GL_COLOR_BUFFER_BIT | GL_LINE_BIT | GL_ENABLE_BIT |
			GL_POLYGON_BIT | GL_HINT_BIT); //Save state
		{

			//      Enable anti-aliased lines, at best quality
			glEnable(GL_LINE_SMOOTH);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
			glLineWidth(width);

			glBegin(GL_LINES);
			glVertex2d(x1, y1);
			glVertex2d(x2, y2);
			glEnd();
		}

		glPopAttrib();
	}
}