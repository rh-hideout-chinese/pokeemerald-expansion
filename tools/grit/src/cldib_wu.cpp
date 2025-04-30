//
// cldib_wu.h
//   Wu quantizer implementation
//   Copied wholesale from FreeImage 3.6
//

///////////////////////////////////////////////////////////////////////
//	    C Implementation of Wu's Color Quantizer (v. 2)
//	    (see Graphics Gems vol. II, pp. 126-133)
//
// Author:	Xiaolin Wu
// Dept. of Computer Science
// Univ. of Western Ontario
// London, Ontario N6A 5B7
// wu@csd.uwo.ca
// 
// Algorithm: Greedy orthogonal bipartition of RGB space for variance
// 	   minimization aided by inclusion-exclusion tricks.
// 	   For speed no nearest neighbor search is done. Slightly
// 	   better performance can be expected by more sophisticated
// 	   but more expensive versions.
// 
// The author thanks Tom Lane at Tom_Lane@G.GP.CS.CMU.EDU for much of
// additional documentation and a cure to a previous bug.
// 
// Free to distribute, comments and suggestions are appreciated.
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
// History
// -------
// July 2000:  C++ Implementation of Wu's Color Quantizer
//             and adaptation for the FreeImage 2 Library
//             Author: Herv� Drolon (drolon@infonie.fr)
// March 2004: Adaptation for the FreeImage 3 library (port to big endian processors)
//             Author: Herv� Drolon (drolon@infonie.fr)
///////////////////////////////////////////////////////////////////////

#include "cldib_core.h"
#include "cldib_quant.h"

///////////////////////////////////////////////////////////////////////

// 3D array indexation
#define INDEX(r, g, b)	( (r)*33*33 + (g)*33 + (b) )


// Constructor / Destructor
dibWuQuantizer::dibWuQuantizer(CLDIB *dib)
{
	mWidth = dib_get_width(dib);
	mHeight = dib_get_height(dib);
	mPitch = dib_get_pitch(dib);
	mDib = dib;

	gm2 = NULL;
	wt = mr = mg = mb = NULL;
	Qadd = NULL;

	// Allocate 3D arrays
	gm2 = (float*)malloc(33*33*33 * sizeof(float));
	wt = (LONG*)malloc(33*33*33 * sizeof(LONG));
	mr = (LONG*)malloc(33*33*33 * sizeof(LONG));
	mg = (LONG*)malloc(33*33*33 * sizeof(LONG));
	mb = (LONG*)malloc(33*33*33 * sizeof(LONG));

	// Allocate Qadd
	Qadd = (WORD*)malloc(mWidth*mHeight * sizeof(WORD));

	if(!gm2 || !wt || !mr || !mg || !mb || !Qadd)
	{
		SAFE_FREE(Qadd);
		SAFE_FREE(mb);
		SAFE_FREE(mg);
		SAFE_FREE(mr);
		SAFE_FREE(wt);
		SAFE_FREE(gm2);
		throw "Not enough memory";
	}
	memset(gm2, 0, 33*33*33 * sizeof(float));
	memset( wt, 0, 33*33*33 * sizeof(LONG));
	memset( mr, 0, 33*33*33 * sizeof(LONG));
	memset( mg, 0, 33*33*33 * sizeof(LONG));
	memset( mb, 0, 33*33*33 * sizeof(LONG));
	memset(Qadd, 0, mWidth*mHeight * sizeof(WORD));
}

dibWuQuantizer::~dibWuQuantizer()
{
	SAFE_FREE(Qadd);
	SAFE_FREE(mb);
	SAFE_FREE(mg);
	SAFE_FREE(mr);
	SAFE_FREE(wt);
	SAFE_FREE(gm2);
}


// Histogram is in elements 1..HISTSIZE along each axis,
// element 0 is for base or marginal value
// NB: these must start out 0!

