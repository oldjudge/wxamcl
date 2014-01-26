
#include "main.h"
#include "dialog_optionen.h"
dlg_options::dlg_options( wxWindow* parent )
:
DlgOptions( parent )
{
	
	#ifndef WXOSX
	m_nb->GetImageList()->Add(wxArtProvider::GetBitmap(wxART_GO_HOME, wxART_FRAME_ICON), wxArtProvider::GetNativeSizeHint(wxART_FRAME_ICON));
	m_nb->GetImageList()->Add(wxArtProvider::GetBitmap(wxART_NEW, wxART_FRAME_ICON), wxArtProvider::GetNativeSizeHint(wxART_FRAME_ICON));
	m_nb->GetImageList()->Add(wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_FRAME_ICON), wxArtProvider::GetNativeSizeHint(wxART_FRAME_ICON));
	m_nb->SetPageImage(0, 0);
	m_nb->SetPageImage(1, 1);
	m_nb->SetPageImage(2, 2);
	#endif
	m_nb->SetSelection(0);
	m_frame = (MudMainFrame*)parent;
	m_cs = m_frame->GetGlobalOptions()->GetCommand();
	m_textcomm->SetValidator(wxTextValidator(wxFILTER_NONE, &m_cs));
	m_csep = m_frame->GetGlobalOptions()->GetSep();
	m_textsep->SetValidator(wxTextValidator(wxFILTER_NONE, &m_csep));
	m_sw = m_frame->GetGlobalOptions()->GetSpeedwalk();
	m_textsw->SetValidator(wxTextValidator(wxFILTER_NONE, &m_sw));
	m_swr = m_frame->GetGlobalOptions()->GetRevSpeedwalk();
	m_textswr->SetValidator(wxTextValidator(wxFILTER_NONE, &m_swr));
	m_scr = m_frame->GetGlobalOptions()->GetScript();
	m_textscript->SetValidator(wxTextValidator(wxFILTER_NONE, &m_scr));
	m_var = m_frame->GetGlobalOptions()->GetVar();
	m_textvar->SetValidator(wxTextValidator(wxFILTER_NONE, &m_var));
	m_list = m_frame->GetGlobalOptions()->GetListVar();
	m_listvar->SetValidator(wxTextValidator(wxFILTER_NONE, &m_list));
	m_lbuf = m_frame->m_child->GetMaxLines();
	m_linebuf->SetValidator(wxGenericValidator(&m_lbuf));
	m_hist = m_frame->GetGlobalOptions()->GetMaxHist();
	m_histsize->SetValidator(wxGenericValidator(&m_hist));
	m_ki = m_frame->m_input->GetKeepInput();
	m_keepin->SetValidator(wxGenericValidator(&m_ki));
	m_pi = m_frame->m_input->GetParse();
	m_parsein->SetValidator(wxGenericValidator(&m_pi));
	m_tabdlg2 = m_frame->m_input->GetTabDlg();
	m_tabdlg->SetValidator(wxGenericValidator(&m_tabdlg2));
	m_mccp2 = m_frame->GetGlobalOptions()->UseMCCP();
	m_mccp->SetValidator(wxGenericValidator(&m_mccp2));
	m_mxp2 = m_frame->GetGlobalOptions()->UseMXP();
	m_mxp->SetValidator(wxGenericValidator(&m_mxp2));
	m_msp2 = m_frame->GetGlobalOptions()->UseMSP();
	m_msp->SetValidator(wxGenericValidator(&m_msp2));
	m_atcp2 = m_frame->GetGlobalOptions()->UseATCP();
	m_atcp->SetValidator(wxGenericValidator(&m_atcp2));
	m_gmcp2 = m_frame->GetGlobalOptions()->UseATCP2();
	m_gmcp->SetValidator(wxGenericValidator(&m_gmcp2));
	m_msdp2 = m_frame->GetGlobalOptions()->UseMSDP();
	m_useMSDP->SetValidator(wxGenericValidator(&m_msdp2));
	m_aard2 = m_frame->GetGlobalOptions()->UseAard();
	m_useaardopts->SetValidator(wxGenericValidator(&m_aard2));
	m_naws2 = m_frame->GetGlobalOptions()->UseNAWS();
	m_naws->SetValidator(wxGenericValidator(&m_naws2));
	m_iacgaeor2 = m_frame->GetGlobalOptions()->UseGAEOR();
	m_iacgaeor->SetValidator(wxGenericValidator(&m_iacgaeor2));
	m_utf8_2 = m_frame->GetGlobalOptions()->UseUTF8();
	m_utf8->SetValidator(wxGenericValidator(&m_utf8_2));
	m_ipv62 = m_frame->m_child->GetUseIPV6();
	m_ipv6->SetValidator(wxGenericValidator(&m_ipv62));
	m_events = m_frame->GetGlobalOptions()->GetUseEvents();
	m_evall->SetValidator(wxGenericValidator(&m_events));
	m_evconn = m_frame->GetGlobalOptions()->GetUseEvConn();
	m_onconnect->SetValidator(wxGenericValidator(&m_evconn));
	m_evrecv = m_frame->GetGlobalOptions()->GetUseEvRecv();
	m_precv->SetValidator(wxGenericValidator(&m_evrecv));
	m_evdisco = m_frame->GetGlobalOptions()->GetUseEvDisco();
	m_ondisconnect->SetValidator(wxGenericValidator(&m_evdisco));
	m_evtelnetdata = m_frame->GetGlobalOptions()->GetUseEvTelnetData();
	m_ontelnetdata->SetValidator(wxGenericValidator(&m_evtelnetdata));
	m_evgmcpdata = m_frame->GetGlobalOptions()->GetUseEvGMCPData();
	m_ongmcpdata->SetValidator(wxGenericValidator(&m_evgmcpdata));
	m_evmsdpdata = m_frame->GetGlobalOptions()->GetUseEvMSDPData();
	m_onmsdpdata->SetValidator(wxGenericValidator(&m_evmsdpdata));
	m_evfile = m_frame->GetGlobalOptions()->GetEventFile();
	wxSetWorkingDirectory(m_frame->GetGlobalOptions()->GetScriptDir());
	m_eventfile->SetPath(m_evfile);
	m_urls = m_frame->m_child->UseClickURLs();
	mm_clickurl->SetValidator(wxGenericValidator(&m_urls));
	m_split = m_frame->UseSplitter();
	m_usesplit->SetValidator(wxGenericValidator(&m_split));
	m_ac = m_frame->GetGlobalOptions()->GetAutoConnect();
	m_autoreconnect->SetValidator(wxGenericValidator(&m_ac));
	m_acdel = m_frame->GetGlobalOptions()->GetACDelay();
	m_acdelay->SetValue((int)m_acdel);
	m_acdelay->SetValidator(wxGenericValidator((int*)&m_acdel));
	if (!m_events)
	{
		m_onconnect->Disable();
		m_ondisconnect->Disable();
		m_precv->Disable();
		m_ontelnetdata->Disable();
		m_ongmcpdata->Disable();
		m_onmsdpdata->Disable();
	}
	else
	{
		m_onconnect->Enable();
		m_ondisconnect->Enable();
		m_precv->Enable();
		m_ontelnetdata->Enable();
		m_ongmcpdata->Enable();
		m_onmsdpdata->Enable();
	}
	m_gmcpmodules->SetValue(wxEmptyString);
	for (int i=0;i<m_frame->GetGlobalOptions()->GetGMCPModules()->size();i++)
	{
		m_gmcpmodules->WriteText(m_frame->GetGlobalOptions()->GetGMCPModules()->at(i));
		m_gmcpmodules->WriteText('\n');
	}
	//wxFileName file;
	//file.Assign("/home/andreas/.wxAmc/scripts/events.lua");
	//m_eventfile->SetPath("/home/andreas/.bashrc");
	//m_eventfile->SetFileName(file);
	//Output
	m_ansi = m_frame->m_child->UseAnsi();
	m_ansion->SetValidator(wxGenericValidator(&m_ansi));
	m_time = m_frame->m_child->UseTimeStamps();
	m_timestamp->SetValidator(wxGenericValidator(&m_time));
	m_millis = m_frame->m_child->UseMilliSeconds();
	m_milli->SetValidator(wxGenericValidator(&m_millis));
	m_echo = m_frame->GetGlobalOptions()->GetEcho();
	m_localecho->SetValidator(wxGenericValidator(&m_echo));
	m_techo = m_frame->GetGlobalOptions()->GetTriggerEcho();
	m_triggerecho->SetValidator(wxGenericValidator(&m_techo));
	m_secho = m_frame->IsVerbose();
	m_scriptverbose->SetValidator(wxGenericValidator(&m_secho));
	m_usew = m_frame->GetGlobalOptions()->UseWrap();
	m_usewrap->SetValidator(wxGenericValidator(&m_usew));
	m_autow = m_frame->GetGlobalOptions()->AutoWrap();
	m_autowrap->SetValidator(wxGenericValidator(&m_autow));
	m_wr = m_frame->m_child->GetWrap();
	m_linewrap->SetValidator(wxGenericValidator(&m_wr));
	if (!m_usew)
	{
		m_autowrap->Disable();
		m_linewrap->Disable();
	}
	if (m_autow)
		m_linewrap->Disable();
	//Prompt
	m_prompt = m_frame->m_child->LockPrompt();
	m_lock->SetValidator(wxGenericValidator(&m_prompt));
	m_gag = m_frame->m_child->GagPrompt();
	m_gagprompt->SetValidator(wxGenericValidator(&m_gag));
	m_regexp = m_frame->m_child->GetPromptRegExp();
	m_promptpattern->SetValidator(wxTextValidator(wxFILTER_NONE, &m_regexp));

	m_font->SetSelectedFont(*m_frame->m_child->GetFont());
	m_col1->SetColour(m_frame->m_child->GetColour(0));
	m_col2->SetColour(m_frame->m_child->GetColour(1));
	m_col3->SetColour(m_frame->m_child->GetColour(2));
	m_col4->SetColour(m_frame->m_child->GetColour(3));
	m_col5->SetColour(m_frame->m_child->GetColour(4));
	m_col6->SetColour(m_frame->m_child->GetColour(5));
	m_col7->SetColour(m_frame->m_child->GetColour(6));
	m_col8->SetColour(m_frame->m_child->GetColour(7));
	m_col9->SetColour(m_frame->m_child->GetColour(8));
	m_col10->SetColour(m_frame->m_child->GetColour(9));
	m_col11->SetColour(m_frame->m_child->GetColour(10));
	m_col12->SetColour(m_frame->m_child->GetColour(11));
	m_col13->SetColour(m_frame->m_child->GetColour(12));
	m_col14->SetColour(m_frame->m_child->GetColour(13));
	m_col15->SetColour(m_frame->m_child->GetColour(14));
	m_col16->SetColour(m_frame->m_child->GetColour(15));

	m_echocol->SetColour(m_frame->m_child->GetColour(16));
	m_clientcol->SetColour(m_frame->m_child->GetColour(17));
	m_customcol->SetColour(m_frame->m_child->GetColour(18));
	BuildSample();
	//Logging
	m_dirPicker1->SetPath(m_frame->GetGlobalOptions()->GetLogDir());
	m_startlog->SetValue(m_frame->m_child->IsLogging());
	m_inc = m_frame->m_child->GetInclude();
	m_includescroll->SetValidator(wxGenericValidator(&m_inc));
	m_timest = m_frame->m_child->IsDateLogging();
	m_ts->SetValidator(wxGenericValidator(&m_timest));
	if(m_frame->m_child->IsHtmlLogging())
		m_lognr = 0;
	else if (m_frame->m_child->IsAnsiLogging())
		m_lognr = 2;
	else m_lognr = 1;
	if (!m_frame->m_child->IsLogging())
	{
		m_startlog->SetLabel(_("Start logging"));
	}
	else
	{
		m_startlog->SetLabel(_("Stop logging"));
	}
	m_logopts->SetSelection(m_lognr);
	//dirs
	m_workdir->SetPath(m_frame->GetGlobalOptions()->GetWorkDir());
	m_workdir->SetLabelText("..");
	m_profdir->SetPath(m_frame->GetGlobalOptions()->GetProfileDir());
	m_scriptdir->SetPath(m_frame->GetGlobalOptions()->GetScriptDir());
	m_packdir->SetPath(m_frame->GetGlobalOptions()->GetPackageDir());
	m_dbdir->SetPath(m_frame->GetGlobalOptions()->GetDatabaseDir());
	m_mspdir->SetPath(m_frame->GetGlobalOptions()->GetSoundDir());
	m_luadir->SetPath(m_frame->GetGlobalOptions()->GetLuaDir());
}

