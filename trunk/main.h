#ifndef MainH
#define MainH

#if !defined __WXGTK__ && !defined __WXMSW__
#define __WXGTK__
#endif
// For compilers that support precompilation, includes "wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
// Include your minimal set of headers here, or wx.h
#include <wx/wx.h>
#endif

#include <wx/event.h>
#include <wx/intl.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>
#include <wx/filesys.h>
#include <wx/fs_zip.h>
#include <wx/socket.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include <wx/tokenzr.h>
#include <wx/dcbuffer.h>
#include <wx/valtext.h>
#include <wx/valgen.h>
#include <wx/file.h>
#include <wx/filefn.h>
#include <wx/defs.h>
#include <wx/cursor.h>
#include <wx/mimetype.h>
#include <wx/aboutdlg.h>
#include <wx/textfile.h>
#include <wx/imaglist.h>
#include <wx/utils.h>
#include <wx/fontdlg.h>
#include <wx/choicdlg.h>
#include <wx/filedlg.h>
#include <wx/stdpaths.h>
#include <wx/timer.h>
#include <wx/mediactrl.h>
#include <wx/thread.h>
#include <wx/clipbrd.h>
#include <wx/treebook.h>
#include <wx/choicebk.h>
#include <wx/listbook.h>
#include <wx/docview.h>
#include <wx/cmdline.h>
#include <wx/sound.h>
#include <wx/tooltip.h>
#include <wx/tipwin.h>
#include <wx/fdrepdlg.h>
#include <wx/buffer.h>
#include <zlib.h>
#include "pcre.h"
#if defined __WXGTK__
extern "C"
{
	#include </usr/include/lua5.1/lua.h>
	#include </usr/include/lua5.1/lauxlib.h>
	#include </usr/include/lua5.1/lualib.h>
}
#endif
#if defined __WXMSW__
extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
	#include <Uxtheme.h>
}
#endif
#include "sqlite3.h"

#if defined __WXDEBUG__
#include <wx/log.h>
#endif
//#include <wx/mstream.h>
//#include <wx/zstream.h>
//#include <wx/sckstrm.h>
//#include <wx/event.h>
//#include <wx/caret.h>
//#include <wx/richtext/richtextctrl.h>
//#include <wx/gdicmn.h>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <utility>
#include <string>
#include <algorithm>

using namespace std;

#if !defined(__WXMSW__) && !defined(__WXPM__)
	#define RGB(r,g,b) ((DWORD)(((BYTE)(r)|((WORD)(g) << 8))|(((DWORD)(BYTE)(b)) << 16)))
	#define BYTE unsigned char
	#define WORD unsigned int
	#define DWORD unsigned long
	#define HIBYTE(x) ((unsigned int)(x) >> 8)
	#define LOBYTE(x) ((unsigned char)(x))
    //#include "sample.xpm"
#endif

#define ID_CONNECT 1000
#define ID_CHARCONNECT 1001
#define ID_DISCONNECT 1002
#define ID_LOADPROF 1003
#define ID_PREFS 1100
#define ID_OUTFONT 1101
#define ID_STAMPS 1102
#define ID_OUTFONTGAUGE 1103
#define ID_OBJS 1200
#define ID_INSTALL 1201
#define ID_UNINSTALL 1202
#define ID_CREATEPKG 1203
#define ID_SAVEP 1300
#define ID_EDITSCRIPT 1400
#define ID_COPY 1500
#define ID_MAKEACTION 1510
#define ID_SPLITTER 1600
#define ID_CHARENCODING 1700
#define ID_USERWINDOW 3000
#define ID_CREATEWINDOW 1602
#define ID_CREATEGAUGEWIN 1603
#define ID_CREATENOTEBOOKWINDOW 1604
#define ID_CREATETOOLBAR 1605
#define ID_TOGGLEACTIONS 1606
#define ID_USERBUTTON 2000
#define ID_MXPMENU 10000
#define ID_MXPMENUPROMPT 10200
#define SOCKET_ID 1
#define ID_INPUTCTRL 500
#define ID_PARSEINPUT 501
#define ID_PROMPT 502
#define ID_MEDIACTRL 503

