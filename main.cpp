
#include "main.h"

// IDs for the controls and the menu commands
enum
{
    // menu items
    Amcl_Connect = ID_CONNECT,
	Amcl_Disconnect = ID_DISCONNECT,
	Amcl_LoadProf = ID_LOADPROF,
    Amcl_Quit = wxID_EXIT,
    Amcl_About = wxID_ABOUT,
	Amcl_Preferences = ID_PREFS,
	Amcl_Objects = ID_OBJS,
	Amcl_Charconnect = ID_CHARCONNECT,
	Amcl_SavePerspective = ID_SAVEP,
	Amcl_InstallPackage = ID_INSTALL,
	Amcl_UninstallPackage = ID_UNINSTALL,
	Amcl_CreatePackage = ID_CREATEPKG,
	Amcl_EditScript = ID_EDITSCRIPT,
	Amcl_CopyClipboard = ID_COPY,
	Amcl_Find = wxID_FIND,
	Amcl_CreateWindow = ID_CREATEWINDOW,
	Amcl_CreateGaugeWin = ID_CREATEGAUGEWIN,
	Amcl_CreateNotebookWin = ID_CREATENOTEBOOKWINDOW,
	Amcl_CreateToolBar = ID_CREATETOOLBAR,
	Amcl_ToggleTriggers = ID_TOGGLEACTIONS
};
//wxDEFINE_EVENT(wxEVENT_CMD_PAUSE2, wxThreadEvent);
//wxDEFINE_EVENT(wxEVENT_CMD_RESUME2, wxThreadEvent);
BEGIN_EVENT_TABLE(MudMainFrame, wxFrame)
	EVT_MENU(Amcl_Connect, MudMainFrame::OnSimpleConnect)
	EVT_MENU(Amcl_Quit,  MudMainFrame::OnQuit)
    EVT_MENU(Amcl_About, MudMainFrame::OnAbout)
	EVT_MENU(Amcl_Preferences, MudMainFrame::OnPrefs)
	EVT_MENU(Amcl_Objects, MudMainFrame::OnObjects)
	EVT_MENU(Amcl_Charconnect, MudMainFrame::OnCharConnect)
	EVT_MENU(Amcl_Disconnect, MudMainFrame::OnDisconnect)
	EVT_MENU(Amcl_LoadProf, MudMainFrame::OnLoadProfile)
	EVT_MENU(Amcl_SavePerspective, MudMainFrame::OnSavePerspective)
	EVT_MENU(Amcl_InstallPackage, MudMainFrame::OnInstallPackage)
	EVT_MENU(Amcl_UninstallPackage, MudMainFrame::OnUninstallPackage)
	EVT_MENU(Amcl_CreatePackage, MudMainFrame::OnCreatePackage)
	EVT_MENU(Amcl_EditScript, MudMainFrame::OnEditScript)
	EVT_MENU(Amcl_ToggleTriggers, MudMainFrame::OnToggleAllTriggers)
	EVT_MENU(Amcl_CreateWindow, MudMainFrame::OnCreateCapture)
	EVT_MENU(Amcl_CreateNotebookWin, MudMainFrame::OnCreateNb)
	EVT_MENU(Amcl_CreateToolBar, MudMainFrame::OnCreateTB)
	EVT_MENU(Amcl_CreateGaugeWin, MudMainFrame::OnCreateGaugeWindow)
	EVT_MENU(/*Amcl_CopyClipboard*/wxID_COPY, MudMainFrame::OnCopyClipboard)
	EVT_MENU(Amcl_CopyClipboard, MudMainFrame::OnAnsiCopyClipboard)
	EVT_MENU(ID_SPLITTER, MudMainFrame::OnShowSplitter)
	EVT_MENU(Amcl_Find, MudMainFrame::OnFind)
	EVT_FIND(wxID_ANY, MudMainFrame::OnFindDialog)
    EVT_FIND_NEXT(wxID_ANY, MudMainFrame::OnFindDialog)
    //EVT_FIND_REPLACE(wxID_ANY, MudMainFrame::OnFindDialog)
    //EVT_FIND_REPLACE_ALL(wxID_ANY, MudMainFrame::OnFindDialog)
    EVT_FIND_CLOSE(wxID_ANY, MudMainFrame::OnFindDialog)
	EVT_MENU_RANGE(ID_USERWINDOW, ID_USERWINDOW+300, MudMainFrame::OnUserWindow)
	EVT_MENU_RANGE(ID_AMCUSERWINDOW, ID_AMCUSERWINDOW + 300, MudMainFrame::OnAmcUserWindow)
	EVT_MENU_RANGE(ID_USERBUTTON, ID_USERBUTTON+1000, MudMainFrame::OnUserButton)
	EVT_MENU_RANGE(ID_CHARENCODING, ID_CHARENCODING+20, MudMainFrame::OnCharEncoding)
	EVT_MENU_RANGE(wxID_FILE1, wxID_FILE1+9, MudMainFrame::OnFileHistory)
	EVT_UPDATE_UI(wxID_COPY/*Amcl_CopyClipboard*/, MudMainFrame::OnMenuUi)
	EVT_UPDATE_UI(Amcl_CopyClipboard, MudMainFrame::OnMenuUi)
	EVT_ERASE_BACKGROUND(MudMainFrame::OnEraseBackground)
    EVT_PAINT(MudMainFrame::OnPaint)
	EVT_BUTTON(ID_PARSEINPUT, MudMainFrame::OnParseInput)
	//EVT_COMMAND(wxID_ANY, wxEVENT_CMD_PAUSE, MudMainFrame::OnScriptPause)
	//EVT_COMMAND(wxID_ANY, wxEVENT_CMD_RESUME, MudMainFrame::OnScriptResume)
	//EVT_THREAD(wxEVENT_CMD_PAUSE2, MudMainFrame::OnScriptPause)
	//EVT_IDLE(MudMainFrame::OnIdle)
	EVT_MEDIA_LOADED(ID_MEDIACTRL, MudMainFrame::OnMediaLoaded)
	EVT_MEDIA_FINISHED(ID_MEDIACTRL, MudMainFrame::OnMediaFinished)
	//EVT_AUINOTEBOOK_PAGE_CHANGED(ID_NOTEBOOK, MudMainFrame::OnNPageChanged)
END_EVENT_TABLE()

//DEFINE_EVENT_TYPE(wxEVENT_CMD_PAUSE)
//DEFINE_EVENT_TYPE(wxEVENT_CMD_RESUME)

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MudClientApp)


BEGIN_EVENT_TABLE(InputTextCtrl, wxTextCtrl)
	EVT_TEXT_ENTER(ID_INPUTCTRL, InputTextCtrl::OnTextEnter)
	EVT_TEXT(ID_INPUTCTRL, InputTextCtrl::OnText)
	EVT_CHAR(InputTextCtrl::OnChar)
	EVT_KEY_DOWN(InputTextCtrl::OnKeyDown)
	EVT_MOUSEWHEEL(InputTextCtrl::OnMouseWheel)
	EVT_LEFT_UP(InputTextCtrl::OnMouseLeftUp)
	EVT_LEFT_DCLICK(InputTextCtrl::OnMouseLeftDClick)
	EVT_SET_FOCUS(InputTextCtrl::OnSetFocus)
	EVT_TIMER(2222, InputTextCtrl::OnSWDelay)
	EVT_IDLE(InputTextCtrl::OnIdle)
END_EVENT_TABLE()
#include "mud11.xpm"
#include "defs.xpm"
#include "prefs.xpm"
#include "net.xpm"
#include "action.xpm"
#include "root.xpm"
#include "script.xpm"

static const wxCmdLineEntryDesc g_cmddesc[] = 
{
	{wxCMD_LINE_PARAM, NULL, NULL, "profile file", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL},
	{wxCMD_LINE_NONE}
};
// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MudClientApp::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
   
	wxInitAllImageHandlers();
    // create the main application window
    MudMainFrame *frame = new MudMainFrame("wxAmcl");
	SetFrame(frame);
    
	//Output window
	frame->m_child = new MudWindow(frame);
	SetChild(frame->m_child);
    
	frame->m_actwindow = frame->m_scriptwin = frame->m_child;
	frame->CreateDefVars();
	
	
    //Input line
	frame->m_input = new InputTextCtrl(frame, ID_INPUTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_TAB|wxTE_LEFT|wxTE_MULTILINE|wxTE_RICH2|wxTE_NOHIDESEL);
	//Bitmap Button
	frame->m_toggle = new wxBitmapButton(frame, ID_PARSEINPUT, wxArtProvider::GetBitmap(wxART_TICK_MARK, wxART_BUTTON));
	//frame->m_toggle = new wxCheckBox(frame, ID_PARSEINPUT,_(""));
	//toolbar
	
	frame->m_toolbar = new wxAuiToolBar(frame, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                   wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_GRIPPER);
	frame->m_toolbar->SetToolBitmapSize(wxSize(24,24));
	frame->m_toolbar->AddTool(ID_CHARCONNECT, _("Connect"), wxBitmap(net_xpm), _("Connect char..."));
	frame->m_toolbar->AddSeparator();
	frame->m_toolbar->AddTool(ID_OBJS, _("Objects"), wxBitmap(defs_xpm), _("Define objects..."));
	frame->m_toolbar->AddTool(ID_PREFS, _("Preferences"), wxBitmap(prefs_xpm), _("Global preferences"));
	frame->m_toolbar->AddSeparator();
	frame->m_toolbar->AddTool(Amcl_EditScript, _("Edit Scripts"), wxBitmap(script_xpm), _("Edit script"));
	
	frame->m_toolbar->Realize();
	//prompt lock window
	
	frame->m_prompt = new wxTextCtrl(frame, ID_PROMPT, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_CENTRE);
	//Splitter Window...hidden
	frame->m_splitter = new MudWindow(frame);
	
	frame->m_media = new wxMediaCtrl();
	frame->m_notebook = nullptr; //need this only when multiple connections
#if defined __WXMSW__
	bool bOK = frame->m_media->Create(frame, ID_MEDIACTRL, "", wxDefaultPosition, wxSize(200, 200), 0 , wxMEDIABACKEND_WMP10);
	wxASSERT_MSG(bOK, ("Could not create media control!"));
#endif
#if defined __WXGTK__
	bool bOK = frame->m_media->Create(frame, ID_MEDIACTRL, wxEmptyString, wxDefaultPosition, wxSize(200,200), 0, wxMEDIABACKEND_GSTREAMER);
    wxASSERT_MSG(bOK, ("Could not create media control!"));
    wxUnusedVar(bOK);
#endif
#if defined __WXOSX__
	frame->m_media->Create(frame, ID_MEDIACTRL, "", wxDefaultPosition, wxSize(200,200), 0);
#endif
    frame->Maximize();
    frame->Show(true);
    frame->Refresh();
    frame->Update();
    
	frame->m_mgr.AddPane(frame->m_input, wxAuiPaneInfo().Name("amcinput").Bottom().Floatable(true).Gripper().CaptionVisible(false).BestSize(500,24).Position(0));
	frame->m_mgr.AddPane(frame->m_splitter, wxAuiPaneInfo().Name("amcsplitter").Top().Dockable(false).CaptionVisible(false).BestSize(100, 300).Hide());//.Hide());
	frame->m_mgr.AddPane(frame->m_child, wxAuiPaneInfo().Name("amcmain").Center().CenterPane().Dockable(false).Floatable(false));
	frame->m_mgr.AddPane(frame->m_toggle, wxAuiPaneInfo().Name(("amctoggle")).Bottom().Floatable(false).CaptionVisible(false).MaxSize(48,24).Fixed().Position(1));
	frame->m_mgr.AddPane(frame->m_prompt, wxAuiPaneInfo().Name(("amcprompt")).Bottom().CaptionVisible(false).Hide());
	wxSize s = frame->GetClientSize();
	frame->m_mgr.AddPane(frame->m_toolbar, wxAuiPaneInfo().Name("amctoolbar").ToolbarPane().Caption(_("Main Toolbar")).CaptionVisible(false).Top().LeftDockable(true).RightDockable(true));
	frame->m_mgr.AddPane(frame->m_media, wxAuiPaneInfo().Name("amcmedia").Floatable(true).Dockable(true).Caption(_("Media")).CaptionVisible(true).Right().BestSize(200,200).Hide());
	frame->m_mgr.SetManagedWindow(frame);
	frame->m_mgr.SetDockSizeConstraint(0.5, 0.5);
	unsigned int flags;// = m_mgr.GetFlags();
	flags = wxAUI_MGR_RECTANGLE_HINT|wxAUI_MGR_ALLOW_FLOATING|wxAUI_MGR_HINT_FADE|wxAUI_MGR_NO_VENETIAN_BLINDS_FADE;
    frame->m_mgr.SetFlags(flags);
    frame->m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_BACKGROUND_COLOUR, frame->m_actwindow->GetAnsiColor(0));

	
	frame->m_notebook = new wxAuiNotebook(frame, wxID_ANY, wxDefaultPosition, s, wxAUI_NB_TOP |  wxAUI_NB_SCROLL_BUTTONS | wxAUI_NB_CLOSE_ON_ACTIVE_TAB | wxAUI_NB_MIDDLE_CLICK_CLOSE | wxAUI_NB_WINDOWLIST_BUTTON);
	frame->m_notebook->SetBackgroundColour(frame->m_child->GetAnsiColor(0));
	frame->m_notebook->SetArtProvider(new wxAuiSimpleTabArt());
	frame->m_notebook->Connect(wxEVT_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler(MudMainFrame::OnNPageChanged), NULL, frame);
	frame->m_notebook->Connect(wxEVT_AUINOTEBOOK_PAGE_CLOSE, wxAuiNotebookEventHandler(MudMainFrame::OnNPageClose), NULL, frame);
	frame->m_notebook->Connect(wxEVT_AUINOTEBOOK_PAGE_CLOSED, wxAuiNotebookEventHandler(MudMainFrame::OnNPageClosed), NULL, frame);
	frame->m_mgr.AddPane(frame->m_notebook, wxAuiPaneInfo().Name("amcmultinb").Center().Dockable(false).Floatable(false).Hide().BestSize(1000, 1000));

    frame->m_mgr.Update();
	
    frame->LoadGlobalOptions();
	amcLua *aL = frame->m_child->GetLState();
	wxSetWorkingDirectory(frame->GetGlobalOptions()->GetWorkDir());
	wxSetWorkingDirectory(frame->GetGlobalOptions()->GetScriptDir());
	aL->DoFile(frame->GetGlobalOptions()->GetEventFile());
		
	
#if defined __WXMSW__
	wxSetEnv("LUA_PATH_5_3", "!\\scripts\\?.lua;!\\lua\\?.lua");
#endif
#if defined __WXGTK__
	wxSetEnv("LUA_PATH_5_3", ".\\scripts\\?.lua;.\\lua\\?.lua");
#endif
#if defined __WXOSX__
	wxSetEnv("LUA_PATH_5_3", ".\\scripts\\?.lua;.\\lua\\?.lua");
#endif

	if (frame->m_input->GetParse())
			frame->m_toggle->SetBitmapLabel(wxArtProvider::GetBitmap(wxART_TICK_MARK, wxART_BUTTON));
		else
			frame->m_toggle->SetBitmapLabel(wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_BUTTON));
	frame->LoadHosts();
	frame->m_child->Msg(_("Welcome to wxAmcl!"));
	
    wxString os = wxGetOsDescription();
    wxString version = wxVERSION_STRING;
	frame->m_child->Msg(wxString::Format(_("Cross platform mudclient using %s on %s."), version, os));
	frame->luaBuildtrigger();
	frame->luaBuildalias();
	frame->luaBuilddefvar();
	
	frame->m_input->SetFocus();
	
	//wxFileName ff("defaultprofile.lua");
	//frame->LoadProfile(ff);
	wxCmdLineParser p(g_cmddesc, wxGetApp().argc, wxGetApp().argv);
	p.Parse(false);
	int i = p.GetParamCount();
	if (i>0)
	{
		wxString file = p.GetParam(0);
		wxFileName f(file);
		frame->LoadProfile(f);
	}
	
	
	//wxString s("\u0419\u0634");
		
	////wxString s="You drop a set of protective arm sleeves.\n\r<\x1b[1;32m2239/2435Hp \x1b[1;33m1003/2642Ma \x1b[1;36m1938/1938Mv \x1b[1;37m609Xp \x1b[1;35m0qt\x1b[0;37m>: \x1b[0;37m\x1b";
	//wxString ss="[0;36mAyla gives you \x1b[1;33m24\x1b[0;36m gold coins for a set of protective arm sleeves.\x1b[0;37m";
	//wxString s ="\x1b[33mSo Sheni barters:\x1b[0;37mhttp://frostblade.net/aardwolf/claneq/display.php?sort=level    Bookmark this page, it is the EQ bible ^^";
	//wxString s = "\x1b[0;36;44m:\x1b[0;0m\x1b[0;37m \x1b[1;34m\x1b[1;36m()\x1b[1;34m Up in the sky\x1b[0;37m  via \x1b[1;36m(StdOpenDoorway)\x1b[0;37m \x1b[0;0m";
	//wxString s="\xff\xfa\x45\x01variable\x02test\xff\xf0";

	//wxString s = "北大侠客行已经执行了[1; 33m三小时五十一分三秒";


	//std::u32string input = U"řabcdě";
	/*wxString ss(u8"          â•”â•â•â•â•â•â•â•â•â•â•â•â•—");
	std::wstring_convert<std::codecvt_utf8<unsigned int>, unsigned int> converter;

	for (unsigned int c : ss)
	{
		//std::cout << converter.to_bytes(c) << std::endl;
		frame->m_child->Msg(converter.to_bytes(c));
	}*/

	//wxString ss("<\x1b[0;31m5322/5322Hps \x1b[1;32m5494/5509Ma \x1b[0;32m3219/3223Mvs \x1b[0;36m0qt\x1b[0;37m> comm.tick {} ");
	//wxString ss = "{ \"name\": \"Asariom\", \"class\": \"Mage\", \"subclass\": \"Elementalist\", \"race\": \"Eldar\", \"clan\": \"\", \"pretitle\": \"\", \"perlevel\": 2000, \"tier\": 0, \"remorts\": 2, \"redos\" : \"0\" }  <\x1b[0;31m933/933Hps \x1b[1;32m1028/1054Ma \x1b[0;32m1111/1112Mvs \x1b[0;36m0qt \x1b[0;35m1815tnl \x1b[1;33m\x1b[0;37m> \x1b[0;37m";
	//frame->m_child->ParseNBuffer((char*)ss.mb_str().data(), false);
	//wxString ss = "\x1b[0;33m           ---  \n";
	//wxString ss = "https://pastebin.com";
	//frame->m_child->ParseNBuffer(ss.char_str(), false);
	/*ss = "\x1b[0;33m          \x1b[0;33m|   \x1b[0;33m\x1b[0;33m|  \n";
	frame->m_child->ParseNBuffer(ss.char_str(), false);
	ss = "\x1b[0;33m          \x1b[0;33m|\x1b[1;37m#\x1b[1;35m#\x1b[1;37m>\x1b[0;33m\x1b[0;33m|  \n";
	frame->m_child->ParseNBuffer(ss.char_str(), false);
	ss = "\x1b[0;33m           ---  \n";
	frame->m_child->ParseNBuffer(ss.char_str(), false);*/
	//s.clear();
	//wxString ss = "\x1b[1m\x1b[37mconnect <username> <password>\x1b[0m";
	//frame->m_child->ParseNBuffer(ss.char_str());
	//wxString s = wxVERSION_STRING;
	//frame->m_child->Msg(wxString::Format(wxT("%s on %s"), s.c_str(), wxGetOsDescription().c_str()));
	//wxString s = "ïðõèô";
	//frame->m_child->Msg(s);
	//Test for triggers
	/*class Trigger tr("Golmeas the Ninja", "#capturewin(\"Score2\", \"21\")", "info", "testclass",54);
	class Trigger tr1("Golmeas the Ninja", "#capturewin(\"Score1\", \"21\")", "info2", "xxx", 70);
	class Trigger tr2("^Password:", "asasir#", "test22", "testclass", 44);
	frame->m_trigger.push_back(tr);
	frame->m_trigger.push_back(tr1);
	frame->m_trigger.push_back(tr2);*/
	//frame->m_child->Msg(frame->GetGlobalOptions()->GetWorkDir());
	//frame->m_child->ParseNBuffer("                       Посетите наш сайт: www.mud.ru");
	//frame -> m_child->ParseNBuffer("http://youtu.be/6LqXTEl56Eg", false);
	//frame->m_child->ParseNBuffer("http://bit.ly", false);
	//frame->m_child->ParseNBuffer("\x1b[44;1m¡Ë¡Ë\x1b[37;0m¡¡ Ëü¸øÎÒ»¶ÀÖ£¬¶øÔÚÓÚËü¸øÁËÎÒ¿Õ¼ä£¬¾¡¹ÜÕâ¿Õ¼äÊÇÐéÄâµÄ£¬   \x1b[44;1m¡Ë¡Ë\x1b[37;0m\n\r\x1b[44;1m¡Ë¡Ë\x1b[37;0m¡¡ µ«¸ÐÇéÊÇÕæÊµµÄ£¬ÕâÇ¡Ç¡ÓëÏÖÊµÊÀ½çÏà·´¡ª¡ªÆñ²»¹ÖÔÕ£¿       \x1b[44;1m¡Ë¡Ë\x1b[37;0m\n\r\x1b[44;1m¡Ë¡Ë\x1b[37;0m                                                       \x1b[44;1m¡Ë¡Ë\x1b[37;0m");
	//frame->m_child->ParseNBuffer("mAsa");
	//frame->m_child->SetMSP(true);
	//frame->m_child->ParseNBuffer("<RExits>\x1b[32mYou see exits leading <COLOR #00FF00><SEND HREF=\"north\">north</SEND></COLOR> (open door) and <COLOR #00FF00><SEND HREF=\"down\">down</SEND></COLOR> (closed door).</RExits>");
	//amcMXP am(frame->m_child);
	//wxString s = "\xff\xfa\xc9char.vitals{ \"hp\" : 394, \"mana\" : 457, \"moves\" : 709	 }\xff\xf0<\x1b[0; 31m394 / 394Hps \x1b[1; 32m457 / 457Ma \x1b[0; 32m709 / 711Mvs \x1b[0; 36m1qt\x1b[0; 37m> \x1b[0; 37m";
	//wxString s = "> \x1b[0;37m";
	//frame->m_child->ParseNBuffer(s.char_str().data());
	//am.Parse("<IMAGE 'intro.jpg' URL='http://coffeemud.net:27744/images/mxp/' H=400 W=400>  Hallo");
	//am.Parse("<!ELEMENT HELP '<SEND HREF=\"HELP &text;\" hint=\"Click\">'>");
	//am.Parse("<HELP>ALIAS</HELP> <HELP>!</HELP>");
	//am.Parse("By what name shall we know thee?\xff\xfa\x5b\xff\xf0\xff\xfa\xc9\xff\xf0");
	//am.Parse("\x1b[1z<send \"look leather satchel\" hint=\"Click to see menu|look|eat|wear|remove|drop\">a \x1b[1;30mleather\x1b[0m satchel</Send>");
	//am.Parse("\x1b[1z<!ELEMENT RName '<FONT \"Comic Sans MS\" COLOR=CYAN> <B>' FLAG=\"RoomName\"><!ELEMENT RDesc FLAG='RoomDesc'><!ELEMENT RExits FLAG='RoomExit'><!ELEMENT Ex '<SEND>'><!ELEMENT List \"<send href='buy &#39;&name;&#39;' hint='Buy &desc;'>\" ATT='name desc'>\x1b[1z<SUPPORT image send frame state>");
	//am.Parse("<send prompt hint='text' href='?mapper.walk|?mapper.talk'>Test me!</send>\n");
	//am.Parse("Wer <color #a0a0a0><send>\r\nTest1ddddddddddddddddddddddd</send></color><color #c0c0c0><send>Test2ddddddddddddddddddddddddddd</send></color><color #a0a0a0><send>Test1111111111111111111111111111111111111</send></color><color #c0c0c0><send>Test22222222222222222222222222222222222222222222222222222222222222</send></color><color #a0a0a0><send>Test1234ffffffffffffffffff</send></color><color #c0c0c0><send>Test2</send></color><color #a0a0a0><send>est1</send></color><color #c0c0c0><send>Test2</send></color><color #a0a0a0><send>Test1</send></color><color #c0c0c0><send>Test2</send></color><color #a0a0a0><send>Test1</send></color><color #c0c0c0><send>Test2</send></color><color #a0a0a0><send>Test1</send></color><color #c0c0c0><send>Test2</send></color><color #a0a0a0><send>Test1</send></color><color #c0c0c0><send>Test2</send></color><color #a0a0a0><send>Test1</send></color><color #c0c0c0><send>Test2</send></color><color #a0a0a0><send>Test1</send></color><color #c0c0c0><send>Test2</send></color><color #a0a0a0><send>st1</send></color><color #c0c0c0><send>Test2</send></color>");
	//am.Parse("0;32mC\x1b[0;34mo\x1b[1;32ml\x1b[0;36mo\x1b[1;36mu\x1b[1;31mr\x1b[1;33m \x1b[1;30mi\x1b[0;37ms \x1b[1;33mn\x1b[1;31mo\x1b[0;35mw \x1b[1;35mO\x1b[1;30mN\x1b[1;31m!\x1b[0;37m\r\n\x1b[1;34m-=====");
	//am.Parse("\x1b[4z\x1b[1;33m416h, \x1b[0;37m\x1b[32m540m \x1b[37mex-\x1b[4z\xff\xfe With a squeak, an old rat darts into the room, looking about wildly.\x1b[4z<PROMPT>\1xb[1;33m416h, \x1b[0;37m\x1b[32m540m \x1b[37mex-\x1b[4z</PROMPT>\xff\xfe");
	//am.Parse("</Rexits>\x1b[1;37m<IMAGE>");
	//am.Parse("<!ELEMENT exit '<send>'>");
	//am.Parse("<exit>north</exit>");
	//am.Parse("Ausgaenge: \x1b[1z<exit exitdir='!Osten' exithint='... Die Huette durch den Ausgang verlassen|... Die Huette durch den Ausgang verlassen (!Osten)'>\x1b[7zOsten\x1b[1z</exit>.");
	//am.Parse("\x1b[1;");
	//am.Parse("30m<send h");
	//am.Parse("ref=\"hedit IMOTD\">edit</send>\x1b[1;32m[92 - <send href=\"hlist imotd.txt\">imotd.txt</send>]");
	//am.Parse("\x1b[4z<RExits>\x1b[1;32mYou see exits leading\x1b[0;37m\x1b[1;32m \x1b[4z<COLOR #00FF00>\x1b[4z<SEND HREF=\"north\">north\x1b[4z</SEND>\x1b[4z</COLOR>, \x1b[4z<COLOR #00FF00>\x1b[4z<SEND HREF=\"northeast\">northeast\x1b[4z</SEND>\x1b[4z</COLOR> (open door), \x1b[0;37m\x1b[4z</RExits>");

	
	//am.Parse("Eine We<!ELEMENT HP FLAG=\"Set Var\">");
	//am.Parse("<P>Desc\nHulu</P>\x1b[1mAchso\n");
	//am.Parse("\x1b[33mSyntax\r\naha <help>test</help> und so weiter <help>was</help>\r\n");
	//am.Parse("\r\n\r\n\r\n\x1b[0m\x1b[H\x1b[J\r\nDer Adlige sagt: Herzlich Willkommen in Avalon, Asarean!\r\nBitte jetzt ein beliebiges \x1b[1mPasswort\x1b[0m eingeben.\r\nPasswort: \xff");
	//am.Parse("You have <!EN hp 5");
	//am.Parse("00 publish>500 (<!EN maxhp 500 publish>500) hit points, <!EN gp 50 publish>50 (<!EN maxgp 50 publish>50) guild points, 0 (684) quest points, 1 (1088) achievement point and <!EN sp 50 publish>50 (<!EN maxsp 50 publish>50) social points.<BR>Your current experience is <!EN xp 19182 publish>19182 and you are level 0 in the Adventurers' Guild; your overall rating is 64.<BR>You have died 0 times and can die 7 times before you are completely dead.<BR>Your wimpy is set to 20%.<BR>You are unburdened (5%) and quite comfortable.<BR>You are neutral, worshipping no god.<BR>You are 4 hours, 30 minutes and 58 seconds old and have logged in 29 times.<BR>> <!EN hp 500 publish><!EN xp 19182 publish><!EN gp 50 publish><!EN maxhp 500 publish><!EN maxgp 50 publish>");
	//am.Parse("\x1b[4z<VERSION>\x1b[4z<SUPPORT>\x1b[4z<!ELEMENT RNum ATT=\"id\" FLAG=\"RoomNum\" EMPTY>\x1b[4z<!ELEMENT RName FLAG=\"RoomName\">\x1b[4z<!EN hp 500><!ELEMENT RDesc FLAG=\"RoomDesc\">\x1b[4z<!ELEMENT RExits FLAG=\"RoomExit\">\x1b[4z<!ELEMENT Prompt FLAG=\"Prompt\">\x1b[34m*------------------(\x1b[37m\x1b[1;37m Announcements from the Administration \x1b[0;37m\x1b[34m)------------------*\r\n\x1b[37m\x1b[1;37m-&gt; Spend 10 minutes logged in any day in March and gain a credit, simple as<RNum 531> ");
   	//am.Parse("<!EL livingpopup '<send href=\"look &ob;|nod &ob;\" hint=\"Test\">'>\n");
	//am.Parse("<Cyan><!EN ob \"Cony\" private><livingpopup>Cony</livingpopup> says: Welcome to the Disc! This is a really friendly place where you can meet and talk to all kinds of folk.<BR><Cyan><!EN ob \"Cony\" private><livingpopup>Cony</livingpopup> says: You probably know about using tells to talk to people, but I particularly like the talker. A talker is an item that gives you channels to chat on.<BR><Cyan><!EN ob \"Cony\" private><livingpopup>Cony</livingpopup> says: It's the best way to talk to lots of people at once. See, everyone with the same channel turned on can hear you.<BR><Cyan><!EN ob \"Cony\" private><livingpopup>Cony</livingpopup> says: There are several types of channels; some that all can listen to, some which can only be accessed by joining a guild, and others that need to be earned in special ways.<BR><Cyan><!EN ob \"Cony\" private><livingpopup>Cony</livingpopup> says: You can also join player created clubs. Doing so will give you access to custom channels, although those are slightly different to those found on the talker.<BR><Cyan><!EN ob \"Cony\" private><livingpopup>Cony</livingpopup> says: Once you leave Pumpkin Town, you will get a voucher that you can exchange for a talker. You can't get a talker here in Pumpkin Town.<BR><Cyan><!EN ob \"Cony\" private><livingpopup>Cony</livingpopup> looks sad for a moment, then brightens.<BR><Cyan><!EN ob \"Cony\" private><livingpopup>Cony</livingpopup> says: But while you're under 18 hours old, you can still use the newbie channel. That's a very special channel you get without having a talker, and is useful for getting help and advice.<BR>");
	//am.Parse("<!E");
	//am.Parse("N xp 234567>");
	
	//am.Parse("\x1b[30m\x1b[1z<c back=blue>word1\x1b[31mword2</font>\n");
	//am.Parse("g <COLOR fore=#ddaa44 back=coral><send>north</send></COLOR><COLOR #ff00ff> Test <send>south</send></COLOR>");
	//am.Parse("rth</SEND></COLOR>, <COLOR #00FF00><SEND HREF=\"northeast\">northeast</SEND></COLOR> (open door), <COLOR #00FF00><SEND HREF=\"east\">east</SEND></COLOR>, <COLOR #00FF00><SEND HREF=\"southeast\">southeast</SEND></COLOR> (open door), <COLOR #00FF00><SEND HREF=\"south\">south</SEND></COLOR> (open door), <COLOR #00FF00><SEND HREF=\"southwest\">southwest</SEND></COLOR>, <COLOR #00FF00><SEND HREF=\"west\">west</SEND></COLOR>, <COLOR #00FF00><SEND HREF=\"northwest\">northwest</SEND></COLOR>, and <COLOR #00FF00><SEND HREF=\"in\">in</SEND></COLOR> (open door).</RExits>");
	//am.Parse("<BR><Cyan>Cony says: Hey There!\x1b[3z<BR><Cyan><send>Cony</send> says test<BR><Cyan>Cony says what\n");
	//am.Parse("This is Cony, the Icon of Cool.  He lounges around, hands in pockets, looking as though the world molded itself to him rather than the other way around.  Occasionally he lifts his wrist to his mouth to talk into a bracelet, and then listens to the stream of sound emitted by it.<BR>He is in good shape.<BR>He is sitting on a bench.<BR><Yellow>Wearing :</Yellow> a <send href=\"look pair of black soft-soled boots in Cony|get pair of black soft-soled boots in Cony|drag pair of black soft-soled boots in Cony |consider pair of black soft-soled boots in Cony|wear pair of black soft-soled boots in Cony|remove pair of black soft-soled boots in Cony|open pair of black soft-soled boots in Cony|close pair of black soft-soled boots in Cony\" hint=\"Right-click to see a menu|look pair of black soft-soled boots in Cony|get pair of black soft-soled boots in Cony|drag pair of black soft-soled boots in Cony |consider pair of black soft-soled boots in Cony|wear pair of black soft-soled boots in Cony|remove pair of black soft-soled boots in Cony|open pair of black soft-soled boots in Cony|close pair of black soft-soled boots in Cony\">pair of black soft-soled boots</send>, a <send href=\"look pair of baggy trousers in Cony|get pair of baggy trousers in Cony|drag pair of baggy trousers in Cony |consider pair of baggy trousers in Cony|wear pair of baggy trousers in Cony|remove pair of baggy trousers in Cony|open pair of baggy trousers in Cony|close pair of baggy trousers in Cony\" hint=\"Right-click to see a menu|look pair of baggy trousers in Cony|get pair of baggy trousers in Cony|drag pair of baggy trousers in Cony |consider pair of baggy trousers in Cony|wear pair of baggy trousers in Cony|remove pair of baggy trousers in Cony|open pair of baggy trousers in Cony|close pair of baggy trousers in Cony\">pair of baggy trousers</send>, a <send href=\"look chequered sports jacket in Cony|get chequered sports jacket in Cony|drag chequered sports jacket in Cony |consider chequered sports jacket in Cony|wear chequered sports jacket in Cony|remove chequered sports jacket in Cony|open chequered sports jacket in Cony|close chequered sports jacket in Cony\" hint=\"Right-click to see a menu|look chequered sports jacket in Cony|get chequered sports jacket in Cony|drag chequered sports jacket in Cony |consider chequered sports jacket in Cony|wear chequered sports jacket in Cony|remove chequered sports jacket in Cony|open chequered sports jacket in Cony|close chequered sports jacket in Cony\">chequered sports jacket</send>, a <send href=\"look wooden bracelet in Cony|get wooden bracelet in Cony|drag wooden bracelet in Cony |consider wooden bracelet in Cony|wear wooden bracelet in Cony|remove wooden bracelet in Cony\" hint=\"Right-click to see a menu|look wooden bracelet in Cony|get wooden bracelet in Cony|drag wooden bracelet in Cony |consider wooden bracelet in Cony|wear wooden bracelet in Cony|remove wooden bracelet in Cony\">wooden bracelet</send> and a <send href=\"look pair of dark shades in Cony|get pair of dark shades in Cony|drag pair of dark shades in Cony |consider pair of dark shades in Cony|wear pair of dark shades in Cony|remove pair of dark shades in Cony\" hint=\"Right-click to see a menu|look pair of dark shades in Cony|get pair of dark shades in Cony|drag pair of dark shades in Cony |consider pair of dark shades in Cony|wear pair of dark shades in Cony|remove pair of dark shades in Cony\">pair of dark shades</send>.<BR>> <!EN hp 500 publish><!EN xp 9121 publish><!EN gp 50 publish><!EN maxhp 500 publish><!EN maxgp 50 publish>");
	//am.Parse("<Cyan>Cony says: Welcome to the Disc! This is a really friendly place where you can meet and talk to all kinds of folk.\x1b[3z<BR>");
	//<!EN ob \"Cony\" private>
	
	//am.Parse("<send href=\"look sash|read sash\" hint=\"menu|look sash|eat sash\">sash</send><BR><Green>Carrying: a <send href=\"look small bucket|drop small bucket|weigh small bucket|give small bucket to |read small bucket|condition small bucket|hold small bucket|unhold small bucket|open small bucket|close small bucket\" hint=\"Right-click to see a menu|look small bucket|drop small bucket|weigh small bucket|give small bucket to |read small bucket|condition small bucket|hold small bucket|unhold small bucket|open small bucket|close small bucket\">small bucket</send>");
	//am.Parse("<send>look\r\nat me</send>");
	//am.Parse("<!EN ob \"Bob\">");
	//am.Parse("<RExits>You see exits leading <COLOR #00FF00><SEND HREF=\"north\">north</SEND></COLOR>, <COLOR #00FF00><SEND HREF=\"northeast\">northeast</SEND></COLOR>, and <COLOR #00FF00><SEND HREF=\"south\">south</SEND></COLOR>.</RExits>");

	//am.Parse("<send href=\"look &ob;|consider &ob;\" PROMPT hint=\"Hint|Look &ob;|Con &ob;\">Bob</send>");
	//am.Parse("<!EL invobjectpopup '<send href=\"look &ob;|drop &ob;|weigh &ob;|give &ob; to |read &ob;|condition &ob;|custum1 &ob;\" PROMPT hint=\"Right click for menu|look &ob;|drop &ob;|weigh &ob;|give &ob; to |read &ob;|condition &ob;|custom1 &ob;\">'>");
	//am.Parse("<!EN ob \"bench\" private><invobjectpopup>A bench</invobjectpopup> sits here.");
	//am.Parse("<!EL Col1 '<FONT COLOR brown darkblue>'>");
	//am.Parse("look at me<BR><Red>Your purse</Red> only contains moths!<BR>>");
	//am.Parse("<Ex>nord</Ex>");
	//am.Parse("<RNum 555><Rdesc>Hallo</Rdesc>");
	//am.Parse("<EX1 up \"up \" nam>&name;</EX1>");
	//am.Parse("<RName>LargePlaza</RName>");
	//am.Parse("<!ELEMENT help '<send href=\"help & text; \">'>");
	//am.Parse("<help>start_newbie</help>");
	//am.Parse("<!ELEMENT RExits FLAG='RoomExit'><!EL Ex '<SEND href=\"go\">'>");
	//am.Parse("<RExits>[Exits: <Ex>north</Ex> <Ex>south</Ex> <Ex>west</Ex>]</RExits> ");//<Ex>east</Ex> <Ex>west</Ex>]</RExits>\x1b[1;34m\x1b[0;37m  ");
	//am.Parse("\x1b[0;31m<RName>East-West Road</RName>\x1b[0;37m [\x1b[1;34mTaker's Place\x1b[0;37m]\r\n<RDesc>You are on a dirty road that leads east to west.  You can see several houses \r\non this road.  To the south is a large pantry.  There are some oil lamps \r\nhanging on top of wooden poles.</RDesc>  \r\n<RExits>[Exits: <Ex>north</Ex> <Ex>east</Ex> <Ex>west</Ex>]</RExits>\x1b[1;34m\x1b[0;37m  ");
	//am.ParseElementRex("<!ELEMENT buy-uid ATT=\'uid=0\' \'<send href=\"buy #&uid;\"      hint=\"Buy &text;\">'><!ELEMENT rdesc FLAG=\"Room\"><!EL buy '<send>buy bread</send>'>");
    //class Trigger tr("Trigger Test", "#capstart(\"Test\", \"true\")", "test", "testclass");
	//frame->m_trigger.push_back(tr);
	// success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
	//amcHotkey hk(AMC_C, wxMOD_CONTROL, wxT("Ctrl + C"), wxT("#connect(\"aardmud.com\", \"4000\")"));
	//frame->m_hotkeys.push_back(hk);
	//amcVar vv(wxT("hps"), wxT("0"));
	//frame->m_vars.push_back(vv);
	/*vector<wxString> ve;
	ve.push_back(wxT("Blur"));
	ve.push_back(wxT("Stone Skin"));
	amcList ll(wxT("test"), ve);
	frame->m_lists.push_back(ll);
	wxString s = frame->m_lists.at(0).GetItem(1);*/
	/*amcTimer t(wxT("test"), wxT("?amc.echo(\"Timer on duty\")"), wxT("test"), 5.5, 3);
	frame->m_timers.push_back(t);
	frame->GetTimers()->at(0).SetActive(true);
	frame->GetTimers()->at(0).Run();*/
	//amcAlias al("\u0419\u0634", "test");
	//frame->m_alias.push_back(al);
	//wxString s = frame->m_child->FindPrevAnsi(wxT("\x1b[34mHallo\x1b[0;33;40mTest und Text"), 10);
	
	//wxSetWorkingDirectory(wxGetApp().GetFrame()->GetGlobalOptions()->GetScriptDir());
	//luaL_dofile(frame->m_child->GetLState()->GetLuaState(), "mapper.lua");
	//frame->m_child->SetIPV6(true);
	
	return true;
}



