//
//! \file cldib_adjust.cpp
//!   color adjustment
//! \date 20050823 - 20080304
//! \author cearn
//
// === NOTES === 

#include <math.h>

#include "cldib_core.h"
#include "cldib_tools.h"

// === CONSTANTS ======================================================
// === CLASSES ========================================================
// === GLOBALS ========================================================
// === PROTOTYPES =====================================================


// --------------------------------------------------------------------
// FUNCTIONS
// --------------------------------------------------------------------


//! Color adjustment by LUT (all bpp; IP).
/*!	\param dib Work bitmap.
*	\param lut Adjustment LUT. Assumed to be 256 entries long.
*	\param cce Color channel to adjust
*/
bool dib_adjust(CLDIB *dib, BYTE lut[], enum eClrChannel cce)
{
	if(dib == NULL || lut == NULL)
		return false;

	int ii;
	int dibB = dib_get_bpp(dib);
	switch(dibB)
	{
	case 1:		case 4:		case 8:
		data_adjust((BYTE*)dib_get_pal(dib), lut, cce, 
			dib_get_nclrs(dib), RGB_SIZE);
		break;
	case 24:	case 32:
		{
			int ofs = dibB >> 8;
			int dibW = dib_get_width(dib);
			int dibH = dib_get_height(dib);
			int dibP = dib_get_pitch(dib);
			BYTE *dibL = dib_get_img(dib);
			for(ii = 0; ii<dibH; ii++)
			{
				data_adjust(dibL, lut, cce, dibW, ofs);
				dibL += dibP;
			}
		}
	default:
		return false;
	}
	return true;
}


//! Data adjustment by LUT; internal for dib_adjust
/*!	\param data Work buffer.
*	\param lut Adjustment LUT. Assumed to be 256 entries long.
*	\param cce Color channel to adjust
*	\param nn Number of data entries
*	\param ofs Offset between entries
*/
bool data_adjust(BYTE *data, BYTE lut[], enum eClrChannel cce, int nn, int ofs)
{
	int ii, jj;
	BYTE *line;
	nn *= ofs;
	for(ii = 0; ii<4; ii++)	// cycle through BGRA
	{
		if(~cce & (1 << ii))
			continue;
		line = &data[ii];
		for(jj = 0; jj<nn; jj += ofs)
			line[jj]= lut[line[jj]];
	}
	return true;
}


//!	Inverts the bitmap (all bpp; IP).
/*!	\param dib Work bitmap.
*/
bool dib_invert(CLDIB *dib)
{
	if(dib == NULL)
		return false;

	int ii, nn;
	int dibB = dib_get_bpp(dib);
	// I need the mask to keep the reserved bits of RGBQUAD.
	DWORD mask = 0xFFFFFFFF, *buf4;

	if(dibB <= 8)	// invert palette
	{
		mask >>= 8;
		buf4 = (DWORD*)dib_get_pal(dib);
		nn = dib_get_nclrs(dib);
	}
	else
	{
		if(dibB ==32)
			mask >>= 8;
		buf4 = (DWORD*)dib_get_img(dib);
		nn = dib_get_pitch(dib)*dib_get_height(dib)/4;
	}

	for(ii = 0; ii<nn; ii++)
		buf4[ii] ^= mask;
	return true;
}


// --- LUT INITIALISERS -----------------------------------------------


//! Brightness LUT (perc = [-100,+100]). b = perc/100 <br> f(x)= x + b
bool dib_lut_brightness(BYTE lut[], double perc)
{	return dib_lut_linear(lut, 1.0, perc/100.0);				}


//! Contrast LUT (perc = [-100,+100]). c = perc/100 <br> f(x)= (c+1)x - �c
bool dib_lut_contrast(BYTE lut[], double perc)
{	return dib_lut_linear(lut, perc/100.0+1.0, -perc/200.0);		}


