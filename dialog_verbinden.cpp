#include "main.h"
#include "dialog_verbinden.h"

dlg_charconn::dlg_charconn( wxWindow* parent )
:
connectdlg( parent )
{
	m_frame = (MudMainFrame*)parent;
	m_lastselection=-1;
	FillList();
}

void dlg_charconn::OnInit( wxInitDialogEvent& event )
{
	// TODO: Implement OnInit
}

void dlg_charconn::OnItemSelected( wxListEvent& event )
{
	m_lastselection = event.GetIndex();
	m_charname->SetValue(m_frame->GetHosts()->at(m_lastselection).GetCharName());
	m_pw->SetValue(m_frame->GetHosts()->at(m_lastselection).GetPwd());
	m_mudname->SetValue(m_frame->GetHosts()->at(m_lastselection).GetMudName());
	m_hostname->SetValue(m_frame->GetHosts()->at(m_lastselection).GetHostName());
	m_ip->SetValue(m_frame->GetHosts()->at(m_lastselection).GetIPString());
	m_port->SetValue(m_frame->GetHosts()->at(m_lastselection).GetPort());
	wxString file = m_frame->GetHosts()->at(m_lastselection).GetProfileFile();
	m_file->SetPath(m_frame->GetHosts()->at(m_lastselection).GetProfileFile());
}

void dlg_charconn::OnItemActivate( wxListEvent& event )
{
	m_lastselection = event.GetIndex();
	EndModal(wxID_OK);
}

void dlg_charconn::OnAdd( wxCommandEvent& event )
{
	amchost ahost;
	ahost.SetCharName(m_charname->GetValue());
	ahost.SetPwd(m_pw->GetValue());
	ahost.SetMudName(m_mudname->GetValue());
	ahost.SetHostName(m_hostname->GetValue());
	long port;
	m_port->GetValue().ToLong(&port);
	ahost.SetPort(port);
	wxString s = m_file->GetPath();
	if (s.empty())
		m_file->SetPath(ahost.GetProfileFile());
	s=ahost.GetProfileFile();
	if (!wxFileName::FileExists(s))
		m_frame->SaveProfile(s);	
	ahost.SetProfileFile(m_file->GetPath());
	if (!wxFileName::FileExists(ahost.GetProfileFile()))
		m_frame->SaveProfile(ahost.GetProfileFile());	
	m_frame->GetHosts()->push_back(ahost);
	FillList();
	m_frame->SaveHosts();

}

void dlg_charconn::OnEdit( wxCommandEvent& event )
{
long idx;

	idx = m_list->GetItemData(m_lastselection);
	m_frame->GetHosts()->at(idx).SetCharName(m_charname->GetValue());
	m_frame->GetHosts()->at(idx).SetPwd(m_pw->GetValue());
	m_frame->GetHosts()->at(idx).SetMudName(m_mudname->GetValue());
	m_frame->GetHosts()->at(idx).SetHostName(m_hostname->GetValue());
	long port;
	m_port->GetValue().ToLong(&port);
	m_frame->GetHosts()->at(idx).SetPort(port);
	m_frame->GetHosts()->at(idx).SetProfileFile(m_file->GetPath());
	FillList();
	m_frame->SaveHosts();
}

void dlg_charconn::OnDelete( wxCommandEvent& event )
{
host_it it;
int i;

	long idx = m_list->GetItemData(m_lastselection);
	for (it=m_frame->GetHosts()->begin(), i=0;i<idx;it++, i++);
	m_frame->GetHosts()->erase(it);
	m_list->DeleteItem(m_lastselection);
	FillList();
	m_frame->SaveHosts();
}

void dlg_charconn::FillList()
{
host_it it;

	m_list->ClearAll();
	m_list->InsertColumn(0, _("Avatar"), wxLIST_FORMAT_LEFT, 100);
	m_list->InsertColumn(1, _("Mud"), wxLIST_FORMAT_LEFT, 100);
	m_list->InsertColumn(2, _("Host"), wxLIST_FORMAT_LEFT, 150);
	m_list->InsertColumn(3, _("Port"), wxLIST_FORMAT_LEFT, 60);
	m_list->InsertColumn(4, _("IP"), wxLIST_FORMAT_LEFT, 150);
	int idx=0;
	for(it=m_frame->GetHosts()->begin();it!=m_frame->GetHosts()->end();it++, idx++)
	{
		m_list->InsertItem(idx, it->GetCharName());
		m_list->SetItem(idx, 1, it->GetMudName());
		m_list->SetItem(idx, 2, it->GetHostName());
		m_list->SetItem(idx, 3, it->GetPort());
		m_list->SetItem(idx, 4, it->GetIPString());
		m_list->SetItemData(idx, idx);//know the index if sorted
	}
}