//#define wxT(x) x
//wxT defines
#define CR 13
#define LF 10
#define BELL 7
#define EOS 0
#define ESC 0x1b
#define BR '['
#define AC_M 'm'
//color index defines
#define DEF_FORECOL 7
#define DEF_BACKCOL 0
#define DEF_COLORS 18

///Telnet defines
#define IAC 0xff
#define DONT 254
#define DO   253
#define WONT 252
#define WILL 251
#define SB   250
#define SE   240
#define AARD1 102
#define AARD2 103
#define TELOPT_COMPRESS  85
#define TELOPT_COMPRESS2 86
#define NAWS 31
#define CHARSET 42
#define MSP 90
#define MXP 91
#define TERMINAL_TYPE 24
#define GA 0xef
#define WILLEOR 25
#define EOR 0xf9
#define IS 0x00
#define SEND 0x01
#define REJECT 0x02
#define SUPPRESS_GO_AHEAD 0x03
#define ATCP 200
#define ATCP2 201
#define ZMP 93
#define MSSP 70
#define MSDP 69
#define MSDP_VAR 0x01
#define MSDP_VAL 0x02
#define MSDP_OPEN 0x03
#define MSDP_CLOSE 0x04
#define NEW_ENVIRON 39

enum
{
	AMC_A = 65,
	AMC_B,
	AMC_C,
	AMC_D,
	AMC_E,
	AMC_F,
	AMC_G,
	AMC_H,
	AMC_I,
	AMC_J,
	AMC_K,
	AMC_L,
	AMC_M,
	AMC_N,
	AMC_O,
	AMC_P,
	AMC_Q,
	AMC_R,
	AMC_S,
	AMC_T,
	AMC_U,
	AMC_V,
	AMC_W,
	AMC_X,
	AMC_Y,
	AMC_Z,
	AMC_F1=WXK_F1,
	AMC_F2=WXK_F2,
	AMC_F3=WXK_F3,
	AMC_F4=WXK_F4,
	AMC_F5=WXK_F5,
	AMC_F6=WXK_F6,
	AMC_F7=WXK_F7,
	AMC_F8=WXK_F8,
	AMC_F9=WXK_F9,
	AMC_F10=WXK_F10,
	AMC_F11=WXK_F11,
	AMC_F12=WXK_F12,
	AMC_MODNONE=wxMOD_NONE,
	AMC_MODALT=wxMOD_ALT,
	AMC_MODCTRL=wxMOD_CMD
};

#define OVECCOUNT 60
//wxDECLARE_EVENT(wxEVENT_CMD_PAUSE2, wxThreadEvent);

#define APP_VERSION "0.1.r48"

#include "mudwindow.h"
#include "luadefs.h"
#include "ansiline.h"
#include "decompress.h"
#include "goptions.h"
//#include "simpleconn.h"
#include "dialog_hostsimple.h"
#include "dialog_optionen.h"
#include "dialog_objekte.h"
#include "dialog_verbinden.h"
#include "dialog_tabedit.h"
#include "dialog_skript.h"
#include "dialog_sscr.h"
#include "dialog_regexp.h"
#include "dialog_package.h"
#include "trigger.h"
#include "alias.h"
#include "vars.h"
#include "hotkey.h"
#include "amcTimer.h"
#include "amchost.h"
#include "scriptedit.h"
#include "gaugewin.h"
#include "amcButton.h"
#include "amcMXP.h"
#include "amcWindow.h"
//#include "amcSqlite.h"

// Define a new application type, each program should derive a class from wxApp
class MudClientApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------
	class MudMainFrame* GetFrame() {return frame;}
	void SetFrame(class MudMainFrame* f) {frame=f;}
    class MudWindow* GetChild() {return mw;}
	void SetChild(class MudWindow* f) {mw=f;}
	// this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();
	virtual int OnExit();
private:
	class MudMainFrame *frame;
	class MudWindow *mw;//child
};

DECLARE_APP(MudClientApp)

//extern const wxEventType wxEVENT_CMD_PAUSE;
//extern const wxEventType wxEVENT_CMD_RESUME;

// Define a new frame type: this is going to be our main frame
class MudMainFrame : public wxFrame
{
public:
    // ctor(s)
    MudMainFrame(const wxString& title);
	MudMainFrame();
	~MudMainFrame();

