#include "main.h"

std::vector<wxString> amcTimer::m_tgroup;

amcTimer::amcTimer(void) : wxTimer()
{
	//m_parent = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	m_parent = wxGetApp().GetFrame();
	m_name = wxEmptyString;
	m_action = wxEmptyString;
	m_group = "default";
	m_on = false;
	m_repeat = m_currepeat = -1;
	m_interval = 0;
	m_idx = 0;
	m_show = true;
}

amcTimer::amcTimer(wxString name, wxString ac, wxString group, float i, int r, bool s) : wxTimer()
{
	//m_parent = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	m_parent = wxGetApp().GetFrame();
	m_name = name;
	m_action = ac;
	m_on = false;
	m_repeat = m_currepeat = r;
	m_interval = (int)(i * 1000);
	m_idx = 0;
	m_group = group;
	m_show = s;
	int ii = count(m_tgroup.begin(), m_tgroup.end(), m_group);
	if (!ii)
		m_tgroup.push_back(m_group);
}

amcTimer::amcTimer(const amcTimer& at) : wxTimer()
{
	m_parent = at.m_parent;
	m_name = at.m_name;
	m_action = at.m_action;
	m_group = at.m_group;
	m_on = at.m_on;
	m_repeat = at.m_repeat;
	m_currepeat = at.m_currepeat;
	m_interval = at.m_interval;
	m_idx = at.m_idx;
	m_show = at.m_show;
}

amcTimer& amcTimer::operator =(const amcTimer & at)
{
	m_parent = at.m_parent;
	m_name = at.m_name;
	m_action = at.m_action;
	m_group = at.m_group;
	m_on = at.m_on;
	m_repeat = at.m_repeat;
	m_currepeat = at.m_currepeat;
	m_interval = at.m_interval;
	m_idx = at.m_idx;
	m_show = at.m_show;
	return *this;
}

amcTimer::~amcTimer(void)
{
}

/*!
	set the group and remember it
*/
void amcTimer::SetGroup(const wxString& s)
{
	m_group = s;
	int i = count(m_tgroup.begin(), m_tgroup.end(), m_group);
	if (!i)
		m_tgroup.push_back(m_group);
}

void amcTimer::Run()
{
	if (m_on)
	{
		if (m_repeat == 1)
			this->Start(m_interval, true);//one shot timer
		else Start(m_interval, false);
	}
}

void amcTimer::Notify()
{
	
	if (m_currepeat==-1)
	{
		m_parent->m_input->Parse(m_action, true);
		return;
	}
	if (m_currepeat >= 1)
	{
		m_parent->m_input->Parse(m_action, true);
		m_currepeat--;
	}
	else
	{
		m_currepeat = m_repeat;
		this->Stop();
	}
}
