#include "main.h"
#include "dialog_sscr.h"

dlg_simplescr::dlg_simplescr( wxWindow* parent )
:
dlg_sscr( parent )
{
	this->SetWindowStyle(wxMAXIMIZE_BOX|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
}
