//
//! \file cldib_core.cpp
//!   cldib_core implementation file
//! \date 20050823 - 20080425
//! \author cearn
//
/* === NOTES === 
  * 20080425,jvijn: made dib_redim and dib_convert work on the 
    image itself, not a copy; a converted copy is returned by 
	dib_redim_copy and dib_convert. 
  * Changed all BOOL/TRUE/FALSE into bool/true/false.
  * 20060725,jvijn: #ifdef around pure WIN32 functions
*/

#include "cldib_core.h"


// --------------------------------------------------------------------
// FUNCTIONS
// --------------------------------------------------------------------

//! Get the main attributes of a DIB
bool dib_get_attr(CLDIB *dib, int *width, int *height, int *bpp, int *pitch)
{
	if(dib == NULL)
		return false;

	if(width)
		*width = dib_get_width(dib);
	if(height)
		*height = dib_get_height(dib);
	if(bpp)
		*bpp = dib_get_bpp(dib);
	if(pitch)
		*pitch = dib_get_pitch(dib);
	return true;
}

//! Get a pointer to the image data at pixel (\a x, \a y).
/*!	\note	Works at the byte level. If you have sub-8 bpps, you'll
*	  still have to shift a bit.
*/
BYTE *dib_get_img_at(CLDIB *dib, int x, int y)
{
	BYTE *dibD = dib_get_img(dib);
	return &dibD[x*dib_get_bpp(dib)/8 + y*dib_get_pitch(dib)];
}

//! Creates a new bitmap (all; ok)
/*!	\param width	Bitmap width
*	\param height	Bitmap height
*	\param bpp	Bitmap bitdepth (1, 4, 8, 16, 24, 32)
*	\param data	Data to fill the bitmap with. If \c NULL, data will 
*	  be uninitialized.
*	\param bTopDown	If \c true, the bitmap will be top-down (origin in 
*	  the top-left); if \c false, it'll be bottom up. Windows bitmaps 
*	  are traditionally bottom-up, with all the awkwardness that goes 
*	  with it (as matrices and screens are usually top-down). 
*	  \c CLDIBs are top-down by default.
*	\note	Always call \c dib_free() on bitmaps when you're done with it.
*/
CLDIB *dib_alloc(int width, int height, int bpp, const BYTE *data,
	bool bTopDown /* true */)
{
	int ii;
	CLDIB *dib = NULL;

	// check validity of requested bpp
	const int bpp_allowed[6]= { 1, 4, 8, 16, 24, 32 };
	for(ii = 0; ii<6; ii++)
		if(bpp == bpp_allowed[ii])
			break;
	if(ii >= 6)
		return NULL;
	
	int nclrs, dibH, dibP, dibS;
	nclrs = (bpp > 8 ? 0 : 1 << bpp);
	dibH = height;
	dibP = dib_align(width, bpp);
	dibS = dibP*dibH;

	// create in two stages, first the dib itself, and then for the data
	// and conk out if either fails
	dib = (CLDIB*)malloc(sizeof(CLDIB));
	if(dib == NULL)
		return NULL;

	dib->data = (BYTE*)calloc(sizeof(BYTE), BMIH_SIZE + nclrs*RGB_SIZE + dibS);
	if(dib->data == NULL)
	{
		free(dib);
		return NULL;
	}

	BITMAPINFOHEADER *bmih = dib_get_hdr(dib);

	bmih->biSize = BMIH_SIZE;
	bmih->biWidth = width;
	bmih->biHeight = bTopDown ? -height : height;
	bmih->biPlanes = 1;
	bmih->biBitCount = bpp;
	bmih->biCompression = 0;
	bmih->biSizeImage = dibS; 
	bmih->biXPelsPerMeter = 0; 
	bmih->biYPelsPerMeter = 0; 
	bmih->biClrUsed = nclrs; 
	bmih->biClrImportant = 0;

	// init palette, all reds, corresponding to COLORREFs [0-nclrs>
	// PONDER: is this right?
	COLORREF *clr = (COLORREF*)dib_get_pal(dib);
	for(ii = 0; ii<nclrs; ii++)
		clr[ii]= ii << 16;


	// init data
	if(data != NULL)
	{
		if(bTopDown)
			memcpy(dib_get_img(dib), data, dibS);
		else
		{
			const BYTE *srcL = &data[(height-1)*dibP];
			BYTE *dstL = dib_get_img(dib);
			for(ii = 0; ii<height; ii++)
				memcpy(&dstL[ii*dibP], &srcL[-ii*dibP], dibP);
		}
	}

	return dib;
}


//! Frees a bitmap's memory (ok)
/*!	\param dib	Bitmap to free.
*	\note	Use of this function is pretty much required on all \c CLDIBs 
*	  unless you like memory leaks. 
*	\note Is \c NULL safe.
*/
void dib_free(CLDIB *dib)
{
	if(dib == NULL)
		return;

	SAFE_FREE(dib->data);
	SAFE_FREE(dib);
}


