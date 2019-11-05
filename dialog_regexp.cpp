#include "main.h"
#include "dialog_regexp.h"

dialog_regexp::dialog_regexp( wxWindow* parent )
:
regexp( parent )
{

}

void dialog_regexp::OnTest( wxCommandEvent& event )
{
	
	wxString test = m_text->GetValue();
	wxString pattern = m_pattern->GetValue();
	RegExp rexp(pattern);
	if (!rexp.Match(test))
	{
		m_matches->SetLabel(_("No match!"));
	}
	else
	{
		wxString s;
		s<< _("Matched from ") << rexp.GetMatchStart() << _(" to ") << rexp.GetMatchEnd() << "\r\n";
		if (wxGetApp().GetFrame()->GetGlobalOptions()->UseUTF8())
		{
			wxString ss = test.ToUTF8();
			test = ss.substr(rexp.GetMatchStart(), rexp.GetMatchLen());
			//ss = wxString::FromUTF8(test);
			ss = test;
			s<< _("Match is: ") << ss << "\r\n";
			
		}
		else
		{
			s<< _("Match is: ") << test.substr(rexp.GetMatchStart(), rexp.GetMatchLen()) << "\r\n";
		}
		s<< _("Captured ") << rexp.GetNumCaptured() << _(" strings.\r\n");
		for (int i=0;i<rexp.GetNumCaptured();i++)
		{
			s<< i+1 <<": "<< rexp.GetMatch(i)<<"\r\n";
		}

		m_matches->SetLabel(s);
	}
}
