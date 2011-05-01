///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __script_dlg__
#define __script_dlg__

#include <wx/intl.h>

#include "scriptedit.h"
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/fontpicker.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class scriptedit
///////////////////////////////////////////////////////////////////////////////
class scriptedit : public wxDialog 
{
	private:
	
	protected:
		amcScriptEdit *m_sce;
		wxStaticText* m_file;
		wxButton* m_load;
		wxButton* m_save;
		wxButton* m_saveas;
		wxButton* m_run;
		wxFontPickerCtrl* m_scfont;
		wxButton* m_close;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnLoadScript( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSave( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnSaveAs( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnRunScript( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFontChanged( wxFontPickerEvent& event ){ event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		scriptedit( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Script"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxRESIZE_BORDER );
		~scriptedit();
	
};

#endif //__script_dlg__
