#include "main.h"
#include "script.xpm"
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
		return wxString::FromUTF8Unchecked(string);
		//return s;
		//wxString s(string, wxCSConv(wxGetApp().GetFrame()->GetGlobalOptions()->GetCurEncoding()), wxStrlen(string));
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
	if (lua_isstring(m_L, idx))
	{
		const char *string = lua_tostring(m_L, idx);
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
	int state = frame->m_child->GetParseState();
	frame->m_child->SetParseState(0);//HAVE_TEXT
	frame->m_input->Parse(command, b);
	frame->m_child->SetParseState(state);
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
	command.append((char)LF);
	frame->m_child->Write(command);
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
	
	class MudWindow *frame = wxGetApp().GetChild();
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
	wxString ba(text, wxCSConv(parent->GetGlobalOptions()->GetCurEncoding()));
	if (ba.IsEmpty())
		ba<<text;
	//replace vars
	
	//parent->m_input->ParseVars(&ba);
	ale.SetText(ba);
	AnsiLine line;
	if (!frame->GetLines()->back().IsFull())
	{
		frame->GetLines()->pop_back();
		frame->m_curline--;
	}
	line.m_vstyle.push_back(ale);
	line.SetFull(true);
	line.SetLineText(text);
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
//! color = amc.color(text, foreground, background)
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
	class MudWindow *frame = wxGetApp().GetChild();//(MudWindow*)MudWindow::FindWindowByName("amcoutput");
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
	
	ale.SetText(text);
	frame->GetLines()->back().m_vstyle.push_back(ale);
	lua_pushstring(L,"");
	wxGetApp().GetChild()->Refresh();
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
	
	ale.SetText(text);
	mw->GetLines()->back().m_vstyle.push_back(ale);
	lua_pushstring(L,"");
	return 1;
}

//! amc.colorall(foreground, background)
/*!
	colors the whole (visible) output buffer to foreground background
	amc.colorall(black,black)
	\param lua_State *L: a valid lua_State
*/
int luafunc_colorall(lua_State*L)
{
	const char* fcol;
	const char* bcol;
	fcol=luaL_optstring(L, 1, "white");
	bcol=luaL_optstring(L, 2, "black");
	class MudWindow *frame = wxGetApp().GetChild();
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

//! amc.colorline(foreground, background)
/*!
	colors the line to foreground background
	amc.colorline("black", "black", amc.getlinenumber())
	\param lua_State *L: a valid lua_State
*/
int luafunc_colorline(lua_State*L)
{
	const char* fcol;
	const char* bcol;
	long nr;
	fcol=luaL_optstring(L, 1, "white");
	bcol=luaL_optstring(L, 2, "black");
	class MudWindow *frame = wxGetApp().GetChild();//
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

//! amc.colorword(word, foreground, background)
/*!
	colors all occurences of word in a line to foreground background
	
	amc.colorword("Tom", "yellow", "blue")
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
	class MudWindow *frame = wxGetApp().GetChild();//(MudWindow*)MudWindow::FindWindowByName("amcoutput");
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
	class MudWindow *frame = wxGetApp().GetChild();
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
	class MudWindow *frame = (MudWindow*)MudWindow::FindWindowByName(wxT("amcoutput"));
	if (frame==NULL)
		return 0;
	lua_pushnumber(L, frame->GetLines()->at(frame->GetStartLine()-1).GetLinenumber());
	return 1;
}

int luafunc_scroll(lua_State *L)
{
	class MudWindow *frame = (MudWindow*)MudWindow::FindWindowByName(wxT("amcoutput"));
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
	const wxString* name = new wxString(winname);
	class MudWindow *frame = (MudWindow*)MudWindow::FindWindowByName(*name);
	//text = wxlua_getwxStringtype(L,1);
	if (frame==NULL)
		return 0;
	//frame->Msg(wxString(text));
	delete name;
	class MudMainFrame *parent = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	AnsiLineElement ale;
	wxColour c;
	map<wxString, wxColour> m = wxGetApp().GetChild()->GetMXPParser()->GetMXPColorMap();
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
	ale.SetText(text);
	AnsiLine line;
	line.m_vstyle.push_back(ale);
	line.SetFull(true);
	line.SetLineText(text);
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
	
	/*wxCriticalSectionLocker e(parent->m_scriptcs);
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
	map<wxString, wxString> m;
	m = frame->GetColCodes();
	map<wxString, int> b;
	b = frame->GetBCol();
	wxString ss = m[fcol];
	wxString t(text);
	//replace vars
	
	parent->m_input->ParseVars(&t);
	wxString msg = wxString::Format("\x1b[%s%02dm%s\x1b[0;0m", ss.c_str(), b[bcol], t.c_str());
	lua_pushstring(L, msg.c_str());
	msg.append("\n");
	//frame->ParseBuffer(msg.char_str());
	frame->ParseNBuffer(msg.char_str());*/
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

int luafunc_drawcircle(lua_State*L)
{
	const char* winname;
	const char* fcol;
	const char* bcol;
	int x,y,rad;
	bool full = false;
	winname = luaL_checkstring(L, 1);
	x = luaL_optint(L, 2, 100);
	y = luaL_optint(L, 3, 100);
	rad = luaL_optint(L, 4, 100);
	full = lua_toboolean(L,5)!=0;
	fcol = luaL_optstring(L, 6, "silver");
	bcol = luaL_optstring(L, 7, "black");
	const wxString* name = new wxString(winname);
	class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	delete name;
	class MudMainFrame *parent = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	wxColour c, c1;
	map<wxString, wxColour> m = wxGetApp().GetChild()->GetMXPParser()->GetMXPColorMap();
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
	bool full = false;
	winname = luaL_checkstring(L, 1);
	x = luaL_optint(L, 2, 100);
	y = luaL_optint(L, 3, 100);
	cx = luaL_optint(L, 4, 100);
	cy = luaL_optint(L, 5, 100);
	full = lua_toboolean(L,6)!=0;
	fcol = luaL_optstring(L, 7, "silver");
	bcol = luaL_optstring(L, 8, "black");
	const wxString* name = new wxString(winname);
	class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	delete name;
	class MudMainFrame *parent = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	wxColour c, c1;
	map<wxString, wxColour> m = wxGetApp().GetChild()->GetMXPParser()->GetMXPColorMap();
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
	x = luaL_optint(L, 2, 100);
	y = luaL_optint(L, 3, 100);
	cx = luaL_optint(L, 4, 100);
	cy = luaL_optint(L, 5, 100);
	fcol = luaL_optstring(L, 6, "silver");
	const wxString* name = new wxString(winname);
	class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	delete name;
	class MudMainFrame *parent = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	wxColour c, c1;
	map<wxString, wxColour> m = wxGetApp().GetChild()->GetMXPParser()->GetMXPColorMap();
	
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
	x = luaL_optint(L, 3, 1);
	y = luaL_optint(L, 4, 1);
	fcol = luaL_optstring(L, 5, "silver");
	bcol = luaL_optstring(L, 6, "black");
	bb = luaL_optint(L,7,0);
	const wxString* name = new wxString(winname);
	class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	delete name;
	class MudMainFrame *parent = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	wxColour f, b;
	map<wxString, wxColour> m = wxGetApp().GetChild()->GetMXPParser()->GetMXPColorMap();
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
	frame->GetamcWinDC()->DrawText(text, x, y);
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
	const wxString* name = new wxString(win);
	class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	delete name;
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
	const wxString* name = new wxString(winname);
	class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	delete name;
	bmap = luaL_checkstring(L, 2);
	int mode = luaL_optint(L, 3, 0);
	int x = luaL_optint(L,4,0);
	int y = luaL_optint(L,5, 0);
	int cx = luaL_optint(L,6,0);
	int cy = luaL_optint(L,7,0);
	
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
	const wxString* name = new wxString(winname);
	class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	delete name;
	frame->GetamcWinDC()->Clear();
	
	return 0;
}

int luafunc_refresh(lua_State *L)
{
	const char* winname;
	winname = luaL_checkstring(L, 1);
	const wxString* name = new wxString(winname);
	class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	delete name;
	frame->Refresh();
	frame->Update();
	return 0;
}

int luafunc_amcwinsize(lua_State *L)
{
	const char* winname;
	winname = luaL_checkstring(L, 1);
	const wxString* name = new wxString(winname);
	class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	delete name;
	int width, height;
	frame->GetClientSize(&width, &height);
	lua_pushnumber(L, width);
	lua_pushnumber(L, height);
	return 2;
}

int luafunc_seteventfile(lua_State *L)
{
	const char* s;
	s = luaL_checkstring(L, 1);
	const wxString* name = new wxString(s);
	class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	delete name;
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
	const wxString* name = new wxString(s);
	class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	delete name;
	s = luaL_checkstring(L,2);
	frame->SetLeftHandler(wxString(s));
	//lua_setglobal(L, s);
	return 1;
}

int luafunc_registerrighthandler(lua_State *L)
{
	const char* s;
	s = luaL_checkstring(L, 1);
	const wxString* name = new wxString(s);
	class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	delete name;
	s = luaL_checkstring(L,2);
	frame->SetRightHandler(wxString(s));
	//lua_setglobal(L, s);
	return 1;
}

int luafunc_registerwheelhandler(lua_State *L)
{
	const char* s;
	s = luaL_checkstring(L, 1);
	const wxString* name = new wxString(s);
	class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	delete name;
	s = luaL_checkstring(L,2);
	frame->SetWheelHandler(wxString(s));
	//lua_setglobal(L, s);
	return 1;
}

int luafunc_registermovehandler(lua_State *L)
{
	const char* s;
	s = luaL_checkstring(L, 1);
	const wxString* name = new wxString(s);
	class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	delete name;
	s = luaL_checkstring(L,2);
	frame->SetMoveHandler(wxString(s));
	//lua_setglobal(L, s);
	return 1;
}

int luafunc_mouseevents(lua_State *L)
{
	const char* s;
	s = luaL_checkstring(L, 1);
	const wxString* name = new wxString(s);
	class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	delete name;
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
	const wxString* name = new wxString(s);
	class amcWindow *frame = (amcWindow*)amcWindow::FindWindowByName(*name);
	if (frame==NULL)
		return 0;
	delete name;
	s = luaL_checkstring(L,2);
	//frame->GetToolTip()->SetMaxWidth(-1);
	frame->SetTip(wxString(s));
	return 0;
}

int luafunc_getline(lua_State *L)
{
	wxUint32 nr = luaL_checknumber(L, 1);
	AnsiLine line = wxGetApp().GetChild()->GetLines()->at(nr);
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
		lua_pushnumber(L, it->GetLen());
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
	size_t i;
	winname = luaL_checkstring(L,1);
	nb = (wxAuiNotebook*)wxWindow::FindWindowByName(winname, frame);
	if (!nb)
	{
		nb = new wxAuiNotebook(frame);
		nb->SetLabel(winname);
		nb->SetName(winname);
		frame->GetNbs()->push_back(winname);
		vector<wxString> s;
		frame->GetNbPanes()->push_back(s);
		frame->m_mgr.AddPane(nb, wxAuiPaneInfo().Name(winname).Caption(winname).CaptionVisible(true).Floatable(true).FloatingSize(400,200).BestSize(400,200).Dockable(true).Dock().Top().Layer(1).Show());
	}
	pagename = luaL_checkstring(L, 2);
	MudWindow *mw = (MudWindow*)MudWindow::FindWindowByName(pagename);
	if (mw)
		return 0;
	if (!frame->GetNbs()->empty())
	{
		for (i=0;i<frame->GetNbs()->size();i++)
		{
			if (winname==frame->GetNbs()->at(i))
				break;
		}
	}
	frame->GetNbPanes()->at(i).push_back(pagename);
	nb->AddPage(new MudWindow(frame, pagename, 9), pagename);
	frame->m_mgr.Update();
	lua_pushlightuserdata(L, (void*)nb->FindWindowByName(winname));
	return 1;
}

int luafunc_addpagenb(lua_State*L)
{
	const char* winname;
	const char* pagename;
	int i;
	class MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));

	winname = luaL_checkstring(L,1);
	pagename = luaL_checkstring(L,2);

	wxAuiNotebook *nb = (wxAuiNotebook*)wxAuiNotebook::FindWindowByName(winname, frame);
	if (nb==NULL)
		return 0;
	if (!frame->GetNbs()->empty())
	{
		for (i=0;i<(int)frame->GetNbs()->size();i++)
		{
			if (winname==frame->GetNbs()->at(i))
				break;
		}
	}
	frame->GetNbPanes()->at(i).push_back(pagename);
	nb->AddPage(new MudWindow(frame, pagename, 9), pagename);
	/*nb->AddPage(new MudWindow(frame, wxT("amc2")), wxT("Second"));
	nb->AddPage(new MudWindow(frame, wxT("amc3")), wxT("I'm here"));*/
	//frame->m_mgr.AddPane(nb, wxAuiPaneInfo().Name(winname).Caption(winname).CaptionVisible(true).Floatable(true).FloatingSize(400,200).BestSize(400,200).Dockable(true).Dock().Top().Layer(1));
	frame->m_mgr.Update();
	return 0;
}

//! amc.createwindow(windowname)
/*!
	creates a window, implements the lua command. Will do nothing if a window with this name already exists */