int MudClientApp::OnExit()
{
	//delete splitter;
return 0;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------
// frame constructor
MudMainFrame::MudMainFrame(const wxString& title)
       :wxFrame()//: wxFrame(NULL, wxID_ANY, title)
{
	
#if defined __WXGTK__
    //SetBackgroundStyle(wxBG_STYLE_SYSTEM);
    //ClearBackground();
#endif
#ifndef __WXGTK__
	SetBackgroundStyle(wxBG_STYLE_PAINT);
#endif
    Create(NULL, wxID_ANY, title);
    //Create(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxCLIP_CHILDREN|wxFULL_REPAINT_ON_RESIZE);
#if defined __WXOSX__
	#include "mud11.xpm"
	wxIcon icon = wxICON(net);
	SetIcon(icon);
#endif
#ifndef __WXOSX__
	SetIcon(wxICON(aamud11));
#endif

	/*m_mgr.SetManagedWindow(this);
	m_mgr.SetDockSizeConstraint(0.5, 0.5);
	unsigned int flags;// = m_mgr.GetFlags();
	flags = wxAUI_MGR_RECTANGLE_HINT|wxAUI_MGR_ALLOW_FLOATING|wxAUI_MGR_HINT_FADE|wxAUI_MGR_NO_VENETIAN_BLINDS_FADE;
    m_mgr.SetFlags(flags);*/

	#if defined __WXGTK__
	wxLocale::AddCatalogLookupPathPrefix("/usr/share/locale");
	#endif
	#if defined __WXMSW__
	wxLocale::AddCatalogLookupPathPrefix(".");
	#endif
	#if defined __WXOSX__
	wxLocale::AddCatalogLookupPathPrefix(wxStandardPaths::Get().GetResourcesDir());
	#endif
	m_locale = new wxLocale(wxLANGUAGE_GERMAN);
	//wxDateTime::SetCountry(wxDateTime::USA);
	
	if (!m_locale->IsOk())
	{
		delete m_locale;
		m_locale = new wxLocale(wxLANGUAGE_ENGLISH);
	}
	m_locale->AddCatalog("wxamcl");
	m_usesplitter = true;
	m_curhost = -1;
	m_gopt = new GlobalOptions(this);
	m_triggerson = true;
	m_curprofile = "defaultprofile.lua";
	m_refcount = 0;
	m_scrverbose = true;
	m_find = NULL;
	m_active_window = 0;
	m_actwindow = NULL;
	m_scriptwin = NULL;
#if wxUSE_MENUS
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;
	wxMenu *copyMenu = new wxMenu;
	wxMenu *viewMenu = new wxMenu;
	wxMenu *extraMenu = new wxMenu;
	// the "About" item should be in the help menu
	wxMenuItem *copy = new wxMenuItem(copyMenu, wxID_COPY, _("Copy\tCtrl+C"), _("Copy selection to clipboard"));
	copy->SetBitmap(wxArtProvider::GetBitmap(wxART_COPY));
	copyMenu->Append(copy);
	copyMenu->Append(Amcl_CopyClipboard, _("Copy with ansi"), _("Copy selection with ansicodes to clipboard"));
	copyMenu->AppendSeparator();
	wxMenuItem *find = new wxMenuItem(copyMenu, wxID_FIND, _("Search"), _("Search buffer"));
	find->SetBitmap(wxArtProvider::GetBitmap(wxART_FIND));
	copyMenu->Append(find);
	//copyMenu->Append(/*Amcl_CopyClipboard*/wxID_COPY);
	wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Amcl_About, _("&About...\tF1"), _("Show about dialog"));
	//helpMenu->Append(wxID_ABOUT);
	wxMenuItem *conn = new wxMenuItem(fileMenu, Amcl_Charconnect, _("Connect char...\tAlt+A"), _("Connect a char to a mud"));
	conn->SetBitmap(net_xpm);
	
	fileMenu->Append(conn);
	//fileMenu->Append(Amcl_Charconnect, _("Connect char..."), _("Connect a char to a mud"),);
    fileMenu->Append(Amcl_Connect, _("&Connect\tAlt+C"), _("Connect to a host"));
	fileMenu->AppendSeparator();
	
	fileMenu->Append(Amcl_Disconnect, _("&Disconnect"), _("Disconnect from the mud"));
	fileMenu->AppendSeparator();
	fileMenu->Append(Amcl_LoadProf, _("Load profile"), _("Load a profile file offline"));
	fileMenu->AppendSeparator();
	fileMenu->Append(Amcl_Quit, _("E&nd\tAlt+X"), _("Terminate program"));

	//extraMenu->Append(Amcl_Objects, _("Define objects..."), _("Define actions, aliases, etc."));
	wxMenuItem *ob = new wxMenuItem(extraMenu, Amcl_Objects, _("Define objects..."), _("Define actions, aliases, etc."));
	ob->SetBitmap(defs_xpm);
	extraMenu->Append(ob);
	extraMenu->Append(Amcl_ToggleTriggers, _("Disable all actions"), _("Enable/Disable trigger parsing"));
	extraMenu->AppendSeparator();
	wxMenu *subMenu = new wxMenu;
	subMenu->Append(Amcl_CreateWindow, _("Create capture window"), _("Create a window for text capturing"));
	subMenu->Append(Amcl_CreateNotebookWin, _("Create a notebook window"), _("Create a window with notebook tabs in it"));
	subMenu->Append(Amcl_CreateGaugeWin, _("Create gauge window"), _("Create a window to display gauges"));
	subMenu->Append(Amcl_CreateToolBar, _("Create toolbar"), _("Create a user toolbar"));
	extraMenu->AppendSubMenu(subMenu, _("Create user window"), _("Create a user window"));
	extraMenu->AppendSeparator();
	extraMenu->Append(Amcl_EditScript, _("Edit Scripts..."), _("Open script editor"));
	extraMenu->AppendSeparator();
	extraMenu->Append(Amcl_CreatePackage, _("Create Package..."), _("Create package file"));
	extraMenu->Append(Amcl_InstallPackage, _("Install Package"), _("Install a profile package"));
	extraMenu->Append(Amcl_UninstallPackage, _("Uninstall Package"), _("Remove a profile package"));
	extraMenu->AppendSeparator();
	extraMenu->Append(Amcl_SavePerspective, _("&Save Layout"), _("Save the window layout"));
	extraMenu->AppendSeparator();
	wxMenuItem *prefs = new wxMenuItem(extraMenu, Amcl_Preferences, _("&Preferences"), _("Global preferences for the client"));
	prefs->SetBitmap(prefs_xpm);
	extraMenu->Append(prefs);

	viewMenu->AppendCheckItem(ID_SPLITTER, _("Split window\tF2"), _("Show the splitter window"));
	
	BuildEncodingMenu(viewMenu);
	
	// now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _("&File"));
	menuBar->Append(copyMenu, _("&Edit"));
	menuBar->Append(viewMenu, _("View"));
	menuBar->Append(extraMenu, _("&Extras"));
    menuBar->Append(helpMenu, _("&Help"));
    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
	m_filehist = new wxFileHistory(5);
	m_filehist->UseMenu(fileMenu);
#endif // wxUSE_MENUS
#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(3);
    SetStatusText(_("Welcome to wxAmcl!"));
    Center();
#endif 
	SetName("wxAMC");

	
	
	DefineKeys();
#if defined __WXMSW__
	wxFont ff(wxFontInfo(9).FaceName("Consolas"));
	m_scriptfont = new wxFont(ff);
	//m_scriptfont = new wxFont(9, wxMODERN, wxNORMAL, wxNORMAL, false, "Consolas");
	wxFont bf(wxFontInfo(9).FaceName("Consolas").Bold().Family(wxFONTFAMILY_MODERN));
#endif
#if defined __WXGTK__
	//m_scriptfont = new wxFont(9, wxMODERN, wxNORMAL, wxNORMAL, "Monospace Regular");
    wxFont ff(wxFontInfo(9).FaceName("Monospace Regular"));
    m_scriptfont = new wxFont(ff);
	//wxFont bf (9, wxMODERN, wxNORMAL, wxFONTWEIGHT_BOLD, false, "Monospace Regular");
    wxFont bf(wxFontInfo(9).FaceName("Monospace Regular").Bold().Family(wxFONTFAMILY_MODERN));
#endif
#if defined __WXOSX__
    wxFont ff(wxFontInfo(9).FaceName("Courier New"));
	m_scriptfont = new wxFont(ff);
	wxFont bf (wxFontInfo(9).FaceName("Courier New").Family(wxFONTFAMILY_MODERN).Bold());
#endif

}

MudMainFrame::MudMainFrame()
       : wxFrame(NULL, wxID_ANY, "")
{
	
}

MudMainFrame::~MudMainFrame()
{
	
	int i = m_childwindows.size();
	for (int ii = 0; ii < i; ii++)
	{
		m_actwindow = m_childwindows.at(ii);
		SaveProfile(m_childwindows.at(ii)->GetProfile());
	}
	if (!i)
		SaveProfile(m_actwindow->GetProfile());
	m_mgr.UnInit();
	if (!m_notebook)
		m_child->Destroy();
	if (m_notebook!=nullptr)
		m_notebook->Destroy();
	m_splitter->Destroy();
	m_prompt->Destroy();
	delete m_locale;
	delete m_gopt;
	delete m_filehist;
	delete m_scriptfont;
	m_media->Destroy();
	if (m_find)
		delete m_find;
 // No delayed deletion here, as the frame is dying anyway
}

// event handlers
void MudMainFrame::OnEraseBackground(wxEraseEvent& event)
{
	//wxLogDebug("OnEraseFrame");
    event.Skip();
}

void MudMainFrame::OnPaint(wxPaintEvent& event)
{
    /*wxSize ss=GetClientSize();
	wxBitmap bm(ss.x, ss.y);
    wxBufferedPaintDC dc(this, bm);
	//wxAutoBufferedPaintDC dc(this);
	//wxBufferedPaintDC dc (this);
	//wxPaintDC dc(this);
	dc.SetBackgroundMode(wxPENSTYLE_SOLID);
	wxBrush b(m_child->GetAnsiColor(0));
	dc.SetBackground(b);
	dc.Clear();*/
    //wxLogDebug("OnPaintFrame");
    m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_BACKGROUND_COLOUR, m_child->GetAnsiColor(0));
}

void MudMainFrame::OnIdle(wxIdleEvent& event)
{
	
	/*wxDialog *dlg = (wxDialog*)wxDialog::FindWindowByName(wxT("amcScriptedit"));
	if (dlg)
		return;	
	m_input->SetFocus();*/
	/*	wxCaret* c = m_input->GetCaret();
		if (!c)
			return;
		if (!c->IsOk())
			return;
		c->Show();*/
        event.Skip();
}

void MudMainFrame::OnCharConnect(wxCommandEvent& event)
{
	
	dlg_charconn *cc = new dlg_charconn(this);
	if (cc->ShowModal() == wxID_OK)
	{
		if (m_child->IsConnected()) //Should we open another world?
		{
			m_active_window++;
			
			if (m_active_window == 1 && m_notebook->GetSelection()==-1)
			{
				m_mgr.GetPane(m_notebook).Show().CenterPane();
				m_mgr.DetachPane(m_child);

				m_child->Reparent(m_notebook);
				m_childwindows.push_back(m_child);
			}
			MudWindow *nmw = new MudWindow(this);
			nmw->SetNFont(m_actwindow->GetFont());
			nmw->SetUFont(m_actwindow->GetFont());
			nmw->SetIFont(m_actwindow->GetFont());
			nmw->Reparent(m_notebook);
			m_childwindows.push_back(nmw);
			m_actwindow = m_scriptwin = nmw;
			
			int oldhost = m_curhost;
			m_curhost = cc->GetLastSelection();
			
			nmw->SetProfile(GetHosts()->at(m_curhost).GetProfileFName().GetFullPath());
			if (m_active_window==1 && m_notebook->GetSelection() == -1)
				m_notebook->AddPage(m_child, GetHosts()->at(oldhost).GetMudName(), false);
			m_notebook->AddPage(nmw, GetHosts()->at(m_curhost).GetMudName(), true);
			
			m_mgr.GetPane(m_notebook).Show();
			m_mgr.Update();

		}
		m_curhost = cc->GetLastSelection();
		if (m_curhost==-1)
		{
			m_actwindow->Msg(_("No profile selected!"));
			return;
		}
		if (!m_actwindow->IsConnected()&&!m_childwindows.size()==1)
		{
			LoadProfile(GetHosts()->at(m_curhost).GetProfileFName());
			
		}
		
		GetHosts()->at(m_curhost).SetIPHost();
		SaveHosts();
		if (!m_actwindow->GetUseIPV6())
			m_actwindow->MyConnect(GetHosts()->at(m_curhost).GetIP4());
#ifdef WXAMCL_USEIPV6
		else
			m_actwindow->MyConnect6(GetHosts()->at(m_curhost).GetIP6());
#endif
		int idx = m_actwindow->GetDefVarIndexByLabel("wxamclChar");
		m_actwindow->GetDefVars()->at(idx).SetValue(GetHosts()->at(m_curhost).GetCharName());
		idx = m_actwindow->GetDefVarIndexByLabel("wxamclIP");
		if (!m_actwindow->GetUseIPV6())
			m_actwindow->GetDefVars()->at(idx).SetValue(GetHosts()->at(m_curhost).GetIPAddress());
#ifdef WXAMCL_USEIPV6
		else
			m_actwindow->GetDefVars()->at(idx).SetValue(GetHosts()->at(m_curhost).GetIP6Address());
			//m_actwindow->GetDefVars()->at(idx).SetValue("::");
#endif
		luaBuilddefvar();
	}
	cc->Destroy();
	
	//m_mgr.GetPane("amcinput").Float();
	
	
}

void MudMainFrame::OnSimpleConnect(wxCommandEvent& WXUNUSED(event))
{
//wxDialog sd;
//wxString ip, ports;
long iPort;
wxIPV4address addr;
#if defined WXAMCL_USEIPV6
wxIPV6address addr6;
#endif
	
	dlg_hostsimple *sd = new dlg_hostsimple(this);
	s_it it;
	for (it=m_lasthost.begin();it!=m_lasthost.end();it++)
		sd->m_server->AppendString(*it);
	vector<int>::iterator iit;
	for (iit=m_lastport.begin();iit!=m_lastport.end();iit++)
		sd->m_port->AppendString(wxString::Format("%d", *iit));
	if (sd->ShowModal()==wxID_OK)
	{
			
			sd->Validate();
			sd->TransferDataFromWindow();
			//addr.Hostname(*sd->m_ip);
			if (m_child->IsConnected()) //Should we open another world?
			{
				m_active_window++;

				if (m_active_window == 1 && m_notebook->GetSelection() == -1)
				{
					m_mgr.GetPane(m_notebook).Show().CenterPane();
					m_mgr.DetachPane(m_child);

					m_child->Reparent(m_notebook);
					m_childwindows.push_back(m_child);
				}
				MudWindow* nmw = new MudWindow(this);
				nmw->SetNFont(m_actwindow->GetFont());
				nmw->SetUFont(m_actwindow->GetFont());
				nmw->SetIFont(m_actwindow->GetFont());
				nmw->Reparent(m_notebook);
				m_childwindows.push_back(nmw);
				m_actwindow = m_scriptwin = nmw;
				if (m_active_window == 1 && m_notebook->GetSelection() == -1)
					m_notebook->AddPage(m_child, _("Welt 1"), false);
				m_notebook->AddPage(nmw, sd->m_server->GetValue(), true);

				m_mgr.GetPane(m_notebook).Show();
				m_mgr.Update();
			}
			
			if (!m_actwindow->GetUseIPV6())
				addr.Hostname(sd->m_server->GetValue());
            #if defined WXAMCL_USEIPV6
			else
				addr6.Hostname(sd->m_server->GetValue());
            #endif
			wxString p = sd->m_port->GetValue();
			p.ToLong(&iPort);
			if (!m_child->GetUseIPV6())
			{
				addr.Service(iPort);
				if (!m_actwindow->GetSock()->IsConnected())
					m_actwindow->MyConnect(addr);
				else
				{
					return;
				}
					
			}
			else
			{
				#if defined WXAMCL_USEIPV6
                addr6.Service(iPort);
				m_actwindow->MyConnect6(addr6);
                #endif
			}
			int i = count(m_lasthost.begin(), m_lasthost.end(), sd->m_server->GetValue());
			if (!i)
				m_lasthost.push_back(sd->m_server->GetValue());
			long l;
			sd->m_port->GetValue().ToLong(&l);
			i = count(m_lastport.begin(), m_lastport.end(), l);
			if (!i)
				m_lastport.push_back(l);
		}
	
	
	int idx = m_actwindow->GetDefVarIndexByLabel("wxamclIP");
	if (!m_actwindow->GetUseIPV6())
		m_actwindow->GetDefVars()->at(idx).SetValue(addr.IPAddress());
	#ifdef WXAMCL_USEIPV6
	else
		m_actwindow->GetDefVars()->at(idx).SetValue(addr6.IPAddress());
	//m_actwindow->GetDefVars()->at(idx).SetValue("::");
	#endif
	luaBuilddefvar();

	sd->Destroy();
}

void MudMainFrame::OnDisconnect(wxCommandEvent& event)
{
	m_actwindow->Close();
}

void MudMainFrame::OnLoadProfile(wxCommandEvent& event)
{
	wxString dir = GetGlobalOptions()->GetProfileDir();
	wxSetWorkingDirectory(dir);
	wxString file = wxFileSelector(_("Choose profile to load"), dir, wxEmptyString, "lua", "lua files (*.lua)|*.lua|all files (*.*)|*.*", wxFD_OPEN, this);
	if (!file.empty())
	{
		LoadProfile(file);
		m_filehist->AddFileToHistory(file);
		
	}

}

void MudMainFrame::OnFileHistory(wxCommandEvent& event)
{
	int id = event.GetId();
	wxString file = m_filehist->GetHistoryFile(id-wxID_FILE1);
	//wxString dir = GetGlobalOptions()->GetProfileDir();
	//wxSetWorkingDirectory(dir);
	LoadProfile(wxFileName(file));
}

void MudMainFrame::OnCopyClipboard(wxCommandEvent& event)
{
	
	if (m_child->IsTextSelected())
    {
        wxString text = m_child->GetSelectedText();
        if (wxTheClipboard->Open())
        {
            wxTheClipboard->SetData( new wxTextDataObject(text));
            wxTheClipboard->Close();
        }
    }
    else if (m_splitter->IsTextSelected())
    {
        wxString text = m_splitter->GetSelectedText();
        if (wxTheClipboard->Open())
        {
            wxTheClipboard->SetData( new wxTextDataObject(text));
            wxTheClipboard->Close();
        }
    }
}

void MudMainFrame::OnAnsiCopyClipboard(wxCommandEvent& event)
{
	wxString text = m_child->GetSelectedAnsiText();
	if (wxTheClipboard->Open())
	{
		wxTheClipboard->SetData( new wxTextDataObject(text));
        wxTheClipboard->Close();
	}
}

void MudMainFrame::OnFind(wxCommandEvent& event)
{
	if (m_find)
	{
		delete m_find;
		m_find=NULL;
	}
	m_find = new wxFindReplaceDialog(this, &m_finddata, _("Search"), 0);
	m_find->Show();
	
}

void MudMainFrame::OnFindDialog(wxFindDialogEvent& event)
{
static int line = m_child->m_curline-1;
static bool bodown = false;

    wxEventType type = event.GetEventType();

    if ( type == wxEVT_COMMAND_FIND || type == wxEVT_COMMAND_FIND_NEXT )
    {
		wxString find = event.GetFindString();
		int flags = event.GetFlags();
		bool down = flags & wxFR_DOWN;
		if (bodown!=down)
		{
			if (down)
				line = 0;
			else line = m_child->m_curline-1;
			bodown = down;
		}
		//aufwärts suchen
		if (!down)
		{
			for (int i= line;i>=0;i--)
			{
				if (m_child->GetLines()->at(i).GetLineText().Find(find)!=wxNOT_FOUND)
				{
					m_child->SetSelectedStart(i);
					m_child->SetSelectedEnd(i);
					m_child->SetScrollbar(wxVERTICAL, i, m_child->m_scrollrange, m_child->m_curline);
					line = i-1;
					m_child->Refresh();
					m_child->Update();
					break;
				}
			}
		}
		else
		{
			for (wxUint64 i= line;i<m_child->m_curline;i++)
			{
				if (m_child->GetLines()->at(i).GetLineText().Find(find)!=wxNOT_FOUND)
				{
					m_child->SetSelectedStart(i);
					m_child->SetSelectedEnd(i);
					m_child->SetScrollbar(wxVERTICAL, i, m_child->m_scrollrange, m_child->m_curline);
					line = i-1;
					m_child->Refresh();
					m_child->Update();
					break;
				}
			}
		}
    }
    else if ( type == wxEVT_COMMAND_FIND_REPLACE ||
                type == wxEVT_COMMAND_FIND_REPLACE_ALL )
    {
    }
    else if ( type == wxEVT_COMMAND_FIND_CLOSE )
    {
		line = m_child->m_curline-1;
		m_find->Hide();
		/*if (m_find)
			delete m_find;
		m_find=NULL;*/
    }
}

void MudMainFrame::OnShowSplitter(wxCommandEvent& event)
{

        wxWindowUpdateLocker noUpdates(this);

		if (UseSplitter() && !m_splitter->IsShown())
		{
			m_actwindow->Freeze();
            m_splitter->Freeze();
			m_splitter->SetLineBuffer(m_actwindow->GetLines());
			m_splitter->m_curline = m_actwindow->m_curline;
			
			int line = m_actwindow->m_curline-m_child->m_scrollrange;
			m_splitter->SetScrollPage();
			m_splitter->SetScrollPos(wxVERTICAL, line-m_splitter->m_scrollrange);
            m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_BACKGROUND_COLOUR, m_actwindow->GetAnsiColor(0));
            
            m_mgr.GetPane("amcsplitter").Dock().Show().Row(0);
            m_mgr.GetPane("amcmain").Show().Row(1);
            m_mgr.Update();
            m_actwindow->Thaw();
            m_splitter->Thaw();
			return;
		}
		if (m_splitter->IsShown())
		{
			m_actwindow->Freeze();
            
			m_mgr.GetPane("amcsplitter").Hide();
            m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_BACKGROUND_COLOUR, m_actwindow->GetAnsiColor(0));
            //m_mgr.GetPane("amcmain").Show();
            m_mgr.Update();
            m_actwindow->Thaw();
			return;
		}
    	
	return;
}

void MudMainFrame::OnUserWindow(wxCommandEvent& event)
{

	if (event.IsChecked())
	{
		m_actwindow->Freeze();
		wxMenuBar* bar = GetMenuBar();
		wxMenuItem* item = bar->FindItem(event.GetId());
		wxString name = item->GetItemLabelText();
		m_mgr.GetPane(name).Show();
		m_mgr.Update();
		m_actwindow->Thaw();
		return;
	}
	else
	{
		m_actwindow->Freeze();
		wxMenuBar* bar = GetMenuBar();
		wxMenuItem* item = bar->FindItem(event.GetId());
		wxString name = item->GetItemLabelText();
		m_mgr.GetPane(name).Hide();
		
		m_mgr.Update();
		m_actwindow->Thaw();
		return;
	}
	//sendto->SetKEvtForwarded(true);
	//sendto->GetEventHandler()->ProcessEvent(newevt);
	return;
}

void MudMainFrame::OnAmcUserWindow(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		m_actwindow->Freeze();
		wxMenuBar* bar = GetMenuBar();
		wxMenuItem* item = bar->FindItem(event.GetId());
		wxString name = item->GetItemLabelText();
		m_mgr.GetPane(name).Show();
		m_mgr.Update();
		m_actwindow->Thaw();
		return;
	}
	else
	{
		m_actwindow->Freeze();
		wxMenuBar* bar = GetMenuBar();
		wxMenuItem* item = bar->FindItem(event.GetId());
		wxString name = item->GetItemLabelText();
		m_mgr.GetPane(name).Hide();

		m_mgr.Update();
		m_actwindow->Thaw();
		return;
	}
	
	return;
}

void MudMainFrame::OnUserButton(wxCommandEvent& event)
{
	int id = event.GetId();
	int idx = GetButtonIndexById(id);
	if (idx==-1)
		return;
	if (GetButtons()->at(idx).IsActive())
		m_input->Parse(GetButtons()->at(idx).GetAction());
	return;
}

