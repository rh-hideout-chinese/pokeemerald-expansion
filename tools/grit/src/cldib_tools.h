//
//! \file cldib_tools.h
//!  Tools header file
//! \date 20050930 - 20060725
//! \author cearn

#ifndef __CLDIB_TOOLS_H__
#define __CLDIB_TOOLS_H__

#include "cldib_core.h"

// --------------------------------------------------------------------
// CONSTANTS
// --------------------------------------------------------------------

/*!	\addtogroup grpDibConv
*	\{
*/

//! bit(un)pack flags
/*!	\ingroup grpDataConv
*/
typedef enum eBUP
{
	BUP_BEBIT = (1 << 30),	//!< Bit-chunks inside bytes are grouped big-endian.
	BUP_BASE0 = (1 << 31)	//!< Offset applies to 0 chunks too.
} eBUP;

/*!	\}	*/

// --------------------------------------------------------------------
// CLASSES
// --------------------------------------------------------------------



// --------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------

// --- MISC (cldib_tools.cpp) ------------------------------------

/*!	\addtogroup grpColor
*	\{
*/
DWORD rgb_dist(const RGBQUAD *a, const RGBQUAD *b);
RGBQUAD str2rgb(const char *str);

/*!	\}	*/


/*!	\addtogroup grpDibTools
*	\{
*/

CLDIB *dib_redim_copy(CLDIB *src, int tileW, int tileH, int tileN);
bool dib_redim(CLDIB *dib, int dstW, int tileH, int tileN);
bool data_redim(const RECORD *src, RECORD *dst, int tileH, int tileN);

//! \name Redox functions
//\{
int dib_pal_reduce(CLDIB *dib, RECORD *extPal);
// dib_tile_reduce(...)
// dib_tile_oxidize(...)
//\}

/*!	\}	*/

// --- CONVERSION (cldib_conv.cpp) ------------------------------------

/*!	\addtogroup grpDibConv
*	\{
*/

//! \name DIB converters
// \{

bool dib_convert(CLDIB *dib, int dstB, DWORD base);
bool dib_bit_unpack(CLDIB *dib, int dstB, DWORD base);
bool dib_8_to_true(CLDIB *dib, int dstB);
bool dib_true_to_true(CLDIB *dib, int dstB);
bool dib_true_to_8(CLDIB *dib, int nclrs);

CLDIB *dib_convert_copy(CLDIB *src, int dstB, DWORD base);
CLDIB *dib_bit_unpack_copy(CLDIB *src, int dstB, DWORD base);
CLDIB *dib_8_to_true_copy(CLDIB *src, int dstB);
CLDIB *dib_true_to_true_copy(CLDIB *src, int dstB);
CLDIB *dib_true_to_8_copy(CLDIB *src, int nclrs);

// \}


//!	\name Data converters
// \{

INLINE WORD swap_word(WORD nn);
INLINE DWORD swap_dword(DWORD nn);

bool data_bit_unpack(void *dstv, const void *srcv, 
	int srcS, int srcB, int dstB, DWORD base);
bool data_bit_pack(void *dstv, const void *srcv, 
	int srcS, int srcB, int dstB, DWORD base);
bool data_bit_rev(void *dstv, const void *srcv, int len, int bpp);
bool data_byte_rev(void *dstv, const void *srcv, int len, int chunk);

bool data_8_to_true(void *dstv, const void *srcv, int srcS, 
	int dstB, RGBQUAD *pal);
bool data_true_to_true(void *dstv, const void *srcv, int srcS, 
	int srcB, int dstB);

// \}

/*!	\}	*/


// --- COLOR ADJUSTMENT (cldib_adjust.cpp) ----------------------------

/*!	\addtogroup grpColor	*/
/*!	\{	*/

bool dib_invert(CLDIB *dib);

//! \name Main adjustment routines
// \{

bool dib_adjust(CLDIB *dib, BYTE lut[], enum eClrChannel cce);
bool data_adjust(BYTE *data, BYTE lut[], enum eClrChannel cce, 
	int nn, int ofs);

// \}


//! \name Lut initialisers
// \{

bool dib_lut_brightness(BYTE lut[], double perc);
bool dib_lut_contrast(BYTE lut[], double perc);
bool dib_lut_gamma(BYTE lut[], double gamma);
bool dib_lut_invert(BYTE lut[]);
bool dib_lut_intensity(BYTE lut[], double perc);
bool dib_lut_linear(BYTE lut[], double a, double b);

// \}

//!	\name Color replacers
// \{
bool dib_pal_replace(CLDIB *dib, DWORD dst[], DWORD src[], int nn);
bool dib_pixel_replace(CLDIB *dib, DWORD dst[], DWORD src[], int nn);
// \}

/*	\}	/addtogroup grpColor	*/


// --------------------------------------------------------------------
// FILE READ/WRITE INTERFACE
// --------------------------------------------------------------------


/*!	\addtogroup grpMisc
*	The file routines don't actually provide any functionality of 
*	their own, just an interface. Write your own routines, then attach 
*	them with <code>dib_set_<i>foo</i>_proc</code>.
*	\{
*/

//!	\name	File read/write interface
// \{

//! General file-reader type
typedef CLDIB *(*fnDibLoad)(const char *fpath, void *extra);
 
//! General file-writer type
typedef bool (*fnDibSave)(const CLDIB *dib, const char *fpath, void *extra);


extern fnDibLoad dib_load;
extern fnDibSave dib_save;

fnDibLoad dib_set_load_proc(fnDibLoad proc);
fnDibSave dib_set_save_proc(fnDibSave proc);

CLDIB *dib_load_dflt(const char *fpath, void *extra);
bool dib_save_dflt(const CLDIB *dib, const char *fpath, void *extra);

//\}

/*!	\}	*/


// --------------------------------------------------------------------
// INLINES
// --------------------------------------------------------------------


//! Swap the bytes in a WORD
INLINE WORD swap_word(WORD xx)
{
	return (xx >> 8) | ((xx&255) << 8);
}

//! Swap the bytes in a DWORD
INLINE DWORD swap_dword(DWORD xx)
{
	return ((xx&0xFF) << 24) | ((xx&0xFF00) << 8) | 
		((xx >> 8)&0xFF00) | ((xx >> 24)&0xFF);
}

#endif // __CLDIB_TOOLS_H__

// EOF
