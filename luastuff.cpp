#include "main.h"
#include "script.xpm"
extern "C"
{
	#include "sha256.h"
}
amcLua::amcLua()
{
	
	m_L = luaL_newstate();
	luaL_openlibs(m_L);
	
	//lua_pushvalue(m_L, -1);
	//luaopen_amc(m_L);lua 5.1.4
	luaopen2_amc(m_L);//lua 5.2.0
	wxSetWorkingDirectory(wxGetApp().GetFrame()->GetGlobalOptions()->GetLuaDir());
	luaL_dofile(m_L, "printt.lua");
	luaL_dofile(m_L, "json.lua");
	luaL_dostring(m_L, "js = require('json')");
	m_len=0;
	
}

amcLua::~amcLua()
{
	lua_close(m_L);
}

void amcLua::RegisterFunc(wxString s, lua_CFunction f (lua_State *))
{
	lua_register(m_L, s.char_str(), (lua_CFunction) f);
}

void amcLua::GetGlobal(wxString s)
{
	lua_getglobal(m_L, (const char*)s.mb_str());
}

int amcLua::GetObjectLen()
{
	//return (int)lua_objlen(m_L, -1);lua5.1.4
	return (int)lua_rawlen(m_L, -1); //lua 5.2.0
}

void amcLua::GetTable(int idx)
{
	lua_gettable(m_L, idx);
}

void amcLua::GetField(int idx, wxString s)
{
	lua_getfield(m_L, idx, (const char*)s.mb_str());
}

void amcLua::RawGeti(int idx, int n)
{
	lua_rawgeti(m_L, idx, n);
}

int amcLua::GetInt(int idx)
{
	if (lua_isnumber(m_L, idx))
		return lua_tointeger(m_L, idx);
	else
		return -1;
}

long amcLua::GetLong(int idx)
{
	if (lua_isnumber(m_L, idx))
		return (long)lua_tonumber(m_L, idx);
	else
		return -1;
}

float amcLua::GetFloat(int idx)
{
	if (lua_isnumber(m_L, idx))
		return (float)lua_tonumber(m_L, idx);
	else
		return -1;
}

bool amcLua::GetBoolean(int idx)
{
	//return (bool)lua_toboolean(m_L, idx);
	return lua_toboolean(m_L, idx) ? true:false;
}

wxString amcLua::GetwxString(int idx)
{
	if (lua_isstring(m_L, idx))
	{
		const char *string = lua_tostring(m_L, idx);
		//wxString ss(string, wxCSConv(wxGetApp().GetFrame()->GetGlobalOptions()->GetCurEncoding()), wxStrlen(string));
		//if (s.empty())
		#ifdef __WXMSW__
			wxString s= wxString::From8BitData(string);
			return s;
		#endif
		#ifdef __WXGTK__
		//wxString s(string, wxCSConv(wxFONTENCODING_ISO8859_1));
			//return wxString::FromUTF8Unchecked(string);
			return wxString::From8BitData(string);
		//return s;
		//wxString s(string, wxCSConv(wxGetApp().GetFrame()->GetGlobalOptions()->GetCurEncoding()), wxStrlen(string));
		#endif
		#ifdef __WXOSX__
			return wxString::From8BitData(string);
		#endif
		//s = wxString::Format("%c", string);
		//return s;
	}
	else return wxEmptyString;
}

wxString amcLua::GetUTF8String(int idx)
{
	if (lua_isstring(m_L, idx))
	{
		const char *string = lua_tostring(m_L, idx);
		//wxString ss(string, wxCSConv(wxGetApp().GetFrame()->GetGlobalOptions()->GetCurEncoding()), wxStrlen(string));
		//if (s.empty())
		wxString s = wxString::FromUTF8(string);
		
		return s;
	}
	return wxEmptyString;
}

const char* amcLua::GetString(int idx)
{
	size_t len;
	if (lua_isstring(m_L, idx))
	{
		const char *string = lua_tolstring(m_L, idx, &len);
		m_len=len;
		return string;
	}
	else return "";
}

int amcLua::DoString(wxString s)
{
	return luaL_dostring(m_L, s.char_str(wxCSConv(wxGetApp().GetFrame()->GetGlobalOptions()->GetCurEncoding())));
	
	//return luaL_dostring(m_L, s.c_str());
}

int amcLua::DoFile(wxString s)
{
	return luaL_dofile(m_L, s.char_str());
}

int amcLua::DoFile(const char* s)
{
	return luaL_dofile(m_L, s);
}

int amcLua::DoResume(wxString s)
{
	return luaL_doresume(m_L, s.char_str());
}

void amcLua::SetGlobal(wxString s)
{
	lua_setglobal(m_L, (const char*)s.mb_str());
}

void amcLua::SetGlobal(const char* s)
{
	lua_setglobal(m_L, s);
}


void amcLua::PushString(const char* s)
{
	lua_pushstring(m_L, s);
}

void amcLua::PushString(wxString s)
{
	lua_pushstring(m_L, (const char*)s.mb_str());
}

void amcLua::PushLString(const char *s, int len)
{
	lua_pushlstring(m_L, s, len);
	m_len=len;
}

void amcLua::PushInt(int i)
{
	lua_pushinteger(m_L, i);
}

void amcLua::SetTop(int idx)
{
	lua_settop(m_L, idx);
}

void amcLua::Pop(int idx)
{
	lua_pop(m_L, idx);
}

int amcLua::GetTop()
{
	return lua_gettop(m_L);
}

int amcLua::Call(int args)
{
	return lua_pcall(m_L, args, LUA_MULTRET, 0);
}
/***global stuff***/
/******************/

//! amc.exec(command)
/*!
	send commands to the mud via Lua
	
	command will be parsed as if given in command line
	\param lua_State *L: a valid lua_State
*/
int luafunc_exec(lua_State*L)
{
	const char* c;
	
	c=luaL_checkstring(L, 1);
	//class MudWindow *frame = (MudWindow*)MudWindow::FindWindowByName(wxT("amcoutput"));
	class MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));

	wxString command(c);
	bool b = (lua_toboolean(L,2)!=0);
	if (frame==NULL)
		return 0;
	int state = frame->m_scriptwin->GetParseState();
	frame->m_scriptwin->SetParseState(0);//HAVE_TEXT
	frame->m_input->Parse(command, b);
	frame->m_scriptwin->SetParseState(state);
	return 0;
}

int luafunc_send(lua_State*L)
{
	const char* c;

	c=luaL_checkstring(L, 1);
	//class MudWindow *frame = (MudWindow*)MudWindow::FindWindowByName(wxT("amcoutput"));
	class MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	if (frame==NULL)
		return 0;
	wxString command(c);
	command.append((char)CR);
	command.append((char)LF);
	frame->m_scriptwin->Write(command);
	return 0;
}

//! amc.echo(text, fcol, bcol)
/*!
	echo function for wxAmc \
	print messages on the screen via Lua
	amc.echo("A message!")
	amc.echo("A message", "red", "green")
	amc.echo("A message", "#aaff00")
	returns the message:
	msg = amc.echo("Text")
	\param lua_State *L: a valid lua_State
*/
int luafunc_echo(lua_State*L)
{
	const char* text;
	const char* fcol;
	const char* bcol;
	
	//wxMutexGuiEnter();
	MudMainFrame *parent = wxGetApp().GetFrame();
	
	const char* white ="silver";
	const char* black ="black";
	fcol=luaL_optstring(L, 2, white);
	bcol=luaL_optstring(L, 3, black);
	text=luaL_checkstring(L, 1);
	
	class MudWindow *frame = parent->m_scriptwin;//wxGetApp().GetChild();
	if (frame==NULL)
		return 0;
	AnsiLineElement ale;
	wxColour c;
	map<wxString, wxColour> m = frame->GetMXPParser()->GetMXPColorMap();
	if (wxString(fcol).StartsWith('#'))
	{
		c.Set(fcol);
		ale.SetFCol(99, c);
	}
	else
		ale.SetFCol(99,m[fcol]);
	if (wxString(bcol).StartsWith('#'))
	{
		c.Set(bcol);
		ale.SetBCol(99, c);
	}
	else
		ale.SetBCol(99,m[bcol]);
	/*wxString ba(text, wxCSConv(parent->GetGlobalOptions()->GetCurEncoding()));
	if (ba.IsEmpty())
		ba<<text;*/
	//replace vars
	wxString ba = wxString::From8BitData(text);
	//parent->m_input->ParseVars(&ba);

	ale.SetText(ba);
	//ale.SetText(text);
	AnsiLine line;
	if (!frame->GetLines()->back().IsFull())
	{
		frame->GetLines()->pop_back();
		frame->m_curline--;
	}
	line.m_vstyle.push_back(ale);
	line.SetFull(true);
	line.SetLineText(ba);
	AnsiLineElement ale1;
	line.m_vstyle.push_back(ale1);
	if (frame->m_curline==0)
		line.SetLinenumber(frame->m_curline);
	else
		line.SetLinenumber(frame->GetLines()->at(frame->m_curline-1).GetLinenumber()+1);
	wxDateTime d;
	//d.SetToCurrent();
	d = wxDateTime::UNow();
	line.SetDateTimeMS(d);
	d = wxDateTime::Now();
	line.SetDateTime(d);
	frame->GetLines()->push_back(line);
	frame->m_curline++;
	//frame->Refresh();
	//frame->Update();
	lua_pushstring(L, text);
		
	if (!frame->GetScroll())
	{
		frame->SetScrollPage();
		frame->Refresh();
		frame->Update();
	}
	
	return 1;
}
//! color = wxamcl.color(text, foreground, background)
/*!
	changes color without newline
	
	\param lua_State *L: a valid lua_State
*/
int luafunc_color(lua_State*L)
{
	const char* fcol;
	const char* bcol;
	fcol=luaL_optstring(L, 2, "white");
	bcol=luaL_optstring(L, 3, "black");
	const char* text=luaL_checkstring(L, 1);
	class MudWindow *frame = wxGetApp().GetFrame()->m_scriptwin;//(MudWindow*)MudWindow::FindWindowByName("amcoutput");
	if (frame==NULL)
		return 0;
	AnsiLineElement ale;
	wxColour c;
	map<wxString, wxColour> m = frame->GetMXPParser()->GetMXPColorMap();
	
	if (wxString(fcol).StartsWith('#'))
	{
		c.Set(fcol);
		ale.SetFCol(99, c);
	}
	else
		ale.SetFCol(99,m[fcol]);
	if (wxString(bcol).StartsWith('#'))
	{
		c.Set(bcol);
		ale.SetBCol(99, c);
	}
	else
		ale.SetBCol(99,m[bcol]);
	wxString t = wxString::From8BitData(text);
	ale.SetText(t);
	frame->GetLines()->back().m_vstyle.push_back(ale);
	frame->GetLines()->back().SetLineText(t);
	lua_pushstring(L,"");
	wxGetApp().GetFrame()->m_scriptwin->Refresh();
	return 1;
}

int luafunc_colorwin(lua_State*L)
{
	const char* fcol;
	const char* bcol;
	const char* win;
	win = luaL_checkstring(L, 1);
	class MudWindow *mw = (MudWindow*)MudWindow::FindWindowByName(win);
	if (!mw)
		return 0;
	fcol=luaL_optstring(L, 3, "white");
	bcol=luaL_optstring(L, 4, "black");
	const char* text=luaL_checkstring(L, 2);
	AnsiLineElement ale;
	wxColour c;
	map<wxString, wxColour> m = mw->GetMXPParser()->GetMXPColorMap();
	
	if (wxString(fcol).StartsWith('#'))
	{
		c.Set(fcol);
		ale.SetFCol(99, c);
	}
	else
		ale.SetFCol(99,m[fcol]);
	if (wxString(bcol).StartsWith('#'))
	{
		c.Set(bcol);
		ale.SetBCol(99, c);
	}
	else
		ale.SetBCol(99,m[bcol]);
	wxString t = wxString::From8BitData(text);
	ale.SetText(t);
	mw->GetLines()->back().m_vstyle.push_back(ale);
	mw->GetLines()->back().SetLineText(t);
	lua_pushstring(L,"");
	return 1;
}

//! wxamcl.colorall(foreground, background)
/*!
	colors the whole (visible) output buffer to foreground background
	wxamcl.colorall(black,black)
	\param lua_State *L: a valid lua_State
*/
int luafunc_colorall(lua_State*L)
{
	const char* fcol;
	const char* bcol;
	fcol=luaL_optstring(L, 1, "white");
	bcol=luaL_optstring(L, 2, "black");
	class MudWindow *frame = wxGetApp().GetFrame()->m_scriptwin;
	if (frame==NULL)
		return 0;
	wxColour c;
	map<wxString, wxColour> mm = frame->GetMXPParser()->GetMXPColorMap();
	
	if (wxString(fcol).StartsWith('#'))
	{
		c.Set(fcol);
		frame->SetCustomColour(c.GetRGB());
		fcol="custom";
	}
	else
	{
		frame->SetCustomColour(mm[fcol].GetRGB());
		fcol = "custom";
	}
	if (wxString(bcol).StartsWith('#'))
	{
		c.Set(bcol);
		frame->SetColour(19, c.GetRGB());
		bcol="bcustom";
	}
	else
	{
		frame->SetColour(19, mm[bcol].GetRGB());
		bcol = "bcustom";
	}
	map<wxString, int> b = frame->GetBCol();
	ale_it it;
	
	for (unsigned long i= frame->GetEndLine();i<frame->GetStartLine();i++)
	{
		for (it = frame->GetLineStyle(i)->begin(); it!=frame->GetLineStyle(i)->end(); it++)
		{
			it->SetFCol(7, frame->GetColour(b[fcol]-40));
			it->SetBCol(0, frame->GetColour(b[bcol]-40));
		}
	}
	frame->Refresh();
	frame->Update();
	return 0;
}

//! wxamcl.colorline(foreground, background)
/*!
	colors the line to foreground background
	wxamcl.colorline("black", "black", amc.getlinenumber())
	\param lua_State *L: a valid lua_State
*/
int luafunc_colorline(lua_State*L)
{
	const char* fcol;
	const char* bcol;
	long nr;
	fcol=luaL_optstring(L, 1, "white");
	bcol=luaL_optstring(L, 2, "black");
	class MudWindow *frame = wxGetApp().GetFrame()->m_scriptwin;//
	if (frame==NULL)
		return 0;
	nr = luaL_optnumber(L, 3, frame->GetStartLine()-1);
	wxColour c;
	map<wxString, wxColour> mm = frame->GetMXPParser()->GetMXPColorMap();
	
	if (wxString(fcol).StartsWith('#'))
	{
		c.Set(fcol);
		frame->SetCustomColour(c.GetRGB());
		fcol="custom";
	}
	else
	{
		frame->SetCustomColour(mm[fcol].GetRGB());
		fcol = "custom";
	}
	if (wxString(bcol).StartsWith('#'))
	{
		c.Set(bcol);
		frame->SetColour(19, c.GetRGB());
		bcol="bcustom";
	}
	else
	{
		frame->SetColour(19, mm[bcol].GetRGB());
		bcol = "bcustom";
	}
	map<wxString, int> b = frame->GetBCol();
	
	ale_it it;
		
	for (it = frame->GetLineStyle(nr)->begin(); it!=frame->GetLineStyle(nr)->end(); it++)
		{
			it->SetFCol(7, frame->GetColour(b[fcol]-40));
			it->SetBCol(0, frame->GetColour(b[bcol]-40));
		}
	frame->Refresh();
	frame->Update();
	return 0;
}

//! wxamcl.colorword(word, foreground, background)
/*!
	colors all occurences of word in a line to foreground background
	
	wxamcl.colorword("Tom", "yellow", "blue")
	\param lua_State *L: a valid lua_State
*/
int luafunc_colorword(lua_State*L)
{
	const char* fcol;
	const char* bcol;
	const char* word;
	wxString a;
	
	word=luaL_checkstring(L, 1);
	fcol=luaL_optstring(L, 2, "white");
	bcol=luaL_optstring(L, 3, "black");
	class MudWindow *frame = wxGetApp().GetFrame()->m_scriptwin;
	if (frame==NULL)
		return 0;
	wxColour c;
	map<wxString, wxColour> mm = frame->GetMXPParser()->GetMXPColorMap();
	
	if (wxString(fcol).StartsWith('#'))
	{
		c.Set(fcol);
		frame->SetCustomColour(c.GetRGB());
		fcol="custom";
	}
	else
	{
		frame->SetCustomColour(mm[fcol].GetRGB());
		fcol = "custom";
	}
	if (wxString(bcol).StartsWith('#'))
	{
		c.Set(bcol);
		frame->SetColour(19, c.GetRGB());
		bcol="bcustom";
	}
	else
	{
		frame->SetColour(19, mm[bcol].GetRGB());
		bcol = "bcustom";
	}
	
	map<wxString, wxString> m = frame->GetColCodes();
	map<wxString, int> b = frame->GetBCol();
	wxString f = m[fcol];
	
	wxString ansi = frame->GetLines()->at(frame->m_curline-1).GetAnsiLine();
	class RegExp rexp(word);
	if (rexp.Match(ansi))
	{
		wxString msg;
		msg<<"\x1b["<<f.c_str()<<b[bcol]<<"m";
		ansi.insert(rexp.GetMatchStart(), msg);
		a = frame->FindPrevAnsi(ansi, rexp.GetMatchStart());
		ansi.insert(rexp.GetMatchEnd()+msg.length(), a);
		int x=0;
		while(rexp.GetMatchEnd()+1<(int)ansi.length())
		{
			x += rexp.GetMatchEnd()+msg.length();
			if (rexp.Match(ansi.substr(x+1)))
			{
				ansi.insert(rexp.GetMatchStart()+x+1, msg);
				a = frame->FindPrevAnsi(ansi, rexp.GetMatchStart()+x+1);
				ansi.insert(rexp.GetMatchEnd()+msg.length()+x+1, a);
				//ansi.insert(rexp.GetMatchEnd()+x+1+msg.length(), wxT("\x1b[0m"));
			}
			else break;
		}
		frame->GetLines()->pop_back();
		frame->m_curline--;
		bool p = wxGetApp().GetFrame()->TriggersOn();
		wxGetApp().GetFrame()->SetTriggersOn(false);
		frame->SetParseState(0);//HAVE_TEXT
		frame->ParseNBuffer(ansi.char_str());
		wxGetApp().GetFrame()->SetTriggersOn(p);
	}
	frame->Refresh();
	frame->Update();
	return 0;
}

int luafunc_replacetext(lua_State*L)
{
	const char* text;
	const char* replace;
	wxString a;
	
	text=luaL_checkstring(L, 1);
	replace=luaL_checkstring(L, 2);
	class MudWindow *frame = wxGetApp().GetFrame()->m_scriptwin;
	if (!frame)	
		return 0;
	
	wxString ansi = frame->GetLines()->at(frame->m_curline-1).GetAnsiLine();
	ansi.Replace(text, replace, true);
	frame->GetLines()->pop_back();
	frame->m_curline--;
	bool p = wxGetApp().GetFrame()->TriggersOn();
	wxGetApp().GetFrame()->SetTriggersOn(false);
	frame->SetParseState(0);//HAVE_TEXT
	frame->ParseNBuffer(ansi.char_str());
	wxGetApp().GetFrame()->SetTriggersOn(p);
	
	frame->Refresh();
	frame->Update();
	return 0;
}

int luafunc_getlinenr(lua_State *L)
{
	
	class MudWindow *frame = wxGetApp().GetFrame()->m_scriptwin;
	if (frame==NULL)
		return 0;
	lua_pushinteger(L, frame->GetLines()->at(frame->GetStartLine()-1).GetLinenumber());
	return 1;
}

int luafunc_scroll(lua_State *L)
{
	//class MudWindow *frame = (MudWindow*)MudWindow::FindWindowByName("amcoutput");
	class MudWindow *frame = wxGetApp().GetFrame()->m_scriptwin;
	if (frame==NULL)
		return 0;
	bool b = (lua_toboolean(L,1)!=0);
	frame->SetScroll(!b);
	return 0;
}

int luafunc_echowin(lua_State*L)
{
	const char* text;
	const char* winname;
	const char* fcol;
	const char* bcol;

	winname = luaL_checkstring(L, 1);
	text = luaL_checkstring(L, 2);
	fcol = luaL_optstring(L, 3, "silver");
	bcol = luaL_optstring(L, 4, "black");
	wxString name (winname);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	//class MudWindow *frame = (MudWindow*)MudWindow::FindWindowByName(*name);
	class MudWindow *frame = (MudWindow*)um[name];
	if (frame==NULL)
		return 0;
	
	//delete name;
//	class MudMainFrame *parent = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	AnsiLineElement ale;
	wxColour c;
	map<wxString, wxColour> m = wxGetApp().GetFrame()->m_scriptwin->GetMXPParser()->GetMXPColorMap();
	if (wxString(fcol).StartsWith('#'))
	{
		c.Set(fcol);
		ale.SetFCol(99, c);
	}
	else
		ale.SetFCol(99,m[fcol]);
	if (wxString(bcol).StartsWith('#'))
	{
		c.Set(bcol);
		ale.SetBCol(99, c);
	}
	else
		ale.SetBCol(99,m[bcol]);
	wxString ba = wxString::From8BitData(text);
	ale.SetText(ba);
	//ale.SetText(text);
	AnsiLine line;
	line.m_vstyle.push_back(ale);
	line.SetFull(true);
	line.SetLineText(ba);
	AnsiLineElement ale1;
	line.m_vstyle.push_back(ale1);
	if (frame->m_curline==0)
		line.SetLinenumber(frame->m_curline);
	else
		line.SetLinenumber(frame->GetLines()->at(frame->m_curline-1).GetLinenumber()+1);
	wxDateTime d;
	//d.SetToCurrent();
	d = wxDateTime::UNow();
	line.SetDateTimeMS(d);
	d = wxDateTime::Now();
	line.SetDateTime(d);
	frame->GetLines()->push_back(line);
	frame->m_curline++;
	//frame->Refresh();
	//frame->Update();
	lua_pushstring(L, text);
	
	
	if (!frame->GetScroll())
	{
		frame->SetScrollPage();
		frame->Refresh();
		frame->Update();
	}
	return 1;
}

int luafunc_getscript(lua_State *L)
{
	MudMainFrame *parent = wxGetApp().GetFrame();
	wxString s(parent->GetGlobalOptions()->GetScript());
	lua_pushstring(L, s.c_str());
	return 1;
}

