#include "main.h"
#include "dialog_tabedit.h"

dlg_tabedit::dlg_tabedit( wxWindow* parent )
:
tablist( parent )
{
	class MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	wxSetWorkingDirectory(frame->GetGlobalOptions()->GetWorkDir());
	m_tabtext->LoadFile(wxT("tabcompletion.txt"));
	//m_tabtext->SetSelection(0,1);
	//m_sdbSizer1OK->SetFocus();
	m_tabtext->SetInsertionPoint(m_tabtext->GetLastPosition());
	m_tabtext->SetFocus();
}

void dlg_tabedit::OnOk(wxCommandEvent &event)
{
	class MudMainFrame *frame = (MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	wxSetWorkingDirectory(frame->GetGlobalOptions()->GetWorkDir());
	m_tabtext->SaveFile(wxT("tabcompletion.txt"));
	EndModal(wxID_OK);
}
