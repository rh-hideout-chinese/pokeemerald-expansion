//
// Main compression routine file.
//
//! \file cprs.cpp
//! \author J Vijn
//! \date 20080208 - 20080208
//
/* === NOTES ===
  * There are only two things you'd need to make this completely 
	separate: RECORD and the GBA types.
  * PONDER: since not all of these things are actually compression, 
	a namecange may be in order at some point :| 
*/

#include <assert.h>
#include "cprs.h"


// --------------------------------------------------------------------
// FUNCTIONS 
// --------------------------------------------------------------------

//! Create the compression header word (little endian)
u32	cprs_create_header(uint size, u8 tag)
{
	u8 data[4];

	data[0]= tag;
	data[1]= (size    ) & 255;
	data[2]= (size>> 8) & 255;
	data[3]= (size >> 16) & 255;
	return *(u32*)data;
}

//! compression dispatcher.
bool cprs_compress(RECORD *dst, const RECORD *src, ECprsTag tag)
{
	assert(dst && src);
	if(dst ==NULL || src ==NULL)
		return false;

	bool bOK = false;

	switch(tag)
	{
	case CPRS_FAKE_TAG:
		bOK = fake_compress(dst, src) != 0;			break;

	case CPRS_LZ77_TAG:
		bOK = lz77gba_compress(dst, src) != 0;		break;

	//CPRS_HUF4_TAG
	case CPRS_HUFF8_TAG:
		bOK = huffgba_compress(dst, src) != 0;	break;

	case CPRS_RLE_TAG:
		bOK = rle8gba_compress(dst, src) != 0;		break;


	//CPRS_DIFF8_TAG
	//CPRS_DIFF16_TAG
	default:
		return false;
	}

	return bOK;
}

bool cprs_decompress(RECORD *dst, const RECORD *src)
{
	assert(dst && src && src->data);
	if(dst ==NULL || src ==NULL || src->data ==NULL)
		return false;

	u32 header = read32le(src->data);
	
	switch(header&255)
	{
	case CPRS_FAKE_TAG:
		fake_decompress(dst, src);
		break;
	case CPRS_LZ77_TAG:
		lz77gba_decompress(dst, src);
		break;
	case CPRS_HUFF_TAG:
		assert(0);
		return false;
	case CPRS_HUFF8_TAG:
		assert(0);
		return false;
	case CPRS_RLE_TAG:
		rle8gba_decompress(dst, src);
		break;
	} 

	return true;
}


//! Don't compress, but still add a compression-like header.
uint fake_compress(RECORD *dst, const RECORD *src)
{
	assert(dst && src && src->data);
	if(dst ==NULL || src ==NULL || src->data ==NULL)
		return 0;

	uint srcS = rec_size(src);
	uint dstS = ALIGN4(srcS)+4;

	u8 *dstD = (u8*)malloc(dstS);
	if(dstD == NULL)
		return 0;

	write32le(dstD, srcS << 8 | CPRS_FAKE_TAG);
	memcpy(dstD+4, src->data, srcS);
	rec_attach(dst, dstD, 1, dstS);

	return dstS;
}


uint fake_decompress(RECORD *dst, const RECORD *src)
{
	assert(dst && src && src->data);
	if(dst ==NULL || src ==NULL || src->data ==NULL)
		return 0;

	u32 header = read32le(src->data);
	if((header&255) != CPRS_FAKE_TAG)
		return 0;

	uint dstS = header >> 8;
	u8 *dstD = (u8*)malloc(dstS);

	memcpy(src->data+4, dstD, dstS);
	rec_attach(dst, dstD, 1, dstS);	

	return dstS;
}

// EOF
