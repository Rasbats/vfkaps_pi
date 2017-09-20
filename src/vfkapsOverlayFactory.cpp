/******************************************************************************
*
* Project:  vfkaps
* Purpose:  vfkaps plugin
* Author:   Mike Rossiter
*
***************************************************************************
*   Copyright (C) 2017 by Mike Rossiter  *
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

class Dlg;
class PlugIn_ViewPort;

//----------------------------------------------------------------------------------------------------------
//    vfkaps_pi Overlay Factory Implementation
//-------------------------------------
MyOverlayFactory::MyOverlayFactory(Dlg &gui)
	: m_dlg(gui)
{
	m_bReadyToRender = true;
}

MyOverlayFactory::~MyOverlayFactory()
{

	m_bReadyToRender = false;
}

void MyOverlayFactory::reset()
{
	m_bReadyToRender = false;
}

void MyOverlayFactory::setData(double lat1, double lon1)
{
	myLat1 = lat1;
	myLon1 = lon1;
}

bool MyOverlayFactory::RenderMyGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp)
{
	
	m_pdc = NULL;  // inform lower layers that this is OpenGL render

	if (!m_bReadyToRender) return false;

	

	if (!m_dlg.m_bMoveUpDownLeftRight){
		setData(vp->clat, vp->clon);
		m_dlg.centreLat = vp->clat;
		m_dlg.centreLon = vp->clon;
		m_dlg.chartScale = vp->chart_scale;
		
		if (m_dlg.m_nVF->GetSelection() == 0)
			DrawAllLinesInViewPort(vp);
		else if (m_dlg.m_nVF->GetSelection() == 1) 
			DrawAllMultiLinesInViewPort(vp);
		else return true;
		//
	}
	else {
		setData(m_dlg.centreLat, m_dlg.centreLon);
		m_dlg.chartScale = vp->chart_scale;
		if (m_dlg.m_nVF->GetSelection() == 0)
			DrawAllLinesInViewPort(vp);
		else if (m_dlg.m_nVF->GetSelection() == 1)
			DrawAllMultiLinesInViewPort(vp);
		else return true;
	}

	return true;

}

bool MyOverlayFactory::RenderMyOverlay(wxDC &dc, PlugIn_ViewPort *vp)
{

#if wxUSE_GRAPHICS_CONTEXT
	wxMemoryDC *pmdc;
	pmdc = wxDynamicCast(&dc, wxMemoryDC);
	wxGraphicsContext *pgc = wxGraphicsContext::Create(*pmdc);
	m_gdc = pgc;
	m_pdc = &dc;
#else
	m_pdc = &dc;
#endif

	if (!m_bReadyToRender) return false;	

	if (!m_dlg.m_bMoveUpDownLeftRight){
		setData(vp->clat, vp->clon);
		m_dlg.centreLat = vp->clat;
		m_dlg.centreLon = vp->clon;
		m_dlg.chartScale = vp->chart_scale;
		if (m_dlg.m_nVF->GetSelection() == 0)
			DrawAllLinesInViewPort(vp);
		else if (m_dlg.m_nVF->GetSelection() == 1)
			DrawAllMultiLinesInViewPort(vp);
		else return true;
	}
	else {
		setData(m_dlg.centreLat, m_dlg.centreLon);	
		m_dlg.chartScale = vp->chart_scale;
		if (m_dlg.m_nVF->GetSelection() == 0)
			DrawAllLinesInViewPort(vp);
		else if (m_dlg.m_nVF->GetSelection() == 1)
			DrawAllMultiLinesInViewPort(vp);
		else return true;
	}

	return true;
}

void MyOverlayFactory::DrawAllLinesInViewPort(PlugIn_ViewPort *BBox)

{
	wxPoint r;
	GetCanvasPixLL(BBox, &r, myLat1, myLon1);

	// Move to the first point
	int x = r.x;
	int y = r.y;

	float xt = m_dlg.myPixArray[0].x;
	float yt = m_dlg.myPixArray[0].y;

	int x1 = xt;
	int y1 = yt;

	p[0].x = x + xt;
	p[0].y = y + yt;


	// Walk thru the point list
	for (int ip = 1; ip < 5; ip++) {
		xt = m_dlg.myPixArray[ip].x;
		yt = m_dlg.myPixArray[ip].y;
	
		int x2 = xt;
		int y2 = yt;

	    DrawMyLine(x1 + x, y1 + y, x2 + x, y2 + y);

		p[ip].x = x1 + x;
		p[ip].y = y1 + y;
		
		x1 = x2;
		y1 = y2;
	}

	if (m_pdc){
#if wxUSE_GRAPHICS_CONTEXT
		m_gdc->SetBrush(*wxTheBrushList->FindOrCreateBrush(wxColour(255, 120, 0, 50), wxSOLID));
		m_gdc->SetPen(m_gdc->CreatePen(*wxThePenList->FindOrCreatePen(wxColour(255, 120, 0, 50), 1, wxSOLID)));
		m_gdc->DrawRectangle(p[0].x, p[0].y, m_dlg.myPixHeight, m_dlg.myPixHeight);
#endif
	}

	if (!m_pdc){
		wxColour myColour = wxColour(255, 120, 0, 50);
		DrawGLBox(p[0].x, p[0].y, m_dlg.myPixHeight, m_dlg.myPixHeight, myColour);
	}

}

// For making the 3x3 grid we do this:
void MyOverlayFactory::DrawAllMultiLinesInViewPort(PlugIn_ViewPort *BBox)

{
	wxPoint r;
	GetCanvasPixLL(BBox, &r, myLat1, myLon1);

	// Move to the first point
	int x = r.x;
	int y = r.y;

	float xt = m_dlg.myMPixArray[0].x;
	float yt = m_dlg.myMPixArray[0].y;

	int x1 = xt;
	int y1 = yt;

	float xv = m_dlg.myMPixArray[0].x;
	float yv = m_dlg.myMPixArray[0].y;

	p[0].x = x + xt;
	p[0].y = y + yt;


	// Walk thru the point list
	// Draw horizontal lines
	for (int ip = 1; ip < 8; ip++) {
		xt = m_dlg.myMPixArray[ip].x;
		yt = m_dlg.myMPixArray[ip].y;

		int x2 = xt;
		int y2 = yt;

		if ((x2 + x) > (x1 + x)){
			DrawMyLine(x1 + x, y1 + y, x2 + x, y2 + y);
		}

		p[ip].x = x1 + x;
		p[ip].y = y1 + y;

		x1 = x2;
		y1 = y2;
	}

	DrawMyLine(m_dlg.myMPixArray[0].x + x, m_dlg.myMPixArray[0].y + y, m_dlg.myMPixArray[6].x + x, m_dlg.myMPixArray[6].y + y);
	DrawMyLine(m_dlg.myMPixArray[8].x + x, m_dlg.myMPixArray[8].y + y, m_dlg.myMPixArray[10].x + x, m_dlg.myMPixArray[10].y + y);
	DrawMyLine(m_dlg.myMPixArray[9].x + x, m_dlg.myMPixArray[9].y + y, m_dlg.myMPixArray[11].x + x, m_dlg.myMPixArray[11].y + y);
	DrawMyLine(m_dlg.myMPixArray[1].x + x, m_dlg.myMPixArray[1].y + y, m_dlg.myMPixArray[7].x + x, m_dlg.myMPixArray[7].y + y);


	if (m_pdc){
#if wxUSE_GRAPHICS_CONTEXT
		m_gdc->SetBrush(*wxTheBrushList->FindOrCreateBrush(wxColour(255, 120, 0, 50), wxSOLID));
		m_gdc->SetPen(m_gdc->CreatePen(*wxThePenList->FindOrCreatePen(wxColour(255, 120, 0, 50), 1, wxSOLID)));
		m_gdc->DrawRectangle(p[0].x, p[0].y, m_dlg.myMPixHeight, m_dlg.myMPixHeight);
#endif
	}

	if (!m_pdc){
		wxColour myColour = wxColour(255, 120, 0, 50);
		DrawGLBox(p[0].x, p[0].y, m_dlg.myMPixHeight, m_dlg.myMPixHeight, myColour);
	}

}

void MyOverlayFactory::DrawMyLine(int x, int y, int x1, int y1)
{	
	wxColour c_blue = wxColour("#ff7800");

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

void MyOverlayFactory::DrawGLBox(double x, double y, double w, double h, wxColour myColour)
{
	   glEnable(GL_BLEND);
	   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		wxColour isoLineColor = myColour;
		glColor4ub(isoLineColor.Red(), isoLineColor.Green(), isoLineColor.Blue(),
			isoLineColor.Alpha());

		/* draw bounding rectangle */
		glBegin(GL_QUADS);
		glVertex2i(x, y);
		glVertex2i(x + w, y);
		glVertex2i(x + w, y + h);
		glVertex2i(x, y + h);
		glEnd();
	
}
