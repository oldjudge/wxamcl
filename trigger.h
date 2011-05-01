#ifndef amcTrigger_H
#define amcTrigger_H


//Class for actions
class Trigger
{
public:
	Trigger();
	Trigger(wxString pattern, wxString action, wxString label, wxString cl = wxT("default"), wxUint32 prior = 50, bool on = true, int m_colmatch = -1, int lines = 1, bool show = true);
	~Trigger();
	bool Match(wxString match);
	wxString BuildAction();
	wxString GetAction() {return m_action;}
	void SetAction(wxString s) {m_action=s;}
	bool operator<(const Trigger& A) {return m_priority<A.m_priority;}
	bool operator>(const Trigger& A) {return m_priority>A.m_priority;}
	friend bool operator<(const Trigger& A, const Trigger& B) {return A.m_priority<B.m_priority;}
	friend bool operator>(const Trigger& A, const Trigger& B) {return A.m_priority>B.m_priority;}
	bool operator==(const Trigger& A) {return m_label==A.m_label;}
	bool operator==(const wxString& S) {return m_label==S;}
	friend bool operator==(const Trigger& A, const Trigger& B) {return A.m_label==B.m_label;}
	friend bool operator==(const Trigger& A, const wxString& S) {return A.m_label==S;}
	friend bool operator==(const wxString& S, const Trigger& A) {return S==A.m_label;}
	//bool Cmp(const Trigger& A) {return m_priority<A.m_priority;}
	wxString GetLabel() {return m_label;}
	void SetLabel(wxString s) {m_label=s;}
	wxString GetPattern() {return m_pattern;}
	void SetPattern(wxString s) {m_pattern=s;}
	bool IsActive() {return m_on;}
	void SetActive(bool b) {m_on=b;}
	wxString GetClass() {return m_class;}
	void SetClass(wxString s);
	wxUint32 GetPriority() {return m_priority;}
	void SetPriority(wxUint32 p) {m_priority=p;}
	long GetMatchCount() {return m_matchcount;}
	void SetMatchCount(long l) {m_matchcount=l;}
	int GetColMatch() {return m_colmatch;}
	void SetColMatch(int i) {m_colmatch=i;}
	void SetLines(int i) {m_lines=m_curlines=i;}
	int GetLines() {return m_lines;}
	const bool& GetShow() const {return m_show;}
	void SetShow(const bool& b) {m_show = b;}
	const bool& GetSendScript() const {return m_sendtoscript;}
	void SetSendScript(const bool& b) {m_sendtoscript = b;}
	int MultiLine();
	bool IsMultiLine() {return m_lines > 1 ? true : false;}
	static std::vector<wxString> * GetTriggerClasses() {return &m_trclass;}
private:
	MudMainFrame *m_parent;
	wxString m_pattern;
	wxString m_action;
	wxUint32 m_priority;
	wxString m_label;
	wxString m_class;
	class RegExp m_rexp;
	bool m_on;
	wxString m_match;
	long m_matchcount;
	int m_colmatch;
	int m_lines;
	int m_curlines;
	bool m_show;
	bool m_sendtoscript;
	bool m_gagline;
	static std::vector<wxString> m_trclass;
	wxString ParsePattern();
};

typedef std::vector<class Trigger>::iterator tr_it;


#endif
