#include "main.h"

GlobalOptions::GlobalOptions()
{
	Init();
}

GlobalOptions::GlobalOptions(wxWindow *parent)
{
	m_parent = (MudMainFrame*)parent;
	Init();
}

GlobalOptions::~GlobalOptions()
{
	delete m_logfile;
	delete m_clientcol;
	delete m_echocol;
	//delete m_eventfile;
}

void GlobalOptions::Init()
{
	m_maxhistory = 200;
	m_command = '#';
	m_sep = ';';
	m_var = '$';
	m_sw = '.';
	m_swb = '*';
	m_script = '?';
	m_intvar = '%';
	m_listvar = '@';
	m_swdelay = 1000;//milliseconds
	m_ansilog = false;
	m_htmllog = false;
	m_logall = true;
	m_logfile = new wxString("log.txt");
	m_autoconnect = false;
	m_localecho = true;
	m_triggerecho = true;
	m_acdelay = 15;
	m_usemccp = true;
	m_usemsp = true;
	m_usemxp = true;
	m_useatcp = false;
	m_useatcp2 = true;
	m_useaard = false;
	m_usemsdp = false;
	m_usewrap = true;
	m_autowrap = true;//use autowrapping..window width
	m_utf8 = false;//mud stream in utf8? beware...

	m_iacgeor = false;
	m_naws = true;
	m_events = true;
	m_connect = m_precv = m_disconnect = m_telnetdata = m_gmcpdata = m_msdpdata = true;
	
	m_raw = false;

	m_clientcol = new wxString("\x1b[56m");
	m_echocol = new wxString("\x1b[57m");

	m_gmcpmodules.push_back("Core 1");
	m_gmcpmodules.push_back("Char 1");
	m_gmcpmodules.push_back("Room 1");
	m_gmcpmodules.push_back("Comm 1");
	m_gmcpmodules.push_back("Group 1");

	m_curencoding = wxFONTENCODING_SYSTEM;

	#if defined __WXMSW__
		/*wxStandardPaths p;
		wxString dir = p.GetUserDataDir();
		dir= p.GetUserConfigDir();
		dir = p.GetDataDir();
		dir = p.GetDocumentsDir();*/
		//m_workdir.Assign(wxStandardPaths::Get().GetDocumentsDir());
		//m_workdir.Assign(wxGetCwd());
		m_workdir.Assign(wxStandardPaths::Get().GetDataDir());
		//m_workdir.AssignCwd();		
	#endif
	#if defined __WXOSX__
		m_workdir.Assign(wxStandardPaths::Get().GetAppDocumentsDir());
	#endif
	wxString s;
	#if defined __WXGTK__
		wxStandardPaths p = wxStandardPaths::Get();
		m_workdir.Assign(p.GetUserDataDir());
		s = m_workdir.GetFullPath();
		if (!m_workdir.DirExists(s))//first time around?
		{
			//Create the necessary directories in users homedir	
			m_workdir.Mkdir(s);
			wxSetWorkingDirectory(GetWorkDir());
			wxMkdir("profiles");
			wxMkdir("logs");
			wxMkdir("scripts");
			wxMkdir("scripts/samples");
			wxMkdir("packages");
			wxMkdir("databases");
			wxMkdir("sounds");
			wxMkdir("lua");
			wxMkdir("images");
			s = p.GetDataDir();
			wxString src = s;
			src<<"/hosts.lua";
			wxString dest = GetWorkDir();
			wxCopyFile(src, dest<<"/hosts.lua");
			src = s;
			src<<"/settings.lua";
			dest = GetWorkDir();
			wxCopyFile(src, dest<<"/settings.lua");
			src = s;
			src<<"/settings.lua";
			dest = GetWorkDir();
			wxCopyFile(src, dest<<"/defaultsettings.lua");
			src = s;
			src<<"/tabcompletion.txt";
			dest = GetWorkDir();
			wxCopyFile(src, dest<<"/tabcompletion.txt");
			src = s;
			src<<"/events.lua";
			dest = GetWorkDir();
			wxCopyFile(src, dest<<"/scripts/events.lua");
			src = s;
			src<<"/json.lua";
			dest = GetWorkDir();
			wxCopyFile(src, dest<<"/lua/json.lua");
			src = s;
			src<<"/printt.lua";
			dest = GetWorkDir();
			wxCopyFile(src, dest<<"/lua/printt.lua");
			src = s;
			src<<"/defaultprofile.lua";
			dest = GetWorkDir();
			wxCopyFile(src, dest<<"/profiles/defaultprofile.lua");
			src = s;
			src<<"/mapper.lua";
			dest = GetWorkDir();
			wxCopyFile(src, dest<<"/scripts/mapper.lua");
			src = s;
			src<<"/mapper_events.lua";
			dest = GetWorkDir();
			wxCopyFile(src, dest<<"/scripts/mapper_events.lua");
			src = s;
			src<<"/events_aard.lua";
			dest = GetWorkDir();
			wxCopyFile(src, dest<<"/scripts/events_aard.lua");
			src = s;
			src<<"/salias.lua";
			dest = GetWorkDir();
			wxCopyFile(src, dest<<"/scripts/samples/salias.lua");
			src = s;
			src<<"/gmcp_echo.lua";
			dest = GetWorkDir();
			wxCopyFile(src, dest<<"/scripts/samples/gmcp_echo.lua");
			wxString ff;
			wxDir dir(s);
            if (!dir.IsOpened())
            {
                wxMkdir(s);
            }
			bool bb= dir.GetFirst(&ff, "*.xpm");
			while (bb)
			{
				dest=GetWorkDir();
				src = s;
				wxCopyFile(src<<"/"<<ff, dest<<"/images/"<<ff);
				ff.Empty();
				bb = dir.GetNext(&ff);
			}
		}
	#endif
	//m_workdir.Assign(wxGetCwd());
	s = m_workdir.GetFullPath();
	//s = m_workdir.GetHomeDir();
	//m_workdir.AssignDir("d:\\wxAMC\\amcl\\amcl2\\amcl29\\");
	m_profiledir.AssignDir(m_workdir.GetFullPath());
	m_profiledir.AppendDir("profiles");
	//m_scriptdir = m_workdir;
	m_scriptdir.AssignDir(m_workdir.GetFullPath());
	m_scriptdir.AppendDir("scripts");
	m_logdir.AssignDir(m_workdir.GetFullPath());
	m_logdir.AppendDir("logs");
	//m_packagedir = m_workdir;
	m_packagedir.AssignDir(m_workdir.GetFullPath());
	m_packagedir.AppendDir("packages");
	m_databasedir.AssignDir(m_workdir.GetFullPath());
	m_databasedir.AppendDir("databases");
	m_sounddir.AssignDir(m_workdir.GetFullPath());
	m_sounddir.AppendDir("sounds");
	m_luadir.AssignDir(m_workdir.GetFullPath());
	m_luadir.AppendDir("lua");
	m_imagesdir.AssignDir(m_workdir.GetFullPath());
	m_imagesdir.AppendDir("images");
	m_eventfile = m_scriptdir.GetFullPath();
	m_eventfile.Append("events.lua");
}

