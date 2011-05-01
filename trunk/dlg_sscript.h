///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __dlg_sscript__
#define __dlg_sscript__

#include <wx/intl.h>

#include "scriptedit.h"
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class dlg_sscr
///////////////////////////////////////////////////////////////////////////////
class dlg_sscr : public wxDialog 
{
	private:
	
	protected:
		amcScriptEdit *m_sce;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
	
	public:
		dlg_sscr( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 613,578 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~dlg_sscr();
	
};

#endif //__dlg_sscript__
