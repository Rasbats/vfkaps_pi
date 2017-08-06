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
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/dialog.h>
#include <wx/choice.h>
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
		wxButton* m_buttonGenerate;
		wxButton* m_buttonCancel;
		wxStaticText* m_staticText8;
		wxStaticText* m_stVFDownloadInfo;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnGenerateKAP( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		m_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Venture Farther KAPs"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 220,149 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~m_dialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class VFKapsPrefsDialog
///////////////////////////////////////////////////////////////////////////////
class VFKapsPrefsDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText10;
		wxStaticLine* m_staticline18;
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
		wxChoice* m_choiceSat;
		wxDirPickerCtrl* m_dirKaps;
		wxTextCtrl* m_tApiKey;
		
		VFKapsPrefsDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 242,304 ), long style = wxCAPTION|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~VFKapsPrefsDialog();
	
};

#endif //__VFKAPSGUI_H__
