#include "main.h"

//#include <wx/listimpl.cpp>
	//WX_DEFINE_LIST(StyleList);
	//WX_DEFINE_LIST(LinesList);

wxString AnsiLine::m_bcodes[16] =
{"\x1b[40m", "\x1b[41m", "\x1b[42m", "\x1b[43m", "\x1b[44m", "\x1b[45m", "\x1b[46m", "\x1b[47m", "\x1b[48m",
"\x1b[49m", "\x1b[50m", "\x1b[51m", "\x1b[52m", "\x1b[53m", "\x1b[54m", "\x1b[55m"};

wxString AnsiLine::m_codes[20] =
{"\x1b[0;30m", "\x1b[0;31m", "\x1b[0;32m", "\x1b[0;33m", "\x1b[0;34m", "\x1b[0;35m", "\x1b[0;36m", "\x1b[0;37m",
"\x1b[1;30m", "\x1b[1;31m", "\x1b[1;32m", "\x1b[1;33m", "\x1b[1;34m", "\x1b[1;35m", "\x1b[1;36m", "\x1b[1;37m",
m_codes[10], m_codes[14]};


AnsiLineElement::AnsiLineElement()
{
	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName(wxT("wxAMC"));
	
	m_fcol.Set(RGB(192,192,192));
	if (frame->m_child)
		m_bcol = frame->m_child->GetAnsiColor(0);
	else m_bcol.Set(RGB(0,0,0));
	m_fcolindex=7;
	m_bcolindex=0;
	m_bfontstyle=0;
	m_bourl=m_mxpsend=m_promptsend=false;
	m_text = wxEmptyString;
	m_len = m_text.length();
	m_hint = wxEmptyString;
	m_url = wxEmptyString;
}

AnsiLineElement::AnsiLineElement(wxString text, int f, int b)
{
	m_text=text;
	m_len=text.length();
	m_bourl=m_mxpsend=m_promptsend=false;
	m_bfontstyle=0;
	m_fcolindex=f;
	m_bcolindex=b;
	MudMainFrame *frame = wxGetApp().GetFrame();//(MudMainFrame*)MudMainFrame::FindWindowByName("wxAMC");
	m_fcol=frame->m_child->GetAnsiColor(f);
	m_bcol=frame->m_child->GetAnsiColor(b);
	m_hint = wxEmptyString;
	m_url = wxEmptyString;
}

AnsiLineElement::AnsiLineElement(const AnsiLineElement& ale)
{
	m_fcolindex = ale.m_fcolindex;
	m_bcolindex = ale.m_bcolindex;
	m_fcol = ale.m_fcol;
	m_bcol = ale.m_bcol;
	m_bfontstyle = ale.m_bfontstyle;
	m_bourl = ale.m_bourl;
	m_mxpsend = ale.m_mxpsend;
	m_promptsend = ale.m_promptsend;
	//m_text = new wxString(*ale.m_text);
	m_text = ale.m_text;
	m_len = m_text.length();
	m_mxpcommand = ale.m_mxpcommand;
	m_mxplabel = ale.m_mxplabel;
	m_hint = ale.m_hint;
	m_url = ale.m_url;
}

AnsiLineElement::~AnsiLineElement()
{
	//delete m_text;
	//m_text = NULL;
}

void AnsiLineElement::SetFCol(int index, wxColour col)
{
	m_fcolindex=index;
	m_fcol=col;
}

void AnsiLineElement::SetBCol(int index, wxColour col)
{
	m_bcolindex=index;
	m_bcol=col;
}

void AnsiLineElement::SetText(wxString text)
{
	//wxASSERT_MSG((m_text->CompareTo(".")!=0), wxT("Falsch"));
	//delete m_text;
	//m_text = new wxString(text);
	m_text.clear();
	/*MudMainFrame *frame = wxGetApp().GetFrame();
	wxCSConv c(frame->GetGlobalOptions()->GetCurEncoding());

	wxString ff(text.To8BitData(), c);
	if (ff.empty())
		ff=text;
	m_text.append(ff);*/
	m_text.append(text);
	//m_text.append(text);
	m_len = m_text.length();
}


wxString AnsiLineElement::GetConvText()
{
	MudMainFrame *frame = wxGetApp().GetFrame();
	if (frame->GetGlobalOptions()->GetCurEncoding()!=wxFONTENCODING_UTF8)
	{
		wxCSConv c(frame->GetGlobalOptions()->GetCurEncoding());
		wxString ff(m_text.To8BitData(), c);
		return ff;
	}
	else return m_text.wx_str();
}

