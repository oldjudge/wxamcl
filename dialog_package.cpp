#include "main.h"
#include "dialog_package.h"

pkg_dlg::pkg_dlg( wxWindow* parent )
:
dlg_pkg( parent )
{
	
	m_frame = (MudMainFrame*)parent;
	wxCommandEvent ev;// = event;
	ev.SetEventObject(m_choice);
	ev.SetInt(0);
	ev.SetEventType(wxEVT_COMMAND_CHOICE_SELECTED);
	wxPostEvent(m_choice, ev);
	m_pkgfile->SetPath(m_frame->GetGlobalOptions()->GetPackageDir());
	
}

void pkg_dlg::OnCheckAll(wxCommandEvent& event)
{
	
	//wxSetWorkingDirectory(m_frame->GetGlobalOptions()->GetPackageDir());
	if (m_checkall->IsChecked())
	{
		for (wxUint16 i=0;i<m_items->GetCount();i++)
		{
			m_items->Check(i);
			wxCommandEvent ev;// = event;
			ev.SetEventObject(m_items);
			ev.SetInt(i);
			ev.SetString(m_items->GetString(i));
			ev.SetEventType(wxEVT_COMMAND_CHECKLISTBOX_TOGGLED);
			wxPostEvent(m_items, ev);
		}
	}
	else
	{
		for (wxUint16 i=0;i<m_items->GetCount();i++)
		{
			m_items->Check(i, false);
			//m_items->Check(i);
			wxCommandEvent ev;// = event;
			ev.SetEventObject(m_items);
			ev.SetInt(i);
			ev.SetString(m_items->GetString(i));
			ev.SetEventType(wxEVT_COMMAND_CHECKLISTBOX_TOGGLED);
			wxPostEvent(m_items, ev);
		}
	}
}

