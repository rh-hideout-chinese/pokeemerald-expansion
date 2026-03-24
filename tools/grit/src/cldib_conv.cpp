//
//! \file cldib_conv.cpp
//!  Bitdepth conversion
//! \date 20050823 - 20070317
//! \author cearn
// === NOTES ===
// * 20070413,jv: Changed to alpha = 0xFF for 32bit conversions.
// * 20070317,jv: added str2rgb
// * 20060727,jv: data_bitpack() modded for BE systems
// * 20060725,jv: unmagiced parts of data_true_to_true()

#include <stdlib.h>
#include <ctype.h>

#include "cldib_core.h"
#include "cldib_quant.h"
#include "cldib_tools.h"

#include "cldib_quant.h"


//! Parse \a str into an RGBQUAD
/*! \param str	String to parse. Allowed formats are 16bit hex 
*	  patterns ("0xIIII", "IIII") or 24bit hex patterns (
*	  "0xRRGGBB" or "RRGGBB").
*/
RGBQUAD str2rgb(const char *str)
{
	DWORD clr = strtoul(str, NULL, 16), val;
	RGBQUAD rgb;

	val = strlen(str) - ( tolower(str[1])=='x' ? 2 : 0);
	if(val <= 4)	// 16bit BGR -> RGBQUAD
	{
		rgb.rgbRed  = (BYTE)( ((clr    )&31)*255/31 );
		rgb.rgbGreen = (BYTE)( ((clr>> 5)&31)*255/31 );
		rgb.rgbBlue = (BYTE)( ((clr >> 10)&31)*255/31 );
	}
	else			// 24bit RGB -> RGBQUAD
	{
		rgb.rgbRed  = (BYTE)( (clr >> 16) & 255 );
		rgb.rgbGreen = (BYTE)( (clr>> 8) & 255 );
		rgb.rgbBlue = (BYTE)( (clr>> 0) & 255 );
	}

	return rgb;
}


// === DIB FUNCTIONS ==================================================

bool dib_convert(CLDIB *dib, int dstB, DWORD base)
{
	// Nothing to do
	if(dib && dib_get_bpp(dib)==dstB && base ==0)
		return true;

	CLDIB *tmp = dib_convert_copy(dib, dstB, base);
	return dib_mov(dib, tmp);
}

bool dib_bit_unpack(CLDIB *dib, int dstB, DWORD base)
{
	// Nothing to do
	if(dib && dib_get_bpp(dib)==dstB && base ==0)
		return true;

	CLDIB *tmp = dib_bit_unpack_copy(dib, dstB, base);
	return dib_mov(dib, tmp);
}

bool dib_8_to_true(CLDIB *dib, int dstB)
{
	CLDIB *tmp = dib_8_to_true_copy(dib, dstB);
	return dib_mov(dib, tmp);
}

bool dib_true_to_true(CLDIB *dib, int dstB)
{
	// Nothing to do
	if(dib && dib_get_bpp(dib)==dstB)
		return true;

	CLDIB *tmp = dib_true_to_true_copy(dib, dstB);
	return dib_mov(dib, tmp);
}

bool dib_true_to_8(CLDIB *dib, int nclrs)
{
	CLDIB *tmp = dib_true_to_8_copy(dib, nclrs);
	return dib_mov(dib, tmp);
}


//! Hub for bpp conversion (all <code>-\></code> all; CPY; ok).
/*!	\param src Source bitmap.
	\param dstB Destination bitdepth (all)
	\param base Bit(un)pack offset. 
	\return Converted bitmap on success; \c NULL on failure
*/
// PONDER: have flags for RGB/BGR and stuff? (Or does that belong to 
// data?)
CLDIB *dib_convert_copy(CLDIB *src, int dstB, DWORD base)
{
	if(src == NULL)
		return NULL;
	int srcB = dib_get_bpp(src);

	// --- conversion types ---
	// palette <-> palette 
	// 1,4,8 -> 1,4,8   via bit(un)pack
	if(srcB <= 8 && dstB <= 8)
	{
		return dib_bit_unpack_copy(src, dstB, base);
	}
	// --- palette <-> truecolor ---
	// 1,4 -> 8
	// 8 -> 16,24,32
	else if(srcB <= 8 && dstB > 8)
	{
		CLDIB *tmp = NULL, *dst = NULL;
		if(srcB<8)
			src = tmp = dib_bit_unpack_copy(src, 8, base);
		dst = dib_8_to_true_copy(src, dstB);
		dib_free(tmp);
		return dst;
	}
	// --- truecolor -> palette (yikes) ---
	// 16,32 -> 24
	// quantize
	else if(srcB > 8 && dstB <= 8)
	{
		CLDIB *tmp = NULL, *dst = NULL;

		DWORD nclrs = 1 << dstB;
		if(base != 0 && base<nclrs)
			nclrs = base;
		
		tmp = dib_true_to_8_copy(src, nclrs);
		if(tmp == NULL)
			return NULL;
		if(dstB == 8)
			return tmp;
		dst = dib_bit_unpack_copy(tmp, dstB, 0);
		dib_free(tmp);
		return dst;
	}
	// --- truecolor <-> truecolor ---
	// 16->24, 16->32 ; 
	// 24->16, 24->32 ; 
	// 32->16, 32->24
	else if(srcB > 8 && dstB > 8)
	{
		return dib_true_to_true_copy(src, dstB);
	}
	return NULL;
}


