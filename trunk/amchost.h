//#pragma once
#ifndef amc_host_H
#define amc_host_H

class amchost
{
public:
	amchost(void);
	~amchost(void);
	void SetCharName(wxString s) {m_charname=s;}
	wxString GetCharName() {return m_charname;}
	void SetPwd(wxString s) {m_password=s;}
	wxString GetPwd() {return m_password;}
	void SetMudName(wxString s) {m_mudname=s;}
	wxString GetMudName() {return m_mudname;}
	void SetHostName(wxString s) {m_hostname=s;}
	void SetIPHost() {m_ip.Hostname(m_hostname);m_ipaddr=m_ip.IPAddress();}
	wxString GetHostName() {return m_hostname;}
	void SetPort(long p) {m_port=p;m_ip.Service(p);}
	wxString GetPort() {return wxString::Format("%ld", m_port);}
	void SetProfileFile(wxString s) {m_profile.Assign(s);}
	wxString GetProfileFile() {return m_profile.GetFullPath();}
	wxString GetProfileName() {return m_profile.GetFullName();}
	wxFileName GetProfileFName() {return m_profile;}
	wxString GetIPAddress() {return m_ip.IPAddress();}
	wxIPV4address GetIP4() {return m_ip;}
	void SetIPAddr(wxString s) {m_ipaddr=s;}
	wxString GetIPString() {return m_ipaddr;}
private:
	wxString m_hostname;
	wxString m_mudname;
	wxString m_charname;
	wxString m_password;
	long m_port;
	wxIPV4address m_ip;
	wxFileName m_profile;
	wxString m_ipaddr;
};

typedef std::vector<class amchost>::iterator host_it;

#endif
