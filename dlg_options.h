///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __DLG_OPTIONS_H__
#define __DLG_OPTIONS_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/checkbox.h>
#include <wx/gbsizer.h>
#include <wx/button.h>
#include <wx/filepicker.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/radiobox.h>
#include <wx/tglbtn.h>
#include <wx/notebook.h>
#include <wx/imaglist.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class DlgOptions
///////////////////////////////////////////////////////////////////////////////
class DlgOptions : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_CS = 900,
			ID_CSEP,
			ID_CSCRIPT,
			ID_CSP,
			ID_CSPR,
			ID_CV,
			ID_CVL,
			ID_CWORLD
		};
		
		wxNotebook* m_nb;
		wxPanel* m_general;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textcomm;
		wxStaticText* m_staticText5;
		wxTextCtrl* m_textsep;
		wxStaticText* m_staticText6;
		wxTextCtrl* m_textscript;
		wxStaticText* m_staticText41;
		wxTextCtrl* m_textsw;
		wxStaticText* m_staticText51;
		wxTextCtrl* m_textswr;
		wxStaticText* m_staticText17;
		wxSpinCtrl* m_swdelay;
		wxStaticText* m_staticText71;
		wxTextCtrl* m_textvar;
		wxStaticText* m_staticText121;
		wxTextCtrl* m_listvar;
		wxStaticText* m_staticText18;
		wxTextCtrl* m_worldvar;
		wxCheckBox* m_keepin;
		wxCheckBox* m_parsein;
		wxStaticText* m_staticText11;
		wxSpinCtrl* m_histsize;
		wxCheckBox* m_tabdlg;
		wxButton* m_tablist;
		wxCheckBox* m_lock;
		wxCheckBox* m_gagprompt;
		wxStaticText* m_staticText131;
		wxTextCtrl* m_promptpattern;
		wxCheckBox* m_gmcp;
		wxTextCtrl* m_gmcpmodules;
		wxCheckBox* m_mccp;
		wxCheckBox* m_mxp;
		wxCheckBox* m_msp;
		wxCheckBox* m_useMSDP;
		wxCheckBox* m_useaardopts;
		wxCheckBox* m_atcp;
		wxCheckBox* m_iacgaeor;
		wxCheckBox* m_naws;
		wxCheckBox* m_utf8;
		wxCheckBox* m_ipv6;
		wxCheckBox* m_autoreconnect;
		wxSpinCtrl* m_acdelay;
		wxCheckBox* m_evall;
		wxCheckBox* m_onconnect;
		wxCheckBox* m_ondisconnect;
		wxCheckBox* m_precv;
		wxCheckBox* m_ontelnetdata;
		wxCheckBox* m_ongmcpdata;
		wxCheckBox* m_onmsdpdata;
		wxStaticText* m_staticText141;
		wxFilePickerCtrl* m_eventfile;
		wxPanel* m_telnet;
		wxStaticText* m_staticText8;
		wxSpinCtrl* m_linebuf;
		wxFontPickerCtrl* m_font;
		wxCheckBox* m_timestamp;
		wxCheckBox* m_milli;
		wxColourPickerCtrl* m_col1;
		wxColourPickerCtrl* m_col2;
		wxColourPickerCtrl* m_col3;
		wxColourPickerCtrl* m_col4;
		wxColourPickerCtrl* m_col5;
		wxColourPickerCtrl* m_col6;
		wxColourPickerCtrl* m_col7;
		wxColourPickerCtrl* m_col8;
		wxColourPickerCtrl* m_col9;
		wxColourPickerCtrl* m_col10;
		wxColourPickerCtrl* m_col11;
		wxColourPickerCtrl* m_col12;
		wxColourPickerCtrl* m_col13;
		wxColourPickerCtrl* m_col14;
		wxColourPickerCtrl* m_col15;
		wxColourPickerCtrl* m_col16;
		wxCheckBox* m_ansion;
		wxCheckBox* m_localecho;
		wxCheckBox* m_triggerecho;
		wxCheckBox* m_scriptverbose;
		wxColourPickerCtrl* m_echocol;
		wxStaticText* m_staticText12;
		wxColourPickerCtrl* m_clientcol;
		wxStaticText* m_staticText13;
		wxColourPickerCtrl* m_customcol;
		wxStaticText* m_staticText14;
		wxRichTextCtrl* m_sample;
		wxButton* m_button2;
		wxCheckBox* m_usewrap;
		wxCheckBox* m_autowrap;
		wxSpinCtrl* m_linewrap;
		wxCheckBox* mm_clickurl;
		wxCheckBox* m_usesplit;
		wxPanel* m_log;
		wxRadioBox* m_logopts;
		wxCheckBox* m_includescroll;
		wxCheckBox* m_ts;
		wxStaticText* m_staticText15;
		wxDirPickerCtrl* m_dirPicker1;
		wxStaticText* m_staticText16;
		wxTextCtrl* m_logfile;
		wxToggleButton* m_startlog;
		wxDirPickerCtrl* m_workdir;
		wxDirPickerCtrl* m_profdir;
		wxDirPickerCtrl* m_scriptdir;
		wxDirPickerCtrl* m_packdir;
		wxDirPickerCtrl* m_dbdir;
		wxDirPickerCtrl* m_mspdir;
		wxDirPickerCtrl* m_luadir;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnTabList( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUseEvents( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFontChanged( wxFontPickerEvent& event ) { event.Skip(); }
		virtual void OnCol1( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnCol2( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnCol3( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnCol4( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnCol5( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnCol6( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnCol7( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnCol8( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnCol9( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnCol10( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnCol11( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnCol12( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnCol13( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnCol14( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnCol15( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnCol16( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnColEcho( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnColClient( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnColCustom( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnDefaultColors( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUseWrap( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAutoWrap( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStartLogging( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		DlgOptions( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Options"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~DlgOptions();
	
};

#endif //__DLG_OPTIONS_H__
