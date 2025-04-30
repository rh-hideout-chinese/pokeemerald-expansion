//
//! \file grit_huff.cpp
//!   Huffman compression implementation
//! \date 20050906 - 20050906
//! \author cearn
//
// === NOTES === 
// * Most tables use BASE 1 INDEXING. because 0 has a special meaning
//   YHBW.
// * 8bpp huffman still fails at times ... but why? array overflow?

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char u8, BYTE;
typedef unsigned int u32;

typedef struct RECORD
{
	int width;
	int height;
	BYTE *data;
} RECORD;

#define ALIGN4(nn) ( ((nn)+3)&~3 )

#define CPRS_HUFF_TAG 0x20


// --------------------------------------------------------------------
// GLOBALS
// --------------------------------------------------------------------


static u32 *gids, *gprobs, *gtiers;
static int *gdad, *glson, *grson;
static BYTE *gtable;


// --------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------


static void hufapp(u32 ids[], const u32 probs[], u32 nn, u32 ii);
static void huff_init_freqs(u32 freqs[], const void *srcv, int srcS, int srcB);
static void huff_table_fill(int id, int tier);


// --------------------------------------------------------------------
// FUNCTIONS
// --------------------------------------------------------------------


//! Sorts the ids to the frequency table
static void hufapp(u32 ids[], const u32 probs[], u32 nn, u32 ii)
{
	u32 jj,kk;

	kk = ids[ii];
	//while(ii < nn/2)
	while(ii <= nn/2)
	{
		//jj = 2*ii+1;
		jj = 2*ii;
		if(jj < nn && probs[ids[jj]] > probs[ids[jj+1]])
			jj++;
		if(probs[kk] <= probs[ids[jj]])
			break;
		ids[ii]= ids[jj];
		ii = jj;
	}
	ids[ii]=kk;
}

//! Gather the frequency table
static void huff_init_freqs(u32 freqs[], const void *srcv, int srcS, int srcB)
{
	int ii, jj, nn = srcS/4, mm = 32/srcB;
	int count = 1 << srcB;
	u32 mask = count-1;
	u32 *srcD = (u32*)srcv;

	memset(freqs, 0, count*sizeof(u32));
	for(ii = 0; ii<nn; ii++)
		for(jj = 0; jj<mm; jj++)			// for all the sub-pixels
			freqs[(srcD[ii] >> (jj*srcB))&mask]++;
}


//! Runs recursively through the tree, filling the table.
// OK. It's just sickening how easy this turned out to be
static void huff_table_fill(int id, int tier)
{
	// go left
	if(glson[id])
	{
		huff_table_fill(glson[id], tier+1);

		u32 curr = (gtiers[tier+1]-gtiers[tier]-3)/2;
		curr |= (glson[glson[id]] ? 0 : 0x80);
		curr |= (grson[grson[id]] ? 0 : 0x40);

		// register branch
		gtable[gtiers[tier]++]= (BYTE)curr;
	}
	else
		// register leaf
		gtable[gtiers[tier]++]= id-1;

	// move up and right
	id = gdad[id];
	if(id < 0)
		huff_table_fill(grson[-id], tier);
}

