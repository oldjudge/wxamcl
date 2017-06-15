///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __DLG_PKG_H__
#define __DLG_PKG_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/choice.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/checklst.h>
#include <wx/checkbox.h>
#include <wx/filepicker.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class dlg_pkg
///////////////////////////////////////////////////////////////////////////////
class dlg_pkg : public wxDialog 
{
	private:
	
	protected:
		wxChoice* m_choice;
		wxChoice* m_groups;
		wxCheckListBox* m_items;
		wxCheckBox* m_checkall;
		wxFilePickerCtrl* m_pkgfile;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGroups( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToggle( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCheckAll( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		dlg_pkg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Create package"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~dlg_pkg();
	
};

#endif //__DLG_PKG_H__