int luafunc_logwin(lua_State *L)
{
	const char* winname;
	bool on_off = true;
	winname = luaL_checkstring(L, 1);
	on_off = lua_toboolean(L, 2) != 0;
	wxString name (winname);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	class MudWindow *frame = (MudWindow*)um[name];
	//class MudWindow *frame = (MudWindow*)MudWindow::FindWindowByName(*name);
	if (frame == NULL)
	{
		lua_pushnil(L);
		return 1;
	}
	//delete name;
	MudMainFrame *parent = wxGetApp().GetFrame();
	wxSetWorkingDirectory(parent->GetGlobalOptions()->GetWorkDir());
	wxSetWorkingDirectory(parent->GetGlobalOptions()->GetLogDir());
	wxString logfile = frame->GetName() << ".log";
	if (on_off)
	{
		if (::wxFileExists(logfile))
			::wxRemoveFile(logfile);
		frame->SetTextLog(new wxFile(logfile, wxFile::write));
		if (!frame->GetTextLog()->IsOpened())
		{
			lua_pushboolean(L, FALSE);
			return 1;
		}
		wxDateTime d;
		d.SetToCurrent();
		wxString s;
		s << _("Logging started: ") << d.FormatDate() << (", ") << d.FormatTime();
		frame->GetTextLog()->Write(s + (char)CR + (char)LF + (char)CR + (char)LF);
		frame->SetLogging(true);
		frame->SetDateLogging(true);
	}
	else
	{
		frame->SetLogging(false);
		frame->SetDateLogging(false);
		frame->GetTextLog()->Close();
		//frame->SetTextLog(nullptr);
	}
	lua_pushboolean(L, TRUE);
	return 1;
}

int luafunc_drawcircle(lua_State*L)
{
	const char* winname;
	const char* fcol;
	const char* bcol;
	int x,y,rad;
	bool full = false;
	winname = luaL_checkstring(L, 1);
	x = (int)luaL_optnumber(L, 2, 100);
	y = (int)luaL_optnumber(L, 3, 100);
	rad = (int)luaL_optnumber(L, 4, 100);
	full = lua_toboolean(L,5)!=0;
	fcol = luaL_optstring(L, 6, "silver");
	bcol = luaL_optstring(L, 7, "black");
	const wxString name (winname);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	class amcWindow *frame = (amcWindow*)um[name];
	//class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	//delete name;

	wxColour c, c1;
	map<wxString, wxColour> m = wxGetApp().GetFrame()->m_scriptwin->GetMXPParser()->GetMXPColorMap();
	if (wxString(bcol).StartsWith('#'))
	{
		c.Set(bcol);
	}
	else c = m[bcol];
	if (wxString(fcol).StartsWith('#'))
	{
		c1.Set(fcol);
	}
	else c1 = m[fcol];
	wxBrush b(c);
	wxPen p(c1);
	if (!full)
		frame->GetamcWinDC()->SetBrush(*wxTRANSPARENT_BRUSH);
	else frame->GetamcWinDC()->SetBrush(b);
	frame->GetamcWinDC()->SetPen(p);
	frame->GetamcWinDC()->DrawCircle( x, y, rad);
	//lua_pushstring(L, text);
	frame->Refresh();
	return 1;
}

int luafunc_drawsquare(lua_State *L)
{
	const char* winname;
	const char* fcol;
	const char* bcol;
	int x,y,cx,cy;
	int def = 100;
	bool full = false;
	winname = luaL_checkstring(L, 1);
	x = (int)luaL_optnumber(L, 2, def);
	//x = (int)luaL_optinteger(L, 2, def);
	y = (int)luaL_optnumber(L, 3, def);
	cx = (int)luaL_optnumber(L, 4, 100);
	cy = (int)luaL_optnumber(L, 5, 100);
	full = lua_toboolean(L,6)!=0;
	fcol = luaL_optstring(L, 7, "silver");
	bcol = luaL_optstring(L, 8, "black");
	const wxString name (winname);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	class amcWindow *frame = (amcWindow*)um[name];
	//class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	//delete name;
//	class MudMainFrame *parent = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	wxColour c, c1;
	map<wxString, wxColour> m = wxGetApp().GetFrame()->m_scriptwin->GetMXPParser()->GetMXPColorMap();
	if (wxString(bcol).StartsWith('#'))
	{
		c.Set(bcol);
	}
	else c = m[bcol];
	if (wxString(fcol).StartsWith('#'))
	{
		c1.Set(fcol);
	}
	else c1 = m[fcol];
	wxBrush b(c);
	wxPen p(c1);
	if (!full)
		frame->GetamcWinDC()->SetBrush(*wxTRANSPARENT_BRUSH);
	else frame->GetamcWinDC()->SetBrush(b);
	frame->GetamcWinDC()->SetPen(p);
	frame->GetamcWinDC()->DrawRectangle(x,y,cx,cy);
	//lua_pushstring(L, text);
	frame->Refresh();
	return 1;
}

int luafunc_drawline(lua_State *L)
{
	const char* winname;
	const char* fcol;
	int x,y,cx,cy;
	winname = luaL_checkstring(L, 1);
	x = (int)luaL_optnumber(L, 2, 100);
	y = (int)luaL_optnumber(L, 3, 100);
	cx = (int)luaL_optnumber(L, 4, 100);
	cy = (int)luaL_optnumber(L, 5, 100);
	fcol = luaL_optstring(L, 6, "silver");
	const wxString name (winname);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	class amcWindow *frame = (amcWindow*)um[name];
	//class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	//delete name;
//	class MudMainFrame *parent = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	wxColour c, c1;
	map<wxString, wxColour> m = wxGetApp().GetFrame()->m_scriptwin->GetMXPParser()->GetMXPColorMap();
	
	if (wxString(fcol).StartsWith('#'))
	{
		c1.Set(fcol);
	}
	else c1 = m[fcol];
	
	wxPen p(c1);
	frame->GetamcWinDC()->SetPen(p);
	frame->GetamcWinDC()->DrawLine(x,y,cx,cy);
	//lua_pushstring(L, text);
	frame->Refresh();
	return 1;
}

int luafunc_drawtext(lua_State*L)
{
	const char* winname;
	const char* fcol;
	const char* bcol;
	const char* text;
	int x, y, bb;

	winname = luaL_checkstring(L, 1);
	text = luaL_optstring(L, 2, "");
	x = (int)luaL_optnumber(L, 3, 1);
	y = (int)luaL_optnumber(L, 4, 1);
	fcol = luaL_optstring(L, 5, "silver");
	bcol = luaL_optstring(L, 6, "black");
	bb = (int)luaL_optnumber(L,7,0);
	const wxString name (winname);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	class amcWindow *frame = (amcWindow*)um[name];
	//class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	//delete name;

	wxColour f, b;
	map<wxString, wxColour> m = wxGetApp().GetFrame()->m_scriptwin->GetMXPParser()->GetMXPColorMap();
	if (wxString(fcol).StartsWith('#'))
	{
		f.Set(fcol);
	}
	else f = m[fcol];
	if (wxString(bcol).StartsWith('#'))
	{
		b.Set(bcol);
	}
	else b = m[bcol];
	if (bb)
		frame->GetamcWinDC()->SetBackgroundMode(wxSOLID);
	frame->GetamcWinDC()->SetTextForeground(f);
	frame->GetamcWinDC()->SetTextBackground(b);
	wxString t(text, wxCSConv(wxGetApp().GetFrame()->GetGlobalOptions()->GetCurEncoding()));
	frame->GetamcWinDC()->DrawText(t, x, y);
	frame->GetamcWinDC()->SetBackgroundMode(wxTRANSPARENT);
	frame->Refresh();
	return 0;
}

int luafunc_setfont(lua_State *L)
{
	const char* win;
	const char* font;
	int psize;
	win = luaL_checkstring(L, 1);
	const wxString name (win);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	class amcWindow *frame = (amcWindow*)um[name];
	//class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	//delete name;
	font = luaL_checkstring(L,2);
	psize = luaL_checknumber(L,3);
	wxFont *f = new wxFont(psize, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, font);
	frame->GetamcWinDC()->SetFont(*f);
	delete f;
	return 0;
}
int luafunc_drawbitmap(lua_State *L)
{
	const char* winname;
	const char* bmap;
	winname = luaL_checkstring(L, 1);
	const wxString name (winname);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	class amcWindow *frame = (amcWindow*)um[name];
	//class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	//delete name;
	bmap = luaL_checkstring(L, 2);
	int mode = (int)luaL_optnumber(L, 3, 0);
	int x = (int)luaL_optnumber(L,4,0);
	int y = (int)luaL_optnumber(L,5, 0);
	int cx = (int)luaL_optnumber(L,6,0);
	int cy = (int)luaL_optnumber(L,7,0);
	
	class MudMainFrame *parent = wxGetApp().GetFrame();
	wxSetWorkingDirectory(parent->GetGlobalOptions()->GetWorkDir());
	wxBitmap bm(bmap, wxBITMAP_TYPE_ANY);

	if (!mode)
		frame->GetamcWinDC()->DrawBitmap(bm, x, y);
	else if (mode==1) //scale
		{
			wxImage img = bm.ConvertToImage();
			img.Rescale(cx, cy);
			wxBitmap bmp(img);
			frame->GetamcWinDC()->DrawBitmap(bmp, x, y);
		}
	else if (mode==2) //tile
	{
		int w = bm.GetWidth();
		int h = bm.GetHeight();
		int ww , hh; 
		frame->GetClientSize(&ww, &hh);
		int col = abs(ww/w);
		int row = abs(hh/h);
		for (int i=0;i<=row;i++)
		{
			for (int ii=0;ii<=col;ii++)
				frame->GetamcWinDC()->DrawBitmap(bm, 0+ii*w, 0+i*h);
		}
	}
	frame->Refresh();
	return 0;
}


int luafunc_clear(lua_State *L)
{
	const char* winname;
	winname = luaL_checkstring(L, 1);
	const wxString name (winname);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	class amcWindow *frame = (amcWindow*)um[name];
	//class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	//delete name;
	frame->GetamcWinDC()->Clear();
	frame->Update();
	return 0;
}

int luafunc_refresh(lua_State *L)
{
	const char* winname;
	winname = luaL_checkstring(L, 1);
	const wxString name (winname);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	class amcWindow *frame = (amcWindow*)um[name];
	//class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	//delete name;
	frame->Refresh();
	frame->Update();
	return 0;
}

int luafunc_amcwinsize(lua_State *L)
{
	const char* winname;
	winname = luaL_checkstring(L, 1);
	const wxString name (winname);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	class amcWindow *frame = (amcWindow*)um[name];
	//class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	//delete name;
	int width, height;
	frame->GetClientSize(&width, &height);
	lua_pushinteger(L, width);
	lua_pushinteger(L, height);
	return 2;
}

int luafunc_seteventfile(lua_State *L)
{
	const char* s;
	s = luaL_checkstring(L, 1);
	const wxString name(s);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	class amcWindow *frame = (amcWindow*)um[name];
	//class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	//delete name;
	s = luaL_checkstring(L,2);
	wxSetWorkingDirectory(wxGetApp().GetFrame()->GetGlobalOptions()->GetScriptDir());
	luaL_dofile(L, s);
	frame->SetEvFile(wxString(s));
	//lua_setglobal(L, s);
	return 1;
}

int luafunc_registerlefthandler(lua_State *L)
{
	const char* s;
	s = luaL_checkstring(L, 1);
	const wxString name(s);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	class amcWindow *frame = (amcWindow*)um[name];
	//class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	//delete name;
	s = luaL_checkstring(L,2);
	frame->SetLeftHandler(wxString(s));
	//lua_setglobal(L, s);
	return 0;
}

int luafunc_registerrighthandler(lua_State *L)
{
	const char* s;
	s = luaL_checkstring(L, 1);
	const wxString name(s);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	class amcWindow *frame = (amcWindow*)um[name];
	//class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	//delete name;
	s = luaL_checkstring(L,2);
	frame->SetRightHandler(wxString(s));
	//lua_setglobal(L, s);
	return 1;
}

int luafunc_registerwheelhandler(lua_State *L)
{
	const char* s;
	s = luaL_checkstring(L, 1);
	const wxString name(s);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	class amcWindow *frame = (amcWindow*)um[name];
	//class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	//delete name;
	s = luaL_checkstring(L,2);
	frame->SetWheelHandler(wxString(s));
	//lua_setglobal(L, s);
	return 1;
}

int luafunc_registermovehandler(lua_State *L)
{
	const char* s;
	s = luaL_checkstring(L, 1);
	const wxString name(s);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	class amcWindow *frame = (amcWindow*)um[name];
	//class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	//delete name;
	s = luaL_checkstring(L,2);
	frame->SetMoveHandler(wxString(s));
	//lua_setglobal(L, s);
	return 1;
}

int luafunc_mouseevents(lua_State *L)
{
	const char* s;
	s = luaL_checkstring(L, 1);
	const wxString name(s);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	class amcWindow *frame = (amcWindow*)um[name];
	//class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	//delete name;
	bool b = lua_toboolean(L,2)!=0;
	if (b)
		frame->EnableMouseEvents();
	else frame->DisableMouseEvents();
	//lua_setglobal(L, s);
	return 0;
}

int luafunc_settip(lua_State *L)
{
	const char* s;
	s = luaL_checkstring(L, 1);
	const wxString name(s);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	class amcWindow *frame = (amcWindow*)um[name];
	//class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	//delete name;
	s = luaL_checkstring(L,2);
	//frame->GetToolTip()->SetMaxWidth(-1);
	frame->SetTip(wxString(s));
	return 0;
}

int luafunc_getline(lua_State *L)
{
	wxUint32 nr = luaL_checknumber(L, 1);
	AnsiLine line = wxGetApp().GetFrame()->m_scriptwin->GetLines()->at(nr);
	ale_it it;
	lua_settop(L,0);
	lua_newtable(L);
	int x= 1;
	for (it=line.GetStyle()->begin();it!=line.GetStyle()->end();it++, x++)
	{
		//lua_settop(L,0);
		lua_newtable(L);
		
		lua_pushstring(L, it->GetText().c_str());
		lua_setfield(L, -2, "text");
		lua_pushinteger(L, it->GetLen());
		lua_setfield(L, -2, "length");
		lua_pushstring(L, it->GetFCol().GetAsString(wxC2S_HTML_SYNTAX).c_str());
		lua_setfield(L, -2, "fore");
		lua_pushstring(L, it->GetBCol().GetAsString(wxC2S_HTML_SYNTAX).c_str());
		lua_setfield(L, -2, "back");
		lua_rawseti(L, -2, x);
	}
	return 1;
}


int luafunc_createnb(lua_State*L)
{
	const char* winname, *pagename;
	wxAuiNotebook *nb;
	class MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	size_t i;
	winname = luaL_checkstring(L,1);
	wxString name(winname);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	nb = (wxAuiNotebook*)um[name];
	//nb = (wxAuiNotebook*)wxWindow::FindWindowByName(winname, frame);
	if (!nb)
	{
		nb = new wxAuiNotebook(frame);
		nb->SetLabel(name);
		nb->SetName(name);
		frame->GetNbs()->push_back(name);
		vector<wxString> s;
		frame->GetNbPanes()->push_back(s);
		frame->m_mgr.AddPane(nb, wxAuiPaneInfo().Name(name).Caption(name).CaptionVisible(true).Floatable(true).FloatingSize(400,200).BestSize(400,200).Dockable(true).Dock().Top().Layer(1).Show());
		um[name] = nb;
	}
	
	pagename = luaL_checkstring(L, 2);
	wxString page(pagename, co);
	
	MudWindow *mw = wxGetApp().GetFrame()->m_scriptwin;
	
	vector<vector<wxString> >::iterator vit;
	if (!mw->GetNbPanes()->empty())
	{
		int x = 0;
		for (vit = mw->GetNbPanes()->begin(); vit != mw->GetNbPanes()->end(); vit++, x++)
		{
			for (size_t i = 0; i < vit->size(); i++)
			{
				wxString s = vit->at(i);
				if (page == s)
					return 0;

			}
		}
	}
	if (!frame->GetNbs()->empty())
	{
		for (i=0;i<frame->GetNbs()->size();i++)
		{
			if (winname==frame->GetNbs()->at(i))
				break;
		}
	}
	frame->GetNbPanes()->at(i).push_back(page);
	MudWindow *pg = new MudWindow(frame, page, 9);
	nb->AddPage(pg, page);
	//um[page] = pg;
	frame->m_mgr.Update();
	lua_pushlightuserdata(L, um[name]);//(void*)nb->FindWindowByName(winname));
	frame->m_scriptwin->SetNbPanes(*frame->GetNbPanes());
	frame->m_scriptwin->SetNbs(*frame->GetNbs());
	frame->m_scriptwin->SetUserWindows(um);
	//delete name;
	return 1;
}

int luafunc_addpagenb(lua_State*L)
{
	const char* winname;
	const char* pagename;
	int i;
	class MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	winname = luaL_checkstring(L,1);
	pagename = luaL_checkstring(L,2);
	wxString name(winname, co);
	wxString page(pagename, co);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	wxAuiNotebook *nb = (wxAuiNotebook*)um[name];
	//wxAuiNotebook *nb = (wxAuiNotebook*)wxAuiNotebook::FindWindowByName(winname, frame);
	if (nb == NULL)
	{
		lua_pushnil(L);
		return 1;
	}
	if (!frame->GetNbs()->empty())
	{
		for (i=0;i<(int)frame->GetNbs()->size();i++)
		{
			if (winname==frame->GetNbs()->at(i))
				break;
		}
	}
	frame->GetNbPanes()->at(i).push_back(pagename);
	MudWindow *mw = new MudWindow(frame, page, 9);
	nb->AddPage(mw, page);
	um[page] = mw;
	frame->m_mgr.Update();
	frame->m_scriptwin->SetNbPanes(*frame->GetNbPanes());
	frame->m_scriptwin->SetUserWindows(um);
	lua_pushboolean(L, TRUE);
	return 1;
}

//! wxamcl.createwindow(windowname)
/*!
	creates a window, implements the lua command. Will do nothing if a window with this name already exists */
/*!	syntax in lua: wxamcl.createwindow("Name")
	\param lua_State *L: a valid lua_State
	\returns nothing
	\sa luafunc_showwindow, luafunc_hidewindow, luafunc_createnb
*/
int luafunc_createwindow(lua_State*L)
{
	const char* winname;
	MudWindow *mw;
	wxColour c;
	
	class MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	
	winname = luaL_checkstring(L,1);
	const char* col = luaL_optstring(L, 2, "black");
	wxString wname(winname, co);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	mw = (MudWindow*)um[wname];
	//mw = (MudWindow*)MudWindow::FindWindowByName(wname, frame);
	if (mw)
		return 0;
	
	mw = new MudWindow(frame, wname, 9);
	mw->SetName(wname);
	wxString s(col);
	if (s.at(0)=='#')
	{
		long bcol = mw->ParseHexColor(s.substr(1));
		c.Set(bcol);
		mw->SetBackgroundCol(c);	
	}
	
	else
	{
		map<wxString, int> b = mw->GetBCol();
		int x = b[col]-40;
		if (x>=0 && x < 16)
			c = mw->GetAnsiColor(b[col]-40);
		else
		{
			c.Set(col);
		}
		mw->SetBackgroundCol(c);
	}
	frame->GetPanes()->push_back(wname);//save all the windows we have
	um[wname] = mw;
	frame->m_mgr.AddPane(mw, wxAuiPaneInfo().Name(wname).Caption(wname).CaptionVisible(true).Floatable(true).FloatingSize(400,200).BestSize(400,200).Dockable(true).Dock().Top().Layer(1).Hide().MinimizeButton());
	frame->m_scriptwin->SetUserWindows(um);
	
	frame->m_mgr.GetPane(mw).Show();
	frame->m_mgr.Update();	
	frame->Refresh();
	frame->Update();
	frame->m_scriptwin->SetPanes(*frame->GetPanes());
	frame->m_scriptwin->Refresh();
	frame->m_scriptwin->Update();
	frame->m_scriptwin->SetUserWindows(um);
	return 0;
}

//! wxamcl.hidewindow(windowname)

/*!	hides a window - implements the lua script command. */
/*! The syntax in lua is: wxamcl.hidewindow("Name")
* \param lua_State *L: a valid lua_State
* \returns nothing
* \sa luafunc_showwindow, luafunc_createwindow
*/

int luafunc_hidewindow(lua_State*L)
{
	char* winname;
	MudWindow *mw;
	
	class MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	winname = (char*)luaL_checkstring(L,1);
	wxString wname(winname, co);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	mw = (MudWindow*)um[wname];
	//mw = (MudWindow*)MudWindow::FindWindowByName(winname, frame);
	if (!mw)
	{
		lua_pushnil(L);
		return 1;
	}
	
	frame->m_mgr.GetPane(wname).Hide();
	frame->m_mgr.Update();
	lua_pushboolean(L, TRUE);
	return 1;
}

//! wxamcl.showwindow(windowname)

//!	shows a (hidden) window in lua
//!	wamcl.showwindow("Name")
//!	\param lua_State *L: a valid lua_State

int luafunc_showwindow(lua_State*L)
{
	const char* winname;
	MudWindow *mw;
	
	class MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	winname = (char*)luaL_checkstring(L,1);
	wxString wname(winname, co);
	unordered_map<wxString, wxWindow*> um = *frame->m_scriptwin->GetUserWindows();
	mw = (MudWindow*)um[wname];
	//mw = (MudWindow*)MudWindow::FindWindowByName(winname, frame);
	if (!mw)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->m_mgr.GetPane(wname).Show();
	frame->m_mgr.Update();
	frame->Refresh();
	frame->Update();
	lua_pushboolean(L, TRUE);
	return 1;
}

//! wxamcl.caption(windowname, caption, true|false)

