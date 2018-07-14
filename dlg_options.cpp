///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dlg_options.h"

///////////////////////////////////////////////////////////////////////////

DlgOptions::DlgOptions( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetExtraStyle( this->GetExtraStyle() | wxWS_EX_TRANSIENT );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_nb = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	wxSize m_nbImageSize = wxSize( 16,16 );
	int m_nbIndex = 0;
	wxImageList* m_nbImages = new wxImageList( m_nbImageSize.GetWidth(), m_nbImageSize.GetHeight() );
	m_nb->AssignImageList( m_nbImages );
	wxBitmap m_nbBitmap;
	wxImage m_nbImage;
	m_nb->SetExtraStyle( wxWS_EX_TRANSIENT );
	
	m_general = new wxPanel( m_nb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_general->SetExtraStyle( wxWS_EX_TRANSIENT );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* gbSizer3;
	gbSizer3 = new wxGridBagSizer( 0, 0 );
	gbSizer3->SetFlexibleDirection( wxBOTH );
	gbSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_general, wxID_ANY, _("Commands") ), wxVERTICAL );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 9, 2, 0, 0 );
	
	m_staticText4 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Command sign:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gSizer1->Add( m_staticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textcomm = new wxTextCtrl( sbSizer1->GetStaticBox(), ID_CS, wxEmptyString, wxDefaultPosition, wxSize( 24,-1 ), 0 );
	#ifdef __WXGTK__
	if ( !m_textcomm->HasFlag( wxTE_MULTILINE ) )
	{
	m_textcomm->SetMaxLength( 1 );
	}
	#else
	m_textcomm->SetMaxLength( 1 );
	#endif
	m_textcomm->SetToolTip( _("Command sign (default: #)") );
	
	gSizer1->Add( m_textcomm, 0, wxALL, 5 );
	
	m_staticText5 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Seperator sign:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	gSizer1->Add( m_staticText5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textsep = new wxTextCtrl( sbSizer1->GetStaticBox(), ID_CSEP, wxEmptyString, wxDefaultPosition, wxSize( 24,-1 ), 0 );
	#ifdef __WXGTK__
	if ( !m_textsep->HasFlag( wxTE_MULTILINE ) )
	{
	m_textsep->SetMaxLength( 1 );
	}
	#else
	m_textsep->SetMaxLength( 1 );
	#endif
	m_textsep->SetToolTip( _("Command separator sign (default: ;)") );
	
	gSizer1->Add( m_textsep, 0, wxALL, 5 );
	
	m_staticText6 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Script sign:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	gSizer1->Add( m_staticText6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textscript = new wxTextCtrl( sbSizer1->GetStaticBox(), ID_CSCRIPT, wxEmptyString, wxDefaultPosition, wxSize( 24,-1 ), 0 );
	#ifdef __WXGTK__
	if ( !m_textscript->HasFlag( wxTE_MULTILINE ) )
	{
	m_textscript->SetMaxLength( 1 );
	}
	#else
	m_textscript->SetMaxLength( 1 );
	#endif
	m_textscript->SetToolTip( _("Script command sign (default: ?)") );
	
	gSizer1->Add( m_textscript, 0, wxALL, 5 );
	
	m_staticText41 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Speedwalk:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	gSizer1->Add( m_staticText41, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textsw = new wxTextCtrl( sbSizer1->GetStaticBox(), ID_CSP, wxEmptyString, wxDefaultPosition, wxSize( 24,-1 ), 0 );
	#ifdef __WXGTK__
	if ( !m_textsw->HasFlag( wxTE_MULTILINE ) )
	{
	m_textsw->SetMaxLength( 1 );
	}
	#else
	m_textsw->SetMaxLength( 1 );
	#endif
	m_textsw->SetToolTip( _("Command sign for speedwalks (default: .)") );
	
	gSizer1->Add( m_textsw, 0, wxALL, 5 );
	
	m_staticText51 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Reverse sw:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	gSizer1->Add( m_staticText51, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textswr = new wxTextCtrl( sbSizer1->GetStaticBox(), ID_CSPR, wxEmptyString, wxDefaultPosition, wxSize( 24,-1 ), 0 );
	#ifdef __WXGTK__
	if ( !m_textswr->HasFlag( wxTE_MULTILINE ) )
	{
	m_textswr->SetMaxLength( 1 );
	}
	#else
	m_textswr->SetMaxLength( 1 );
	#endif
	m_textswr->SetToolTip( _("Command sign for reverse speedwalks (default: *)") );
	
	gSizer1->Add( m_textswr, 0, wxALL, 5 );
	
	m_staticText17 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Speedwalk delay (ms)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	gSizer1->Add( m_staticText17, 0, wxALL, 5 );
	
	m_swdelay = new wxSpinCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 5000, 0 );
	gSizer1->Add( m_swdelay, 0, wxALL, 5 );
	
	m_staticText71 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Variable:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText71->Wrap( -1 );
	gSizer1->Add( m_staticText71, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textvar = new wxTextCtrl( sbSizer1->GetStaticBox(), ID_CV, wxEmptyString, wxDefaultPosition, wxSize( 24,-1 ), 0 );
	#ifdef __WXGTK__
	if ( !m_textvar->HasFlag( wxTE_MULTILINE ) )
	{
	m_textvar->SetMaxLength( 1 );
	}
	#else
	m_textvar->SetMaxLength( 1 );
	#endif
	m_textvar->SetToolTip( _("Variable sign (default: $)") );
	
	gSizer1->Add( m_textvar, 0, wxALL, 5 );
	
	m_staticText121 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("List:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText121->Wrap( -1 );
	gSizer1->Add( m_staticText121, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_listvar = new wxTextCtrl( sbSizer1->GetStaticBox(), ID_CVL, wxEmptyString, wxDefaultPosition, wxSize( 24,-1 ), 0 );
	#ifdef __WXGTK__
	if ( !m_listvar->HasFlag( wxTE_MULTILINE ) )
	{
	m_listvar->SetMaxLength( 1 );
	}
	#else
	m_listvar->SetMaxLength( 1 );
	#endif
	m_listvar->SetToolTip( _("List sign (default: @)") );
	
	gSizer1->Add( m_listvar, 0, wxALL, 5 );
	
	m_staticText18 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Send to all worlds: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	gSizer1->Add( m_staticText18, 0, wxALL, 5 );
	
	m_worldvar = new wxTextCtrl( sbSizer1->GetStaticBox(), ID_CWORLD, wxEmptyString, wxDefaultPosition, wxSize( 24,-1 ), 0 );
	#ifdef __WXGTK__
	if ( !m_worldvar->HasFlag( wxTE_MULTILINE ) )
	{
	m_worldvar->SetMaxLength( 1 );
	}
	#else
	m_worldvar->SetMaxLength( 1 );
	#endif
	m_worldvar->SetToolTip( _("Send to all worlds (default: :)") );
	
	gSizer1->Add( m_worldvar, 0, wxALL, 5 );
	
	
	sbSizer1->Add( gSizer1, 0, wxALL, 5 );
	
	
	gbSizer3->Add( sbSizer1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( m_general, wxID_ANY, _("Command window") ), wxVERTICAL );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	gbSizer1->SetFlexibleDirection( wxBOTH );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	m_keepin = new wxCheckBox( sbSizer5->GetStaticBox(), wxID_ANY, _("Keep input"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( m_keepin, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_parsein = new wxCheckBox( sbSizer5->GetStaticBox(), wxID_ANY, _("Parse input"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( m_parsein, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_staticText11 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, _("History size:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	gbSizer1->Add( m_staticText11, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_histsize = new wxSpinCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 150,-1 ), wxSP_ARROW_KEYS, 0, 200, 199 );
	gbSizer1->Add( m_histsize, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	
	bSizer6->Add( gbSizer1, 1, wxALL, 5 );
	
	
	sbSizer5->Add( bSizer6, 1, wxALL, 5 );
	
	m_tabdlg = new wxCheckBox( sbSizer5->GetStaticBox(), wxID_ANY, _("Use tabcompletion-dialog"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( m_tabdlg, 0, wxALL, 5 );
	
	m_tablist = new wxButton( sbSizer5->GetStaticBox(), wxID_ANY, _("Edit tabcompletion list"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( m_tablist, 0, wxALL, 5 );
	
	
	gbSizer3->Add( sbSizer5, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( m_general, wxID_ANY, _("Prompt") ), wxVERTICAL );
	
	m_lock = new wxCheckBox( sbSizer10->GetStaticBox(), wxID_ANY, _("Lock prompt"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer10->Add( m_lock, 0, wxALL, 5 );
	
	m_gagprompt = new wxCheckBox( sbSizer10->GetStaticBox(), wxID_ANY, _("Gag prompt when locked"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer10->Add( m_gagprompt, 0, wxALL, 5 );
	
	m_staticText131 = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, _("Prompt detection pattern:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText131->Wrap( -1 );
	sbSizer10->Add( m_staticText131, 0, wxALL, 5 );
	
	m_promptpattern = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer10->Add( m_promptpattern, 0, wxALL|wxEXPAND, 5 );
	
	
	gbSizer3->Add( sbSizer10, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer12;
	sbSizer12 = new wxStaticBoxSizer( new wxStaticBox( m_general, wxID_ANY, _("Connection options") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->AddGrowableCol( 0 );
	fgSizer1->AddGrowableRow( 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_gmcp = new wxCheckBox( sbSizer12->GetStaticBox(), wxID_ANY, _("Use GMCP"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_gmcp, 0, wxALL, 5 );
	
	m_gmcpmodules = new wxTextCtrl( sbSizer12->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxVSCROLL );
	fgSizer1->Add( m_gmcpmodules, 1, wxALL|wxEXPAND, 5 );
	
	m_mccp = new wxCheckBox( sbSizer12->GetStaticBox(), wxID_ANY, _("Negotiate MCCP"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_mccp, 0, wxALL, 5 );
	
	m_mxp = new wxCheckBox( sbSizer12->GetStaticBox(), wxID_ANY, _("Negotiate MXP"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_mxp, 0, wxALL, 5 );
	
	m_msp = new wxCheckBox( sbSizer12->GetStaticBox(), wxID_ANY, _("Negotiate MSP"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_msp, 0, wxALL, 5 );
	
	m_useMSDP = new wxCheckBox( sbSizer12->GetStaticBox(), wxID_ANY, _("Use MSDP"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_useMSDP, 0, wxALL, 5 );
	
	m_useaardopts = new wxCheckBox( sbSizer12->GetStaticBox(), wxID_ANY, _("Use Aard Telopts"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_useaardopts, 0, wxALL, 5 );
	
	m_atcp = new wxCheckBox( sbSizer12->GetStaticBox(), wxID_ANY, _("Use ATCP"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_atcp, 0, wxALL, 5 );
	
	m_iacgaeor = new wxCheckBox( sbSizer12->GetStaticBox(), wxID_ANY, _("GA EOR"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_iacgaeor, 0, wxALL, 5 );
	
	m_naws = new wxCheckBox( sbSizer12->GetStaticBox(), wxID_ANY, _("Negotiate NAWS"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_naws, 0, wxALL, 5 );
	
	m_utf8 = new wxCheckBox( sbSizer12->GetStaticBox(), wxID_ANY, _("UTF8 connection"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_utf8, 0, wxALL, 5 );
	
	m_ipv6 = new wxCheckBox( sbSizer12->GetStaticBox(), wxID_ANY, _("Use IPV6"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_ipv6, 0, wxALL, 5 );
	
	m_autoreconnect = new wxCheckBox( sbSizer12->GetStaticBox(), wxID_ANY, _("Reconnect after disconnect"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_autoreconnect, 0, wxALL, 5 );
	
	m_acdelay = new wxSpinCtrl( sbSizer12->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 15 );
	fgSizer1->Add( m_acdelay, 0, wxALL, 5 );
	
	
	sbSizer12->Add( fgSizer1, 1, wxALL|wxEXPAND, 5 );
	
	
	gbSizer3->Add( sbSizer12, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer13;
	sbSizer13 = new wxStaticBoxSizer( new wxStaticBox( m_general, wxID_ANY, _("Events") ), wxVERTICAL );
	
	m_evall = new wxCheckBox( sbSizer13->GetStaticBox(), wxID_ANY, _("Use events"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer13->Add( m_evall, 0, wxALL, 5 );
	
	m_onconnect = new wxCheckBox( sbSizer13->GetStaticBox(), wxID_ANY, _("OnConnect"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer13->Add( m_onconnect, 0, wxALL, 5 );
	
	m_ondisconnect = new wxCheckBox( sbSizer13->GetStaticBox(), wxID_ANY, _("OnDisconnect"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer13->Add( m_ondisconnect, 0, wxALL, 5 );
	
	m_precv = new wxCheckBox( sbSizer13->GetStaticBox(), wxID_ANY, _("OnPacketReceived"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer13->Add( m_precv, 0, wxALL, 5 );
	
	m_ontelnetdata = new wxCheckBox( sbSizer13->GetStaticBox(), wxID_ANY, _("OnTelnetData"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer13->Add( m_ontelnetdata, 0, wxALL, 5 );
	
	m_ongmcpdata = new wxCheckBox( sbSizer13->GetStaticBox(), wxID_ANY, _("OnGMCPData"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer13->Add( m_ongmcpdata, 0, wxALL, 5 );
	
	m_onmsdpdata = new wxCheckBox( sbSizer13->GetStaticBox(), wxID_ANY, _("OnMSDPData"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer13->Add( m_onmsdpdata, 0, wxALL, 5 );
	
	m_staticText141 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, _("Script file:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText141->Wrap( -1 );
	sbSizer13->Add( m_staticText141, 0, wxALL, 5 );
	
	m_eventfile = new wxFilePickerCtrl( sbSizer13->GetStaticBox(), wxID_ANY, wxEmptyString, _("Select a file"), wxT("Lua files|*.lua"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE|wxFLP_USE_TEXTCTRL );
	sbSizer13->Add( m_eventfile, 0, wxALL|wxEXPAND, 5 );
	
	
	gbSizer3->Add( sbSizer13, wxGBPosition( 1, 1 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );
	
	
	gbSizer3->AddGrowableCol( 0 );
	gbSizer3->AddGrowableCol( 1 );
	gbSizer3->AddGrowableCol( 2 );
	gbSizer3->AddGrowableRow( 0 );
	gbSizer3->AddGrowableRow( 1 );
	
	bSizer2->Add( gbSizer3, 1, 0, 5 );
	
	
	m_general->SetSizer( bSizer2 );
	m_general->Layout();
	bSizer2->Fit( m_general );
	m_nb->AddPage( m_general, _("General"), true );
	m_nbBitmap = wxArtProvider::GetBitmap( wxART_NEW, wxART_FRAME_ICON );
	if ( m_nbBitmap.Ok() )
	{
		m_nbImage = m_nbBitmap.ConvertToImage();
		m_nbImages->Add( m_nbImage.Scale( m_nbImageSize.GetWidth(), m_nbImageSize.GetHeight() ) );
		m_nb->SetPageImage( m_nbIndex, m_nbIndex );
		m_nbIndex++;
	}
	m_telnet = new wxPanel( m_nb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_telnet->SetExtraStyle( wxWS_EX_TRANSIENT );
	
	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* gbSizer2;
	gbSizer2 = new wxGridBagSizer( 0, 0 );
	gbSizer2->SetFlexibleDirection( wxBOTH );
	gbSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_telnet, wxID_ANY, _("Line buffer") ), wxVERTICAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText8 = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("Size:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	bSizer5->Add( m_staticText8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_linebuf = new wxSpinCtrl( sbSizer3->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS|wxSP_WRAP, 1, 100000, 3000 );
	bSizer5->Add( m_linebuf, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	sbSizer3->Add( bSizer5, 1, wxALL, 5 );
	
	
	gbSizer2->Add( sbSizer3, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( m_telnet, wxID_ANY, _("Font") ), wxVERTICAL );
	
	m_font = new wxFontPickerCtrl( sbSizer6->GetStaticBox(), wxID_ANY, wxFont( 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Consolas") ), wxDefaultPosition, wxDefaultSize, wxFNTP_FONTDESC_AS_LABEL|wxFNTP_USEFONT_FOR_LABEL );
	m_font->SetMaxPointSize( 100 ); 
	sbSizer6->Add( m_font, 0, wxALL|wxEXPAND, 5 );
	
	
	gbSizer2->Add( sbSizer6, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( m_telnet, wxID_ANY, _("Timestamps") ), wxVERTICAL );
	
	m_timestamp = new wxCheckBox( sbSizer8->GetStaticBox(), wxID_ANY, _("Show timestamps"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer8->Add( m_timestamp, 0, wxALL|wxEXPAND, 5 );
	
	m_milli = new wxCheckBox( sbSizer8->GetStaticBox(), wxID_ANY, _("Show milliseconds"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer8->Add( m_milli, 0, wxALL, 5 );
	
	
	gbSizer2->Add( sbSizer8, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( m_telnet, wxID_ANY, _("Dark colors") ), wxHORIZONTAL );
	
	m_col1 = new wxColourPickerCtrl( sbSizer9->GetStaticBox(), wxID_ANY, wxColour( 0, 0, 0 ), wxDefaultPosition, wxSize( -1,-1 ), wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	sbSizer9->Add( m_col1, 0, wxALL, 5 );
	
	m_col2 = new wxColourPickerCtrl( sbSizer9->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	sbSizer9->Add( m_col2, 0, wxALL, 5 );
	
	m_col3 = new wxColourPickerCtrl( sbSizer9->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	sbSizer9->Add( m_col3, 0, wxALL, 5 );
	
	m_col4 = new wxColourPickerCtrl( sbSizer9->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	sbSizer9->Add( m_col4, 0, wxALL, 5 );
	
	m_col5 = new wxColourPickerCtrl( sbSizer9->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	sbSizer9->Add( m_col5, 0, wxALL, 5 );
	
	m_col6 = new wxColourPickerCtrl( sbSizer9->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	sbSizer9->Add( m_col6, 0, wxALL, 5 );
	
	m_col7 = new wxColourPickerCtrl( sbSizer9->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	sbSizer9->Add( m_col7, 0, wxALL, 5 );
	
	m_col8 = new wxColourPickerCtrl( sbSizer9->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	sbSizer9->Add( m_col8, 0, wxALL, 5 );
	
	
	gbSizer2->Add( sbSizer9, wxGBPosition( 3, 0 ), wxGBSpan( 1, 3 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer91;
	sbSizer91 = new wxStaticBoxSizer( new wxStaticBox( m_telnet, wxID_ANY, _("Bright colors") ), wxHORIZONTAL );
	
	m_col9 = new wxColourPickerCtrl( sbSizer91->GetStaticBox(), wxID_ANY, wxColour( 0, 0, 0 ), wxDefaultPosition, wxSize( -1,-1 ), wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	sbSizer91->Add( m_col9, 0, wxALL, 5 );
	
	m_col10 = new wxColourPickerCtrl( sbSizer91->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	sbSizer91->Add( m_col10, 0, wxALL, 5 );
	
	m_col11 = new wxColourPickerCtrl( sbSizer91->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	sbSizer91->Add( m_col11, 0, wxALL, 5 );
	
	m_col12 = new wxColourPickerCtrl( sbSizer91->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	sbSizer91->Add( m_col12, 0, wxALL, 5 );
	
	m_col13 = new wxColourPickerCtrl( sbSizer91->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	sbSizer91->Add( m_col13, 0, wxALL, 5 );
	
	m_col14 = new wxColourPickerCtrl( sbSizer91->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	sbSizer91->Add( m_col14, 0, wxALL, 5 );
	
	m_col15 = new wxColourPickerCtrl( sbSizer91->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	sbSizer91->Add( m_col15, 0, wxALL, 5 );
	
	m_col16 = new wxColourPickerCtrl( sbSizer91->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	sbSizer91->Add( m_col16, 0, wxALL, 5 );
	
	
	gbSizer2->Add( sbSizer91, wxGBPosition( 4, 0 ), wxGBSpan( 1, 3 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer81;
	sbSizer81 = new wxStaticBoxSizer( new wxStaticBox( m_telnet, wxID_ANY, _("Options") ), wxVERTICAL );
	
	m_ansion = new wxCheckBox( sbSizer81->GetStaticBox(), wxID_ANY, _("Ansi colors on"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer81->Add( m_ansion, 0, wxALL, 5 );
	
	m_localecho = new wxCheckBox( sbSizer81->GetStaticBox(), wxID_ANY, _("Local echo on"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer81->Add( m_localecho, 0, wxALL, 5 );
	
	m_triggerecho = new wxCheckBox( sbSizer81->GetStaticBox(), wxID_ANY, _("Echo triggers on"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer81->Add( m_triggerecho, 0, wxALL, 5 );
	
	m_scriptverbose = new wxCheckBox( sbSizer81->GetStaticBox(), wxID_ANY, _("Script verbose on"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer81->Add( m_scriptverbose, 0, wxALL, 5 );
	
	
	gbSizer2->Add( sbSizer81, wxGBPosition( 5, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer92;
	sbSizer92 = new wxStaticBoxSizer( new wxStaticBox( m_telnet, wxID_ANY, _("Extra colors") ), wxVERTICAL );
	
	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 3, 2, 0, 0 );
	
	m_echocol = new wxColourPickerCtrl( sbSizer92->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	gSizer2->Add( m_echocol, 0, wxALL, 5 );
	
	m_staticText12 = new wxStaticText( sbSizer92->GetStaticBox(), wxID_ANY, _("Echo color"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	gSizer2->Add( m_staticText12, 0, wxALL, 5 );
	
	m_clientcol = new wxColourPickerCtrl( sbSizer92->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	gSizer2->Add( m_clientcol, 0, wxALL, 5 );
	
	m_staticText13 = new wxStaticText( sbSizer92->GetStaticBox(), wxID_ANY, _("Client color"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	gSizer2->Add( m_staticText13, 0, wxALL, 5 );
	
	m_customcol = new wxColourPickerCtrl( sbSizer92->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	gSizer2->Add( m_customcol, 0, wxALL, 5 );
	
	m_staticText14 = new wxStaticText( sbSizer92->GetStaticBox(), wxID_ANY, _("Custom color"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	gSizer2->Add( m_staticText14, 0, wxALL, 5 );
	
	
	sbSizer92->Add( gSizer2, 1, wxEXPAND, 5 );
	
	
	gbSizer2->Add( sbSizer92, wxGBPosition( 5, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_sample = new wxRichTextCtrl( m_telnet, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxHSCROLL|wxSUNKEN_BORDER|wxVSCROLL|wxWANTS_CHARS );
	m_sample->SetMinSize( wxSize( 200,100 ) );
	
	gbSizer2->Add( m_sample, wxGBPosition( 5, 2 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	m_button2 = new wxButton( m_telnet, wxID_ANY, _("Default colors"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( m_button2, wxGBPosition( 6, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer11;
	sbSizer11 = new wxStaticBoxSizer( new wxStaticBox( m_telnet, wxID_ANY, _("Line wrap options") ), wxVERTICAL );
	
	m_usewrap = new wxCheckBox( sbSizer11->GetStaticBox(), wxID_ANY, _("Wrap lines"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer11->Add( m_usewrap, 0, wxALL, 5 );
	
	m_autowrap = new wxCheckBox( sbSizer11->GetStaticBox(), wxID_ANY, _("Autowrap"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer11->Add( m_autowrap, 0, wxALL, 5 );
	
	m_linewrap = new wxSpinCtrl( sbSizer11->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS|wxSP_WRAP, 0, 1000, 0 );
	sbSizer11->Add( m_linewrap, 0, wxALL, 5 );
	
	
	gbSizer2->Add( sbSizer11, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer14;
	sbSizer14 = new wxStaticBoxSizer( new wxStaticBox( m_telnet, wxID_ANY, _("Misc") ), wxVERTICAL );
	
	mm_clickurl = new wxCheckBox( sbSizer14->GetStaticBox(), wxID_ANY, _("Clickable URLs"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer14->Add( mm_clickurl, 0, wxALL, 5 );
	
	m_usesplit = new wxCheckBox( sbSizer14->GetStaticBox(), wxID_ANY, _("Use splitwindow for scrollback"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer14->Add( m_usesplit, 0, wxALL|wxEXPAND, 5 );
	
	
	gbSizer2->Add( sbSizer14, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	
	gbSizer2->AddGrowableCol( 0 );
	gbSizer2->AddGrowableCol( 1 );
	gbSizer2->AddGrowableCol( 2 );
	gbSizer2->AddGrowableRow( 0 );
	gbSizer2->AddGrowableRow( 1 );
	gbSizer2->AddGrowableRow( 2 );
	gbSizer2->AddGrowableRow( 3 );
	gbSizer2->AddGrowableRow( 4 );
	gbSizer2->AddGrowableRow( 5 );
	
	bSizer51->Add( gbSizer2, 1, wxALL|wxEXPAND, 5 );
	
	
	m_telnet->SetSizer( bSizer51 );
	m_telnet->Layout();
	bSizer51->Fit( m_telnet );
	m_nb->AddPage( m_telnet, _("Output options"), false );
	m_nbBitmap = wxArtProvider::GetBitmap( wxART_EXECUTABLE_FILE, wxART_FRAME_ICON );
	if ( m_nbBitmap.Ok() )
	{
		m_nbImage = m_nbBitmap.ConvertToImage();
		m_nbImages->Add( m_nbImage.Scale( m_nbImageSize.GetWidth(), m_nbImageSize.GetHeight() ) );
		m_nb->SetPageImage( m_nbIndex, m_nbIndex );
		m_nbIndex++;
	}
	m_log = new wxPanel( m_nb, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_log->SetExtraStyle( wxWS_EX_TRANSIENT );
	
	wxBoxSizer* bSizer61;
	bSizer61 = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* gbSizer4;
	gbSizer4 = new wxGridBagSizer( 0, 0 );
	gbSizer4->SetFlexibleDirection( wxBOTH );
	gbSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer16;
	sbSizer16 = new wxStaticBoxSizer( new wxStaticBox( m_log, wxID_ANY, _("Logging options") ), wxVERTICAL );
	
	sbSizer16->SetMinSize( wxSize( 300,-1 ) ); 
	wxString m_logoptsChoices[] = { _("Hmtl"), _("Plain Text"), _("Text with ansi codes") };
	int m_logoptsNChoices = sizeof( m_logoptsChoices ) / sizeof( wxString );
	m_logopts = new wxRadioBox( sbSizer16->GetStaticBox(), wxID_ANY, _("Format"), wxDefaultPosition, wxDefaultSize, m_logoptsNChoices, m_logoptsChoices, 1, wxRA_SPECIFY_COLS );
	m_logopts->SetSelection( 0 );
	sbSizer16->Add( m_logopts, 0, wxALL|wxEXPAND, 5 );
	
	m_includescroll = new wxCheckBox( sbSizer16->GetStaticBox(), wxID_ANY, _("Include scroll buffer"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer16->Add( m_includescroll, 0, wxALL, 5 );
	
	m_ts = new wxCheckBox( sbSizer16->GetStaticBox(), wxID_ANY, _("Timestamps"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer16->Add( m_ts, 0, wxALL, 5 );
	
	m_staticText15 = new wxStaticText( sbSizer16->GetStaticBox(), wxID_ANY, _("Logging directory:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	sbSizer16->Add( m_staticText15, 0, wxALL, 5 );
	
	m_dirPicker1 = new wxDirPickerCtrl( sbSizer16->GetStaticBox(), wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	sbSizer16->Add( m_dirPicker1, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText16 = new wxStaticText( sbSizer16->GetStaticBox(), wxID_ANY, _("Filename:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	sbSizer16->Add( m_staticText16, 0, wxALL, 5 );
	
	m_logfile = new wxTextCtrl( sbSizer16->GetStaticBox(), wxID_ANY, _("log.txt"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer16->Add( m_logfile, 0, wxALL|wxEXPAND, 5 );
	
	m_startlog = new wxToggleButton( sbSizer16->GetStaticBox(), wxID_ANY, _("Start logging"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer16->Add( m_startlog, 0, wxALL, 5 );
	
	
	gbSizer4->Add( sbSizer16, wxGBPosition( 0, 0 ), wxGBSpan( 5, 1 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer22;
	sbSizer22 = new wxStaticBoxSizer( new wxStaticBox( m_log, wxID_ANY, _("Working directory") ), wxVERTICAL );
	
	m_workdir = new wxDirPickerCtrl( sbSizer22->GetStaticBox(), wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
	sbSizer22->Add( m_workdir, 0, wxALL|wxEXPAND, 5 );
	
	
	gbSizer4->Add( sbSizer22, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer161;
	sbSizer161 = new wxStaticBoxSizer( new wxStaticBox( m_log, wxID_ANY, _("Profile directory") ), wxVERTICAL );
	
	m_profdir = new wxDirPickerCtrl( sbSizer161->GetStaticBox(), wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
	sbSizer161->Add( m_profdir, 0, wxALL|wxEXPAND, 5 );
	
	
	gbSizer4->Add( sbSizer161, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer18;
	sbSizer18 = new wxStaticBoxSizer( new wxStaticBox( m_log, wxID_ANY, _("Scripting directory") ), wxVERTICAL );
	
	m_scriptdir = new wxDirPickerCtrl( sbSizer18->GetStaticBox(), wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
	sbSizer18->Add( m_scriptdir, 0, wxALL|wxEXPAND, 5 );
	
	
	gbSizer4->Add( sbSizer18, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer19;
	sbSizer19 = new wxStaticBoxSizer( new wxStaticBox( m_log, wxID_ANY, _("Package directory") ), wxVERTICAL );
	
	m_packdir = new wxDirPickerCtrl( sbSizer19->GetStaticBox(), wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
	sbSizer19->Add( m_packdir, 0, wxALL|wxEXPAND, 5 );
	
	
	gbSizer4->Add( sbSizer19, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer21;
	sbSizer21 = new wxStaticBoxSizer( new wxStaticBox( m_log, wxID_ANY, _("Database directory") ), wxVERTICAL );
	
	m_dbdir = new wxDirPickerCtrl( sbSizer21->GetStaticBox(), wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
	sbSizer21->Add( m_dbdir, 0, wxALL|wxEXPAND, 5 );
	
	
	gbSizer4->Add( sbSizer21, wxGBPosition( 4, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer211;
	sbSizer211 = new wxStaticBoxSizer( new wxStaticBox( m_log, wxID_ANY, _("Sound (MSP) directory") ), wxVERTICAL );
	
	m_mspdir = new wxDirPickerCtrl( sbSizer211->GetStaticBox(), wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
	sbSizer211->Add( m_mspdir, 0, wxALL|wxEXPAND, 5 );
	
	
	gbSizer4->Add( sbSizer211, wxGBPosition( 5, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer221;
	sbSizer221 = new wxStaticBoxSizer( new wxStaticBox( m_log, wxID_ANY, _("Lua directory") ), wxVERTICAL );
	
	m_luadir = new wxDirPickerCtrl( sbSizer221->GetStaticBox(), wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL );
	sbSizer221->Add( m_luadir, 0, wxALL|wxEXPAND, 5 );
	
	
	gbSizer4->Add( sbSizer221, wxGBPosition( 6, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	
	gbSizer4->AddGrowableCol( 1 );
	
	bSizer61->Add( gbSizer4, 1, wxEXPAND, 5 );
	
	
	m_log->SetSizer( bSizer61 );
	m_log->Layout();
	bSizer61->Fit( m_log );
	m_nb->AddPage( m_log, _("Logging && paths"), false );
	m_nbBitmap = wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_FRAME_ICON );
	if ( m_nbBitmap.Ok() )
	{
		m_nbImage = m_nbBitmap.ConvertToImage();
		m_nbImages->Add( m_nbImage.Scale( m_nbImageSize.GetWidth(), m_nbImageSize.GetHeight() ) );
		m_nb->SetPageImage( m_nbIndex, m_nbIndex );
		m_nbIndex++;
	}
	
	bSizer1->Add( m_nb, 10, wxEXPAND | wxALL, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	
	bSizer1->Add( m_sdbSizer1, 0, wxALL, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_tablist->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DlgOptions::OnTabList ), NULL, this );
	m_evall->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DlgOptions::OnUseEvents ), NULL, this );
	m_font->Connect( wxEVT_COMMAND_FONTPICKER_CHANGED, wxFontPickerEventHandler( DlgOptions::OnFontChanged ), NULL, this );
	m_col1->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol1 ), NULL, this );
	m_col2->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol2 ), NULL, this );
	m_col3->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol3 ), NULL, this );
	m_col4->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol4 ), NULL, this );
	m_col5->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol5 ), NULL, this );
	m_col6->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol6 ), NULL, this );
	m_col7->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol7 ), NULL, this );
	m_col8->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol8 ), NULL, this );
	m_col9->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol9 ), NULL, this );
	m_col10->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol10 ), NULL, this );
	m_col11->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol11 ), NULL, this );
	m_col12->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol12 ), NULL, this );
	m_col13->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol13 ), NULL, this );
	m_col14->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol14 ), NULL, this );
	m_col15->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol15 ), NULL, this );
	m_col16->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol16 ), NULL, this );
	m_echocol->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnColEcho ), NULL, this );
	m_clientcol->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnColClient ), NULL, this );
	m_customcol->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnColCustom ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DlgOptions::OnDefaultColors ), NULL, this );
	m_usewrap->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DlgOptions::OnUseWrap ), NULL, this );
	m_autowrap->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DlgOptions::OnAutoWrap ), NULL, this );
	m_startlog->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( DlgOptions::OnStartLogging ), NULL, this );
}

DlgOptions::~DlgOptions()
{
	// Disconnect Events
	m_tablist->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DlgOptions::OnTabList ), NULL, this );
	m_evall->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DlgOptions::OnUseEvents ), NULL, this );
	m_font->Disconnect( wxEVT_COMMAND_FONTPICKER_CHANGED, wxFontPickerEventHandler( DlgOptions::OnFontChanged ), NULL, this );
	m_col1->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol1 ), NULL, this );
	m_col2->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol2 ), NULL, this );
	m_col3->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol3 ), NULL, this );
	m_col4->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol4 ), NULL, this );
	m_col5->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol5 ), NULL, this );
	m_col6->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol6 ), NULL, this );
	m_col7->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol7 ), NULL, this );
	m_col8->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol8 ), NULL, this );
	m_col9->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol9 ), NULL, this );
	m_col10->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol10 ), NULL, this );
	m_col11->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol11 ), NULL, this );
	m_col12->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol12 ), NULL, this );
	m_col13->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol13 ), NULL, this );
	m_col14->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol14 ), NULL, this );
	m_col15->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol15 ), NULL, this );
	m_col16->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnCol16 ), NULL, this );
	m_echocol->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnColEcho ), NULL, this );
	m_clientcol->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnColClient ), NULL, this );
	m_customcol->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( DlgOptions::OnColCustom ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DlgOptions::OnDefaultColors ), NULL, this );
	m_usewrap->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DlgOptions::OnUseWrap ), NULL, this );
	m_autowrap->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DlgOptions::OnAutoWrap ), NULL, this );
	m_startlog->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( DlgOptions::OnStartLogging ), NULL, this );
	
}