void MudMainFrame::OnCharEncoding(wxCommandEvent& event)
{
	wxFontEncoding ec;
	int id = event.GetId();
	wxMenuBar* bar = GetMenuBar();
	wxMenuItem* item;
	for (int i=ID_CHARENCODING;i<ID_CHARENCODING+17;i++)
	{
		item = bar->FindItem(i);
		item->Check(false);
	}
	item = bar->FindItem(id);
	item->Check();
	switch(id)
	{
	case ID_CHARENCODING:
		ec = wxFONTENCODING_SYSTEM;
		break;
	case ID_CHARENCODING+1:
		ec = wxFONTENCODING_UTF8;
		break;
	case ID_CHARENCODING+2:
		ec = wxFONTENCODING_ISO8859_1;
		break;
	case ID_CHARENCODING+3:
		ec = wxFONTENCODING_ISO8859_15;
		break;
	case ID_CHARENCODING + 4:
		ec = wxFONTENCODING_ISO8859_2;
		break;
	case ID_CHARENCODING+5:
		ec = wxFONTENCODING_ISO8859_7;
		break;
	case ID_CHARENCODING+6:
		ec = wxFONTENCODING_CP1253;
		break;
	case ID_CHARENCODING+7:
		ec = wxFONTENCODING_KOI8;
		break;
	case ID_CHARENCODING+8:
		ec = wxFONTENCODING_KOI8_U;
		break;
	case ID_CHARENCODING+9:
		ec = wxFONTENCODING_ISO8859_5;
		break;
	case ID_CHARENCODING+10:
		ec = wxFONTENCODING_CP1251;
		break;
	case ID_CHARENCODING+11:
		ec = wxFONTENCODING_BIG5;
		break;
	case ID_CHARENCODING+12:
		ec = wxFONTENCODING_CP936;
		break;
	case ID_CHARENCODING+13:
		ec = wxFONTENCODING_SHIFT_JIS;
		break;
	case ID_CHARENCODING+14:
		ec = wxFONTENCODING_ISO2022_JP;
		break;
	case ID_CHARENCODING+15:
		ec = wxFONTENCODING_EUC_JP;
		break;
	case ID_CHARENCODING + 16:
		ec = wxFONTENCODING_ISO8859_8;
		break;
	
	}
	//wxFontEncoding cur = m_gopt->GetCurEncoding();
	m_gopt->SetEncoding(ec);
	if (id!=ID_CHARENCODING)
		m_gopt->SetUTF8(true);
	else	m_gopt->SetUTF8(false);
	ale_it it;
	
	this->SaveGlobalOptions();
	this->m_actwindow->Refresh();
	luaBuildalias();
	luaBuilddefvar();
	luaBuildtrigger();
	luaBuildvar();
	m_child->Update();
	return;
}

void MudMainFrame::OnPrefs(wxCommandEvent& WXUNUSED(event))
{

	dlg_options *od = new dlg_options(this);
    od->GetGeneral()->InitDialog();
	od->GetTelnet()->InitDialog();
	od->GetLog()->InitDialog();
	if (od->ShowModal()==wxID_OK)
	{
		od->GetGeneral()->TransferDataFromWindow();
		od->GetTelnet()->TransferDataFromWindow();
		od->GetLog()->TransferDataFromWindow();
		m_child->SetMaxLines((wxUint64)od->GetMaxLines());
		m_gopt->SetMaxHist(od->GetHistSize());
		m_gopt->SetCommand(od->GetCS().c_str());
		m_gopt->SetSep(od->GetCSep().c_str());
		m_gopt->SetSpeedwalk(od->GetCSw().c_str());
		m_gopt->SetSWDelay(od->GetCSwD());
		m_gopt->SetBSpeedwalk(od->GetCSwr().c_str());
		m_gopt->SetScript(od->GetCScr().c_str());
		m_gopt->SetVar(od->GetCVar().c_str());
		m_gopt->SetListVar(od->GetCList().c_str());
		m_gopt->SetWorldSend(od->GetCWorld().c_str());
		m_gopt->SetMCCP(od->GetMccp());
		m_gopt->SetNAWS(od->GetNaws());
		m_gopt->SetGAEOR(od->GetGAEOR());
		m_gopt->SetMXP(od->GetMXP());
		m_gopt->SetMSP(od->GetMSP());
		m_gopt->SetUseATCP(od->GetATCP());
		m_gopt->SetUseATCP2(od->GetGMCP());
		m_gopt->SetUseAard(od->GetAard());
		m_gopt->SetUseMSDP(od->GetMSDP());
		m_gopt->SetUTF8(od->GetUTF8());
		m_gopt->SetAutoConnect(od->GetAC());
		m_gopt->SetACDelay(od->GetACDel());
		m_input->SetKeepInput(od->GetKeepInput());
		m_input->SetParse(od->GetParse());
		m_input->SetTabDlg(od->GetTabDlg());
		if (m_input->GetParse())
			m_toggle->SetBitmapLabel(wxArtProvider::GetBitmap(wxART_TICK_MARK, wxART_BUTTON));
		else
			m_toggle->SetBitmapLabel(wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_BUTTON));
		od->GetTelnet()->TransferDataFromWindow();
		m_actwindow->SetAnsi(od->GetAnsi());
		m_actwindow->SetTimeStamps(od->GetStamps());
		m_actwindow->SetMilliSeconds(od->GetMilli());
		m_actwindow->SetLockPrompt(od->GetPrompt());
		m_actwindow->SetGagPrompt(od->GetGagPrompt());
		m_actwindow->SetPromptRegExp(od->GetRegExp());
		m_gopt->SetEcho(od->GetEcho());
		m_gopt->SetTriggerEcho(od->GetTEcho());
		SetVerbose(od->GetSEcho());
		m_gopt->SetUseWrap(od->GetUseWrap());
		m_gopt->SetAutoWrap(od->GetAutoWrap());
		m_actwindow->SetWrap(od->GetLineWrap());
		m_splitter->SetWrap(od->GetLineWrap());
		m_gopt->SetUseEvents(od->GetEvents());
		m_gopt->SetUseEvConn(od->GetEvConn());
		m_gopt->SetUseEvDisco(od->GetEvDisco());
		m_gopt->SetUseEvTelnetData(od->GetEvTelnetData());
		m_gopt->SetUseEvRecv(od->GetEvRecv());
		m_gopt->SetUseEvGMCPData(od->GetEvGMCPData());
		m_gopt->SetUseEvMSDPData(od->GetEvMSDPData());
		
		m_gopt->SetEventFile(od->GetEventFile());
		m_actwindow->SetEventFile(od->GetEventFile());
		//amcLua *aL = m_child->GetLState();
		amcLua *aL = m_actwindow->GetLState();
		wxSetWorkingDirectory(GetGlobalOptions()->GetWorkDir());
		wxSetWorkingDirectory(GetGlobalOptions()->GetScriptDir());
		//aL->DoFile(GetGlobalOptions()->GetEventFile());
		aL->DoFile(m_actwindow->GetEventFile());
		m_actwindow->SetClickURLs(od->GetUrls());
		
		SetSplitter(od->GetSplitter());
		m_actwindow->SetInclude(od->GetInclude());
		m_actwindow->SetDateLogging(od->GetTs());
		m_actwindow->SetIPV6(od->GetIPV6());
		int i = od->GetLogOpt();
		switch (i)
		{
		case 0:
			m_actwindow->SetHtmlLogging(true);
			m_actwindow->SetAnsiLogging(false);
			break;
		case 1:
			m_actwindow->SetHtmlLogging(false);
			m_actwindow->SetAnsiLogging(false);
			break;
		case 2:
			m_actwindow->SetHtmlLogging(false);
			m_actwindow->SetAnsiLogging(true);
			break;
		}
		wxString sss=od->GetLogDir();
		m_gopt->SetLogDir(sss);
		m_gopt->SetSoundDir(od->GetSoundDir());
		m_gopt->SetDatabaseDir(od->GetDatabaseDir());
		m_gopt->SetProfileDir(od->GetProfileDir());
		m_gopt->SetPackageDir(od->GetPackageDir());
		m_gopt->SetScriptDir(od->GetScriptDir());
		m_gopt->SetLuaDir(od->GetLuaDir());
		wxString ss = od->GetGMCPMods();
		wxArrayString as;
		as = wxSplit(ss, '\n');
		m_gopt->GetGMCPModules()->clear();
		for (size_t i=0;i<as.GetCount();i++)
			if (!as.Item(i).IsEmpty())
				m_gopt->GetGMCPModules()->push_back(as.Item(i));
		//m_child->AdjustScrollPage();
		SaveGlobalOptions();
		if (m_curhost != -1)
			//SaveProfile(GetHosts()->at(m_curhost).GetProfileName());
			SaveProfile(m_actwindow->GetProfile());
		else SaveProfile(m_curprofile);
		m_actwindow->Refresh();
		m_actwindow->Update();
	}
	od->Destroy();
}

void MudMainFrame::OnObjects(wxCommandEvent& event)
{
	dlg_obj *obj = new dlg_obj(this);
	obj->GetActions()->InitDialog();
	//obj->GetAlias()->InitDialog();
	//obj->GetHotkeys()->InitDialog();
	wxString s = event.GetString();
	if (s.Cmp(wxEmptyString))
	{
		obj->SetData(s);
	}
	
	if (obj->ShowModal()==wxID_OK)
	{
		//SaveProfile here
		obj->GetActions()->TransferDataFromWindow();
		if (m_curhost != -1)
			//SaveProfile(GetHosts()->at(m_curhost).GetProfileName());
			SaveProfile(m_actwindow->GetProfile());
		else SaveProfile(m_curprofile);
	}
	obj->Destroy();
	SetFocus();
	//m_input->SetFocus();
}

void MudMainFrame::OnSavePerspective(wxCommandEvent& WXUNUSED(event))
{
	if (m_curhost != -1)
		SaveProfile(m_actwindow->GetProfile());
	else SaveProfile(m_curprofile);
}

void MudMainFrame::OnInstallPackage(wxCommandEvent& event)
{
	wxString dir = GetGlobalOptions()->GetPackageDir();
	wxSetWorkingDirectory(dir);
	wxString file = wxFileSelector(_("Choose package to install"), dir, wxEmptyString, "lua", "lua files (*.lua)|*.lua|all files (*.*)|*.*", wxFD_OPEN, this);
	if (!file.empty())
	{
		
		s_it f = find(m_packages.begin(), m_packages.end(), file);
		if (f != m_packages.end())
		{
			wxString ss;
			ss << _("Error: You already have installed a package with the name: ") << file;
			m_child->Msg(ss);
			return;
		}
		wxString call;
		call << GetGlobalOptions()->GetCommand() << "func(\"" << file << "\", \"InstallPackage()\")";
		//s = wxString::Format(wxT("%cfunc(\"events.lua\", \"OnConnected()\")"), m_parent->GetGlobalOptions()->GetCommand());
		if (m_input->ParseCommandLine(&call))
		{
			m_packages.push_back(file);
			wxString s;
			s<<_("Installed package: ")<<file;
			m_child->Msg(s);
			//SaveProfile here
			if (m_curhost!=-1)
				SaveProfile(GetHosts()->at(m_curhost).GetProfileName());
			else SaveProfile(m_curprofile);
		}
		else m_child->Msg(_("Error installing package!"));

	}
}

void MudMainFrame::OnUninstallPackage(wxCommandEvent& event)
{
	wxString dir = GetGlobalOptions()->GetPackageDir();
	wxSetWorkingDirectory(dir);
	wxString file = wxFileSelector(_("Choose package to remove"), dir, wxEmptyString, ("lua"), ("lua files (*.lua)|*.lua|all files (*.*)|*.*"), wxFD_OPEN, this);
	if (!file.empty())
	{
		wxString call;
		call << GetGlobalOptions()->GetCommand() << ("func(\"") << file << ("\", \"UninstallPackage()\")");
		//s = wxString::Format(("%cfunc(\"events.lua\", \"OnConnected()\")"), m_parent->GetGlobalOptions()->GetCommand());
		if (m_input->ParseCommandLine(&call))
		{
			s_it it = find(m_packages.begin(), m_packages.end(), file);
			m_packages.erase(it);
			m_child->Msg(_("Uninstalled package!"));
		}
		else m_child->Msg(_("Error uninstalling package!"));
	}
}

void MudMainFrame::OnCreatePackage(wxCommandEvent& event)
{
	pkg_dlg *pkg = new pkg_dlg(this);
	//obj->GetActions()->InitDialog();
	//obj->GetAlias()->InitDialog();
	//obj->GetHotkeys()->InitDialog();
	if (pkg->ShowModal()==wxID_OK)
	{
		SavePackageFile(pkg->GetFile(), pkg->GetTrigger(), pkg->GetAlias(), pkg->GetHks(), pkg->GetGauges(), pkg->GetTimers(), pkg->GetLists(), pkg->GetVars(), pkg->GetButtons());	
	}
	pkg->Destroy();
	//SetFocus();
}

void MudMainFrame::OnEditScript(wxCommandEvent& event)
{
	wxDialog *dlg = (wxDialog*)wxDialog::FindWindowByName("amcScriptedit");
	if (dlg)
		return;
	dlg_script *sc = new dlg_script(this);
	sc->SetName("amcScriptedit");
	sc->Raise();
	sc->Show();
	
	//if (sc->ShowModal()==wxID_OK)
	//{
	//}
	//sc->Destroy();
}

void MudMainFrame::OnCreateCapture(wxCommandEvent& event)
{
MudWindow* mw;
wxString win = wxGetTextFromUser(_("Name of the window:"), _("Create new window"));
	if(win==wxEmptyString)
		return;
	mw = (MudWindow*)MudWindow::FindWindowByName(win, this);
	if (mw)
		return;
	mw = new MudWindow(this, win, 9);
	mw->SetName(win);
	
	m_actwindow->GetPanes()->push_back(win);//save all the windows we have
	
	m_mgr.AddPane(mw, wxAuiPaneInfo().Name(win).Caption(win).CaptionVisible(true).Floatable(true).FloatingSize(400,200).BestSize(400,200).Dockable(true).Dock().Top().Layer(1).Hide());
	unordered_map <wxString, wxWindow *> uw;
	uw = *this->m_actwindow->GetUserWindows();
	uw[win] = mw;
	this->m_actwindow->SetUserWindows(uw);
	m_mgr.GetPane(mw).Show();
	m_mgr.Update();	
	Refresh();
	Update();
	m_actwindow->Refresh();
	m_actwindow->Update();
}

void MudMainFrame::OnCreateNb(wxCommandEvent& event)
{
wxAuiNotebook* mw;
size_t i;
wxString win = wxGetTextFromUser(_("Name of the window:"), _("Create new window"));
	if(win==wxEmptyString)
		return;
	unordered_map <wxString, wxWindow *> uw;
	uw = *this->m_actwindow->GetUserWindows();
	mw = (wxAuiNotebook*)uw[win];
	//mw = (wxAuiNotebook*)wxAuiNotebook::FindWindowByName(win, this);
	if (mw)
		return;
	if (!mw)
	{
		mw = new wxAuiNotebook(this);
		mw->SetLabel(win);
		mw->SetName(win);
		m_actwindow->GetNbs()->push_back(win);
		vector<wxString> s;
		m_actwindow->GetNbPanes()->push_back(s);
		MudWindow *mw1 = (MudWindow*)MudWindow::FindWindowByName("tab1");
		if (mw1)
			return;
		if (!m_actwindow->GetNbs()->empty())
		{
			for (i=0;i<m_actwindow->GetNbs()->size();i++)
			{
				if (win==m_actwindow->GetNbs()->at(i))
					break;
			}
		}
		m_actwindow->GetNbPanes()->at(i).push_back("tab1");
		mw->AddPage(new MudWindow(this, "tab1", 9), "tab1");
		m_mgr.AddPane(mw, wxAuiPaneInfo().Name(win).Caption(win).CaptionVisible(true).Floatable(true).FloatingSize(400,200).BestSize(400,200).Dockable(true).Dock().Top().Layer(1).Show());
	}
	
	m_mgr.GetPane(mw).Show();
	m_mgr.Update();
	
	uw[win] = mw;
	this->m_actwindow->SetUserWindows(uw);
	Refresh();
	Update();
	m_actwindow->Refresh();
	m_actwindow->Update();
}

void MudMainFrame::OnCreateTB(wxCommandEvent& event)
{
	wxString tool = wxGetTextFromUser(_("Name of the toolbar:"), _("Create new toolbar"));
	wxAuiToolBar *tb;
	unordered_map <wxString, wxWindow *> uw;
	uw = *this->m_actwindow->GetUserWindows();
	
	tb = (wxAuiToolBar*)uw[tool];
	//tb = (wxAuiToolBar*)MudMainFrame::FindWindowByName(tool, this);
	if (tb)
		return;
	tb = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_TEXT | wxAUI_TB_GRIPPER);
	tb->SetName(tool);
	tb->SetToolTextOrientation(wxAUI_TBTOOL_TEXT_RIGHT);
	m_mgr.AddPane(tb, wxAuiPaneInfo().Name(tool).Caption(tool).ToolbarPane().CaptionVisible(false).Floatable(true).BestSize(600, 24).LeftDockable(true).Dockable(true).Dock().Top());
	m_mgr.GetPane(tb).Show();
	m_mgr.Update();	
	Refresh();
	Update();
	uw[tool] = tb;
	m_actwindow->SetUserWindows(uw);
	m_actwindow->Refresh();
	m_actwindow->Update();
}

void MudMainFrame::OnCreateGaugeWindow(wxCommandEvent& event)
{
	
	GaugeWindow *gw;
	wxString gauge = wxGetTextFromUser(_("Name of the window:"), _("Create new window"));
	unordered_map <wxString, wxWindow *> uw;
	uw = *this->m_actwindow->GetUserWindows();

	gw = (GaugeWindow*)uw[gauge];
	//gw = (GaugeWindow*)GaugeWindow::FindWindowByName(gauge, this);
	if (gw)
		return;
	gw = new GaugeWindow(this, gauge);
	gw->SetName(gauge);
	GetGaugePanes()->push_back(gauge);
	vector<wxString> s;
	GetGauges()->push_back(s);
	uw[gauge] = gw;
	m_actwindow->SetUserWindows(uw);
	m_mgr.AddPane(gw, wxAuiPaneInfo().Name(gauge).Caption(gauge).CaptionVisible(true).Floatable(true).FloatingSize(400,200).BestSize(400,200).Dockable(true).Dock().Top().Layer(1));
	m_mgr.Update();
}

void MudMainFrame::OnToggleAllTriggers(wxCommandEvent& event)
{
	m_triggerson = !m_triggerson;
	wxMenuBar* bar = GetMenuBar();
	wxMenuItem* item = bar->FindItem(event.GetId());
	if (m_triggerson)
		item->SetItemLabel(_("Disable all actions"));
	else
		item->SetItemLabel(_("Enable all actions"));
}
/*void MudMainFrame::OnScriptPause(wxThreadEvent& event)
{
unsigned int x;
	wxCriticalSectionLocker e(m_scriptcs);
	//unsigned int id = event.GetInt();
	wxThreadIdType id = event.GetExtraLong();
	for (x=0;x<GetThreads()->size();x++)
	{
		wxThreadIdType ii = GetThreads()->at(x)->GetMyId();
		if (id==GetThreads()->at(x)->GetMyId())
			break;
	}
	if (x >= GetThreads()->size())
		return;
	GetThreads()->at(x)->TestDestroy();
	if (GetThreads()->at(x)->IsRunning())
	{
		
		//amcScriptThread* th = GetThreads()->at(x);
		//th->Pause();
		//th->TestDestroy();
		
		GetThreads()->at(x)->Pause();
		#if __WXGTK__
		//for(int i=0;i<200;i++)
		GetThreads()->at(x)->TestDestroy();
		#endif
		#if __WXGTK__
		if (!GetThreads()->at(x)->IsPaused())
			GetThreads()->at(x)->TestDestroy();
		#endif
	}
	
}*/

/*void MudMainFrame::OnScriptResume(wxThreadEvent& event)
{
unsigned int x;
	
	wxCriticalSectionLocker d(m_scriptcs);
	wxThreadIdType id = (wxThreadIdType)event.GetExtraLong();
	for (x=0;x<GetThreads()->size();x++)
	{
		if (id==GetThreads()->at(x)->GetMyId())
			break;
	}
	if (x>=GetThreads()->size())
		return;
	
	if (GetThreads()->at(x)->IsPaused())
		GetThreads()->at(x)->Resume();
	//GetThreads()->at(x)->TestDestroy();
	//delete thread from vector
	
	vector<class amcScriptThread*>::iterator i = GetThreads()->begin();
	GetThreads()->erase(i+x);
	//delete the resume trigger
	wxString label;
	label << "temp" << id;
	int co = GetTriggerIndexByLabel(label);
	tr_it it = GetTrigger()->begin()+co;
	GetTrigger()->erase(it);
	
}*/

void MudMainFrame::OnMenuUi(wxUpdateUIEvent& event)
{
	//if (m_child->IsTextSelected() || m_splitter->IsTextSelected())
    MudWindow *mw = (MudWindow*)event.GetEventObject();
    if (mw->IsTextSelected())
		event.Enable(true);
	else
		event.Enable(false);
   }

void MudMainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	int i = m_childwindows.size();
	
	for (int ii = 0; ii < i; ii++)
	{
		m_actwindow = m_childwindows.at(ii);
		SaveProfile(m_childwindows.at(ii)->GetProfile());
	}
	if (!i)
		SaveProfile(m_actwindow->GetProfile());
	/*if (m_curhost!=-1)
		SaveProfile(GetHosts()->at(m_curhost).GetProfileName());
	else SaveProfile(m_curprofile);*/
	Close(true);
}

void MudMainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxAboutDialogInfo info;
    wxIcon const m(aamud11_xpm);
    info.SetIcon(m);
	info.AddDeveloper("oldjudge64@gmail.com");
	info.SetVersion(APP_VERSION);
	info.SetName(_("wxAmcl"));
	info.SetDescription(_("Mud client using wxWidgets!"));
	info.SetWebSite("https://github.com/oldjudge/wxamcl");
    info.SetCopyright("(c) 2017");
	
	wxAboutBox(info);
}

void MudMainFrame::OnParseInput(wxCommandEvent& event)
{
	m_input->SetParse(!m_input->GetParse());
	if (m_input->GetParse())
		m_toggle->SetBitmapLabel(wxArtProvider::GetBitmap(wxART_TICK_MARK, wxART_BUTTON));
	else
		m_toggle->SetBitmapLabel(wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_BUTTON));
	SaveGlobalOptions();
}

void MudMainFrame::BuildEncodingMenu(wxMenu* view)
{
	view->AppendSeparator();
	wxMenu *subMenu1 = new wxMenu;
	subMenu1->AppendCheckItem(ID_CHARENCODING, _("Standard"), _("System Standard encoding"));
	subMenu1->AppendCheckItem(ID_CHARENCODING+1, _("UTF-8"), _("UTF-8"));
	wxMenu *subMenu11 = new wxMenu;
	subMenu11->AppendCheckItem(ID_CHARENCODING+2, _("ISO-8859-1"), _("ISO-8859-1"));
	subMenu11->AppendCheckItem(ID_CHARENCODING+3, _("ISO-8859-15"), _("ISO-8859-15"));
	subMenu1->AppendSubMenu(subMenu11,_("Western"), _("Western"));
	subMenu1->AppendCheckItem(ID_CHARENCODING + 4, _("Central and East Europe"), ("ISO-8859-2"));

	wxMenu *subMenu12 = new wxMenu;
	subMenu12->AppendCheckItem(ID_CHARENCODING+5, _("ISO-8859-7"), _("ISO-8859-7"));
	subMenu12->AppendCheckItem(ID_CHARENCODING+6, _("Windows-1253"), _("Windows1253"));
	subMenu1->AppendSubMenu(subMenu12,_("Greek"), _("Greek"));
	wxMenu *subMenu2 = new wxMenu;
	subMenu2->AppendCheckItem(ID_CHARENCODING+7, _("KOI-8R"), _("KOI-8R"));
	subMenu2->AppendCheckItem(ID_CHARENCODING+8, _("KOI-8U"), _("KOI-8U"));
	subMenu2->AppendCheckItem(ID_CHARENCODING+9, _("ISO8859-5"), _("ISO-8859-5"));
	subMenu2->AppendCheckItem(ID_CHARENCODING+10, _("Windows-1251"), ("Windows-1251"));
	subMenu1->AppendSubMenu(subMenu2,_("Cyrillic"), _("Russian"));
	wxMenu *subMenu3 = new wxMenu;
	subMenu3->AppendCheckItem(ID_CHARENCODING+11, _("Big5"), _("Big5"));
	subMenu3->AppendCheckItem(ID_CHARENCODING+12, _("GBK"), ("CP936"));
	//subMenu3->AppendCheckItem(ID_CHARENCODING+13, _("GB1232"), ("GB1232"));
	subMenu1->AppendSubMenu(subMenu3,_("Chinese"), _("Chinese"));
	wxMenu *subMenu4 = new wxMenu;
	subMenu4->AppendCheckItem(ID_CHARENCODING+13, _("Shift-JIS"), _("JIS"));
	subMenu4->AppendCheckItem(ID_CHARENCODING+14, _("ISO2022-JP"), ("ISO2022-JP"));
	subMenu4->AppendCheckItem(ID_CHARENCODING+15, _("EUC_JP"), ("EUC_JP"));
	subMenu1->AppendSubMenu(subMenu4,_("Japanese"), _("Japanese"));
	subMenu1->AppendCheckItem(ID_CHARENCODING + 16, _("Hebrew"), ("ISO-8859-8"));
	view->AppendSubMenu(subMenu1, _("Character encoding"), _("Change character encoding"));
}

void MudMainFrame::CreateDefVars()
{
	
	m_actwindow->GetDefVars()->clear();
	m_actwindow->GetDefVars()->push_back(amcDefVar("wxamclChar", " "));
	m_actwindow->GetDefVars()->push_back(amcDefVar("wxamclIP", "0.0.0.0"));
	m_actwindow->GetDefVars()->push_back(amcDefVar("wxamclLocalIP", "0.0.0.0"));
	m_actwindow->GetDefVars()->push_back(amcDefVar("wxamclLines", "0"));

}

void MudMainFrame::DefineKeys()
{
	m_keys["AMC_A"] = 65;
	m_keys["AMC_B"] = 66;
	m_keys["AMC_C"] = 67;
	m_keys["AMC_D"] = 68;
	m_keys["AMC_E"] = 69;
	m_keys["AMC_F"] = 70;
	m_keys["AMC_G"] = 71;
	m_keys["AMC_H"] = 72;
	m_keys["AMC_I"] = 73;
	m_keys["AMC_J"] = 74;
	m_keys["AMC_K"] = 75;
	m_keys["AMC_L"] = 76;
	m_keys["AMC_M"] = 77;
	m_keys["AMC_N"] = 78;
	m_keys["AMC_O"] = 79;
	m_keys["AMC_P"] = 80;
	m_keys["AMC_Q"] = 81;
	m_keys["AMC_R"] = 82;
	m_keys["AMC_S"] = 83;
	m_keys["AMC_T"] = 84;
	m_keys["AMC_U"] = 85;
	m_keys["AMC_V"] = 86;
	m_keys["AMC_W"] = 87;
	m_keys["AMC_X"] = 88;
	m_keys["AMC_Y"] = 89;
	m_keys["AMC_Z"] = 90;
	m_keys["AMC_F1"] = WXK_F1;
	m_keys["AMC_F2"] = WXK_F2;
	m_keys["AMC_F3"] = WXK_F3;
	m_keys["AMC_F4"] = WXK_F4;
	m_keys["AMC_F5"] = WXK_F5;
	m_keys["AMC_F6"] = WXK_F6;
	m_keys["AMC_F7"] = WXK_F7;
	m_keys["AMC_F8"] = WXK_F8;
	m_keys["AMC_F9"] = WXK_F9;
	m_keys["AMC_F10"] = WXK_F10;
	m_keys["AMC_F11"] = WXK_F11;
	m_keys["AMC_F12"] = WXK_F12;
	m_keys["AMC_0"] = 48;
	m_keys["AMC_1"] = 49;
	m_keys["AMC_2"] = 50;
	m_keys["AMC_3"] = 51;
	m_keys["AMC_4"] = 52;
	m_keys["AMC_5"] = 53;
	m_keys["AMC_6"] = 54;
	m_keys["AMC_7"] = 55;
	m_keys["AMC_8"] = 56;
	m_keys["AMC_9"] = 57;
	m_keys["AMC_SPACE"] = WXK_SPACE;
	m_keys["AMC_NUMPAD_UP"] = WXK_NUMPAD_UP;
	m_keys["AMC_NUMPAD_DOWN"] = WXK_NUMPAD_DOWN;
	m_keys["AMC_NUMPAD_RIGHT"] = WXK_NUMPAD_RIGHT;
	m_keys["AMC_NUMPAD_LEFT"] = WXK_NUMPAD_LEFT;
	m_keys["AMC_NUMPAD7"] = WXK_NUMPAD7;
	m_keys["AMC_NUMPAD8"] = WXK_NUMPAD8;
	m_keys["AMC_NUMPAD9"] = WXK_NUMPAD9;
	m_keys["AMC_NUMPAD5"] = WXK_NUMPAD5;
	m_keys["AMC_NUMPAD1"] = WXK_NUMPAD1;
	m_keys["AMC_NUMPAD2"] = WXK_NUMPAD2;
	m_keys["AMC_NUMPAD3"] = WXK_NUMPAD3;
	m_keys["AMC_NUMPAD4"] = WXK_NUMPAD4;
	m_keys["AMC_NUMPAD6"] = WXK_NUMPAD6;
	m_keys["AMC_NUMPAD0"] = WXK_NUMPAD0;
	m_keys["AMC_MODNONE"] = wxMOD_NONE;
	m_keys["AMC_ALT"] = wxMOD_ALT;
	m_keys["AMC_ALTGR"] = wxMOD_ALTGR;
	m_keys["AMC_CTRL"] = wxMOD_CMD;
	m_keys["AMC_SHIFT"] = wxMOD_SHIFT;
	m_keys["AMC_SHIFT_ALT"] = wxMOD_SHIFT|wxMOD_ALT;
	m_keys["AMC_CMD_ALT"] = wxMOD_CMD|wxMOD_ALT;

}