/*!	syntax in lua: amc.createwindow("Name") or createwindow("name")
	\param lua_State *L: a valid lua_State
	\returns nothing
	\sa luafunc_showwindow, luafunc_hidewindow, luafunc_createnb
*/
int luafunc_createwindow(lua_State*L)
{
	const char* winname;
	MudWindow *mw;
	wxColour c;
	//if (!wxThread::IsMain())
	//	wxMutexGuiEnter();
	class MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	wxCriticalSectionLocker e(frame->m_scriptcs);
	winname = luaL_checkstring(L,1);
	const char* col = luaL_optstring(L, 2, "black"); 
	mw = (MudWindow*)MudWindow::FindWindowByName(winname, frame);
	if (mw)
		return 0;
	mw = new MudWindow(frame, winname, 9);
	mw->SetName(winname);
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
	frame->GetPanes()->push_back(winname);//save all the windows we have
	//if (!wxThread::IsMain())
	//	wxMutexGuiLeave();
	frame->m_mgr.AddPane(mw, wxAuiPaneInfo().Name(winname).Caption(winname).CaptionVisible(true).Floatable(true).FloatingSize(400,200).BestSize(400,200).Dockable(true).Dock().Top().Layer(1).Hide().MinimizeButton());
	//frame->m_mgr.AddPane((wxWindow*)mw, wxAuiPaneInfo().Name(wxT("Asa")).Top().Caption(wxT("Asa")));
	
	frame->m_mgr.GetPane(mw).Show();
	frame->m_mgr.Update();	
	frame->Refresh();
	frame->Update();
	frame->m_child->Refresh();
	frame->m_child->Update();
	
	return 0;
}

//! amc.hidewindow(windowname)

/*!	hides a window - implements the lua script command. */
/*! The syntax in lua is: amc.hidewindow("Name") or hidewindow("name")
* \param lua_State *L: a valid lua_State
* \returns nothing
* \sa luafunc_showwindow, luafunc_createwindow
*/

int luafunc_hidewindow(lua_State*L)
{
	char* winname;
	MudWindow *mw;
	//if (!wxThread::IsMain())
	//	wxMutexGuiEnter();
	class MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	//wxCriticalSectionLocker e(frame->m_scriptcs);
	winname = (char*)luaL_checkstring(L,1);
	mw = (MudWindow*)MudWindow::FindWindowByName(winname, frame);
	if (!mw)
		return 0;
	
	frame->m_mgr.GetPane(wxString(winname)).Hide();
	frame->m_mgr.Update();
	//if (!wxThread::IsMain())
	//	wxMutexGuiLeave();
	return 0;
}

//! amc.showwindow(windowname)

//!	shows a (hidden) window in lua
//!	amc.showwindow("Name")
//!	\param lua_State *L: a valid lua_State

int luafunc_showwindow(lua_State*L)
{
	const char* winname;
	MudWindow *mw;
	//if (!wxThread::IsMain())
	//	wxMutexGuiEnter();
	class MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	//wxCriticalSectionLocker e(frame->m_scriptcs);
	winname = (char*)luaL_checkstring(L,1);
	mw = (MudWindow*)MudWindow::FindWindowByName(winname, frame);
	if (!mw)
		return 0;
	
	frame->m_mgr.GetPane(wxString(winname)).Show();
	frame->m_mgr.Update();
	frame->Refresh();
	frame->Update();
	
	//if (!wxThread::IsMain())
	//	wxMutexGuiLeave();
	return 0;
}

//! amc.clearwindow(windowname)

//!	clears window in lua
//!	amc.clearwindow("Name")
//!	\param lua_State *L: a valid lua_State

int luafunc_clearwindow(lua_State *L)
{
	const char* winname;
	MudWindow *mw;
	class MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");

	winname = luaL_checkstring(L,1);
	mw = (MudWindow*)MudWindow::FindWindowByName(winname, frame);
	if (!mw)
		return 0;
	mw->ClearLines();
	return 0;
}

int luafunc_destroywindow(lua_State *L)
{
	const char* name = luaL_checkstring(L,1);
	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	MudWindow* mw = (MudWindow*)MudWindow::FindWindowByName(name, frame);
	if (!mw)
	{
		lua_pushnil(L);
		return 1;
	}
	s_it sit;
	wxString s(name);
	//if (!m_panes.empty())
	if (!frame->GetPanes()->empty())
	{
		for (sit=frame->GetPanes()->begin();sit!=frame->GetPanes()->end();sit++)
		{
			if (!s.compare(sit->c_str()))
			{
				frame->GetPanes()->erase(sit);
				break;
			}
		}
	}
	frame->m_mgr.GetPane(s).Hide();
	frame->m_mgr.DetachPane(mw);
	frame->m_mgr.Update();
	mw->Destroy();
	return 0;
}

int luafunc_destroyamcwindow(lua_State *L)
{
	const char* name = luaL_checkstring(L,1);
	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	amcWindow* mw = (amcWindow*)amcWindow::FindWindowByName(name, frame);
	if (!mw)
	{
		lua_pushnil(L);
		return 1;
	}
	s_it sit;
	wxString s(name);
	//if (!m_panes.empty())
	if (!frame->GetAmcWindows()->empty())
	{
		for (sit=frame->GetAmcWindows()->begin();sit!=frame->GetAmcWindows()->end();sit++)
		{
			if (!s.compare(sit->c_str()))
			{
				frame->GetAmcWindows()->erase(sit);
				break;
			}
		}
	}
	frame->m_mgr.GetPane(s).Hide();
	frame->m_mgr.DetachPane(mw);
	frame->m_mgr.Update();
	mw->Destroy();
	return 0;
}

int luafunc_destroynb(lua_State *L)
{
	const char* name = luaL_checkstring(L,1);
	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	wxAuiNotebook* mw = (wxAuiNotebook*)wxAuiNotebook::FindWindowByName(name, frame);
	if (!mw)
	{
		lua_pushnil(L);
		return 1;
	}
	s_it sit;
	wxString s(name);
	size_t i=0;
	//if (!m_panes.empty())
	if (!frame->GetNbs()->empty())
	{
		for (sit=frame->GetNbs()->begin();sit!=frame->GetNbs()->end();sit++,i++)
		{
			if (!s.compare(sit->c_str()))
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
	frame->m_mgr.GetPane(s).Hide();
	frame->m_mgr.DetachPane(mw);
	frame->m_mgr.Update();
	mw->Destroy();
	return 0;
}

int luafunc_setbackground(lua_State*L)
{
MudWindow* mw;
wxWindow *win;
wxColour c;
	const char* winname = luaL_checkstring(L,1);
	const char* col = luaL_optstring(L, 2, "black"); 
	class MudMainFrame *frame = wxGetApp().GetFrame();
	win = MudWindow::FindWindowByName(winname, frame);
	
	if (!win)
		return 0;
	//if (sizeof(*mw)==sizeof(class MudWindow))
	if (win->IsKindOf(CLASSINFO(MudWindow)))
	{
	mw = (MudWindow*)win;
	wxString s(col);
	if (s.at(0)=='#')
	{
		c.Set(s);
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
	}
	else if (win->IsKindOf(CLASSINFO(GaugeWindow)))
	{
		GaugeWindow* gw = (GaugeWindow*)win;
		c.Set(col);
		gw->SetBackgroundCol(c);
	}
	return 0;
}

int luafunc_createamcwin(lua_State*L)
{
	const char* winname;
	amcWindow *mw;
	wxColour c;
	//if (!wxThread::IsMain())
	//	wxMutexGuiEnter();
	class MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	winname = luaL_checkstring(L,1);
	const char* col = luaL_optstring(L, 2, "black"); 
	mw = (amcWindow*)amcWindow::FindWindowByName(winname, frame);
	if (mw)
		return 0;
	mw = new amcWindow(frame, winname);
	mw->SetName(winname);
	wxString s(col);
	/*if (s.at(0)=='#')
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
	}*/
	frame->GetAmcWindows()->push_back(winname);//save all the windows we have
	//if (!wxThread::IsMain())
	//	wxMutexGuiLeave();
	frame->m_mgr.AddPane(mw, wxAuiPaneInfo().Name(winname).Caption(winname).CaptionVisible(true).Floatable(true).FloatingSize(400,200).BestSize(400,200).Dockable(true).Dock().Top().Layer(1).Hide());
	frame->m_mgr.GetPane(mw).Show();
	frame->m_mgr.Update();	
	frame->Refresh();
	frame->Update();
	frame->m_child->Refresh();
	frame->m_child->Update();
	
	return 0;
}

//! amc.createtoolbar(windowname)
/*!
	creates a toolbar for user buttons */
/*!	syntax in lua: amc.createtoolbar("Name") or createtoolbar("name")
	\param lua_State *L: a valid lua_State
	\returns nothing
	\sa luafunc_showwindow, luafunc_hidewindow, luafunc_createnb
*/
int luafunc_createtoolbar(lua_State*L)
{
	const char* winname;
	wxAuiToolBar *tb;
	class MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	wxCriticalSectionLocker e(frame->m_scriptcs);
	winname = luaL_checkstring(L,1);
	tb = (wxAuiToolBar*)MudMainFrame::FindWindowByName(winname, frame);
	if (tb)
		return 0;
	tb = new wxAuiToolBar(frame, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_TEXT | wxAUI_TB_GRIPPER);
	tb->SetName(winname);
	tb->SetToolTextOrientation(wxAUI_TBTOOL_TEXT_RIGHT);
	
	//frame->GetPanes()->push_back(winname);//save all the windows we have
	frame->m_mgr.AddPane(tb, wxAuiPaneInfo().Name(winname).Caption(winname).ToolbarPane().CaptionVisible(false).Floatable(true).BestSize(600, 24).LeftDockable(true).Dockable(true).Dock().Top());
	//wxToolBar *tbx = new wxToolBar(frame, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	//frame->m_mgr.AddPane(tbx, wxAuiPaneInfo().Name(winname).Caption(winname).Gripper().CaptionVisible(false).Floatable(true).BestSize(600, 24).LeftDockable(true).Dockable(true).Dock().Top());
	//frame->m_mgr.GetPane(tb).Show();
	frame->m_mgr.GetPane(tb).Show();
	frame->m_mgr.Update();	
	frame->Refresh();
	frame->Update();
	frame->m_child->Refresh();
	frame->m_child->Update();
	return 0;
}

int luafunc_addbutton(lua_State *L)
{
const char* winname;
wxAuiToolBar *tb;
amcButton b;
	class MudMainFrame *frame = wxGetApp().GetFrame();
	//wxCriticalSectionLocker e(frame->m_scriptcs);
	winname = luaL_checkstring(L,1);
	tb = (wxAuiToolBar*)MudMainFrame::FindWindowByName(winname, frame);
	
	if (!tb)
		return 0;
	int id = luaL_checkinteger(L, 4);
	if (id<0 || id>1000)
	{
		frame->m_child->Msg(_("Id for user button needs to be >0 and <1000"), 3);
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
	b.SetTbName(winname);
	frame->GetButtons()->push_back(b);
	tb->Realize();
	frame->m_mgr.Update();
	return 0;
}

int luafunc_loadprofile(lua_State *L)
{
	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	char* l = (char*)luaL_checkstring(L,1);//filename
	if (frame->LoadProfile(wxFileName(l)))
	{
		lua_pushnumber(L, frame->GetTrigger()->size());
		lua_pushnumber(L, frame->GetAlias()->size());
		lua_pushnumber(L, frame->GetHotkeys()->size());
		lua_pushnumber(L, frame->GetVars()->size());
		lua_pushnumber(L, frame->GetLists()->size());
		return 5;
	}
	else return 0;
}

int luafunc_convertprofile(lua_State *L)
{
	MudMainFrame *frame = wxGetApp().GetFrame();
	const char *file = luaL_checkstring(L, 1);
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
		#ifdef __WXMSW__
			wxFileName::SplitPath(s, NULL, &evf, &evx, wxPATH_UNIX);
		#endif
		#ifdef __WXGTK__
			wxFileName::SplitPath(s, NULL, &evf, &evx, wxPATH_WIN);
		#endif
		s.clear();
		s<<frame->GetGlobalOptions()->GetPackageDir()<<evf<<"."<<evx;
		frame->GetPackages()->at(i).assign(s);
	}
	
	#ifdef __WXGTK__
	wxFileName::SplitPath(frame->GetGlobalOptions()->GetEventFile(), NULL, &evf, &evx, wxPATH_WIN);
	#endif
	#ifdef __WXMSW__
	wxFileName::SplitPath(frame->GetGlobalOptions()->GetEventFile(), NULL, &evf, &evx, wxPATH_UNIX);
	#endif
	wxFileName ev(frame->GetGlobalOptions()->GetScriptDir()+evf+"."+evx);
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
	int waittime = luaL_optint(L, 2, -1);
	//class amcScriptThread* th;
	
	//th->TestDestroy();
	wxString action;
	//action << frame->GetGlobalOptions()->GetCommand() << "resume (\"" << th->GetId() << "\")";
	action << frame->GetGlobalOptions()->GetCommand() << "resume (\"" << frame->GetLRefCount() << "\")";
	wxString label;
	//label << "temp" << th->GetId();
	label << "temp" << frame->GetLRefCount();
	
	Trigger t(pattern, action, label);
	t.SetShow(false);
	frame->GetTrigger()->push_back(t);
	//frame->GetLStates()->push_back(L);
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
	}
	//ti.Run();
	return lua_yield(L,0);
}

int luafunc_wait(lua_State *L)
{
	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	//wxCriticalSectionLocker e(frame->m_scriptcs);
	float i = (float)luaL_checknumber(L,1);
	//i *= 1000;
	//class amcScriptThread* th;
	wxString s;
	s << "#resume(\"" << (frame->GetLRefCount()) << "\")";
	wxString t;
	t << "resume" << (frame->GetLRefCount());
	amcTimer ti(t, s, "threads", (float)i, 2, false);
	ti.SetActive(true);
	frame->GetTimers()->push_back(ti);
	frame->GetLuaStates()->insert(make_pair(frame->GetLRefCount(), L));
	frame->SetLRefCount(frame->GetLRefCount()+1);
	int idx = frame->GetTimerIndexByLabel(t);
	frame->m_input->SetWaiting(true);
	if (idx!=-1)
		frame->GetTimers()->at(idx).Run();
	
	return lua_yield(L,0);
	/*
	if (wxThread::IsMain())
		::wxMilliSleep((unsigned long)i);
		//::wxSleep(3);
	else
		::wxMilliSleep((unsigned long)i);
		//wxThread::Sleep((unsigned long)i);
	lua_pushnumber(L, i);
	return 1;*/
}

int luafunc_gag(lua_State *L)
{
	int line = luaL_checkint(L,1);
	if (line>0)
		return 1;
	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));

	if (!frame->m_child->GetLines()->empty())
	{
		//frame->m_child->GetLines()->back().SetGagme(true);
		line_it lit = frame->m_child->GetLines()->end()-1;
		//lit = lit+line;
		//for (int i=cline;i>line+cline;i--, lit--);
		frame->m_child->GetLines()->erase(lit);
		if (frame->m_child->m_curline>=1)
			//frame->m_child->m_curline = frame->m_child->GetLines()->size()-1;
			frame->m_child->m_curline--;
		else frame->m_child->m_curline=0;
		//frame->m_child->SetScrollPage();
		frame->m_child->Refresh();
		frame->m_child->Update();
	}
	return 0;
}

