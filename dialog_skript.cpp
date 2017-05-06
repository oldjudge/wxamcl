#include "main.h"
#include "dialog_skript.h"

dlg_script::dlg_script( wxWindow* parent )
:
scriptedit( parent )
{
	m_scfont->SetSelectedFont(m_sce->GetDefFont());
	MudMainFrame *frame = (MudMainFrame*)GetParent();
	if (frame->m_child->GetFocusOnInput())
		frame->m_child->SetFocusOnInput(false);
}

void dlg_script::OnOk(wxCommandEvent &event)
{
	MudMainFrame *frame = (MudMainFrame*)GetParent();
	frame->m_child->SetFocusOnInput(true);
	this->Destroy();
}

void dlg_script::OnLoadScript(wxCommandEvent& WXUNUSED(event))
{
	MudMainFrame *frame = (MudMainFrame*)GetParent();
	wxString dir = frame->GetGlobalOptions()->GetScriptDir();
	wxSetWorkingDirectory(dir);
	wxString file = wxFileSelector(_("Choose script to load"), dir, wxEmptyString, "lua", _("lua files (*.lua)|*.lua|all files (*.*)|*.*"), wxFD_OPEN, this);
	if (!file.empty())
	{
		m_sce->ClearAll();
	    m_sce->LoadFile(file);
		m_file->SetLabel(file);
		m_sce->EmptyUndoBuffer();
		m_sce->Colourise(0, m_sce->GetLineCount()+1);
		m_sce->EnsureCaretVisible();
		m_sce->DocumentEnd();
		m_sce->SetSTCFocus(true);
		m_sce->SetFocus();
	}

}

void dlg_script::OnSaveAs(wxCommandEvent& WXUNUSED(event))
{
	MudMainFrame *frame = (MudMainFrame*)GetParent();
	wxString dir = frame->GetGlobalOptions()->GetScriptDir();
	wxSetWorkingDirectory(dir);
	wxString file = wxFileSelector(_("Save script"), dir, wxEmptyString, "lua", _("lua files (*.lua)|*.lua|all files (*.*)|*.*"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT, this);
	if (!file.empty())
	{
		m_sce->SaveFile(file);
	}
}

void dlg_script::OnSave(wxCommandEvent& WXUNUSED(event))
{
	MudMainFrame *frame = (MudMainFrame*)GetParent();
	wxString dir = frame->GetGlobalOptions()->GetScriptDir();
	wxSetWorkingDirectory(dir);
	wxString file = m_file->GetLabel();
	if (!file.empty())
	{
		m_sce->SaveFile(file);
	}
}

void dlg_script::OnRunScript(wxCommandEvent& WXUNUSED(event))
{
	MudMainFrame *frame = (MudMainFrame*)GetParent();
	amcLua *aL = frame->m_child->GetLState();
	//int err = aL->DoString(m_sce->GetText().c_str());
	int err = aL->DoString(m_sce->GetText().mb_str());
	if (err)
	{
		wxString s = aL->GetwxString(aL->GetTop());
		frame->m_child->Msg(s.c_str());
		aL->Pop(1);
		return;
	}
}

void dlg_script::OnFontChanged(wxFontPickerEvent &event)
{
	wxFont f = m_scfont->GetSelectedFont();
	wxFont bf = f;
	bf.SetWeight(wxFONTWEIGHT_BOLD);
	if (f.IsOk())
	{
		m_sce->StyleSetFont (wxSTC_STYLE_DEFAULT, f);
		m_sce->StyleSetFont(wxSTC_LUA_WORD, bf);
		m_sce->StyleSetBold(wxSTC_LUA_WORD, true);
		m_sce->StyleSetFont (wxSTC_LUA_DEFAULT, f);
		m_sce->StyleSetFont(wxSTC_LUA_WORD2, f);
		m_sce->StyleSetFont(wxSTC_LUA_WORD3, bf);
		m_sce->StyleSetBold(wxSTC_LUA_WORD3, true);
		m_sce->StyleSetFont(wxSTC_LUA_STRING, f);
		m_sce->StyleSetFont(wxSTC_LUA_CHARACTER, f);
		m_sce->StyleSetFont(wxSTC_LUA_LITERALSTRING, f);
		m_sce->StyleSetFont(wxSTC_LUA_NUMBER, f);
		m_sce->StyleSetFont(wxSTC_LUA_STRINGEOL, f);
		m_sce->StyleSetFont(wxSTC_LUA_OPERATOR, f);
		m_sce->StyleSetFont(wxSTC_LUA_IDENTIFIER, f);
		MudMainFrame *frame = (MudMainFrame*)GetParent();
		frame->SetScriptFont(&f);
		frame->SaveGlobalOptions();
	}
	m_sce->Refresh();
	m_sce->Update();
}