bool MudMainFrame::LoadGlobalOptions()
{
	amcLua *aL = m_child->GetLState();
	struct lua_State *L = aL->GetLuaState();
	int err=0;
	wxString s;
	const char* error;
	wxSetWorkingDirectory(GetGlobalOptions()->GetWorkDir());
	lua_checkstack(L, 40);
	if ((err=m_child->GetLState()->DoFile("settings.lua")))
	{
		int top = lua_gettop(L);
		error = luaL_checkstring(L, top);
		m_child->Msg(error);
		return false;
	}
	aL->GetGlobal("global_options");
	aL->GetField(-1, "lines");
	m_child->SetMaxLines(aL->GetInt(-1));
	aL->GetField(-2, "history");
	m_gopt->SetMaxHist(aL->GetInt(-1));
	aL->GetField(-3, "keepinput");
	m_input->SetKeepInput(aL->GetBoolean(-1));
	aL->GetField(-4, "parseinput");
	m_input->SetParse(aL->GetBoolean(-1));
	aL->GetField(-5, "command");
	s = aL->GetwxString(-1);
	m_gopt->SetCommand(s.data());
	aL->GetField(-6, "separator");
	s = aL->GetwxString(-1);
	m_gopt->SetSep(s.data());
	aL->GetField(-7, "variable");
	s = aL->GetwxString(-1);
	m_gopt->SetVar(s.data());
	aL->GetField(-8, "speedwalk");
	s = aL->GetwxString(-1);
	m_gopt->SetSpeedwalk(s.data());
	aL->GetField(-9, "backspeedwalk");
	s = aL->GetwxString(-1);
	m_gopt->SetBSpeedwalk(s.data());
	aL->GetField(-10, "swdelay");
	m_gopt->SetSWDelay(aL->GetInt(-1));
	aL->GetField(-11, "script");
	s = aL->GetwxString(-1);
	m_gopt->SetScript(s.data());
	aL->GetField(-12, "list");
	s = aL->GetwxString(-1);
	m_gopt->SetListVar(s.data());
	//wxFont f;
	aL->GetField(-13, "font");
    s = aL->GetwxString(-1);
    wxFont f(s);
	/*f.SetFaceName(aL->GetwxString(-1));
	aL->GetField(-13, "fontsize");
	f.SetPointSize(aL->GetInt(-1));
	aL->GetField(-14, "fontfamily");
	//f.SetFamily(aL->GetInt(-1));
	aL->GetField(-15, "fontweight");
	f.SetWeight(aL->GetInt(-1));
    
	aL->GetField(-16, "fontstyle");
	f.SetStyle(aL->GetInt(-1));*/
	m_child->SetNFont(&f);
	m_child->SetFont(f);
	
	m_child->SetUFont(&f);
	m_child->SetIFont(&f);
	m_splitter->SetNFont(&f);
	m_splitter->SetUFont(&f);
	m_splitter->SetIFont(&f);
	
	aL->GetField(-14, "mccp");
	m_gopt->SetMCCP(aL->GetBoolean(-1));
	aL->GetField(-15, "gaeor");
	m_gopt->SetGAEOR(aL->GetBoolean(-1));
	aL->GetField(-16, "naws");
	m_gopt->SetNAWS(aL->GetBoolean(-1));
	aL->GetField(-17, "mxp");
	m_gopt->SetMXP(aL->GetBoolean(-1));
	aL->GetField(-18, "msp");
	m_gopt->SetMSP(aL->GetBoolean(-1));
	aL->GetField(-19, "atcp");
	m_gopt->SetUseATCP(aL->GetBoolean(-1));
	aL->GetField(-20, "gmcp");
	m_gopt->SetUseATCP2(aL->GetBoolean(-1));
	aL->GetField(-21, "msdp");
	m_gopt->SetUseMSDP(aL->GetBoolean(-1));
	aL->GetField(-22, "ansi");
	m_child->SetAnsi(aL->GetBoolean(-1));
	aL->GetField(-23, "echo");
	m_gopt->SetEcho(aL->GetBoolean(-1));
	aL->GetField(-24, "techo");
	m_gopt->SetTriggerEcho(aL->GetBoolean(-1));
	aL->GetField(-25, "utf8");
	m_gopt->SetUTF8(aL->GetBoolean(-1));
	aL->GetField(-26, "ipv6");
	m_child->SetIPV6(aL->GetBoolean(-1));
	aL->GetField(-27, "urls");
	m_child->SetClickURLs(aL->GetBoolean(-1));
	aL->GetField(-28, "splitter");
	this->SetSplitter(aL->GetBoolean(-1));
	aL->GetField(-29, "autoreconnect");
	m_gopt->SetAutoConnect(aL->GetBoolean(-1));
	aL->GetField(-30, "acdelay");
	m_gopt->SetACDelay(aL->GetInt(-1));
	aL->GetField(-31, "scriptfont");
	//wxFont ff;
	s = aL->GetwxString(-1);
	delete m_scriptfont;
//	m_scriptfont = new wxFont(9, wxMODERN, wxNORMAL, wxNORMAL, false, s);
    m_scriptfont = new wxFont(s);//(wxFontInfo(9).FaceName(s).Family(wxFONTFAMILY_MODERN));
	aL->GetField(-32, "charencoding");
	int ec = (int)aL->GetInt(-1);
	wxMenuBar* bar = GetMenuBar();
	wxMenuItem* item;
	switch(ec)
	{
		
		case wxFONTENCODING_SYSTEM:
			item = bar->FindItem(ID_CHARENCODING);
			item->Check();
		break;
		case wxFONTENCODING_UTF8:
			item = bar->FindItem(ID_CHARENCODING+1);
			item->Check();
		break;
		case wxFONTENCODING_ISO8859_1:
			item = bar->FindItem(ID_CHARENCODING+2);
			item->Check();
		break;
		case wxFONTENCODING_ISO8859_15:
			item = bar->FindItem(ID_CHARENCODING+3);
			item->Check();
		break;
        case wxFONTENCODING_ISO8859_2:
            item = bar->FindItem(ID_CHARENCODING+4);
            item->Check();
        break;
		case wxFONTENCODING_ISO8859_7:
			item = bar->FindItem(ID_CHARENCODING+5);
			item->Check();
		break;
		case wxFONTENCODING_CP1253:
			item = bar->FindItem(ID_CHARENCODING+6);
			item->Check();
		break;
		case wxFONTENCODING_KOI8:
			item = bar->FindItem(ID_CHARENCODING+7);
			item->Check();
		break;
		case wxFONTENCODING_KOI8_U:
			item = bar->FindItem(ID_CHARENCODING+8);
			item->Check();
		break;
		case wxFONTENCODING_ISO8859_5:
			item = bar->FindItem(ID_CHARENCODING+9);
			item->Check();
		break;
		case wxFONTENCODING_CP1251:
			item = bar->FindItem(ID_CHARENCODING+10);
			item->Check();
		break;
		case wxFONTENCODING_BIG5:
			item = bar->FindItem(ID_CHARENCODING+11);
			item->Check();
		break;
		case wxFONTENCODING_CP936:
			item = bar->FindItem(ID_CHARENCODING+12);
			item->Check();
		break;
		
		case wxFONTENCODING_SHIFT_JIS:
			item = bar->FindItem(ID_CHARENCODING+13);
			item->Check();
		break;
		case wxFONTENCODING_ISO2022_JP:
			item = bar->FindItem(ID_CHARENCODING+14);
			item->Check();
		break;
		case wxFONTENCODING_EUC_JP:
			item = bar->FindItem(ID_CHARENCODING+15);
			item->Check();
		break;
        case wxFONTENCODING_ISO8859_8:
            item = bar->FindItem(ID_CHARENCODING+16);
            item->Check();
        break;
	}
	m_gopt->SetEncoding((wxFontEncoding)aL->GetInt(-1));
	aL->GetGlobal("global_colors");
	int len = aL->GetObjectLen();
	aL->Pop(1);
	for (int i=0; i<len; i++)
	{
		aL->GetGlobal("global_colors");
		aL->RawGeti(-1, i+1);
		wxString c = aL->GetwxString(-1);
		wxColour cc;
		cc.Set(c.c_str());
		m_child->SetColour(i, cc);
		if (!i)
			{
			SetBackgroundColour(RGB(255,255,255));
			ClearBackground();
			Refresh();
			Update();
			m_child->SetBackgroundCol(cc);
			m_splitter->SetBackgroundCol(cc);
			}
		aL->SetTop(0);
	}
	aL->GetGlobal("global_recenthosts");
	len = aL->GetObjectLen();
	aL->Pop(1);
	for (int i=0; i<len; i++)
	{
		aL->GetGlobal("global_recenthosts");
		aL->RawGeti(-1, i+1);
		wxString host = aL->GetwxString(-1);
		m_lasthost.push_back(host);
		aL->SetTop(0);
	}
	aL->GetGlobal("global_recentports");
	len = aL->GetObjectLen();
	aL->Pop(1);
	for (int i=0; i<len; i++)
	{
		aL->GetGlobal("global_recentports");
		aL->RawGeti(-1, i+1);
		int port = aL->GetInt(-1);
		m_lastport.push_back(port);
		aL->SetTop(0);
	}
	return true;
}

bool MudMainFrame::SavePackageFile(wxFileName file, vector<wxString>*tr, vector<wxString>*al, vector<wxString>*hk, vector<wxString>*g, vector<wxString>*t, vector<wxString>*li, vector<wxString>*v, vector<wxString>*bu)
{
s_it it;
	wxSetWorkingDirectory(GetGlobalOptions()->GetPackageDir());
	wxFile* f = new wxFile(file.GetFullName(), wxFile::write);
	if (!f->IsOpened())
		return false;
	f->Write("\n\nfunction InstallPackage()\n\t");
	f->Write("--section action\n");
	for (it=tr->begin();it!=tr->end();it++)
	{
		int idx = GetTriggerIndexByLabel(*it);
		if (idx==-1)
			continue;
		wxString s;
		s<<"    wxamcl.action.new(\""<<GetTrigger()->at(idx).GetLabel()<<"\", [=["<<GetTrigger()->at(idx).GetPattern()<<"]=], "<<"[=["<<GetTrigger()->at(idx).GetAction()<<"]=], \""<<GetTrigger()->at(idx).GetClass()<<"\", true, "<<GetTrigger()->at(idx).GetPriority()
		 <<", "<<GetTrigger()->at(idx).GetColMatch()<<", "<<GetTrigger()->at(idx).GetLines()<<")\n"; 
		f->Write(s.c_str());
	}
	
	f->Write("\t--section alias\n");
	for (it=al->begin();it!=al->end();it++)
	{
		int idx = GetAliasIndexByLabel(*it);
		if (idx==-1)
			continue;
		wxString s;
		s<<"    wxamcl.alias.new(\""<<GetAlias()->at(idx).GetName()<<"\", [=["<<GetAlias()->at(idx).GetAction()<<"]=], \""<<GetAlias()->at(idx).GetGroup()<<"\", true)\n";
		f->Write(s.c_str());
	}
	
	f->Write("\t--section hotkeys\n");
	for (it=hk->begin();it!=hk->end();it++)
	{
		int idx = GetHkIndexByLabel(*it);
		if (idx==-1)
			continue;
		wxString s;
		
		//long k = m[cc];
		s<<"    wxamcl.hk.new(\""<<GetHotkeys()->at(idx).GetName()<<"\", \""<<GetHotkeys()->at(idx).GetKeyName()<<"\", \""<<GetHotkeys()->at(idx).GetModName()<<"\", \""<<GetHotkeys()->at(idx).GetAction()<<"\", \""<<GetHotkeys()->at(idx).GetGroup()<<"\", true)\n";
		f->Write(s.c_str());
	}
	f->Write("\t--section timers\n");
	for(it=t->begin();it!=t->end();it++)
	{
		int idx = this->GetTimerIndexByLabel(*it);
		if (idx==-1)
			continue;
		wxString s;
		s<<"    wxamcl.timer.new(\""<<GetTimers()->at(idx).GetName()<<"\", \""<<GetTimers()->at(idx).GetAction()<<"\", \""<<GetTimers()->at(idx).GetGroup()<<"\", "<<GetTimers()->at(idx).GetInterval()<<", "<<GetTimers()->at(idx).GetRepeat()<<", true)\n";
		f->Write(s.c_str());
	}
	f->Write("\t--section lists\n");
	for (it=li->begin();it!=li->end();it++)
	{
		int idx = GetListIndexByLabel(*it);
		if (idx==-1)
			continue;
		wxString s;
		s<<"    wxamcl.list.new(\""<<GetLists()->at(idx).GetName()<<"\", \""<<GetLists()->at(idx).GetGroup()<<"\", true)\n";
		f->Write(s.c_str());
		for (int c=0;c<GetLists()->at(idx).GetSize();c++)
		{
			s.Clear();
			s<<"        wxamcl.list.additem(\""<<GetLists()->at(idx).GetName()<<"\", \""<<GetLists()->at(idx).GetItem(c)<<"\")\n";
			f->Write(s.c_str());
		}
	}
	f->Write("\t--section variables\n");
	for (it=v->begin();it!=v->end();it++)
	{
		int idx = GetVarIndexByLabel(*it);
		if (idx==-1)
			continue;
		wxString s;
		s<<"    wxamcl.var.new(\""<<GetVars()->at(idx).GetName()<<"\", [=["<<GetVars()->at(idx).GetValue()<<"]=], \""<<GetVars()->at(idx).GetGroup()<<"\", true)\n";
		f->Write(s.c_str());
	}
	f->Write("\t--section buttons\n");
	for (it=bu->begin();it!=bu->end();it++)
	{
		int idx = GetButtonIndexByLabel(*it);
		if (idx==-1)
			continue;
		wxString s;
		s<<"    wxamcl.button.new(\""<<GetButtons()->at(idx).GetName()<<"\", [=["<<GetButtons()->at(idx).GetTbName()<<"]=], [=["<<GetButtons()->at(idx).GetAction()<<"]=], \""<<GetButtons()->at(idx).GetGroup()<<"\", true)\n";
		f->Write(s.c_str());
	}
	f->Write("\t--section gauges\n");
	s_it iit;
	for (iit=g->begin();iit!=g->end();iit++)
	{
		if (!GetGaugePanes()->empty())
		{
			for (it=GetGaugePanes()->begin();it!=GetGaugePanes()->end();it++)
			{
				GaugeWindow* gw = (GaugeWindow*)GaugeWindow::FindWindowByName(it->c_str(), this);
				g_it git;
				int idx = gw->GetGaugeIndexByName(*iit);
				if (idx==-1)
					continue;
				wxString s;
		
				//long k = m[cc];
				s<<"    wxamcl.gauge.new(\""<<gw->GetName()<<"\", \""<<gw->GetGauges()->at(idx).GetName()<<"\", \""<<gw->GetGauges()->at(idx).GetVar1()<<"\", \""
				<<gw->GetGauges()->at(idx).GetVar2()<<"\", \""<<gw->GetGauges()->at(idx).GetFCol().GetAsString(wxC2S_HTML_SYNTAX)<<"\", \""<<gw->GetGauges()->at(idx).GetBCol().GetAsString(wxC2S_HTML_SYNTAX)<<"\", "
				<<(gw->GetGauges()->at(idx).GetVertical() ? "true":"false")<<")\n";
				f->Write(s.c_str());
				s.Empty();
				s<<"    wxamcl.gauge.setsize(\""<<gw->GetName()<<"\", \""<<gw->GetGauges()->at(idx).GetName()<<"\", "<<gw->GetGauges()->at(idx).GetX()<<", "<<gw->GetGauges()->at(idx).GetY()<<", "<<gw->GetGauges()->at(idx).GetCx()<<
					", "<<gw->GetGauges()->at(idx).GetCy()<<")\n";
				f->Write(s.c_str());
				s.Empty();
				s << "    wxamcl.gauge.setstyle(\"" << gw->GetName() << "\", \"" << gw->GetGauges()->at(idx).GetName() << "\", " << gw->GetGauges()->at(idx).GetStyle() << ")\n";
				f->Write(s.c_str());
			}
		}
	}
	f->Write("end\n");
	f->Write("\n\nfunction UninstallPackage()\n");
	f->Write("\t--section action\n");
	for (it=tr->begin();it!=tr->end();it++)
	{
		int idx = GetTriggerIndexByLabel(*it);
		if (idx==-1)
			continue;
		wxString s;
		s<<"    wxamcl.action.delete(\""<<GetTrigger()->at(idx).GetLabel()<<"\")\n";
		f->Write(s.c_str());
	}
	f->Write("\t--section alias\n");
	for (it=al->begin();it!=al->end();it++)
	{
		int idx = GetAliasIndexByLabel(*it);
		if (idx==-1)
			continue;
		wxString s;
		s<<"    wxamcl.alias.delete(\""<<GetAlias()->at(idx).GetName()<<"\")\n";
		f->Write(s.c_str());
	}
	f->Write("\t--section gauges\n");
	for (iit=g->begin();iit!=g->end();iit++)
	{
		if (!GetGaugePanes()->empty())
		{
			for (it=GetGaugePanes()->begin();it!=GetGaugePanes()->end();it++)
			{
				GaugeWindow* gw = (GaugeWindow*)GaugeWindow::FindWindowByName(it->c_str(), this);
				g_it git;
				int idx = gw->GetGaugeIndexByName(*iit);
				if (idx==-1)
					continue;
				wxString s;
		
				//long k = m[cc];
				s<<"    wxamcl.gauge.delete(\""<<gw->GetName()<<"\", "<<"\""<<gw->GetGauges()->at(idx).GetName()<<"\")\n";
				f->Write(s.c_str());
			}
		}
	}

	f->Write("\t--section hotkeys\n");
	for (it=hk->begin();it!=hk->end();it++)
	{
		int idx = GetHkIndexByLabel(*it);
		if (idx==-1)
			continue;
		wxString s;
		s<<"    wxamcl.hk.delete(\""<<GetHotkeys()->at(idx).GetName()<<"\")\n";
		f->Write(s.c_str());
	}
	f->Write("\t--section timers\n");
	for (it=t->begin();it!=t->end();it++)
	{
		int idx = GetTimerIndexByLabel(*it);
		if (idx==-1)
			continue;
		wxString s;
		s<<"    wxamcl.timer.delete(\""<<GetTimers()->at(idx).GetName()<<"\")\n";
		f->Write(s.c_str());
	}
	f->Write("\t--section lists\n");
	for (it=li->begin();it!=li->end();it++)
	{
		int idx = GetListIndexByLabel(*it);
		if (idx==-1)
			continue;
		wxString s;
		s<<"    wxamcl.list.delete(\""<<GetLists()->at(idx).GetName()<<"\")\n";
		f->Write(s.c_str());
	}
	f->Write("\t--section variables\n");
	for (it=v->begin();it!=v->end();it++)
	{
		int idx = GetVarIndexByLabel(*it);
		if (idx==-1)
			continue;
		wxString s;
		s<<"    wxamcl.var.delete(\""<<GetVars()->at(idx).GetName()<<"\")\n";
		f->Write(s.c_str());
	}
	f->Write("\t--section buttons\n");
	for (it=bu->begin();it!=bu->end();it++)
	{
		int idx = GetButtonIndexByLabel(*it);
		if (idx==-1)
			continue;
		wxString s;
		s<<"    wxamcl.button.delete(\""<<GetButtons()->at(idx).GetName()<<"\")\n";
		f->Write(s.c_str());
	}
	f->Write("end\n");
	f->Close();
	delete f;
	return true;
}

bool MudMainFrame::SaveGlobalOptions()
{
	wxString s;
	wxSetWorkingDirectory(GetGlobalOptions()->GetWorkDir());
	::wxRemoveFile("settings.lua");
	wxFile* file = new wxFile("settings.lua", wxFile::write);
	if (!file->IsOpened())
		return false;
	file->Write("\n\t-- global settings for wxAmcl\n\n\tglobal_options = {\n\t\t");
	wxString x="[\"lines\"] =";
	x<<m_child->GetMaxLines()<<", \n";
	file->Write(x.c_str());
	//file->Write(wxString::Format("[\"lines\"] = %dl,\n", m_child->GetMaxLines()));
	file->Write(wxString::Format("\t\t[\"history\"] = %d,\n", m_gopt->GetMaxHist()));
	file->Write(wxString::Format("\t\t[\"keepinput\"] = %s,\n", m_input->GetKeepInput() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"parseinput\"] = %s,\n", m_input->GetParse() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"command\"] = \"%c\",\n", m_gopt->GetCommand()));
	file->Write(wxString::Format("\t\t[\"separator\"] = \"%c\",\n", m_gopt->GetSep()));
	file->Write(wxString::Format("\t\t[\"variable\"] = \"%c\",\n", m_gopt->GetVar()));
	file->Write(wxString::Format("\t\t[\"speedwalk\"] = \"%c\",\n", m_gopt->GetSpeedwalk()));
	file->Write(wxString::Format("\t\t[\"backspeedwalk\"] = \"%c\",\n", m_gopt->GetRevSpeedwalk()));
	file->Write(wxString::Format("\t\t[\"swdelay\"] = \"%d\",\n", m_gopt->GetSWDelay()));
	file->Write(wxString::Format("\t\t[\"script\"] = \"%c\",\n", m_gopt->GetScript()));
	file->Write(wxString::Format("\t\t[\"list\"] = \"%c\",\n", m_gopt->GetListVar()));
	//file->Write(wxString::Format("\t\t[\"font\"] = \"%s\",\n", m_child->GetFont()->GetFaceName().c_str()));
    file->Write(wxString::Format("\t\t[\"font\"] = \"%s\",\n", m_child->GetFont()->GetNativeFontInfoDesc().c_str()));
    wxLogDebug(m_child->GetFont()->GetNativeFontInfoDesc());
	/*file->Write(wxString::Format("\t\t[\"fontsize\"] = %d,\n", m_child->GetFont()->GetPointSize()));
	file->Write(wxString::Format("\t\t[\"fontfamily\"] = %d,\n", m_child->GetFont()->GetFamily()));
	file->Write(wxString::Format("\t\t[\"fontweight\"] = %d,\n", m_child->GetFont()->GetWeight()));
	file->Write(wxString::Format("\t\t[\"fontstyle\"] = %d,\n", m_child->GetFont()->GetStyle()));*/
	file->Write(wxString::Format("\t\t[\"mccp\"] = %s,\n", m_gopt->UseMCCP() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"gaeor\"] = %s,\n", m_gopt->UseGAEOR() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"naws\"] = %s,\n", m_gopt->UseNAWS() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"mxp\"] = %s,\n", m_gopt->UseMXP() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"msp\"] = %s,\n", m_gopt->UseMSP() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"atcp\"] = %s,\n", m_gopt->UseATCP() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"gmcp\"] = %s,\n", m_gopt->UseATCP2() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"msdp\"] = %s,\n", m_gopt->UseMSDP() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"ansi\"] = %s,\n", m_child->UseAnsi() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"echo\"] = %s,\n", m_gopt->GetEcho() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"techo\"] = %s,\n", m_gopt->GetTriggerEcho() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"utf8\"] = %s,\n", m_gopt->UseUTF8() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"ipv6\"] = %s,\n", m_child->GetUseIPV6() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"urls\"] = %s,\n", m_child->UseClickURLs() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"splitter\"] = %s,\n", this->UseSplitter() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"autoreconnect\"] = %s,\n", m_gopt->GetAutoConnect() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"acdelay\"] = %d,\n", m_gopt->GetACDelay()));
	file->Write(wxString::Format("\t\t[\"scriptfont\"] = \"%s\", \n", this->GetScriptFont()->GetNativeFontInfoDesc()));
	file->Write(wxString::Format("\t\t[\"charencoding\"] = %d, \n", m_gopt->GetCurEncoding()));
	file->Write("\t}\n\n");
	file->Write(("\tglobal_colors = {\n\t\t"));
	/*file->Write(wxString::Format("%i, %i, %i, %i, %i, %i, %i, %i,\n\t\t", m_child->GetAnsiColor(0).GetPixel(), m_child->GetAnsiColor(1).GetPixel(), m_child->GetAnsiColor(2).GetPixel(),
		m_child->GetAnsiColor(3).GetPixel(), m_child->GetAnsiColor(4).GetPixel(), m_child->GetAnsiColor(5).GetPixel(),
		m_child->GetAnsiColor(6).GetPixel(), m_child->GetAnsiColor(7).GetPixel()));
	file->Write(wxString::Format("%i, %i, %i, %i, %i, %i, %i, %i,\n\t\t", m_child->GetAnsiColor(8).GetPixel(), m_child->GetAnsiColor(9).GetPixel(), m_child->GetAnsiColor(10).GetPixel(),
		m_child->GetAnsiColor(11).GetPixel(), m_child->GetAnsiColor(12).GetPixel(), m_child->GetAnsiColor(13).GetPixel(),
		m_child->GetAnsiColor(14).GetPixel(), m_child->GetAnsiColor(15).GetPixel()));
	file->Write(wxString::Format("%i, %i, %i\n", m_child->GetAnsiColor(16).GetPixel(), m_child->GetAnsiColor(17).GetPixel(), m_child->GetAnsiColor(18).GetPixel()));*/
	file->Write(wxString::Format("\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\",\n\t\t", m_child->GetAnsiColor(0).GetAsString(wxC2S_HTML_SYNTAX).c_str(), m_child->GetAnsiColor(1).GetAsString(wxC2S_HTML_SYNTAX).c_str(), m_child->GetAnsiColor(2).GetAsString(wxC2S_HTML_SYNTAX).c_str(),
		m_child->GetAnsiColor(3).GetAsString(wxC2S_HTML_SYNTAX).c_str(), m_child->GetAnsiColor(4).GetAsString(wxC2S_HTML_SYNTAX).c_str(), m_child->GetAnsiColor(5).GetAsString(wxC2S_HTML_SYNTAX).c_str(),
		m_child->GetAnsiColor(6).GetAsString(wxC2S_HTML_SYNTAX).c_str(), m_child->GetAnsiColor(7).GetAsString(wxC2S_HTML_SYNTAX).c_str()));
	file->Write(wxString::Format("\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\",\n\t\t", m_child->GetAnsiColor(8).GetAsString(wxC2S_HTML_SYNTAX).c_str(), m_child->GetAnsiColor(9).GetAsString(wxC2S_HTML_SYNTAX).c_str(), m_child->GetAnsiColor(10).GetAsString(wxC2S_HTML_SYNTAX).c_str(),
		m_child->GetAnsiColor(11).GetAsString(wxC2S_HTML_SYNTAX).c_str(), m_child->GetAnsiColor(12).GetAsString(wxC2S_HTML_SYNTAX).c_str(), m_child->GetAnsiColor(13).GetAsString(wxC2S_HTML_SYNTAX).c_str(),
		m_child->GetAnsiColor(14).GetAsString(wxC2S_HTML_SYNTAX).c_str(), m_child->GetAnsiColor(15).GetAsString(wxC2S_HTML_SYNTAX).c_str()));
	file->Write(wxString::Format("\"%s\", \"%s\", \"%s\"\n", m_child->GetAnsiColor(16).GetAsString(wxC2S_HTML_SYNTAX).c_str(), m_child->GetAnsiColor(17).GetAsString(wxC2S_HTML_SYNTAX).c_str(), m_child->GetAnsiColor(18).GetAsString(wxC2S_HTML_SYNTAX).c_str()));
	file->Write("\t}\n\n");
	file->Write("\tglobal_recenthosts = {\n\t\t");
	s_it it;
	for (it=m_lasthost.begin();it!=m_lasthost.end();it++)
	{
		file->Write(wxString::Format("\"%s\", ", *it));
		
	}
	file->Write("\n\t}\n\n");
	file->Write("\tglobal_recentports = {\n\t\t");
	vector<int>::iterator iit;
	for (iit=m_lastport.begin();iit!=m_lastport.end();iit++)
	{
		file->Write(wxString::Format("%d, ", *iit));
		
	}
	file->Write("\n\t}\n\n");
	wxDateTime dt;
	dt.SetToCurrent();
	file->Write(wxString::Format("\n\n\t-- written on %s, %s\n", dt.FormatDate().c_str(), dt.FormatTime().c_str()));
	file->Close();
	delete file;
	return true;
}

