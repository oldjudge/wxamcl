/*! \file gaugewin.h
	\brief header file for gaugewin.cpp
*/

#ifndef GaugeWindow_H
#define GaugeWindow_H

//style defines
#define GAUGE_STANDARD 0
#define GAUGE_LINES 1
#define GAUGE_ROUNDED 2
#define GAUGE_RLINES 3
#define GAUGE_3D 4

#define GAUGE_TEXT_BELOW 0
#define GAUGE_TEXT_ABOVE 1
#define GAUGE_TEXT_GAUGE 2
#define GAUGE_TEXT_NONE	 3
/*! \class GaugeWindow
	\brief class representing an output window.
	
	Window to output graphical gauges 
*/
class GaugeWindow : public wxWindow
{
public:
	DECLARE_DYNAMIC_CLASS(GaugeWindow)
	GaugeWindow();
	GaugeWindow(wxFrame *parent);
	GaugeWindow(wxFrame *parent, wxString name);
	~GaugeWindow();
	int GetGaugeIndexByName(wxString s);
	wxFont* GetFont() {return m_font;}
	void SetFont(wxFont* f) {delete m_font;m_font = new wxFont(*f);}
	std::vector<class amcGauge> * GetGauges() {return &m_gauges;}
	wxString IsTypeOf() {return "amcGaugeWindow";}
	void SetBackgroundCol(wxColour c);
private:
	class MudMainFrame *m_parent;
	wxFont *m_font;
	vector<class amcGauge> m_gauges;
	wxColour m_background;
	//Event handlers
	void OnEraseBackground(wxEraseEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnContextMenu(wxContextMenuEvent& event);
	void OnOutputFont(wxCommandEvent& event);
	DECLARE_EVENT_TABLE()
};

/*! \class amcGauge
	\brief class representing a gauge.
	
	Gauges to be drawn in a GaugeWindow 
*/

class amcGauge
{
public:
	amcGauge();
	~amcGauge();
	amcGauge(wxString winname, wxString name, wxString var1, wxString var2, wxColour fc, wxColour bc, int x=10, int y=10, int cx=100, int cy=40, bool vert=true);
	wxString GetName() {return m_name;}
	void SetLabel(wxString s) {m_label=s;}
	void SetName(wxString s) {m_name=s;}
	bool SetWindow(wxString name);
	void DrawGauge(wxBufferedPaintDC *cdc);
	bool GetVertical() {return m_vertical;}
	void SetVertical(bool b) {m_vertical=b;}
	wxString GetVar1() {return m_var1;}
	wxString GetVar2() {return m_var2;}
	void SetVar1(wxString s) {m_var1=s;}
	void SetVar2(wxString s) {m_var2=s;}
	void SetVarIndices();
	wxColour GetFCol() {return m_fcol;}
	wxColour GetBCol() {return m_bcol;}
	wxColour GetAlarm() {return m_alarm;}
	wxColour GetTextCol() {return m_text;}
	void SetFCol(wxColour c) {m_fcol=c;}
	void SetBCol(wxColour c) {m_bcol=c;}
	void SetAlarmCol(wxColour c) {m_alarm=c;}
	void SetTextCol(wxColour c) {m_text=c;}
	int GetX() {return m_x;}
	int GetY() {return m_y;}
	int GetCx() {return m_cx;}
	int GetCy() {return m_cy;}
	int GetStyle() {return m_style;}
	int GetTextPos() {return m_textpos;}
	int GetAlarmPerc() {return m_alarmperc;}
	bool UseAlarm() {return m_usealarm;}
	bool ShowValue() {return m_showvalue;}
	void SetX(int i) {m_x=i;}
	void SetY(int i) {m_y=i;}
	void SetCx(int i) {m_cx=i;}
	void SetCy(int i) {m_cy=i;}
	void SetStyle(int i) {m_style=i;}
	void SetTextPos(int i) {m_textpos=i;}
	void SetAlarmPerc(int f) {m_alarmperc=f;}
	void SetUseAlarm(bool b) {m_usealarm=b;}
	void SetShowValue(bool b) {m_showvalue=b;}
	void Register() {m_gwin->GetGauges()->push_back(*this);}
private:
	MudMainFrame* m_parent;
	GaugeWindow* m_gwin;
	wxString m_name, m_label;
	wxString m_var1, m_var2;
	int m_idx1, m_idx2, m_x, m_y, m_cx, m_cy;
	wxColour m_fcol, m_bcol;
	wxColour m_alarm;
	wxColour m_text;
	int m_textpos;
	bool m_vertical;
	bool m_on;
	float m_perc;
	int m_alarmperc;
	bool m_usealarm;
	int m_style;
	bool m_showvalue;
	
};
typedef std::vector<class amcGauge>::iterator g_it;
#endif