//!	shows or hides caption of a userwindow in lua
//!	wamcl.caption("Name", "Caption", true)
//!	\param lua_State *L: a valid lua_State
int luafunc_captionwindow(lua_State *L)
{
	const char* winname;
	const char* caption;
	bool bo;
	MudWindow *mw;
	
	class MudMainFrame *frame = wxGetApp().GetFrame();
	winname = (char*)luaL_checkstring(L, 1);
	caption = (char*)luaL_optstring(L, 2, "Caption");
	bo = lua_toboolean(L, 3);
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	wxString wname(winname, co);
	unordered_map<wxString, wxWindow*> um = *frame->m_scriptwin->GetUserWindows();
	mw = (MudWindow*)um[wname];
	//mw = (MudWindow*)MudWindow::FindWindowByName(winname, frame);
	if (!mw)
	{
		lua_pushnil(L);
		return 1;
	}
	if (bo)
		frame->m_mgr.GetPane(wxString(wname)).Caption(wxString(caption)).CaptionVisible(bo);
	else
		frame->m_mgr.GetPane(wxString(wname)).CaptionVisible(false).Caption(wxString(caption));
	frame->m_mgr.Update();
	frame->Refresh();
	frame->Update();
	lua_pushboolean(L, TRUE);
	return 1;
}

int luafunc_floatwindow(lua_State *L)
{
	const char* winname;
	MudWindow *mw;

	class MudMainFrame *frame = wxGetApp().GetFrame();
	winname = (char*)luaL_checkstring(L, 1);
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	
	wxString wname(winname, co);
	unordered_map<wxString, wxWindow*> um = *frame->m_scriptwin->GetUserWindows();
	mw = (MudWindow*)um[wname];
	//mw = (MudWindow*)MudWindow::FindWindowByName(winname, frame);
	if (!mw)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->m_mgr.GetPane(wname).Float();
	frame->m_mgr.Update();
	lua_pushboolean(L, TRUE);
	return 1;
}

int luafunc_dockwindow(lua_State *L)
{
	const char* winname;
	MudWindow *mw;

	class MudMainFrame *frame = wxGetApp().GetFrame();
	winname = (char*)luaL_checkstring(L, 1);
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	wxString wname(winname, co);
	unordered_map<wxString, wxWindow*> um = *frame->m_scriptwin->GetUserWindows();
	mw = (MudWindow*)um[wname];
	//mw = (MudWindow*)MudWindow::FindWindowByName(winname, frame);
	if (!mw)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->m_mgr.GetPane(wname).Dock();
	frame->m_mgr.Update();
	lua_pushboolean(L, TRUE);
	return 1;
}

//! wxamcl.clearwindow(windowname)

//!	clears window in lua
//!	wxamcl.clearwindow("Name")
//!	\param lua_State *L: a valid lua_State

int luafunc_clearwindow(lua_State *L)
{
	const char* winname;
	MudWindow *mw;
	class MudMainFrame *frame = wxGetApp().GetFrame();
	winname = luaL_checkstring(L,1);
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	wxString wname(winname, co);
	unordered_map<wxString, wxWindow*> um = *frame->m_scriptwin->GetUserWindows();
	mw = (MudWindow*)um[wname];
	//mw = (MudWindow*)MudWindow::FindWindowByName(winname, frame);
	if (!mw)
	{
		lua_pushnil(L);
		return 1;
	}
	mw->ClearLines();
	lua_pushboolean(L, TRUE);
	return 1;
}

int luafunc_destroywindow(lua_State *L)
{
	const char* winname = luaL_checkstring(L,1);
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	wxString wname(winname, co);
	unordered_map<wxString, wxWindow*> um = *frame->m_scriptwin->GetUserWindows();
	MudWindow* mw = (MudWindow*)um[wname];
	//MudWindow* mw = (MudWindow*)MudWindow::FindWindowByName(name, frame);
	if (!mw)
	{
		lua_pushnil(L);
		return 1;
	}
	s_it sit;
		
	if (!frame->GetPanes()->empty())
	{
		for (sit=frame->GetPanes()->begin();sit!=frame->GetPanes()->end();sit++)
		{
			if (!wname.compare(sit->c_str()))
			{
				frame->GetPanes()->erase(sit);
				break;
			}
		}
	}
	frame->m_mgr.GetPane(wname).Hide();
	frame->m_mgr.DetachPane(mw);
	frame->m_mgr.Update();
	mw->Destroy();
	frame->m_scriptwin->SetPanes(*frame->GetPanes());
	um.erase(wname);
	frame->m_scriptwin->SetUserWindows(um);
	lua_pushboolean(L, TRUE);
	return 1;
}

int luafunc_destroyamcwindow(lua_State *L)
{
	const char* name = luaL_checkstring(L,1);
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	wxString wname(name, co);
	unordered_map<wxString, wxWindow*> um = *frame->m_scriptwin->GetUserWindows();
	amcWindow* mw = (amcWindow*)um[wname];
	//amcWindow* mw = (amcWindow*)amcWindow::FindWindowByName(name, frame);
	if (!mw)
	{
		lua_pushnil(L);
		return 1;
	}
	s_it sit;
	
	
	if (!frame->GetAmcWindows()->empty())
	{
		for (sit=frame->GetAmcWindows()->begin();sit!=frame->GetAmcWindows()->end();sit++)
		{
			if (!wname.compare(sit->c_str()))
			{
				frame->GetAmcWindows()->erase(sit);
				break;
			}
		}
	}
	frame->m_mgr.GetPane(wname).Hide();
	frame->m_mgr.DetachPane(mw);
	frame->m_mgr.Update();
	mw->Destroy();
	frame->m_scriptwin->SetAmcWindows(*frame->GetAmcWindows());
	um.erase(wname);
	frame->m_scriptwin->SetUserWindows(um);
	lua_pushboolean(L, TRUE);
	return 1;
}

int luafunc_destroynb(lua_State *L)
{
	const char* name = luaL_checkstring(L,1);
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	wxString wname(name, co);
	unordered_map<wxString, wxWindow*> um = *frame->m_scriptwin->GetUserWindows();
	wxAuiNotebook* mw = (wxAuiNotebook*)um[wname];
	//wxAuiNotebook* mw = (wxAuiNotebook*)wxAuiNotebook::FindWindowByName(name, frame);
	if (!mw)
	{
		lua_pushnil(L);
		return 1;
	}
	s_it sit;
	
	size_t i=0;
	
	if (!frame->GetNbs()->empty())
	{
		for (sit=frame->GetNbs()->begin();sit!=frame->GetNbs()->end();sit++,i++)
		{
			if (!wname.compare(sit->c_str()))
			{
				frame->GetNbs()->erase(sit);
				break;
			}
		}
	}
	vector<vector<wxString> >::iterator ssit;
	ssit = frame->GetNbPanes()->begin()+i;
	frame->GetNbPanes()->erase(ssit);
	//frame->GetNbPanes()->at(i).clear();
	frame->m_mgr.GetPane(wname).Hide();
	frame->m_mgr.DetachPane(mw);
	frame->m_mgr.Update();
	frame->m_scriptwin->SetNbs(*frame->GetNbs());
	frame->m_scriptwin->SetNbPanes(*frame->GetNbPanes());
	um.erase(wname);
	frame->m_scriptwin->SetUserWindows(um);
	mw->Destroy();
	lua_pushboolean(L, TRUE);
	return 1;
}

int luafunc_setbackground(lua_State*L)
{
MudWindow* mw;
wxWindow *win;
wxColour c;
	const char* winname = luaL_checkstring(L,1);
	const char* col = luaL_optstring(L, 2, "black"); 
	class MudMainFrame *frame = wxGetApp().GetFrame();

	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	wxString wname(winname, co);
	unordered_map<wxString, wxWindow*> um = *frame->m_scriptwin->GetUserWindows();
	win = (MudWindow*)um[wname];
	//win = MudWindow::FindWindowByName(winname, frame);
	
	if (!win)
	{
		lua_pushnil(L);
		return 1;
	}
	wxString s(col);
	if (s.at(0) == '#')
		c.Set(s);
	else
	{
		map<wxString, int> b = frame->m_scriptwin->GetBCol();
		int x = b[col] - 40;
		if (x >= 0 && x < 16)
			c = frame->m_scriptwin->GetAnsiColor(b[col] - 40);
		else if (x > 16)
		{
			c.Set(col);
		}
		else
		{
			map<wxString, wxColour> m = frame->m_scriptwin->GetMXPParser()->GetMXPColorMap();
			wxString cc(m[col].GetAsString());
			c.Set(cc);
		}
	}
	
	
	
	if (win->IsKindOf(CLASSINFO(MudWindow)))
	{
		mw = (MudWindow*)win;
		mw->SetBackgroundCol(c);
	}
	else if (win->IsKindOf(CLASSINFO(GaugeWindow)))
	{
		GaugeWindow* gw = (GaugeWindow*)win;
		//c.Set(col);
		gw->SetBackgroundCol(c);
	}
	else if (win->IsKindOf(CLASSINFO(amcWindow)))
	{
		amcWindow* aw = (amcWindow*)win;
		//c.Set(col);
		aw->SetBackground(c);
	}
	lua_pushboolean(L, TRUE);
	return 1;
}

int luafunc_createamcwin(lua_State*L)
{
	const char* winname;
	amcWindow *mw;
	wxColour c;
	
	class MudMainFrame *frame = wxGetApp().GetFrame();
	winname = luaL_checkstring(L,1);
	const char* col = luaL_optstring(L, 2, "black"); 
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	
	wxString wname(winname, co);
	unordered_map<wxString, wxWindow*> um = *frame->m_scriptwin->GetUserWindows();
	mw = (amcWindow*)um[wname];
	//mw = (amcWindow*)amcWindow::FindWindowByName(winname, frame);
	if (mw)
		return 0;
	mw = new amcWindow(frame, wname);
	mw->SetName(wname);
	um[wname] = mw;
	wxString s(col);
	if (s.at(0)=='#')
	{
		long bcol = frame->m_scriptwin->ParseHexColor(s.substr(1));
		c.Set(bcol);
		mw->SetBackground(c);	
	}
	
	else
	{
		map<wxString, int> b = frame->m_scriptwin->GetBCol();
		int x = b[col]-40;
		if (x>=0 && x < 16)
			c = frame->m_scriptwin->GetAnsiColor(b[col]-40);
		else
		{
			c.Set(col);
		}
		mw->SetBackground(c);
	}
	frame->GetAmcWindows()->push_back(wname);//save all the windows we have
	frame->m_mgr.AddPane(mw, wxAuiPaneInfo().Name(wname).Caption(wname).CaptionVisible(true).Floatable(true).FloatingSize(400,200).BestSize(400,200).Dockable(true).Dock().Top().Layer(1).Hide());
	frame->m_mgr.GetPane(mw).Show();
	frame->m_mgr.Update();	
	frame->Refresh();
	frame->Update();
	frame->m_scriptwin->SetAmcWindows(*frame->GetAmcWindows());
	frame->m_scriptwin->SetUserWindows(um);
	frame->m_scriptwin->Refresh();
	frame->m_scriptwin->Update();
	
	return 0;
}

//! wxamcl.createtoolbar(windowname)
/*!
	creates a toolbar for user buttons */
/*!	syntax in lua: wxamcl.createtoolbar("Name")
	\param lua_State *L: a valid lua_State
	\returns nothing
	\sa luafunc_showwindow, luafunc_hidewindow, luafunc_createnb
*/
int luafunc_createtoolbar(lua_State*L)
{
	const char* winname;
	wxAuiToolBar *tb;
	class MudMainFrame *frame = wxGetApp().GetFrame();
	
	winname = luaL_checkstring(L,1);
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	wxString wname(winname, co);
	
	unordered_map<wxString, wxWindow*> um = *frame->m_scriptwin->GetUserWindows();
	tb = (wxAuiToolBar*)um[wname];
	//tb = (wxAuiToolBar*)MudMainFrame::FindWindowByName(winname, frame);
	if (tb)
		return 0;
	tb = new wxAuiToolBar(frame, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_TEXT | wxAUI_TB_GRIPPER);
	tb->SetName(wname);
	tb->SetToolTextOrientation(wxAUI_TBTOOL_TEXT_RIGHT);
	um[wname] = tb;
	
	frame->m_mgr.AddPane(tb, wxAuiPaneInfo().Name(winname).Caption(winname).ToolbarPane().CaptionVisible(false).Floatable(true).BestSize(600, 24).LeftDockable(true).Dockable(true).Dock().Top());
	
	frame->m_mgr.GetPane(tb).Show();
	frame->m_mgr.Update();	
	frame->Refresh();
	frame->Update();
	frame->m_scriptwin->SetUserWindows(um);
	frame->m_scriptwin->Refresh();
	frame->m_scriptwin->Update();
	return 0;
}

int luafunc_addbutton(lua_State *L)
{
const char* winname;
wxAuiToolBar *tb;
amcButton b;
	class MudMainFrame *frame = wxGetApp().GetFrame();
	winname = luaL_checkstring(L,1);
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	wxString wname(winname, co);
	
	unordered_map<wxString, wxWindow*> um = *frame->m_scriptwin->GetUserWindows();
	tb = (wxAuiToolBar*)um[wname];
	
	//tb = (wxAuiToolBar*)MudMainFrame::FindWindowByName(winname, frame);
	
	if (!tb)
		return 0;
	int id = luaL_checkinteger(L, 4);
	if (id<0 || id>1000)
	{
		frame->m_scriptwin->Msg(_("Id for user button needs to be >0 and <1000"), 3);
		return 0;
	}
	tb->AddTool(ID_USERBUTTON + luaL_checkinteger(L, 4), luaL_checkstring(L,2), script_xpm);
	tb->SetToolTextOrientation(wxAUI_TBTOOL_TEXT_RIGHT);
	b.SetName(luaL_checkstring(L, 2));
	b.SetText(luaL_checkstring(L, 2));
	b.SetAction(luaL_checkstring(L, 3));
	b.SetId(ID_USERBUTTON + luaL_checkinteger(L, 4));
	b.SetActive(true);
	b.SetParent(tb);
	b.SetTbName(wname);
	frame->GetButtons()->push_back(b);
	frame->m_scriptwin->SetButtons(*frame->GetButtons());
	tb->Realize();
	frame->m_mgr.Update();
	return 0;
}

int luafunc_loadprofile(lua_State *L)
{
	MudMainFrame *frame = wxGetApp().GetFrame();
	const char* l = (char*)luaL_checkstring(L,1);
	if (frame->LoadProfile(wxFileName(l)))
	{
		lua_pushinteger(L, frame->GetTrigger()->size());
		lua_pushinteger(L, frame->GetAlias()->size());
		lua_pushinteger(L, frame->GetHotkeys()->size());
		lua_pushinteger(L, frame->GetVars()->size());
		lua_pushinteger(L, frame->GetLists()->size());
		return 5;
	}
	else return 0;
}

int luafunc_convertprofile(lua_State *L)
{
	MudMainFrame *frame = wxGetApp().GetFrame();
	const char *file = luaL_checkstring(L, 1);
	int id = luaL_checkinteger(L, 2);//source file 0=MSW, 1=UNIX, 2=OSX
	//wxString s = frame->GetGlobalOptions()->GetWorkDir();
	wxFileName fn(frame->GetGlobalOptions()->GetWorkDir());
	frame->LoadProfile(wxFileName(file));
	frame->GetGlobalOptions()->SetWorkDir(fn.GetFullPath());
	wxFileName fn1;
	fn1.AssignDir(fn.GetFullPath());
	fn1.AppendDir("scripts");
	frame->GetGlobalOptions()->SetScriptDir(fn1.GetFullPath());
	fn1.AssignDir(fn.GetFullPath());
	fn1.AppendDir("logs");
	frame->GetGlobalOptions()->SetLogDir(fn1.GetFullPath());
	fn1.AssignDir(fn.GetFullPath());
	fn1.AppendDir("packages");
	frame->GetGlobalOptions()->SetPackageDir(fn1.GetFullPath());
	fn1.AssignDir(fn.GetFullPath());
	fn1.AppendDir("sounds");
	frame->GetGlobalOptions()->SetSoundDir(fn1.GetFullPath());
	fn1.AssignDir(fn.GetFullPath());
	fn1.AppendDir("lua");
	frame->GetGlobalOptions()->SetLuaDir(fn1.GetFullPath());
	fn1.AssignDir(fn.GetFullPath());
	fn1.AppendDir("databases");
	frame->GetGlobalOptions()->SetDatabaseDir(fn1.GetFullPath());
	wxString evf;
	wxString evx;
	for (size_t i=0; i< frame->GetPackages()->size(); i++)
	{
		wxString s= frame->GetPackages()->at(i);
		switch (id)
		{
		case 0://MSW
			wxFileName::SplitPath(s, NULL, &evf, &evx, wxPATH_WIN);
			break;
		case 1:
			wxFileName::SplitPath(s, NULL, &evf, &evx, wxPATH_UNIX);
			break;
		case 2:
			wxFileName::SplitPath(s, NULL, &evf, &evx, wxPATH_MAC);
			break;
		default:
			wxFileName::SplitPath(s, NULL, &evf, &evx, wxPATH_WIN);
			break;
		}
		s.clear();
		s<<fn1.GetFullPath()<<"packages"<<evf<<"."<<evx;
		frame->GetPackages()->at(i).assign(s);
	}
	switch (id)
	{
	case 0://MSW
		wxFileName::SplitPath(frame->GetGlobalOptions()->GetEventFile(), NULL, &evf, &evx, wxPATH_WIN);
		break;
	case 1:
		wxFileName::SplitPath(frame->GetGlobalOptions()->GetEventFile(), NULL, &evf, &evx, wxPATH_UNIX);
		break;
	case 2:
		wxFileName::SplitPath(frame->GetGlobalOptions()->GetEventFile(), NULL, &evf, &evx, wxPATH_MAC);
		break;
	default:
		wxFileName::SplitPath(frame->GetGlobalOptions()->GetEventFile(), NULL, &evf, &evx, wxPATH_WIN);
	}
	
	wxFileName ev(fn1.GetFullPath()+"scripts"+evf+"."+evx);
	frame->GetGlobalOptions()->SetEventFile(ev.GetFullPath());
	/*
	
	wxString ev = m_eventfiel
	m_eventfile = m_scriptdir.GetFullPath();*/
	//m_eventfile.Append("events.lua");
	frame->SaveProfile(file);
	return 0;
}

int luafunc_waitfor(lua_State *L)
{
	
	MudMainFrame *frame = wxGetApp().GetFrame();
	
	const char* pattern = luaL_checkstring(L,1);
	int waittime = (int)luaL_optnumber(L, 2, -1);
	wxString action;
	
	action << frame->GetGlobalOptions()->GetCommand() << "resume (\"" << frame->GetLRefCount() << "\")";
	wxString label;
	
	label << "temp" << frame->GetLRefCount();
	
	Trigger t(pattern, action, label);
	t.SetShow(false);
	frame->GetTrigger()->push_back(t);
	frame->m_scriptwin->SetTriggers(*frame->GetTrigger());
	
	frame->GetLuaStates()->insert(make_pair(frame->GetLRefCount(), L));
	frame->SetLRefCount(frame->GetLRefCount()+1);
	if (waittime!=-1)
	{
		wxString s;
		s << "#resume(\"" << (frame->GetLRefCount()-1) << "\")";
		wxString t;
		t << "resume" << (frame->GetLRefCount()-1);
		amcTimer ti(t, s, "threads", (float)waittime, 1, false);
		ti.SetActive(true);
		frame->GetTimers()->push_back(ti);
		frame->GetTimers()->at(0).Run();
		frame->m_scriptwin->SetTimers(*frame->GetTimers());
	}
	
	return lua_yield(L,0);
}

int luafunc_wait(lua_State *L)
{
	MudMainFrame *frame = wxGetApp().GetFrame();
	
	float i = (float)luaL_checknumber(L,1);
	
	wxString s;
	s << "#resume(\"" << (frame->GetLRefCount()) << "\")";
	wxString t;
	t << "resume" << (frame->GetLRefCount());
	amcTimer ti(t, s, "threads", (float)i, 2, false);
	ti.SetActive(true);
	frame->GetTimers()->push_back(ti);
	frame->m_scriptwin->SetTimers(*frame->GetTimers());
	frame->GetLuaStates()->insert(make_pair(frame->GetLRefCount(), L));
	frame->SetLRefCount(frame->GetLRefCount()+1);
	int idx = frame->GetTimerIndexByLabel(t);
	frame->m_input->SetWaiting(true);
	if (idx!=-1)
		frame->GetTimers()->at(idx).Run();
	
	return lua_yield(L,0);
}

int luafunc_gag(lua_State *L)
{
	//int line = luaL_checkint(L,1);
	int line = (int)luaL_checknumber(L, 1);
	if (line>0)
		return 1;
	MudMainFrame *frame = wxGetApp().GetFrame();

	if (!frame->m_scriptwin->GetLines()->empty())
	{
		
		line_it lit = frame->m_scriptwin->GetLines()->end()-1;
		
		frame->m_scriptwin->GetLines()->erase(lit);
		if (frame->m_scriptwin->m_curline>=1)
		
			frame->m_scriptwin->m_curline--;
		else frame->m_scriptwin->m_curline=0;
		
		frame->m_scriptwin->Refresh();
		frame->m_scriptwin->Update();
	}
	return 0;
}


//Userdata
//! \brief open the wxamcl Lua library
/*!
	register the wxamcl lib in the lua namespace
	set wxamcl.mta metatable for wxAmcl actions
	override so we can do: wxamcl.echo
	\param lua_State *L: a valid lua_State
*/

int luaopen_amc(lua_State *L)
{
	
	return 0;
	
}

LUAMOD_API int luaopen2_amc(lua_State *L)
{
	
	
	luaL_newlib(L, amclib_f);
	lua_pushvalue(L, -1);
	lua_setglobal(L, "wxamcl");
	
	lua_getglobal(L, "wxamcl");
	luaL_newlib(L, amclib_mxp);
	lua_setfield(L, -2, "mxp");
	luaL_newlib(L, amclib_gmcp);
	lua_setfield(L, -2, "gmcp");
	luaL_newlib(L, amclib_draw);
	lua_setfield(L, -2, "draw");
	luaL_newlib(L, amclib_trigger);
	lua_setfield(L, -2, "action");

	luaL_newlib(L, amclib_vars);
	lua_setfield(L, -2, "var");
	luaL_newlib(L, amclib_gauge);
	lua_setfield(L, -2, "gauge");
	luaL_newlib(L, amclib_hk);
	lua_setfield(L, -2, "hk");
	luaL_newlib(L, amclib_alias);
	lua_setfield(L, -2, "alias");

	luaL_newlib(L, amclib_timers);
	lua_setfield(L, -2, "timer");
	luaL_newlib(L, amclib_list);
	lua_setfield(L, -2, "list");
	luaL_newlib(L, amclib_btn);
	lua_setfield(L, -2, "button");
	luaL_newlib(L, amclib_db);
	lua_setfield(L, -2, "db");
	
	luaL_newmetatable(L, "wxamcl.mta");//action type
	luaL_setfuncs(L, amclib_m, 0);
	lua_pop(L, 1);
	
	//lua_pushvalue(L, -1);
	//lua_setglobal(L, "wxamcl.mta");
	return 1;
}