//! Bit unpack for dibs (all <code>-\></code> all; CPY; ok).
/*! Actually bit pack <i>and</i> unpack (primarily for pal-to-pal 
*	conversions). Uses \c data_bit_unpack()	internally.
*	\param src Source bitmap.
*	\param dstB Destination bitdepth.
*	\param base Bit unpack offset. Is added to pixel value to allow
*	  values over the original bitdepths. Unless bit 31 is set, 
*	  will only add to non-zero pixels.
*	\return (Un)packed bitmap; \c NULL on failure.
*/
CLDIB *dib_bit_unpack_copy(CLDIB *src, int dstB, DWORD base)
{
	if(src == NULL)
		return NULL;

	int srcB = dib_get_bpp(src);
	int srcW = dib_get_width(src);
	int srcH = dib_get_height(src);

	CLDIB *dst = dib_alloc(srcW, srcH, dstB, NULL, dib_is_topdown(src));

	if(dst ==NULL)
		return NULL;

	BYTE *srcD = dib_get_img(src), *dstD = dib_get_img(dst);

	// equal amount of padding pixels: full img (un)pack safe ... I hope
	if( ((-srcW*srcB)&31)*dstB == ((-srcW*dstB)&31)*srcB )
	{
		data_bit_unpack(dstD, srcD, dib_get_size_img(src), 
			srcB, dstB, base | BUP_BEBIT);
	}
	else	// padding problem: must unpack per scanline
	{
		// NOTE: BUP+alignment == big trouble
		//   For example 1@1 -> x@32 would result in 8@32 px
		int iy;
		int srcP = dib_get_pitch(src), dstP = dib_get_pitch(dst);
		int dstS = dstB*srcP*8/srcB;	// full size that bup uses
		dstS = (dstS+31)/32*4;
		BYTE *tmpD = (BYTE*)malloc(dstS);

		for(iy = 0; iy<srcH; iy++)
		{
			data_bit_unpack(tmpD, &srcD[iy*srcP], srcP, 
				srcB, dstB, base | BUP_BEBIT);
			memcpy(&dstD[iy*dstP], tmpD, dstP);
		}
		free(tmpD);
	}

	// Add palette (FIXME for pal[0] ?)
	// only copy minimum # colors
	// use base for 'palette base'
	int nclrs = MIN(dib_get_nclrs(src), dib_get_nclrs(dst));
	if(nclrs)
	{
		nclrs--;
		bool bBase0 = (base&BUP_BASE0)!=0;
		RGBQUAD *srcPal = dib_get_pal(src), *dstPal = dib_get_pal(dst);
		if(srcB>dstB)	// pack: src uses base
		{
			base = base&((1 << srcB)-1);
			// copy zero
			dstPal[0]= bBase0 ? srcPal[base] : srcPal[0];
			// copy rest
			memcpy(&dstPal[1], &srcPal[base+1], nclrs*RGB_SIZE);
		}
		else			// unpack: dst uses base
		{
			base = base&((1 << dstB)-1);
			// copy zero
			dstPal[bBase0 ? base : 0]= srcPal[0];
			// copy rest
			memcpy(&dstPal[base+1], &srcPal[1], nclrs*RGB_SIZE);
		}
	}

	return dst;
}