//! Makes an exact copy of a bitmap
/*!	\param src	Bitmap to clone.
*	\return Cloned bitmap
*/
CLDIB *dib_clone(CLDIB *src)
{
	if(src == NULL)
		return NULL;

	CLDIB *dib = (CLDIB*)malloc(sizeof(CLDIB));
	if(dib == NULL)
		return NULL;
	dib->data = (BYTE*)malloc(dib_get_size(src));
	if(!dib->data)
	{
		free(dib);
		return NULL;
	}
	memcpy(dib->data, src->data, dib_get_size(src));
	return dib;
}


//! Move the contents of \a src into \a dst.
/*!
	\note	Will FREE \a src!
*/
bool dib_mov(CLDIB *dst, CLDIB *src)
{
	if(dst ==NULL || src ==NULL || src->data ==NULL)
		return false;

	SAFE_FREE(dst->data);
	dst->data = src->data;
	free(src);

	return true;
}

// --- BITMAP / CANVAS ------------------------------------------------


#ifdef _MSC_VER

//! Create a HBITMAP from a CLDIB.
/*!	\param dib	Valid CLDIB
*	\return	Initialized HBITMAP; NULL on failure.
*/
HBITMAP dib_to_hbm(CLDIB *dib)
{
	if(dib == NULL)
		return NULL;

	HDC hdc = GetDC(NULL);

	BYTE *hbmD;
	HBITMAP hbm = CreateDIBSection(hdc, dib_get_info(dib),
		DIB_RGB_COLORS, (void**)&hbmD, NULL, 0);

	// while the following _should_ work, it sometimes doesn't 
	// for some inexplicable reason.
	//SetDIBits(hdc, hbm, 0, dib_get_height(dib), 
	//	dib_get_img(dib), dib_get_info(dib), DIB_RGB_COLORS);

	ReleaseDC(NULL, hdc);
	if(hbm == NULL)
		return NULL;
	// so we're doing it manually
	memcpy(hbmD, dib_get_img(dib), dib_get_size_img(dib));

	// PONDER: palette?

	return hbm;
}


//! Create a CLDIB from a HBITMAP.
/*!	\param dib	valid HBITMAP
*	\return	initialized CLDIB; NULL on failure.
*/
CLDIB *dib_from_hbm(HBITMAP hbm)
{
	if(hbm == NULL)
		return NULL;

	BITMAP bm;
	GetObject(hbm, sizeof(BITMAP), &bm);
	CLDIB *dib = dib_alloc(bm.bmWidth, bm.bmHeight, bm.bmBitsPixel, NULL);

	if(dib == NULL)
		return NULL;

	// The WinXP GetDIBits somehow overwrites biClrUsed
	// Hack to fix that
	BITMAPINFOHEADER *bmih = dib_get_hdr(dib);
	int nclrs = bmih->biClrUsed;

	HDC hdc = GetDC(NULL);
	GetDIBits(hdc, hbm, 0, dib_get_height(dib), 
	  dib_get_img(dib), dib_get_info(dib), DIB_RGB_COLORS);
	ReleaseDC(NULL, hdc);

	bmih->biClrUsed = nclrs;	// man, this is f@%#@%g weak
	return dib;
}


//! Copies a DIB to a device context (StretchBlt variant).
/*!	\param hdc	Destination DC.
*	\param rectDest	Destination rectangle. If NULL, the DIB's 
*	  dimensions are used.
*	\param dib	DIB to blit.
*	\param rectSrc	Source rectangle. If NULL, the DIB's 
*	  dimensions is used.
*	\param flags	Blit flags.
*	\note	Tested for top-down and bottom-up DIB's
*/
int dib_to_hdc(HDC hdc, const RECT *rectDst, 
			CLDIB *dib, const RECT *rectSrc, DWORD flags)
{
	RECT dstR, srcR;
	int dibHa = dib_get_height(dib);

	if(rectDst == NULL)
		SetRect(&dstR, 0, 0, dib_get_width(dib), dibHa);
	else
		CopyRect(&dstR, rectDst);

	if(rectSrc == NULL)
		SetRect(&srcR, 0, 0, dib_get_width(dib), dibHa);
	else
		CopyRect(&srcR, rectSrc);

	int srcW = srcR.right-srcR.left, srcH = srcR.bottom-srcR.top;
	int dstW = dstR.right-dstR.left, dstH = dstR.bottom-dstR.top;

	SetStretchBltMode(hdc, COLORONCOLOR);
	return StretchDIBits( hdc, 
		dstR.left, dstR.bottom, dstW, -dstH, 
		srcR.left, dibHa-srcR.top, srcW, -srcH, 
		dib_get_img(dib), dib_get_info(dib), 
		DIB_RGB_COLORS, flags);	
}


