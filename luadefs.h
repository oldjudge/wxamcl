#ifndef amcLua_H
#define amcLua_H

//#define luaL_doresume(L, fn) (luaL_loadfile(L, fn) || lua_resume(L, 0)) 5.1.4
#define luaL_doresume(L, fn) (luaL_loadfile(L, fn) || lua_resume(L, NULL, 0))
//amc namespace functions
#define checkaction(L) (str_ac*)luaL_checkudata(L, 1, "wxamcl.mta")
#define checkalias(L) (str_al*)luaL_checkudata(L, 1, "wxamcl.mtal")
#define checkvar(L) (str_var*)luaL_checkudata(L, 1, "wxamcl.mtv")
#define checktimer(L) (str_timer*)luaL_checkudata(L, 1, "wxamcl.mtt")
#define checkhk(L) (str_hk*)luaL_checkudata(L, 1, "wxamcl.mthk")
#define checkbtn(L) (str_btn*)luaL_checkudata(L, 1, "wxamcl.mtbtn");
#define checklist(L) (str_lst*)luaL_checkudata(L, 1, "wxamcl.mtll");
int luafunc_createwindow(lua_State *L);
int luafunc_hidewindow(lua_State *L);
int luafunc_showwindow(lua_State *L);
int luafunc_captionwindow(lua_State *L);
int luafunc_floatwindow(lua_State *L);
int luafunc_dockwindow(lua_State *L);
int luafunc_clearwindow(lua_State *L);
int luafunc_destroywindow(lua_State *L);
int luafunc_destroynb(lua_State *L);
int luafunc_destroyamcwindow(lua_State *L);
int luafunc_setbackground(lua_State *L);
int luafunc_createnb(lua_State *L);
int luafunc_addpagenb(lua_State *L);
int luafunc_createtoolbar(lua_State *L);
int luafunc_addbutton(lua_State *L);
int luafunc_exec(lua_State *L);
int luafunc_send(lua_State *L);
int luafunc_echo(lua_State *L);
int luafunc_echowin(lua_State *L);
int luafunc_color(lua_State *L);
int luafunc_colorwin(lua_State *L);
int luafunc_colorall(lua_State *L);
int luafunc_colorline(lua_State *L);
int luafunc_colorword(lua_State *L);
int luafunc_replacetext(lua_State *L);
int luafunc_getlinenr(lua_State *L);
int luafunc_scroll(lua_State *L);
int luafunc_loadprofile(lua_State *L);
int luafunc_convertprofile(lua_State *L);
int luafunc_wait(lua_State *L);
int luafunc_waitfor(lua_State *L);
int luafunc_gag(lua_State *L);
int luafunc_drawcircle(lua_State *L);
int luafunc_drawtext(lua_State *L);
int luafunc_drawsquare(lua_State *L);
int luafunc_drawline(lua_State *L);
int luafunc_drawbitmap(lua_State *L);
int luafunc_clear(lua_State *L);
int luafunc_refresh(lua_State *L);
int luafunc_settip(lua_State *L);
int luafunc_createamcwin(lua_State *L);
int luafunc_amcwinsize(lua_State *L);
int luafunc_registerlefthandler(lua_State *L);
int luafunc_registerwheelhandler(lua_State *L);
int luafunc_registerrighthandler(lua_State *L);
int luafunc_registermovehandler(lua_State *L);
int luafunc_seteventfile(lua_State *L);
int luafunc_mouseevents(lua_State *L);
int luafunc_setfont(lua_State *L);
int luafunc_getline(lua_State *L);
int luafunc_getscript(lua_State *L);
int luafunc_logwin(lua_State *L);
//action
int luafunc_newaction(lua_State *L);
int luafunc_getaction(lua_State *L);
int luafunc_deleteaction(lua_State *L);
int luafunc_enableaction(lua_State *L);
int luafunc_getpattern(lua_State *L);
int luafunc_setpattern(lua_State *L);
int luafunc_getac(lua_State *L);
int luafunc_setac(lua_State *L);
int luafunc_getpriority(lua_State *L);
int luafunc_setpriority(lua_State *L);
int luafunc_getcolmatch(lua_State *L);
int luafunc_setcolmatch(lua_State *L);
int luafunc_enabletriggers(lua_State *L);
int luafunc_disabletriggers(lua_State *L);
int luafunc_getallactions(lua_State *L);
int luafunc_actiontostring(lua_State *L);
int luafunc_exectr(lua_State *L);
int luafunc_enabletrgroup(lua_State *L);
int luafunc_deltrgroup(lua_State *L);
int luafunc_gettrgroup(lua_State *L);
int luafunc_gettruserdata(lua_State *L);
//alias
int luafunc_newalias(lua_State *L);
int luafunc_newalias1(lua_State *L);//for amc.alias....
int luafunc_getalias(lua_State *L);
int luafunc_deletealias(lua_State *L);
int luafunc_enablealias(lua_State *L);
int luafunc_getalaction(lua_State *L);
int luafunc_setalaction(lua_State *L);
int luafunc_getallalias(lua_State *L);
int luafunc_deletegroup(lua_State *L);
int luafunc_enablegroup(lua_State *L);
int luafunc_aliastostring(lua_State *L);
//hotkey
int luafunc_newhk(lua_State *L);
int luafunc_gethk(lua_State *L);
int luafunc_delhk(lua_State *L);
int luafunc_gethkaction(lua_State *L);
int luafunc_sethkaction(lua_State *L);
int luafunc_enablehk(lua_State *L);
int luafunc_deletehkgroup(lua_State *L);
int luafunc_exechk(lua_State *L);
int luafunc_getallhk(lua_State *L);
int luafunc_enablehkgroup(lua_State *L);
//var
int luafunc_newvar(lua_State *L);
int luafunc_newvar1(lua_State *L);
int luafunc_getvar(lua_State *L);
int luafunc_setvar(lua_State *L);
int luafunc_delvar(lua_State *L);
int luafunc_enablevar(lua_State *L);
int luafunc_getallvar(lua_State *L);
int luafunc_delvargroup(lua_State *L);
int luafunc_enablevargroup(lua_State *L);
//list
int luafunc_newlist(lua_State *L);
int luafunc_getlist(lua_State *L);
int luafunc_getitemat(lua_State *L);
int luafunc_additem(lua_State *L);
int luafunc_delallitems(lua_State *L);
int luafunc_dellist(lua_State *L);
int luafunc_delitemat(lua_State *L);
int luafunc_delitem(lua_State *L);
int luafunc_contains(lua_State *L);
int luafunc_getsize(lua_State *L);
int luafunc_enablelistgroup(lua_State *L);
int luafunc_getalllist(lua_State *L);
int luafunc_dellistgroup(lua_State *L);
//timer
int luafunc_newtimer(lua_State *L);
int luafunc_deltimer(lua_State *L);
int luafunc_starttimer(lua_State *L);
int luafunc_stoptimer(lua_State *L);
int luafunc_enabletimer(lua_State *L);
//gauge
int luafunc_gauge(lua_State *L);
int luafunc_newgauge(lua_State *L);
int luafunc_sizegauge(lua_State *L);
int luafunc_colorgauge(lua_State *L);
int luafunc_creategaugewin(lua_State *L);
int luafunc_setgaugelabel(lua_State *L);
int luafunc_deletegauge(lua_State *L);
int luafunc_setstyle(lua_State *L);
int luafunc_settextpos(lua_State *L);
int luafunc_setshowvalue(lua_State *L);
//button
int luafunc_newbtn(lua_State *L);
int luafunc_delbtn(lua_State *L);
int luafunc_getbtn(lua_State *L);
int luafunc_setacbtn(lua_State *L);
int luafunc_getacbtn(lua_State *L);
int luafunc_sellabelbtn(lua_State *L);
int luafunc_setbitmap(lua_State *L);
int luafunc_pressbtn(lua_State *L);
//sqlite3
int luafunc_newdb(lua_State *L);
int luafunc_execdb(lua_State *L);
int luafunc_closedb(lua_State *L);
int luafunc_columnsdb(lua_State *L);
int luafunc_resultdb(lua_State *L);
int luafunc_insertdb(lua_State *L);
//mxp script stuff
int luafunc_setmxp(lua_State *L);
int luafunc_parsemxp(lua_State *L);
int luafunc_parsemxpwin(lua_State *L);
int luafunc_linkmxp(lua_State *L);
//msp script stuff
int luafunc_setmsp(lua_State *L);
//
int luafunc_sendgmcp(lua_State *L);