void dlg_options::OnTabList(wxCommandEvent &event)
{
	dlg_tabedit * tab = new dlg_tabedit(this);
	
	if (tab->ShowModal()==wxID_OK)
	{
	}
	tab->Destroy();
	
}

void dlg_options::OnFontChanged(wxFontPickerEvent &event)
{
	wxFont f = m_font->GetSelectedFont();
	if (f.IsOk())
	{
		m_frame->m_child->SetNFont(&f);
		m_frame->m_child->SetUFont(&f);
		BuildSample();
	}
	m_frame->m_child->Refresh();
	m_frame->m_child->Update();
}

void dlg_options::OnDefaultColors(wxCommandEvent &event)
{
	m_frame->m_child->SetDefaultColors();
	m_col1->SetColour(m_frame->m_child->GetColour(0));
	m_col2->SetColour(m_frame->m_child->GetColour(1));
	m_col3->SetColour(m_frame->m_child->GetColour(2));
	m_col4->SetColour(m_frame->m_child->GetColour(3));
	m_col5->SetColour(m_frame->m_child->GetColour(4));
	m_col6->SetColour(m_frame->m_child->GetColour(5));
	m_col7->SetColour(m_frame->m_child->GetColour(6));
	m_col8->SetColour(m_frame->m_child->GetColour(7));
	m_col9->SetColour(m_frame->m_child->GetColour(8));
	m_col10->SetColour(m_frame->m_child->GetColour(9));
	m_col11->SetColour(m_frame->m_child->GetColour(10));
	m_col12->SetColour(m_frame->m_child->GetColour(11));
	m_col13->SetColour(m_frame->m_child->GetColour(12));
	m_col14->SetColour(m_frame->m_child->GetColour(13));
	m_col15->SetColour(m_frame->m_child->GetColour(14));
	m_col16->SetColour(m_frame->m_child->GetColour(15));

	m_echocol->SetColour(m_frame->m_child->GetColour(16));
	m_clientcol->SetColour(m_frame->m_child->GetColour(17));
	m_customcol->SetColour(m_frame->m_child->GetColour(18));
	BuildSample();
}