//! wxamcl.action.new(name, table{pattern="pattern", action="action", group="group", on=true|false, priority=0-100, colmatch=-1|0-18})
/*!
	Creates a new action in lua, provide a unique label and a table with the values
	creates a user type action in lua and returns this userdatum
	userdatum = wxamcl.action.new("newaction", {pattern="A line", action="send to mud", group="default", on=true, prior=50, colmatch=-1})
	\param lua_State *L: a valid lua State
*/
int luafunc_newaction(lua_State*L)
{
tr_it it;
const char* l;
const char* c;
Trigger tr;
str_ac* t;
int index=1;
	
	class MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
		
	//called from amc.newaction
	if(lua_type(L, index) != LUA_TTABLE)
	{
		l = luaL_checkstring(L, index++);
		wxString f(l, co);
		for (it=frame->GetTrigger()->begin();it!=frame->GetTrigger()->end();it++)
		{
			if(f==*it)
			{
				frame->m_scriptwin->Msg(_("Error creating action. Action labels need to be unique!"));
				return 0;
			}
		}
		tr.SetLabel(f);
	}

	if (lua_type(L,index)==LUA_TTABLE)
	{
		//lua_getfield(L, -1, c);
		if (index==1)//called via amc.action.newaction = {}
		{
			l = luaL_checkstring(L, -2);
			tr.SetLabel(l);
			if (lua_type(L, -1)==LUA_TNIL)
			{
				int i = frame->GetTriggerIndexByLabel(l);
				if (i==-1)
				{
					lua_pushnil(L);
					return 1;
				}
				tr_it it = frame->GetTrigger()->begin()+i;
				frame->GetTrigger()->erase(it);
				stable_sort(frame->GetTrigger()->begin(), frame->GetTrigger()->end(), greater<class Trigger>());
				lua_pushinteger(L, frame->GetTrigger()->size());
				return 1;
			}
			lua_getfield(L, -1, "pattern");
			const char* cc = luaL_optstring(L, -1, "^*$");
			tr.SetPattern(wxString(cc,co));
			lua_getfield(L, -2, "action");
			cc = luaL_optstring(L, -1, "?wxamcl.echo('Action fired!')");
			tr.SetAction(wxString(cc,co));
			lua_getfield(L, -3, "group");
			cc = luaL_optstring(L, -1, "default");
			tr.SetClass(wxString(cc,co));
			lua_getfield(L, -4, "on");
			tr.SetActive(lua_toboolean(L,-1)!=0);
			lua_getfield(L, -5, "priority");
			tr.SetPriority((int)luaL_optnumber(L,-1,50));
			lua_getfield(L, -6, "colmatch");
			tr.SetColMatch((int)luaL_optnumber(L,-1,-1));
			lua_getfield(L, -7, "lines");
			tr.SetLines((int)luaL_optnumber(L,-1,1));
		}
		else
		{
			lua_getfield(L, index, "pattern");
			const char* cc = luaL_optstring(L, -1, "^*$");
			tr.SetPattern(cc);
			lua_getfield(L, index, "action");
			cc = luaL_optstring(L, -1, "?wxamcl.echo('Action fired!')");
			tr.SetAction(cc);
			lua_getfield(L, index, "group");
			cc = (char*)luaL_optstring(L, -1, "default");
			tr.SetClass(cc);
			lua_getfield(L, index, "on");
			tr.SetActive(lua_toboolean(L,-1)!=0);
			lua_getfield(L, index, "priority");
			tr.SetPriority((int)luaL_optnumber(L,-1,50));
			lua_getfield(L, index, "colmatch");
			tr.SetColMatch((int)luaL_optnumber(L,-1,-1));
			lua_getfield(L, index, "lines");
			tr.SetLines((int)luaL_optnumber(L,-1,1));
		}
	}
	else
	{
		c = luaL_optstring(L,index++, "^*$");
		tr.SetPattern(wxString(c,co));
		c = luaL_optstring(L,index++, "?wxamcl.echo('Action fired!')");
		tr.SetAction(wxString(c,co));
		tr.SetClass(wxString(luaL_optstring(L,index++, "default"), co));
		tr.SetActive(lua_toboolean(L,index++)!=0);
		tr.SetPriority((int)luaL_optnumber(L,index++,50));
		tr.SetColMatch((int)luaL_optnumber(L,index++,-1));
		tr.SetLines((int)luaL_optnumber(L, index++, 1));
	}
	frame->GetTrigger()->push_back(tr);
	frame->m_scriptwin->SetTriggers(*frame->GetTrigger());
	stable_sort(frame->GetTrigger()->begin(), frame->GetTrigger()->end(), greater<class Trigger>());
	t = (str_ac*)lua_newuserdata(L, sizeof(struct str_ac));
	wxStrcpy(t->label, l);
	wxStrcpy(t->pattern, tr.GetPattern().mb_str(co).data());// .c_str());
	wxStrcpy(t->action, tr.GetAction().mb_str(co).data());// .c_str());
	wxStrcpy(t->cla, tr.GetClass().mb_str(co).data());// .c_str());
	t->on = tr.IsActive();
	t->prior = tr.GetPriority();
	t->colmatch = tr.GetColMatch();
	t->count = tr.GetMatchCount();
	t->lines = tr.GetLines();
	t->send = tr.GetSendScript();
	luaL_getmetatable(L, "wxamcl.mta");
	lua_setmetatable(L, -2);
	//frame->luaBuildtrigger();
	return 1;
}

int findtrigger(lua_State *L, const char* tr)
{
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	wxString f(tr, co);
	return frame->GetTriggerIndexByLabel(f);
}

int luafunc_gettruserdata(lua_State *L)
{
str_ac* t;
const char* c;
int i;


	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	/*wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	c = luaL_checkstring(L,1);
	wxString f(c, co);
	i = frame->GetTriggerIndexByLabel(f);*/
	i = findtrigger(L, c=luaL_checkstring(L, 1));
	if (i==-1)
	{
		frame->m_scriptwin->Msg(_("Action not found!"));
		lua_pushnil(L);
		return 1;
	}
	t = (str_ac*)lua_newuserdata(L, sizeof(struct str_ac));
	wxStrcpy(t->label, c);
	wxStrcpy(t->pattern, frame->GetTrigger()->at(i).GetPattern().mb_str(co).data());// .c_str());
	wxStrcpy(t->action, frame->GetTrigger()->at(i).GetAction().mb_str(co).data());// .c_str());
	wxStrcpy(t->cla, frame->GetTrigger()->at(i).GetClass().mb_str(co).data());// .c_str());
	t->on = frame->GetTrigger()->at(i).IsActive();
	t->prior = frame->GetTrigger()->at(i).GetPriority();
	t->colmatch = frame->GetTrigger()->at(i).GetColMatch();
	t->count = frame->GetTrigger()->at(i).GetMatchCount();
	t->lines = frame->GetTrigger()->at(i).GetLines();
	t->send = frame->GetTrigger()->at(i).GetSendScript();
	luaL_getmetatable(L, "wxamcl.mta");
	lua_setmetatable(L, -2);
	//frame->luaBuildtrigger();
	return 1;
}
//! table = wxacml.action.get(action|userdatum)
/*!
	returns a table representing an wxAMC action in Lua
	t = wxamcl.getaction("Map1")
	t = wxamcl.getaction(x) provide a userdatum returned from newaction or getuserdata
	table has fields: label, pattern, action, class, on, priority, colmatch, matchcount, lines, script
	\param lua_State *L: a valid lua_State
*/
int luafunc_getaction(lua_State*L)
{
str_ac* t;
const char* c;
int i, index=1;

	//MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	class MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		i = frame->GetTriggerIndexByLabel(wxString(t->label,co));
	}
	else if (lua_type(L, index) == LUA_TTABLE)
	{
		wxString s(luaL_checkstring(L, index + 1), co);
				
		i = frame->GetTriggerIndexByLabel(s);
		if (i == -1)
		{
			frame->m_scriptwin->Msg(_("Action not found!"));
			lua_pushnil(L);
			return 1;
		}
		wxString ss = frame->GetTrigger()->at(i).GetAction();
		lua_settop(L, 0);
		lua_newtable(L);

		for (i = 0; i<frame->GetTrigger()->size(); i++)
		{
			lua_pushstring(L, frame->GetTrigger()->at(i).GetLabel().mb_str(co).data());// .mb_str());
																				//lua_setfield(L, -1, GetTrigger()->at(i).GetLabel());
			lua_setfield(L, -2, "label");
			lua_pushstring(L, frame->GetTrigger()->at(i).GetPattern().mb_str(co).data());
			lua_setfield(L, -2, "pattern");
			lua_pushstring(L, frame->GetTrigger()->at(i).GetAction().mb_str(co).data());// .mb_str());
			lua_setfield(L, -2, "action");
			lua_pushstring(L, frame->GetTrigger()->at(i).GetClass().mb_str(co).data());// .mb_str());
			lua_setfield(L, -2, "group");
			lua_pushboolean(L, frame->GetTrigger()->at(i).IsActive());
			lua_setfield(L, -2, "on");
			lua_pushinteger(L, frame->GetTrigger()->at(i).GetPriority());
			lua_setfield(L, -2, "priority");
			lua_pushinteger(L, frame->GetTrigger()->at(i).GetColMatch());
			lua_setfield(L, -2, "colmatch");
			lua_pushinteger(L, frame->GetTrigger()->at(i).GetLines());
			lua_setfield(L, -2, "lines");
			lua_pushinteger(L, frame->GetTrigger()->at(i).GetMatchCount());
			lua_setfield(L, -2, "matchcount");
			lua_pushboolean(L, frame->GetTrigger()->at(i).GetSendScript());
			lua_setfield(L, -2, "script");
			

		}
		//lua_pushstring(L, ss.mb_str(co).data());// .mb_str());
		return 1;
	}
	else
	{
		c = luaL_checkstring(L,index);
		i = findtrigger(L, c);
	}
	if (i==-1)
	{
		frame->m_scriptwin->Msg(_("Action not found!"));
		lua_pushnil(L);
		return 1;
	}
	lua_settop(L,0);
	lua_newtable(L);
	wxString l = frame->GetTrigger()->at(i).GetLabel();
	
	lua_pushstring(L, l.mb_str(co).data());// frame->GetTrigger()->at(i).GetLabel());// .char_str());
	lua_setfield(L, -2, "label");
	lua_pushstring(L, frame->GetTrigger()->at(i).GetPattern().mb_str(co).data());// .char_str());
	lua_setfield(L, -2, "pattern");
	lua_pushstring(L, frame->GetTrigger()->at(i).GetAction().mb_str(co).data());// .char_str());
	lua_setfield(L, -2, "action");
	lua_pushstring(L, frame->GetTrigger()->at(i).GetClass().mb_str(co).data());// .char_str());
	lua_setfield(L, -2, "group");
	lua_pushinteger(L, frame->GetTrigger()->at(i).GetPriority());
	lua_setfield(L, -2, "priority");
	lua_pushinteger(L, frame->GetTrigger()->at(i).GetColMatch());
	lua_setfield(L, -2, "colmatch");
	lua_pushinteger(L, frame->GetTrigger()->at(i).GetMatchCount());
	lua_setfield(L, -2, "matchcount");
	lua_pushboolean(L, frame->GetTrigger()->at(i).IsActive());
	lua_setfield(L, -2, "on");
	lua_pushinteger(L, frame->GetTrigger()->at(i).GetLines());
	lua_setfield(L, -2, "lines");
	lua_pushboolean(L, frame->GetTrigger()->at(i).GetSendScript());
	lua_setfield(L, -2, "script");
	return 1;
}

//! x = wxamcl.action.delete(action|userdatum)
/*!
	deletes an wxAMC action in Lua
	x=wxamcl.action.delete("Map1")
	x=wxamcl.action.delete(x) provide a userdatum returned from newaction
	returns the number of actions or nil in case of error
	\param lua_State *L: a valid lua_State
*/
int luafunc_deleteaction(lua_State *L)
{
tr_it it;
char* c;
int index=1, i;
str_ac *t;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		//t = (str_ac*)lua_touserdata(L, index);
		t = checkaction(L);
		i = frame->GetTriggerIndexByLabel(wxString(t->label,co));
	}
	else
	{
		c = (char*)luaL_checkstring(L,index);
		i = findtrigger(L, c);
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	it = frame->GetTrigger()->begin()+i;
	frame->GetTrigger()->erase(it);
	frame->m_scriptwin->SetTriggers(*frame->GetTrigger());
	t = NULL;
	stable_sort(frame->GetTrigger()->begin(), frame->GetTrigger()->end(), greater<class Trigger>());
	lua_pushinteger(L, frame->GetTrigger()->size());
	return 1;
}

//! x = wxamcl.action.enable(action|userdatum)
/*!
enables or disables an wxAMCL action in Lua
x=wxamcl.action.enable("Map1", true|false)
x=wxamcl.action.enable(x, true|false) provide a userdatum returned from newaction or getuserdata
returns the label of the action or nil in case of error
\param lua_State *L: a valid lua_State
*/
int luafunc_enableaction(lua_State *L)
{
const char* c;
int i, index=1;
str_ac *t=NULL;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		t = (str_ac*)lua_touserdata(L, index++);
		i = frame->GetTriggerIndexByLabel(wxString(t->label,co));
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = findtrigger(L, c);
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetTrigger()->at(i).SetActive(lua_toboolean(L,index)!=0);
	if (!t)
	{
		lua_pushstring(L,c);
	}
	else
	{
		t->on = frame->GetTrigger()->at(i).IsActive();
		frame->m_scriptwin->SetTriggers(*frame->GetTrigger());
		lua_pushstring(L, t->label);
	}
	return 1;
}

int luafunc_getpattern(lua_State*L)
{
char* l;
str_ac* t;
int index=1;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		lua_pushstring(L, t->pattern);
		return 1;
	}

	else
	{
		l = (char*)luaL_checkstring(L,index);
		int i = findtrigger(L, l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		else
			lua_pushstring(L, frame->GetTrigger()->at(i).GetPattern().mb_str(co).data());// char_str());
			return 1;
	}
	return 1;
}
//! wxamcl.action.setpattern(action|userdatum)
/*!
	sets the pattern of an wxAMC action in Lua
	wxamcl.action.setpattern("Map1", "this is the pattern")
	wxamcl.action.setpattern(x) provide a userdatum returned from newaction
	returns nil on error
	\param lua_State *L: a valid lua_State
*/
int luafunc_setpattern(lua_State*L)
{
const char* l;
const char* c;
Trigger tr;
str_ac* t;
int i, index=1;
	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		c = luaL_checkstring(L, ++index);
		wxString f(t->label, co);
		i = frame->GetTriggerIndexByLabel(f);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		wxString ff(c, co);
		frame->GetTrigger()->at(i).SetPattern(ff);
		wxStrcpy(t->pattern, ff.mb_str(co).data());
		//t->pattern = c;
		return 0;
	}
	else
	{
		l = luaL_checkstring(L,index++);
		wxString ff(l, co);
		c = luaL_checkstring(L, index);
		i = frame->GetTriggerIndexByLabel(ff);
		wxString fff(c, co);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetTrigger()->at(i).SetPattern(fff);
		frame->m_scriptwin->SetTriggers(*frame->GetTrigger());
	}
	return 0;
}

int luafunc_getac(lua_State*L)
{
tr_it it;
const char* l;
str_ac* t;
int index=1;
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		lua_pushstring(L, t->action);
		return 1;
	}

	else
	{
		l = luaL_checkstring(L,index);
		int i = findtrigger(L, l);
		if (i == -1)
		{
			lua_pushnil(L);
			return 1;
		}
		else
			lua_pushstring(L, frame->GetTrigger()->at(i).GetAction().mb_str(co).data());//.char_str());
			return 1;
	}
	return 1;
}

