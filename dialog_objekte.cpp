#include "main.h"
#include "dialog_objekte.h"

//#if defined __WXGTK__
#include "root.xpm"
#include "group.xpm"
#include "action.xpm"
#include "script.xpm"
//#endif

int dlg_obj::m_page = 0;

dlg_obj::dlg_obj( wxWindow* parent )
:
ObjDlg( parent )
{
	m_frame = (MudMainFrame*)parent;
	m_data = false;
	m_index = m_hkindex = m_vindex = m_lindex = m_tindex = -1;
	//Fill the tree control
	wxImageList *il = new wxImageList(16,16);
	//wxIcon root(wxICON(root1));
	//wxIcon group(wxICON(group1));
	//wxIcon action(wxICON(action1));
	wxIcon root(root1_xpm);
	#ifdef __WXMSW__
		SetWindowTheme((HWND)m_tree->GetHandle(), L"Explorer", NULL);
		SetWindowTheme((HWND)m_pattern->GetHandle(), L"Explorer", NULL); 
		SetWindowTheme((HWND)m_action->GetHandle(), L"Explorer", NULL);
		SetWindowTheme((HWND)m_treeCtrl3->GetHandle(), L"Explorer", NULL);
		SetWindowTheme((HWND)m_gaugew->GetHandle(), L"Explorer", NULL);
	#endif
	wxIcon group(group1_xpm);
	wxIcon action(action1_xpm);
	//int x = action.GetHeight();
	//int y = action.GetWidth();
	//il->Add(wxArtProvider::GetBitmap(wxART_FOLDER));
	//il->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE));
	//il->Add(wxArtProvider::GetBitmap(wxART_EXECUTABLE_FILE));
	il->Add(root);
	il->Add(group);
	il->Add(action);
	m_tree->AssignImageList(il);
	m_listalias->InsertColumn(0, _("Alias"), wxLIST_FORMAT_LEFT, 150);
	m_listalias->InsertColumn(1, _("Action"), wxLIST_FORMAT_LEFT, 300);
	m_listalias->InsertColumn(2, _("Group"), wxLIST_FORMAT_LEFT, -1);
	m_listhkey->InsertColumn(0, _("Hotkey"), wxLIST_FORMAT_LEFT, 150);
	m_listhkey->InsertColumn(1, _("Action"), wxLIST_FORMAT_LEFT, 300);
	m_listhkey->InsertColumn(2, _("Group"), wxLIST_FORMAT_LEFT, -1);
	m_listvar->InsertColumn(0, _("Variable"), wxLIST_FORMAT_LEFT, 150);
	m_listvar->InsertColumn(1, _("Value"), wxLIST_FORMAT_LEFT, 300);
	m_listvar->InsertColumn(2, _("Group"), wxLIST_FORMAT_LEFT, -1);
	m_listlist->InsertColumn(0, _("List"), wxLIST_FORMAT_LEFT, 150);
	m_listlist->InsertColumn(1, _("Items"), wxLIST_FORMAT_LEFT, 300);
	m_listlist->InsertColumn(2, _("Group"), wxLIST_FORMAT_LEFT, -1);
	m_timerlist->InsertColumn(0, _("Timer"), wxLIST_FORMAT_LEFT, 150);
	m_timerlist->InsertColumn(1, _("Action"), wxLIST_FORMAT_LEFT, 300);
	m_timerlist->InsertColumn(2, _("Group"), wxLIST_FORMAT_LEFT, -1);
	BuildTree();
	BuildAlias();
	BuildHotkeys();
	BuildVars();
	BuildLists();
	BuildTimers();
	BuildGaugeTree();
	BuildButtons();
	m_onoff->SetValue(true);
	m_onoff->SetLabel(_("Group active"));
	m_key = _("None");
	m_notebook->SetSelection(m_page);
	
	m_s = m_oldactiongroup = wxEmptyString;
	m_notebook->GetCurrentPage()->SetFocus();
	
}

void dlg_obj::OnPageChanged( wxNotebookEvent& event )
{
	m_page = event.GetSelection();
	if (m_page==6)//gauges
	{
		v_it iter;
		m_var1->Clear();
		m_var2->Clear();
		for (iter = m_frame->m_actwindow->GetVars()->begin(); iter!= m_frame->m_actwindow->GetVars()->end(); iter++)
		{
			m_var1->Append(iter->GetName());
			m_var2->Append(iter->GetName());
		}
	}

	event.Skip();
}

void dlg_obj::BuildTree()
{
s_it it;
tr_it iter;

	m_tree->DeleteAllItems();
	wxString msg;
	msg<<"Actions ("<<m_frame->m_actwindow->GetTrigger()->size()<<")";
	//m_tree->AddRoot(wxString::Format(_("Actions (%d)"), m_frame->GetTrigger()->size()),0,0);
	m_tree->AddRoot(msg,0,0);
	m_class->Clear();
	m_class->Append("default");

	for (it = Trigger::GetTriggerClasses()->begin(); it!=Trigger::GetTriggerClasses()->end(); it++)
	{
		wxTreeItemId id = m_tree->AppendItem(m_tree->GetRootItem(), *it, 1, 1);
		for (iter = m_frame->m_actwindow->GetTrigger()->begin(); iter!= m_frame->m_actwindow->GetTrigger()->end(); iter++)
		{
			if (iter->GetShow())
			{
				
				if (*it == iter->GetClass())
					m_tree->AppendItem(id, iter->GetLabel(), 2, 2);
			}
		}

	m_class->Append(*it);
	}
	m_tree->ExpandAll();
	
}

void dlg_obj::BuildAlias()
{
al_it iter;
s_it it;

int index=0;

	m_listalias->DeleteAllItems();
	for (iter = m_frame->m_actwindow->GetAlias()->begin(); iter!= m_frame->m_actwindow->GetAlias()->end(); iter++)
		{
			iter->SetIndex(index);
			long tmp = m_listalias->InsertItem(index, iter->GetAlias(),-1);
			m_listalias->SetItemData(tmp, iter->GetIndex());
			m_listalias->SetItem(index, 1, iter->GetAction(), -1);
			m_listalias->SetItem(index++, 2, iter->GetGroup(), -1);
		}
	
	m_groupcombo->Clear();
	m_groupcombo->Append("all");
	for (it = amcAlias::GetAliasGroups()->begin();it != amcAlias::GetAliasGroups()->end();it++)
	{
		m_groupcombo->Append(*it);
	}
}

void dlg_obj::BuildHotkeys()
{
hk_it iter;
s_it it;
int index=0;

	m_listhkey->DeleteAllItems();
	for (iter = m_frame->m_actwindow->GetHotkeys()->begin(); iter!= m_frame->m_actwindow->GetHotkeys()->end(); iter++)
		{
			iter->SetIndex(index);
			long tmp = m_listhkey->InsertItem(index, iter->GetName(),-1);
			m_listhkey->SetItemData(tmp, iter->GetIndex());
			m_listhkey->SetItem(index, 1, iter->GetAction(), -1);
			m_listhkey->SetItem(index++, 2, iter->GetGroup(), -1);
		}
	m_hkcombo->Clear();
	m_hkcombo->Append("all");
	for (it = amcHotkey::GetHotkeyGroups()->begin();it != amcHotkey::GetHotkeyGroups()->end();it++)
	{
		m_hkcombo->Append(*it);
	}
}

void dlg_obj::BuildVars()
{
v_it iter;
s_it it;
int index=0;

	m_listvar->DeleteAllItems();
	for (iter = m_frame->m_actwindow->GetVars()->begin(); iter!= m_frame->m_actwindow->GetVars()->end(); iter++)
		{
			iter->SetIndex(index);
			long tmp = m_listvar->InsertItem(index, iter->GetName(),-1);
			m_listvar->SetItemData(tmp, iter->GetIndex());
			m_listvar->SetItem(index, 1, iter->GetValue(), -1);
			m_listvar->SetItem(index++, 2, iter->GetGroup(), -1);
		}
	m_vargroup->Clear();
	m_vargroup->Append("all");
	for (it = amcVar::GetVarGroups()->begin();it != amcVar::GetVarGroups()->end();it++)
	{
		m_vargroup->Append(*it);
	}
}

void dlg_obj::BuildLists()
{
li_it iter;
s_it it;
int index=0;

	m_listlist->DeleteAllItems();
	for (iter = m_frame->m_actwindow->GetLists()->begin(); iter!= m_frame->m_actwindow->GetLists()->end(); iter++)
		{
			iter->SetIndex(index);
			long tmp = m_listlist->InsertItem(index, iter->GetName(),-1);
			m_listlist->SetItemData(tmp, iter->GetIndex());
			m_listlist->SetItem(index, 1, iter->GetValue(), -1);
			m_listlist->SetItem(index++, 2, iter->GetGroup(), -1);
		}
	m_ligroup->Clear();
	m_ligroup->Append(("all"));
	for (it = amcList::GetListGroups()->begin();it != amcList::GetListGroups()->end();it++)
	{
		m_ligroup->Append(*it);
	}
}

void dlg_obj::BuildTimers()
{
t_it iter;
s_it it;
int index=0;
	m_timerlist->DeleteAllItems();
	for (iter = m_frame->m_actwindow->GetTimers()->begin(); iter!= m_frame->m_actwindow->GetTimers()->end(); iter++)
		{
			if (iter->GetShow())
			{
				iter->SetIdx(index);
				long tmp = m_timerlist->InsertItem(index, iter->GetName(),-1);
				m_timerlist->SetItemData(tmp, iter->GetIdx());
				m_timerlist->SetItem(index, 1, iter->GetAction(), -1);
				m_timerlist->SetItem(index++, 2, iter->GetGroup(), -1);
			}
		}
	m_tigroup->Clear();
	m_tigroup->Append("all");
	for (it = amcTimer::GetTimerGroups()->begin();it != amcTimer::GetTimerGroups()->end();it++)
	{
		m_tigroup->Append(*it);
	}
}

