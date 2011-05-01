#ifndef amcHotkey_H
#define amcHotkey_H
//! Class representing a hotkey (a macro)
/*!
	this class implements hotkeys for the mudclient
*/

class amcHotkey
{
public:
	amcHotkey(); //!< standard constructor 
	amcHotkey(long keycode, int mods, wxString action, wxString name, wxString group = wxT("default"), bool on=true); //!< create a real alias constructor
	~amcHotkey(); //!< destructor
	friend bool operator<(const amcHotkey& A, const amcHotkey& B) {return A.m_name<B.m_name;}
	friend bool operator>(const amcHotkey& A, const amcHotkey& B) {return A.m_name>B.m_name;}
	bool operator==(const wxString& S) {return m_name==S;}
	bool operator==(const amcHotkey& A) {return m_name==A.m_name;}
	friend bool operator==(const wxString& S, const amcHotkey& A) {return S==A.m_name;}
	friend bool operator==(const amcHotkey& A, const wxString& S) {return S==A.m_name;}
	friend bool operator==(const amcHotkey& A, const amcHotkey& B) {return A.m_name==B.m_name;}
	long GetHotkey() {return m_hotkey;} //!< get the keycode
	int GetModifier() {return m_mods;} //!< get modifiers
	wxString GetAction() {return m_action;} //!< get the plain action
	wxString GetGroup() {return m_group;} //!< get the group
	wxString GetName() {return m_name;}//!< get the name
	wxString GetKeyName();
	wxString GetModName();
	bool IsActive() {return m_on;} //!< is the hotkey active
	void SetHotkey(long k) {m_hotkey=k;} //!< Set the definition
	void SetMods(int m) {m_mods=m;}//!< Set the key modifiers
	void SetAction(wxString s) {m_action=s;} //!< set the action to perform
	void SetActive(bool b) {m_on=b;} //!< set active status
	void SetGroup(wxString s); //!< set the group
	void SetName(wxString s) {m_name=s;} //!<set name of hotkey
	int GetIndex() {return m_idx;}
	void SetIndex(int i) {m_idx=i;}
	//wxString BuildAction(); //!< replace all vars
	static std::vector<wxString> * GetHotkeyGroups() {return &m_hgroup;} //!< get all hotkey groups as pointer
private:
	MudMainFrame *m_parent; //!< pointer to parent window
	long m_hotkey; //!< keycode
	int m_mods; //!< alt ctrl shift
	wxString m_action; //!< action to perform
	wxString m_group; //!< group the hotkey belongs to
	bool m_on; //!< hotkey active?
	wxString m_name; //!< name of hotkey
	int m_idx;//!< internal index
	static std::vector<wxString> m_hgroup; //!< all the hotkey groups static
};

typedef std::vector<class amcHotkey>::iterator hk_it;

#endif