/*lua_CFunction luafunc_setactionprop(lua_State*L)
{
tr_it it;
wxChar* c;
wxChar* d;
wxChar* e;

Trigger tr;
int index=1;

	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	int num = lua_gettop(L);
	if (lua_type(L,index)==LUA_TTABLE)
		index++;

	c = (wxChar*)luaL_checkstring(L,index++);
	d = (wxChar*)luaL_checkstring(L,index++);

	for (size_t i=0;i<frame->GetTrigger()->size();i++)
	{
		if (c==frame->GetTrigger()->at(i).GetLabel())
		{
			wxString s(d);
			if (s==wxT("pattern"))
			{
				e = (wxChar*)luaL_checkstring(L,index);
				frame->GetTrigger()->at(i).SetPattern(e);
			}
			else if (s==wxT("action"))
			{
				e = (wxChar*)luaL_checkstring(L,index);
				frame->GetTrigger()->at(i).SetAction(e);
			}
			else if (s==wxT("class"))
			{
				e = (wxChar*)luaL_checkstring(L,index);
				frame->GetTrigger()->at(i).SetClass(e);
			}
			else if (s==wxT("on"))
			{
				frame->GetTrigger()->at(i).SetActive(lua_toboolean(L,index)!=0);
			}
			return (lua_CFunction)0;
		}
	}

	frame->m_child->Msg(_("Action not found!"));
	lua_pushnil(L);
	return (lua_CFunction)1;
}**/


//Userdata
//! \brief open the amc Lua library
/*!
	register the amc lib in the lua namespace
	set wxamcl.mta metatable for wxAmc actions
	override so we can do: wxamcl.echo or echo only
	\param lua_State *L: a valid lua_State
*/

int luaopen_amc(lua_State *L)
{/*
	luaL_newmetatable(L, "wxamcl.mta");//action type
	luaL_register(L, NULL, amclib_m);
	luaL_newmetatable(L, "wxamcl.mtal");//alias type
	luaL_register(L, NULL, amclib_al);
	luaL_newmetatable(L, "wxamcl.mtv");//var type
	luaL_register(L, NULL, amclib_v);
	luaL_newmetatable(L, "wxamcl.mthk");//hotkey type
	luaL_register(L, NULL, amclib_h);
	luaL_newmetatable(L, "wxamcl.mtt");//timer type
	luaL_register(L, NULL, amclib_timers);
	luaL_newmetatable(L, "wamcl.mtbtn");//button type
	luaL_register(L, NULL, amclib_btn);
	luaL_newmetatable(L, "wamcl.mtll");//list type
	luaL_register(L, NULL, amclib_list);
	lua_pushvalue (L, LUA_GLOBALSINDEX);
	luaL_register(L, "wxamcl", amclib_f);
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -2);         // push metatable
	lua_rawset(L, -3);
	lua_setmetatable (L, -2);
	//lua_pushvalue (L, LUA_GLOBALSINDEX);
	
	luaL_register(L, "wxamcl.action", amclib_trigger);
	luaL_register(L, "wxamcl.alias", amclib_alias);
	luaL_register(L, "wxamcl.gmcp", amclib_gmcp);
	luaL_register(L, "wxamcl.gauge", amclib_gauge);
	luaL_register(L, "wxamcl.mxp", amclib_mxp);
	luaL_register(L, "wxamcl.hk", amclib_hk);
	luaL_register(L, "wxamcl.var", amclib_vars);
	luaL_register(L, "wxamcl.timer", amclib_timers);
	luaL_register(L, "wxamcl.list", amclib_list);
	luaL_register(L, "wxamcl.button", amclib_btn);
	luaL_register(L, "wxamcl.db", amclib_db);
	luaL_register(L, "wxamcl.draw", amclib_draw);
	return 1;*/
	return 0;
}

LUAMOD_API int luaopen2_amc(lua_State *L)
{
	
	//lua_setglobal(L, "wxamcl");
	//lua_pushliteral(L, "__index");
	//lua_pushvalue(L, -2);         // push metatable
	//lua_rawset(L, -3);
	//lua_setmetatable (L, -2);
	/*luaL_newmetatable(L, "wxamcl.mtal");//alias type
	luaL_setfuncs(L, amclib_al, 0);
	luaL_newmetatable(L, "wxamcl.mtv");//var type
	luaL_setfuncs(L, amclib_v, 0);
	luaL_newmetatable(L, "wxamcl.mthk");//hotkey type
	luaL_setfuncs(L, amclib_h, 0);
	luaL_newmetatable(L, "wxamcl.mtt");//timer type
	luaL_setfuncs(L, amclib_timers, 0);
	luaL_newmetatable(L, "wamcl.mtbtn");//button type
	luaL_setfuncs(L, amclib_btn, 0);
	luaL_newmetatable(L, "wamcl.mtll");//list type
	luaL_setfuncs(L, amclib_list, 0);
	lua_pushvalue (L, LUA_RIDX_GLOBALS);
	//luaL_setfuncs(L, amclib_f, 0);
	luaL_newlib(L, amclib_f);
	lua_pushliteral(L, "__index");*/
	
	//lua_pushvalue (L, LUA_GLOBALSINDEX);
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

//! amc.action.new(name, table{pattern="pattern", action="action", class="class", on=true|false, priority=0-100, colmatch=-1|0-18})
/*!
	Creates a new action in lua, provide a unique label and a table with the values
	creates a user type action in lua and returns this userdatum
	userdatum = amc.newaction("newaction", {pattern="A line", action="send to mud", class="default", on=true, prior=50, colmatch=-1})
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
	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	//int x= sizeof(struct str_ac);

	//called from amc.newaction
	if(lua_type(L, index) != LUA_TTABLE)
	{
		l = luaL_checkstring(L, index++);
	
		for (it=frame->GetTrigger()->begin();it!=frame->GetTrigger()->end();it++)
		{
			if(l==*it)
			{
				frame->m_child->Msg(_("Error creating action. Action labels need to be unique!"));
				return 0;
			}
		}
		tr.SetLabel(l);
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
				lua_pushnumber(L, frame->GetTrigger()->size());
				return 1;
			}
			lua_getfield(L, -1, "pattern");
			const char* cc = luaL_checkstring(L, -1);
			tr.SetPattern(cc);
			lua_getfield(L, -2, "action");
			cc = luaL_checkstring(L, -1);
			tr.SetAction(cc);
			lua_getfield(L, -3, "class");
			cc = luaL_optstring(L, -1, "default");
			tr.SetClass(cc);
			lua_getfield(L, -4, "on");
			tr.SetActive(lua_toboolean(L,-1)!=0);
			lua_getfield(L, -5, "priority");
			tr.SetPriority(luaL_optint(L,-1,50));
			lua_getfield(L, -6, "colmatch");
			tr.SetColMatch(luaL_optint(L,-1,-1));
			lua_getfield(L, -7, "lines");
			tr.SetLines(luaL_optint(L,-1,1));
		}
		else
		{
			lua_getfield(L, index, "pattern");
			const char* cc = luaL_checkstring(L, -1);
			tr.SetPattern(cc);
			lua_getfield(L, index, "action");
			cc = luaL_checkstring(L, -1);
			tr.SetAction(cc);
			lua_getfield(L, index, "class");
			cc = (char*)luaL_optstring(L, -1, "default");
			tr.SetClass(cc);
			lua_getfield(L, index, "on");
			tr.SetActive(lua_toboolean(L,-1)!=0);
			lua_getfield(L, index, "priority");
			tr.SetPriority(luaL_optint(L,-1,50));
			lua_getfield(L, index, "colmatch");
			tr.SetColMatch(luaL_optint(L,-1,-1));
			lua_getfield(L, index, "lines");
			tr.SetLines(luaL_optint(L,-1,1));
		}
	}
	else
	{
		c = luaL_checkstring(L,index++);
		tr.SetPattern(c);
		c = luaL_checkstring(L,index++);
		tr.SetAction(c);
		tr.SetClass(luaL_optstring(L,index++, "default"));
		tr.SetActive(lua_toboolean(L,index++)!=0);
		tr.SetPriority(luaL_optint(L,index++,50));
		tr.SetColMatch(luaL_optint(L,index++,-1));
		tr.SetLines(luaL_optint(L, index++, 1));
	}
	frame->GetTrigger()->push_back(tr);
	stable_sort(frame->GetTrigger()->begin(), frame->GetTrigger()->end(), greater<class Trigger>());
	t = (str_ac*)lua_newuserdata(L, sizeof(struct str_ac));
	wxStrcpy(t->label, l);
	wxStrcpy(t->pattern, tr.GetPattern().c_str());
	wxStrcpy(t->action, tr.GetAction().c_str());
	wxStrcpy(t->cla, tr.GetClass().c_str());
	t->on = tr.IsActive();
	t->prior = tr.GetPriority();
	t->colmatch = tr.GetColMatch();
	t->count = tr.GetMatchCount();
	t->lines = tr.GetLines();
	luaL_getmetatable(L, "wxamcl.mta");
	lua_setmetatable(L, -2);
	//frame->luaBuildtrigger();
	return 1;
}

int luafunc_gettruserdata(lua_State *L)
{
str_ac* t;
const char* c;
int i;

	MudMainFrame *frame = wxGetApp().GetFrame();
	c = luaL_checkstring(L,1);
	i = frame->GetTriggerIndexByLabel(c);
	if (i==-1)
	{
		frame->m_child->Msg(_("Action not found!"));
		lua_pushnil(L);
		return 1;
	}
	t = (str_ac*)lua_newuserdata(L, sizeof(struct str_ac));
	wxStrcpy(t->label, c);
	wxStrcpy(t->pattern, frame->GetTrigger()->at(i).GetPattern().c_str());
	wxStrcpy(t->action, frame->GetTrigger()->at(i).GetAction().c_str());
	wxStrcpy(t->cla, frame->GetTrigger()->at(i).GetClass().c_str());
	t->on = frame->GetTrigger()->at(i).IsActive();
	t->prior = frame->GetTrigger()->at(i).GetPriority();
	t->colmatch = frame->GetTrigger()->at(i).GetColMatch();
	t->count = frame->GetTrigger()->at(i).GetMatchCount();
	t->lines = frame->GetTrigger()->at(i).GetLines();
	luaL_getmetatable(L, "wxamcl.mta");
	lua_setmetatable(L, -2);
	//frame->luaBuildtrigger();
	return 1;
}
//! table = amc.getaction(action|userdatum)
/*!
	returns a table representing an wxAMC action in Lua
	t = amc.getaction("Map1")
	t = amc.getaction(x) provide a userdatum returned from newaction
	table has fields: label, pattern, action, class, on, priority, colmatch, matchcount
	\param lua_State *L: a valid lua_State
*/
int luafunc_getaction(lua_State*L)
{
str_ac* t;
const char* c;
int i, index=1;

	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		i = frame->GetTriggerIndexByLabel(t->label);
	}
	else
	{
		c = luaL_checkstring(L,index);
		i = frame->GetTriggerIndexByLabel(c);
	}
	if (i==-1)
	{
		frame->m_child->Msg(_("Action not found!"));
		lua_pushnil(L);
		return 1;
	}
	lua_settop(L,0);
	lua_newtable(L);
	lua_pushstring(L, frame->GetTrigger()->at(i).GetLabel().char_str());
	lua_setfield(L, -2, "label");
	lua_pushstring(L, frame->GetTrigger()->at(i).GetPattern().char_str());
	lua_setfield(L, -2, "pattern");
	lua_pushstring(L, frame->GetTrigger()->at(i).GetAction().char_str());
	lua_setfield(L, -2, "action");
	lua_pushstring(L, frame->GetTrigger()->at(i).GetClass().char_str());
	lua_setfield(L, -2, "class");
	lua_pushnumber(L, frame->GetTrigger()->at(i).GetPriority());
	lua_setfield(L, -2, "priority");
	lua_pushnumber(L, frame->GetTrigger()->at(i).GetColMatch());
	lua_setfield(L, -2, "colmatch");
	lua_pushnumber(L, frame->GetTrigger()->at(i).GetMatchCount());
	lua_setfield(L, -2, "matchcount");
	lua_pushboolean(L, frame->GetTrigger()->at(i).IsActive());
	lua_setfield(L, -2, "on");
	lua_pushnumber(L, frame->GetTrigger()->at(i).GetLines());
	lua_setfield(L, -2, "lines");
	return 1;
}

