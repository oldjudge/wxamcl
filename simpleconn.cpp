///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "simpleconn.h"
#include "main.h"
///////////////////////////////////////////////////////////////////////////

DlgSimpleConn::DlgSimpleConn( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Host") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 2, 2, 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	label_1 = new wxStaticText( this, wxID_ANY, _("Server:"), wxDefaultPosition, wxDefaultSize, 0 );
	label_1->Wrap( -1 );
	fgSizer1->Add( label_1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	m_ip = new wxString("localhost");
	m_server = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN|wxCB_SORT, wxGenericValidator(m_ip) );
	//m_server->Append( "localhost" );
	fgSizer1->Add( m_server, 0, wxALL|wxEXPAND, 5 );
	
	label_2 = new wxStaticText( this, wxID_ANY, _("Port:  "), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	label_2->Wrap( -1 );
	fgSizer1->Add( label_2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	m_port = new wxString("4000");
	text_ctrl_2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0, wxTextValidator(wxFILTER_NUMERIC, m_port) );
	
	fgSizer1->Add( text_ctrl_2, 0, wxALL|wxEXPAND, 5 );
	
	sbSizer1->Add( fgSizer1, 0, wxALL|wxEXPAND, 5 );
	
	bSizer1->Add( sbSizer1, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	but1 = new wxButton( this, wxID_OK, _("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
	but1->SetDefault(); 
	bSizer4->Add( but1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	but2 = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( but2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizer4, 0, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
}

DlgSimpleConn::~DlgSimpleConn()
{
	delete m_ip;
	delete m_port;
}
