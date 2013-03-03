/*! \file amcButton.cpp
	\brief implements the amcButton class.
	
	This represents user buttons.
*/
#include "main.h"

std::vector<wxString> amcButton::m_bgroup;
//amcButton
amcButton::amcButton()
{
	m_frame = wxGetApp().GetFrame(); //(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	m_parent = NULL;
	m_name = wxEmptyString;
	m_label = wxEmptyString;
	m_action = wxEmptyString;
	m_tbname = wxEmptyString;
	m_bitmap ="script.xpm";
	m_on = false;
	m_id = 0;
	m_show = false;
}

amcButton::~amcButton()
{
	
}

amcButton::amcButton(wxAuiToolBar *tb, wxString label, wxString text, wxString action, wxString group)
{
	m_frame = wxGetApp().GetFrame();
	m_parent = tb;
	
	m_label = label;
	m_text  = text;
	m_action = action;
	m_group = group;
	m_bitmap = "script.xpm";
	m_on = true;
	m_show = true;
	m_id = 0;
	int ii = count(m_bgroup.begin(), m_bgroup.end(), m_group);
	if (!ii)
		m_bgroup.push_back(m_group);
}

amcButton::amcButton(const amcButton& at)
{
	m_parent = at.m_parent;
	m_frame = at.m_frame;
	m_label = at.m_label;
	m_text = at.m_text;
	m_name = at.m_name;
	m_tbname = at.m_tbname;
	m_action = at.m_action;
	m_group = at.m_group;
	m_on = at.m_on;
	m_id = at.m_id;
	m_show = at.m_show;
	m_bitmap = at.m_bitmap;
}

/*!
	set the group and remember it
*/
void amcButton::SetGroup(const wxString& s)
{
	m_group = s;
	int i = count(m_bgroup.begin(), m_bgroup.end(), m_group);
	if (!i)
		m_bgroup.push_back(m_group);
}


amcButton& amcButton::operator =(const amcButton & at)
{
	m_parent = at.m_parent;
	m_frame = at.m_frame;
	m_label = at.m_label;
	m_text = at.m_text;
	m_name = at.m_name;
	m_tbname = at.m_tbname;
	m_action = at.m_action;
	m_group = at.m_group;
	m_on = at.m_on;
	m_show = at.m_show;
	m_id = at.m_id;
	m_bitmap = at.m_bitmap;
	return *this;
}

void amcButton::SetBitmap(const wxString& m)
{
	m_bitmap = m;
}

void amcButton::SetAsSeparator(wxAuiToolBar *tb)
{
	m_parent = tb;
	m_name = "separator";
	m_label = "separator";
	m_text  = "separator";
	m_action = wxEmptyString;
	m_group = "default";
	m_bitmap = wxEmptyString;
	m_on = true;
	m_show = true;
	m_id = 0;
	int ii = count(m_bgroup.begin(), m_bgroup.end(), m_group);
	if (!ii)
		m_bgroup.push_back("default");
}