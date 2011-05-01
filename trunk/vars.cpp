#include "main.h"

std::vector<wxString> amcVar::m_vgroup;

/*!
	default constructor
*/
amcVar::amcVar()
{
	m_parent = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	m_name = wxEmptyString;
	m_value = wxEmptyString;
	m_group = wxT("default");
	m_on = false;
	m_idx = 0;
}

/*!
	construct some variable
*/
amcVar::amcVar(wxString name, wxString val, wxString gr, bool on)
{
	m_parent = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	m_name = name;
	m_value = val;
	m_group = gr;
	m_on = on;
	m_idx = 0;

	int i = count(m_vgroup.begin(), m_vgroup.end(), m_group);
	if (!i)
		m_vgroup.push_back(m_group);
}

/*!
	set the group and remember it
*/
void amcVar::SetGroup(wxString s)
{
	m_group = s;
	int i = count(m_vgroup.begin(), m_vgroup.end(), m_group);
	if (!i)
		m_vgroup.push_back(m_group);
}

/*! destructor
*/
amcVar::~amcVar()
{
}

//**amcDefVar implementation **//
//std::vector<wxString> amcDefVar::m_group;

amcDefVar::amcDefVar() : amcVar()
{
}

amcDefVar::~amcDefVar()
{
}

amcDefVar::amcDefVar(wxString name, wxString value) : amcVar(name, value)
{
}

//** amcList implementation **//
std::vector<wxString> amcList::m_lgroup;

/*!
	default constructor
*/
amcList::amcList()
{
	m_parent = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	m_name = wxEmptyString;
	m_value = wxEmptyString;
	m_group = wxT("default");
	m_on = false;
	m_idx = 0;
}

/*!
	construct some list
*/
amcList::amcList(wxString name, std::vector<wxString> val, wxString gr, bool on)
{
	m_parent = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	m_name = name;
	m_list = val;
	m_group = gr;
	m_on = on;
	m_idx = 0;

	int i = count(m_lgroup.begin(), m_lgroup.end(), m_group);
	if (!i)
		m_lgroup.push_back(m_group);
}

/*!
	set the group and remember it
*/
void amcList::SetGroup(wxString s)
{
	m_group = s;
	int i = count(m_lgroup.begin(), m_lgroup.end(), m_group);
	if (!i)
		m_lgroup.push_back(m_group);
}

wxString amcList::GetValue()
{
	s_it it;
	m_value = wxEmptyString;
	for (it=m_list.begin();it!=m_list.end();it++)
	{
		m_value.append(*it);
		m_value.append(wxT("|"));
	}
	wxString s;
	if (m_value.EndsWith(wxT("|"), &s))
		m_value=s;
	return m_value;
}

bool amcList::DeleteItem(wxString item)
{
s_it f;
	f = std::find(m_list.begin(), m_list.end(), item);
	if (f==m_list.end())
		return false;
	m_list.erase(f);
	return true;
}

bool amcList::Contains(wxString item)
{
s_it f;
	f = std::find(m_list.begin(), m_list.end(), item);
	if (f==m_list.end())
		return false;
	else 
		return true;
}

/*! destructor
*/
amcList::~amcList()
{
}