// Build 3-D color histogram of counts, r/g/b, c^2
void 
dibWuQuantizer::Hist3D(LONG *vwt, LONG *vmr, LONG *vmg, LONG *vmb, float *m2)
{
	int ii, ix, iy;
	int inr, ing, inb;
	int table[256];

	for(ii = 0; ii<256; ii++)
		table[ii] = ii*ii;

	int imgW, imgH, pxlW;
	dib_get_attr(mDib, &imgW, &imgH, &pxlW, NULL);
	pxlW  /= 8;

	BYTE *pxl, rr, gg, bb;

	for(iy = 0; iy<imgH; iy++)
	{
		pxl = dib_get_img_at(mDib, 0, iy);
		for(ix = 0; ix<imgW; ix++)	
		{
			rr = pxl[CCID_RED];
			gg = pxl[CCID_GREEN];
			bb = pxl[CCID_BLUE];

			inr = rr/8 + 1;
			ing = gg/8 + 1;
			inb = bb/8 + 1;
			Qadd[iy*imgW + ix] = ii = INDEX(inr, ing, inb);
			// [inr][ing][inb]
			vwt[ii]++;
			vmr[ii] += rr;
			vmg[ii] += gg;
			vmb[ii] += bb;
			m2[ii] += (float)( table[rr] + table[gg] + table[bb] );
			pxl += pxlW;
		}
	}

	return;
}


// At conclusion of the histogram step, we can interpret
// wt[r][g][b] = sum over voxel of P(c)
// mr[r][g][b] = sum over voxel of r*P(c)  ,  similarly for mg, mb
// m2[r][g][b] = sum over voxel of c^2*P(c)
// Actually each of these should be divided by 'ImageSize' to give the usual
// interpretation of P() as ranging from 0 to 1, but we needn't do that here.


// We now convert histogram into moments so that we can rapidly calculate
// the sums of the above quantities over any desired box.

// Compute cumulative moments
void 
dibWuQuantizer::M3D(LONG *vwt, LONG *vmr, LONG *vmg, LONG *vmb, float *m2)
{
	WORD ind1, ind2;
	BYTE ii, ir, ig, ib;
	LONG line, line_r, line_g, line_b;
	LONG area[33], area_r[33], area_g[33], area_b[33];
	float line2, area2[33];

	for(ir = 1; ir <= 32; ir++) 
	{
		for(ii = 0; ii <= 32; ii++) 
		{
			area2[ii]= 0;
			area[ii]= area_r[ii]= area_g[ii]= area_b[ii]= 0;
		}
		for(ig = 1; ig <= 32; ig++) 
		{
			line2 = 0;
			line = line_r = line_g = line_b = 0;
			for(ib = 1; ib <= 32; ib++) 
			{			 
				ind1 = INDEX(ir, ig, ib); // [r][g][b]
				line += vwt[ind1];
				line_r += vmr[ind1]; 
				line_g += vmg[ind1]; 
				line_b += vmb[ind1];
				line2 += m2[ind1];

				area[ib] += line;
				area_r[ib] += line_r;
				area_g[ib] += line_g;
				area_b[ib] += line_b;
				area2[ib] += line2;

				ind2 = ind1 - 1089; // [r-1][g][b]
				vwt[ind1] = vwt[ind2] + area[ib];
				vmr[ind1] = vmr[ind2] + area_r[ib];
				vmg[ind1] = vmg[ind2] + area_g[ib];
				vmb[ind1] = vmb[ind2] + area_b[ib];
				m2[ind1] = m2[ind2] + area2[ib];
			}
		}
	}
}

// Compute sum over a box of any given statistic
LONG 
dibWuQuantizer::Vol( Box *cube, LONG *mmt ) 
{
	return  ( mmt[INDEX(cube->r1, cube->g1, cube->b1)] 
			- mmt[INDEX(cube->r1, cube->g1, cube->b0)]
			- mmt[INDEX(cube->r1, cube->g0, cube->b1)]
			+ mmt[INDEX(cube->r1, cube->g0, cube->b0)]
			- mmt[INDEX(cube->r0, cube->g1, cube->b1)]
			+ mmt[INDEX(cube->r0, cube->g1, cube->b0)]
			+ mmt[INDEX(cube->r0, cube->g0, cube->b1)]
			- mmt[INDEX(cube->r0, cube->g0, cube->b0)] 
			);
}

