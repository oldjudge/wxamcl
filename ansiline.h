#ifndef Ansi_H
#define Ansi_H
class AnsiLineElement
{
	
public:
	AnsiLineElement();
	AnsiLineElement(const AnsiLineElement& ale);
	AnsiLineElement(wxString text, int fcol, int bcol);
	~AnsiLineElement();

	void SetFCol(int index, wxColour col);
	void SetBCol(int index, wxColour col);
	void SetText(wxString text);
	void SetURLText(wxString s) {m_url=s;}
	void SetFontStyle(wxByte s) {m_bfontstyle=s;}
	void SetURL(bool url) {m_bourl=url;}
	void SetMXPSend(bool send) {m_mxpsend=send;}
	void SetPromptSend(bool send) {m_promptsend=send;}
	void AddMXPCommand(wxString s) {m_mxpcommand.push_back(s);}
	void AddMXPLabel(wxString s) {m_mxplabel.push_back(s);}
	void SetHint(wxString s) {m_hint=s;}
	wxString GetText() {return m_text;}
	wxString GetURLText() {return m_url;}
	wxColour GetFCol() {return m_fcol;}
	wxUint16 GetFColIndex() {return m_fcolindex;}
	wxColour GetBCol() {return m_bcol;}
	wxUint16 GetBColIndex() {return m_bcolindex;}
	wxByte GetFontStyle() {return m_bfontstyle;}
	size_t GetLen() {return m_len;}
	bool GetURL() {return m_bourl;}
	bool GetMXPSend() {return m_mxpsend;}
	bool GetPromptSend() {return m_promptsend;}
	vector<wxString> *GetMXPCommand() {return &m_mxpcommand;}
	vector<wxString> *GetMXPLabel() {return &m_mxplabel;}
	wxString GetHint() {return m_hint;}
private:
	//wxString *m_text;
	wxString m_text;
	size_t m_len;
	wxColour m_fcol; //Foreground
	wxColour m_bcol; //Background
	wxUint16 m_fcolindex;
	wxUint16 m_bcolindex;
	wxByte m_bfontstyle;
	bool m_bourl;
	bool m_mxpsend;
	bool m_promptsend;
	vector<wxString> m_mxpcommand;
	vector<wxString> m_mxplabel;
	wxString m_hint;
	wxString m_url;
};

//WX_DECLARE_LIST(AnsiLineElement, StyleList);

class AnsiLine
{
public:
	AnsiLine();
	AnsiLine(const AnsiLine& al);
	~AnsiLine();
	std::vector<class AnsiLineElement> m_vstyle;
	size_t Freq(wxString *st, wxChar ch=ESC);
	void SetLinenumber(wxUint32 ln) {m_linenumber=ln;}
	wxUint32 GetLinenumber() {return m_linenumber;}
	void SetLineText(wxString st);
	void AssignText(wxString st);
	wxString GetLineText() {return m_linetext;}
	void SetAnsiLine(wxString s) {m_ansiline.append(s);}
	wxString GetAnsiLine() {return m_ansiline;}
	size_t GetTextLength() {return m_linetext.length();}
	void SetYPos(wxInt32 yp) {m_ypos = yp;}
	wxInt32 GetYPos() {return m_ypos;}
	void SetDateTime(wxDateTime d) {m_cdt = d;}
	wxDateTime GetDateTime() {return m_cdt;}
	wxString GetTime() {return m_cdt.FormatTime();}
	wxString GetMilliSeconds() {return wxString::Format("%03d", m_cdt.GetMillisecond());}
	bool IsTriggered() {return m_botriggered;}
	void SetTriggered(bool b) {m_botriggered = b;}
	int GetCharFColIndex(int idx);
	bool IsFull() {return m_bofull;}
	void SetFull(bool b) {m_bofull=b;}
	bool WasLogged() {return m_bologged;}
	void SetLogged(bool b) {m_bologged=b;}
	void SetGagme(bool b) {m_bogagme=b;}
	bool GetGagme() {return m_bogagme;}
	wxString GetAnsiString();
	static wxString GetAnsiFCode(int i) {return m_codes[i];}
	static wxString GetAnsiBCode(int i) {return m_bcodes[i];}
	vector<class AnsiLineElement> * GetStyle() {return &m_vstyle;}
private:
	wxUint32 m_linenumber;
	bool m_botriggered;
	bool m_bologged;
	bool m_bofull;
	bool m_bogagme;
	wxString m_linetext;
	wxString m_ansiline;
	wxInt32 m_ypos;
	wxDateTime m_cdt;
	static wxString m_codes[20];
	static wxString m_bcodes[16];

};

typedef vector<class AnsiLineElement>::iterator ale_it;
typedef deque<class AnsiLine>::iterator line_it;

#endif