//! Converts 8bpp to true color dib (8 <code>-\></code> 16,24,32; CPY; ok).
/*!	\param src Source bitmap. Must be 8 bpp.
*	\param dstB Destination bitdepth. Must be 16, 24 or 32.
*	\return Converted bitmap on success; \c NULL on failure
*/
CLDIB *dib_8_to_true_copy(CLDIB *src, int dstB)
{
	if(src == NULL || dib_get_bpp(src)!=8 || dstB<=8)
		return NULL;

	int srcW = dib_get_width(src);
	int srcH = dib_get_height(src);
	int srcB = dib_get_bpp(src);

	CLDIB *dst = dib_alloc(srcW, srcH, dstB, NULL, dib_is_topdown(src));

	if(dst ==NULL)
		return NULL;

	BYTE *srcD = dib_get_img(src), *dstD = dib_get_img(dst);

	// Equal amount of padding pixels: full img conversion safe 
	// ... I hope
	if(dstB != 24 && ((-srcW*8)&24)*dstB == ((-srcW*dstB)&31)*8 )
	{
		data_8_to_true(dstD, srcD, dib_get_size_img(src), 
			dstB, dib_get_pal(src));
	}
	else	// padding problem: must unpack per scanline
	{
		int iy;
		int srcP = dib_get_pitch(src), dstP = dib_get_pitch(dst);
		for(iy = 0; iy<srcH; iy++)
		{
			data_8_to_true(&dstD[iy*dstP], &srcD[iy*srcP], 
				srcW, dstB, dib_get_pal(src));
		}
	}

	return dst;
}

//! Converts between true color bitdepths (16,24,32 <code>-\></code> 16.24.32; CPY; ok).
/*!	\param src Source bitmap.
*	\param dstB Destination bitdepth.
*	\return Converted bitmap on success; \c NULL on failure	
*/
CLDIB *dib_true_to_true_copy(CLDIB *src, int dstB)
{
	if(src == NULL || dib_get_bpp(src)<=8 || dstB <= 8)
		return NULL;

	int srcW = dib_get_width(src);
	int srcH = dib_get_height(src);
	int srcB = dib_get_bpp(src);

	if(srcB == dstB)
		return dib_clone(src);

	CLDIB *dst = dib_alloc(srcW, srcH, dstB, NULL, dib_is_topdown(src));

	if(dst ==NULL)
		return NULL;

	BYTE *srcD = dib_get_img(src), *dstD = dib_get_img(dst);

	// Padding problems, convert per scanline
	if( (srcW*srcB&31) || (srcW*dstB&31)  )
	{
		int iy;
		int srcP = dib_get_pitch(src), dstP = dib_get_pitch(dst);
		for(iy = 0; iy<srcH; iy++)
			data_true_to_true(&dstD[iy*dstP], &srcD[iy*srcP], srcP, 
				srcB, dstB);
	}
	else
		data_true_to_true(dstD, srcD, dib_get_size_img(src), 
			srcB, dstB);
	return dst;
}


//! Converts true-color bitmap to 8 bpp (16,24,32 <code>-\></code> 8; CPY; ok).
/*! Uses the Wu quantizer (thank you FreeImage) to quantize a 
*	true-color bitmap to a paletted one..
*	\param src Source bitmap. Must be true color.
*	\param nclrs Number of colors in the output bitmap. (It's still 
*	  always 8 bpp, though).
*	\return Converted bitmap on success; \c NULL on failure
*/
CLDIB *dib_true_to_8_copy(CLDIB *src, int nclrs)
{
	if(src == NULL || dib_get_bpp(src) <= 8)
		return NULL;

	CLDIB *tmp = NULL, *dst = NULL;
	if(dib_get_bpp(src) != 24)
		src = tmp = dib_true_to_true_copy(src, 24);
	if(src == NULL)
		return NULL;
	try
	{
		dibWuQuantizer wuq(src);
		dst = wuq.Quantize(nclrs);
	}
	catch(...) {}

	dib_free(tmp);
	return dst;
}

// === DATA FUNCTIONS =================================================
// These operate on the byte level, ignoring padding