	class MudWindow *m_child;
	class MudWindow *m_splitter;
	class InputTextCtrl *m_input;
	class wxAuiToolBar *m_toolbar;
	class wxBitmapButton *m_toggle;
	//class wxStaticText *m_prompt;
	class wxTextCtrl *m_prompt;
	//wxCheckBox *m_toggle;
	class wxMediaCtrl *m_media;
	wxAuiManager m_mgr;
	wxLocale *m_locale;
	std::vector<class Trigger> m_trigger;
	std::vector<class amcAlias> m_alias;
	std::vector<class amcHotkey> m_hotkeys;
	std::vector<class amcVar> m_vars;
	std::vector<class amcDefVar> m_defvars;
	std::vector<class amcList> m_lists;
	std::vector<class amcTimer> m_timers;
	std::vector<class amcButton> m_buttons;
    // event handlers (these functions should _not_ be virtual)
    void OnSimpleConnect(wxCommandEvent& event);
	void OnCharConnect(wxCommandEvent& event);
	void OnDisconnect(wxCommandEvent& event);
	void OnLoadProfile(wxCommandEvent& event);
    void OnPrefs(wxCommandEvent& event);
	void OnObjects(wxCommandEvent& event);
	void OnSavePerspective(wxCommandEvent& event);
	void OnInstallPackage(wxCommandEvent& event);
	void OnUninstallPackage(wxCommandEvent& event);
	void OnCreatePackage(wxCommandEvent& event);
	void OnEditScript(wxCommandEvent& event);
	void OnToggleAllTriggers(wxCommandEvent& event);
	void OnCopyClipboard(wxCommandEvent& event);
	void OnFind(wxCommandEvent& event);
	void OnFindDialog(wxFindDialogEvent& event);
	void OnAnsiCopyClipboard(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
	void OnParseInput(wxCommandEvent& event);
	void OnMenuUi(wxUpdateUIEvent& event);
	void OnShowSplitter(wxCommandEvent& event);
	void OnUserWindow(wxCommandEvent& event);
	void OnUserButton(wxCommandEvent& event);
	void OnCharEncoding(wxCommandEvent& event);
	void OnCreateCapture(wxCommandEvent& event);
	void OnCreateNb(wxCommandEvent& event);
	void OnCreateTB(wxCommandEvent& event);
	void OnCreateGaugeWindow(wxCommandEvent& event);
	//stuff
	bool UseSplitter() {return m_usesplitter;}
	void SetSplitter(bool b) {m_usesplitter=b;}
	bool LoadGlobalOptions();
	bool SaveGlobalOptions();
	bool SaveProfile(wxString s);
	bool LoadProfile(wxFileName s);
	wxString GetCurProfileName() {return m_curprofile;}
	void SetCurProfileName(wxString s) {m_curprofile = s;}
	bool SaveHosts();
	bool LoadHosts();
	bool SavePackageFile(wxFileName file, vector<wxString>*tr, vector<wxString>*al, vector<wxString>*hk, vector<wxString>*g, vector<wxString>*t, vector <wxString>*li, vector<wxString>*v, vector<wxString>*bu);
	void CreateDefVars();
	class GlobalOptions *GetGlobalOptions() {return m_gopt;}
	std::vector<class Trigger> * GetTrigger() {return &m_trigger;};
	std::vector<class amcAlias> * GetAlias() {return &m_alias;};
	std::vector<class amcHotkey> * GetHotkeys() {return &m_hotkeys;};
	std::vector<class amcVar> * GetVars() {return &m_vars;};
	std::vector<class amcDefVar> * GetDefVars() {return &m_defvars;};
	std::vector<class amcList> * GetLists() {return &m_lists;};
	std::vector<class amcTimer> * GetTimers() {return &m_timers;};
	std::vector<class amcButton> * GetButtons() {return &m_buttons;};
	std::vector<class amchost> *GetHosts() {return &m_amchost;}
	int GetCurHost() {return m_curhost;}
	std::vector<wxString> *GetPanes() {return &m_panes;}
	std::vector<wxString> *GetNbs() {return &m_nbs;}
	vector<vector<wxString> > *GetNbPanes() {return &m_nbpanes;}
	std::vector<wxString> *GetGaugePanes() {return &m_gaugepanes;}
	vector<vector<wxString> > *GetGauges() {return &m_gauges;}
	vector<wxString> *GetAmcWindows() {return &m_amcwindows;}
	map<wxString, long> GetKeys() {return m_keys;}
	int GetTriggerIndexByLabel(wxString s);
	bool TriggersOn() {return m_triggerson;}
	void SetTriggersOn(bool b) {m_triggerson=b;}
	bool IsVerbose() {return m_scrverbose;}
	void SetVerbose(bool b) {m_scrverbose=b;}
	int GetAliasIndexByLabel(wxString s);
	int GetVarIndexByLabel(wxString s);
	int GetListIndexByLabel(wxString s);
	int GetTimerIndexByLabel(wxString s);
	int GetButtonIndexByLabel(wxString s);
	int GetButtonIndexById(int i);
	int GetDefVarIndexByLabel(wxString s);
	int GetHkIndexByLabel(wxString s);
	vector<wxString> *GetPackages() {return &m_packages;}
	std::vector<class amcScriptThread*> *GetThreads() {return &m_threads;}
	map<int, struct lua_State*> *GetLuaStates() {return &m_luastates;}
	int GetLRefCount() {return m_refcount;}
	void SetLRefCount(int i) {m_refcount=i;}
	void luaBuildtrigger();
	void luaBuildalias();
	void luaBuildvar();
	void luaCreateATCPTable();
	void luaCreateGMCPTable();
	void luaCreateMSDPTable();
	std::vector<wxString> *GetLastHost() {return &m_lasthost;}
	std::vector<int> *GetLastPort() {return &m_lastport;}
	wxCriticalSection m_scriptcs;
	friend class amcScriptThread;
	void SetScriptFont(wxFont *f) {delete m_scriptfont;m_scriptfont = new wxFont(*f);}
	wxFont* GetScriptFont() {return m_scriptfont;}
	void BuildEncodingMenu(wxMenu*);	//class wxMediaCtrl *GetMediaCtrl() {return &m_media;}
private:
	bool m_usesplitter;
	bool m_triggerson;
	class GlobalOptions *m_gopt;
	std::vector<amchost> m_amchost;
	int m_curhost;
	std::vector<wxString> m_panes;
	std::vector<wxString> m_nbs;
	vector<vector<wxString> > m_nbpanes;
	vector<wxString> m_amcwindows;
	std::vector<wxString> m_gaugepanes;
	vector<vector<wxString> > m_gauges;
	vector<wxString> m_packages;
	vector<class amcScriptThread*> m_threads;
	map<int, struct lua_State*> m_luastates;
	map<wxString, long> m_keys;
	int m_refcount;
	wxString m_curprofile;
	std::vector<wxString> m_lasthost;
	std::vector<int> m_lastport;
	//class wxMediaCtrl m_media;
	bool m_scrverbose;
	wxFileHistory *m_filehist;
	wxFindReplaceDialog *m_find;
	wxFindReplaceData m_finddata;
	wxFont *m_scriptfont;
	void DefineKeys();
    void OnEraseBackground(wxEraseEvent& event);
	//void OnScriptPause(wxThreadEvent& event);
	//void OnScriptResume(wxThreadEvent& event);
	void OnIdle(wxIdleEvent& event);
	void OnMediaLoaded(wxMediaEvent& WXUNUSED(event));
	void OnMediaFinished(wxMediaEvent& WXUNUSED(event));
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
};

//TextCtrl for CommandLine
class InputTextCtrl : public wxTextCtrl
{
	public:
    MudMainFrame *m_parent;

