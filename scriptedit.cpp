#include "main.h"

BEGIN_EVENT_TABLE (amcScriptEdit, wxStyledTextCtrl)
	EVT_STC_MARGINCLICK (wxID_ANY, amcScriptEdit::OnMarginClick)
END_EVENT_TABLE()

amcScriptEdit::amcScriptEdit(wxWindow *parent,  wxWindowID id,
          const wxPoint &pos, const wxSize &size, long style)
		  : wxStyledTextCtrl (parent, id, pos, size, style)
{

	m_fontsize=9;
	wxString luawords =
		wxT("function end if then do else for in return break while local repeat elseif and or not false true nil require");
	wxString luawords2 =
		wxT("wxamcl.echo wxamcl.echowin wxamcl.gag wxamcl.color wxamcl.colorwin wxamcl.colorline wxamcl.colorword wxamcl.colorall wxamcl.scroll \
				wxamcl.getlinenumber wxamcl.getline wxamcl.execute wxamcl.wait wxamcl.waitfor wxamcl.loadprofile \
				wxamcl.createwindow wxamcl.hidewindow wxamcl.showwindow wxamcl.clearwindow wxamcl.destroywindow\
				wxamcl.action.new wxamcl.action.get wxamcl.action.delete wxamcl.action.enable wxamcl.action.getpattern wxamcl.action.setpattern \
				wxamcl.action.getact wxamcl.action.setact wxamcl.action.getpriority wxamcl.action.setpriority wxamcl.action.getcolmatch wxamcl.action.setcolmatch \
				wxamcl.action.enableall wxamcl.action.disableall wxamcl.action.getall wxamcl.action.delgroup wxamcl.action.enablegroup \
				wxamcl.alias.new wxamcl.alias.get wxamcl.alias.delete wxamcl.alias.enable wxamcl.alias.getall wxamcl.alias.getaction\
				wxamcl.alias.setaction wxamcl.alias.delgroup wxamcl.alias.enablegroup \
				wxamcl.hk.new wxamcl.hk.delgroup wxamcl.hk.delete wxamcl.hk.enable \
				wxamcl.var.new wxamcl.var.set wxamcl.var.get wxamcl.var.delete wxamcl.var.enable \
				wxamcl.gauge.update wxamcl.gauge.new wxamcl.gauge.setsize wxamcl.gauge.setcolor wxamcl.gauge.createwindow wxamcl.gauge.setlabel \
				wxamcl.timer.new wxamcl.timer.delete wxamcl.timer.start wxamcl.timer.stop wxamcl.timer.enable \
				wxamcl.button.new, wxamcl.button.delete, wxamcl.button.get, wxamcl.button.setaction, wxamcl.button.getaction, wxamcl.button.press, wxamcl.button.setlabel, wxamcl.button.setbitmap, \
				wxamcl.mxp.enable wxamcl.mxp.echo wxamcl.mxp.echowin \
				wxamcl.list.new wxamcl.list.additem wxamcl.list.clear wxamcl.list.delete wxamcl.list.contains wxamcl.list.delitem wxamcl.list.delitemat \
				wxamcl.gmcp.send \
				wxamcl.db.open wxamcl.db.execute wxamcl.db.columns wxamcl.db.results wxamcl.db.close wxamcl.db.insert \
				wxamcl.draw.text wxamcl.draw.line wxamcl.draw.circle wxamcl.draw.square wxamcl.draw.winsize wxamcl.draw.bitmap wxamcl.draw.setfont wxamcl.draw.clear wxamcl.draw.refresh wxamcl.draw.settip \
				wxamcl.setmsp wxamcl.getscriptsign wxamcl.createamcwin \
				wxamcl.seteventfile wxamcl.mouseevents wxamcl.setlefthandler wxamcl.setrighthandler wxamcl.setwheelhandler wxamcl.setmovehandler \
				wxamcl.mxp.enable wxamcl.mxp.link wxamcl.mxp.echo wxamcl.mxp.echowin");
	wxString amcwords =
		wxT("clearwin capstart capend setvar gag help loadprofile func script bscript gagwin connect pwd refreshwin raw capturewin capturenb log htmllog resume test"); 
	wxString luawords3 =
        ("wxamcl.Action wxamcl.Alias wxamcl.Vars wxamcl.ATCP wxamcl.GMCP wxamcl.MSDP");
    
	SetLexer(wxSTC_LEX_LUA);
	
	SetKeyWords(0, luawords);
	SetKeyWords(1, luawords2);
	SetKeyWords(3, luawords3);
	SetKeyWords(2, amcwords);
	
	SetMarginWidth (0, 0);
	SetMarginType (0, wxSTC_MARGIN_NUMBER);
    StyleSetForeground (wxSTC_STYLE_LINENUMBER, wxColour ("DARK GREY"));
	StyleSetBackground (wxSTC_STYLE_LINENUMBER, *wxLIGHT_GREY);

	 // set margin as unused
    SetMarginType (1, wxSTC_MARGIN_SYMBOL);
    SetMarginWidth (1, 0);
    SetMarginSensitive (1, false);

	// set visibility
    SetVisiblePolicy (wxSTC_VISIBLE_STRICT|wxSTC_VISIBLE_SLOP, 1);
    SetXCaretPolicy (wxSTC_CARET_EVEN|wxSTC_VISIBLE_STRICT|wxSTC_CARET_SLOP, 1);
    SetYCaretPolicy (wxSTC_CARET_EVEN|wxSTC_VISIBLE_STRICT|wxSTC_CARET_SLOP, 1);
		
	SetProperty(wxT("fold.compact"), wxT("0"));
	SetProperty(wxT("fold.comment"), wxT("1"));
	SetProperty(wxT("fold"), wxT("1"));
	SetMarginWidth (2, 0);
	SetMarginType (2, wxSTC_MARGIN_SYMBOL);
    SetMarginMask (2, wxSTC_MASK_FOLDERS);
    StyleSetBackground (2, *wxWHITE);
    SetMarginSensitive (2, true);
	
	SetMarginWidth(0, 36);
	SetMarginWidth(2, 16);
	// markers
    MarkerDefine (wxSTC_MARKNUM_FOLDER,        wxSTC_MARK_BOXPLUS, _T("WHITE"), _T("BLACK"));
    MarkerDefine (wxSTC_MARKNUM_FOLDEROPEN,    wxSTC_MARK_BOXMINUS, _T("WHITE"), _T("BLACK"));
    MarkerDefine (wxSTC_MARKNUM_FOLDERSUB,     wxSTC_MARK_VLINE,     _T("WHITE"), _T("BLACK"));
    MarkerDefine (wxSTC_MARKNUM_FOLDEREND,     wxSTC_MARK_BOXPLUSCONNECTED, _T("WHITE"), _T("BLACK"));
    MarkerDefine (wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUSCONNECTED, _T("WHITE"), _T("WHITE"));
    MarkerDefine (wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_TCORNER,     _T("WHITE"), _T("BLACK"));
    MarkerDefine (wxSTC_MARKNUM_FOLDERTAIL,    wxSTC_MARK_LCORNER,     _T("WHITE"), _T("BLACK"));
	SetFoldFlags (wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED |
                  wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);
	MudMainFrame *f = wxGetApp().GetFrame();
	//#if defined __WXMSW__
	wxFont font (*f->GetScriptFont());
	wxFont bfont (m_fontsize, wxMODERN, wxNORMAL, wxFONTWEIGHT_BOLD, false, font.GetFaceName());
	//#endif
	/*#if defined __WXGTK_
	wxFont font (*f->GetScriptFont());
	wxFont bfont (m_fontsize, wxMODERN, wxNORMAL, wxFONTWEIGHT_BOLD, false, font.GetFaceName());
	#endif
	#if defined __WXOSX
	wxFont font (*f->GetScriptFont());
	wxFont bfont (m_fontsize, wxMODERN, wxNORMAL, wxFONTWEIGHT_BOLD, false, font.GetFaceName());
	#endif*/
	m_font = font;
    StyleSetFont (wxSTC_STYLE_DEFAULT, m_font);
    StyleSetForeground (wxSTC_STYLE_DEFAULT, *wxBLACK);
    StyleSetBackground (wxSTC_STYLE_DEFAULT, *wxWHITE);
	//StyleSetBold(wxSTC_STYLE_DEFAULT, true);
	StyleSetForeground(wxSTC_STYLE_INDENTGUIDE, wxColour ("DARK GREY"));
	
    // set spaces and indention
    SetTabWidth (4);
	SetUseTabs (false);
    SetTabIndents (true);
    SetBackSpaceUnIndents (true);
	//Set Lua styles
	
	StyleSetFont (wxSTC_LUA_DEFAULT, m_font);
    StyleSetForeground (wxSTC_LUA_DEFAULT, *wxBLACK);
    //StyleSetBackground (wxSTC_LUA_DEFAULT, *wxWHITE);
	StyleSetForeground(wxSTC_LUA_COMMENTLINE, wxColour (wxT("FOREST GREEN")));
	StyleSetForeground(wxSTC_LUA_COMMENT, wxColour (wxT("FOREST GREEN")));
	StyleSetForeground(wxSTC_LUA_COMMENTDOC, wxColour (wxT("FOREST GREEN")));
	StyleSetForeground(wxSTC_LUA_PREPROCESSOR, wxColour (wxT("BLUE")));
	StyleSetFont(wxSTC_LUA_WORD, bfont);
	StyleSetBold(wxSTC_LUA_WORD, true);
	StyleSetForeground(wxSTC_LUA_WORD, wxColour ("BLUE"));
	StyleSetFont(wxSTC_LUA_WORD2, m_font);
	StyleSetForeground(wxSTC_LUA_WORD2, wxColour ("BLUE"));
	StyleSetForeground(wxSTC_LUA_WORD3, wxColour ("MEDIUM BLUE"));
	StyleSetFont(wxSTC_LUA_WORD3, bfont);
	StyleSetBold(wxSTC_LUA_WORD3, true);
    StyleSetForeground(wxSTC_LUA_WORD4, wxColour ("KHAKI"));
    StyleSetFont(wxSTC_LUA_WORD4, bfont);
    StyleSetBold(wxSTC_LUA_WORD4, true);
	StyleSetFont(wxSTC_LUA_STRING, m_font);
	StyleSetForeground(wxSTC_LUA_STRING, wxColour ("RED"));
	StyleSetFont(wxSTC_LUA_CHARACTER, m_font);
	StyleSetForeground(wxSTC_LUA_CHARACTER, wxColour (wxT("RED")));
	StyleSetFont(wxSTC_LUA_LITERALSTRING, m_font);
	StyleSetForeground(wxSTC_LUA_LITERALSTRING, wxColour (wxT("ORANGE RED")));
	StyleSetFont(wxSTC_LUA_NUMBER, m_font);
	StyleSetForeground(wxSTC_LUA_NUMBER, wxColour (wxT("SIENNA")));
	StyleSetFont(wxSTC_LUA_STRINGEOL, m_font);
	StyleSetForeground(wxSTC_LUA_STRINGEOL, wxColour (wxT("SIENNA")));
	StyleSetFont(wxSTC_LUA_OPERATOR, m_font);
	StyleSetForeground(wxSTC_LUA_OPERATOR, wxColour (wxT("DARK ORCHID")));
	StyleSetFont(wxSTC_LUA_IDENTIFIER, m_font);
	StyleSetForeground(wxSTC_LUA_IDENTIFIER, wxColour (wxT("DARK ORCHID")));
	SetViewWhiteSpace(false);
	SetCurrentPos(0);
}

amcScriptEdit::~amcScriptEdit()
{
}

//! misc
void amcScriptEdit::OnMarginClick (wxStyledTextEvent &event) {
    if (event.GetMargin() == 2) {
        int lineClick = LineFromPosition (event.GetPosition());
        int levelClick = GetFoldLevel (lineClick);
        if ((levelClick & wxSTC_FOLDLEVELHEADERFLAG) > 0) {
            ToggleFold (lineClick);
        }
    }
	event.Skip();
}