void pkg_dlg::OnChoice( wxCommandEvent& event )
{
al_it it;
v_it vit;
tr_it tit;
hk_it hk;
t_it tiit;
li_it lit;
b_it bit;
g_it git;
s_it gp, sit;
	
	int sel = m_choice->GetSelection();
	//wxSetWorkingDirectory(m_frame->GetGlobalOptions()->GetPackageDir());
	m_items->Clear();
	switch (sel)
	{
	case 0://all
	
	case 1://action
		for (tit=m_frame->GetTrigger()->begin();tit!=m_frame->GetTrigger()->end();tit++)
		{
			m_items->AppendString(tit->GetLabel());
		}
		for (sit=m_trigger.begin();sit!=m_trigger.end();sit++)
		{
			m_items->Check(m_items->FindString(*sit));
		}
		m_groups->Clear();
		m_groups->Append(_("All"));
		for (sit = Trigger::GetTriggerClasses()->begin(); sit != Trigger::GetTriggerClasses()->end(); sit++)
			m_groups->Append(*sit);
		m_groups->Select(0);
		if (sel)
		break;
	case 2://alias
		for (it=m_frame->GetAlias()->begin();it!=m_frame->GetAlias()->end();it++)
		{
			m_items->AppendString(it->GetName());
		}
		
		for (sit=m_alias.begin();sit!=m_alias.end();sit++)
		{
			m_items->Check(m_items->FindString(*sit));
		}
		if (sel)
		{
			m_groups->Clear();
			m_groups->Append(_("All"));
		}
		for (sit = amcAlias::GetAliasGroups()->begin(); sit != amcAlias::GetAliasGroups()->end(); sit++)
			m_groups->Append(*sit);
		m_groups->Select(0);
		if (sel)
		break;
	case 3://buttons
		for (bit=m_frame->GetButtons()->begin();bit!=m_frame->GetButtons()->end();bit++)
		{
			m_items->AppendString(bit->GetName());
		}
		
		for (sit=m_buttons.begin();sit!=m_buttons.end();sit++)
		{
			m_items->Check(m_items->FindString(*sit));
		}
		if (sel)
		{
			m_groups->Clear();
			m_groups->Append(_("All"));
		}
		for (sit = amcButton::GetButtonGroups()->begin(); sit != amcButton::GetButtonGroups()->end(); sit++)
			m_groups->Append(*sit);
		m_groups->Select(0);
		if (sel)
		break;
	case 4://gauges
		if (!m_frame->GetGaugePanes()->empty())
		{
			for (gp=m_frame->GetGaugePanes()->begin();gp!=m_frame->GetGaugePanes()->end();gp++)
			{
				GaugeWindow* gw = (GaugeWindow*)GaugeWindow::FindWindowByName(gp->c_str(), m_frame);
				for (git=gw->GetGauges()->begin();git!=gw->GetGauges()->end();git++)
				{
					m_items->AppendString(git->GetName());
				}
			}
		}
		if (sel)
		{
			m_groups->Clear();
			m_groups->Append(_("All"));
			if (!m_frame->GetGaugePanes()->empty())
			{
				for (gp = m_frame->GetGaugePanes()->begin(); gp != m_frame->GetGaugePanes()->end(); gp++)
				{
					GaugeWindow* gw = (GaugeWindow*)GaugeWindow::FindWindowByName(gp->c_str(), m_frame);
					m_groups->Append(gp->c_str());

				}
			}
			m_groups->Select(0);
		}
		
		if (sel)
		break;
	case 5://hotkeys
		for (hk=m_frame->GetHotkeys()->begin();hk!=m_frame->GetHotkeys()->end();hk++)
		{
			m_items->AppendString(hk->GetName());
		}
		for (sit=m_hks.begin();sit!=m_hks.end();sit++)
		{
			m_items->Check(m_items->FindString(*sit));
		}
		if (sel)
		{
			m_groups->Clear();
			m_groups->Append(_("All"));
		}
		for (sit = amcHotkey::GetHotkeyGroups()->begin(); sit != amcHotkey::GetHotkeyGroups()->end(); sit++)
			m_groups->Append(*sit);
		m_groups->Select(0);
		if (sel)
		break;
	case 6://lists
		for (lit=m_frame->GetLists()->begin();lit!=m_frame->GetLists()->end();lit++)
		{
			m_items->AppendString(lit->GetName());
		}
		for (sit=m_lists.begin();sit!=m_lists.end();sit++)
		{
			m_items->Check(m_items->FindString(*sit));
		}
		if (sel)
		{
			m_groups->Clear();
			m_groups->Append(_("All"));
		}
		for (sit = amcList::GetListGroups()->begin(); sit != amcList::GetListGroups()->end(); sit++)
			m_groups->Append(*sit);
		m_groups->Select(0);
		if (sel)
		break;
	case 7://timers
		for (tiit=m_frame->GetTimers()->begin();tiit!=m_frame->GetTimers()->end();tiit++)
		{
			m_items->AppendString(tiit->GetName());
		}
		for (sit=m_timers.begin();sit!=m_timers.end();sit++)
		{
			m_items->Check(m_items->FindString(*sit));
		}
		if (sel)
		{
			m_groups->Clear();
			m_groups->Append(_("All"));
		}
		for (sit = amcTimer::GetTimerGroups()->begin(); sit != amcTimer::GetTimerGroups()->end(); sit++)
			m_groups->Append(*sit);
		m_groups->Select(0);
		if (sel)
		break;
	case 8://variables
		for (vit=m_frame->GetVars()->begin();vit!=m_frame->GetVars()->end();vit++)
		{
			m_items->AppendString(vit->GetName());
		}
		for (sit=m_vars.begin();sit!=m_vars.end();sit++)
		{
			m_items->Check(m_items->FindString(*sit));
		}
		if (sel)
		{
			m_groups->Clear();
			m_groups->Append(_("All"));
		}
		for (sit = amcVar::GetVarGroups()->begin(); sit != amcVar::GetVarGroups()->end(); sit++)
			m_groups->Append(*sit);
		m_groups->Select(0);
		break;
	default:
		break;
	}
}

