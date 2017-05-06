///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "connect_dlg.h"

///////////////////////////////////////////////////////////////////////////

connectdlg::connectdlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	bSizer2->SetMinSize( wxSize( 600,-1 ) ); 
	m_list = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL );
	bSizer2->Add( m_list, 2, wxALL|wxEXPAND, 5 );
	
	bSizer1->Add( bSizer2, 1, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Data:") ), wxVERTICAL );
	
	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	
	gbSizer1->SetFlexibleDirection( wxBOTH );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Character:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	gbSizer1->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_charname = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( m_charname, wxGBPosition( 0, 1 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Password:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gbSizer1->Add( m_staticText2, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_pw = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	gbSizer1->Add( m_pw, wxGBPosition( 1, 1 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("MUD:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	gbSizer1->Add( m_staticText3, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_mudname = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( m_mudname, wxGBPosition( 2, 1 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Host:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gbSizer1->Add( m_staticText4, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_hostname = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( m_hostname, wxGBPosition( 3, 1 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, _("IP-Address:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	gbSizer1->Add( m_staticText5, wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_ip = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	gbSizer1->Add( m_ip, wxGBPosition( 4, 1 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, _("Port:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	gbSizer1->Add( m_staticText6, wxGBPosition( 5, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_port = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( m_port, wxGBPosition( 5, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, _("Profile file:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	gbSizer1->Add( m_staticText7, wxGBPosition( 6, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_file = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, _("Select a file"), ("Lua profile (*.lua)|*.lua|All files|*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_OPEN|wxFLP_USE_TEXTCTRL );
	gbSizer1->Add( m_file, wxGBPosition( 6, 1 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );
	gbSizer1->AddGrowableCol( 2 );
	sbSizer2->Add( gbSizer1, 0, wxALL|wxEXPAND, 1 );
	
	bSizer1->Add( sbSizer2, 1, wxALL|wxEXPAND, 5 );
	
	wxGridSizer* gSizer3;
	gSizer3 = new wxGridSizer( 1, 3, 0, 0 );
	
	m_add = new wxButton( this, wxID_ANY, _("Add data"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( m_add, 0, wxALL, 5 );
	
	m_edit = new wxButton( this, wxID_ANY, _("Edit data"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( m_edit, 0, wxALL, 5 );
	
	m_del = new wxButton( this, wxID_ANY, _("Delete data"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( m_del, 0, wxALL, 5 );
	
	bSizer1->Add( gSizer3, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 1, 2, 0, 0 );
	
	m_ok = new wxButton( this, wxID_OK, _("Connect"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ok->SetDefault(); 
	gSizer2->Add( m_ok, 0, wxALL, 5 );
	
	m_cancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_cancel, 0, wxALL, 5 );
	
	bSizer1->Add( gSizer2, 0, wxALIGN_LEFT|wxALL|wxSHAPED, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( connectdlg::OnInit ) );
	m_list->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( connectdlg::OnItemActivate ), NULL, this );
	m_list->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( connectdlg::OnItemSelected ), NULL, this );
	m_file->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( connectdlg::OnFileChanged ), NULL, this );
	m_add->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( connectdlg::OnAdd ), NULL, this );
	m_edit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( connectdlg::OnEdit ), NULL, this );
	m_del->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( connectdlg::OnDelete ), NULL, this );
}

connectdlg::~connectdlg()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( connectdlg::OnInit ) );
	m_list->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( connectdlg::OnItemActivate ), NULL, this );
	m_list->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( connectdlg::OnItemSelected ), NULL, this );
	m_file->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( connectdlg::OnFileChanged ), NULL, this );
	m_add->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( connectdlg::OnAdd ), NULL, this );
	m_edit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( connectdlg::OnEdit ), NULL, this );
	m_del->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( connectdlg::OnDelete ), NULL, this );
	
}