//! x = amc.delaction(action|userdatum)
/*!
	deletes an wxAMC action in Lua
	x=amc.delaction("Map1")
	x=amc.delaction(x) provide a userdatum returned from newaction
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
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		//t = (str_ac*)lua_touserdata(L, index);
		t = checkaction(L);
		i = frame->GetTriggerIndexByLabel(t->label);
	}
	else
	{
		c = (char*)luaL_checkstring(L,index);
		i = frame->GetTriggerIndexByLabel(c);
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	it = frame->GetTrigger()->begin()+i;
	frame->GetTrigger()->erase(it);
	t = NULL;
	stable_sort(frame->GetTrigger()->begin(), frame->GetTrigger()->end(), greater<class Trigger>());
	lua_pushnumber(L, frame->GetTrigger()->size());
	return 1;
}

int luafunc_enableaction(lua_State *L)
{
const char* c;
int i, index=1;
str_ac *t=NULL;

	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		t = (str_ac*)lua_touserdata(L, index++);
		i = frame->GetTriggerIndexByLabel(t->label);
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetTriggerIndexByLabel(c);
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
		lua_pushstring(L, t->label);
	}
	return 1;
}

int luafunc_getpattern(lua_State*L)
{
char* l;
str_ac* t;
int index=1;

	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		lua_pushstring(L, t->pattern);
		return 1;
	}

	else
	{
		l = (char*)luaL_checkstring(L,index);
		int i = frame->GetTriggerIndexByLabel(l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		else
			lua_pushstring(L, frame->GetTrigger()->at(i).GetPattern().char_str());
			return 1;
	}
	return 1;
}
//! amc.setpattern(action|userdatum)
/*!
	sets the pattern of an wxAMC action in Lua
	amc.setpattern("Map1", "this is the pattern")
	amc.setpattern(x) provide a userdatum returned from newaction
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

	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		c = luaL_checkstring(L, ++index);
		i = frame->GetTriggerIndexByLabel(t->label);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetTrigger()->at(i).SetPattern(c);
		wxStrcpy(t->pattern, c);
		//t->pattern = c;
		return 0;
	}
	else
	{
		l = luaL_checkstring(L,index++);
		c = luaL_checkstring(L, index);
		i = frame->GetTriggerIndexByLabel(l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetTrigger()->at(i).SetPattern(c);
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

	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		lua_pushstring(L, t->action);
		return 1;
	}

	else
	{
		l = luaL_checkstring(L,index);
		int i = frame->GetTriggerIndexByLabel(l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		else
			lua_pushstring(L, frame->GetTrigger()->at(i).GetAction().char_str());
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

	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));

	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		c = (char*)luaL_checkstring(L, ++index);
		i = frame->GetTriggerIndexByLabel(t->label);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetTrigger()->at(i).SetAction(c);
		wxStrcpy(t->action, c);
		return 0;
	}
	else
	{
		l = (char*)luaL_checkstring(L,index++);
		c = (char*)luaL_checkstring(L, index);
		i = frame->GetTriggerIndexByLabel(l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetTrigger()->at(i).SetAction(c);
	}
	return 0;
}

//! num = amc.getpriority(name|userdatum)
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
	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));

	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		lua_pushnumber(L, t->prior);
		return 1;
	}

	else
	{
		l = (char*)luaL_checkstring(L,index);
		int i = frame->GetTriggerIndexByLabel(l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		else
			lua_pushnumber(L, frame->GetTrigger()->at(i).GetPriority());
			return 1;
	}
	return 1;
}

//! amc.setpriority(name|userdatum, priority)
/*!
	sets the priority of an action, default = 50
	\param lua_State *L: a valid lua_State
*/
int luafunc_setpriority(lua_State *L)
{
str_ac *t;
int n, i, index=1;
const char *l;

	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");

	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		n = luaL_optint(L, ++index, 50);
		i = frame->GetTriggerIndexByLabel(t->label);
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
		n = luaL_optint(L, index, 50);
		i = frame->GetTriggerIndexByLabel(l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetTrigger()->at(i).SetPriority(n);
		stable_sort(frame->GetTrigger()->begin(), frame->GetTrigger()->end(), greater<class Trigger>());
	}
	return 0;
}

//! num = amc.getcolmatch(name|userdatum)
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
	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));

	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		lua_pushnumber(L, t->colmatch);
		return 1;
	}

	else
	{
		l = (char*)luaL_checkstring(L,index);
		int i = frame->GetTriggerIndexByLabel(l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		else
			lua_pushnumber(L, frame->GetTrigger()->at(i).GetColMatch());
			return 1;
	}
	return 1;
}

//! amc.setcolmatch(name|userdatum, colmatch)
/*!
	sets the foreground color to match of an action, default = -1 = none
	\param lua_State *L: a valid lua_State
*/
int luafunc_setcolmatch(lua_State *L)
{
str_ac *t;
int n, i, index=1;
const char* l;

	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");

	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		n = luaL_optint(L, ++index, -1);
		i = frame->GetTriggerIndexByLabel(t->label);
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
		n = luaL_optint(L, index, -1);
		i = frame->GetTriggerIndexByLabel(l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetTrigger()->at(i).SetColMatch(n);
	}
	return 0;
}

int luafunc_getallactions(lua_State*L)
{
size_t i;

	MudMainFrame *frame = wxGetApp().GetFrame();//

	lua_settop(L,0);
	lua_newtable(L);
	for (i=0;i<frame->GetTrigger()->size();i++)
	{
		lua_pushstring(L, frame->GetTrigger()->at(i).GetLabel().char_str());
		lua_rawseti(L, -2, i+1);
	}
	lua_pushnumber(L, i);
	return 2;
}

int luafunc_enabletriggers(lua_State *L)
{
	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	frame->SetTriggersOn(true);
	lua_pushnumber(L, frame->GetTrigger()->size());
	return 1;
}

int luafunc_disabletriggers(lua_State *L)
{
	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	frame->SetTriggersOn(false);
	lua_pushnumber(L, frame->GetTrigger()->size());
	return 1;
}


int luafunc_enabletrgroup(lua_State *L)
{
tr_it iter;
	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	const char* trgroup;
	trgroup = luaL_checkstring(L, 1);
	bool active = lua_toboolean(L,2) != 0;
	for (iter = frame->GetTrigger()->begin(); iter!= frame->GetTrigger()->end(); iter++)
		{
			if (trgroup == iter->GetClass())
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
	trgroup = luaL_checkstring(L, 1);
	
	for (size_t i=0;i<frame->GetTrigger()->size(); i++)
	{
		if(frame->GetTrigger()->at(i).GetClass()==trgroup)
		{
			frame->GetTrigger()->erase(frame->GetTrigger()->begin()+i--);
		}
	}
	for (it = Trigger::GetTriggerClasses()->begin(); it!=Trigger::GetTriggerClasses()->end(); it++)
	{
		if (*it == trgroup)
		{
			Trigger::GetTriggerClasses()->erase(it);
			break;
		}
	}
	if (frame->IsVerbose())
	{
		wxString s;
		s<<_("Deleted action group ")<<trgroup<<".";
		frame->m_child->Msg(s, 3);
	}
	return 0;
}

int luafunc_gettrgroup(lua_State *L)
{
const char* trgroup;
size_t i;
int x=0;
	MudMainFrame *frame = wxGetApp().GetFrame();
	trgroup = luaL_checkstring(L, 1);
	lua_settop(L,0);
	lua_newtable(L);
	for (i=0;i<frame->GetTrigger()->size();i++)
	{
		if (frame->GetTrigger()->at(i).GetClass()==trgroup)
		{
			lua_pushstring(L, frame->GetTrigger()->at(i).GetLabel().char_str());
			lua_rawseti(L, -2, x+1);
			x++;
		}
	}
	lua_pushnumber(L, x);
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

	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkaction(L);
		lua_pushstring(L, t->action);
		i = frame->GetTriggerIndexByLabel(t->label);
	}
	else
	{
		l = luaL_checkstring(L,index);
		i = frame->GetTriggerIndexByLabel(l);
		lua_pushstring(L, frame->GetTrigger()->at(i).GetAction().char_str());
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	
	int state = frame->m_child->GetParseState();
	frame->m_child->SetParseState(0);//HAVE_TEXT
	wxString command = frame->GetTrigger()->at(i).GetAction();
	frame->m_input->Parse(command, true);
	frame->m_child->SetParseState(state);
	return 1;
	
}

int luafunc_actiontostring(lua_State *L)
{
str_ac* t;

	MudMainFrame *frame = wxGetApp().GetFrame();
	t = (str_ac*)checkaction(L);
	lua_pushfstring(L, "type: wxamcl.action, label: \"%s\", pattern: \"%s\", action: \"%s\"", (const char*)t->label, (const char*)t->pattern, t->action);
	return 1;
}

//! amc.alias.new(table{alias="alias", action="action", group="group", on=true|false})
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

	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	//int x= sizeof(struct str_al);
	if (lua_type(L,index)==LUA_TTABLE)
	{
		//lua_getfield(L, -1, c);
		lua_getfield(L, index, "alias");
		const char* cc = luaL_checkstring(L, -1);
		wxString s(cc);
		if (s.at(0)!='^')
			s = '^' + s;
		if (!s.EndsWith("$"))
			s.append('$');
		for (it=frame->GetAlias()->begin();it!=frame->GetAlias()->end();it++)
		{
			if(s==*it)
			{
				frame->m_child->Msg(_("Alias already exists!"));
				return 0;
			}
		}
		al.SetAlias(s);
		lua_getfield(L, index, "action");
		cc = luaL_checkstring(L, -1);
		al.SetAction(cc);
		lua_getfield(L, index, "group");
		cc = luaL_optstring(L, -1, "default");
		al.SetGroup(cc);
		lua_getfield(L, index, "on");
		al.SetActive(lua_toboolean(L,-1)!=0);
	}
	else
	{
		c = luaL_checkstring(L,index++);
		wxString s(c);
		if (s.at(0)!='^')
			s = '^' + s;
		if (!s.EndsWith("$"))
			s.append('$');
		for (it=frame->GetAlias()->begin();it!=frame->GetAlias()->end();it++)
		{
			if(s==*it)
			{
				frame->m_child->Msg(_("Alias already exists!"));
				return 0;
			}
		}
		al.SetAlias(s);
		c = luaL_checkstring(L,index++);
		al.SetAction(c);
		al.SetGroup(luaL_optstring(L,index++, "default"));
		al.SetActive(lua_toboolean(L,index++)!=0);
		
	}
	frame->GetAlias()->push_back(al);
	stable_sort(frame->GetAlias()->begin(), frame->GetAlias()->end(), less<class amcAlias>());
	a = (str_al*)lua_newuserdata(L, sizeof(struct str_al));
	wxStrcpy(a->alias, al.GetAlias().c_str());
	wxStrcpy(a->action, al.GetAction().c_str());
	wxStrcpy(a->cla, al.GetGroup().c_str());
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

	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	//int x= sizeof(struct str_al);
	if (lua_type(L,index)==LUA_TTABLE)
	{
		//lua_getfield(L, -1, c);
		cc = luaL_checkstring(L, -2);
		if (lua_type(L, -1)==LUA_TNIL)
		{
			int i = frame->GetAliasIndexByLabel(cc);
			if (i==-1)
			{
				lua_pushnil(L);
				return 1;
			}
			al_it it = frame->GetAlias()->begin()+i;
			frame->GetAlias()->erase(it);
			stable_sort(frame->GetAlias()->begin(), frame->GetAlias()->end(), greater<class amcAlias>());
			lua_pushnumber(L, frame->GetAlias()->size());
			return 1;
		}
		/*	lua_getfield(L, -1, wxT("pattern"));
			wxChar* cc = (wxChar*)luaL_checkstring(L, -1);
			tr.SetPattern(cc);
			lua_getfield(L, -2, wxT("action"));
			cc = (wxChar*)luaL_checkstring(L, -1);
			tr.SetAction(cc);
			lua_getfield(L, -3, wxT("class"));
			cc = (wxChar*)luaL_optstring(L, -1, wxT("default"));
			tr.SetClass(cc);
			lua_getfield(L, -4, wxT("on"));
			tr.SetActive(lua_toboolean(L,-1)!=0);
			lua_getfield(L, -5, wxT("priority"));
			tr.SetPriority(luaL_optint(L,-1,50));
			lua_getfield(L, -6, wxT("colmatch"));
			tr.SetColMatch(luaL_optint(L,-1,-1));
			lua_getfield(L, -7, wxT("lines"));
			tr.SetLines(luaL_optint(L,-1,1));
		lua_getfield(L, index, wxT("alias"));*/
		
		wxString s(cc);
		if (s.at(0)!=wxT('^'))
			s = wxT('^') + s;
		if (!s.EndsWith(wxT("$")))
			s.append(wxT('$'));
		for (it=frame->GetAlias()->begin();it!=frame->GetAlias()->end();it++)
		{
			if(s==*it)
			{
				frame->m_child->Msg(_("Alias already exists!"));
				return 0;
			}
		}
		al.SetAlias(s);
		lua_getfield(L, -1, "action");
		cc = luaL_checkstring(L, -1);
		al.SetAction(cc);
		lua_getfield(L, -2, "group");
		cc = luaL_optstring(L, -1, "default");
		al.SetGroup(cc);
		lua_getfield(L, -3, "on");
		al.SetActive(lua_toboolean(L,-1)!=0);
	}
	
	frame->GetAlias()->push_back(al);
	stable_sort(frame->GetAlias()->begin(), frame->GetAlias()->end(), less<class amcAlias>());
	a = (str_al*)lua_newuserdata(L, sizeof(struct str_al));
	wxStrcpy(a->alias, al.GetAlias().c_str());
	wxStrcpy(a->action, al.GetAction().c_str());
	wxStrcpy(a->cla, al.GetGroup().c_str());
	a->on = al.IsActive();
	luaL_getmetatable(L, "wxamcl.mtal");
	lua_setmetatable(L, -2);
	return 1;
}

