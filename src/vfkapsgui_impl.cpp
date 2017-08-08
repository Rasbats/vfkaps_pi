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

//#include "vfkapsgui_impl.h"
#include <wx/progdlg.h>
#include <wx/wx.h>
#include "wx/dir.h"

#include "vfkapsgui_impl.h"
#include "vfkapsgui.h"
#include "vfkaps_pi.h"

#include <wx/protocol/http.h>
#include <wx/sstream.h>
#include <wx/url.h>
#include <wx/string.h>
#include <wx/dir.h>
#include <wx/arrstr.h>
#include <wx/utils.h>


#define FAIL(X) do { error = X; goto failed; } while(0)


wxString FormatBytes(double bytes)
{
	return wxString::Format(_T("%.1fMB"), bytes / 1024 / 1024);
}


Dlg::Dlg(wxWindow *parent, vfkaps_pi *ppi)
	: m_dialog( parent)
{	
    this->Fit();
    dbg=false; //for debug output set to true

	pPlugIn = ppi;
	pParent = parent;

	wxFileConfig *pConf = GetOCPNConfigObject();

	if (pConf)
	{
		pConf->SetPath(_T("/Settings/vfkaps_pi"));

		wxString m_sTempSat = pConf->Read(_T("satsource"));
		int m_iChoiceSat = wxAtoi(m_sTempSat);

		switch (m_iChoiceSat){
		case 0: m_sUseSat = _T("google");
			break;
		case 1: m_sUseSat = _T("virtualEarth");
			break;
		case 2: m_sUseSat = _T("nokia");
			break;		
		}

		m_choiceSat->SetSelection(m_iChoiceSat);

		m_sUseDirectory = pConf->Read(_T("kapdirectory"));
		m_sUseKey = pConf->Read(_T("apikey"));
	}

	Connect(wxEVT_DOWNLOAD_EVENT, (wxObjectEventFunction)(wxEventFunction)&Dlg::onDLEvent);
	m_bconnected = true;

	m_buttonCancel->Hide();
	m_stVFDownloadInfo->SetLabel(_T("Waiting to download KAP                                 "));
}

Dlg::~Dlg()
{
	pPlugIn->m_iChoiceSat = m_choiceSat->GetSelection();

	Disconnect(wxEVT_DOWNLOAD_EVENT, (wxObjectEventFunction)(wxEventFunction)&Dlg::onDLEvent);
	m_bconnected = false;
	
	wxArrayString myChartArray = GetChartDBDirArrayString();
	UpdateChartDBInplace(myChartArray, true, false);
}

void Dlg::SetViewPort(PlugIn_ViewPort *vp)
{
	if (m_vp == vp)  return;

	m_vp = new PlugIn_ViewPort(*vp);	

}

void Dlg::OnClose(wxCloseEvent& event)
{
	pPlugIn->m_iChoiceSat = m_choiceSat->GetSelection();
	pPlugIn->m_sCopyUseDirectory = m_sUseDirectory;
	pPlugIn->OnvfkapsDialogClose();
}


void Dlg::OnCancel(wxCommandEvent& event)
{
	cancelled = true;
}

