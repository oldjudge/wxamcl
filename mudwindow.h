/*! \file mudwindow.h
	\brief header file for mudwindow.cpp
*/

#ifndef MudWindow_H
#define MudWindow_H
#include "ansiline.h"

/*! \class MudWindow
	\brief class representing an output window.
	
	Window to output incoming mud text (ansi), used for all windows displaying text 
*/
class MudWindow : public wxWindow
{
public:
	DECLARE_DYNAMIC_CLASS(MudWindow)
	MudWindow();
	MudWindow(wxFrame *parent);
	MudWindow(wxFrame *parent, wxString name, int fontsize);
	~MudWindow();
	//Getters
	wxColour GetAnsiColor(int index) {return m_colansi[index];}
	wxColour GetColour(int idx) {return m_colansi[idx];}
	wxColour GetBackCol() {return m_background;}
	bool UseAnsi() {return m_useansi;}
	unsigned int GetWrap() {return m_wrap;}
	bool UseTimeStamps() {return m_timestamps;}
	bool UseMilliSeconds() {return m_milliseconds;}
	bool LockPrompt() {return m_boprompt;}
	wxString GetPromptRegExp();
	bool GagPrompt() {return m_gagprompt;}
	bool UseClickURLs() {return m_bourl;}
	const bool& IsConnected() const {return m_connected;}
	bool IsLogging() {return m_log;}
	bool IsAnsiLogging() {return m_logansi;}
	bool IsDateLogging() {return m_logdate;}
	wxFile *GetTextLog() {return m_tlog;}
	wxFile *GetHtmlLog() {return m_htmllog;}
	bool IsHtmlLogging() {return m_bohtml;}
	bool GetInclude() {return m_include;}
	wxUint64 GetMaxLines() {return m_maxlines;}
	bool GetPW() {return m_password;}
	unsigned long GetStartLine() {return m_start;}
	unsigned long GetEndLine() {return m_end;}
	bool GetScroll() {return m_noscroll;}
	bool GetFirstCaptured() {return m_firstlinecaptured;}
	bool GetLastCaptured() {return m_lastcaptured;}
	class Decompressor* GetDecompressor() {return m_dc;}
	class amcLua* GetLState() {return m_L;}
	wxDateTime GetConnectionDT() {return m_dtconnected;}
	bool IsMCCPActive() {return m_mccp2;}
	bool IsMXPActive() {return m_mxp;}
	bool IsMSPActive() {return m_msp;}
	bool IsGMCPActive() {return m_gmcp;}
	bool IsMSDPActive() {return m_msdp;}
	wxIPV4address *GetIPAddr() {return &m_addr;}
	class amcMXP* GetMXPParser() {return m_MXP;}
	bool GetFocusOnInput() {return m_focusoninput;}
	wxSocketClient* GetSock() {return m_sock;}
	//Setters
	void SetColour(int idx, wxColour c) {m_colansi[idx] = c;}
	void SetBackgroundCol(wxColour c) {m_background=c;}
	void SetCustomColour(unsigned long col) {m_colansi[18].Set(col);}
	void SetAnsi(bool b) {m_useansi=b;}
	void SetWrap(unsigned int i) {m_wrap=i;}
	void SetTimeStamps(bool b) {m_timestamps=b;}
	void SetMilliSeconds(bool b) {m_milliseconds=b;}
	void SetLockPrompt(bool b) {m_boprompt=b;}
	void SetPromptRegExp(wxString s);
	void SetGagPrompt(bool b) {m_gagprompt=b;}
	void SetClickURLs(bool b) {m_bourl=b;}
	void SetMCCP2(bool b) {m_mccp2 = b;}
	void SetMXP(bool b) {m_mxp = b;}
	void SetMSP(bool b) {m_msp = b;}
	void SetMSDP(bool b) {m_msdp = b;}
	void SetLogging(bool b) {m_log=b;}
	void SetAnsiLogging(bool b) {m_logansi=b;}
	void SetDateLogging(bool b) {m_logdate=b;}
	void SetTextLog(wxFile *f) {m_tlog = f;}
	void SetHtmlLog(wxFile *f) {m_htmllog = f;}
	void SetHtmlLogging(bool b) {m_bohtml=b;}
	void SetInclude(bool b) {m_include=b;}
	void SetMaxLines(wxUint64 x) {m_maxlines=x;}
	void SetPW(bool b) {m_password = b;}
	void SetScroll(bool b) {m_noscroll=b;}
	void SetFirstCaptured(bool b) {m_firstlinecaptured=b;}
	void SetLastCaptured(bool b) {m_lastcaptured=b;}
	void SetConnectionDT() {m_dtconnected = wxDateTime::UNow();}
	void SetFocusOnInput(bool b) {m_focusoninput=b;}
	void SetSelectedStart(long l) {m_selline=l;}
	void SetSelectedEnd(long l) {m_sellineend=l;}

