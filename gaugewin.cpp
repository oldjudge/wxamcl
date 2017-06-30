/*! \file gaugewin.cpp
	\brief implements the GaugeWindow class.
	
	This represents a complete Window, which ouputs gauges.
*/
#include "main.h"

BEGIN_EVENT_TABLE(GaugeWindow, wxWindow)
    EVT_ERASE_BACKGROUND(GaugeWindow::OnEraseBackground)
	EVT_PAINT(GaugeWindow::OnPaint)
	EVT_SIZE(GaugeWindow::OnSize)
	EVT_CONTEXT_MENU(GaugeWindow::OnContextMenu)
	EVT_MENU(ID_OUTFONTGAUGE, GaugeWindow::OnOutputFont)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS(GaugeWindow, wxWindow)

GaugeWindow::GaugeWindow()
{
	GaugeWindow(wxGetApp().GetFrame());
}
/*! \brief standard constructor
	\param wxFrame parent window
*/
GaugeWindow::GaugeWindow(wxFrame *parent):wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL| wxBORDER_NONE)
{
	m_parent = (MudMainFrame*) parent;
	SetName("amcgaugewin");
	SetLabel("amcgaugewin");
	SetScrollbar(wxVERTICAL, 0, 0, 0);
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	m_font = new wxFont(wxFontInfo(11).FaceName("CourierNew").Family(wxFONTFAMILY_MODERN));
	m_background = m_parent->m_child->GetAnsiColor(0);

}
/*! \brief constructor
	\param wxFrame parent
	\param wxString name of window
*/
GaugeWindow::GaugeWindow(wxFrame *parent, wxString name):wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL| wxBORDER_NONE)
{
	m_parent = (MudMainFrame*) parent;
	SetName(name);
	SetLabel(name);
	//SetBackgroundStyle(wxBG_STYLE_SYSTEM);
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	SetScrollbar(wxVERTICAL, 0, 0, 0);
	#if !defined __WXMSW__
		m_font = new wxFont(11, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Fixed");
	#else
		m_font = new wxFont(wxFontInfo(11).FaceName("Courier New").Family(wxFONTFAMILY_MODERN));
	#endif
	m_background = m_parent->m_child->GetAnsiColor(0);
}

GaugeWindow::~GaugeWindow()
{
	delete m_font;
	m_gauges.clear();
}

void GaugeWindow::OnEraseBackground(wxEraseEvent& event)
{
	SetBackgroundColour(m_background);
	ClearBackground();
}

void GaugeWindow::OnPaint(wxPaintEvent& event)
{
	//wxPaintDC dc(this);
	wxSize ss=GetClientSize();
	wxBitmap bm(ss.x, ss.y);
	wxBufferedPaintDC dc(this, bm);
	dc.SetBackgroundMode(wxSOLID);
	wxBrush b(m_background);
	dc.SetBackground(b);
	dc.Clear();
	g_it it;
	for (it=m_gauges.begin();it!=m_gauges.end();it++)
		it->DrawGauge(&dc);
}


void GaugeWindow::OnSize(wxSizeEvent& event)
{
	Refresh();
	Update();
}

void GaugeWindow::OnContextMenu(wxContextMenuEvent& event)
{
	wxMenu *contextMenu = new wxMenu;
	contextMenu->Append(ID_OUTFONTGAUGE, _("Font"), _("Set the output font"));
	wxPoint p = event.GetPosition();
	p = ScreenToClient(p);
	PopupMenu(contextMenu, p.x, p.y);
	delete contextMenu;
}

void GaugeWindow::OnOutputFont(wxCommandEvent& event)
{
	wxFont f = wxGetFontFromUser(m_parent, *m_font, _("Set font for this window"));
	if (f.IsOk())
	{
		SetFont(&f);
		//SetUFont(&f);
		Refresh();
		Update();
		//if (this==m_parent->m_child)
		//	m_parent->SaveGlobalOptions();
	}
}

int GaugeWindow::GetGaugeIndexByName(wxString s)
{
g_it it;
int i;

	if (m_gauges.empty())
		return -1;
	for (it = m_gauges.begin(), i=0; it!=m_gauges.end(); it++, i++)
	{
		if (!s.compare(it->GetName()))
			return i;
	}
	return -1;
}

void GaugeWindow::SetBackgroundCol(wxColour c)
{
	SetBackgroundColour(c);
	m_background=c;
	Refresh();
	Update();
}

//amcGauge
amcGauge::amcGauge()
{
	m_parent = wxGetApp().GetFrame(); //(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	m_gwin = NULL;
	m_name = wxEmptyString;
	m_label = wxEmptyString;
	m_var1 = wxEmptyString;
	m_var2 = wxEmptyString;
	m_idx1 = m_idx2 = 0;
	m_x = m_y = 10;
	m_cx = 100;
	m_cy = 40;
	m_fcol.Set("GREEN");
	m_bcol.Set("BLACK");
	m_alarm.Set("RED");
	m_text.Set("WHITE");
	m_vertical = true;
	m_on = false;
	m_usealarm = true;
	m_alarmperc = 30;
	m_perc = 1.0;
	m_style = GAUGE_STANDARD;
	m_textpos = GAUGE_TEXT_GAUGE;
	m_showvalue = false;
}

amcGauge::~amcGauge()
{
	
}

amcGauge::amcGauge(wxString winname, wxString name, wxString var1, wxString var2, wxColour fc, wxColour bc, int x, int y, int cx, int cy, bool vert)
{
	m_parent = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	m_gwin = (GaugeWindow*)GaugeWindow::FindWindowByName(winname, m_parent);
	if (!m_gwin)
	{
		m_gwin = new GaugeWindow(m_parent, winname);
		m_parent->GetGaugePanes()->push_back(winname);
		vector<wxString> s;
		m_parent->GetGauges()->push_back(s);
		m_parent->m_mgr.AddPane(m_gwin, wxAuiPaneInfo().Name(winname).Caption(winname).CaptionVisible(true).Floatable(true).FloatingSize(400,200).BestSize(400,200).Dockable(true).Dock().Top().Layer(1).Show());
		m_parent->m_mgr.Update();
	}
	m_name = name;
	m_label = name;
	m_var1 = var1;
	m_var2 = var2;
	m_idx1 = m_parent->GetVarIndexByLabel(m_var1);
	m_idx2 = m_parent->GetVarIndexByLabel(m_var2);
	double val1, val2;
	if (!m_parent->GetVars()->empty())
	{
		m_parent->GetVars()->at(m_idx1).GetValue().ToDouble(&val1);
		m_parent->GetVars()->at(m_idx2).GetValue().ToDouble(&val2);
		m_perc = (float)(val1/val2);
	}
	m_fcol = fc;
	m_bcol = bc;
	m_alarm.Set("RED");
	m_text.Set("WHITE");
	m_x = x;
	m_y = y;
	m_cx = cx;
	m_cy = cy;
	m_on = true;
	m_vertical = vert;
	m_usealarm = true;
	m_alarmperc = 30;
	m_style = GAUGE_STANDARD;
	m_textpos = GAUGE_TEXT_GAUGE;
	m_showvalue = false;
}

bool amcGauge::SetWindow(wxString win)
{
	m_parent = wxGetApp().GetFrame();
	m_gwin = (GaugeWindow*)GaugeWindow::FindWindowByName(win, m_parent);
	if (m_gwin)
		return true;
	else return false;
}

void amcGauge::SetVarIndices()
{
	m_idx1 = m_parent->GetVarIndexByLabel(m_var1);
	m_idx2 = m_parent->GetVarIndexByLabel(m_var2);
}

void amcGauge::DrawGauge(wxBufferedPaintDC *dc)
{
	//wxClientDC dc(m_gwin);
	//wxBufferedDC dc(cdc);
	wxBrush fore(m_fcol);
	wxBrush back(m_bcol);
	wxBrush alarm(m_alarm);
	double val1, val2;
	if (!m_parent->GetVars()->empty())
	{
		m_parent->GetVars()->at(m_idx1).GetValue().ToDouble(&val1);
		m_parent->GetVars()->at(m_idx2).GetValue().ToDouble(&val2);
		if (val2)
			m_perc = (float)(val1/val2);
		else m_perc = 0;
	}
	dc->SetBrush(back);
	dc->SetPen(*wxWHITE_PEN);
	if (m_vertical)
	{
		switch (m_style)
		{
			case GAUGE_STANDARD:
			case GAUGE_LINES:
				dc->DrawRectangle(m_x, m_y, m_cx, m_cy);
				break;
			case GAUGE_ROUNDED:
			case GAUGE_RLINES:
				dc->DrawRoundedRectangle(m_x, m_y, m_cx, m_cy, -0.5);
				break;
			case GAUGE_3D:
				dc->DrawRectangle(m_x, m_y, m_cx, m_cy);
				break;
			default:
				dc->DrawRectangle(m_x, m_y, m_cx, m_cy);
				break;
		}
		//dc.DrawRectangle(m_x, m_y, m_cy, m_cx);
		if (!m_usealarm)
			dc->SetBrush(fore);
		else if (m_usealarm && m_perc<(float)m_alarmperc/100) 
			dc->SetBrush(alarm);
		else dc->SetBrush(fore);
		switch (m_style)
		{
			case GAUGE_STANDARD:
				dc->DrawRectangle(m_x, m_y+m_cy, m_cx, -(m_cy*m_perc));
				break;
			case GAUGE_LINES:
				dc->DrawRectangle(m_x, m_y+m_cy, m_cx, -(m_cy*m_perc));
				for (int i=1;i<10;i++)
				{
					dc->DrawLine(m_x, m_y+i*(m_cy/10), m_cx+m_x, m_y+i*(m_cy/10));
				}
				break;
			case GAUGE_ROUNDED:
				//dc.DrawRoundedRectangle(m_x, m_y, m_cy, -(m_cx*m_perc), -0.3);
				dc->DrawRoundedRectangle(m_x, m_y+(m_cy-m_cy*m_perc), m_cx, m_cy*m_perc, -0.5);
				break;
			case GAUGE_RLINES:
				dc->DrawRoundedRectangle(m_x, m_y+(m_cy-m_cy*m_perc), m_cx, m_cy*m_perc, -0.5);
				for (int i=1;i<10;i++)
				{
					dc->DrawLine(m_x, m_y+i*(m_cy/10), m_cx+m_x, m_y+i*(m_cy/10));
				}
				break;
			case GAUGE_3D:
			{
				
				wxColour c;
				wxColour cd;
				if (!m_usealarm)
				{
					c= m_fcol;
					cd = c.ChangeLightness(30);
					dc->SetBrush(wxBrush(cd));
					dc->SetPen(wxPen(cd));
				}
				else if (m_usealarm && m_perc < (float)m_alarmperc / 100)
				{
					c = m_alarm;
					wxColour cd = c.ChangeLightness(30);
					dc->SetBrush(wxBrush(cd));
					dc->SetPen(wxPen(cd));
				}
				else
				{
					c = m_fcol;
					cd = c.ChangeLightness(30);
					dc->SetBrush(wxBrush(cd));
					dc->SetPen(wxPen(cd));
				}
				wxRect rc(m_x, m_y + m_cy, m_cx/2, -(m_cy*m_perc));
				dc->GradientFillLinear(rc, cd, c);
				wxRect rc1(m_x + m_cx / 2, m_y+m_cy, m_cx / 2, -(m_cy*m_perc));
				dc->GradientFillLinear(rc1, c, cd);
				
				
				//dc->DrawRectangle(m_x+5, m_y + m_cy, m_cx-10, -(m_cy*m_perc));
				
				break;
			}
			default:
				dc->DrawRectangle(m_x, m_y, m_cx, -(m_cy*m_perc));
				break;
		}
		//dc.DrawRectangle(m_x, m_y+m_cx, m_cy, -(m_cx*m_perc));
		dc->SetTextForeground(m_text);
		dc->SetTextBackground(m_parent->m_child->GetAnsiColor(0));
		wxFont *font = m_gwin->GetFont();
		dc->SetFont(*font);
		switch(m_textpos)
		{
			case GAUGE_TEXT_BELOW:
				dc->DrawText(m_label, m_x, m_y+m_cy+3);
				if (m_showvalue)
				{
					wxString val;
					val<<m_parent->GetVars()->at(m_idx1).GetValue();
					dc->DrawText(val, m_x, m_y+m_cy+dc->GetCharHeight()+3);
				}
				break;
			case GAUGE_TEXT_GAUGE:
				dc->SetBackgroundMode(wxTRANSPARENT);
				if (m_showvalue)
				{
					wxString val;
					val << m_parent->GetVars()->at(m_idx1).GetValue();
					dc->DrawRotatedText(val, m_x + 2, m_y +(m_cy/2), 90);
				}
				else
					dc->DrawRotatedText(m_label, m_x+2, m_y+(m_cy/2), 90);
				break;
			case GAUGE_TEXT_ABOVE:
				dc->DrawText(m_label, m_x, m_y-dc->GetCharHeight()-2);
				break;
			case GAUGE_TEXT_NONE:
				break;
			default:
				dc->DrawText(m_label, m_x+5, m_y+2);
				break;
		}
		//dc->DrawText(m_label, m_x, m_y+m_cy);
		//dc.DrawRotatedText(m_label, m_x, m_y+m_cx, 90);
	}
	else
	{
		switch (m_style)
		{
			case GAUGE_STANDARD:
			case GAUGE_LINES:
				dc->DrawRectangle(m_x, m_y, m_cy, m_cx);
				break;
			case GAUGE_ROUNDED:
			case GAUGE_RLINES:
				dc->DrawRoundedRectangle(m_x, m_y, m_cy, m_cx, -0.5);
				break;
			case GAUGE_3D:
				dc->DrawRectangle(m_x, m_y, m_cy, m_cx);
				break;
			default:
				dc->DrawRectangle(m_x, m_y, m_cy, m_cx);
				break;
		}
		//dc.DrawRectangle(m_x, m_y, m_cx, m_cy);
		if (!m_usealarm)
			dc->SetBrush(fore);
		else if (m_usealarm && m_perc<(float)m_alarmperc/100) 
			dc->SetBrush(alarm);
		else dc->SetBrush(fore);
		switch (m_style)
		{
			case GAUGE_STANDARD:
				dc->DrawRectangle(m_x, m_y, m_cy*m_perc, m_cx);
				break;
			case GAUGE_LINES:
				dc->DrawRectangle(m_x, m_y, m_cy*m_perc, m_cx);
				for (int i=0;i<10;i++)
				{
					dc->DrawLine(m_x+i*(m_cy/10), m_y, m_x+i*(m_cy/10), m_y+m_cx);
				}
				break;
			case GAUGE_ROUNDED:
				dc->DrawRoundedRectangle(m_x, m_y, m_cy*m_perc, m_cx, -0.5);
				break;
			case GAUGE_RLINES:
				dc->DrawRoundedRectangle(m_x, m_y, m_cy*m_perc, m_cx, -0.5);
				for (int i=1;i<10;i++)
				{
					dc->DrawLine(m_x+i*(m_cy/10), m_y, m_x+i*(m_cy/10), m_y+m_cx);
				}
				break;
			case GAUGE_3D:
			{
				wxColour c;
				wxColour cd;
				if (!m_usealarm)
				{
					c = m_fcol;
					cd = c.ChangeLightness(30);
					dc->SetBrush(wxBrush(cd));
					dc->SetPen(wxPen(cd));
				}
				else if (m_usealarm && m_perc < (float)m_alarmperc / 100)
				{
					c = m_alarm;
					wxColour cd = c.ChangeLightness(30);
					dc->SetBrush(wxBrush(cd));
					dc->SetPen(wxPen(cd));
				}
				else
				{
					c = m_fcol;
					cd = c.ChangeLightness(30);
					dc->SetBrush(wxBrush(cd));
					dc->SetPen(wxPen(cd));
				}
				wxRect rc(m_x, m_y, m_cy*m_perc, m_cx/2);
				dc->GradientFillLinear(rc, c, cd, wxTOP);
				wxRect rc1(m_x,m_y+m_cx/2, m_cy*m_perc, m_cx/2);
				dc->GradientFillLinear(rc1, cd, c, wxTOP);
				break;
			}
			default:
				dc->DrawRectangle(m_x, m_y, m_cy*m_perc, m_cx);
				break;
		}
		//dc.SetPen(*wxTRANSPARENT_PEN);
		
		dc->SetTextForeground(m_text);
		dc->SetTextBackground(m_parent->m_child->GetAnsiColor(0));
		wxFont *font = m_gwin->GetFont();
		dc->SetFont(*font);
		//dc.DrawText(m_label, m_x, m_y+m_cy);
		switch(m_textpos)
		{
			case GAUGE_TEXT_BELOW:
				dc->DrawText(m_label, m_x, m_y+m_cx);
				if (m_showvalue)
				{
					wxString val;
					val << m_parent->GetVars()->at(m_idx1).GetValue();
					dc->DrawText(val, m_x, m_y + m_cx + dc->GetCharHeight() + 3);
				}
				break;
			case GAUGE_TEXT_GAUGE:
				dc->SetBackgroundMode(wxTRANSPARENT);
				
				if (m_showvalue)
				{
					wxString val;
					val << m_parent->GetVars()->at(m_idx1).GetValue();
					dc->DrawText(val, m_x+5, m_y + 2);
				}
				else
					dc->DrawText(m_label, m_x + 5, m_y + 2);
				break;
			case GAUGE_TEXT_ABOVE:
				dc->DrawText(m_label, m_x, m_y-m_cx);
				break;
			case GAUGE_TEXT_NONE:
				break;
			default:
				dc->DrawText(m_label, m_x+5, m_y+2);
				break;
		}
	}
}