void pkg_dlg::OnGroups( wxCommandEvent& event)
{
	al_it it;
	v_it vit;
	tr_it tit;
	hk_it hk;
	t_it tiit;
	li_it lit;
	b_it bit;
	g_it git;
	s_it gp, sit;

	int sel = m_groups->GetSelection();
	int csel = m_choice->GetSelection();
	m_items->Clear();
	wxString s; 
	switch (csel)
	{
	case 0:
		break;
	case 1://actions
		if (sel)
		{
			s = Trigger::GetTriggerClasses()->at(sel - 1);
			for (tit = m_frame->GetTrigger()->begin(); tit != m_frame->GetTrigger()->end(); tit++)
			{
				if (s == tit->GetClass())
					m_items->AppendString(tit->GetLabel());
			}
		}
		else
		{
			for (tit = m_frame->GetTrigger()->begin(); tit != m_frame->GetTrigger()->end(); tit++)
			{
				m_items->AppendString(tit->GetLabel());
			}
		}
		break;
	case 2:
		if (sel)
		{
			s = amcAlias::GetAliasGroups()->at(sel - 1);
			for (it = m_frame->GetAlias()->begin(); it != m_frame->GetAlias()->end(); it++)
			{
				if (s == it->GetGroup())
					m_items->AppendString(it->GetAlias());
			}
		}
		else
		{
			for (it = m_frame->GetAlias()->begin(); it != m_frame->GetAlias()->end(); it++)
			{
				m_items->AppendString(it->GetAlias());
			}
		}
		break;
	case 3:
		if (sel)
		{
			s = amcButton::GetButtonGroups()->at(sel - 1);
			for (bit = m_frame->GetButtons()->begin(); bit != m_frame->GetButtons()->end(); bit++)
			{
				if (s == bit->GetGroup())
					m_items->AppendString(bit->GetName());
			}
		}
		else
		{
			for (bit = m_frame->GetButtons()->begin(); bit != m_frame->GetButtons()->end(); bit++)
			{
				m_items->AppendString(bit->GetName());
			}
		}
		break;
	case 4:
		
		break;
	case 5:
		if (sel)
		{
			s = amcHotkey::GetHotkeyGroups()->at(sel - 1);
			for (hk = m_frame->GetHotkeys()->begin(); hk != m_frame->GetHotkeys()->end(); hk++)
			{
				if (s == hk->GetGroup())
					m_items->AppendString(hk->GetName());
			}
		}
		else
		{
			for (hk = m_frame->GetHotkeys()->begin(); hk != m_frame->GetHotkeys()->end(); hk++)
			{
				m_items->AppendString(hk->GetName());
			}
		}
		break;
	case 6:
		if (sel)
		{
			s = amcList::GetListGroups()->at(sel - 1);
			for (lit = m_frame->GetLists()->begin(); lit != m_frame->GetLists()->end(); lit++)
			{
				if (s == lit->GetGroup())
					m_items->AppendString(lit->GetName());
			}
		}
		else
		{
			for (lit = m_frame->GetLists()->begin(); lit != m_frame->GetLists()->end(); lit++)
			{
				m_items->AppendString(lit->GetName());
			}
		}
		break;
	case 7:
		if (sel)
		{
			s = amcTimer::GetTimerGroups()->at(sel - 1);
			for (tiit = m_frame->GetTimers()->begin(); tiit != m_frame->GetTimers()->end(); tiit++)
			{
				if (s == tiit->GetGroup())
					m_items->AppendString(tiit->GetName());
			}
		}
		else
		{
			for (tiit = m_frame->GetTimers()->begin(); tiit != m_frame->GetTimers()->end(); tiit++)
			{
				m_items->AppendString(tiit->GetName());
			}
		}
		break;
	case 8:
		if (sel)
		{
			s = amcVar::GetVarGroups()->at(sel - 1);
			for (vit = m_frame->GetVars()->begin(); vit != m_frame->GetVars()->end(); vit++)
			{
				if (s == vit->GetGroup())
					m_items->AppendString(vit->GetName());
			}
		}
		else
		{
			for (vit = m_frame->GetVars()->begin(); vit != m_frame->GetVars()->end(); vit++)
			{
				m_items->AppendString(vit->GetName());
			}
		}
		break;
	default:
		break;
	}

}

