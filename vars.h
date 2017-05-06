#ifndef amcVars_H
#define amcVars_H

//! Class representing a variable
/*!
	this class implements variables for the mudclient
*/

class amcVar
{
public:
	amcVar(); //!< standard constructor 
	amcVar(wxString name, wxString content, wxString group = "default", bool on=true); //!< create a variable constructor
	~amcVar(); //!< destructor
	friend bool operator<(const amcVar& A, const amcVar& B) {return A.m_name<B.m_name;}
	friend bool operator>(const amcVar& A, const amcVar& B) {return A.m_name>B.m_name;}
	bool operator==(const wxString& S) {return m_name==S;}
	bool operator==(const amcVar& A) {return m_name==A.m_name;}
	friend bool operator==(const wxString& S, const amcVar& A) {return S==A.m_name;}
	friend bool operator==(const amcVar& A, const wxString& S) {return S==A.m_name;}
	friend bool operator==(const amcVar& A, const amcVar& B) {return A.m_name==B.m_name;}
	//bool Match(wxString match); //!< see if we have a match
	wxString GetName() {return m_name;} //!< get the var identifier
	wxString GetValue() {return m_value;} //!< get the value
	wxString GetGroup() {return m_group;} //!< get the group
	bool IsActive() {return m_on;} //!< is the var active
	void SetName(wxString s) {m_name=s;} //!< Set the definition
	void SetValue(wxString s) {m_value=s;} //!< set the content, always a wxString
	void SetActive(bool b) {m_on=b;} //!< set active status
	void SetGroup(wxString s); //!< set the group
	void SetIndex(int i) {m_idx=i;}//!< set the index for listctrl use only
	int GetIndex() {return m_idx;}//!< get index
	//wxString BuildAction(); //!< replace all vars
	static std::vector<wxString> * GetVarGroups() {return &m_vgroup;} //!< get all var groups as pointer
private:
	MudMainFrame *m_parent; //!< pointer to parent window
	wxString m_name; //!< definition
	wxString m_value; //!< content of var
	wxString m_group; //!< group the var belongs to
	bool m_on; //<! alias active?
	//class RegExp m_rexp; //!< regexp class fpr matching
	//wxString m_match; //!< pattern to match for regexp
	int m_idx;//!< internal index
	static std::vector<wxString> m_vgroup; //!< all the var groups static
};

typedef std::vector<class amcVar>::iterator v_it;

class amcDefVar : public amcVar
{
public:
	amcDefVar();
	~amcDefVar();
	amcDefVar(wxString name, wxString value);
};

typedef std::vector<class amcDefVar>::iterator dv_it;

class amcList
{
public:
	amcList(); //!< standard constructor 
	amcList(wxString name, vector<wxString> content, wxString group = "default", bool on=true); //!< create a variable constructor
	~amcList(); //!< destructor
	friend bool operator<(const amcList& A, const amcList& B) {return A.m_name<B.m_name;}
	friend bool operator>(const amcList& A, const amcList& B) {return A.m_name>B.m_name;}
	bool operator==(const wxString& S) {return m_name==S;}
	bool operator==(const amcList& A) {return m_name==A.m_name;}
	friend bool operator==(const wxString& S, const amcList& A) {return S==A.m_name;}
	friend bool operator==(const amcList& A, const wxString& S) {return S==A.m_name;}
	friend bool operator==(const amcList& A, const amcList& B) {return A.m_name==B.m_name;}
	//bool Match(wxString match); //!< see if we have a match
	wxString GetName() {return m_name;} //!< get the list identifier
	wxString GetValue();//!< get the string in a|b|c format
	wxString GetItem(int i) {return m_list.at(i);}
	int GetSize() {return m_list.size();}
	void ClearItems() {m_list.empty();}
	wxString GetGroup() {return m_group;} //!< get the group
	bool IsActive() {return m_on;} //!< is the list active
	void SetName(wxString s) {m_name=s;} //!< Set the definition
	void AddItem(wxString s) {m_list.push_back(s);} //!< add an item, always a wxString
	void SetActive(bool b) {m_on=b;} //!< set active status
	void SetGroup(wxString s); //!< set the group
	void SetIndex(int i) {m_idx=i;}//!< set the index for listctrl use only
	int GetIndex() {return m_idx;}//!< get index
	void DeleteItemAt(int idx) {m_list.erase(m_list.begin()+idx);}//!< delete item at index idx
	bool DeleteItem(wxString item);//!< delete item
	bool Contains(wxString item);//!< is item in list?
	static std::vector<wxString> * GetListGroups() {return &m_lgroup;} //!< get all var groups as pointer
private:
	MudMainFrame *m_parent; //!< pointer to parent window
	wxString m_name; //!< definition
	wxString m_value; //!< content of var
	wxString m_group; //!< group the var belongs to
	bool m_on; //<! alias active?
	std::vector<wxString> m_list; //<! single list elements
	//wxString m_match; //!< pattern to match for regexp
	int m_idx;//!< internal index
	static std::vector<wxString> m_lgroup; //!< all the list groups static
};

typedef std::vector<class amcList>::iterator li_it;
#endif
