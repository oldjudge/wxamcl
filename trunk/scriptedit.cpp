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
		wxT("amc.echo amc.echowin amc.gag amc.color amc.colorline amc.colorall amc.scroll \
				amc.getlinenumber amc.execute amc.wait amc.waitfor amc.loadprofile \
				amc.createwindow amc.hidewindow amc.showwindow amc.clearwindow \
				amc.action.new amc.action.get amc.action.delete amc.action.enable amc.action.getpattern amc.action.setpattern \
				amc.action.getact amc.action.setact amc.action.getpriority amc.action.setpriority amc.action.getcolmatch amc.action.setcolmatch \
				amc.action.enableall amc.action.disableall amc.action.getall amc.action.delgroup amc.action.enablegroup \
				amc.alias.new amc.alias.get amc.alias.delete amc.alias.enable amc.alias.getall amc.alias.getaction\
				amc.alias.setaction amc.alias.delgroup amc.alias.enablegroup \
				amc.hk.new amc.hk.delgroup amc.hk.delete amc.hk.enable \
				amc.var.new amc.var.set amc.var.get amc.var.delete amc.var.enable \
				amc.gauge.update amc.gauge.new amc.gauge.setsize amc.gauge.setcolor amc.gauge.createwindow amc.gauge.setlabel \
				amc.timer.new amc.timer.delete amc.timer.start amc.timer.stop amc.timer.enable \
				amc.mxp.enable amc.mxp.echo amc.mxp.echowin \
				amc.list.new amc.list.additem amc.list.clear amc.list.delete amc.list.contains amc.list.delitem amc.list.delitemat \
				amc.gmcp.send \
				amc.db.open amc.db.execute amc.db.columns amc.db.results amc.db.close amc.db.insert \
				amc.draw.text amc.draw.line amc.draw.circle amc.draw.square amc.draw.winsize");
	wxString amcwords =
		wxT("clearwin capstart capend setvar gag help loadprofile func script bscript gagwin connect pwd refreshwin raw capturewin capturenb log htmllog resume test"); 
	
	SetLexer(wxSTC_LEX_LUA);
	
	SetKeyWords(0, luawords);
	SetKeyWords(1, luawords2);
	//SetKeyWords(1, luawords3);
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
	#if defined __WXMSW__
	wxFont font (*f->GetScriptFont());
	wxFont bfont (m_fontsize, wxMODERN, wxNORMAL, wxFONTWEIGHT_BOLD, false, font.GetFaceName());
	#endif
	#if defined __WXGTK__
	wxFont font (*f->GetScriptFont());
	wxFont bfont (m_fontsize, wxMODERN, wxNORMAL, wxFONTWEIGHT_BOLD, false, font.GetFaceName());
	#endif
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