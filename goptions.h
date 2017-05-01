#ifndef GOptions_H
#define GOptions_H

class GlobalOptions
{
public:
	GlobalOptions();
	GlobalOptions(wxWindow *parent);
	~GlobalOptions();
	void Init();

	//int GetMaxLines() {return m_maxlines;}
	//void SetMaxLines(int m) {m_maxlines=m;}
	unsigned int GetMaxHist() {return m_maxhistory;}
	void SetMaxHist(int m) {m_maxhistory=m;}
	wxChar GetCommand() {return m_command;}
	void SetCommand(const wxChar *c) {m_command=*c;}
	const wxChar GetSep() {return m_sep;}
	void SetSep(const wxChar *c) {m_sep=*c;}
	wxChar GetVar() {return m_var;}
	void SetVar(const wxChar *c) {m_var=*c;}
	void SetSpeedwalk(const wxChar *c) {m_sw=*c;}
	void SetBSpeedwalk(const wxChar *c) {m_swb=*c;}
	wxChar GetSpeedwalk() {return m_sw;}
	wxChar GetScript() {return m_script;}
	wxChar GetRevSpeedwalk() {return m_swb;}
	void SetScript(const wxChar *c) {m_script=*c;}
	wxChar GetIntVar() {return m_intvar;}
	void SetIntVar(const wxChar *c) {m_intvar=*c;}
	wxChar GetListVar() {return m_listvar;}
	void SetListVar(const wxChar *c) {m_listvar=*c;}
	bool UseMCCP() {return m_usemccp;}
	void SetMCCP(bool b) {m_usemccp=b;}
	bool UseMXP() {return m_usemxp;}
	void SetMXP(bool b) {m_usemxp=b;}
	bool UseMSP() {return m_usemsp;}
	void SetMSP(bool b) {m_usemsp=b;}
	bool UseWrap() {return m_usewrap;}
	void SetUseWrap(bool b) {m_usewrap=b;}
	bool AutoWrap() {return m_autowrap;}
	void SetAutoWrap(bool b) {m_autowrap=b;}
	bool UseNAWS() {return m_naws;}
	void SetNAWS(bool b) {m_naws=b;}
	bool UseGAEOR() {return m_iacgeor;}
	void SetGAEOR(bool b) {m_iacgeor=b;}
	bool UseATCP() {return m_useatcp;}
	void SetUseATCP(bool b) {m_useatcp=b;}
	bool UseATCP2() {return m_useatcp2;}
	void SetUseATCP2(bool b) {m_useatcp2=b;}
	bool UseMSDP() {return m_usemsdp;}
	void SetUseMSDP(bool b) {m_usemsdp=b;}
	bool UseAard() {return m_useaard;}
	void SetUseAard(bool b) {m_useaard=b;}
	void SetDebugRaw(bool b) {m_raw=b;}
	bool GetEcho() {return m_localecho;}
	void SetEcho(bool b) {m_localecho=b;}
	bool GetTriggerEcho() {return m_triggerecho;}
	void SetTriggerEcho(bool b) {m_triggerecho=b;}
	bool GetUseEvents() {return m_events;}
	bool GetUseEvConn() {return m_connect;}
	bool GetUseEvRecv() {return m_precv;}
	bool GetUseEvDisco() {return m_disconnect;}
	bool GetUseEvTelnetData() {return m_telnetdata;}
	bool GetUseEvGMCPData() {return m_gmcpdata;}
	bool GetUseEvMSDPData() {return m_msdpdata;}
	void SetUseEvents(bool b) {m_events=b;}
	void SetUseEvConn(bool b) {m_connect=b;}
	void SetUseEvRecv(bool b) {m_precv=b;}
	void SetUseEvDisco(bool b) {m_disconnect=b;}
	void SetUseEvTelnetData(bool b) {m_telnetdata=b;}
	void SetUseEvGMCPData(bool b) {m_gmcpdata=b;}
	void SetUseEvMSDPData(bool b) {m_msdpdata=b;}
	wxString GetEventFile() {return m_eventfile;}
	void SetEventFile(wxString s) {m_eventfile=s;}
	bool DebugRaw() {return m_raw;}

