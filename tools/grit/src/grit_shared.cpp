//
//! \file grit_shared.cpp
//!   GritShared routines
//! \date 20050814 - 20080512
//! \author cearn
//
/* === NOTES === 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <sys/param.h>

#include "cldib.h"
#include "grit.h"



// --------------------------------------------------------------------
// GritShared functions
// --------------------------------------------------------------------

//! GritShared constructor
GritShared *grs_alloc()
{
	GritShared *grs = (GritShared*)malloc(sizeof(GritShared));
	if(grs == NULL)
		return NULL;

	memset(grs, 0, sizeof(GritShared));
	memset(&grs->palRec, 0, sizeof(RECORD));

	return grs;
}

//! GritShared destructor
void grs_free(GritShared *grs)
{
	if(grs == NULL)
		return;

	grs_clear(grs);
	free(grs);
}

//! Clear GritShared struct
void grs_clear(GritShared *grs)
{
	//free(grs->symName);	
	free(grs->tilePath);
	dib_free(grs->dib);
	free(grs->palRec.data);
	
	memset(grs, 0, sizeof(GritShared));
}


//! Run exporter with shared data.
/*! \note	Still very unsafe, but I need to redo everything later anyway.
*/
void grs_run(GritShared *grs, GritRec *gr_base)
{
	// Make sure we have shared data.
	if( grs->dib ==NULL && grs->palRec.data ==NULL)
	{
		lprintf(LOG_WARNING, "No shared data to run with!\n");
		return;
	}

	// Make copy of gr_base for flags, etc
	GritRec *gr = grit_alloc();
	grs_free(gr->shared);

	grit_copy_options(gr, gr_base);
	grit_copy_strings(gr, gr_base);

	// Attach shared data
	gr->shared = grs;
	strrepl(&gr->symName, grs->symName);
	strrepl(&gr->dstPath, grs->dstPath);

	if(grs->dib == NULL)
	{
		// Palette only. Create new dib.
		gr->srcDib = dib_alloc(16, 16, 8, NULL);
		memset(dib_get_pal(gr->srcDib), 0, PAL_MAX*RGB_SIZE);
		memcpy(dib_get_pal(gr->srcDib), grs->palRec.data, rec_size(&grs->palRec));
	}
	else
		gr->srcDib = dib_clone(grs->dib);

	// NOTE: aliasing screws up deletion later; detach manually.
	gr->_dib = gr->srcDib;	

	// Run for shared gr
	do 
	{
		if(!grit_validate(gr))
			break;

		bool grit_prep_gfx(GritRec *gr);
		bool grit_prep_shared_pal(GritRec *gr);

		if(gr->gfxProcMode != GRIT_EXCLUDE)
			grit_prep_gfx(gr);
		
		if(gr->palProcMode != GRIT_EXCLUDE)
			grit_prep_shared_pal(gr);

		if(gr->bExport)
			grit_export(gr);

	} while(0);

	gr->_dib = NULL;

	// Detach shared data and delete gr
	gr->shared = NULL;
	grit_free(gr);
}
