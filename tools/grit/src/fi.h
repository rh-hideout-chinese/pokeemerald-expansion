//
//! \file fi.h
//!  Extra FreeImage stuff
//! \date 20070226 - 20070226
//! \author cearn
// === NOTES ===
// * Now, why am I using CLDIB stuff when I could just as 
//	 well have use FreeImage all round? Well, historical reasons, I 
//	 guess. The FreeImage library is large, VERY large. And to use 
//	 a library that's bigger than the app itself seems strange.
//	 Aside from that, FI didn't quite have all I wanted when I 
//	 started this, so internally I'm using something that is.

#ifndef __FI_EX_H__
#define __FI_EX_H__

#include "cldib.h"

#include <FreeImage.h>

/*!	\defgroup grpFiEx		Extra FreeImage Routines		*/
/*!	\defgroup grpFiCldib	FreeImage - CLDIB wrappers		*/

// --------------------------------------------------------------------
// CONSTANTS
// --------------------------------------------------------------------

FI_ENUM(FI_SUPPORT_MODE)
{
	FIF_MODE_READ		=  (1 << 1),	//!< Supports reading
	FIF_MODE_WRITE		=  (1 << 2),	//!< Supports writing
	FIF_MODE_EXP_1BPP	=  (1 << 4),	//!< Supports 1bpp export
	FIF_MODE_EXP_2BPP	=  (2 << 4),	//!< Supports 2bpp export
	FIF_MODE_EXP_4BPP	=  (4 << 4),	//!< Supports 4bpp export
	FIF_MODE_EXP_8BPP	=  (8 << 4),	//!< Supports 8bpp export
	FIF_MODE_EXP_16BPP	= (16 << 4),	//!< Supports 16bpp export
	FIF_MODE_EXP_24BPP	= (32 << 4),	//!< Supports 24bpp export
	FIF_MODE_EXP_32BPP	= (64 << 4),	//!< Supports 32bpp export

 	FIF_MODE_EXP_MASK	= 0x07F0, 
	FIF_MODE_EXP_SHIFT	= 4, 
};


// --------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------

//! \addtogroup grpFiEx
/*!	\{	*/

void fiInit();

FIBITMAP *fi_load(const char *fpath);
bool fi_save(FIBITMAP *fi, const char *fpath);

FI_SUPPORT_MODE fiGetSupportModes(FREE_IMAGE_FORMAT fif);

int fiFillOfnFilter(char *szFilter, FI_SUPPORT_MODE fsm, 
	FREE_IMAGE_FORMAT *fifs, int fif_count);


/*!	\}	*/



//! \addtogroup grpFiCldib
/*!	\{	*/

// For converting between CLDIB and FIBITMAP
// and saving/loading. 
CLDIB *fi2dib(FIBITMAP *fi);
FIBITMAP *dib2fi(CLDIB *dib);
CLDIB *cldib_load(const char *fpath, void *extra);
bool cldib_save(const CLDIB *dib, const char *fpath, void *extra);

/*!	\}	*/

#endif	// __FI_EX_H__
