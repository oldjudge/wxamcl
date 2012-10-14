///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 10 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "objects_dlgs.h"

///////////////////////////////////////////////////////////////////////////

ObjDlg::ObjDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0|wxCLIP_CHILDREN );
	m_trigger = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	bSizer4->SetMinSize( wxSize( 200,-1 ) ); 
	m_tree = new wxTreeCtrl( m_trigger, ID_TREE, wxDefaultPosition, wxSize( -1,-1 ), wxTR_DEFAULT_STYLE|wxTR_EDIT_LABELS|wxSUNKEN_BORDER );
	m_tree->SetToolTip( _("List of all defined actions") );
	
	bSizer4->Add( m_tree, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer8->Add( bSizer4, 1, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_trigger, wxID_ANY, _("Define action") ), wxVERTICAL );
	
	wxGridBagSizer* gbSizer2;
	gbSizer2 = new wxGridBagSizer( 1, 1 );
	gbSizer2->SetFlexibleDirection( wxBOTH );
	gbSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	m_staticText6 = new wxStaticText( m_trigger, wxID_ANY, _("Label:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	gbSizer2->Add( m_staticText6, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_label = new wxTextCtrl( m_trigger, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxSUNKEN_BORDER );
	m_label->SetToolTip( _("Name of the trigger") );
	
	gbSizer2->Add( m_label, wxGBPosition( 0, 1 ), wxGBSpan( 1, 3 ), wxALL|wxEXPAND, 5 );
	
	m_staticText10 = new wxStaticText( m_trigger, wxID_ANY, _("Pattern:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	gbSizer2->Add( m_staticText10, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_pattern = new wxTextCtrl( m_trigger, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_LEFT|wxTE_MULTILINE|wxTE_WORDWRAP|wxSUNKEN_BORDER );
	m_pattern->SetToolTip( _("Regular expression pattern of mud text") );
	m_pattern->SetMaxSize( wxSize( -1,24 ) );
	
	gbSizer2->Add( m_pattern, wxGBPosition( 1, 1 ), wxGBSpan( 2, 3 ), wxALL|wxEXPAND|wxFIXED_MINSIZE, 5 );
	
	m_patternedit = new wxButton( m_trigger, wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( m_patternedit, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_staticText11 = new wxStaticText( m_trigger, wxID_ANY, _("Action:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	gbSizer2->Add( m_staticText11, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_action= new amcScriptEdit(m_trigger, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER);
	gbSizer2->Add( m_action, wxGBPosition( 3, 1 ), wxGBSpan( 5, 3 ), wxALL|wxEXPAND, 0 );
	
	m_sceditor = new wxButton( m_trigger, wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( m_sceditor, wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_staticText13 = new wxStaticText( m_trigger, wxID_ANY, _("Group:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	gbSizer2->Add( m_staticText13, wxGBPosition( 8, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_class = new wxComboBox( m_trigger, wxID_ANY, _("default"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxSUNKEN_BORDER ); 
	gbSizer2->Add( m_class, wxGBPosition( 8, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_onoff = new wxToggleButton( m_trigger, ID_TOGGLECLASS, _("Group off"), wxDefaultPosition, wxDefaultSize, 0 );
	m_onoff->SetToolTip( _("Disable all actions in a class") );
	
	gbSizer2->Add( m_onoff, wxGBPosition( 8, 2 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_delclass = new wxButton( m_trigger, wxID_ANY, _("Delete group"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( m_delclass, wxGBPosition( 8, 3 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_staticText14 = new wxStaticText( m_trigger, wxID_ANY, _("Priority:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	gbSizer2->Add( m_staticText14, wxGBPosition( 9, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_prior = new wxSpinCtrl( m_trigger, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxSP_ARROW_KEYS, 0, 100, 100 );
	m_prior->SetToolTip( _("Priority of the action (highest evaluated first)") );
	
	gbSizer2->Add( m_prior, wxGBPosition( 9, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_staticText9 = new wxStaticText( m_trigger, wxID_ANY, _("Lines:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	gbSizer2->Add( m_staticText9, wxGBPosition( 9, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_lines = new wxSpinCtrl( m_trigger, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 48,-1 ), wxSP_ARROW_KEYS, 1, 100, 1 );
	gbSizer2->Add( m_lines, wxGBPosition( 9, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_oncolor = new wxCheckBox( m_trigger, wxID_ANY, _("Match on color"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( m_oncolor, wxGBPosition( 10, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_amccombo = new amcColorComboBox(m_trigger);
	m_amccombo->Enable( false );
	
	gbSizer2->Add( m_amccombo, wxGBPosition( 10, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	m_staticText8 = new wxStaticText( m_trigger, wxID_ANY, _("Matched:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	gbSizer2->Add( m_staticText8, wxGBPosition( 11, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_matched = new wxTextCtrl( m_trigger, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 48,-1 ), wxTE_READONLY|wxSUNKEN_BORDER );
	m_matched->SetToolTip( _("Show how often the trigger matched") );
	
	gbSizer2->Add( m_matched, wxGBPosition( 11, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_tron = new wxCheckBox( m_trigger, wxID_ANY, _("Action active"), wxDefaultPosition, wxDefaultSize, 0 );
	m_tron->SetToolTip( _("Action active?") );
	
	gbSizer2->Add( m_tron, wxGBPosition( 12, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_rextest = new wxButton( m_trigger, wxID_ANY, _("Test regular expression"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( m_rextest, wxGBPosition( 14, 1 ), wxGBSpan( 1, 2 ), wxALL, 5 );
	
	m_sendscript = new wxCheckBox( m_trigger, wxID_ANY, _("Send to script"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( m_sendscript, wxGBPosition( 5, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	
	gbSizer2->AddGrowableCol( 1 );
	
	sbSizer2->Add( gbSizer2, 1, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	wxGridSizer* gSizer6;
	gSizer6 = new wxGridSizer( 1, 3, 0, 0 );
	
	m_btadd = new wxButton( m_trigger, ID_ADDACTION, _("Add action"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer6->Add( m_btadd, 0, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );
	
	m_btedit = new wxButton( m_trigger, ID_EDITACTION, _("Edit action"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer6->Add( m_btedit, 0, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );
	
	m_btdel = new wxButton( m_trigger, ID_DELACTION, _("Delete action"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer6->Add( m_btdel, 0, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );
	
	
	bSizer10->Add( gSizer6, 1, wxALIGN_RIGHT|wxALL, 5 );
	
	
	sbSizer2->Add( bSizer10, 0, wxALIGN_BOTTOM|wxALIGN_RIGHT|wxBOTTOM|wxLEFT|wxTOP, 5 );
	
	
	bSizer8->Add( sbSizer2, 3, wxALL|wxEXPAND, 5 );
	
	
	m_trigger->SetSizer( bSizer8 );
	m_trigger->Layout();
	bSizer8->Fit( m_trigger );
	m_notebook->AddPage( m_trigger, _("Actions"), false );
	m_alias = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( m_alias, wxID_ANY, _("Defined aliases") ), wxVERTICAL );
	
	m_listalias = new wxListCtrl( m_alias, ID_LALIAS, wxDefaultPosition, wxSize( 500,-1 ), wxLC_REPORT|wxSUNKEN_BORDER );
	sbSizer7->Add( m_listalias, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer3->Add( sbSizer7, 2, wxALL|wxEXPAND, 5 );
	
	wxGridBagSizer* gbSizer21;
	gbSizer21 = new wxGridBagSizer( 0, 0 );
	gbSizer21->SetFlexibleDirection( wxBOTH );
	gbSizer21->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );
	
	m_staticText61 = new wxStaticText( m_alias, wxID_ANY, _("Alias:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText61->Wrap( -1 );
	gbSizer21->Add( m_staticText61, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_defalias = new wxTextCtrl( m_alias, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer21->Add( m_defalias, wxGBPosition( 0, 1 ), wxGBSpan( 1, 3 ), wxALL|wxEXPAND, 5 );
	
	m_staticText7 = new wxStaticText( m_alias, wxID_ANY, _("Action:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	gbSizer21->Add( m_staticText7, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_defaction = new wxTextCtrl( m_alias, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	gbSizer21->Add( m_defaction, wxGBPosition( 1, 1 ), wxGBSpan( 2, 3 ), wxALL|wxEXPAND, 5 );
	
	m_staticText101 = new wxStaticText( m_alias, wxID_ANY, _("Group:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText101->Wrap( -1 );
	gbSizer21->Add( m_staticText101, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_groupcombo = new wxComboBox( m_alias, wxID_ANY, _("default"), wxDefaultPosition, wxDefaultSize, 0, NULL); 
	gbSizer21->Add( m_groupcombo, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	m_alfilter = new wxCheckBox( m_alias, wxID_ANY, _("filter"), wxDefaultPosition, wxDefaultSize, 0 );
	m_alfilter->SetValue(true); 
	gbSizer21->Add( m_alfilter, wxGBPosition( 3, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_groupon = new wxToggleButton( m_alias, wxID_ANY, _("Group off"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer21->Add( m_groupon, wxGBPosition( 3, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_alon = new wxCheckBox( m_alias, wxID_ANY, _("Alias active"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer21->Add( m_alon, wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_delgroup = new wxButton( m_alias, wxID_ANY, _("Delete group"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer21->Add( m_delgroup, wxGBPosition( 4, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	gbSizer21->AddGrowableCol( 1 );
	gbSizer21->AddGrowableRow( 1 );
	
	bSizer3->Add( gbSizer21, 1, wxALL|wxEXPAND, 5 );
	
	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 1, 3, 0, 0 );
	
	m_addalias = new wxButton( m_alias, ID_ADDALIAS, _("Add alias"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_addalias, 0, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );
	
	m_editalias = new wxButton( m_alias, ID_EDITALIAS, _("Edit alias"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_editalias, 0, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );
	
	m_delalias = new wxButton( m_alias, ID_DELALIAS, _("Delete alias"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_delalias, 0, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );
	
	
	bSizer3->Add( gSizer2, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	
	m_alias->SetSizer( bSizer3 );
	m_alias->Layout();
	bSizer3->Fit( m_alias );
	m_notebook->AddPage( m_alias, _("Alias"), false );
	m_buttons = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer131;
	bSizer131 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );
	
	m_treeCtrl3 = new wxTreeCtrl( m_buttons, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	bSizer14->Add( m_treeCtrl3, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer131->Add( bSizer14, 1, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer11;
	sbSizer11 = new wxStaticBoxSizer( new wxStaticBox( m_buttons, wxID_ANY, _("Define buttons") ), wxVERTICAL );
	
	wxGridBagSizer* gbSizer10;
	gbSizer10 = new wxGridBagSizer( 0, 0 );
	gbSizer10->SetFlexibleDirection( wxBOTH );
	gbSizer10->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText371 = new wxStaticText( m_buttons, wxID_ANY, _("Label:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText371->Wrap( -1 );
	gbSizer10->Add( m_staticText371, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_butlabel = new wxTextCtrl( m_buttons, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer10->Add( m_butlabel, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	m_staticText38 = new wxStaticText( m_buttons, wxID_ANY, _("Command:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText38->Wrap( -1 );
	gbSizer10->Add( m_staticText38, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_butcommand = new wxTextCtrl( m_buttons, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer10->Add( m_butcommand, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	m_staticText39 = new wxStaticText( m_buttons, wxID_ANY, _("Parent toolbar:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText39->Wrap( -1 );
	gbSizer10->Add( m_staticText39, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_parenttool = new wxComboBox( m_buttons, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	gbSizer10->Add( m_parenttool, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	Bitmap = new wxStaticText( m_buttons, wxID_ANY, _("Bitmap: "), wxDefaultPosition, wxDefaultSize, 0 );
	Bitmap->Wrap( -1 );
	gbSizer10->Add( Bitmap, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_bitmap = new wxTextCtrl( m_buttons, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer10->Add( m_bitmap, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	
	gbSizer10->AddGrowableCol( 1 );
	
	sbSizer11->Add( gbSizer10, 1, wxALL|wxEXPAND, 5 );
	
	wxGridSizer* gSizer7;
	gSizer7 = new wxGridSizer( 1, 3, 0, 0 );
	
	m_addbutton = new wxButton( m_buttons, wxID_ANY, _("Add button"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer7->Add( m_addbutton, 0, wxALL, 5 );
	
	m_editbutton = new wxButton( m_buttons, wxID_ANY, _("Edit button"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer7->Add( m_editbutton, 0, wxALL, 5 );
	
	m_delbutton = new wxButton( m_buttons, wxID_ANY, _("Delete button"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer7->Add( m_delbutton, 0, wxALL, 5 );
	
	
	sbSizer11->Add( gSizer7, 0, wxALL, 5 );
	
	
	bSizer131->Add( sbSizer11, 4, wxALL|wxEXPAND, 5 );
	
	
	m_buttons->SetSizer( bSizer131 );
	m_buttons->Layout();
	bSizer131->Fit( m_buttons );
	m_notebook->AddPage( m_buttons, _("Buttons"), false );
	m_gauge = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer102;
	bSizer102 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_gaugew = new wxTreeCtrl( m_gauge, wxID_ANY, wxDefaultPosition, wxSize( 150,-1 ), wxTR_DEFAULT_STYLE );
	bSizer11->Add( m_gaugew, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer102->Add( bSizer11, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer71;
	sbSizer71 = new wxStaticBoxSizer( new wxStaticBox( m_gauge, wxID_ANY, _("Define gauges") ), wxVERTICAL );
	
	wxGridBagSizer* gbSizer9;
	gbSizer9 = new wxGridBagSizer( 0, 0 );
	gbSizer9->SetFlexibleDirection( wxBOTH );
	gbSizer9->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	m_staticText24 = new wxStaticText( m_gauge, wxID_ANY, _("Label:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	gbSizer9->Add( m_staticText24, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_gaugelabel = new wxTextCtrl( m_gauge, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer9->Add( m_gaugelabel, wxGBPosition( 0, 1 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );
	
	m_staticText25 = new wxStaticText( m_gauge, wxID_ANY, _("Variable 1:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	gbSizer9->Add( m_staticText25, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxArrayString m_var1Choices;
	m_var1 = new wxChoice( m_gauge, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_var1Choices, 0 );
	m_var1->SetSelection( 0 );
	gbSizer9->Add( m_var1, wxGBPosition( 1, 1 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );
	
	m_staticText26 = new wxStaticText( m_gauge, wxID_ANY, _("Variable 2:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	gbSizer9->Add( m_staticText26, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxArrayString m_var2Choices;
	m_var2 = new wxChoice( m_gauge, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_var2Choices, 0 );
	m_var2->SetSelection( 0 );
	gbSizer9->Add( m_var2, wxGBPosition( 2, 1 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );
	
	wxString m_gaugedirChoices[] = { _("Vertical"), _("Horizontal") };
	int m_gaugedirNChoices = sizeof( m_gaugedirChoices ) / sizeof( wxString );
	m_gaugedir = new wxRadioBox( m_gauge, wxID_ANY, _("Direction"), wxDefaultPosition, wxDefaultSize, m_gaugedirNChoices, m_gaugedirChoices, 2, wxRA_SPECIFY_ROWS );
	m_gaugedir->SetSelection( 0 );
	gbSizer9->Add( m_gaugedir, wxGBPosition( 0, 3 ), wxGBSpan( 3, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( m_gauge, wxID_ANY, _("Style") ), wxVERTICAL );
	
	wxString m_drawstyleChoices[] = { _("Standard"), _("Lines"), _("Rounded"), _("Rounded with Lines") };
	int m_drawstyleNChoices = sizeof( m_drawstyleChoices ) / sizeof( wxString );
	m_drawstyle = new wxChoice( m_gauge, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_drawstyleNChoices, m_drawstyleChoices, 0 );
	m_drawstyle->SetSelection( 0 );
	sbSizer8->Add( m_drawstyle, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	
	gbSizer9->Add( sbSizer8, wxGBPosition( 0, 4 ), wxGBSpan( 3, 1 ), wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer101;
	sbSizer101 = new wxStaticBoxSizer( new wxStaticBox( m_gauge, wxID_ANY, _("Label properties") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 3, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText36 = new wxStaticText( m_gauge, wxID_ANY, _("Position:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	fgSizer2->Add( m_staticText36, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxString m_textposChoices[] = { _("below gauge"), _("above gauge"), _("gauge") };
	int m_textposNChoices = sizeof( m_textposChoices ) / sizeof( wxString );
	m_textpos = new wxChoice( m_gauge, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_textposNChoices, m_textposChoices, 0 );
	m_textpos->SetSelection( 0 );
	fgSizer2->Add( m_textpos, 1, wxALL|wxEXPAND, 5 );
	
	m_staticText37 = new wxStaticText( m_gauge, wxID_ANY, _("Colour:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	fgSizer2->Add( m_staticText37, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_gaugetextcol = new wxColourPickerCtrl( m_gauge, wxID_ANY, wxColour( 255, 255, 255 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	fgSizer2->Add( m_gaugetextcol, 0, wxALL, 5 );
	
	m_showvalue = new wxCheckBox( m_gauge, wxID_ANY, _("show value"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_showvalue, 0, wxALL|wxEXPAND, 5 );
	
	
	sbSizer101->Add( fgSizer2, 1, wxALL|wxEXPAND, 5 );
	
	
	gbSizer9->Add( sbSizer101, wxGBPosition( 5, 0 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( m_gauge, wxID_ANY, _("Position of gauge") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 4, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText32 = new wxStaticText( m_gauge, wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	fgSizer1->Add( m_staticText32, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_posx = new wxSpinCtrl( m_gauge, wxID_ANY, wxT("10"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 5000, 0 );
	fgSizer1->Add( m_posx, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText33 = new wxStaticText( m_gauge, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	fgSizer1->Add( m_staticText33, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_posy = new wxSpinCtrl( m_gauge, wxID_ANY, wxT("10"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 5000, 0 );
	fgSizer1->Add( m_posy, 0, wxALL, 5 );
	
	m_staticText34 = new wxStaticText( m_gauge, wxID_ANY, _("Width:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText34->Wrap( -1 );
	fgSizer1->Add( m_staticText34, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_width = new wxSpinCtrl( m_gauge, wxID_ANY, wxT("40"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 2000, 0 );
	fgSizer1->Add( m_width, 0, wxALL, 5 );
	
	m_staticText35 = new wxStaticText( m_gauge, wxID_ANY, _("Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText35->Wrap( -1 );
	fgSizer1->Add( m_staticText35, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_height = new wxSpinCtrl( m_gauge, wxID_ANY, wxT("200"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 2000, 0 );
	fgSizer1->Add( m_height, 0, wxALL, 5 );
	
	
	sbSizer10->Add( fgSizer1, 1, wxALL|wxEXPAND, 5 );
	
	
	gbSizer9->Add( sbSizer10, wxGBPosition( 5, 2 ), wxGBSpan( 1, 4 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText351 = new wxStaticText( m_gauge, wxID_ANY, _("Parent window:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText351->Wrap( -1 );
	gbSizer9->Add( m_staticText351, wxGBPosition( 6, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL|wxLEFT, 5 );
	
	m_parentw = new wxComboBox( m_gauge, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	gbSizer9->Add( m_parentw, wxGBPosition( 6, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	wxGridSizer* gSizer61;
	gSizer61 = new wxGridSizer( 3, 2, 0, 5 );
	
	m_staticText27 = new wxStaticText( m_gauge, wxID_ANY, _("Foreground:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	gSizer61->Add( m_staticText27, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_fore = new wxColourPickerCtrl( m_gauge, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_SHOW_LABEL );
	gSizer61->Add( m_fore, 0, wxALL, 5 );
	
	m_staticText28 = new wxStaticText( m_gauge, wxID_ANY, _("Background:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	gSizer61->Add( m_staticText28, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_back = new wxColourPickerCtrl( m_gauge, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	gSizer61->Add( m_back, 0, wxALL, 5 );
	
	m_staticText29 = new wxStaticText( m_gauge, wxID_ANY, _("Alarm:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	gSizer61->Add( m_staticText29, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_alarm = new wxColourPickerCtrl( m_gauge, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL );
	gSizer61->Add( m_alarm, 0, wxALL, 5 );
	
	
	gbSizer9->Add( gSizer61, wxGBPosition( 3, 0 ), wxGBSpan( 1, 6 ), wxALL, 5 );
	
	m_alarmslider = new wxSlider( m_gauge, wxID_ANY, 30, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	gbSizer9->Add( m_alarmslider, wxGBPosition( 4, 1 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );
	
	m_staticText40 = new wxStaticText( m_gauge, wxID_ANY, _("Show alarm color %"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText40->Wrap( -1 );
	gbSizer9->Add( m_staticText40, wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	gbSizer9->AddGrowableCol( 1 );
	
	sbSizer71->Add( gbSizer9, 1, wxALL|wxEXPAND, 5 );
	
	wxGridSizer* gSizer5;
	gSizer5 = new wxGridSizer( 1, 3, 0, 0 );
	
	m_addgauge = new wxButton( m_gauge, wxID_ANY, _("Add gauge"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer5->Add( m_addgauge, 0, wxALL, 5 );
	
	m_editgauge = new wxButton( m_gauge, wxID_ANY, _("Edit gauge"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer5->Add( m_editgauge, 0, wxALL, 5 );
	
	m_delgauge = new wxButton( m_gauge, wxID_ANY, _("Delete gauge"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer5->Add( m_delgauge, 0, wxALL, 5 );
	
	
	sbSizer71->Add( gSizer5, 0, wxALL, 5 );
	
	
	bSizer102->Add( sbSizer71, 1, wxALL|wxEXPAND, 5 );
	
	
	m_gauge->SetSizer( bSizer102 );
	m_gauge->Layout();
	bSizer102->Fit( m_gauge );
	m_notebook->AddPage( m_gauge, _("Gauges"), false );
	m_hotkey = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer21;
	sbSizer21 = new wxStaticBoxSizer( new wxStaticBox( m_hotkey, wxID_ANY, _("Defined hotkeys") ), wxVERTICAL );
	
	m_listhkey = new wxListCtrl( m_hotkey, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ALIGN_LEFT|wxLC_REPORT );
	sbSizer21->Add( m_listhkey, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer7->Add( sbSizer21, 2, wxALL|wxEXPAND, 5 );
	
	wxGridBagSizer* gbSizer3;
	gbSizer3 = new wxGridBagSizer( 0, 0 );
	gbSizer3->SetFlexibleDirection( wxBOTH );
	gbSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );
	
	m_text11 = new wxStaticText( m_hotkey, wxID_ANY, _("Press key:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_text11->Wrap( -1 );
	gbSizer3->Add( m_text11, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_hkey = new amcHotkeyCtrl(m_hotkey);
	gbSizer3->Add( m_hkey, wxGBPosition( 0, 1 ), wxGBSpan( 1, 3 ), wxALL|wxEXPAND, 5 );
	
	m_groupdel = new wxButton( m_hotkey, wxID_ANY, _("Delete group"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer3->Add( m_groupdel, wxGBPosition( 4, 3 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_staticText12 = new wxStaticText( m_hotkey, wxID_ANY, _("Command:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	gbSizer3->Add( m_staticText12, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_hkeyaction = new wxTextCtrl( m_hotkey, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	gbSizer3->Add( m_hkeyaction, wxGBPosition( 1, 1 ), wxGBSpan( 2, 3 ), wxALL|wxEXPAND, 5 );
	
	m_hkeyon = new wxCheckBox( m_hotkey, wxID_ANY, _("Hotkey active"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer3->Add( m_hkeyon, wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_hkcombo = new wxComboBox( m_hotkey, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL); 
	gbSizer3->Add( m_hkcombo, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	m_staticText131 = new wxStaticText( m_hotkey, wxID_ANY, _("Group:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText131->Wrap( -1 );
	gbSizer3->Add( m_staticText131, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_hkgroupoff = new wxToggleButton( m_hotkey, wxID_ANY, _("Group off"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer3->Add( m_hkgroupoff, wxGBPosition( 3, 3 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	m_hkfilter = new wxCheckBox( m_hotkey, wxID_ANY, _("filter"), wxDefaultPosition, wxDefaultSize, 0 );
	m_hkfilter->SetValue(true); 
	gbSizer3->Add( m_hkfilter, wxGBPosition( 3, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	gbSizer3->AddGrowableCol( 1 );
	gbSizer3->AddGrowableRow( 1 );
	
	bSizer7->Add( gbSizer3, 1, wxALL|wxEXPAND, 5 );
	
	wxGridSizer* gSizer3;
	gSizer3 = new wxGridSizer( 1, 3, 0, 0 );
	
	m_addkey = new wxButton( m_hotkey, wxID_ANY, _("Add hotkey"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( m_addkey, 0, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );
	
	m_editkey = new wxButton( m_hotkey, wxID_ANY, _("Edit hotkey"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( m_editkey, 0, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );
	
	m_delkey = new wxButton( m_hotkey, wxID_ANY, _("Delete hotkey"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( m_delkey, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	
	bSizer7->Add( gSizer3, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	
	m_hotkey->SetSizer( bSizer7 );
	m_hotkey->Layout();
	bSizer7->Fit( m_hotkey );
	m_notebook->AddPage( m_hotkey, _("Hotkeys"), false );
	m_list = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer101;
	bSizer101 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_list, wxID_ANY, _("Defined lists") ), wxVERTICAL );
	
	m_listlist = new wxListCtrl( m_list, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT );
	sbSizer3->Add( m_listlist, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer101->Add( sbSizer3, 2, wxALL|wxEXPAND, 5 );
	
	wxGridBagSizer* gbSizer5;
	gbSizer5 = new wxGridBagSizer( 2, 0 );
	gbSizer5->SetFlexibleDirection( wxBOTH );
	gbSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText17 = new wxStaticText( m_list, wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	gbSizer5->Add( m_staticText17, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_deflist = new wxTextCtrl( m_list, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer5->Add( m_deflist, wxGBPosition( 0, 1 ), wxGBSpan( 1, 3 ), wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_staticText18 = new wxStaticText( m_list, wxID_ANY, _("Items:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	gbSizer5->Add( m_staticText18, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_items = new wxComboBox( m_list, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	gbSizer5->Add( m_items, wxGBPosition( 1, 1 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	m_additem = new wxButton( m_list, wxID_ANY, _("Add item"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer5->Add( m_additem, wxGBPosition( 1, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	m_sgroup = new wxStaticText( m_list, wxID_ANY, _("Group:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_sgroup->Wrap( -1 );
	gbSizer5->Add( m_sgroup, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_ligroup = new wxComboBox( m_list, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL ); 
	gbSizer5->Add( m_ligroup, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_lifilter = new wxCheckBox( m_list, wxID_ANY, _("filter"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lifilter->SetValue(true); 
	gbSizer5->Add( m_lifilter, wxGBPosition( 2, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_ligroupoff = new wxToggleButton( m_list, wxID_ANY, _("Group off"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer5->Add( m_ligroupoff, wxGBPosition( 2, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	m_lion = new wxCheckBox( m_list, wxID_ANY, _("List active"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer5->Add( m_lion, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_lidelgroup = new wxButton( m_list, wxID_ANY, _("Delete group"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer5->Add( m_lidelgroup, wxGBPosition( 3, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	
	gbSizer5->AddGrowableCol( 1 );
	
	bSizer101->Add( gbSizer5, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	wxGridBagSizer* gbSizer6;
	gbSizer6 = new wxGridBagSizer( 0, 0 );
	gbSizer6->SetFlexibleDirection( wxBOTH );
	gbSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_addlist = new wxButton( m_list, wxID_ANY, _("Add list"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer6->Add( m_addlist, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_editlist = new wxButton( m_list, wxID_ANY, _("Edit list"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer6->Add( m_editlist, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_dellist = new wxButton( m_list, wxID_ANY, _("Delete list"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer6->Add( m_dellist, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	
	bSizer101->Add( gbSizer6, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	
	m_list->SetSizer( bSizer101 );
	m_list->Layout();
	bSizer101->Fit( m_list );
	m_notebook->AddPage( m_list, _("Lists"), false );
	m_timer = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer1011;
	bSizer1011 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer31;
	sbSizer31 = new wxStaticBoxSizer( new wxStaticBox( m_timer, wxID_ANY, _("Defined timers") ), wxVERTICAL );
	
	m_timerlist = new wxListCtrl( m_timer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT );
	sbSizer31->Add( m_timerlist, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer1011->Add( sbSizer31, 2, wxALL|wxEXPAND, 5 );
	
	wxGridBagSizer* gbSizer51;
	gbSizer51 = new wxGridBagSizer( 0, 0 );
	gbSizer51->SetFlexibleDirection( wxBOTH );
	gbSizer51->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText171 = new wxStaticText( m_timer, wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText171->Wrap( -1 );
	gbSizer51->Add( m_staticText171, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_deftimer = new wxTextCtrl( m_timer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer51->Add( m_deftimer, wxGBPosition( 0, 1 ), wxGBSpan( 1, 3 ), wxALL|wxEXPAND, 5 );
	
	m_staticText181 = new wxStaticText( m_timer, wxID_ANY, _("Action:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText181->Wrap( -1 );
	gbSizer51->Add( m_staticText181, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_timeraction = new wxTextCtrl( m_timer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer51->Add( m_timeraction, wxGBPosition( 1, 1 ), wxGBSpan( 1, 3 ), wxALL|wxEXPAND, 5 );
	
	m_sgroup1 = new wxStaticText( m_timer, wxID_ANY, _("Group:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_sgroup1->Wrap( -1 );
	gbSizer51->Add( m_sgroup1, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_tigroup = new wxComboBox( m_timer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL); 
	gbSizer51->Add( m_tigroup, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_tifilter = new wxCheckBox( m_timer, wxID_ANY, _("filter"), wxDefaultPosition, wxDefaultSize, 0 );
	m_tifilter->SetValue(true); 
	gbSizer51->Add( m_tifilter, wxGBPosition( 2, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_tigroupoff = new wxToggleButton( m_timer, wxID_ANY, _("Group off"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer51->Add( m_tigroupoff, wxGBPosition( 2, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	m_ton = new wxCheckBox( m_timer, wxID_ANY, _("Timer active"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer51->Add( m_ton, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_tidelgroup = new wxButton( m_timer, wxID_ANY, _("Delete group"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer51->Add( m_tidelgroup, wxGBPosition( 3, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	m_staticText23 = new wxStaticText( m_timer, wxID_ANY, _("Repeat:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	gbSizer51->Add( m_staticText23, wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL|wxLEFT, 5 );
	
	m_rep = new wxSpinCtrl( m_timer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS|wxSP_WRAP, -1, 10000, 1 );
	gbSizer51->Add( m_rep, wxGBPosition( 4, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_intervall = new wxTextCtrl( m_timer, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer51->Add( m_intervall, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	gbSizer51->AddGrowableCol( 1 );
	
	bSizer1011->Add( gbSizer51, 1, wxALL|wxEXPAND, 5 );
	
	wxGridBagSizer* gbSizer61;
	gbSizer61 = new wxGridBagSizer( 0, 0 );
	gbSizer61->SetFlexibleDirection( wxBOTH );
	gbSizer61->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_addtimer = new wxButton( m_timer, wxID_ANY, _("Add timer"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer61->Add( m_addtimer, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_edittimer = new wxButton( m_timer, wxID_ANY, _("Edit timer"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer61->Add( m_edittimer, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_deltimer = new wxButton( m_timer, wxID_ANY, _("Delete timer"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer61->Add( m_deltimer, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_tstart = new wxButton( m_timer, wxID_ANY, _("Start timer"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer61->Add( m_tstart, wxGBPosition( 0, 3 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	
	bSizer1011->Add( gbSizer61, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	
	m_timer->SetSizer( bSizer1011 );
	m_timer->Layout();
	bSizer1011->Fit( m_timer );
	m_notebook->AddPage( m_timer, _("Timers"), false );
	m_var = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( m_var, wxID_ANY, _("Defined variables") ), wxVERTICAL );
	
	m_listvar = new wxListCtrl( m_var, ID_LALIAS, wxDefaultPosition, wxSize( 500,-1 ), wxLC_REPORT|wxSUNKEN_BORDER );
	sbSizer4->Add( m_listvar, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer31->Add( sbSizer4, 2, wxALL|wxEXPAND, 5 );
	
	wxGridBagSizer* gbSizer211;
	gbSizer211 = new wxGridBagSizer( 0, 0 );
	gbSizer211->SetFlexibleDirection( wxBOTH );
	gbSizer211->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );
	
	m_staticText611 = new wxStaticText( m_var, wxID_ANY, _("Variable:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText611->Wrap( -1 );
	gbSizer211->Add( m_staticText611, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_defvar = new wxTextCtrl( m_var, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer211->Add( m_defvar, wxGBPosition( 0, 1 ), wxGBSpan( 1, 3 ), wxALL|wxEXPAND, 5 );
	
	m_staticText71 = new wxStaticText( m_var, wxID_ANY, _("Value:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText71->Wrap( -1 );
	gbSizer211->Add( m_staticText71, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_varvalue = new wxTextCtrl( m_var, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	gbSizer211->Add( m_varvalue, wxGBPosition( 1, 1 ), wxGBSpan( 2, 3 ), wxALL|wxEXPAND, 5 );
	
	m_staticText1011 = new wxStaticText( m_var, wxID_ANY, _("Group:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1011->Wrap( -1 );
	gbSizer211->Add( m_staticText1011, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_vargroup = new wxComboBox( m_var, wxID_ANY, _("default"), wxDefaultPosition, wxDefaultSize, 0, NULL); 
	gbSizer211->Add( m_vargroup, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	m_vfilter = new wxCheckBox( m_var, wxID_ANY, _("filter"), wxDefaultPosition, wxDefaultSize, 0 );
	m_vfilter->SetValue(true); 
	gbSizer211->Add( m_vfilter, wxGBPosition( 3, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_vgroupoff = new wxToggleButton( m_var, wxID_ANY, _("Group off"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer211->Add( m_vgroupoff, wxGBPosition( 3, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_von = new wxCheckBox( m_var, wxID_ANY, _("Variable active"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer211->Add( m_von, wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_vdelgroup = new wxButton( m_var, wxID_ANY, _("Delete group"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer211->Add( m_vdelgroup, wxGBPosition( 4, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	gbSizer211->AddGrowableCol( 1 );
	gbSizer211->AddGrowableRow( 1 );
	
	bSizer31->Add( gbSizer211, 1, wxALL|wxEXPAND, 5 );
	
	wxGridSizer* gSizer21;
	gSizer21 = new wxGridSizer( 1, 3, 0, 0 );
	
	m_addvar = new wxButton( m_var, ID_ADDALIAS, _("Add variable"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer21->Add( m_addvar, 0, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );
	
	m_editvar = new wxButton( m_var, ID_EDITALIAS, _("Edit variable"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer21->Add( m_editvar, 0, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );
	
	m_delvar = new wxButton( m_var, ID_DELALIAS, _("Delete variable"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer21->Add( m_delvar, 0, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );
	
	
	bSizer31->Add( gSizer21, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	
	m_var->SetSizer( bSizer31 );
	m_var->Layout();
	bSizer31->Fit( m_var );
	m_notebook->AddPage( m_var, _("Variables"), true );
	
	bSizer1->Add( m_notebook, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	
	bSizer13->Add( m_sdbSizer1, 1, wxALIGN_BOTTOM|wxALL, 5 );
	
	
	bSizer1->Add( bSizer13, 0, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( ObjDlg::OnInitObjects ) );
	m_notebook->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( ObjDlg::OnPageChanged ), NULL, this );
	m_tree->Connect( wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT, wxTreeEventHandler( ObjDlg::OnActionBeginLabelEdit ), NULL, this );
	m_tree->Connect( wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler( ObjDlg::OnActionEndLabelEdit ), NULL, this );
	m_tree->Connect( wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler( ObjDlg::OnTreeItemMenu ), NULL, this );
	m_tree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( ObjDlg::OnTreeSelChanged ), NULL, this );
	m_patternedit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnPatternEdit ), NULL, this );
	m_sceditor->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnSceditor ), NULL, this );
	m_onoff->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnClassToggle ), NULL, this );
	m_delclass->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnDelClass ), NULL, this );
	m_oncolor->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjDlg::OnColourCheck ), NULL, this );
	m_tron->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjDlg::OnTriggerOn ), NULL, this );
	m_rextest->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnRegExpTest ), NULL, this );
	m_sendscript->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjDlg::OnSendToScript ), NULL, this );
	m_btadd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnActionAdd ), NULL, this );
	m_btedit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnActionEdit ), NULL, this );
	m_btdel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnActionDelete ), NULL, this );
	m_listalias->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( ObjDlg::OnItemSelected ), NULL, this );
	m_groupcombo->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ObjDlg::OnGroupChanged ), NULL, this );
	m_groupon->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnGroupOff ), NULL, this );
	m_alon->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjDlg::OnAliasOn ), NULL, this );
	m_delgroup->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnGroupDelete ), NULL, this );
	m_addalias->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnAliasAdd ), NULL, this );
	m_editalias->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnAliasEdit ), NULL, this );
	m_delalias->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnAliasDelete ), NULL, this );
	m_treeCtrl3->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( ObjDlg::OnButtonSelChanged ), NULL, this );
	m_addbutton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnButtonAdd ), NULL, this );
	m_editbutton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnButtonEdit ), NULL, this );
	m_delbutton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnButtonDelete ), NULL, this );
	m_gaugew->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( ObjDlg::OnGaugeTreeSelChanged ), NULL, this );
	m_addgauge->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnAddGauge ), NULL, this );
	m_editgauge->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnEditGauge ), NULL, this );
	m_delgauge->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnDelGauge ), NULL, this );
	m_listhkey->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( ObjDlg::OnHkSelected ), NULL, this );
	m_groupdel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnHkGroupDelete ), NULL, this );
	m_hkeyon->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjDlg::OnHkOn ), NULL, this );
	m_hkcombo->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ObjDlg::OnHkGroupChanged ), NULL, this );
	m_hkgroupoff->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnHkGroupToggle ), NULL, this );
	m_addkey->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnHotkeyAdd ), NULL, this );
	m_editkey->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnHotkeyEdit ), NULL, this );
	m_delkey->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnHotkeyDelete ), NULL, this );
	m_listlist->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( ObjDlg::OnListSelected ), NULL, this );
	m_additem->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnAddItem ), NULL, this );
	m_ligroup->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ObjDlg::OnLGroupChanged ), NULL, this );
	m_ligroupoff->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnListGroupoff ), NULL, this );
	m_lion->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjDlg::OnListOn ), NULL, this );
	m_lidelgroup->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnDeleteListGroup ), NULL, this );
	m_addlist->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnListAdd ), NULL, this );
	m_editlist->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnListEdit ), NULL, this );
	m_dellist->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnListDelete ), NULL, this );
	m_timerlist->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( ObjDlg::OnTimerSelected ), NULL, this );
	m_tigroup->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ObjDlg::OnTGroupChanged ), NULL, this );
	m_tigroupoff->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnTimerGroupOff ), NULL, this );
	m_ton->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjDlg::OnTimerOn ), NULL, this );
	m_tidelgroup->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnDeleteTimerGroup ), NULL, this );
	m_addtimer->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnTimerAdd ), NULL, this );
	m_edittimer->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnTimerEdit ), NULL, this );
	m_deltimer->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnTimerDelete ), NULL, this );
	m_tstart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnTimerStart ), NULL, this );
	m_listvar->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( ObjDlg::OnVarSelected ), NULL, this );
	m_vargroup->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ObjDlg::OnVGroupChanged ), NULL, this );
	m_vgroupoff->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnVGroupOff ), NULL, this );
	m_von->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjDlg::OnVarOn ), NULL, this );
	m_vdelgroup->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnVGroupDelete ), NULL, this );
	m_addvar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnVarAdd ), NULL, this );
	m_editvar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnVarEdit ), NULL, this );
	m_delvar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnVarDelete ), NULL, this );
}

ObjDlg::~ObjDlg()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( ObjDlg::OnInitObjects ) );
	m_notebook->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( ObjDlg::OnPageChanged ), NULL, this );
	m_tree->Disconnect( wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT, wxTreeEventHandler( ObjDlg::OnActionBeginLabelEdit ), NULL, this );
	m_tree->Disconnect( wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler( ObjDlg::OnActionEndLabelEdit ), NULL, this );
	m_tree->Disconnect( wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler( ObjDlg::OnTreeItemMenu ), NULL, this );
	m_tree->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( ObjDlg::OnTreeSelChanged ), NULL, this );
	m_patternedit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnPatternEdit ), NULL, this );
	m_sceditor->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnSceditor ), NULL, this );
	m_onoff->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnClassToggle ), NULL, this );
	m_delclass->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnDelClass ), NULL, this );
	m_oncolor->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjDlg::OnColourCheck ), NULL, this );
	m_tron->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjDlg::OnTriggerOn ), NULL, this );
	m_rextest->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnRegExpTest ), NULL, this );
	m_sendscript->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjDlg::OnSendToScript ), NULL, this );
	m_btadd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnActionAdd ), NULL, this );
	m_btedit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnActionEdit ), NULL, this );
	m_btdel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnActionDelete ), NULL, this );
	m_listalias->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( ObjDlg::OnItemSelected ), NULL, this );
	m_groupcombo->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ObjDlg::OnGroupChanged ), NULL, this );
	m_groupon->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnGroupOff ), NULL, this );
	m_alon->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjDlg::OnAliasOn ), NULL, this );
	m_delgroup->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnGroupDelete ), NULL, this );
	m_addalias->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnAliasAdd ), NULL, this );
	m_editalias->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnAliasEdit ), NULL, this );
	m_delalias->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnAliasDelete ), NULL, this );
	m_treeCtrl3->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( ObjDlg::OnButtonSelChanged ), NULL, this );
	m_addbutton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnButtonAdd ), NULL, this );
	m_editbutton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnButtonEdit ), NULL, this );
	m_delbutton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnButtonDelete ), NULL, this );
	m_gaugew->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( ObjDlg::OnGaugeTreeSelChanged ), NULL, this );
	m_addgauge->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnAddGauge ), NULL, this );
	m_editgauge->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnEditGauge ), NULL, this );
	m_delgauge->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnDelGauge ), NULL, this );
	m_listhkey->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( ObjDlg::OnHkSelected ), NULL, this );
	m_groupdel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnHkGroupDelete ), NULL, this );
	m_hkeyon->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjDlg::OnHkOn ), NULL, this );
	m_hkcombo->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ObjDlg::OnHkGroupChanged ), NULL, this );
	m_hkgroupoff->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnHkGroupToggle ), NULL, this );
	m_addkey->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnHotkeyAdd ), NULL, this );
	m_editkey->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnHotkeyEdit ), NULL, this );
	m_delkey->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnHotkeyDelete ), NULL, this );
	m_listlist->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( ObjDlg::OnListSelected ), NULL, this );
	m_additem->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnAddItem ), NULL, this );
	m_ligroup->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ObjDlg::OnLGroupChanged ), NULL, this );
	m_ligroupoff->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnListGroupoff ), NULL, this );
	m_lion->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjDlg::OnListOn ), NULL, this );
	m_lidelgroup->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnDeleteListGroup ), NULL, this );
	m_addlist->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnListAdd ), NULL, this );
	m_editlist->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnListEdit ), NULL, this );
	m_dellist->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnListDelete ), NULL, this );
	m_timerlist->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( ObjDlg::OnTimerSelected ), NULL, this );
	m_tigroup->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ObjDlg::OnTGroupChanged ), NULL, this );
	m_tigroupoff->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnTimerGroupOff ), NULL, this );
	m_ton->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjDlg::OnTimerOn ), NULL, this );
	m_tidelgroup->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnDeleteTimerGroup ), NULL, this );
	m_addtimer->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnTimerAdd ), NULL, this );
	m_edittimer->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnTimerEdit ), NULL, this );
	m_deltimer->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnTimerDelete ), NULL, this );
	m_tstart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnTimerStart ), NULL, this );
	m_listvar->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( ObjDlg::OnVarSelected ), NULL, this );
	m_vargroup->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ObjDlg::OnVGroupChanged ), NULL, this );
	m_vgroupoff->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnVGroupOff ), NULL, this );
	m_von->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjDlg::OnVarOn ), NULL, this );
	m_vdelgroup->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnVGroupDelete ), NULL, this );
	m_addvar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnVarAdd ), NULL, this );
	m_editvar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnVarEdit ), NULL, this );
	m_delvar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjDlg::OnVarDelete ), NULL, this );
	
}