// The next two routines allow a slightly more efficient calculation
// of Vol() for a proposed subbox of a given box.  The sum of Top()
// and Bottom() is the Vol() of a subbox split in the given direction
// and with the specified new upper bound.


// Compute part of Vol(cube, mmt) that doesn't depend on r1, g1, or b1
// (depending on dir)

LONG 
dibWuQuantizer::Bottom(Box *cube, BYTE dir, LONG *mmt)
{
	switch(dir)
	{
		case CCID_RED:
			return( - mmt[INDEX(cube->r0, cube->g1, cube->b1)]
					+ mmt[INDEX(cube->r0, cube->g1, cube->b0)]
					+ mmt[INDEX(cube->r0, cube->g0, cube->b1)]
					- mmt[INDEX(cube->r0, cube->g0, cube->b0)] );
			break;
		case CCID_GREEN:
			return( - mmt[INDEX(cube->r1, cube->g0, cube->b1)]
					+ mmt[INDEX(cube->r1, cube->g0, cube->b0)]
					+ mmt[INDEX(cube->r0, cube->g0, cube->b1)]
					- mmt[INDEX(cube->r0, cube->g0, cube->b0)] );
			break;
		case CCID_BLUE:
			return( - mmt[INDEX(cube->r1, cube->g1, cube->b0)]
					+ mmt[INDEX(cube->r1, cube->g0, cube->b0)]
					+ mmt[INDEX(cube->r0, cube->g1, cube->b0)]
					- mmt[INDEX(cube->r0, cube->g0, cube->b0)] );
			break;
	}
	return 0;
}


// Compute remainder of Vol(cube, mmt), substituting pos for
// r1, g1, or b1 (depending on dir)

LONG 
dibWuQuantizer::Top(Box *cube, BYTE dir, int pos, LONG *mmt)
{
	switch(dir)
	{
		case CCID_RED:
			return (  mmt[INDEX(pos, cube->g1, cube->b1)] 
					- mmt[INDEX(pos, cube->g1, cube->b0)]
					- mmt[INDEX(pos, cube->g0, cube->b1)]
					+ mmt[INDEX(pos, cube->g0, cube->b0)] );
			break;
		case CCID_GREEN:
			return (  mmt[INDEX(cube->r1, pos, cube->b1)] 
					- mmt[INDEX(cube->r1, pos, cube->b0)]
					- mmt[INDEX(cube->r0, pos, cube->b1)]
					+ mmt[INDEX(cube->r0, pos, cube->b0)] );
			break;
		case CCID_BLUE:
			return (  mmt[INDEX(cube->r1, cube->g1, pos)]
					- mmt[INDEX(cube->r1, cube->g0, pos)]
					- mmt[INDEX(cube->r0, cube->g1, pos)]
					+ mmt[INDEX(cube->r0, cube->g0, pos)] );
			break;
	}

	return 0;
}

// Compute the weighted variance of a box 
// NB: as with the raw statistics, this is really the variance * ImageSize 
float 
dibWuQuantizer::Var(Box *cube)
{
	float dr = (float) Vol(cube, mr); 
	float dg = (float) Vol(cube, mg); 
	float db = (float) Vol(cube, mb);
	float xx =  
			 gm2[INDEX(cube->r1, cube->g1, cube->b1)] 
			-gm2[INDEX(cube->r1, cube->g1, cube->b0)]
			-gm2[INDEX(cube->r1, cube->g0, cube->b1)]
			+gm2[INDEX(cube->r1, cube->g0, cube->b0)]
			-gm2[INDEX(cube->r0, cube->g1, cube->b1)]
			+gm2[INDEX(cube->r0, cube->g1, cube->b0)]
			+gm2[INDEX(cube->r0, cube->g0, cube->b1)]
			-gm2[INDEX(cube->r0, cube->g0, cube->b0)];

    return (xx - (dr*dr+dg*dg+db*db)/(float)Vol(cube,wt));    
}

