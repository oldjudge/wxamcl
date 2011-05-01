#ifndef amcMXP_H
#define amcMXP_H

#define MXP_TAG_OPEN 0
#define MXP_TAG_CLOSED 1
#define MXP_TEXT 2
#define MXP_ELEMENT_START 3
#define MXP_ELEMENT_ACTION 4
#define MXP_ELEMENT 5
#define MXP_COMMENT 6
#define MXP_ESC 7
#define MXP_TEXTINTAG 8
#define MXP_ENDTAG 9
#define MXP_IAC 10
#define MXP_ESCINTEXTTAG 11
#define MXP_MISC 16

#define MXP_MODE_OPEN 0
#define MXP_MODE_SECURE 1
#define MXP_MODE_LOCKED 2
#define MXP_MODE_RESET 3
#define MXP_MODE_TEMPSECURE 4
#define MXP_MODE_LOCKOPEN 5
#define MXP_MODE_LOCKSECURE 6
#define MXP_MODE_LOCKLOCKED 7

class amcMXP
{
public:
	amcMXP(MudWindow *mw);
	~amcMXP();
	bool Parse(wxString s);
	//bool ParseElement(wxString s, size_t *pos);
	bool ParseElementRex(wxString s, size_t *pos);
	bool ParseElementInternals(wxString s);
	bool ParseTag(class amcMXPTag *t, int elnum);
	bool ParseSingleTag(class amcMXPTag *t);
	bool ParseOpenTag(class amcMXPTag *t);
	bool ParseEntity(wxString s);
	bool ParseEntityRex(wxString s, size_t *pos);
	void ReplaceEntities(wxString* s);
	int FindEntity(wxString m);
	int FindElement(wxString m);
	size_t GetNumElements() {return m_elems.size();}
	size_t GetNumEntities() {return m_entities.size();}
	vector<wxString> SplitString(wxString c, wxString s);
	map<wxString, wxColour> GetMXPColorMap() {return m_mxpcolor;}
private:
	void SetColors();
	map<wxString, wxColour> m_mxpcolor;
	static int m_parsestate;
	int m_mxpmode;
	bool m_tagopen;
	vector<class amcMXPElement> m_elems;
	vector<class amcMXPEntity> m_entities;
	MudWindow* m_parent;
};

class amcMXPEntity
{
public:
	amcMXPEntity();
	~amcMXPEntity();
	void SetName(wxString k) {m_name = k;}
	void SetValue(wxString k) {m_value = k;}
	wxString GetName() {return m_name;}
	wxString GetValue() {return m_value;}
private:
	wxString m_name;
	wxString m_value;
	bool m_publish;
	bool m_delete;
	bool m_add;
	bool m_remove;
};

class amcMXPTag
{
public:
	amcMXPTag();
	~amcMXPTag();
	amcMXPTag& operator=(const amcMXPTag& A);
	wxString GetTag() {return m_tag;}
	wxString GetText() {return m_text;}
	wxString GetStrippedText();
	wxString GetEndTag() {return m_endtag;}
	wxColour GetFCol() {return m_fore;}
	wxColour GetBCol() {return m_back;}
	void AppendTag(wxString s) {m_tag.Append(s);}
	void AppendText(wxString s) {m_text.Append(s);}
	void AppendEndTag(wxString s) {m_endtag.Append(s);}
	void SetEndTag(wxString s) {m_endtag = s;}
	void SetTag(wxString s) {m_tag = s;}
	void SetText(wxString s) {m_text = s;}
	void SetFCol(wxColour c) {m_fore=c;}
	void SetBCol(wxColour c) {m_back=c;}
	void ReplaceEntitys();
	void FindParams();
	void Reset();
	bool IsEmpty();
	bool IsMXPTag();
	bool IsOpenTag();
private:
	wxString m_tag;
	wxString m_endtag;
	wxString m_text;
	vector<wxString> m_param;
	wxColour m_fore;
	wxColour m_back;
	int m_fontattr;
	int m_fontsize;
	wxString m_fontname;
};

class amcMXPElement
{
public:
	amcMXPElement();
	~amcMXPElement();
	amcMXPTag *GetTag() {return &m_mxptag;}
	void AppendName(wxString s) {m_name.Append(s);}
	void AppendAction(wxString s) {m_action.Append(s);}
	void AppendProperty(wxString s) {m_properties.Append(s);}
	void AppendAtt(wxString s) {m_att.Append(s);}
	void AppendTag(wxString s) {m_tag.Append(s);}
	void AppendFlag(wxString s) {m_flag.Append(s);}
	void SetVarName(wxString s) {m_varname = s;}
	void SetHint(wxString s) {m_hint = s;}
	void SetRoomFlag(bool b) {m_isroomflag=b;}
	void SetPromptFlag(bool b) {m_ispromptflag=b;}
	void SetEmptyFlag(bool b) {m_empty=b;}
	void SetVarFlag(bool b) {m_issetvar=b;}
	void SetSendTag(bool b) {m_sendtag=b;}
	void SetAttFlag(bool b) {m_boatt=b;}
	void SetPromptSend(bool b) {m_sendprompt=b;}
	void SetColor(bool b) {m_bocolor=b;}
	wxString GetName() {return m_name;}
	wxString GetFlag() {return m_flag;}
	wxString GetAction() {return m_action;}
	wxString GetVarName() {return m_varname;}
	wxString GetHint() {return m_hint;}
	bool HasAttributes() {return m_boatt;}
	bool HasRoomFlag() {return m_isroomflag;}
	bool HasPromptFlag() {return m_ispromptflag;}
	bool HasSetVarFlag() {return m_issetvar;}
	bool IsSendTag() {return m_sendtag;}
	bool IsSendPrompt() {return m_sendprompt;}
	bool IsEmptyTag() {return m_empty;}
	bool HasColor() {return m_bocolor;}
	vector<wxString> *GetSendCommands() {return &m_sendcommands;}
	vector<wxString> *GetLabels() {return &m_labels;}
	vector<wxString> *GetAttributes() {return &m_attributes;}
	wxString GetAttr(int idx) {return m_attributes.at(idx);}
	void BuildMXPSendCommands();
	void BuildAttributes();
	void Clear();
private:
	wxString m_name;
	wxString m_action;
	wxString m_properties;
	wxString m_att;
	wxString m_flag;
	wxString m_tag;
	wxString m_hint;
	wxString m_varname;
	bool m_empty;
	bool m_delete;
	bool m_open;
	bool m_isroomflag;
	bool m_ispromptflag;
	bool m_sendprompt;
	bool m_issetvar;
	bool m_sendtag;
	bool m_boatt;
	bool m_bocolor;
	amcMXPTag m_mxptag;
	vector<wxString> m_attributes;
	vector<wxString> m_sendcommands;
	vector<wxString> m_labels;
};

#endif