//! Copies a DIB to a device context (direct StretchBlt variant).
/*!	\param hdc	Destination DC.
*	\param dX	Destination left
*	\param dY	Destination top (?)
*	\param dW	Destination width
*	\param dH	Destination height
*	\param dib	DIB to blit
*	\param sX	Source left
*	\param sY	Source top (?)
*	\param sW	Source width
*	\param sH	Source height.
*	\param flags	Blit flags.
*	\note	Tested for top-down and bottom-up DIB's
*/
int dib_blit(HDC hdc, int dX, int dY, int dW, int dH, 
	CLDIB *dib, int sX, int sY, int sW, int sH, DWORD flags)
{
	if(!dib)
		return 0;
	int dibHa = dib_get_height(dib);

	SetStretchBltMode(hdc, COLORONCOLOR);
	return StretchDIBits( hdc, 
		dX, dY+dH, dW, -dH, 
		sX, dibHa-sY+1, sW, -sH, 
		dib_get_img(dib), dib_get_info(dib), 
		DIB_RGB_COLORS, flags);		
}

// === HBITMAP functions ==============================================


//! Copies a HBITMAP to a device context (direct StretchBlt variant).
/*!	\param hdc	Destination DC.
*	\param dX	Destination left
*	\param dY	Destination top (?)
*	\param dW	Destination width
*	\param dH	Destination height
*	\param hbm	HBITMAP to blit
*	\param sX	Source left
*	\param sY	Source top (?)
*	\param sW	Source width
*	\param sH	Source height.
*	\param flags	Blit flags.
*	\note	Tested for top-down and bottom-up DIB's
*/
int hbm_blit(HDC hdc, int dX, int dY, int dW, int dH, 
	HBITMAP hbm, int sX, int sY, int sW, int sH, DWORD flags)
{
	HDC hdcSrc = CreateCompatibleDC(hdc);
	HBITMAP hOldSrc = (HBITMAP)SelectObject(hdcSrc, hbm);

	SetStretchBltMode(hdc, COLORONCOLOR);
	int res = StretchBlt(hdc, dX, dY, dW, dH, 
		hdcSrc, sX, sY, sW, sH, SRCCOPY);

	SelectObject(hdcSrc, hOldSrc);
	DeleteDC(hdcSrc);
	return res;
}

#endif // _MSC_VER


// --------------------------------------------------------------------
// OPERATIONS
// --------------------------------------------------------------------

//! Flip a bitmap horizontally (8, 16, 24, 32)
bool dib_hflip(CLDIB *dib)
{
	if(dib == NULL) 
		return false;
			
	int dibW, dibH, dibB, dibP;
	dib_get_attr(dib, &dibW, &dibH, &dibB, &dibP);

	if(dibB < 8)
		return false;

	BYTE *dibL, *bufD;

	bufD = (BYTE*)malloc(dibP);
	if(bufD == NULL)
		return false;

	dibL = dib_get_img(dib);

	int ix, iy, ib, nb = dibB/8;
	
	for(iy = 0; iy<dibH; iy++)
	{	
		memcpy(bufD, dibL, dibP);

		//# TODO: 1, 4 bpp
		
		for(ix = 0; ix<dibW; ix++)
		{
			for(ib = 0; ib<nb; ib++)
				dibL[ix*nb+ib] = bufD[(dibW-1-ix)*nb+ib];
		}
		dibL += dibP;
	}

	free(bufD);

	return true;
}

//! Flips a bitmap (IP, ok)
/*!	\param dib bitmap to flip.
*	\note This is an in-place flip.
*/
bool dib_vflip(CLDIB *dib)
{
	BYTE *topL, *botL, *tempD;

	if(dib == NULL) 
		return false;

	DWORD dibP = dib_get_pitch(dib), dibH = dib_get_height(dib);
	tempD = (BYTE*)malloc(dibP);
	if(tempD == NULL)
		return false;

	topL = dib_get_img(dib);
	botL = topL+dibP*(dibH-1);

	dibH  /= 2;
	while(dibH--)
	{
		memcpy(tempD, topL, dibP);
		memcpy(topL, botL, dibP);
		memcpy(botL, tempD, dibP);
		topL += dibP;
		botL -= dibP;
	}
	free(tempD);

	return true;
}


//! Flicks between top-down and bottom-up bitmaps (all; ok)
/*!	\param dib bitmap to flip.
*	\note This does not actually flip the scanlines, just the sign of 
*	  the height parameter.
*/
bool dib_vflip2(CLDIB *dib)
{
	if(!dib_vflip(dib))
		return false;
	int hh = dib_get_height2(dib);
	dib_get_hdr(dib)->biHeight = -hh;
	return true;
}


