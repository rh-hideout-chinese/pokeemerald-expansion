//
//! \file grit_misc.cpp
//!   Various routines
//! \date 20050814 - 20080111
//! \author  cearn
//
/* === NOTES === 
  * 20080111, JV. Name changes, part 1
*/

#include "grit.h"

#include "cprs.h"

// --------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// FUNCTIONS
// --------------------------------------------------------------------


//! Compression hub
/*!
	\param dst. Record to compress too
	\param src. Record to compress
	\param mode. Compression type
	\note Aliasing \a dst and \a src is safe.
*/
bool grit_compress(RECORD *dst, const RECORD *src, uint mode)
{
	if(dst ==NULL || src ==NULL)
		return false;

	RECORD cprsRec = { 0, 0, NULL };

	if(mode == GRIT_CPRS_OFF)
	{
		cprsRec = *src;
		cprsRec.data = (u8*)malloc(ALIGN4(rec_size(src)));
		memcpy(cprsRec.data, src->data, rec_size(src));

		rec_alias(dst, &cprsRec);
		return true;						
	}
	else if(mode < GRIT_CPRS_MAX)
	{
		const ECprsTag tags[5]= { CPRS_FAKE_TAG, 
			CPRS_LZ77_TAG, CPRS_HUFF8_TAG, CPRS_RLE_TAG, CPRS_FAKE_TAG 
		};

		//# FIXME: Wut?
		lprintf(LOG_STATUS, "Compressing: %02x\n", mode, tags[mode]);

		if(cprs_compress(&cprsRec, src, tags[mode]) != 0)
		{
			rec_alias(dst, &cprsRec);
			return true;
		}		
	}

	lprintf(LOG_WARNING, "  Compression failed\n");

	return false;
}

// EOF