void dlg_obj::BuildGaugeTree()
{
s_it sit;

	m_gaugew->DeleteAllItems();
	m_gaugew->AddRoot(_("Gauge Windows"));

	if (!m_frame->m_actwindow->GetGaugePanes()->empty())
	{
		
		for (sit=m_frame->m_actwindow->GetGaugePanes()->begin();sit!=m_frame->m_actwindow->GetGaugePanes()->end();sit++)
		{
			m_parentw->Append(*sit);
			wxTreeItemId id = m_gaugew->AppendItem(m_gaugew->GetRootItem(), *sit);
			GaugeWindow* gw = (GaugeWindow*)GaugeWindow::FindWindowByName(sit->c_str(), m_frame);
			g_it git;
			for (git=gw->GetGauges()->begin();git!=gw->GetGauges()->end();git++)
			{
				m_gaugew->AppendItem(id, git->GetName());
			}
		}
	}
	#ifndef __WXOSX__
	m_parentw->SetSelection(0);
	#endif
	m_gaugew->ExpandAll();
	//Fill controls with vars
	v_it iter;
	m_var1->Clear();
	m_var2->Clear();
	for (iter = m_frame->m_actwindow->GetVars()->begin(); iter!= m_frame->m_actwindow->GetVars()->end(); iter++)
		{
			m_var1->Append(iter->GetName());
			m_var2->Append(iter->GetName());
		}
	
}



void dlg_obj::BuildButtons()
{
b_it iter;
vector<wxString> list;
vector<wxTreeItemId> id;
	
	m_treeCtrl3->DeleteAllItems();
	m_treeCtrl3->AddRoot(_("Buttons"));
	for (iter = m_frame->m_actwindow->GetButtons()->begin(); iter!= m_frame->m_actwindow->GetButtons()->end(); iter++)
		{
			if (find(list.begin(),list.end(), iter->GetTbName())==list.end())
			{
				list.push_back(iter->GetTbName());
				wxTreeItemId ti = m_treeCtrl3->AppendItem(m_treeCtrl3->GetRootItem(), iter->GetTbName());
				id.push_back(ti);
				
			}
		}
	for (iter = m_frame->m_actwindow->GetButtons()->begin(); iter!= m_frame->m_actwindow->GetButtons()->end(); iter++)
		{
			s_it s;
			int i=0;
			for (s = list.begin();s != list.end();s++, i++)
			{
				if (iter->GetName()=="separator")
					continue;
				if (iter->GetTbName()==*s)
					m_treeCtrl3->AppendItem(id.at(i), iter->GetName());
			}
		}
	m_treeCtrl3->ExpandAll();
}



void dlg_obj::OnInitObjects( wxInitDialogEvent& event )
{
	switch (m_page)
	{
	case 0:
		//m_notebook->SetFocus();
		//m_label->SetFocus();
		m_trigger->SetFocus();
		if (!m_data)
			m_label->SetFocus();
		else
		{
			m_pattern->Freeze();
			m_pattern->Clear();
			m_s.Replace("\r\n", "\n");
			m_pattern->AppendText(m_s);
			m_pattern->ShowPosition(m_pattern->GetLastPosition()-3);
			//m_pattern->ScrollLines(1);
			m_pattern->SetFocus();
			m_pattern->Thaw();
		}
		break;
	case 1:
		m_notebook->SetFocus();
		m_defalias->SetFocus();
		break;
	case 2:
		m_notebook->SetFocus();
		m_hkey->SetFocus();
		break;
	case 3:
		m_notebook->SetFocus();
		m_defvar->SetFocus();
		break;
	case 4:
		m_notebook->SetFocus();
		m_deflist->SetFocus();
		break;
	case 5:
		m_notebook->SetFocus();
		m_deftimer->SetFocus();
		break;
	case 6:
		m_notebook->SetFocus();
		m_gauge->SetFocus();
		break;
	}
}

void dlg_obj::OnTreeSelChanged( wxTreeEvent& event )
{
	int index;
	wxTreeItemId id = event.GetItem();
	
	index = m_frame->m_actwindow->GetTriggerIndexByLabel(m_tree->GetItemText(id));
	if (index==-1)
		return;
	else
	{
		m_label->SetValue(m_frame->m_actwindow->GetTrigger()->at(index).GetLabel());
		m_pattern->SetValue(m_frame->m_actwindow->GetTrigger()->at(index).GetPattern());
		wxString s = m_frame->m_actwindow->GetTrigger()->at(index).GetAction();
		s.Replace(";", "\r\n");
		m_action->SetText(s);
		m_tron->SetValue(m_frame->m_actwindow->GetTrigger()->at(index).IsActive());
		m_sendscript->SetValue(m_frame->m_actwindow->GetTrigger()->at(index).GetSendScript());
		m_prior->SetValue(m_frame->m_actwindow->GetTrigger()->at(index).GetPriority());
		m_lines->SetValue(m_frame->m_actwindow->GetTrigger()->at(index).GetLines());
		if (m_frame->m_actwindow->GetTrigger()->at(index).GetColMatch()==-1)
		{
			m_oncolor->SetValue(false);
			m_amccombo->Disable();
			m_amccombo->SetSelection(0);
		}
		else
		{
			m_oncolor->SetValue(true);
			m_amccombo->Enable();
			m_amccombo->SetSelection(m_frame->m_actwindow->GetTrigger()->at(index).GetColMatch());
			}
		m_matched->SetValue(wxString::Format("%ld", m_frame->m_actwindow->GetTrigger()->at(index).GetMatchCount()));
		m_class->SetStringSelection(m_frame->m_actwindow->GetTrigger()->at(index).GetClass());
		if (m_tron->GetValue())
		{
			m_onoff->SetValue(true);
			m_onoff->SetLabel(_("Group active"));
		}
		else
		{
			m_onoff->SetValue(false);
			m_onoff->SetLabel(_("Group off"));
		}
	}
}

void dlg_obj::OnTriggerOn( wxCommandEvent& event )
{
	wxTreeItemId id = m_tree->GetSelection();
	if (!id.IsOk())
		return;
	int index = m_frame->m_actwindow->GetTriggerIndexByLabel(m_tree->GetItemText(id));
	if (index==-1)
		return;
	else
	{
		m_frame->m_actwindow->GetTrigger()->at(index).SetActive(m_tron->GetValue());
		//m_frame->m_actwindow->SetTriggers(*m_frame->GetTrigger());
	}
}

void dlg_obj::OnSendToScript( wxCommandEvent& event )
{
	wxTreeItemId id = m_tree->GetSelection();
	if (!id.IsOk())
		return;
	int index = m_frame->m_actwindow->GetTriggerIndexByLabel(m_tree->GetItemText(id));
	if (index==-1)
		return;
	else
	{
		m_frame->m_actwindow->GetTrigger()->at(index).SetSendScript(m_sendscript->GetValue());
		//m_frame->m_actwindow->SetTriggers(*m_frame->GetTrigger());
	}

}

void dlg_obj::OnSceditor( wxCommandEvent& event)
{
	dlg_simplescr * sscr = new dlg_simplescr(this);
	wxTreeItemId id = m_tree->GetSelection();
	if (!id.IsOk())
		return;
	int index = m_frame->m_actwindow->GetTriggerIndexByLabel(m_tree->GetItemText(id));
	if (index==-1)
		return;
	else
	{
		wxString s = m_frame->m_actwindow->GetTrigger()->at(index).GetAction();
		s.Replace(";", "\r\n");
		sscr->GetEditor()->SetText(s);
		if (sscr->ShowModal()==wxID_OK)
		{
			s = sscr->GetEditor()->GetText();
			wxString c = m_frame->GetGlobalOptions()->GetSep();
			m_action->SetText(s);
			s.Replace("\r\n", c.c_str());
			m_frame->m_actwindow->GetTrigger()->at(index).SetAction(s);
		}
		sscr->Destroy();
	}
}

void dlg_obj::OnPatternEdit(wxCommandEvent& event)
{
	dlg_simplescr * sscr = new dlg_simplescr(this);
	wxTreeItemId id = m_tree->GetSelection();
	if (!id.IsOk())
		return;
	int index = m_frame->m_actwindow->GetTriggerIndexByLabel(m_tree->GetItemText(id));
	if (index==-1)
		return;
	else
	{
		wxString s = m_frame->m_actwindow->GetTrigger()->at(index).GetPattern();
		//s.Replace(";", "\r\n");
		sscr->GetEditor()->SetText(s);
		if (sscr->ShowModal()==wxID_OK)
		{
			s = sscr->GetEditor()->GetText();
			//wxString c = m_frame->GetGlobalOptions()->GetSep();
			m_pattern->SetValue(s);
			//s.Replace("\r\n", c.c_str());
			m_frame->m_actwindow->GetTrigger()->at(index).SetPattern(s);
		}
		sscr->Destroy();
	}
	//m_frame->m_actwindow->SetTriggers(*m_frame->GetTrigger());
}

void dlg_obj::OnClassToggle( wxCommandEvent& event )
{
tr_it iter;
	wxTreeItemId id = m_tree->GetSelection();
	if (!id.IsOk())
		return;
	int index = m_frame->m_actwindow->GetTriggerIndexByLabel(m_tree->GetItemText(id));
	if (index==-1)
		return;
	else
	{
		wxString s = m_frame->m_actwindow->GetTrigger()->at(index).GetClass();
		if (m_onoff->GetValue())
			m_onoff->SetLabel(_("Group active"));
		else
			m_onoff->SetLabel(_("Group off"));
		for (iter = m_frame->m_actwindow->GetTrigger()->begin(); iter!= m_frame->m_actwindow->GetTrigger()->end(); iter++)
		{
			if (s == iter->GetClass())
			{
				iter->SetActive(m_onoff->GetValue());
				m_tron->SetValue(m_onoff->GetValue());
			}
		}
	}
}

void dlg_obj::OnDelClass( wxCommandEvent& event )
{
	s_it it;

	wxTreeItemId id = m_tree->GetSelection();
	if (!id.IsOk())
		return;
	int index = m_frame->m_actwindow->GetTriggerIndexByLabel(m_tree->GetItemText(id));
	if (index==-1)
		return;
	else
	{
		wxString s = m_frame->m_actwindow->GetTrigger()->at(index).GetClass();
		if (wxMessageBox(_("This will delete all triggers in this group!"), _("Continue?"), wxYES_NO, this)==wxYES)
		{
			for (size_t i=0;i<m_frame->m_actwindow->GetTrigger()->size(); i++)
			{
				if(m_frame->m_actwindow->GetTrigger()->at(i).GetClass()==s)
				{
					m_frame->m_actwindow->GetTrigger()->erase(m_frame->m_actwindow->GetTrigger()->begin()+i--);
				}
			}
			for (it = Trigger::GetTriggerClasses()->begin(); it!=Trigger::GetTriggerClasses()->end(); it++)
			{
				if (*it == s)
				{
					Trigger::GetTriggerClasses()->erase(it);
					break;
				}
			}
		BuildTree();
		}
	}
	//m_frame->m_actwindow->SetTriggers(*m_frame->GetTrigger());
}

