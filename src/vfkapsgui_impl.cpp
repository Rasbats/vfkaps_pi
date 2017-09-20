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

#include <wx/progdlg.h>
#include <wx/wx.h>
#include "wx/dir.h"

#include "vfkapsgui_impl.h"
#include "vfkapsgui.h"
#include "vfkaps_pi.h"

#include <wx/protocol/http.h>
#include <wx/filesys.h>
#include <wx/zipstrm.h>
#include <wx/wfstream.h>
#include <wx/sstream.h>
#include <wx/url.h>
#include <wx/string.h>
#include <wx/dir.h>
#include <wx/arrstr.h>
#include <wx/utils.h>
#include <wx/filename.h>
#include <wx/filefn.h>
#include <math.h>
#include <memory>
#include <wx/checkbox.h>
#include <wx/checklst.h>
#include <wx/hyperlink.h>
#include "tinyxml.h"


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
		m_choiceSat1->SetSelection(m_iChoiceSat);

		m_sUseDirectory = pConf->Read(_T("kapdirectory"));
		m_sUseKey = pConf->Read(_T("apikey"));
	}

	m_bMoveUpDownLeftRight = false;

	m_buttonGenerate->SetLabel(_T("Generate Chart"));
	m_stVFDownloadInfo->SetLabel(_("Ready for chart download"));     

	m_buttonGenerate1->SetLabel(_T("Generate Multi-Charts"));
	m_stVFDownloadInfo1->SetLabel(_("Ready for multi-chart download"));

	m_stVFDownloadInfo2->SetLabel(_("Ready for marker chart download"));
	
	m_nVF->SetSelection(0);
	
	myChartFileNameArray.Clear();
	sessionCount = 0;
}

Dlg::~Dlg()
{
	if (m_nVF->GetSelection() == 0){
		pPlugIn->m_iChoiceSat = m_choiceSat->GetSelection(); // need to reset the choice of provider
	}
	else if (m_nVF->GetSelection() == 1){
		pPlugIn->m_iChoiceSat = m_choiceSat1->GetSelection(); // need to reset the choice of provider
	}
	else if (m_nVF->GetSelection() == 2){
		if (m_sUseSat ==_T("google")) pPlugIn->m_iChoiceSat = 0;
		else if (m_sUseSat == _T("virtualEarth")) pPlugIn->m_iChoiceSat = 1;
		else if (m_sUseSat == _T("nokia")) pPlugIn->m_iChoiceSat = 2;;
	}
	pPlugIn->m_sCopyUseDirectory = m_sUseDirectory;
}

void Dlg::SetViewPort(PlugIn_ViewPort *vp)
{
	if (m_vp == vp)  return;

	m_vp = new PlugIn_ViewPort(*vp);
}

void Dlg::OnClose(wxCloseEvent& event)
{
	if (m_nVF->GetSelection() == 0){
		pPlugIn->m_iChoiceSat = m_choiceSat->GetSelection(); // need to reset the choice of provider
	}
	else if (m_nVF->GetSelection() == 1){
		pPlugIn->m_iChoiceSat = m_choiceSat1->GetSelection(); // need to reset the choice of provider
	}
	else if (m_nVF->GetSelection() == 2){
		if (m_sUseSat == _T("google")) pPlugIn->m_iChoiceSat = 0;
		else if (m_sUseSat == _T("virtualEarth")) pPlugIn->m_iChoiceSat = 1;
		else if (m_sUseSat == _T("nokia")) pPlugIn->m_iChoiceSat = 2;;
	}
	pPlugIn->m_sCopyUseDirectory = m_sUseDirectory;
	pPlugIn->OnvfkapsDialogClose();
}

