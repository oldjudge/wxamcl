/*! \file mudwindow.cpp
	\brief implements the MudWindow class.
	
	This represents a complete Window, which ouputs incoming mudtext.
	
	Includes a socket, so each window can connect to another mud, this is not used.
*/
#include "main.h"
#define HAVE_TEXT 0
#define HAVE_ESC 1
#define HAVE_ESCBR 2
#define HAVE_LINE 3
#define HAVE_IAC 4
#define HAVE_IACIAC 5
#define HAVE_DELIMITER1 6
#define HAVE_DELIMITER2 7
#define HAVE_DELIMITER3 8
#define HAVE_IACWILL 9
#define HAVE_IACDO 10
#define HAVE_IACWONT 11
#define HAVE_IACDONT 12
#define HAVE_IACSB 13
#define HAVE_IACSE 14
#define HAVE_IACSBCOMPRESS2 15
#define HAVE_IACSBTT 16
#define HAVE_IACSBATCP 17
#define HAVE_IACSBMXP 18
#define HAVE_IACGA 19
#define HAVE_COMPRESS_START 20
#define HAVE_MSP1 21
#define HAVE_MSP 22
#define HAVE_IACSBAARD 23
#define HAVE_IACSBATCP2 24
#define HAVE_IACSBMSDP 25
#define HAVE_LF 26
#define HAVE_IACSBCHARSET 27

BEGIN_EVENT_TABLE(MudWindow, wxWindow)
    //EVT_ERASE_BACKGROUND(MudWindow::OnEraseBackground)
	EVT_PAINT(MudWindow::OnPaint)
	EVT_SIZE(MudWindow::OnSize)
	EVT_SCROLLWIN(MudWindow::OnScroll)
	EVT_SOCKET(SOCKET_ID, MudWindow::OnSocketEvent)
	EVT_LEFT_DOWN(MudWindow::OnLeftDown)
	EVT_LEFT_UP(MudWindow::OnLeftUp)
	EVT_RIGHT_UP(MudWindow::OnRightUp)
	EVT_MOTION(MudWindow::OnMouseMove)
	EVT_MOUSEWHEEL(MudWindow::OnMouseWheel)
	EVT_CHAR(MudWindow::OnChar)
	EVT_CONTEXT_MENU(MudWindow::OnContextMenu)
	EVT_MENU(ID_OUTFONT, MudWindow::OnOutputFont)
	EVT_MENU(ID_STAMPS, MudWindow::OnTimeStamps)
	EVT_MENU(ID_MAKEACTION, MudWindow::OnMakeAction)
	EVT_MENU_RANGE(ID_MXPMENU, ID_MXPMENU+100, MudWindow::OnMxpMenu)
	EVT_MENU_RANGE(ID_MXPMENUPROMPT, ID_MXPMENUPROMPT+100, MudWindow::OnMxpPromptMenu)
	EVT_TIMER(1111, MudWindow::OnAutoReconnect)
END_EVENT_TABLE()

bool MudWindow::m_bonewline = false;
bool MudWindow::m_bocolcode = false;
bool MudWindow::m_atcpdata = false;

IMPLEMENT_DYNAMIC_CLASS(MudWindow, wxWindow)

MudWindow::MudWindow():wxWindow()
{
	MudWindow(wxGetApp().GetFrame());
	//m_tt.SetTip("");
}

