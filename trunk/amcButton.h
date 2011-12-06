#ifndef amcButton_H
#define amcButton_H
//! Class representing a user button
/*!
	this class implements user buttons for the mudclient
*/
class amcButton 
{
public:
	amcButton(void);
	amcButton(wxAuiToolBar* tb, wxString label, wxString text, wxString action, wxString group = "default");
	amcButton(const amcButton& a);
	amcButton& operator=(const amcButton& a);
	//friend bool operator<(const amcTimer& A, const amcTimer& B) {return A.m_name<B.m_name;}
	//friend bool operator>(const amcTimer& A, const amcTimer& B) {return A.m_name>B.m_name;}
	bool operator==(const wxString& S) {return m_name==S;}
	//bool operator==(const amcTimer& A) {return m_name==A.m_name;}
	friend bool operator==(const wxString& S, const amcButton& A) {return S==A.m_name;}
	friend bool operator==(const amcButton& A, const wxString& S) {return S==A.m_name;}
	friend bool operator==(const amcButton& A, const amcButton& B) {return A.m_name==B.m_name;}
	~amcButton(void);
	void SetAction(const wxString& action) {this->m_action = action;}
	void SetGroup(const wxString& group);
	void SetId(const int& id) {this->m_id = id;}
	void SetName(const wxString& name) {this->m_name = name;}
	void SetText(const wxString& text) {this->m_text = text;}
	void SetBitmap(const wxString& bit);
	void SetActive(const bool& on) {this->m_on = on;}
	void SetParent(wxAuiToolBar* parent) {this->m_parent = parent;}
	void SetTbName(const wxString& name) {this->m_tbname = name;}
	const wxString& GetAction() const {return m_action;}
	const wxString& GetGroup() const {return m_group;}
	const wxString& GetBitmap() const {return m_bitmap;}
	const int& GetId() const {return m_id;}
	const wxString& GetName() const {return m_name;}
	const wxString& GetText() const {return m_text;}
	const wxString& GetTbName() const {return m_tbname;}
	const bool& IsActive() const {return m_on;}
	const wxAuiToolBar* GetParent() const {return m_parent;}
	const bool& GetShow() const {return m_show;}
	void SetShow(const bool& b) {this->m_show = b;}
	void SetAsSeparator(wxAuiToolBar* tb);
	void Register();
	static std::vector<wxString> * GetButtonGroups() {return &m_bgroup;} //!< get all timer groups as pointer
private:
	wxAuiToolBar* m_parent;
	MudMainFrame * m_frame;
	wxString m_name;
	wxString m_label;
	wxString m_text;
	wxString m_action;
	wxString m_group;
	wxString m_tbname;
	wxString m_bitmap;
	bool m_on;
	int m_id;
	bool m_show;
	static std::vector<wxString> m_bgroup; //!< all the timer groups static
};

typedef std::vector<class amcButton>::iterator b_it;
#endif