void dlg_options::OnColor(wxColourPickerCtrl* ct, int idx)
{
	wxColour c = ct->GetColour();
	if (c.IsOk())
	{
		m_frame->m_child->SetColour(idx, c);
		BuildSample();
		if (!idx)
		{
			wxGetApp().GetFrame()->SetBackgroundColour(c);
			wxGetApp().GetFrame()->ClearBackground();
			wxGetApp().GetChild()->SetBackgroundColour(c);
			wxGetApp().GetChild()->SetBackgroundCol(c);
			wxGetApp().GetChild()->ClearBackground();
			wxGetApp().GetChild()->Refresh();
			wxGetApp().GetChild()->Update();
			m_frame->m_splitter->SetBackgroundCol(c);
		}
	}
}

void dlg_options::OnCol1(wxColourPickerEvent &event)
{
	OnColor(m_col1, 0);
	
}

void dlg_options::OnCol2(wxColourPickerEvent &event)
{
	OnColor(m_col2, 1);
}

void dlg_options::OnCol3(wxColourPickerEvent &event)
{
	OnColor(m_col3, 2);
}

void dlg_options::OnCol4(wxColourPickerEvent &event)
{
	OnColor(m_col4, 3);
}

void dlg_options::OnCol5(wxColourPickerEvent &event)
{
	OnColor(m_col5, 4);
}