/*! \brief standard constructor
	\param wxFrame parent window
*/
MudWindow::MudWindow(wxFrame *parent):wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL| wxBORDER_NONE)
{
	m_parent = (MudMainFrame*) parent;
	m_sock = new wxSocketClient();
	//m_sock->Initialize();
	//m_sock->SetInitialSocketBuffers(15000, 15000);
	// Setup the event handler and subscribe to most events
	m_sock->SetEventHandler(*this, SOCKET_ID);
	m_sock->SetNotify(wxSOCKET_CONNECTION_FLAG |
                    wxSOCKET_INPUT_FLAG |
                    wxSOCKET_LOST_FLAG);
		
	m_sock->Notify(true);
	m_connected = false;
	SetConnectionDT();
	SetDefaultColors();
	SetCssClasses();
	m_background = m_colansi[0];
	m_drawbmp.Create(wxSystemSettings::GetMetric(wxSYS_SCREEN_X), wxSystemSettings::GetMetric(wxSYS_SCREEN_Y));
	#if !defined __WXMSW__
		m_font = new wxFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier New");
		m_ufont = new wxFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, "Courier New");
		m_ifont = new wxFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL, false, "Courier New");
		SetBackgroundStyle(wxBG_STYLE_CUSTOM);
		SetBackgroundColour(m_background);
		ClearBackground();
	#else
		m_font = new wxFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Fixedsys");
		m_ufont = new wxFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, "Fixedsys");
		m_ifont = new wxFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL, false, "Fixedsys");
		SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	#endif
	
	m_oldcolor = new wxString("");
	m_curline = 0;
	m_parsestate = HAVE_TEXT;
	m_scrollrange = 0;
	m_useansi = true;
	m_timestamps = false;
	m_milliseconds = true;
	m_mccp2 = false;
	m_mccpneg = false;
	m_mxp = false; //MXP negotiated
	m_msp = false;
	m_msdp=false;
	m_MXP = new amcMXP(this);
	m_atcp = false;
	m_atcp2 = false;
	m_gmcp = false;
	m_debuggmcp = false;
	m_atcpstring = wxEmptyString;
	m_charset=wxEmptyString;
	m_oddmccp2 = 0;
	m_wrap = 150;//means autowrap at window width
	m_password = false;
	m_noscroll = false;
	m_selstart.x = -1;
	m_selstart.y = -1;
	m_selend = m_selstart;
	m_selected = m_linkclicked = false;
	m_selline = m_sellineend = -1;
	m_indexstart = m_indexend = 0;
	m_start = m_end = 0;
	m_wheelrot = 0;
	m_kevtforwarded = false;
	//wxSize ss = GetClientSize();
	m_trigger = true;//triggers for main output on
	m_useipv6 = false;
	m_firstlinecaptured = m_lastcaptured = false;
	m_log = m_logansi = m_logdate = m_bohtml = m_include = false;
	m_include = true;
	m_logfile = "log.txt";
	m_tlog = NULL;
	m_htmllog = NULL;
	m_L = new amcLua();
	//RegisterLuaFuncs();

	//m_gopt = new GlobalOptions(this);
	m_maxlines = 5000;//default line buffer for the window(\\e\\[0-1}+?;?[0-9]+m) (?<!\\e\\[[0-1];?3[0-9])m
	m_dc = new Decompressor();//\\b
	
	//m_mxp = new amcMXP();
	//"(((ht|f)tp:\\/\\/)?([A-Za-z0-9]+)?\\.?([A-Za-z0-9\\-]+)?\\.(?:a)(\\/?([a-zA-Z0-9\\-\\~\\?\\.=])))
	/////m_url = new RegExp("((ht|f)tp(s?)\\:\\/\\/)?([A-Za-z0-9]+)?\\.?(?!\\.)([A-Za-z0-9\\-]+)?\\.(?!txt)[a-z]{2,4}(\\/([a-zA-Z0-9\\.\\?=\\-\\~+%_&#]+)){0,6}"); //\\/?(\\~|\\.|\\-|=|\\?|\\w+)?.+)\\b");
	m_url = new RegExp("((ht|f)tp(s?)\\:\\/\\/)?[A-Za-z0-9]{1,100}\\.?(?!\\.)[A-Za-z0-9\\-]{2,}\\.(?!txt)[a-z]{2,4}(\\/([a-zA-Z0-9\\.\\?=\\-\\/\\~+%_&#:]+)){0,6}"); //\\/?(\\~|\\.|\\-|=|\\?|\\w+)?.+)\\b");
	//m_url = new RegExp("((ht|f)tp(s?)\\:\\/\\/|~/|/)?([\\w]+:\\w+@)?([a-zA-Z]{1}([\\w\\-]+\\.)+([\\w]{2,5}))(:[\\d]{1,5})?((/?\\w+/)+|/?)(\\w+\\.[\\w]{3,4})?((\\?\\w+=\\w+)?(&\\w+=\\w+)*)?");
	m_bourl = true;
	//m_splitbuffer = true;
	m_ansicode = new RegExp("\\e\\[[0-1]?;?3?[0-9]?;?5?[0-9]?m");
	 //m_prompt = new RegExp(wxT(".*>"));
	m_prompt = new RegExp("");             
	m_boprompt = false;
	m_gagprompt = false;

	//m_botelnetparsed=false;
	m_focusoninput = true;

	m_curansicolor = m_colansi[DEF_FORECOL];
	//m_capture.reserve(100);
	//m_capwin.reserve(100);
	//m_capgag.reserve(100);
	//m_url = new RegExp(wxT("((http:\\/\\/)?([A-Za-z0-9]+)?\\.[A-Za-z0-9\\-]+\\.[a-z]+[\\/?\\~?\\.\\-=\\?\\w+]+)\\b"));
	//m_url = new RegExp("orf");
	SetScrollbar(wxVERTICAL, 0, 0, 0);
	SetName("amcoutput");
	m_tt = new wxToolTip("");
	//m_tt->SetDelay(5);
	this->SetToolTip(m_tt);
	//wxString *text = new wxString("testinf");
	//ParseLine(text);
}
/*! \brief constructor used for capture windows

	\param wxFrame parent
	\param wxString name of window
	\param int fontsize for used font
*/
MudWindow::MudWindow(wxFrame *parent, wxString name, int fontsize):wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL| wxBORDER_NONE |wxTRANSPARENT_WINDOW)
{
	m_parent = (MudMainFrame*) parent;
	/*m_sock = new wxSocketClient();
	// Setup the event handler and subscribe to most events
	m_sock->SetEventHandler(*this, SOCKET_ID);
	m_sock->SetNotify(wxSOCKET_CONNECTION_FLAG |
                    wxSOCKET_INPUT_FLAG |
                    wxSOCKET_LOST_FLAG);
	m_sock->Notify(true);*/
	m_sock = NULL;
	m_connected = false;
	SetConnectionDT();
	SetDefaultColors();
	SetCssClasses();
	m_background = m_colansi[0];
	#if !defined __WXMSW__
		m_font = new wxFont(fontsize, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier New");
		m_ufont = new wxFont(fontsize, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, "Courier New");
		m_ifont = new wxFont(fontsize, wxFONTFAMILY_MODERN, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL, false, "Courier New");
		SetBackgroundStyle(wxBG_STYLE_SYSTEM);
		//SetBackgroundStyle(wxBG_STYLE_PAINT);
		SetBackgroundColour(m_background);
		ClearBackground();
	#else
		m_font = new wxFont(fontsize, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier");
		m_ufont = new wxFont(fontsize, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true, "Courier");
		m_ifont = new wxFont(fontsize, wxFONTFAMILY_MODERN, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL, false, "Courier");
		SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	#endif
	m_font->SetPointSize(fontsize);
	m_oldcolor = new wxString("");
	m_curline = 0;
	m_parsestate = HAVE_TEXT;
	m_scrollrange = 0;
	m_useansi = true;
	m_timestamps = true;
	m_milliseconds = true;
	m_mccp2 = false;
	m_mccpneg = false;
	m_oddmccp2 = 0;
	m_mxp = false;
	m_MXP = new amcMXP(this);
	m_msp = false;
	m_atcp = false;
	m_atcp2 = false;
	m_gmcp = false;
	m_debuggmcp = false;
	m_msdp=false;
	m_atcpstring = wxEmptyString;
	m_charset = wxEmptyString;
	m_wrap = 150;
	m_noscroll = false;
	m_selstart.x = -1;
	m_selstart.y = -1;
	m_selend = m_selstart;
	m_selected = m_linkclicked = false;
	m_selline = m_sellineend = -1;
	m_indexstart = m_indexend = 0;
	m_start = m_end = 0;
	m_wheelrot = 0;
	m_kevtforwarded = m_lastcaptured = false;
	m_firstlinecaptured = false;
	m_log = m_logansi = m_logdate = m_bohtml = false;
	m_include = true;
	m_logfile = "log.txt";
	m_tlog=NULL;
	m_htmllog = NULL;
	//m_L = new amcLua();
	m_L = NULL;
	m_bourl = false;
	m_url = NULL;
	//m_splitbuffer = false;
	m_ansicode = NULL;
	m_drawbmp.Create(wxSystemSettings::GetMetric(wxSYS_SCREEN_X), wxSystemSettings::GetMetric(wxSYS_SCREEN_Y));
	//m_drawbmp.Create(100,100);
	//RegisterLuaFuncs();

	//m_gopt = new GlobalOptions(this);
	m_maxlines = 500;//default line buffer for the window
	m_trigger = false; //triggers for user created windows off
	m_useipv6 = false;
	//m_dc = new Decompressor();//\\b
	m_dc = NULL;
	//m_mxp = NULL;
	//m_url = new RegExp(wxT("((http:\\/\\/)?([A-Za-z0-9]+)?\\.[A-Za-z0-9\\-]+\\.[a-z]+[\\/?\\~?\\.\\-=\\?\\w+]+)\\b"));
	//m_url = NULL;
	m_prompt = NULL;
	m_boprompt = false;
	m_gagprompt = false;
	//m_botelnetparsed = false;
	m_focusoninput = false;
	m_curansicolor = m_colansi[DEF_FORECOL];
	SetScrollbar(wxVERTICAL, 0, 0, 0);
	SetScrollbar(wxHORIZONTAL, 0, 0, 0);
	SetName(name);
	SetLabel(name);
	m_tt = new wxToolTip("");
	this->SetToolTip(m_tt);
	//m_tt = NULL;
}

MudWindow::~MudWindow()
{
//line_it lit;
//ale_it it;
//AnsiLine *line=NULL;
//AnsiLineElement ale;
//int x=0;
	if (m_connected)
	{
		m_sock->Close();
		if (m_mccp2)
		{
            m_mccp2=false;
            m_dc->EndDecompress();
			m_dc->Init();
		}
		if (m_parent->GetGlobalOptions()->GetUseEvents())
		{
			if (m_parent->GetGlobalOptions()->GetUseEvDisco())
			{
				wxString s;
				s = wxString::Format("%cfunc(\"%s\", \"OnDisconnected()\")", m_parent->GetGlobalOptions()->GetCommand(),
					m_parent->GetGlobalOptions()->GetEventFile());
				m_parent->m_input->ParseCommandLine(&s);
			}
		}
		// call ondiscoevent if defined
	}
	delete m_sock;
	delete m_font;
	delete m_ufont;
	delete m_ifont;
	delete m_oldcolor;
	delete m_dc;
	delete m_MXP;
	//if (m_tt)
	//	delete m_tt;
	delete m_L;
	delete m_url;
	delete m_ansicode;
	delete m_prompt;
	if (m_tlog)
	{
		if (m_tlog->IsOpened())
			m_tlog->Close();
	}
	delete m_tlog;
	if (m_htmllog)
	{
		if (m_htmllog->IsOpened())
			m_htmllog->Close();
		delete m_htmllog;
	}
	
	
	//llen = m_vmudlines.size();
	ClearLines();
}

wxString MudWindow::GetPromptRegExp()
{
	return m_prompt->GetPattern();
}

void MudWindow::SetPromptRegExp(wxString s)
{
	m_prompt->SetPattern(s);
	m_prompt->SetPrecompiled(false);
}

void MudWindow::ClearLines()
{
	if (!m_vmudlines.empty())
		m_vmudlines.clear();
	m_curline=0;
}

//functions
void MudWindow::MyConnect(wxIPV4address addr)
{
bool waitmore = true;
	m_addr = addr;
	wxIPV4address local;
	//windows only?m_sock->Connect(m_addr, local, true);
	//m_sock->SetFlags(wxSOCKET_WAITALL);
	Msg(_("Trying to connect..."));
	Refresh();
	Update();
	m_sock->Connect(m_addr, local, false);
	while ( !m_sock->WaitOnConnect(0, 200) && waitmore)
    {
		
		// possibly give some feedback to the user,
        // and update waitmore as needed.
    }
	m_sock->GetLocal(local);
	wxString s = local.IPAddress();
	int idx = m_parent->GetDefVarIndexByLabel("amcLocalIP");
	m_parent->GetDefVars()->at(idx).SetValue(s);
	//s = m_addr.IPAddress();
	/*bool waitmore = true;
	
			 if (!m_sock->IsConnected())
	{
		Msg(_("Connection failed! No internet connection available?"));
		return;
	}*/
	//m_sock->SetFlags(wxSOCKET_NOWAIT);
	//m_sock->SetFlags(wxSOCKET_WAITALL);
	//m_sock->Peek(cBuffer, 1);
}

void MudWindow::MyConnect(wxIPV6address addr)
{
bool waitmore = true;
	m_addr6 = addr;
	wxIPV6address local;
	//windows only?m_sock->Connect(m_addr, local, true);
	//m_sock->SetFlags(wxSOCKET_WAITALL);
	Msg(_("Trying to connect..."));
	Refresh();
	Update();
	m_sock->Connect(m_addr6, local, false);
	while ( !m_sock->WaitOnConnect(0, 200) && waitmore)
    {
		
		// possibly give some feedback to the user,
        // and update waitmore as needed.
    }
	m_sock->GetLocal(local);
	
	int idx = m_parent->GetDefVarIndexByLabel("amcLocalIP");
	m_parent->GetDefVars()->at(idx).SetValue("IPV6 address");
	//s = m_addr.IPAddress();
	/*bool waitmore = true;
	
			 if (!m_sock->IsConnected())
	{
		Msg(_("Connection failed! No internet connection available?"));
		return;
	}*/
	//m_sock->SetFlags(wxSOCKET_NOWAIT);
	//m_sock->SetFlags(wxSOCKET_WAITALL);
	//m_sock->Peek(cBuffer, 1);
}

void MudWindow::OnAutoReconnect(wxTimerEvent& event)
{
	MyConnect(m_parent->GetHosts()->at(m_parent->GetCurHost()).GetIP4());
}

void MudWindow::Write(wxString command)
{
	//char test[100];
	//wxStrcpy(test, (char*)command.char_str(wxConvUTF8));
	//wxString s8 = command.To8BitData();
	
	if (m_sock->IsConnected())
	{
		if (!m_parent->GetGlobalOptions()->UseUTF8())
		{
			//m_sock->Write(s8.data(), (wxUint32)s8.length());
		#ifdef __WXGTK
			wxString su = command.ToUTF8();
			if (su.empty()&&!command.empty())
				su = command;
			//m_sock->Write(command.To8BitData(), command.To8BitData().length());//works in linux
			m_sock->Write(su.To8BitData(), wxStrlen(su.To8BitData()));
			if (m_parent->GetGlobalOptions()->DebugRaw())
				WriteRaw(su.char_str(), su.char_str().length(), false);
		#endif
		#ifdef WXOSX
			wxString su = command.ToUTF8();
			if (su.empty()&&!command.empty())
				su = command;
			//m_sock->Write(command.To8BitData(), command.To8BitData().length());//works in linux
			m_sock->Write(su.To8BitData(), wxStrlen(su.To8BitData()));
			if (m_parent->GetGlobalOptions()->DebugRaw())
				WriteRaw(su.char_str(), su.char_str().length(), false);
		#endif
		
		#ifdef __WXMSW__
			m_sock->Write(command.To8BitData(), (wxUint32)command.To8BitData().length());
			if (m_parent->GetGlobalOptions()->DebugRaw())
				WriteRaw(command.char_str(), command.char_str().length(), false);
		#endif

		}
		else
		{
			wxString f;
			wxFontEncoding fe = m_parent->GetGlobalOptions()->GetCurEncoding();
			if (fe != wxFONTENCODING_UTF8)
				f = command.mb_str(wxCSConv(fe));
			else f = command.ToUTF8();
			if (f.empty() && !command.empty())
			{
				f = command.ToUTF8();
				m_sock->Write(f.c_str(), f.Length());
				//m_sock->Write(f.To8BitData(), (wxUint32)f.To8BitData().length());
				return;
			}
			//m_sock->Write(f.To8BitData(), (wxUint32)f.To8BitData().length());//wxStrlen(f.To8BitData()));
			m_sock->Write(f.c_str(), wxStrlen(f));
			//m_sock->Write(command.mb_str(wxCSConv(m_parent->GetGlobalOptions()->GetCurEncoding())), wxStrlen(command));
		}
	}
}

void MudWindow::Write8Bit(wxString command)
{
	
	if (m_sock->IsConnected())
	{
		#ifdef __WXGTK__
			//wxString su = command.ToUTF8();
			wxString su = command;
			if (su.empty()&&!command.empty())
				su = command;
			//m_sock->Write(command.To8BitData(), command.To8BitData().length());//works in linux
			m_sock->Write(su.To8BitData(), wxStrlen(su.To8BitData()));
			if (m_parent->GetGlobalOptions()->DebugRaw())
				WriteRaw(su.char_str(), su.char_str().length(), false);
		#endif
		#ifdef WXOSX
			//wxString su = command.ToUTF8();
			wxString su = command;
			if (su.empty()&&!command.empty())
				su = command;
			//m_sock->Write(command.To8BitData(), command.To8BitData().length());//works in linux
			m_sock->Write(su.To8BitData(), wxStrlen(su.To8BitData()));
			if (m_parent->GetGlobalOptions()->DebugRaw())
				WriteRaw(su.char_str(), su.char_str().length(), false);
		#endif
		
		
		#ifdef __WXMSW__
			m_sock->Write(command.To8BitData(), (wxUint32)command.To8BitData().length());
			wxUint32 x = m_sock->LastCount();
			if (m_parent->GetGlobalOptions()->DebugRaw())
				WriteRaw(command.char_str(), command.char_str().length(), false);
			//m_sock->Write(command, wxStrlen(command));
		#endif

	}
}

void MudWindow::Close()
{
	m_sock->Close();
	Msg(_("Connection closed by user!"));
}

void MudWindow::Msg(wxString msg, int fcol, int bcol)
{
AnsiLine line;
AnsiLineElement style[2];
//int index=0;

	//line = new AnsiLine();
	//style = new AnsiLineElement[2];
	if (!m_vmudlines.empty())
	{
		if (!m_vmudlines.back().IsFull())
		{
		m_curline--;
		//line = new AnsiLine(m_vmudlines.back());
		line = m_vmudlines.back();
		m_vmudlines.pop_back();
		//index = (int)m_vmudlines.back().m_vstyle.size();
		//index = (int)line->m_vstyle.size();
		//style = new AnsiLineElement[freq+index+5];
		//delete l;
		}
	}
	style->SetText(msg);
	style->SetFCol(fcol, m_colansi[fcol]);
	style->SetBCol(bcol, m_colansi[bcol]);
	style->SetText(msg);
	//line.SetLineText(msg);
	line.m_vstyle.push_back(style[0]);
	//line->m_style.DeleteContents(true);

	style[1].SetText(wxEmptyString);
	style[1].SetFCol(DEF_FORECOL, m_colansi[DEF_FORECOL]);
	style[1].SetBCol(bcol, m_colansi[bcol]);
	line.m_vstyle.push_back(style[1]);

	if (m_curline==0)
		line.SetLinenumber(m_curline);
	else
		line.SetLinenumber(m_vmudlines.at(m_curline-1).GetLinenumber()+1);
		
	wxDateTime d;
	//d.SetToCurrent();
	d = wxDateTime::UNow();
	line.SetDateTimeMS(d);
	d = wxDateTime::Now();
	line.SetDateTime(d);
	line.SetFull(true);
	line.SetLineText(msg);
	wxString ansimsg;
	ansimsg << AnsiLine::GetAnsiFCode(fcol)<<AnsiLine::GetAnsiBCode(bcol)<<msg<<"\x1b[0m";
	wxString temp = line.GetAnsiLine();
	wxString sub;
	if (!temp.empty() && temp.at(temp.length()-1)=='\0')
		sub = temp.Left(temp.length()-1);
	else sub = temp;
	sub.append(ansimsg);
	line.SetAnsiLine(sub);
	//line.SetAnsiLine(line.GetAnsiString());
	m_vmudlines.push_back(line);
	m_curline++;
	if (IsLogging())
	{
		/*if (m_vmudlines.at(m_curline-1).IsFull() && !m_vmudlines.at(m_curline-1).WasLogged())
			if (!IsAnsiLogging() && !IsHtmlLogging())
			{
				if (IsDateLogging())
					m_tlog->Write(m_vmudlines.at(m_curline-1).GetTime()+": ");
				m_tlog->Write(m_vmudlines.at(m_curline-1).GetLineText()+(char)CR+(char)LF);
			}
			else if (!IsHtmlLogging())
			{
				m_tlog->Write(m_vmudlines.at(m_curline-1).GetAnsiLine()+(char)CR+(char)LF);
				m_tlog->Write("\r\n");
			}
			else if (IsHtmlLogging())
			{
				wxString s;
				ale_it it;
				AnsiLine al = m_vmudlines.at(m_curline-1);
				for (it = al.m_vstyle.begin();it!=al.m_vstyle.end();it++)
				{
					wxString t = it->GetText();
					if (!t.Cmp(wxEmptyString))
						t.Append(" ");
					s = wxString::Format("<a class=\"%s\">%s</a>", m_css.at(it->GetFColIndex()-1), t);
					m_htmllog->Write(s);
				}
				m_htmllog->Write("\r\n");
			}
		m_vmudlines.at(m_curline-1).SetLogged(true);*/
		SendLineToLog(m_curline-1);
	}
	SetScrollPage();
	Refresh();
	//Update();
	//delete line;

}

void MudWindow::SendLineToLog(wxUint64 i)
{
	if (m_vmudlines.at(i).IsFull() && !m_vmudlines.at(i).WasLogged())
		if (!IsAnsiLogging() && !IsHtmlLogging())
		{
			if (IsDateLogging())
				m_tlog->Write(m_vmudlines.at(i).GetTime()+": ");
			m_tlog->Write(m_vmudlines.at(i).GetLineText()+(char)CR+(char)LF);
		}
		else if (!IsHtmlLogging())
		{
			m_tlog->Write(m_vmudlines.at(i).GetAnsiLine()+(char)CR+(char)LF);
			//m_tlog->Write("\r\n");
		}
		else if (IsHtmlLogging())
		{
			wxString s;
			ale_it it;
			AnsiLine al = m_vmudlines.at(i);
			if (IsDateLogging())
			{
				wxString ss;
				unsigned short us = al.GetDateTime().GetMillisecond();
				ss <<"<a class=col7>"<<al.GetTime()+":"<<us<<": "<<"</a>";
				m_htmllog->Write(ss);
			}
			if (!al.GetLineText().Cmp(wxEmptyString))
			{
				s = wxString::Format("<a class=\"%s\"> </a>", m_css.at(7));
				m_htmllog->Write(s.fn_str());
			}
			else 
			{
				for (it = al.m_vstyle.begin();it!=al.m_vstyle.end();it++)
				{
					wxString t = it->GetText();
					//if (!t.Cmp(wxEmptyString))
					//	t.Append("");
					t.Replace("<", "&lt;");
					t.Replace(">", "&gt;");
					if (!it->GetBColIndex())
					{
						int x = it->GetFColIndex()-1;
						if (x>16)
							x=16;
						s = wxString::Format("<a class=\"%s\">%s</a>", m_css.at(x), t);
					}
					else
					{
						int x = it->GetFColIndex()-1;
						if (x>16)
							x=16;
						s = wxString::Format("<a style=\"background-color: %s\" class=\"%s\">%s</a>", it->GetBCol().GetAsString(wxC2S_HTML_SYNTAX), m_css.at(x), t);
					}
					
					m_htmllog->Write(s.c_str());
				}
			}
			
			m_htmllog->Write("\r\n");
		}
	if (m_vmudlines.at(i).IsFull())
		m_vmudlines.at(i).SetLogged(true);
}

void MudWindow::WriteHtmlHeader(wxFile *f)
{
wxString s;
	
	s<<"<html>\r\n<head>\r\n<title>wxAmcl Log-File</title>\r\n<meta name=\"author\" content=\"Mag. Andreas Sachs\">\r\n";
	f->Write(s);
	s.Clear();
	s<<"<style type=\"text/css\">";
	f->Write(s);
	s = wxString::Format("a{font-family:%s, Lucida Console, Fixedsys, Courier;font-size: %dpt;}\r\n", m_parent->m_child->GetFont()->GetFaceName(), m_parent->m_child->GetFont()->GetPointSize());
	f->Write(s);
	s = wxString::Format("a.col1{color: %s;}\r\n", m_parent->m_child->GetAnsiColor(1).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
	s = wxString::Format("a.col2{color: %s;}\r\n", m_parent->m_child->GetAnsiColor(2).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
	s = wxString::Format("a.col3{color: %s;}\r\n", m_parent->m_child->GetAnsiColor(3).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
	s = wxString::Format("a.col4{color: %s;}\r\n", m_parent->m_child->GetAnsiColor(4).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
	s = wxString::Format("a.col5{color: %s;}\r\n", m_parent->m_child->GetAnsiColor(5).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
	s = wxString::Format("a.col6{color: %s;}\r\n", m_parent->m_child->GetAnsiColor(6).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
	s = wxString::Format("a.col7{color: %s;}\r\n", m_parent->m_child->GetAnsiColor(7).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
	s = wxString::Format("a.col8{color: %s;}\r\n", m_parent->m_child->GetAnsiColor(8).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
	s = wxString::Format("a.col9{color: %s;}\r\n", m_parent->m_child->GetAnsiColor(9).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
	s = wxString::Format("a.col10{color: %s;}\r\n", m_parent->m_child->GetAnsiColor(10).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
	s = wxString::Format("a.col11{color: %s;}\r\n", m_parent->m_child->GetAnsiColor(11).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
	s = wxString::Format("a.col12{color: %s;}\r\n", m_parent->m_child->GetAnsiColor(12).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
	s = wxString::Format("a.col13{color: %s;}\r\n", m_parent->m_child->GetAnsiColor(13).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
	s = wxString::Format("a.col14{color: %s;}\r\n", m_parent->m_child->GetAnsiColor(14).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
	s = wxString::Format("a.col15{color: %s;}\r\n", m_parent->m_child->GetAnsiColor(15).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
	s = wxString::Format("a.col16{color: %s;}\r\n", m_parent->m_child->GetAnsiColor(16).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
	s = wxString::Format("a.col17{color: %s;}\r\n", m_parent->m_child->GetAnsiColor(17).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
	s.Clear();
	s<<"</style></head>";
	f->Write(s);
	s = wxString::Format("\r\n<body text=\"%s\"", m_parent->m_child->GetAnsiColor(7).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
	s.Clear();
	s<<" link=\"#FF0000\" alink=\"#FF0000\" vlink=\"#FF0000\"";
	f->Write(s);
	s=wxString::Format(" bgcolor=\"%s\">\r\n<pre>", m_parent->m_child->GetAnsiColor(0).GetAsString(wxC2S_HTML_SYNTAX));
	f->Write(s);
}

void MudWindow::SetCssClasses()
{
	m_css.clear();
	m_css.push_back("col1");
	m_css.push_back("col2");
	m_css.push_back("col3");
	m_css.push_back("col4");
	m_css.push_back("col5");
	m_css.push_back("col6");
	m_css.push_back("col7");
	m_css.push_back("col8");
	m_css.push_back("col9");
	m_css.push_back("col10");
	m_css.push_back("col11");
	m_css.push_back("col12");
	m_css.push_back("col13");
	m_css.push_back("col14");
	m_css.push_back("col15");
	m_css.push_back("col16");
	m_css.push_back("col17");
}

void MudWindow::SetDefaultColors()
{
	m_colansi[0].Set("BLACK");
	//m_colansi[1].Set(RGB(160,0,0));
	m_colansi[1].Set(160,0,0);
	m_colansi[2].Set(0,160,0);
	m_colansi[3].Set(160,160,0);
	m_colansi[4].Set(0,0,160);
	m_colansi[5].Set(160,0,160);
	m_colansi[6].Set(0,160,160);
	m_colansi[7].Set(192,192,192);
	m_colansi[8].Set(128,128,128);
	m_colansi[9].Set(255,0,0);
	m_colansi[10].Set(0,255,0);
	m_colansi[11].Set(255,255,0);
	m_colansi[12].Set(0,0,255);
	m_colansi[13].Set(255,0,255);
	m_colansi[14].Set(0,255,255);
	m_colansi[15].Set(255,255,255);
	m_colansi[16] = m_colansi[10];//echo messages
	m_colansi[17] = m_colansi[14];//client messages
	m_colansi[18].Set("PINK");//custom color
	m_colansi[19].Set("PINK");//custom1

	//maps
	m_bcols[wxT("black")] = 40;
	m_bcols[wxT("red")] = 41;
	m_bcols[wxT("green")] = 42;
	m_bcols[wxT("yellow")] = 43;
	m_bcols[wxT("blue")] = 44;
	m_bcols[wxT("magenta")] = 45;
	m_bcols[wxT("cyan")] = 46;
	m_bcols[wxT("white")] = 47;
	m_bcols[wxT("gray")] = 48;
	m_bcols[wxT("bred")] = 49;
	m_bcols[wxT("bgreen")] = 50;
	m_bcols[wxT("byellow")] = 51;
	m_bcols[wxT("bblue")] = 52;
	m_bcols[wxT("bmagenta")] = 53;
	m_bcols[wxT("bcyan")] = 54;
	m_bcols[wxT("bwhite")] = 55;
	m_bcols[wxT("custom")] = 58;
	m_bcols[wxT("bcustom")] = 59;//customcolor1 for background

	m_colcodes[wxT("black")] = wxT("0;30;");
	m_colcodes[wxT("red")] = wxT("0;31;");
	m_colcodes[wxT("green")] = wxT("0;32;");
	m_colcodes[wxT("yellow")] = wxT("0;33;");
	m_colcodes[wxT("blue")] = wxT("0;34;");
	m_colcodes[wxT("magenta")] = wxT("0;35;");
	m_colcodes[wxT("cyan")] = wxT("0;36;");
	m_colcodes[wxT("white")] = wxT("0;37;");
	m_colcodes[wxT("gray")] = wxT("1;30;");
	m_colcodes[wxT("bred")] = wxT("1;31;");
	m_colcodes[wxT("bgreen")] = wxT("1;32;");
	m_colcodes[wxT("byellow")] = wxT("1;33;");
	m_colcodes[wxT("bblue")] = wxT("1;34;");
	m_colcodes[wxT("bmagenta")] = wxT("1;35;");;
	m_colcodes[wxT("bcyan")] = wxT("1;36;");
	m_colcodes[wxT("bwhite")] = wxT("1;37;");
	m_colcodes[wxT("client")] = wxT("1;36;");
	m_colcodes[wxT("send")] = wxT("1;32;");
	m_colcodes[wxT("italic")] = wxT("3;");
	m_colcodes[wxT("underlined")] = wxT("4;");
	m_colcodes[wxT("custom")] = wxT("1;58;");
	m_colcodes[wxT("custom1")] = wxT("1;59;");

	//xterm colours
	m_xterm[0].Set(RGB(0, 0, 0));         // (black)       
  m_xterm[1].Set(RGB (128, 0, 0));       // (maroon)      
  m_xterm[2].Set(RGB (0, 128, 0));       // (green)       
  m_xterm[3].Set(RGB (128, 128, 0));     // (olive)       
  m_xterm[4].Set(RGB (0, 0, 128));       // (navy)        
  m_xterm[5].Set(RGB (128, 0, 128));     // (purple)      
  m_xterm[6].Set(RGB (0, 128, 128));     // (teal)        
  m_xterm[7].Set(RGB (192, 192, 192));   // (silver)      
  m_xterm[8].Set(RGB (128, 128, 128));  // (gray)                 
  m_xterm[9] .Set(RGB (255, 0, 0));      // (red)               
  m_xterm[10].Set(RGB (0, 255, 0));      // (lime)              
  m_xterm[11].Set(RGB (255, 255, 0));    // (yellow)            
  m_xterm[12].Set(RGB (0, 0, 255));      // (blue)              
  m_xterm[13].Set(RGB (255, 0, 255));    // (magenta)  
  m_xterm[14].Set(RGB (0, 255, 255));    // (cyan)        
  m_xterm[15].Set(RGB (255, 255, 255));  // (white)             

// This gives even 6x6x6 colour cube
//  there are 6 colours in the cube, but only 5 gaps:
//   Thus the colours will be: 0x00 / 0x33 / 0x66 / 0x99 / 0xCC / 0xFF

  const BYTE colour_increment = 255 / 5;     // that is, 51 (0x33)

  int red, green, blue;

  for (red = 0; red < 6; red++)
      for (green = 0; green < 6; green++)
        for (blue = 0; blue < 6; blue++)
           m_xterm[16 + (red * 36) + (blue * 6) + green].Set(RGB (red   * colour_increment, 
                   blue  * colour_increment, 
                   green * colour_increment));


  // finish off with 24 greyscale colours  
  int grey;
  for (grey = 0; grey < 24; grey++)
    {
    BYTE value = 8 + (grey * 10);
    m_xterm [232 + grey].Set(RGB (value, value, value));
    }

  m_replcol["^0"]="\x1b[0m";
  wxString ss="^x";
  wxString sss="\x1b[38;5;";
  for (int xx=0;xx<255;xx++)
	{
	m_replcol[ss<<xx]=sss<<xx<<"m";
	ss="^x";
	sss="\x1b[38;5;";
	}
  

}

void MudWindow::AddLine(AnsiLine al)
{
AnsiLineElement style;
	al.SetLinenumber(m_curline++);
	if (!m_vmudlines.empty())
	{
		if (m_vmudlines.back().m_vstyle.back().GetFColIndex()!= DEF_FORECOL)
		{
			al.m_vstyle.begin()->SetFCol(m_vmudlines.back().m_vstyle.back().GetFColIndex(), m_vmudlines.back().m_vstyle.back().GetFCol());
			al.m_vstyle.begin()->SetBCol(m_vmudlines.back().m_vstyle.back().GetBColIndex(), m_vmudlines.back().m_vstyle.back().GetBCol());//style[index]
		}
	}
	m_vmudlines.push_back(al);
	//SetScrollPage();
}

//stream expected as char data
void MudWindow::ParseBuffer(char* cBuffer)
{
//int* iArray;
int iArray[1000];
int pos = -1;
int index = 1;
int len=0;
static int oldline = 0;
//int count1 = 0;
//wxChar *cLine;
//wxString *sLine=NULL;
wxString sLine;
//wxString s;
//tr_it trit;
map<wxString, bool>::iterator mit;
	if (!cBuffer)
	{
		wxLogDebug("Nullpointer in ParseBuffer passed!! m_curline: %d", m_curline);
		return;
	}
	//iArray = NULL;
	//iArray = (int*)calloc(2,sizeof(int));
	iArray[0]=0;
	while (*(cBuffer + ++pos))
	{
		if (*(cBuffer + pos)== (char)CR || *(cBuffer + pos)== (char)LF)
		{
			index++;
			//iArray = (int*)realloc(iArray, (index+1)*sizeof(int));
			if (*(cBuffer+pos)== LF && *(cBuffer+pos+1)== CR)
				iArray[index-1]=(++pos+1);
			else if (*(cBuffer+pos)== CR && *(cBuffer+pos+1)== LF)
				iArray[index-1]=(++pos+1);
			else iArray[index-1]=pos+1;
		}
		if (m_parent->GetGlobalOptions()->UseGAEOR())
		{
			if (*(cBuffer + pos)== (char)IAC)
			{
				if (*(cBuffer + pos + 1)== (char)GA || *(cBuffer+pos+1)==(char)EOR)
				{
					*(cBuffer + pos) = (char)CR;
					*(cBuffer + pos + 1) = (char)LF;
					pos--;
				}
			}
				//*(cBuffer + pos + 2) = EOS;
			
		}
	}
	//iArray = (int*)realloc(iArray, (index+1)*sizeof(int));
	iArray[index]= (int)wxStrlen(cBuffer);
	//::wxLogDebug(wxT("index=%3d"), index);
	pos=-1;
	//curline = lines;
	//wxStopWatch sw;
	//do
    for (pos=0;pos<index;pos++)
	{
		//sw.Start();
		//pos++;
		oldline = m_curline;
		if ((iArray[pos+1])>64000)
			break;
		len = iArray[pos+1] - iArray[pos];
		if (!len)
			continue;
		//sLine = new wxString(&cBuffer[iArray[pos]], len);
		//sLine.clear();
		//sLine.assign(&cBuffer[iArray[pos]], len);
		sLine = wxString::From8BitData(&cBuffer[iArray[pos]], len);
				
		//sLine.Append((char)EOS);
		//sLine.append((char*)'\0');
		//wxASSERT_MSG((sLine==NULL), "String creation failed!");
		if (sLine.GetChar(len-1)!=CR && sLine.GetChar(len-1)!=LF)
			m_bonewline = false;
		else m_bonewline = true;
		if (m_bonewline)
			sLine.Trim();
		sLine.Append('\x0');
		//test for one!! URL in line
		if (m_bourl)
		{
			
			if (m_url->Match(sLine, false))
			{//yes .. underlined font
				int sub = m_url->GetMatchStart()-8;//some stuff cause ansicodes can mess regexp detection of URL
				if (sub<0)
					sub=0;
				bool b = m_ansicode->Match(sLine.substr(sub, m_url->GetMatchLen()), false);
				if (!b)
					sub=0;
				int start=0;
				if (m_url->GetMatchStart()<m_ansicode->GetMatchEnd()+sub+1)
					start = m_ansicode->GetMatchEnd();
				else start = m_url->GetMatchStart();
				if (!sub && !m_url->GetMatchStart())
					start=0;
				sLine.insert(start+sub, "\x1b[4m");
				//sLine.insert(m_url->GetMatchStart(), "\x1b[4m");
				sLine.insert(m_url->GetMatchEnd()+4, "\x1b[0m");
			}
		}
		if (m_curline<m_vmudlines.size())
			m_curline=m_vmudlines.size();
		ParseLine(&sLine);
		if (m_curline>m_vmudlines.size())
			m_curline=m_vmudlines.size();
		
		if (m_curline>=GetMaxLines())
		{
			m_curline--;
			m_vmudlines.pop_front();
		}
		if (IsLogging())
		{
			/*if (m_vmudlines.at(m_curline-1).IsFull() && !m_vmudlines.at(m_curline-1).WasLogged())
			{
				if (!IsAnsiLogging() && !IsHtmlLogging())
				{
					
					if (IsDateLogging())
						m_tlog->Write(m_vmudlines.at(m_curline-1).GetTime()+": ");
					m_tlog->Write(m_vmudlines.at(m_curline-1).GetLineText()+(char)CR+(char)LF);
				}
				else if (!IsHtmlLogging())
				{
					m_tlog->Write(sLine+(char)CR+(char)LF);
					m_tlog->Write("\r\n");
				}
				else if (IsHtmlLogging())
				{
					wxString s;
					ale_it it;
					AnsiLine al = m_vmudlines.at(m_curline-1);
					for (it = al.m_vstyle.begin();it!=al.m_vstyle.end();it++)
					{
						wxString t = it->GetText();
						if (!t.Cmp(wxEmptyString))
							t.Append(" ");
						t.Replace("<", "&lt;");
						t.Replace(">", "&gt;");
						s = wxString::Format("<a class=\"%s\">%s</a>", m_css.at(it->GetFColIndex()-1), t);
						m_htmllog->Write(s);
					}
					m_htmllog->Write("\r\n");
				}
				m_vmudlines.at(m_curline-1).SetLogged(true);
			
			}*/
			SendLineToLog(m_curline-1);
		}
		//wxString s = m_vmudlines.at(m_curline-1).GetAnsiString();
		//test trigger
		//trigger check
		
		CheckTrigger(m_curline-1, true);
		
		//capturing with capstart, capend
		if (!m_capwindow.empty())
		{
			//vector<wxString>::iterator it;
			//AnsiLine al;
			MudWindow *mw;
			//int i;
			for (mit = m_capwindow.begin(); mit!=m_capwindow.end(); mit++)
			{
				mw = (MudWindow*)MudWindow::FindWindowByName(mit->first, m_parent);
				if (mw==NULL)
					continue;
				if (!mw->GetFirstCaptured())
				{
					mw->AddLine(m_vmudlines.at(m_curline-1));
					//mw->ParseLine(&sLine);
				}
				else mw->SetFirstCaptured(false);
				//mw->Freeze();

				//mw->ParseLine(sLine);
				if (mit->second)
				{
					m_vmudlines.pop_back();
					m_curline--;
				}
				//mw->Thaw();
			}

		}
		//still to capture to another window?
		if (!m_capwin.empty())
		{
			s_it it;
			//AnsiLine al;
			size_t i=0;
			MudWindow *mw;
			vector<long>::iterator lit;
			vector<bool>::iterator bit;
			for (i=0, it=m_capwin.begin(), lit=m_capture.begin(), bit=m_capgag.begin();i<m_capwin.size();i++, it++, lit++, bit++)
			{
				mw = (MudWindow*)MudWindow::FindWindowByName(it->c_str(), m_parent);
				if (mw==NULL)
					continue;

				if (*lit>0)
				{
					mw->AddLine(m_vmudlines.at(m_curline-1));
					if (*bit)
					{
						m_vmudlines.pop_back();
						m_curline--;
					}
					m_capture.at(i)--;
					mw->SetScrollPage();
					mw->Refresh();
					mw->Update();
				}
			}
			for (i=0, it=m_capwin.begin(), lit=m_capture.begin(), bit=m_capgag.begin(); it!=m_capwin.end(); it++, lit++, bit++, i++)
			{
				if (*lit<=0)
				{
					m_capwin.erase(it);
					m_capture.erase(lit);
					m_capgag.erase(bit);
					it = m_capwin.begin()+i;
					lit = m_capture.begin()+i;
					bit = m_capgag.begin()+i;
					if (it==m_capwin.end())
						break;
				}
			}
		}

		//should we lock the prompt?
		if (m_boprompt)
		{
			int x, y;
			wxString s = wxEmptyString;
			s += m_vmudlines.at(m_curline-1).GetLineText();
			m_parent->m_prompt->GetTextExtent(s, &x, &y);
			if (m_prompt->Match(s, false))
			{
				if (m_gagprompt) //should we gag the original prompt?
				{
					m_vmudlines.pop_back();
					m_curline--;
				}
				m_parent->m_mgr.GetPane(wxT("amcprompt")).Position(0).BestSize(x+10,24).Fixed();
				if (!m_parent->m_mgr.GetPane(wxT("amcprompt")).IsShown())
				{
					
					m_parent->m_mgr.GetPane(wxT("amcinput")).Position(1);
					m_parent->m_mgr.GetPane(wxT("amctoggle")).Position(2);
					m_parent->m_mgr.GetPane(wxT("amcprompt")).Show();	
				}
				m_parent->m_mgr.Update();
				m_parent->m_prompt->Clear();
				m_parent->m_prompt->AppendText(s);
				
				
			}
		}
	
		if (m_vmudlines.at(m_curline-1).GetGagme())
		{
			m_vmudlines.pop_back();
			m_curline--;
			this->SetScrollPage();
		}
		//::wxLogDebug(wxT("time: %ld ms, %s"), sw.Time(), sLine.c_str());
    //} while (pos<index-1);
	}
}

void MudWindow::ParseUTF8Buffer(wxString cBuffer)
{
//int* iArray;
int iArray[1000];
int pos = -1;
int index = 1;
int len=0;
static int oldline = 0;
//int count1 = 0;
//wxChar *cLine;
//wxString *sLine=NULL;
wxString sLine;
//wxString s;
//tr_it trit;
map<wxString, bool>::iterator mit;
	
	//iArray = NULL;
	//iArray = (int*)calloc(2,sizeof(int));
	iArray[0]=0;
	while (++pos<(int)cBuffer.length())
	{
		if (cBuffer.at(pos)== CR || cBuffer.at(pos)== LF)
		{
			index++;
			//iArray = (int*)realloc(iArray, (index+1)*sizeof(int));
			if (cBuffer.at(pos)== LF && cBuffer.at(pos+1)== CR)
				iArray[index-1]=(++pos+1);
			else if (cBuffer.at(pos)== CR && cBuffer.at(pos+1)== LF)
				iArray[index-1]=(++pos+1);
			else iArray[index-1]=pos+1;
		}
		if (m_parent->GetGlobalOptions()->UseGAEOR())
		{
			if (cBuffer.at(pos)== IAC && (cBuffer.at(pos + 1)== GA || cBuffer.at(pos+1)==EOR))
			{
				cBuffer.SetChar(pos, CR);
				cBuffer.SetChar(pos + 1, LF);
				//*(cBuffer + pos + 2) = EOS;
				pos--;
			}
		}
	}
	//iArray = (int*)realloc(iArray, (index+1)*sizeof(int));
	iArray[index]= (int)wxStrlen(cBuffer);
	//::wxLogDebug(wxT("index=%3d"), index);
	pos=-1;
	//curline = lines;
	//wxStopWatch sw;
	//do
    for (pos=0;pos<index;pos++)
	{
		//sw.Start();
		//pos++;
		oldline = m_curline;
		len = iArray[pos+1] - iArray[pos];
		if (!len)
			continue;
		//sLine = new wxString(&cBuffer[iArray[pos]], len);
		//sLine.clear();
		//sLine.assign(&cBuffer[iArray[pos]], len);
		//sLine = wxString::From8BitData(&cBuffer[iArray[pos]], len);
		sLine = cBuffer.substr(iArray[pos], len);		
		//sLine.Append(EOS);
		//sLine.append((char*)'\0');
		//wxASSERT_MSG((sLine==NULL), "String creation failed!");
		if (sLine.GetChar(len-1)!=CR && sLine.GetChar(len-1)!=LF)
			m_bonewline = false;
		else m_bonewline = true;
		if (m_bonewline)
			sLine.Trim();
		sLine.Append((char)EOS);
		//test for URL in line
		if (m_bourl)
		{
			
			if (m_url->Match(sLine, false))
			{//yes .. underlined font
				int sub = m_url->GetMatchStart()-8;//some stuff cause ansicodes can mess regexp detection of URL
				if (sub<0)
					sub=0;
				bool b = m_ansicode->Match(sLine.substr(sub, m_url->GetMatchLen()), false);
				if (!b)
					sub=0;
				int start=0;
				if (m_url->GetMatchStart()<m_ansicode->GetMatchEnd()+sub+1)
					start = m_ansicode->GetMatchEnd();
				else start = m_url->GetMatchStart();
				if (!sub && !m_url->GetMatchStart())
					start=0;
				sLine.insert(start+sub, "\x1b[4m");
				//sLine.insert(m_url->GetMatchStart(), "\x1b[4m");
				sLine.insert(m_url->GetMatchEnd()+4, "\x1b[0m");
			}
		}
		
		if (m_curline<m_vmudlines.size())
			m_curline=m_vmudlines.size();
		ParseLine(&sLine);
		if (m_curline>=GetMaxLines())
		{
			m_curline--;
			m_vmudlines.pop_front();
		}
		if (IsLogging())
		{
			if (m_vmudlines.at(m_curline-1).IsFull() && !m_vmudlines.at(m_curline-1).WasLogged())
			{
				if (!IsAnsiLogging() && !IsHtmlLogging())
				{
					if (IsDateLogging())
						m_tlog->Write(m_vmudlines.at(m_curline-1).GetTime()+": ");
					m_tlog->Write(m_vmudlines.at(m_curline-1).GetLineText()+(char)CR+(char)LF);
				}
				else if (!IsHtmlLogging())
				{
					m_tlog->Write(sLine+(char)CR+(char)LF);
					m_tlog->Write("\r\n");
				}
				else if (IsHtmlLogging())
				{
					wxString s;
					ale_it it;
					AnsiLine al = m_vmudlines.at(m_curline-1);
					for (it = al.m_vstyle.begin();it!=al.m_vstyle.end();it++)
					{
						wxString t = it->GetText();
						if (!t.Cmp(wxEmptyString))
							t.Append(" ");
						t.Replace("<", "&lt;");
						t.Replace(">", "&gt;");
						s = wxString::Format("<a class=\"%s\">%s</a>", m_css.at(it->GetFColIndex()-1), t);
						m_htmllog->Write(s);
					}
					m_htmllog->Write("\r\n");
				}
				m_vmudlines.at(m_curline-1).SetLogged(true);
			}
		}
		//wxString s = m_vmudlines.at(m_curline-1).GetAnsiString();
		//test trigger
		//trigger check
		
		CheckTrigger(m_curline-1, true);
		
		//capturing with capstart, capend
		if (!m_capwindow.empty())
		{
			//vector<wxString>::iterator it;
			//AnsiLine al;
			MudWindow *mw;
			//int i;
			for (mit = m_capwindow.begin(); mit!=m_capwindow.end(); mit++)
			{
				mw = (MudWindow*)MudWindow::FindWindowByName(mit->first, m_parent);
				if (mw==NULL)
					continue;
				if (!mw->GetFirstCaptured())
				{
					mw->AddLine(m_vmudlines.at(m_curline-1));
					//mw->ParseLine(&sLine);
				}
				else mw->SetFirstCaptured(false);
				//mw->Freeze();

				//mw->ParseLine(sLine);
				if (mit->second)
				{
					m_vmudlines.pop_back();
					m_curline--;
				}
				//mw->Thaw();
			}

		}
		//still to capture to another window?
		if (!m_capwin.empty())
		{
			s_it it;
			//AnsiLine al;
			size_t i=0;
			MudWindow *mw;
			vector<long>::iterator lit;
			vector<bool>::iterator bit;
			for (i=0, it=m_capwin.begin(), lit=m_capture.begin(), bit=m_capgag.begin();i<m_capwin.size();i++, it++, lit++, bit++)
			{
				mw = (MudWindow*)MudWindow::FindWindowByName(it->c_str(), m_parent);
				if (mw==NULL)
					continue;

				if (*lit>0)
				{
					mw->AddLine(m_vmudlines.at(m_curline-1));
					if (*bit)
					{
						m_vmudlines.pop_back();
						m_curline--;
					}
					m_capture.at(i)--;
					mw->SetScrollPage();
					mw->Refresh();
					mw->Update();
				}
			}
			for (i=0, it=m_capwin.begin(), lit=m_capture.begin(), bit=m_capgag.begin(); it!=m_capwin.end(); it++, lit++, bit++, i++)
			{
				if (*lit<=0)
				{
					m_capwin.erase(it);
					m_capture.erase(lit);
					m_capgag.erase(bit);
					it = m_capwin.begin()+i;
					lit = m_capture.begin()+i;
					bit = m_capgag.begin()+i;
					if (it==m_capwin.end())
						break;
				}
			}
		}

		//should we lock the prompt?
		if (m_boprompt)
		{
			int x, y;
			wxString s = wxEmptyString;
			s += m_vmudlines.at(m_curline-1).GetLineText();
			m_parent->m_prompt->GetTextExtent(s, &x, &y);
			if (m_prompt->Match(s, false))
			{
				if (m_gagprompt) //should we gag the original prompt?
				{
					m_vmudlines.pop_back();
					m_curline--;
				}
				m_parent->m_mgr.GetPane(wxT("amcprompt")).Position(0).BestSize(x+10,24).Fixed();
				if (!m_parent->m_mgr.GetPane(wxT("amcprompt")).IsShown())
				{
					
					m_parent->m_mgr.GetPane(wxT("amcinput")).Position(1);
					m_parent->m_mgr.GetPane(wxT("amctoggle")).Position(2);
					m_parent->m_mgr.GetPane(wxT("amcprompt")).Show();	
				}
				m_parent->m_mgr.Update();
				m_parent->m_prompt->Clear();
				m_parent->m_prompt->AppendText(s);
			}
		}
		if (m_vmudlines.at(m_curline-1).GetGagme())
		{
			m_vmudlines.pop_back();
			m_curline--;
		}

		//::wxLogDebug(wxT("time: %ld ms, %s"), sw.Time(), sLine.c_str());
    //} while (pos<index-1);
	}
}

void MudWindow::ParseBufferMXP(char *Buffer)
{
	/*if (m_parent->GetGlobalOptions()->UseMCCP() && !m_mccp2 && m_mccpneg)//compression not on, manually started?
		ParseBuffer(Buffer);
	else*/
	wxString s;
	if (!m_parent->GetGlobalOptions()->UseUTF8())	
		s = wxString::From8BitData((const char*) Buffer);
	else
	{
		//wxString f(Buffer, wxCSConv(m_parent->GetGlobalOptions()->GetCurEncoding()));
		//s=f;
		//if (f.empty()&& wxStrlen(Buffer)>0)
		//{
		s = wxString::From8BitData((const char*) Buffer);
		//}
	}
	//wxString s;
	//s = wxString::From8BitData((const char*)Buffer);
	m_MXP->Parse(s);
}

void MudWindow::ParseNBuffer(char* cBuffer, bool b)
{
	//try a state machine^^
//static int state = HAVE_TEXT;
static wxString sLine = wxEmptyString;
static wxString esc = wxEmptyString;
static AnsiLine line;
static AnsiLineElement style[2000];
static int index=0;
static wxString atcp = wxEmptyString;
int pos=0;
//int apos=0
int aoldpos=0;
static int opos=0;
wxString s;
static long col1=0, col2=0, col3=0;
int offset=30;
bool gotline = false;
static bool ttsent = false;
static bool colset = false;
//static bool bol = false;
	Freeze();
	if (!m_parent->GetGlobalOptions()->UseUTF8())	
		s = wxString::From8BitData((const char*) cBuffer);
	else
	{
		//if (cBuffer[0]==(char)IAC)
		//	s = wxString::From8BitData((const char*) cBuffer);
		//else
		{
			//wxString f(cBuffer, wxCSConv(m_parent->GetGlobalOptions()->GetCurEncoding()));
			//s=f;
			//if (f.empty()&& wxStrlen(cBuffer)>0)
			//{
			#ifdef __WXGTK__
			s = wxString(cBuffer);
			//s = wxString::From8BitData((const char*) cBuffer);
			if (s.empty())
				s = wxString::From8BitData((const char*)cBuffer);
			#endif
			#ifdef WXOSX__
			s = wxString(cBuffer);
			//s = wxString::From8BitData((const char*) cBuffer);
			if (s.empty())
				s = wxString::From8BitData((const char*)cBuffer);
			#endif
			
			#ifdef __WXMSW__
			s = wxString::From8BitData((const char*) cBuffer);
			#endif
				//wxString ff(s.To8BitData(), wxCSConv(m_parent->GetGlobalOptions()->GetCurEncoding()));
				//s=ff;
			//}
		}
	}
	//s = wxString::FromAscii(cBuffer);	
	wxString::iterator it;
		
	if (m_vmudlines.empty())
		m_parsestate = HAVE_TEXT;
	
	//if (s.EndsWith('\n'));
		//sLine.Empty();
	if (m_bourl)//Clickable URLs
	{
		int spos = 0;
		
		bool b = m_parent->GetGlobalOptions()->UseUTF8();
		m_parent->GetGlobalOptions()->SetUTF8(false);
		while (m_url->Match(s.Mid(spos), false, true))
		{
			int start=0;
			int sub=0;
			sub = m_url->GetMatchStart()-8;//some stuff cause ansicodes can mess regexp detection of URL
			if (sub<0)
				sub=0;
			int xx = m_url->GetMatchLen();
			wxString test = s.Mid(sub+spos, xx);
			
			bool b = m_ansicode->Match(test, false);
			//bool b = m_ansicode->Match(s.substr(spos-8, m_url->GetMatchLen()), false);
			if (!b)
				sub=0;
			//if (b && m_url->GetMatchStart()<m_ansicode->GetMatchEnd()+spos+1)
			if (b)
			{
				if (m_url->GetMatchStart()<m_ansicode->GetMatchEnd()+sub+1)
					start = m_ansicode->GetMatchEnd()+sub;
				else if (m_url->GetMatchStart()==m_ansicode->GetMatchEnd()+sub+1)
					start = m_ansicode->GetMatchEnd()+1+sub;
				else
					start = m_url->GetMatchStart();
			}       
			if (!b)
				start = m_url->GetMatchStart();
			if (spos)
				start += spos;
			if (!sub && !m_url->GetMatchStart())
				start=0;
			m_url->Match(s.Mid(start));
			xx=m_url->GetMatchLen();
			test = s;
			
			wxString s1 = test.Left(start);
			wxString s2 = test.Mid(start, xx);
			wxString s3 = test.Mid(start+xx);
			s = s1<<"\x1b[4m"<<s2<<"\x1b[0m"<<s3;
			
			//s = s.insert(start+sub, "\x1b[4m");
			//s= s.insert(m_url->GetMatchEnd()+4+spos, "\x1b[0m");
			//spos += m_url->GetMatchEnd()+4;
			spos = start+xx+8;
		}
		m_parent->GetGlobalOptions()->SetUTF8(b);
	}
	if (!m_vmudlines.empty())
	{
		if (!b)
			sLine.Empty();
		if (!m_vmudlines.back().IsFull() && !gotline) 
		{
			line = m_vmudlines.back();
			if (!b)
				sLine.Empty();
		}
	}
	m_indexstart = line.m_vstyle.size();
	
	for (it=s.begin()+pos;it!=s.end();it++, pos++)
	{
		switch (m_parsestate)
		{
			case HAVE_TEXT:
				if (*it=='\n')
				{
					m_parsestate = HAVE_LINE;
					break;
				}
				if (*it=='\r')
				{
					m_parsestate = HAVE_LF;
					break;
				}
				if (*it=='!' && m_msp)
				{				
					m_parsestate = HAVE_MSP1;
					sLine.Append(*it);
					break;
				}
				if (*it==BELL)
				{
					wxBell();
					break;
				}
				if (*it==ESC)
				{
					m_parsestate = HAVE_ESC;
					//if (pos>opos)
					//{
					if (!m_vmudlines.empty())
					{
						if (!m_vmudlines.back().IsFull() && !gotline) 
						{
							line = m_vmudlines.back();
							if (b)
								line.m_vstyle.pop_back();
							m_indexstart = line.m_vstyle.size();
							gotline = true;
							//sLine.Empty();
						}
					}
					sLine.Replace("\t", "    ");
					style[index].SetText(sLine);
					if (m_bourl)
					{	
						if (m_url->Match(style[index].GetText(), false))
							style[index].SetURL(true);
					}
					//opos=pos;
					line.m_vstyle.push_back(style[index++]);
					m_indexend=line.m_vstyle.size();
					line.SetLineText(sLine);
					sLine.Empty();
					//}
				break;
				}
				if (*it==IAC)
				{
					m_parsestate = HAVE_IAC;
					if (!m_vmudlines.empty())
					{
						if (!m_vmudlines.back().IsFull() && !gotline)
						{
							line = m_vmudlines.back();
							gotline = true;
							if (b)
								line.m_vstyle.pop_back();
							m_indexstart = line.m_vstyle.size();
							//sLine.Empty();
						}
					}
					//if (pos>opos)
					//{	
					sLine.Replace("\t", "    ");	
					style[index].SetText(sLine);
					//opos=pos;
					if (m_bourl)
					{	
						if (m_url->Match(style[index].GetText(), false))
							style[index].SetURL(true);
					}
					line.m_vstyle.push_back(style[index++]);
					m_indexend=line.m_vstyle.size();
					line.SetLineText(sLine);
					sLine.Empty();
					//}
				break;
				}
				sLine.Append(*it);
				break;
			case HAVE_LF:
				m_parsestate = HAVE_TEXT;
				if (it!=s.begin())
				{
					it--;
					pos--;
				}
				//sLine.Replace('\r', "");
				break;
			case HAVE_LINE:
				{
				//sLine.Trim();
				//if (pos>opos)
				//{
					
					sLine.Replace("\t", "    ");
					style[index].SetText(sLine);
					if (m_bourl)
					{	
						if (m_url->Match(style[index].GetText(), false))
							style[index].SetURL(true);
					}
					if (!m_vmudlines.empty())
					{
						if (!m_vmudlines.back().IsFull() && !gotline)
						{
							line = m_vmudlines.back();
							gotline = true;
							if (b)
								line.m_vstyle.pop_back();
							m_indexstart = line.m_vstyle.size();
						}
					}
					line.m_vstyle.push_back(style[index++]);
					m_indexend=line.m_vstyle.size();
					line.SetLineText(sLine);
				
				line.SetFull(true);
				if (!m_vmudlines.empty())
				{
					if (!m_vmudlines.back().IsFull())
					{
						m_vmudlines.pop_back();
						m_curline--;
					}
				}
				gotline = false;
				if (m_curline==0)
					line.SetLinenumber(m_curline);
				else
				{
					if (m_curline-1>m_vmudlines.size())
					m_curline = m_vmudlines.size();
					line.SetLinenumber(m_vmudlines.back().GetLinenumber()+1);
				}
				int idx = m_parent->GetDefVarIndexByLabel("amcLines");
				wxString l;
				l << line.GetLinenumber();
				m_parent->GetDefVars()->at(idx).SetValue(l);
				wxDateTime d;
				d = wxDateTime::UNow();
				line.SetDateTimeMS(d);
				d = wxDateTime::Now();
				line.SetDateTime(d);
				line.SetAnsiLine(s.SubString(aoldpos, it-s.begin()-1));
				aoldpos = it-s.begin()+1;
				//line.SetAnsiLine(*sLine);
				if (!line.GetGagme())
				{
					m_vmudlines.push_back(line);
					m_curline++;
				}
				
				m_indexend = index;
				//line.m_vstyle.clear();
				AnsiLine newline;
				line=newline;
				
				for (int i=0;i<=index;i++)
				{
					style[i].SetFontStyle(0);
					style[i].SetURL(false);
					style[i].SetText("");
					style[i].SetFCol(7, m_colansi[7]);
					style[i].SetBCol(0, m_colansi[0]);
				}
				index=0;
				if (!m_vmudlines.empty())
				{
					if (!m_vmudlines.back().m_vstyle.empty())
					{
						AnsiLineElement last = m_vmudlines.back().m_vstyle.back();
						style[index].SetFCol(last.GetFColIndex(), last.GetFCol());
						style[index].SetBCol(last.GetBColIndex(), last.GetBCol());
						style[index].SetFontStyle(last.GetFontStyle());
					}
				}
				sLine.Empty();
				
				if (m_curline>=GetMaxLines())
				{		
					m_curline--;
					m_vmudlines.pop_front();
				}
				if (IsLogging())
					SendLineToLog(m_curline-1);
				CheckTrigger(m_curline-1, true);
				RedirectWindow();
				if (it!=s.begin())
				{
					it--;
					aoldpos--;
				}
				m_parsestate = HAVE_TEXT;
				//Update();
				break;
				}
			case HAVE_ESC:
				if (*it==BR)
					m_parsestate = HAVE_ESCBR;
				else
				{
					sLine.Append(*it);
					m_parsestate = HAVE_TEXT;
				}
				break;
			case HAVE_ESCBR:
				if (*it==';')
				{
					m_parsestate = HAVE_DELIMITER1;
					esc.ToLong(&col1);
					if (col1<30 || (col1>39 && col1<48) || (col1>89 && col1<110) )
						SwitchColor(col1, offset, &style[index]);
					colset = true;
					esc.Empty();
					break;
				}
				if (*it=='z')
				{
					esc.Empty();
					m_parsestate = HAVE_TEXT;
					//m_mxp=true;!!!???
					break;
				}
				if (*it=='H')
				{
					esc.Empty();
					m_parsestate = HAVE_TEXT;
					break;
				}
				if (*it=='J')
				{
					esc.ToLong(&col1);
					if (col1==2) //Clear screen
					{
						m_parsestate = HAVE_TEXT;
						wxSize ss;
						ss=GetClientSize();
						wxClientDC dc(this);
						dc.SetFont(*m_font);
						int s_lines = ss.GetHeight()/dc.GetCharHeight();
						for(int x=0;x<s_lines;x++)
							ParseNBuffer((char*)"\n", false);
					}
					esc.Empty();
					break;
				}
				if (*it=='c') //ESC[0c identify terminal type
				{
					esc.Empty();
					m_parsestate=HAVE_TEXT;
					break;
				}
				if (*it=='m')
				{
					if (esc==wxEmptyString)
						col1=0;
					else
						esc.ToLong(&col1);
					if (index)
					{
						style[index].SetFCol(style[index-1].GetFColIndex(), style[index-1].GetFCol());
						style[index].SetBCol(style[index-1].GetBColIndex(), style[index-1].GetBCol());
						style[index].SetFontStyle(style[index-1].GetFontStyle());
					}
					else if (!index)
					{
						if (!m_vmudlines.empty())
						{
							if (!m_vmudlines.back().m_vstyle.empty())
							{
								AnsiLineElement last = m_vmudlines.back().m_vstyle.back();
								style[index].SetFCol(last.GetFColIndex(), last.GetFCol());
								style[index].SetBCol(last.GetBColIndex(), last.GetBCol());
								style[index].SetFontStyle(last.GetFontStyle());
							}
						}
					}
					SwitchColor(col1, offset, &style[index]);
					m_parsestate = HAVE_TEXT;
					colset = true;
					//gotline = false;
					esc.Empty();
					break;
				}
				esc.Append(*it);
				break;
			case HAVE_DELIMITER1:
				if (*it==';')
				{
					m_parsestate = HAVE_DELIMITER2;
					esc.ToLong(&col2);
					
					if (col1==1)
						offset-=8;
					SwitchColor(col2, offset, &style[index]);
					offset=30;
					colset = true;
					esc.Empty();
					break;
				}
				if (*it=='m')
				{
					esc.ToLong(&col2);
					
					if (index && !colset)
					{
						style[index].SetFCol(style[index-1].GetFColIndex(), style[index-1].GetFCol());
						style[index].SetBCol(style[index-1].GetBColIndex(), style[index-1].GetBCol());
						style[index].SetFontStyle(style[index-1].GetFontStyle());
					}
					else if(!index)
					{
					if (!m_vmudlines.empty())
						{
							if (!m_vmudlines.back().m_vstyle.empty())
							{
								AnsiLineElement last = m_vmudlines.back().m_vstyle.back();
								style[index].SetFCol(last.GetFColIndex(), last.GetFCol());
								style[index].SetBCol(last.GetBColIndex(), last.GetBCol());
								style[index].SetFontStyle(0);
								style[index].SetURL(false);
							}
						}
					}
					if (!col1)
						SwitchColor(col1, offset, &style[index]);
					if (col1==1)
						offset-=8;
					SwitchColor(col2, offset, &style[index]);
					offset=30;
					m_parsestate = HAVE_TEXT;
					colset = true;
					esc.Empty();
					break;
				}
				esc.Append(*it);
				break;
			case HAVE_DELIMITER2:
				if (*it=='m' || *it==';')
				{
					esc.ToLong(&col3);
					if (col1==38 && col2==5)
					{
						if (col3>255)
							col3=7;
						if (colset)
							index--;
						style[index].SetFCol(99, m_xterm[col3]);
						m_parsestate = HAVE_TEXT;
						m_curansicolor=m_xterm[col3];
						colset = true;
						esc.Empty();
						break;
					}
					if (col1==48 && col2==5)
					{
						if (col3>255)
							col3=7;

						if(colset)
							index--;
						style[index].SetBCol(99, m_xterm[col3]);
						m_parsestate = HAVE_TEXT;
						//m_curansicolor=m_xterm[col3];
						colset = true;
						esc.Empty();
						break;
					}
					if (col2==1)
						offset-=8;
					SwitchColor(col3, offset, &style[index]);
					offset=30;
					m_parsestate = HAVE_TEXT;
					
					colset = true;
					if (*it==';')
					{
						m_parsestate = HAVE_DELIMITER2;
						//colset=false;
					}
					esc.Empty();
					break;
				}
				/*if (*it==';')
				{
					m_parsestate = HAVE_ESCBR;
					esc.Empty();
					break;
				}*/
				esc.Append(*it);
				break;
			case HAVE_IAC:
				if (*it==IAC)//IAC IAC
				{
					m_parsestate = HAVE_TEXT;
					sLine.Append(*it);
					break;
				}
				if (*it==GA || *it==EOR)
				{
					m_parsestate = HAVE_TEXT;
					if (m_parent->GetGlobalOptions()->UseGAEOR())
						m_parsestate = HAVE_LINE;
					else
						sLine.Append(wxEmptyString);
					
				}
				
				if (*it==WILL)
					m_parsestate = HAVE_IACWILL;
				if (*it==DO)
					m_parsestate = HAVE_IACDO;
				if (*it==WONT)
					m_parsestate = HAVE_IACWONT;
				if (*it==DONT)
					m_parsestate = HAVE_IACDONT;
				if (*it==SB)
					m_parsestate = HAVE_IACSB;
				break;
			case HAVE_IACWILL:
				m_parsestate = HAVE_TEXT;
				if (*it==SEND)
				{
					m_password = true;
					break;
				}
				if (*it==WILLEOR)
				{
					if (m_parent->GetGlobalOptions()->UseGAEOR())
					{
						wxString s;
						s.Printf("%c%c%c", IAC, DO, WILLEOR);
						Write8Bit(s);
						//m_sock->Write(s.To8BitData(), 3);
					}
					else
					{
						wxString s;
						s.Printf("%c%c%c", IAC, DONT, WILLEOR);
						Write8Bit(s);
						//m_sock->Write(s.To8BitData(), 3);
					}
					break;	
				}
				if (*it==TELOPT_COMPRESS2)
				{
					if (!m_mccp2)
					{
						if (m_parent->GetGlobalOptions()->UseMCCP())
						{
							wxString s;
							s.Printf("%c%c%c", IAC, DO, TELOPT_COMPRESS2);
							//m_sock->Write(s.To8BitData(), s.length());
							Write8Bit(s);
							m_mccpneg = true;
							Msg(_("MCCP2 agreed!"));
						}
						else
						{
							wxString s;
							s.Printf("%c%c%c", IAC, DONT, TELOPT_COMPRESS2);
							//m_sock->Write(s, s.length());
							Write8Bit(s);
							//m_sock->Write("\xff\xfe\x56", 3); //IAC DONT MCCP
						}
					}
					break;
				}
				if (*it==TELOPT_COMPRESS)
				{
					wxString s;
					s.Printf("%c%c%c", IAC, DONT, TELOPT_COMPRESS);
					Write8Bit(s);
					//m_sock->Write("\xff\xfe\x55", 3);
					break;
				}                 
				if (*it==MSP)
				{
					if (m_parent->GetGlobalOptions()->UseMSP())
					{
						//m_sock->Write("\xff\xfd\x5a", 3);
						wxString s;
						s.Printf("%c%c%c", IAC, DO, MSP);
						//m_sock->Write(s.To8BitData(), 3);
						Write8Bit(s);
						m_msp = true;
						Msg(_("MSP enabled!"));
					}
					else
					{
						//m_sock->Write("\xff\xfe\x5a", 3);
						wxString s;
						s.Printf("%c%c%c", IAC, DONT, MSP);
						Write8Bit(s);
						//m_sock->Write(s.To8BitData(), 3);
						m_msp = false;
						Msg(_("MSP denied!"));
					}
					break;
				}
				if (*it==MXP)
				{
					if (m_parent->GetGlobalOptions()->UseMXP())
					{
						wxString s;
						s.Printf("%c%c%c", IAC, DO, MXP);
						Write8Bit(s);
						//m_sock->Write(s.To8BitData(), 3);
						m_mxp = true;
						Msg(_("MXP enabled!"));
					}
					else
					{
						m_mxp=false;
						wxString s;
						s.Printf("%c%c%c", IAC, DONT, MXP);
						//m_sock->Write(s.To8BitData(), 3);
						Write8Bit(s);
						Msg(_("MXP denied!"));
					}
					break;
				}
				if (*it== SUPPRESS_GO_AHEAD)
				{
					wxString s;
					s.Printf("%c%c%c", IAC, DO, SUPPRESS_GO_AHEAD);
					//m_sock->Write(s.To8BitData(), (wxUint32)s.length());
					Write8Bit(s);
					break;
				}
				if (*it== NAWS)
				{
					if (m_parent->GetGlobalOptions()->UseNAWS())
					{
						wxString s;
						wxSize ss;
						s.Printf("%c%c%c", IAC, WILL, NAWS);
						//m_sock->Write(s.To8BitData(), (wxUint32)s.length());
						Write8Bit(s);
						Msg(_("NAWS agreed!"));
						ss=GetClientSize();
						wxClientDC dc(this);
						dc.SetFont(*m_font);
						int s_lines = ss.GetHeight()/dc.GetCharHeight();
						int s_chars = ss.GetWidth()/dc.GetCharWidth();
						char c[10];
						c[0]=(char)IAC;
						c[1]=(char)SB;
						c[2]=(char)NAWS;
						c[3]=(char)HIBYTE(s_chars);
						c[4]=(char)LOBYTE(s_chars);
						c[5]=(char)HIBYTE(s_lines);
						c[6]=(char)LOBYTE(s_lines);
						c[7]=(char)IAC;
						c[8]=(char)SE;
						//m_sock->Write(c, 9);
						Write8Bit(wxString(c, 9));
					}
					else
					{
						wxString s;
						s.sprintf("%c%c%c", IAC, WONT, NAWS);
						Write8Bit(s);
						//m_sock->Write(s.To8BitData(), 3);
					}
					break;
				}
				if (*it==AARD1)
				{
					if (m_parent->GetGlobalOptions()->UseAard())
					{
						wxString s;
						s.sprintf("%c%c%c", IAC, DO, AARD1);
						Write8Bit(s);
					}
					else
					{
						wxString s;
						s.sprintf("%c%c%c", IAC, DONT, AARD1);
						Write8Bit(s);
					}
					//m_sock->Write8Bit(s.To8BitData(), 3);
					//Msg(_("AARD telnet negotiated!"));
					break;
				}
				if (*it==ATCP)
				{
					if (m_parent->GetGlobalOptions()->UseATCP())
					{
						wxString s;
						s.Printf("%c%c%c", IAC, DO, ATCP);
						//m_sock->Write(s.To8BitData(), (wxUint32)3);
						Write8Bit(s);
						Msg(_("ATCP negotiated!"));
						m_atcp = true;
						m_parent->luaCreateATCPTable();
						
					}
					else
					{
						wxString s;
						s.Printf("%c%c%c", IAC, DONT, ATCP);
						Write8Bit(s);
						//m_sock->Write(s.To8BitData(), (wxUint32)3);
					}
					break;
				}
				if (*it==ATCP2)
				{
					if (m_parent->GetGlobalOptions()->UseATCP2())
					{
						wxString s;
						s.Printf("%c%c%c", IAC, DO, ATCP2);
						//m_sock->Write(s.To8BitData(), (wxUint32)3);
						Write8Bit(s);
						Msg(_("GMCP negotiated!"));
						m_atcp2 = true;
						m_parent->luaCreateGMCPTable();
						
					}
					else
					{
						wxString s;
						s.Printf("%c%c%c", IAC, DONT, ATCP2);
						Write8Bit(s);
						//m_sock->Write(s.To8BitData(), (wxUint32)3);
					}
					break;
				}
				if (*it== TERMINAL_TYPE)
				{
					wxString s;
					s.Printf("%c%c%c", IAC, DO, TERMINAL_TYPE);
					//m_sock->Write(s.To8BitData(), (wxUint32)3);
					Write8Bit(s);
					//Msg(_("Terminal type requested!"));
					break;
				}
				if (*it==ZMP)
				{
					wxString s;
					s.Printf("%c%c%c", IAC, DONT , ZMP);
					//m_sock->Write(s.To8BitData(), (wxUint32)3);
					Write8Bit(s);
					break;
				}
				if (*it== MSSP)
				{
					wxString s;
					s.Printf("%c%c%c", IAC, DONT , MSSP);
					//m_sock->Write(s.To8BitData(), (wxUint32)3);
					Write8Bit(s);
					break;
				}
				if (*it== MSDP)
				{
					if (m_parent->GetGlobalOptions()->UseMSDP())
					{
						wxString s;
						s.Printf("%c%c%c", IAC, DO , MSDP);
						//m_sock->Write(s.To8BitData(), (wxUint32)3);
						Write8Bit(s);
						m_msdp = true;
						Msg(_("MSDP negotiated!"));
						m_parent->luaCreateMSDPTable();
					}
					else
					{
						wxString s;
						s.Printf("%c%c%c", IAC, DONT, MSDP);
						//m_sock->Write(s.To8BitData(), (wxUint32)3);
						Write8Bit(s);
						m_msdp = false;
					}
					break;
				}
				if (*it== NEW_ENVIRON)
				{
					wxString s;
					s.Printf("%c%c%c", IAC, DONT , NEW_ENVIRON);
					//m_sock->Write(s.To8BitData(), (wxUint32)3);
					Write8Bit(s);
					break;
				}
				else
				{
					wxString s;
					s.Printf("%c%c%c", IAC, DONT , *it);
					Write8Bit(s);
					break;
				}
				break;
			
			case HAVE_IACDO:
				m_parsestate = HAVE_TEXT;
				if (*it==TELOPT_COMPRESS)
				{
					wxString s;
					s.Printf("%c%c%c", IAC, WONT, TELOPT_COMPRESS);
					Write8Bit(s);
					//m_sock->Write(s.To8BitData(), (wxUint32)3);
					break;
				}
				if (*it==TERMINAL_TYPE)
				{
					wxString s;
					s.Printf("%c%c%c", IAC, WILL, TERMINAL_TYPE);
					Write8Bit(s);
					//Msg(_("Terminal type requested!"));
					break;
				}
				if (*it==NAWS)
				{
					if (m_parent->GetGlobalOptions()->UseNAWS())
					{
						wxString s;
						wxSize ss;
						s.Printf("%c%c%c", IAC, WILL, NAWS);
						Write8Bit(s);
						//m_sock->Write(s.To8BitData(), (wxUint32)3);
						//Msg(_("NAWS agreed!"));
						ss=GetClientSize();
						wxClientDC dc(this);
						dc.SetFont(*m_font);
						ss=GetClientSize();
						int s_lines = ss.GetHeight()/dc.GetCharHeight();
						int s_chars = ss.GetWidth()/dc.GetCharWidth();
						//int x = HIBYTE(s_chars);
						char c[10];
						c[0]=(char)IAC;
						c[1]=(char)SB;
						c[2]=(char)NAWS;
						c[3]=(char)HIBYTE(s_chars);
						c[4]=(char)LOBYTE(s_chars-1);
						c[5]=(char)HIBYTE(s_lines);
						c[6]=(char)LOBYTE(s_lines);
						c[7]=(char)IAC;
						c[8]=(char)SE;
						//m_sock->Write(c, 9);
						Write8Bit(wxString(c, 9));
						break;
					}
				}
				if (*it== MXP)
				{
					wxString s;
					if (m_parent->GetGlobalOptions()->UseMXP())
					{
						s.Printf("%c%c%c", IAC, WILL, MXP);
						//m_sock->Write(s.To8BitData(), (wxUint32)s.length());
						Write8Bit(s);
						Msg(_("MXP enabled!"));
						m_mxp = true;
					}
					else
					{
						s.Printf("%c%c%c", IAC, WONT, MXP);
						//m_sock->Write(s.To8BitData(), (wxUint32)s.length());
						Write8Bit(s);
						m_mxp = false;
						Msg(_("MXP denied!"));
					}
					break;
				}
				if (*it==AARD1)
				{
					if (m_parent->GetGlobalOptions()->UseAard())
					{
						wxString s;
						s.sprintf("%c%c%c", IAC, WILL, AARD1);
						Write8Bit(s);
					}
					else
					{
						wxString s;
						s.sprintf("%c%c%c", IAC, WONT, AARD1);
						Write8Bit(s);
					}
					//m_sock->Write(s.To8BitData(), 3);
					break;
				}
				if (*it==ATCP)
				{
					if (m_parent->GetGlobalOptions()->UseATCP())
					{
						wxString s;
						s.Printf("%c%c%c", IAC, WILL, ATCP);
						//m_sock->Write(s.To8BitData(), (wxUint32)3);
						Write8Bit(s);
						m_atcp = true;
						m_parent->luaCreateATCPTable();
						
					}
					else
					{
						wxString s;
						s.Printf("%c%c%c", IAC, WONT, ATCP);
						Write8Bit(s);
						//m_sock->Write(s.To8BitData(), (wxUint32)3);
						m_atcp = false;
					}
					break;
				}
				if (*it== NEW_ENVIRON)
				{
					wxString s;
					s.Printf("%c%c%c", IAC, WONT , NEW_ENVIRON);
					//m_sock->Write(s.To8BitData(), (wxUint32)3);
					Write8Bit(s);
					break;
				}
				if (*it==CHARSET)
				{
					wxString s;
					if (m_parent->GetGlobalOptions()->UseUTF8())
					{
						s.Printf("%c%c%c", IAC, WILL, CHARSET);
						Write8Bit(s);
					}
					else
					{
						s.Printf("%c%c%c", IAC, WONT, CHARSET);
						Write8Bit(s);
					}
				}
				else
				{
					wxString s;
					s.Printf("%c%c%c", IAC, WONT , *it);
					//m_sock->Write(s.To8BitData(), (wxUint32)3);
					Write8Bit(s);
					break;
				}
				
				//break;
				break;
			case HAVE_IACWONT:
				if (*it== SEND)
					m_password = false;
				m_parsestate = HAVE_TEXT;
				break;
			case HAVE_IACDONT:
				m_parsestate = HAVE_TEXT;
				break;
			case HAVE_IACSB:
				if (*it==TELOPT_COMPRESS2)
					m_parsestate = HAVE_IACSBCOMPRESS2;
				if (*it== TERMINAL_TYPE)
					m_parsestate = HAVE_IACSBTT;
				if (*it== MXP)
					m_parsestate = HAVE_IACSBMXP;
				if (*it==AARD1)
					m_parsestate = HAVE_IACSBAARD;
				if (*it==ATCP)
					m_parsestate = HAVE_IACSBATCP;
				if (*it==ATCP2)
					m_parsestate = HAVE_IACSBATCP2;
				if (*it==MSDP)
					m_parsestate = HAVE_IACSBMSDP;
				if (*it==CHARSET)
					m_parsestate = HAVE_IACSBCHARSET;
				break;
			case HAVE_IACSBCOMPRESS2:
				if (*it==SE)
				{
					m_mccp2 = true;
					m_parsestate = HAVE_COMPRESS_START;
					 
				}
				break;
			case HAVE_IACSBTT:
				if (*it==SE &&!ttsent)
				{
					//wxString s;
					char c[13];
					c[0]=(char)IAC;
					c[1]=(char)SB;
					c[2]=(char)TERMINAL_TYPE;
					c[3]=(char)IS;
					c[4]='w';
					c[5]='x';
					c[6]='A';
					c[7]='M';
					c[8]='C';
					c[9]='L';
					c[10]=(char)IAC;
					c[11]=(char)SE;
					//m_sock->Write(c, 12);
					Write8Bit(wxString(c, 12));
					ttsent = true;
					m_parsestate = HAVE_TEXT;
				}
				else if (*it==SE && ttsent)
				{
					char c[12];
					c[0]=(char)IAC;
					c[1]=(char)SB;
					c[2]=(char)TERMINAL_TYPE;
					c[3]=(char)IS;
					c[4]='A';
					c[5]='N';
					c[6]='S';
					c[7]='I';
					c[8]=(char)IAC;
					c[9]=(char)SE;
					//m_sock->Write(c, 10);
					Write8Bit(wxString(c, 10));
					//ttsent = false;
					m_parsestate = HAVE_TEXT;
				}
				break;
			case HAVE_IACSBMXP:
				if (*it==SE)
				{
					index--;
					m_parsestate = HAVE_TEXT;
				}
				break;
			case HAVE_IACSBAARD:
				if (*it==SE)
				{
					if (m_parent->GetGlobalOptions()->GetUseEvents() && m_parent->GetGlobalOptions()->GetUseEvTelnetData())
					{
						wxString ss;
						ss = wxString::Format("%cfunc(\"%s\", \"OnTelnetData(\'%d\',\'%s')\")", m_parent->GetGlobalOptions()->GetCommand(),
							m_parent->GetGlobalOptions()->GetEventFile(), 102, m_atcpstring.c_str());
						m_parent->m_input->ParseCommandLine(&ss);
					}
					m_parsestate = HAVE_TEXT;
					m_atcpstring.Empty();
					if (line.GetLineText()==wxEmptyString && line.m_vstyle.size()<=1)
					{
						line.SetGagme(true);
						m_parsestate = HAVE_LINE;
					}
				}
				else if (*it!=IAC)
					m_atcpstring.Append(*it);
				break;
			case HAVE_IACSBATCP:
				if (*it==SE)
				{
					m_atcpstring.Replace("\n", " ");
					m_atcpstring.Replace("\x1b[4m", "");
					m_atcpstring.Replace("\x1b[0m", "");
					if (m_parent->GetGlobalOptions()->GetUseEvents() && m_parent->GetGlobalOptions()->GetUseEvTelnetData())
					{
						wxString ss;
						ss = wxString::Format("%cfunc(\"%s\", \"OnTelnetData(\'%d\',\'%s')\")", m_parent->GetGlobalOptions()->GetCommand(),
							m_parent->GetGlobalOptions()->GetEventFile(), 200, m_atcpstring.c_str());
						m_parent->m_input->ParseCommandLine(&ss);
					}
					m_parsestate = HAVE_TEXT;
					if (m_atcpstring.StartsWith("Room.Num"))
					{
						lua_getglobal(m_L->GetLuaState(), "ATCP");
						//lua_getfield(m_L->GetLuaState(), -1, "RoomNum");
						wxString s = m_atcpstring.AfterFirst(' ');
						lua_pushstring(m_L->GetLuaState(), s.c_str());
						lua_setfield(m_L->GetLuaState(), -2, "RoomNum");
					}
					if (m_atcpstring.StartsWith("Room.Brief"))
					{
						lua_getglobal(m_L->GetLuaState(), "ATCP");
						//lua_getfield(m_L->GetLuaState(), -1, "RoomNum");
						wxString s = m_atcpstring.AfterFirst(' ');
						lua_pushstring(m_L->GetLuaState(), s.c_str());
						lua_setfield(m_L->GetLuaState(), -2, "RoomBrief");
					}
					if (m_atcpstring.StartsWith("Room.FullExits"))
					{
						lua_getglobal(m_L->GetLuaState(), "ATCP");
						//lua_getfield(m_L->GetLuaState(), -1, "RoomNum");
						wxString s = m_atcpstring.AfterFirst(' ');
						lua_pushstring(m_L->GetLuaState(), s.c_str());
						lua_setfield(m_L->GetLuaState(), -2, "RoomFullExits");
					}
					if (m_atcpstring.StartsWith("Room.Environment"))
					{
						lua_getglobal(m_L->GetLuaState(), "ATCP");
						//lua_getfield(m_L->GetLuaState(), -1, "RoomNum");
						wxString s = m_atcpstring.AfterFirst(' ');
						lua_pushstring(m_L->GetLuaState(), s.c_str());
						lua_setfield(m_L->GetLuaState(), -2, "RoomEnvironment");
					}
					if (m_atcpstring.StartsWith("Room.Coordinates"))
					{
						lua_getglobal(m_L->GetLuaState(), "ATCP");
						//lua_getfield(m_L->GetLuaState(), -1, "RoomNum");
						wxString s = m_atcpstring.AfterFirst(' ');
						lua_pushstring(m_L->GetLuaState(), s.c_str());
						lua_setfield(m_L->GetLuaState(), -2, "RoomCoordinates");
					}
					m_atcpstring.Empty();
					if (line.GetLineText()==wxEmptyString && line.m_vstyle.size()<=1)
					{
						line.SetGagme(true);
						m_parsestate = HAVE_LINE;
					}
				}
				else if (*it!=IAC)
					m_atcpstring.Append(*it);
				break;
			case HAVE_IACSBATCP2:
				if (*it==SE)
				{
					//m_atcpstring.Replace("\n", " ");
					
					m_atcpstring.Replace("\x1b[4m", "");
					m_atcpstring.Replace("\x1b[0m", "");
					m_parsestate = HAVE_TEXT;
					wxSetWorkingDirectory(m_parent->GetGlobalOptions()->GetWorkDir());
					wxFile* file = new wxFile("debuggmcp.txt", wxFile::write_append);
					file->Write(m_atcpstring+"\n");
					file->Close();
					delete file;
					if (m_atcpstring.empty())
					{
						index--;
						break;
					}
					wxString s = m_atcpstring.AfterFirst(' ');
					wxString code;
					wxString v = m_atcpstring.BeforeFirst(' ');
					v.Replace(".", "");
					code<<v;
					s_it fit = find(m_gmcpmods.begin(), m_gmcpmods.end(), code);
					if (fit==m_gmcpmods.end())
						m_gmcpmods.push_back(code);
					code<<" = js.decode([=["<<s<<"]=])";
					luaL_dostring(m_L->GetLuaState(), code.c_str());
					
					
					lua_getglobal(m_L->GetLuaState(), v.c_str());
					if (lua_type(m_L->GetLuaState(),-1)==LUA_TTABLE)
					{
						lua_getglobal(m_L->GetLuaState(), "wxamcl");
						lua_getfield(m_L->GetLuaState(), -1, "GMCP");
						lua_getglobal(m_L->GetLuaState(), v.c_str());
						lua_setfield(m_L->GetLuaState(), -2, v.c_str());
					}
					//lua_getfield(m_L->GetLuaState(), -1, "RoomNum");
					//lua_pushstring(m_L->GetLuaState());
					
					
					/*wxString info = _("Got GMCP module: ");
					info<<v;
					Msg(info);*/
					if (m_parent->GetGlobalOptions()->GetUseEvents() && m_parent->GetGlobalOptions()->GetUseEvGMCPData())
					{
						wxString ss;
						ss = wxString::Format("%cfunc(\"%s\", \"OnGMCPData(\'%s')\")", m_parent->GetGlobalOptions()->GetCommand(),
							m_parent->GetGlobalOptions()->GetEventFile(), v.c_str());
						m_parent->m_input->ParseCommandLine(&ss);
					}
					//luaL_dostring(m_L->GetLuaState(), "echo(tostring(result))");
					
					m_atcpstring.Empty();
					if (line.GetLineText()==wxEmptyString && line.m_vstyle.size()<=1)
					{
						line.SetGagme(true);
						m_parsestate = HAVE_LINE;
					}
				}
				
				else if (*it!=IAC)
					m_atcpstring.Append(*it);
				break;
			case HAVE_IACSBMSDP:
			{
				wxString var, val;
				
				if (*it==SE)
				{
					ParseMSDP(m_atcpstring);
					m_atcpstring.Empty();
					m_parsestate=HAVE_TEXT;
					
					break;
				}
				else if (*it!=IAC)
					m_atcpstring.Append(*it);
				break;
			}
			case HAVE_IACSBCHARSET:
				if (*it==SE)//REQUEST
				{
					if (!m_charset.EndsWith("UTF-8"))
					{
						char c[12];
						c[0]=(char)IAC;
						c[1]=(char)SB;
						c[2]=(char)CHARSET;
						c[3]=(char)SEND;
						c[4]='U';
						c[5]='T';
						c[6]='F';
						c[7]='-';
						c[8]='8';
						c[9]=(char)IAC;
						c[10]=(char)SE;
						m_sock->Write(c, 11);
						//ttsent = false;
						m_parsestate = HAVE_TEXT;
						
					}
				}
				else m_charset.Append(*it);
				break;
			case HAVE_COMPRESS_START:
			{
				char cBuf[64000];
				//wxString c = s.Mid(pos);
				//m_dc->Init();
				//int xx = m_sock->LastCount();
				//int err=m_dc->Decompress(&cBuffer[pos], m_sock->LastCount()-pos);
				//int err=m_dc->Decompress(&cBuffer[pos], wxStrlen(cBuffer)-pos);
				int xx = m_sock->LastCount();
				int err=m_dc->Decompress(&m_cBuffer[pos], (size_t)(xx-pos));
				if (err==-1)
				{
					SetMCCP2(false);
					m_dc->EndDecompress();
					m_dc->Init();
					it = s.end()-1;
					break;
				}
				m_dc->GetUCBuffer(cBuf);
				
				
				/*if (m_mxp)
					ParseBufferMXP(&cBuf[pos]);
				else
					ParseNBuffer(cBuf);*/
				//pos=0;
				it = s.end()-1;
				
				m_parsestate = HAVE_TEXT;
				break;
			}
			case HAVE_MSP1:
				if (*it=='!')
				{
					m_parsestate = HAVE_MSP;
					sLine.Append(*it);
					//sLine.RemoveLast();
				}
				else if (*it==ESC)
				{
					m_parsestate = HAVE_ESC;
					sLine.Replace("\t", "    ");
					style[index].SetText(sLine);
					if (m_bourl)
					{	
						if (m_url->Match(style[index].GetText(), false))
							style[index].SetURL(true);
					}
					//opos=pos;
					line.m_vstyle.push_back(style[index++]);
					m_indexend=line.m_vstyle.size();
					line.SetLineText(sLine);
					sLine.Empty();
				}
				else if (*it=='\n')
					m_parsestate = HAVE_LINE;
				else
				{
					sLine.Append(*it);
					m_parsestate = HAVE_TEXT;
				}
				break;
			case HAVE_MSP:
				{
					wxString sound = s.substr(it-s.begin(), 5);
					if (!sound.Cmp("SOUND") || !sound.Cmp("MUSIC"))
					{
						pos = ParseMSP(&s, it-s.begin());
						it = s.begin()+pos;
						m_parsestate = HAVE_TEXT;
						sLine.Empty();
					}
					else
					{
						m_parsestate = HAVE_TEXT;
						sLine.Append(*it);
					}
				}
				break;
			default:
				break;
		}
	}
		
	sLine.Replace("\t", "    ");
	style[index].SetText(sLine);
	if (m_bourl)
	{	
		if (m_url->Match(style[index].GetText(), false))
			style[index].SetURL(true);
	}
	opos=pos;
	if (!m_vmudlines.empty())
		{
			if (!m_vmudlines.back().m_vstyle.empty() && !m_vmudlines.back().IsFull() /*&& gotline*/ && !colset)
			{
				AnsiLineElement last = m_vmudlines.back().m_vstyle.back();
				style[index].SetFCol(last.GetFColIndex(), last.GetFCol());
				style[index].SetBCol(last.GetBColIndex(), last.GetBCol());
				//style[index].SetFontStyle(last.GetFontStyle());
				style[index].SetFontStyle(0);
				style[index].SetURL(false);
			}
		}
	
	line.m_vstyle.push_back(style[index]);
	colset = false;
	m_indexend=line.m_vstyle.size();
	line.SetLineText(sLine);
	if (!m_vmudlines.empty())
	{
		if (!m_vmudlines.back().IsFull())
		{
			m_vmudlines.pop_back();
			m_curline--;
		}
	}
	if (m_parsestate==HAVE_LINE)
	{
		line.SetFull(true);
		m_parsestate=HAVE_TEXT;
		sLine.Empty();
		
		gotline = false;
		for (int i=0;i<=index;i++)
		{
			style[i].SetFontStyle(0);
			style[i].SetURL(false);
			style[i].SetText("");
			style[i].SetFCol(7, m_colansi[7]);
			style[i].SetBCol(0, m_colansi[0]);
		}
		index=0;
	}
	if (m_parsestate == HAVE_COMPRESS_START)
		m_parsestate = HAVE_TEXT;
	if (m_curline==0)
		line.SetLinenumber(m_curline);
	else
	{
		if (m_curline-1>m_vmudlines.size())
			m_curline = m_vmudlines.size();
		//line.SetLinenumber(m_vmudlines.at(m_curline-1).GetLinenumber()+1);
		line.SetLinenumber(m_vmudlines.back().GetLinenumber()+1);
	}
	int idx = m_parent->GetDefVarIndexByLabel("amcLines");
	wxString l;
	l << line.GetLinenumber();
	m_parent->GetDefVars()->at(idx).SetValue(l);
	wxDateTime d, ddt;
	ddt = wxDateTime::UNow();
	line.SetDateTimeMS(ddt);
	d = wxDateTime::Now();
	line.SetDateTime(d);
	line.SetAnsiLine(s.SubString(aoldpos, it-s.begin()-1));
	aoldpos = it-s.begin();
	
	//line.SetAnsiLine(*sLine);
	if (m_parsestate!=HAVE_LF)
	{
		if (!line.GetGagme())
		{
			m_vmudlines.push_back(line);
			m_curline++;
		}
	}
	if (m_parsestate==HAVE_LF)
	{
		m_parsestate = HAVE_TEXT;
		//sLine.Empty();
	}
	
	AnsiLine newline;
	line=newline;
	if (m_curline>=GetMaxLines())
	{		
		m_curline--;
		m_vmudlines.pop_front();
	}
	if (IsLogging())
		SendLineToLog(m_curline-1);
	Thaw();
	CheckTrigger(m_curline-1, true);
	RedirectWindow();
	//Update();
}

void MudWindow::ParseMSDP(wxString s)
{
#define HAVE_TEXT 0
#define HAVE_VAR 1
#define HAVE_VAL 2
#define HAVE_OPEN 3
#define HAVE_CLOSE 4
#define HAVE_OPENVAR 5
#define HAVE_OPENVAL 6
wxString::iterator it;
int m_state = HAVE_TEXT;
int pos=0;
wxString var, val, arrvar;
static int x=1;
	for(it=s.begin();it!=s.end();it++, pos++)
	{
		switch(m_state)
		{
			case HAVE_TEXT:
				if (*it==MSDP_VAR)
					m_state = HAVE_VAR;
				if (*it==MSDP_VAL)
					m_state = HAVE_VAL;
				if (*it==MSDP_OPEN)
					m_state = HAVE_OPEN;
				if (*it==MSDP_CLOSE)
					m_state=HAVE_CLOSE;
				break;
			case HAVE_VAR:
				if (*it==MSDP_VAL)
				{
					m_state=HAVE_VAL;
					arrvar = var;
					//var.Empty();
				}
				else
					var.append(*it);
				break;
			case HAVE_VAL:
				if (*it==MSDP_OPEN)
				{
					m_state = HAVE_OPEN;
					break;
				}
				if (*it==IAC)
				{
					m_state=HAVE_TEXT;
					if (m_parent->GetGlobalOptions()->GetUseEvents() && m_parent->GetGlobalOptions()->GetUseEvMSDPData())
					{
						wxString ss;
						lua_getglobal(m_L->GetLuaState(), "MSDP");
						lua_pushstring(m_L->GetLuaState(), val.c_str());
						lua_setfield(m_L->GetLuaState(), -2, "Data");
						ss = wxString::Format("%cfunc(\"%s\", \"OnMSDPData(\'%s')\")", m_parent->GetGlobalOptions()->GetCommand(),
							m_parent->GetGlobalOptions()->GetEventFile(), var.c_str());
						m_parent->m_input->ParseCommandLine(&ss);
						var.Empty();
						val.Empty();
					}
				}
				if (*it==MSDP_VAR)
				{
					m_state=HAVE_VAR;
					if (m_parent->GetGlobalOptions()->GetUseEvents() && m_parent->GetGlobalOptions()->GetUseEvMSDPData())
					{
						wxString ss;
						if (x==1)
						{
							lua_getglobal(m_L->GetLuaState(), "MSDP");
							lua_pushstring(m_L->GetLuaState(), val.c_str());
							lua_setfield(m_L->GetLuaState(), -2, "Data");
						}
						else
						{
							lua_getglobal(m_L->GetLuaState(), "MSDP");
							lua_getfield(m_L->GetLuaState(), -1, "Data");
							lua_pushstring(m_L->GetLuaState(), val.c_str());
							lua_rawseti(m_L->GetLuaState(), -2, x++);
						}
						ss = wxString::Format("%cfunc(\"%s\", \"OnMSDPData(\'%s')\")", m_parent->GetGlobalOptions()->GetCommand(),
							m_parent->GetGlobalOptions()->GetEventFile(), var.c_str());
						m_parent->m_input->ParseCommandLine(&ss);
						var.Empty();
						val.Empty();
						x=1;
					}
				}
				if (*it==MSDP_VAL)//array
				{
					if (x==1)
					{
						lua_getglobal(m_L->GetLuaState(), "MSDP");
						lua_newtable(m_L->GetLuaState());
						lua_setfield(m_L->GetLuaState(), -2, "Data");
						lua_getglobal(m_L->GetLuaState(), "MSDP");
						lua_getfield(m_L->GetLuaState(), -1, "Data");
						lua_pushstring(m_L->GetLuaState(), val.c_str());
						lua_rawseti(m_L->GetLuaState(), -2, x++);
						val.Empty();
					}
					else
					{
						lua_getglobal(m_L->GetLuaState(), "MSDP");
						lua_getfield(m_L->GetLuaState(), -1, "Data");
						lua_pushstring(m_L->GetLuaState(), val.c_str());
						lua_rawseti(m_L->GetLuaState(), -2, x++);
					}
					val.Empty();
				}
				else if (*it!=MSDP_VAR && *it!=MSDP_VAL)
					val.append(*it);
				break;
			case HAVE_OPEN:
				if (*it==MSDP_CLOSE)
				{
					m_state=HAVE_TEXT;
				}
				if (*it==MSDP_VAR)
				{
					m_state = HAVE_OPENVAR;
					lua_getglobal(m_L->GetLuaState(), "MSDP");
					lua_newtable(m_L->GetLuaState());
					lua_setfield(m_L->GetLuaState(), -2, "Data");
					arrvar=var;
					var.Empty();
					break;
				}
				//else
					//var.Append(*it);
				break;
			case HAVE_OPENVAR:
				if (*it==MSDP_VAL)
				{
					m_state = HAVE_OPENVAL;
				}
				else
					var.Append(*it);
				break;
			case HAVE_OPENVAL:
				if (*it==MSDP_VAR)
				{
					m_state=HAVE_OPENVAR;
					lua_getglobal(m_L->GetLuaState(), "MSDP");
					lua_getfield(m_L->GetLuaState(), -1, "Data");
					if (x==1)
					{
						lua_pushstring(m_L->GetLuaState(), var.c_str());
						lua_pushstring(m_L->GetLuaState(), val.c_str());
						lua_rawset(m_L->GetLuaState(), -3);
					}
					else
					{
						wxString chunk;
						chunk<<"MSDP.Data"<<"[\""<<var.mb_str()<<"\"]"<<"["<<x++<<"]=\""<<val.mb_str()<<"\"";
						luaL_dostring(m_L->GetLuaState(), chunk.mb_str());
						x=1;
					}
					var.Empty();
					val.Empty();
				}
				else if (*it==MSDP_VAL)
				{
					lua_getglobal(m_L->GetLuaState(), "MSDP");
					lua_getfield(m_L->GetLuaState(), -1, "Data");
					if (x==1)
					{
						lua_newtable(m_L->GetLuaState());
						lua_setfield(m_L->GetLuaState(), -2, var.c_str());
						/*lua_getglobal(m_L->GetLuaState(), "MSDP");
						lua_getfield(m_L->GetLuaState(), -1, "Data");
						lua_getfield(m_L->GetLuaState(), -2, var.mb_str());
						lua_pushnumber(m_L->GetLuaState(), 1);
						lua_pushstring(m_L->GetLuaState(), val.c_str());
						lua_rawset(m_L->GetLuaState(), -3);*/
										
						wxString chunk;
						chunk<<"MSDP.Data"<<"[\""<<var.mb_str()<<"\"]"<<"["<<x++<<"]=\""<<val.mb_str()<<"\"";
						luaL_dostring(m_L->GetLuaState(), chunk.mb_str());
						//arrvar=var;
					}
					else
					{
						wxString chunk;
						chunk<<"MSDP.Data"<<"[\""<<var.mb_str()<<"\"]"<<"["<<x++<<"]=\""<<val.mb_str()<<"\"";
						luaL_dostring(m_L->GetLuaState(), chunk.mb_str());
					}
					val.Empty();
				}
				else if (*it==MSDP_CLOSE)
				{
					m_state = HAVE_CLOSE;
					lua_getglobal(m_L->GetLuaState(), "MSDP");
					lua_getfield(m_L->GetLuaState(), -1, "Data");
					if (x==1)
					{
						lua_pushstring(m_L->GetLuaState(), val.c_str());
						lua_setfield(m_L->GetLuaState(), -2, var.c_str());
					}
					else
					{
						wxString chunk;
						chunk<<"MSDP.Data"<<"[\""<<var.mb_str()<<"\"]"<<"["<<x++<<"]=\""<<val.mb_str()<<"\"";
						luaL_dostring(m_L->GetLuaState(), chunk.mb_str());
					}
					if (m_parent->GetGlobalOptions()->GetUseEvents() && m_parent->GetGlobalOptions()->GetUseEvMSDPData())
					{
						wxString ss = wxString::Format("%cfunc(\"%s\", \"OnMSDPData(\'%s')\")", m_parent->GetGlobalOptions()->GetCommand(),
							m_parent->GetGlobalOptions()->GetEventFile(), arrvar.c_str());
						m_parent->m_input->ParseCommandLine(&ss);
						var.Empty();
						val.Empty();
						arrvar.Empty();
						x=1;
					}
				}
				else
					val.Append(*it);
				break;
			case HAVE_CLOSE:
				if (*it==MSDP_VAR)
				{
					m_state = HAVE_VAR;
				}
				else
					var.Append(*it);
				break;
		}
	}
	if (m_state== HAVE_VAL)
	{
		if (x==1)
		{
			lua_getglobal(m_L->GetLuaState(), "MSDP");
			lua_pushstring(m_L->GetLuaState(), val.c_str());
			//lua_setfield(m_L->GetLuaState(), -2, "Data");
			lua_setfield(m_L->GetLuaState(), -2, var.c_str());
		}
		else
		{
			lua_getglobal(m_L->GetLuaState(), "MSDP");
			lua_getfield(m_L->GetLuaState(), -1, "Data");
			lua_pushstring(m_L->GetLuaState(), val.c_str());
			lua_rawseti(m_L->GetLuaState(), -2, x++);
		}
		if (m_parent->GetGlobalOptions()->GetUseEvents() && m_parent->GetGlobalOptions()->GetUseEvMSDPData())
		{
			wxString ss = wxString::Format("%cfunc(\"%s\", \"OnMSDPData(\'%s')\")", m_parent->GetGlobalOptions()->GetCommand(),
				m_parent->GetGlobalOptions()->GetEventFile(), var.c_str());
			m_parent->m_input->ParseCommandLine(&ss);
			var.Empty();
			val.Empty();
		}
		x=1;
	}
	
}

void MudWindow::SwitchColor(long c, int offset, AnsiLineElement* ale)
{
	int x;
	wxColour f;
	if(!m_useansi)
		c=0;
	switch(c)
	{
		case 0:
			ale->SetFCol(7, m_colansi[DEF_FORECOL]);
			ale->SetBCol(0, m_colansi[0]);
			ale->SetFontStyle(0);
			ale->SetURL(false);
			f = m_colansi[DEF_FORECOL];
			break;
		case 1:
			x = ale->GetFColIndex()+8;
			if (x<8)
				ale->SetFCol(x+8, m_colansi[x+8]);//15, m_colansi[15]);
			if (x>8 && x <16)
				ale->SetFCol(x, m_colansi[x]);
			f = m_colansi[x+8];
			break;
		case 3://italic
			ale->SetFontStyle(3);
			break;
		case 4:
			ale->SetFontStyle(4);
			break;
		case 10:
			break;
		case 22://no bold
			ale->SetFCol(ale->GetFColIndex()-8, m_colansi[ale->GetFColIndex()-8]);
			f = m_colansi[ale->GetFColIndex()-8];
			break;
		case 23://no italic
		case 24://no underline
			//ale->SetFontStyle(0);
			break;
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
		case 37:
			ale->SetFCol(c-offset, m_colansi[c-offset]);
			f = m_colansi[c-offset];
			break;
		case 39:
			ale->SetFCol(7, m_colansi[DEF_FORECOL]);
			f = m_colansi[DEF_FORECOL];
			break;
		case 40:
		case 41:
		case 42:
		case 43:
		case 44:
		case 45:
		case 46:
		case 47:
			ale->SetBCol(c-40, m_colansi[c-40]);
			break;
		case 49:
			ale->SetBCol(0, m_colansi[0]);
			break;
		case 56:
		case 57:
		case 58:
			ale->SetFCol(c-40, m_colansi[c-40]);
			f = m_colansi[c-40];
			break;
		case 59:
			ale->SetBCol(c-40, m_colansi[c-40]);
			break;
		case 90:
		case 91:
		case 92:
		case 93:
		case 94:
		case 95:
		case 96:
		case 97:
		case 98:
		case 99:
			ale->SetFCol(c-82, m_colansi[c-82]);
			f = m_colansi[c-82];
			break;
		case 100:
		case 101:
		case 102:
		case 103:
		case 104:
		case 105:
		case 106:
		case 107:
		case 108:
		case 109:
			ale->SetBCol(c-92, m_colansi[c-92]);
			break;
	}
	m_curansicolor = f;
}

void MudWindow::RedirectWindow()
{
map<wxString, bool>::iterator mit;
	//capturing with capstart, capend
	if (!m_capwindow.empty())
	{
	MudWindow *mw;
	for (mit = m_capwindow.begin(); mit!=m_capwindow.end(); mit++)
		{
			mw = (MudWindow*)MudWindow::FindWindowByName(mit->first, m_parent);
			if (mw==NULL)
				continue;
			if (!mw->GetFirstCaptured())
			{
				mw->AddLine(m_vmudlines.at(m_curline-1));
			}
			else
				mw->SetFirstCaptured(false);
			if (mit->second)
			{
				m_vmudlines.pop_back();
				m_curline--;
			}
		}
	}
	//still to capture to another window?
	if (!m_capwin.empty())
	{
		s_it it;
		size_t i=0;
		MudWindow *mw;
		vector<long>::iterator lit;
		vector<bool>::iterator bit;
		for (i=0, it=m_capwin.begin(), lit=m_capture.begin(), bit=m_capgag.begin();i<m_capwin.size();i++, it++, lit++, bit++)
		{
			mw = (MudWindow*)MudWindow::FindWindowByName(it->c_str(), m_parent);
			if (mw==NULL)
				continue;
			if (*lit>0)
			{
				mw->AddLine(m_vmudlines.at(m_curline-1));
				if (*bit)
				{
					m_vmudlines.pop_back();
					m_curline--;
				}
				m_capture.at(i)--;
				mw->SetScrollPage();
				mw->Refresh();
				mw->Update();
			}
		}
		for (i=0, it=m_capwin.begin(), lit=m_capture.begin(), bit=m_capgag.begin(); it!=m_capwin.end(); it++, lit++, bit++, i++)
		{
			if (*lit<=0)
			{
				m_capwin.erase(it);
				m_capture.erase(lit);
				m_capgag.erase(bit);
				it = m_capwin.begin()+i;
				lit = m_capture.begin()+i;
				bit = m_capgag.begin()+i;
				if (it==m_capwin.end())
					break;
			}
		}
	}

	//should we lock the prompt?
	if (m_boprompt)
	{
		int x, y;
		wxString s = wxEmptyString;
		s += m_vmudlines.at(m_curline-1).GetLineText();
		m_parent->m_prompt->GetTextExtent(s, &x, &y);
		if (m_prompt->Match(s, false))
		{
			if (m_gagprompt) //should we gag the original prompt?
			{
				m_vmudlines.pop_back();
				m_curline--;
			}
			m_parent->m_mgr.GetPane("amcprompt").Position(0).BestSize(x+10,24).Fixed();
			if (!m_parent->m_mgr.GetPane("amcprompt").IsShown())
			{
				m_parent->m_mgr.GetPane("amcinput").Position(1);
				m_parent->m_mgr.GetPane("amctoggle").Position(2);
				m_parent->m_mgr.GetPane("amcprompt").Show();	
			}
			int x;
			if (m_parent->m_splitter->IsShown())
				x = m_parent->m_splitter->GetScrollPos(wxVERTICAL);
			m_parent->m_mgr.Update();
			m_parent->m_prompt->Clear();
			m_parent->m_prompt->AppendText(s);
			if (m_parent->m_splitter->IsShown())
				m_parent->m_splitter->SetScrollPos(wxVERTICAL, x);
		
			//m_parent->m_input->SetSelection(m_parent->m_input->GetLastPosition(),0);
			}
	}
	else if (m_parent->m_prompt->IsShown())
	{
		m_parent->m_mgr.GetPane("amcprompt").Hide();
		m_parent->m_mgr.Update();
		m_parent->m_input->SetFocus();
	}
	
	if (m_vmudlines.at(m_curline-1).GetGagme())
	{
		m_vmudlines.pop_back();
		m_curline--;
		this->SetScrollPage();
	}
	//::wxLogDebug(wxT("time: %ld ms, %s"), sw.Time(), sLine.c_str());
    //} while (pos<index-1);
}

void MudWindow::CheckTrigger(int linenr, bool multi)
{
wxString s;
wxStringTokenizer tkz;
	if (!m_trigger)
		return;
	wxString token = m_parent->GetGlobalOptions()->GetSep();
	token.append("\n");
	if (linenr>=(int)m_vmudlines.size())
		linenr=m_curline-1;
	if (!m_vmudlines.at(linenr).IsTriggered() && m_parent->TriggersOn())
	{
		for (size_t i=0;i<m_parent->m_trigger.size();i++)
		{
			s = wxEmptyString;
			if (!m_parent->m_trigger.at(i).IsActive())
				continue;
			if (m_parent->m_trigger.at(i).IsMultiLine())
			{
				if (!multi)
					continue;
				for (int x=linenr-m_parent->m_trigger.at(i).GetLines()+1;x<linenr+1;x++)
				{
					s += m_vmudlines.at(x).GetLineText() + "\n";
				}
			}
			else
			{
				//if (linenr<m_vmudlines.size())//sanity check
				//	linenr=m_vmudlines.size();
				if (linenr>=(int)m_vmudlines.size())
					linenr=m_curline-1;
				s = m_vmudlines.at(linenr).GetLineText();
			}
			if (m_parent->m_trigger.at(i).Match(s))//trit->Match(s))
			{
				wxString ac = m_parent->m_trigger.at(i).BuildAction();//trit->BuildAction();
				if (m_parent->m_trigger.at(i).GetSendScript())
				{
					ac.Replace(m_parent->GetGlobalOptions()->GetSep(), "\n");
					if (m_parent->m_child->GetLState()->DoString(ac))
					{
						struct lua_State* L = m_parent->m_child->GetLState()->GetLuaState();
						int top = lua_gettop(L);
						wxString error = luaL_checkstring(L, top);
						m_parent->m_child->Msg(error);
						continue;
					}
					continue;
				}
				tkz.SetString(ac, token);
				while ( tkz.HasMoreTokens() )
				{
					wxString comm = tkz.GetNextToken();
					RegExp colsub("(\\^x\\d+)+");
					int posm=0;
					while (colsub.Match(comm.Mid(posm)))
					{
						comm.Replace(colsub.GetMatch(0), m_replcol[colsub.GetMatch(0)]);
						posm+=colsub.GetMatch(0).length();
					}
					if (!comm.Cmp("#pwd"))
					{
						m_vmudlines.at(linenr).SetFull(true);
					}
					if (!m_parent->m_input->ParseCommandLine(&comm))
					{
						Write(comm+(char)LF);
						
					}
					else continue;
					if (comm.at(0)!=m_parent->GetGlobalOptions()->GetCommand()&&comm.at(0)!=m_parent->GetGlobalOptions()->GetScript())
					{
						if (m_parent->GetGlobalOptions()->GetTriggerEcho())
						{
							wxString out = "\x1b[56m";
							out.append(comm);
							out.append("\x1b[0m");
							//ParseBuffer((wxChar*)Out(ac).data());
							//ParseLine(&out);
							int temp = m_parsestate;
							m_parsestate = HAVE_TEXT;
							ParseNBuffer(out.char_str(),false);
							m_parsestate = temp;
							if (!m_vmudlines.at(linenr).IsFull())
							{
								m_vmudlines.at(linenr).SetFull(true);
							}
						}
						
						if (linenr>=(int)m_vmudlines.size())
							linenr=m_curline-1;
						if (!m_vmudlines.at(linenr).IsFull())
						{
							ParseNBuffer((char*)" \n", false);
							m_vmudlines.at(linenr).SetFull(true);
							
							//m_vmudlines.at(linenr).SetTriggered(true);
						}
					}
					//else m_vmudlines.at(linenr).SetFull(true);
				}//while
				
			}
		}
		//if (m_curline-1>linenr)
		//	CheckTrigger(linenr);
		if (linenr>=(int)m_curline)
			linenr--;
		if (m_vmudlines.at(linenr).IsFull())
			m_vmudlines.at(linenr).SetTriggered(true);
	}
}


void MudWindow::ParseLine(wxString *sLine)
{
static bool boLast = false;
static bool boBreak = true;
//AnsiLine *line=NULL;
AnsiLine line;
//AnsiLineElement *style;
AnsiLineElement style[500];
int pos = -1;
size_t stcpy = 0;
size_t freq;
int index=0;
size_t len;
	
	wxString s = *sLine;
	//wxStopWatch sw;
	//sw.Start();
	freq = line.Freq(sLine);
	wxString empty = "";
	boLast = false;
	if (!m_vmudlines.empty())
	{
		if (m_vmudlines.back().IsFull()&&!boBreak)
			boBreak = true;
		if (!m_vmudlines.back().IsFull())
			boBreak = false;
	}
	if (!boBreak)
	{
		m_curline--;
		//line = new AnsiLine(m_vmudlines.back());
		line = m_vmudlines.back();
		index = (int)m_vmudlines.back().m_vstyle.size();
		//index = (int)line->m_vstyle.size();
		//style = new AnsiLineElement[freq+index+5];
		//delete l;

	}
	else
	{
		//line = new AnsiLine();
		//style = new AnsiLineElement[freq+5];
	}
	/*if (freq && m_curline && boBreak)
	{
		//AnsiLine *oldline = m_mudlines.back();

		//style[0] = *oldline->m_style.back();
		//style[0].SetText(*empty);
		//line->m_style.Append(style);
	}*/
	
	if (m_bocolcode)
	{
		if (!sLine->length())
			return;
		pos++;
		while(sLine->at(pos)!=AC_M && sLine->at(pos)!=EOS)
			pos++;
		if (sLine->at(pos+1)==ESC &&  sLine->at(pos+2)==BR)
		{
			pos++;
			while(sLine->at(pos)!=AC_M && sLine->at(pos)!=EOS)
				pos++;
		}
		len = m_oldcolor->length();
		wxString s;
		s = sLine->substr(0, pos+1-stcpy);
		m_oldcolor->append(s);
		//delete s;

		if (m_oldcolor->at(pos-stcpy+len)==AC_M)
		{
			m_bocolcode = false;
			AnsiLineElement ale;
			if (!m_vmudlines.empty())
				if (!m_vmudlines.back().m_vstyle.empty())
					ale = m_vmudlines.back().m_vstyle.back();
			if (index>=1)
				SetStyleColors(1, m_oldcolor, &style[index], &style[index-1]);//&style[index]);
			else
				SetStyleColors(1, m_oldcolor, &style[index], &ale);
			//ParseColor(1, curline, index, szOldCol);
			stcpy = pos+1;
		}
		else pos--;
		if (pos>(int)sLine->length())
			pos = (int)sLine->length();
	}
	/*int x=0;
	for(wxString::const_iterator it = sLine->begin();it!=sLine->end();it++)
		x++;*/
	m_indexstart = index;
	while (++pos<=(int)sLine->length() && sLine->GetChar(pos)!=0)
	{
		if (sLine->GetChar(pos) == ESC)
		{
			if (pos!=(int)stcpy)
			{
				if (!stcpy)
				{
					//AnsiLine oldline = m_vmudlines.back();
					//AnsiLineElement ale = oldline.m_vstyle.back();

					style[index].SetFCol(m_vmudlines.back().m_vstyle.back().GetFColIndex(), m_vmudlines.back().m_vstyle.back().GetFCol());
					style[index].SetBCol(m_vmudlines.back().m_vstyle.back().GetBColIndex(), m_vmudlines.back().m_vstyle.back().GetBCol());//style[index]
					//style[index].SetFontStyle(m_vmudlines.back().m_vstyle.back().GetFontStyle());
					style[index].SetPromptSend(m_vmudlines.back().m_vstyle.back().GetPromptSend());
					style[index].SetMXPSend(m_vmudlines.back().m_vstyle.back().GetMXPSend());
					if (!m_vmudlines.back().m_vstyle.back().GetMXPCommand()->empty())
					{
						for (size_t i=0;i<m_vmudlines.back().m_vstyle.back().GetMXPCommand()->size();i++)
							style[index].AddMXPCommand(m_vmudlines.back().m_vstyle.back().GetMXPCommand()->at(i));
					}
					//style[index].AddMXPCommand(m_vmudlines.back().m_vstyle.back().Get
				}
				//AnsiLineElement style[index] = new AnsiLineElement();
				//Text für ersten substring finden
				wxString sub = sLine->substr(stcpy, pos-stcpy);
				sub.Replace("\t", "    ");
				style[index].SetText(sub);
				if (m_mxp)
				{
					if (!sub.Cmp("<VERSION>"))
					{
						wxString ss = "\x1b[1z<VERSION MXP=\"0.5\" CLIENT=\"wxAmcl\" VERSION=\"0.1\">\n";
						m_sock->Write(ss.To8BitData(), ss.length());
						style[index].SetText("");
					}
				}
				else if (!m_mxp)
				{
					style[index].SetText(sub);
				}
				
				if (m_bourl)
				{
					if (m_url->Match(sub, false))
						style[index].SetURL(true);
				}

				line.SetLineText(sub);
				//mitDefaultwerten
				line.m_vstyle.push_back(style[index++]);
			}

			//style[index].SetText(*empty);
			AnsiLineElement ale;
			if (!m_vmudlines.empty())
				if (!m_vmudlines.back().m_vstyle.empty())
					ale = m_vmudlines.back().m_vstyle.back();
			if (index>=1)
				pos = stcpy = SetStyleColors(pos+1, sLine, &style[index], &style[index-1]);
			else
				pos = stcpy = SetStyleColors(pos+1, sLine, &style[index], &ale);
			stcpy++;
			boLast = false;
		}
		if (s.GetChar(pos)==IAC)//(sLine->GetChar(pos)==IAC)
		{
			//ParseBuffer(wxT("IAC found"));
			
			if (pos>(int)stcpy)//&& !boLast)
			{
				wxString sub = sLine->substr(stcpy, pos-stcpy);
				sub.Replace("\t", "    ");
				style[index].SetText(sub);
				if (m_bourl)
				{
					if (m_url->Match(sub, false))
						style[index].SetURL(true);
				}
				line.SetLineText(sub);
				line.m_vstyle.push_back(style[index++]);

			}
			pos = stcpy = ParseTelnet(sLine, pos);
			if (sLine->GetChar(0)==IAC && sLine->GetChar(sLine->length()-2)==SE && pos==(int)sLine->length()-2)
			{
				m_curline++;			
				return;
			}
			/*if (sLine->GetChar(pos)==SE && sLine->GetChar(pos-1)==IAC && m_atcpdata)
			{
				//line.SetLineText(line.GetLineText().replace(style[index-1].GetText(), wxEmptyString));
				m_atcpdata=false;
				if (!line.m_vstyle.empty())
					line.m_vstyle.pop_back();
			}*/
			if (pos>=(int)sLine->length())
			{
				boBreak = true;
				m_curline++;
				return;
			}
			
			if (m_atcpdata)
			{
				ale_it it;
				for(it=line.m_vstyle.begin();it!=line.m_vstyle.end();it++)
					it->SetText(wxEmptyString);
				line.AssignText(wxEmptyString);
				//line.SetGagme(true);
				m_atcpdata=false;
			}
			stcpy++;
			
			boLast = true;
		}
		if (sLine->GetChar(pos)== '!' && sLine->GetChar(pos + 1) == '!')
		{  //MSP testen
			wxString sound = sLine->substr(pos+2, 5);
			if (!sound.Cmp("SOUND") || !sound.Cmp("MUSIC"))
			{
				pos = stcpy = ParseMSP(sLine, pos);
				stcpy++;
				//curline=lines;
				boLast = false;
				//if (szLine[pos]=='\r' && szLine[pos+1]=='\n') {
				//	pos +=2;
				//	stcpy+=2;
				//	}
				//if (curline>=iScrollBuf-1)
				//	curline--;
			}
		}
		
	}
	//if (sLine->GetChar(stcpy)==EOS)
	//	stcpy--;
	if (pos!=(int)stcpy)
	{
	//AnsiLineElement *style2 = new AnsiLineElement();
		
		if (sLine->GetChar(stcpy)!=ESC && sLine->GetChar(stcpy)!=SE) {
			wxString sub = sLine->substr(stcpy, pos-stcpy);
			sub.Replace("\t", "    ");
			style[index].SetText(sub);
			if (m_bourl)
			{
				if (m_url->Match(sub, false))
					style[index].SetURL(true);
			}
			line.SetLineText(sub);
			if (!stcpy && m_curline)
			{
				//AnsiLine oldline = m_vmudlines.back();
				//AnsiLineElement ale = oldline.m_vstyle.back();

				style[index].SetFCol(m_vmudlines.back().m_vstyle.back().GetFColIndex(), m_vmudlines.back().m_vstyle.back().GetFCol());
				style[index].SetBCol(m_vmudlines.back().m_vstyle.back().GetBColIndex(), m_vmudlines.back().m_vstyle.back().GetBCol());//style[index]
				style[index].SetMXPSend(m_vmudlines.back().m_vstyle.back().GetMXPSend());
			}
		}
		else
		{
			//style[index].SetText(*empty);
			//line->SetLineText(empty);
			AnsiLineElement ale;
			if (!m_vmudlines.empty())
				if (!m_vmudlines.back().m_vstyle.empty())
					ale = m_vmudlines.back().m_vstyle.back();
			
			if (index>=1)
				SetStyleColors(stcpy+1, sLine, &style[index], &style[index-1]);
			else
				SetStyleColors(stcpy+1, sLine, &style[index], &ale);
		}
		line.m_vstyle.push_back(style[index++]);
	}
	else
	{
	//AnsiLineElement *style3 = new AnsiLineElement();
		style[index].SetText(empty);
		line.SetLineText(empty);
		line.m_vstyle.push_back(style[index++]);
	}
	
	m_indexend = index-1;
	if (!boBreak)
	{
		m_vmudlines.pop_back();
	}
	if (!m_bonewline)
	{
		line.SetFull(false);
		boBreak=false;
	}
	else
	{
		boBreak=true;
		line.SetFull(true);
	}
	if (m_curline==0)
		line.SetLinenumber(m_curline);
	else
	{
		if (m_curline-1>m_vmudlines.size())
			m_curline = m_vmudlines.size();
		//line.SetLinenumber(m_vmudlines.at(m_curline-1).GetLinenumber()+1);
		line.SetLinenumber(m_vmudlines.back().GetLinenumber()+1);
	}
	int idx = m_parent->GetDefVarIndexByLabel("amcLines");
	wxString l;
	l << line.GetLinenumber();
	m_parent->GetDefVars()->at(idx).SetValue(l);
	
	wxDateTime d;
	//d.SetToCurrent();
	d = wxDateTime::UNow();
	line.SetDateTimeMS(d);
	d = wxDateTime::Now();
	line.SetDateTime(d);
	line.SetAnsiLine(*sLine);
	m_vmudlines.push_back(line);
	m_curline++;
	//m_botelnetparsed = false;
	/*if (IsLogging() && !m_vmudlines.at(m_curline-1).WasLogged() && m_vmudlines.at(m_curline-1).IsFull())
	{
		if (!IsAnsiLogging())
		{
			if (IsDateLogging())
				m_tlog->Write(m_vmudlines.at(m_curline-1).GetTime()+": ");
			m_tlog->Write(m_vmudlines.at(m_curline-1).GetLineText()+(char)CR+(char)LF);
		}
		else
		{
			m_tlog->Write(m_vmudlines.at(m_curline-1).GetAnsiLine()+(char)CR+(char)LF);
			m_tlog->Write("\r\n");
		}
		m_vmudlines.at(m_curline-1).SetLogged(true);
	}*/
	//::wxLogDebug(wxT("pline: %ld"), sw.Time());
	//delete empty;
	//delete[] style;
	//delete line;
	
}

size_t MudWindow::SetStyleColors(size_t pos, wxString *sLine, AnsiLineElement* style, AnsiLineElement* laststyle)
{
int nr = 0;
int colCode = DEF_FORECOL+30; //7
bool boFirst = true;
bool boBSet = false;
static wxByte bFontAttr = 0;
static wxByte bColor = DEF_BACKCOL;
AnsiLine line;
AnsiLineElement ale;
wxUint16 col;
	if (!m_vmudlines.empty())
	{
		if (!m_vmudlines.back().m_vstyle.empty())
		{
			style->SetFCol(laststyle->GetFColIndex(),laststyle->GetFCol());
			style->SetBCol(laststyle->GetBColIndex(),laststyle->GetBCol());
		}
	}
	//style->SetBCol(0, m_colansi[0]);
	while (nr!=-1)
	{
		nr = GetColor(&pos, sLine, boFirst, &bFontAttr, &bColor);
		if (nr!=-1)
		{
			colCode=nr;
			if (!colCode)
			{
				style->SetBCol(0, m_colansi[0]);
				boBSet = true;
			}
			boFirst = false;
		}
	}
	if (colCode==111)//simulate to clear the screen if \x1b[2J was sent
	{
		wxSize ss;
		ss=GetClientSize();
		wxClientDC dc(this);
		dc.SetFont(*m_font);
		int s_lines = ss.GetHeight()/dc.GetCharHeight();
		
		for(int x=0;x<s_lines;x++)
			//ParseBuffer("\r\n");
			ParseUTF8Buffer("\r\n");
		colCode = 37;
	}
	if (colCode>=3 && colCode<=5)
	{
		style->SetFCol(DEF_FORECOL, m_colansi[DEF_FORECOL]);
	}
	else if (colCode==9)
	{
		line = m_vmudlines.back();
		ale = line.m_vstyle.back();
		col = ale.GetFColIndex();
		style->SetFCol(col+8, m_colansi[col+8]);
	}
	else if (colCode!=1)
	{
	    if (colCode<0)
            colCode=37;
		if (!colCode)
		{
			colCode=37;
            bColor=0;
			style->SetBCol(0, m_colansi[0]);
		}
        if (colCode>55)
            colCode-=10;
		if (colCode==10)
			colCode=37;
		
		style->SetFCol(colCode-30, m_colansi[colCode-30]);
		
		//AnsiLine[line].ColIndex[index]=colCode-30;
		//AnsiLine[line].Color[index] = cols[colCode-30];
		/*if (colCode>55)
		{
			style->SetFCol(colCode-40, m_colansi[colCode-40]);
			//AnsiLine[line].ColIndex[index]=colCode-40;
			//AnsiLine[line].Color[index] = cols[colCode-40];
		}*/
	}
	else if (colCode==1)
	{
		style->SetFCol(DEF_FORECOL+8, m_colansi[DEF_FORECOL+8]);
		//AnsiLine[line].ColIndex[index]=DEFAULT_TEXT_COLOR + 8;
		//AnsiLine[line].Color[index]= cols[DEFAULT_TEXT_COLOR + 8];
	}
	else
	{
		line = m_vmudlines.back();
		ale = line.m_vstyle.back();
		col = ale.GetFColIndex();
		style->SetFCol(col+8, m_colansi[col+8]);
		//AnsiLine[line].ColIndex[index] = AnsiLine[line].ColIndex[index-1] + 8;
		//AnsiLine[line].Color[index]= cols[AnsiLine[line].ColIndex[index-1]+8];
	}
	if(bFontAttr)
	{
		style->SetFontStyle(bFontAttr);
		if (bFontAttr==4)
		{
			if (m_bourl)
			{
				if (m_url->Match(style->GetText(), false))
					style->SetURL(true);
			}
		}
	}
		//AnsiLine[line].bFontAttr[index]=bFontAttr;
	/*if (bFontAttr==4 && boURL) {
	   AnsiLine[line].boURL[index]=TRUE;
	   boURL = FALSE;
		}*/
	if (bColor)
	{
		if (bColor==61)
			style->SetBCol(19, m_colansi[19]);
		else
			style->SetBCol(bColor-40, m_colansi[bColor-40]);
		//AnsiLine[line].BackColIndex[index] = bColor - 40;
		//bColor=0;
	}
	else if (!boBSet) //style->SetBCol(0, m_colansi[0]);
	{
		
	}
	if(!m_useansi)
	{
		style->SetFCol(DEF_FORECOL, m_colansi[DEF_FORECOL]);
		//AnsiLine[line].ColIndex[index]=DEFAULT_TEXT_COLOR;
		//AnsiLine[line].Color[index] = cols[DEFAULT_TEXT_COLOR];
	}
	if (style->GetFColIndex()>DEF_COLORS)
	{
		style->SetFCol(DEF_FORECOL, m_colansi[DEF_FORECOL]);
	/*if (AnsiLine[line].ColIndex[index]>DEF_COLORS) {
		AnsiLine[line].ColIndex[index]= DEFAULT_TEXT_COLOR;
		AnsiLine[line].Color[index] = cols[DEFAULT_TEXT_COLOR];
		}*/
	}
	return pos-1;//+1;
}


int MudWindow::GetColor(size_t *pos, wxString *sLine, bool boFirst, wxByte *bFontAttr, wxByte *bBackColor)
{
size_t st;
long static lastcolcode = 0;
long colCode=0, tempcol;
wxString sColor, tmp;

	if (sLine->IsEmpty())
		return -1;
	if (*pos>=sLine->length())
		return -1;
	if (boFirst) {
		st = *pos;
		if (sLine->at(*pos-1)==ESC && sLine->at(*pos)==EOS) {
		//if (*(szData + *pos - 1)=='\x1b' && *(szData + *pos)=='\0') {
			m_bocolcode = true;
			m_oldcolor->Append((char)ESC);
			//_tcscpy(szOldCol, "\x1b");
			return -1;
			}
		if (sLine->GetChar(*pos-1)!=ESC || sLine->GetChar(*pos)!= BR)
		//if (*(szData + *pos - 1)!='\x1b' || *(szData + *pos)!='[')
			return -1;
		}
	else {
		st = *pos + 1;
		if (sLine->GetChar(*pos)==ESC && sLine->GetChar(*pos+1)==EOS) {
		//if (*(szData + *pos)=='\x1b' && *(szData + *pos +1)=='\0') {
			m_bocolcode = true;
			m_oldcolor->Append((char)ESC);
			//_tcscpy(szOldCol, "\x1b");
			(*pos)--;
			return -1;
			}

		if (sLine->GetChar(*pos)!=ESC || sLine->GetChar(*pos+1)!=BR)
		//if (*(szData + *pos)!='\x1b' || *(szData + *pos+1)!='[')
			return -1;
		}
	
	if (sLine->GetChar(*pos)==BR && sLine->GetChar(*pos+1)==EOS) {
	//if (*(szData + *pos)=='[' && *(szData + *pos+1)=='\0') {
		m_bocolcode = true;
		(*pos) +=2;
		*m_oldcolor = sLine->substr(st-1, *pos-st);
		//memcpy(szOldCol,&szData[st-1], *pos-st);
		//szOldCol[*pos-st]='\0';
		(*pos)--;
		return -1;
		}
	if (sLine->GetChar(*pos)==BR && sLine->GetChar(*pos+1)=='2' && sLine->GetChar(*pos+2)=='J')
	{
		(*pos)+=3;
		colCode=111;//ClearScreen
		return lastcolcode=colCode;
	}
	if (sLine->GetChar(*pos)==BR && sLine->GetChar(*pos+1)=='H')
	{
		(*pos) += 2;
		return -1;
	}
	if (sLine->GetChar(*pos)==BR && sLine->GetChar(*pos+1)=='J')
	{
		(*pos) += 2;
		return -1;
	}
	if (sLine->GetChar(*pos)==BR && sLine->GetChar(*pos+1) && sLine->GetChar(*pos+2)=='J')
	{
		(*pos) += 2;
		return -1;
	}
	if (sLine->GetChar(*pos)==BR && sLine->GetChar(*pos+1)=='7' && sLine->GetChar(*pos+2)=='z')
	{
		(*pos) +=3;
		return -1;
	}
	if (sLine->GetChar(*pos)==BR && sLine->GetChar(*pos+1)==AC_M) {
	//if (*(szData + *pos)=='[' && *(szData + *pos+1)=='m') {
		//colCode=37;
		colCode=0;
		(*pos) +=2;
		return lastcolcode=colCode;
		}
	(*pos) += 2;


	//while (!isalpha((int)*(szData + *pos)) && *(szData+ *pos)!='\0')
	while (!wxIsalpha(sLine->GetChar(*pos)) && sLine->GetChar(*pos)!=EOS)
	{
		(*pos)++;
		/*if (*pos >= sLine->length())
		{
			(*pos)--;
			break;
		}*/
	}
	if (sLine->GetChar(*pos)==EOS) {
		m_bocolcode = true;
		*m_oldcolor = sLine->substr(st-1, *pos-st+1);
		//memcpy(szOldCol,&szData[st-1], *pos-st+1);
		//szOldCol[*pos-st+1]='\0';
		(*pos)--;
		return -1;
		}
	//if (*(szData + *pos)!='m') {
	if (sLine->GetChar(*pos)!= AC_M) {
		//if (*(szData + *pos)=='\0') {
		if (sLine->GetChar(*pos)==EOS) {
			m_bocolcode = true;
			*m_oldcolor = sLine->substr(st-1, *pos-st+1);
			//memcpy(szOldCol,&szData[st-1], *pos-st+1);
			//szOldCol[*pos-st+1]='\0';
			//(*pos)--;
			return -1;
			}
		else {
			(*pos)++;
			return -1;
			}
		}

	//if (*(szData + *pos)=='\0'){
	
	sColor = sLine->Mid(st+1, *pos-st-1);
	//memcpy(szColor, &szData[st+1], *pos-st);
	//szColor[*pos-st]='\0';
	tmp = sColor.BeforeFirst(';');
	tmp.ToLong(&colCode);

	//if (colCode>29 && lastcolcode>40 && lastcolcode<50)
	//	colCode+=8;
	//sColor = sLine->Mid(st+1, *pos-st);
    if (colCode>39 && colCode<48)
    {
    *bBackColor=(BYTE)colCode;
    colCode=37;

    }
	if (sColor.length()>2)
	{
		if(sColor.GetChar(1)==';' && !colCode)
		{
			//memcpy(szColor, &szColor[2], _tcslen(&szColor[2]));
			//colCode = atoi(szColor);
			sColor = sColor.Mid(2, wxStrlen(sColor.c_str()+2));
			tmp = sColor.BeforeFirst(';');
			tmp.ToLong(&colCode);
			*bBackColor = 0;
			if (colCode>39 && colCode<48) {
				*bBackColor=(BYTE)colCode;
				colCode=7;
				}
			if (sColor.length()>=3)
			{
				if (sColor.GetChar(2)== ';') {
				//memcpy(szColor, &szColor[3], _tcslen(&szColor[3]));
				//int x = atoi(szColor);
					sColor = sColor.Mid(3, wxStrlen(sColor.c_str()+3));
					long x;
					sColor.ToLong(&x);
					if (x>=40)
						*bBackColor = (BYTE)x;
					else colCode = x;
					}
			}
		}
	}
	if (sColor.length()>2)
	{
		if (sColor.GetChar(1)==';' && (colCode==1 || !colCode)) {
			//memcpy(szColor, &szColor[2], _tcslen(&szColor[2]));
			sColor = sColor.Mid(2, wxStrlen(sColor.c_str()+2));
			if (colCode>40 && colCode<48) {
				*bBackColor=(BYTE)colCode;
				colCode=37;
				}
			tempcol = colCode;
			tmp = sColor.BeforeFirst(';');
			tmp.ToLong(&colCode);
			//colCode = atoi(szColor);//+8;
			//*bBackColor = 0;
			if (colCode>40 && colCode<48) {
				*bBackColor=(BYTE)colCode;
				colCode=37;
				}
			else if (tempcol) colCode += 8;
			if (sColor.length()>=3)
			{
				if (sColor.GetChar(2)==';') {
				//memcpy(szColor, &szColor[3], _tcslen(&szColor[3]));
					sColor = sColor.Mid(3, wxStrlen(sColor.c_str()+3));
					long x;
					sColor.ToLong(&x);
				//	= atoi(szColor);
					if (x>=40)
						*bBackColor = (BYTE)x;
					else colCode = x;
					}
			}
		}
	}
	//if ((*pos)<(int)_tcslen(szData))
	if ((*pos)<sLine->length())
		(*pos)++;
	if (colCode==1 && boFirst) {
		colCode = GetColor(pos, sLine, FALSE, bFontAttr, bBackColor);
		if (colCode==-1) colCode = 1;
		if (colCode>=3 && colCode<=5) {
			*bFontAttr = (BYTE)colCode;
			colCode = GetColor(pos, sLine, FALSE, bFontAttr, bBackColor) + 8;
			}
		else if (colCode!=1)
			colCode += 8;
		}
	else if (colCode==1 && !boFirst && lastcolcode<40)
		colCode = lastcolcode + 8;
	else if (colCode==1 && !boFirst && lastcolcode>=40)
		colCode = 1;
	else if (lastcolcode==1 && !boFirst)
		colCode += 8;
	//italic, underlined, flashing
	if ((colCode>=3 && colCode<=5) && boFirst) {
		*bFontAttr = (BYTE)colCode;
		if (sColor.length()>2)
		{
			if(sColor.GetChar(1)==';') {
				//memcpy(szColor, &szColor[2], _tcslen(&szColor[2]));
				//colCode = atoi(szColor);
				sColor = sColor.Mid(2, wxStrlen(sColor.c_str()+2));
				sColor.ToLong(&colCode);
				if (colCode>=40)
					*bBackColor=(BYTE)colCode;
				}
		}
		}
	else if ((lastcolcode>=3 && lastcolcode<=5) && !boFirst) {
		*bFontAttr = (BYTE)lastcolcode;
		if (sColor.length()>2)
		{
			if(sColor.GetChar(1)==';') {
				sColor = sColor.Mid(2, wxStrlen(sColor.c_str()+2));
				sColor.ToLong(&colCode);
				//memcpy(szColor, &szColor[2], _tcslen(&szColor[2]));
				//colCode = atoi(szColor);
				}
		}
		}	
	else if ((colCode>=3 && colCode<=5) && !boFirst && lastcolcode) {
		*bFontAttr = (BYTE)colCode;
		colCode=lastcolcode;
		}
	else if((colCode>=3 && colCode<=5))
		*bFontAttr = (BYTE)colCode;
	else if (!colCode)
	{
		*bFontAttr = 0;
		*bBackColor = 0;
	}
	return lastcolcode = colCode;
}

size_t MudWindow::ParseTelnet(wxString *sLine, size_t curpos)
{
size_t pos=0;
static bool boATCPData = false;
static int number = 200;
RegExp num("([\\w\\.]+)\\s([\\d\\w,\\(\\)\\s:\\/\\-']+)");
//static wxString data = wxEmptyString;
	wxString sL = *sLine;
	curpos++;
	if (boATCPData)
	{
		boATCPData = false;
		m_atcpstring.Append(" ");
		//while (sL[curpos].GetValue()!=IAC && sL[curpos+1].GetValue()!=SE)
		if(sL[curpos].GetValue()==SE)
		{
			wxString sub = sL.substr(0, curpos-1);
			//m_atcpstring.append(sub);
			m_atcpstring << sub.ToUTF8();
			curpos++;
			m_atcpdata = true;
			if (curpos+1==sL.length())
			{
				m_atcpstring.Append(sL[curpos]);
				//boATCPData = true;
				//return curpos+pos-1;
			}
			if (m_parent->GetGlobalOptions()->GetUseEvents() && !boATCPData && !m_atcpstring.empty() && m_parent->GetGlobalOptions()->GetUseEvTelnetData())
			{
				wxString s;
				s = wxString::Format("%cfunc(\"%s\", \"OnTelnetData(\'%d\',\'%s')\")", m_parent->GetGlobalOptions()->GetCommand(),
					m_parent->GetGlobalOptions()->GetEventFile(), number, m_atcpstring.c_str());
				if (!boATCPData)
					m_parent->m_input->ParseCommandLine(&s);
			}
			if (!boATCPData)
			{
				//RegExp brief("Room.Brief (\\w+)");
				amcLua *aL = GetLState();
				lua_State *L = aL->GetLuaState();
				lua_settop(L,0);
				lua_getglobal(L, "_amcATCP");
				if (num.Match(m_atcpstring))
				{
					lua_pushstring(L, num.GetMatch(1).mb_str());
					wxString name = num.GetMatch(0);
					name.Replace(".", "");
					lua_setfield(L, -2, name.mb_str());
				}
				m_atcpstring.Empty();
				//m_atcpdata = false;
			}
			return curpos+pos-1;
		}
	}
	if (sLine->at(curpos)==EOS)
		return curpos+pos-1;
	//wxUniChar c = sL[curpos].GetValue();
	if (sLine->at(curpos)==WILL)
	{
	   pos++;
	  
	   switch (sL[curpos+1].GetValue())
	   {
		    case SEND:
				m_password = true;
				//pos--;
				break;
			case EOR:
				if (m_parent->GetGlobalOptions()->UseGAEOR())
				{
				
					wxString s;
					s.Printf("%c%c%c", IAC, DO, EOR);
					m_sock->Write(s.To8BitData(), 3);
				}
				break;

			case TELOPT_COMPRESS2:
				if (!m_mccp2)
				{
					//sm.boMCCP2 = TRUE;
					if (m_parent->GetGlobalOptions()->UseMCCP())
					{
						//IAC DO COMPRESS
						//if (!m_parent->GetGlobalOptions()->UseUTF8())
						wxString s;
						s.Printf("%c%c%c", IAC, DO, TELOPT_COMPRESS2);
						Write(s);
						
						m_mccpneg = true;
						Msg(_("MCCP2 agreed!"));
						

					}
					else
						m_sock->Write("\xff\xfe\x56", 3); //IAC DONT MCCP
					//boMCCP2 = TRUE;
				}
				break;
			case TELOPT_COMPRESS:
				m_sock->Write("\xff\xfe\x55", 3);
				break;
			case MSP:
				//no i will not IAC DONT MSP
				if (m_parent->GetGlobalOptions()->UseMSP())
				{
					m_sock->Write("\xff\xfd\x5a", 3);
					m_msp = true;
					Msg(_("MSP enabled!"));
				}
				else
				{
					m_sock->Write("\xff\xfe\x5a", 3);
					Msg(_("MSP denied!"));
				}
				break;
			case MXP:
				if (m_parent->GetGlobalOptions()->UseMXP())
				{
					wxString s;
					s.Printf("%c%c%c", IAC, DO, MXP);
					m_sock->Write(s.To8BitData(), 3);
					m_mxp = true;
					//m_sock->Write("\xff\xfd\x5b", 3);
					Msg(_("MXP enabled!"));
				}
				else
				{
					wxString s;
					s.Printf("%c%c%c", IAC, DONT , MXP);
					m_sock->Write(s.To8BitData(), 3);
					Msg(_("MXP denied!"));
				}
				break;
			case SUPPRESS_GO_AHEAD:
				{
				wxString s;
				s.Printf("%c%c%c", IAC, DO, SUPPRESS_GO_AHEAD);
				//sprintf(szSend, "%c%c%c", IAC, DO, SUPPRESS_GO_AHEAD);
				m_sock->Write(s.To8BitData(), (wxUint32)s.length());
				break;
				}
			case NAWS:
				if (m_parent->GetGlobalOptions()->UseNAWS())
				{
					wxString s;
					wxSize ss;
					s.Printf("%c%c%c", IAC, WILL, NAWS);
					m_sock->Write(s.To8BitData(), (wxUint32)s.length());
					//Msg(_("NAWS agreed!"));
					ss=GetClientSize();
					wxClientDC dc(this);
					dc.SetFont(*m_font);
					int s_lines = ss.GetHeight()/dc.GetCharHeight();
					int s_chars = ss.GetWidth()/dc.GetCharWidth();
					char c[10];
					c[0]=(char)IAC;
					c[1]=(char)SB;
					c[2]=(char)NAWS;
					c[3]=(char)HIBYTE(s_chars);
					c[4]=(char)LOBYTE(s_chars);
					c[5]=(char)HIBYTE(s_lines);
					c[6]=(char)LOBYTE(s_lines);
					c[7]=(char)IAC;
					c[8]=(char)SE;
					m_sock->Write(c, 9);
					//s.Clear();
					//s.Printf("%c%c%c%d%d%d%d%c%c", IAC, SB, (int)NAWS, (int)HIBYTE(s_chars), (int)LOBYTE(s_chars), (int)HIBYTE(s_lines), (int)LOBYTE(s_lines), IAC, SE);
					//s.Printf("%c%c%c%d%d%d%d%c%c", IAC, SB, NAWS, 0, 159, 0, 44, IAC, SE);
					//m_sock->Write(s.To8BitData(), (wxUint32)9);
					//m_sock->Write(ch,9);
					//wxString msg;
					//msg.Printf(_("NAWS set: %d %d"), LOBYTE(s_chars), LOBYTE(s_lines));
					//Msg(msg);
				}
				else
				{
					wxString s;
					s.sprintf("%c%c%c", IAC, WONT, NAWS);
					m_sock->Write(s.To8BitData(), 3);
				}
				break;
			case AARD1:
				{
				wxString s;
				s.sprintf("%c%c%c", IAC, DO, AARD1);
				m_sock->Write(s.To8BitData(), 3);
				Msg(_("AARD telnet negotiated!"));
				break;
				}
			case ATCP:
				{
					if (m_parent->GetGlobalOptions()->UseATCP())
					{
						wxString s;
						s.Printf("%c%c%c", IAC, DO, ATCP);
						m_sock->Write(s.To8BitData(), (wxUint32)3);
						Msg(_("ATCP negotiated!"));
						m_atcp = true;
						m_parent->luaCreateATCPTable();
					}
					else
					{
						wxString s;
						s.Printf("%c%c%c", IAC, DONT, ATCP);
						m_sock->Write(s.To8BitData(), (wxUint32)3);
					}
				}
				break;
			case TERMINAL_TYPE:
				{
				wxString s;
				s.Printf("%c%c%c", IAC, DO, TERMINAL_TYPE);
				m_sock->Write(s.To8BitData(), (wxUint32)3);
				Msg(_("Terminal type requested!"));
				}
				break;
			case ZMP:
				{
				wxString s;
				s.Printf("%c%c%c", IAC, DONT , ZMP);
				m_sock->Write(s.To8BitData(), (wxUint32)3);
				}
				break;
			case MSSP:
				{
				wxString s;
				s.Printf("%c%c%c", IAC, DONT , MSSP);
				m_sock->Write(s.To8BitData(), (wxUint32)3);
				}
				break;
			case NEW_ENVIRON:
				{
				wxString s;
				s.Printf("%c%c%c", IAC, DONT , NEW_ENVIRON);
				m_sock->Write(s.To8BitData(), (wxUint32)3);
				}
				break;
			default:
				//pos += 2;
				break;
			}
		}
		if (sLine->at(curpos) == DO)
		{
			pos++;
			switch (sL[curpos+1].GetValue())
			{
				case TERMINAL_TYPE:
					{
					wxString s;
					s.Printf("%c%c%c", IAC, WILL, TERMINAL_TYPE);
					m_sock->Write(s.To8BitData(), (wxUint32)3);
					Msg(_("Terminal type requested!"));
					}
					break;
				case NAWS:
					if (m_parent->GetGlobalOptions()->UseNAWS())
					{
						wxString s;
						wxSize ss;
						s.Printf("%c%c%c", IAC, WILL, NAWS);
						m_sock->Write(s.To8BitData(), (wxUint32)3);
						//Msg(_("NAWS agreed!"));
						ss=GetClientSize();
						wxClientDC dc(this);
						dc.SetFont(*m_font);
						ss=GetClientSize();
						int s_lines = ss.GetHeight()/dc.GetCharHeight();
						int s_chars = ss.GetWidth()/dc.GetCharWidth();
						//int x = HIBYTE(s_chars);
						char c[10];
						c[0]=(char)IAC;
						c[1]=(char)SB;
						c[2]=(char)NAWS;
						c[3]=(char)HIBYTE(s_chars);
						c[4]=(char)LOBYTE(s_chars);
						c[5]=(char)HIBYTE(s_lines);
						c[6]=(char)LOBYTE(s_lines);
						c[7]=(char)IAC;
						c[8]=(char)SE;
						m_sock->Write(c, 9);
						//s.Printf("%c%c%c%c%c%c%c%c%c", IAC, SB, (int)NAWS, (int)HIBYTE(s_chars), (int)LOBYTE(s_chars), (int)HIBYTE(s_lines), (int)LOBYTE(s_lines),  IAC, SE);
						//m_sock->Write(s.To8BitData(), (wxUint32)9);
						//Msg(_("NAWS set!"));
					}
					break;
				case MXP:
					{
					wxString s;
					if (m_parent->GetGlobalOptions()->UseMXP())
					{
						s.Printf("%c%c%c", IAC, WILL, MXP);
						m_sock->Write(s.To8BitData(), (wxUint32)s.length());
						Msg(_("MXP enabled!"));
					}
					else
					{
						s.Printf("%c%c%c", IAC, WONT, MXP);
						m_sock->Write(s.To8BitData(), (wxUint32)s.length());
						Msg(_("MXP denied!"));
					}
					break;
					}
				case AARD1:
					break;
				case ATCP:
					{
						if (m_parent->GetGlobalOptions()->UseATCP())
						{
							wxString s;
							s.Printf("%c%c%c", IAC, WILL, ATCP);
							m_sock->Write(s.To8BitData(), (wxUint32)3);
							m_atcp = true;
							m_parent->luaCreateATCPTable();
						}
						else
						{
							wxString s;
							s.Printf("%c%c%c", IAC, WONT, ATCP);
							m_sock->Write(s.To8BitData(), (wxUint32)3);
							m_atcp = false;
						}
					}
					break;
				case NEW_ENVIRON:
					{
					wxString s;
					s.Printf("%c%c%c", IAC, WONT , NEW_ENVIRON);
					m_sock->Write(s.To8BitData(), (wxUint32)3);
					}
					break;
				default:
					break;
				
				}
			}
		if (sLine->at(curpos) == WONT)
		{
			pos++;
			switch (sL[curpos + 1].GetValue())
			{
				case SEND:
					m_password = false;
					//pos += 2;
					break;
				case MXP:
					m_mxp = false;
					//Msg("WON'T MXP");
					break;
				case TELOPT_COMPRESS2:
					Msg("WONT COMPRESS");
					break;
				default:
					//pos += 2;
					break;
				}
			}
		if (sLine->at(curpos) == DONT)
		{
			pos++;
			switch (sL[curpos+1].GetValue())
			{
				case NAWS:
					break;
				case TELOPT_COMPRESS2:
					Msg("Dont Compress");
					break;
				default:
					break;
			}
		}
		if (sLine->at(curpos) == SB)
		{
			pos++;
			switch (sL[curpos + 1].GetValue())
			{
				case MXP:
					if (sLine->at(curpos+2) == IAC && sLine->at(curpos+3) == SE)
						{
							m_mxp = true;
						}
					pos += 2;
					if (curpos+3<=sLine->length()-1)
					{
						wxString h = sL.substr(curpos+5);
						if (h.Cmp(wxEmptyString))
						{
							ParseBufferMXP(h.char_str());
							pos = sLine->length()-3;
						}
					}
				//pos = stcpy = sLine->length()-2;
			
					break;
				case TELOPT_COMPRESS2:
					if (m_mccp2)
					{
						pos+=2;
						break;
					}
					if (sLine->at(curpos+2) == IAC && sLine->at(curpos+3) == SE)
					{
						m_mccp2 = true;
					}
					pos += 2;
					if ((curpos+4) < (size_t)sLine->length()-1)
					{
						m_oddmccp2 = curpos+4;
						pos = sLine->length()-1;
						wxString sub = sL.substr(m_oddmccp2);
						
						m_dc->Decompress(sub, sub.length()-1);
					}
					break;
				
				case TERMINAL_TYPE:
					
					if (sLine->at(curpos+2)==SEND && sLine->at(curpos+3)==IAC && sLine->at(curpos+4)==SE)
					{
						//wxString s;
						char c[11];
						c[0]=(char)IAC;
						c[1]=(char)SB;
						c[2]=(char)TERMINAL_TYPE;
						c[3]=(char)IS;
						c[4]='A';
						c[5]='N';
						c[6]='S';
						c[7]='I';
						c[8]=(char)IAC;
						c[9]=(char)SE;
						m_sock->Write(c, 10);
						
						pos+=3;
					}
					break;
				case AARD1:
					number = AARD1;
					curpos++;
					m_atcpdata = false;
					//m_curline--;
					while (sL[curpos].GetValue()!=IAC && sL[curpos+1].GetValue()!=SE)
					{
						if (sL[curpos].GetValue()!=AARD1)
							if (sL[curpos].GetValue()!=0)
								m_atcpstring.Append(sL[curpos]);
						curpos++;
						
						if (curpos+1==sL.length())
						{
							if (sL[curpos]!=0)
								m_atcpstring.Append(sL[curpos]);
							boATCPData = true;
							m_atcpdata = false;
							if (m_mxp)
								curpos-=2;
							else curpos-=3;
							break;
						}
					}
					//m_botelnetparsed = true;
					break;
				case ATCP:
					{
					//wxString s;
					//wxString data;
						number = ATCP;
						curpos++;
						//m_curline--;
						m_atcpdata = false;
						while (sL[curpos].GetValue()!=IAC && sL[curpos+1].GetValue()!=SE)
						{
							if (sL[curpos].GetValue()!=ATCP)
								if (sL[curpos].GetValue()!=0)
									m_atcpstring.Append(sL[curpos]);
							curpos++;
							
							if (curpos+1==sL.length())
							{
								if (sL[curpos]!=0)
									m_atcpstring.Append(sL[curpos]);
								boATCPData = true;
								m_atcpdata = false;
								if (m_mxp)
									curpos-=2;
								else curpos-=2;
								break;
							}
						}
						
						//if (m_parent->GetGlobalOptions()->GetUseEvDisco())
						//	{
						
					}
					
					break;
				default:
					break;
				}
			}
		if (m_parent->GetGlobalOptions()->GetUseEvents() && !boATCPData && !m_atcpstring.empty() && m_parent->GetGlobalOptions()->GetUseEvTelnetData())
		{
			wxString s;
			s = wxString::Format("%cfunc(\"%s\", \"OnTelnetData(\'%d\',\'%s')\")", m_parent->GetGlobalOptions()->GetCommand(),
					m_parent->GetGlobalOptions()->GetEventFile(), number, m_atcpstring.c_str());
			if (!boATCPData)
				m_parent->m_input->ParseCommandLine(&s);
		}
		if (!boATCPData)
		{
			amcLua *aL = GetLState();
			lua_State *L = aL->GetLuaState();
			lua_settop(L,0);
			lua_getglobal(L, "_amcATCP");
			//int len = lua_objlen(L,-2);
			if (num.Match(m_atcpstring))
			{
				lua_pushstring(L, num.GetMatch(1).mb_str());
				wxString name = num.GetMatch(0);
				name.Replace(".", "");
				lua_setfield(L, -2, name.mb_str());
			}
			m_atcpstring.Empty();
			//m_atcpdata = false;
		}
		
return curpos+pos;
}

size_t MudWindow::ParseMSP(wxString *sLine, size_t curpos)
{
	//MSP-Defaults
wxString soundname, msp;
wxString buffer;
/*int iVolume = 100;
int iRepeat = 1;
int Priority = 50;
int Continue = 1;*/
size_t pos = curpos;
//int spos=0, anotherpos=0;
wxString sL = *sLine;

	curpos++;
	while (sL.at(curpos)!=')')
		curpos++;
	if (curpos>pos)
	{
		msp = sL.substr(pos, curpos-pos+1);
	}
	int start = msp.Find('(');
	int end = msp.Find(' ');//file name
	RegExp vol("V=(\\d+)");
	if (vol.Match(msp), true)
	{
		int i =	atoi(vol.GetMatch(0).mb_str());
		float f = (float)i/100;
		m_parent->m_media->SetVolume(f);
		
	}
	else
		m_parent->m_media->SetVolume(1.0);
	msp = msp.substr(start+1, end-(start+1));
	wxString dir = m_parent->GetGlobalOptions()->GetSoundDir();
	wxSetWorkingDirectory(dir);
	dir<<msp;
	
	m_parent->m_media->Load(dir);
	
	
	return curpos;
}


wxUint64 MudWindow::GetScrollPage()
{
	return AdjustScrollPage();
}

wxUint64 MudWindow::AdjustScrollPage()
{
wxClientDC dc(this);
wxSize s;
wxCoord char_height, starty, char_len;
int pos, start, end, diff=0;

	s=GetClientSize();
	dc.SetFont(*m_font);
	char_height = dc.GetCharHeight();
	starty = s.y-char_height;
	char_len = dc.GetCharWidth();
	if (m_parent->GetGlobalOptions()->UseWrap() && m_parent->GetGlobalOptions()->AutoWrap())//we use autowrapping
		m_wrap = (s.x/char_len);
	else if (!m_parent->GetGlobalOptions()->UseWrap())
		m_wrap=0;
	
	pos =  GetScrollPos(wxVERTICAL);
	start = m_curline < pos + m_scrollrange ? m_curline : pos + m_scrollrange;
	end = start-m_scrollrange;
	if (end<0)
		end=0;
	int i = start - 1;
	int ff=0;
	while (i>=(end+diff))
	{

		if (m_wrap)
		{
			int x;
			//GetTextExtent(m_vmudlines.at(i).GetLineText(), &x, &y);
			//x = abs(x/char_len);
			x = (int)m_vmudlines.at(i).GetTextLength();
			ff = abs((int)(x/m_wrap));
		}
		else ff=0;
		if (ff)
		{
			//m_scrollrange -= ff;
			diff += ff;
			starty -= (ff*char_height);
			//i-=ff;
			//end = start - m_scrollrange-ff;
		}
		i--;
		starty -= char_height;
		//if (starty < 3*char_height)
		//	break;
	}
	float round = float(s.y/char_height);
	round += 0.5;
	m_scrollrange = (wxUint64)floor(round);
	m_scrollrange -= diff+1;
	
	if (m_scrollrange<=0)
		m_scrollrange=1;
	//pos += (m_curline-m_scrollrange);
	//if (pos<0)
	//	pos=0;
	//SetScrollbar(wxVERTICAL, pos, m_scrollrange, m_curline);
	//::wxLogDebug(wxT("start = %d, end=%d, diff=%d, scrollrange=%d"), start, end, diff, m_scrollrange);
return m_scrollrange;
//return diff;
}

void MudWindow::SetScrollPage()
{
int scrollpos;

	AdjustScrollPage();
	scrollpos = m_curline - m_scrollrange;
	if (scrollpos<0)
		scrollpos=0;
	SetScrollbar(wxVERTICAL, scrollpos, m_scrollrange, m_curline);
	//Refresh();
	//Update();
}

//Event handlers
void MudWindow::OnSize(wxSizeEvent& event)
{
	wxSize ss=GetClientSize();
	//wxBitmap bm(ss.x, ss.y);
	m_drawbmp.SetWidth(ss.x);
	m_drawbmp.SetHeight(ss.y);
	SetScrollPage();
	Refresh();
	//Update();
}
void MudWindow::OnPaint(wxPaintEvent& event)
{
wxCoord char_height, char_len;
wxCoord starty=1;
long end=0, start=0;
//wxCoord startx=1;
wxSize s, ss;
int pos;
size_t sublines=0;

	ss=GetClientSize();
	wxBitmap bm(ss.x, ss.y);
	//m_drawbmp.SetWidth(ss.x);
	//m_drawbmp.SetHeight(ss.y);
	wxBufferedPaintDC dc(this, bm);
	//wxAutoBufferedPaintDC dc(this);
	//wxBufferedPaintDC dc (this);
	//wxPaintDC dc(this);
	dc.SetBackgroundMode(wxSOLID);
	wxBrush b(m_background);
	dc.SetBackground(b);
	dc.Clear();
	dc.SetFont(*m_font);
	char_height = dc.GetCharHeight();
	char_len = dc.GetCharWidth();
	s = dc.GetSize();
	//dc.SetLogicalOrigin(0,s.y);
	starty=s.y-char_height;
	//dc.SetAxisOrientation(true, true);
	//m_scrollrange = (s.y/char_height);
	if (m_parent->GetGlobalOptions()->UseWrap() && m_parent->GetGlobalOptions()->AutoWrap())//we use autowrapping
		m_wrap = (s.x/char_len);
	else if (!m_parent->GetGlobalOptions()->UseWrap())
		m_wrap=0;
	pos =  GetScrollPos(wxVERTICAL);
	start = m_curline < pos + m_scrollrange ? m_curline : pos + m_scrollrange;
	end = start-m_scrollrange-1;
	if (end<0)
		end=0;
	//::wxLogDebug(wxT("start=%3d, end=%3d, m_curline=%3d, m_scrollrange=%3d"), start, end, m_curline, m_scrollrange);
	m_start = start;
	m_end = end;
	//if (!m_vmudlines.empty())
	//{

		for (long i=start-1; i>=(long)(end+sublines);i--)
		{
			if (m_wrap)//calculate how many lines this line will need using the wrap column!
			{
				int l = m_vmudlines.at(i).GetTextLength();
				if (m_timestamps)
				{
					l += m_vmudlines.at(i).GetTime().length();
					if (m_milliseconds)
						l += m_vmudlines.at(i).GetMilliSeconds().length();
				}
					sublines = l/m_wrap;
				//end += sublines;
			}
			if (!m_parent->GetGlobalOptions()->UseWrap() || !sublines)//only one...draw it
				starty = DrawAnsi(&dc, starty, i, char_len, char_height);
			else
				starty = DrawMultiAnsi(&dc, starty, i, char_len, char_height, sublines);
		}
	//}
}

void MudWindow::OnContextMenu(wxContextMenuEvent &event)
{
	/*wxMenu *contextMenu = new wxMenu;
	contextMenu->Append(ID_OUTFONT, _("Font"), _("Set the output font"));
	contextMenu->AppendCheckItem(ID_STAMPS, _("Timestamps"), _("Show timestamps in this window"));
	contextMenu->Check(ID_STAMPS, m_timestamps);
	if (m_selline!=-1)
	{
		contextMenu->AppendSeparator();
		contextMenu->Append(ID_MAKEACTION, _("Create action..."), _("Create an action using the linetext"));
	}
	wxPoint p = event.GetPosition();
	p = ScreenToClient(p);
	//PopupMenu(contextMenu, p.x, p.y);
	delete contextMenu;*/
	event.Skip();
}

void MudWindow::OnOutputFont(wxCommandEvent& event)
{
	wxFont f = wxGetFontFromUser(m_parent, *m_font, _("Set font for this window"));
	if (f.IsOk())
	{
		SetNFont(&f);
		SetUFont(&f);
		Refresh();
		Update();
		if (this==m_parent->m_child)
			m_parent->SaveGlobalOptions();
	}
}

void MudWindow::OnTimeStamps(wxCommandEvent& event)
{
	m_timestamps = !m_timestamps;
	wxMenu *m = (wxMenu*)event.GetEventObject();
	m->Check(ID_STAMPS, m_timestamps);
	Refresh();
	Update();
}

void MudWindow::OnMakeAction(wxCommandEvent& event)
{
	//wxCommandEvent ev;// = new wxCommandEvent();
	wxCommandEvent ev;// = event;
	ev.SetEventObject(m_parent);
	ev.SetId(ID_OBJS);
	ev.SetEventType(wxEVT_COMMAND_MENU_SELECTED);
	ev.SetString(GetSelectedText());
	if (wxTheClipboard->Open())
	{
		wxTheClipboard->SetData( new wxTextDataObject(GetSelectedText()));
        wxTheClipboard->Close();
	}
	wxPostEvent(m_parent, ev);
}

void MudWindow::OnMxpMenu(wxCommandEvent& event)
{
	//wxMenu *m = (wxMenu*)event.GetEventObject();
	m_parent->m_input->Parse(m_mxpcommand.at(event.GetId()-ID_MXPMENU));
}

void MudWindow::OnMxpPromptMenu(wxCommandEvent& event)
{
	m_parent->m_input->WriteText(m_mxpcommand.at(event.GetId()-ID_MXPMENUPROMPT));
}


//Draw one ansi line .. no wrapping
wxCoord MudWindow::DrawAnsi(wxBufferedPaintDC* dc, wxCoord starty, int lnr, wxCoord char_len, wxCoord char_height)
{
ale_it it;
wxCoord startx=1;
//wxCoord cur_pos=1;

	int x=0;
	m_vmudlines.at(lnr).SetYPos(starty);
	if (m_timestamps)
	{
		wxString s = m_vmudlines.at(lnr).GetTime();
		if (m_milliseconds)
			s.Append(":"+ m_vmudlines.at(lnr).GetMilliSeconds() + " ");
		else
			s.Append(" ");
		dc->SetTextForeground(m_colansi[7]);
		dc->SetTextBackground(m_colansi[0]);
		dc->DrawText(s, startx, starty);
		wxSize si = dc->GetTextExtent(s);
		startx+=si.GetWidth();
	}
	if (!m_vmudlines.at(lnr).m_vstyle.empty())
	{
		for (it = m_vmudlines.at(lnr).m_vstyle.begin(); it!=m_vmudlines.at(lnr).m_vstyle.end(); it++)
		{
			startx = DrawStyle(dc, lnr, x++, startx, starty, char_len);
		}
	}
	starty-=char_height;

return starty;
}

wxCoord MudWindow::DrawMultiAnsi(wxBufferedPaintDC* dc, wxCoord starty, int lnr, wxCoord char_len, wxCoord char_height, size_t sublines)
{
ale_it it;
wxCoord startx=1;
//wxCoord cur_pos=1;
//int out=0;
int x=0;
size_t sublen=0;
size_t stringpos = 0;
AnsiLineElement style;
size_t lines=1;
size_t xx = 0;
wxSize si;
	starty -= (wxCoord)(sublines*char_height);
	m_vmudlines.at(lnr).SetYPos(starty);
	if (m_timestamps)
	{
		wxString s = m_vmudlines.at(lnr).GetTime();
		if (m_milliseconds)
			s.Append(":"+ m_vmudlines.at(lnr).GetMilliSeconds() + " ");
		else
			s.Append(" "); //wxString s = m_vmudlines.at(lnr).GetTime() + " ";
		dc->SetTextForeground(m_colansi[7]);
		dc->SetTextBackground(m_colansi[0]);
		dc->DrawText(s, startx, starty);
		si = dc->GetTextExtent(s);
		startx+=si.GetWidth();
		xx = s.length();
	}
	int len=0;
	for (int i=0;i<m_vmudlines.at(lnr).m_vstyle.size();i++)
		len += m_vmudlines.at(lnr).m_vstyle.at(i).GetLen();
	while(sublines)
	{

		sublen = m_vmudlines.at(lnr).m_vstyle.at(x).GetText().length();
		//if (sublines && sublen==stringpos)
		//	break;
			//continue;
		while (stringpos < len)//m_vmudlines.at(lnr).GetLineText().length())
		{
			if (stringpos==sublen)
			{
				x++;
				while (!m_vmudlines.at(lnr).m_vstyle.at(x).GetText().length())
					x++;
				/*if (!m_vmudlines.at(lnr).m_vstyle.at(x).GetText().length())
					x++;
				if (!m_vmudlines.at(lnr).m_vstyle.at(x).GetText().length())
					x++;*/
				if (x>=m_vmudlines.at(lnr).m_vstyle.size())
					x=m_vmudlines.at(lnr).m_vstyle.size()-1;
				sublen += m_vmudlines.at(lnr).m_vstyle.at(x).GetText().length();
				
			}
			if ((lnr >= (int)m_selline && lnr <= (int)m_sellineend) || (lnr >= (int)m_sellineend && lnr <= (int)m_selline))
			{
				dc->SetTextForeground(m_vmudlines.at(lnr).m_vstyle.at(x).GetBCol());
				dc->SetTextBackground(m_vmudlines.at(lnr).m_vstyle.at(x).GetFCol());
			}
			else
			{
				dc->SetTextForeground(m_vmudlines.at(lnr).m_vstyle.at(x).GetFCol());
				dc->SetTextBackground(m_vmudlines.at(lnr).m_vstyle.at(x).GetBCol());
			}
			wxString sub = m_vmudlines.at(lnr).GetLineText().at(stringpos);
			if (m_vmudlines.at(lnr).m_vstyle.at(x).GetFontStyle()==4)//underlined
				dc->SetFont(*m_ufont);
			if (m_vmudlines.at(lnr).m_vstyle.at(x).GetFontStyle()==3)//italic
				dc->SetFont(*m_ifont);
			
			si = dc->GetTextExtent(sub);
			dc->SetClippingRegion(startx, starty, si.GetWidth(), char_height);
			dc->DrawText(sub, startx, starty);
			dc->DestroyClippingRegion();
			
			if (m_vmudlines.at(lnr).m_vstyle.at(x).GetFontStyle()==4)//underlined
				dc->SetFont(*m_font);
			if (m_vmudlines.at(lnr).m_vstyle.at(x).GetFontStyle()==3)//italic
				dc->SetFont(*m_font);
			//startx += (char_len);
			//startx += 1;
			startx += si.GetWidth();	
			
			if (stringpos+xx==m_wrap*lines)
			{
				startx=1;
				starty += char_height;
				sublines--;
				lines++;
			}
			stringpos++;
			if (stringpos+xx==m_wrap*lines)
			{
				sublines--;
				if ((int)sublines<0)
					sublines=0;
				lines++;
				startx=1;
				starty += char_height;
			}
		}
		if (sublines && sublen==stringpos)
			break;
	}

return (wxCoord)(starty - (lines*char_height));
}

wxCoord MudWindow::DrawStyle(wxBufferedPaintDC *dc, unsigned int lnr, int snr, wxCoord startx, wxCoord starty, wxCoord char_len)
{
	if ((lnr >= (unsigned int)m_selline && lnr <= (unsigned int)m_sellineend) || (lnr >= (unsigned int)m_sellineend && lnr <= (unsigned int)m_selline))
	{
		dc->SetTextForeground(m_vmudlines.at(lnr).m_vstyle.at(snr).GetBCol());
		dc->SetTextBackground(m_vmudlines.at(lnr).m_vstyle.at(snr).GetFCol());
	}
	else
	{
		dc->SetTextForeground(m_vmudlines.at(lnr).m_vstyle.at(snr).GetFCol());
		dc->SetTextBackground(m_vmudlines.at(lnr).m_vstyle.at(snr).GetBCol());
	}
	if (m_vmudlines.at(lnr).m_vstyle.at(snr).GetFontStyle()==4)//underlined
		dc->SetFont(*m_ufont);
	if (m_vmudlines.at(lnr).m_vstyle.at(snr).GetFontStyle()==3)//italic
		dc->SetFont(*m_ifont);
	
		//m_font->SetUnderlined(true);
	wxString text;
	text = m_vmudlines.at(lnr).m_vstyle.at(snr).GetText();
	if (text.length())
	{
		/*for (s=text.begin();s!=text.end();s++)
		{
			ssi = dc->GetTextExtent(*s);
			//dc->SetClippingRegion(startx, starty, si.GetWidth(), si.GetHeight());
			dc->DrawText(*s, startx, starty);
			//dc->DestroyClippingRegion();
			startx += ssi.GetWidth()-1;
		}*/
		wxSize si = dc->GetTextExtent(text);
		dc->SetClippingRegion(startx, starty, si.GetWidth(), si.GetHeight());
		dc->DrawText(text, startx, starty);
		dc->DestroyClippingRegion();
		startx += si.GetWidth();
		
	}
	//startx += (wxCoord)m_vmudlines.at(lnr).m_vstyle.at(snr).GetLen()*char_len;
	
	if (m_vmudlines.at(lnr).m_vstyle.at(snr).GetFontStyle()==4)//underlined
		dc->SetFont(*m_font);
	if (m_vmudlines.at(lnr).m_vstyle.at(snr).GetFontStyle()==3)//italic
		dc->SetFont(*m_font);
	//m_font->SetUnderlined(false);
	return startx;
}

long MudWindow::ParseHexColor(wxString s)
{
	wxString red = s.substr(0, 2);
	wxString green = s.substr(2, 2);
	wxString blue = s.substr(4,2);
	long r;
	red.ToLong(&r, 16);
	long g;
	green.ToLong(&g, 16);
	long b;
	blue.ToLong(&b, 16);
	return RGB(r,g,b);
}

unsigned long MudWindow::CalcLine(wxPoint click)
{
unsigned long line=0;
int i, range;
	wxClientDC dc(this);
	dc.SetFont(*m_font);
	wxCoord char_height = dc.GetCharHeight();
	int pos = GetScrollPos(wxVERTICAL);
	if (!pos)
		range = m_curline;
	else
		range = m_scrollrange;// GetScrollRange(wxVERTICAL);
	for (i = pos + range -1; i >= pos+1; i--)
	{
	    if (i>=(int)m_vmudlines.size())
            continue;
		if (click.y <= m_vmudlines.at(i).GetYPos() && click.y >= m_vmudlines.at(i-1).GetYPos())
		{
			line = i;
			break;
		}
	}
	if ((pos+range-1)>=(int)m_vmudlines.size())
        return (unsigned long)m_vmudlines.size();
	int l = m_vmudlines.at(pos+range-1).GetTextLength();
	if (m_timestamps)
		l += m_vmudlines.at(pos+range-1).GetTime().length();
	int sublines = 0;
	if (m_wrap)
		sublines = l/m_wrap;
	sublines++;
	if (click.y >= m_vmudlines.at(pos+range-1).GetYPos() && click.y <= m_vmudlines.at(pos+range-1).GetYPos()+char_height*sublines)
		return range + pos -1;
	return line-1;
}

void MudWindow::SetLineBuffer(deque<class AnsiLine> * v)
{
line_it lit;

	//m_vmudlines.clear();
	m_vmudlines = *v;
}


//Events
void MudWindow::OnScroll(wxScrollWinEvent& event)
{
//wxEventType evt;
WXTYPE evt;
	wxInt64 pos, oldpos;
	if (event.GetOrientation()==wxHORIZONTAL)
        return;
	evt = event.GetEventType();
	//#if defined __WXMSW__
	//AdjustScrollPage();
	//#endif
	//SetScrollPage();

	pos = oldpos = GetScrollPos(wxVERTICAL);//GetScrollPos(wxVERTICAL);
	//AdjustScrollPage();
    #if defined __WXMSW__
	if (evt==wxEVT_SCROLLWIN_LINEUP)
	{
	if (pos)
		--pos;
	}
	else if (evt==wxEVT_SCROLLWIN_LINEDOWN)
	{
	if ((wxUint64)pos<m_curline-m_scrollrange)
		++pos;
	}
	else if (evt==wxEVT_SCROLLWIN_PAGEUP)
	{
	//pos-=m_scrollrange;
	pos -= GetScrollThumb(wxVERTICAL);
	if (pos<0)
        pos=0;
	//AdjustScrollPage();
	}
	else if (evt==wxEVT_SCROLLWIN_PAGEDOWN)
	{
	pos+=m_scrollrange;
	if ((wxUint64)pos>m_curline)
        pos = m_curline;
	//AdjustScrollPage();
	}
	else if (evt==wxEVT_SCROLLWIN_THUMBRELEASE || evt==wxEVT_SCROLLWIN_THUMBTRACK)
	{
		pos=event.GetPosition();
	}
	else if (evt==wxEVT_SCROLLWIN_TOP)
		pos=0;
	else if (evt==wxEVT_SCROLLWIN_BOTTOM)
		pos = m_curline-GetScrollThumb(wxVERTICAL);
	
    if (oldpos!=pos)
	{
		SetScrollbar(wxVERTICAL, pos, m_scrollrange, m_curline);
		Refresh();
		Update();
		
	}
	//AdjustScrollPage();
	#endif
	
	#if defined __WXGTK__ 
	if (GetKEvtForwarded())//key evts have oldpos
	{
        if (evt == wxEVT_SCROLLWIN_PAGEUP)
            pos -= GetScrollThumb(wxVERTICAL);
        else if (evt==wxEVT_SCROLLWIN_PAGEDOWN)
            pos += GetScrollThumb(wxVERTICAL);
        else if (evt==wxEVT_SCROLLWIN_TOP)
            pos = 0;
        else if (evt==wxEVT_SCROLLWIN_BOTTOM)
            pos = m_curline-GetScrollThumb(wxVERTICAL);
    SetKEvtForwarded(false);
    }
	
	if (pos<0)
		pos = 0;
	if (pos>m_curline)
		pos = m_curline;
	//AdjustScrollPage();
	//if (oldpos!=pos)
	//{
		//SetScrollPos(wxVERTICAL, pos);
		SetScrollbar(wxVERTICAL, pos, m_scrollrange, m_curline);
		Refresh();
		Update();
	//}
	//SetScrollPos(wxVERTICAL, pos);
	//Refresh();
	//Update();
	#endif
	#if defined WXOSX 
	if (GetKEvtForwarded())//key evts have oldpos
	{
        if (evt == wxEVT_SCROLLWIN_PAGEUP)
            pos -= GetScrollThumb(wxVERTICAL);
        else if (evt==wxEVT_SCROLLWIN_PAGEDOWN)
            pos += GetScrollThumb(wxVERTICAL);
        else if (evt==wxEVT_SCROLLWIN_TOP)
            pos = 0;
        else if (evt==wxEVT_SCROLLWIN_BOTTOM)
            pos = m_curline-GetScrollThumb(wxVERTICAL);
    SetKEvtForwarded(false);
    }
	
	if (pos<0)
		pos = 0;
	if (pos>m_curline)
		pos = m_curline;
	//AdjustScrollPage();
	//if (oldpos!=pos)
	//{
		//SetScrollPos(wxVERTICAL, pos);
		SetScrollbar(wxVERTICAL, pos, m_scrollrange, m_curline);
		Refresh();
		Update();
	//}
	//SetScrollPos(wxVERTICAL, pos);
	//Refresh();
	//Update();
	#endif
	
	event.Skip();
}

void MudWindow::OnChar(wxKeyEvent& event)
{
int key = event.GetKeyCode();
wxScrollWinEvent newevt;

	newevt.SetPosition(0);
	newevt.SetOrientation(wxVERTICAL);
	newevt.SetEventObject(this);
    switch (key)
	{
	case WXK_HOME:
		newevt.SetEventType(wxEVT_SCROLLWIN_TOP);
		this->GetEventHandler()->ProcessEvent(newevt);
		break;
	case WXK_END:
		newevt.SetEventType(wxEVT_SCROLLWIN_BOTTOM);
		this->GetEventHandler()->ProcessEvent(newevt);
		break;
	}
}


void MudWindow::OnEraseBackground(wxEraseEvent& event)
{
	//SetBackgroundColour(m_colansi[0]);
	//ClearBackground();
	//event.Skip();
}

void MudWindow::OnLeftDown(wxMouseEvent& event)
{
wxPoint p = event.GetPosition();
wxClientDC dc(this);
ale_it it;
size_t len = 0;
size_t cur_subline=0;
bool multiline = false;
int stamp_offset = 0;

	if (m_vmudlines.empty())
		return;
	dc.SetFont(*m_font);
	size_t cxpos = p.x/dc.GetCharWidth();
	cxpos++;
	size_t line = CalcLine(p);
	if ((long)line<0)
		return;
    if (line > m_vmudlines.size()-1)
        line = m_vmudlines.size()-1;
	if (m_timestamps)
	{
		wxString s = m_vmudlines.at(line).GetTime();
		if (m_milliseconds)
			s.Append(":"+ m_vmudlines.at(line).GetMilliSeconds() + " ");
		else
			s.Append(" ");
		stamp_offset=s.length();
	}
	int l = m_vmudlines.at(line).GetTextLength();
	if (m_timestamps)
		l += m_vmudlines.at(line).GetTime().length();
	int sublines = 0;
	if (m_wrap)
		sublines = abs((int)(l/m_wrap));
	if (sublines)
	{
		if (p.y>m_vmudlines.at(line).GetYPos()+dc.GetCharHeight()/**sublines*/+1)
		{
			multiline = true;
			size_t diff = p.y-(m_vmudlines.at(line).GetYPos()+dc.GetCharHeight()+1);
			cur_subline = (size_t)abs((int)(diff/dc.GetCharHeight()))+1;
		}
	}
	int x=0;
	for (it = m_vmudlines.at(line).m_vstyle.begin(); it!=m_vmudlines.at(line).m_vstyle.end(); it++,x++)
	{
		
		len += it->GetLen();
		
		if (sublines && len>=m_wrap && multiline)
		//if (len>m_wrap && p.y>m_vmudlines.at(line).GetYPos()+dc.GetCharHeight()*sublines)
		{
			len -= m_wrap;
			cur_subline--;
			if (cur_subline>0)
				continue;
		}
		
		if (!cur_subline || it== m_vmudlines.at(line).m_vstyle.end()-1)
		{
			if ((cxpos-stamp_offset) <= len )
				break;
		}
		
	}
	if (x>=m_vmudlines.at(line).m_vstyle.size())
		 it = m_vmudlines.at(line).m_vstyle.end()-1;
	if ((cxpos-stamp_offset)<=len)
	{
		if (it->GetFontStyle()==4 && it->GetURL())
		{
			if (it->GetURLText()==wxEmptyString)
				wxLaunchDefaultBrowser(it->GetText());
			else
				wxLaunchDefaultBrowser(it->GetURLText());
			m_linkclicked = true;
			return;
 		}
		
		if (it->GetFontStyle()==4 && it->GetMXPSend())
		{
			if (!it->GetMXPCommand()->empty() && !it->GetPromptSend())
				m_parent->m_input->Parse(it->GetMXPCommand()->at(0));
			else if (it->GetPromptSend())
				m_parent->m_input->WriteText(it->GetMXPCommand()->at(0));
			
			m_linkclicked = true;
			return;
 		}
	}
	if (!m_selected && !m_linkclicked)
	{
		m_selstart = event.GetPosition();
		m_selected = true;
		m_selline = m_sellineend = CalcLine(m_selstart);
	}
	else if (!m_linkclicked)
	{
		m_selected = false;
		m_selline = m_sellineend = -1;
	}
	Refresh();
	Update();
	event.Skip();
}

void MudWindow::OnMouseMove(wxMouseEvent& event)
{
wxPoint p = event.GetPosition();
wxClientDC dc(this);
ale_it it;
size_t len = 0;
size_t cur_subline=0;
static bool bohand=false;
int stamp_offset = 0;
bool multiline = false;
	if (m_vmudlines.empty())
		return;

	dc.SetFont(*m_font);
	unsigned int cxpos = p.x/dc.GetCharWidth();
	cxpos++;
	size_t line = CalcLine(p);
	if ((long)line<0)
		return;
    if (line > m_vmudlines.size()-1)
        line = m_vmudlines.size()-1;

	if (m_vmudlines.at(line).m_vstyle.empty())
        return;
	if (m_timestamps)
	{
		wxString s = m_vmudlines.at(line).GetTime();
		if (m_milliseconds)
			s.Append(":"+ m_vmudlines.at(line).GetMilliSeconds() + " ");
		else
			s.Append(" ");
		stamp_offset=s.length();
	}
	int l = m_vmudlines.at(line).GetTextLength();
	if (m_timestamps)
		l += m_vmudlines.at(line).GetTime().length();
	int sublines = 0;
	if (m_wrap)
		sublines = abs((int)(l/m_wrap));
	if (sublines)
	{
		if (p.y>m_vmudlines.at(line).GetYPos()+dc.GetCharHeight()/**sublines*/+1)
		{
			multiline = true;
			size_t diff = p.y-(m_vmudlines.at(line).GetYPos()+dc.GetCharHeight()+1);
			cur_subline = (size_t)abs((int)(diff/dc.GetCharHeight()))+1;
		}
	}
	int x=0;
	for (it = m_vmudlines.at(line).m_vstyle.begin(); it!=m_vmudlines.at(line).m_vstyle.end(); it++, x++)
	{
		
		len += it->GetLen();
		
		if (sublines && len>=m_wrap && multiline)
		//if (len>m_wrap && p.y>m_vmudlines.at(line).GetYPos()+dc.GetCharHeight()*sublines)
		{
			len -= m_wrap;
			cur_subline--;
			if (cur_subline>=0)
				continue;
		}
		
		if (!cur_subline || it== m_vmudlines.at(line).m_vstyle.end()-1)
		{
			if ((cxpos-stamp_offset) <= len )
				break;
		}
		
	}
	
	if (x>=m_vmudlines.at(line).m_vstyle.size())
		 it = m_vmudlines.at(line).m_vstyle.end()-1;
	if ((cxpos-stamp_offset)<=len)
	{
		if ( (it->GetFontStyle()==4 && it->GetURL()) || (it->GetFontStyle()==4 && it->GetMXPSend()) )
		{
			SetCursor(wxCURSOR_HAND);
			bohand = true;
			//m_tt->SetAutoPop(5000);
			if (m_tt)
				m_tt->SetTip(it->GetHint());
		}
		else
		{
			SetCursor(wxCURSOR_ARROW);
			//m_tt->SetAutoPop(0);
			if (m_tt)
				m_tt->SetTip("");
			bohand = false;
		}
	}
	else
		if (bohand)
		{
			SetCursor(wxCURSOR_ARROW);
			//m_tt->SetAutoPop(1);
			if (m_tt)
				m_tt->SetTip("");
			
		}
	if (event.LeftIsDown() && event.Dragging())
	{
		m_selend = event.GetPosition();
		m_sellineend = CalcLine(m_selend);
	}
	//event.Skip();
	Refresh();
	Update();
	
	event.Skip();

}

void MudWindow::OnLeftUp(wxMouseEvent& event)
{
	//if (m_selected)
	//	m_selected = false;
	m_linkclicked = false;
	event.Skip();
}

void MudWindow::OnRightUp(wxMouseEvent& event)
{
wxPoint p = event.GetPosition();
wxClientDC dc(this);
ale_it it;
size_t len = 0;
size_t cur_subline=0;
bool multiline = false;
int stamp_offset = 0;

	if (m_vmudlines.empty())
		return;
	dc.SetFont(*m_font);
	size_t cxpos = p.x/dc.GetCharWidth();
	cxpos++;
	size_t line = CalcLine(p);
	if ((long)line<0)
		return;
    if (line > m_vmudlines.size()-1)
        line = m_vmudlines.size()-1;
	if (m_timestamps)
	{
		wxString s = m_vmudlines.at(line).GetTime();
		if (m_milliseconds)
			s.Append(":"+ m_vmudlines.at(line).GetMilliSeconds() + " ");
		else
			s.Append(" ");
		stamp_offset=s.length();
	}
	int l = m_vmudlines.at(line).GetTextLength();
	if (m_timestamps)
		l += m_vmudlines.at(line).GetTime().length();
	int sublines;
	if (m_wrap)
		sublines = abs((int)(l/m_wrap));
	if (sublines)
	{
		if (p.y>m_vmudlines.at(line).GetYPos()+dc.GetCharHeight()/**sublines*/+1)
		{
			multiline = true;
			size_t diff = p.y-(m_vmudlines.at(line).GetYPos()+dc.GetCharHeight()+1);
			cur_subline = (size_t)abs((int)(diff/dc.GetCharHeight()))+1;
		}
	}
	int x=0;
	for (it = m_vmudlines.at(line).m_vstyle.begin(); it!=m_vmudlines.at(line).m_vstyle.end(); it++, x++)
	{
		
		len += it->GetLen();
		
		if (sublines && len>=m_wrap && multiline)
		//if (len>m_wrap && p.y>m_vmudlines.at(line).GetYPos()+dc.GetCharHeight()*sublines)
		{
			len -= m_wrap;
			cur_subline--;
			if (cur_subline>0)
				continue;
		}
		
		if (!cur_subline || it== m_vmudlines.at(line).m_vstyle.end()-1)
		{
			if ((cxpos-stamp_offset) <= len )
				break;
		}
		
	}

	if (x>=m_vmudlines.at(line).m_vstyle.size())
		 it = m_vmudlines.at(line).m_vstyle.end()-1;
	/*if (m_wrap)
		sublines = l/m_wrap;
	else
		sublines=0;

	for (it = m_vmudlines.at(line).m_vstyle.begin(); it!=m_vmudlines.at(line).m_vstyle.end(); it++)
	{
		len += it->GetLen();
		if (sublines && len>m_wrap && p.y>m_vmudlines.at(line).GetYPos()+dc.GetCharHeight()*sublines)
		{
			len -= m_wrap*sublines;
		}
		if ((cxpos-stamp_offset) <= len)
			break;
	}*/
	if ((cxpos-stamp_offset)<=len)
	{
		/*if (it->GetFontStyle()==4 && it->GetURL())
		{
			wxLaunchDefaultBrowser(it->GetText());
			return;
 		}*/
		
		if (it->GetFontStyle()==4 && it->GetMXPSend())
		{
			wxMenu *contextMenu = new wxMenu;
			s_it sit;
			int i =0;
			if (!it->GetPromptSend())
			{
				for (sit=it->GetMXPLabel()->begin();sit!=it->GetMXPLabel()->end();sit++, i++)
					contextMenu->Append(ID_MXPMENU+i, *sit, *sit);
				m_mxpcommand.clear();
				m_mxpcommand = *it->GetMXPCommand();
			}
			else
			{
				for (sit=it->GetMXPLabel()->begin();sit!=it->GetMXPLabel()->end();sit++, i++)
					contextMenu->Append(ID_MXPMENUPROMPT+i, *sit, *sit);
				m_mxpcommand.clear();
				m_mxpcommand = *it->GetMXPCommand();
			}
			wxPoint p = event.GetPosition();
			//p = ScreenToClient(p);
			PopupMenu(contextMenu, p.x, p.y);
			delete contextMenu;
			return;
		/*	if (!it->GetMXPCommand()->empty())
				m_parent->m_input->Parse(it->GetMXPCommand()->at(0));
			return;*/
 		}
		else
		{
		wxMenu *contextMenu = new wxMenu;
		contextMenu->Append(ID_OUTFONT, _("Font"), _("Set the output font"));
		contextMenu->AppendCheckItem(ID_STAMPS, _("Timestamps"), _("Show timestamps in this window"));
		contextMenu->Check(ID_STAMPS, m_timestamps);
		if (m_selline!=-1)
		{
			contextMenu->AppendSeparator();
			contextMenu->Append(ID_MAKEACTION, _("Create action..."), _("Create an action using the linetext"));
		}
		wxPoint p = event.GetPosition();
		//p = ScreenToClient(p);
		PopupMenu(contextMenu, p.x, p.y);
		delete contextMenu;
		}
	}
	else
	{
		
	}
	
	/*if (!m_selected)
	{
		m_selstart = event.GetPosition();
		m_selected = true;
		m_selline = m_sellineend = CalcLine(m_selstart);
	}
	else
	{
		m_selected = false;
		m_selline = m_sellineend = -1;
	}*/
	Refresh();
	Update();
	event.Skip();
}

void MudWindow::OnMouseWheel(wxMouseEvent& event)
{

	#if defined __WXMSW__
	m_wheelrot += event.GetWheelRotation();
	int line = m_wheelrot/event.GetWheelDelta();
	m_wheelrot -= line*event.GetWheelDelta();
	
	if (line!=0)
	{
		wxScrollWinEvent newevt;
		newevt.SetPosition(0);
		newevt.SetOrientation(wxVERTICAL);
		newevt.SetEventObject(this);

		if (event.IsPageScroll())
        {
            if (line > 0)
                newevt.SetEventType(wxEVT_SCROLLWIN_PAGEUP);
            else
                newevt.SetEventType(wxEVT_SCROLLWIN_PAGEDOWN);
            this->GetEventHandler()->ProcessEvent(newevt);
        }
        else
        {
            line *= event.GetLinesPerAction();
            if (line > 0)
                newevt.SetEventType(wxEVT_SCROLLWIN_LINEUP);
            else
                newevt.SetEventType(wxEVT_SCROLLWIN_LINEDOWN);
            int i = abs(line);
            for ( ;i>0;i--)
                this->GetEventHandler()->ProcessEvent(newevt);

        }
	}
    #endif
	#if defined __WXGTK__
	if (m_parent->UseSplitter() && !m_parent->m_splitter->IsShown() && event.GetWheelRotation()>0)
	{
		m_parent->m_child->Freeze();
		m_parent->m_splitter->SetLineBuffer(m_parent->m_child->GetLines());
		m_parent->m_splitter->m_curline = m_parent->m_child->m_curline;
		m_parent->m_mgr.GetPane(wxT("amcsplitter")).Show();
		m_parent->m_mgr.Update();
		int line = m_parent->m_child->m_curline-m_parent->m_child->m_scrollrange;
		m_parent->m_splitter->SetScrollPage();
		m_parent->m_splitter->SetScrollPos(wxVERTICAL, line-m_parent->m_splitter->m_scrollrange);
		m_parent->m_splitter->Refresh();
		m_parent->m_splitter->Update();
		m_parent->m_child->Thaw();
	}
	#endif
	#if defined WXOSX
	if (m_parent->UseSplitter() && !m_parent->m_splitter->IsShown() && event.GetWheelRotation()>0)
	{
		m_parent->m_child->Freeze();
		m_parent->m_splitter->SetLineBuffer(m_parent->m_child->GetLines());
		m_parent->m_splitter->m_curline = m_parent->m_child->m_curline;
		m_parent->m_mgr.GetPane(wxT("amcsplitter")).Show();
		m_parent->m_mgr.Update();
		int line = m_parent->m_child->m_curline-m_parent->m_child->m_scrollrange;
		m_parent->m_splitter->SetScrollPage();
		m_parent->m_splitter->SetScrollPos(wxVERTICAL, line-m_parent->m_splitter->m_scrollrange);
		m_parent->m_splitter->Refresh();
		m_parent->m_splitter->Update();
		m_parent->m_child->Thaw();
	}
	#endif
    //Refresh();
    //Update();
	event.Skip();
}

void MudWindow::OnSocketEvent(wxSocketEvent& event)
{
char cBuf[64000];
//wxCharTypeBuffer<char> cBuf(64000);
wxString s, buffer;
wxUint32 uiBytesRead;
//  int scrollpos;
//  static bool first=true;

  switch(event.GetSocketEvent())
  {
    case wxSOCKET_INPUT:
		{
			
		if (m_mccp2)
			m_sock->Read(m_cBuffer, 4096);
		else m_sock->Read(m_cBuffer, 30000);
		uiBytesRead = m_sock->LastCount();
		//buffer.assign(cBuffer, uiBytesRead);
		//wxString ss = t.ToUTF8();
		
		m_cBuffer[uiBytesRead]=EOS;
		
		if (m_mccp2 && uiBytesRead && !m_oddmccp2)
		{
			int err=m_dc->Decompress(m_cBuffer, (size_t)uiBytesRead);
			if (err==-1)
			{
				SetMCCP2(false);
				m_dc->GetUCBuffer(cBuf);
				m_dc->EndDecompress();
				m_dc->Init();
				break;
			}
			//cBuf = new wxChar[m_dc->GetUCLen()+10];
			//cBuf=new wxChar[30000];
			m_dc->GetUCBuffer(cBuf);
		}
		if (m_parent->GetGlobalOptions()->DebugRaw())
		{
			if (m_mccp2 && cBuf!=NULL)
				WriteRaw(cBuf, m_dc->GetUCLen());
			else if (uiBytesRead!=0)
				WriteRaw(m_cBuffer, uiBytesRead);
		}
		//wxString test(cBuffer, uiBytesRead);
		//expose rawPacket to lua
		GetLState()->SetTop(0);
		if (m_mccp2 && cBuf!=NULL)
		{
			GetLState()->PushString((const char*)cBuf);
		}
		else if (uiBytesRead)
		{
			GetLState()->PushString((const char*)m_cBuffer);
		
		}
		GetLState()->SetGlobal((const char*)"amcPacket");
		GetLState()->SetTop(0);
		if (m_parent->GetGlobalOptions()->GetUseEvents())
		{
			if (m_parent->GetGlobalOptions()->GetUseEvRecv())
			{
				s = wxString::Format("%cfunc(\"%s\", \"OnPacketReceived()\")", m_parent->GetGlobalOptions()->GetCommand(),
					m_parent->GetGlobalOptions()->GetEventFile());
				m_parent->m_input->ParseCommandLine(&s);
				GetLState()->SetTop(0);
				GetLState()->GetGlobal("amcPacket");
				if (!m_parent->GetGlobalOptions()->UseUTF8())
				{
					if (m_mccp2 && cBuf!=NULL)
					{
						wxStrcpy(cBuf, GetLState()->GetString(-1));
					}
					else wxStrcpy(m_cBuffer, GetLState()->GetString(-1));
				}
				else
				{
					wxString sss = GetLState()->GetwxString(-1);
					if (m_mccp2 && cBuf!=NULL)
					{
						//wxStrcpy(cBuf, sss.char_str(wxCSConv(m_parent->GetGlobalOptions()->GetCurEncoding())));
						//if (cBuf[0]=='\0')
						wxStrcpy(cBuf, sss.char_str());
					}
					else if (uiBytesRead)
					{
						//wxStrcpy(m_cBuffer, sss.char_str(wxCSConv(m_parent->GetGlobalOptions()->GetCurEncoding())));
						//if (m_cBuffer[0]=='\0')
							wxStrcpy(m_cBuffer, sss.char_str());
					}
				}
			}
		}
		
		//Main loop to parse the stream arrived
		if (m_mccp2 && uiBytesRead && !m_oddmccp2)
		{
			if (m_parent->GetGlobalOptions()->UseUTF8())
			{
				if (!m_mxp)
					ParseNBuffer(cBuf, false);
				else ParseBufferMXP(cBuf);
			}
			else
			{
				if (m_mxp)
				{
					ParseBufferMXP(cBuf);
				}
				else
					ParseNBuffer(cBuf, false);
			}
		}
		else
		{
			if (m_parent->GetGlobalOptions()->UseUTF8())
			{
				//wxString f(cBuffer, uiBytesRead);
				//wxString f(m_cBuffer, wxCSConv(wxFONTENCODING_UTF8), uiBytesRead);
				if (!m_mxp)
					ParseNBuffer(m_cBuffer, false);
				else ParseBufferMXP(m_cBuffer);
				//ParseUTF8Buffer(f);
			}
			else
			{
				if (m_mxp)
				{
					ParseBufferMXP(m_cBuffer);
				}
				else
				{
					ParseNBuffer(m_cBuffer, false);
				}
			}
		}
		if (m_oddmccp2)
		{
			int err=m_dc->Decompress(&m_cBuffer[m_oddmccp2], uiBytesRead-m_oddmccp2);
			//cBuf = new wxChar[m_dc->GetUCLen()];
			m_dc->GetUCBuffer(cBuf);
			//ParseBuffer(cBuf);
			ParseNBuffer(cBuf);
		}
		
		if (!m_noscroll)
		{
			
			SetScrollPage();
			Refresh();
				//Update();
			
		}
		if (!m_parent->IsActive())
			m_parent->RequestUserAttention();
		if (m_atcp)
		{
			char test[] = {"\xff\xfa\xc8hello wxamcl 1.0.0\nroom_brief 1\nchar_vitals 1\n\xff\xf0\0"};
			//wxString s = "\xff\xfa\xc8hello wxamc 1.0.0\nauth 1\nroom_brief 1\nchar_vitals 1\nchar_name 1\xff\xf0";
			//s.Printf("%c%c%chello wxamc 1.0.0\nauth 1\nroom_brief 1\nchar_vitals 1\xff\xf0", IAC, SB, ATCP);
			s = wxString::From8BitData((const char*)test);
			//m_sock->Write(test, (wxUint32)53);
			Write8Bit(s);
			m_atcp = false;
		}
		if (m_atcp2)
		{
			char test[] = {"\x00ff\x00fa\xc9\x43ore.Hello {\"Client\": \"wxAmcl\", \"Version\": \"alpha\"}\xff\xf0\0"};
			//wxString s = "\xff\xfa\xc8hello wxamc 1.0.0\nauth 1\nroom_brief 1\nchar_vitals 1\nchar_name 1\xff\xf0";
			//s.Printf("%c%c%chello wxamc 1.0.0\nauth 1\nroom_brief 1\nchar_vitals 1\xff\xf0", IAC, SB, ATCP);
			s = wxString::From8BitData((const char*)test);
			//m_sock->Write(test, wxStrlen(test));
			Write8Bit(s);
			
			char gmcp[1500];
			gmcp[0]='\0';
			wxStrcat(gmcp, "\xff\xfa\xc9\x43ore.Supports.Set [\"");
			for (int i = 0; i<m_parent->GetGlobalOptions()->GetGMCPModules()->size();i++)
			{
				wxStrcat(gmcp, m_parent->GetGlobalOptions()->GetGMCPModules()->at(i));
				wxStrcat(gmcp, "\", \"");
			}
			gmcp[wxStrlen(gmcp)-3]='\0';
			wxStrcat(gmcp, "]\xff\xf0\0");
			 
			Write8Bit(wxString::From8BitData(gmcp));
			
			//m_sock->Write(gmcp, wxStrlen(gmcp));
			m_atcp2 = false;
			m_gmcp = true;
			gmcp[0]='\0';
			/*char test1[] = {"\xff\xfa\xc9\x43ore.Supports.Set [\"Core 1\", \"Char 1\", \"Char.Skills 1\", \"Room 1\", \"Char.Items 1\", \"Comm.Channel 1\"]\xff\xf0"};
			wxString ss = wxString::From8BitData((const char*)test1);
			m_sock->Write(test1, (wxUint32)ss.length());*/
				
		}
		if (m_focusoninput)
		{
			m_parent->m_input->SetFocus();
			m_parent->m_input->SetSelection(m_parent->m_input->GetLastPosition(),0);
			m_focusoninput=false;
			//m_parent->m_input->SetInsertionPointEnd();//(m_parent->m_input->GetLastPosition());
			
			//m_parent->m_input->SetSelection(0, m_parent->m_input->GetLastPosition()+1);
			//m_parent->m_input->SetSelection(0,m_parent->m_input->GetLastPosition()+1);
		}
		
		break;
	}
    case wxSOCKET_LOST:
		{
		wxString msg;
		wxDateTime end = wxDateTime::Now();
		if (m_connected)
		{
			wxTimeSpan diff = end.Subtract(GetConnectionDT());
			wxString form = diff.Format(_("%D days, %H hours, %M minutes and %S seconds."));
			
			msg << _("Your connection lasted: ") << form;
		}
		else
			msg = _("Connection failed!");
		Msg(msg);
	
		if (m_sock->Error())
			wxSocketError err=m_sock->LastError();
		//Msg(_("Connection lost!!"));
		m_sock->Close();
		if (m_mccp2)
		{
            m_mccp2=false;
            m_dc->EndDecompress();
			m_dc->Init();
		}
		if (m_parent->GetGlobalOptions()->GetUseEvents())
		{
			if (m_parent->GetGlobalOptions()->GetUseEvDisco())
			{
				s = wxString::Format("%cfunc(\"%s\", \"OnDisconnected()\")", m_parent->GetGlobalOptions()->GetCommand(),
					m_parent->GetGlobalOptions()->GetEventFile());
				m_parent->m_input->ParseCommandLine(&s);
			}
		}
		m_connected = false;
		m_parent->SetStatusText(_("Not Connected!"), 1);
		if (m_parent->GetGlobalOptions()->GetAutoConnect())
		{
			if (m_parent->GetCurHost()!=-1)
			{
				m_rc.SetOwner(this->GetEventHandler(),1111);
				m_rc.Start(m_parent->GetGlobalOptions()->GetACDelay()*1000);
				Msg(_("Auto reconnecting.."));
			}
		}

			/*AdjustScrollPage();
		scrollpos = m_curline - m_scrollrange;
		if (scrollpos<0)
			scrollpos=0;
		SetScrollbar(wxVERTICAL, scrollpos, m_scrollrange, m_curline);
		Refresh();
		Update();*/
		SetScrollPage();
		Refresh();
		Update();
		break;
		}
		break;
	
    case wxSOCKET_CONNECTION :
		if (m_rc.IsRunning())
			m_rc.Stop();
		//m_sock->SetFlags(wxSOCKET_NONE);
		//m_sock->SetFlags(wxSOCKET_WAITALL);
		SetConnectionDT();//remember time of connection;
		if (m_parent->GetGlobalOptions()->GetUseEvents())
		{
			if (m_parent->GetGlobalOptions()->GetUseEvConn())
			{
				s.empty();
				s = wxString::Format("%cfunc(\"%s\", \"OnConnected()\")", m_parent->GetGlobalOptions()->GetCommand(),
					m_parent->GetGlobalOptions()->GetEventFile());
				m_parent->m_input->ParseCommandLine(&s);
			}
		}
		m_sock->Read(m_cBuffer, 3000);
		uiBytesRead = m_sock->LastCount();
		m_cBuffer[uiBytesRead]=EOS;
		
		if (m_parent->GetGlobalOptions()->DebugRaw())
			WriteRaw(m_cBuffer, uiBytesRead);
		
		if (m_parent->GetGlobalOptions()->UseUTF8())
		{
			//m_parent->GetGlobalOptions()->SetUTF8(false);
			ParseNBuffer(m_cBuffer, false);
			//m_parent->GetGlobalOptions()->SetUTF8(true);
		}
		else
			ParseNBuffer(m_cBuffer);

		
		SetScrollPage();
		Refresh();
		Update();
		m_sock->SetFlags(wxSOCKET_NONE);
		m_connected = true;
		m_parent->m_input->SetFocus();
		break;
	default:
		break;
	}
	if (!m_vmudlines.empty())
		m_parent->SetStatusText(wxString::Format(_("Lines: %d"), m_vmudlines.at(m_curline-1).GetLinenumber()), 2);
	if (m_connected)
		m_parent->SetStatusText(_("Connected!"), 1);
}

void MudWindow::WriteRaw(char* buf, int len, bool inc)
{
	wxSetWorkingDirectory(m_parent->GetGlobalOptions()->GetLogDir());
	wxFile* file = new wxFile(RAW_FILE, wxFile::write_append);
	wxString t, tt;
	wxDateTime d, dt;
	//d.SetToCurrent();
	d = wxDateTime::Now();
	dt = wxDateTime::UNow();
	wxString date;
	date = wxString::Format("%02d:%02d:%02d:%03d", d.GetHour(), d.GetMinute(), d.GetSecond(), dt.GetMillisecond());
	if (inc)
		file->Write(t<<_("incoming packet: ")<< len <<_(" bytes (")<<date<<(")\n"));
	else
		file->Write(t<<_("sent packet: ")<<len<<_(" bytes (")<<date<<(")\n"));

	for (int i=0;i<len;i+=32)
	{
		for (int ii=0;ii<32;ii++)
		{
			if (i+ii>=len)
			{
				file->Write(" ", 1);
				continue;
			}
		if (buf[i+ii]=='\r' || buf[i+ii]=='\n' || buf[i+ii]==ESC)
			file->Write(".", 1);
		else
			file->Write(wxString(buf[i+ii]), 1);
		}
		file->Write("\t", 1);
		for (int ii=0;ii<32;ii++)
		{
			if (i+ii>=len)
				break;
			t = wxString::Format(" %02X", buf[i+ii]);
			tt.Empty();
			if (t.length()>3)
				tt <<" "<<t.substr(7,2);
			else tt = t;
			file->Write(tt, tt.length());
		}
		file->Write("\n", 1);
		}
	file->Write("\n", 1);
	file->Close();
	delete file;
}

wxString MudWindow::FindPrevAnsi(wxString ansi, int idx)
{
	wxString sub = ansi.substr(0, idx);
	int x = sub.rfind("\x1b[");
	if (x==(int)string::npos)
		return "\x1b[0m";
	else
	{
		
		int xx = sub.find('m', x);
		return ("\x1b[0m" + sub.substr(x, xx-x+1));
	}
	return wxEmptyString;
}

wxString MudWindow::GetSelectedText()
{
	wxString s;
	if ((long)m_selline==-1)
		return wxEmptyString;
	for (long i=m_selline;i<=m_sellineend;i++)
		//s.Append(m_vmudlines.at(i).GetAnsiLine());
		s<<m_vmudlines.at(i).GetLineText()<<"\r\n";
	return s;
}

wxString MudWindow::GetSelectedAnsiText()
{
	wxString s;
	if ((long)m_selline==-1)
		return wxEmptyString;
	for (long i=m_selline;i<=m_sellineend;i++)
	{
		wxString ansi = m_vmudlines.at(i).GetAnsiLine();
		wxString sub;
		if (!ansi.empty())
		{
			sub = wxEmptyString;
			if (ansi.at(ansi.length()-1)=='\0')
				sub = ansi.Left(ansi.length()-1);
			else sub = ansi;
		//s.Append(m_vmudlines.at(i).GetAnsiLine(), m_vmudlines.at(i).GetAnsiLine().length());
		}
		s<<sub<<"\r\n";
		
		//s<<m_vmudlines.at(i).GetAnsiLine()<<"\r\n";
	}
	return s;
}