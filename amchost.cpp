#include "main.h"

amchost::amchost()
{
	m_ip.Hostname("localhost");
	m_ip.Service(4000);
	m_ip6.Hostname("localhost");
	m_ip6.Service(4000);
	m_hostname = "localhost";
	m_mudname = wxEmptyString;
	m_charname = wxEmptyString;
	m_password = wxEmptyString;
	m_port = 4000;
	MudMainFrame* frame = wxGetApp().GetFrame();
	wxString name = frame->GetGlobalOptions()->GetProfileDir();
	name << "newprofile.lua";
	//m_profile.AssignCwd();
	m_profile.Assign(name);
	m_ipaddr = "127.0.0.1";
}

amchost::~amchost()
{
}

