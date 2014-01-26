#ifndef __dialog_tabedit__
#define __dialog_tabedit__

/**
@file
Subclass of tablist, which is generated by wxFormBuilder.
*/

#include "tabedit_dlg.h"

/** Implementing tablist */
class dlg_tabedit : public tablist
{
public:
	/** Constructor */
	dlg_tabedit( wxWindow* parent );
protected:
	void OnOk(wxCommandEvent& event);
};

#endif // __dialog_tabedit__