void dlg_obj::OnActionAdd( wxCommandEvent& event )
{
tr_it it;

	Trigger tr;
	wxString s = m_label->GetValue();
	for (it=m_frame->m_actwindow->GetTrigger()->begin();it!=m_frame->m_actwindow->GetTrigger()->end();it++)
	{
		if(s==*it)
		{
			wxMessageBox(_("Action labels need to be unique!"), _("Label already exists!"), wxOK, this);
			return;
		}
	}
	tr.SetLabel(s);
	wxString action = m_action->GetText();
	wxString c = m_frame->GetGlobalOptions()->GetSep();
	action.Replace("\r\n", c.c_str());
	tr.SetAction(action);

	tr.SetPattern(m_pattern->GetValue());
	tr.SetActive(m_tron->GetValue());
	tr.SetSendScript(m_sendscript->GetValue());
	tr.SetPriority(m_prior->GetValue());
	tr.SetLines(m_lines->GetValue());
	if (m_class->GetValue()==wxEmptyString)
		tr.SetClass(_("default"));
	else tr.SetClass(m_class->GetValue());
	if (m_oncolor->GetValue())
		tr.SetColMatch(m_amccombo->GetSelection());
	else tr.SetColMatch(-1);
	m_frame->m_actwindow->GetTrigger()->push_back(tr);
	stable_sort(m_frame->m_actwindow->GetTrigger()->begin(), m_frame->m_actwindow->GetTrigger()->end(), greater<class Trigger>());
	BuildTree();
	m_class->SetStringSelection(tr.GetClass());
	
}

void dlg_obj::OnActionEdit( wxCommandEvent& event )
{
tr_it it;

	wxTreeItemId id = m_tree->GetSelection();
	if (!id.IsOk())
		return;
	int index = m_frame->m_actwindow->GetTriggerIndexByLabel(m_tree->GetItemText(id));
	if (index==-1)
		return;
	else
	{
		wxString s = m_label->GetValue();
		for (it=m_frame->m_actwindow->GetTrigger()->begin();it!=m_frame->m_actwindow->GetTrigger()->end();it++)
		{
			if(s==*it && s!=m_frame->m_actwindow->GetTrigger()->at(index).GetLabel())
			{
				wxMessageBox(_("Action labels need to be unique!"), _("Label already exists!"), wxOK, this);
				return;
			}
		}
		m_frame->m_actwindow->GetTrigger()->at(index).SetLabel(s);
		m_tree->SetItemText(id, s);
		m_frame->m_actwindow->GetTrigger()->at(index).SetPattern(m_pattern->GetValue());
		wxString action = m_action->GetText();
		wxString c = m_frame->GetGlobalOptions()->GetSep();
		action.Replace("\r\n", c.c_str());
		m_frame->m_actwindow->GetTrigger()->at(index).SetAction(action);//(m_action->GetValue());
		m_frame->m_actwindow->GetTrigger()->at(index).SetActive(m_tron->GetValue());
		m_frame->m_actwindow->GetTrigger()->at(index).SetSendScript(m_sendscript->GetValue());
		m_frame->m_actwindow->GetTrigger()->at(index).SetPriority(m_prior->GetValue());
		m_frame->m_actwindow->GetTrigger()->at(index).SetLines(m_lines->GetValue());
		m_frame->m_actwindow->GetTrigger()->at(index).SetClass(m_class->GetValue());
		if (m_oncolor->GetValue())
			m_frame->m_actwindow->GetTrigger()->at(index).SetColMatch(m_amccombo->GetSelection());
		else
			m_frame->m_actwindow->GetTrigger()->at(index).SetColMatch(-1);
		stable_sort(m_frame->m_actwindow->GetTrigger()->begin(), m_frame->m_actwindow->GetTrigger()->end(), greater<class Trigger>());
		//BuildTree();
		m_class->SetStringSelection(m_frame->m_actwindow->GetTrigger()->at(index).GetClass());
		m_tree->SetFocus();
		m_tree->SelectItem(id);
	}
	//m_frame->m_actwindow->SetTriggers(*m_frame->GetTrigger());
}

void dlg_obj::OnActionDelete( wxCommandEvent& event )
{
tr_it it;

	wxTreeItemId id = m_tree->GetSelection();
	if (!id.IsOk())
		return;
	int index = m_frame->m_actwindow->GetTriggerIndexByLabel(m_tree->GetItemText(id));
	if (index==-1)
		return;
	else
	{
		it = m_frame->m_actwindow->GetTrigger()->begin()+index;
		//for (it=m_frame->GetTrigger()->begin(), i=0;i<index;it++, i++);
		m_frame->m_actwindow->GetTrigger()->erase(it);
		m_tree->Delete(id);
		stable_sort(m_frame->m_actwindow->GetTrigger()->begin(), m_frame->m_actwindow->GetTrigger()->end(), greater<class Trigger>());
		BuildTree();
	}
	//m_frame->m_actwindow->SetTriggers(*m_frame->GetTrigger());
}

void dlg_obj::OnItemSelected( wxListEvent& event )
{
	//int idx = m_frame->GetAliasIndexByLabel(event.GetText());
	m_index = event.GetIndex();
	if (m_index!=-1)
	{
		m_index = m_listalias->GetItemData(m_index);
	}
	if (m_index==-1)
		return;
	else
	{
		m_defalias->SetValue(m_frame->m_actwindow->GetAlias()->at(m_index).GetAlias());
		m_defaction->SetValue(m_frame->m_actwindow->GetAlias()->at(m_index).GetAction());
		m_groupcombo->SetStringSelection(m_frame->m_actwindow->GetAlias()->at(m_index).GetGroup());
		m_alon->SetValue(m_frame->m_actwindow->GetAlias()->at(m_index).IsActive());
		m_groupon->SetValue(m_frame->m_actwindow->GetAlias()->at(m_index).IsActive());
		if (m_groupon->GetValue())
			m_groupon->SetLabel(_("Group active"));
		else
			m_groupon->SetLabel(_("Group off"));
	}
}

void dlg_obj::OnActionBeginLabelEdit(wxTreeEvent& event)
{
	int index;
	wxTreeItemId id = event.GetItem();
	index = m_frame->m_actwindow->GetTriggerIndexByLabel(m_tree->GetItemText(id));
	if (index==-1)
	{
		if (m_tree->ItemHasChildren(id) && id != m_tree->GetRootItem())
			index = -2;
	if (index==-1)	
		return;
	}
	if (index==-2)
		m_oldactiongroup = event.GetLabel();
}

void dlg_obj::OnActionEndLabelEdit(wxTreeEvent &event)
{
	wxTreeItemId id = event.GetItem();
	int index = m_frame->m_actwindow->GetTriggerIndexByLabel(m_tree->GetItemText(id));
	if (index==-1)
	{
		if (m_tree->ItemHasChildren(id) && id != m_tree->GetRootItem())
			index = -2;
		if (index==-1)	
			return;
	}
	if (index!=-2)
	{
		wxString s = event.GetLabel();
		tr_it it;
		for (it=m_frame->m_actwindow->GetTrigger()->begin();it!=m_frame->m_actwindow->GetTrigger()->end();it++)
		{
			if(s==*it && s!=m_frame->m_actwindow->GetTrigger()->at(index).GetLabel())
			{
				wxMessageBox(_("Action labels need to be unique!"), _("Label already exists!"), wxOK, this);
				return;
			}
		}
		m_frame->m_actwindow->GetTrigger()->at(index).SetLabel(s);
		m_label->SetValue(s);
	}
	//Group name changed
	else if (index==-2)
	{
		s_it it;
		//change the group in all triggers
		for (size_t i=0;i<m_frame->m_actwindow->GetTrigger()->size(); i++)
		{
			if(m_frame->m_actwindow->GetTrigger()->at(i).GetClass()==m_oldactiongroup)
			{
				m_frame->m_actwindow->GetTrigger()->at(i).SetClass(event.GetLabel());
			}
		}
		for (it = Trigger::GetTriggerClasses()->begin(); it!=Trigger::GetTriggerClasses()->end(); it++)
		{
			if (*it == m_oldactiongroup)
			{
				Trigger::GetTriggerClasses()->erase(it);
				break;
			}
		}
	BuildTree();
	}
	//m_frame->m_actwindow->SetTriggers(*m_frame->GetTrigger());
}


void dlg_obj::OnAliasAdd( wxCommandEvent& event )
{
amcAlias al;
al_it it;

	wxString s = m_defalias->GetValue();
	//s.insert(0, wxT('^'));
	if (s.at(0)!='^')
		s = '^' + s;
	if (!s.EndsWith("$"))
		s.append('$');
	for (it=m_frame->m_actwindow->GetAlias()->begin();it!=m_frame->m_actwindow->GetAlias()->end();it++)
	{
		if(s==*it)
		{
			wxMessageBox(_("Alias already exists!"), _("Alias already exists!"), wxOK, this);
			return;
		}
	}
	al.SetAlias(s);
	al.SetAction(m_defaction->GetValue());
	al.SetActive(m_alon->GetValue());
	al.SetGroup(m_groupcombo->GetValue());
	m_frame->m_actwindow->GetAlias()->push_back(al);
	stable_sort(m_frame->m_actwindow->GetAlias()->begin(), m_frame->m_actwindow->GetAlias()->end(), less<class amcAlias>());
	m_frame->luaBuildalias();
	//BuildAlias();
	m_groupcombo->SetStringSelection(al.GetGroup());
	int index=0;
	for (it = m_frame->m_actwindow->GetAlias()->begin(); it!= m_frame->m_actwindow->GetAlias()->end(); it++)
		{
		it->SetIndex(index++);
		}
	wxCommandEvent ev;
	OnGroupChanged(ev);
	//m_frame->m_actwindow->SetAlias(*m_frame->GetAlias());
}

void dlg_obj::OnAliasEdit( wxCommandEvent& event )
{
al_it it;
		
	if (m_index==-1)
		return;
	wxString s = m_defalias->GetValue();
	//s.insert(0, wxT('^'));
	if (s.at(0)!='^')
		s = '^' + s;
	if (!s.EndsWith("$"))
		s.append('$');
	
	wxString l = m_defalias->GetValue();
	for (it=m_frame->m_actwindow->GetAlias()->begin();it!=m_frame->m_actwindow->GetAlias()->end();it++)
	{
		if(l==*it && l!=m_frame->m_actwindow->GetAlias()->at(m_index).GetAlias())
		{
			wxMessageBox(_("Alias already exists!"), _("Alias already exists!"), wxOK, this);
			return;
		}
	}
	m_frame->m_actwindow->GetAlias()->at(m_index).SetAlias(s);
	m_frame->m_actwindow->GetAlias()->at(m_index).SetAction(m_defaction->GetValue());
	m_frame->m_actwindow->GetAlias()->at(m_index).SetActive(m_alon->GetValue());
	m_frame->m_actwindow->GetAlias()->at(m_index).SetGroup(m_groupcombo->GetValue());
	//BuildAlias();
	m_groupcombo->SetStringSelection(m_frame->m_actwindow->GetAlias()->at(m_index).GetGroup());
	wxCommandEvent ev;
	OnGroupChanged(ev);
	//m_frame->m_actwindow->SetAlias(*m_frame->GetAlias());
}

