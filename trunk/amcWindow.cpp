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
	//EVT_CONTEXT_MENU(amcWindow::OnContextMenu)
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
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	#if !defined __WXMSW__
		m_font = new wxFont(11, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier New");
	#else
		m_font = new wxFont(11, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier New");
	#endif
	m_background = m_parent->m_child->GetAnsiColor(0);
	m_mouseevents=false;
	m_mouseleft = "OnMouseLeft";
	m_mouseright = "OnMouseRight";
	m_mousewheel = "OnMouseWheel";
	m_mousemove = "OnMouseMove";
	m_evfile = "event.lua";
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
	m_evfile = "events.lua";
	m_wheelrot = 0;
	
	m_bitmap.Create(1278, 1024);
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
	//SetBackgroundStyle(wxBG_STYLE_SYSTEM);
	SetScrollbar(wxVERTICAL, 0, 0, 0);
	#if !defined __WXMSW__
		m_font = new wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Fixed");
	#else
		m_font = new wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier New");
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
}

void amcWindow::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	dc.Blit(0,0,m_bitmap.GetWidth(), m_bitmap.GetHeight(), m_dc, 0, 0);
}


void amcWindow::OnSize(wxSizeEvent& event)
{
	Refresh();
	Update();
}

void amcWindow::OnRightDown(wxMouseEvent &event)
{
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
	wxPoint p = event.GetPosition();
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