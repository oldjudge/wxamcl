///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 16 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "script_dlg.h"

///////////////////////////////////////////////////////////////////////////

scriptedit::scriptedit( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Edit script") ), wxVERTICAL );
	
	const wxSize s(800,500);
	m_sce = new amcScriptEdit(this, wxID_ANY, wxDefaultPosition, s);
	sbSizer1->Add( m_sce, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer3->Add( sbSizer1, 1, wxALL|wxEXPAND, 5 );
	
	m_file = new wxStaticText( this, wxID_ANY, _("No file loaded!"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_file->Wrap( -1 );
	bSizer3->Add( m_file, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer8->Add( bSizer3, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_load = new wxButton( this, wxID_ANY, _("Load script"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_load, 0, wxALL, 5 );
	
	m_save = new wxButton( this, wxID_ANY, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_save, 0, wxALL, 5 );
	
	m_saveas = new wxButton( this, wxID_ANY, _(" Save script as"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_saveas, 0, wxALL, 5 );
	
	m_run = new wxButton( this, wxID_ANY, _("Run script"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_run, 0, wxALL, 5 );
	
	m_scfont = new wxFontPickerCtrl( this, wxID_ANY, wxNullFont, wxDefaultPosition, wxDefaultSize, wxFNTP_DEFAULT_STYLE );
	m_scfont->SetMaxPointSize( 100 ); 
	bSizer4->Add( m_scfont, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_close = new wxButton( this, wxID_OK, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	m_close->SetDefault(); 
	bSizer5->Add( m_close, 1, wxALIGN_RIGHT|wxALL, 5 );
	
	
	bSizer4->Add( bSizer5, 1, wxEXPAND, 5 );
	
	
	bSizer8->Add( bSizer4, 0, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer8 );
	this->Layout();
	bSizer8->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_load->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( scriptedit::OnLoadScript ), NULL, this );
	m_save->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( scriptedit::OnSave ), NULL, this );
	m_saveas->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( scriptedit::OnSaveAs ), NULL, this );
	m_run->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( scriptedit::OnRunScript ), NULL, this );
	m_scfont->Connect( wxEVT_COMMAND_FONTPICKER_CHANGED, wxFontPickerEventHandler( scriptedit::OnFontChanged ), NULL, this );
	m_close->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( scriptedit::OnOk ), NULL, this );
}

scriptedit::~scriptedit()
{
	// Disconnect Events
	m_load->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( scriptedit::OnLoadScript ), NULL, this );
	m_save->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( scriptedit::OnSave ), NULL, this );
	m_saveas->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( scriptedit::OnSaveAs ), NULL, this );
	m_run->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( scriptedit::OnRunScript ), NULL, this );
	m_scfont->Disconnect( wxEVT_COMMAND_FONTPICKER_CHANGED, wxFontPickerEventHandler( scriptedit::OnFontChanged ), NULL, this );
	m_close->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( scriptedit::OnOk ), NULL, this );
	
}