void dlg_obj::OnAliasDelete( wxCommandEvent& event )
{
al_it it;

	if (m_index==-1)
		return;
	else
	{
		it = m_frame->m_actwindow->GetAlias()->begin()+m_index;
		
		m_frame->m_actwindow->GetAlias()->erase(it);
		
		int index=0;
		for (it = m_frame->m_actwindow->GetAlias()->begin(); it!= m_frame->m_actwindow->GetAlias()->end(); it++)
		{
			it->SetIndex(index++);
		}
		wxCommandEvent ev;
		OnGroupChanged(ev);
		//m_frame->m_actwindow->SetAlias(*m_frame->GetAlias());
	}
}

void dlg_obj::OnAliasOn( wxCommandEvent& event )
{
	if (m_index==-1)
		return;
	else
	{
		m_frame->m_actwindow->GetAlias()->at(m_index).SetActive(m_alon->GetValue());
	}
	//m_frame->m_actwindow->SetAlias(*m_frame->GetAlias());
}

void dlg_obj::OnGroupOff( wxCommandEvent& event )
{
al_it iter;
	
	if (m_index==-1)
		return;
	else
	{
		wxString s = m_frame->m_actwindow->GetAlias()->at(m_index).GetGroup();
		if (m_groupon->GetValue())
			m_groupon->SetLabel(_("Group active"));
		else
			m_groupon->SetLabel(_("Group off"));
		for (iter = m_frame->m_actwindow->GetAlias()->begin(); iter!= m_frame->m_actwindow->GetAlias()->end(); iter++)
		{
			if (s == iter->GetGroup())
			{
				iter->SetActive(m_groupon->GetValue());
				m_alon->SetValue(m_groupon->GetValue());
			}
		}
	}
	//m_frame->m_actwindow->SetAlias(*m_frame->GetAlias());

}

void dlg_obj::OnGroupDelete( wxCommandEvent& event)
{
s_it it;

	wxString s = m_groupcombo->GetValue();
	if (m_index==-1 && s == wxEmptyString)
		return;
	else
	{
		if (s == wxEmptyString)
			s = m_frame->m_actwindow->GetAlias()->at(m_index).GetGroup();
		if (wxMessageBox(_("This will delete all aliases in this group!"), _("Continue?"), wxYES_NO, this)==wxYES)
		{
			for (size_t i=0;i<m_frame->m_actwindow->GetAlias()->size(); i++)
			{
				if(m_frame->m_actwindow->GetAlias()->at(i).GetGroup()==s)
				{
					m_frame->m_actwindow->GetAlias()->erase(m_frame->m_actwindow->GetAlias()->begin()+i--);
				}
			}
			for (it = amcAlias::GetAliasGroups()->begin(); it!=amcAlias::GetAliasGroups()->end(); it++)
			{
				if (*it == s)
				{
					amcAlias::GetAliasGroups()->erase(it);
					break;
				}
			}
		BuildAlias();
		//m_frame->m_actwindow->SetAlias(*m_frame->GetAlias());
		}
	}
}

void dlg_obj::OnGroupChanged( wxCommandEvent& event )
{
int index=0;
al_it iter;

	wxString group = m_groupcombo->GetValue();
	if (group == "all")
	{
		BuildAlias();
		return;
	}
	else if (m_alfilter->GetValue())
	{
		m_listalias->DeleteAllItems();
		for (iter = m_frame->m_actwindow->GetAlias()->begin(); iter!= m_frame->m_actwindow->GetAlias()->end(); iter++)
		{
			if (group==iter->GetGroup())
			{
				int idx = m_frame->m_actwindow->GetAliasIndexByLabel(iter->GetAlias());
				long tmp = m_listalias->InsertItem(index, iter->GetAlias(),-1);
				m_listalias->SetItemData(tmp, idx);
				m_listalias->SetItem(index, 1, iter->GetAction(), -1);
				m_listalias->SetItem(index++, 2, iter->GetGroup(), -1);
			}
		}
	}
}

void dlg_obj::OnColourCheck( wxCommandEvent& event )
{
	wxTreeItemId id = m_tree->GetSelection();
	if (!id.IsOk())
		return;
	int index = m_frame->m_actwindow->GetTriggerIndexByLabel(m_tree->GetItemText(id));

	if (m_oncolor->GetValue())
		m_amccombo->Enable();
	else
	{
        m_amccombo->Disable();
		if (index>0)
            m_frame->m_actwindow->GetTrigger()->at(index).SetColMatch(-1);
		m_amccombo->SetSelection(0);
	}
	m_amccombo->Refresh();
}

void dlg_obj::OnHotkeyAdd(wxCommandEvent &event)
{
amcHotkey hk;
hk_it it;

	long keycode = m_hkey->GetHotkey();
	int mods = m_hkey->GetModifier();
	
	hk.SetHotkey(keycode);
	hk.SetMods(mods);
	hk.SetName(m_hkey->GetHkName());
	hk.SetAction(m_hkeyaction->GetValue());
	hk.SetActive(m_hkeyon->GetValue());
	hk.SetGroup(m_hkcombo->GetValue());
	m_frame->m_actwindow->GetHotkeys()->push_back(hk);
	
	
	int index=0;
	for (it = m_frame->m_actwindow->GetHotkeys()->begin(); it!= m_frame->m_actwindow->GetHotkeys()->end(); it++)
	{
		it->SetIndex(index++);
	}
	wxCommandEvent ev;
	OnHkGroupChanged(ev);
	m_hkcombo->SetStringSelection(hk.GetGroup());
	//m_frame->m_actwindow->SetHotkeys(*m_frame->GetHotkeys());
}

void dlg_obj::OnHotkeyEdit( wxCommandEvent& event )
{
hk_it it;
		
	if (m_hkindex==-1)
		return;
	wxString l = m_hkey->GetHkName();
	for (it=m_frame->m_actwindow->GetHotkeys()->begin();it!=m_frame->m_actwindow->GetHotkeys()->end();it++)
	{
		if(l==*it && l!=m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).GetName())
		{
			wxMessageBox(_("Hotkey already exists!"), _("Hotkey already exists!"), wxOK, this);
			return;
		}
	}
	long keycode = m_hkey->GetHotkey();
	int mods = m_hkey->GetModifier();
	m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).SetHotkey(keycode);
	m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).SetMods(mods);
	m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).SetName(m_hkey->GetHkName());
	m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).SetAction(m_hkeyaction->GetValue());
	m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).SetActive(m_hkeyon->GetValue());
	m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).SetGroup(m_hkcombo->GetValue());
	//BuildHotkeys();
	wxCommandEvent ev;
	OnHkGroupChanged(ev);
	m_hkcombo->SetStringSelection(m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).GetGroup());
	//m_frame->m_actwindow->SetHotkeys(*m_frame->GetHotkeys());
}

void dlg_obj::OnHkSelected( wxListEvent& event )
{
	m_hkindex = event.GetIndex();
	if (m_hkindex!=-1)
	{
		m_hkindex = m_listhkey->GetItemData(m_hkindex);
	}
	if (m_hkindex==-1)
		return;
	else
	{
		m_hkey->SetValue(m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).GetName());
		m_hkey->SetHkName(m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).GetName());
		m_hkey->SetHotkey(m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).GetHotkey());
		m_hkey->SetModifier(m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).GetModifier());
		m_hkeyaction->SetValue(m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).GetAction());
		m_hkcombo->SetStringSelection(m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).GetGroup());
		m_hkeyon->SetValue(m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).IsActive());
		m_hkgroupoff->SetValue(m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).IsActive());
		if (m_hkgroupoff->GetValue())
			m_hkgroupoff->SetLabel(_("Group active"));
		else
			m_hkgroupoff->SetLabel(_("Group off"));
	}
}

void dlg_obj::OnHotkeyDelete(wxCommandEvent& event)
{
hk_it it;
	if (m_hkindex==-1)
		return;
	else
	{
		it = m_frame->m_actwindow->GetHotkeys()->begin()+m_hkindex;
		//for (it=m_frame->GetTrigger()->begin(), i=0;i<index;it++, i++);
		m_frame->m_actwindow->GetHotkeys()->erase(it);
		m_listhkey->DeleteItem(m_hkindex);
		//BuildHotkeys();
		int index=0;
		for (it = m_frame->m_actwindow->GetHotkeys()->begin(); it!= m_frame->m_actwindow->GetHotkeys()->end(); it++)
		{
			it->SetIndex(index++);
		}
		wxCommandEvent ev;
		OnHkGroupChanged(ev);
		//m_frame->m_actwindow->SetHotkeys(*m_frame->GetHotkeys());
	}
}

void dlg_obj::OnHkOn( wxCommandEvent& event)
{
	if (m_hkindex==-1)
		return;
	else
	{
		m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).SetActive(m_hkeyon->GetValue());
	}
	//m_frame->m_actwindow->SetHotkeys(*m_frame->GetHotkeys());

}