int luaopen_amc(lua_State *L);
LUAMOD_API int luaopen2_amc(lua_State *L);

static const struct luaL_Reg amclib_f [] = {
	{"createwindow", luafunc_createwindow},
	{"hidewindow", luafunc_hidewindow},
	{"showwindow", luafunc_showwindow},
	{"caption", luafunc_captionwindow},
	{"floatwindow", luafunc_floatwindow},
	{"dockwindow", luafunc_dockwindow},
	{"clearwindow", luafunc_clearwindow},
	{"destroywindow", luafunc_destroywindow},
	{"destroyamcwindow", luafunc_destroyamcwindow},
	{"destroynb", luafunc_destroynb},
	{"setbackground", luafunc_setbackground},
	{"createnb", luafunc_createnb},
	{"addpage", luafunc_addpagenb},
	{"createtoolbar", luafunc_createtoolbar},
	{"addbutton", luafunc_addbutton},
	{"execute", luafunc_exec},
	{"send", luafunc_send},
	{"echo", luafunc_echo},
	{"echowin", luafunc_echowin},
	{"color", luafunc_color},
	{"colorwin", luafunc_colorwin},
	{"substitute", luafunc_replacetext},
	{"loadprofile", luafunc_loadprofile},
	{"convertprofile", luafunc_convertprofile},
	{"wait", luafunc_wait},
	{"waitfor", luafunc_waitfor},
	{"colorall", luafunc_colorall},
	{"colorline", luafunc_colorline},
	{"colorword", luafunc_colorword},
	{"getlinenumber", luafunc_getlinenr},
	{"scroll", luafunc_scroll},
	{"gag", luafunc_gag},
	//{"drawcircle", luafunc_drawcircle},
	//{"drawtext", luafunc_drawtext},
	{"createamcwin", luafunc_createamcwin},
	{"setlefthandler", luafunc_registerlefthandler},
	{"setrighthandler", luafunc_registerrighthandler},
	{"setwheelhandler", luafunc_registerwheelhandler},
	{"setmovehandler", luafunc_registermovehandler},
	{"seteventfile", luafunc_seteventfile},
	{"mouseevents", luafunc_mouseevents},
	{"getline", luafunc_getline},
	{"getscriptsign", luafunc_getscript},
	{"logwin", luafunc_logwin},
	
	//msp stuff
	{"setmsp", luafunc_setmsp},
	
	{NULL, NULL}
};