void Dlg::OnGenerateKAP(wxCommandEvent& event)
{
	if (m_nVF->GetSelection() == 0){
		m_sUseMultiKap = _T("0");
		m_iPage = 0;
	}
	else if (m_nVF->GetSelection() == 1){
		m_sUseMultiKap = _T("1");
		m_iPage = 1;
	}

	myZoom = GetScale(chartScale);

	if ((myZoom < 11) && (m_sUseMultiKap == _T("1"))){
		wxMessageBox(_("Surrounding charts are not available at this scale\nPlease zoom in closer or use the single chart page\n\nChart scale needs to be less than 1:300000"));
		return;
	}

	myChartFileNameArray.Clear();

	int m_iChoiceSat, m_iChoiceSat1;
	if (m_nVF->GetSelection() == 0){
		m_iChoiceSat = m_choiceSat->GetSelection(); // need to reset the choice of provider
	}
	else if (m_nVF->GetSelection() == 1){
		m_iChoiceSat1 = m_choiceSat1->GetSelection(); // need to reset the choice of provider
	}
	
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
		wxMessageBox(_("Please enter your API key in Preferences"));
		return;
	}

	if (m_sUseDirectory == _T("/")){
		wxMessageBox(_("Please choose/create your satellite chart directory in Preferences"));
		return;
	}

	// construct local file path
	// file name does not need to be as complicated but carried over from old versions ....
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

	wxString scale = wxString::Format(_T("%i"), (int)myZoom);

	wxString sChartName = sLat + sLon;
	wxString files = p + _T("_") + scale + _T("_") + _T("VF") + sChartName + _T(".zip");
	
	wxFileName fn;
	fn.SetFullName(files);

	if (!wxDirExists(m_sUseDirectory)){
		wxMessageBox(_("Directory for saving the chart does not exist \nPlease use preferences to select/create a valid directory"));
		return;
	}

	fn.SetPath(m_sUseDirectory);
	file_path = fn.GetFullPath();

	if (m_nVF->GetSelection() == 1){
		myZoom = myZoom + 1;
		if (myZoom == 20){
			wxMessageBox(_("Multi-Charts are not available at this very large scale\nPlease zoom out a little"));
			return;
		}
	}

	wxString urlString = OnPrepare(myZoom, centreLat, centreLon, 2, m_sUseSat, m_sUseKey, m_sUseMultiKap);
	wxURI url(urlString);

	wxString logStart = _T("VFParams:");
	wxString logString = logStart + urlString;
	wxLogMessage(logString);

	_OCPN_DLStatus ret = OCPN_downloadFile(url.BuildURI(), file_path,
		_T("VentureFarther"), _T("")
		, wxNullBitmap, this,
		OCPN_DLDS_ELAPSED_TIME | OCPN_DLDS_ESTIMATED_TIME | OCPN_DLDS_REMAINING_TIME | OCPN_DLDS_SPEED | OCPN_DLDS_SIZE | OCPN_DLDS_CAN_PAUSE | OCPN_DLDS_CAN_ABORT | OCPN_DLDS_AUTO_CLOSE,
		10);

	if (ret == OCPN_DL_ABORTED){
		switch (m_iPage){
		case 0: m_stVFDownloadInfo->SetLabel(_("Download aborted"));
			break;
		case 1: m_stVFDownloadInfo1->SetLabel(_("Download aborted"));
			break;
		}
		return;
	}

	if (ret == OCPN_DL_FAILED){		
		wxMessageBox(_("Download failed.\n\nDo you have enough credit with VentureFarther?\nAre you connected to the Internet?"));

		switch (m_iPage){
		case 0: m_stVFDownloadInfo->SetLabel(_("Download failed"));
			break;
		case 1: m_stVFDownloadInfo1->SetLabel(_("Download failed"));
			break;
		}		
		return;
	}
	else {
		switch (m_iPage){
		case 0: m_stVFDownloadInfo->SetLabel(_("Download complete, about to extract charts"));
			break;
		case 1: m_stVFDownloadInfo1->SetLabel(_("Download complete, about to extract charts"));
			break;
		}
	}
	
    ExtractData(file_path);

	JumpToPosition(m_vp->clat, m_vp->clon, m_vp->view_scale_ppm);	

	RequestRefresh(pParent);	

}

void Dlg::OnPageChange(wxNotebookEvent& event){

	int m_iChoiceSat;
	if (m_sUseSat == _T("google"))m_iChoiceSat = 0;
	else if (m_sUseSat == _T("virtualEarth")) m_iChoiceSat = 1;
	else if (m_sUseSat == _T("nokia")) m_iChoiceSat = 2;;

	m_choiceSat->SetSelection(m_iChoiceSat);
	m_choiceSat1->SetSelection(m_iChoiceSat);

	m_iPage = m_nVF->GetSelection();
	
	if (m_iPage == 0){
		m_sUseMultiKap = _T("0");
	} else if (m_iPage == 1){		
		m_sUseMultiKap = _T("1");
	} else if (m_iPage == 2){
		GetCountries();
	}

	RequestRefresh(pParent);
}