	bool UseUTF8() {return m_utf8;}
	void SetUTF8(bool b) {m_utf8 = b;}
	bool GetAutoConnect()  {return m_autoconnect;}
	void SetAutoConnect(bool b) {m_autoconnect=b;}
	int GetACDelay()  {return m_acdelay;}
	void SetACDelay(int f) {m_acdelay=f;}
	void SetSWDelay(int f) {m_swdelay=f;}
	int GetSWDelay() {return m_swdelay;}
    #ifndef __WXOSX__
	wxString GetWorkDir() {return m_workdir.GetFullPath();}
	wxString GetProfileDir() {return m_profiledir.GetFullPath();}
	wxString GetScriptDir() {return m_scriptdir.GetFullPath();}
	wxString GetLogDir() {return m_logdir.GetFullPath();}
	wxString GetPackageDir() {return m_packagedir.GetFullPath();}
	wxString GetDatabaseDir() {return m_databasedir.GetFullPath();}
	wxString GetSoundDir() {return m_sounddir.GetFullPath();}
	wxString GetLuaDir() {return m_luadir.GetFullPath();}
	wxString GetImagesDir() {return m_imagesdir.GetFullPath();}
    #endif
    #ifdef __WXOSX__
    wxString GetWorkDir() {return m_workdir.GetFullPath();}
	wxString GetProfileDir() {return m_profiledir.GetFullPath().RemoveLast();}
	wxString GetScriptDir() {return m_scriptdir.GetFullPath().RemoveLast();}
	wxString GetLogDir() {return m_logdir.GetFullPath().RemoveLast();}
	wxString GetPackageDir() {return m_packagedir.GetFullPath().RemoveLast();}
	wxString GetDatabaseDir() {return m_databasedir.GetFullPath().RemoveLast();}
	wxString GetSoundDir() {return m_sounddir.GetFullPath().RemoveLast();}
	wxString GetLuaDir() {return m_luadir.GetFullPath().RemoveLast();}
	wxString GetImagesDir() {return m_imagesdir.GetFullPath().RemoveLast();}
    #endif
	void SetWorkDir(wxString s) {m_workdir.AssignDir(s);}
	void SetLogDir(wxString s) {m_logdir.AssignDir(s);}
	void SetSoundDir(wxString s) {m_sounddir.AssignDir(s);}
	void SetScriptDir(wxString s) {m_scriptdir.AssignDir(s);}
	void SetDatabaseDir(wxString s) {m_databasedir.AssignDir(s);}
	void SetProfileDir(wxString s) {m_profiledir.AssignDir(s);}
	void SetPackageDir(wxString s) {m_packagedir.AssignDir(s);}
	void SetLuaDir(wxString s) {m_luadir.AssignDir(s);}
	void SetImagesDir(wxString s) {m_imagesdir.AssignDir(s);}

	vector<wxString>* GetGMCPModules() {return &m_gmcpmodules;}
	wxString* GetClientCol() {return m_clientcol;}
	wxString* GetMsgCol() {return m_echocol;}
	//wxWindow* GetParent() {return m_parent;}
	MudMainFrame* GetParent() {return m_parent;}
	wxFontEncoding GetCurEncoding() {return m_curencoding;}
	void SetEncoding(wxFontEncoding ec) {m_curencoding=ec;}
private:
	//Global prefs
	//int m_maxlines;
	unsigned int m_maxhistory;

	wxChar m_command;
	wxChar m_sep;
	wxChar m_var;
	wxChar m_sw;
	wxChar m_swb;
	wxChar m_script;
	wxChar m_intvar;
	wxChar m_listvar;
	int m_swdelay;
	bool m_ansilog;
	bool m_htmllog;
	bool m_logall;
	bool m_localecho;
	bool m_triggerecho;
	wxString *m_logfile;
	bool m_autoconnect;
	int m_acdelay;
	bool m_usemccp;
	bool m_usemsp;
	bool m_usemxp;
	bool m_useatcp;
	bool m_useatcp2;
	bool m_usemsdp;
	bool m_useaard;
	bool m_usewrap;
	bool m_autowrap;
	bool m_utf8;
	
	bool m_iacgeor;
	bool m_naws;

	bool m_raw;
	bool m_events;
	bool m_connect;
	bool m_precv;
	bool m_disconnect;
	bool m_telnetdata;
	bool m_msdpdata;
	bool m_gmcpdata;
	vector<wxString> m_gmcpmodules;
	wxString m_eventfile;

	wxString *m_clientcol;
	wxString *m_echocol;

	//wxWindow *m_parent;
	MudMainFrame *m_parent;
	wxFontEncoding m_curencoding;
	wxFileName m_workdir;
	wxFileName m_profiledir;
	wxFileName m_scriptdir;
	wxFileName m_logdir;
	wxFileName m_packagedir;
	wxFileName m_databasedir;
	wxFileName m_sounddir;
	wxFileName m_luadir;
	wxFileName m_imagesdir;
};


class RegExp
{
public:
	RegExp();
	RegExp(wxString pattern);
	~RegExp();
	bool Match(wxString match, bool bo=true, bool multi=false);
	int GetMatchStart() {return m_start;}
	int GetMatchEnd() {return m_end;}
	int GetMatchLen() {return m_end-m_start;}
	int GetNumCaptured() {return m_r-1;}
	void SubMatches();
	wxString GetPattern() {return m_pattern;}
	void SetPattern(wxString s) {m_pattern = s;}
	wxString GetMatch(int idx);
	bool IsPrecompiled() {return m_precompiled;}
	void SetPrecompiled(bool b) {m_precompiled=b;}
private:
	pcre* m_re;
	pcre_extra* m_prextra;
	const char* m_error;
	int m_erroffset;
	int m_r;
	int m_ovector[OVECCOUNT];
	int m_start, m_end;
	wxString m_pattern;
	wxString m_match;
	pcre* Compile();
	pcre* CompileMulti();
	int Exec();
	int ExecMulti();
	bool m_precompiled;
	std::vector<wxString> m_matches;
};
#endif
