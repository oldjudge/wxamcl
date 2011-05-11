///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __connect_dlg__
#define __connect_dlg__

#include <wx/intl.h>

#include <wx/listctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/filepicker.h>
#include <wx/gbsizer.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class connectdlg
///////////////////////////////////////////////////////////////////////////////
class connectdlg : public wxDialog 
{
	private:
	
	protected:
		wxListCtrl* m_list;
		wxStaticText* m_staticText1;
		wxTextCtrl* m_charname;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_pw;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_mudname;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_hostname;
		wxStaticText* m_staticText5;
		wxTextCtrl* m_ip;
		wxStaticText* m_staticText6;
		wxTextCtrl* m_port;
		wxStaticText* m_staticText7;
		wxFilePickerCtrl* m_file;
		wxButton* m_add;
		wxButton* m_edit;
		wxButton* m_del;
		wxButton* m_ok;
		wxButton* m_cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnItemActivate( wxListEvent& event ) { event.Skip(); }
		virtual void OnItemSelected( wxListEvent& event ) { event.Skip(); }
		virtual void OnFileChanged( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void OnAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDelete( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		connectdlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Connect to a mud"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~connectdlg();
	
};

#endif //__connect_dlg__
