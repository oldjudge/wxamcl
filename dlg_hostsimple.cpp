///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jul 11 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dlg_hostsimple.h"

///////////////////////////////////////////////////////////////////////////

Connect::Connect( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Host") ), wxVERTICAL );
	
	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	gbSizer1->SetFlexibleDirection( wxBOTH );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	gbSizer1->SetEmptyCellSize( wxSize( 40,-1 ) );
	
	m_staticText3 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("Host:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	gbSizer1->Add( m_staticText3, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_server = new wxComboBox( sbSizer2->GetStaticBox(), wxID_ANY, _("localhost"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	gbSizer1->Add( m_server, wxGBPosition( 0, 1 ), wxGBSpan( 1, 5 ), wxALL|wxEXPAND, 5 );
	
	m_staticText4 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("Port:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gbSizer1->Add( m_staticText4, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_port = new wxComboBox( sbSizer2->GetStaticBox(), wxID_ANY, _("4000"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_port->Append( _("4000") );
	m_port->Append( _("23") );
	gbSizer1->Add( m_port, wxGBPosition( 1, 1 ), wxGBSpan( 1, 5 ), wxALL|wxEXPAND, 5 );
	
	
	gbSizer1->AddGrowableCol( 1 );
	
	sbSizer2->Add( gbSizer1, 1, wxALL, 5 );
	
	
	bSizer5->Add( sbSizer2, 0, wxALL, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	
	bSizer5->Add( m_sdbSizer1, 0, wxALL|wxEXPAND|wxTOP, 5 );
	
	
	this->SetSizer( bSizer5 );
	this->Layout();
	bSizer5->Fit( this );
}

Connect::~Connect()
{
}