/** a = getalias(name)
 * \brief get an amcAlias as lua table
 * \param L
 * \return table containing the alias
 */
int luafunc_getalias(lua_State* L)
{
str_al* t;
const char* c;
int i, index=1;

	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		t = checkalias(L);
		wxString s(t->alias);
		if (s.at(0)!='^')
			s = '^' + s;
		if (!s.EndsWith("$"))
			s.append('$');
		i = frame->GetAliasIndexByLabel(s);
	}
	else if (lua_type(L,index)==LUA_TTABLE)
	{
		wxString s = luaL_checkstring(L, index+1);
		if (s.at(0)!='^')
			s = '^' + s;
		if (!s.EndsWith("$"))
			s.append('$');
		int idx = frame->GetAliasIndexByLabel(s);
		if (idx==-1)
			return 0;
		wxString ss = frame->GetAlias()->at(idx).GetAction();
		lua_pushstring(L,ss.mb_str());
		return 1;
	}
	else
	{
		c = luaL_checkstring(L,index);
		wxString s(c);
		if (s.at(0)!='^')
			s = '^' + s;
		if (!s.EndsWith("$"))
			s.append('$');
		i = frame->GetAliasIndexByLabel(s);
	}
	if (i==-1)
	{
		frame->m_child->Msg(_("Alias not found!"));
		lua_pushnil(L);
		return 1;
	}
	lua_settop(L,0);
	lua_newtable(L);
	lua_pushstring(L, frame->GetAlias()->at(i).GetAlias().char_str());
	lua_setfield(L, -2, "alias");
	lua_pushstring(L, frame->GetAlias()->at(i).GetAction().mb_str());
	lua_setfield(L, -2, "action");
	lua_pushstring(L, frame->GetAlias()->at(i).GetGroup().mb_str());
	lua_setfield(L, -2, "group");
	lua_pushboolean(L, frame->GetAlias()->at(i).IsActive());
	lua_setfield(L, -2, "on");
	return 1;	
}

/** a,x = getallalias()
 * \brief get all amcAlias as lua table
 * \param L
 * \return table containing the alias, number of alias in table
 */
int luafunc_getallalias(lua_State*L)
{
size_t i;

	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));

	lua_settop(L,0);
	lua_newtable(L);
	for (i=0;i<frame->GetAlias()->size();i++)
	{
		lua_pushstring(L, frame->GetAlias()->at(i).GetAlias().mb_str());
		lua_rawseti(L, -2, i+1);
	}
	lua_pushnumber(L, i);
	return 2;
}

//! x = amc.alias.delete(alias|userdatum)
/*!
	deletes an wxAMC alias in Lua */
/*!	x=amc.delalias("food1") */
/*!	x=amc.delaction(x) provide a userdatum returned from newalias */
/*	returns the number of aliases or nil in case of error
	\param lua_State *L: a valid lua_State
*/
int luafunc_deletealias(lua_State *L)
{
al_it it;
char* c;
int index=1, i;
str_al *a;

	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		a = (str_al*)lua_touserdata(L, index);
		i = frame->GetAliasIndexByLabel(a->alias);
	}
	else
	{
		c = (char*)luaL_checkstring(L,index);
		i = frame->GetAliasIndexByLabel(c);
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
	lua_pushnumber(L, frame->GetAlias()->size());
	return 1;
}

//! x = enablealias(name, true|false)
/*!
	enable or disable alias via Lua
*/
int luafunc_enablealias(lua_State *L)
{
const char* c;
int i, index=1;
str_al *t=NULL;

	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		t = (str_al*)lua_touserdata(L, index++);
		i = frame->GetAliasIndexByLabel(t->alias);
	}
	else
	{
		c = (char*)luaL_checkstring(L,index++);
		i = frame->GetAliasIndexByLabel(c);
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetAlias()->at(i).SetActive(lua_toboolean(L,index)!=0);
	if (!t)
	{
		lua_pushstring(L,c);
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
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkalias(L);
		lua_pushstring(L, t->action);
		return 1;
	}

	else
	{
		l = luaL_checkstring(L,index);
		int i = frame->GetAliasIndexByLabel(l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		else
			lua_pushstring(L, frame->GetAlias()->at(i).GetAction().mb_str());
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
	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));

	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkalias(L);
		c = (char*)luaL_checkstring(L, ++index);
		i = frame->GetAliasIndexByLabel(t->alias);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetAlias()->at(i).SetAction(c);
		wxStrcpy(t->action, c);
		return 0;
	}
	else
	{
		l = (char*)luaL_checkstring(L,index++);
		c = (char*)luaL_checkstring(L, index);
		i = frame->GetAliasIndexByLabel(l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetAlias()->at(i).SetAction(c);
	}
	return 0;
}