void Dlg::OnGenerateKAP(wxCommandEvent& event)
{
	m_buttonCancel->Show();
	wxArrayString myChartArray;
	
	int m_iChoiceSat = m_choiceSat->GetSelection(); // need to reset the choice of provider
	wxString p = wxString::Format(_T("%i"), (int)m_iChoiceSat);

	switch (m_iChoiceSat){
	case 0: m_sUseSat = _T("google");
		break;
	case 1: m_sUseSat = _T("virtualEarth");
		break;
	case 2: m_sUseSat = _T("nokia");
		break;
	}
	

	if (m_sUseKey == wxEmptyString){
		wxMessageBox(_T("Please enter your API key in Preferences"));
	}

	if (!m_bconnected){
		Connect(wxEVT_DOWNLOAD_EVENT, (wxObjectEventFunction)(wxEventFunction)&Dlg::onDLEvent);
		m_bconnected = true;
	}


	m_bTransferComplete = false;
	m_bTransferSuccess = true;
	cancelled = false;

	//construct local file path

	sLat = wxString::Format(_T("%.6f"), (double) centreLat);
	sLon = wxString::Format(_T("%.6f"), (double) centreLon);

	sLat.Replace(_T(" "),_T("_"),true);
	if (sLat.Left(1) == "-"){
		sLat.Replace(_T("-"), _T(""),true);
		sLat = sLat + _T("_S_");
	}
	else{
		sLat = sLat + _T("_N_");
	}

	if (sLon.Left(1) == "-"){
		sLon.Replace(_T("-"), _T(""), true);
		sLon = sLon + _T("_W");
	}
	else{
		sLon = sLon + _T("_E");
	}

	int myZoom = GetScale(chartScale);
	wxString scale = wxString::Format(_T("%i"), (int)myZoom);
	//wxMessageBox(scale);

	wxString sChartName = sLat + sLon;
	wxString file = p + _T("_") + scale + _T("_") + _T("VF") + sChartName + _T(".kap");
	
	wxFileName fn;
	fn.SetFullName(file);

	if (!wxDirExists(m_sUseDirectory)){
		wxMessageBox(_T("Directory for saving KAP does not exist \nPlease use preferences to select/create a valid directory"));
		return;
	}

	fn.SetPath(m_sUseDirectory);
	wxString file_path = fn.GetFullPath();

	if (CheckForDuplicateFileName(m_sUseDirectory, file_path)){
		
		RemoveChartFromDBInPlace(file_path);
		myChartArray = GetChartDBDirArrayString();
		UpdateChartDBInplace(myChartArray, true, false);
		wxRemoveFile(file_path);
		
		ForceChartDBUpdate();
		RequestRefresh(pParent);		
		
	}

	wxString urlString = OnPrepare(myZoom, centreLat, centreLon, 2, m_sUseSat, m_sUseKey);
	wxURI url(urlString);

	long handle;
	OCPN_downloadFileBackground(url.BuildURI(), file_path, this, &handle);
	
	while (!m_bTransferComplete && m_bTransferSuccess && !cancelled)
	{
		m_stVFDownloadInfo->SetLabel(wxString::Format(_("Downloading Chart %u of %u (%s / %s)"),
			1, 1, m_transferredsize.c_str(), m_totalsize.c_str()));
		wxMilliSleep(1000);
		wxYield();
	}
	if (cancelled)	{
		OCPN_cancelDownloadFileBackground(handle);
		m_stVFDownloadInfo->SetLabel(_T("Download cancelled"));
		m_buttonCancel->Hide();
	}
	else {
		m_stVFDownloadInfo->SetLabel(_T("Download complete"));
		m_buttonCancel->Hide();
	}
	
	AddChartToDBInPlace(file_path, true);

	myChartArray = GetChartDBDirArrayString();
	UpdateChartDBInplace(myChartArray,true, false);

	RequestRefresh(pParent);

}

wxString Dlg::OnPrepare(int zoom, double centerLat, double centerLon, int scale, wxString satType, wxString key)
{
	wxString VF = _T("https://www.venturefarther.com/kap/KapDownload.action?");
	wxString m_sZoom = wxString::Format(_T("%i"), (int)zoom);
	wxString m_sCenterLat = wxString::Format(_T("%.6f"), (double)centerLat);
	wxString m_sCenterLon = wxString::Format(_T("%.6f"), (double)centerLon);
	wxString m_sScale = wxString::Format(_T("%i"), (int) scale);
	wxString m_sSatType = satType;
	wxString m_sKey = key;

	wxString a = _T("&");

	wxString ret = VF + _T("zoom=") + m_sZoom + a + _T("centerLat=") + m_sCenterLat + a + _T("centerLon=") + m_sCenterLon + _T("&size=640x640&kapZip=kap") 
		+ a + _T("scale=") + m_sScale + a + _T("satType=") + m_sSatType + a + _T("key=") + m_sKey;

	return ret;
	
}

