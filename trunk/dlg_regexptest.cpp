///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dlg_regexptest.h"
#include "main.h"
///////////////////////////////////////////////////////////////////////////

regexp::regexp( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Text to test") ), wxVERTICAL );
	
	sbSizer1->SetMinSize( wxSize( 500,-1 ) ); 
	m_text = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	sbSizer1->Add( m_text, 1, wxALL|wxEXPAND, 5 );
	
	bSizer1->Add( sbSizer1, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Pattern") ), wxVERTICAL );
	
	m_pattern = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	sbSizer2->Add( m_pattern, 1, wxALL|wxEXPAND, 5 );
	
	bSizer1->Add( sbSizer2, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Matches") ), wxVERTICAL );
	
	m_matches = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,200 ), wxALIGN_LEFT|wxST_NO_AUTORESIZE|wxSTATIC_BORDER );
	m_matches->Wrap( -1 );
	sbSizer3->Add( m_matches, 1, wxALL|wxEXPAND, 5 );
	
	bSizer1->Add( sbSizer3, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_test = new wxButton( this, wxID_ANY, _("Test"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_test, 0, wxALL, 5 );
	
	m_close = new wxButton( this, wxID_OK, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_close, 0, wxALL, 5 );
	
	bSizer1->Add( bSizer3, 0, wxALL, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	m_test->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( regexp::OnTest ), NULL, this );
}

regexp::~regexp()
{
	// Disconnect Events
	m_test->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( regexp::OnTest ), NULL, this );
}