	//socket functions
	void MyConnect(wxIPV4address addr);
	void Write(wxString command);
	void Write8Bit(wxString command);
	void Close();
	
	//functions to parse the mud packets
	void ParseBuffer(char *cBuffer);
	void ParseNBuffer(char* cBuffer, bool b=true);
	void ParseUTF8Buffer(wxString buffer);
	void ParseLine(wxString *sLine);
	void ParseBufferMXP(char *Buffer);
	void CheckTrigger(int linenr, bool multi=false);
	void GetLineIndices(int *start, int *end) {*start=m_indexstart; *end=m_indexend;}
	void RedirectWindow();
	int GetParseState() {return m_parsestate;}
	void SetParseState(int i) {m_parsestate=i;}
	void ParseMSDP(wxString s);
	//ouput/color/font functions
	void SetDefaultColors();
	void Msg(wxString msg, int fcol=17, int bcol=0);
	wxString Out(wxString s) {return "\x1b[56m"+s+"\x1b[0m\r\n";}
	long ParseHexColor(wxString s);
	wxString FindPrevAnsi(wxString ansi, int idx);
	wxFont* GetFont() {return m_font;}
	void SetNFont(wxFont* f) {delete m_font;m_font = new wxFont(*f);}
	void SetUFont(wxFont* f) {delete m_ufont;m_ufont = new wxFont(*f);m_ufont->SetUnderlined(true);}
	void SetIFont(wxFont* f) {delete m_ifont;m_ifont = new wxFont(*f);m_ifont->SetStyle(wxFONTSTYLE_ITALIC);}
	map<wxString, wxString> GetColCodes() {return m_colcodes;}
	map<wxString, int> GetBCol() {return m_bcols;}
	wxString GetSelectedText();
	wxString GetSelectedAnsiText();
	bool IsTextSelected() {if (m_selline!=-1) return true; else return false;}
	void SwitchColor(long l, int offset, AnsiLineElement *ale);
	wxColour GetCurAnsiColour()  {return m_curansicolor; }
	void SetCurAnsiColour(wxColour c) {m_curansicolor = c;}
	//Logging functions
	void DeleteHtmlLog() {delete m_htmllog;m_htmllog=NULL;}
	void SendLineToLog(wxUint64 i);
	void WriteHtmlHeader(wxFile *f);
	void WriteRaw(char* buffer, int len, bool inc=true);
	
	//Scrolling/line buffer functions
	wxUint64 GetScrollPage();
	wxUint64 AdjustScrollPage();
	void SetScrollPage();
	std::deque<class AnsiLine> * GetLines() {return &m_vmudlines;}
	void SetLineBuffer(deque<class AnsiLine> * v);
	vector<class AnsiLineElement> * GetLineStyle(int nr) {return m_vmudlines.at(nr).GetStyle();}
	void ClearLines();
	void AddLine(AnsiLine al);
	
	//Key events forwarding	
	void SetKEvtForwarded(bool b) {m_kevtforwarded = true;}
	bool GetKEvtForwarded() {return m_kevtforwarded;}
	
	//Getters for capturing text to different windows
	vector<long> * GetNumCapture() {return &m_capture;}
	vector<wxString> * GetWinCapture() {return &m_capwin;}
	vector<bool> * GetGagCapture() {return &m_capgag;}
	map<wxString, bool> *GetCapWindow() {return &m_capwindow;}
	//GMCP
	vector<wxString> * GetGMCPModules() {return &m_gmcpmods;}
	void SetDebugGMCP(bool b) {m_debuggmcp=b;}
	bool GetDebugGMCP() {return m_debuggmcp;}
	//Static functions
	static void SetNewLine(bool bo) {m_bonewline=bo;}
	static bool GetNewLine() {return m_bonewline;}
	//public variables
	wxUint64 m_curline;
	wxUint64 m_scrollrange;
private:
	class MudMainFrame *m_parent;
	class amcLua *m_L;
	wxSocketClient *m_sock;
	wxIPV4address m_addr;
	bool m_connected;
	wxDateTime m_dtconnected;
	deque<class AnsiLine> m_vmudlines;
	//class GlobalOptions *m_gopt;
	class Decompressor *m_dc;
	class RegExp *m_url;
	class RegExp *m_ansicode;
	class RegExp *m_prompt;
	class amcMXP *m_MXP;
	wxBitmap m_drawbmp;
	wxToolTip* m_tt;
	bool m_boprompt;
	bool m_gagprompt;

	bool m_noscroll;