void Dlg::onDLEvent(OCPN_downloadEvent &ev)
{
	switch (ev.getDLEventCondition()){
	case OCPN_DL_EVENT_TYPE_END:
		m_bTransferComplete = true;
		m_bTransferSuccess = (ev.getDLEventStatus() == OCPN_DL_NO_ERROR) ? true : false;
		break;

	case OCPN_DL_EVENT_TYPE_PROGRESS:
		m_totalsize = FormatBytes(ev.getTotal());
		m_transferredsize = FormatBytes(ev.getTransferred());

		break;
	
	case OCPN_DL_FAILED:	
		wxMessageBox(_T("Download failed.\n\nDo you have enough credit with VentureFarther?"));
		m_stVFDownloadInfo->SetLabel(_T("Download failed"));

		break;

	default:
		break;
	}
}

int Dlg::GetScale(double myChartScale)
{
	// If myChartScale is not exactly as shown in OpenCPN get the best scale to use.

	if (myChartScale<1200)
	{
		myChartScale = 800;
	}

	else if (myChartScale >= 1200 && myChartScale<2400)
	{
		myChartScale = 1600;
	}

	else if (myChartScale >= 2400 && myChartScale<4800)
	{
		myChartScale = 3200;
	}

	else if (myChartScale >= 4800 && myChartScale<9600)
	{
		myChartScale = 6400;
	}

	else if (myChartScale >= 9600 && myChartScale<19200)
	{
		myChartScale = 12800;
	}

	else if (myChartScale >= 19200 && myChartScale<38400)
	{
		myChartScale = 25600;
	}

	else if (myChartScale >= 38400 && myChartScale<76800)
	{
		myChartScale = 51200;
	}

	else if (myChartScale >= 76800 && myChartScale<153550)
	{
		myChartScale = 102400;
	}

	else if (myChartScale >= 153550 && myChartScale<306850)
	{
		myChartScale = 204700;
	}

	else if (myChartScale >= 306850 && myChartScale<613700)
	{
		myChartScale = 409000;
	}

	else if (myChartScale >= 613700 && myChartScale<1227400)
	{
		myChartScale = 818000;
	}

	else if (myChartScale >= 1227400 && myChartScale<2454800)
	{
		myChartScale = 1636000;
	}

	else if (myChartScale >= 2454800 && myChartScale<4909600)
	{
		myChartScale = 3272000;
	}

	else myChartScale = 9999000;
	

	// Use the modified scale to find the correct zoom level

	if (myChartScale == 800)
	{
		return 19;
	}
	
	else if (myChartScale == 1600)
	{
		return 18;
	}

	else if (myChartScale == 3200)
	{
		return 17;
	}

	else if (myChartScale == 6400)
	{
		return 16;
	}

	else if (myChartScale == 12800)
	{
		return 15;
	}

	else if (myChartScale == 25600)
	{
		return 14;
	}

	else if (myChartScale == 51200)
	{
		return 13;
	}

	else if (myChartScale == 102400)
	{
		return 12;
	}

	else if (myChartScale == 204700)
	{
		return 11;
	}
	else if (myChartScale == 409000)
	{
		return 10;
	}

	else if (myChartScale == 818000)
	{
		return 9;
	}

	else if (myChartScale == 1636000)
	{
		return 8;
	}

	else if (myChartScale == 3272000)
	{
		return 7;
	}

	else return 6;

	
}

void Dlg::DrawBox(double lat, double lon){

	pPlugIn->m_pOverlayFactory->m_bReadyToRender = true;
	pPlugIn->m_pOverlayFactory->setData(this, lat, lon);
	
}

void Dlg::OnChooseSat(wxCommandEvent& event){

	int m_iChoiceSat = m_choiceSat->GetSelection();

	switch (m_iChoiceSat){
	case 0: m_sUseSat = _T("google");
		break;
	case 1: m_sUseSat = _T("virtualEarth");
		break;
	case 2: m_sUseSat = _T("nokia");
		break;
	}

}

bool Dlg::CheckForDuplicateFileName(wxString dirname, wxString filename){

	wxArrayString files_array;

	wxDir::GetAllFiles(dirname, &files_array, wxEmptyString, wxDIR_FILES | wxDIR_DIRS | wxDIR_HIDDEN);

	int array_count = files_array.GetCount();

	for (int i = 0; i<array_count; i++){

		wxString filen;
		filen = files_array[i];

		if (filen == filename){				
			return true;
		}		

	}
	return false;
}