// We want to minimize the sum of the variances of two subboxes.
// The sum(c^2) terms can be ignored since their sum over both subboxes
// is the same (the sum for the whole box) no matter where we split.
// The remaining terms have a minus sign in the variance formula,
// so we drop the minus sign and MAXIMIZE the sum of the two terms.

float
dibWuQuantizer::Maximize(Box *cube, BYTE dir, int first, int last, int *cut, 
	LONG whole_r, LONG whole_g, LONG whole_b, LONG whole_w)
{
	int ii;
	float temp, max = 0.0;

	LONG half_r, half_g, half_b, half_w;
	LONG base_r = Bottom(cube, dir, mr);
	LONG base_g = Bottom(cube, dir, mg);
	LONG base_b = Bottom(cube, dir, mb);
	LONG base_w = Bottom(cube, dir, wt);

	*cut = -1;
	for(ii = first; ii<last; ii++)
	{
		half_r = base_r + Top(cube, dir, ii, mr);
		half_g = base_g + Top(cube, dir, ii, mg);
		half_b = base_b + Top(cube, dir, ii, mb);
		half_w = base_w + Top(cube, dir, ii, wt);

        // now half_x is sum over lower half of box, if split at i
		if(half_w == 0)		// subbox could be empty of pixels!
			continue;		// never split into an empty box
		else
			temp = ((float)half_r*half_r + (float)half_g*half_g + 
				(float)half_b*half_b)/half_w;

		half_r = whole_r - half_r;
		half_g = whole_g - half_g;
		half_b = whole_b - half_b;
		half_w = whole_w - half_w;

        if(half_w == 0)		// subbox could be empty of pixels!
			continue;		// never split into an empty box
		else
			temp += ((float)half_r*half_r + (float)half_g*half_g + 
				(float)half_b*half_b)/half_w;

    	if(temp > max)
		{	max = temp;	*cut = ii;	}
    }

    return max;
}

bool
dibWuQuantizer::Cut(Box *set1, Box *set2) 
{
	BYTE dir;
	int cutr, cutg, cutb;

    LONG whole_r = Vol(set1, mr);
    LONG whole_g = Vol(set1, mg);
    LONG whole_b = Vol(set1, mb);
    LONG whole_w = Vol(set1, wt);

    float maxr = Maximize(set1, CCID_RED, 
		set1->r0+1, set1->r1, &cutr, 
		whole_r, whole_g, whole_b, whole_w);    
	float maxg = Maximize(set1, CCID_GREEN, 
		set1->g0+1, set1->g1, &cutg, 
		whole_r, whole_g, whole_b, whole_w);    
	float maxb = Maximize(set1, CCID_BLUE, 
		set1->b0+1, set1->b1, &cutb, 
		whole_r, whole_g, whole_b, whole_w);

    if ((maxr >= maxg) && (maxr >= maxb))
	{
		dir = CCID_RED;
		if (cutr < 0)
			return false; // can't split the box
    } 
	else if((maxg >= maxr) && (maxg>=maxb))
		dir = CCID_GREEN;
	else
		dir = CCID_BLUE;

	set2->r1 = set1->r1;
    set2->g1 = set1->g1;
    set2->b1 = set1->b1;

    switch(dir)
	{
	case CCID_RED:
		set2->r0 = set1->r1 = cutr;
		set2->g0 = set1->g0;
		set2->b0 = set1->b0;
		break;

	case CCID_GREEN:
		set2->g0 = set1->g1 = cutg;
		set2->r0 = set1->r0;
		set2->b0 = set1->b0;
		break;

	case CCID_BLUE:
		set2->b0 = set1->b1 = cutb;
		set2->r0 = set1->r0;
		set2->g0 = set1->g0;
		break;
    }

    set1->vol = 
		(set1->r1-set1->r0)*(set1->g1-set1->g0)*(set1->b1-set1->b0);
    set2->vol = 
		(set2->r1-set2->r0)*(set2->g1-set2->g0)*(set2->b1-set2->b0);

    return true;
}


