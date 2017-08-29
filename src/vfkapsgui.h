///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __VFKAPSGUI_H__
#define __VFKAPSGUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/dialog.h>
#include <wx/statline.h>
#include <wx/filepicker.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class m_dialog
///////////////////////////////////////////////////////////////////////////////
class m_dialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText10;
		wxStaticText* m_staticText8;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnChooseSat( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGenerateKAP( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteLastDownload( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonUp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonLeft( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonCentre( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonRight( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonDown( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxChoice* m_choiceSat;
		wxButton* m_buttonGenerate;
		wxButton* m_buttonClear;
		wxStaticBoxSizer* sbSizerDirection;
		wxGridSizer* gSizer2;
		wxButton* m_button31;
		wxButton* m_buttonUp;
		wxButton* m_button51;
		wxButton* m_buttonLeft;
		wxButton* m_buttonCentre;
		wxButton* m_buttonRight;
		wxButton* m_button91;
		wxButton* m_buttonDown;
		wxButton* m_button111;
		wxStaticText* m_stVFDownloadInfo;
		
		m_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("VentureFarther"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 241,363 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~m_dialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class VFKapsPrefsDialog
///////////////////////////////////////////////////////////////////////////////
class VFKapsPrefsDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_stKapFolder;
		wxStaticLine* m_staticline19;
		wxStaticLine* m_staticline20;
		wxStaticText* m_staticText9;
		wxStaticLine* m_staticline191;
		wxStaticLine* m_staticline201;
		wxStaticLine* m_staticline22;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
	
	public:
		wxDirPickerCtrl* m_dirKaps;
		wxTextCtrl* m_tApiKey;
		wxCheckBox* m_cbUseMultiKap;
		
		VFKapsPrefsDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 251,318 ), long style = wxCAPTION|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~VFKapsPrefsDialog();
	
};

#endif //__VFKAPSGUI_H__