bool MudMainFrame::SaveProfile (wxString s)
{
tr_it it;
al_it ita;
hk_it ith;
v_it itv;
li_it itl;

	wxSetWorkingDirectory(GetGlobalOptions()->GetProfileDir());
	::wxRemoveFile(s);
	wxFile* file = new wxFile(s, wxFile::write);
	if (!file->IsOpened())
		return false;
	file->Write(("\n\t-- profile file for wxAmcl\n\n\tamc_actions = {\n"));
	for (it=m_actwindow->GetTrigger()->begin();it!=m_actwindow->GetTrigger()->end();it++)
	{
	    file->Write(wxString::Format("\t\t{[\"label\"] = [[%s]], ", it->GetLabel().c_str()));
		file->Write(wxString::Format("[\"pattern\"] = [=[%s]=], ", it->GetPattern().c_str()));
		file->Write(wxString::Format("[\"action\"] = [=[%s]=], ", it->GetAction().c_str()));
		file->Write(wxString::Format("[\"class\"] = [=[%s]=], ", it->GetClass().c_str()));
		file->Write(wxString::Format("[\"priority\"] = %d, ", it->GetPriority()));
		file->Write(wxString::Format("[\"colmatch\"] = %d, ", it->GetColMatch()));
		file->Write(wxString::Format("[\"matchcount\"] = %ld, ", it->GetMatchCount()));
		file->Write(wxString::Format("[\"on\"] = %s, ", it->IsActive() ? "true":"false"));
		file->Write(wxString::Format("[\"lines\"] = %d, ", it->GetLines()));
		file->Write(wxString::Format("[\"script\"] = %s}, \n", it->GetSendScript() ? "true":"false"));
	}
	file->Write("\t}");
	file->Write("\n\n\tamc_alias = {\n");
	wxString ss;
	for (ita=m_actwindow->GetAlias()->begin();ita!=m_actwindow->GetAlias()->end();ita++)
	{
		ss<<("\t\t{[\"alias\"] = [[") << ita->GetAlias().c_str() << ("]], ");
		file->Write(ss.c_str());//wxString::Format("\t\t{[\"label\"] = [[%s]], ", it->GetLabel().c_str()));
		ss.clear();
		ss<<("[\"action\"] = [[") << ita->GetAction().c_str() << ("]], ");
		file->Write(ss.c_str());//wxString::Format("[\"pattern\"] = [=[%s]=], ", it->GetPattern().c_str()));
		ss.clear();
		ss<<("[\"group\"] = [[") << ita->GetGroup().c_str() << ("]], ");
		file->Write(ss.c_str());//wxString::Format("[\"action\"] = [=[%s]=], ", it->GetAction().c_str()));
		ss.clear();
		ss<<("[\"on\"] = ") << (ita->IsActive() ? ("true"):("false")) << (" }, \n");
		file->Write(ss.c_str());//wxString::Format("[\"on\"] = %s, ", it->IsActive() ? ("true"):("false")));
		ss.clear();
	}
	file->Write(("\t}"));
	file->Write("\n\n\tamc_hotkey = {\n");
	for (ith=m_actwindow->GetHotkeys()->begin();ith!=m_actwindow->GetHotkeys()->end();ith++)
	{
		ss<<("\t\t{[\"name\"] = [[") << ith->GetName().c_str() << ("]], ");
		file->Write(ss.c_str());//wxString::Format("\t\t{[\"label\"] = [[%s]], ", it->GetLabel().c_str()));
		ss.clear();
		ss<<("[\"action\"] = [[") << ith->GetAction().c_str() << ("]], ");
		file->Write(ss.c_str());//wxString::Format("[\"pattern\"] = [=[%s]=], ", it->GetPattern().c_str()));
		ss.clear();
		ss<<("[\"group\"] = [[") << ith->GetGroup().c_str() << ("]], ");
		file->Write(ss.c_str());//wxString::Format("[\"action\"] = [=[%s]=], ", it->GetAction().c_str()));
		ss.clear();
		ss<<("[\"on\"] = ") << (ith->IsActive() ? ("true"):("false")) << (", ");
		file->Write(ss.c_str());//wxString::Format("[\"on\"] = %s, ", it->IsActive() ? ("true"):("false")));
		ss.clear();
		ss<<("[\"key\"] = ") << ith->GetHotkey() << (", ");
		file->Write(ss.c_str());//wxString::Format("[\"on\"] = %s, ", it->IsActive() ? ("true"):("false")));
		ss.clear();
		ss<<("[\"modifier\"] = ") << ith->GetModifier() << (" }, \n");
		file->Write(ss.c_str());//wxString::Format("[\"on\"] = %s, ", it->IsActive() ? ("true"):("false")));
		ss.clear();
	}
	file->Write(("\t}"));
	file->Write("\n\n\tamc_vars = {\n");
	for (itv=m_actwindow->GetVars()->begin();itv!=m_actwindow->GetVars()->end();itv++)
	{
		ss<<("\t\t{[\"name\"] = [[") << itv->GetName().c_str() << ("]], ");
		file->Write(ss.c_str());//wxString::Format("\t\t{[\"label\"] = [[%s]], ", it->GetLabel().c_str()));
		ss.clear();
		ss<<("[\"value\"] = [=[") << itv->GetValue().c_str() << ("]=], ");
		file->Write(ss.c_str());//wxString::Format("[\"pattern\"] = [=[%s]=], ", it->GetPattern().c_str()));
		ss.clear();
		ss<<("[\"group\"] = [[") << itv->GetGroup().c_str() << ("]], ");
		file->Write(ss.c_str());//wxString::Format("[\"action\"] = [=[%s]=], ", it->GetAction().c_str()));
		ss.clear();
		ss<<("[\"on\"] = ") << (itv->IsActive() ? ("true"):("false")) << (" }, \n");
		file->Write(ss.c_str());//wxString::Format("[\"on\"] = %s, ", it->IsActive() ? ("true"):("false")));
		ss.clear();
	}
	file->Write(("\t}"));
	file->Write(("\n\n\tamc_lists = {\n"));
	for (itl=m_actwindow->GetLists()->begin();itl!=m_actwindow->GetLists()->end();itl++)
	{
		ss<<("\t\t{[\"name\"] = [[") << itl->GetName().c_str() << ("]], ");
		file->Write(ss.c_str());//wxString::Format("\t\t{[\"label\"] = [[%s]], ", it->GetLabel().c_str()));
		ss.clear();
		ss<<("[\"group\"] = [[") << itl->GetGroup().c_str() << ("]], ");
		file->Write(ss.c_str());//wxString::Format("[\"action\"] = [=[%s]=], ", it->GetAction().c_str()));
		ss.clear();
		ss<<("[\"on\"] = ") << (itl->IsActive() ? ("true"):("false")) << (", ");
		file->Write(ss.c_str());//wxString::Format("[\"on\"] = %s, ", it->IsActive() ? ("true"):("false")));
		ss.clear();
		file->Write(("[\"items\"] = { "));
		for (int i=0;i<itl->GetSize();i++)
		{
			ss<<("\"")<<itl->GetItem(i)<<("\", ");
			file->Write(ss.c_str());
			ss.clear();
		}
		file->Write(("}, }, \n"));
	}
	file->Write("\t}");
	
	file->Write("\n\n\tamc_prompt = {\n");
	ss<<("\t\t[\"lockprompt\"] = ")<<(m_actwindow->LockPrompt() ? ("true"):("false")) << (" , \n");
	file->Write(ss.c_str());
	ss.clear();
	ss<<("\t\t[\"gagprompt\"] = ")<<(m_actwindow->GagPrompt() ? ("true"):("false")) << (" , \n");
	file->Write(ss.c_str());
	ss.clear();
	ss<<("\t\t[\"promptpattern\"] = [[") << m_actwindow->GetPromptRegExp().c_str() << ("]], \n");
	file->Write(ss.c_str());
	file->Write("\t}");

	file->Write("\n\n\tamc_panes = {\n");
	s_it sit;
	//if (!m_panes.empty())
	if (!m_actwindow->GetPanes()->empty())
	{
		for (sit=m_actwindow->GetPanes()->begin();sit!=m_actwindow->GetPanes()->end();sit++)
		{
			file->Write(wxString::Format("\t\t{[\"name\"] = [[%s]], ", sit->c_str()));
			MudWindow* mw = (MudWindow*)MudWindow::FindWindowByName(*sit, this);
			file->Write(wxString::Format("[\"font\"] = [[%s]], ", mw->GetFont()->GetNativeFontInfoDesc().c_str()));
			file->Write(wxString::Format("[\"timestamps\"] = %s,\n", mw->UseTimeStamps() ? "true" : "false"));
			wxAuiPaneInfo pa = m_mgr.GetPane(*sit);
			wxString pi = m_mgr.SavePaneInfo(pa);
			file->Write(wxString::Format("\t\t[\"amcpaneinfo\"] = [[%s]]}, \n", pi.c_str()));
		}
	}
	file->Write("\t}");
	file->Write("\n\n\tamc_nbs = {\n");
	if (!m_actwindow->GetNbs()->empty())
	{
		for (sit=m_actwindow->GetNbs()->begin();sit!=m_actwindow->GetNbs()->end();sit++)
		{
			file->Write(wxString::Format("\t\t{[\"name\"] = [[%s]], ", sit->c_str()));
			wxAuiPaneInfo pa = m_mgr.GetPane(*sit);
			wxString pi = m_mgr.SavePaneInfo(pa);
			file->Write(wxString::Format("[\"amcpaneinfo\"] = [[%s]]}, \n", pi.c_str()));
		}
	}
	file->Write("\t}");
	file->Write("\n\n\tamc_nbpanes = {\n");
	vector<vector<wxString> >::iterator vit;
	if (!m_actwindow->GetNbPanes()->empty())
	{
		for (vit=m_actwindow->GetNbPanes()->begin();vit!=m_actwindow->GetNbPanes()->end();vit++)
		{
			file->Write(("\t\t{ "));
			for(size_t i=0; i<vit->size();i++)
			{
				file->Write(wxString::Format("{[\"name\"] = [[%s]], ", vit->at(i).c_str()));
				MudWindow* mw = (MudWindow*)MudWindow::FindWindowByName(vit->at(i), this);
				file->Write(wxString::Format("[\"font\"] = [[%s]], ", mw->GetFont()->GetNativeFontInfoDesc().c_str()));
				file->Write(wxString::Format("[\"timestamps\"] = %s},", mw->UseTimeStamps() ? ("true") : ("false")));
			}
			file->Write(("\t}, \n"));
		}
	}
	file->Write(("\t}"));
	file->Write(("\n\n\tamc_gaugepanes = {\n"));
	if (!m_actwindow->GetGaugePanes()->empty())
	{
		for (sit=m_actwindow->GetGaugePanes()->begin();sit!=m_actwindow->GetGaugePanes()->end();sit++)
		{
			file->Write(wxString::Format("\t\t{[\"name\"] = [[%s]], ", sit->c_str()));
			GaugeWindow* gw = (GaugeWindow*)GaugeWindow::FindWindowByName(*sit, this);
			file->Write(wxString::Format("[\"font\"] = [[%s]], \n", gw->GetFont()->GetNativeFontInfoDesc().c_str()));
			wxAuiPaneInfo pa = m_mgr.GetPane(*sit);
			wxString pi = m_mgr.SavePaneInfo(pa);
			file->Write(wxString::Format("\t\t[\"amcpaneinfo\"] = [[%s]]}, \n", pi.c_str()));
			
		}
	}
	file->Write(("\t}"));
	file->Write(("\n\n\tamc_gauges = {\n"));
	//vector<vector<wxString> >::iterator vit;
	if (!m_actwindow->GetGaugePanes()->empty())
	{
		for (sit=m_actwindow->GetGaugePanes()->begin();sit!=m_actwindow->GetGaugePanes()->end();sit++)
		{
			GaugeWindow* gw = (GaugeWindow*)GaugeWindow::FindWindowByName(sit->c_str(), this);
			g_it git;
			file->Write(("\t\t{\n "));
			for (git=gw->GetGauges()->begin();git!=gw->GetGauges()->end();git++)
			{
				ss.clear();
				ss<<("\t\t{[\"gaugename\"] = [[")<<git->GetName()<<("]], ");
				file->Write(ss.c_str());
				//file->Write(wxString::Format("{[\"gaugename\"] = [[%s]], ", git->GetName()));
				ss.clear();
				ss<<("[\"var1\"] = [[")<<git->GetVar1()<<("]], ");
				file->Write(ss.c_str());
				//file->Write(wxString::Format("[\"var1\"] = [[%s]], ", git->GetVar1()));
				ss.clear();
				ss<<"[\"var2\"] = [["<<git->GetVar2()<<"]], ";
				file->Write(ss.c_str());
				//file->Write(wxString::Format("[\"var2\"] = [[%s]], ", git->GetVar2()));
				file->Write(wxString::Format("[\"fcol\"] = \"%s\", ", git->GetFCol().GetAsString(wxC2S_HTML_SYNTAX).c_str()));
				file->Write(wxString::Format("[\"bcol\"] = \"%s\", ", git->GetBCol().GetAsString(wxC2S_HTML_SYNTAX).c_str()));
				file->Write(wxString::Format("[\"alarm\"] = \"%s\", ", git->GetAlarm().GetAsString(wxC2S_HTML_SYNTAX).c_str()));
				file->Write(wxString::Format("[\"alarmperc\"] = \"%d\", ", git->GetAlarmPerc()));
				file->Write(wxString::Format("[\"x\"] = \"%d\", ", git->GetX()));
				file->Write(wxString::Format("[\"y\"] = \"%d\", ", git->GetY()));
				file->Write(wxString::Format("[\"cx\"] = \"%d\", ", git->GetCx()));
				file->Write(wxString::Format("[\"cy\"] = \"%d\", ", git->GetCy()));
				file->Write(wxString::Format("[\"vertical\"] = %s, ", git->GetVertical() ? "true" : "false"));
				file->Write(wxString::Format("[\"style\"] = %d, ", git->GetStyle()));
				file->Write(wxString::Format("[\"showvalue\"] = %s, ", git->ShowValue() ? "true" : "false"));
				file->Write(wxString::Format("[\"textcol\"] = \"%s\", ", git->GetTextCol().GetAsString(wxC2S_HTML_SYNTAX).c_str()));
				file->Write(wxString::Format("[\"textpos\"] = %d}, \n", git->GetTextPos()));
				//file->Write(wxString::Format("[\"bcol\"] = \"%s\", ", git->GetBCol().GetAsString(wxC2S_HTML_SYNTAX).c_str()));
			}
			file->Write(("\t\t}, \n"));
		}
	}
	file->Write("\t}");
	file->Write(("\n\n\tamc_amcwindows = {\n"));
	
	//if (!m_panes.empty())
	if (!m_actwindow->GetAmcWindows()->empty())
	{
		for (sit=m_actwindow->GetAmcWindows()->begin();sit!=m_actwindow->GetAmcWindows()->end();sit++)
		{
			file->Write(wxString::Format("\t\t{[\"name\"] = [[%s]], ", sit->c_str()));
			amcWindow* aw = (amcWindow*)amcWindow::FindWindowByName(*sit, this);
			file->Write(wxString::Format("[\"fontname\"] = [[%s]], \n", aw->GetFont().GetNativeFontInfoDesc().c_str()));
			wxAuiPaneInfo pa = m_mgr.GetPane(*sit);
			wxString pi = m_mgr.SavePaneInfo(pa);
			file->Write(wxString::Format("\t\t[\"amcpaneinfo\"] = [[%s]]}, \n", pi.c_str()));
			
		}
	}
	file->Write(("\t}"));
	file->Write("\n\n\tamc_buttons = {\n");
	wxString bttb_old;
	std::vector<wxString> bttb;
	if (!m_actwindow->GetButtons()->empty())
	{
		b_it bit;
		for(bit=m_actwindow->GetButtons()->begin();bit!=m_actwindow->GetButtons()->end();bit++)
		{
			ss.clear();
			ss << "\t\t{[\"name\"] = [[" << bit->GetName() << "]], ";
			file->Write(ss.c_str());
			ss.clear();
			ss << "[\"action\"] = [[" << bit->GetAction() << "]], ";
			file->Write(ss.c_str());
			ss.clear();
			ss << "[\"id\"] = "<< bit->GetId() <<", ";
			file->Write(ss.c_str());
			ss.clear();
			ss << "[\"group\"] = [[" << bit->GetGroup() << "]], ";
			file->Write(ss.c_str());
			ss.clear();
			ss << "[\"tb\"] = [[" << bit->GetTbName() << "]], ";
			if (bttb_old.Cmp(bit->GetTbName()))
			{
				bttb_old = bit->GetTbName();
				bttb.push_back(bit->GetTbName());
			}
			
			file->Write(ss.c_str());
			ss.clear();
			ss << "[\"bitmap\"] = [[" << bit->GetBitmap() << "]]},\n";
			file->Write(ss.c_str());
			ss.clear();
		}
	}
	
	file->Write("\t}");
	file->Write("\t\n\n\tamc_tbs = {\n");
	for (int i = 0; i < bttb.size(); i++)
	{
		file->Write(wxString::Format("\t{[\"name\"] = [[%s]], ", bttb.at(i)));
		wxAuiPaneInfo pa = m_mgr.GetPane(bttb.at(i));
		wxString pi = m_mgr.SavePaneInfo(pa);
		file->Write(wxString::Format("[\"amcpaneinfo\"] = [[%s]]}, \n", pi.c_str()));
	}
	file->Write("\t}");
	file->Write("\n\n\tamc_packages = {\n");
	ss.clear();
	for (sit=m_actwindow->GetPackages()->begin();sit!=m_actwindow->GetPackages()->end();sit++)
	{
		ss<<"\t\t[[" << *sit << "]],\n";
		file->Write(ss.c_str());//wxString::Format("\t\t{[\"label\"] = [[%s]], ", it->GetLabel().c_str()));
		ss.clear();
	}
	file->Write("\t}");
	file->Write("\n\n\tamc_events = {\n");
	file->Write(wxString::Format("\t\t[\"useevents\"] = %s,\n", m_gopt->GetUseEvents() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"event_onconnect\"] = %s,\n", m_gopt->GetUseEvConn() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"event_onreceived\"] = %s,\n", m_gopt->GetUseEvRecv() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"event_ondisconnect\"] = %s,\n", m_gopt->GetUseEvDisco() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"event_ontelnetdata\"] = %s,\n", m_gopt->GetUseEvTelnetData() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"event_ongmcpdata\"] = %s,\n", m_gopt->GetUseEvGMCPData () ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"event_onmsdpdata\"] = %s,\n", m_gopt->GetUseEvMSDPData() ? "true" : "false"));
	file->Write(wxString::Format("\t\t[\"eventfile\"] = [[%s]],\n", m_actwindow->GetEventFile().c_str()));
	file->Write("\t}");

	file->Write("\n\n\tamc_gmcpmodules = {\n");
	for (size_t i=0;i<m_gopt->GetGMCPModules()->size();i++)
	{
		if (!m_gopt->GetGMCPModules()->at(i).empty())
		{
			file->Write("\t\t");
			file->Write("\""+m_gopt->GetGMCPModules()->at(i).c_str()+"\"");
			file->Write(",\n");
		}
	}
	file->Write("\t}");
	file->Write("\n\n\tamc_directories = {\n");
	ss.Clear();
	ss << "\t\t[\"scriptdir\"] = [[" << m_gopt->GetScriptDir() <<"]],\n";
	file->Write(ss.c_str());
	ss.Clear();
	ss << "\t\t[\"logdir\"] = [[" << m_gopt->GetLogDir() <<"]],\n";
	file->Write(ss.c_str());
	ss.Clear();
	ss << "\t\t[\"sounddir\"] = [[" << m_gopt->GetSoundDir() <<"]],\n";
	file->Write(ss.c_str());
	ss.Clear();
	ss << "\t\t[\"packagedir\"] = [[" << m_gopt->GetPackageDir() <<"]],\n";
	file->Write(ss.c_str());
	ss.Clear();
	ss << "\t\t[\"databasedir\"] = [[" << m_gopt->GetDatabaseDir() <<"]],\n";
	file->Write(ss.c_str());
	file->Write("\t}");
	wxString p = m_mgr.SavePerspective();
	file->Write(("\n\n\tamc_layout = "));
	file->Write(wxString::Format("[=[%s]=]\n", p.c_str()));
	wxAuiPaneInfo pa = m_mgr.GetPane("amcinput");
	wxString pi = m_mgr.SavePaneInfo(pa);
	
	file->Write(("\n\n\tamc_mainwindows = {\n"));
	file->Write(wxString::Format("\t\t[\"amcinput\"] = [[%s]] ,\n", pi.c_str()));
	pa = m_mgr.GetPane("amcmain");
	pi = m_mgr.SavePaneInfo(pa);
	file->Write(wxString::Format("\t\t[\"amcmain\"] = [[%s]] ,\n", pi.c_str()));
	pa = m_mgr.GetPane("amcsplitter");
	pi = m_mgr.SavePaneInfo(pa);
	file->Write(wxString::Format("\t\t[\"amcsplitter\"] = [[%s]] ,\n", pi.c_str()));
	pa = m_mgr.GetPane("amctoggle");
	pi = m_mgr.SavePaneInfo(pa);
	file->Write(wxString::Format("\t\t[\"amctoggle\"] = [[%s]] ,\n", pi.c_str()));
	pa = m_mgr.GetPane("amcmedia");
	pi = m_mgr.SavePaneInfo(pa);
	file->Write(wxString::Format("\t\t[\"amcmedia\"] = [[%s]] ,\n", pi.c_str()));
	pa = m_mgr.GetPane("amcmultinb");
	pi = m_mgr.SavePaneInfo(pa);
	file->Write(wxString::Format("\t\t[\"amcmultinb\"] = [[%s]] ,\n", pi.c_str()));
	pa = m_mgr.GetPane("amctooolbar");
	pi = m_mgr.SavePaneInfo(pa);
	file->Write(wxString::Format("\t\t[\"amctoolbar\"] = [[%s]] ,\n", pi.c_str()));
	pa = m_mgr.GetPane("amcprompt");
	pi = m_mgr.SavePaneInfo(pa);
	file->Write(wxString::Format("\t\t[\"amcprompt\"] = [[%s]] ,\n", pi.c_str()));

	file->Write("\t}");
	wxDateTime dt;
	dt.SetToCurrent();
	file->Write(wxString::Format(("\n\t-- written on %s, %s\n"), dt.FormatDate().c_str(), dt.FormatTime().c_str()));
	
	file->Close();
	delete file;
	return true;
}

bool MudMainFrame::LoadProfile(wxFileName s, bool firsttime)
{
	s_it it;
	unordered_map <wxString, wxWindow *> uw;
	uw = *this->m_actwindow->GetUserWindows();
	if (firsttime)
	{
		for (it = m_panes.begin(); it != m_panes.end(); it++)
		{
			MudWindow* mw = (MudWindow*)MudWindow::FindWindowByName(*it, this);
			m_mgr.DetachPane(mw);
			//m_mgr.Update();
			mw->Destroy();
		}
		for (it = m_amcwindows.begin(); it != m_amcwindows.end(); it++)
		{
			amcWindow* aw = (amcWindow*)amcWindow::FindWindowByName(*it, this);
			if (aw == NULL)
				continue;
			m_mgr.DetachPane(aw);
			//m_mgr.Update();
			aw->Destroy();
		}
		vector<vector<wxString> >::iterator vit;
		if (!GetNbPanes()->empty())
		{
			int x = 0;
			for (vit = GetNbPanes()->begin(); vit != GetNbPanes()->end(); vit++, x++)
			{
				it = m_nbs.begin() + x;
				wxAuiNotebook *nb = (wxAuiNotebook*)wxWindow::FindWindowByName(*it, this);
				for (size_t i = 0; i < vit->size(); i++)
				{
					wxString s = vit->at(i);
					MudWindow* mw = (MudWindow*)MudWindow::FindWindowByName(s, this);
					if (!mw)
						continue;
					nb->RemovePage(nb->GetPageIndex(mw));
					m_mgr.DetachPane(mw);
					mw->Destroy();
				}
			}
		}
		for (it = m_nbs.begin(); it != m_nbs.end(); it++)
		{

			wxAuiNotebook *nb = (wxAuiNotebook*)wxWindow::FindWindowByName(*it, this);
			m_mgr.DetachPane(nb);
			nb->Destroy();
		}

		if (!GetGaugePanes()->empty())
		{
			for (it = GetGaugePanes()->begin(); it != GetGaugePanes()->end(); it++)
			{
				GaugeWindow *gw = (GaugeWindow*)GaugeWindow::FindWindowByName(*it, this);
				if (!gw)
					continue;
				m_mgr.DetachPane(gw);
				gw->Destroy();
			}
		}
		wxAuiToolBar *tb = 0;
		if (!this->GetButtons()->empty())
		{
			for (size_t x = 0; x < GetButtons()->size(); x++)
			{
				wxString n = GetButtons()->at(x).GetTbName();
				tb = (wxAuiToolBar*)wxAuiToolBar::FindWindowByName(n, this);
				if (!tb)
					continue;
				m_mgr.GetPane(tb).Dock();
				m_mgr.Update();
				m_mgr.DetachPane(tb);
				bool b = tb->Destroy();
				if (b)
					tb = NULL;
			}
			GetButtons()->clear();
		}
		m_mgr.Update();
	}
	
	
	

	//Build Menu
	wxMenuBar* bar = GetMenuBar();
	wxMenu* view = bar->GetMenu(bar->FindMenu(_("View")));

	if (m_splitter->IsShown())
		view->Check(ID_SPLITTER, true);
	int ii = view->GetMenuItemCount();

	if (ii > 3)
	{
		for (size_t i = 0; i < m_actwindow->GetPanes()->size(); i++)
		{
			view->Destroy(view->FindItem(m_actwindow->GetPanes()->at(i)));
		}
		for (size_t i = 0; i < m_actwindow->GetNbs()->size(); i++)
		{
			view->Destroy(view->FindItem(m_actwindow->GetNbs()->at(i)));
		}
		for (size_t i = 0; i < m_actwindow->GetGaugePanes()->size(); i++)
		{
			view->Destroy(view->FindItem(m_actwindow->GetGaugePanes()->at(i)));
		}
		for (size_t i = 0; i < m_actwindow->GetAmcWindows()->size(); i++)
		{
			view->Destroy(view->FindItem(m_actwindow->GetAmcWindows()->at(i)));
		}
	}


	amcLua *aL = m_actwindow->GetLState();
	struct lua_State *L = aL->GetLuaState();
	int err = 0;
	const char* error;
	wxSetWorkingDirectory(GetGlobalOptions()->GetProfileDir());
	
	if ((err = m_actwindow->GetLState()->DoFile(s.GetFullPath())))
	{
		int top = lua_gettop(L);
		error = luaL_checkstring(L, top);
		m_actwindow->Msg(error);
		return false;
	}

	aL->GetGlobal("amc_actions");
	int len = aL->GetObjectLen();
	m_trigger.clear();
	Trigger::GetTriggerClasses()->clear();
	aL->Pop(1);
	for (int i = 0; i < len; i++)
	{
		Trigger tr;
		aL->GetGlobal("amc_actions");
		aL->PushInt(i + 1);
		aL->GetTable(-2);
		aL->GetField(-1, "label");
		tr.SetLabel(aL->GetUTF8String(-1));
		aL->GetField(-2, "pattern");
		tr.SetPattern(aL->GetUTF8String(-1));
		aL->GetField(-3, "action");
		tr.SetAction(aL->GetUTF8String(-1));
		aL->GetField(-4, "class");
		tr.SetClass(aL->GetUTF8String(-1));
		aL->GetField(-5, "priority");
		tr.SetPriority(aL->GetInt(-1));
		aL->GetField(-6, "colmatch");
		tr.SetColMatch(aL->GetInt(-1));
		aL->GetField(-7, "matchcount");
		tr.SetMatchCount((long)aL->GetInt(-1));
		aL->GetField(-8, "on");
		tr.SetActive(aL->GetBoolean(-1));
		aL->GetField(-9, "lines");
		tr.SetLines(aL->GetInt(-1));
		aL->GetField(-10, "script");
		tr.SetSendScript(aL->GetBoolean(-1));
		aL->SetTop(0);
		m_trigger.push_back(tr);
	}

	stable_sort(m_trigger.begin(), m_trigger.end(), greater<class Trigger>());
	//luaBuildtrigger();
	aL->GetGlobal("amc_alias");
	len = aL->GetObjectLen();
	amcAlias::GetAliasGroups()->clear();
	m_alias.clear();
	aL->Pop(1);
	for (int i = 0; i < len; i++)
	{
		amcAlias al;
		aL->GetGlobal("amc_alias");
		aL->PushInt(i + 1);
		aL->GetTable(-2);
		aL->GetField(-1, "alias");

		al.SetAlias(aL->GetUTF8String(-1));
		aL->GetField(-2, "action");
		al.SetAction(aL->GetUTF8String(-1));
		aL->GetField(-3, "group");
		al.SetGroup(aL->GetUTF8String(-1));
		aL->GetField(-4, "on");
		al.SetActive(aL->GetBoolean(-1));
		aL->SetTop(0);
		m_alias.push_back(al);
	}
	stable_sort(m_alias.begin(), m_alias.end(), less<class amcAlias>());
	
	aL->GetGlobal("amc_hotkey");
	len = aL->GetObjectLen();
	amcHotkey::GetHotkeyGroups()->clear();
	m_hotkeys.clear();
	aL->Pop(1);
	for (int i = 0; i < len; i++)
	{
		amcHotkey hk;
		aL->GetGlobal("amc_hotkey");
		aL->PushInt(i + 1);
		aL->GetTable(-2);
		aL->GetField(-1, "name");
		hk.SetName(aL->GetUTF8String(-1));
		aL->GetField(-2, "action");
		hk.SetAction(aL->GetUTF8String(-1));
		aL->GetField(-3, "group");
		hk.SetGroup(aL->GetUTF8String(-1));
		aL->GetField(-4, "on");
		hk.SetActive(aL->GetBoolean(-1));
		aL->GetField(-5, "key");
		hk.SetHotkey(aL->GetLong(-1));
		aL->GetField(-6, "modifier");
		hk.SetMods(aL->GetInt(-1));
		aL->SetTop(0);
		m_hotkeys.push_back(hk);
	}
	//stable_sort(m_alias.begin(), m_alias.end(), less<class amcAlias>());
	aL->GetGlobal("amc_vars");
	len = aL->GetObjectLen();
	m_vars.clear();
	amcVar::GetVarGroups()->clear();
	aL->Pop(1);
	for (int i = 0; i < len; i++)
	{
		amcVar v;
		aL->GetGlobal("amc_vars");
		aL->PushInt(i + 1);
		aL->GetTable(-2);
		aL->GetField(-1, "name");
		v.SetName(aL->GetUTF8String(-1));
		aL->GetField(-2, "value");
		v.SetValue(aL->GetUTF8String(-1));
		aL->GetField(-3, "group");
		v.SetGroup(aL->GetUTF8String(-1));
		aL->GetField(-4, "on");
		v.SetActive(aL->GetBoolean(-1));
		aL->SetTop(0);
		m_vars.push_back(v);
	}
	stable_sort(m_vars.begin(), m_vars.end(), less<class amcVar>());
	//luaBuildvar();
	aL->GetGlobal(("amc_lists"));
	len = aL->GetObjectLen();
	m_lists.clear();
	amcList::GetListGroups()->clear();
	aL->Pop(1);
	for (int i = 0; i < len; i++)
	{
		amcList li;
		aL->GetGlobal("amc_lists");
		aL->PushInt(i + 1);
		aL->GetTable(-2);
		aL->GetField(-1, "name");
		li.SetName(aL->GetUTF8String(-1));
		aL->GetField(-2, "group");
		li.SetGroup(aL->GetUTF8String(-1));
		aL->GetField(-3, "on");
		li.SetActive(aL->GetBoolean(-1));
		aL->GetField(-4, "items");
		int l = aL->GetObjectLen();
		aL->Pop(1);
		for (int ii = 0; ii < l; ii++)
		{
			aL->GetField(-4, "items");
			aL->RawGeti(-1, ii + 1);
			li.AddItem(aL->GetUTF8String(-1));
			aL->Pop(2);
		}
		aL->SetTop(0);
		m_lists.push_back(li);
	}
	
	//Create the windows only if first time called
	if (firsttime)
	{

		uw.clear();
		m_panes.clear();
		m_nbs.clear();
		aL->GetGlobal("amc_panes");
		len = aL->GetObjectLen();
		aL->Pop(1);
		for (int i = 0; i < len; i++)
		{
			aL->GetGlobal("amc_panes");
			aL->PushInt(i + 1);
			aL->GetTable(-2);
			aL->GetField(-1, "name");
			wxString win = aL->GetUTF8String(-1);
			GetPanes()->push_back(win);


			aL->GetField(-2, "font");
			wxFont f(aL->GetUTF8String(-1));

			MudWindow * mw = new MudWindow(this, win, f.GetPointSize());
			//MudWindow mw(this, win, 9);
			mw->SetName(win);
#ifdef __WXMSW__
			if (GetGlobalOptions()->GetCurEncoding() == wxFONTENCODING_UTF8)
				mw->SetWrapping(false); //workaround under windows UTF8
#endif

			mw->SetNFont(&f);
			mw->SetUFont(&f);
			aL->GetField(-3, "timestamps");
			mw->SetTimeStamps(aL->GetBoolean(-1));
			aL->GetField(-4, "amcpaneinfo");
			wxString info = aL->GetUTF8String(-1);
			wxAuiPaneInfo pane;
			m_mgr.LoadPaneInfo(info, pane);
			m_mgr.AddPane(mw, pane);
			//m_mgr.AddPane(mw, wxAuiPaneInfo().Name(win).Caption(win).CaptionVisible(true).Floatable(true).FloatingSize(400, 200).BestSize(400, 200).Dockable(true).Dock().Top().Layer(1).Show());
			aL->SetTop(0);


			uw[win] = mw;
		}
		m_amcwindows.clear();
		aL->GetGlobal("amc_amcwindows");
		len = aL->GetObjectLen();
		aL->Pop(1);
		for (int i = 0; i < len; i++)
		{
			aL->GetGlobal("amc_amcwindows");
			aL->PushInt(i + 1);
			aL->GetTable(-2);
			aL->GetField(-1, "name");
			wxString win = aL->GetUTF8String(-1);
			GetAmcWindows()->push_back(win);

			aL->GetField(-2, "fontname");
			wxFont f(aL->GetUTF8String(-1));
			aL->GetField(-3, "amcpaneinfo");
			wxString info = aL->GetUTF8String(-1);
			

			//amcWindow * aw = new amcWindow(this, win);
			amcWindow * aw = new amcWindow(this, win);
			aw->SetName(win);

			//m_mgr.AddPane(aw, wxAuiPaneInfo().Name(win).Caption(win).CaptionVisible(true).Floatable(true).FloatingSize(400, 200).BestSize(400, 200).Dockable(true).Dock().Top().Layer(1).Show());
			aL->SetTop(0);
			uw[win] = aw;
			wxAuiPaneInfo pane;
			m_mgr.LoadPaneInfo(info, pane);
			m_mgr.AddPane(aw, pane);
		}

		aL->GetGlobal("amc_nbs");
		m_nbpanes.clear();
		len = aL->GetObjectLen();
		aL->Pop(1);
		for (int i = 0; i < len; i++)
		{
			aL->GetGlobal("amc_nbs");
			aL->PushInt(i + 1);
			aL->GetTable(-2);
			aL->GetField(-1, "name");
			wxString win = aL->GetUTF8String(-1);
			GetNbs()->push_back(win);
			vector<wxString> s;
			GetNbPanes()->push_back(s);
			wxAuiNotebook * nb = new wxAuiNotebook(this);
			nb->SetName(win);
			nb->SetLabel(win);
			aL->GetField(-2, "amcpaneinfo");
			wxString info = aL->GetUTF8String(-1);
			aL->GetGlobal("amc_nbpanes");
			aL->PushInt(i + 1);
			aL->GetTable(-2);
			int len1 = aL->GetObjectLen();
			aL->Pop(1);
			uw[win] = nb;

			for (int x = 0; x < len1; x++)
			{
				aL->GetGlobal("amc_nbpanes");
				aL->PushInt(i + 1);
				aL->GetTable(-2);
				aL->PushInt(x + 1);
				aL->GetTable(-2);
				aL->GetField(-1, "name");
				wxString win1 = aL->GetUTF8String(-1);
				MudWindow * mw = new MudWindow(this, win1, 9);
				mw->SetName(win1);
				//uw[win1] = mw;
				GetNbPanes()->at(i).push_back(win1);
				aL->GetField(-2, "font");

				wxFont f(aL->GetUTF8String(-1));
				mw->SetNFont(&f);
				mw->SetUFont(&f);
				aL->GetField(-3, "timestamps");
				mw->SetTimeStamps(aL->GetBoolean(-1));
				nb->AddPage(mw, win1);
				//aL->Pop(1);
				aL->SetTop(0);
				//delete mw;
			}
			//m_mgr.AddPane(nb, wxAuiPaneInfo().Name(win).Caption(win).CaptionVisible(true).Floatable(true).FloatingSize(400, 200).BestSize(400, 200).Dockable(true).Dock().Top().Layer(1).Show());
			wxAuiPaneInfo pane;
			m_mgr.LoadPaneInfo(info, pane);
			m_mgr.AddPane(nb, pane);
			aL->SetTop(0);
			//delete nb;
		}

		aL->GetGlobal("amc_gaugepanes");
		len = aL->GetObjectLen();
		aL->Pop(1);
		GetGaugePanes()->clear();
		GetGauges()->clear();
		for (int i = 0; i < len; i++)
		{
			aL->GetGlobal("amc_gaugepanes");
			aL->PushInt(i + 1);
			aL->GetTable(-2);
			aL->GetField(-1, "name");
			wxString win = aL->GetUTF8String(-1);
			GetGaugePanes()->push_back(win);
			vector<wxString> s;
			GetGauges()->push_back(s);
			class GaugeWindow * gw = new GaugeWindow(this, win);
			gw->SetName(win);
			gw->SetLabel(win);
			uw[win] = gw;
			//wxFont f;
			aL->GetField(-2, "font");
			wxFont f(aL->GetUTF8String(-1));

			gw->SetFont(&f);
			aL->GetField(-3, "amcpaneinfo");
			wxString info = aL->GetUTF8String(-1);
			aL->GetGlobal(("amc_gauges"));
			aL->PushInt(i + 1);
			aL->GetTable(-2);
			int len1 = aL->GetObjectLen();
			aL->Pop(1);

			for (int x = 0; x < len1; x++)
			{
				aL->GetGlobal("amc_gauges");
				aL->PushInt(i + 1);
				aL->GetTable(-2);
				aL->PushInt(x + 1);
				aL->GetTable(-2);
				aL->GetField(-1, "gaugename");
				wxString win1 = aL->GetUTF8String(-1);
				GetGauges()->at(i).push_back(win1);
				aL->GetField(-2, "var1");
				wxString var1 = aL->GetUTF8String(-1);
				aL->GetField(-3, "var2");
				wxString var2 = aL->GetUTF8String(-1);
				aL->GetField(-4, "fcol");
				wxString fcol = aL->GetUTF8String(-1);
				aL->GetField(-5, "bcol");
				wxString bcol = aL->GetUTF8String(-1);
				aL->GetField(-6, "alarm");
				wxString al = aL->GetUTF8String(-1);
				aL->GetField(-7, "alarmperc");
				int f = aL->GetInt(-1);
				aL->GetField(-8, "x");
				int xx = aL->GetInt(-1);
				aL->GetField(-9, "y");
				int y = aL->GetInt(-1);
				aL->GetField(-10, "cx");
				int cx = aL->GetInt(-1);
				aL->GetField(-11, "cy");
				int cy = aL->GetInt(-1);
				aL->GetField(-12, "vertical");
				bool b = aL->GetBoolean(-1);
				aL->GetField(-13, "style");
				int style = aL->GetInt(-1);
				aL->GetField(-14, "showvalue");
				bool c = aL->GetBoolean(-1);
				aL->GetField(-15, "textcol");
				wxString tcol = aL->GetUTF8String(-1);
				aL->GetField(-16, "textpos");
				int t = aL->GetInt(-1);
				wxColour fc;
				wxColour bc;
				wxColour alarm;
				fc.Set(fcol.c_str());
				bc.Set(bcol.c_str());
				alarm.Set(al.c_str());
				amcGauge g(win, win1, var1, var2, fc, bc, xx, y, cx, cy, b);
				g.SetStyle(style);
				g.SetTextPos(t);
				g.SetTextCol(tcol);
				g.SetAlarmCol(alarm);
				g.SetAlarmPerc(f);
				g.SetShowValue(c);
				g.Register();
				//gw->GetGauges()->push_back(g);
				aL->SetTop(0);
			}
			//m_mgr.AddPane(gw, wxAuiPaneInfo().Name(win).CaptionVisible(false).Floatable(true).FloatingSize(400, 200).BestSize(400, 200).Dockable(true).Dock().Top().Layer(1).Show());
			aL->SetTop(0);
			wxAuiPaneInfo pane;
			m_mgr.LoadPaneInfo(info, pane);
			m_mgr.AddPane(gw, pane);
			//delete gw;
		}

	}//end firsttime

	aL->GetGlobal("amc_packages");
	len = aL->GetObjectLen();
	aL->Pop(1);
	GetPackages()->clear();
	for (int i = 0; i < len; i++)
	{
		aL->GetGlobal("amc_packages");
		aL->RawGeti(-1, i + 1);
		GetPackages()->push_back(aL->GetUTF8String(-1));
		aL->SetTop(0);
	}
	aL->GetGlobal("amc_prompt");
	aL->GetField(-1, "lockprompt");
	m_actwindow->SetLockPrompt(aL->GetBoolean(-1));
	aL->GetField(-2, "gagprompt");
	m_actwindow->SetGagPrompt(aL->GetBoolean(-1));
	aL->GetField(-3, "promptpattern");
	wxString reg = aL->GetUTF8String(-1);
	m_actwindow->SetPromptRegExp(reg.data());
	aL->SetTop(0);

	aL->GetGlobal("amc_buttons");
	len = aL->GetObjectLen();
	aL->Pop(1);
	m_buttons.clear();
	for (int i = 0; i < len; i++)
	{
		amcButton b;
		aL->GetGlobal("amc_buttons");
		aL->PushInt(i + 1);
		aL->GetTable(-2);
		aL->GetField(-1, "name");
		b.SetName(aL->GetUTF8String(-1));
		b.SetText(aL->GetUTF8String(-1));
		aL->GetField(-2, "action");
		b.SetAction(aL->GetUTF8String(-1));
		aL->GetField(-3, "id");
		b.SetId(aL->GetInt(-1));
		aL->GetField(-4, "group");
		b.SetGroup(aL->GetUTF8String(-1));
		aL->GetField(-5, "tb");
		b.SetTbName(aL->GetUTF8String(-1));
		aL->GetField(-6, "bitmap");
		b.SetBitmap(aL->GetUTF8String(-1));
		b.SetActive(true);
		aL->SetTop(0);
		m_buttons.push_back(b);
	}
	

	aL->GetGlobal("amc_events");
	aL->GetField(-1, "useevents");
	m_gopt->SetUseEvents(aL->GetBoolean(-1));
	aL->GetField(-2, "event_onconnect");
	m_gopt->SetUseEvConn(aL->GetBoolean(-1));
	aL->GetField(-3, "event_onreceived");
	m_gopt->SetUseEvRecv(aL->GetBoolean(-1));
	aL->GetField(-4, "event_ondisconnect");
	m_gopt->SetUseEvDisco(aL->GetBoolean(-1));
	aL->GetField(-5, "event_ontelnetdata");
	m_gopt->SetUseEvTelnetData(aL->GetBoolean(-1));
	aL->GetField(-6, "event_ongmcpdata");
	m_gopt->SetUseEvGMCPData(aL->GetBoolean(-1));
	aL->GetField(-7, "event_onmsdpdata");
	m_gopt->SetUseEvMSDPData(aL->GetBoolean(-1));
	aL->GetField(-8, "eventfile");
	wxString f = aL->GetUTF8String(-1);
	m_gopt->SetEventFile(f);
	this->m_actwindow->SetEventFile(f);

	aL->GetGlobal("amc_gmcpmodules");
	m_gopt->GetGMCPModules()->clear();
	len = aL->GetObjectLen();
	aL->Pop(1);
	for (int i = 0; i < len; i++)
	{
		aL->GetGlobal("amc_gmcpmodules");
		aL->RawGeti(-1, i + 1);
		m_gopt->GetGMCPModules()->push_back(aL->GetUTF8String(-1));
	}

	aL->GetGlobal("amc_directories");
	aL->GetField(-1, "scriptdir");
	f = aL->GetUTF8String(-1);
	m_gopt->SetScriptDir(f);
	aL->GetField(-2, "logdir");
	f = aL->GetUTF8String(-1);
	m_gopt->SetLogDir(f);
	aL->GetField(-3, "sounddir");
	f = aL->GetUTF8String(-1);
	m_gopt->SetSoundDir(f);
	aL->GetField(-4, "packagedir");
	f = aL->GetUTF8String(-1);
	m_gopt->SetPackageDir(f);
	aL->GetField(-5, "databasedir");
	f = aL->GetUTF8String(-1);
	m_gopt->SetDatabaseDir(f);
	aL->SetTop(0);
	
	aL->GetGlobal("amc_tbs");
	len = aL->GetObjectLen();
	aL->Pop(1);
	for (int i = 0; i < len; i++)
	{
		aL->GetGlobal("amc_tbs");
		aL->PushInt(i + 1);
		aL->GetTable(-2);
		aL->GetField(-1, "name");
		wxString win = aL->GetUTF8String(-1);
		aL->GetField(-2, "amcpaneinfo");
		wxString info = aL->GetUTF8String(-1);
		wxAuiPaneInfo pane;
		m_mgr.LoadPaneInfo(info, pane);
		bool k = m_mgr.GetPane(win).IsOk();
		if (!k)
		{
			wxAuiToolBar* tb = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_TEXT | wxAUI_TB_GRIPPER);
			tb->SetName(win);
			uw[win] = tb;
			tb->SetToolTextOrientation(wxAUI_TBTOOL_TEXT_RIGHT);
			m_mgr.AddPane(tb, pane);
		}
	}

	for (size_t i = 0; i < GetButtons()->size(); i++)
	{
		wxString n = GetButtons()->at(i).GetTbName();
		//wxAuiToolBar *tb = (wxAuiToolBar*)wxAuiToolBar::FindWindowByName(n, this);//(wxAuiToolBar*)MudMainFrame::FindWindowByName(n, this);
		wxAuiToolBar *tb = 0;
		bool k = m_mgr.GetPane(n).IsOk();
		if (k)
		{
			tb = (wxAuiToolBar*)wxAuiToolBar::FindWindowByName(n, this);
			GetButtons()->at(i).SetParent(tb);
			if (GetButtons()->at(i).GetName() == "separator")
				tb->AddSeparator();
			else
			{

				m_mgr.Update();
				wxSetWorkingDirectory(GetGlobalOptions()->GetImagesDir());
				tb->SetToolTextOrientation(wxAUI_TBTOOL_TEXT_RIGHT);
				wxBitmap bt(GetButtons()->at(i).GetBitmap(), wxBITMAP_TYPE_XPM);
				tb->AddTool(GetButtons()->at(i).GetId(), GetButtons()->at(i).GetName(), bt);//script_xpm);

			}
			tb->Realize();
			continue;
		}
		else
		{
			
			//m_mgr.AddPane(tb, wxAuiPaneInfo().Name(n).Caption(n).ToolbarPane().CaptionVisible(false).Floatable(true).BestSize(600, 24).LeftDockable(true).Dockable(true).Dock().Top());
			
			GetButtons()->at(i).SetParent(tb);
			if (GetButtons()->at(i).GetName() == "separator")
				tb->AddSeparator();
			else
			{
				wxSetWorkingDirectory(GetGlobalOptions()->GetImagesDir());
				wxBitmap bt(GetButtons()->at(i).GetBitmap(), wxBITMAP_TYPE_XPM);
				tb->AddTool(GetButtons()->at(i).GetId(), GetButtons()->at(i).GetName(), bt);
			}
			tb->SetToolTextOrientation(wxAUI_TBTOOL_TEXT_RIGHT);
			tb->Realize();
			//delete tb;
		}
	}
		

	//BuildEncodingMenu(view);
	int ec = (int)m_gopt->GetCurEncoding();
	//wxMenuBar* bar1 = GetMenuBar();
	wxMenuItem* item;
	switch(ec)
	{
		
		case wxFONTENCODING_SYSTEM:
			item = bar->FindItem(ID_CHARENCODING);
			item->Check();
		break;
		case wxFONTENCODING_UTF8:
			item = bar->FindItem(ID_CHARENCODING+1);
			item->Check();
		break;
		case wxFONTENCODING_ISO8859_1:
			item = bar->FindItem(ID_CHARENCODING+2);
			item->Check();
		break;
		case wxFONTENCODING_ISO8859_15:
			item = bar->FindItem(ID_CHARENCODING+3);
			item->Check();
		break;
		case wxFONTENCODING_ISO8859_7:
			item = bar->FindItem(ID_CHARENCODING+4);
			item->Check();
		break;
		case wxFONTENCODING_CP1253:
			item = bar->FindItem(ID_CHARENCODING+5);
			item->Check();
		break;
		case wxFONTENCODING_KOI8:
			item = bar->FindItem(ID_CHARENCODING+6);
			item->Check();
		break;
		case wxFONTENCODING_KOI8_U:
			item = bar->FindItem(ID_CHARENCODING+7);
			item->Check();
		break;
		case wxFONTENCODING_ISO8859_5:
			item = bar->FindItem(ID_CHARENCODING+8);
			item->Check();
		break;
		case wxFONTENCODING_CP1251:
			item = bar->FindItem(ID_CHARENCODING+9);
			item->Check();
		break;
		case wxFONTENCODING_BIG5:
			item = bar->FindItem(ID_CHARENCODING+10);
			item->Check();
		break;
		case wxFONTENCODING_CP936:
			item = bar->FindItem(ID_CHARENCODING+11);
			item->Check();
		break;
		case wxFONTENCODING_SHIFT_JIS:
			item = bar->FindItem(ID_CHARENCODING+12);
			item->Check();
		break;
		case wxFONTENCODING_ISO2022_JP:
			item = bar->FindItem(ID_CHARENCODING+13);
			item->Check();
		break;
		case wxFONTENCODING_EUC_JP:
			item = bar->FindItem(ID_CHARENCODING+14);
			item->Check();
		break;
	}
	aL->GetGlobal("amc_mainwindows");
	len = aL->GetObjectLen();
	aL->Pop(1);
	for (int i = 0; i < len; i++)
	{
		aL->GetField(-1, "amcinput");
		f = aL->GetUTF8String(-1);
		wxAuiPaneInfo pane;
		m_mgr.LoadPaneInfo(f, pane);
		m_mgr.AddPane(m_input, pane);
		aL->GetField(-2, "amcmain");
		f = aL->GetUTF8String(-1);
		
		m_mgr.LoadPaneInfo(f, pane);
		m_mgr.AddPane(m_child, pane);
		aL->GetField(-3, "amcsplitter");
		f = aL->GetUTF8String(-1);
		
		m_mgr.LoadPaneInfo(f, pane);
		m_mgr.AddPane(m_splitter, pane);
		aL->GetField(-4, "amctoggle");
		f = aL->GetUTF8String(-1);
		
		m_mgr.LoadPaneInfo(f, pane);
		m_mgr.AddPane(m_toggle, pane);
		aL->GetField(-7, "amctoolbar");
		f = aL->GetUTF8String(-1);
		
		m_mgr.LoadPaneInfo(f, pane);
		m_mgr.AddPane(m_toolbar, pane);
		aL->GetField(-6, "amcmultinb");
		f = aL->GetUTF8String(-1);
		
		m_mgr.LoadPaneInfo(f, pane);
		m_mgr.AddPane(m_notebook, pane);
		aL->GetField(-5, "amcmedia");
		f = aL->GetUTF8String(-1);
		
		m_mgr.LoadPaneInfo(f, pane);
		m_mgr.AddPane(m_media, pane);
		aL->GetField(-8, "amcprompt");
		f = aL->GetUTF8String(-1);

		m_mgr.LoadPaneInfo(f, pane);
		m_mgr.AddPane(m_prompt, pane);
	}
	
	aL->GetGlobal("amc_layout");
	wxString p = aL->GetUTF8String(-1);
	aL->Pop(1);
	//m_mgr.LoadPerspective(p);
	m_mgr.GetPane("amcmain").Show();
	m_mgr.GetPane("amcmultinb").Hide();
	m_mgr.Update();
	if (firsttime)
	{
		for (size_t i = 0; i < GetPanes()->size(); i++)
		{
			view->InsertCheckItem(i + 1, ID_USERWINDOW + i, GetPanes()->at(i));
		}

		int items1 = view->GetMenuItemCount() - 1;
		
		for (size_t i = 0; i < GetNbs()->size(); i++)
			view->InsertCheckItem(i + items1 - 1, ID_USERWINDOW + items1 + i, GetNbs()->at(i));

		int items2 = view->GetMenuItemCount() - 1;
		for (size_t i = 0; i < GetGaugePanes()->size(); i++)
			view->InsertCheckItem(i + items2 - 1, ID_USERWINDOW + items2 + i, GetGaugePanes()->at(i));

		for (size_t i = 0; i < GetPanes()->size(); i++)
		{
			if (m_mgr.GetPane(GetPanes()->at(i)).IsShown())
				view->Check(ID_USERWINDOW + i, true);
		}
		for (size_t i = 0; i < GetNbs()->size(); i++)
		{
			if (m_mgr.GetPane(GetNbs()->at(i)).IsShown())
				view->Check(ID_USERWINDOW + items1 + i, true);
		}
		for (size_t i = 0; i < GetGaugePanes()->size(); i++)
		{
			if (m_mgr.GetPane(GetGaugePanes()->at(i)).IsShown())
				view->Check(ID_USERWINDOW + items2 + i, true);
		}
		int items3 = view->GetMenuItemCount() - 1;
		
		for (size_t i = 0; i < GetAmcWindows()->size(); i++)
		{
			view->InsertCheckItem(i + items3 - 1, ID_AMCUSERWINDOW + i, GetAmcWindows()->at(i));
		}
		for (size_t i = 0; i < GetAmcWindows()->size(); i++)
		{
			if (m_mgr.GetPane(GetAmcWindows()->at(i)).IsShown())
				view->Check(ID_AMCUSERWINDOW + i, true);
		}

		
	}//end firsttime
	//m_child->Msg(wxString::Format(_("Loaded profile %s (%d actions, %d alias, %d hotkeys, %d vars, %d lists, %d timers, %d buttons)."), s.GetFullName().c_str(), m_trigger.size(), m_alias.size(), m_hotkeys.size(), m_vars.size(), m_lists.size(), m_timers.size(), m_buttons.size()));
	m_curprofile = s.GetFullPath();
	m_actwindow->SetProfile(s.GetFullPath());

	m_actwindow->SetTriggers(m_trigger);
	m_actwindow->SetAlias(m_alias);
	m_actwindow->SetVars(m_vars);
	m_actwindow->SetHotkeys(m_hotkeys);
	m_actwindow->SetLists(m_lists);
	m_actwindow->SetTimers(m_timers);
	m_actwindow->SetButtons(m_buttons);
	m_actwindow->SetPackages(m_packages);
	
	if (firsttime)
		{
		m_actwindow->SetGaugePanes(m_gaugepanes);
		m_actwindow->SetGauges(m_gauges);
		
		m_actwindow->SetPanes(m_panes);
		m_actwindow->SetNbs(m_nbs);
		m_actwindow->SetNbPanes(m_nbpanes);
		m_actwindow->SetAmcWindows(m_amcwindows);
		m_actwindow->SetUserWindows(uw);
		}
	m_input->SetFocus();
	luaBuildalias();
	luaBuildtrigger();
	luaBuildvar();
	luaBuilddefvar();
	return true;
}