void dlg_options::OnCol6(wxColourPickerEvent &event)
{
	OnColor(m_col6, 5);
}

void dlg_options::OnCol7(wxColourPickerEvent &event)
{
	OnColor(m_col7, 6);
}

void dlg_options::OnCol8(wxColourPickerEvent &event)
{
	OnColor(m_col8, 7);
}

void dlg_options::OnCol9(wxColourPickerEvent &event)
{
	OnColor(m_col9, 8);
}

void dlg_options::OnCol10(wxColourPickerEvent &event)
{
	OnColor(m_col10, 9);
}

void dlg_options::OnCol11(wxColourPickerEvent &event)
{
	OnColor(m_col11, 10);
}

void dlg_options::OnCol12(wxColourPickerEvent &event)
{
	OnColor(m_col12, 11);
}

void dlg_options::OnCol13(wxColourPickerEvent &event)
{
	OnColor(m_col13, 12);
}

void dlg_options::OnCol14(wxColourPickerEvent &event)
{
	OnColor(m_col14, 13);
}

void dlg_options::OnCol15(wxColourPickerEvent &event)
{
	OnColor(m_col15, 14);
}

void dlg_options::OnCol16(wxColourPickerEvent &event)
{
	OnColor(m_col16, 15);
}

void dlg_options::OnColEcho(wxColourPickerEvent &event)
{
	OnColor(m_echocol, 16);
}

void dlg_options::OnColClient(wxColourPickerEvent &event)
{
	OnColor(m_clientcol, 17);
}