wxString Dlg::OnPrepare(int zoom, double centerLat, double centerLon, int scale, wxString satType, wxString key, wxString multikap)
{
	wxString VF = _T("https://www.venturefarther.com/kap/KapDownload.action?");
	wxString m_sZoom = wxString::Format(_T("%i"), (int)zoom);
	wxString m_sCenterLat = wxString::Format(_T("%8.6f"), centerLat);
	wxString m_sCenterLon = wxString::Format(_T("%8.6f"), centerLon);
	wxString m_sScale = wxString::Format(_T("%i"), (int) scale);
	wxString m_sSatType = satType;
	wxString m_sKey = key;
	wxString m_sMultiKap = multikap;

	wxString a = _T("&");

	wxString ret = VF + _T("zoom=") + m_sZoom + a + _T("centerLat=") + m_sCenterLat + a + _T("centerLon=") + m_sCenterLon + a + _T("size=640x640") + a + _T("kapZip=zip") + a + _T("includeSurroundingKaps=") + m_sMultiKap + a
		 + _T("scale=") + m_sScale + a + _T("satType=") + m_sSatType + a + _T("key=") + m_sKey;
	
	return ret;	
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
	// Would switch case be quicker???

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

void Dlg::OnChooseSat(wxCommandEvent& event){

	int m_iChoiceSat;
	if (m_nVF->GetSelection() == 0){
		m_iChoiceSat = m_choiceSat->GetSelection(); // need to reset the choice of provider
	}
	else if (m_nVF->GetSelection() == 1){
		m_iChoiceSat = m_choiceSat1->GetSelection(); // need to reset the choice of provider
	}

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


void Dlg::ExtractData(wxString filename)
{
	wxString zpath = m_sUseDirectory;

	bool unzip;
	unzip = ExtractZipFiles(filename, zpath);

	if (unzip == true) {
		wxString zp;
		switch (m_iPage){
		case 0: 
			zp = wxString::Format(_("Satellite Charts extracted to %s"), zpath);
			m_stVFDownloadInfo->SetLabel(zp);
			break;
		case 1:
			zp = wxString::Format(_("Satellite Charts extracted to %s"), zpath);
			m_stVFDownloadInfo1->SetLabel(zp);
			break;
		case 2: 
			zp = wxString::Format(_("Satellite Charts extracted to %s"), zpath);
			m_stVFDownloadInfo2->SetLabel(zp);
			break;
		}
		
		wxRemoveFile(file_path); //remove the zip file

	}
	else {

		switch (m_iPage){
		case 0: m_stVFDownloadInfo->SetLabel(_("Unable to extract the charts"));
			break;
		case 1: m_stVFDownloadInfo1->SetLabel(_("Unable to extract the charts"));
			break;
		case 2: m_stVFDownloadInfo2->SetLabel(_("Unable to extract the charts"));
			break;
		}
	}	

	RequestRefresh(pParent);
}


bool Dlg::ExtractZipFiles(const wxString& aZipFile, const wxString& aTargetDir) {
	bool ret = true;
    wxString vfName = wxEmptyString;
	bool gotMarker = false;
	//wxFileSystem fs;
	std::auto_ptr<wxZipEntry> entry(new wxZipEntry());

	do {

		wxFileInputStream in(aZipFile);

		if (!in) {
			wxLogMessage(_("Cannot open file '") + aZipFile + _T("'."));
			ret = false;
			break;
		}
		wxZipInputStream zip(in);

		

		while (entry.reset(zip.GetNextEntry()), entry.get() != NULL) {
			// access meta-data
			wxString name = entry->GetName();
			vfName = name;
			name = aTargetDir + wxFileName::GetPathSeparator() + name;
			
			// read 'zip' to access the entry's data
			if (entry->IsDir()) {
				int perm = entry->GetMode();
				wxFileName::Mkdir(name, perm, wxPATH_MKDIR_FULL);				
			}
			else {
				zip.OpenEntry(*entry.get());
				if (!zip.CanRead()) {
					wxLogError(_("Cannot read zip entry '") + entry->GetName() + _T("'."));
					ret = false;
					break;
				}

				wxFileOutputStream file(name);

				if (!file) {
					wxLogError(_("Cannot create file '") + name + _T("'."));
					ret = false;
					break;
				}

				zip.Read(file);
				
				if (vfName == _T("VF_Marker.gpx")){  // test if the zip contains an anchorage chart
					gotMarker = true;					
				}
				else {
					AddChartToDBInPlace(name, false);
					myChartFileNameArray.Add(name);
				}
				
			}

		}

	} while (false);

	// Process the VF_Marker.gpx file
	if (gotMarker){
		AddMarkerWP();
	}

	if (wxIsPlatform64Bit() && (sessionCount == 0)){
		wxMessageBox(_("At the end of the download session:\nGo to Toolbox-> Charts->Chart Files\nSelect Scan Charts and Update Database"));
		sessionCount++;
	}

	return ret;
}

void Dlg::OnButtonCentre(wxCommandEvent &event){

	m_bMoveUpDownLeftRight = false;
	centreLat = m_vp->clat;
	centreLon = m_vp->clon;
	RequestRefresh(pParent);

}

void Dlg::MakeBoxPoints(){
	
	myZoom = GetScale(m_vp->chart_scale);

	double boxlat = m_vp->clat;
	double boxlon = m_vp->clon;

	double mpp;
	mpp = 156543.03392 * cos(boxlat * PI / 180) / pow(2, myZoom);

	mpp *= 640;		// Reference box is 640x640
	mpp /= 1852;	// metres to NM

	double halfbox = mpp / 60 / 2;  // decimal degree

	double centreC = boxlat;
	double dlat1, dlat2;

	dlat1 = centreC + halfbox;
	dlat2 = centreC - halfbox;

	int pixheight;


	wxPoint p1;
	GetCanvasPixLL(m_vp, &p1, dlat1, boxlon);

	wxPoint p2;
	GetCanvasPixLL(m_vp, &p2, dlat2, boxlon);

	pixheight = (p2.y) - (p1.y);

	pixheight /= 2;

	myPixArray[0].x = pixheight;
	myPixArray[0].x *= -1;
	myPixArray[0].y = pixheight;
	myPixArray[0].y *= -1;

	myPixArray[1].x = pixheight;
	myPixArray[1].y = pixheight;
	myPixArray[1].y *= -1;

	myPixArray[2].x = pixheight;
	myPixArray[2].y = pixheight;

	myPixArray[3].x = pixheight;
	myPixArray[3].x *= -1;
	myPixArray[3].y = pixheight;

	myPixArray[4].x = pixheight;
	myPixArray[4].x *= -1;
	myPixArray[4].y = pixheight;
	myPixArray[4].y *= -1;

	myPixHeight = pixheight * 2;

}

void Dlg::MakeMultiBoxPoints(){

	myZoom = GetScale(m_vp->chart_scale);

	double boxlat = m_vp->clat;
	double boxlon = m_vp->clon;

	double mpp;
	mpp = 156543.03392 * cos(boxlat * PI / 180) / pow(2, myZoom);

	mpp *= 640;		// Reference box is 640x640
	mpp /= 1852;	// metres to NM

	mpp /= 2;

	double halfbox = mpp / 60 / 2;  // decimal degree

	double centreC = boxlat;
	double dlat1, dlat2;

	dlat1 = centreC + halfbox;
	dlat2 = centreC - halfbox;

	int pixheight;

	wxPoint p1;
	GetCanvasPixLL(m_vp, &p1, dlat1, boxlon);

	wxPoint p2;
	GetCanvasPixLL(m_vp, &p2, dlat2, boxlon);

	pixheight = (p2.y) - (p1.y);

	pixheight /= 2;

	myMPixArray[0].x = pixheight;
	myMPixArray[0].x *= -3;
	myMPixArray[0].y = pixheight;
	myMPixArray[0].y *= -3;

	myMPixArray[1].x = pixheight;
	myMPixArray[1].x *= 3;
	myMPixArray[1].y = pixheight;
	myMPixArray[1].y *= -3;

	myMPixArray[2].x = pixheight;
	myMPixArray[2].x *= -3;
	myMPixArray[2].y = pixheight;
	myMPixArray[2].y *= -1;

	myMPixArray[3].x = pixheight;
	myMPixArray[3].x *= 3;
	myMPixArray[3].y = pixheight;
	myMPixArray[3].y *= -1;

	myMPixArray[4].x = pixheight;
	myMPixArray[4].x *= -3;
	myMPixArray[4].y = pixheight;
	
	myMPixArray[5].x = pixheight;
	myMPixArray[5].x *= 3;
	myMPixArray[5].y = pixheight;
	
	myMPixArray[6].x = pixheight;
	myMPixArray[6].x *= -3;
	myMPixArray[6].y = pixheight;
	myMPixArray[6].y *= 3;

	myMPixArray[7].x = pixheight;
	myMPixArray[7].x *= 3;
	myMPixArray[7].y = pixheight;
	myMPixArray[7].y *= 3;

	myMPixArray[8].x = pixheight;
	myMPixArray[8].x *= -1;
	myMPixArray[8].y = pixheight;
	myMPixArray[8].y *= -3;

	myMPixArray[9].x = pixheight;
	myMPixArray[9].y = pixheight;
	myMPixArray[9].y *= -3;

	myMPixArray[10].x = pixheight;
	myMPixArray[10].x *= -1;
	myMPixArray[10].y = pixheight;
	myMPixArray[10].y *= 3;

	myMPixArray[11].x = pixheight;
	myMPixArray[11].y = pixheight;
	myMPixArray[11].y *= 3;

	myMPixHeight = pixheight * 6;
}

void Dlg::OnButtonUp(wxCommandEvent &event){

	m_bMoveUpDownLeftRight = true;
	wxPoint p;

	double chartscale = m_vp->view_scale_ppm;

	GetCanvasPixLL(m_vp, &p, centreLat, centreLon);

	if (m_nVF->GetSelection() == 0){
		p.y -= myPixHeight;
	}
	if (m_nVF->GetSelection() == 1){
		p.y -= myMPixHeight;
	}

	double myLat, myLon;
	GetCanvasLLPix(m_vp, p, &myLat, &myLon);

	JumpToPosition(myLat, myLon, chartscale);

	centreLat = myLat;
	centreLon = myLon;
}


void Dlg::OnButtonRight(wxCommandEvent &event){

	m_bMoveUpDownLeftRight = true;
	wxPoint p;

	double chartscale = m_vp->view_scale_ppm;

	GetCanvasPixLL(m_vp, &p, centreLat, centreLon);

	if (m_nVF->GetSelection() == 0){
		p.x += myPixHeight;
	}
	if (m_nVF->GetSelection() == 1){
		p.x += myMPixHeight;
	}
	
	double myLat, myLon;
	GetCanvasLLPix(m_vp, p, &myLat, &myLon);

	JumpToPosition(myLat, myLon, chartscale);

	centreLat = myLat;
	centreLon = myLon;

	RequestRefresh(pParent);

}

void Dlg::OnButtonDown(wxCommandEvent &event){

	m_bMoveUpDownLeftRight = true;
	wxPoint p;

	double chartscale = m_vp->view_scale_ppm;

	GetCanvasPixLL(m_vp, &p, centreLat, centreLon);

	if (m_nVF->GetSelection() == 0){
		p.y += myPixHeight;
	}
	if (m_nVF->GetSelection() == 1){
		p.y += myMPixHeight;
	}

	double myLat, myLon;
	GetCanvasLLPix(m_vp, p, &myLat, &myLon);

	JumpToPosition(myLat, myLon, chartscale);

	centreLat = myLat;
	centreLon = myLon;
	RequestRefresh(pParent);

}

void Dlg::OnButtonLeft(wxCommandEvent &event){

	m_bMoveUpDownLeftRight = true;
	wxPoint p;

	double chartscale = m_vp->view_scale_ppm;

	GetCanvasPixLL(m_vp, &p, centreLat, centreLon);

	if (m_nVF->GetSelection() == 0){
		p.x -= myPixHeight;
	}
	if (m_nVF->GetSelection() == 1){
		p.x -= myMPixHeight;
	}

	double myLat, myLon;
	GetCanvasLLPix(m_vp, p, &myLat, &myLon);

	JumpToPosition(myLat, myLon, chartscale);

	centreLat = myLat;
	centreLon = myLon;

	RequestRefresh(pParent);

}

void Dlg::OnDeleteLastDownload(wxCommandEvent &event){
	
	int sz = myChartFileNameArray.Count();
	if (sz == 0){
		wxMessageBox(_("Have you downloaded any charts in this session?"));
		return;
	}
	
	wxMessageDialog deletemess(this, _("You have chosen to delete the charts from the last download\nDo you wish to continue?"),
		_("Delete the last download"), wxOK | wxCANCEL);
	if (deletemess.ShowModal() == wxID_CANCEL)
		return;
	else {
		
		for (int i = 0; i < sz; i++){
			RemoveChartFromDBInPlace(myChartFileNameArray[i]);
			wxRemoveFile(myChartFileNameArray[i]);
		}

		myChartFileNameArray.Clear();
	}

	if (wxIsPlatform64Bit()){
		wxMessageBox(_("Go to Toolbox-> Charts->Chart Files\nSelect Scan Charts and Update Database"));
	}

	RequestRefresh(pParent);

}

void Dlg::GetCountries(){

	wxString res = wxEmptyString;
	wxString fn = wxFileName::CreateTempFileName(_T("vfkaps_pi"));

	wxString urlString = _T("https://www.venturefarther.com/kap/CountriesWithMarkers.json");
	wxURI url(urlString);

	_OCPN_DLStatus ret = OCPN_downloadFile(url.BuildURI(), fn,
		_T("VentureFarther"), _T("")
		, wxNullBitmap, this,
		OCPN_DLDS_ELAPSED_TIME | OCPN_DLDS_ESTIMATED_TIME | OCPN_DLDS_REMAINING_TIME | OCPN_DLDS_SPEED | OCPN_DLDS_SIZE | OCPN_DLDS_CAN_PAUSE | OCPN_DLDS_CAN_ABORT | OCPN_DLDS_AUTO_CLOSE,
		10);

	if (ret == OCPN_DL_FAILED){
		wxMessageBox(_("Download failed.\n\nDo you have enough credit with VentureFarther?\nAre you connected to the Internet?"));
		wxRemoveFile(fn);
		return;
	}
	else if (ret == OCPN_DL_NO_ERROR) {
		wxFile f(fn);
		f.ReadAll(&res);
		f.Close();
		wxRemoveFile(fn);
		ReadJsonCountries(res);
		return;
	}
	wxRemoveFile(fn);
	return;
}

void Dlg::ReadJsonCountries(wxString injson){

	wxString content;

	wxJSONReader r;
	wxJSONValue vCountry;

	r.Parse(injson, &vCountry);

	myCountries = vCountry["countries"];

	// before obtaining the array of strings, we check that the type
	// of the 'language' object is an array
	// NOTE: this is not strictly necessary.
	bool isCountryArray = myCountries.IsArray();

	if (!isCountryArray)wxMessageBox(_T("fail"));

	wxString buildCountry;
	for (int i = 0; i < myCountries.Size(); i++) {
		buildCountry = myCountries[i][_T("name")].AsString() + _T(" (") + myCountries[i][_T("numberOfMarkers")].AsString() + _T(")");
		listcountries.Add(buildCountry);
	}

	m_choiceCountries->Set(listcountries);
	m_choiceCountries->SetSelection(0);
}

void Dlg::OnSelectCountry(wxCommandEvent& event){

	wxString sc = m_choiceCountries->GetStringSelection();

	int sf = sc.Find(_T(" ("));
	wxString found = sc.Mid(0, sf);

	wxString countryId;

	for (int i = 0; i < myCountries.Size(); i++) {
		if (myCountries[i][_T("name")].AsString() == found){
			countryId = myCountries[i][_T("countryId")].AsString();
		}
	}

	GetJsonCountryMarkers(countryId);
}

bool Dlg::GetJsonCountryMarkers(wxString countryId)
{
	wxString res = wxEmptyString;
	wxString fn = wxFileName::CreateTempFileName(_T("vfkaps_pi"));

	wxString urlString = _T("https://www.venturefarther.com/kap/CountryKapParams.json?countryId=") + countryId;
	wxURI url(urlString);

	_OCPN_DLStatus ret = OCPN_downloadFile(url.BuildURI(), fn,
		_T("VentureFarther"), _T("")
		, wxNullBitmap, this,
		OCPN_DLDS_ELAPSED_TIME | OCPN_DLDS_ESTIMATED_TIME | OCPN_DLDS_REMAINING_TIME | OCPN_DLDS_SPEED | OCPN_DLDS_SIZE | OCPN_DLDS_CAN_PAUSE | OCPN_DLDS_CAN_ABORT | OCPN_DLDS_AUTO_CLOSE,
		10);

	if (ret == OCPN_DL_FAILED){
		wxMessageBox(_("Download failed.\n\nDo you have enough credit with VentureFarther?"));
		wxRemoveFile(fn);
		return false;
	}
	else if (ret == OCPN_DL_NO_ERROR) {
		wxFile f(fn);
		f.ReadAll(&res);
		f.Close();
		wxRemoveFile(fn);

		ReadJsonCountryMarkers(res);

		return true;
	}
	wxRemoveFile(fn);
	return false;
}

void Dlg::ReadJsonCountryMarkers(wxString injson){

	myMarkers.Clear();

	wxJSONReader r;
	wxJSONValue v;

	r.Parse(injson, &v);

	myMarkers = v["kapParams"];

	// before obtaining the array of strings, we check that the type
	// of the 'language' object is an array
	// NOTE: this is not strictly necessary.
	bool isMarkArray = myMarkers.IsArray();

	wxArrayString listmarkers;
	//listmarkers.Add(_("Select All"));
	listmarkers.Add(_("Clear ALL selections ..."));
	int c = myMarkers.Size();
	for (int i = 0; i < c; i++) {
		listmarkers.Add(myMarkers[i][_T("displayName")].AsString());
	}

	m_checkListMarkers->Set(listmarkers);
	m_checkListMarkers->SetSelection(0);

	m_checkListMarkers->SetInitialSize();
	this->SetInitialSize();

}


void Dlg::OnSelectAll(wxCommandEvent& event){
	
	int i;

	if (m_checkListMarkers->IsChecked(0)){
		for (i = 0; i < m_checkListMarkers->GetCount(); i++){
			m_checkListMarkers->Check(i, false);
		}
		m_checkListMarkers->Check(0, true);
	}
		

}

void Dlg::GetSelectedMarker(){

	for (int c = 0; c < m_checkListMarkers->GetCount(); c++){
		if (m_checkListMarkers->IsChecked(c)){
			listcheckedmarkers.Add(m_checkListMarkers->GetString(c));
		}
	}

}

void Dlg::OnGetMarkerKAPs(wxCommandEvent& event){

	if (m_sUseKey == wxEmptyString){
		wxMessageBox(_("Please enter your API key in Preferences"));
		return;
	}

	if (m_sUseDirectory == _T("\\")){
		wxMessageBox(_("Please choose/create your satellite chart directory in Preferences"));
		return;
	}

	m_sUseMultiKap = _T("0");
	m_iPage = 2;

	wxString marker;

	for (int c = 0; c < m_checkListMarkers->GetCount(); c++){
		if (m_checkListMarkers->IsChecked(c)){
			listcheckedmarkers.Add(m_checkListMarkers->GetString(c));
		}
	}

	int c = listcheckedmarkers.Count();

	int MarkerId;
	double dLat, dLon;
	int iZoom;

	for (int z = 0; z < c; z++){  // loop through all the markers

		marker = listcheckedmarkers[z];

		for (int i = 0; i < myMarkers.Size(); i++) {
			if (myMarkers[i][_T("displayName")].AsString() == marker){

				MarkerId = myMarkers[i][_T("markerId")].AsInt();
				iZoom = myMarkers[i][_T("zoom")].AsInt();
				m_sUseSat = myMarkers[i][_T("satType")].AsString();
				dLat = myMarkers[i][_T("centerLat")].AsDouble();
				dLon = myMarkers[i][_T("centerLon")].AsDouble();

			}
		}

		wxString sLat, sLon, sZoom, sMarkerId;

		sLat = wxString::Format(_T("%.6f"), (double)dLat);
		sLon = wxString::Format(_T("%.6f"), (double)dLon);
		sZoom = wxString::Format(_T("%i"), (int)iZoom);
		sMarkerId = wxString::Format(_T("%i"), (int)MarkerId);

		wxString p = _T("VF");
		wxString sChartName = sLat + _T("_") + sLon;
		wxString files = p + sChartName + _T(".zip");

		wxFileName fn;
		fn.SetFullName(files);

		if (!wxDirExists(m_sUseDirectory)){
			wxMessageBox(_("Directory for saving the chart does not exist \nPlease use preferences to select/create a valid directory"));
			return;
		}

		fn.SetPath(m_sUseDirectory);
		file_path = fn.GetFullPath();

		wxString urlString = OnPrepare(iZoom, dLat, dLon, 2, m_sUseSat, m_sUseKey, _T("0"));

		wxString extras = _T("&includeMarkerInZip=1");
		extras = extras + _T("&") + _T("mapObjectId=") + sMarkerId;

		wxURI url(urlString + extras);

		wxString logStart = _T("VFMarkerParams:");
		wxString logString = logStart + urlString + extras;
		wxLogMessage(logString);

		_OCPN_DLStatus ret = OCPN_downloadFile(url.BuildURI(), file_path,
			_T("VentureFarther"), _T("")
			, wxNullBitmap, this,
			OCPN_DLDS_ELAPSED_TIME | OCPN_DLDS_ESTIMATED_TIME | OCPN_DLDS_REMAINING_TIME | OCPN_DLDS_SPEED | OCPN_DLDS_SIZE | OCPN_DLDS_CAN_PAUSE | OCPN_DLDS_CAN_ABORT | OCPN_DLDS_AUTO_CLOSE,
			10);

		if (ret == OCPN_DL_ABORTED){
			return;
		}

		if (ret == OCPN_DL_FAILED){
			wxMessageBox(_("Download failed.\n\nDo you have enough credit with VentureFarther?"));
			m_stVFDownloadInfo2->SetLabel(_("Download failed"));
			return;
		}
		else {
			m_stVFDownloadInfo2->SetLabel(_("Download complete\nabout to extract the charts"));
		}

		ExtractData(file_path);

	}

	RequestRefresh(pParent);
}

void Dlg::AddMarkerWP(){

	PlugIn_Waypoint myMarkerWP = ReadGPX();

	AddSingleWaypoint(&myMarkerWP, true);
    
}

PlugIn_Waypoint Dlg::ReadGPX(){

	TiXmlDocument doc(m_sUseDirectory + _T("/") + _T("VF_Marker.gpx"));
	doc.LoadFile();
	TiXmlElement *root = doc.RootElement();

	PlugIn_Waypoint myMarkerWP;

	wxString rte_lat, rte_lon, rte_name, rte_sym, rte_desc;

	int i = 0;
	for (TiXmlElement* a = root->FirstChildElement(); a; a = a->NextSiblingElement(), i++) {
		rte_lat = wxString::FromUTF8(a->Attribute("lat"));
		rte_lat.ToDouble(&myMarkerWP.m_lat);

		rte_lon = wxString::FromUTF8(a->Attribute("lon"));
		rte_lon.ToDouble(&myMarkerWP.m_lon);

		for (TiXmlElement* e = root->FirstChildElement(); e; e = e->NextSiblingElement(), i++) {
        					
			for (TiXmlElement* f = e->FirstChildElement(); f; f = f->NextSiblingElement()) {
								
				if (!strcmp(f->Value(), "name")) {
					rte_name = wxString::FromUTF8(f->GetText());					 					
					myMarkerWP.m_MarkName = rte_name;
				}
				
				if (!strcmp(f->Value(), "sym")) {
					rte_sym = wxString::FromUTF8(f->GetText());
					myMarkerWP.m_IconName = rte_sym;				
				}

				if (!strcmp(f->Value(), "desc")) {
					rte_desc = wxString::FromUTF8(f->GetText());
					myMarkerWP.m_MarkDescription = rte_desc;
				}
				
			}

		}
	}
	return myMarkerWP;
}