	InputTextCtrl(wxWindow *parent, wxWindowID is, const wxString &value, const wxPoint &pos, const wxSize &size, int style=0);
	bool ParseCommandLine(wxString *sCommand);
	bool ParseVars(wxString *s);
	bool ParsePath(wxString *s);
	bool ParseLists(wxString *s);
	bool GetParse() {return m_parse;}
	bool GetKeepInput() {return m_keepinput;}
	bool GetTabDlg() {return m_tabbox;}
	void SetParse(bool b) {m_parse=b;}
	void SetKeepInput(bool b) {m_keepinput=b;}
	void SetTabDlg(bool b) {m_tabbox=b;}
	bool SaveHistory();
	bool LoadHistory();
	bool LoadTabText();
	bool GetWaiting() {return m_waiting;}
	void SetWaiting(bool b) {m_waiting=b;}
	std::vector<class wxString> * GetHistory() {return &m_history;}
	int GetHPos() {return m_hpos;}
	void Parse(wxString sC, bool b = true, bool hist=true);
	friend class amcScriptThread;
private:
	std::map<class wxString, int (InputTextCtrl::*)(wxString*)> m_sComm;
	std::map<class wxString, int (InputTextCtrl::*)(wxString*)>::iterator m_it;
	std::vector<class wxString> m_history;
	std::vector<class wxString> m_tabtext;
	std::vector<class wxString> m_fparams;