//! Bit unpacks data, with optional extras (ok).
/*!
*	\param dstv Destination buffer. Must be pre-allocated.
*	\param srcv Source buffer.
*	\param srcS Size of \a srcv in bytes.
*	\param srcB Source bitdepth.
*	\param dstB Destination bitdepth.
*	\param base Unpacking offset (additive).<br>
*	  \arg \c base {0-29} : Offset
*	  \arg \c base {30} : Big-endian bit read
*	  \arg \c base {31} : Add offset to zero-valued pixels too
*/
bool data_bit_unpack(void *dstv, const void *srcv, 
	int srcS, int srcB, int dstB, DWORD base)
{
	if(srcB > dstB)
		return data_bit_pack(dstv, srcv, srcS, srcB, dstB, base);

	DWORD *dstL4 = (DWORD*)dstv, *srcL4 = (DWORD*)srcv;
	DWORD srcMask = (~0u) >> (32-srcB);	// src mask
	DWORD srcBuf, dstBuf, tmp;			// buffers
	int srcShift, dstShift;				// current pos in u32
	int dstN = dstB*srcS*8/srcB;			// # dst bits
	dstN = (dstN+31)/32;					// # dst u32s

	bool bBase0 = (base&BUP_BASE0) != 0;
	DWORD srcEndMask = ((base&BUP_BEBIT) && srcB<8) ? 8-srcB : 0;
	DWORD dstEndMask = ((base&BUP_BEBIT) && dstB<8) ? 8-dstB : 0;
	base &= ~(BUP_BEBIT|BUP_BASE0);

	srcShift = 32;
	// NOTE: dstB >= srcB means dst-buffer is used up sooner
	while(dstN--)
	{
		if(srcShift >= 32)	// srcBuf covered, get load new src
		{
			srcBuf = *srcL4++;	// load source buffer
			if(BYTE_ORDER == BIG_ENDIAN)
				srcBuf = swap_dword(srcBuf);
			srcShift = 0;
		}
		// piece together a dstBuf
		dstBuf = 0;
		for(dstShift = 0; dstShift<32; dstShift += dstB)
		{
			tmp = (srcBuf >> (srcShift^srcEndMask))&srcMask;
			srcShift += srcB;
			if(tmp || bBase0)
				tmp += base;
			dstBuf |= tmp << (dstShift^dstEndMask);
		}
		if(BYTE_ORDER == BIG_ENDIAN)
			dstBuf = swap_dword(dstBuf);
		*dstL4++ = dstBuf;
	}
 
	return true;
}

//! Bit packs data, with optional extras (ok).
/*!	\param dstv Destination buffer. Must be pre-allocated.
*	\param srcv Source buffer.
*	\param srcS Size of \a srcv in bytes.
*	\param srcB Source bitdepth.
*	\param dstB Destination bitdepth.
*	\param base Packing offset (subtractive)<br>
*	  \arg \c base {0-29} : Offset
*	  \arg \c base {30} : Big-endian bit read
*	  \arg \c base {31} : Subtract offset from zero-valued pixels too 
*	    (rather silly exercise, but still)
*	\note \a base works as inverse of base in bit_unpack. But AN 
*		EXACT INVERSE IS IMPOSSIBLE
*/
bool data_bit_pack(void *dstv, const void *srcv, 
	int srcS, int srcB, int dstB, DWORD base)
{
	if(dstB > srcB)
		return data_bit_unpack(dstv, srcv, srcS, srcB, dstB, base);

	DWORD *dstL4 = (DWORD*)dstv, *srcL4 = (DWORD*)srcv;
	DWORD dstMask = (~0u) >> (32-dstB);	// dst mask
	DWORD srcBuf, dstBuf, tmp;			// buffers
	int srcShift, dstShift;				// current pos in u32

	int srcN = (srcS+3)/4;

	bool bBase0 = (base&BUP_BASE0)!=0;
	DWORD srcEndMask = ((base&BUP_BEBIT) && srcB<8) ? 8-srcB : 0;
	DWORD dstEndMask = ((base&BUP_BEBIT) && dstB<8) ? 8-dstB : 0;
	base &= ~(BUP_BEBIT|BUP_BASE0);

	int dstB_add = dstB;
	if(dstB == 5) dstB_add = 8;
	if(dstB == 3) dstB_add = 8;

	dstBuf = dstShift = 0;
	// NOTE: srcB >= dstB means src-buffer is used up sooner
	while(srcN--)
	{
		srcBuf = *srcL4++;	// load source buffer
		if(BYTE_ORDER == BIG_ENDIAN)
			srcBuf = swap_dword(srcBuf);

		// pack into the dst buffer
		for(srcShift = 0; srcShift<32; srcShift += srcB)
		{
			tmp = (srcBuf >> (srcShift^srcEndMask));
			if(tmp || bBase0)
				tmp -= base;
			dstBuf |= (tmp&dstMask) << (dstShift^dstEndMask);
			dstShift += dstB_add;
		}
		if(dstShift >= 32)	// dst buffer full, store
		{
			if(BYTE_ORDER == BIG_ENDIAN)
				dstBuf = swap_dword(dstBuf);
			*dstL4++ = dstBuf;

			dstBuf = dstShift = 0;
		}
	}
	if(dstShift)	// finish last piece
	{
		if(BYTE_ORDER == BIG_ENDIAN)
			dstBuf = swap_dword(dstBuf);
		*dstL4++ = dstBuf;
	}

	return true;
}