//! Gamma LUT (gamma>0). f(x)= x^(1/gamma)
bool dib_lut_gamma(BYTE lut[], double gamma)
{
	if(gamma<=0)
		return false;

	// N*(x/N)^a = x^a * (N^(1-a))
	int ii, val;
	double exp = 1.0/gamma;
	double scale = pow(255.0, 1-exp);

	for(ii = 0; ii<256; ii++)
	{
		val = (int)( scale*pow(ii, exp) + 0.5 );
		lut[ii]= val<=255 ? val : 255;
	}
	return true;
}


//! Fill intensity LUT (perc = [-100,100]). i = perc/100 <br> f(x)= (i+1)x
bool dib_lut_intensity(BYTE lut[], double perc)
{	return dib_lut_linear(lut, perc/100.0+1.0, 0.0);			}


//! Fill inversion LUT. f(x)= 1-x
bool dib_lut_invert(BYTE lut[])
{
	int ii;
	for(ii = 0; ii<256; ii++)
		lut[ii]= ~lut[ii];

	return true;
}


//! Fill linear LUT. f(x) = a*x+b
bool dib_lut_linear(BYTE lut[], double a, double b)
{
	int ii, val;
	if(a ==1.0 && b ==0.0)	// nothing to do
	{
		for(ii = 0; ii<256; ii++)
			lut[ii]= ii;
		return true;
	}

	b *= 255.0;		// scaling for ii domain
	b += 0.5;		// for rounding
	for(ii = 0; ii<256; ii++)
	{
		val = (int)( (a*ii + b) );
		lut[ii]= (BYTE)MAX(0, MIN(val, 255));
	}
	return true;
}


// --- COLOR REPLACERS ------------------------------------------------


//! Replaces palette entries (8 bpp; IP).
/*! This can be used to remap the palette entries. It uses arrays 
*	\a src and \a dst to indicate which indices need replacing, and 
*	which should be used as the replacements. For example, 
*	\a src = {1,2,3} and \a dst = {4,5,6} would copy the colors from 
*	indices 1,2 and 3 into 4,5 and 6. You can use this for color-swapping
*	by, say, using \a src = {1, 2, 3, 4} and \a dst = {3, 4, 1, 2}, 
*	which will swap the colors of 1-4. 
*	\param dib Work bitmap.
*	\param dst List of pal entries to replace.
*	\param src List of replacement pal entries.
*	\param nn Number of entries in src and dst.
*	\return Success status.
*	\note	This does not change the pixel values! For that, use 
*	  \sa dib_pixel_replace.
*/
bool dib_pal_replace(CLDIB *dib, DWORD *dst, DWORD *src, int nn)
{
	if(dib == NULL)
		return false;
	if(dib_get_bpp(dib) != 8)
		return false;

	int ii;
	RGBQUAD *pal = dib_get_pal(dib);

	// Using a buffer to avoid swapping clashes
	// (a->b, then later b->a would be bad)
	RGBQUAD *buf = (RGBQUAD*)malloc(nn*RGB_SIZE);


	// If src or dst is NULL, straighforward indices are assumed.
	if(src)
		for(ii = 0; ii<nn; ii++)
			buf[ii]= pal[src[ii]];
	else
		for(ii = 0; ii<nn; ii++)
			buf[ii]= pal[ii];

	if(dst)
		for(ii = 0; ii<nn; ii++)
			pal[dst[ii]]= buf[ii];
	else
		for(ii = 0; ii<nn; ii++)
			pal[ii]= buf[ii];

	free(buf);

	return true;
}


