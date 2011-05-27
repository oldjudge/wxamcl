/*! \file amcWindow.h
	\brief header file for amcWindow.cpp
*/

#ifndef amcWindow_H
#define amcWindow_H

/*! \class amcWindow
	\brief class representing an output window.
	
	Window to output whatever 
*/
class amcWindow : public wxWindow
{
public:
	DECLARE_DYNAMIC_CLASS(amcWindow)
	amcWindow();
	amcWindow(wxFrame *parent);
	amcWindow(wxFrame *parent, wxString name);
	~amcWindow();
	wxMemoryDC* GetamcWinDC() {return m_dc;}
	wxString GetLeftHandler() {return m_mouseleft;}
	void SetLeftHandler(wxString s) {m_mouseleft=s;}
	void SetRightHandler(wxString s) {m_mouseright=s;}
	void SetWheelHandler(wxString s) {m_mousewheel=s;}
	void SetMoveHandler(wxString s) {m_mousemove=s;}
	wxString GetEvFile() {return m_evfile;}
	void SetEvFile(wxString s) {m_evfile=s;}
	void SetTip(wxString s) {m_tt->SetTip(s);}
	void EnableMouseEvents() {m_mouseevents=true;}
	void DisableMouseEvents() {m_mouseevents=false;}
	
private:
	class MudMainFrame *m_parent;
	wxFont *m_font;
	wxColour m_background;
	wxBitmap m_bitmap;
	
	wxMemoryDC* m_dc;
	bool m_mouseevents;
	wxString m_evfile;
	wxString m_mousewheel;
	wxString m_mouseleft;
	wxString m_mouseright;
	wxString m_mousemove;
	wxToolTip *m_tt;
	int m_wheelrot;
	//Event handlers
	void OnEraseBackground(wxEraseEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnLeftDown(wxMouseEvent& event);
	void OnRightDown(wxMouseEvent& event);
	void OnMouseWheel(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	void OnEnterWindow(wxMouseEvent& event);
	void OnLeaveWindow(wxMouseEvent& event);
	//void OnContextMenu(wxContextMenuEvent& event);
	//void OnOutputFont(wxCommandEvent& event);
	DECLARE_EVENT_TABLE()
};
#endif