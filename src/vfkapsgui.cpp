///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "vfkapsgui.h"

///////////////////////////////////////////////////////////////////////////

m_dialog::m_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 7, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_nVF = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pSingle = new wxPanel( m_nVF, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );

	m_staticText10 = new wxStaticText( m_pSingle, wxID_ANY, wxT("Satellite Chart Source :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	m_staticText10->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	fgSizer3->Add( m_staticText10, 0, wxALL, 5 );

	wxString m_choiceSatChoices[] = { wxT("Google"), wxT("Bing"), wxT("Nokia") };
	int m_choiceSatNChoices = sizeof( m_choiceSatChoices ) / sizeof( wxString );
	m_choiceSat = new wxChoice( m_pSingle, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSatNChoices, m_choiceSatChoices, 0 );
	m_choiceSat->SetSelection( 1 );
	fgSizer3->Add( m_choiceSat, 0, wxALL|wxEXPAND, 5 );

	m_buttonGenerate = new wxButton( m_pSingle, wxID_ANY, wxT("Generate Chart"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_buttonGenerate, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_buttonClear = new wxButton( m_pSingle, wxID_ANY, wxT("..... Delete last download ....."), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_buttonClear, 0, wxALL|wxEXPAND, 5 );

	sbSizerDirection = new wxStaticBoxSizer( new wxStaticBox( m_pSingle, wxID_ANY, wxEmptyString ), wxVERTICAL );

	gSizer2 = new wxGridSizer( 0, 3, 0, 0 );

	m_button31 = new wxButton( sbSizerDirection->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_button31->Hide();

	gSizer2->Add( m_button31, 0, wxALL, 5 );

	m_buttonUp = new wxButton( sbSizerDirection->GetStaticBox(), wxID_ANY, wxT("^"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonUp->SetFont( wxFont( 19, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	gSizer2->Add( m_buttonUp, 0, wxALL|wxEXPAND, 5 );

	m_button51 = new wxButton( sbSizerDirection->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 0,0 ), 0|wxTRANSPARENT_WINDOW|wxBORDER_NONE );
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


	fgSizer3->Add( sbSizerDirection, 1, wxEXPAND, 5 );

	m_staticText8 = new wxStaticText( m_pSingle, wxID_ANY, wxT("Status :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	m_staticText8->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	fgSizer3->Add( m_staticText8, 0, wxALL, 5 );

	m_stVFDownloadInfo = new wxStaticText( m_pSingle, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_stVFDownloadInfo->Wrap( -1 );
	fgSizer3->Add( m_stVFDownloadInfo, 0, wxALL|wxEXPAND, 5 );


	m_pSingle->SetSizer( fgSizer3 );
	m_pSingle->Layout();
	fgSizer3->Fit( m_pSingle );
	m_nVF->AddPage( m_pSingle, wxT("Single Chart"), false );
	m_pMultiple = new wxPanel( m_nVF, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	wxFlexGridSizer* fgSizer31;
	fgSizer31 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer31->SetFlexibleDirection( wxBOTH );
	fgSizer31->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText101 = new wxStaticText( m_pMultiple, wxID_ANY, wxT("Satellite Chart Source :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText101->Wrap( -1 );
	m_staticText101->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	fgSizer31->Add( m_staticText101, 0, wxALL, 5 );

	wxString m_choiceSat1Choices[] = { wxT("Google"), wxT("Bing"), wxT("Nokia") };
	int m_choiceSat1NChoices = sizeof( m_choiceSat1Choices ) / sizeof( wxString );
	m_choiceSat1 = new wxChoice( m_pMultiple, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSat1NChoices, m_choiceSat1Choices, 0 );
	m_choiceSat1->SetSelection( 2 );
	fgSizer31->Add( m_choiceSat1, 0, wxALL|wxEXPAND, 5 );

	m_buttonGenerate1 = new wxButton( m_pMultiple, wxID_ANY, wxT("Generate Multi-Chart"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer31->Add( m_buttonGenerate1, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_buttonClear1 = new wxButton( m_pMultiple, wxID_ANY, wxT("..... Delete last download ....."), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer31->Add( m_buttonClear1, 0, wxALL|wxEXPAND, 5 );

	sbSizerDirection1 = new wxStaticBoxSizer( new wxStaticBox( m_pMultiple, wxID_ANY, wxEmptyString ), wxVERTICAL );

	gSizer21 = new wxGridSizer( 0, 3, 0, 0 );

	m_button311 = new wxButton( sbSizerDirection1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_button311->Hide();

	gSizer21->Add( m_button311, 0, wxALL, 5 );

	m_buttonUp1 = new wxButton( sbSizerDirection1->GetStaticBox(), wxID_ANY, wxT("^"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonUp1->SetFont( wxFont( 19, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	gSizer21->Add( m_buttonUp1, 0, wxALL|wxEXPAND, 5 );

	m_button511 = new wxButton( sbSizerDirection1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 0,0 ), 0|wxTRANSPARENT_WINDOW|wxBORDER_NONE );
	m_button511->SetMinSize( wxSize( 0,0 ) );
	m_button511->SetMaxSize( wxSize( 0,0 ) );

	gSizer21->Add( m_button511, 0, wxALL, 5 );

	m_buttonLeft1 = new wxButton( sbSizerDirection1->GetStaticBox(), wxID_ANY, wxT("<"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonLeft1->SetFont( wxFont( 14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial Black") ) );

	gSizer21->Add( m_buttonLeft1, 0, wxALL|wxEXPAND, 5 );

	m_buttonCentre1 = new wxButton( sbSizerDirection1->GetStaticBox(), wxID_ANY, wxT("O"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonCentre1->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial Black") ) );

	gSizer21->Add( m_buttonCentre1, 0, wxALL|wxEXPAND, 5 );

	m_buttonRight1 = new wxButton( sbSizerDirection1->GetStaticBox(), wxID_ANY, wxT(">"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonRight1->SetFont( wxFont( 14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial Black") ) );

	gSizer21->Add( m_buttonRight1, 0, wxALL|wxEXPAND, 5 );

	m_button911 = new wxButton( sbSizerDirection1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_button911->Hide();

	gSizer21->Add( m_button911, 0, wxALL, 5 );

	m_buttonDown1 = new wxButton( sbSizerDirection1->GetStaticBox(), wxID_ANY, wxT("v"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonDown1->SetFont( wxFont( 16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	gSizer21->Add( m_buttonDown1, 0, wxALL|wxEXPAND, 5 );

	m_button1111 = new wxButton( sbSizerDirection1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_button1111->Hide();

	gSizer21->Add( m_button1111, 0, wxALL, 5 );


	sbSizerDirection1->Add( gSizer21, 1, wxEXPAND, 5 );


	fgSizer31->Add( sbSizerDirection1, 1, wxEXPAND, 5 );

	m_staticText81 = new wxStaticText( m_pMultiple, wxID_ANY, wxT("Status :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	m_staticText81->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	fgSizer31->Add( m_staticText81, 0, wxALL, 5 );

	m_stVFDownloadInfo1 = new wxStaticText( m_pMultiple, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_stVFDownloadInfo1->Wrap( -1 );
	fgSizer31->Add( m_stVFDownloadInfo1, 0, wxALL|wxEXPAND, 5 );


	m_pMultiple->SetSizer( fgSizer31 );
	m_pMultiple->Layout();
	fgSizer31->Fit( m_pMultiple );
	m_nVF->AddPage( m_pMultiple, wxT("Multi-Chart"), false );
	m_pAnchorage = new wxPanel( m_nVF, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	wxFlexGridSizer* fgSizer32;
	fgSizer32 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer32->SetFlexibleDirection( wxBOTH );
	fgSizer32->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxArrayString m_choiceCountriesChoices;
	m_choiceCountries = new wxChoice( m_pAnchorage, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceCountriesChoices, 0 );
	m_choiceCountries->SetSelection( 1 );
	fgSizer32->Add( m_choiceCountries, 0, wxALL|wxEXPAND, 5 );

	m_staticText102 = new wxStaticText( m_pAnchorage, wxID_ANY, wxT("Anchorage Charts :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText102->Wrap( -1 );
	m_staticText102->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	fgSizer32->Add( m_staticText102, 0, wxALL, 5 );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxString m_checkListMarkersChoices[] = { wxT("Select") };
	int m_checkListMarkersNChoices = sizeof( m_checkListMarkersChoices ) / sizeof( wxString );
	m_checkListMarkers = new wxCheckListBox( m_pAnchorage, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_checkListMarkersNChoices, m_checkListMarkersChoices, wxLB_MULTIPLE );
	bSizer1->Add( m_checkListMarkers, 100, wxALL|wxEXPAND, 5 );


	fgSizer32->Add( bSizer1, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	m_buttonGenerate3 = new wxButton( m_pAnchorage, wxID_ANY, wxT("Generate"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_buttonGenerate3, 0, wxALL|wxEXPAND, 5 );

	m_buttonClear2 = new wxButton( m_pAnchorage, wxID_ANY, wxT("..... Delete last download ....."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_buttonClear2, 0, wxALL|wxEXPAND, 5 );

	m_staticText82 = new wxStaticText( m_pAnchorage, wxID_ANY, wxT("Status :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText82->Wrap( -1 );
	m_staticText82->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer2->Add( m_staticText82, 0, wxALL, 5 );

	m_stVFDownloadInfo2 = new wxStaticText( m_pAnchorage, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_stVFDownloadInfo2->Wrap( -1 );
	bSizer2->Add( m_stVFDownloadInfo2, 0, wxALL|wxEXPAND, 5 );


	fgSizer32->Add( bSizer2, 1, wxALL|wxEXPAND, 5 );


	m_pAnchorage->SetSizer( fgSizer32 );
	m_pAnchorage->Layout();
	fgSizer32->Fit( m_pAnchorage );
	m_nVF->AddPage( m_pAnchorage, wxT("Country Anchorage Charts"), true );

	fgSizer1->Add( m_nVF, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( fgSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( m_dialog::OnClose ) );
	m_nVF->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( m_dialog::OnPageChange ), NULL, this );
	m_choiceSat->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( m_dialog::OnChooseSat ), NULL, this );
	m_buttonGenerate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnGenerateKAP ), NULL, this );
	m_buttonClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnDeleteLastDownload ), NULL, this );
	m_buttonUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonUp ), NULL, this );
	m_buttonLeft->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonLeft ), NULL, this );
	m_buttonCentre->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonCentre ), NULL, this );
	m_buttonRight->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonRight ), NULL, this );
	m_buttonDown->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonDown ), NULL, this );
	m_choiceSat1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( m_dialog::OnChooseSat ), NULL, this );
	m_buttonGenerate1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnGenerateKAP ), NULL, this );
	m_buttonClear1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnDeleteLastDownload ), NULL, this );
	m_buttonUp1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonUp ), NULL, this );
	m_buttonLeft1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonLeft ), NULL, this );
	m_buttonCentre1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonCentre ), NULL, this );
	m_buttonRight1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonRight ), NULL, this );
	m_buttonDown1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonDown ), NULL, this );
	m_choiceCountries->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( m_dialog::OnSelectCountry ), NULL, this );
	m_checkListMarkers->Connect( wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, wxCommandEventHandler( m_dialog::OnSelectAll ), NULL, this );
	m_buttonGenerate3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnGetMarkerKAPs ), NULL, this );
	m_buttonClear2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnDeleteLastDownload ), NULL, this );
}

m_dialog::~m_dialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( m_dialog::OnClose ) );
	m_nVF->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( m_dialog::OnPageChange ), NULL, this );
	m_choiceSat->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( m_dialog::OnChooseSat ), NULL, this );
	m_buttonGenerate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnGenerateKAP ), NULL, this );
	m_buttonClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnDeleteLastDownload ), NULL, this );
	m_buttonUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonUp ), NULL, this );
	m_buttonLeft->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonLeft ), NULL, this );
	m_buttonCentre->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonCentre ), NULL, this );
	m_buttonRight->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonRight ), NULL, this );
	m_buttonDown->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonDown ), NULL, this );
	m_choiceSat1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( m_dialog::OnChooseSat ), NULL, this );
	m_buttonGenerate1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnGenerateKAP ), NULL, this );
	m_buttonClear1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnDeleteLastDownload ), NULL, this );
	m_buttonUp1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonUp ), NULL, this );
	m_buttonLeft1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonLeft ), NULL, this );
	m_buttonCentre1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonCentre ), NULL, this );
	m_buttonRight1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonRight ), NULL, this );
	m_buttonDown1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnButtonDown ), NULL, this );
	m_choiceCountries->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( m_dialog::OnSelectCountry ), NULL, this );
	m_checkListMarkers->Disconnect( wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, wxCommandEventHandler( m_dialog::OnSelectAll ), NULL, this );
	m_buttonGenerate3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnGetMarkerKAPs ), NULL, this );
	m_buttonClear2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnDeleteLastDownload ), NULL, this );

}

VFKapsPrefsDialog::VFKapsPrefsDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 1, 0, 0 );
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
