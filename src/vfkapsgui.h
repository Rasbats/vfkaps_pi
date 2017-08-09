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
#include <wx/dialog.h>
#include <wx/statline.h>
#include <wx/filepicker.h>
#include <wx/textctrl.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class m_dialog
///////////////////////////////////////////////////////////////////////////////
class m_dialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText10;
		wxButton* m_buttonGenerate;
		wxStaticText* m_staticText8;
		wxStaticText* m_stVFDownloadInfo;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnChooseSat( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGenerateKAP( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxChoice* m_choiceSat;
		
		m_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("VentureFarther"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 237,176 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
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
		
		VFKapsPrefsDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 238,239 ), long style = wxCAPTION|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~VFKapsPrefsDialog();
	
};

#endif //__VFKAPSGUI_H__