//! Main Huffman routine
int cprs_gba_huff(RECORD *dst, const RECORD *src, int srcB)
{
	if(dst ==NULL || src ==NULL || src->data ==NULL)
		return 0;

	int ii, jj, kk;
	int nch = 1 << srcB, nodes = 2*nch-1;
	int srcS = src->width*src->height;

	// build frequency table and used id list
	u32 freqs[256], _ids[512], _probs[512];
	gids = _ids-1;

	gprobs = _probs-1;
	huff_init_freqs(freqs, src->data, srcS, srcB);
	memcpy(_probs, freqs, 256*sizeof(u32));
	memset(&_probs[256], 0, 256*sizeof(u32));

	int nids = 0;
	for(ii = 1; ii<=nch; ii++)
		if(gprobs[ii])
			gids[++nids]= ii;

	// --- build tree ---

	// first the 'real' nodes
	for(ii = nids; ii>0; ii--)
		hufapp(gids, gprobs, nids, ii);

	int _lson[512], _rson[512], _dad[512];

	glson = _lson-1;
	grson = _rson-1;
	gdad = _dad-1;
	memset(_lson, 0, 512*sizeof(int));
	memset(_rson, 0, 512*sizeof(int));
	memset(_dad, 0, 512*sizeof(int));

	// now the composite nodes
	// ids[1] is always the lowest form
	ii = nch;
	while(nids)
	{
		jj = gids[1];
		gids[1]= gids[nids--];
		hufapp(gids, gprobs, nids, 1);
		gprobs[++ii]= gprobs[gids[1]] + gprobs[jj];
		glson[ii]=  gids[1];
		grson[ii]= jj;
		gdad[gids[1]]= -ii;	// negative indicates left node
		gdad[jj]= gids[1]= ii;
		hufapp(gids, gprobs, nids, 1);
	}

	// ii-1 is root, not ii!!
	// Otherwise, you get one extra but useless bit in the codes
	nids = ii-1;
	gdad[nids]= 0;

	// --- make the codes ---
	u32 lens[256], codes[256], code;

	// NOTE: gids is now trashed anyway, so keep track of the 
	// tiers there now
	int maxlen = 0;
	gtiers = _ids;
	memset(gtiers, 0, 256*sizeof(u32));

	for(ii = 0; ii<nch; ii++)
	{
		if(gprobs[ii+1] == 0)
			continue;

		kk = gdad[ii+1];
		code = 0;
		for(jj = 0; kk; jj++)
		{
			if(kk>0)
				code |= 1 << jj;
			else
				kk = -kk;
			kk = gdad[kk];
		}
		codes[ii]= code;
		if(jj>=32)		// codes are too long, FAIL!
			return 0;
		lens[ii]= jj;

		// tier tracker:
		jj++;
		gtiers[jj]++;
		if(jj>maxlen)
			maxlen = jj;
	}

	// --- create the table --- (ack!)

	// finish up tier positions
	for(ii = maxlen-1; ii>=0; ii--)
		gtiers[ii] += gtiers[ii+1]/2;

	for(ii = 0; ii<maxlen; ii++)
		gtiers[ii+1] += gtiers[ii];

	BYTE table[512];
	gtable = table;
	memset(table, -1, 512);

	huff_table_fill(nids, 0);

	// --- Encode the source data ---

	int dstS = srcS*2;
	u32 mask = nch-1;

	BYTE *dstD = (BYTE*)malloc(dstS);
	if(dstD == NULL)	// whatchoo mean, failed ?!?
		return 0;

	u32 *srcL4 = (u32*)src->data, *dstL4 = (u32*)dstD;
	u32 buf, chunk = 0;
	int nn = srcS/4, mm = 32/srcB, len = 32;

	for(ii = 0; ii<nn; ii++)
	{
		buf = *srcL4++;
		for(jj = 0; jj<mm; jj++)
		{
			kk = (buf >> (jj*srcB)) & mask;
			len -= lens[kk];
			if(len<0)	// goto new u32
			{
				chunk |= codes[kk] >> (-len);
				*dstL4++= chunk;
				len += 32;
				chunk = codes[kk] << len;
				dstS += 4;
			}
			else		// business as usual
				chunk |= codes[kk] << len;
		}
	}
	// don't forget the rest
	if(len != 32)
		*dstL4++ = chunk;
	dstS = (BYTE*)dstL4 - (BYTE*)dstD;

	// --- put everything together ---
	// full size: header (4) + table size (1) + table (gtiers[maxlen]) + dstS

	len = gtiers[maxlen];
	dstS = ALIGN4(5+len+dstS);
	free(dst->data);

	dst->width = 1;
	dst->height = dstS;
	dst->data = (BYTE*)malloc(dstS);

	*(u32*)dst->data = srcS << 8 | CPRS_HUFF_TAG | srcB;
	dst->data[4]= (len-1)/2;
	memcpy(&dst->data[5], gtable, len);
	memcpy(&dst->data[5+len], dstD, dstS-len-5);
	free(dstD);

	return dstS;
}

// EOF