	wxColour m_colansi[20];
	wxColour m_xterm[300];
	wxColour m_background;
	std::map<wxString, int> m_bcols;
	std::map<wxString, wxString> m_colcodes;
	wxFont *m_font, *m_ufont, *m_ifont;
	static bool m_bonewline;
	static bool m_bocolcode;
	static bool m_atcpdata;//for atcp middle of subnegotiation
	wxString m_atcpstring;
	wxString m_charset;
	wxString *m_oldcolor;

	wxUint64 m_maxlines;
	bool m_useansi;/*!< use ansi colors? */
	bool m_timestamps;/*!< show a timestamp before line ? */
	bool m_milliseconds;/*!< show milliseconds in timestamp? */
	bool m_password;//hide text
	bool m_mccp2;//compression active
	bool m_mccpneg;//compresson negotiated?
	size_t m_oddmccp2;//helper for mccp2
	bool m_mxp;//mxp active?
	bool m_msp;//msp active?
	bool m_msdp;//msdp active?
	unsigned int m_wrap;//linewrap column
	bool m_selected;//text selected with mouse?
	bool m_linkclicked;
	bool m_trigger;/*!< check triggers for this window? */
	bool m_atcp;/*!< atcp negotiated? */
	bool m_atcp2;/*!< atcp2 = gmcp negotiated? */
	bool m_gmcp;/*!< are we using gmcp? */
	bool m_debuggmcp;/*!<write gmcp messages to file */
	std::vector<wxString> m_gmcpmods;
	wxPoint m_selstart;
	wxPoint m_selend;
	long m_selline, m_sellineend;
	int m_indexstart, m_indexend;//mxphelper for sendtags
	unsigned long m_start, m_end;//lines visible on screen
	int m_wheelrot;
	bool m_kevtforwarded;
	bool m_log;//logging on?
	bool m_logansi;//ansi codes in log?
	bool m_logdate;//timestamps in log
	bool m_bohtml;//Html logging
	bool m_include;//include the scrollbuffer in log
	bool m_focusoninput;//set focus in inputline;
	int m_parsestate;//state machine parsing state
	//vectors for capturewin
	std::vector<long> m_capture;
	std::vector<wxString> m_capwin;
	std::vector<bool> m_capgag;
	
	//map for capstart, capend
	std::map<wxString, bool> m_capwindow;
	
	bool m_firstlinecaptured;
	bool m_lastcaptured;
	wxString m_logfile;
	wxFile* m_tlog;
	wxFile* m_htmllog;
	//colorcodes for html logging
	std::vector<wxString> m_css;
	//bool m_botelnetparsed;
	bool m_bourl;/*!< clickable URLs? */
	//for mxp commands menus
	std::vector<wxString> m_mxpcommand;
	//current ansicolor
	wxColour m_curansicolor;
	wxTimer m_rc;

	char m_cBuffer[30001];
	//private Functions
	size_t ParseTelnet(wxString *sLine, size_t pos);
	size_t ParseMSP(wxString *sLine, size_t pos);
	size_t SetStyleColors(size_t pos, wxString *sLine, AnsiLineElement *style, AnsiLineElement *laststyle);
	int GetColor(size_t *pos, wxString *sLine, bool boFirst, wxByte *bFontAttr, wxByte *bBackColor);
	wxCoord DrawAnsi(wxBufferedPaintDC *dc, wxCoord starty, int lnr, wxCoord char_len, wxCoord char_height);
	wxCoord DrawMultiAnsi(wxBufferedPaintDC *dc, wxCoord starty, int lnr, wxCoord char_len, wxCoord char_height, size_t sublines);
	wxCoord DrawStyle(wxBufferedPaintDC *dc, unsigned int lnr, int snr, wxCoord startx, wxCoord starty, wxCoord char_len);
	unsigned long CalcLine(wxPoint click);
	void SetCssClasses();
	
	//Event handlers
	void OnEraseBackground(wxEraseEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnScroll(wxScrollWinEvent& event);
	void OnSocketEvent(wxSocketEvent& event);
	void OnLeftDown(wxMouseEvent& event);
	void OnRightUp(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	void OnLeftUp(wxMouseEvent& event);
	void OnMouseWheel(wxMouseEvent& event);
	void OnChar(wxKeyEvent& event);
	void OnContextMenu(wxContextMenuEvent& event);
	void OnOutputFont(wxCommandEvent& event);
	void OnTimeStamps(wxCommandEvent& event);
	void OnMakeAction(wxCommandEvent& event);
	void OnMxpMenu(wxCommandEvent& event);
	void OnMxpPromptMenu(wxCommandEvent& event);
	void OnAutoReconnect(wxTimerEvent& event);
	DECLARE_EVENT_TABLE()
};
#endif
