///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __tabedit_dlg__
#define __tabedit_dlg__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class tablist
///////////////////////////////////////////////////////////////////////////////
class tablist : public wxDialog 
{
	private:
	
	protected:
		wxTextCtrl* m_tabtext;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnOk( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		tablist( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit tabcompletion list"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~tablist();
	
};

#endif //__tabedit_dlg__
