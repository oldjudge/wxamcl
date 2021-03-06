/*! \file amcWindow.cpp
	\brief implements the amcWindow class.
	
	This represents a complete Window, which ouputs whatever.
*/
#include "main.h"

BEGIN_EVENT_TABLE(amcWindow, wxWindow)
    EVT_ERASE_BACKGROUND(amcWindow::OnEraseBackground)
	EVT_PAINT(amcWindow::OnPaint)
	EVT_SIZE(amcWindow::OnSize)
	EVT_LEFT_DOWN(amcWindow::OnLeftDown)
	EVT_RIGHT_DOWN(amcWindow::OnRightDown)
	EVT_MOTION(amcWindow::OnMouseMove)
	EVT_MOUSEWHEEL(amcWindow::OnMouseWheel)
	EVT_ENTER_WINDOW(amcWindow::OnEnterWindow)
	EVT_LEAVE_WINDOW(amcWindow::OnLeaveWindow)
	EVT_CONTEXT_MENU(amcWindow::OnContextMenu)
	//EVT_MENU(ID_OUTFONTGAUGE, amcWindow::OnOutputFont)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS(amcWindow, wxWindow)

amcWindow::amcWindow()
{
	amcWindow(wxGetApp().GetFrame());
}
/*! \brief standard constructor
	\param wxFrame parent window
*/
amcWindow::amcWindow(wxFrame *parent):wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL| wxBORDER_NONE)
{
	m_parent = (MudMainFrame*) parent;
	SetName("amcwindow");
	SetLabel("amcwindow");
	SetScrollbar(wxVERTICAL, 0, 0, 0);
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	#if !defined __WXMSW__
		m_font = new wxFont(11, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier New");
	#else
		m_font = new wxFont(wxFontInfo(10).FaceName("Courier New").Family(wxFONTFAMILY_MODERN));
	#endif
	m_background = m_parent->m_child->GetAnsiColor(0);
	m_mouseevents=false;
	m_mouseleft = "OnMouseLeft";
	m_mouseright = "OnMouseRight";
	m_mousewheel = "OnMouseWheel";
	m_mousemove = "OnMouseMove";
	m_onsize = "OnSize";
	m_evfile = "amcevents.lua";
	m_wheelrot=0;
	
	m_tt = NULL;
}
/*! \brief constructor
	\param wxFrame parent
	\param wxString name of window
*/
amcWindow::amcWindow(wxFrame *parent, wxString name):wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL| wxBORDER_NONE)
{
	m_parent = (MudMainFrame*) parent;
	SetName(name);
	SetLabel(name);
	m_mouseevents=false;
	m_mouseleft = "OnMouseLeft";
	m_mouseright = "OnMouseRight";
	m_mousewheel = "OnMouseWheel";
	m_mousemove = "OnMouseMove";
	m_onsize = "OnSize";
	m_evfile = "amcevents.lua";
	m_wheelrot = 0;
	
	m_bitmap.Create(1920, 1280);
	m_dc = new wxMemoryDC(m_bitmap);
	#if defined __WX_MSW__
		wxToolTip::SetMaxWidth(-1);
		m_tt->SetMaxWidth(-1);
	#endif
	m_tt = new wxToolTip("");
	//m_tt->SetDelay(5);
	this->SetToolTip(m_tt);
	m_tt->SetAutoPop(3000);
	//this->GetToolTip()->SetMaxWidth(-1);
	//SetBackgroundStyle(wxBG_STYLE_S);
	SetScrollbar(wxVERTICAL, 0, 0, 0);
	#if !defined __WXMSW__
		m_font = new wxFont(wxFontInfo(10).Family(wxFONTFAMILY_MODERN).FaceName("Fixed"));
	#else
		m_font = new wxFont(wxFontInfo(10).Family(wxFONTFAMILY_MODERN).FaceName("Courier New"));
	#endif
	m_background = m_parent->m_child->GetAnsiColor(0);
	m_dc->SetBackgroundMode(wxTRANSPARENT);
	m_dc->SetBackground(*wxBLACK_BRUSH);
	m_dc->SetFont(*m_font);
	m_dc->Clear();
	Refresh();
}

amcWindow::~amcWindow()
{
	delete m_font;
	delete m_dc;
}

void amcWindow::OnEraseBackground(wxEraseEvent& event)
{
	//SetBackgroundColour(m_background);
	//ClearBackground();
}

