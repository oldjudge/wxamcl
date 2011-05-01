#include <wx/odcombo.h>

//implemented in trigger.cpp
class amcColorComboBox : public wxOwnerDrawnComboBox
{
protected:
	void OnDrawItem(wxDC& dc, const wxRect& rect, int item, int flags) const;
	wxCoord OnMeasureItem(size_t item) const;
	wxCoord OnMeasureItemWidth(size_t item) const;
public:
	amcColorComboBox(wxWindow *parent);
	~amcColorComboBox();
private:
	wxWindow *m_parent;
	wxString m_cols[16];
};

class amcHotkeyCtrl : public wxTextCtrl
{
public:
	amcHotkeyCtrl(wxWindow *parent);
	~amcHotkeyCtrl();
	long GetHotkey() {return m_hotkey;}
	int GetModifier() {return m_mod;}
	wxString GetHkName() {return m_hkname;}
	void SetHotkey(long h) {m_hotkey=h;}
	void SetModifier(int m) {m_mod=m;}
	void SetHkName(wxString s) {m_hkname=s;}
protected:
	void OnKeyDown(wxKeyEvent& event);
	void OnKeyUp(wxKeyEvent& event);
	void OnChar(wxKeyEvent& event);
private:
	wxWindow *m_parent;
	wxString m_key;
	bool m_validkey;
	long m_hotkey;
	int m_mod;
	wxString m_hkname;
};
