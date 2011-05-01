#include "main.h"

std::vector<wxString> amcHotkey::m_hgroup;

/*!
	default constructor
*/
amcHotkey::amcHotkey()
{
	m_parent = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	m_hotkey = 0;
	m_mods = wxMOD_NONE;
	m_action = wxEmptyString;
	m_group = wxT("default");
	m_on = false;
}

/*!
	construct some hotkey
*/
amcHotkey::amcHotkey(long keycode, int mods, wxString name, wxString action, wxString gr, bool on)
{
	m_parent = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	m_hotkey = keycode;
	m_mods = mods;
	m_action = action;
	m_group = gr;
	m_on = on;
	m_name = name;
	
	int i = count(m_hgroup.begin(), m_hgroup.end(), m_group);
	if (!i)
		m_hgroup.push_back(m_group);
}

/*!
	set the group an remember it
*/
void amcHotkey::SetGroup(wxString s)
{
	m_group = s;
	int i = count(m_hgroup.begin(), m_hgroup.end(), m_group);
	if (!i)
		m_hgroup.push_back(m_group);
}

/*! destructor
*/
amcHotkey::~amcHotkey()
{
}

wxString amcHotkey::GetKeyName()
{
	map<wxString, long> m = m_parent->GetKeys();
	map<wxString, long>::iterator it;
	for (it=m.begin();it!=m.end();it++)
	{
		if (m_hotkey==it->second)
			return it->first;
	}
	return "";
}

wxString amcHotkey::GetModName()
{
	map<wxString, long> m = m_parent->GetKeys();
	map<wxString, long>::iterator it;
	for (it=m.begin();it!=m.end();it++)
	{
		if (m_mods==it->second)
			return it->first;
	}
	return "";
}