//! Reverses bits inside bytes (ok).
/*! Switches between bit-little and bit-big pixel formats.
*	\param dstv Destination buffer. Must be pre-allocated.
*	\param srcv Source buffer.
*	\param len Size of the buffers in bytes.
*	\param bpp Bitdepth of the chunks to reverse (1, 2, 4)
*	\note \a dst and \a src may be aliased safely.
*/
bool data_bit_rev(void *dstv, const void *srcv, int len, int bpp)
{
	if(bpp>8)
		return false;
	else if(bpp ==8)
	{
		memcpy(dstv, srcv, len);
		return true;
	}

	BYTE *srcL = (BYTE*)srcv, *dstL = (BYTE*)dstv;
	BYTE mask = (1 << bpp)-1, in, out;
	int ii;
	while(len--)
	{
		in = *srcL++;
		out = 0;
		for(ii = 0; ii<8; ii += bpp)
			out |= ((in >> ii)&mask) << (8-bpp-ii);
		*dstL++= (BYTE)out;
	}
	
	return true;
}


//! Reverses order of bytes in multi-byte chunks (ok).
/*! Switches between byte-little and byte-big pixel formats.
*	\param dstv Destination buffer. Must be pre-allocated.
*	\param srcv Source buffer.
*	\param len Size of the buffers in bytes.
*	\param chunk Size of the chunk to reverse the bytes of (say, 4 for 
*	  DWORDs, etc)
*	\note \a dst and \a src may be aliased safely.
*	\note \a len is in bytes, not chunks; \a len should be a multiple 
*	  of \a chunk (though not strictly required).
*/
bool data_byte_rev(void *dstv, const void *srcv, int len, int chunk)
{
	if(chunk<1)
		return false;

	if(srcv != dstv)	// dst and src separate
	{
		BYTE *srcL = (BYTE*)srcv, *dstL = (BYTE*)dstv;
		int ii, jj = chunk-1;
		// jj acts as a reverse offset and causes the dst index
		// to run backwards (the factor 2) and is reset at 
		// chunk boundaries
		for(ii = 0; ii<len; ii++, jj -= 2)
		{
			if(jj+chunk < 0)
				jj = chunk-1;
			dstL[ii+jj]= srcL[ii];
		}
	}
	else				// in-place reversal
	{
		BYTE *memL = (BYTE*)srcv, tmp;
		int ii;
		len  /= chunk;	// cut down to # chunks
		while(len--)
		{
			// only half, otherwise we'd do a double reverse
			for(ii = 0; ii<chunk/2; ii++)
			{
				tmp = memL[ii];
				memL[ii]= memL[chunk-1-ii];
				memL[chunk-1-ii]= tmp;
			}
			memL += chunk;
		}
	}

	return true;
}


//! Convert data from 8 bpp to true color (8 <code>-\></code> 16,24,32; ok).
/*! Depalettized data, disregarding any potential padding pixels.
*	\param dstv Destination buffer. Must be pre-allocated.
*	\param srcv Source buffer.
*	\param srcS Size of source buffer in bytes.
*	\param dstB Destination bitdepth.
*	\param pal Palette to use for colors.
*/
bool data_8_to_true(void *dstv, const void *srcv, int srcS, 
	int dstB, RGBQUAD *pal)
{
	int ii;
	BYTE *srcD = (BYTE*)srcv;
	RGBQUAD rgb;

	switch(dstB)
	{
	case 16:	// x rrrrr ggggg bbbbb
		{
			WORD *dstD2 = (WORD*)dstv;
			for(ii = 0; ii<srcS; ii++)
			{
				rgb = pal[srcD[ii]];
				dstD2[ii]= RGB16(rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue);
			}
			break;
		}
	case 24:	// bb gg rr
		{
			RGBTRIPLE *dstD3 = (RGBTRIPLE*)dstv;
			for(ii = 0; ii<srcS; ii++)
			{
				rgb = pal[srcD[ii]];
				dstD3[ii].rgbtBlue  = rgb.rgbBlue;
				dstD3[ii].rgbtGreen = rgb.rgbGreen;
				dstD3[ii].rgbtRed   = rgb.rgbRed;
			}
			break;
		}
	case 32:	// bb gg rr aa
		{
			RGBQUAD *dstD4 = (RGBQUAD*)dstv;
			for(ii = 0; ii<srcS; ii++)
			{
				dstD4[ii]= pal[srcD[ii]];
				dstD4[ii].rgbReserved = 0xFF;
			}
			break;
		}
	default:
		return false;
	}

	return true;
}


