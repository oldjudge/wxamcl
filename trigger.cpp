#include "main.h"

std::vector<wxString> Trigger::m_trclass;

Trigger::Trigger()
{
	m_parent = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	m_pattern = wxEmptyString;
	m_action = wxEmptyString;
	m_class = "default";
	/*int i = count(m_trclass.begin(), m_trclass.end(), m_class);
	if (!i)
		m_trclass.push_back(m_class);*/
	m_label = "default";
	m_priority = 50;
	//m_rexp = new RegExp();
	m_on = false;
	m_match = "";
	m_matchcount = 0;
	m_colmatch = -1;
	m_lines = m_curlines = 1;
	m_show = true;
	m_sendtoscript = false;
	m_gagline = false;
}

Trigger::Trigger(wxString pattern, wxString action, wxString label, wxString cl, wxUint32 prior, bool on, int col, int lines, bool show)
{
	m_parent = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	m_pattern = pattern;
	m_action = action;
	m_label = label;
	m_class = cl;
	m_priority = prior;
	//m_rexp = new RegExp();
	m_on = on;
	m_matchcount = 0;
	//GetThe RealIndex!!!
	int i = count(m_trclass.begin(), m_trclass.end(), m_class);
	if (!i)
		m_trclass.push_back(m_class);
	m_colmatch = col;
	m_lines = m_curlines = lines;
	m_show = show;
	m_sendtoscript = false;
	m_gagline = false;
}

void Trigger::SetClass(wxString s)
{
	m_class = s;
	int i = count(m_trclass.begin(), m_trclass.end(), m_class);
	if (!i)
		m_trclass.push_back(m_class);
}
Trigger::~Trigger()
{
}

int Trigger::MultiLine()
{
	return m_curlines;
}

bool Trigger::Match(wxString match)
{
	if (!m_on)
		return false;
	m_curlines = m_lines;
	m_match = match;
	m_rexp.SetPattern(ParsePattern());
	if (m_rexp.Match(m_match))
	{
		if (m_colmatch == -1)
		{
			m_matchcount++;
			return true;
		}
		else
		{
			int begin = m_rexp.GetMatchStart();
			class MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
			ale_it it = frame->m_child->GetLineStyle(frame->m_child->m_curline - 1)->begin();
			for (it; it != frame->m_child->GetLineStyle(frame->m_child->m_curline - 1)->end(); it++)
			{
				wxString m = it->GetConvText();
				if (!m.IsEmpty())
				{
					if (m_match.StartsWith(m))
					{
						begin = it->GetFColIndex();
						break;
					}
				}
			}

			//if (frame->m_child->GetLines()->at(frame->m_child->m_curline - 1).GetCharFColIndex(begin) == m_colmatch)
			if (begin == m_colmatch)
			{
				m_matchcount++;
				return true;
			}
			else return false;
		}
	}
	else return false;
}

wxString Trigger::ParsePattern()
{
	size_t idx, i;
	wxString var, pattern;

	pattern = m_pattern;
	do
	{
		//replace the vars $
		MudMainFrame *frame = wxGetApp().GetFrame();
		//class MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
		idx = pattern.find(frame->GetGlobalOptions()->GetVar());
		if (idx != string::npos)
		{
			i = idx + 1;
			while (i<pattern.length())
			{
				if (wxIsalnum(pattern.at(i)))			
					i++;
				else break;
			}
			//while (isalnum(pattern.at(i)))
			//	i++;
			var = pattern.substr(idx, i - idx);
			int x = frame->GetVarIndexByLabel(var.substr(1));
			if (x == -1) //error no var with the name there
				break;
			if (frame->m_vars.at(x).IsActive()) //only replace if var active
				pattern.Replace(var, frame->m_vars.at(x).GetValue());
		}
	}
	while (idx != string::npos);

	do
	{
		//replace the lists @
		class MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
		idx = pattern.find(frame->GetGlobalOptions()->GetListVar());
		if (idx != string::npos)
		{
			i = idx + 1;
			while (i<pattern.length())
			{
				if (wxIsalnum(pattern.at(i)))			
					i++;
				else break;
			}
			//while (isalnum(pattern.at(i)))
			//	i++;
			var = pattern.substr(idx, i - idx);
			int x = frame->GetListIndexByLabel(var.substr(1));
			if (x == -1) //error no list with the name there
				break;
			if (frame->m_lists.at(x).IsActive()) //only replace if list active
				pattern.Replace(var, frame->m_lists.at(x).GetValue());
		}
	}
	while (idx != string::npos);
	return pattern;
}