void
dibWuQuantizer::Mark(Box *cube, int label, BYTE *tag) 
{
	int r, g, b;
    for(r = cube->r0 + 1; r <= cube->r1; r++)
		for(g = cube->g0 + 1; g <= cube->g1; g++)
			for(b = cube->b0 + 1; b <= cube->b1; b++)
				tag[INDEX(r, g, b)]= label;
}

// Wu Quantization algorithm
CLDIB *
dibWuQuantizer::Quantize(int PalSize)
{
	int ii, jj;
	BYTE *tag = NULL;
	CLDIB *dst = NULL;
	try
	{
		int	next;
		LONG weight;
		float vv[PAL_MAX], temp;
		Box	cube[PAL_MAX];
		
		// Compute 3D histogram
		Hist3D(wt, mr, mg, mb, gm2);
		// Compute moments
		M3D(wt, mr, mg, mb, gm2);

		cube[0].r0 = cube[0].g0 = cube[0].b0 = 0;
		cube[0].r1 = cube[0].g1 = cube[0].b1 = 32;
		next = 0;

		for(ii = 1; ii<PalSize; ii++) 
		{
			if(Cut(&cube[next], &cube[ii])) 
			{
				// volume test ensures we won't try to cut one-cell box
				vv[next]= (cube[next].vol > 1) ? Var(&cube[next]) : 0;
				vv[  ii]= (cube[  ii].vol > 1) ? Var(&cube[  ii]) : 0;
			} 
			else 
			{
				  vv[next]= 0.0;	// don't try to split this box again
				  ii--;				// didn't create box ii
			}

			next = 0; 
			temp = vv[0];
			for(jj = 1; jj <= ii; jj++)
			{
				if(vv[jj] > temp) 
				{	temp = vv[jj]; next = jj;	}
			}

			if(temp <= 0.0) 
			{
				  PalSize = ii+1;
				  // Error: "Only got 'PalSize' boxes"
				  break;
			}
		}

		// Partition done
		// the space for array gm2 can be freed now
		free(gm2);
		gm2 = NULL;

		// Allocate a new dib
		int srcW = dib_get_width(mDib);
		int srcH = dib_get_height(mDib);

		dst = dib_alloc(srcW, srcH, 8, NULL, true);
		if(dst == NULL)
			throw "Not enough memory";

		// create an optimized palette
		RGBQUAD *pal = dib_get_pal(dst);
		memset(pal, 0, PAL_MAX*RGB_SIZE);

		tag = (BYTE*)malloc(33*33*33 * sizeof(BYTE));
		if(tag == NULL)
			throw "Not enough memory";

		for(ii = 0; ii < PalSize; ii++) 
		{
			Mark(&cube[ii], ii, tag);
			weight = Vol(&cube[ii], wt);

			if(weight) 
			{
				pal[ii].rgbRed   = (BYTE)(Vol(&cube[ii], mr) / weight);
				pal[ii].rgbGreen = (BYTE)(Vol(&cube[ii], mg) / weight);
				pal[ii].rgbBlue  = (BYTE)(Vol(&cube[ii], mb) / weight);
			} 
			else	// Error: bogus box 'k'
				pal[ii].rgbRed = pal[ii].rgbGreen = pal[ii].rgbBlue = 0;		
		}

		int dstP = dib_get_pitch(dst);
		BYTE *dstL = dib_get_img(dst);

		for(ii = 0; ii<srcH; ii++)
		{
			for(jj = 0; jj<srcW; jj++)
				dstL[jj]= tag[Qadd[ii*srcW+jj]];
			dstL += dstP;

		}
	} 
	catch(...) 
	{}

	SAFE_FREE(tag);

	return dst;
}

// EOF