RegExp::RegExp()
{
	m_pattern = wxEmptyString;
	m_match = wxEmptyString;
	//m_re = pcre_compile(wxT(""), 0, &m_error, &m_erroffset, NULL);
	m_re=0;
	m_prextra = 0;
	m_r=0;
	m_start = m_end = -1;
	m_precompiled = false;
}

RegExp::RegExp(wxString pattern)
{
	MudMainFrame *frame = wxGetApp().GetFrame();
	m_pattern = pattern;
	if (!frame->GetGlobalOptions()->UseUTF8())
		m_re = pcre_compile(m_pattern.To8BitData().data(), 0, &m_error, &m_erroffset, NULL);
	
	else
	{
		wxString s = m_pattern;//.ToUTF8();
		//m_re = pcre_compile(s.mb_str(), PCRE_UTF8|PCRE_NO_UTF8_CHECK, &m_error, &m_erroffset, NULL);
		m_re = pcre_compile(m_pattern.ToUTF8(), PCRE_UTF8|PCRE_NO_UTF8_CHECK, &m_error, &m_erroffset, NULL);
		
	}
		//m_prextra = pcre_study(m_re, 0, &m_error);
	m_prextra = 0;
	m_match = wxEmptyString;
	m_start = m_end = -1;
	m_r=0;
	if (m_re)
		m_precompiled = true;//false;
	else m_precompiled = false;
}

RegExp::~RegExp()
{
	if (m_re!=NULL)
	{
		pcre_free(m_re);
		m_re = NULL;
	}
	if (m_prextra)
	{
		pcre_free(m_prextra);
		m_prextra = NULL;
	}
	if (!m_matches.empty())
		m_matches.clear();
}

bool RegExp::Match(wxString match, bool bo, bool multi)
{
	m_match = match;
	//MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	if (!m_precompiled)
	{
		if (!multi)
		{
			if (!Compile())
				return false;
		}
		else
		{
			if (!CompileMulti())
				return false;
		}
	}
	if (Exec() > 0)
	{
		//frame->m_child->Msg(wxString::Format("true: %d", m_r));
		m_start = m_ovector[0];
		m_end = m_ovector[1];
		if (bo)
			SubMatches();
		if (!m_precompiled)
		{
			pcre_free(m_re);
			m_re=NULL;
		}
		return true;
	}
	else
	{
		//frame->m_child->Msg(wxString::Format("false: %d", m_r));
		if (!m_precompiled)
		{
			pcre_free(m_re);
			m_re=NULL;
		}
		return false;
	}

}