//AnsiLine

AnsiLine::AnsiLine()
{
	m_botriggered=false;
	m_bologged=false;
	m_bofull=false;
	m_bogagme=false;
	m_linenumber=0;
	m_ypos=0;
	m_linetext = wxEmptyString;
	m_ansiline = wxEmptyString;
	m_cdt = wxDateTime::Now();
	m_cdts = wxDateTime::UNow();
}

AnsiLine::AnsiLine(const AnsiLine& al)
{
	m_botriggered= al.m_botriggered;
	m_bologged= al.m_bologged;
	m_bofull = al.m_bofull;
	m_bogagme = al.m_bogagme;
	m_linenumber= al.m_linenumber;
	m_ypos= al.m_ypos;
	//m_linetext = new wxString(*al.m_linetext);
	m_linetext = al.m_linetext;
	m_ansiline = al.m_ansiline;
	//m_vstyle.assign(al.m_vstyle.begin(), al.m_vstyle.end());
	//m_vstyle.reserve(200);
	m_vstyle = al.m_vstyle;
	//for (i=0;i<al.m_vstyle.size();i++)
    //    m_vstyle.push_back(al.m_vstyle.at(i));//al.m_vstyle;
	m_cdt = al.m_cdt;
	m_cdts = al.m_cdts;
}

AnsiLine::~AnsiLine()
{
//	delete m_linetext;
	//m_linetext=NULL;
	m_vstyle.clear();
}

wxString AnsiLine::GetConvLineText()
{
	MudMainFrame *frame = wxGetApp().GetFrame();
	if (frame->GetGlobalOptions()->GetCurEncoding()!=wxFONTENCODING_UTF8)
	{
		wxCSConv c(frame->GetGlobalOptions()->GetCurEncoding());
		wxString ff(m_linetext.To8BitData(), c);
		return ff;
	}
	else return m_linetext;
}

wxString AnsiLine::GetConvAnsiLine()
{
	MudMainFrame *frame = wxGetApp().GetFrame();
	if (frame->GetGlobalOptions()->GetCurEncoding()!=wxFONTENCODING_UTF8)
	{
		wxCSConv c(frame->GetGlobalOptions()->GetCurEncoding());
		wxString ff(m_ansiline.To8BitData(), c);
		return ff;
	}
	else return m_ansiline;
}

size_t AnsiLine::Freq(wxString *st, wxChar ch)
{
size_t t=0;
size_t count=0;

	if (st->empty())
		return 0;
	do
	{
		t=st->find(ch, ++t);
		count++;
	} while (t!=wxString::npos);
	return count-1;
}

int AnsiLine::GetCharFColIndex(int idx)
{
size_t len=0, i;
ale_it it;

	if (m_vstyle.empty())
		return -1;
	if (idx>(int)m_linetext.length())
		return -1;
	for (it=m_vstyle.begin(), i=0;it!=m_vstyle.end();it++, i++)
	{
		len += m_vstyle.at(i).GetLen();
		if (idx<=(int)len)
			break;
	}
	return (int)m_vstyle.at(i).GetFColIndex();

}

wxString AnsiLine::GetAnsiString()
{
ale_it it;
wxString s;
int i;

	if (m_vstyle.empty())
		return wxEmptyString;
	for (it=m_vstyle.begin(), i=0;it!=m_vstyle.end();it++, i++)
	{
		s<<m_codes[it->GetFColIndex()]<<m_bcodes[it->GetBColIndex()]<<it->GetText();
	}
	return s;
}

void AnsiLine::SetLineText(wxString st)
{
	//MudMainFrame *frame = wxGetApp().GetFrame();
	//wxString ff(st.To8BitData(), wxCSConv(frame->GetGlobalOptions()->GetCurEncoding()));
	//if (ff.empty())
	//	ff=st;
	m_linetext.append(st);
}

void AnsiLine::AssignText(wxString st)
{
	//MudMainFrame *frame = wxGetApp().GetFrame();
	//wxString ff(st.To8BitData(), wxCSConv(frame->GetGlobalOptions()->GetCurEncoding()));
	//if (ff.empty())
	//	ff=st;
	m_linetext = st;
}
