///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dlg_pkg.h"

///////////////////////////////////////////////////////////////////////////

dlg_pkg::dlg_pkg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Choose package content") ), wxVERTICAL );
	
	wxString m_choiceChoices[] = { _("All"), _("Actions"), _("Alias"), _("Buttons"), _("Gauges"), _("Hotkeys"), _("Lists"), _("Timers"), _("Variables") };
	int m_choiceNChoices = sizeof( m_choiceChoices ) / sizeof( wxString );
	m_choice = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceNChoices, m_choiceChoices, 0 );
	m_choice->SetSelection( 0 );
	sbSizer1->Add( m_choice, 0, wxALL|wxEXPAND, 5 );
	
	bSizer1->Add( sbSizer1, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Check items") ), wxVERTICAL );
	
	wxArrayString m_itemsChoices;
	m_items = new wxCheckListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_itemsChoices, wxLB_NEEDED_SB );
	m_items->SetMinSize( wxSize( 400,300 ) );
	
	sbSizer2->Add( m_items, 2, wxALL|wxEXPAND, 5 );
	
	m_checkall = new wxCheckBox( this, wxID_ANY, _("Check all items"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer2->Add( m_checkall, 0, wxALL, 5 );
	
	bSizer1->Add( sbSizer2, 1, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Package file") ), wxVERTICAL );
	
	m_pkgfile = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, _("Select a file"), wxT("*.*|*.lua"), wxDefaultPosition, wxDefaultSize, wxFLP_OVERWRITE_PROMPT|wxFLP_SAVE|wxFLP_USE_TEXTCTRL|wxFLP_CHANGE_DIR );
	sbSizer3->Add( m_pkgfile, 0, wxALL|wxEXPAND, 5 );
	
	bSizer1->Add( sbSizer3, 0, wxALL|wxEXPAND, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	bSizer1->Add( m_sdbSizer1, 0, wxALIGN_RIGHT|wxALL|wxLEFT, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_choice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( dlg_pkg::OnChoice ), NULL, this );
	m_items->Connect( wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, wxCommandEventHandler( dlg_pkg::OnToggle ), NULL, this );
	m_checkall->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( dlg_pkg::OnCheckAll ), NULL, this );
}

dlg_pkg::~dlg_pkg()
{
	// Disconnect Events
	m_choice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( dlg_pkg::OnChoice ), NULL, this );
	m_items->Disconnect( wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, wxCommandEventHandler( dlg_pkg::OnToggle ), NULL, this );
	m_checkall->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( dlg_pkg::OnCheckAll ), NULL, this );
	
}
