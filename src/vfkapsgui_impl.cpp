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
		m_sUseMultiKap = pConf->Read(_T("multikap"));
	}

	m_bMoveUpDownLeftRight = false;

	if (m_sUseMultiKap == _T("0")){
		m_buttonGenerate->SetLabel(_T("Generate Chart"));
		m_stVFDownloadInfo->SetLabel(_("Ready for chart download"));     
	}
	else if (m_sUseMultiKap == _T("1")){
		m_buttonGenerate->SetLabel(_T("Generate Multi-Charts"));
		m_stVFDownloadInfo->SetLabel(_("Ready for multi-chart download"));
	}
	myChartFileNameArray.Clear();
	sessionCount = 0;
}

Dlg::~Dlg()
{
	pPlugIn->m_iChoiceSat = m_choiceSat->GetSelection();
	pPlugIn->m_sCopyUseDirectory = m_sUseDirectory;
	pPlugIn->m_sCopyUseMultiKap = m_sUseMultiKap;
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
	pPlugIn->m_sCopyUseMultiKap = m_sUseMultiKap;
	pPlugIn->OnvfkapsDialogClose();
}

void Dlg::OnGenerateKAP(wxCommandEvent& event)
{
	

	myZoom = GetScale(chartScale);

	//wxString z = wxString::Format(_T("%i"), (int)myZoom);
	//wxMessageBox(z);

	if ((myZoom < 12) && (m_sUseMultiKap == _T("1"))){
		wxMessageBox(_("Surrounding charts are not available at this scale\nPlease use preferences to change to single chart mode"));
		return;
	}


	myChartFileNameArray.Clear();
	
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
		wxMessageBox(_("Please enter your API key in Preferences"));
		return;
	}

	if (m_sUseDirectory == _T("\\")){
		wxMessageBox(_("Please choose/create your satellite chart directory in Preferences"));
		return;
	}

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

	/*
	if (CheckForDuplicateFileName(m_sUseDirectory, file_path)){
		
		RemoveChartFromDBInPlace(file_path);

		wxRemoveFile(file_path);
		
		RequestRefresh(pParent);		
		
	}
	*/



	wxString urlString = OnPrepare(myZoom, centreLat, centreLon, 2, m_sUseSat, m_sUseKey, m_sUseMultiKap);
	wxURI url(urlString);

	wxString logStart = _T("VFParams:");
	wxString logString = logStart + urlString;
	wxLogMessage(logString);

	
	/*
	wxTextFile file1(file_path);
	file1.Open();

	file1.AddLine(urlString);
	file1.Write();
	file1.Close();

	wxMessageBox(wxString::Format(_T("%8.6f"), centreLat));
	return;*/
	
	_OCPN_DLStatus ret = OCPN_downloadFile(url.BuildURI(), file_path,
		_T("VentureFarther"), _T("")
		, wxNullBitmap, this,
		OCPN_DLDS_ELAPSED_TIME | OCPN_DLDS_ESTIMATED_TIME | OCPN_DLDS_REMAINING_TIME | OCPN_DLDS_SPEED | OCPN_DLDS_SIZE | OCPN_DLDS_CAN_PAUSE | OCPN_DLDS_CAN_ABORT | OCPN_DLDS_AUTO_CLOSE,
		10);

	if (ret == OCPN_DL_FAILED){
		wxMessageBox(_("Download failed.\n\nDo you have enough credit with VentureFarther?"));
		m_stVFDownloadInfo->SetLabel(_("Download failed"));
		return;
	}
	else {
		m_stVFDownloadInfo->SetLabel(_("Download complete, about to extract the charts"));		
	}


	wxMilliSleep(2000);
	
    ExtractData(file_path);

	JumpToPosition(m_vp->clat, m_vp->clon, m_vp->view_scale_ppm);	

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


void Dlg::ExtractData(wxString filename)
{
	m_stVFDownloadInfo->SetLabel(_("Download complete, waiting for extraction"));
	wxString zpath = m_sUseDirectory;

	bool unzip;
	unzip = ExtractZipFiles(filename, zpath);

	if (unzip == true) {
		wxString zp = wxString::Format(_("Satellite Charts extracted to %s"), zpath);
		m_stVFDownloadInfo->SetLabel(zp);

		wxRemoveFile(file_path); //remove the zip file

	}
	else {
		m_stVFDownloadInfo->SetLabel(_("Unable to extract the charts"));
	}

}


bool Dlg::ExtractZipFiles(const wxString& aZipFile, const wxString& aTargetDir) {
	bool ret = true;

	//wxFileSystem fs;
	std::auto_ptr<wxZipEntry> entry(new wxZipEntry());

	do {

		wxFileInputStream in(aZipFile);

		if (!in) {
			wxLogError(_("Cannot open file '") + aZipFile + _T("'."));
			ret = false;
			break;
		}
		wxZipInputStream zip(in);

		while (entry.reset(zip.GetNextEntry()), entry.get() != NULL) {
			// access meta-data
			wxString name = entry->GetName();
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
			    AddChartToDBInPlace(name, true);
				myChartFileNameArray.Add(name);
			}

		}

	} while (false);

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

void Dlg::OnButtonUp(wxCommandEvent &event){

	m_bMoveUpDownLeftRight = true;
	wxPoint p;

	double chartscale = m_vp->view_scale_ppm;

	GetCanvasPixLL(m_vp, &p, centreLat, centreLon);
	p.y -= myPixHeight;

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
	p.x += myPixHeight;
	
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
	p.y += myPixHeight;

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
	p.x -= myPixHeight;

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