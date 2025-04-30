//
//! \file grit_rle.cpp
//!   GBA RLE compression
//! \date 20050814 - 20050906
//! \author cearn
//
// === NOTES === 

#include <stdlib.h>
#include <memory.h>

/// === TYPES =========================================================

typedef unsigned char u8, BYTE;
typedef unsigned int u32;

typedef struct RECORD
{
	int width;
	int height;
	BYTE *data;
} RECORD;

#define ALIGN4(nn) ( ((nn)+3)&~3 )

#define CPRS_RLE_TAG 0x30


// --------------------------------------------------------------------
// FUNCTIONS
// --------------------------------------------------------------------


//! Compressor for GBA RLE
/*!
*/

//BYTE *cprs_gba_rle8(const BYTE *srcD, int srcS, int *pdstS)
int cprs_gba_rle8(RECORD *dst, const RECORD *src)
{
	if(src ==NULL || dst ==NULL || src->data == NULL)
		return 0;

	int ii, rle, non;
	BYTE curr, prev;

	int srcS = src->width*src->height;
	BYTE *srcD = src->data;

	// Annoyingly enough, rle _can_ end up being larger than
	// the original. A checker-board will do it for example.
	// if srcS is the size of the alternating pattern, then
	// the endresult will be 4 + srcS + (srcS+0x80-1)/0x80.
	int dstS = 8+2*(srcS);
	BYTE *dstD = (BYTE*)malloc(dstS), *dstL = dstD;
	if(dstD == NULL)
		return 0;

	prev = srcD[0];
	rle = non = 1;

	// NOTE! non will always be 1 more than the actual non-stretch
	// PONDER: why [1,srcS] ?? (to finish up the stretch)
	for(ii = 1; ii<=srcS; ii++)
	{
		if(ii != srcS)
			curr = srcD[ii];

		if(rle ==0x82 || ii ==srcS)	// stop rle
			prev = ~curr;

		if(rle<3 && (non+rle > 0x80 || ii ==srcS))	// ** mini non
		{
			non += rle;
			dstL[0]= non-2;	
			memcpy(&dstL[1], &srcD[ii-non+1], non-1);
			dstL += non;
			non = rle = 1;
		}
		else if(curr == prev)		// ** start rle / non on hold
		{
			rle++;
			if( rle ==3 && non>1 )	// write non-1 bytes
			{
				dstL[0]= non-2;
				memcpy(&dstL[1], &srcD[ii-non-1], non-1);
				dstL += non;
				non = 1;
			}
		}
		else						// ** rle end / non start
		{
			if(rle>=3)	// write rle
			{
				dstL[0]= 0x80|(rle-3);
				dstL[1]= srcD[ii-1];
				dstL += 2;
				non = 0;
				rle = 1;
			}
			non += rle;
			rle = 1;
		}
		prev = curr;
	}
	
	dstS = ALIGN4(dstL-dstD)+4;

	dstL = (BYTE*)malloc(dstS);
	if(dstL == NULL)
	{
		free(dstD);
		return 0;
	}

	*(u32*)dstL = (srcS << 8) | CPRS_RLE_TAG;
	memcpy(&dstL[4], dstD, dstS-4);

	dst->width = 1;
	dst->height = dstS;
	free(dst->data);
	dst->data = dstL;


	free(dstD);

	return dstS;
}

// EOF
