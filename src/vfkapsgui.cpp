///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "vfkapsgui.h"

///////////////////////////////////////////////////////////////////////////

m_dialog::m_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 3, 1, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, wxT("Satellite Chart Source :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	m_staticText10->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	
	fgSizer1->Add( m_staticText10, 0, wxALL, 5 );
	
	wxString m_choiceSatChoices[] = { wxT("Google"), wxT("Bing"), wxT("Nokia") };
	int m_choiceSatNChoices = sizeof( m_choiceSatChoices ) / sizeof( wxString );
	m_choiceSat = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSatNChoices, m_choiceSatChoices, 0 );
	m_choiceSat->SetSelection( 0 );
	fgSizer1->Add( m_choiceSat, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonGenerate = new wxButton( this, wxID_ANY, wxT("Generate Chart"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_buttonGenerate, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	m_buttonClear = new wxButton( this, wxID_ANY, wxT("..... Delete last download ....."), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_buttonClear, 0, wxALL|wxEXPAND, 5 );
	
	sbSizerDirection = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxEmptyString ), wxVERTICAL );
	
	gSizer2 = new wxGridSizer( 3, 3, 0, 0 );
	
	m_button31 = new wxButton( sbSizerDirection->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_button31->Hide();
	
	gSizer2->Add( m_button31, 0, wxALL, 5 );
	
	m_buttonUp = new wxButton( sbSizerDirection->GetStaticBox(), wxID_ANY, wxT("^"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonUp->SetFont( wxFont( 19, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	
	gSizer2->Add( m_buttonUp, 0, wxALL|wxEXPAND, 5 );
	
	m_button51 = new wxButton( sbSizerDirection->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 0,0 ), 0|wxNO_BORDER|wxTRANSPARENT_WINDOW );
	m_button51->SetMinSize( wxSize( 0,0 ) );
	m_button51->SetMaxSize( wxSize( 0,0 ) );
	
	gSizer2->Add( m_button51, 0, wxALL, 5 );
	
	m_buttonLeft = new wxButton( sbSizerDirection->GetStaticBox(), wxID_ANY, wxT("<"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonLeft->SetFont( wxFont( 14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial Black") ) );
	
	gSizer2->Add( m_buttonLeft, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonCentre = new wxButton( sbSizerDirection->GetStaticBox(), wxID_ANY, wxT("O"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonCentre->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial Black") ) );
	
	gSizer2->Add( m_buttonCentre, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonRight = new wxButton( sbSizerDirection->GetStaticBox(), wxID_ANY, wxT(">"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonRight->SetFont( wxFont( 14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial Black") ) );
	
	gSizer2->Add( m_buttonRight, 0, wxALL|wxEXPAND, 5 );
	
	m_button91 = new wxButton( sbSizerDirection->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_button91->Hide();
	
	gSizer2->Add( m_button91, 0, wxALL, 5 );
	
	m_buttonDown = new wxButton( sbSizerDirection->GetStaticBox(), wxID_ANY, wxT("v"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonDown->SetFont( wxFont( 16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	
	gSizer2->Add( m_buttonDown, 0, wxALL|wxEXPAND, 5 );
	
	m_button111 = new wxButton( sbSizerDirection->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_button111->Hide();
	
	gSizer2->Add( m_button111, 0, wxALL, 5 );
	
	
	sbSizerDirection->Add( gSizer2, 1, wxEXPAND, 5 );
	
	
	fgSizer1->Add( sbSizerDirection, 1, wxEXPAND, 5 );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("Status :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	m_staticText8->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	
	fgSizer1->Add( m_staticText8, 0, wxALL, 5 );
	
	m_stVFDownloadInfo = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_stVFDownloadInfo->Wrap( -1 );
	fgSizer1->Add( m_stVFDownloadInfo, 0, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( m_dialog::OnClose ) );
	m_choiceSat->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( m_dialog::OnChooseSat ), NULL, this );
	m_buttonGenerate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnGenerateKAP ), NULL, this );
	m_buttonClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnDeleteLastDownload ), NULL, this );
	m_buttonUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonUp ), NULL, this );
	m_buttonLeft->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonLeft ), NULL, this );
	m_buttonCentre->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonCentre ), NULL, this );
	m_buttonRight->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonRight ), NULL, this );
	m_buttonDown->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonDown ), NULL, this );
}

m_dialog::~m_dialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( m_dialog::OnClose ) );
	m_choiceSat->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( m_dialog::OnChooseSat ), NULL, this );
	m_buttonGenerate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnGenerateKAP ), NULL, this );
	m_buttonClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnDeleteLastDownload ), NULL, this );
	m_buttonUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonUp ), NULL, this );
	m_buttonLeft->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonLeft ), NULL, this );
	m_buttonCentre->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonCentre ), NULL, this );
	m_buttonRight->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonRight ), NULL, this );
	m_buttonDown->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonDown ), NULL, this );
	
}

VFKapsPrefsDialog::VFKapsPrefsDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_stKapFolder = new wxStaticText( this, wxID_ANY, wxT("Directory for saving chart downloads :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stKapFolder->Wrap( -1 );
	m_stKapFolder->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	
	fgSizer2->Add( m_stKapFolder, 0, wxALL, 5 );
	
	m_staticline19 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer2->Add( m_staticline19, 0, wxALL, 5 );
	
	m_dirKaps = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	fgSizer2->Add( m_dirKaps, 0, wxALL, 5 );
	
	m_staticline20 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer2->Add( m_staticline20, 0, 0, 5 );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("API key :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	m_staticText9->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	
	fgSizer2->Add( m_staticText9, 0, wxALL, 5 );
	
	m_staticline191 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer2->Add( m_staticline191, 0, wxALL, 5 );
	
	m_tApiKey = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_tApiKey->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	
	fgSizer2->Add( m_tApiKey, 0, wxALL|wxEXPAND, 5 );
	
	m_cbUseMultiKap = new wxCheckBox( this, wxID_ANY, wxT("    Fetch surrounding charts"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_cbUseMultiKap, 0, wxALL|wxEXPAND, 5 );
	
	m_staticline201 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer2->Add( m_staticline201, 0, wxALL, 5 );
	
	m_staticline22 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer2->Add( m_staticline22, 0, wxALL|wxEXPAND, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	
	fgSizer2->Add( m_sdbSizer1, 1, wxTOP, 5 );
	
	
	this->SetSizer( fgSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

VFKapsPrefsDialog::~VFKapsPrefsDialog()
{
}
