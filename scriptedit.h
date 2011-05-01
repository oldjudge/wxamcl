#ifndef amcScriptEdit_H
#define amcScriptEdit_H
//! wxWidgets/contrib headers
#include <wx/stc/stc.h>  // styled text control

class amcScriptEdit: public wxStyledTextCtrl
{
public:
    //! constructor
    amcScriptEdit (wxWindow *parent, wxWindowID id = wxID_ANY,
          const wxPoint &pos = wxDefaultPosition,
          const wxSize &size = wxDefaultSize,
          long style = wxSUNKEN_BORDER|wxVSCROLL
         );

    //! destructor
    ~amcScriptEdit ();
	void SetFontSize(int fs) {m_fontsize=fs;}
	wxFont GetDefFont() {return m_font;}
	void SetFont(wxFont font) {m_font=font;StyleSetFont (wxSTC_STYLE_DEFAULT, font);}
	void OnMarginClick(wxStyledTextEvent& event);
private:
	//const wxString* m_luawords;
	int m_fontsize;
	wxFont m_font;
	DECLARE_EVENT_TABLE()
};

#endif