static const struct luaL_Reg amclib_m [] = {
	//{wxT("__newindex"), (lua_CFunction)luafunc_setactionprop},
	//{wxT("__index"), (lua_CFunction)luafunc_getaction},
	{"__tostring", luafunc_actiontostring},
	{NULL, NULL}
};

static const struct luaL_Reg amclib_al [] = {
	{"__tostring", luafunc_aliastostring},
	{NULL, NULL}
};

static const struct luaL_Reg amclib_v [] = {
	//{wxT("__tostring"), luafunc_aliastostring},
	{NULL, NULL}
};

static const struct luaL_Reg amclib_h [] = {
	//{wxT("__tostring"), luafunc_aliastostring},
	{NULL, NULL}
};
//gmcp
static const struct luaL_Reg amclib_gmcp [] = {
	{"send", luafunc_sendgmcp},
	{NULL, NULL}
};

static const struct luaL_Reg amclib_db [] = {
	{"open", luafunc_newdb},
	{"execute", luafunc_execdb},
	{"close", luafunc_closedb},
	{"columns", luafunc_columnsdb},
	{"results", luafunc_resultdb},
	{"insert", luafunc_insertdb},
	{NULL, NULL}
};

const struct luaL_Reg amclib_mxp [] = {
	{"enable", luafunc_setmxp},
	{"echo", luafunc_parsemxp},
	{"echowin", luafunc_parsemxpwin},
	{"link", luafunc_linkmxp},
	{NULL, NULL}
};
static const struct luaL_Reg amclib_alias[] = {
	{"new", luafunc_newalias},
	{"get", luafunc_getalias},
	{"delete", luafunc_deletealias},
	{"enable", luafunc_enablealias},
	{"getaction", luafunc_getalaction},
	{"setaction", luafunc_setalaction},
	{"getall", luafunc_getallalias},
	{"delgroup", luafunc_deletegroup},
	{"enablegroup", luafunc_enablegroup},
	{NULL, NULL}
};