wxString Trigger::BuildAction()
{
	//return m_action;
	wxString s = m_action;
	size_t idx = 0, i = 0;
	long num = 0;
	wxString var;

	do
	{
		idx = s.find(m_parent->GetGlobalOptions()->GetIntVar());
		if (idx != string::npos)
		{
			i = idx + 1;
			while (i<s.length())
			{
				if (wxIsdigit(s.at(i)))			
					i++;
				else break;
			}
			//while (isdigit(s.at(i)))
			//	i++;
			var = s.substr(idx + 1, i - idx - 1);
			var.ToLong(&num);
			var = s.substr(idx, i - idx);
			s.Replace(var, m_rexp.GetMatch(num));
		}
	}
	while (idx != string::npos);
	return s;
}
//ColorComboBox
amcColorComboBox::amcColorComboBox(wxWindow *parent) : wxOwnerDrawnComboBox()
{
	m_parent = parent;
    m_cols[0] = _("Black (color 1)");
	m_cols[1] = _("Red (color 2)");
	m_cols[2] = _("Green (color 3)");
	m_cols[3] = _("Yellow (color 4)");
	m_cols[4] = _("Blue (color 5)");
	m_cols[5] = _("Magenta (color 6)");
	m_cols[6] = _("Cyan (color 7)");
	m_cols[7] = _("Grey (color 8)");
	m_cols[8] = _("Dark gray (color 9)");
	m_cols[9] = _("Bright red (color 10)");
	m_cols[10] = _("Bright green (color 11)");
	m_cols[11] = _("Bright yellow (color 12)");
	m_cols[12] = _("Bright blue (color 13)");
	m_cols[13] = _("Bright magenta (color 14)");
	m_cols[14] = _("Bright cyan (color 15)");
	m_cols[15] = _("Bright white (color 16)");
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 16, m_cols, wxTE_PROCESS_ENTER, wxDefaultValidator, wxT("amcColorComboBox"));
  
}

amcColorComboBox::~amcColorComboBox()
{

}

wxCoord amcColorComboBox::OnMeasureItem(size_t item) const
{
	//wxRect rc = GetRect();
	//return (wxCoord)(rc.GetHeight()/16);
	return 8;
}

wxCoord amcColorComboBox::OnMeasureItemWidth(size_t item) const
{
	//wxSize rc = GetClientSize();
	//return (wxCoord)rc.GetWidth();
	return -1;
}

void amcColorComboBox::OnDrawItem(wxDC& dc, const wxRect& rect, int item, int flags) const
{
	wxBrush br;
	class MudMainFrame *frame = wxGetApp().GetFrame(); //(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	br.SetColour(frame->m_child->GetColour(item));
	dc.SetBrush(br);
	wxRect rc = rect.Inflate(-2, -2);
	dc.DrawRectangle(rc.GetLeft(), rc.GetTop(), rc.GetWidth(), rc.GetHeight());
}

//amcHotkeyCtrl
amcHotkeyCtrl::amcHotkeyCtrl(wxWindow *parent) : wxTextCtrl(parent, wxID_ANY)
{
	m_parent = parent;
	m_key = wxEmptyString;
	m_mod = wxMOD_NONE;
	m_validkey = false;
	m_hkname = wxEmptyString;
	Connect( wxEVT_CHAR, wxKeyEventHandler( amcHotkeyCtrl::OnChar ), NULL, this );
	Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( amcHotkeyCtrl::OnKeyDown ), NULL, this );
	Connect( wxEVT_KEY_UP, wxKeyEventHandler( amcHotkeyCtrl::OnKeyUp ), NULL, this );
}

amcHotkeyCtrl::~amcHotkeyCtrl()
{
}

