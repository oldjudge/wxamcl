///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 10 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __OBJECTS_DLGS_H__
#define __OBJECTS_DLGS_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/treectrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include "scriptedit.h"
#include <wx/combobox.h>
#include <wx/tglbtn.h>
#include <wx/spinctrl.h>
#include <wx/checkbox.h>
#include "amccombo.h"
#include <wx/gbsizer.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/listctrl.h>
#include <wx/choice.h>
#include <wx/radiobox.h>
#include <wx/clrpicker.h>
#include <wx/slider.h>
#include <wx/notebook.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class ObjDlg
///////////////////////////////////////////////////////////////////////////////
class ObjDlg : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_TREE = 1000,
			ID_TOGGLECLASS,
			ID_ADDACTION,
			ID_EDITACTION,
			ID_DELACTION,
			ID_LALIAS,
			ID_ADDALIAS,
			ID_EDITALIAS,
			ID_DELALIAS
		};
		
		wxNotebook* m_notebook;
		wxPanel* m_trigger;
		wxStaticText* m_staticText6;
		wxTextCtrl* m_label;
		wxStaticText* m_staticText10;
		wxTextCtrl* m_pattern;
		wxButton* m_patternedit;
		wxStaticText* m_staticText11;
		amcScriptEdit* m_action;
		wxButton* m_sceditor;
		wxStaticText* m_staticText13;
		wxComboBox* m_class;
		wxToggleButton* m_onoff;
		wxButton* m_delclass;
		wxStaticText* m_staticText14;
		wxSpinCtrl* m_prior;
		wxStaticText* m_staticText9;
		wxSpinCtrl* m_lines;
		wxCheckBox* m_oncolor;
		amcColorComboBox *m_amccombo;
		wxStaticText* m_staticText8;
		wxTextCtrl* m_matched;
		wxCheckBox* m_tron;
		wxButton* m_rextest;
		wxCheckBox* m_sendscript;
		wxButton* m_btadd;
		wxButton* m_btedit;
		wxButton* m_btdel;
		wxPanel* m_alias;
		wxListCtrl* m_listalias;
		wxStaticText* m_staticText61;
		wxTextCtrl* m_defalias;
		wxStaticText* m_staticText7;
		wxTextCtrl* m_defaction;
		wxStaticText* m_staticText101;
		wxComboBox* m_groupcombo;
		wxCheckBox* m_alfilter;
		wxToggleButton* m_groupon;
		wxCheckBox* m_alon;
		wxButton* m_delgroup;
		wxButton* m_addalias;
		wxButton* m_editalias;
		wxButton* m_delalias;
		wxPanel* m_buttons;
		wxTreeCtrl* m_treeCtrl3;
		wxStaticText* m_staticText371;
		wxTextCtrl* m_butlabel;
		wxStaticText* m_staticText38;
		wxTextCtrl* m_butcommand;
		wxStaticText* m_staticText39;
		wxComboBox* m_parenttool;
		wxStaticText* Bitmap;
		wxTextCtrl* m_bitmap;
		wxButton* m_addbutton;
		wxButton* m_editbutton;
		wxButton* m_delbutton;
		wxPanel* m_gauge;
		wxTreeCtrl* m_gaugew;
		wxStaticText* m_staticText24;
		wxTextCtrl* m_gaugelabel;
		wxStaticText* m_staticText25;
		wxChoice* m_var1;
		wxStaticText* m_staticText26;
		wxChoice* m_var2;
		wxRadioBox* m_gaugedir;
		wxChoice* m_drawstyle;
		wxStaticText* m_staticText36;
		wxChoice* m_textpos;
		wxStaticText* m_staticText37;
		wxColourPickerCtrl* m_gaugetextcol;
		wxCheckBox* m_showvalue;
		wxStaticText* m_staticText32;
		wxSpinCtrl* m_posx;
		wxStaticText* m_staticText33;
		wxSpinCtrl* m_posy;
		wxStaticText* m_staticText34;
		wxSpinCtrl* m_width;
		wxStaticText* m_staticText35;
		wxSpinCtrl* m_height;
		wxStaticText* m_staticText351;
		wxComboBox* m_parentw;
		wxStaticText* m_staticText27;
		wxColourPickerCtrl* m_fore;
		wxStaticText* m_staticText28;
		wxColourPickerCtrl* m_back;
		wxStaticText* m_staticText29;
		wxColourPickerCtrl* m_alarm;
		wxSlider* m_alarmslider;
		wxStaticText* m_staticText40;
		wxButton* m_addgauge;
		wxButton* m_editgauge;
		wxButton* m_delgauge;
		wxPanel* m_hotkey;
		wxListCtrl* m_listhkey;
		wxStaticText* m_text11;
		amcHotkeyCtrl *m_hkey;
		wxButton* m_groupdel;
		wxStaticText* m_staticText12;
		wxTextCtrl* m_hkeyaction;
		wxCheckBox* m_hkeyon;
		wxComboBox* m_hkcombo;
		wxStaticText* m_staticText131;
		wxToggleButton* m_hkgroupoff;
		wxCheckBox* m_hkfilter;
		wxButton* m_addkey;
		wxButton* m_editkey;
		wxButton* m_delkey;
		wxPanel* m_list;
		wxListCtrl* m_listlist;
		wxStaticText* m_staticText17;
		wxTextCtrl* m_deflist;
		wxStaticText* m_staticText18;
		wxComboBox* m_items;
		wxButton* m_additem;
		wxStaticText* m_sgroup;
		wxComboBox* m_ligroup;
		wxCheckBox* m_lifilter;
		wxToggleButton* m_ligroupoff;
		wxCheckBox* m_lion;
		wxButton* m_lidelgroup;
		wxButton* m_addlist;
		wxButton* m_editlist;
		wxButton* m_dellist;
		wxPanel* m_timer;
		wxListCtrl* m_timerlist;
		wxStaticText* m_staticText171;
		wxTextCtrl* m_deftimer;
		wxStaticText* m_staticText181;
		wxTextCtrl* m_timeraction;
		wxStaticText* m_sgroup1;
		wxComboBox* m_tigroup;
		wxCheckBox* m_tifilter;
		wxToggleButton* m_tigroupoff;
		wxCheckBox* m_ton;
		wxButton* m_tidelgroup;
		wxStaticText* m_staticText23;
		wxSpinCtrl* m_rep;
		wxTextCtrl* m_intervall;
		wxButton* m_addtimer;
		wxButton* m_edittimer;
		wxButton* m_deltimer;
		wxButton* m_tstart;
		wxPanel* m_var;
		wxListCtrl* m_listvar;
		wxStaticText* m_staticText611;
		wxTextCtrl* m_defvar;
		wxStaticText* m_staticText71;
		wxTextCtrl* m_varvalue;
		wxStaticText* m_staticText1011;
		wxComboBox* m_vargroup;
		wxCheckBox* m_vfilter;
		wxToggleButton* m_vgroupoff;
		wxCheckBox* m_von;
		wxButton* m_vdelgroup;
		wxButton* m_addvar;
		wxButton* m_editvar;
		wxButton* m_delvar;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInitObjects( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnPageChanged( wxNotebookEvent& event ) { event.Skip(); }
		virtual void OnActionBeginLabelEdit( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnActionEndLabelEdit( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnTreeItemMenu( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnTreeSelChanged( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnPatternEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSceditor( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClassToggle( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDelClass( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnColourCheck( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTriggerOn( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRegExpTest( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSendToScript( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnActionAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnActionEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnActionDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnItemSelected( wxListEvent& event ) { event.Skip(); }
		virtual void OnGroupChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGroupOff( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAliasOn( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGroupDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAliasAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAliasEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAliasDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonSelChanged( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnButtonAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGaugeTreeSelChanged( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnAddGauge( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditGauge( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDelGauge( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHkSelected( wxListEvent& event ) { event.Skip(); }
		virtual void OnHkGroupDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHkOn( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHkGroupChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHkGroupToggle( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHotkeyAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHotkeyEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHotkeyDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnListSelected( wxListEvent& event ) { event.Skip(); }
		virtual void OnAddItem( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLGroupChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnListGroupoff( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnListOn( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteListGroup( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnListAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnListEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnListDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTimerSelected( wxListEvent& event ) { event.Skip(); }
		virtual void OnTGroupChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTimerGroupOff( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTimerOn( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteTimerGroup( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTimerAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTimerEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTimerDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTimerStart( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnVarSelected( wxListEvent& event ) { event.Skip(); }
		virtual void OnVGroupChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnVGroupOff( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnVarOn( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnVGroupDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnVarAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnVarEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnVarDelete( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxTreeCtrl* m_tree;
		
		ObjDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Define objects"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~ObjDlg();
	
};

#endif //__OBJECTS_DLGS_H__