static const struct luaL_Reg amclib_trigger[] = {
	{"new", luafunc_newaction},
	{"get", luafunc_getaction},
	{"delete", luafunc_deleteaction},
	{"enable", luafunc_enableaction},
	{"getpattern", luafunc_getpattern},
	{"setpattern", luafunc_setpattern},
	{"getact", luafunc_getac},
	{"setact", luafunc_setac},
	{"getpriority", luafunc_getpattern},
	{"setpriority", luafunc_setpriority},
	{"getcolmatch", luafunc_getcolmatch},
	{"setcolmatch", luafunc_setcolmatch},
	{"enableall", luafunc_enabletriggers},
	{"disableall", luafunc_disabletriggers},
	{"getall", luafunc_getallactions},
	{"getgroup", luafunc_gettrgroup},
	{"enablegroup", luafunc_enabletrgroup},
	{"delgroup", luafunc_deltrgroup},
	{"execute", luafunc_exectr},
	{"getuserdata", luafunc_gettruserdata},
	{NULL, NULL}
};

int findtrigger(lua_State *L, const char* tr);

static const struct luaL_Reg amclib_gauge [] = {
	{"update", luafunc_gauge},
	{"new", luafunc_newgauge},
	{"setsize", luafunc_sizegauge},
	{"setcolor", luafunc_colorgauge},
	{"createwindow", luafunc_creategaugewin},
	{"setlabel", luafunc_setgaugelabel},
	{"delete", luafunc_deletegauge},
	{"setstyle", luafunc_setstyle},
	{"settextpos", luafunc_settextpos},
	{"showvalue", luafunc_setshowvalue},
	{NULL, NULL}
};

static const struct luaL_Reg amclib_vars[] = {
	{"new", luafunc_newvar},
	{"set", luafunc_setvar},
	{"get", luafunc_getvar},
	{"delete", luafunc_delvar},
	{"enable", luafunc_enablevar},
	{"getall", luafunc_getallvar},
	{"enablegroup", luafunc_enablevargroup},
	{"delgroup", luafunc_delvargroup},
	{NULL, NULL}
};

static const struct luaL_Reg amclib_hk [] = {
	{"new", luafunc_newhk},
	{"get", luafunc_gethk},
	{"delete", luafunc_delhk},
	{"getaction", luafunc_gethkaction},
	{"setaction", luafunc_sethkaction},
	{"enable", luafunc_enablehk},
	{"getall", luafunc_getallhk},
	{"enablegroup", luafunc_enablehkgroup},
	{"delgroup", luafunc_deletehkgroup},
	{"execute", luafunc_exechk},
	{NULL, NULL}
};

static const struct luaL_Reg amclib_list [] = {
	{"new", luafunc_newlist},
	{"get", luafunc_getlist},
	{"getitemat", luafunc_getitemat},
	{"additem", luafunc_additem},
	{"clear", luafunc_delallitems},
	{"delete", luafunc_dellist},
	{"delitemat", luafunc_delitemat},
	{"delitem", luafunc_delitem},
	{"contains", luafunc_contains},
	{"getsize", luafunc_getsize},
	{"getall", luafunc_getalllist},
	{"enablegroup", luafunc_enablelistgroup},
	{"delgroup", luafunc_dellistgroup},
	{NULL, NULL}
};