//! Convert data betwee true color bitdepths (16,24,32 <code>-\></code> 16,24,32; ok).
/*!	\param dstv Destination buffer. Must be pre-allocated.
*	\param srcv Source buffer.
*	\param srcS Size of source buffer in bytes.
*	\param srcB Source bitdepth
*	\param dstB Destination bitdepth.
*/
bool data_true_to_true(void *dstv, const void *srcv, int srcS, 
	int srcB, int dstB)
{
	if(srcB == dstB)	// same depth, just copy
	{
		memcpy(dstv, srcv, srcS);
		return true;
	}

	int ii, nn;
	BYTE *srcD = (BYTE*)srcv, *dstD = (BYTE*)dstv;

	switch(dstB)
	{
	case 16:	// 24|32 -> x rrrrr ggggg bbbbb
		{
			int ofs = srcB >> 3;
			WORD *dstD2 = (WORD*)dstv;
			nn = srcS/ofs;
			for(ii = 0; ii<nn; ii++)
			{
				RGBTRIPLE *pixel = (RGBTRIPLE *)&srcD[ofs*ii];
				dstD2[ii]= RGB16(pixel->rgbtRed , pixel->rgbtGreen, pixel->rgbtBlue);
			}
			return true;
		}
	case 24:	// 16|32 -> bb gg rr
		if(srcB ==16)	// 16->24
		{
			WORD *srcD2 = (WORD*)srcv;
			RGBTRIPLE *dstD3 = (RGBTRIPLE*)dstv;
			DWORD tmp;
			for(ii = 0; ii<srcS/2; ii++)
			{
				tmp = srcD2[ii];
				dstD3[ii].rgbtBlue =  (BYTE)(( tmp     &31)*255/31);
				dstD3[ii].rgbtGreen = (BYTE)(((tmp>> 5)&31)*255/31);
				dstD3[ii].rgbtRed =   (BYTE)(((tmp >> 10)&31)*255/31);
			}
		}
		else			// 32->24
		{
			RGBQUAD *srcD4 = (RGBQUAD*)srcv;
			RGBTRIPLE *dstD3 = (RGBTRIPLE*)dstv;
			for(ii = 0; ii<srcS/4; ii++)
			{
				dstD3[ii].rgbtBlue =  srcD4[ii].rgbBlue;
				dstD3[ii].rgbtGreen = srcD4[ii].rgbGreen;
				dstD3[ii].rgbtRed =   srcD4[ii].rgbRed;
			}
		}
		return true;
	case 32:	// bb gg rr 00
		if(srcB ==16)	// 16->32
		{
			WORD *srcD2 = (WORD*)srcv;
			RGBQUAD *dstD4 = (RGBQUAD*)dstv;
			DWORD tmp;
			for(ii = 0; ii<srcS/2; ii++)
			{
				tmp = srcD2[ii];
				dstD4[ii].rgbBlue =  (BYTE)(( tmp     &31)*255/31);
				dstD4[ii].rgbGreen = (BYTE)(((tmp>> 5)&31)*255/31);
				dstD4[ii].rgbRed =   (BYTE)(((tmp >> 10)&31)*255/31);
				dstD4[ii].rgbReserved = 0xFF;
			}
		}
		else			// 24->32
		{
			RGBTRIPLE *srcD3 = (RGBTRIPLE*)srcv;
			RGBQUAD *dstD4 = (RGBQUAD*)dstv;
			for(ii = 0; ii<srcS/3; ii++)
			{			
				dstD4[ii].rgbBlue =  srcD3[ii].rgbtBlue;
				dstD4[ii].rgbGreen = srcD3[ii].rgbtGreen;
				dstD4[ii].rgbRed =   srcD3[ii].rgbtRed;
				dstD4[ii].rgbReserved = 0xFF;
			}
		}
		return true;
	default:
		return false;
	}

	return true;
}

// EOF
