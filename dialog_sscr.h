#ifndef __dialog_sscr__
#define __dialog_sscr__

/**
@file
Subclass of dlg_sscr, which is generated by wxFormBuilder.
*/

#include "dlg_sscript.h"

/** Implementing dlg_sscr */
class dlg_simplescr : public dlg_sscr
{
public:
	/** Constructor */
	dlg_simplescr( wxWindow* parent );
	amcScriptEdit * GetEditor() {return m_sce;}
};

#endif // __dialog_sscr__