void MudMainFrame::luaBuildtrigger()
{
size_t i;
	amcLua *aL = m_actwindow->GetLState();
	struct lua_State *L = aL->GetLuaState();
	wxCSConv co(GetGlobalOptions()->GetCurEncoding());
	lua_settop(L,0);
	lua_newtable(L);

	for (i=0;i<m_actwindow->GetTrigger()->size();i++)
	{
		lua_pushstring(L, m_actwindow->GetTrigger()->at(i).GetLabel().mb_str(co).data());// .mb_str());
		//lua_setfield(L, -1, GetTrigger()->at(i).GetLabel());
		lua_newtable(L);
		lua_pushstring(L, m_actwindow->GetTrigger()->at(i).GetPattern().mb_str(co).data());
		lua_setfield(L, -2, "pattern");
		lua_pushstring(L, m_actwindow->GetTrigger()->at(i).GetAction().mb_str(co).data());// .mb_str());
		lua_setfield(L, -2, "action");
		lua_pushstring(L, m_actwindow->GetTrigger()->at(i).GetClass().mb_str(co).data());// .mb_str());
		lua_setfield(L, -2, "group");
		lua_pushboolean(L, m_actwindow->GetTrigger()->at(i).IsActive());
		lua_setfield(L, -2, "on");
		lua_pushinteger(L, m_actwindow->GetTrigger()->at(i).GetPriority());
		lua_setfield(L, -2, "priority");
		lua_pushinteger(L, m_actwindow->GetTrigger()->at(i).GetColMatch());
		lua_setfield(L, -2, "colmatch");
		lua_pushinteger(L, m_actwindow->GetTrigger()->at(i).GetLines());
		lua_setfield(L, -2, "lines");
		lua_pushinteger(L, m_actwindow->GetTrigger()->at(i).GetMatchCount());
		lua_setfield(L, -2, "matchcount");
		lua_pushboolean(L, m_actwindow->GetTrigger()->at(i).GetSendScript());
		lua_setfield(L, -2, "script");
		lua_settable(L,-3);

	}
	//register this as table in global namespace wxamcl
	lua_setglobal(L, "_amctrigger");
	lua_getglobal(L, "wxamcl"); //5.1.4
	lua_getglobal(L, "_amctrigger");
	lua_setfield(L, -2, "Action"); //5.1.4
	//lua_setfield(L, -1, "Action");
	lua_settop(L,0);
	
	lua_getglobal(L, "_amctrigger");
	lua_newtable(L);
	lua_setmetatable(L,-2);
	lua_getglobal(L, "_amctrigger");
	lua_getmetatable(L,-1);
	lua_pushstring(L, "__newindex");
	lua_pushcfunction(L, luafunc_newaction);
	lua_settable(L, -3);
	lua_settop(L, 0);
	lua_getglobal(L, "_amctrigger");
	lua_getmetatable(L, -1);
	lua_pushstring(L, "__index");
	lua_pushcfunction(L, luafunc_getaction);
	lua_settable(L, -3);
	
	lua_settop(L,0);
	return;
}

void MudMainFrame::luaBuildalias()
{
size_t i;
	amcLua *aL = m_actwindow->GetLState();
	struct lua_State *L = aL->GetLuaState();
	wxCSConv co(GetGlobalOptions()->GetCurEncoding());
	lua_settop(L,0);
	lua_newtable(L);

	for (i=0;i<m_actwindow->GetAlias()->size();i++)
	{
		lua_pushstring(L, m_actwindow->GetAlias()->at(i).GetName().mb_str(co).data());// .mb_str());
		lua_newtable(L);
		lua_pushstring(L, m_actwindow->GetAlias()->at(i).GetAction().mb_str(co).data());// .mb_str());
		lua_setfield(L, -2, "action");
		lua_pushstring(L, m_actwindow->GetAlias()->at(i).GetGroup().mb_str(co).data());//.mb_str());
		lua_setfield(L, -2, "group");
		lua_pushboolean(L, m_actwindow->GetAlias()->at(i).IsActive());
		lua_setfield(L, -2, "on");
		lua_settable(L,-3);

	}
	//register this as table in global namespace wxamcl
	lua_setglobal(L, "_amcalias");
	lua_getglobal(L, "wxamcl"); //5.1.4
	lua_getglobal(L, "_amcalias");
	lua_setfield(L, -2, "Alias"); //5.1.4
	lua_settop(L,0);
	
	lua_getglobal(L, "_amcalias");
	lua_newtable(L);
	lua_setmetatable(L,-2);
	lua_getglobal(L, "_amcalias");
	lua_getmetatable(L,-1);
	lua_pushstring(L, "__newindex");
	lua_pushcfunction(L, luafunc_newalias1);
	lua_settable(L, -3);
	lua_settop(L,0);
	lua_getglobal(L, "_amcalias");
	lua_getmetatable(L,-1);
	lua_pushstring(L, "__index");
	lua_pushcfunction(L, luafunc_getalias);
	lua_settable(L, -3);
	lua_settop(L,0);
	return;
}

void MudMainFrame::luaBuildvar()
{
size_t i;
	amcLua *aL = m_actwindow->GetLState();
	struct lua_State *L = aL->GetLuaState();
	wxCSConv co(GetGlobalOptions()->GetCurEncoding());
	lua_settop(L,0);
	lua_newtable(L);

	for (i=0;i<m_actwindow->GetVars()->size();i++)
	{
		lua_pushstring(L, m_actwindow->GetVars()->at(i).GetName().mb_str(co).data());// .mb_str());
		lua_newtable(L);
		lua_pushstring(L, m_actwindow->GetVars()->at(i).GetValue().mb_str(co).data());// .mb_str());
		lua_setfield(L, -2, "value");
		lua_pushstring(L, m_actwindow->GetVars()->at(i).GetGroup().mb_str(co).data());// .mb_str());
		lua_setfield(L, -2, "group");
		lua_pushboolean(L, m_actwindow->GetVars()->at(i).IsActive());
		lua_setfield(L, -2, "on");
		lua_settable(L,-3);
	}
	//register this as table in global namespace wxamcl
	lua_setglobal(L, "_amcvariables");
	lua_getglobal(L, "wxamcl"); //5.1.4
	lua_getglobal(L, "_amcvariables");
	lua_setfield(L, -2, "Vars"); // 5.2.0
	lua_settop(L,0);
	
	lua_getglobal(L, "_amcvariables");
	lua_newtable(L);
	lua_setmetatable(L,-2);
	lua_getglobal(L, "_amcvariables");
	lua_getmetatable(L,-1);
	lua_pushstring(L, "__newindex");
	lua_pushcfunction(L, luafunc_newvar);
	lua_settable(L, -3);
	lua_settop(L,0);
	lua_getglobal(L, "_amcvariables");
	lua_getmetatable(L,-1);
	lua_pushstring(L, "__index");
	lua_pushcfunction(L, luafunc_getvar);
	lua_settable(L, -3);
	lua_settop(L,0);
	return;
}

void MudMainFrame::luaBuilddefvar()
{
size_t i;
	amcLua *aL = m_actwindow->GetLState();
	struct lua_State *L = aL->GetLuaState();
	wxCSConv co(GetGlobalOptions()->GetCurEncoding());
	lua_settop(L, 0);
	lua_newtable(L);
	wxString s, ss;
	for (i = 0; i<m_actwindow->GetDefVars()->size(); i++)
	{
		lua_pushstring(L, m_actwindow->GetDefVars()->at(i).GetName().mb_str(co).data());// .mb_str());
		lua_newtable(L);
		s = m_actwindow->GetDefVars()->at(i).GetValue().mb_str(co).data();
		lua_pushstring(L, m_actwindow->GetDefVars()->at(i).GetValue().mb_str(co).data());// .mb_str());
		ss = m_actwindow->GetDefVars()->at(i).GetName().mb_str(co).data();
		lua_setfield(L, -2, "value");
		lua_settable(L, -3);
		wxString deb;

		deb << "Name: (DefVar)" << ss << " Value: " << s;
		wxLogDebug(deb);
	}
	//register this as table in global namespace wxamcl
	lua_setglobal(L, "_amcdefvariables");
	lua_getglobal(L, "wxamcl"); //5.1.4
	lua_getglobal(L, "_amcdefvariables");
	lua_setfield(L, -2, "ClientVars"); // 5.2.0
	lua_settop(L, 0);

	

	/*lua_getglobal(L, "_amcdefvariables");
	lua_newtable(L);
	lua_setmetatable(L, -2);
	lua_getglobal(L, "_amcdefvariables");
	lua_getmetatable(L, -1);
	lua_pushstring(L, "__newindex");
	lua_pushcfunction(L, luafunc_newvar);
	lua_settable(L, -3);
	lua_settop(L, 0);
	lua_getglobal(L, "_amcdefvariables");
	lua_getmetatable(L, -1);
	lua_pushstring(L, "__index");
	lua_pushcfunction(L, luafunc_getvar);
	lua_settable(L, -3);
	lua_settop(L, 0);*/
	return;
}

void MudMainFrame::luaCreateATCPTable()
{
	amcLua *aL = m_actwindow->GetLState();
	struct lua_State *L = aL->GetLuaState();

	lua_settop(L,0);
	lua_newtable(L);
	lua_pushstring(L, "");
	lua_setfield(L, -2, "RoomNum");
	lua_pushstring(L, "");
	lua_setfield(L, -2, "RoomBrief");
	
	//lua_settable(L, -3);
	//register this as table in global namespace amc
	lua_setglobal(L, "_amcATCP");
	lua_getglobal(L, "wxamcl");
	lua_getglobal(L, "_amcATCP");
	lua_setfield(L, -2, "ATCP");
	lua_settop(L,0);
	return;
}

void MudMainFrame::luaCreateGMCPTable()
{
	amcLua *aL = m_actwindow->GetLState();
	struct lua_State *L = aL->GetLuaState();

	lua_settop(L,0);
	lua_newtable(L);
	/*lua_pushstring(L, "");
	lua_setfield(L, -2, "num");
	lua_pushstring(L, "");
	lua_setfield(L, -2, "name");*/
	
	//lua_settable(L, -3);
	//register this as table in global namespace amc
	lua_setglobal(L, "_amcGMCP");
	lua_getglobal(L, "wxamcl");
	lua_getglobal(L, "_amcGMCP");
	lua_setfield(L, -2, "GMCP");
	lua_settop(L,0);
	return;
}

void MudMainFrame::luaCreateMSDPTable()
{
	amcLua *aL = m_actwindow->GetLState();
	struct lua_State *L = aL->GetLuaState();

	lua_settop(L,0);
	lua_newtable(L);
	/*lua_pushstring(L, "");
	lua_setfield(L, -2, "num");
	lua_pushstring(L, "");
	lua_setfield(L, -2, "name");*/
	
	//lua_settable(L, -3);
	//register this as table in global namespace amc
	lua_setglobal(L, "_amcMSDP");
	lua_getglobal(L, "wxamcl");
	lua_getglobal(L, "_amcMSDP");
	lua_setfield(L, -2, "MSDP");
	lua_settop(L,0);
	return;
}
bool MudMainFrame::SaveHosts()
{
host_it it;

	wxSetWorkingDirectory(GetGlobalOptions()->GetWorkDir());
	::wxRemoveFile(("hosts.lua"));
	wxFile *file = new wxFile(("hosts.lua"), wxFile::write);
    if (!file->IsOpened())
		return false;
	file->Write(("\n\t-- hosts file for wxAmcl\n\n\tamc_hosts = {\n"));
	for (it=GetHosts()->begin(); it!=GetHosts()->end();it++)
	{
		file->Write(wxString::Format("\t\t{[\"char\"] = [[%s]], ", it->GetCharName().c_str()));
		wxString s = it->GetPwd();
		wxString s64 = wxBase64Encode(s.data(), s.length());
		wxChar c = 0x1b;
		for (size_t i=0; i<s.length(); i++)
		{
			wxChar cc = (wxChar)s[i];
			cc ^= c++;
			s[i] = cc;
		}
			file->Write(wxString::Format("[\"pwd\"] = [=[%s]=], ", s.c_str()));
		file->Write(wxString::Format("[\"mud\"] = [[%s]], ", it->GetMudName().c_str()));
		file->Write(wxString::Format("[\"host\"] = [[%s]], ", it->GetHostName().c_str()));
		file->Write(wxString::Format("[\"port\"] = [[%s]], ", it->GetPort().c_str()));
		file->Write(wxString::Format("[\"ip\"] = [[%s]], ", it->GetIPString().c_str()));
		file->Write(wxString::Format("[\"profile\"] = [[%s]],", it->GetProfileFile().c_str()));
		file->Write(wxString::Format("[\"pwd2\"] = [=[%s]=] },\n ", s64.c_str()));
	}
	file->Write("\t}");
	file->Close();
	delete file;
	return true;
}

bool MudMainFrame::LoadHosts()
{
	amcLua *aL = m_child->GetLState();
	struct lua_State *L = aL->GetLuaState();
	int err=0;
	wxString s;
	const char* error;
	wxSetWorkingDirectory(GetGlobalOptions()->GetWorkDir());
	if ((err=m_child->GetLState()->DoFile("hosts.lua")))
	{
		int top = lua_gettop(L);
		error = luaL_checkstring(L, top);
		m_child->Msg(error);
		return false;
	}

	aL->GetGlobal("amc_hosts");
	int len = aL->GetObjectLen();
	aL->Pop(1);
	for (int i=0; i<len; i++)
	{
		amchost ahost;
		aL->GetGlobal("amc_hosts");
		aL->PushInt(i+1);
		aL->GetTable(-2);
		aL->GetField(-1, "char");
		ahost.SetCharName(aL->GetwxString(-1));
		aL->GetField(-2, "pwd");
		wxString s = aL->GetwxString(-1);
		wxChar c = 0x1b;
		for(size_t i=0;i<s.length();i++)
		{
			wxChar cc = (wxChar)s[i];
			cc ^= c++;
			s[i] = cc;
		}
		ahost.SetPwd(s);
		aL->GetField(-3, "mud");
		ahost.SetMudName(aL->GetwxString(-1));
		aL->GetField(-4, "host");
		ahost.SetHostName(aL->GetwxString(-1));
		aL->GetField(-5, "port");
		ahost.SetPort((long)aL->GetInt(-1));
		aL->GetField(-6, "ip");
		ahost.SetIPAddr(aL->GetwxString(-1));
		aL->GetField(-7, "profile");
		ahost.SetProfileFile(aL->GetwxString(-1));
		aL->GetField(-8, "pwd2");
		wxString s64 = aL->GetwxString(-1);
		size_t z = wxBase64DecodedSize(s64.length());
		wxMemoryBuffer mBuf(z);
		mBuf = wxBase64Decode(s64.data(), s64.length());
		wxString sss(mBuf, mBuf.GetDataLen());
		
		aL->SetTop(0);
		m_amchost.push_back(ahost);
	}
	return true;
}

int MudMainFrame::GetTriggerIndexByLabel(wxString s)
{
tr_it it;
int i;

	for (it = m_trigger.begin(), i=0; it!=m_trigger.end(); it++, i++)
	{
		if (!s.compare(it->GetLabel()))
			return i;
	}
	return -1;
}

int MudMainFrame::GetAliasIndexByLabel(wxString s)
{
al_it it;
int i;
	if (s.at(0)!=('^'))
		s = ('^') + s;
	//if (!s.EndsWith(("$")))
	//	s.append(('$'));
	for (it = m_alias.begin(), i=0; it!=m_alias.end(); it++, i++)
	{
		if (!s.compare(0,s.length(), it->GetAlias(), 0, s.length()))
			return i;
	}
	return -1;
}

int MudMainFrame::GetVarIndexByLabel(wxString s)
{
v_it it;
int i;

	for (it = m_vars.begin(), i=0; it!=m_vars.end(); it++, i++)
	{
		if (!s.compare(it->GetName()))
			return i;
	}
	return -1;
}

int MudMainFrame::GetDefVarIndexByLabel(wxString s)
{
dv_it it;
int i;

	for (it = m_defvars.begin(), i=0; it!=m_defvars.end(); it++, i++)
	{
		if (!s.compare(it->GetName()))
			return i;
	}
	return -1;
}

int MudMainFrame::GetListIndexByLabel(wxString s)
{
li_it it;
int i;

	for (it = m_lists.begin(), i=0; it!=m_lists.end(); it++, i++)
	{
		if (!s.compare(it->GetName()))
			return i;
	}
	return -1;
}

int MudMainFrame::GetTimerIndexByLabel(wxString s)
{
t_it it;
int i;

	for (it = m_timers.begin(), i=0; it!=m_timers.end(); it++, i++)
	{
		if (!s.compare(it->GetName()))
			return i;
	}
	return -1;
}

int MudMainFrame::GetButtonIndexByLabel(wxString s)
{
b_it it;
int i;

	for (it = m_buttons.begin(), i=0; it!=m_buttons.end(); it++, i++)
	{
		if (!s.compare(it->GetName()))
			return i;
	}
	return -1;
}

int MudMainFrame::GetButtonIndexById(int id)
{
b_it it;
int i;

	for (it = m_buttons.begin(), i=0; it!=m_buttons.end(); it++, i++)
	{
		if (id == it->GetId())
			return i;
	}
	return -1;
}

int MudMainFrame::GetHkIndexByLabel(wxString s)
{
hk_it it;
int i;

	for (it = m_hotkeys.begin(), i=0; it!=m_hotkeys.end(); it++, i++)
	{
		if (!s.compare(it->GetName()))
			return i;
	}
	return -1;
}

void MudMainFrame::OnMediaLoaded(wxMediaEvent& WXUNUSED(evt))
{
	m_media->Play();
}

void MudMainFrame::OnMediaFinished(wxMediaEvent& WXUNUSED(evt))
{
	
	if (m_mgr.GetPane("amcmedia").IsShown())
	{
		m_mgr.GetPane("amcmedia").Hide();
		m_mgr.Update();
	}
}

