///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __dlg_regexptest__
#define __dlg_regexptest__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class regexp
///////////////////////////////////////////////////////////////////////////////
class regexp : public wxDialog 
{
	private:
	
	protected:
		wxTextCtrl* m_text;
		wxTextCtrl* m_pattern;
		wxStaticText* m_matches;
		wxButton* m_test;
		wxButton* m_close;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnTest( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		regexp( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Test your Regular Expression"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~regexp();
	
};

#endif //__dlg_regexptest__
