#include "main.h"

std::vector<wxString> amcAlias::m_algroup;

/*!
	default constructor
*/
amcAlias::amcAlias()
{
	//m_parent = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	m_parent = wxGetApp().GetFrame();
	m_alias = wxEmptyString;
	m_action = wxEmptyString;
	m_group = "default";
	m_on = false;
	m_match = wxEmptyString;
	m_idx = 0;
}

/*!
	construct some alias
*/
amcAlias::amcAlias(wxString alias, wxString action, wxString gr, bool on)
{
	//m_parent = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	m_parent = wxGetApp().GetFrame();
	m_alias = alias;
	m_action = action;
	m_group = gr;
	m_on = on;
	m_idx = 0;
	
	int i = count(m_algroup.begin(), m_algroup.end(), m_group);
	if (!i)
		m_algroup.push_back(m_group);
}

/*!
	set the group an remember it
*/
void amcAlias::SetGroup(wxString s)
{
	m_group = s;
	int i = count(m_algroup.begin(), m_algroup.end(), m_group);
	if (!i)
		m_algroup.push_back(m_group);
}

/*! destructor
*/
amcAlias::~amcAlias()
{
}

/*!
	see if the user input matches our pattern
*/
bool amcAlias::Match(wxString match)
{
	if (!m_on)
		return false;
	
	m_match = match;
	m_rexp.SetPattern(m_alias);
	if (m_rexp.Match(m_match))
	{
		return true;
	}
	else
		return false;
}

wxString amcAlias::BuildAction()
{
wxString s = m_action;
size_t idx=0, i=0;
long num=0;
wxString var;
	
	do
	{
		//replace the intvars %0
		idx = s.find(m_parent->GetGlobalOptions()->GetIntVar());
		if (idx!=string::npos)
		{
			i = idx+1;
			while (i<s.length())
			{
				if (wxIsdigit(s.at(i)))			
					i++;
				else break;
			}
			//while (isdigit(s.at(i)))
			//	i++;
			var = s.substr(idx+1, i-idx-1);
			var.ToLong(&num);
			var = s.substr(idx, i-idx);
			s.Replace(var, m_rexp.GetMatch(num));
		}
	} while (idx!=string::npos);
	return s;
}

wxString amcAlias::GetName()
{
wxString name;
	if (m_alias.at(0)=='^')
		name = m_alias.substr(1);
	if (m_alias.at(m_alias.length()-1)=='$')
		name = name.substr(0, name.length()-1);
	return name;
}
