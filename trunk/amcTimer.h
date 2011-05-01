#ifndef amcTimer_H
#define amcTimer_H

class amcTimer : public wxTimer
{
public:
	amcTimer(void);
	amcTimer(wxString name, wxString action, wxString group = wxT("default"), float i = 1.0, int r = -1, bool s = true);
	amcTimer(const amcTimer& a);
	amcTimer& operator=(const amcTimer& a);
	friend bool operator<(const amcTimer& A, const amcTimer& B) {return A.m_name<B.m_name;}
	friend bool operator>(const amcTimer& A, const amcTimer& B) {return A.m_name>B.m_name;}
	bool operator==(const wxString& S) {return m_name==S;}
	bool operator==(const amcTimer& A) {return m_name==A.m_name;}
	friend bool operator==(const wxString& S, const amcTimer& A) {return S==A.m_name;}
	friend bool operator==(const amcTimer& A, const wxString& S) {return S==A.m_name;}
	friend bool operator==(const amcTimer& A, const amcTimer& B) {return A.m_name==B.m_name;}
	~amcTimer(void);
	void SetAction(const wxString& action) {this->m_action = action;}
	void SetGroup(const wxString& group);
	void SetIdx(const int& idx) {this->m_idx = idx;}
	void SetInterval(const float& interval) {this->m_interval = (int)(interval * 1000);}
	void SetName(const wxString& name) {this->m_name = name;}
	void SetActive(const bool& on) {this->m_on = on;}
	void SetParent(MudMainFrame* parent) {this->m_parent = parent;}
	void SetRepeat(const int& repeat) {this->m_repeat = repeat;}
	const wxString& GetAction() const {return m_action;}
	const wxString& GetGroup() const {return m_group;}
	const int& GetIdx() const {return m_idx;}
	const int& GetInterval() const {return m_interval;}
	float GetFInterval() {return (float)m_interval/1000;}
	const wxString& GetName() const {return m_name;}
	const bool& IsActive() const {return m_on;}
	const MudMainFrame* GetParent() const {return m_parent;}
	void SetCurrepeat(const int& currepeat) {this->m_currepeat = currepeat;}
	const int& GetCurrepeat() const {return m_currepeat;}
	const int& GetRepeat() const {return m_repeat;}
	const bool& GetShow() const {return m_show;}
	void SetShow(const bool& b) {this->m_show = b;}
	void Run();
	static std::vector<wxString> * GetTimerGroups() {return &m_tgroup;} //!< get all timer groups as pointer
private:
	MudMainFrame* m_parent;
	wxString m_name;
	wxString m_action;
	wxString m_group;
	bool m_on;
	int m_repeat;
	int m_currepeat;
	int m_interval;
	int m_idx;
	bool m_show;
	static std::vector<wxString> m_tgroup; //!< all the timer groups static
	void Notify();
};

typedef std::vector<class amcTimer>::iterator t_it;
#endif