void amcHotkeyCtrl::OnChar(wxKeyEvent &event)
{
	//long keycode = event.GetKeyCode();
	//int mod = event.GetModifiers();
}

void amcHotkeyCtrl::OnKeyDown(wxKeyEvent &event)
{
	int mod = event.GetModifiers();
	long keycode = event.GetKeyCode();
	bool nokey = true;

	if (mod == wxMOD_CMD)
		m_key = _("Ctrl + ");
	if (mod == wxMOD_ALT)
		m_key = _("Alt + ");
	if (mod == wxMOD_SHIFT)
		m_key = _("Shift + ");
	if (mod&wxMOD_CMD && mod&wxMOD_ALT)
		m_key = _("Ctrl + Alt + ");
	if (mod&wxMOD_SHIFT && mod&wxMOD_ALT)
		m_key = _("Shift + Alt + ");
	if (mod&wxMOD_SHIFT && mod&wxMOD_CMD)
		m_key = _("Shift + Ctrl + ");
	if (mod&wxMOD_SHIFT && mod&wxMOD_ALT && mod&wxMOD_CMD)
		m_key = _("Shift + Ctrl + Alt + ");
	if (mod == wxMOD_NONE)
		m_key = wxEmptyString;
	m_mod = mod;
	switch (keycode)
	{
		case WXK_F1: m_key << _("F1"); break;
		case WXK_F2: m_key << _("F2"); break;
		case WXK_F3: m_key << _("F3"); break;
		case WXK_F4: m_key << _("F4"); break;
		case WXK_F5: m_key << _("F5"); break;
		case WXK_F6: m_key << _("F6"); break;
		case WXK_F7: m_key << _("F7"); break;
		case WXK_F8: m_key << _("F8"); break;
		case WXK_F9: m_key << _("F9"); break;
		case WXK_F10: m_key << _("F10"); break;
		case WXK_F11: m_key << _("F11"); break;
		case WXK_F12: m_key << _("F12"); break;
		case WXK_F13: m_key << _("F13"); break;
		case WXK_F14: m_key << _("F14"); break;
		case WXK_F15: m_key << _("F15"); break;
		case WXK_F16: m_key << _("F16"); break;
		case WXK_F17: m_key << _("F17"); break;
		case WXK_F18: m_key << _("F18"); break;
		case WXK_F19: m_key << _("F19"); break;
		case WXK_F20: m_key << _("F20"); break;
		case WXK_F21: m_key << _("F21"); break;
		case WXK_F22: m_key << _("F22"); break;
		case WXK_F23: m_key << _("F23"); break;
		case WXK_F24: m_key << _("F24"); break;
		case WXK_NUMPAD0: m_key << _("NUMPAD0"); break;
		case WXK_NUMPAD1: m_key << _("NUMPAD1"); break;
		case WXK_NUMPAD2: m_key << _("NUMPAD2"); break;
		case WXK_NUMPAD3: m_key << _("NUMPAD3"); break;
		case WXK_NUMPAD4: m_key << _("NUMPAD4"); break;
		case WXK_NUMPAD5: m_key << _("NUMPAD5"); break;
		case WXK_NUMPAD6: m_key << _("NUMPAD6"); break;
		case WXK_NUMPAD7: m_key << _("NUMPAD7"); break;
		case WXK_NUMPAD8: m_key << _("NUMPAD8"); break;
		case WXK_NUMPAD9: m_key << _("NUMPAD9"); break;
		case WXK_NUMPAD_LEFT: m_key << _("NUMPAD_LEFT"); break;
		case WXK_NUMPAD_UP: m_key << _("NUMPAD_UP"); break;
		case WXK_NUMPAD_RIGHT: m_key << _("NUMPAD_RIGHT"); break;
		case WXK_NUMPAD_DOWN: m_key << _("NUMPAD_DOWN"); break;
		case WXK_NUMPAD_PAGEUP: m_key << _("NUMPAD_PAGEUP"); break;
		case WXK_NUMPAD_PAGEDOWN: m_key << _("NUMPAD_PAGEDOWN"); break;
		case WXK_NUMPAD_HOME: m_key << _("NUMPAD_HOME"); break;
		case WXK_NUMPAD_END: m_key << _("NUMPAD_END"); break;
		case WXK_NUMPAD_BEGIN: m_key << _("NUMPAD_BEGIN"); break;
		case WXK_NUMPAD_INSERT: m_key << _("NUMPAD_INSERT"); break;
		case WXK_NUMPAD_DELETE: m_key << _("NUMPAD_DELETE"); break;
		case WXK_NUMPAD_EQUAL: m_key << _("NUMPAD_EQUAL"); break;
		case WXK_NUMPAD_MULTIPLY: m_key << _("NUMPAD_MULTIPLY"); break;
		case WXK_NUMPAD_DIVIDE: m_key << _("NUMPAD_DIVIDE"); break;
		case WXK_NUMPAD_ADD: m_key << _("NUMPAD_ADD"); break;
		case WXK_NUMPAD_SEPARATOR: m_key << _("NUMPAD_SEPARATOR"); break;
		case WXK_NUMPAD_SUBTRACT: m_key << _("NUMPAD_SUBTRACT"); break;
		case WXK_NUMPAD_DECIMAL: m_key << _("NUMPAD_DECIMAL"); break;
		case WXK_NUMPAD_SPACE: m_key << _("NUMPAD_SPACE"); break;
		case WXK_NUMPAD_TAB: m_key << _("NUMPAD_TAB"); break;
		case WXK_NUMPAD_ENTER: m_key << _("NUMPAD_ENTER"); break;
		case WXK_MULTIPLY: m_key << _("MULTIPLY"); break;
		case WXK_ADD: m_key << _("ADD"); break;
		case WXK_SEPARATOR: m_key << _("SEPARATOR"); break;
		case WXK_SUBTRACT: m_key << _("SUBTRACT"); break;
		case WXK_DECIMAL: m_key << _("DECIMAL"); break;
		case WXK_DIVIDE: m_key << _("DIVIDE"); break;
		case WXK_MENU: m_key << _("MENU"); break;
		case WXK_PAUSE: m_key << _("PAUSE"); break;
		case WXK_CAPITAL: m_key << _("CAPITAL"); break;
		case WXK_END: m_key << _("END"); break;
		case WXK_HOME: m_key << _("HOME"); break;
		case WXK_LEFT: m_key << _("LEFT"); break;
		case WXK_UP: m_key << _("UP"); break;
		case WXK_RIGHT: m_key << _("RIGHT"); break;
		case WXK_DOWN: m_key << _("DOWN"); break;
		case WXK_SELECT: m_key << _("SELECT"); break;
		case WXK_PRINT: m_key << _("PRINT"); break;
		case WXK_BACK: m_key << wxT(""); break;
		case WXK_SHIFT:
		case WXK_ALT:
		case WXK_CONTROL: break;
		case WXK_TAB: Navigate(); break;
		default: nokey = false; break;
	}
	if (keycode != 0 && keycode != WXK_BACK && keycode != WXK_CONTROL && keycode != WXK_ALT && keycode != WXK_SHIFT)
		m_validkey = true;
	else
		m_validkey = false;
	m_hotkey = keycode;
#if defined __WXMSW__ && !defined __CODELITE__
	keycode = MapVirtualKey(event.m_rawCode, MAPVK_VK_TO_CHAR);
#endif
	//if (keycode>0 && keycode!=WXK_BACK && keycode!=WXK_CONTROL && keycode!=WXK_SHIFT && keycode!=WXK_ALT)
	if (keycode > 0 && !nokey)
		m_key << (wxChar)keycode;
	ChangeValue(m_key);
	m_hkname = m_key;
	SetInsertionPointEnd();

	//event.Skip();
}

void amcHotkeyCtrl::OnKeyUp(wxKeyEvent &event)
{
	int mod = event.GetModifiers();
	long keycode = event.GetKeyCode();
	if (mod == wxMOD_NONE && (keycode == WXK_CONTROL || keycode == WXK_SHIFT || keycode == WXK_ALT))
	{
		if (m_validkey == false)
			m_key = _("None");
	}
	ChangeValue(m_key);
	SetInsertionPointEnd();
	event.Skip();
}
