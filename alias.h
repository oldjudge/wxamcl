#ifndef amcAlias_H
#define amcAlias_H

//! Class representing an alias
/*!
	this class implements (regexp, pcre7.8) alias for the mudclient
*/

class amcAlias
{
public:
	amcAlias(); //!< standard constructor 
	amcAlias(wxString alias, wxString action, wxString group = "default", bool on=true); //!< create a real alias constructor
	~amcAlias(); //!< destructor
	friend bool operator<(const amcAlias& A, const amcAlias& B) {return A.m_alias<B.m_alias;}
	friend bool operator>(const amcAlias& A, const amcAlias& B) {return A.m_alias>B.m_alias;}
	bool operator==(const wxString& S) {return m_alias==S;}
	bool operator==(const amcAlias& A) {return m_alias==A.m_alias;}
	friend bool operator==(const wxString& S, const amcAlias& A) {return S==A.m_alias;}
	friend bool operator==(const amcAlias& A, const wxString& S) {return S==A.m_alias;}
	friend bool operator==(const amcAlias& A, const amcAlias& B) {return A.m_alias==B.m_alias;}
	bool Match(wxString match); //!< see if we have a match
	wxString GetAlias() {return m_alias;} //!< get the alias definition
	wxString GetName(); //!< get alias without ^ and $
	wxString GetAction() {return m_action;} //!< get the plain action
	wxString GetGroup() {return m_group;} //!< get the group
	bool IsActive() {return m_on;} //!< is the alias active
	void SetAlias(wxString s) {m_alias=s;} //!< Set the definition
	void SetAction(wxString s) {m_action=s;} //!< set the action to perform
	void SetActive(bool b) {m_on=b;} //!< set active status
	void SetGroup(wxString s); //!< set the group
	void SetIndex(int i) {m_idx=i;}//!< set the index for listctrl use only
	int GetIndex() {return m_idx;}//!< get index
	wxString BuildAction(); //!< replace all vars
	static std::vector<wxString> * GetAliasGroups() {return &m_algroup;} //!< get all alias groups as pointer
private:
	MudMainFrame *m_parent; //!< pointer to parent window
	wxString m_alias; //!< definition, regexp style
	wxString m_action; //!< action to perform
	wxString m_group; //!< group the alias belongs to
	bool m_on; //<! alias active?
	class RegExp m_rexp; //!< regexp class fpr matching
	wxString m_match; //!< pattern to match for regexp
	int m_idx;//!< internal index
	static std::vector<wxString> m_algroup; //!< all the alias groups static
};

typedef std::vector<class amcAlias>::iterator al_it;
#endif