int luafunc_deletegroup(lua_State *L)
{
char* c;
s_it it;

	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	c = (char*)luaL_checkstring(L,1);
	bool del = lua_toboolean(L,2)!=0;
	if (del)
	{
		for (size_t i=0;i<frame->GetAlias()->size(); i++)
		{
			if(frame->GetAlias()->at(i).GetGroup()==c)
			{
				frame->GetAlias()->erase(frame->GetAlias()->begin()+i--);
			}
		}
	}
	else
	{
		for (size_t i=0;i<frame->GetAlias()->size(); i++)
		{
			if(frame->GetAlias()->at(i).GetGroup()==c)
			{
				frame->GetAlias()->at(i).SetGroup("default");
			}
		}
	}
	for (it = amcAlias::GetAliasGroups()->begin(); it!=amcAlias::GetAliasGroups()->end(); it++)
	{
		if (*it == c)
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

	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	c = (char*)luaL_checkstring(L,1);
	bool active = lua_toboolean(L,2)!=0;
	if (active)
	{
		for (size_t i=0;i<frame->GetAlias()->size(); i++)
		{
			if(frame->GetAlias()->at(i).GetGroup()==c)
			{
				frame->GetAlias()->at(i).SetActive(true);
			}
		}
	}
	else
	{
		for (size_t i=0;i<frame->GetAlias()->size(); i++)
		{
			if(frame->GetAlias()->at(i).GetGroup()==c)
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

	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
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
	int x = sizeof(struct str_timer);
	if (lua_type(L,index)==LUA_TTABLE)
	{
		//lua_getfield(L, -1, c);
		lua_getfield(L, index, "name");
		cc = luaL_checkstring(L, -1);
		for (it=frame->GetTimers()->begin();it!=frame->GetTimers()->end();it++)
		{
			if(cc==*it)
			{
				frame->m_child->Msg(_("Timer already exists!"));
				return 0;
			}
		}
		timer.SetName(cc);
		lua_getfield(L, index, "action");
		cc = luaL_checkstring(L, -1);
		timer.SetAction(cc);
		lua_getfield(L, index, "group");
		cc = luaL_optstring(L, -1, "default");
		timer.SetGroup(cc);
		lua_getfield(L, index, "on");
		timer.SetActive(lua_toboolean(L,-1)!=0);
		lua_getfield(L, index, "intervall");
		float intv = (float)luaL_checknumber(L,-1);
		timer.SetInterval(intv);
		//hk.SetHotkey(luaL_checklong(L, -1));
		lua_getfield(L, index, "rep");
		int i = (int)luaL_optint(L,-1,-1);
		timer.SetRepeat(i);
		timer.SetCurrepeat(i);
	}
	else
	{
		cc = luaL_checkstring(L,index++);
		for (it=frame->GetTimers()->begin();it!=frame->GetTimers()->end();it++)
		{
			if(cc==*it)
			{
				frame->m_child->Msg(_("Timer already exists!"));
				return 0;
			}
		}
		timer.SetName(cc);
		cc = luaL_checkstring(L,index++);
		timer.SetAction(cc);
		timer.SetGroup(luaL_optstring(L,index++, "default"));
		timer.SetInterval(luaL_checknumber(L,index++));
		timer.SetRepeat(luaL_optint(L,index,-1));
		timer.SetCurrepeat(luaL_optint(L,index++,-1));
		timer.SetActive(lua_toboolean(L,index++)!=0);
	}
	frame->GetTimers()->push_back(timer);
	stable_sort(frame->GetTimers()->begin(), frame->GetTimers()->end(), less<class amcTimer>());
	//stable_sort(frame->GetHotkeys()->begin(), frame->GetHotkeys()->end(), less<class amcHotkey>());
	strt = (str_timer*)lua_newuserdata(L, sizeof(struct str_timer));
	wxStrcpy(strt->name, timer.GetName().mb_str());
	wxStrcpy(strt->action, timer.GetAction().mb_str());
	wxStrcpy(strt->group, timer.GetGroup().mb_str());
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
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		t = (str_timer*)lua_touserdata(L, index);
		i = frame->GetTimerIndexByLabel(t->name);
	}
	else
	{
		c = luaL_checkstring(L,index);
		i = frame->GetTimerIndexByLabel(c);
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	it = frame->GetTimers()->begin()+i;
	frame->GetTimers()->erase(it);
	//v = NULL;
	//stable_sort(frame->GetVars()->begin(), frame->GetVars()->end(), less<class amcVar>());
	lua_pushnumber(L, frame->GetTimers()->size());
	return 1;
}

int luafunc_starttimer(lua_State *L)
{
t_it it;
const char* c;
int index=1, i;
str_timer* t;

	MudMainFrame *frame = wxGetApp().GetFrame();	
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		t = (str_timer*)lua_touserdata(L, index);
		i = frame->GetTimerIndexByLabel(t->name);
	}
	else
	{
		c = luaL_checkstring(L,index);
		i = frame->GetTimerIndexByLabel(c);
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
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		t = (str_timer*)lua_touserdata(L, index);
		i = frame->GetTimerIndexByLabel(t->name);
	}
	else
	{
		c = luaL_checkstring(L,index);
		i = frame->GetTimerIndexByLabel(c);
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	
	frame->GetTimers()->at(i).SetActive(false);
	frame->GetTimers()->at(i).Stop();
	return 0;
}

int luafunc_enabletimer(lua_State *L)
{
const char* c;
int i, index=1;
str_timer* t=NULL;

	MudMainFrame *frame = wxGetApp().GetFrame();
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		t = (str_timer*)lua_touserdata(L, index++);
		i = frame->GetTimerIndexByLabel(t->name);
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetTimerIndexByLabel(c);
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetTimers()->at(i).SetActive(lua_toboolean(L,index)!=0);
	if (!t)
	{
		lua_pushstring(L,c);
	}
	else
	{
		t->on = frame->GetTimers()->at(i).IsActive();
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
	int x = sizeof(struct str_hk);
	if (lua_type(L,index)==LUA_TTABLE)
	{
		//lua_getfield(L, -1, c);
		lua_getfield(L, index, "name");
		cc = luaL_checkstring(L, -1);
		for (it=frame->GetHotkeys()->begin();it!=frame->GetHotkeys()->end();it++)
		{
			if(cc==*it)
			{
				frame->m_child->Msg(_("Hotkey already exists!"));
				return 0;
			}
		}
		hk.SetName(cc);
		lua_getfield(L, index, "action");
		cc = luaL_checkstring(L, -1);
		hk.SetAction(cc);
		lua_getfield(L, index, "group");
		cc = luaL_optstring(L, -1, "default");
		hk.SetGroup(cc);
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
		for (it=frame->GetHotkeys()->begin();it!=frame->GetHotkeys()->end();it++)
		{
			if(cc==*it)
			{
				frame->m_child->Msg(_("Hotkey already exists!"));
				return 0;
			}
		}
		hk.SetName(cc);
		cc = luaL_checkstring(L,index++);
		map<wxString, long> m = frame->GetKeys();
		long k = m[cc];
		hk.SetHotkey(k);
		cc = luaL_checkstring(L,index++);
		int i = (int)m[cc];
		hk.SetMods(i);
		cc = luaL_checkstring(L,index++);
		hk.SetAction(cc);
		hk.SetGroup(luaL_optstring(L,index++, "default"));
		hk.SetActive(lua_toboolean(L,index++)!=0);
	}
	frame->GetHotkeys()->push_back(hk);
	//stable_sort(frame->GetHotkeys()->begin(), frame->GetHotkeys()->end(), less<class amcHotkey>());
	hkey = (str_hk*)lua_newuserdata(L, sizeof(struct str_hk));
	wxStrcpy(hkey->name, hk.GetName().mb_str());
	wxStrcpy(hkey->action, hk.GetAction().mb_str());
	wxStrcpy(hkey->group, hk.GetGroup().mb_str());
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

	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		h = checkhk(L);
		wxString s(h->name);
		i = frame->GetHkIndexByLabel(s);
	}
	else if (lua_type(L,index)==LUA_TTABLE)
	{
		wxString s = luaL_checkstring(L, index+1);
		int idx = frame->GetHkIndexByLabel(s);
		if (idx==-1)
			return 0;
		wxString ss = frame->GetHotkeys()->at(idx).GetAction();
		lua_pushstring(L,ss.mb_str());
		return 1;
	}
	else
	{
		c = luaL_checkstring(L,index);
		wxString s(c);
		i = frame->GetHkIndexByLabel(s);
	}
	if (i==-1)
	{
		frame->m_child->Msg(_("Hotkey not found!"));
		lua_pushnil(L);
		return 1;
	}
	lua_settop(L,0);
	lua_newtable(L);
	lua_pushstring(L, frame->GetHotkeys()->at(i).GetName().char_str());
	lua_setfield(L, -2, "name");
	lua_pushstring(L, frame->GetHotkeys()->at(i).GetAction().mb_str());
	lua_setfield(L, -2, "action");
	lua_pushstring(L, frame->GetHotkeys()->at(i).GetGroup().mb_str());
	lua_setfield(L, -2, "group");
	lua_pushboolean(L, frame->GetHotkeys()->at(i).IsActive());
	lua_setfield(L, -2, "on");
	lua_pushstring(L, frame->GetHotkeys()->at(i).GetKeyName().mb_str());
	lua_setfield(L, -2, "keyname");
	lua_pushstring(L, frame->GetHotkeys()->at(i).GetModName().mb_str());
	lua_setfield(L, -2, "modname");
	lua_pushnumber(L, frame->GetHotkeys()->at(i).GetHotkey());
	lua_setfield(L, -2, "key");
	lua_pushnumber(L, frame->GetHotkeys()->at(i).GetModifier());
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
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		v = (str_hk*)lua_touserdata(L, index);
		i = frame->GetHkIndexByLabel(v->name);
	}
	else
	{
		c = luaL_checkstring(L,index);
		i = frame->GetHkIndexByLabel(c);
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	it = frame->GetHotkeys()->begin()+i;
	frame->GetHotkeys()->erase(it);
	//v = NULL;
	//stable_sort(frame->GetVars()->begin(), frame->GetVars()->end(), less<class amcVar>());
	lua_pushnumber(L, frame->GetHotkeys()->size());
	return 1;
}

int luafunc_gethkaction(lua_State *L)
{
const char* l;
str_hk* t;
int index=1;

	MudMainFrame *frame = wxGetApp().GetFrame();
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		t = checkhk(L);
		lua_pushstring(L, t->action);
		return 1;
	}

	else
	{
		l = luaL_checkstring(L,index);
		int i = frame->GetHkIndexByLabel(l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		else
			lua_pushstring(L, frame->GetHotkeys()->at(i).GetAction().mb_str());
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
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		//t = checkalias(L);
		t = (str_hk*)lua_touserdata(L, index);
		c = luaL_checkstring(L, ++index);
		i = frame->GetHkIndexByLabel(t->name);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetHotkeys()->at(i).SetAction(c);
		wxStrcpy(t->action, c);
		return 0;
	}
	else
	{
		l = luaL_checkstring(L,index++);
		c = luaL_checkstring(L, index);
		i = frame->GetHkIndexByLabel(l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetHotkeys()->at(i).SetAction(c);
	}
	return 0;
}

int luafunc_enablehk(lua_State *L)
{
const char* c;
int i, index=1;
str_hk* v=NULL;

	MudMainFrame *frame = wxGetApp().GetFrame();
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		v = (str_hk*)lua_touserdata(L, index++);
		i = frame->GetHkIndexByLabel(v->name);
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetHkIndexByLabel(c);
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetHotkeys()->at(i).SetActive(lua_toboolean(L,index)!=0);
	if (!v)
	{
		lua_pushstring(L,c);
	}
	else
	{
		v->on = frame->GetHotkeys()->at(i).IsActive();
		lua_pushstring(L, v->name);
	}
	return 1;
}

int luafunc_deletehkgroup(lua_State *L)
{
const char* c;
s_it it;

	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	c = luaL_checkstring(L,1); 
	bool del = lua_toboolean(L,2)!=0;
	if (del)
	{
		for (size_t i=0;i<frame->GetHotkeys()->size(); i++)
		{
			if(frame->GetHotkeys()->at(i).GetGroup()==c)
			{
				frame->GetHotkeys()->erase(frame->GetHotkeys()->begin()+i--);
			}
		}
	}
	else
	{
		for (size_t i=0;i<frame->GetHotkeys()->size(); i++)
		{
			if(frame->GetHotkeys()->at(i).GetGroup()==c)
			{
				frame->GetHotkeys()->at(i).SetGroup("default");
			}
		}
	}
	for (it = amcHotkey::GetHotkeyGroups()->begin(); it!=amcHotkey::GetHotkeyGroups()->end(); it++)
	{
		if (*it == c)
		{
			amcHotkey::GetHotkeyGroups()->erase(it);
			break;
		}
	}
	return 0;
}

int luafunc_enablehkgroup(lua_State *L)
{
hk_it iter;
const char* hkgroup;

	MudMainFrame *frame = wxGetApp().GetFrame();
	hkgroup = luaL_checkstring(L, 1);
	bool active = lua_toboolean(L,2) != 0;
	for (iter = frame->GetHotkeys()->begin(); iter!= frame->GetHotkeys()->end(); iter++)
	{
		if (hkgroup == iter->GetGroup())
		{
			iter->SetActive(active);
		}
	}
	if (frame->IsVerbose())
	{
		wxString s;
		if (active)
			s<<_("Enabled hotkey group ")<<hkgroup<<".";
		else
			s<<_("Disabled hotkey group ")<<hkgroup<<".";
		frame->m_child->Msg(s, 3);
	}
	return 0;
}

int luafunc_getallhk(lua_State *L)
{
size_t i;

	MudMainFrame *frame = wxGetApp().GetFrame();
	lua_settop(L,0);
	lua_newtable(L);
	for (i=0;i<frame->GetHotkeys()->size();i++)
	{
		lua_pushstring(L, frame->GetHotkeys()->at(i).GetName().mb_str());
		lua_rawseti(L, -2, i+1);
	}
	lua_pushnumber(L, i);
	return 2;
}

int luafunc_exechk(lua_State *L)
{
const char* c;
int i, index=1;
str_hk* v=NULL;

	MudMainFrame *frame = wxGetApp().GetFrame();
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		v = (str_hk*)lua_touserdata(L, index++);
		i = frame->GetHkIndexByLabel(v->name);
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetHkIndexByLabel(c);
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	int state = frame->m_child->GetParseState();
	frame->m_child->SetParseState(0);//HAVE_TEXT
	wxString command = frame->GetHotkeys()->at(i).GetAction();
	frame->m_input->Parse(command, true);
	frame->m_child->SetParseState(state);
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

	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	int x = sizeof(struct str_var);
	if (lua_type(L,index)==LUA_TTABLE)
	{
		//lua_getfield(L, -1, c);
		lua_getfield(L, index, "name");
		cc = luaL_checkstring(L, -1);
		for (it=frame->GetVars()->begin();it!=frame->GetVars()->end();it++)
		{
			if(cc==*it)
			{
				frame->m_child->Msg(_("Variable already exists!"));
				return 0;
			}
		}
		v.SetName(cc);
		lua_getfield(L, index, "value");
		cc = luaL_checkstring(L, -1);
		v.SetValue(cc);
		lua_getfield(L, index, "group");
		cc = luaL_optstring(L, -1, "default");
		v.SetGroup(cc);
		lua_getfield(L, index, "on");
		v.SetActive(lua_toboolean(L,-1)!=0);
	}
	else
	{
		cc = luaL_checkstring(L,index++);
		for (it=frame->GetVars()->begin();it!=frame->GetVars()->end();it++)
		{
			if(cc==*it)
			{
				frame->m_child->Msg(_("Variable already exists!"));
				return 0;
			}
		}
		v.SetName(cc);
		cc = luaL_checkstring(L,index++);
		v.SetValue(cc);
		v.SetGroup(luaL_optstring(L,index++, "default"));
		v.SetActive(lua_toboolean(L,index++)!=0);
	}
	frame->GetVars()->push_back(v);
	stable_sort(frame->GetVars()->begin(), frame->GetVars()->end(), less<class amcVar>());
	a = (str_var*)lua_newuserdata(L, sizeof(struct str_var));
	wxStrcpy(a->name, v.GetName().c_str());
	wxStrcpy(a->value, v.GetValue().c_str());
	wxStrcpy(a->group, v.GetGroup().c_str());
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

	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	//int x= sizeof(struct str_al);
	if (lua_type(L,index)==LUA_TTABLE)
	{
		//lua_getfield(L, -1, c);
		cc = luaL_checkstring(L, -2);
		if (lua_type(L, -1)==LUA_TNIL)
		{
			int i = frame->GetVarIndexByLabel(cc);
			if (i==-1)
			{
				lua_pushnil(L);
				return 1;
			}
			v_it it = frame->GetVars()->begin()+i;
			frame->GetVars()->erase(it);
			stable_sort(frame->GetVars()->begin(), frame->GetVars()->end(), greater<class amcVar>());
			lua_pushnumber(L, frame->GetVars()->size());
			return 1;
		}
		wxString s(cc);
		for (it=frame->GetVars()->begin();it!=frame->GetVars()->end();it++)
		{
			if(s==*it)
			{
				frame->m_child->Msg(_("Variable already exists!"));
				return 0;
			}
		}
		v.SetName(s);
		lua_getfield(L, -1, "value");
		cc = luaL_checkstring(L, -1);
		v.SetValue(cc);
		lua_getfield(L, -2, "group");
		cc = luaL_optstring(L, -1, "default");
		v.SetGroup(cc);
		lua_getfield(L, -3, "on");
		v.SetActive(lua_toboolean(L,-1)!=0);
	}
	
	frame->GetVars()->push_back(v);
	stable_sort(frame->GetVars()->begin(), frame->GetVars()->end(), less<class amcVar>());
	av = (str_var*)lua_newuserdata(L, sizeof(struct str_var));
	wxStrcpy(av->name, v.GetName().c_str());
	wxStrcpy(av->value, v.GetValue().c_str());
	wxStrcpy(av->group, v.GetGroup().c_str());
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
	if (lua_type(L,1)==LUA_TUSERDATA)
	{
		v = checkvar(L);
		wxString s(v->name);
		idx = frame->GetVarIndexByLabel(s);
	}
	else
	{
		name = luaL_checkstring(L, 1);
		idx = frame->GetVarIndexByLabel(name);
	}
	if (idx==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	lua_pushstring(L, frame->GetVars()->at(idx).GetValue().mb_str());
	return 1;
}

int luafunc_setvar(lua_State *L)
{
const char* name;
const char* value;
int idx;
str_var* v;
int index=1;
	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));	
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		v = checkvar(L);
		value = (char*)luaL_checkstring(L, ++index);
		idx = frame->GetVarIndexByLabel(v->name);
		if (idx==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		wxString s(value);
		frame->m_input->ParseVars(&s);
		frame->GetVars()->at(idx).SetValue(s);
		wxStrcpy(v->value, s.c_str());
		lua_pushboolean(L, 1);
		return 1;
	}
	else
	{
		name = luaL_checkstring(L, 1);
		idx = frame->GetVarIndexByLabel(name);
		if (idx==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		value = luaL_checkstring(L, 2);
		wxString s(value);
		frame->m_input->ParseVars(&s);
		frame->GetVars()->at(idx).SetValue(s);
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
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		v = (str_var*)lua_touserdata(L, index);
		i = frame->GetVarIndexByLabel(v->name);
	}
	else
	{
		c = luaL_checkstring(L,index);
		i = frame->GetVarIndexByLabel(c);
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	it = frame->GetVars()->begin()+i;
	frame->GetVars()->erase(it);
	v = NULL;
	stable_sort(frame->GetVars()->begin(), frame->GetVars()->end(), less<class amcVar>());
	lua_pushnumber(L, frame->GetVars()->size());
	return 1;
}

int luafunc_enablevar(lua_State *L)
{
const char* c;
int i, index=1;
str_var* v=NULL;

	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		v = (str_var*)lua_touserdata(L, index++);
		i = frame->GetVarIndexByLabel(v->name);
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetVarIndexByLabel(c);
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetVars()->at(i).SetActive(lua_toboolean(L,index)!=0);
	if (!v)
	{
		lua_pushstring(L,c);
	}
	else
	{
		v->on = frame->GetVars()->at(i).IsActive();
		lua_pushstring(L, v->name);
	}
	return 1;
}

int luafunc_getallvar(lua_State *L)
{
	size_t i;

	MudMainFrame *frame = wxGetApp().GetFrame();

	lua_settop(L,0);
	lua_newtable(L);
	for (i=0;i<frame->GetVars()->size();i++)
	{
		lua_pushstring(L, frame->GetVars()->at(i).GetName().mb_str());
		lua_rawseti(L, -2, i+1);
	}
	lua_pushnumber(L, i);
	return 2;
}

int luafunc_enablevargroup(lua_State *L)
{
v_it iter;
	MudMainFrame *frame = wxGetApp().GetFrame();
	const char* vgroup;
	vgroup = luaL_checkstring(L, 1);
	bool active = lua_toboolean(L,2) != 0;
	for (iter = frame->GetVars()->begin(); iter!= frame->GetVars()->end(); iter++)
	{
		if (vgroup == iter->GetGroup())
		{
			iter->SetActive(active);
		}
	}
	if (frame->IsVerbose())
	{
		wxString s;
		if (active)
			s<<_("Enabled variable group ")<<vgroup<<".";
		else
			s<<_("Disabled variable group ")<<vgroup<<".";
		frame->m_child->Msg(s, 3);
	}
	return 0;
}

int luafunc_delvargroup(lua_State *L)
{
s_it it;
const char* vgroup;
	MudMainFrame *frame = wxGetApp().GetFrame();
	vgroup = luaL_checkstring(L, 1);
	
	for (size_t i=0;i<frame->GetVars()->size(); i++)
	{
		if(frame->GetVars()->at(i).GetGroup()==vgroup)
		{
			frame->GetVars()->erase(frame->GetVars()->begin()+i--);
		}
	}
	
	for (it = amcVar::GetVarGroups()->begin(); it!=amcVar::GetVarGroups()->end(); it++)
	{
		if (*it == vgroup)
		{
			amcVar::GetVarGroups()->erase(it);
			if (frame->IsVerbose())
			{
				wxString s;
				s<<_("Deleted variable class ")<<vgroup<<".";
				frame->m_child->Msg(s, 3);
			}
			return 0;
		}
	}
	if (it==amcVar::GetVarGroups()->end())
	{
		wxString s;
		s<<_("Group ")<<vgroup<<_(" does not exist!");
		frame->m_child->Msg(s,3);
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

	MudMainFrame *frame = (MudMainFrame*)wxGetApp().GetFrame();//MudMainFrame::FindWindowByName("wxAMC");
//	int x= sizeof(struct str_ll);
	//called from amc.newlist
	if(lua_type(L, index) != LUA_TTABLE)
	{
		c = luaL_checkstring(L, index++);
	
		for (it=frame->GetLists()->begin();it!=frame->GetLists()->end();it++)
		{
			if(c==*it)
			{
				frame->m_child->Msg(_("Error creating list!"));
				return 0;
			}
		}
		list.SetName(c);
	}

	if (lua_type(L,index)==LUA_TTABLE)
	{
		//lua_getfield(L, -1, c);
		lua_getfield(L, index, "name");
		const char* cc = luaL_checkstring(L, -1);
		for (it=frame->GetLists()->begin();it!=frame->GetLists()->end();it++)
		{
			if(cc==*it)
			{
				frame->m_child->Msg(_("List already exists!"));
				return 0;
			}
		}
		list.SetName(cc);
		lua_getfield(L, index, "group");
		cc = luaL_optstring(L, -1, "default");
		list.SetGroup(cc);
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
		list.SetGroup(luaL_optstring(L,index++, "default"));
		list.SetActive(lua_toboolean(L,index++)!=0);
		
	}
	frame->GetLists()->push_back(list);
	//stable_sort(frame->GetLists()->begin(), frame->GetLists()->end(), less<class amcList>());
	l = (str_ll*)lua_newuserdata(L, sizeof(struct str_ll));
	wxStrcpy(l->name, list.GetName().c_str());
	//l->name = list.GetName();
	wxStrcpy(l->cla, list.GetGroup().c_str());
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
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		l = (str_ll*)lua_touserdata(L, index++);
		i = frame->GetListIndexByLabel(l->name);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetListIndexByLabel(c);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
	}
	lua_settop(L,0);
	lua_newtable(L);
	int co = frame->GetLists()->at(i).GetSize();
	for (int ii=0;ii<co;ii++)
	{
		lua_pushstring(L, frame->GetLists()->at(i).GetItem(ii));
		lua_rawseti(L, -2, ii+1);
	}
	lua_pushnumber(L, co);
	return 2;
}

int luafunc_getitemat(lua_State *L)
{
const char* c;
int i, index=1;
str_ll* l;

	MudMainFrame *frame = (MudMainFrame*)wxGetApp().GetFrame();
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		l = (str_ll*)lua_touserdata(L, index++);
		i = frame->GetListIndexByLabel(l->name);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetListIndexByLabel(c);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
	}
	int co = luaL_checknumber(L, index);
	if (co>frame->GetLists()->at(i).GetSize()||!co)
	{
		if (frame->IsVerbose())
		{
			frame->m_child->Msg(_("Given index out of bounds!"), 3);
		}
		lua_pushnil(L);
		return 1;
	}
	lua_pushstring(L,frame->GetLists()->at(i).GetItem(co-1).c_str());
	return 1;
}

int luafunc_additem(lua_State *L)
{
const char* c;
int i, index=1;
str_ll* l;

	MudMainFrame *frame = (MudMainFrame*)wxGetApp().GetFrame();
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		l = (str_ll*)lua_touserdata(L, index++);
		i = frame->GetListIndexByLabel(l->name);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		c = luaL_checkstring(L, index++);
		wxStrcpy(l->items[frame->GetLists()->at(i).GetSize()], c);
		frame->GetLists()->at(i).AddItem(c);
		lua_pushnumber(L, frame->GetLists()->at(i).GetSize());
		return 1;
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetListIndexByLabel(c);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		c = luaL_checkstring(L, index);
		frame->GetLists()->at(i).AddItem(c);
		lua_pushnumber(L, frame->GetLists()->at(i).GetSize());
		return 1;
	}
	return 0;
}

int luafunc_delallitems(lua_State *L)
{
char* c;
int i, index=1;
str_ll* l;

	MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		l = (str_ll*)lua_touserdata(L, index++);
		i = frame->GetListIndexByLabel(l->name);
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
		i = frame->GetListIndexByLabel(c);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetLists()->at(i).ClearItems();
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

	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		l = (str_ll*)lua_touserdata(L, index);
		i = frame->GetListIndexByLabel(l->name);
	}
	else
	{
		c = luaL_checkstring(L,index);
		i = frame->GetListIndexByLabel(c);
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
	lua_pushnumber(L, frame->GetLists()->size());
	return 1;
}

int luafunc_delitemat(lua_State *L)
{
li_it it;
const char* c;
int idx=0;
int index=1, i;
str_ll* l;
	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		l = (str_ll*)lua_touserdata(L, index++);
		i = frame->GetListIndexByLabel(l->name);
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetListIndexByLabel(c);
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	idx=luaL_checkint(L, index);
	if (idx>frame->GetLists()->at(i).GetSize())
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetLists()->at(i).DeleteItemAt(idx-1);
	lua_pushnumber(L, frame->GetLists()->size());
	return 1;
}

int luafunc_delitem(lua_State *L)
{
li_it it;
const char* c;
int index=1, i;
str_ll* l;
	MudMainFrame *frame = wxGetApp().GetFrame();
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		l = (str_ll*)lua_touserdata(L, index++);
		i = frame->GetListIndexByLabel(l->name);
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetListIndexByLabel(c);
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	c=luaL_checkstring(L, index);
	if (!frame->GetLists()->at(i).DeleteItem(c))
	{
		lua_pushnil(L);
		return 1;
	}
	lua_pushnumber(L, frame->GetLists()->size());
	return 1;
}

int luafunc_contains(lua_State *L)
{
li_it it;
const char* c;
int index=1, i;
str_ll* l;
	MudMainFrame *frame = wxGetApp().GetFrame();
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		l = (str_ll*)lua_touserdata(L, index++);
		i = frame->GetListIndexByLabel(l->name);
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetListIndexByLabel(c);
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	c = luaL_checkstring(L, index);
	if (!frame->GetLists()->at(i).Contains(c))
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
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		l = (str_ll*)lua_touserdata(L, index++);
		i = frame->GetListIndexByLabel(l->name);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
	}
	else
	{
		c = luaL_checkstring(L,index++);
		i = frame->GetListIndexByLabel(c);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
	}
	lua_pushnumber(L, frame->GetLists()->at(i).GetSize());
	return 1;
}

int luafunc_enablelistgroup(lua_State *L)
{
li_it iter;
MudMainFrame *frame = wxGetApp().GetFrame();
const char* lgroup;
bool exist = false;
	lgroup = luaL_checkstring(L, 1);
	bool active = lua_toboolean(L,2) != 0;
	for (iter = frame->GetLists()->begin(); iter!= frame->GetLists()->end(); iter++)
	{
		if (lgroup == iter->GetGroup())
		{
			iter->SetActive(active);
			exist = true;
		}
	}
	if (!exist)
	{
		wxString s;
		s<<_("Group ")<<lgroup<<_(" does not exist!");
		frame->m_child->Msg(s,3);
		return 0;
	}
	if (frame->IsVerbose())
	{
		wxString s;
		if (active)
			s<<_("Enabled list group ")<<lgroup<<".";
		else
			s<<_("Disabled list group ")<<lgroup<<".";
		frame->m_child->Msg(s, 3);
	}
	return 0;
}

int luafunc_getalllist(lua_State *L)
{
	size_t i;
	MudMainFrame *frame = wxGetApp().GetFrame();

	lua_settop(L,0);
	lua_newtable(L);
	for (i=0;i<frame->GetLists()->size();i++)
	{
		lua_pushstring(L, frame->GetLists()->at(i).GetName().mb_str());
		lua_rawseti(L, -2, i+1);
	}
	lua_pushnumber(L, i);
	return 2;
}

int luafunc_dellistgroup(lua_State *L)
{
s_it it;
const char* lgroup;
	MudMainFrame *frame = wxGetApp().GetFrame();
	lgroup = luaL_checkstring(L, 1);
	
	for (size_t i=0;i<frame->GetLists()->size(); i++)
	{
		if(frame->GetLists()->at(i).GetGroup()==lgroup)
		{
			frame->GetLists()->erase(frame->GetLists()->begin()+i--);
		}
	}
	
	for (it = amcList::GetListGroups()->begin(); it!=amcList::GetListGroups()->end(); it++)
	{
		if (*it == lgroup)
		{
			amcList::GetListGroups()->erase(it);
			if (frame->IsVerbose())
			{
				wxString s;
				s<<_("Deleted list group ")<<lgroup<<".";
				frame->m_child->Msg(s, 3);
			}
			return 0;
		}
	}
	if (it==amcList::GetListGroups()->end())
	{
		wxString s;
		s<<_("Group ")<<lgroup<<_(" does not exist!");
		frame->m_child->Msg(s,3);
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
	const wxString* name = new wxString(winname);
	class GaugeWindow *frame = (GaugeWindow*)GaugeWindow::FindWindowByName(*name);
	//text = wxlua_getwxStringtype(L,1);
	if (frame==NULL)
	{
		delete name;
		return 0;
	}
		//frame->Msg(wxString(text));
	int idx = frame->GetGaugeIndexByName(gauge);
	delete name;
	wxClientDC dc(frame);
	//frame->GetGauges()->at(idx).DrawGauge(&dc);
	frame->Refresh();
	return 0;
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
	class MudWindow *frame = wxGetApp().GetChild();//(MudWindow*)MudWindow::FindWindowByName("amcoutput");
	if (frame==NULL)
		return 0;
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
	amcGauge g(winname, name, var1, var2, frame->GetColour(b[fcol]-40), frame->GetColour(b[bcol]-40), 10, 10, 100, 40, vert);
	class MudMainFrame *f = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	if (!f->GetGaugePanes()->empty())
	{
		for (i=0;i<f->GetGaugePanes()->size();i++)
		{
			if (winname==f->GetGaugePanes()->at(i))
				break;
		}
	}
	g.Register();
	f->GetGauges()->at(i).push_back(name);
	//frame->GetGauges()->at(idx).DrawGauge();
	return 0;
}

int luafunc_sizegauge(lua_State *L)
{
	const char *winname;
	const char * gauge;
	int x,y,cx,cy;
	
	winname = luaL_checkstring(L, 1);
	gauge = luaL_checkstring(L, 2);
	x = luaL_optint(L, 3, 10);
	y = luaL_optint(L, 4, 10);
	cx = luaL_optint(L, 5, 100);
	cy = luaL_optint(L, 6, 40);
	//class MudWindow *frame = wxGetApp().GetChild();
	class GaugeWindow *frame = (GaugeWindow*)GaugeWindow::FindWindowByName(winname);
	if (frame==NULL)
		return 0;
	int idx = frame->GetGaugeIndexByName(gauge);
	if (idx==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetGauges()->at(idx).SetX(x);
	frame->GetGauges()->at(idx).SetY(y);
	frame->GetGauges()->at(idx).SetCx(cx);
	frame->GetGauges()->at(idx).SetCy(cy);
	wxClientDC dc(frame);
	//frame->GetGauges()->at(idx).DrawGauge(&dc);
	frame->Refresh();
	//frame->Update();
	return 0;
}
int luafunc_colorgauge(lua_State *L)
{
	const char* fcol;
	const char* bcol;
	const char* alarm;
	const char* winname;
	const char* gauge;
	winname = luaL_checkstring(L, 1);
	gauge = luaL_checkstring(L, 2);
	fcol=luaL_optstring(L, 3, "white");
	bcol=luaL_optstring(L, 4, "black");
	alarm=luaL_optstring(L, 5, "red");
	class GaugeWindow *frame = (GaugeWindow*)GaugeWindow::FindWindowByName(winname);
	class MudWindow *frame1 = wxGetApp().GetChild();
	if (frame==NULL)
		return 0;
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
	int idx = frame->GetGaugeIndexByName(gauge);
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
	return 0;
}

int luafunc_creategaugewin(lua_State*L)
{
	const char* winname;
	GaugeWindow *gw;
	class MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));

	winname = luaL_checkstring(L,1);
	gw = (GaugeWindow*)GaugeWindow::FindWindowByName(winname, frame);
	if (gw)
		return 0;
	gw = new GaugeWindow(frame, winname);
	gw->SetName(winname);
	frame->GetGaugePanes()->push_back(winname);
	vector<wxString> s;
	frame->GetGauges()->push_back(s);
	
	frame->m_mgr.AddPane(gw, wxAuiPaneInfo().Name(winname).Caption(winname).CaptionVisible(true).Floatable(true).FloatingSize(400,200).BestSize(400,200).Dockable(true).Dock().Top().Layer(1));
	//frame->m_mgr.AddPane(mw, wxAuiPaneInfo().Name(winname).Top().Caption(winname));
	frame->m_mgr.Update();
	return 0;
}

int luafunc_setgaugelabel(lua_State *L)
{
	const char* winname;
	const char* gauge;
	const char* label;
	winname = luaL_checkstring(L, 1);
	gauge = luaL_checkstring(L, 2);
	label = luaL_checkstring(L, 3);
	class GaugeWindow *frame = (GaugeWindow*)GaugeWindow::FindWindowByName(winname);
	class MudWindow *frame1 = wxGetApp().GetChild();
	if (frame==NULL)
		return 0;
	int idx = frame->GetGaugeIndexByName(gauge);
	if (idx==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetGauges()->at(idx).SetLabel(label);
	wxClientDC dc(frame);
	//frame->GetGauges()->at(idx).DrawGauge(&dc);
	frame->Refresh();
	return 0;
}

int luafunc_deletegauge(lua_State *L)
{
const char* winname;
const char* gauge;

	winname = luaL_checkstring(L, 1);
	gauge = luaL_checkstring(L, 2);
	class GaugeWindow *frame = (GaugeWindow*)GaugeWindow::FindWindowByName(winname);
	class MudWindow *frame1 = wxGetApp().GetChild();
	if (frame==NULL)
		return 0;
	int idx = frame->GetGaugeIndexByName(gauge);
	if (idx==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	frame->GetGauges()->erase(frame->GetGauges()->begin()+idx);
	wxClientDC dc(frame);
	//frame->GetGauges()->at(idx).DrawGauge(&dc);
	frame->Refresh();
	return 0;
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
	int x = sizeof(struct str_btn);
	if (lua_type(L,index)==LUA_TTABLE)
	{
		//lua_getfield(L, -1, c);
		lua_getfield(L, index, "name");
		cc = luaL_checkstring(L, -1);
		for (it=frame->GetButtons()->begin();it!=frame->GetButtons()->end();it++)
		{
			if(cc==*it)
			{
				frame->m_child->Msg(_("Button already exists!"));
				return 0;
			}
		}
		b.SetName(cc);
		b.SetText(cc);
		lua_getfield(L, index, "action");
		cc = luaL_checkstring(L, -1);
		b.SetAction(cc);
		lua_getfield(L, index, "group");
		cc = luaL_optstring(L, -1, "default");
		b.SetGroup(cc);
		lua_getfield(L, index, "on");
		b.SetActive(lua_toboolean(L,-1)!=0);
		b.SetId(ID_USERBUTTON+frame->GetButtons()->size()+1);
		lua_getfield(L, index, "toolbar");
		cc = luaL_checkstring(L, -1);
		tb = (wxAuiToolBar*)MudMainFrame::FindWindowByName(cc, frame);
		if (!tb)
		{
			wxString s;
			s<<"amc.createtoolbar('"<<cc<<"')";
			luaL_dostring(L,s.c_str());
			tb = (wxAuiToolBar*)MudMainFrame::FindWindowByName(cc, frame);
			//lua_pushnil(L);
		}
		b.SetTbName(cc);
		b.SetParent(tb);
		tb->AddTool(b.GetId(), b.GetName(), script_xpm);
		tb->SetToolTextOrientation(wxAUI_TBTOOL_TEXT_RIGHT);
		
	}
	else
	{
		cc = luaL_checkstring(L,index++);
		for (it=frame->GetButtons()->begin();it!=frame->GetButtons()->end();it++)
		{
			if(cc==*it)
			{
				frame->m_child->Msg(_("Button already exists!"));
				return 0;
			}
		}
		b.SetName(cc);
		b.SetText(cc);
		cc = luaL_checkstring(L,index++);//toolbar
		tb = (wxAuiToolBar*)MudMainFrame::FindWindowByName(cc, frame);
		if (!tb)
		{
			wxString s;
			s<<"amc.createtoolbar('"<<cc<<"')";
			luaL_dostring(L,s.c_str());
			tb = (wxAuiToolBar*)MudMainFrame::FindWindowByName(cc, frame);
			//lua_pushnil(L);
		}
		b.SetTbName(cc);
		b.SetParent(tb);
		b.SetId(ID_USERBUTTON+frame->GetButtons()->size()+1);
		tb->AddTool(b.GetId(), b.GetName(), script_xpm);
		tb->SetToolTextOrientation(wxAUI_TBTOOL_TEXT_RIGHT);
		cc = luaL_checkstring(L,index++);
		b.SetAction(cc);
		//cc = luaL_checkstring(L,index++);
		b.SetGroup(luaL_optstring(L,index++, "default"));
		b.SetActive(lua_toboolean(L,index++)!=0);
		
	}
	frame->GetButtons()->push_back(b);
	tb->Realize();
	//stable_sort(frame->GetHotkeys()->begin(), frame->GetHotkeys()->end(), less<class amcHotkey>());
	bb = (str_btn*)lua_newuserdata(L, sizeof(struct str_btn));
	wxStrcpy(bb->name, b.GetName().mb_str());
	wxStrcpy(bb->text, b.GetText().mb_str());
	wxStrcpy(bb->action, b.GetAction().mb_str());
	wxStrcpy(bb->group, b.GetGroup().mb_str());
	wxStrcpy(bb->tbar, b.GetTbName().mb_str());
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
	
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		bt = checkbtn(L);
		i = frame->GetVarIndexByLabel(bt->name);
	}
	else
	{
		cc = luaL_checkstring(L,index);
		i = frame->GetVarIndexByLabel(cc);
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
	if (lua_type(L,1)==LUA_TUSERDATA)
	{
		bt = checkbtn(L);
		wxString s(bt->name);
		idx = frame->GetButtonIndexByLabel(s);
	}
	else
	{
		name = luaL_checkstring(L, 1);
		idx = frame->GetButtonIndexByLabel(name);
	}
	if (idx==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	lua_settop(L,0);
	lua_newtable(L);
	lua_pushstring(L, frame->GetButtons()->at(idx).GetName().char_str());
	lua_setfield(L, -2, "name");
	lua_pushstring(L, frame->GetButtons()->at(idx).GetAction().mb_str());
	lua_setfield(L, -2, "action");
	lua_pushstring(L, frame->GetButtons()->at(idx).GetGroup().mb_str());
	lua_setfield(L, -2, "group");
	lua_pushboolean(L, frame->GetButtons()->at(idx).IsActive());
	lua_setfield(L, -2, "on");
	lua_pushstring(L, frame->GetButtons()->at(idx).GetTbName().mb_str());
	lua_setfield(L, -2, "toolbar");
	lua_pushnumber(L, frame->GetButtons()->at(idx).GetId());
	lua_setfield(L, -2, "id");
	lua_pushstring(L, frame->GetButtons()->at(idx).GetText().mb_str());
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
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		//t = checkalias(L);
		b = checkbtn(L);
		c = luaL_checkstring(L, ++index);
		i = frame->GetButtonIndexByLabel(b->name);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetButtons()->at(i).SetAction(c);
		wxStrcpy(b->action, c);
		return 0;
	}
	else
	{
		l = luaL_checkstring(L,index++);
		c = luaL_checkstring(L, index);
		i = frame->GetButtonIndexByLabel(l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetButtons()->at(i).SetAction(c);
	}
	return 0;
}

int luafunc_getacbtn(lua_State *L)
{
const char* name;
str_btn* bt;
int idx;
	MudMainFrame *frame = (MudMainFrame*)wxGetApp().GetFrame();	
	if (lua_type(L,1)==LUA_TUSERDATA)
	{
		bt = checkbtn(L);
		wxString s(bt->name);
		idx = frame->GetButtonIndexByLabel(s);
	}
	else
	{
		name = luaL_checkstring(L, 1);
		idx = frame->GetButtonIndexByLabel(name);
	}
	if (idx==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	lua_pushstring(L, frame->GetButtons()->at(idx).GetAction().mb_str());
	return 1;
}

int luafunc_sellabelbtn(lua_State *L)
{
const char* l;
const char* c;
str_btn* b;
int i, index=1;
	
	MudMainFrame *frame = wxGetApp().GetFrame();
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		//t = checkalias(L);
		b = checkbtn(L);
		c = luaL_checkstring(L, ++index);
		i = frame->GetButtonIndexByLabel(b->name);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetButtons()->at(i).SetText(c);
		wxStrcpy(b->text, c);
		return 0;
	}
	else
	{
		l = luaL_checkstring(L,index++);
		c = luaL_checkstring(L, index);
		i = frame->GetButtonIndexByLabel(l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetButtons()->at(i).SetText(c);
		wxAuiToolBar* tb = (wxAuiToolBar*)frame->GetButtons()->at(i).GetParent();
		tb->SetToolLabel(frame->GetButtons()->at(i).GetId(), c);
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
	if (lua_type(L, index)==LUA_TUSERDATA)
	{
		//t = checkalias(L);
		b = checkbtn(L);
		bmap = luaL_checkstring(L, ++index);
		i = frame->GetButtonIndexByLabel(b->name);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetButtons()->at(i).SetBitmap(bmap);
		wxStrcpy(b->text, bmap);
		return 0;
	}
	else
	{
		l = luaL_checkstring(L,index++);
		bmap = luaL_checkstring(L, index);
		i = frame->GetButtonIndexByLabel(l);
		if (i==-1)
		{
			lua_pushnil(L);
			return 1;
		}
		frame->GetButtons()->at(i).SetBitmap(bmap);
		wxAuiToolBar* tb = (wxAuiToolBar*)frame->GetButtons()->at(i).GetParent();
		wxBitmap bt;
		wxSetWorkingDirectory(frame->GetGlobalOptions()->GetImagesDir());
		bt.LoadFile(bmap, wxBITMAP_TYPE_XPM);
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
	//cc = luaL_checkstring(L,1);
	if (lua_type(L,index)==LUA_TUSERDATA)
	{
		bt = checkbtn(L);
		i = frame->GetButtonIndexByLabel(bt->name);
	}
	else
	{
		cc = luaL_checkstring(L,index);
		i = frame->GetButtonIndexByLabel(cc);
	}
	if (i==-1)
	{
		lua_pushnil(L);
		return 1;
	}
	else
	{
		wxString command= frame->GetButtons()->at(i).GetAction();
		int state = frame->m_child->GetParseState();
		frame->m_child->SetParseState(0);//HAVE_TEXT
		frame->m_input->Parse(command, false);
		frame->m_child->SetParseState(state);
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
		frame->m_child->Msg(_("Database file does not exist!"));
		return 0;
	}
	wxString f(file);
	rc = sqlite3_open(f.ToUTF8(), &db);
	if (rc!= SQLITE_OK)
	{
		error = (char*)sqlite3_errmsg(db);
		frame->m_child->Msg(error);
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
	class MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	db = (sqlite3*)lua_touserdata(L, 1);
	if (!db)
		return 0;
	sql = lua_tostring(L,2);
	int rc = sqlite3_exec(db, sql, NULL, NULL, &error);
	if (rc!=SQLITE_OK)
		{
		frame->m_child->Msg(error);
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
	class MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
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
		frame->m_child->Msg(error);
		sqlite3_free(error);
		return 0;
	}
	return 0;
}

int luafunc_columnsdb(lua_State *L)
{
	sqlite3* db;
	sqlite3_stmt* stmt;
	class MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
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
		lua_pushnumber(L, c);
		sqlite3_finalize(stmt);
		return 2;
	}
	return 0;
}

int luafunc_resultdb(lua_State *L)
{
	sqlite3* db;
	
	class MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
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
		frame->m_child->Msg(error);
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
		lua_pushnumber(L, rows);
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
	MudWindow *mw = wxGetApp().GetChild();
	bool b = lua_toboolean(L,1) ? true : false;
	mw->SetMXP(b);
	//mw->SetMXP((bool)lua_toboolean(L,1));
	return 0;
}

int luafunc_parsemxp(lua_State *L)
{
	const char *msg;
	msg = luaL_checkstring(L, 1);
	MudWindow *mw = wxGetApp().GetChild();
	mw->ParseBufferMXP(wxString(msg).char_str());
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
	MudWindow *mw = (MudWindow*)MudWindow::FindWindowByName(win);
	
	if (!mw)
		return 0;
	mw->ParseBufferMXP(wxString(msg).char_str());
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
	text = luaL_checkstring(L,1);
	link = luaL_checkstring(L,2);
	hint = luaL_optstring(L,3,text);
	l<<"<send hint=\""<<hint<<"\" href=\""<<link<<"\">"<<text<<"</send>";
	MudWindow *mw = wxGetApp().GetChild();
	if (!mw)
		return 0;
	mw->ParseBufferMXP(l.char_str());
	mw->Refresh();
	mw->Update();
	return 0;
}

int luafunc_setmsp(lua_State *L)
{
	MudWindow *mw = wxGetApp().GetChild();
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
	if (!frame->m_child->GetSock())
		return 0;
	if (frame->m_child->GetSock()->IsConnected())
		frame->m_child->GetSock()->Write(mes, wxStrlen(mes));
	else if (frame->IsVerbose())
	{
		frame->m_child->Msg(_("Client is not connected!"), 3);
	}
	return 0;
}

//#endif