	bool m_keepinput;//keep input or clear it
	bool m_parse;//send as is or parse input
	int m_hpos;
	wxString m_tabsearch;
	int m_tabpos;
	bool m_tab;
	bool m_tabbox;
	wxString m_lastcommand;
	bool m_waiting;
	wxTimer m_sw;
	wxString m_swsend;
	//functions
	bool ParseCommand(wxString *sCommand);
	//functions mudcommands
	int CommRaw(wxString *sPar);//#raw
	int Connect(wxString *sPar);//#conncect
	int Pwd(wxString *sPar);//#pwd
	int CaptureWin(wxString *sPar);//#capturewin
	int CaptureNb(wxString *sPar);//#capturenb
	int CapStart(wxString *sPar);//#capstart
	int CapEnd(wxString *sPar);//#capend
	int ClearWin(wxString *sPar);//#clearwin
	int RefreshWin(wxString *sPar);//#refreshwin
	int GagWin(wxString *sPar);//#gagwin
	int Gag(wxString *sPar);//gag
	int Func(wxString *sPar);//#func
	int Log(wxString *sPar);//#log
	int HtmlLog(wxString *sPar);//#htmllog
	int Script(wxString *sPar);//#script
	//int BScript(wxString *sPar);//#bscript
	int TScript(wxString *sPar);//#tscript
	int SetVar(wxString *sPar);//#setvar
	int Resume(wxString *sPar);//#resume
	int Test(wxString *sPar);//#test
	int Help(wxString *sPar);//#help
	int LoadProfile(wxString *sPar);//#loadprofile
	int Media(wxString *sPar);//#media
	int Mxp(wxString *sPar);//#mxp
	int Info(wxString *sPar);//#info

	int ParseFParams(wxString *sPar, wxChar delim = wxT('\"'));
	wxString GetFParam(int index) {return m_fparams.at(index-1);}
	wxString Complete();
	//events
	void OnTextEnter(wxCommandEvent& event);
	void OnText(wxCommandEvent& event);
	void OnChar(wxKeyEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnMouseWheel(wxMouseEvent& event);
	void OnSetFocus(wxFocusEvent& event);
	void OnSWDelay(wxTimerEvent& event);
	DECLARE_EVENT_TABLE()
};

typedef vector<wxString>::iterator s_it;

class amcScriptThread : public wxThread
{
public:
    amcScriptThread();
	amcScriptThread(MudMainFrame *frame, wxString s);
	amcScriptThread(const amcScriptThread&);
	~amcScriptThread();
	amcScriptThread& operator=(const amcScriptThread& A) {m_id=A.m_id;m_pars=A.m_pars;m_frame=A.m_frame;return *this;}
	bool operator==(const amcScriptThread& A) {return m_id==A.m_id;}
	friend bool operator==(const amcScriptThread& A, const amcScriptThread& B) {return A.m_id==B.m_id;}
	virtual void *Entry();
	//virtual bool TestDestroy();
	void SetId(wxThreadIdType id) {m_id=id;}
	wxThreadIdType GetMyId() {return m_id;}
	void SetMutex(wxMutex *x) {m_mutex=x;}
	void SetCond(wxCondition *c) {m_cond = c;}
	wxCondition* GetCond() {return m_cond;}
	wxMutex* GetMutex() {return m_mutex;}
private:
    MudMainFrame *m_frame;
    wxThreadIdType m_id;
	wxString m_pars;
	wxMutex* m_mutex;
	wxCondition* m_cond;
};
#endif