void pkg_dlg::OnToggle( wxCommandEvent& event )
{
	//wxSetWorkingDirectory(m_frame->GetGlobalOptions()->GetPackageDir());
	int sel = m_choice->GetSelection();
	int item = event.GetInt();
	int x=0;
	int cc=0;
	switch (sel)
	{
	case 0://all
		x = m_frame->GetTrigger()->size();
		if (!m_frame->GetTrigger()->empty() && item<x)
		{
			if (m_items->IsChecked(item))
				m_trigger.push_back(m_frame->GetTrigger()->at(item).GetLabel());
			else
			{
				s_it f = find(m_trigger.begin(),m_trigger.end(), m_frame->GetTrigger()->at(item).GetLabel());
				if (f!=m_trigger.end())
					m_trigger.erase(f);
			}
			break;
		}
		cc = x;
		x += m_frame->GetAlias()->size();
		if (!m_frame->GetAlias()->empty() && item<x)
		{
			if (m_items->IsChecked(item))
				m_alias.push_back(m_frame->GetAlias()->at(item-cc).GetName());
			else
			{
				s_it f = find(m_alias.begin(),m_alias.end(), m_frame->GetAlias()->at(item-cc).GetName());
				if (f!=m_alias.end())
					m_alias.erase(f);
			}
			break;
		}
		cc = x;
		x += m_frame->GetButtons()->size();
		if (!m_frame->GetButtons()->empty() && item<x)
		{
			if (m_items->IsChecked(item))
				m_buttons.push_back(m_frame->GetButtons()->at(item-cc).GetName());
			else
			{
				s_it f = find(m_buttons.begin(),m_buttons.end(), m_frame->GetButtons()->at(item-cc).GetName());
				if (f!=m_buttons.end())
					m_buttons.erase(f);
			}
			break;
		}
		cc = x;
		if (!m_frame->GetGaugePanes()->empty())
		{
			for (s_it gp=m_frame->GetGaugePanes()->begin();gp!=m_frame->GetGaugePanes()->end();gp++)
			{
				GaugeWindow* gw = (GaugeWindow*)GaugeWindow::FindWindowByName(gp->c_str(), m_frame);
				x += gw->GetGauges()->size();
			}
		}
		if (!m_frame->GetGauges()->empty() && item<x)
		{
			if (m_items->IsChecked(item))
				m_gauges.push_back(m_items->GetString(item));
			else
			{
				s_it f = find(m_gauges.begin(),m_gauges.end(), m_items->GetString(item));
				if (f!=m_gauges.end())
					m_gauges.erase(f);
			}
			break;
		}
		cc = x;
		x += m_frame->GetHotkeys()->size();
		if (!m_frame->GetHotkeys()->empty() && item<x)
		{
			if (m_items->IsChecked(item))
				m_hks.push_back(m_frame->GetHotkeys()->at(item-cc).GetName());
			else
			{
				s_it f = find(m_hks.begin(),m_hks.end(), m_frame->GetHotkeys()->at(item-cc).GetName());
				if (f!=m_hks.end())
					m_hks.erase(f);
			}
			break;
		}
		cc = x;
		x += m_frame->GetLists()->size();
		if (!m_frame->GetLists()->empty() && item<x)
		{
			if (m_items->IsChecked(item))
				m_lists.push_back(m_frame->GetLists()->at(item-cc).GetName());
			else
			{
				s_it f = find(m_lists.begin(),m_lists.end(), m_frame->GetLists()->at(item-cc).GetName());
				if (f!=m_lists.end())
					m_lists.erase(f);
			}
			break;
		}
		cc = x;
		x += m_frame->GetTimers()->size();
		if (!m_frame->GetTimers()->empty() && item<x)
		{
			if (m_items->IsChecked(item))
				m_timers.push_back(m_frame->GetTimers()->at(item-cc).GetName());
			else
			{
				s_it f = find(m_timers.begin(),m_timers.end(), m_frame->GetTimers()->at(item-cc).GetName());
				if (f!=m_timers.end())
					m_timers.erase(f);
			}
			break;
		}
		cc = x;
		x += m_frame->GetVars()->size();
		if (!m_frame->GetVars()->empty() && item<x)
		{
			if (m_items->IsChecked(item))
				m_vars.push_back(m_frame->GetVars()->at(item-cc).GetName());
			else
			{
				s_it f = find(m_vars.begin(),m_vars.end(), m_frame->GetVars()->at(item-cc).GetName());
				if (f!=m_vars.end())
					m_vars.erase(f);
			}
		}
		break;
	case 1://trigger
		if (m_items->IsChecked(item))
		{
			wxString n = m_items->GetString(item);
			int idx = m_frame->GetTriggerIndexByLabel(n);
			m_trigger.push_back(m_frame->GetTrigger()->at(idx).GetLabel());
		}
		else
		{
			s_it f = find(m_trigger.begin(),m_trigger.end(), m_frame->GetTrigger()->at(item).GetLabel());
			if (f!=m_trigger.end())
				m_trigger.erase(f);
		}
		break;
	case 2://alias
		if (m_items->IsChecked(item))
		{
			wxString n = m_items->GetString(item);
			int idx = m_frame->GetAliasIndexByLabel(n);
			m_alias.push_back(m_frame->GetAlias()->at(idx).GetName());
		}
		
		else
		{
			s_it f = find(m_alias.begin(),m_alias.end(), m_frame->GetAlias()->at(item).GetName());
			if (f!=m_alias.end())
				m_alias.erase(f);
		}
		break;
	case 3://buttons
		if (m_items->IsChecked(item))
		{
			wxString n = m_items->GetString(item);
			int idx = m_frame->GetButtonIndexByLabel(n);
			m_buttons.push_back(m_frame->GetButtons()->at(idx).GetName());
		}
			
		else
		{
			s_it f = find(m_buttons.begin(),m_buttons.end(), m_frame->GetButtons()->at(item).GetName());
			if (f!=m_buttons.end())
				m_buttons.erase(f);
		}
		break;
	case 4://gauges
		if (m_items->IsChecked(item))
			m_gauges.push_back(m_items->GetString(item));
		else
		{
			s_it f = find(m_gauges.begin(),m_gauges.end(), m_items->GetString(item));
			if (f!=m_gauges.end())
				m_gauges.erase(f);
		}
		break;
	case 5://hotkeys
		if (m_items->IsChecked(item))
		{
			wxString n = m_items->GetString(item);
			int idx = m_frame->GetHkIndexByLabel(n);
			m_hks.push_back(m_frame->GetHotkeys()->at(idx).GetName());
		}
			
		else
		{
			s_it f = find(m_hks.begin(),m_hks.end(), m_frame->GetHotkeys()->at(item).GetName());
			if (f!=m_hks.end())
				m_hks.erase(f);
		}
		break;
	case 6://lists
		if (m_items->IsChecked(item))
		{
			wxString n = m_items->GetString(item);
			int idx = m_frame->GetListIndexByLabel(n);
			m_lists.push_back(m_frame->GetLists()->at(idx).GetName());
		}
			
		else
		{
			s_it f = find(m_lists.begin(),m_lists.end(), m_frame->GetLists()->at(item).GetName());
			if (f!=m_lists.end())
				m_lists.erase(f);
		}
		break;
	case 7://timers
		if (m_items->IsChecked(item))
		{
			wxString n = m_items->GetString(item);
			int idx = m_frame->GetTimerIndexByLabel(n);
			m_timers.push_back(m_frame->GetTimers()->at(idx).GetName());
		}
			
		else
		{
			s_it f = find(m_timers.begin(),m_timers.end(), m_frame->GetTimers()->at(item).GetName());
			if (f!=m_timers.end())
				m_timers.erase(f);
		}
		break;
	case 8://vars
		if (m_items->IsChecked(item))
		{
			wxString n = m_items->GetString(item);
			int idx = m_frame->GetVarIndexByLabel(n);
			m_vars.push_back(m_frame->GetVars()->at(idx).GetName());
		}
			
		else
		{
			s_it f = find(m_vars.begin(),m_vars.end(), m_frame->GetVars()->at(item).GetName());
			if (f!=m_vars.end())
				m_vars.erase(f);
		}
		break;
	default:
		break;
	}
}