void amcWindow::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	dc.Blit(0,0,m_bitmap.GetWidth(), m_bitmap.GetHeight(), m_dc, 0, 0);
	event.Skip();
}


void amcWindow::OnSize(wxSizeEvent& event)
{
	
	/*wxString s = wxString::Format("%cfunc(\"%s\", \"%s()\")", m_parent->GetGlobalOptions()->GetCommand(),
		m_evfile, m_onsize);

	m_parent->m_input->ParseCommandLine(&s);
	Refresh();
	Update();*/
}

void amcWindow::OnRightDown(wxMouseEvent &event)
{
	if (m_mouseevents)
	{
		wxPoint p = event.GetPosition();
		wxString s = wxString::Format("%cfunc(\"%s\", \"%s(\'%d\',\'%d')\")", m_parent->GetGlobalOptions()->GetCommand(),
			m_evfile, m_mouseright, p.x, p.y);
		
		m_parent->m_input->ParseCommandLine(&s);
	}
	event.Skip();
}

void amcWindow::OnLeftDown(wxMouseEvent &event)
{
	if (m_mouseevents)
	{
		wxPoint p = event.GetPosition();
		wxString s = wxString::Format("%cfunc(\"%s\", \"%s(\'%d\',\'%d')\")", m_parent->GetGlobalOptions()->GetCommand(),
							m_evfile, m_mouseleft, p.x, p.y);
		//wxString s = wxString::Format("?%s('%d','%d')", m_mouseleft, p.x, p.y);
		m_parent->m_input->ParseCommandLine(&s);
	}
	event.Skip();
}

void amcWindow::OnMouseWheel(wxMouseEvent &event)
{
	//wxPoint p = event.GetPosition();
	m_wheelrot += event.GetWheelRotation();
	int line = m_wheelrot/event.GetWheelDelta();
	m_wheelrot -= line*event.GetWheelDelta();
	if (m_mouseevents)
	{
		wxString s = wxString::Format("%cfunc(\"%s\", \"%s(\'%d\')\")", m_parent->GetGlobalOptions()->GetCommand(),
							m_evfile, m_mousewheel, line);
		//wxString s = wxString::Format("?%s('%d','%d')", m_mouseleft, p.x, p.y);
		m_parent->m_input->ParseCommandLine(&s);
	}
	event.Skip();
}

void amcWindow::OnMouseMove(wxMouseEvent &event)
{
	wxPoint p = event.GetPosition();
	if (m_mouseevents)
	{
		wxString s = wxString::Format("%cfunc(\"%s\", \"%s(\'%d\',\'%d')\")", m_parent->GetGlobalOptions()->GetCommand(),
							m_evfile, m_mousemove, p.x, p.y);
		m_parent->m_input->ParseCommandLine(&s);
	}
	event.Skip();
}

void amcWindow::OnEnterWindow(wxMouseEvent &event)
{
	//m_parent->m_child->Msg("Entered");
	this->SetFocus();
}

void amcWindow::OnLeaveWindow(wxMouseEvent &event)
{
	//m_parent->m_child->Msg("Left");
	m_parent->m_input->SetFocus();
}

void amcWindow::OnContextMenu(wxContextMenuEvent &event)
{
    wxMenu *contextMenu = new wxMenu;
		contextMenu->Append(ID_OUTFONTAMCWIN, _("Font"), _("Set the output font"));
		contextMenu->AppendCheckItem(ID_STAMPS, _("Timestamps"), _("Show timestamps in this window"));
		contextMenu->Check(ID_STAMPS, m_parent->m_child->UseTimeStamps());
		
		contextMenu->AppendSeparator();
		contextMenu->Append(ID_MAKEACTION, _("Create action..."), _("Create an action using the linetext"));
		contextMenu->AppendSeparator();
		contextMenu->Append(wxID_COPY, _("Copy\tCtrl+C"), _("Copy selection to clipboard"));
		contextMenu->Append(ID_COPY, _("Copy with ansi"), _("Copy selection with ansicodes to clipboard"));
		
		wxPoint p = event.GetPosition();
		p = ScreenToClient(p);
		PopupMenu(contextMenu, p.x, p.y);
		delete contextMenu;
}

void amcWindow::SetBackground(wxColor c)
{
	SetBackgroundColour(c);
	m_background = c;
	m_dc->SetBackground(wxBrush(m_background));
	m_dc->Clear();
	Refresh();
	Update();
}