static const struct luaL_Reg amclib_timers[] = {
	{"new", luafunc_newtimer},
	{"delete", luafunc_deltimer},
	{"start", luafunc_starttimer},
	{"stop", luafunc_stoptimer},
	{"enable", luafunc_enabletimer},
	{NULL, NULL}
};

static const struct luaL_Reg amclib_btn[] = {
	{"new", luafunc_newbtn},
	{"delete", luafunc_delbtn},
	{"get", luafunc_getbtn},
	{"setaction", luafunc_setacbtn},
	{"getaction", luafunc_getacbtn},
	{"setlabel", luafunc_sellabelbtn},
	{"setbitmap", luafunc_setbitmap},
	{"press", luafunc_pressbtn},
	{NULL, NULL}
};

static const struct luaL_Reg amclib_draw[] = {
	{"text", luafunc_drawtext},
	{"circle", luafunc_drawcircle},
	{"square", luafunc_drawsquare},
	{"bitmap", luafunc_drawbitmap},
	{"setfont", luafunc_setfont},
	{"line", luafunc_drawline},
	{"clear", luafunc_clear},
	{"winsize", luafunc_amcwinsize},
	{"refresh", luafunc_refresh},
	{"settip", luafunc_settip},
	{NULL, NULL}

};
//represents Trigger in a C way
struct str_ac {
	char label[100];
	//wxString* label;
	char pattern[2000];
	char action[1000];
	char cla[100];
	int prior;
	int colmatch;
	int lines;
	int count;
	bool on;
	bool send;
};

//represents amcAlias in a C way
struct str_al {
	char alias[100];
	char action[1000];
	char cla[100];
	bool on;
};
//amcHotkey
struct str_hk {
	char name[50];
	long keycode;
	int mod;
	char action[1000];
	char group[100];
	bool on;

};
//amcList
struct str_ll {
	char name[100];
	//wxString name;
	char items[1000][200];
	char cla[100];
	bool on;
};

//amcVar
struct str_var {
	char name[100];
	char value[1000];
	char group[100];
	bool on;
};
//amcTimer
struct str_timer {
	char name[100];
	char action[1000];
	char group[1000];
	float intervall;
	int repeat;
	bool on;
};
//amcButton
struct str_btn {
	char name[100];
	char text[100];
	char action[1000];
	char group[100];
	bool on;
	char tbar[100];
	wxAuiToolBar *tb;
};
//amcMudWindow
struct str_win {
	wxString name;
};

//! \class amcLua
/*!
	represents a Lua interpreter in wxAmc
*/
class amcLua
{
public:
	amcLua();
	//amcLua(MudWindow *mw);
	~amcLua();
	struct lua_State* GetLuaState() {return m_L;} /*!< return the Lua state */
	void RegisterFunc(wxString s, lua_CFunction f(lua_State*));
	int DoString(wxString s); /*!< lua_dostring wrapper */
	int DoFile(wxString s); /*!< lua_dofile wrapper */
	int DoFile(const char* s); /*!< lua_dofile wrapper */
	int DoResume(wxString s);
	void GetGlobal(wxString s); /*!< lua_getglobal wrapper */
	int GetObjectLen();
	void GetField(int idx, wxString s);
	void RawGeti(int idx, int n);
	int GetInt(int idx);
	long GetLong(int idx);
	float GetFloat(int idx);
	bool GetBoolean(int idx);
	wxString GetwxString(int idx);
	wxString GetUTF8String(int idx);
	const char* GetString(int idx);
	void SetGlobal(wxString s);
	void SetGlobal(const char* s);
	void SetTop(int idx);
	void PushString(wxString s);
	void PushString(const char* s);
	void PushLString(const char* s, int len);
	void PushInt(int i);
	void GetTable(int idx);
	void Pop(int idx);
	int GetTop();
	int Call(int args);/*!< lua_pcall wrapper */
	int GetStringLen() {return m_len;}
	
private:
	struct lua_State* m_L; /*!< Lua state for amcLua */
	int m_len; /*string len for pushed string*/
};

//lua5.3
#define luaL_optint luaL_optinteger
#define luaL_checkint luaL_checkinteger

#endif