void dlg_obj::OnHkGroupDelete(wxCommandEvent& event)
{
s_it it;

	wxString s = m_hkcombo->GetValue();
	if (m_hkindex==-1 && s == wxEmptyString)
		return;
	else
	{
		if (s == wxEmptyString)
			s = m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).GetGroup();
		if (wxMessageBox(_("This will delete all hotkeys in this group!"), _("Continue?"), wxYES_NO, this)==wxYES)
		{
			for (size_t i=0;i<m_frame->m_actwindow->GetHotkeys()->size(); i++)
			{
				if(m_frame->m_actwindow->GetHotkeys()->at(i).GetGroup()==s)
				{
					m_frame->m_actwindow->GetHotkeys()->erase(m_frame->m_actwindow->GetHotkeys()->begin()+i--);
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
		BuildHotkeys();
		}
	}
	//m_frame->m_actwindow->SetHotkeys(*m_frame->GetHotkeys());
}

void dlg_obj::OnHkGroupToggle( wxCommandEvent& event )
{
hk_it iter;
	
	if (m_hkindex==-1)
		return;
	else
	{
		wxString s = m_frame->m_actwindow->GetHotkeys()->at(m_hkindex).GetGroup();
		if (m_hkgroupoff->GetValue())
			m_hkgroupoff->SetLabel(_("Group active"));
		else
			m_hkgroupoff->SetLabel(_("Group off"));
		for (iter = m_frame->m_actwindow->GetHotkeys()->begin(); iter!= m_frame->m_actwindow->GetHotkeys()->end(); iter++)
		{
			if (s == iter->GetGroup())
			{
				iter->SetActive(m_hkgroupoff->GetValue());
				m_hkeyon->SetValue(m_hkgroupoff->GetValue());
			}
		}
	}
}

void dlg_obj::OnHkGroupChanged( wxCommandEvent& event )
{
int index=0;
hk_it iter;

	wxString group = m_hkcombo->GetValue();
	if (group == "all")
	{
		BuildHotkeys();
		return;
	}
	else if (m_hkfilter->GetValue())
	{
		m_listhkey->DeleteAllItems();
		for (iter = m_frame->m_actwindow->GetHotkeys()->begin(); iter!= m_frame->m_actwindow->GetHotkeys()->end(); iter++)
		{
			if (group==iter->GetGroup())
			{
				int idx = m_frame->m_actwindow->GetHkIndexByLabel(iter->GetName());
				long tmp = m_listhkey->InsertItem(index, iter->GetName(),-1);
				m_listhkey->SetItemData(tmp, idx);
				m_listhkey->SetItem(index, 1, iter->GetAction(), -1);
				m_listhkey->SetItem(index++, 2, iter->GetGroup(), -1);
			}
		}
	}
}

void dlg_obj::OnVarSelected( wxListEvent& event )
{
	//int idx = m_frame->GetAliasIndexByLabel(event.GetText());
	m_vindex = event.GetIndex();
	if (m_vindex!=-1)
	{
		m_vindex = m_listvar->GetItemData(m_vindex);
	}
	if (m_vindex==-1)
		return;
	else
	{
		m_defvar->SetValue(m_frame->m_actwindow->GetVars()->at(m_vindex).GetName());
		m_varvalue->SetValue(m_frame->m_actwindow->GetVars()->at(m_vindex).GetValue());
		m_vargroup->SetStringSelection(m_frame->m_actwindow->GetVars()->at(m_vindex).GetGroup());
		m_von->SetValue(m_frame->m_actwindow->GetVars()->at(m_vindex).IsActive());
		m_vgroupoff->SetValue(m_frame->m_actwindow->GetVars()->at(m_vindex).IsActive());
		if (m_vgroupoff->GetValue())
			m_vgroupoff->SetLabel(_("Group active"));
		else
			m_vgroupoff->SetLabel(_("Group off"));
	}
	m_vargroup->SetStringSelection(m_frame->m_actwindow->GetVars()->at(m_vindex).GetGroup());
}

void dlg_obj::OnVarAdd( wxCommandEvent& event )
{
amcVar v;
v_it it;

	wxString s = m_defvar->GetValue();
	for (it=m_frame->m_actwindow->GetVars()->begin();it!=m_frame->m_actwindow->GetVars()->end();it++)
	{
		if(s==*it)
		{
			wxMessageBox(_("Variable already exists!"), _("Variable already exists!"), wxOK, this);
			return;
		}
	}
	v.SetName(s);
	v.SetValue(m_varvalue->GetValue());
	v.SetActive(m_von->GetValue());
	v.SetGroup(m_vargroup->GetValue());
	m_frame->m_actwindow->GetVars()->push_back(v);
	stable_sort(m_frame->m_actwindow->GetVars()->begin(), m_frame->m_actwindow->GetVars()->end(), less<class amcVar>());
	//BuildVars();
	int index=0;
	for (it = m_frame->m_actwindow->GetVars()->begin(); it!= m_frame->m_actwindow->GetVars()->end(); it++)
	{
		it->SetIndex(index++);
	}
	m_vargroup->SetStringSelection(v.GetGroup());
	m_frame->luaBuildvar();
	wxCommandEvent ev;
	OnVGroupChanged(ev);
	//m_frame->m_actwindow->SetVars(*m_frame->GetVars());
}

void dlg_obj::OnVarEdit( wxCommandEvent& event )
{
v_it it;
		
	if (m_vindex==-1)
		return;
	wxString s = m_defvar->GetValue();
	for (it=m_frame->m_actwindow->GetVars()->begin();it!=m_frame->m_actwindow->GetVars()->end();it++)
	{
		if(s==*it && s!=m_frame->m_actwindow->GetVars()->at(m_vindex).GetName())
		{
			wxMessageBox(_("Variable already exists!"), _("Variable already exists!"), wxOK, this);
			return;
		}
	}
	m_frame->m_actwindow->GetVars()->at(m_vindex).SetName(s);
	m_frame->m_actwindow->GetVars()->at(m_vindex).SetValue(m_varvalue->GetValue());
	m_frame->m_actwindow->GetVars()->at(m_vindex).SetActive(m_von->GetValue());
	m_frame->m_actwindow->GetVars()->at(m_vindex).SetGroup(m_vargroup->GetValue());
	m_vargroup->SetStringSelection(m_frame->m_actwindow->GetVars()->at(m_vindex).GetGroup());
	wxCommandEvent ev;
	OnVGroupChanged(ev);
	//m_frame->m_actwindow->SetVars(*m_frame->GetVars());
}

void dlg_obj::OnVarDelete( wxCommandEvent& event )
{
v_it it;

	if (m_vindex==-1)
		return;
	else
	{
		it = m_frame->m_actwindow->GetVars()->begin()+m_vindex;
		
		m_frame->m_actwindow->GetVars()->erase(it);
		
		int index=0;
		for (it = m_frame->m_actwindow->GetVars()->begin(); it!= m_frame->m_actwindow->GetVars()->end(); it++)
		{
			it->SetIndex(index++);
		}
		wxCommandEvent ev;
		OnVGroupChanged(ev);
		//m_frame->m_actwindow->SetVars(*m_frame->GetVars());
	}
}

void dlg_obj::OnVarOn( wxCommandEvent& event )
{
	if (m_vindex==-1)
		return;
	else
	{
		m_frame->m_actwindow->GetVars()->at(m_vindex).SetActive(m_von->GetValue());
		//m_frame->m_actwindow->SetVars(*m_frame->GetVars());
	}
}

void dlg_obj::OnVGroupDelete( wxCommandEvent& event)
{
s_it it;

	wxString s = m_vargroup->GetValue();
	if (m_vindex==-1 && s == wxEmptyString)
		return;
	else
	{
		if (s == wxEmptyString)
			s = m_frame->m_actwindow->GetVars()->at(m_vindex).GetGroup();
		if (wxMessageBox(_("This will delete all variables in this group!"), _("Continue?"), wxYES_NO, this)==wxYES)
		{
			for (size_t i=0;i<m_frame->m_actwindow->GetVars()->size(); i++)
			{
				if(m_frame->m_actwindow->GetVars()->at(i).GetGroup()==s)
				{
					m_frame->m_actwindow->GetVars()->erase(m_frame->m_actwindow->GetVars()->begin()+i--);
				}
			}
			for (it = amcVar::GetVarGroups()->begin(); it!=amcVar::GetVarGroups()->end(); it++)
			{
				if (*it == s)
				{
					amcVar::GetVarGroups()->erase(it);
					break;
				}
			}
		BuildVars();
		}
	}
	//m_frame->m_actwindow->SetVars(*m_frame->GetVars());
}

void dlg_obj::OnVGroupOff( wxCommandEvent& event )
{
v_it iter;
	
	if (m_vindex==-1)
		return;
	else
	{
		wxString s = m_frame->m_actwindow->GetVars()->at(m_vindex).GetGroup();
		if (m_vgroupoff->GetValue())
			m_vgroupoff->SetLabel(_("Group active"));
		else
			m_vgroupoff->SetLabel(_("Group off"));
		for (iter = m_frame->m_actwindow->GetVars()->begin(); iter!= m_frame->m_actwindow->GetVars()->end(); iter++)
		{
			if (s == iter->GetGroup())
			{
				iter->SetActive(m_vgroupoff->GetValue());
				m_von->SetValue(m_vgroupoff->GetValue());
			}
		}
	}
}

void dlg_obj::OnVGroupChanged( wxCommandEvent& event )
{
int index=0;
v_it iter;

	wxString group = m_vargroup->GetValue();
	if (group == "all")
	{
		BuildVars();
		return;
	}
	else if (m_vfilter->GetValue())
	{
		m_listvar->DeleteAllItems();
		for (iter = m_frame->m_actwindow->GetVars()->begin(); iter!= m_frame->m_actwindow->GetVars()->end(); iter++)
		{
			if (group==iter->GetGroup())
			{
				long tmp = m_listvar->InsertItem(index, iter->GetName(),-1);
				m_listvar->SetItemData(tmp, m_frame->m_actwindow->GetVarIndexByLabel(iter->GetName()));
				m_listvar->SetItem(index, 1, iter->GetValue(), -1);
				m_listvar->SetItem(index++, 2, iter->GetGroup(), -1);
			}
		}
	}
}

void dlg_obj::OnListSelected( wxListEvent& event )
{
	//int idx = m_frame->GetAliasIndexByLabel(event.GetText());
	m_lindex = event.GetIndex();
	if (m_lindex!=-1)
	{
		m_lindex = m_listlist->GetItemData(m_lindex);
	}
	if (m_lindex==-1)
		return;
	else
	{
		m_deflist->SetValue(m_frame->m_actwindow->GetLists()->at(m_lindex).GetName());
		//m_varvalue->SetValue(m_frame->GetVars()->at(m_vindex).GetValue());
		int i;
		m_items->Clear();
		for (i=0; i<m_frame->m_actwindow->GetLists()->at(m_lindex).GetSize();i++)
			m_items->Append(m_frame->m_actwindow->GetLists()->at(m_lindex).GetItem(i));
		m_ligroup->SetStringSelection(m_frame->m_actwindow->GetLists()->at(m_lindex).GetGroup());
		m_lion->SetValue(m_frame->m_actwindow->GetLists()->at(m_lindex).IsActive());
		m_ligroupoff->SetValue(m_frame->m_actwindow->GetLists()->at(m_lindex).IsActive());
		if (m_ligroupoff->GetValue())
			m_ligroupoff->SetLabel(_("Group active"));
		else
			m_ligroupoff->SetLabel(_("Group off"));
	}
	m_ligroup->SetStringSelection(m_frame->m_actwindow->GetLists()->at(m_lindex).GetGroup());
}

void dlg_obj::OnListAdd( wxCommandEvent& event )
{
amcList l;
li_it it;

	wxString s = m_deflist->GetValue();
	for (it=m_frame->m_actwindow->GetLists()->begin();it!=m_frame->m_actwindow->GetLists()->end();it++)
	{
		if(s==*it)
		{
			wxMessageBox(_("List already exists!"), _("List already exists!"), wxOK, this);
			return;
		}
	}
	l.SetName(s);
	l.SetActive(m_lion->GetValue());
	l.SetGroup(m_ligroup->GetValue());
	m_frame->m_actwindow->GetLists()->push_back(l);
	stable_sort(m_frame->m_actwindow->GetLists()->begin(), m_frame->m_actwindow->GetLists()->end(), less<class amcList>());
	//BuildLists();
	int index=0;
	for (it = m_frame->m_actwindow->GetLists()->begin(); it!= m_frame->m_actwindow->GetLists()->end(); it++)
	{
		it->SetIndex(index++);
	}
	m_ligroup->SetStringSelection(l.GetGroup());
	wxCommandEvent ev;
	OnLGroupChanged(ev);
	it = find(m_frame->m_actwindow->GetLists()->begin(), m_frame->m_actwindow->GetLists()->end(), l.GetName());
	m_listlist->SetItemState(it->GetIndex(), wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	//m_frame->m_actwindow->SetLists(*m_frame->GetLists());
}

void dlg_obj::OnListEdit(wxCommandEvent &event)
{
li_it it;
		
	if (m_lindex==-1)
		return;
	wxString s = m_deflist->GetValue();
	for (it=m_frame->m_actwindow->GetLists()->begin();it!=m_frame->m_actwindow->GetLists()->end();it++)
	{
		if(s==*it && s!=m_frame->m_actwindow->GetLists()->at(m_lindex).GetName())
		{
			wxMessageBox(_("List already exists!"), _("List already exists!"), wxOK, this);
			return;
		}
	}
	m_frame->m_actwindow->GetLists()->at(m_lindex).SetName(s);
	
	m_frame->m_actwindow->GetLists()->at(m_lindex).SetActive(m_lion->GetValue());
	m_frame->m_actwindow->GetLists()->at(m_lindex).SetGroup(m_ligroup->GetValue());
	//BuildLists();
	m_ligroup->SetStringSelection(m_frame->m_actwindow->GetLists()->at(m_lindex).GetGroup());
	wxCommandEvent ev;
	OnLGroupChanged(ev);
	//m_frame->m_actwindow->SetLists(*m_frame->GetLists());
}

void dlg_obj::OnListDelete(wxCommandEvent& event)
{
li_it it;

	if (m_lindex==-1)
		return;
	else
	{
		it = m_frame->m_actwindow->GetLists()->begin()+m_lindex;
		//for (it=m_frame->GetTrigger()->begin(), i=0;i<index;it++, i++);
		m_frame->m_actwindow->GetLists()->erase(it);
		
		int index=0;
		for (it = m_frame->m_actwindow->GetLists()->begin(); it!= m_frame->m_actwindow->GetLists()->end(); it++)
		{
			it->SetIndex(index++);
		}
		wxCommandEvent ev;
		OnLGroupChanged(ev);
		//m_frame->m_actwindow->SetLists(*m_frame->GetLists());
	}
}

void dlg_obj::OnAddItem(wxCommandEvent& event)
{
	if (m_lindex==-1)
		return;
	m_frame->m_actwindow->GetLists()->at(m_lindex).AddItem(m_items->GetValue());
	m_items->Append(m_items->GetValue());
	BuildLists();
	m_ligroup->SetStringSelection(m_frame->m_actwindow->GetLists()->at(m_lindex).GetGroup());
	//m_frame->m_actwindow->SetLists(*m_frame->GetLists());
}

void dlg_obj::OnListOn(wxCommandEvent& event)
{
	if (m_lindex==-1)
		return;
	else
	{
		m_frame->m_actwindow->GetLists()->at(m_lindex).SetActive(m_lion->GetValue());
		//m_frame->m_actwindow->SetLists(*m_frame->GetLists());
	}
}

void dlg_obj::OnListGroupOff( wxCommandEvent& event )
{
li_it iter;
	
	if (m_lindex==-1)
		return;
	else
	{
		wxString s = m_frame->m_actwindow->GetLists()->at(m_lindex).GetGroup();
		if (m_ligroupoff->GetValue())
			m_ligroupoff->SetLabel(_("Group active"));
		else
			m_ligroupoff->SetLabel(_("Group off"));
		for (iter = m_frame->m_actwindow->GetLists()->begin(); iter!= m_frame->m_actwindow->GetLists()->end(); iter++)
		{
			if (s == iter->GetGroup())
			{
				iter->SetActive(m_ligroupoff->GetValue());
				m_lion->SetValue(m_ligroupoff->GetValue());
			}
		}
	}
}

void dlg_obj::OnDeleteListGroup( wxCommandEvent& event )
{
s_it it;

	wxString s = m_ligroup->GetValue();
	if (m_lindex==-1 && s == wxEmptyString)
		return;
	else
	{
		if (s == wxEmptyString)
			s = m_frame->m_actwindow->GetLists()->at(m_lindex).GetGroup();
		if (wxMessageBox(_("This will delete all lists in this group!"), _("Continue?"), wxYES_NO, this)==wxYES)
		{
			for (size_t i=0;i<m_frame->m_actwindow->GetLists()->size(); i++)
			{
				if(m_frame->m_actwindow->GetLists()->at(i).GetGroup()==s)
				{
					m_frame->m_actwindow->GetLists()->erase(m_frame->m_actwindow->GetLists()->begin()+i--);
				}
			}
			for (it = amcList::GetListGroups()->begin(); it!=amcList::GetListGroups()->end(); it++)
			{
				if (*it == s)
				{
					amcList::GetListGroups()->erase(it);
					break;
				}
			}
		BuildLists();
		}
	}
	//m_frame->m_actwindow->SetLists(*m_frame->GetLists());
}

void dlg_obj::OnLGroupChanged( wxCommandEvent& event )
{
int index=0;
li_it iter;

	wxString group = m_ligroup->GetValue();
	if (group == "all")
	{
		BuildLists();
		return;
	}
	else if (m_lifilter->GetValue())
	{
		m_listlist->DeleteAllItems();
		for (iter = m_frame->m_actwindow->GetLists()->begin(); iter!= m_frame->m_actwindow->GetLists()->end(); iter++)
		{
			if (group==iter->GetGroup())
			{
				long tmp = m_listlist->InsertItem(index, iter->GetName(),-1);
				m_listlist->SetItemData(tmp, m_frame->m_actwindow->GetListIndexByLabel(iter->GetName()));
				m_listlist->SetItem(index, 1, iter->GetValue(), -1);
				m_listlist->SetItem(index++, 2, iter->GetGroup(), -1);
			}
		}
	}
}

void dlg_obj::OnTimerSelected( wxListEvent& event )
{
	//int idx = m_frame->GetAliasIndexByLabel(event.GetText());
	m_tindex = event.GetIndex();
	if (m_tindex!=-1)
	{
		m_tindex = m_timerlist->GetItemData(m_tindex);
	}
	if (m_tindex==-1)
		return;
	else
	{
		m_deftimer->SetValue(m_frame->m_actwindow->GetTimers()->at(m_tindex).GetName());
		m_timeraction->SetValue(m_frame->m_actwindow->GetTimers()->at(m_tindex).GetAction());
		m_tigroup->SetStringSelection(m_frame->m_actwindow->GetTimers()->at(m_tindex).GetGroup());
		m_ton->SetValue(m_frame->m_actwindow->GetTimers()->at(m_tindex).IsActive());
		m_rep->SetValue(m_frame->m_actwindow->GetTimers()->at(m_tindex).GetRepeat());
		wxString s;
		s<<m_frame->m_actwindow->GetTimers()->at(m_tindex).GetFInterval();
		m_intervall->SetValue(s);
		m_tigroupoff->SetValue(m_frame->m_actwindow->GetTimers()->at(m_tindex).IsActive());
		if (m_tigroupoff->GetValue())
			m_tigroupoff->SetLabel(_("Group active"));
		else
			m_tigroupoff->SetLabel(_("Group off"));
	}
	m_tigroup->SetStringSelection(m_frame->m_actwindow->GetTimers()->at(m_tindex).GetGroup());
}

void dlg_obj::OnTimerAdd(wxCommandEvent& event)
{
amcTimer t;
t_it it;

	wxString s = m_deftimer->GetValue();
	for (it=m_frame->m_actwindow->GetTimers()->begin();it!=m_frame->m_actwindow->GetTimers()->end();it++)
	{
		if(s==*it)
		{
			wxMessageBox(_("Timer already exists!"), _("Timer already exists!"), wxOK, this);
			return;
		}
	}
	t.SetName(s);
	t.SetAction(m_timeraction->GetValue());
	t.SetActive(m_ton->GetValue());
	t.SetGroup(m_tigroup->GetValue());
	double f;
	m_intervall->GetValue().ToDouble(&f);
	t.SetInterval((float)f);
	t.SetRepeat(m_rep->GetValue());
	t.SetCurrepeat(m_rep->GetValue());
	m_frame->m_actwindow->GetTimers()->push_back(t);
	stable_sort(m_frame->m_actwindow->GetTimers()->begin(), m_frame->m_actwindow->GetTimers()->end(), less<class amcTimer>());
	//BuildTimers();
	int index=0;
	for (it = m_frame->m_actwindow->GetTimers()->begin(); it!= m_frame->m_actwindow->GetTimers()->end(); it++)
	{
		it->SetIdx(index++);
	}
	m_tigroup->SetStringSelection(t.GetGroup());
	wxCommandEvent ev;
	OnTGroupChanged(ev);
	//m_frame->m_actwindow->SetTimers(*m_frame->GetTimers());
}

void dlg_obj::OnTimerDelete( wxCommandEvent& event )
{
t_it it;

	if (m_tindex==-1)
		return;
	else
	{
		it = m_frame->m_actwindow->GetTimers()->begin()+m_tindex;
		//for (it=m_frame->GetTrigger()->begin(), i=0;i<index;it++, i++);
		m_frame->m_actwindow->GetTimers()->erase(it);
		//m_listalias->DeleteItem(event.GetIndex());
		//BuildTimers();
		int index=0;
		for (it = m_frame->m_actwindow->GetTimers()->begin(); it!= m_frame->m_actwindow->GetTimers()->end(); it++)
		{
			it->SetIdx(index++);
		}
		wxCommandEvent ev;
		OnTGroupChanged(ev);
		//m_frame->m_actwindow->SetTimers(*m_frame->GetTimers());
	}
}

void dlg_obj::OnTimerEdit(wxCommandEvent &event)
{
t_it it;
		
	if (m_tindex==-1)
		return;
	wxString s = m_deftimer->GetValue();
	for (it=m_frame->m_actwindow->GetTimers()->begin();it!=m_frame->m_actwindow->GetTimers()->end();it++)
	{
		if(s==*it && s!=m_frame->m_actwindow->GetTimers()->at(m_tindex).GetName())
		{
			wxMessageBox(_("Timer already exists!"), _("Timer already exists!"), wxOK, this);
			return;
		}
	}
	m_frame->m_actwindow->GetTimers()->at(m_tindex).SetName(s);
	m_frame->m_actwindow->GetTimers()->at(m_tindex).SetAction(m_timeraction->GetValue());
	double f;
	m_intervall->GetValue().ToDouble(&f);
	m_frame->m_actwindow->GetTimers()->at(m_tindex).SetInterval((float)f);
	m_frame->m_actwindow->GetTimers()->at(m_tindex).SetRepeat(m_rep->GetValue());
	m_frame->m_actwindow->GetTimers()->at(m_tindex).SetCurrepeat(m_rep->GetValue());
	m_frame->m_actwindow->GetTimers()->at(m_tindex).SetActive(m_ton->GetValue());
	m_frame->m_actwindow->GetTimers()->at(m_tindex).SetGroup(m_tigroup->GetValue());
	//BuildTimers();
	m_tigroup->SetStringSelection(m_frame->m_actwindow->GetTimers()->at(m_tindex).GetGroup());
	wxCommandEvent ev;
	OnTGroupChanged(ev);
	//m_frame->m_actwindow->SetTimers(*m_frame->GetTimers());
}

void dlg_obj::OnTimerStart(wxCommandEvent& event)
{
	if (m_tindex==-1)
		return;
	m_frame->m_actwindow->GetTimers()->at(m_tindex).SetActive(true);
	m_frame->m_actwindow->GetTimers()->at(m_tindex).Run();
}

void dlg_obj::OnTimerOn( wxCommandEvent& event )
{
	if (m_tindex==-1)
		return;
	else
	{
		m_frame->m_actwindow->GetTimers()->at(m_tindex).SetActive(m_ton->GetValue());
		//m_frame->m_actwindow->SetTimers(*m_frame->GetTimers());
	}
}

void dlg_obj::OnTimerGroupOff(wxCommandEvent &event)
{
t_it iter;
	
	if (m_tindex==-1)
		return;
	else
	{
		wxString s = m_frame->m_actwindow->GetTimers()->at(m_tindex).GetGroup();
		if (m_tigroupoff->GetValue())
			m_tigroupoff->SetLabel(_("Group active"));
		else
			m_tigroupoff->SetLabel(_("Group off"));
		for (iter = m_frame->m_actwindow->GetTimers()->begin(); iter!= m_frame->m_actwindow->GetTimers()->end(); iter++)
		{
			if (s == iter->GetGroup())
			{
				iter->SetActive(m_tigroupoff->GetValue());
				m_ton->SetValue(m_tigroupoff->GetValue());
			}
		}
	}
}

void dlg_obj::OnDeleteTimerGroup(wxCommandEvent& event)
{
s_it it;

	wxString s = m_tigroup->GetValue();
	if (m_tindex==-1 && s == wxEmptyString)
		return;
	else
	{
		if (s == wxEmptyString)
			s = m_frame->m_actwindow->GetTimers()->at(m_tindex).GetGroup();
		if (wxMessageBox(_("This will delete all timers in this group!"), _("Continue?"), wxYES_NO, this)==wxYES)
		{
			for (size_t i=0;i<m_frame->m_actwindow->GetTimers()->size(); i++)
			{
				if(m_frame->m_actwindow->GetTimers()->at(i).GetGroup()==s)
				{
					m_frame->m_actwindow->GetTimers()->erase(m_frame->m_actwindow->GetTimers()->begin()+i--);
				}
			}
			for (it = amcTimer::GetTimerGroups()->begin(); it!=amcTimer::GetTimerGroups()->end(); it++)
			{
				if (*it == s)
				{
					amcTimer::GetTimerGroups()->erase(it);
					break;
				}
			}
		BuildTimers();
		}
	}
	//m_frame->m_actwindow->SetTimers(*m_frame->GetTimers());
}

void dlg_obj::OnTGroupChanged( wxCommandEvent& event )
{
int index=0;
t_it iter;

	wxString group = m_tigroup->GetValue();
	if (group == "all")
	{
		BuildTimers();
		return;
	}
	else if (m_tifilter->GetValue())
	{
		m_timerlist->DeleteAllItems();
		for (iter = m_frame->m_actwindow->GetTimers()->begin(); iter!= m_frame->m_actwindow->GetTimers()->end(); iter++)
		{
			if (group==iter->GetGroup())
			{
				long tmp = m_timerlist->InsertItem(index, iter->GetName(),-1);
				m_timerlist->SetItemData(tmp, m_frame->m_actwindow->GetTimerIndexByLabel(iter->GetName()));
				m_timerlist->SetItem(index, 1, iter->GetAction(), -1);
				m_timerlist->SetItem(index++, 2, iter->GetGroup(), -1);
			}
		}
	}
}

void dlg_obj::OnRegExpTest(wxCommandEvent &event)
{
	dialog_regexp * regexp = new dialog_regexp(this);
	regexp->GetPattern()->SetValue(m_pattern->GetValue());
	if (regexp->ShowModal()==wxID_OK)
		{
			
		}
		regexp->Destroy();
	
}

void dlg_obj::OnGaugeTreeSelChanged( wxTreeEvent& event )
{
	class GaugeWindow *gw = NULL;
	wxTreeItemId id = event.GetItem();
	if (m_gaugew->ItemHasChildren(id))
		return;
	wxTreeItemId parent = m_gaugew->GetItemParent(id);
	if (parent)
	{	
		wxString win = m_gaugew->GetItemText(parent);
		gw = (GaugeWindow*)GaugeWindow::FindWindowByName(win);
		if (!gw)
			return;
	}
	if (!gw)
		return;
	int index = gw->GetGaugeIndexByName(m_gaugew->GetItemText(id));
	if (index==-1)
		return;
	else
	{
		m_gaugelabel->SetValue(m_gaugew->GetItemText(id));
		m_var1->SetStringSelection(gw->GetGauges()->at(index).GetVar1());
		m_var2->SetStringSelection(gw->GetGauges()->at(index).GetVar2());
		m_fore->SetColour(gw->GetGauges()->at(index).GetFCol());
		m_back->SetColour(gw->GetGauges()->at(index).GetBCol());
		m_alarm->SetColour(gw->GetGauges()->at(index).GetAlarm());
		int x = gw->GetGauges()->at(index).GetAlarmPerc();
		m_alarmslider->SetValue(x);
		m_gaugetextcol->SetColour(gw->GetGauges()->at(index).GetTextCol());
		if (gw->GetGauges()->at(index).GetVertical())
			m_gaugedir->SetSelection(0);
		else
			m_gaugedir->SetSelection(1);
		m_drawstyle->Select(gw->GetGauges()->at(index).GetStyle());
		m_textpos->Select(gw->GetGauges()->at(index).GetTextPos());
		m_posx->SetValue(gw->GetGauges()->at(index).GetX());
		m_posy->SetValue(gw->GetGauges()->at(index).GetY());
		m_width->SetValue(gw->GetGauges()->at(index).GetCx());
		m_height->SetValue(gw->GetGauges()->at(index).GetCy());
		m_showvalue->SetValue(gw->GetGauges()->at(index).ShowValue());
	}
}

void dlg_obj::OnAddGauge(wxCommandEvent &event)
{
amcGauge g;
int i;

	g.SetLabel(m_gaugelabel->GetValue());
	g.SetWindow(m_parentw->GetValue());
	g.SetVar1(m_var1->GetStringSelection());
	g.SetVar2(m_var2->GetStringSelection());
	g.SetVarIndices();
	g.SetFCol(m_fore->GetColour());
	g.SetBCol(m_back->GetColour());
	g.SetAlarmCol(m_alarm->GetColour());
	g.SetTextCol(m_gaugetextcol->GetColour());
	g.SetX(m_posx->GetValue());
	g.SetY(m_posy->GetValue());
	g.SetCx(m_width->GetValue());
	g.SetCy(m_height->GetValue());
	g.SetShowValue(m_showvalue->GetValue());
	int x = m_alarmslider->GetValue();
	g.SetAlarmPerc(x);
	i=m_gaugedir->GetSelection();
	if (!i)
		g.SetVertical(true);
	else g.SetVertical(false);
	class MudMainFrame *f = wxGetApp().GetFrame();
	if (!f->m_actwindow->GetGaugePanes()->empty())
	{
		for (i=0;i<(int)f->m_actwindow->GetGaugePanes()->size();i++)
		{
			if (m_parentw->GetValue()==f->m_actwindow->GetGaugePanes()->at(i))
				break;
		}
	}
	g.Register();
	f->m_actwindow->GetGauges()->at(i).push_back(g.GetName());
	BuildGaugeTree();
	//m_frame->m_actwindow->SetGauges(*m_frame->GetGauges());
}

void dlg_obj::OnDelGauge(wxCommandEvent &event)
{
g_it it;
class GaugeWindow *gw;
	
	wxTreeItemId id = m_gaugew->GetSelection();
	if (m_gaugew->ItemHasChildren(id))
		return;
	wxTreeItemId parent = m_gaugew->GetItemParent(id);
	if (parent)
	{	
		wxString win = m_gaugew->GetItemText(parent);
		gw = (GaugeWindow*)GaugeWindow::FindWindowByName(win);
		if (!gw)
			return;
	}
	int index = gw->GetGaugeIndexByName(m_gaugew->GetItemText(id));
	if (index==-1)
		return;
	else
	{
		it = gw->GetGauges()->begin()+index;
		gw->GetGauges()->erase(it);
		BuildGaugeTree();
		gw->Refresh();
	}
	//m_frame->m_actwindow->SetTimers(*m_frame->GetTimers());
}

void dlg_obj::OnEditGauge(wxCommandEvent &event)
{
g_it it;
class GaugeWindow *gw;
	
	wxTreeItemId id = m_gaugew->GetSelection();
	if (m_gaugew->ItemHasChildren(id))
		return;
	wxTreeItemId parent = m_gaugew->GetItemParent(id);
	if (parent)
	{	
		wxString win = m_gaugew->GetItemText(parent);
		gw = (GaugeWindow*)GaugeWindow::FindWindowByName(win);
		if (!gw)
			return;
	}
	int index = gw->GetGaugeIndexByName(m_gaugew->GetItemText(id));
	if (index==-1)
		return;
	else
	{
		gw->GetGauges()->at(index).SetLabel(m_gaugelabel->GetValue());
		m_gaugew->SetItemText(id, m_gaugelabel->GetValue());
		gw->GetGauges()->at(index).SetVar1(m_var1->GetStringSelection());
		gw->GetGauges()->at(index).SetVar2(m_var2->GetStringSelection());
		gw->GetGauges()->at(index).SetVarIndices();
		gw->GetGauges()->at(index).SetFCol(m_fore->GetColour());
		gw->GetGauges()->at(index).SetBCol(m_back->GetColour());
		gw->GetGauges()->at(index).SetAlarmCol(m_alarm->GetColour());
		gw->GetGauges()->at(index).SetTextCol(m_gaugetextcol->GetColour());
		gw->GetGauges()->at(index).SetX(m_posx->GetValue());
		gw->GetGauges()->at(index).SetY(m_posy->GetValue());
		gw->GetGauges()->at(index).SetCx(m_width->GetValue());
		gw->GetGauges()->at(index).SetCy(m_height->GetValue());
		gw->GetGauges()->at(index).SetShowValue(m_showvalue->GetValue());
		gw->GetGauges()->at(index).SetTextCol(m_gaugetextcol->GetColour());
		int x = m_alarmslider->GetValue();
		gw->GetGauges()->at(index).SetAlarmPerc(x);
		int i = m_gaugedir->GetSelection();
		if (!i)
			gw->GetGauges()->at(index).SetVertical(true);
		else gw->GetGauges()->at(index).SetVertical(false);
		gw->GetGauges()->at(index).SetStyle(m_drawstyle->GetSelection());
		gw->GetGauges()->at(index).SetTextPos(m_textpos->GetSelection());
		//BuildGaugeTree();
		gw->Refresh();
		m_gaugew->SetFocus();
		m_gaugew->SelectItem(id);
	}
	//m_frame->m_actwindow->SetTimers(*m_frame->GetTimers());
}

void dlg_obj::OnButtonSelChanged( wxTreeEvent& event )
{
	int index;
	wxTreeItemId id = event.GetItem();
	if (m_treeCtrl3->ItemHasChildren(id))
		return;
	index = m_frame->m_actwindow->GetButtonIndexByLabel(m_treeCtrl3->GetItemText(id));
	if (index==-1)
		return;
	m_butlabel->SetValue(m_frame->m_actwindow->GetButtons()->at(index).GetText());
	m_butcommand->SetValue(m_frame->m_actwindow->GetButtons()->at(index).GetAction());
	m_bmfilepicker->SetInitialDirectory(m_frame->GetGlobalOptions()->GetImagesDir());
	m_bmfilepicker->SetPath(m_frame->m_actwindow->GetButtons()->at(index).GetBitmap());
	int found = m_parenttool->FindString(m_frame->m_actwindow->GetButtons()->at(index).GetTbName());
	if (found==wxNOT_FOUND)
	{
		m_parenttool->AppendString(m_frame->m_actwindow->GetButtons()->at(index).GetTbName());
		m_parenttool->SetStringSelection(m_frame->m_actwindow->GetButtons()->at(index).GetTbName());
	}
	else
		m_parenttool->SetStringSelection(m_frame->m_actwindow->GetButtons()->at(index).GetTbName());
}

void dlg_obj::OnButtonAdd(wxCommandEvent &event)
{
amcButton b;
b_it it;
wxAuiToolBar *tb;

	wxString s = m_butlabel->GetValue();
	for (it=m_frame->m_actwindow->GetButtons()->begin();it!=m_frame->m_actwindow->GetButtons()->end();it++)
	{
		if(s==it->GetName())
		{
			wxMessageBox(_("Button already exists!"), _("Button already exists!"), wxOK, this);
			return;
		}
	}
	if (s=="separator")
	{
		tb = (wxAuiToolBar*)MudMainFrame::FindWindowByName(m_parenttool->GetValue(), m_frame);
		if (tb)
		{
			tb->AddSeparator();
			b.SetAsSeparator(tb);
			b.SetTbName(m_parenttool->GetValue());
			m_frame->m_actwindow->GetButtons()->push_back(b);
			BuildButtons();
			tb->Realize();
			return;
		}
		else return;
	}
	b.SetName(s);
	b.SetText(s);
	b.SetAction(m_butcommand->GetValue());
	b.SetActive(true);
	b.SetId(ID_USERBUTTON+m_frame->m_actwindow->GetButtons()->size()+1);
	s = m_parenttool->GetValue();
	if (s==wxEmptyString)
		return;
	tb = (wxAuiToolBar*)MudMainFrame::FindWindowByName(s, m_frame);
	if (!tb)
	{
		tb = new wxAuiToolBar(m_frame, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_TEXT | wxAUI_TB_GRIPPER);
		tb->SetName(s);
		tb->SetToolTextOrientation(wxAUI_TBTOOL_TEXT_RIGHT);
		m_frame->m_mgr.AddPane(tb, wxAuiPaneInfo().Name(s).Caption(s).ToolbarPane().CaptionVisible(false).Floatable(true).BestSize(600, 24).LeftDockable(true).Dockable(true).Dock().Top());
		m_frame->m_mgr.Update();
		//m_frame->m_mgr.GetPane(tb).Show();
		
	}
	b.SetTbName(s);
	b.SetParent(tb);
	b.SetBitmap(m_bmfilepicker->GetPath());
	//tb->AddTool(b.GetId(), b.GetName(), script_xpm);
	wxBitmap bt;
	wxSetWorkingDirectory(m_frame->GetGlobalOptions()->GetImagesDir());
	bt.LoadFile(b.GetBitmap(), wxBITMAP_TYPE_XPM);
	tb->AddTool(b.GetId(), b.GetName(), bt);
	tb->SetToolTextOrientation(wxAUI_TBTOOL_TEXT_RIGHT);
	m_frame->m_actwindow->GetButtons()->push_back(b);
	//stable_sort(m_frame->GetVars()->begin(), m_frame->GetVars()->end(), less<class amcVar>());
	BuildButtons();
	tb->Realize();
	m_frame->m_mgr.Update();
	//m_frame->m_actwindow->SetButtons(*m_frame->GetButtons());
}

void dlg_obj::OnButtonDelete(wxCommandEvent& event)
{
b_it it;
	wxTreeItemId id = m_treeCtrl3->GetSelection();
	if (!id.IsOk())
		return;
	int index = m_frame->m_actwindow->GetButtonIndexByLabel(m_treeCtrl3->GetItemText(id));
	if (index==-1)
		return;
	else
	{
		it = m_frame->m_actwindow->GetButtons()->begin()+index;
		wxAuiToolBar* tb = (wxAuiToolBar*)it->GetParent();
		tb->DeleteTool(it->GetId());
		m_frame->m_actwindow->GetButtons()->erase(it);
		m_treeCtrl3->Delete(id);
		//stable_sort(m_frame->GetTrigger()->begin(), m_frame->GetTrigger()->end(), greater<class Trigger>());
		BuildButtons();
		tb->Realize();
		m_frame->m_mgr.Update();
	}
	//m_frame->m_actwindow->SetTimers(*m_frame->GetTimers());
}

void dlg_obj::OnButtonEdit(wxCommandEvent& event)
{
b_it it;

	wxTreeItemId id = m_treeCtrl3->GetSelection();
	if (!id.IsOk())
		return;
	int index = m_frame->m_actwindow->GetButtonIndexByLabel(m_treeCtrl3->GetItemText(id));
	if (index==-1)
		return;
	else
	{
		wxString s = m_butlabel->GetValue();
		for (it=m_frame->m_actwindow->GetButtons()->begin();it!=m_frame->m_actwindow->GetButtons()->end();it++)
		{
			if(s==*it && s!=m_frame->m_actwindow->GetButtons()->at(index).GetName())
			{
				wxMessageBox(_("Button labels need to be unique!"), _("Label already exists!"), wxOK, this);
				return;
			}
		}
		m_frame->m_actwindow->GetButtons()->at(index).SetName(s);
		m_treeCtrl3->SetItemText(id, s);
		m_frame->m_actwindow->GetButtons()->at(index).SetText(s);
		m_frame->m_actwindow->GetButtons()->at(index).SetAction(m_butcommand->GetValue());
		m_frame->m_actwindow->GetButtons()->at(index).SetTbName(m_parenttool->GetValue());
		m_frame->m_actwindow->GetButtons()->at(index).SetBitmap(m_bmfilepicker->GetPath());
		//BuildButtons();
		wxAuiToolBar* tb = (wxAuiToolBar*)m_frame->m_actwindow->GetButtons()->at(index).GetParent();
		tb->SetToolLabel(m_frame->m_actwindow->GetButtons()->at(index).GetId(), s);
		wxBitmap bt;
		wxSetWorkingDirectory(m_frame->GetGlobalOptions()->GetImagesDir());
		wxString f = m_bmfilepicker->GetPath();
		if (f.EndsWith("xpm"))
			bt.LoadFile(f, wxBITMAP_TYPE_XPM);
		else if (f.EndsWith("bmp"))
			bt.LoadFile(f, wxBITMAP_TYPE_BMP);
		else
			bt.LoadFile(f, wxBITMAP_TYPE_ANY);
		tb->SetToolBitmap(m_frame->m_actwindow->GetButtons()->at(index).GetId(), bt);
		tb->Realize();
		//m_frame->m_mgr.Update();
		m_treeCtrl3->SetFocus();
		m_treeCtrl3->SelectItem(id);
	}
	//m_frame->m_actwindow->SetTimers(*m_frame->GetTimers());
}

void dlg_obj::SetData(wxString s)
{
	m_page=0;
	//m_notebook->ChangeSelection(m_page);
	m_notebook->SetSelection(m_page);
	m_data = true;
	m_s = s;
	//(*m_pattern)<<s;
}