void dlg_options::OnColCustom(wxColourPickerEvent &event)
{
	OnColor(m_customcol, 18);
}

void dlg_options::BuildSample()
{
	m_sample->Clear();
	//wxRichTextAttr ra((m_frame->m_child->GetColour(7), m_frame->m_child->GetColour(0));
	//m_sample->SetBasicStyle(ra);
	
	m_sample->SetBackgroundColour(m_frame->m_child->GetColour(0));
	m_sample->SetFont(*m_frame->m_child->GetFont());
	m_sample->BeginTextColour(m_frame->m_child->GetColour(7));
	m_sample->WriteText(_("Mud Output looks like this"));
	m_sample->EndTextColour();
	m_sample->Newline();
	//m_sample->BeginTextColour(m_frame->m_child->GetColour(16));
	m_sample->BeginTextColour(m_frame->m_child->GetAnsiColor(16));
	m_sample->WriteText(_("Echo color looks like this"));
	m_sample->EndTextColour();
	m_sample->Newline();
	m_sample->BeginTextColour(m_frame->m_child->GetColour(17));
	m_sample->WriteText(_("Client messages look like this"));
	m_sample->Newline();
	m_sample->EndTextColour();
	m_sample->BeginTextColour(m_frame->m_child->GetColour(18));
	m_sample->WriteText(_("Custom color looks like this"));
	m_sample->EndTextColour();
}

void dlg_options::OnUseWrap(wxCommandEvent &event)
{
	if (m_usewrap->GetValue())
	{
		m_autowrap->Enable();
		if (!m_autowrap->GetValue())
			m_linewrap->Enable();
		else m_linewrap->Disable();
	}
	else
	{
		m_autowrap->Disable();
		m_linewrap->Disable();
	}
}

void dlg_options::OnAutoWrap(wxCommandEvent &event)
{
	if (m_autowrap->GetValue())
	{
		m_linewrap->Disable();
	}
	else m_linewrap->Enable();
}

void dlg_options::OnUseEvents(wxCommandEvent &event)
{
	if (m_evall->GetValue())
	{
		m_onconnect->SetValue(true);
		m_precv->SetValue(true);
		m_ondisconnect->SetValue(true);
		m_ontelnetdata->SetValue(true);
		m_ongmcpdata->SetValue(true);
		m_onmsdpdata->SetValue(true);
		m_onconnect->Enable();
		m_precv->Enable();
		m_ondisconnect->Enable();
		m_ontelnetdata->Enable();
		m_ongmcpdata->Enable();
		m_onmsdpdata->Enable();
		
	}
	else
	{
		m_onconnect->SetValue(false);
		m_precv->SetValue(false);
		m_ondisconnect->SetValue(false);
		m_ontelnetdata->SetValue(false);
		m_ongmcpdata->SetValue(false);
		m_onmsdpdata->SetValue(false);
		m_onconnect->Disable();
		m_precv->Disable();
		m_ondisconnect->Disable();
		m_ontelnetdata->Disable();
		m_ongmcpdata->Disable();
		m_onmsdpdata->Disable();
	}
}

void dlg_options::OnStartLogging(wxCommandEvent &event)
{
	if (m_frame->m_child->IsLogging())
	{
		m_frame->m_child->SetLogging(false);
		m_startlog->SetLabel(_("Start logging"));
	}
	else
	{
		m_frame->m_child->SetLogging(true);
		m_startlog->SetLabel(_("Stop logging"));
		m_frame->m_child->SetHtmlLogging(m_logopts->GetSelection()==0);
		m_frame->m_child->SetAnsiLogging(m_logopts->GetSelection()==2);
		m_frame->m_child->SetDateLogging(m_ts->GetValue());
		m_frame->m_child->SetInclude(m_includescroll->GetValue());
		wxString path = m_dirPicker1->GetPath();
		wxString file = m_logfile->GetValue();
		wxSetWorkingDirectory(path);
		wxFile *f = new wxFile(file, wxFile::write);
		
		if (m_frame->m_child->IsHtmlLogging())
		{
			m_frame->m_child->SetHtmlLog(f);
			m_frame->m_child->WriteHtmlHeader(f);
		}
		else
		{
			m_frame->m_child->SetTextLog(f);
		}
		if (m_frame->m_child->GetInclude())
		{
			for (int i =0;i<m_frame->m_child->m_curline-1;i++)
			{
				m_frame->m_child->SendLineToLog(i);
			}
		}
	}
}