//! Copies a portion of a bitmap (all; ok)
/*! Similar to \c dib_clone, but can crop the image too. The 
*	boundaries of the new bitmap need not fit inside the source; the 
*	outside parts will be zeroed.
*	\param src Source bitmap.
*	\param ll Left of rectangle.
*	\param tt Top of rectangle.
*	\param rr Right of rectangle.
*	\param bb Bottom of rectangle.
*	\param bClip If \c true, the rectangle will be clipped to the 
*	  dimensions of \c src.
*	\return Copied and cropped bitmap.	
*/
CLDIB *dib_copy(CLDIB *src, int ll, int tt, int rr, int bb, bool bClip)
{
	if(src ==NULL || ll ==rr || tt ==bb)
		return NULL;

	int srcW = dib_get_width(src);
	int srcH = dib_get_height(src);
	int srcB = dib_get_bpp(src);
	int srcP = dib_get_pitch(src);

	// Normalize rect
	if(rr<ll)
	{	int tmp = ll; ll = rr; rr = tmp;	}
	if(bb<tt)
	{	int tmp = tt; tt = bb; bb = tmp;	}

	// Clip if requested
	if(bClip)
	{
		if(ll<0)	ll = 0;
		if(tt<0)	tt = 0;
		if(rr>srcW)	rr = srcW;
		if(bb>srcH) bb = srcH; 
	}

	int dstW = rr-ll, dstH = bb-tt;
	CLDIB *dst = dib_alloc(dstW, dstH, srcB, NULL, true);
	if(dst ==NULL)
		return NULL;
	
	dib_pal_cpy(dst, src);

	// set base src,dst pointers
	int dstP = dib_get_pitch(dst);
	BYTE *srcL = dib_get_img(src), *dstL = dib_get_img(dst);

	if(ll>=0)	// set horz base
		srcL += ll*srcB >> 3;
	else
		dstL -= ll*srcB >> 3;		// - (-|ll|)

	if(tt>=0)	// set vert base
		srcL += tt*srcP;
	else
		dstL -= tt*dstP;		// - (-|tt|)
	
	// if we're not clipping, we have to be careful at the boundaries
	if(!bClip)
	{
		memset(dib_get_img(dst), 0, dib_get_size_img(dst));
		dstW = MIN(rr,srcW) - MAX(ll,0);
		dstH = MIN(bb,srcH) - MAX(tt,0);
	}

	int ii, nn = (dstW*srcB+7)/8;
	// specials for byte-crossing bpp<8 (bleh)
	if(ll>0 && (ll*srcB&7) )
	{
		int ix, iy;
		int ofs = (ll*srcB)&7;
		BYTE ch;
		for(iy = 0; iy<dstH; iy++)
		{
			for(ix = 0; ix<nn; ix++)
			{
				ch = srcL[iy*srcP+ix] << ofs;
				ch |= srcL[iy*srcP+ix+1] >> (8-ofs);
				dstL[iy*dstP+ix]= ch;
			}
		}
	}
	else	// byte-cpy is safe
	{
		for(ii = 0; ii<dstH; ii++)
			memcpy(&dstL[ii*dstP], &srcL[ii*srcP], nn);
	}

	return dst;
}


//! Paste \a src onto \a dst at position (\a dstX,\a dstY).
/*!
	\note	Still early going and somewhat restrictive. Bpps must 
		be equal and 8 or higher. Seems ok for those occasions.
*/
bool dib_paste(CLDIB *dst, CLDIB *src, int dstX, int dstY)
{
	if(src ==NULL || dst == NULL)
		return false;

	int srcW, srcH, srcB, srcP;
	int dstW, dstH, dstB, dstP;

	dib_get_attr(dst, &dstW, &dstH, &dstB, &dstP);
	dib_get_attr(src, &srcW, &srcH, &srcB, &srcP);

	// Bitdepth check. To remove later
	if(srcB != dstB || srcB<8)
		return false;

	// --- Clip ---
	int srcX = 0, srcY = 0;
	if(dstX+srcW<0 || dstX>=dstW)	return true;
	if(dstY+srcH<0 || dstY>=dstH)	return true;

	if(dstX<0)	{	srcW += dstX;	srcX -= dstX; dstX = 0;	}
	if(dstY<0)	{	srcH += dstY;	srcY -= dstY; dstY = 0;	}

	if(srcW >= dstW-dstX)	{	srcW = dstW-dstX;	}
	if(srcH >= dstH-dstY)	{	srcH = dstH-dstY;	}

	// --- Copy ---
	UINT len = srcW*srcB/8;
	BYTE *srcL = dib_get_img_at(src, srcX, srcY);
	BYTE *dstL = dib_get_img_at(dst, dstX, dstY);

	for(int ii = 0; ii<srcH; ii++)
		memcpy(&dstL[ii*dstP], &srcL[ii*srcP], len);

	return true;
}

// EOF