void MudMainFrame::OnNPageChanged(wxAuiNotebookEvent& event)
{
	
	if (event.GetOldSelection() == -1)
		return;
	if (event.GetOldSelection() == event.GetSelection())
		return;
	
	m_actwindow = wxGetApp().GetFrame()->m_childwindows.at(event.GetOldSelection());
	DeleteWindows();
	m_actwindow = m_scriptwin = wxGetApp().GetFrame()->m_childwindows.at(event.GetSelection());
	m_actwindow->SetParseState(29);//HAVE_TO_DELETE_SLINE
	CreateWindows();
	wxString s = m_actwindow->GetProfile();
	LoadProfile(s, false);
	//m_mgr.Update();
	m_mgr.GetPane(m_notebook).Show().Center().BestSize(900,500).Dock().CaptionVisible(false);
	m_mgr.Update();
	m_actwindow->Update();
	Update();
	unordered_map <wxString, wxWindow *> ummw;
	ummw = *m_actwindow->GetUserWindows();
	unordered_map<wxString, wxWindow*>::iterator uit;
	for (uit = ummw.begin(); uit != ummw.end(); uit++)
	{
		uit->second->Update();
	}
	wxMenuBar* bar = GetMenuBar();
	wxMenu* view = bar->GetMenu(bar->FindMenu(_("View")));
	for (size_t i = 0; i < m_actwindow->GetPanes()->size(); i++)
	{
		view->InsertCheckItem(i + 1, ID_USERWINDOW + i, m_actwindow->GetPanes()->at(i));

	}

	int items1 = view->GetMenuItemCount() - 1;
	for (size_t i = 0; i < m_actwindow->GetNbs()->size(); i++)
		view->InsertCheckItem(i + items1 - 1, ID_USERWINDOW + items1 + i, m_actwindow->GetNbs()->at(i));

	int items2 = view->GetMenuItemCount() - 1;
	for (size_t i = 0; i < m_actwindow->GetGaugePanes()->size(); i++)
		view->InsertCheckItem(i + items2 - 1, ID_USERWINDOW + items2 + i, m_actwindow->GetGaugePanes()->at(i));

	for (size_t i = 0; i < m_actwindow->GetPanes()->size(); i++)
	{
		if (m_mgr.GetPane(m_actwindow->GetPanes()->at(i)).IsShown())
			view->Check(ID_USERWINDOW + i, true);
	}
	for (size_t i = 0; i < m_actwindow->GetNbs()->size(); i++)
	{
		if (m_mgr.GetPane(m_actwindow->GetNbs()->at(i)).IsShown())
			view->Check(ID_USERWINDOW + items1 + i, true);
	}
	for (size_t i = 0; i < m_actwindow->GetGaugePanes()->size(); i++)
	{
		if (m_mgr.GetPane(m_actwindow->GetGaugePanes()->at(i)).IsShown())
			view->Check(ID_USERWINDOW + items2 + i, true);
	}
	int items3 = view->GetMenuItemCount() - 1;
	for (size_t i = 0; i < m_actwindow->GetAmcWindows()->size(); i++)
	{
		view->InsertCheckItem(i + items3 - 1, ID_AMCUSERWINDOW + i, m_actwindow->GetAmcWindows()->at(i));

	}
	for (size_t i = 0; i < m_actwindow->GetAmcWindows()->size(); i++)
	{
		if (m_mgr.GetPane(m_actwindow->GetAmcWindows()->at(i)).IsShown())
			view->Check(ID_AMCUSERWINDOW + i, true);

	}
	//event.Skip();
}

void MudMainFrame::OnNPageClose(wxAuiNotebookEvent& event)
{
	m_actwindow = m_scriptwin = wxGetApp().GetFrame()->m_childwindows.at(event.GetSelection());
	SaveProfile(m_actwindow->GetProfile());
	DeleteWindows();
	m_childwindows.erase(m_childwindows.begin() + event.GetSelection());
	
	m_active_window = m_childwindows.size();
}

void MudMainFrame::OnNPageClosed(wxAuiNotebookEvent& event)
{
	m_actwindow = m_scriptwin = m_childwindows.at(m_notebook->GetSelection());
	CreateWindows();
	LoadProfile(m_actwindow->GetProfile(), false);
	m_mgr.GetPane(m_notebook).Show().Center().BestSize(900, 500).Dock().CaptionVisible(false);
	m_mgr.Update();
	m_actwindow->Update();
	Update();
	unordered_map <wxString, wxWindow *> ummw;
	ummw = *m_actwindow->GetUserWindows();
	unordered_map<wxString, wxWindow*>::iterator uit;
	for (uit = ummw.begin(); uit != ummw.end(); uit++)
	{
		uit->second->Update();
	}
	wxMenuBar* bar = GetMenuBar();
	wxMenu* view = bar->GetMenu(bar->FindMenu(_("View")));
	for (size_t i = 0; i < m_actwindow->GetPanes()->size(); i++)
	{
		view->InsertCheckItem(i + 1, ID_USERWINDOW + i, m_actwindow->GetPanes()->at(i));

	}

	int items1 = view->GetMenuItemCount() - 1;
	for (size_t i = 0; i < m_actwindow->GetNbs()->size(); i++)
		view->InsertCheckItem(i + items1 - 1, ID_USERWINDOW + items1 + i, m_actwindow->GetNbs()->at(i));

	int items2 = view->GetMenuItemCount() - 1;
	for (size_t i = 0; i < m_actwindow->GetGaugePanes()->size(); i++)
		view->InsertCheckItem(i + items2 - 1, ID_USERWINDOW + items2 + i, m_actwindow->GetGaugePanes()->at(i));

	for (size_t i = 0; i < m_actwindow->GetPanes()->size(); i++)
	{
		if (m_mgr.GetPane(m_actwindow->GetPanes()->at(i)).IsShown())
			view->Check(ID_USERWINDOW + i, true);
	}
	for (size_t i = 0; i < m_actwindow->GetNbs()->size(); i++)
	{
		if (m_mgr.GetPane(m_actwindow->GetNbs()->at(i)).IsShown())
			view->Check(ID_USERWINDOW + items1 + i, true);
	}
	for (size_t i = 0; i < m_actwindow->GetGaugePanes()->size(); i++)
	{
		if (m_mgr.GetPane(m_actwindow->GetGaugePanes()->at(i)).IsShown())
			view->Check(ID_USERWINDOW + items2 + i, true);
	}
	int items3 = view->GetMenuItemCount() - 1;
	for (size_t i = 0; i < m_actwindow->GetAmcWindows()->size(); i++)
	{
		view->InsertCheckItem(i + items3 - 1, ID_AMCUSERWINDOW + i, m_actwindow->GetAmcWindows()->at(i));

	}
	for (size_t i = 0; i < m_actwindow->GetAmcWindows()->size(); i++)
	{
		if (m_mgr.GetPane(m_actwindow->GetAmcWindows()->at(i)).IsShown())
		view->Check(ID_AMCUSERWINDOW + i, true);

	}
}

void MudMainFrame::DeleteWindows()
{
	
unordered_map <wxString, wxWindow *> ummw;
ummw = *this->m_actwindow->GetUserWindows();
unordered_map<wxString, wxWindow*>::iterator uit;

	for (uit = ummw.begin(); uit != ummw.end(); uit++)
		{
			m_mgr.GetPane(uit->second).Hide();
			m_mgr.DetachPane(uit->second);
			uit->second->Hide();
		}

	m_mgr.Update();

	//Build Menu
	wxMenuBar* bar = GetMenuBar();
	wxMenu* view = bar->GetMenu(bar->FindMenu(_("View")));
	if (m_splitter->IsShown())
		view->Check(ID_SPLITTER, true);
	int ii = view->GetMenuItemCount();

	if (ii > 3)
	{
		for (size_t i = 0; i < m_actwindow->GetPanes()->size(); i++)
		{
			int b = view->FindItem(m_actwindow->GetPanes()->at(i));
			view->Destroy(b);
		}
		for (size_t i = 0; i < m_actwindow->GetNbs()->size(); i++)
		{
			view->Destroy(view->FindItem(m_actwindow->GetNbs()->at(i)));
		}
		for (size_t i = 0; i < m_actwindow->GetGaugePanes()->size(); i++)
		{
			view->Destroy(view->FindItem(m_actwindow->GetGaugePanes()->at(i)));
		}
		for (size_t i = 0; i < m_actwindow->GetAmcWindows()->size(); i++)
		{
			view->Destroy(view->FindItem(m_actwindow->GetAmcWindows()->at(i)));
		}
	}

}

void MudMainFrame::CreateWindows()
{
	unordered_map <wxString, wxWindow *> ummw;
	ummw = *this->m_actwindow->GetUserWindows();
	unordered_map<wxString, wxWindow*>::iterator uit;
	for (uit = ummw.begin(); uit != ummw.end(); uit++)
	{
		m_mgr.AddPane(uit->second, wxAuiPaneInfo().Name(uit->first).Caption(uit->first).Show().Top());
	}
	
}

//InputTextCtrl

InputTextCtrl::InputTextCtrl(wxWindow *parent, wxWindowID id, const wxString &value,
               const wxPoint &pos, const wxSize &size, int style)
        : wxTextCtrl(parent, id, value, pos, size, style)
{
	m_parent = (MudMainFrame*)parent;
	m_sComm["raw"] = &InputTextCtrl::CommRaw;
	m_sComm["connect"] = &InputTextCtrl::Connect;
    #if defined WXAMCL_USEIPV6
	m_sComm["connect6"] = &InputTextCtrl::Connect6;
    #endif
	m_sComm["pwd"] = &InputTextCtrl::Pwd;
	m_sComm["capturewin"] = &InputTextCtrl::CaptureWin;
	m_sComm["capturenb"] = &InputTextCtrl::CaptureNb;
	m_sComm["capstart"] = &InputTextCtrl::CapStart;
	m_sComm["capend"] = &InputTextCtrl::CapEnd;
	m_sComm["clearwin"] = &InputTextCtrl::ClearWin;
	m_sComm["refreshwin"] = &InputTextCtrl::RefreshWin;
	m_sComm["help"] = &InputTextCtrl::Help;
	m_sComm["gagwin"] = &InputTextCtrl::GagWin;
	m_sComm["gag"] = &InputTextCtrl::Gag;
	m_sComm["func"] = &InputTextCtrl::Func;
	m_sComm["setvar"] = &InputTextCtrl::SetVar;
	m_sComm["script"] = &InputTextCtrl::Script;
	//m_sComm[wxT("bscript")] = &InputTextCtrl::BScript;
	m_sComm["tscript"] = &InputTextCtrl::TScript;
	m_sComm["log"] = &InputTextCtrl::Log;
	m_sComm["htmllog"] = &InputTextCtrl::HtmlLog;
	m_sComm["test"] = &InputTextCtrl::Test;
	m_sComm["resume"] = &InputTextCtrl::Resume;
	m_sComm["loadprofile"] = &InputTextCtrl::LoadProfile;
	m_sComm["media"] = &InputTextCtrl::Media;
	m_sComm["mxp"] = &InputTextCtrl::Mxp;
	m_sComm["info"] = &InputTextCtrl::Info;
	m_sComm["debugGMCP"] = &InputTextCtrl::DebugGMCP;
	m_keepinput = true;
	m_parse = true;
	m_hpos = 0;
	LoadHistory();
	LoadTabText();
	m_tabsearch = wxEmptyString;
	m_tab = false;
	m_tabbox = true;
	m_lastcommand = wxEmptyString;
	m_waiting = false;
	m_sw.SetOwner(this->GetEventHandler(),2222);
	m_swsend = wxEmptyString;
	m_dclick = false;
}

void InputTextCtrl::OnTextEnter(wxCommandEvent &event)
{
 
}

void InputTextCtrl::OnIdle(wxIdleEvent &event)
{
	
		/*if (m_gotfocus)
		{
			SetSelection(-1, -1);
			m_gotfocus = false;
		}*/
	
	event.Skip();
}

void InputTextCtrl::OnSetFocus(wxFocusEvent &event)
{
#if defined __WXMSW__
	//wxLogDebug("OnSetFocus..Input Text");
	
	//SetSelection(-1, -1);
#endif
	/*if (m_keepinput)
		m_gotfocus = true;*/
	event.Skip();
}

void InputTextCtrl::OnMouseWheel(wxMouseEvent &event)
{
	MudWindow* sendto = m_parent->m_actwindow;
	
	if (m_parent->UseSplitter() && !m_parent->m_splitter->IsShown() && event.GetWheelRotation()>0)
		{
		m_parent->m_actwindow->Freeze();
		m_parent->m_splitter->SetLineBuffer(m_parent->m_actwindow->GetLines());
		m_parent->m_splitter->m_curline = m_parent->m_actwindow->m_curline;
		m_parent->m_mgr.GetPane("amcsplitter").Show();
		m_parent->m_mgr.Update();
		int line = m_parent->m_actwindow->m_curline-m_parent->m_actwindow->m_scrollrange;
		m_parent->m_splitter->SetScrollPage();
		m_parent->m_splitter->SetScrollPos(wxVERTICAL, line-m_parent->m_splitter->m_scrollrange);
		m_parent->m_splitter->Refresh();
		//m_parent->m_splitter->Update();
		m_parent->m_actwindow->Thaw();
		return;
		}
	if (m_parent->m_splitter->IsShown()&& m_parent->UseSplitter())
		sendto = m_parent->m_splitter;
	sendto->GetEventHandler()->ProcessEvent(event);
}

void InputTextCtrl::OnMouseLeftUp(wxMouseEvent &event)
{
	
	m_dclick = false;
	event.Skip();
}

void InputTextCtrl::OnMouseLeftDClick(wxMouseEvent &event)
{
	//SetSelection(-1, -1);
	SelectAll();
	
	m_dclick = true;
	//event.Skip();
}

void InputTextCtrl::OnKeyDown(wxKeyEvent &event)
{
	long keycode = event.GetKeyCode();
	int mods = event.GetModifiers();
	hk_it iter;
	wxScrollWinEvent newevt;
	MudWindow *sendto;

	newevt.SetPosition(0);
	newevt.SetOrientation(wxVERTICAL);
	if (m_parent->m_splitter->IsShown())
		sendto = m_parent->m_splitter;
	else
		sendto = m_parent->m_actwindow;
	
	if (m_dclick)
	{
		Clear();
		m_dclick = false;
	}
	MudMainFrame* frame = (MudMainFrame*)GetParent();
	//check if this is an hotkey combo
	for (iter = frame->m_actwindow->GetHotkeys()->begin(); iter!= frame->m_actwindow->GetHotkeys()->end(); iter++)
	{
		if (keycode == iter->GetHotkey() && mods == iter->GetModifier())
		{
			if (iter->IsActive())
			{
				Parse(iter->GetAction());
			}
			return;
		}
	}
	if (keycode==WXK_RETURN)
		m_lastcommand = GetRange(0, GetLastPosition());
#ifdef __WXOSX__
    if (keycode==WXK_UP)
    {
        if (m_hpos<=0)
            m_hpos = 0;
        Clear();
        if (!m_history.empty())
            WriteText(m_history.at(m_hpos));
        m_hpos--;
    }
    if (keycode==WXK_DOWN)
    {
	
		m_hpos++;
        if (m_hpos>= (int)m_history.size()-1)
            m_hpos = (int)m_history.size()-1;
        Clear();
        if (!m_history.empty())
            WriteText(m_history.at(m_hpos));
    }
	if (keycode == WXK_UP && mods == wxMOD_CONTROL)
	{
		newevt.SetEventType(wxEVT_SCROLLWIN_PAGEUP);
		if (m_parent->UseSplitter() && !m_parent->m_splitter->IsShown())
		{
			wxWindowUpdateLocker noUpdates(m_parent);
			m_parent->m_actwindow->Freeze();
			m_parent->m_splitter->Freeze();
			m_parent->m_splitter->SetLineBuffer(m_parent->m_actwindow->GetLines());
			m_parent->m_splitter->m_curline = m_parent->m_actwindow->m_curline;
			m_parent->m_mgr.GetPane("amcsplitter").Show();

			int line = m_parent->m_actwindow->m_curline - m_parent->m_actwindow->m_scrollrange;
			m_parent->m_splitter->SetScrollPage();
			m_parent->m_splitter->SetScrollPos(wxVERTICAL, line - m_parent->m_splitter->m_scrollrange);
			m_parent->m_splitter->Refresh();
			m_parent->m_splitter->Thaw();
			m_parent->m_actwindow->Thaw();
			m_parent->m_mgr.Update();
			return;
		}
		sendto->SetKEvtForwarded(true);
		sendto->GetEventHandler()->ProcessEvent(newevt);
		return;
	}
	if (keycode == WXK_DOWN && mods == wxMOD_CONTROL)
	{
		sendto->SetKEvtForwarded(true);
		newevt.SetEventType(wxEVT_SCROLLWIN_PAGEDOWN);
		sendto->GetEventHandler()->ProcessEvent(newevt);
		return;
	}
    #endif
	event.Skip();
}

void InputTextCtrl::OnText(wxCommandEvent &event)
{
	if (!m_tab)
		m_tabsearch = GetLineText(GetNumberOfLines()-1);
}

void InputTextCtrl::OnChar(wxKeyEvent &event)
{
wxString command("", wxConvLibc);
int keycode;
wxScrollWinEvent newevt;
MudWindow *sendto;
//static bool boFirst = true;

	newevt.SetPosition(0);
	newevt.SetOrientation(wxVERTICAL);
	if (m_parent->m_splitter->IsShown())
		sendto = m_parent->m_splitter;
	else
		sendto = m_parent->m_actwindow;

	newevt.SetEventObject(sendto);//forward scroll events

	keycode = event.GetKeyCode();
	switch (keycode)
		{
#ifndef __WXOSX__	
	case WXK_UP:

			if (m_hpos<=0)
				m_hpos = 0;
			Clear();
			if (!m_history.empty())
				WriteText(m_history.at(m_hpos));
			m_hpos--;
			break;
		case WXK_DOWN:
			m_hpos++;
			if (m_hpos>= (int)m_history.size()-1)
				m_hpos = (int)m_history.size()-1;
			Clear();
			if (!m_history.empty())
				WriteText(m_history.at(m_hpos));
			break;
#endif
		case WXK_PAGEUP:
            
			newevt.SetEventType(wxEVT_SCROLLWIN_PAGEUP);
			if (m_parent->UseSplitter() && !m_parent->m_splitter->IsShown())
			{
                wxWindowUpdateLocker noUpdates(m_parent);
				m_parent->m_actwindow->Freeze();
                m_parent->m_splitter->Freeze();
				m_parent->m_splitter->SetLineBuffer(m_parent->m_actwindow->GetLines());
				m_parent->m_splitter->m_curline = m_parent->m_actwindow->m_curline;
				m_parent->m_mgr.GetPane("amcsplitter").Show();
				
				int line = m_parent->m_actwindow->m_curline-m_parent->m_actwindow->m_scrollrange;
				m_parent->m_splitter->SetScrollPage();
				m_parent->m_splitter->SetScrollPos(wxVERTICAL, line-m_parent->m_splitter->m_scrollrange);
				m_parent->m_splitter->Refresh();
				m_parent->m_splitter->Thaw();
				m_parent->m_actwindow->Thaw();
                m_parent->m_mgr.Update();
				return;
			}
			sendto->SetKEvtForwarded(true);
			sendto->GetEventHandler()->ProcessEvent(newevt);
			return;
		case WXK_PAGEDOWN:
            sendto->SetKEvtForwarded(true);
			newevt.SetEventType(wxEVT_SCROLLWIN_PAGEDOWN);
			sendto->GetEventHandler()->ProcessEvent(newevt);
			return;
		case WXK_HOME:
            sendto->SetKEvtForwarded(true);
			newevt.SetEventType(wxEVT_SCROLLWIN_TOP);
			sendto->GetEventHandler()->ProcessEvent(newevt);
			return;
		case WXK_END:
			if (m_parent->m_splitter->IsShown())
			{
				wxWindowUpdateLocker noUpdates(m_parent);
                m_parent->m_actwindow->Freeze();
                m_parent->m_splitter->Freeze();
				m_parent->m_mgr.GetPane("amcsplitter").Hide();
				//m_parent->m_splitter->GetLineBuffer().empty();
				//m_parent->m_mgr.GetPane(wxT("amcmain")).Hide();
				
				m_parent->m_actwindow->Thaw();
                m_parent->m_splitter->Thaw();
                m_parent->m_mgr.Update();
				return;
			}
			sendto->SetKEvtForwarded(true);
            newevt.SetEventType(wxEVT_SCROLLWIN_BOTTOM);
			sendto->GetEventHandler()->ProcessEvent(newevt);
			return;
        }
	if (keycode==WXK_TAB) //TabCompletion
	{
		wxArrayString choices;
		wxString r;
		int c=0, idx=-1;
		m_tab = true;
		wxString s = m_tabsearch;
		if (m_tabbox)
		{
			do 
			{
				r=Complete();
				if (choices.Index(r)==wxNOT_FOUND)
					choices.Add(r);
				c++;
			} while (r.compare(wxEmptyString));
			choices.Remove("");
			choices.Sort();
			if (c>1)
				idx = wxGetSingleChoiceIndex(_("Choose"), _("TabCompletion"), choices);
		//Clear();
		//ChangeValue(Complete());
			if (idx!=-1)
				ChangeValue(choices[idx]);
		}
		else
			ChangeValue(Complete());
		SetInsertionPointEnd();
		m_tabsearch = s;
		m_tab = false;
		return;
	}
	
	
	if (keycode==WXK_RETURN && event.GetModifiers()==wxMOD_NONE)
	{
		ChangeValue(m_lastcommand);
		command = GetRange(0, GetLastPosition());
        wxString test = GetValue();
		command.Trim();
		Parse(command);
		if (!m_keepinput)
			Clear();
		else
		{
			Clear();
			ChangeValue(command);
		}
		//SetSelection(GetLastPosition()+1, 0);
		//SetInsertionPoint(GetLastPosition());
		#ifndef __WXOSX__
		//SetSelection(0,GetLastPosition()+1);
		SelectAll();
        //SetSelection(-1,-1);
		#endif
		#ifdef __WXOSX__
		SetSelection(-1,-1);
		#endif
		if (!m_parent->m_actwindow->GetScroll())
		 	m_parent->Refresh();

		if (!m_history.empty())
		{
			if (m_history.size()-1>m_parent->GetGlobalOptions()->GetMaxHist())
			{
				m_history.erase(m_history.begin());
				m_hpos--;
			}
		}
		SaveHistory();
	}
	else
	{
		event.Skip();
	}
}

void InputTextCtrl::Parse(wxString command, bool echo, bool history)
{
	
	if (command=="")
	{
		//command.append(CR);
		command.Append((char)CR);
		command.append((char)LF);
		m_parent->m_actwindow->Write(command);
		//m_parent->m_child->Write(command);
		m_parent->Refresh();
		m_parent->m_actwindow->ParseNBuffer((char*)" \n", false);
		//m_parent->m_child->ParseNBuffer((char*)" \n", false);
		return;
	}
	wxString token = m_parent->GetGlobalOptions()->GetSep();
	token.append("\n");
	wxStringTokenizer tkz(command, token);//m_parent->GetGlobalOptions()->GetSep());
	if (m_parse)
	{
		while ( tkz.HasMoreTokens() )
		{
			wxString comm = tkz.GetNextToken();
			if (comm.empty())
				continue;
			if (!m_parent->m_actwindow->GetPW())//m_parent->m_child->GetPW())
			{
				//do not print #commands
				if (comm.at(0)!=m_parent->GetGlobalOptions()->GetCommand()&&comm.at(0)!=m_parent->GetGlobalOptions()->GetScript())
				{
					if (m_parent->GetGlobalOptions()->GetEcho() && echo)
					{
						bool p = m_parent->TriggersOn();
						m_parent->SetTriggersOn(false);
						ParseVars(&comm);
						ParseLists(&comm);
						//wxString out1 = comm.mb_str(wxCSConv(m_parent->GetGlobalOptions()->GetCurEncoding())).data();
						wxString out1 = comm;
						wxString out;
						if (out1.empty())
						{
							#ifndef __WXGTK__
                            out << "\x1b[56m" << _("Unicode conversion error!") << "\x1b[0m\n";
							
                            #endif
                            #ifdef __WXGTK__
                            out << "\x1b[56m" << comm << "\x1b[0m\n";
                            #endif
						}
						else
							#ifndef __WXGTK__
                            out << "\x1b[56m" << out1 <<"\x1b[0m\n";
                            #endif
                            #ifdef __WXGTK__
                            out << "\x1b[56m" << comm << "\x1b[0m\n";
                            #endif
						
						#ifdef __WXGTK__
                        char buf[30000];
                        int x = strlen(out.mb_str(wxCSConv(m_parent->GetGlobalOptions()->GetCurEncoding())).data());
                        wxStrncpy(buf, out.mb_str(wxCSConv(m_parent->GetGlobalOptions()->GetCurEncoding())).data(), x);
                        buf[x]=EOS;
						//m_parent->m_child->ParseNBuffer((char*)out.ToUTF8().data(), false);
						m_parent->m_child->ParseNBuffer(buf, false);
						#endif
						#ifndef __WXGTK__
						m_parent->m_actwindow->ParseNBuffer((char*)out.char_str(), false);
						//m_parent->m_child->ParseNBuffer((char*)out.char_str(), false);
						#endif
						//m_parent->m_child->Refresh();
						//m_parent->m_child->Update();
						m_parent->m_actwindow->Update();
						m_parent->SetTriggersOn(p);
					}
				}
				/*int i=0;
				if (!m_history.empty())
				{
					i = count(m_history.begin(), m_history.end(), comm);
					if (!i)
					{*/
						if (!m_history.empty() && comm!=m_history.back() && history)
							m_history.push_back(comm);
						else if (m_history.empty() && history)
							m_history.push_back(comm);
						m_hpos = (int)m_history.size()-1;
						wxString l;
						l << m_hpos;
						wxLogDebug(l);
					//}
				//}
			}
			else
			{
				if (m_parent->GetGlobalOptions()->GetEcho() && echo)
				{
					wxString out = "\x1b[56m";
					out.append(wxEmptyString);
					out.append("\x1b[0m\n");
					/**m_parent->m_child->ParseBuffer(out.char_str());**/
					m_parent->m_actwindow->ParseNBuffer(out.char_str(wxCSConv(m_parent->GetGlobalOptions()->GetCurEncoding())), false);
					//m_parent->m_child->ParseNBuffer(out.char_str(wxCSConv(m_parent->GetGlobalOptions()->GetCurEncoding())), false);
				}
			}
			if (!ParseCommandLine(&comm))
			{
				
				//comm.append((char)LF);
				comm.append((char)CR);
				comm.append((char)LF);
				//m_parent->m_child->Write(command);
				m_parent->m_actwindow->Write(comm);
				
			}
		}
	}
	else //send input line as typed...no parsing implement echo here
	{
		if (!m_history.empty() && command!=m_history.back() && history)
			m_history.push_back(command);
		else if (m_history.empty() && history)
			m_history.push_back(command);
		m_hpos = (int)m_history.size()-1;
		if (m_parent->GetGlobalOptions()->GetEcho() && echo)
			{
				wxString out = "\x1b[56m";
				out.append(command);
				out.append("\x1b[0m\n");
				/***m_parent->m_child->ParseBuffer(out.char_str());***/
				m_parent->m_actwindow->ParseNBuffer(out.char_str(), false);
				//m_parent->m_child->ParseNBuffer(out.char_str(), false);
			}
		command.append((char)CR);
		command.append((char)LF);
		m_parent->m_actwindow->Write(command);
		//m_parent->m_child->Write(command);
		
	}
	
}

bool InputTextCtrl::ParseCommandLine(wxString *sCommand)
{
wxString s, var;
al_it iter;

	if (*sCommand==wxEmptyString)
		return true;
	//check for variables
	if (!ParseVars(sCommand))
		return true;//no such var found..do nothing
	if (!ParseLists(sCommand))
		return false;
	//check if this is an alias
	for (iter = m_parent->m_actwindow->GetAlias()->begin(); iter!= m_parent->m_actwindow->GetAlias()->end(); iter++)
		{
			if (iter->Match(*sCommand))
			{
				wxString send = iter->BuildAction();
				ParseVars(&send);
				wxCSConv co(m_parent->GetGlobalOptions()->GetCurEncoding());
				wxString conv = send;// send.mb_str(co);
				if (conv.IsEmpty())
					conv = send.ToUTF8();
				//Parse(send.mb_str(co), false, false); //do not echo und put in history if alias
				Parse(conv, false, false);
				
				return true;
			}
		}
	//check for command
	if (sCommand->at(0)==m_parent->GetGlobalOptions()->GetCommand())
	{
		s = sCommand->substr(1);
		if (ParseCommand(&s))
			return true;

	}
	//check for lua script command
	if (sCommand->at(0)==m_parent->GetGlobalOptions()->GetScript())
	{
		s = sCommand->substr(1);
		
		if (m_parent->m_actwindow->GetLState()->DoString(s))
		{
			struct lua_State* L = m_parent->m_actwindow->GetLState()->GetLuaState();
			int top = lua_gettop(L);
			wxString error = luaL_checkstring(L, top);
			m_parent->m_actwindow->Msg(error);
			return true;
		}
		
		return true;
	}
	//check for path
	if (sCommand->at(0)==m_parent->GetGlobalOptions()->GetSpeedwalk())
	{
		s = sCommand->substr(1);
		if (ParsePath(&s))
			return true;

	}
	//check for worldsend, only simple commands
	if (sCommand->at(0) == m_parent->GetGlobalOptions()->GetWorldSend())
	{
		s = sCommand->substr(1);
		s.Append((char)CR);
		s.Append((char)LF);
		size_t ss = m_parent->m_childwindows.size();
		for (size_t x = 0; x < ss; x++)
		{
			
			m_parent->m_childwindows.at(x)->Write(s.mb_str());
		}
		return true;

	}
	return false;
}

bool InputTextCtrl::ParseVars(wxString *s)
{
int i;
size_t idx=0;
wxString var;
//wxString ss = *s;
	//first we parse the mudclient defined vars
	
	//now user defined vars
	do
	{
		//replace the vars $
		idx = s->find(m_parent->GetGlobalOptions()->GetVar(), idx);
		if (idx!=string::npos) 
		{
			i = idx+1;
			//while (wxIsalnum(s->at(i)) || i<(int)s->length())
			while (i<(int)s->length())
			{
				if (wxIsalnum(s->at(i)))			
					i++;
				else break;
			}
			var = s->substr(idx, i-idx);
			int x = m_parent->GetDefVarIndexByLabel(var.substr(1));
			if (x==-1)
			{
				x = m_parent->m_actwindow->GetVarIndexByLabel(var.substr(1));
				if (x==-1) //error no var with the name there
					return false;
				if (m_parent->m_actwindow->GetVars()->at(x).IsActive())
				{//only replace if var active 
					s->Replace(var, m_parent->m_actwindow->GetVars()->at(x).GetValue());
					
				}
				else idx++;
			}
			else
			{
				if (m_parent->m_defvars.at(x).IsActive()) //only replace if var active 
					s->Replace(var, m_parent->m_defvars.at(x).GetValue());
			}
		}
	} while (idx!=string::npos);
	return true;
}

bool InputTextCtrl::ParseLists(wxString *s)
{
int i;
size_t idx;
wxString var;

	do
	{
		//replace the vars $
		idx = s->find(m_parent->GetGlobalOptions()->GetListVar());
		if (idx!=string::npos)
		{
			i = idx+1;
			while (i<(int)s->length())
			{
				if (wxIsalnum(s->at(i)))			
					i++;
				else break;
			}
			//while (isalnum(s->at(i)))
			//	i++;
			var = s->substr(idx, i-idx);
			int x = m_parent->m_actwindow->GetListIndexByLabel(var.substr(1));
			if (x==-1) //error no list with the name there
				return false;
			if (m_parent->m_actwindow->GetLists()->at(x).IsActive()) //only replace if var active 
				s->Replace(var, m_parent->m_actwindow->GetLists()->at(x).GetValue());
		}
	} while (idx!=string::npos);
	return true;
}

bool InputTextCtrl::ParsePath(wxString *s)
{
unsigned int i=0;
long idx;
size_t f;
wxString send;
m_swsend = wxEmptyString;

int sw = m_parent->GetGlobalOptions()->GetSWDelay();
	for (wxString::const_iterator it =s->begin();it!=s->end();it++)
	//for (i=0;i<s->length();i++)
	{
		if (!wxIsdigit(*it))//s->at(i)))
		{
			if (*it=='(')//(s->at(i)=='(')
			{
				f = s->find(')', it-s->begin());
				if (f==string::npos)
					return false;
				i = ++it-s->begin();
				send = s->substr(i, f-i);
				m_swsend.append('('+send+')');
				if (!sw)
					Parse(send, true);
				it += send.length();
			}
			else
			{ 
				m_swsend.append(*it);
				if (!sw)
					Parse(*it, true);//s->at(i), true);
			}
		}
		else
		{
			wxString sub = s->substr(it-s->begin());
			idx=wxAtol(sub);
			//sub.ToLong(&idx);
			it++;
			if (idx>=10)
				it++;
			//send = s->substr(i, 1);
			send = *it;
			//send=send.substr(0, 1);
			if (*it=='(')//(s->at(i)=='(')
			{
				f = s->find(')', it-s->begin());
				if (f==string::npos)
					return false;
				i = ++it-s->begin();
				send = s->substr(i, f-i);
				//m_swsend.append('('+send+')');
				//send = s->substr(++i, f-i-1);
				//Parse(send, true);
				it += send.length();
			}
			for (int ii=0;ii<idx;ii++)
			{
				if (send.length()>1)
					m_swsend.append('('+send+')');
				else
					m_swsend.append(send);
				if (!sw)
					Parse(send, true);
				//Parse(s->at(i), true);
			}
			
		}
	}
	if (sw)
		m_sw.Start(sw);
	return true;
}

