#ifndef __dialog_regexp__
#define __dialog_regexp__

/**
@file
Subclass of regexp, which is generated by wxFormBuilder.
*/
#include "main.h"
#include "dlg_regexptest.h"

/** Implementing regexp */
class dialog_regexp : public regexp
{
protected:
	// Handlers for regexp events.
	void OnTest( wxCommandEvent& event );
	
public:
	/** Constructor */
	dialog_regexp( wxWindow* parent );
	wxTextCtrl* GetPattern() {return m_pattern;}
};

#endif // __dialog_regexp__