pcre* RegExp::Compile()
{
	//m_re = pcre_compile(m_pattern.c_str(), 0, &m_error, &m_erroffset, NULL);
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (!frame->GetGlobalOptions()->UseUTF8())
		//m_re = pcre_compile(m_pattern.mb_str(), 0, &m_error, &m_erroffset, NULL);
		m_re = pcre_compile(m_pattern.mb_str(co).data(), 0, &m_error, &m_erroffset, NULL);
	else
	{
		wxString s = m_pattern.ToUTF8();
		m_re = pcre_compile(s.mb_str(), PCRE_UTF8|PCRE_NO_UTF8_CHECK, &m_error, &m_erroffset, NULL);
		
	}
	return m_re;
}

pcre* RegExp::CompileMulti()
{
	//m_re = pcre_compile(m_pattern.c_str(), 0, &m_error, &m_erroffset, NULL);
	MudMainFrame *frame = wxGetApp().GetFrame();
	
	if (!frame->GetGlobalOptions()->UseUTF8())
		m_re = pcre_compile(m_pattern.char_str(), PCRE_MULTILINE, &m_error, &m_erroffset, NULL);
	else
	{
		wxString s = m_pattern.ToUTF8();
		m_re = pcre_compile(s.mb_str(), PCRE_UTF8|PCRE_NO_UTF8_CHECK|PCRE_MULTILINE, &m_error, &m_erroffset, NULL);
	}
	return m_re;
}

int RegExp::Exec()
{
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	wxString ss = m_match.mb_str(co);
	if (ss.empty())
		return -1;
	if (!frame->GetGlobalOptions()->UseUTF8())
	{
		if (m_precompiled)
			return m_r = pcre_exec(m_re, m_prextra, m_match.mb_str(co).data(), (int)m_match.length(), 0, 0, m_ovector, OVECCOUNT);
		else return m_r = pcre_exec(m_re, NULL, m_match.mb_str(co).data(), (int)m_match.length(), 0, 0, m_ovector, OVECCOUNT);
	}
	else
	{
		wxString s = m_match.ToUTF8();
		if (m_precompiled)
			return m_r = pcre_exec(m_re, m_prextra, s.mb_str(), (int)s.mb_str().length(), 0, PCRE_NO_UTF8_CHECK, m_ovector, OVECCOUNT);
		else return m_r = pcre_exec(m_re, NULL, s.mb_str(), (int)s.mb_str().length(), 0, PCRE_NO_UTF8_CHECK, m_ovector, OVECCOUNT);
	}
	//return m_rc;
}

int RegExp::ExecMulti()
{
	MudMainFrame *frame = wxGetApp().GetFrame();
	if (!frame->GetGlobalOptions()->UseUTF8())
	{
		if (m_precompiled)
			return m_r = pcre_exec(m_re, m_prextra, m_match.To8BitData().data(), (int)m_match.length(), 0, PCRE_NOTBOL|PCRE_NOTEOL, m_ovector, OVECCOUNT);
		else return m_r = pcre_exec(m_re, NULL, m_match.To8BitData().data(), (int)m_match.length(), 0, PCRE_NOTBOL|PCRE_NOTEOL, m_ovector, OVECCOUNT);
	}
	else
	{
		wxString s = m_match.ToUTF8();
		if (m_precompiled)
			return m_r = pcre_exec(m_re, m_prextra, s.mb_str(), (int)m_match.length(), 0, PCRE_NO_UTF8_CHECK|PCRE_NOTBOL|PCRE_NOTEOL, m_ovector, OVECCOUNT);
		else return m_r = pcre_exec(m_re, NULL, s.mb_str(), (int)s.length(), 0, PCRE_NO_UTF8_CHECK|PCRE_NOTBOL|PCRE_NOTEOL, m_ovector, OVECCOUNT);
	}
	//return m_rc;
}

void RegExp::SubMatches()
{
int i;
wxString sub;

	if (!m_matches.empty())
		m_matches.clear();
	MudMainFrame *frame = wxGetApp().GetFrame();
	for (i = 1; i < m_r; i++)
	{
		if (m_ovector[2*i]!=-1)
		{
			if (frame->GetGlobalOptions()->UseUTF8())
			{
				wxString s = m_match.ToUTF8();
				sub = s.substr(m_ovector[2*i], m_ovector[2*i+1] - m_ovector[2*i]);
				m_matches.push_back(wxString::FromUTF8(sub));
			}
			else
			{
				sub = m_match.substr(m_ovector[2*i], m_ovector[2*i+1] - m_ovector[2*i]);
				m_matches.push_back(sub);
			}
		}
		else m_matches.push_back("");
	}
	//Expose wildcards to lua
	amcLua *aL = frame->m_child->GetLState();
	struct lua_State *L = aL->GetLuaState();
	s_it it;
	int x;

	lua_newtable(L);
	for(it=m_matches.begin(), x=0;it!=m_matches.end();it++, x++)
	{
		lua_pushnumber(L, x);
		wxString s = *it;
		lua_pushstring(L, s.char_str());
		lua_settable(L, -3);
	}
	lua_setglobal(L, "amcWildcards");
}

wxString RegExp::GetMatch(int idx)
{
	if (m_matches.empty())
		return wxEmptyString;
	else if (idx>=(int)m_matches.size())
		return wxEmptyString;
	else return m_matches[idx];
}