void InputTextCtrl::OnSWDelay(wxTimerEvent& event)
{
static size_t i=0;
wxString send;

	send = m_swsend.at(i);
	if (!send.Cmp('('))
	{
		send = m_swsend.substr(++i, 2);
		i+=2;
	}
	Parse(send, true);
	i++;
	if (i>=m_swsend.length())
	{
		i=0;
		m_sw.Stop();
	}
}

bool InputTextCtrl::ParseCommand(wxString *sCommand)
{
int (InputTextCtrl::*func)(wxString*);
wxString s, params;

	size_t idx = sCommand->find_first_of("(");
	if (idx==string::npos)
	{
		s = *sCommand;
		params = wxEmptyString;
	}
	else
	{
		s = sCommand->substr(0, idx);
		params = sCommand->substr(idx);
	}
		//m_it = m_sComm.find(*sCommand);
	s.Trim();
	//m_it = m_sComm.find(s);
	//if (m_it != m_sComm.end())
	//{
		//func = m_it->second;
		func = m_sComm[s];
		if (!func)
		{
			wxString err;
			err << _("No such command found: ") << *sCommand << "!";
			m_parent->m_actwindow->Msg(err, 9);
			m_sComm.erase(s);
			return true;
		}
		int ret = (*this.*func)(&params);
		//some error in command?
		switch (ret)
		{
		case 0://no error
			return true;
		case -1:
			m_parent->m_actwindow->Msg(_("Wrong number of parameters!"));
			return true;
		case 1:
			m_parent->m_actwindow->Msg(_("Parameter not valid or out of range!"));
			return true;
		case 2:
			m_parent->m_actwindow->Msg(_("Syntax error in a Lua script!"));
			m_parent->m_actwindow->Msg(*sCommand);
			return true;
		case 3:
			m_parent->m_actwindow->Msg(_("Could not load specified file!"));
			break;
		default:
			return false;
		}
	//}
	//else m_parent->m_child->Msg(_("Unknown command!"));
	return false;
}
/***Mud Commands***/
int InputTextCtrl::CommRaw(wxString *sPar)
{
	wxSetWorkingDirectory(m_parent->GetGlobalOptions()->GetLogDir());
	if (::wxFileExists(RAW_FILE))
		::wxRemoveFile(RAW_FILE);
	m_parent->GetGlobalOptions()->SetDebugRaw(true);
	return 0;
}

int InputTextCtrl::Connect(wxString *sPar)
{
long iPort;
wxIPV4address addr;
int num;

	num = ParseFParams(sPar);
	if (num<2)
		return -1;
	addr.Hostname(GetFParam(1));
	//sd->m_port->ToLong(&iPort);
	GetFParam(2).ToLong(&iPort);
	addr.Service(iPort);
	m_parent->m_actwindow->MyConnect(addr);
	return 0;
}

#if defined WXAMCL_USEIPV6
int InputTextCtrl::Connect6(wxString *sPar)
{
long iPort;
wxIPV6address addr;
int num;

	num = ParseFParams(sPar);
	if (num<2)
		return -1;
	addr.Hostname(GetFParam(1));
	//sd->m_port->ToLong(&iPort);
	GetFParam(2).ToLong(&iPort);
	addr.Service(iPort);
	m_parent->m_actwindow->MyConnect6(addr);
	return 0;
}
#endif
int InputTextCtrl::Pwd(wxString *sPar)
{
	if (ParseFParams(sPar))
		return -1;
	if (m_parent->GetCurHost()!=-1)
	{
	
		m_parent->m_scriptwin->Write(m_parent->GetHosts()->at(m_parent->GetCurHost()).GetPwd()+'\n');
	}
	return 0;
}

//#capturewin("name", "0", "true|false") ***Add: "0|1" window or notebook capture "name_of_notebook_page"
int InputTextCtrl::CaptureWin(wxString *sPar)
{
int num;
long line;
	num = ParseFParams(sPar);
	if (num<2)
		return -1;
	amcLua *aL = m_parent->m_scriptwin->GetLState();
	//struct lua_State *L = aL->GetLuaState();
	wxString param1 = GetFParam(1);
	wxString param2 = GetFParam(2);
	wxString bo = GetFParam(3);
	wxString s = wxString::Format(("wxamcl.createwindow(\"%s\")"), param1);
	aL->DoString(s); //Create the window
	MudWindow *mw = (MudWindow*)MudWindow::FindWindowByName(param1);
	if (mw==NULL)
		return 1;
	//mw->m_curline++;
	param2.ToLong(&line);
	long cline = m_parent->m_scriptwin->m_curline-1;
	if (line<0)
		cline+=line;
	else if (line>0)
	{
		m_parent->m_scriptwin->GetNumCapture()->push_back(line);
		m_parent->m_scriptwin->GetWinCapture()->push_back(param1);
		if (num==3 && bo=="true")
			m_parent->m_scriptwin->GetGagCapture()->push_back(true);
		else
			m_parent->m_scriptwin->GetGagCapture()->push_back(false);
	}
	
	return 0;
}

//#capturenb("name", "page", "0", "true|false")
int InputTextCtrl::CaptureNb(wxString *sPar)
{
int num;
long line;
	num = ParseFParams(sPar);
	if (num<3)
		return -1;
	amcLua *aL = m_parent->m_scriptwin->GetLState();
	//struct lua_State *L = aL->GetLuaState();
	wxString Param1 = GetFParam(1);
	wxString Param2 = GetFParam(2);
	wxString Param3 = GetFParam(3);
	wxString Param4 = GetFParam(4);
	wxString s = wxString::Format("wxamcl.createnb(\"%s\", \"%s\")", Param1, Param2);
	aL->DoString(s); //Create the aui notebook if not there
	//MudWindow *mw = (MudWindow*)MudWindow::FindWindowByName(GetFParam(2).c_str());
	wxCSConv co(m_parent->GetGlobalOptions()->GetCurEncoding());
	MudWindow *mw = (MudWindow*)MudWindow::FindWindowByName(Param2);
	if (mw==NULL)
		return 1;
	//mw->m_curline++;
	Param3.ToLong(&line);
	long cline = m_parent->m_scriptwin->m_curline-1;
	if (line<0)
		cline+=line;
	else if (line>0)
	{
		m_parent->m_scriptwin->GetNumCapture()->push_back(line);
		m_parent->m_scriptwin->GetWinCapture()->push_back(Param2);
		if (num==4 && Param4=="true")
			m_parent->m_scriptwin->GetGagCapture()->push_back(true);
		else
			m_parent->m_scriptwin->GetGagCapture()->push_back(false);
	}
	wxAuiNotebook *nb = (wxAuiNotebook*)wxWindow::FindWindowByName(Param1, m_parent);
	if (nb->GetPageIndex(mw)!=wxNOT_FOUND)
	{
		if (mw->GetAutoFocus())
		{
			nb->SetSelection(nb->GetPageIndex(mw));
			this->SetFocus();
		}
	}
	
	return 0;
}

// #capstart("windowname", "true|false") 2nd param will gag lines in outputwindow
int InputTextCtrl::CapStart(wxString *sPar)
{
	//map<wxString, bool> w;
	int num1 = ParseFParams(sPar);
	if (num1<2)
		return -1;
	amcLua *aL = m_parent->m_scriptwin->GetLState();
	//struct lua_State *L = aL->GetLuaState();
	wxString ss = GetFParam(1);
	wxString bo = GetFParam(2);
	MudWindow *mw = (MudWindow*)MudWindow::FindWindowByName(ss.c_str(), m_parent);
	if (mw==NULL)
	{
		wxString s = wxString::Format("wxamcl.createwindow(\"%s\")", ss.c_str());
		aL->DoString(s); //Create the window
		mw = (MudWindow*)MudWindow::FindWindowByName(ss);
	}

	//w = m_parent->m_actwindow->GetCapWindow();
	//->push_back(GetFParam(1));

	if (num1==2 && bo=="true")
	{
		long cline = m_parent->m_scriptwin->m_curline-1;
		//AnsiLine al = m_parent->m_child->GetLineBuffer().at(cline);
		mw->AddLine(m_parent->m_scriptwin->GetLines()->at(cline));
		//mw->Refresh();
		mw->SetFirstCaptured(true);
		
		m_parent->m_scriptwin->GetCapWindow()->insert(pair<wxString,bool>(ss, true));
		
	}
	else
		m_parent->m_scriptwin->GetCapWindow()->insert(make_pair(ss, false));
		//w[GetFParam(1)] = false;
		//m_parent->m_child->GetGagWindow()->push_back(false);
	return 0;
}

// #capend("windowname", "true|false") 2nd param will gag last line too
int InputTextCtrl::CapEnd(wxString *sPar)
{
//list<wxString>::iterator it;
//list<bool>::iterator bit;
	if (ParseFParams(sPar)!=1)
		return -1;
	//wxStopWatch sw;
	//sw.Start();
	wxString s = GetFParam(1);
	MudWindow *mw = (MudWindow*)MudWindow::FindWindowByName(s, m_parent);
	if (mw==NULL)
		return 1;
	//long cline = m_parent->m_child->m_curline-1;
	//AnsiLine al =

	mw->AddLine(m_parent->m_scriptwin->GetLines()->at(m_parent->m_scriptwin->m_curline-1));
	vector<vector<wxString> >::iterator vit;
	if (!m_parent->GetNbs()->empty())
	{
		//int x=0;
		s_it it;
		for (it=m_parent->GetNbs()->begin();it!=m_parent->GetNbs()->end();it++)
		{
			wxAuiNotebook *nb = (wxAuiNotebook*)wxWindow::FindWindowByName(*it, m_parent);
			if (!nb)
				continue;
			if (nb->GetPageIndex(mw)!=wxNOT_FOUND)
			{
				if (mw->GetAutoFocus())
				{
					nb->SetSelection(nb->GetPageIndex(mw));
				}
				break;
			}
		}
	}//::wxLogDebug(wxT("capend: %ldms"), sw.Time());
	this->SetFocus();
	
	if (m_parent->m_scriptwin->GetCapWindow()->operator [](s))
	{
		m_parent->m_scriptwin->GetLines()->at(m_parent->m_scriptwin->m_curline-1).SetGagme(true);
		
	}
	m_parent->m_scriptwin->GetCapWindow()->erase(s);
	//mw->Refresh();
	//mw->Update();
	return 0;
}

// #clearwin("windowname") clear outputbuffer of window
int InputTextCtrl::ClearWin(wxString *sPar)
{
	int num = ParseFParams(sPar);
	if (!num)
		return -1;
	MudWindow *mw = (MudWindow*)MudWindow::FindWindowByName(GetFParam(1));
	if (mw==NULL)
		return 1;
	mw->ClearLines();
	//mw->SetScrollPage();
	return 0;
}

// #gagwin("windowname", "line") gag lines in capture window
int InputTextCtrl::GagWin(wxString *sPar)
{
long line;

	int num = ParseFParams(sPar);
	if (!num)
		return -1;
	MudWindow *mw = (MudWindow*)MudWindow::FindWindowByName(GetFParam(1).c_str());
	if (mw==NULL)
		return 1;
	GetFParam(2).ToLong(&line);
	if (line>0)
		return 1;
	//long cline = m_parent->m_child->m_curline-1;
	//if (line<0)
	//	cline+=line;

	if (!mw->GetLines()->empty())
	{
		line_it lit = mw->GetLines()->end();
		lit = lit-1+line;
		//for (int i=cline;i>line+cline;i--, lit--);
		mw->GetLines()->erase(lit);
		if (mw->m_curline>=1)
			mw->m_curline--;
		else mw->m_curline=0;
		//mw->SetScrollPage();
		//mw->Refresh();
		//mw->Update();
	}
	return 0;
}

int InputTextCtrl::RefreshWin(wxString *sPar)
{
	int num = ParseFParams(sPar);
	if (num!=1)
		return -1;
	MudWindow *mw = (MudWindow*)MudWindow::FindWindowByName(GetFParam(1));
	if (mw==NULL)
		return 1;
	mw->SetScrollPage();
	mw->Refresh();
	mw->Update();
	return 0;
}
// #gag("line") gag lines in window
int InputTextCtrl::Gag(wxString *sPar)
{
long line;

	int num = ParseFParams(sPar);
	if (num!=1)
		return -1;
	MudWindow *mw = (MudWindow*)m_parent->m_scriptwin;
	if (mw==NULL)
		return 1;
	GetFParam(1).ToLong(&line);
	if (line>0)
		return 1;
	//long cline = m_parent->m_child->m_curline-1;
	//if (line<0)
	//	cline+=line;

	if (!mw->GetLines()->empty())
	{
		line_it lit = mw->GetLines()->end()-1;
		lit = lit+line;
		//if (!line)
		//	lit->SetGagme(true);
		//else 
		//{
			mw->GetLines()->erase(lit);
			if (mw->m_curline>=1)
				mw->m_curline--;
			else mw->m_curline=0;
		//}
		mw->SetScrollPage();
		mw->Refresh();
		//mw->Update();*/
	}
	return 0;
}

int InputTextCtrl::Func(wxString *sPar)
{
	int num = ParseFParams(sPar);
	
	if (num!=2)
		return -1;
	amcLua *aL = m_parent->m_scriptwin->GetLState();
	wxSetWorkingDirectory(m_parent->GetGlobalOptions()->GetWorkDir());
	wxSetWorkingDirectory(m_parent->GetGlobalOptions()->GetScriptDir());
	wxString file = GetFParam(1);
	wxString func = GetFParam(2);
	int err = aL->DoFile(file.mb_str().data());
	if (err)
	{
		wxString s = aL->GetwxString(aL->GetTop());
		m_parent->m_scriptwin->Msg(s);
		aL->Pop(1);
		return 2;
	}
	
	wxString subname = func.BeforeFirst('(');
	wxString arglist = func.AfterFirst('(');
	int len = ParseFParams(&arglist, '\'');
	aL->GetGlobal(subname);
	for (int x=0;x<len;x++)
		aL->PushString(GetFParam(x+1));
	err = aL->Call(len);
	if (err)
	{
		wxString s = aL->GetwxString(aL->GetTop());
		m_parent->m_scriptwin->Msg(s);
		aL->Pop(1);
		return 2;
	}
	aL->SetTop(0);
	return 0;
}

int InputTextCtrl::Script(wxString *sPar)
{
	int num = ParseFParams(sPar);

	if (num!=1)
		return -1;
	amcLua *aL = m_parent->m_scriptwin->GetLState();
	//if (!wxThread::IsMain())
	//	wxMutexGuiEnter();
	wxSetWorkingDirectory(m_parent->GetGlobalOptions()->GetWorkDir());
	wxSetWorkingDirectory(m_parent->GetGlobalOptions()->GetScriptDir());
	
	//int err = aL->DoFile(GetFParam(1).c_str());
	int err = aL->DoFile(GetFParam(1));
	//if (!wxThread::IsMain())
	//	wxMutexGuiLeave();
	if (err)
	{
		wxString s = aL->GetwxString(aL->GetTop());
		m_parent->m_scriptwin->Msg(s.mb_str());
		aL->Pop(1);
		return 2;
	}
	return 0;
}

/*int InputTextCtrl::BScript(wxString *sPar)
{
	
	amcScriptThread *asth = new amcScriptThread(m_parent, *sPar);
	if (asth->Run()!= wxTHREAD_NO_ERROR)
		return 1;
	return 0;
}*/

int InputTextCtrl::TScript(wxString *sPar)
{

	int num = ParseFParams(sPar);
	if (num!=1)
		return -1;
	amcLua *aL = m_parent->m_scriptwin->GetLState();
	
	wxSetWorkingDirectory(m_parent->GetGlobalOptions()->GetWorkDir());
	wxSetWorkingDirectory(m_parent->GetGlobalOptions()->GetScriptDir());
	lua_State *L1 = lua_newthread(aL->GetLuaState());
	
	//int err = aL->DoFile(GetFParam(1).c_str());
	luaL_loadfile(L1, GetFParam(1).char_str());
	//int err = lua_resume(L1, 0); 5.1.4
	int err = lua_resume(L1, NULL, 0);
	if (err && err!= LUA_YIELD)
	{
		wxString s = aL->GetwxString(aL->GetTop());
		m_parent->m_scriptwin->Msg(s);
		aL->Pop(1);
		return 2;
	}
	return 0;
}

int InputTextCtrl::LoadProfile(wxString *sPar)
{
	int num = ParseFParams(sPar);
	if (num!=1)
		return -1;
	if (!m_parent->LoadProfile(GetFParam(1)))
		return 3;
	return 0;
	
}

int InputTextCtrl::Log(wxString *sPar)
{
	int num = ParseFParams(sPar);
	if (num!=3)
		return -1;
	m_parent->m_actwindow->SetLogging(true);
	if (GetFParam(2)=="true")
		m_parent->m_actwindow->SetAnsiLogging(true);
	else m_parent->m_actwindow->SetAnsiLogging(false);
	if (GetFParam(3)=="true")
		m_parent->m_actwindow->SetDateLogging(true);
	else m_parent->m_actwindow->SetDateLogging(false);
	wxSetWorkingDirectory(m_parent->GetGlobalOptions()->GetWorkDir());
	wxSetWorkingDirectory(m_parent->GetGlobalOptions()->GetLogDir());
    ::wxRemoveFile(GetFParam(1));
	m_parent->m_actwindow->SetTextLog(new wxFile(GetFParam(1), wxFile::write));
    if (!m_parent->m_actwindow->GetTextLog()->IsOpened())
		return 1;
	wxDateTime d;
	d.SetToCurrent();
	wxString s;
	s<<_("Logging started: ")<<d.FormatDate()<<(", ")<<d.FormatTime();
	m_parent->m_actwindow->GetTextLog()->Write(s+(char)CR+(char)LF+(char)CR+(char)LF);
	return 0;
}

int InputTextCtrl::HtmlLog(wxString *sPar)
{
	int num = ParseFParams(sPar);
	if (num!=2)
		return -1;
	wxSetWorkingDirectory(m_parent->GetGlobalOptions()->GetWorkDir());
	wxSetWorkingDirectory(m_parent->GetGlobalOptions()->GetLogDir());
	::wxRemoveFile(GetFParam(1));
	if (GetFParam(2)=="true")
		m_parent->m_actwindow->SetHtmlLogging(true);
	else m_parent->m_actwindow->SetHtmlLogging(false);
	m_parent->m_actwindow->SetLogging(true);
	if (GetFParam(2)=="true")
	{	
		m_parent->m_actwindow->SetHtmlLog(new wxFile(GetFParam(1), wxFile::write));
		wxFile *f = m_parent->m_actwindow->GetHtmlLog();
		if (!f->IsOpened())
			return 1;
		m_parent->m_actwindow->WriteHtmlHeader(f);
		/*wxString s;
		s<<"<html>\r\n<head>\r\n<title>wxAmc Log-File</title>\r\n<meta name=\"author\" content=\"Mag. Andreas Sachs\">\r\n";
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
		//itoa(cols[0], szConv, 16);
		s=wxString::Format(" bgcolor=\"%s\">\r\n<pre>", m_parent->m_child->GetAnsiColor(0).GetAsString(wxC2S_HTML_SYNTAX));
		f->Write(s);*/
		if (m_parent->m_actwindow->GetInclude())
		{
			for (wxUint64 i =0;i<m_parent->m_actwindow->m_curline-1;i++)
			{
				m_parent->m_actwindow->SendLineToLog(i);
			}
		}
	}
	else
	{
		wxString s;
		wxFile *f = m_parent->m_actwindow->GetHtmlLog();
		//s<<"<a class=\"col7\">"
		s<<"</a><br>\r\n"<<"\r\n</pre>\r\n</body>\r\n</html>\r\n";
		f->Write(s);
		f->Close();
		m_parent->m_actwindow->DeleteHtmlLog();
		m_parent->m_actwindow->SetLogging(false);
	}
	
	return 0;
}

int InputTextCtrl::SetVar(wxString *sPar)
{
	int num = ParseFParams(sPar);
	if (num!=2)
		return -1;
	wxString var = GetFParam(1);
	wxString val = GetFParam(2);
	int idx = m_parent->GetVarIndexByLabel(var);
	if (idx==-1)
		return 1;
	m_parent->GetVars()->at(idx).SetValue(val);
	return 0;
}

//#test("mud output")
int InputTextCtrl::Test(wxString *sPar)
{
	if (ParseFParams(sPar)!=1)
		return -1;
	wxString s = GetFParam(1);
	s = "\x1b[0m" + s + (char)CR+(char)LF;
	s = s.mb_str(wxCSConv(m_parent->GetGlobalOptions()->GetCurEncoding()));
	if (s.empty())
		s << "\x1b[0m" << GetFParam(1) <<"\n";
	/**m_parent->m_child->ParseBuffer(s.char_str());**/
	m_parent->m_actwindow->ParseNBuffer(s.char_str());
	return 0;
}

int InputTextCtrl::Resume(wxString *sPar)
{
//wxThreadIdType tid;
//amcScriptThread* t = new amcScriptThread();
int ref;
	//if (!wxThread::IsMain())	
	//	wxMutexGuiEnter();
	if (ParseFParams(sPar)!=1)
		return -1;
	wxString s = GetFParam(1);
	ref = wxAtoi(s);
	map<int, struct lua_State*> * ml = m_parent->GetLuaStates();
	map<int, lua_State*>::iterator itm = ml->find(ref);
	
	//vector<struct lua_State*>::iterator i = m_parent->GetLStates()->begin();
	//m_parent->GetLStates()->erase(i+ref);
	//delete the resume trigger
	wxString label;
	label << "temp" << ref;
	int co = m_parent->GetTriggerIndexByLabel(label);
	if (co!=-1)
	{
		tr_it it = m_parent->GetTrigger()->begin()+co;
		m_parent->GetTrigger()->erase(it);
	}
	label.Clear();
	label << "resume" << ref;
	co = m_parent->GetTimerIndexByLabel(label);
	if (co!=-1)
	{
		//m_parent->GetTimers()->at(co).Stop();
		t_it itt = m_parent->GetTimers()->begin()+co;
		m_parent->GetTimers()->erase(itt);
	}
	m_waiting = false;
	//int err = lua_resume(itm->second, 0); 5.1.4
	lua_resume(itm->second, NULL, 0);	
	return 0;
}

int InputTextCtrl::Media(wxString *sPar)
{
	if (ParseFParams(sPar) != 2)
		return -1;
	wxString dir = m_parent->GetGlobalOptions()->GetWorkDir();
	wxSetWorkingDirectory(dir);
	wxString file = GetFParam(1);
	wxString hrrm = dir + "\\" + file;
	if (!m_parent->m_media->Load(file))
		return 3;
	
	if (!GetFParam(2).Cmp("true"))
	{
		m_parent->m_mgr.GetPane("amcmedia").Show().Float();
		m_parent->m_mgr.Update();
	}
	
	return 0;
}

int InputTextCtrl::Mxp(wxString *sPar)
{
	if (ParseFParams(sPar) != 1)
		return -1;
	if (!GetFParam(1).Cmp("on"))
	{
		m_parent->m_actwindow->SetMXP(true);
	}
	else if (!GetFParam(1).Cmp("off"))
		m_parent->m_actwindow->SetMXP(false);
	return 0;
}

int InputTextCtrl::Info(wxString *sPar)
{
	if (ParseFParams(sPar) != 0)
		return -1;
	wxString s;
	s << _("--- Information ----");
	m_parent->m_actwindow->Msg("");
	m_parent->m_actwindow->Msg(s, 17, 4);
	s.clear();
	s<<_("Version: ")<<APP_VERSION;
	m_parent->m_actwindow->Msg(s);
	s.clear();
	m_parent->m_actwindow->Msg(_("--- Libraries used ---"));
	s.clear();
	s << _("Lua version ") << LUA_RELEASE;
	m_parent->m_actwindow->Msg(s);
	s.clear();
	s << _("Sqlite3 version ") << sqlite3_version;
	m_parent->m_actwindow->Msg(s);
	s.clear();
	s << _("Pcre version ") << pcre_version();
	m_parent->m_actwindow->Msg(s);
	s.clear();
	m_parent->m_actwindow->Msg(_("--- Protocols used ---"));
	s.clear();
	s << _("MCCP: ") << (m_parent->m_actwindow->IsMCCPActive() ? _("active") : _("not active"));
	m_parent->m_actwindow->Msg(s);
	s.clear();
	if (m_parent->m_actwindow->IsMCCPActive())
	{
		wxString ratio;
		ratio.sprintf("%2.2f", m_parent->m_actwindow->GetDecompressor()->GetRatio()*100);
		s << _("Saving ") << ratio << "%.";
		m_parent->m_actwindow->Msg(s);
		s.clear();
	}
	
	s << _("MXP: ") << (m_parent->m_actwindow->IsMXPActive() ? _("active") : _("not active"));
	m_parent->m_actwindow->Msg(s);
	if (m_parent->m_actwindow->IsMXPActive())
	{
		s.clear();
		s << _("Elements received: ") << m_parent->m_actwindow->GetMXPParser()->GetNumElements();
		m_parent->m_actwindow->Msg(s);
		
		for (size_t i=0;i<m_parent->m_actwindow->GetMXPParser()->GetNumElements();i++)
		{
			s.clear();
			s << _("    Received element * ")<< m_parent->m_actwindow->GetMXPParser()->GetElementAt(i)<<" * "<< m_parent->m_actwindow->GetMXPParser()->GetActionAt(i);
			m_parent->m_actwindow->Msg(s);
		}
		s.clear();
		s << _("Entities received: ") << m_parent->m_actwindow->GetMXPParser()->GetNumEntities();
		m_parent->m_actwindow->Msg(s);
	}
	s.clear();
	s << _("MSP: ") << (m_parent->m_actwindow->IsMSPActive() ? _("active") : _("not active"));
	m_parent->m_actwindow->Msg(s);
	s.clear();
	s << _("GMCP: ") << (m_parent->m_actwindow->IsGMCPActive() ? _("active") : _("not active"));
	m_parent->m_actwindow->Msg(s);
	
	for (size_t i=0;i<m_parent->m_actwindow->GetGMCPModules()->size();i++)
	{
		s.clear();
		s << _("    Received variable * ") << m_parent->m_actwindow->GetGMCPModules()->at(i) << " * .";
		m_parent->m_actwindow->Msg(s);
	}
	s.clear();
	s << _("MSDP: ") << (m_parent->m_actwindow->IsMSDPActive() ? _("active") : _("not active"));
	m_parent->m_actwindow->Msg(s);
	s.clear();
	if (!m_parent->m_actwindow->GetUseIPV6())
		s << _("Connected to ") <<m_parent->m_actwindow->GetIPAddr()->IPAddress()<<" "<<m_parent->m_actwindow->GetIPAddr()->Hostname()<<" (IPV4)";
    #if defined WXAMCL_USEIPV6 
        #ifndef __WXMSW__
        else
            s << _("Connected to ") <<m_parent->m_actwindow->GetIP6Addr()->OrigHostname()<<" "<<m_parent->m_actwindow->GetIP6Addr()->Hostname()<<" (IPV6)";
		#endif
        #ifdef __WXMSW__
        else
            s << _("Connected to ") << m_parent->m_actwindow->GetIP6Addr()->IPAddress()/*OrigHostname()*/ << " " << m_parent->m_actwindow->GetIP6Addr()->Hostname() << " (IPV6)";
        #endif
    #endif
	m_parent->m_actwindow->Msg(s);
	s.clear();
	s << _("--- Information end----");
	m_parent->m_actwindow->Msg(s, 17, 4);
	return 0;
}

int InputTextCtrl::DebugGMCP(wxString *sPar)
{
	if (ParseFParams(sPar) != 1)
		return -1;
	if (!GetFParam(1).Cmp("on"))
	{
		m_parent->m_actwindow->SetDebugGMCP(true);
		wxSetWorkingDirectory(m_parent->GetGlobalOptions()->GetWorkDir());
		if (::wxFileExists("debuggmcp.txt"))
			::wxRemoveFile("debuggmcp.txt");
	}
	else if (!GetFParam(1).Cmp("off"))
		m_parent->m_actwindow->SetDebugGMCP(false);
	return 0;
}

int InputTextCtrl::Help(wxString *sPar)
{
std::map<class wxString, int (InputTextCtrl::*)(wxString*)>::iterator it;

	for (it=m_sComm.begin();it!=m_sComm.end();it++)
		m_parent->m_actwindow->Msg(it->first);
	return 0;
}

int InputTextCtrl::ParseFParams(wxString *s, wxChar delim)
{
//wxString p;
size_t idx1=0, idx2=0;
	m_fparams.clear();
	do
	{
		if (idx2!=0)
		{
			m_fparams.push_back(s->substr(idx1+1, idx2-idx1-1));
			idx2++;
		}
		idx1 = s->find(delim, idx2);
		idx2 = s->find(delim, idx1+1);
	} while (idx1!=string::npos && idx2!=string::npos);
	//replace if param is a variable
	for (idx1=0;idx1<m_fparams.size();idx1++)
	{
		ParseVars(&m_fparams.at(idx1));
	}
	return (int)m_fparams.size();
}
/*** Mud Commands end***/
//Loading functions
bool InputTextCtrl::SaveHistory()
{
    wxSetWorkingDirectory(m_parent->GetGlobalOptions()->GetWorkDir());
    wxTextFile file("history.txt");
    if (!::wxFileExists("history.txt"))
		file.Create("history.txt");
	if (!file.Open())
		return false;
	file.Clear();
	s_it it;
	for (it=m_history.begin(); it!=m_history.end();it++)
		file.AddLine(*it);
	file.Write();
	file.Close();
	return true;
}

bool InputTextCtrl::LoadHistory()
{
wxSetWorkingDirectory(m_parent->GetGlobalOptions()->GetWorkDir());
wxTextFile file("history.txt");
wxString str;

    if (!::wxFileExists("history.txt"))
		return false;
	if (!file.Open())
		return false;
	for ( str = file.GetFirstLine(); !file.Eof(); str = file.GetNextLine() )
	{
		m_history.push_back(str);
	}
	//m_history.push_back(file.GetLastLine());
	file.Close();
	m_hpos = (int)m_history.size()-1;
	//m_hpos = (int)m_history.size();
	return true;
}

bool InputTextCtrl::LoadTabText()
{
wxSetWorkingDirectory(m_parent->GetGlobalOptions()->GetWorkDir());
wxTextFile file("tabcompletion.txt");
wxString str;
if (!::wxFileExists("tabcompletion.txt"))
		return false;
	if (!file.Open())
		return false;
	for ( str = file.GetFirstLine(); !file.Eof(); str = file.GetNextLine() )
	{
		m_tabtext.push_back(str);
	}
	//m_history.push_back(file.GetLastLine());
	file.Close();
	m_tabpos = 0;
	return true;
}

wxString InputTextCtrl::Complete()
{
s_it it;
size_t i;
std::vector<wxString> svec;

	svec = m_history;
	for (it=m_tabtext.begin();it!=m_tabtext.end(); it++)
		svec.push_back(*it);
	for(i=m_tabpos;i<svec.size();i++)
	{
		if (svec.at(i).StartsWith(m_tabsearch))
		{
			m_tabpos=(int)(i+1);
			return svec.at(i);
		}
	}
	if(i>=svec.size())
		m_tabpos=0;
	//return m_tabsearch;
	return wxEmptyString;
}

//threads
amcScriptThread::amcScriptThread(MudMainFrame *frame, wxString sPar) : wxThread()
{
	Create();
	m_frame = frame;
	m_id = GetId();
	m_pars = sPar;
	m_mutex=NULL;
	m_cond=NULL;
	TestDestroy();
	
}

amcScriptThread::amcScriptThread() : wxThread()
{
	Create();
	m_frame = NULL;
	m_id = GetId();
	m_pars = wxEmptyString;
}


amcScriptThread::amcScriptThread(const amcScriptThread& asc) : wxThread()
{
	m_frame = asc.m_frame;
	m_id = asc.m_id;
	m_pars = asc.m_pars;
}

amcScriptThread::~amcScriptThread()
{
}

void *amcScriptThread::Entry()
{
	//wxMutexGuiEnter();
	wxSetWorkingDirectory(m_frame->GetGlobalOptions()->GetWorkDir());
	wxSetWorkingDirectory(m_frame->GetGlobalOptions()->GetScriptDir());
	amcLua *aL = m_frame->m_actwindow->GetLState();
	//int err = aL->DoFile(GetFParam(1).c_str());
	m_frame->m_input->ParseFParams(&m_pars);
	wxString s = m_frame->m_input->GetFParam(1);
	const char *c = s.To8BitData();
	
	int err = aL->DoFile(c);
	
	if (err)
	{
		wxString s = aL->GetwxString(aL->GetTop());
		m_frame->m_actwindow->Msg(s);
		aL->Pop(1);
		return NULL;
	}
	//m_frame->m_input->Script(&m_pars);
	//wxMutexGuiLeave();
	if (TestDestroy())
		return NULL;
	return NULL;
}