//! Replaces pixel entries (8,24,32 bpp; IP; ok).
/*! This can be used to remap the pixel values. It uses arrays 
*	\a src and \a dst to indicate which pixel-values need replacing, and 
*	which should be used as the replacements. For example, you could 
*	make all green values red by using 
*	\a src = { FF0000 }, and \a dst = { 00FF00 }. 
*	Or you could swap red and green via 
*	\a src = { FF0000, 00FF00 } and \a dst = { 00FF00, 0000FF }.
*    \param dib Work bitmap.
*	\param dst List of pixel values to replace (DWORD or RGBQUAD array).
*	\param src List of replacement pixel values (DWORD or RGBQUAD array).
*	\param nn Number of entries in dst and src.
*	\return Success status.
*/
bool dib_pixel_replace(CLDIB *dib, DWORD dst[], DWORD src[], int nn)
{
	if(dib == NULL)
		return false;

	int dibW = dib_get_width(dib);
	int dibH = dib_get_height(dib);
	int dibB = dib_get_bpp(dib);
	int dibP = dib_get_pitch(dib);
	int dibS = dibH*dibP;

	int ii, jj, ix, iy;
	switch(dibB)
	{
	case 8:		// swap via LUT
		{
			// create the lut
			int lut[256];
			for(ii = 0; ii<256; ii++)		// base lut
				lut[ii]= ii;
			for(ii = 0; ii<nn; ii++)		// add the swap list
				lut[dst[ii]]= src[ii];

			// and swap
			BYTE *dibL = dib_get_img(dib);
			for(ii = 0; ii<dibS; ii++)
				dibL[ii]= lut[dibL[ii]];
			break;
		}
	case 24:		// UNTESTED
		{
			BYTE *dibL = dib_get_img(dib);
			RGBQUAD *dstRGB = (RGBQUAD*)dst, *srcRGB = (RGBQUAD*)src;
			RGBTRIPLE *rgbt = (RGBTRIPLE*)dibL;
			for(iy = 0; iy<dibH; iy++)
			{
				for(ix = 0; ix<dibW; ix++)
				{
					for(jj = 0; jj<nn; jj++)
					{
						if( rgbt->rgbtRed   == dstRGB[jj].rgbRed &&
							rgbt->rgbtGreen == dstRGB[jj].rgbGreen &&
							rgbt->rgbtBlue  == dstRGB[jj].rgbBlue)
						{
							rgbt->rgbtRed   = srcRGB[jj].rgbRed;
							rgbt->rgbtGreen = srcRGB[jj].rgbGreen;
							rgbt->rgbtBlue  = srcRGB[jj].rgbBlue;
							break;
						}
						rgbt++;
					}
				}
				dibL += dibP;
				rgbt = (RGBTRIPLE*)dibL;
			}
		}
	case 32:		// UNTESTED
		{
			DWORD *dibL = (DWORD*)dib_get_img(dib);
			for(ii = 0; ii<dibS; ii++)
			{
				for(jj = 0; jj<nn; jj++)
				{
					if(dibL[ii]= dst[jj])
					{
						dibL[ii]= src[jj];
						break;
					}
				}
			}
		}
		break;
	default:
		return false;
	}
	return true;
}


//! Swap red and blue components.
/*!	\note	In-place swap.
*/
CLDIB *dib_swap_rgb(CLDIB *dib)
{
	if(dib == NULL)
		return NULL;

	int ii, ix, iy;
	int dibW, dibH, dibB, dibP;
	dib_get_attr(dib, &dibW, &dibH, &dibB, &dibP);

	switch(dibB)
	{
	case 16:
		{
			WORD *dibL = (WORD*)dib_get_img(dib);
			for(ii = 0; ii<dibP*dibH/2; ii++)
				dibL[ii]= swap_rgb16(dibL[ii]);			
		}
		break;

	case 24:
		{
			BYTE *dibD = dib_get_img(dib);
			RGBTRIPLE *dibL;
			for(iy = 0; iy<dibH; iy++)
			{
				dibL = (RGBTRIPLE*)&dibD[iy*dibP];
				for(ix = 0; ix<dibW; ix++)
					dibL[ix]= swap_rgb24(dibL[ix]);					
			}
		}
		break;

	case 32:
		{
			RGBQUAD *dibL = (RGBQUAD*)dib_get_img(dib);
			for(ii = 0; ii<dibP*dibH/4; ii++)
				dibL[ii]= swap_rgb32(dibL[ii]);			
		}
		break;
	
	default:	// paletted
		{
			RGBQUAD *dibL = (RGBQUAD*)dib_get_pal(dib);
			for(ii = 0; ii<dib_get_nclrs(dib); ii++)
				dibL[ii]= swap_rgb32(dibL[ii]);	
		}
	}

	return dib;
}


// EOF
