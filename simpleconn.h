///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __simpleconn__
#define __simpleconn__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/combobox.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class DlgSimpleConn
///////////////////////////////////////////////////////////////////////////////
class DlgSimpleConn : public wxDialog 
{
	private:
	
	public:
		wxStaticText* label_1;
		wxComboBox* m_server;
		wxStaticText* label_2;
		wxTextCtrl* text_ctrl_2;
		wxButton* but1;
		wxButton* but2;
		wxString* m_ip;
		wxString* m_port;
	public:
		DlgSimpleConn( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Connect"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~DlgSimpleConn();
	
};

#endif //__simpleconn__
