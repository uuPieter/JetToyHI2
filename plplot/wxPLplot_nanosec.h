#if !defined ( WXPLPLOT_NANOSEC_H__INCLUDED_ )
#define WXPLPLOT_NANOSEC_H__INCLUDED_

/* #undef PLPLOT_WX_DEBUG_OUTPUT */
#ifdef PLPLOT_WX_DEBUG_OUTPUT
#include <wx/log.h> // for wxLogDebug
// Experimental option to attempt to include a nanosec timestamp with wxLogDebug output
// This is experimental because it may lead to build errors (since clock_gettime and
// some of its clock_id options will not be available on all systems).
/* #undef PLPLOT_WX_NANOSEC */
#ifdef PLPLOT_WX_NANOSEC
#include "plplot.h"
PLDLLIMPEXP_WX void
pl_wx_nanosec(const char *string);

#define PLPLOT_wxLogDebug(string) pl_wx_nanosec(string)

#endif //#ifdef PLPLOT_WX_NANOSEC

#if !defined(PLPLOT_wxLogDebug)
#define PLPLOT_wxLogDebug(string) wxLogDebug(string)
#endif
#else //ifdef PLPLOT_WX_DEBUG_OUTPUT
#define PLPLOT_wxLogDebug(string)
#endif //ifdef PLPLOT_WX_DEBUG_OUTPUT

#endif //#if !defined ( WXPLPLOT_NANOSEC_H__INCLUDED_ )