int luafunc_setac(lua_State*L)
{
char* l;
char* c;
str_ac* t;
int i, index=1;

MudMainFrame *frame = wxGetApp().GetFrame();// (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		c = (char*)luaL_checkstring(L, ++index);
		i = frame->GetTriggerIndexByLabel(wxString(t->label,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		wxString f = wxString(c, co);
		frame->GetTrigger()->at(i).SetAction(f);
		wxStrcpy(t->action, f.mb_str(co).data());
		return 0;
	}
	else
	{
		l = (char*)luaL_checkstring(L,index++);
		c = (char*)luaL_checkstring(L, index);
		i = findtrigger(L, l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetTrigger()->at(i).SetAction(wxString(c,co));
		frame->m_scriptwin->SetTriggers(*frame->GetTrigger());
	}
	return 0;
}

//! num = wxamcl.getpriority(name|userdatum)
/*!
	returns the priority of an wxAmc action in Lua or nil
	\param lua_State *L: a valid lua_State
*/
int luafunc_getpriority(lua_State*L)
{
tr_it it;
char* l;
str_ac* t;
int index=1;
MudMainFrame *frame = wxGetApp().GetFrame();

	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		lua_pushinteger(L, t->prior);
		return 1;
	}

	else
	{
		l = (char*)luaL_checkstring(L,index);
		int i = findtrigger(L, l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		else
			lua_pushinteger(L, frame->GetTrigger()->at(i).GetPriority());
			return 1;
	}
	return 1;
}

//! wxamcl.setpriority(name|userdatum, priority)
/*!
	sets the priority of an action, default = 50
	\param lua_State *L: a valid lua_State
*/
int luafunc_setpriority(lua_State *L)
{
str_ac *t;
int n, i, index=1;
const char *l;

MudMainFrame *frame = wxGetApp().GetFrame();
wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		n = (int)luaL_optnumber(L, ++index, 50);
		i = frame->GetTriggerIndexByLabel(wxString(t->label,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetTrigger()->at(i).SetPriority(n);
		t->prior = n;
		stable_sort(frame->GetTrigger()->begin(), frame->GetTrigger()->end(), greater<class Trigger>());
		return 0;
	}
	else
	{
		l = luaL_checkstring(L,index++);
		n = (int)luaL_optnumber(L, index, 50);
		i = findtrigger(L, l);
		
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetTrigger()->at(i).SetPriority(n);
		stable_sort(frame->GetTrigger()->begin(), frame->GetTrigger()->end(), greater<class Trigger>());
		frame->m_scriptwin->SetTriggers(*frame->GetTrigger());
	}
	return 0;
}

//! num = wxamcl.getcolmatch(name|userdatum)
/*!
	returns the forgeground color to match of an wxAmc action in Lua or nil
	\param lua_State *L: a valid lua_State
*/
int luafunc_getcolmatch(lua_State*L)
{
tr_it it;
char* l;
str_ac* t;
int index=1;
MudMainFrame *frame = wxGetApp().GetFrame();

	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		lua_pushinteger(L, t->colmatch);
		return 1;
	}

	else
	{
		l = (char*)luaL_checkstring(L,index);
		int i = findtrigger(L, l);
		
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		else
			lua_pushinteger(L, frame->GetTrigger()->at(i).GetColMatch());
			return 1;
	}
	return 1;
}

//! wxamcl.setcolmatch(name|userdatum, colmatch)
/*!
	sets the foreground color to match of an action, default = -1 = none
	\param lua_State *L: a valid lua_State
*/
int luafunc_setcolmatch(lua_State *L)
{
str_ac *t;
int n, i, index=1;
const char* l;

MudMainFrame *frame = wxGetApp().GetFrame();
wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		n = (int)luaL_optnumber(L, ++index, -1);
		
		i = frame->GetTriggerIndexByLabel(wxString(t->label,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetTrigger()->at(i).SetColMatch(n);
		t->colmatch = n;
		return 0;
	}
	else
	{
		l = luaL_checkstring(L,index++);
		n = (int)luaL_optnumber(L, index, -1);
		i = findtrigger(L, l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetTrigger()->at(i).SetColMatch(n);
		frame->m_scriptwin->SetTriggers(*frame->GetTrigger());
	}
	return 0;
}

int luafunc_getallactions(lua_State*L)
{
size_t i;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	lua_settop(L,0);
	lua_newtable(L);
	for (i=0;i<frame->GetTrigger()->size();i++)
	{
		lua_pushstring(L, frame->GetTrigger()->at(i).GetLabel().mb_str(co).data());// char_str());
		lua_rawseti(L, -2, i+1);
	}
	lua_pushinteger(L, i);
	return 2;
}

int luafunc_enabletriggers(lua_State *L)
{
	MudMainFrame *frame = wxGetApp().GetFrame();
	frame->SetTriggersOn(true);
	lua_pushinteger(L, frame->GetTrigger()->size());
	return 1;
}

int luafunc_disabletriggers(lua_State *L)
{
	MudMainFrame *frame = wxGetApp().GetFrame();
	frame->SetTriggersOn(false);
	lua_pushinteger(L, frame->GetTrigger()->size());
	return 1;
}


int luafunc_enabletrgroup(lua_State *L)
{
tr_it iter;
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	const char* trgroup;
	trgroup = luaL_checkstring(L, 1);
	wxString trg(trgroup, co);
	bool active = lua_toboolean(L,2) != 0;
	for (iter = frame->GetTrigger()->begin(); iter!= frame->GetTrigger()->end(); iter++)
		{
			if (trg == iter->GetClass())
			{
				iter->SetActive(active);
			}
		}
	return 0;
}

int luafunc_deltrgroup(lua_State *L)
{
s_it it;
const char* trgroup;
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	trgroup = luaL_checkstring(L, 1);
	wxString trg(trgroup, co);
	for (size_t i=0;i<frame->GetTrigger()->size(); i++)
	{
		if(frame->GetTrigger()->at(i).GetClass()==trg)
		{
			frame->GetTrigger()->erase(frame->GetTrigger()->begin()+i--);
		}
	}
	for (it = Trigger::GetTriggerClasses()->begin(); it!=Trigger::GetTriggerClasses()->end(); it++)
	{
		if (*it == trg)
		{
			Trigger::GetTriggerClasses()->erase(it);
			break;
		}
	}
	if (frame->IsVerbose())
	{
		wxString s;
		s<<_("Deleted action group ")<<trgroup<<".";
		frame->m_scriptwin->Msg(s, 3);
	}
	return 0;
}

int luafunc_gettrgroup(lua_State *L)
{
const char* trgroup;
size_t i;
int x=0;
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	trgroup = luaL_checkstring(L, 1);
	wxString trg(trgroup, co);
	lua_settop(L,0);
	lua_newtable(L);
	for (i=0;i<frame->GetTrigger()->size();i++)
	{
		if (frame->GetTrigger()->at(i).GetClass()==trg)
		{
			lua_pushstring(L, frame->GetTrigger()->at(i).GetLabel().mb_str(co).data());// .char_str());
			lua_rawseti(L, -2, x+1);
			x++;
		}
	}
	lua_pushinteger(L, x);
	return 2;
}

int luafunc_exectr(lua_State *L)
{
tr_it it;
const char* l;
str_ac* t;
int index=1;
int i;
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		lua_pushstring(L, t->action);
		i = frame->GetTriggerIndexByLabel(wxString(t->label,co));
	}
	else
	{
		l = luaL_checkstring(L,index);
		i = findtrigger(L, l);
		lua_pushstring(L, frame->GetTrigger()->at(i).GetAction().mb_str(co).data());// .char_str());
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	
	int state = frame->m_scriptwin->GetParseState();
	frame->m_scriptwin->SetParseState(0);//HAVE_TEXT
	wxString command = frame->GetTrigger()->at(i).GetAction();
	frame->m_input->Parse(command, true);
	frame->m_scriptwin->SetParseState(state);
	return 1;
	
}

int luafunc_actiontostring(lua_State *L)
{
str_ac* t;

//	MudMainFrame *frame = wxGetApp().GetFrame();
	t = (str_ac*)checkaction(L);
	lua_pushfstring(L, "type: wxamcl.action, label: \"%s\", pattern: \"%s\", action: \"%s\", group: \"%s\"", (const char*)t->label, (const char*)t->pattern, t->action, (const char*)t->cla);
	return 1;
}

//! wxamcl.alias.new(table{alias="alias", action="action", group="group", on=true|false})
/*!
	Creates a new alias in lua, provide a table with the values
	creates a user type action in lua and returns this userdatum
	userdatum = amc.alias.new({alias="ef", action="eat food", class="default", on=true})
	\param lua_State *L: a valid lua State
*/
int luafunc_newalias(lua_State*L)
{
al_it it;
const char* c;
amcAlias al;
str_al* a;
int index=1;

	MudMainFrame *frame = wxGetApp().GetFrame(); 
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	
	if (lua_type(L,index)==LUA_TTABLE)
	{
		//lua_getfield(L, -1, c);
		lua_getfield(L, index, "alias");
		const char* cc = luaL_checkstring(L, -1);
		wxString s(cc, co);
		if (s.at(0)!='^')
			s = '^' + s;
		if (!s.EndsWith("$"))
			s.append('$');
		for (it=frame->GetAlias()->begin();it!=frame->GetAlias()->end();it++)
		{
			if(s==*it)
			{
				frame->m_scriptwin->Msg(_("Alias already exists!"));
				return 0;
			}
		}
		al.SetAlias(s);
		lua_getfield(L, index, "action");
		cc = luaL_checkstring(L, -1);
		al.SetAction(wxString(cc,co));
		lua_getfield(L, index, "group");
		cc = luaL_optstring(L, -1, "default");
		al.SetGroup(wxString(cc,co));
		lua_getfield(L, index, "on");
		al.SetActive(lua_toboolean(L,-1)!=0);
	}
	else
	{
		c = luaL_checkstring(L,index++);
		wxString s(c,co);
		if (s.at(0)!='^')
			s = '^' + s;
		if (!s.EndsWith("$"))
			s.append('$');
		for (it=frame->GetAlias()->begin();it!=frame->GetAlias()->end();it++)
		{
			if(s==*it)
			{
				frame->m_scriptwin->Msg(_("Alias already exists!"));
				return 0;
			}
		}
		al.SetAlias(s);
		c = luaL_checkstring(L,index++);
		al.SetAction(wxString(c,co));
		al.SetGroup(wxString(luaL_optstring(L,index++, "default"),co));
		al.SetActive(lua_toboolean(L,index++)!=0);
		
	}
	frame->GetAlias()->push_back(al);
	stable_sort(frame->GetAlias()->begin(), frame->GetAlias()->end(), less<class amcAlias>());
	frame->m_scriptwin->SetAlias(*frame->GetAlias());
	a = (str_al*)lua_newuserdata(L, sizeof(struct str_al));
	wxStrcpy(a->alias, al.GetAlias().mb_str(co).data());// .c_str());
	wxStrcpy(a->action, al.GetAction().mb_str(co).data());// .c_str());
	wxStrcpy(a->cla, al.GetGroup().mb_str(co).data());// .c_str());
	a->on = al.IsActive();
	luaL_getmetatable(L, "wxamcl.mtal");
	lua_setmetatable(L, -2);
	return 1;
}

int luafunc_newalias1(lua_State*L)
{
al_it it;
const char* cc;
amcAlias al;
str_al* a;
int index=1;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TTABLE)
	{
		
		cc = luaL_checkstring(L, -2);
		wxString f(cc, co);
		if (lua_type(L, -1)==LUA_TNIL)
		{
			int i = frame->GetAliasIndexByLabel(f);
			if (i==-1)
			{
				lua_pushnil(L);
				return 1;
			}
			al_it it = frame->GetAlias()->begin()+i;
			frame->GetAlias()->erase(it);
			stable_sort(frame->GetAlias()->begin(), frame->GetAlias()->end(), greater<class amcAlias>());
			frame->m_scriptwin->SetAlias(*frame->GetAlias());
			lua_pushinteger(L, frame->GetAlias()->size());
			return 1;
		}
				
		wxString s(cc,co);
		if (s.at(0)!='^')
			s = '^' + s;
		if (!s.EndsWith("$"))
			s.append('$');
		for (it=frame->GetAlias()->begin();it!=frame->GetAlias()->end();it++)
		{
			if(s==*it)
			{
				frame->m_scriptwin->Msg(_("Alias already exists!"));
				return 0;
			}
		}
		al.SetAlias(s);
		lua_getfield(L, -1, "action");
		cc = luaL_checkstring(L, -1);
		al.SetAction(wxString(cc,co));
		lua_getfield(L, -2, "group");
		cc = luaL_optstring(L, -1, "default");
		al.SetGroup(wxString(cc,co));
		lua_getfield(L, -3, "on");
		al.SetActive(lua_toboolean(L,-1)!=0);
	}
	
	frame->GetAlias()->push_back(al);
	stable_sort(frame->GetAlias()->begin(), frame->GetAlias()->end(), less<class amcAlias>());
	frame->m_scriptwin->SetAlias(*frame->GetAlias());
	a = (str_al*)lua_newuserdata(L, sizeof(struct str_al));
	wxStrcpy(a->alias, al.GetAlias().mb_str(co).data());// .c_str());
	wxStrcpy(a->action, al.GetAction().mb_str(co).data());// .c_str());
	wxStrcpy(a->cla, al.GetGroup().mb_str(co).data());// .c_str());
	a->on = al.IsActive();
	luaL_getmetatable(L, "wxamcl.mtal");
	lua_setmetatable(L, -2);
	return 1;
}

/** a = wxamcl.alias.get(name)
 * \brief get an amcAlias as lua table
 * \param L
 * \return table containing the alias
 */
int luafunc_getalias(lua_State* L)
{
str_al* t;
const char* c;
int i, index=1;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		t = checkalias(L);
		wxString s(t->alias, co);
		if (s.at(0)!='^')
			s = '^' + s;
		if (!s.EndsWith("$"))
			s.append('$');
		i = frame->GetAliasIndexByLabel(s);
	}
	else if (lua_type(L,index)==LUA_TTABLE)
	{
		wxString s(luaL_checkstring(L, index+1), co);
		if (s.at(0)!='^')
			s = '^' + s;
		if (!s.EndsWith("$"))
			s.append('$');
		int idx = frame->GetAliasIndexByLabel(s);
		if (idx==-1)
			return 0;
		wxString ss = frame->GetAlias()->at(idx).GetAction();
		lua_pushstring(L, ss.mb_str(co).data());// .mb_str());
		return 1;
	}
	else
	{
		c = luaL_checkstring(L,index);
		wxString s(c, co);
		if (s.at(0)!='^')
			s = '^' + s;
		if (!s.EndsWith("$"))
			s.append('$');
		i = frame->GetAliasIndexByLabel(s);
	}
	if (i==-1)
	{
		frame->m_scriptwin->Msg(_("Alias not found!"));
		lua_pushnil(L);
		return 1;
	}
	lua_settop(L,0);
	lua_newtable(L);
	lua_pushstring(L, frame->GetAlias()->at(i).GetAlias().mb_str(co).data());// .char_str());
	lua_setfield(L, -2, "alias");
	lua_pushstring(L, frame->GetAlias()->at(i).GetAction().mb_str(co).data());// .mb_str());
	lua_setfield(L, -2, "action");
	lua_pushstring(L, frame->GetAlias()->at(i).GetGroup().mb_str(co).data());// .mb_str());
	lua_setfield(L, -2, "group");
	lua_pushboolean(L, frame->GetAlias()->at(i).IsActive());
	lua_setfield(L, -2, "on");
	return 1;	
}

/** a,x = wxamcl.alias.getall()
 * \brief get all amcAlias as lua table
 * \param L
 * \return table containing the alias, number of alias in table
 */
int luafunc_getallalias(lua_State*L)
{
size_t i;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	lua_settop(L,0);
	lua_newtable(L);
	for (i=0;i<frame->GetAlias()->size();i++)
	{
		lua_pushstring(L, frame->GetAlias()->at(i).GetAlias().mb_str(co).data());// .mb_str());
		lua_rawseti(L, -2, i+1);
	}
	lua_pushinteger(L, i);
	return 2;
}

//! x = wxamcl.alias.delete(alias|userdatum)
/*!
	deletes an wxAMC alias in Lua */
/*!	x=wxamcl.alias.delete("food1") */
/*!	x=wxamcl.alias.delete(x) provide a userdatum returned from newalias */
/*	returns the number of aliases or nil in case of error
	\param lua_State *L: a valid lua_State
*/
int luafunc_deletealias(lua_State *L)
{
al_it it;
char* c;
int index=1, i;
str_al *a;

	MudMainFrame *frame = wxGetApp().GetFrame(); 
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		a = (str_al*)lua_touserdata(L, index);
		i = frame->GetAliasIndexByLabel(wxString(a->alias,co));
	}
	else
	{
		c = (char*)luaL_checkstring(L,index);
		i = frame->GetAliasIndexByLabel(wxString(c,co));
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	it = frame->GetAlias()->begin()+i;
	frame->GetAlias()->erase(it);
	a = NULL;
	stable_sort(frame->GetAlias()->begin(), frame->GetAlias()->end(), less<class amcAlias>());
	frame->m_scriptwin->SetAlias(*frame->GetAlias());
	lua_pushinteger(L, frame->GetAlias()->size());
	return 1;
}

//! x = wxamcl.alias.enable(name, true|false)
/*!
	enable or disable alias via Lua
*/
int luafunc_enablealias(lua_State *L)
{
const char* c;
int i, index=1;
str_al *t=NULL;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		t = (str_al*)lua_touserdata(L, index++);
		i = frame->GetAliasIndexByLabel(wxString(t->alias,co));
	}
	else
	{
		c = (char*)luaL_checkstring(L,index++);
		i = frame->GetAliasIndexByLabel(wxString(c,co));
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetAlias()->at(i).SetActive(lua_toboolean(L,index)!=0);
	frame->m_scriptwin->SetAlias(*frame->GetAlias());
	if (!t)
	{
		wxString f(c, co);
		lua_pushstring(L, f.mb_str(co).data());
	}
	else
	{
		t->on = frame->GetAlias()->at(i).IsActive();
		lua_pushstring(L, t->alias);
	}
	return 1;
}

int luafunc_getalaction(lua_State *L)
{
const char* l;
str_al* t;
int index=1;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkalias(L);
		//lua_pushstring(L, wxString(t->action,co));
		wxString im = wxString(t->action, co);
		lua_pushstring(L, im.mb_str(co).data());
		return 1;
	}

	else
	{
		l = luaL_checkstring(L,index);
		int i = frame->GetAliasIndexByLabel(wxString(l,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		else
			lua_pushstring(L, frame->GetAlias()->at(i).GetAction().mb_str(co).data());// .mb_str());
			return 1;
	}
	return 1;
}

int luafunc_setalaction(lua_State *L)
{
char* l;
char* c;
amcAlias al;
str_al* t;
int i, index=1;
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkalias(L);
		c = (char*)luaL_checkstring(L, ++index);
		i = frame->GetAliasIndexByLabel(wxString(t->alias,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		wxString f(c, co);
		frame->GetAlias()->at(i).SetAction(f);
		frame->m_scriptwin->SetAlias(*frame->GetAlias());
		wxStrcpy(t->action, f.mb_str(co).data());
		return 0;
	}
	else
	{
		l = (char*)luaL_checkstring(L,index++);
		c = (char*)luaL_checkstring(L, index);
		i = frame->GetAliasIndexByLabel(wxString(l,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetAlias()->at(i).SetAction(wxString(c,co));
		frame->m_scriptwin->SetAlias(*frame->GetAlias());
	}
	return 0;
}

int luafunc_deletegroup(lua_State *L)
{
char* c;
s_it it;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	c = (char*)luaL_checkstring(L,1);
	wxString f(c, co);
	bool del = lua_toboolean(L,2)!=0;
	if (del)
	{
		for (size_t i=0;i<frame->GetAlias()->size(); i++)
		{
			if(frame->GetAlias()->at(i).GetGroup()==f)
			{
				frame->GetAlias()->erase(frame->GetAlias()->begin()+i--);
			}
		}
	}
	else
	{
		for (size_t i=0;i<frame->GetAlias()->size(); i++)
		{
			if(frame->GetAlias()->at(i).GetGroup()==f)
			{
				frame->GetAlias()->at(i).SetGroup("default");
			}
		}
	}
	frame->m_scriptwin->SetAlias(*frame->GetAlias());
	for (it = amcAlias::GetAliasGroups()->begin(); it!=amcAlias::GetAliasGroups()->end(); it++)
	{
		if (*it == f)
		{
			amcAlias::GetAliasGroups()->erase(it);
			break;
		}
	}
	return 0;
}

int luafunc_enablegroup(lua_State *L)
{
char* c;
s_it it;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	c = (char*)luaL_checkstring(L,1);
	wxString f(c, co);
	bool active = lua_toboolean(L,2)!=0;
	if (active)
	{
		for (size_t i=0;i<frame->GetAlias()->size(); i++)
		{
			if(frame->GetAlias()->at(i).GetGroup()==f)
			{
				frame->GetAlias()->at(i).SetActive(true);
			}
		}
	}
	else
	{
		for (size_t i=0;i<frame->GetAlias()->size(); i++)
		{
			if(frame->GetAlias()->at(i).GetGroup()==f)
			{
				frame->GetAlias()->at(i).SetActive(false);
			}
		}
	}
	return 0;
}

int luafunc_aliastostring(lua_State *L)
{
str_al* t;


	t = (str_al*)checkalias(L);
	lua_pushfstring(L, "type: amc.alias, alias: \"%s\", action: \"%s\"", t->alias, t->action);
	return 1;
}
//timer
int luafunc_newtimer(lua_State *L)
{
t_it it;
int index=1;
struct str_timer* strt;
const char *cc;
amcTimer timer;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
//	int x = sizeof(struct str_timer);
	if (lua_type(L,index)==LUA_TTABLE)
	{
		//lua_getfield(L, -1, c);
		lua_getfield(L, index, "name");
		cc = luaL_checkstring(L, -1);
		wxString s(cc, co);
		for (it=frame->GetTimers()->begin();it!=frame->GetTimers()->end();it++)
		{
			if(s==*it)
			{
				frame->m_scriptwin->Msg(_("Timer already exists!"));
				return 0;
			}
		}
		timer.SetName(s);
		lua_getfield(L, index, "action");
		cc = luaL_checkstring(L, -1);
		timer.SetAction(wxString(cc,co));
		lua_getfield(L, index, "group");
		cc = luaL_optstring(L, -1, "default");
		timer.SetGroup(wxString(cc,co));
		lua_getfield(L, index, "on");
		timer.SetActive(lua_toboolean(L,-1)!=0);
		lua_getfield(L, index, "intervall");
		float intv = (float)luaL_checknumber(L,-1);
		timer.SetInterval(intv);
		//hk.SetHotkey(luaL_checklong(L, -1));
		lua_getfield(L, index, "rep");
		int i = (int)(int)luaL_optnumber(L,-1,-1);
		timer.SetRepeat(i);
		timer.SetCurrepeat(i);
	}
	else
	{
		cc = luaL_checkstring(L,index++);
		wxString s(cc, co);
		for (it=frame->GetTimers()->begin();it!=frame->GetTimers()->end();it++)
		{
			if(s==*it)
			{
				frame->m_scriptwin->Msg(_("Timer already exists!"));
				return 0;
			}
		}
		timer.SetName(s);
		cc = luaL_checkstring(L,index++);
		timer.SetAction(wxString(cc,co));
		timer.SetGroup(wxString(luaL_optstring(L,index++, "default"),co));
		timer.SetInterval(luaL_checknumber(L,index++));
		timer.SetRepeat((int)luaL_optnumber(L,index,-1));
		timer.SetCurrepeat((int)luaL_optnumber(L,index++,-1));
		timer.SetActive(lua_toboolean(L,index++)!=0);
	}
	frame->GetTimers()->push_back(timer);
	stable_sort(frame->GetTimers()->begin(), frame->GetTimers()->end(), less<class amcTimer>());
	frame->m_scriptwin->SetTimers(*frame->GetTimers());
	//stable_sort(frame->GetHotkeys()->begin(), frame->GetHotkeys()->end(), less<class amcHotkey>());
	strt = (str_timer*)lua_newuserdata(L, sizeof(struct str_timer));
	wxStrcpy(strt->name, timer.GetName().mb_str(co).data());
	wxStrcpy(strt->action, timer.GetAction().mb_str(co).data());
	wxStrcpy(strt->group, timer.GetGroup().mb_str(co).data());
	strt->on = timer.IsActive();
	strt->intervall = timer.GetInterval();
	strt->repeat = timer.GetRepeat();
	luaL_getmetatable(L, "wxamcl.mtt");
	lua_setmetatable(L, -2);
	return 1;
}

int luafunc_deltimer(lua_State *L)
{
t_it it;
const char* c;
int index=1, i;
str_timer* t;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		t = (str_timer*)lua_touserdata(L, index);
		i = frame->GetTimerIndexByLabel(wxString(t->name,co));
	}
	else
	{
		c = luaL_checkstring(L,index);
		i = frame->GetTimerIndexByLabel(wxString(c,co));
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	it = frame->GetTimers()->begin()+i;
	frame->GetTimers()->erase(it);
	//stable_sort(frame->GetVars()->begin(), frame->GetVars()->end(), less<class amcVar>());
	frame->m_scriptwin->SetTimers(*frame->GetTimers());
	lua_pushinteger(L, frame->GetTimers()->size());
	return 1;
}

int luafunc_starttimer(lua_State *L)
{
t_it it;
const char* c;
int index=1, i;
str_timer* t;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		t = (str_timer*)lua_touserdata(L, index);
		i = frame->GetTimerIndexByLabel(wxString(t->name,co));
	}
	else
	{
		c = luaL_checkstring(L,index);
		i = frame->GetTimerIndexByLabel(wxString(c,co));
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	
	frame->GetTimers()->at(i).SetActive(true);
	frame->GetTimers()->at(i).Run();
	return 0;
}

int luafunc_stoptimer(lua_State *L)
{
t_it it;
const char* c;
int index=1, i;
str_timer* t;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		t = (str_timer*)lua_touserdata(L, index);
		i = frame->GetTimerIndexByLabel(wxString(t->name,co));
	}
	else
	{
		c = luaL_checkstring(L,index);
		i = frame->GetTimerIndexByLabel(wxString(c,co));
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	
	frame->GetTimers()->at(i).SetActive(false);
	frame->GetTimers()->at(i).Stop();
	frame->m_scriptwin->SetTimers(*frame->GetTimers());
	return 0;
}

int luafunc_enabletimer(lua_State *L)
{
const char* c;
int i, index=1;
str_timer* t=NULL;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		t = (str_timer*)lua_touserdata(L, index++);
		i = frame->GetTimerIndexByLabel(wxString(t->name,co));
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetTimerIndexByLabel(wxString(c,co));
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetTimers()->at(i).SetActive(lua_toboolean(L,index)!=0);
	if (!t)
	{
		wxString s(c, co);
		lua_pushstring(L, s.mb_str(co).data());
	}
	else
	{
		t->on = frame->GetTimers()->at(i).IsActive();
		frame->m_scriptwin->SetTimers(*frame->GetTimers());
		lua_pushstring(L, t->name);
	}
	return 1;
}

//hotkey
int luafunc_newhk(lua_State *L)
{
hk_it it;
const char *cc;
amcHotkey hk;
str_hk* hkey;
int index=1;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
//	int x = sizeof(struct str_hk);
	if (lua_type(L,index)==LUA_TTABLE)
	{
		//lua_getfield(L, -1, c);
		lua_getfield(L, index, "name");
		cc = luaL_checkstring(L, -1);
		wxString f(cc, co);
		for (it=frame->GetHotkeys()->begin();it!=frame->GetHotkeys()->end();it++)
		{
			if(f==*it)
			{
				frame->m_scriptwin->Msg(_("Hotkey already exists!"));
				return 0;
			}
		}
		hk.SetName(f);
		lua_getfield(L, index, "action");
		cc = luaL_checkstring(L, -1);
		hk.SetAction(wxString(cc,co));
		lua_getfield(L, index, "group");
		cc = luaL_optstring(L, -1, "default");
		hk.SetGroup(wxString(cc,co));
		lua_getfield(L, index, "on");
		hk.SetActive(lua_toboolean(L,-1)!=0);
		lua_getfield(L, index, "keycode");
		map<wxString, long> m = frame->GetKeys();
		long k = m[luaL_checkstring(L, -1)];
		hk.SetHotkey(k);
		//hk.SetHotkey(luaL_checklong(L, -1));
		lua_getfield(L, index, "mod");
		int i = (int)m[luaL_checkstring(L,-1)];
		hk.SetMods(i);
	}
	else
	{
		cc = luaL_checkstring(L,index++);
		wxString f(cc, co);
		for (it=frame->GetHotkeys()->begin();it!=frame->GetHotkeys()->end();it++)
		{
			if(f==*it)
			{
				frame->m_scriptwin->Msg(_("Hotkey already exists!"));
				return 0;
			}
		}
		hk.SetName(f);
		cc = luaL_checkstring(L,index++);
		map<wxString, long> m = frame->GetKeys();
		long k = m[cc];
		hk.SetHotkey(k);
		cc = luaL_checkstring(L,index++);
		wxString g(cc, co);
		int i = (int)m[g];
		hk.SetMods(i);
		cc = luaL_checkstring(L,index++);
		hk.SetAction(wxString(cc,co));
		hk.SetGroup(wxString(luaL_optstring(L,index++, "default"),co));
		hk.SetActive(lua_toboolean(L,index++)!=0);
	}
	frame->GetHotkeys()->push_back(hk);
	frame->m_scriptwin->SetHotkeys(*frame->GetHotkeys());
	//stable_sort(frame->GetHotkeys()->begin(), frame->GetHotkeys()->end(), less<class amcHotkey>());
	hkey = (str_hk*)lua_newuserdata(L, sizeof(struct str_hk));
	wxStrcpy(hkey->name, hk.GetName().mb_str(co).data());// .mb_str());
	wxStrcpy(hkey->action, hk.GetAction().mb_str(co).data());// .mb_str());
	wxStrcpy(hkey->group, hk.GetGroup().mb_str(co).data());// .mb_str());
	hkey->on = hk.IsActive();
	hkey->keycode = hk.GetHotkey();
	hkey->mod = hk.GetModifier();
	luaL_getmetatable(L, "wxamcl.mthk");
	lua_setmetatable(L, -2);
	return 1;
}

int luafunc_gethk(lua_State *L)
{
str_hk* h;
const char* c;
int i, index=1;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		h = checkhk(L);
		wxString s(h->name,co);
		i = frame->GetHkIndexByLabel(s);
	}
	else if (lua_type(L,index)==LUA_TTABLE)
	{
		wxString s (luaL_checkstring(L, index+1),co);
		int idx = frame->GetHkIndexByLabel(s);
		if (idx==-1)
			return 0;
		wxString ss = frame->GetHotkeys()->at(idx).GetAction();
		lua_pushstring(L, ss.mb_str(co).data());// .mb_str());
		return 1;
	}
	else
	{
		c = luaL_checkstring(L,index);
		wxString s(c,co);
		i = frame->GetHkIndexByLabel(s);
	}
	if (i==-1)
	{
		frame->m_scriptwin->Msg(_("Hotkey not found!"));
		lua_pushnil(L);
		return 1;
	}
	lua_settop(L,0);
	lua_newtable(L);
	lua_pushstring(L, frame->GetHotkeys()->at(i).GetName().mb_str(co).data());// .char_str());
	lua_setfield(L, -2, "name");
	lua_pushstring(L, frame->GetHotkeys()->at(i).GetAction().mb_str(co).data());// .mb_str());
	lua_setfield(L, -2, "action");
	lua_pushstring(L, frame->GetHotkeys()->at(i).GetGroup().mb_str(co).data());// .mb_str());
	lua_setfield(L, -2, "group");
	lua_pushboolean(L, frame->GetHotkeys()->at(i).IsActive());
	lua_setfield(L, -2, "on");
	lua_pushstring(L, frame->GetHotkeys()->at(i).GetKeyName().mb_str(co).data());// .mb_str());
	lua_setfield(L, -2, "keyname");
	lua_pushstring(L, frame->GetHotkeys()->at(i).GetModName().mb_str(co).data());// .mb_str());
	lua_setfield(L, -2, "modname");
	lua_pushinteger(L, frame->GetHotkeys()->at(i).GetHotkey());
	lua_setfield(L, -2, "key");
	lua_pushinteger(L, frame->GetHotkeys()->at(i).GetModifier());
	lua_setfield(L, -2, "modifier");
	return 1;	
}

int luafunc_delhk(lua_State *L)
{
hk_it it;
const char* c;
int index=1, i;
str_hk* v;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		v = (str_hk*)lua_touserdata(L, index);
		i = frame->GetHkIndexByLabel(wxString(v->name,co));
	}
	else
	{
		c = luaL_checkstring(L,index);
		i = frame->GetHkIndexByLabel(wxString(c,co));
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	it = frame->GetHotkeys()->begin()+i;
	frame->GetHotkeys()->erase(it);
	frame->m_scriptwin->SetHotkeys(*frame->GetHotkeys());
	//v = NULL;
	//stable_sort(frame->GetVars()->begin(), frame->GetVars()->end(), less<class amcVar>());
	lua_pushinteger(L, frame->GetHotkeys()->size());
	return 1;
}

int luafunc_gethkaction(lua_State *L)
{
const char* l;
str_hk* t;
int index=1;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkhk(L);
		lua_pushstring(L, t->action);
		return 1;
	}

	else
	{
		l = luaL_checkstring(L,index);
		wxString s(l, co);
		int i = frame->GetHkIndexByLabel(s);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		else
			lua_pushstring(L, frame->GetHotkeys()->at(i).GetAction().mb_str(co).data());// .mb_str());
			return 1;
	}
	return 1;
}

int luafunc_sethkaction(lua_State *L)
{
const char* l;
const char* c;
amcHotkey hk;
str_hk* t;
int i, index=1;
	
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		//t = checkalias(L);
		t = (str_hk*)lua_touserdata(L, index);
		c = luaL_checkstring(L, ++index);
		i = frame->GetHkIndexByLabel(wxString(t->name,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		wxString s(c, co);
		frame->GetHotkeys()->at(i).SetAction(s);
		wxStrcpy(t->action, s.mb_str(co).data());
		return 0;
	}
	else
	{
		l = luaL_checkstring(L,index++);
		c = luaL_checkstring(L, index);
		i = frame->GetHkIndexByLabel(wxString(l,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetHotkeys()->at(i).SetAction(wxString(c,co));
		frame->m_scriptwin->SetHotkeys(*frame->GetHotkeys());
	}
	return 0;
}

int luafunc_enablehk(lua_State *L)
{
const char* c;
int i, index=1;
str_hk* v=NULL;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		v = (str_hk*)lua_touserdata(L, index++);
		i = frame->GetHkIndexByLabel(wxString(v->name,co));
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetHkIndexByLabel(wxString(c,co));
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetHotkeys()->at(i).SetActive(lua_toboolean(L,index)!=0);
	if (!v)
	{
		wxString s(c, co);
		lua_pushstring(L,s.mb_str(co).data());
	}
	else
	{
		v->on = frame->GetHotkeys()->at(i).IsActive();
		frame->m_scriptwin->SetHotkeys(*frame->GetHotkeys());
		lua_pushstring(L, v->name);
	}
	return 1;
}

int luafunc_deletehkgroup(lua_State *L)
{
const char* c;
s_it it;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	c = luaL_checkstring(L,1);
	wxString s(c, co);
	bool del = lua_toboolean(L,2)!=0;
	if (del)
	{
		for (size_t i=0;i<frame->GetHotkeys()->size(); i++)
		{
			if(frame->GetHotkeys()->at(i).GetGroup()==s)
			{
				frame->GetHotkeys()->erase(frame->GetHotkeys()->begin()+i--);
			}
		}
	}
	else
	{
		for (size_t i=0;i<frame->GetHotkeys()->size(); i++)
		{
			if(frame->GetHotkeys()->at(i).GetGroup()==s)
			{
				frame->GetHotkeys()->at(i).SetGroup("default");
			}
		}
	}
	for (it = amcHotkey::GetHotkeyGroups()->begin(); it!=amcHotkey::GetHotkeyGroups()->end(); it++)
	{
		if (*it == s)
		{
			amcHotkey::GetHotkeyGroups()->erase(it);
			break;
		}
	}
	frame->m_scriptwin->SetHotkeys(*frame->GetHotkeys());
	return 0;
}

int luafunc_enablehkgroup(lua_State *L)
{
hk_it iter;
const char* hkgroup;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	hkgroup = luaL_checkstring(L, 1);
	wxString hkg(hkgroup, co);
	bool active = lua_toboolean(L,2) != 0;
	for (iter = frame->GetHotkeys()->begin(); iter!= frame->GetHotkeys()->end(); iter++)
	{
		if (hkg == iter->GetGroup())
		{
			iter->SetActive(active);
		}
	}
	if (frame->IsVerbose())
	{
		wxString s;
		if (active)
			s<<_("Enabled hotkey group ")<<hkg<<".";
		else
			s<<_("Disabled hotkey group ")<<hkg<<".";
		frame->m_scriptwin->Msg(s, 3);
	}
	frame->m_scriptwin->SetHotkeys(*frame->GetHotkeys());
	return 0;
}

int luafunc_getallhk(lua_State *L)
{
size_t i;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	lua_settop(L,0);
	lua_newtable(L);
	for (i=0;i<frame->GetHotkeys()->size();i++)
	{
		lua_pushstring(L, frame->GetHotkeys()->at(i).GetName().mb_str(co).data());// .mb_str());
		lua_rawseti(L, -2, i+1);
	}
	lua_pushinteger(L, i);
	return 2;
}

int luafunc_exechk(lua_State *L)
{
const char* c;
int i, index=1;
str_hk* v=NULL;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		v = (str_hk*)lua_touserdata(L, index++);
		i = frame->GetHkIndexByLabel(wxString(v->name,co));
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetHkIndexByLabel(wxString(c,co));
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	int state = frame->m_scriptwin->GetParseState();
	frame->m_scriptwin->SetParseState(0);//HAVE_TEXT
	wxString command = frame->GetHotkeys()->at(i).GetAction();
	frame->m_input->Parse(command, true);
	frame->m_scriptwin->SetParseState(state);
	return 0;
}

//var
int luafunc_newvar(lua_State *L)
{
v_it it;
const char* cc;
amcVar v;
str_var* a;
int index=1;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
//	int x = sizeof(struct str_var);
	if (lua_type(L,index)==LUA_TTABLE)
	{
		//lua_getfield(L, -1, c);
		lua_getfield(L, index, "name");
		cc = luaL_checkstring(L, -1);
		wxString s(cc, co);
		for (it=frame->GetVars()->begin();it!=frame->GetVars()->end();it++)
		{
			if(s==*it)
			{
				frame->m_scriptwin->Msg(_("Variable already exists!"));
				return 0;
			}
		}
		v.SetName(s);
		lua_getfield(L, index, "value");
		cc = luaL_checkstring(L, -1);
		v.SetValue(wxString(cc,co));
		lua_getfield(L, index, "group");
		cc = luaL_optstring(L, -1, "default");
		v.SetGroup(wxString(cc,co));
		lua_getfield(L, index, "on");
		v.SetActive(lua_toboolean(L,-1)!=0);
	}
	else
	{
		cc = luaL_checkstring(L,index++);
		wxString s(cc, co);
		for (it=frame->GetVars()->begin();it!=frame->GetVars()->end();it++)
		{
			if(s==*it)
			{
				frame->m_scriptwin->Msg(_("Variable already exists!"));
				return 0;
			}
		}
		v.SetName(s);
		cc = luaL_checkstring(L,index++);
		v.SetValue(wxString(cc,co));
		v.SetGroup(wxString(luaL_optstring(L,index++, "default"),co));
		v.SetActive(lua_toboolean(L,index++)!=0);
	}
	frame->GetVars()->push_back(v);
	stable_sort(frame->GetVars()->begin(), frame->GetVars()->end(), less<class amcVar>());
	frame->m_scriptwin->SetVars(*frame->GetVars());
	a = (str_var*)lua_newuserdata(L, sizeof(struct str_var));
	wxStrcpy(a->name, v.GetName().mb_str(co).data());// .c_str());
	wxStrcpy(a->value, v.GetValue().mb_str(co).data());// .c_str());
	wxStrcpy(a->group, v.GetGroup().mb_str(co).data());// .c_str());
	a->on = v.IsActive();
	luaL_getmetatable(L, "wxamcl.mtv");
	lua_setmetatable(L, -2);
	return 1;
	
}

//wegen amc.vars.ab = nil in scripts
int luafunc_newvar1(lua_State*L)
{
v_it it;
const char* cc;
amcVar v;
str_var* av;
int index=1;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	//int x= sizeof(struct str_al);
	if (lua_type(L,index)==LUA_TTABLE)
	{
		//lua_getfield(L, -1, c);
		cc = luaL_checkstring(L, -2);
		if (lua_type(L, -1)==LUA_TNIL)
		{
			int i = frame->GetVarIndexByLabel(wxString(cc,co));
			if (i==-1)
			{
				lua_pushnil(L);
				return 1;
			}
			v_it it = frame->GetVars()->begin()+i;
			frame->GetVars()->erase(it);
			stable_sort(frame->GetVars()->begin(), frame->GetVars()->end(), greater<class amcVar>());
			frame->m_scriptwin->SetVars(*frame->GetVars());
			lua_pushinteger(L, frame->GetVars()->size());
			return 1;
		}
		wxString s(cc,co);
		for (it=frame->GetVars()->begin();it!=frame->GetVars()->end();it++)
		{
			if(s==*it)
			{
				frame->m_scriptwin->Msg(_("Variable already exists!"));
				return 0;
			}
		}
		v.SetName(s);
		lua_getfield(L, -1, "value");
		cc = luaL_checkstring(L, -1);
		v.SetValue(wxString(cc,co));
		lua_getfield(L, -2, "group");
		cc = luaL_optstring(L, -1, "default");
		v.SetGroup(wxString(cc,co));
		lua_getfield(L, -3, "on");
		v.SetActive(lua_toboolean(L,-1)!=0);
	}
	
	frame->GetVars()->push_back(v);
	stable_sort(frame->GetVars()->begin(), frame->GetVars()->end(), less<class amcVar>());
	frame->m_scriptwin->SetVars(*frame->GetVars());
	av = (str_var*)lua_newuserdata(L, sizeof(struct str_var));
	wxStrcpy(av->name, v.GetName().mb_str(co).data());// .c_str());
	wxStrcpy(av->value, v.GetValue().mb_str(co).data());// .c_str());
	wxStrcpy(av->group, v.GetGroup().mb_str(co).data());// .c_str());
	av->on = v.IsActive();
	luaL_getmetatable(L, "wxamcl.mtv");
	lua_setmetatable(L, -2);
	return 1;
}

int luafunc_getvar(lua_State *L)
{
const char* name;
str_var* v;
int idx;
	MudMainFrame *frame = (MudMainFrame*)wxGetApp().GetFrame();
	MudWindow *mw = frame->m_scriptwin;
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,1)==LUA_TUSERDATA)
	{
		v = checkvar(L);
		wxString s(v->name, co);
		idx = mw->GetVarIndexByLabel(s);
	}
	else if (lua_type(L, 1) == LUA_TTABLE)
	{
		wxString s(luaL_checkstring(L, 2), co);
		idx = mw->GetVarIndexByLabel(s);
	}
	else
	{
		name = luaL_checkstring(L, 1);
		idx = mw->GetVarIndexByLabel(wxString(name,co));
	}
	if (idx==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	long number;
	wxString ss = mw->GetVars()->at(idx).GetValue().mb_str(co);

	if (ss.ToLong(&number))
		lua_pushinteger(L, number);
	else
		lua_pushstring(L, mw->GetVars()->at(idx).GetValue().mb_str(co).data());// .mb_str());
	return 1;
}

int luafunc_setvar(lua_State *L)
{
const char* name;
const char* value;
int idx;
str_var* v;
int index=1;
	MudMainFrame *frame = wxGetApp().GetFrame();
	MudWindow *mw = frame->m_scriptwin;
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		v = checkvar(L);
		value = (char*)luaL_checkstring(L, ++index);
		idx = mw->GetVarIndexByLabel(wxString(v->name,co));
		if (idx==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		wxString s(value,co);
		frame->m_input->ParseVars(&s);
		frame->GetVars()->at(idx).SetValue(s);
		frame->m_scriptwin->SetVars(*frame->GetVars());
		wxStrcpy(v->value, s.mb_str(co).data());// .c_str());
		lua_pushboolean(L, 1);
		return 1;
	}
	else
	{
		name = luaL_checkstring(L, 1);
		idx = mw->GetVarIndexByLabel(wxString(name,co));
		if (idx==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		value = luaL_checkstring(L, 2);
		wxString s(value,co);
		frame->m_input->ParseVars(&s);
		frame->GetVars()->at(idx).SetValue(s);
		frame->m_scriptwin->SetVars(*frame->GetVars());
		lua_pushboolean(L, 1);
		return 1;
	}
}

int luafunc_delvar(lua_State *L)
{
v_it it;
const char* c;
int index=1, i;
str_var* v;

	MudMainFrame *frame = wxGetApp().GetFrame();
	MudWindow *mw = frame->m_scriptwin;
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		v = (str_var*)lua_touserdata(L, index);
		i = mw->GetVarIndexByLabel(wxString(v->name,co));
	}
	else
	{
		c = luaL_checkstring(L,index);
		i = mw->GetVarIndexByLabel(wxString(c,co));
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	it = mw->GetVars()->begin()+i;
	mw->GetVars()->erase(it);
	v = NULL;
	stable_sort(mw->GetVars()->begin(), mw->GetVars()->end(), less<class amcVar>());
	frame->SetVars(*mw->GetVars());
	//frame->m_scriptwin->SetVars(*->GetVars());
	lua_pushinteger(L, mw->GetVars()->size());
	return 1;
}

int luafunc_enablevar(lua_State *L)
{
const char* c;
int i, index=1;
str_var* v=NULL;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		v = (str_var*)lua_touserdata(L, index++);
		i = frame->GetVarIndexByLabel(wxString(v->name,co));
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetVarIndexByLabel(wxString(c,co));
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetVars()->at(i).SetActive(lua_toboolean(L,index)!=0);
	if (!v)
	{
		wxString s(c, co);
		lua_pushstring(L,s.mb_str(co).data());
	}
	else
	{
		v->on = frame->GetVars()->at(i).IsActive();
		lua_pushstring(L, v->name);
	}
	frame->m_scriptwin->SetVars(*frame->GetVars());
	return 1;
}

int luafunc_getallvar(lua_State *L)
{
	size_t i;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	lua_settop(L,0);
	lua_newtable(L);
	for (i=0;i<frame->GetVars()->size();i++)
	{
		lua_pushstring(L, frame->GetVars()->at(i).GetName().mb_str(co).data());// .mb_str());
		lua_rawseti(L, -2, i+1);
	}
	lua_pushinteger(L, i);
	return 2;
}

int luafunc_enablevargroup(lua_State *L)
{
v_it iter;
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	const char* vgroup;
	vgroup = luaL_checkstring(L, 1);
	wxString vgr(vgroup, co);
	bool active = lua_toboolean(L,2) != 0;
	for (iter = frame->GetVars()->begin(); iter!= frame->GetVars()->end(); iter++)
	{
		if (vgr == iter->GetGroup())
		{
			iter->SetActive(active);
		}
	}
	if (frame->IsVerbose())
	{
		wxString s;
		if (active)
			s<<_("Enabled variable group ")<<vgr<<".";
		else
			s<<_("Disabled variable group ")<<vgr<<".";
		frame->m_scriptwin->Msg(s, 3);
	}
	frame->m_scriptwin->SetVars(*frame->GetVars());
	return 0;
}

int luafunc_delvargroup(lua_State *L)
{
s_it it;
const char* vgroup;
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	vgroup = luaL_checkstring(L, 1);
	wxString vgr(vgroup, co);
	for (size_t i=0;i<frame->GetVars()->size(); i++)
	{
		if(frame->GetVars()->at(i).GetGroup()==vgr)
		{
			frame->GetVars()->erase(frame->GetVars()->begin()+i--);
		}
	}
	
	for (it = amcVar::GetVarGroups()->begin(); it!=amcVar::GetVarGroups()->end(); it++)
	{
		if (*it == vgr)
		{
			amcVar::GetVarGroups()->erase(it);
			if (frame->IsVerbose())
			{
				wxString s;
				s<<_("Deleted variable class ")<<vgr<<".";
				frame->m_scriptwin->Msg(s, 3);
			}
			frame->m_scriptwin->SetVars(*frame->GetVars());
			return 0;
		}
	}
	if (it==amcVar::GetVarGroups()->end())
	{
		wxString s;
		s<<_("Group ")<<vgr<<_(" does not exist!");
		frame->m_scriptwin->Msg(s,3);
		return 0;
	}
	
	return 0;
}


//list
int luafunc_newlist(lua_State *L)
{
amcList list;
li_it it;
const char* c;
str_ll* l;
int index=1;

	MudMainFrame *frame = (MudMainFrame*)wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
//	int x= sizeof(struct str_ll);
	//called from amc.newlist
	if(lua_type(L, index) != LUA_TTABLE)
	{
		c = luaL_checkstring(L, index++);
		wxString s(c, co);
		for (it=frame->GetLists()->begin();it!=frame->GetLists()->end();it++)
		{
			if(s==*it)
			{
				frame->m_scriptwin->Msg(_("Error creating list!"));
				return 0;
			}
		}
		list.SetName(s);
	}

	if (lua_type(L,index)==LUA_TTABLE)
	{
		//lua_getfield(L, -1, c);
		lua_getfield(L, index, "name");
		const char* cc = luaL_checkstring(L, -1);
		wxString s(cc, co);
		for (it=frame->GetLists()->begin();it!=frame->GetLists()->end();it++)
		{
			if(s==*it)
			{
				frame->m_scriptwin->Msg(_("List already exists!"));
				return 0;
			}
		}
		list.SetName(s);
		lua_getfield(L, index, "group");
		cc = luaL_optstring(L, -1, "default");
		list.SetGroup(wxString(cc,co));
		lua_getfield(L, index, "on");
		list.SetActive(lua_toboolean(L,-1)!=0);
		}
	else
	{
		/*c = (char*)luaL_checkstring(L,index++);
		for (it=frame->GetLists()->begin();it!=frame->GetLists()->end();it++)
		{
			if(c==*it)
			{
				frame->m_child->Msg(_("List already exists!"));
				return 0;
			}
		}
		list.SetName(c);*/
		list.SetGroup(wxString(luaL_optstring(L,index++, "default"),co));
		list.SetActive(lua_toboolean(L,index++)!=0);
		
	}
	frame->GetLists()->push_back(list);
	frame->m_scriptwin->SetLists(*frame->GetLists());
	//stable_sort(frame->GetLists()->begin(), frame->GetLists()->end(), less<class amcList>());
	l = (str_ll*)lua_newuserdata(L, sizeof(struct str_ll));
	wxStrcpy(l->name, list.GetName().mb_str(co).data());// .c_str());
	//l->name = list.GetName();
	wxStrcpy(l->cla, list.GetGroup().mb_str(co).data());// .c_str());
	l->on = list.IsActive();
	luaL_getmetatable(L, "wxamcl.mtll");
	lua_setmetatable(L, -2);
	return 1;
}

int luafunc_getlist(lua_State *L)
{
const char* c;
int i, index=1;
str_ll* l;

	MudMainFrame *frame = (MudMainFrame*)wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		l = (str_ll*)lua_touserdata(L, index++);
		i = frame->GetListIndexByLabel(wxString(l->name,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetListIndexByLabel(wxString(c,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
	}
	lua_settop(L,0);
	lua_newtable(L);
	int con = frame->GetLists()->at(i).GetSize();
	for (int ii=0;ii<con;ii++)
	{
		lua_pushstring(L, frame->GetLists()->at(i).GetItem(ii).mb_str(co).data());
		lua_rawseti(L, -2, ii+1);
	}
	lua_pushinteger(L, con);
	return 2;
}

int luafunc_getitemat(lua_State *L)
{
const char* c;
int i, index=1;
str_ll* l;

	MudMainFrame *frame = (MudMainFrame*)wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		l = (str_ll*)lua_touserdata(L, index++);
		i = frame->GetListIndexByLabel(wxString(l->name,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetListIndexByLabel(wxString(c,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
	}
	int con = luaL_checknumber(L, index);
	if (con>frame->GetLists()->at(i).GetSize()||!con)
	{
		if (frame->IsVerbose())
		{
			frame->m_scriptwin->Msg(_("Given index out of bounds!"), 3);
		}
		lua_pushnil(L);
		return 1;
	}
	lua_pushstring(L, frame->GetLists()->at(i).GetItem(con - 1).mb_str(co).data());//.c_str());
	return 1;
}

int luafunc_additem(lua_State *L)
{
const char* c;
int i, index=1;
str_ll* l;

	MudMainFrame *frame = (MudMainFrame*)wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		l = (str_ll*)lua_touserdata(L, index++);
		i = frame->GetListIndexByLabel(wxString(l->name,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		c = luaL_checkstring(L, index++);
		wxString s(c, co);
		wxStrcpy(l->items[frame->GetLists()->at(i).GetSize()], s.mb_str(co).data());
		frame->GetLists()->at(i).AddItem(s);
		frame->m_scriptwin->SetLists(*frame->GetLists());
		lua_pushinteger(L, frame->GetLists()->at(i).GetSize());
		return 1;
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetListIndexByLabel(wxString(c,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		c = luaL_checkstring(L, index);
		frame->GetLists()->at(i).AddItem(wxString(c,co));
		frame->m_scriptwin->SetLists(*frame->GetLists());
		lua_pushinteger(L, frame->GetLists()->at(i).GetSize());
		return 1;
	}
	return 0;
}

int luafunc_delallitems(lua_State *L)
{
char* c;
int i, index=1;
str_ll* l;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		l = (str_ll*)lua_touserdata(L, index++);
		i = frame->GetListIndexByLabel(wxString(l->name,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetLists()->at(i).ClearItems();
		//todo empty ll->items
		return 0;
	}
	else
	{
		c = (char*)luaL_checkstring(L,index++);
		i = frame->GetListIndexByLabel(wxString(c,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetLists()->at(i).ClearItems();
		frame->m_scriptwin->SetLists(*frame->GetLists());
		return 0;
	}
	return 0;
}

int luafunc_dellist(lua_State *L)
{
li_it it;
const char* c;
int index=1, i;
str_ll* l;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		l = (str_ll*)lua_touserdata(L, index);
		i = frame->GetListIndexByLabel(wxString(l->name,co));
	}
	else
	{
		c = luaL_checkstring(L,index);
		i = frame->GetListIndexByLabel(wxString(c,co));
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	it = frame->GetLists()->begin()+i;
	frame->GetLists()->erase(it);
	l = NULL;
	stable_sort(frame->GetLists()->begin(), frame->GetLists()->end(), less<class amcList>());
	frame->m_scriptwin->SetLists(*frame->GetLists());
	lua_pushinteger(L, frame->GetLists()->size());
	return 1;
}

int luafunc_delitemat(lua_State *L)
{
li_it it;
const char* c;
int idx=0;
int index=1, i;
str_ll* l;
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		l = (str_ll*)lua_touserdata(L, index++);
		i = frame->GetListIndexByLabel(wxString(l->name,co));
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetListIndexByLabel(wxString(c,co));
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	//idx=luaL_checkint(L, index);
	idx = (int)luaL_checknumber(L, index);
	if (idx>frame->GetLists()->at(i).GetSize())
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetLists()->at(i).DeleteItemAt(idx-1);
	frame->m_scriptwin->SetLists(*frame->GetLists());
	lua_pushinteger(L, frame->GetLists()->size());
	return 1;
}

int luafunc_delitem(lua_State *L)
{
li_it it;
const char* c;
int index=1, i;
str_ll* l;
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		l = (str_ll*)lua_touserdata(L, index++);
		i = frame->GetListIndexByLabel(wxString(l->name,co));
	}
	else
	{
		c = luaL_checkstring(L,index++);
		wxString s(c, co);
		i = frame->GetListIndexByLabel(s);
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	c=luaL_checkstring(L, index);
	wxString s(c, co);
	if (!frame->GetLists()->at(i).DeleteItem(s))
	{
		lua_pushnil(L);
		return 1;
	}
	frame->m_scriptwin->SetLists(*frame->GetLists());
	lua_pushinteger(L, frame->GetLists()->size());
	return 1;
}

int luafunc_contains(lua_State *L)
{
li_it it;
const char* c;
int index=1, i;
str_ll* l;
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		l = (str_ll*)lua_touserdata(L, index++);
		i = frame->GetListIndexByLabel(wxString(l->name,co));
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetListIndexByLabel(wxString(c,co));
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	c = luaL_checkstring(L, index);
	wxString s(c, co);
	if (!frame->GetLists()->at(i).Contains(s))
		lua_pushboolean(L, 0);
	else
		lua_pushboolean(L, 1);
	return 1;
}

int luafunc_getsize(lua_State *L)
{
const char* c;
int i, index=1;
str_ll* l;

	MudMainFrame *frame = (MudMainFrame*)wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		l = (str_ll*)lua_touserdata(L, index++);
		i = frame->GetListIndexByLabel(wxString(l->name,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetListIndexByLabel(wxString(c,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
	}
	lua_pushinteger(L, frame->GetLists()->at(i).GetSize());
	return 1;
}

int luafunc_enablelistgroup(lua_State *L)
{
li_it iter;
MudMainFrame *frame = wxGetApp().GetFrame();
wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
const char* lgroup;
bool exist = false;
	lgroup = luaL_checkstring(L, 1);
	wxString lgr(lgroup, co);
	bool active = lua_toboolean(L,2) != 0;
	for (iter = frame->GetLists()->begin(); iter!= frame->GetLists()->end(); iter++)
	{
		if (lgr == iter->GetGroup())
		{
			iter->SetActive(active);
			exist = true;
		}
	}
	if (!exist)
	{
		wxString s;
		s<<_("Group ")<<lgr<<_(" does not exist!");
		frame->m_scriptwin->Msg(s,3);
		return 0;
	}
	if (frame->IsVerbose())
	{
		wxString s;
		if (active)
			s<<_("Enabled list group ")<<lgr<<".";
		else
			s<<_("Disabled list group ")<<lgr<<".";
		frame->m_scriptwin->Msg(s, 3);
	}
	frame->m_scriptwin->SetLists(*frame->GetLists());
	return 0;
}

int luafunc_getalllist(lua_State *L)
{
	size_t i;
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	lua_settop(L,0);
	lua_newtable(L);
	for (i=0;i<frame->GetLists()->size();i++)
	{
		lua_pushstring(L, frame->GetLists()->at(i).GetName().mb_str(co).data());
		lua_rawseti(L, -2, i+1);
	}
	lua_pushinteger(L, i);
	return 2;
}

int luafunc_dellistgroup(lua_State *L)
{
s_it it;
const char* lgroup;
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	lgroup = luaL_checkstring(L, 1);
	wxString lgr(lgroup, co);
	for (size_t i=0;i<frame->GetLists()->size(); i++)
	{
		if(frame->GetLists()->at(i).GetGroup()==lgr)
		{
			frame->GetLists()->erase(frame->GetLists()->begin()+i--);
		}
	}
	
	for (it = amcList::GetListGroups()->begin(); it!=amcList::GetListGroups()->end(); it++)
	{
		if (*it == lgr)
		{
			amcList::GetListGroups()->erase(it);
			if (frame->IsVerbose())
			{
				wxString s;
				s<<_("Deleted list group ")<<lgr<<".";
				frame->m_scriptwin->Msg(s, 3);
			}
			frame->m_scriptwin->SetLists(*frame->GetLists());
			return 0;
		}
	}
	if (it==amcList::GetListGroups()->end())
	{
		wxString s;
		s<<_("Group ")<<lgr<<_(" does not exist!");
		frame->m_scriptwin->Msg(s,3);
		return 0;
	}
	
	return 0;
}

//gauges
int luafunc_gauge(lua_State *L)
{
	const char* winname;
	const char* gauge;
	winname=luaL_checkstring(L, 1);
	gauge=luaL_checkstring(L, 2);
	wxString name(winname);
	unordered_map<wxString, wxWindow*> um = *wxGetApp().GetFrame()->m_scriptwin->GetUserWindows();
	class GaugeWindow *frame = (GaugeWindow*)um[name];
	//class GaugeWindow *frame = (GaugeWindow*)GaugeWindow::FindWindowByName(*name);
	
	if (frame==NULL)
	{
		//delete name;
		lua_pushnil(L);
		return 1;
	}

	//delete name;
	wxClientDC dc(frame);
	
	frame->Refresh();
	lua_pushboolean(L, TRUE);
	return 1;
}

int luafunc_newgauge(lua_State *L)
{
	const char* winname;
	const char* name;
	const char* var1;
	const char* var2;
	const char* fcol;
	const char* bcol;
	unsigned int i;
	bool vert;
	//long col, bcolor;
	winname=luaL_checkstring(L, 1);
	name=luaL_checkstring(L, 2);
	var1=luaL_checkstring(L, 3);
	var2=luaL_checkstring(L, 4);
	fcol=luaL_optstring(L, 5, "white");
	bcol=luaL_optstring(L, 6, "black");
	vert=(lua_toboolean(L,7)!=0);
	class MudWindow *frame = wxGetApp().GetFrame()->m_scriptwin;
	if (frame == NULL)
	{
		lua_pushnil(L);
		return 1;
	}
	wxString s(fcol);
	if (s.at(0)=='#')
	{
		fcol = "custom";
		long col = frame->ParseHexColor(s.substr(1));
		frame->SetCustomColour(col);
	}
	wxString bs(bcol);
	if (bs.at(0)=='#')
	{
		bcol = "bcustom";
		long col = frame->ParseHexColor(bs.substr(1));
		frame->SetColour(19, col);
	}
	map<wxString, int> b = frame->GetBCol();
	class MudMainFrame *f = wxGetApp().GetFrame();
	int idx = f->GetVarIndexByLabel(var1);
	if (idx == -1)
	{
		amcVar v1(var1, "1", "gauges");
		f->GetVars()->push_back(v1);
		f->m_scriptwin->GetVars()->push_back(v1);
		stable_sort(f->GetVars()->begin(), f->GetVars()->end(), less<class amcVar>());
		stable_sort(f->m_scriptwin->GetVars()->begin(), f->m_scriptwin->GetVars()->end(), less<class amcVar>());
		f->luaBuildvar();
	}
	idx = f->GetVarIndexByLabel(var2);
	if (idx == -1)
	{
		amcVar v2(var2, "1", "gauges");
		f->GetVars()->push_back(v2);
		f->m_scriptwin->GetVars()->push_back(v2);
		stable_sort(f->GetVars()->begin(), f->GetVars()->end(), less<class amcVar>());
		stable_sort(f->m_scriptwin->GetVars()->begin(), f->m_scriptwin->GetVars()->end(), less<class amcVar>());
		f->luaBuildvar();
	}
	wxCSConv co(f->GetGlobalOptions()->GetCurEncoding());
	wxString n(name, co);
	amcGauge g(winname, n, var1, var2, frame->GetColour(b[fcol]-40), frame->GetColour(b[bcol]-40), 10, 10, 100, 40, vert);
	
	if (!f->GetGaugePanes()->empty())
	{
		for (i=0;i<f->GetGaugePanes()->size();i++)
		{
			if (winname==f->GetGaugePanes()->at(i))
				break;
		}
	}
	g.Register();
	f->GetGauges()->at(i).push_back(n);
	f->m_scriptwin->SetGauges(*f->GetGauges());
	//frame->GetGauges()->at(idx).DrawGauge();
	lua_pushboolean(L, TRUE);
	return 1;
}

int luafunc_sizegauge(lua_State *L)
{
	const char *winname;
	const char * gauge;
	int x,y,cx,cy;
	MudMainFrame *f = wxGetApp().GetFrame();
	wxCSConv co(f->GetGlobalOptions()->GetCurEncoding());
	winname = luaL_checkstring(L, 1);
	gauge = luaL_checkstring(L, 2);
	x = (int)luaL_optnumber(L, 3, 10);
	y = (int)luaL_optnumber(L, 4, 10);
	cx = (int)luaL_optnumber(L, 5, 100);
	cy = (int)luaL_optnumber(L, 6, 40);
	
	wxString name(winname, co);
	unordered_map<wxString, wxWindow*> um = *f->m_scriptwin->GetUserWindows();
	class GaugeWindow *frame = (GaugeWindow*)um[name];
	//class GaugeWindow *frame = (GaugeWindow*)GaugeWindow::FindWindowByName(winname);
	if (frame == NULL)
	{
		lua_pushnil(L);
		return 1;
	}
	
	wxString g(gauge, co);
	int idx = frame->GetGaugeIndexByName(g);
	if (idx==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetGauges()->at(idx).SetX(x);
	frame->GetGauges()->at(idx).SetY(y);
	frame->GetGauges()->at(idx).SetCx(cx);
	frame->GetGauges()->at(idx).SetCy(cy);
	//frame->m_scriptwin->SetGauges(*frame->GetGauges());
	wxClientDC dc(frame);
	//frame->GetGauges()->at(idx).DrawGauge(&dc);
	frame->Refresh();
	//frame->Update();
	lua_pushboolean(L, TRUE);
	return 1;
}
int luafunc_colorgauge(lua_State *L)
{
	const char* fcol;
	const char* bcol;
	const char* alarm;
	const char* winname;
	const char* gauge;
	MudMainFrame *f = wxGetApp().GetFrame();
	wxCSConv co(f->GetGlobalOptions()->GetCurEncoding());

	winname = luaL_checkstring(L, 1);
	gauge = luaL_checkstring(L, 2);
	fcol=luaL_optstring(L, 3, "white");
	bcol=luaL_optstring(L, 4, "black");
	alarm=luaL_optstring(L, 5, "red");
	wxString name(winname, co);
	unordered_map<wxString, wxWindow*> um = *f->m_scriptwin->GetUserWindows();
	class GaugeWindow *frame = (GaugeWindow*)um[name];
	//class GaugeWindow *frame = (GaugeWindow*)GaugeWindow::FindWindowByName(winname);
	class MudWindow *frame1 = wxGetApp().GetFrame()->m_scriptwin;
	if (frame == NULL)
	{
		lua_pushnil(L);
		return 1;
	}
	wxString s(fcol);
	if (s.at(0)=='#')
	{
		fcol = "custom";
		long col = frame1->ParseHexColor(s.substr(1));
		frame1->SetCustomColour(col);
	}
	wxString bs(bcol);
	if (bs.at(0)=='#')
	{
		bcol = "bcustom";
		long col = frame1->ParseHexColor(bs.substr(1));
		frame1->SetColour(19, col);
	}
	map<wxString, int> b = frame1->GetBCol();
	
	wxString g(gauge, co);
	int idx = frame->GetGaugeIndexByName(g);
	if (idx==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetGauges()->at(idx).SetFCol(frame1->GetColour(b[fcol]-40));
	frame->GetGauges()->at(idx).SetBCol(frame1->GetColour(b[bcol]-40));
	frame->GetGauges()->at(idx).SetAlarmCol(frame1->GetColour(b[alarm]-40));
	//wxClientDC dc(frame);
	//frame->GetGauges()->at(idx).DrawGauge(&dc);
	frame->Refresh();
	lua_pushboolean(L, TRUE);
	return 1;
}

int luafunc_creategaugewin(lua_State*L)
{
	const char* winname;
	GaugeWindow *gw;
	class MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	
	winname = luaL_checkstring(L,1);
	wxString wname(winname, co);
	unordered_map<wxString, wxWindow*> um = *frame->m_scriptwin->GetUserWindows();
	gw = (GaugeWindow*)um[wname];
	//gw = (GaugeWindow*)GaugeWindow::FindWindowByName(winname, frame);
	if (gw)
		return 0;
	gw = new GaugeWindow(frame, wname);
	gw->SetName(wname);
	frame->GetGaugePanes()->push_back(wname);
	frame->m_scriptwin->SetGaugePanes(*frame->GetGaugePanes());
	um[wname] = gw;
	frame->m_scriptwin->SetUserWindows(um);
	
	vector<wxString> s;
	frame->GetGauges()->push_back(s);
	frame->m_scriptwin->SetGauges(*frame->GetGauges());
	frame->m_mgr.AddPane(gw, wxAuiPaneInfo().Name(wname).Caption(wname).CaptionVisible(true).Floatable(true).FloatingSize(400,200).BestSize(400,200).Dockable(true).Dock().Top().Layer(1));
	
	frame->m_mgr.Update();
	return 0;
}

int luafunc_setgaugelabel(lua_State *L)
{
	const char* winname;
	const char* gauge;
	const char* label;
	MudMainFrame *f = wxGetApp().GetFrame();
	wxCSConv co(f->GetGlobalOptions()->GetCurEncoding());
	winname = luaL_checkstring(L, 1);
	gauge = luaL_checkstring(L, 2);
	label = luaL_checkstring(L, 3);
	wxString wname(winname, co);
	unordered_map<wxString, wxWindow*> um = *f->m_scriptwin->GetUserWindows();
	class GaugeWindow *frame = (GaugeWindow*)um[wname];
	//class GaugeWindow *frame = (GaugeWindow*)GaugeWindow::FindWindowByName(winname);

	if (frame == NULL)
	{
		lua_pushnil(L);
		return 1;
	}
	
	wxString g(gauge, co);
	int idx = frame->GetGaugeIndexByName(g);
	if (idx==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetGauges()->at(idx).SetLabel(wxString(label,co));
	//frame->m_scriptwin->SetGauges(*frame->GetGauges());
	wxClientDC dc(frame);
	
	frame->Refresh();
	lua_pushboolean(L, TRUE);
	return 1;
}

int luafunc_deletegauge(lua_State *L)
{
const char* winname;
const char* gauge;
	
	MudMainFrame *f = wxGetApp().GetFrame();
	wxCSConv co(f->GetGlobalOptions()->GetCurEncoding());
	winname = luaL_checkstring(L, 1);
	gauge = luaL_checkstring(L, 2);
	wxString wname(winname, co);
	unordered_map<wxString, wxWindow*> um = *f->m_scriptwin->GetUserWindows();
	class GaugeWindow *frame = (GaugeWindow*)um[wname];
	//class GaugeWindow *frame = (GaugeWindow*)GaugeWindow::FindWindowByName(winname);

	if (frame == NULL)
	{
		lua_pushnil(L);
		return 1;
	}
	
	wxString g(gauge, co);
	int idx = frame->GetGaugeIndexByName(g);
	if (idx==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetGauges()->erase(frame->GetGauges()->begin()+idx);
	wxClientDC dc(frame);
	
	frame->Refresh();
	lua_pushboolean(L, TRUE);
	return 1;
}

int luafunc_setstyle(lua_State *L)
{
	const char* winname;
	const char* gauge;
	int style;
	MudMainFrame *f = wxGetApp().GetFrame();
	wxCSConv co(f->GetGlobalOptions()->GetCurEncoding());
	winname = luaL_checkstring(L, 1);
	gauge = luaL_checkstring(L, 2);
	style = luaL_optint(L, 3, 0);
	wxString wname(winname, co);
	unordered_map<wxString, wxWindow*> um = *f->m_scriptwin->GetUserWindows();
	class GaugeWindow *frame = (GaugeWindow*)um[wname];
	//class GaugeWindow *frame = (GaugeWindow*)GaugeWindow::FindWindowByName(winname);
	if (frame == NULL)
	{
		lua_pushnil(L);
		return 1;
	}
	
	wxString g(gauge, co);
	int idx = frame->GetGaugeIndexByName(g);
	if (idx == -1)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetGauges()->at(idx).SetStyle(style);
	frame->Refresh();
	lua_pushboolean(L, TRUE);
	return 1;
}

int luafunc_settextpos(lua_State *L)
{
const char* winname;
const char* gauge;
int pos;

	MudMainFrame *f = wxGetApp().GetFrame();
	wxCSConv co(f->GetGlobalOptions()->GetCurEncoding());
	winname = luaL_checkstring(L, 1);
	gauge = luaL_checkstring(L, 2);
	pos = luaL_optint(L, 3, 0);
	wxString wname(winname, co);
	unordered_map<wxString, wxWindow*> um = *f->m_scriptwin->GetUserWindows();
	class GaugeWindow *frame = (GaugeWindow*)um[wname];
	//class GaugeWindow *frame = (GaugeWindow*)GaugeWindow::FindWindowByName(winname);
	if (frame == NULL)
	{
		lua_pushnil(L);
		return 1;
	}
	
	wxString g(gauge, co);
	int idx = frame->GetGaugeIndexByName(g);
	if (idx == -1)
	{
		lua_pushnil(L);
		return 1;
	}
	
	frame->GetGauges()->at(idx).SetTextPos(pos);
	frame->Refresh();
	lua_pushboolean(L, TRUE);
	return 1;
}

int luafunc_setshowvalue(lua_State *L)
{
	const char* winname;
	const char* gauge;
	bool pos;
	MudMainFrame *f = wxGetApp().GetFrame();
	wxCSConv co(f->GetGlobalOptions()->GetCurEncoding());
	winname = luaL_checkstring(L, 1);
	gauge = luaL_checkstring(L, 2);
	pos = (lua_toboolean(L, 3) != 0);
	wxString wname(winname, co);
	unordered_map<wxString, wxWindow*> um = *f->m_scriptwin->GetUserWindows();
	class GaugeWindow *frame = (GaugeWindow*)um[wname];
	//class GaugeWindow *frame = (GaugeWindow*)GaugeWindow::FindWindowByName(winname);
	if (frame == NULL)
	{
		lua_pushnil(L);
		return 1;
	}
	
	wxString g(gauge, co);
	int idx = frame->GetGaugeIndexByName(g);
	if (idx == -1)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetGauges()->at(idx).SetShowValue(pos);
	frame->Refresh();
	lua_pushboolean(L, TRUE);
	return 1;
}

//buttons
int luafunc_newbtn(lua_State *L)
{
amcButton b;
b_it it;
wxAuiToolBar *tb;
const char *cc;
int index=1;
struct str_btn *bb;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());

//	int x = sizeof(struct str_btn);
	if (lua_type(L,index)==LUA_TTABLE)
	{
		//lua_getfield(L, -1, c);
		lua_getfield(L, index, "name");
		cc = luaL_checkstring(L, -1);
		wxString s(cc, co);
		for (it=frame->GetButtons()->begin();it!=frame->GetButtons()->end();it++)
		{
			if(s==*it)
			{
				frame->m_scriptwin->Msg(_("Button already exists!"));
				return 0;
			}
		}
		b.SetName(s);
		b.SetText(s);
		lua_getfield(L, index, "action");
		cc = luaL_checkstring(L, -1);
		b.SetAction(wxString(cc,co));
		lua_getfield(L, index, "group");
		cc = luaL_optstring(L, -1, "default");
		b.SetGroup(wxString(cc,co));
		lua_getfield(L, index, "on");
		b.SetActive(lua_toboolean(L,-1)!=0);
		b.SetId(ID_USERBUTTON+frame->GetButtons()->size()+1);
		lua_getfield(L, index, "toolbar");
		cc = luaL_checkstring(L, -1);
		wxString t(cc, co);
		tb = (wxAuiToolBar*)MudMainFrame::FindWindowByName(t, frame);
		if (!tb)
		{
			wxString s;
			s<<"wxamcl.createtoolbar('"<<t<<"')";
			luaL_dostring(L,s.c_str());
			tb = (wxAuiToolBar*)MudMainFrame::FindWindowByName(t, frame);
			//lua_pushnil(L);
		}
		b.SetTbName(t);
		b.SetParent(tb);
		tb->AddTool(b.GetId(), b.GetName(), script_xpm);
		tb->SetToolTextOrientation(wxAUI_TBTOOL_TEXT_RIGHT);
		
	}
	else
	{
		cc = luaL_checkstring(L,index++);
		wxString t(cc, co);
		for (it=frame->GetButtons()->begin();it!=frame->GetButtons()->end();it++)
		{
			if(t==*it)
			{
				frame->m_scriptwin->Msg(_("Button already exists!"));
				return 0;
			}
		}
		b.SetName(t);
		b.SetText(t);
		cc = luaL_checkstring(L,index++);//toolbar
		wxString s(cc, co);
		tb = (wxAuiToolBar*)MudMainFrame::FindWindowByName(s, frame);
		if (!tb)
		{
			wxString ss;
			ss<<"wxamcl.createtoolbar('"<<s<<"')";
			luaL_dostring(L,ss.c_str());
			tb = (wxAuiToolBar*)MudMainFrame::FindWindowByName(s, frame);
			//lua_pushnil(L);
		}
		b.SetTbName(s);
		b.SetParent(tb);
		b.SetId(ID_USERBUTTON+frame->GetButtons()->size()+1);
		tb->AddTool(b.GetId(), b.GetName(), script_xpm);
		tb->SetToolTextOrientation(wxAUI_TBTOOL_TEXT_RIGHT);
		cc = luaL_checkstring(L,index++);
		b.SetAction(wxString(cc,co));
		//cc = luaL_checkstring(L,index++);
		b.SetGroup(wxString(luaL_optstring(L,index++, "default"),co));
		b.SetActive(lua_toboolean(L,index++)!=0);
		
	}
	frame->GetButtons()->push_back(b);
	frame->m_scriptwin->SetButtons(*frame->GetButtons());
	tb->Realize();
	//stable_sort(frame->GetHotkeys()->begin(), frame->GetHotkeys()->end(), less<class amcHotkey>());
	bb = (str_btn*)lua_newuserdata(L, sizeof(struct str_btn));
	wxStrcpy(bb->name, b.GetName().mb_str(co).data());
	wxStrcpy(bb->text, b.GetText().mb_str(co).data());
	wxStrcpy(bb->action, b.GetAction().mb_str(co).data());
	wxStrcpy(bb->group, b.GetGroup().mb_str(co).data());
	wxStrcpy(bb->tbar, b.GetTbName().mb_str(co).data());
	bb->tb = tb;
	bb->on = b.IsActive();
	luaL_getmetatable(L, "wxamcl.mtbtn");
	lua_setmetatable(L, -2);
	return 1;
}

int luafunc_delbtn(lua_State *L)
{
const char* cc;
b_it it;
int index=1;
int i=0;
str_btn* bt;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		bt = checkbtn(L);
		i = frame->GetVarIndexByLabel(wxString(bt->name,co));
	}
	else
	{
		cc = luaL_checkstring(L,index);
		wxString s(cc, co);
		i = frame->GetVarIndexByLabel(s);
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	else
	{
		it = frame->GetButtons()->begin()+i;
		wxAuiToolBar* tb = (wxAuiToolBar*)it->GetParent();
		tb->DeleteTool(it->GetId());
		frame->GetButtons()->erase(it);
		frame->m_scriptwin->SetButtons(*frame->GetButtons());
		//stable_sort(m_frame->GetTrigger()->begin(), m_frame->GetTrigger()->end(), greater<class Trigger>());
		tb->Realize();
		frame->m_mgr.Update();
	}
	return 0;
}

int luafunc_getbtn(lua_State *L)
{
const char* name;
str_btn* bt;
int idx;
	MudMainFrame *frame = (MudMainFrame*)wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,1)==LUA_TUSERDATA)
	{
		bt = checkbtn(L);
		wxString s(bt->name, co);
		idx = frame->GetButtonIndexByLabel(s);
	}
	else
	{
		name = luaL_checkstring(L, 1);
		idx = frame->GetButtonIndexByLabel(wxString(name,co));
	}
	if (idx==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	lua_settop(L,0);
	lua_newtable(L);
	lua_pushstring(L, frame->GetButtons()->at(idx).GetName().mb_str(co).data());// .char_str());
	lua_setfield(L, -2, "name");
	lua_pushstring(L, frame->GetButtons()->at(idx).GetAction().mb_str(co).data());
	lua_setfield(L, -2, "action");
	lua_pushstring(L, frame->GetButtons()->at(idx).GetGroup().mb_str(co).data());
	lua_setfield(L, -2, "group");
	lua_pushboolean(L, frame->GetButtons()->at(idx).IsActive());
	lua_setfield(L, -2, "on");
	lua_pushstring(L, frame->GetButtons()->at(idx).GetTbName().mb_str(co).data());
	lua_setfield(L, -2, "toolbar");
	lua_pushinteger(L, frame->GetButtons()->at(idx).GetId());
	lua_setfield(L, -2, "id");
	lua_pushstring(L, frame->GetButtons()->at(idx).GetText().mb_str(co).data());
	lua_setfield(L, -2, "text");
	return 1;	
}

int luafunc_setacbtn(lua_State *L)
{
const char* l;
const char* c;
str_btn* b;
int i, index=1;
	
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		//t = checkalias(L);
		b = checkbtn(L);
		c = luaL_checkstring(L, ++index);
		wxString s(c, co);
		i = frame->GetButtonIndexByLabel(wxString(b->name,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetButtons()->at(i).SetAction(s);
		frame->m_scriptwin->SetButtons(*frame->GetButtons());
		wxStrcpy(b->action, s.mb_str(co).data());
		return 0;
	}
	else
	{
		l = luaL_checkstring(L,index++);
		c = luaL_checkstring(L, index);
		i = frame->GetButtonIndexByLabel(wxString(l,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		wxString s(l, co);
		frame->GetButtons()->at(i).SetAction(s);
		frame->m_scriptwin->SetButtons(*frame->GetButtons());
	}
	return 0;
}

int luafunc_getacbtn(lua_State *L)
{
const char* name;
str_btn* bt;
int idx;
	MudMainFrame *frame = (MudMainFrame*)wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L,1)==LUA_TUSERDATA)
	{
		bt = checkbtn(L);
		wxString s(bt->name, co);
		idx = frame->GetButtonIndexByLabel(s);
	}
	else
	{
		name = luaL_checkstring(L, 1);
		idx = frame->GetButtonIndexByLabel(wxString(name,co));
	}
	if (idx==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	lua_pushstring(L, frame->GetButtons()->at(idx).GetAction().mb_str(co).data());
	return 1;
}

int luafunc_sellabelbtn(lua_State *L)
{
const char* l;
const char* c;
str_btn* b;
int i, index=1;
	
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		//t = checkalias(L);
		b = checkbtn(L);
		c = luaL_checkstring(L, ++index);
		wxString s(c, co);
		i = frame->GetButtonIndexByLabel(wxString(b->name,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		
		frame->GetButtons()->at(i).SetText(s);
		frame->m_scriptwin->SetButtons(*frame->GetButtons());
		wxStrcpy(b->text, s.mb_str(co).data());
		return 0;
	}
	else
	{
		l = luaL_checkstring(L,index++);
		c = luaL_checkstring(L, index);
		i = frame->GetButtonIndexByLabel(wxString(l,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		wxString s(c, co);
		frame->m_scriptwin->SetButtons(*frame->GetButtons());
		frame->GetButtons()->at(i).SetText(s);
		wxAuiToolBar* tb = (wxAuiToolBar*)frame->GetButtons()->at(i).GetParent();
		tb->SetToolLabel(frame->GetButtons()->at(i).GetId(), s);
		tb->Realize();
		frame->m_mgr.Update();
	}
	return 0;
}

int luafunc_setbitmap(lua_State *L)
{
const char* l;
const char* bmap;
str_btn* b;
int i, index=1;
	
	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		//t = checkalias(L);
		b = checkbtn(L);
		bmap = luaL_checkstring(L, ++index);
		i = frame->GetButtonIndexByLabel(wxString(b->name,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		wxString s(bmap, co);
		frame->GetButtons()->at(i).SetBitmap(s);
		frame->m_scriptwin->SetButtons(*frame->GetButtons());
		wxStrcpy(b->text, s.mb_str(co).data());
		return 0;
	}
	else
	{
		l = luaL_checkstring(L,index++);
		bmap = luaL_checkstring(L, index);
		i = frame->GetButtonIndexByLabel(wxString(l,co));
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		wxString s(bmap, co);
		frame->GetButtons()->at(i).SetBitmap(s);
		frame->m_scriptwin->SetButtons(*frame->GetButtons());
		wxAuiToolBar* tb = (wxAuiToolBar*)frame->GetButtons()->at(i).GetParent();
		wxBitmap bt;
		wxSetWorkingDirectory(frame->GetGlobalOptions()->GetImagesDir());
		bt.LoadFile(s, wxBITMAP_TYPE_XPM);
		tb->SetToolBitmap(frame->GetButtons()->at(i).GetId(), bt);
		tb->Realize();
		frame->m_mgr.Update();
	}
	return 0;
}

int luafunc_pressbtn(lua_State *L)
{
const char* cc;
b_it it;
int index=1;
int i=0;
str_btn* bt;

	MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	//cc = luaL_checkstring(L,1);
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		bt = checkbtn(L);
		i = frame->GetButtonIndexByLabel(wxString(bt->name,co));
	}
	else
	{
		cc = luaL_checkstring(L,index);
		i = frame->GetButtonIndexByLabel(wxString(cc,co));
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	else
	{
		wxString command= frame->GetButtons()->at(i).GetAction();
		int state = frame->m_scriptwin->GetParseState();
		frame->m_scriptwin->SetParseState(0);//HAVE_TEXT
		frame->m_input->Parse(command, false);
		frame->m_scriptwin->SetParseState(state);
	}
	return 0;
}

///sqlite3
int luafunc_newdb(lua_State *L)
{
	sqlite3 *db;
	char* error;
	const char* file;
	int rc=0;
	class MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));

	wxSetWorkingDirectory(frame->GetGlobalOptions()->GetDatabaseDir());
	file = luaL_checkstring(L, 1);
	if (!::wxFileExists(file))
	{
		frame->m_scriptwin->Msg(_("Database file does not exist!"));
		return 0;
	}
	wxString f(file);
	rc = sqlite3_open(f.ToUTF8(), &db);
	if (rc!= SQLITE_OK)
	{
		error = (char*)sqlite3_errmsg(db);
		frame->m_scriptwin->Msg(error);
		sqlite3_free(error);
		return 0;
	}
	lua_pushlightuserdata(L, db);
	return 1;
}

int luafunc_closedb(lua_State *L)
{
	sqlite3 *db;
	db = (sqlite3*)lua_touserdata(L, 1);
	if (!db)
		return 0;
	sqlite3_close(db);
	return 0;
}

int luafunc_execdb(lua_State *L)
{
	sqlite3* db;
	const char* sql;
	char *error;
	class MudMainFrame *frame = wxGetApp().GetFrame();
	db = (sqlite3*)lua_touserdata(L, 1);
	if (!db)
		return 0;
	sql = lua_tostring(L,2);
	int rc = sqlite3_exec(db, sql, NULL, NULL, &error);
	if (rc!=SQLITE_OK)
		{
		frame->m_scriptwin->Msg(error);
		sqlite3_free(error);
		return 0;
	}
	return 0;
}

int luafunc_insertdb(lua_State *L)
{
	sqlite3* db;
	const char* table;
	const char* column;
	const char* value;
	char *error;
	class MudMainFrame *frame = wxGetApp().GetFrame();
	int num = lua_gettop(L);
	db = (sqlite3*)lua_touserdata(L, 1);
	if (!db)
		return 0;
	table = lua_tostring(L,2);
	column = lua_tostring(L,3);
	value = lua_tostring(L,4);
	wxString s;
	if (num==4)
		s<<"insert into "<<table<<" "<<"("<<column<<") values (\""<<value<<"\")";
	else if (num>4)
	{
		s<<"insert into "<<table<<" "<<"("<<column<<") values (\""<<value<<"\",";
		for (int i=5;i<=num;i++)
		{
			value=lua_tostring(L,i);
			s<<"\""<<value<<"\"";
			if (i<num)
				s<<",";
		}
		s<<")";
	}
	int rc = sqlite3_exec(db, s.mb_str(), NULL, NULL, &error);
	if (rc!=SQLITE_OK)// && error)
		{
		frame->m_scriptwin->Msg(error);
		sqlite3_free(error);
		return 0;
	}
	return 0;
}

int luafunc_columnsdb(lua_State *L)
{
	sqlite3* db;
	sqlite3_stmt* stmt;
//	class MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	db = (sqlite3*)lua_touserdata(L, 1);
	if (!db)
		return 0;
	const char* table;
	table = lua_tostring(L,2);
	wxString s = "SELECT * from ";
	wxString ss(table);
	s = s+ss;
	
	int rc = sqlite3_prepare_v2(db, s.mb_str(), (int)(ss.length()+s.length()), &stmt, NULL);
	if (rc!=SQLITE_OK)
		{
		lua_pushnil(L);
		return 1;
	}
	else
	{
		int c = sqlite3_column_count(stmt);
		lua_settop(L,0);
		lua_newtable(L);
		for (int i=0;i<c;i++)
		{
			lua_pushstring(L, sqlite3_column_name(stmt, i));
			lua_rawseti(L, -2, i+1);
		}
		lua_pushinteger(L, c);
		sqlite3_finalize(stmt);
		return 2;
	}
	return 0;
}

int luafunc_resultdb(lua_State *L)
{
	sqlite3* db;
	
	class MudMainFrame *frame = wxGetApp().GetFrame();
	db = (sqlite3*)lua_touserdata(L, 1);
	if (!db)
		return 0;
	const char* sql;
	char* error;
	int rows, columns;
	char** result;
	sql = lua_tostring(L,2);
	wxString s(sql);
	int rc = sqlite3_get_table(db, s.mb_str(), &result, &rows, &columns, &error);
	if (rc!=SQLITE_OK )//&& error)
		{
		lua_pushnil(L);
		frame->m_scriptwin->Msg(error);
		sqlite3_free(error);
		return 1;
	}
	else
	{
		lua_settop(L,0);
		lua_newtable(L);
		int i, x;
		for (i=0+columns, x=1;i<columns+rows*columns;i++,x++)
		{
			lua_pushstring(L, result[i]);
			lua_rawseti(L, -2, x);
		}
		lua_newtable(L);
		for (i=0, x=1;i<columns;i++)
		{
			lua_pushstring(L, result[i]);
			lua_rawseti(L, -2, i+1);
		}
		lua_pushinteger(L, rows);
		sqlite3_free_table(result);
		if (!columns)
		{
			lua_pushnil(L);
			lua_pushnil(L);
			lua_pushnil(L);
			return 3;
		}
			
		return 3;
	}
	return 0;
}

int luafunc_setmxp(lua_State *L)
{
	MudWindow *mw = wxGetApp().GetFrame()->m_scriptwin;
	bool b = lua_toboolean(L,1) ? true : false;
	mw->SetMXP(b);
	//mw->SetMXP((bool)lua_toboolean(L,1));
	return 0;
}

int luafunc_parsemxp(lua_State *L)
{
	const char *msg;
	msg = luaL_checkstring(L, 1);
	MudWindow *mw = wxGetApp().GetFrame()->m_scriptwin;
	bool mx = mw->IsMXPActive();
	mw->SetMXP(true);
	mw->ParseBufferMXP(wxString(msg).char_str());
	mw->SetMXP(mx);
	mw->Refresh();
	mw->Update();
	return 0;
}

int luafunc_parsemxpwin(lua_State *L)
{
	const char *msg;
	const char *win;
	win = luaL_checkstring(L, 1);
	msg = luaL_checkstring(L, 2);
	class MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	wxString wname(win, co);
	unordered_map<wxString, wxWindow*> um = *frame->m_scriptwin->GetUserWindows();
	MudWindow *mw = (MudWindow*)um[wname];
	//MudWindow *mw = (MudWindow*)MudWindow::FindWindowByName(win);
	
	if (!mw)
		return 0;
	bool mx = mw->IsMXPActive();
	mw->SetMXP(true);
	mw->ParseBufferMXP(wxString(msg,co).char_str());
	mw->SetMXP(mx);
	mw->Refresh();
	mw->Update();
	return 0;
}

int luafunc_linkmxp(lua_State *L)
{
const char *link;
const char *hint;
const char *text;
wxString l;
	class MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	text = luaL_checkstring(L,1);
	link = luaL_checkstring(L,2);
	hint = luaL_optstring(L,3,text);
	l<<"<send hint=\""<<wxString(hint,co)<<"\" href=\""<<wxString(link,co)<<"\">"<<wxString(text,co)<<"</send>";
	MudWindow *mw = frame->m_scriptwin;
	if (!mw)
		return 0;
	mw->ParseBufferMXP(l.char_str());
	mw->Refresh();
	mw->Update();
	return 0;
}

int luafunc_setmsp(lua_State *L)
{
	MudWindow *mw = wxGetApp().GetFrame()->m_scriptwin;
	bool b = lua_toboolean(L,1) ? true : false;
	mw->SetMSP(b);
	//mw->SetMXP((bool)lua_toboolean(L,1));
	return 0;
}

int luafunc_sendgmcp(lua_State *L)
{
	char mes[1000];
	char gmcp[] = {"\xff\xfa\xc9"};
	char end[] = {"\xff\xf0\0"};
	const char *msg;
	msg = luaL_checkstring(L,1);
	class MudMainFrame *frame = wxGetApp().GetFrame();
	if (frame==NULL)
		return 0;
	wxString command(msg);
	wxStrcat(mes, gmcp);
	wxStrcat(mes, msg);
	wxStrcat(mes, end);
	if (!frame->m_scriptwin->GetSock())
		return 0;
	if (frame->m_scriptwin->GetSock()->IsConnected())
		frame->m_scriptwin->GetSock()->Write(mes, wxStrlen(mes));
	else if (frame->IsVerbose())
	{
		frame->m_scriptwin->Msg(_("Client is not connected!"), 3);
	}
	return 0;
}

int luafunc_sha256(lua_State *L)
{
	unsigned char digest[32];
	const char * text = luaL_checkstring(L, 1);
	class MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv co(frame->GetGlobalOptions()->GetCurEncoding());
	wxString t(text, co);
	sha256_context ctx;
	sha256_starts(&ctx);
	sha256_update(&ctx, (unsigned char*)t.mb_str().data(), t.length());
	sha256_finish(&ctx, digest);
	wxString hex;
	for (int i = 0; i < 32; i++)
	{
		wxString hx = wxString::Format("%02lx", digest[i]);
		hex.Append(hx);
	}
	
	wxString d(digest);
	//lua_pushstring(L, (const char*)digest);
	lua_pushstring(L, d.mb_str().data());
	lua_pushstring(L, hex.mb_str().data());
	return 2;
}

//#endif
