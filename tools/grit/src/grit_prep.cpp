//
//! \file grit_prep.cpp
//!   Data preparation routines
//! \date 20050814 - 20100131
//! \author cearn
/* === NOTES === 
  * 20100131,jv: Replaced mapping core. grit_prep_tiles and older reducing 
	functions still need cleaning.
  * 20080215,jv: made tile-size variable. Only works for -gb though.
  * 20080211,jv: pal-size not forced to 4-bytes anymore (as it should be).
  * 20080111,jv. Name changes, part 1
  * 20061209,jv: Fixed NDS alpha stuff. 
  * 20060727,jv: TODO: alpha clr(id) corrections
  * 20060727,jv: use RGB16 for pal conversion
  * 20060727,jv: endian stuff for prep_map, prep_gfx, prep_pal
  * PONDER: tile sort for grit_prep_map
  * PONDER: all records for grit_tile_reduce?
*/

#include <stdio.h>
#include <stdlib.h>
//#include <sys/param.h>

#include "cldib.h"
#include "grit.h"


// --------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------

bool grit_prep_work_dib(GritRec *gr);
bool grit_prep_tiles(GritRec *gr);

bool grit_prep_gfx(GritRec *gr);
bool grit_prep_map(GritRec *gr);
bool grit_prep_pal(GritRec *gr);
bool grit_prep_shared_pal(GritRec *gr);

u16 grit_find_tile_pal(BYTE *tileD);
bool grit_tile_cmp(BYTE *test, BYTE *base, u32 x_xor, u32 y_xor, BYTE mask);
CLDIB *grit_tile_reduce(RECORD *dst, CLDIB *srcDib, u32 flags, CLDIB *extDib);
RECORD *grit_meta_reduce(RECORD *dst, const RECORD *src, int metaN, u32 flags);


// --------------------------------------------------------------------
// CONSTANTS
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// FUNCTIONS
// --------------------------------------------------------------------


//! Data preparation hub
/*!	Converts and prepares the bitmap for export. 
	
*/
bool grit_prep(GritRec *gr)
{
	// TODO: clear internals
	lprintf(LOG_STATUS, "Preparing data.\n");

	if(grit_prep_work_dib(gr) == false)
	{
		lprintf(LOG_ERROR, "  No work DIB D: .\n");
		return false;
	}

	if(gr->isTiled())
	{
		if(gr->isMapped())		// Convert to tilemap/tileset
			grit_prep_map(gr);
		else					// Just (meta)tile the image.
			//# TODO: just (meta)tile; no map.
			grit_prep_tiles(gr);
	}

/* OLD
	// NOTE: don't check for -g! just yet: -g! + -m is possible too
	// if tiles: prep tiles & map
	grit_prep_tiles(gr);

	if(gr->gfxMode == GRIT_GFX_TILE)
	{
		if(gr->mapProcMode != GRIT_EXCLUDE)
			grit_prep_map(gr);
	}
*/

	if(gr->gfxProcMode != GRIT_EXCLUDE)
	{
		if(!grit_prep_gfx(gr))
			return false;
	}
	
	if(gr->palProcMode != GRIT_EXCLUDE)
	{
		if(!grit_prep_pal(gr))
			return false;
	}

	dib_free(gr->_origDib);

	lprintf(LOG_STATUS, "Data preparation complete.\n");		
	return true;
}

//! Sets up work bitmap of desired size and 8 or 16 bpp.
/*!	This basically does two things. First, create a bitmap from the 
	designated area of the source bitmap. Then, converts it 8 or 
	16 bpp, depending on \a gr.gfxBpp. Conversion to lower bpp is 
	done later, when it's more convenient. The resultant bitmap is 
	put into \a gr._dib, and will be used in later preparation.
*/
bool grit_prep_work_dib(GritRec *gr)
{
	int ii, nn;
	RGBQUAD *rgb;

	lprintf(LOG_STATUS, "Work-DIB creation.\n");		

	gr->_origDib = dib_clone(gr->srcDib);

	// --- resize ---
	CLDIB *dib = dib_copy(gr->srcDib, 
		gr->areaLeft, gr->areaTop, gr->areaRight, gr->areaBottom, 
		false);
	if(dib == NULL)
	{
		lprintf(LOG_ERROR, "  Work-DIB creation failed.\n");		
		return false;
	}
	// ... that's it? Yeah, looks like.

	// --- resample (to 8 or 16) ---
	// 
	int dibB = dib_get_bpp(dib);

	// Convert to 16bpp, but ONLY for bitmaps
	if( gr->gfxBpp == 16 && gr->gfxMode != GRIT_GFX_TILE )
	{
		if(dibB != 16)
		{
			lprintf(LOG_WARNING, "  converting from %d bpp to %d bpp.\n", 
				dibB, gr->gfxBpp);

			CLDIB *dib2 = dib_convert_copy(dib, 16, 0);

			// If paletted src AND -pT AND NOT -gT[!]
			//   use trans color pal[T]
			//# PONDER: did I fix this right?
			if(dibB <= 8 && gr->palHasAlpha && !gr->gfxHasAlpha) 
			{
				rgb = &dib_get_pal(dib)[gr->palAlphaId];
				lprintf(LOG_WARNING, 
					"  pal->true-color conversion with transp pal-id option.\n"
					"    using color %02X%02X%02X", 
						rgb->rgbRed, rgb->rgbGreen, rgb->rgbBlue);
				
				gr->gfxHasAlpha = true;
				gr->gfxAlphaColor = *rgb;
			}

			dib_free(dib);

			if(dib2 == NULL)
			{
				lprintf(LOG_ERROR, "prep: Bpp conversion failed.\n");	
				return false;
			}
			dib = dib2;
		}

		// --- Dealing with 16bpp images ---
		// Modes: 
		// 555      | GBA           | swap R_B   
		// 555+A = 1  | NDS           | swap R_B + add NDS_ALPHA
		// 555+A    | NDS, transp   | swap R_B + NDS_ALPHA if !trans-clr
		// src-pal + -pT -> NDS, transp

		// Swap palette bRGB to bBGR
		// And resolve -gT
		nn = dib_get_size_img(dib)/2;
		WORD *dibD2 = (WORD*)dib_get_img(dib);

		// Single transparent color
		if(gr->gfxHasAlpha)
		{
			rgb = &gr->gfxAlphaColor;
			WORD clr = RGB16(rgb->rgbBlue, rgb->rgbGreen, rgb->rgbRed), wd;

			lprintf(LOG_STATUS, 
				"  converting to: 16bpp BGR, alpha = 1, except for 0x%04X.\n", 
				clr);

			for(ii = 0; ii<nn; ii++)
			{
				wd = swap_rgb16(dibD2[ii]);
				dibD2[ii]= (wd == clr ? wd : wd | NDS_ALPHA);	
			}	
		}
		else if(gr->gfxMode == GRIT_GFX_BMP_A)
		{
			lprintf(LOG_STATUS, "converting to: 16bpp BGR, alpha = 1.\n");

			for(ii = 0; ii<nn; ii++)
				dibD2[ii]= swap_rgb16(dibD2[ii]) | NDS_ALPHA;
		}
		else
		{
			lprintf(LOG_STATUS, "converting to: 16bpp, BGR.\n");

			for(ii = 0; ii<nn; ii++)
				dibD2[ii]= swap_rgb16(dibD2[ii]);				
		}
	}
	else if(dibB != 8)	// otherwise, convert to 8bpp
	{
		lprintf(LOG_WARNING, "  converting from %d bpp to %d bpp.\n", 
			dibB, gr->gfxBpp);
		
		if(!dib_convert(dib, 8, 0))
		{
			dib_free(dib);
			lprintf(LOG_ERROR, "  Bpp conversion failed.\n");	
			return false;
		}
	}

	// Palette transparency additions.
	if(dib_get_bpp(dib)==8)
	{
		// If gfx-trans && !pal-trans:
		//   Find gfx-trans in palette and use that
		if(gr->gfxHasAlpha && !gr->palHasAlpha)
		{
			rgb = &gr->gfxAlphaColor;
			RGBQUAD *pal = dib_get_pal(dib);

			lprintf(LOG_WARNING, 
				"  tru/pal -> pal conversion with transp color option.\n"
				"    looking for color %02X%02X%02X in palette.\n", 
				rgb->rgbRed, rgb->rgbGreen, rgb->rgbBlue);
			
			uint ii_min = 0, dist, dist_min;
			dist_min = rgb_dist(rgb, &pal[0]);

			for(ii = 1; ii<256; ii++)
			{
				dist = rgb_dist(rgb, &pal[ii]);
				if(dist < dist_min)
				{
					ii_min = ii;
					dist_min = dist;
				}
			}

			// HACK: count 'match' only if average error is < +/-14
			if(dist_min < 576)
			{
				gr->palHasAlpha = true;
				gr->palAlphaId = ii_min;
			}
		}

		// Swap alpha and pixels palette entry
		if(gr->palHasAlpha)
		{
			lprintf(LOG_STATUS, "  Palette transparency: pal[%d].\n", 
				gr->palAlphaId);
			BYTE *imgD = dib_get_img(dib);
			nn = dib_get_size_img(dib);

			for(ii = 0; ii<nn; ii++)
			{
				if(imgD[ii] == 0)
					imgD[ii]= gr->palAlphaId;
				else if(imgD[ii] == gr->palAlphaId)
					imgD[ii]= 0;
			}
			RGBQUAD tmp, *pal = dib_get_pal(dib);
			SWAP3(pal[0], pal[gr->palAlphaId], tmp);
		}

		// TODO: Palette merging.
		if(gr->palIsShared)
		{
			lprintf(LOG_STATUS, "  Palette merging\n");
			nn = dib_pal_reduce(dib, &gr->shared->palRec);
			if(nn>PAL_MAX)
				lprintf(LOG_WARNING, "    New palette exceeds 256. Truncating.\n");
		}
	}

	dib_free(gr->_dib);
	gr->_dib = dib;
	
	lprintf(LOG_STATUS, "Work-DIB creation complete: %dx%d@%d.\n", 
		dib_get_width(gr->_dib), dib_get_height(gr->_dib), 
		dib_get_bpp(gr->_dib));		
	return true;
}

//! Rearranges the work dib into a strip of 8x8 tiles.
/*!	This only runs for tiled images and can have up to three 
	stages. First, Rearrange into screen-blocks (option -mLs); then 
	into metatiles (-Mw, -Mh), then base-tiles.
*/
bool grit_prep_tiles(GritRec *gr)
{
	lprintf(LOG_STATUS, "Tile preparation.\n");

	// Main sizes
	int imgW = dib_get_width(gr->_dib), imgH = dib_get_height(gr->_dib);
	int tileW = gr->tileWidth, tileH = gr->tileHeight;
	int metaW = gr->metaWidth, metaH = gr->metaHeight;

	// Tiling sizes for stages
	int frameW = tileW*metaW, frameH = tileH*metaH;		// For meta tiling

	bool bMeta = gr->isMetaTiled();
	bool bTile = tileW*tileH > 1;

	// Change things for column-major ordering
	if(gr->bColMajor)
	{
		int lastH = imgH, tmp;
		if(bMeta)	SWAP3(frameH, lastH, tmp);		
		if(bTile)	SWAP3(tileH, lastH, tmp);
	}

	// Meta redim
	if(bMeta)
	{
		lprintf(LOG_STATUS, "  tiling to %dx%d tiles.\n", frameW, frameH);
		if(!dib_redim(gr->_dib, frameW, frameH, 0))
		{
			lprintf(LOG_ERROR, "  meta-tiling failed.\n");
			return false;
		}
	}

	// Tile redim
	if(bTile)
	{
		lprintf(LOG_STATUS, "  tiling to %dx%d tiles.\n", tileW, tileH);

		if(!dib_redim(gr->_dib, tileW, tileH, 0))
		{
			lprintf(LOG_ERROR, "  tiling failed.\n");
			return false;
		}
	}

	lprintf(LOG_STATUS, "Tile preparation complete.\n");		
	return true;
}

//! Prepares map and meta map.
/*!	Does map creation and layout, tileset reduction and map 
	compression. Updates \a gr._dib with the new tileset, and fills 
	in \a gr._mapRec and \a gr._metaRec.
	\note The work bitmap must be 8 bpp here, and already rearranged 
	to a tile strip, which are the results of \c grit_prep_work_dib() 
	and \c grit_prep_tiles(), respectively.
*/
bool grit_prep_map(GritRec *gr)
{
	if(dib_get_bpp(gr->_dib) < 8)
	{
		lprintf(LOG_ERROR, "  Can't map for bpp<8.\n");
		return false;
	}

	CLDIB *workDib = gr->_dib;

	// --- if SBB-mode, tile to 256x256. ---
	if(gr->mapLayout == GRIT_MAP_REG)
	{
		lprintf(LOG_STATUS, "  tiling to Screenblock size (256x256p).\n");

		int blockW = 256, blockH = 256;
		if(gr->bColMajor)
		{
			blockW = dib_get_width(workDib);
			blockH = dib_get_height(workDib);
			dib_redim(workDib, 256, blockH, 0);
		}

		if(!dib_redim(workDib, blockW, blockH, 0))
		{
			lprintf(LOG_ERROR, "  SBB tiling failed.\n");
			return false;
		}		
	}

	ETmapFlags flags;
	Tilemap *metaMap = NULL, *map = NULL;
	RECORD metaRec = { 0, 0, NULL }, mapRec = { 0, 0, NULL };
	MapselFormat mf;

	CLDIB *extDib = NULL;
	int tileN = 0;
	uint extW = 0, extH = 0, tileW = gr->tileWidth, tileH = gr->tileHeight;
	uint mtileW = gr->mtileWidth(), mtileH = gr->mtileHeight();

	if(gr->gfxIsShared)
	{
		extDib = gr->shared->dib;
		extW = extDib ? dib_get_width(extDib) : 0;
		extH = extDib ? dib_get_height(extDib) : 0;
	}

	// --- If metatiled, convert to metatiles. ---
	if(gr->isMetaTiled())
	{
		lprintf(LOG_STATUS, "  Performing metatile reduction: tiles%s%s\n", 
			(gr->mapRedux & GRIT_META_PAL ? ", palette" : "") );

		flags  = TMAP_DEFAULT;
		if(gr->mapRedux & GRIT_META_PAL)
			flags |= TMAP_PBANK;
		if(gr->bColMajor)
			flags |= TMAP_COLMAJOR;
	
		metaMap = tmap_alloc();
		if(extW == mtileW)
		{
			lprintf(LOG_STATUS, "  Using external metatileset.\n");
			tmap_init_from_dib(metaMap, workDib, mtileW, mtileH, flags, extDib);
		}
		else
			tmap_init_from_dib(metaMap, workDib, mtileW, mtileH, flags, NULL);

		mf = c_mapselGbaText;
		tileN = tmap_get_tilecount(metaMap);
		if(tileN >= (1 << mf.idLen))
			lprintf(LOG_WARNING, "  Number of metatiles (%d) exceeds field limit (%d).\n", 
				tileN, 1 << mf.idLen);

		tmap_pack(metaMap, &metaRec, &mf);
		if( BYTE_ORDER == BIG_ENDIAN && mf.bitDepth > 8 )
			data_byte_rev(metaRec.data, metaRec.data, rec_size(&metaRec), mf.bitDepth/8);		

		// Make temp copy for base-tiling and try to avoid aliasing pointers.
		// Gawd, I hate manual mem-mgt >_<.
		dib_free(workDib);
		if(gr->bColMajor)
			workDib = dib_redim_copy(metaMap->tiles, tileN*mtileW, mtileH, 0);
		else
			workDib = dib_clone(metaMap->tiles);
	}

	// ---Convert to base tiles. ---
	flags = 0;
	if(gr->mapRedux & GRIT_RDX_TILE)
		flags |= TMAP_TILE;
	if(gr->mapRedux & GRIT_RDX_FLIP)
		flags |= TMAP_FLIP;
	if(gr->mapRedux & GRIT_RDX_PBANK)
		flags |= TMAP_PBANK;
	if(gr->bColMajor)
		flags |= TMAP_COLMAJOR;

	lprintf(LOG_STATUS, "  Performing tile reduction: %s%s%s\n", 
		(flags & TMAP_TILE  ? "unique tiles; " : ""), 
		(flags & TMAP_FLIP  ? "flip; " : ""), 
		(flags & TMAP_PBANK ? "palswap; " : "")); 

	map = tmap_alloc();
	if(extW == tileW)
	{
		lprintf(LOG_STATUS, "  Using external tileset.\n");
		tmap_init_from_dib(map, workDib, tileW, tileH, flags, extDib);
	}
	else
		tmap_init_from_dib(map, workDib, tileW, tileH, flags, NULL);

	// --- Pack/Reformat and compress ---
	//# TODO: allow custom mapsel format.
	mf = gr->msFormat;

	tileN = tmap_get_tilecount(metaMap);
	if(tileN >= (1 << mf.idLen))
		lprintf(LOG_WARNING, "  Number of tiles (%d) exceeds field limit (%d).\n", 
			tileN, 1 << mf.idLen);

	tmap_pack(map, &mapRec, &mf);

	if( BYTE_ORDER == BIG_ENDIAN && mf.bitDepth > 8 )
		data_byte_rev(mapRec.data, mapRec.data, rec_size(&mapRec), mf.bitDepth/8);		

	grit_compress(&mapRec, &mapRec, gr->mapCompression);

	// --- Cleanup ---

	// Make extra copy for external tile dib.
	if(gr->gfxIsShared)
	{
		dib_free(gr->shared->dib);

		// Use metatileset for external, unless the old external was a 
		// base tileset.
		if(gr->isMetaTiled() && extW != tileW)
			gr->shared->dib = dib_clone(metaMap->tiles);
		else
			gr->shared->dib = dib_clone(map->tiles);
	}

	// Attach tileset for later processing.
	gr->_dib = tmap_detach_tiles(map);

	rec_alias(&gr->_mapRec, &mapRec);
	rec_alias(&gr->_metaRec, &metaRec);

	tmap_free(map);
	tmap_free(metaMap);

	lprintf(LOG_STATUS, "Map preparation complete.\n");		
	return true;
}

//! Image data preparation.
/*!	Prepares the work dib for export, i.e. converts to the final 
	bitdepth, compresses the data and fills in \a gr._gfxRec.
*/
bool grit_prep_gfx(GritRec *gr)
{
	lprintf(LOG_STATUS, "Graphics preparation.\n");		

	int srcB = dib_get_bpp(gr->_dib);	// should be 8 or 16 by now
	int srcP = dib_get_pitch(gr->_dib);
	int srcS = dib_get_size_img(gr->_dib);
	BYTE *srcD = dib_get_img(gr->_dib);

	//make sure that the dib is power of 2 for texture operations
	if(gr->texModeEnabled)
	{
		int width = dib_get_width(gr->_dib);
		int height = dib_get_height(gr->_dib);
		int width_test = (width&(width-1));
		int height_test = (width&(width-1));
		if(width_test && height_test)
		{
			lprintf(LOG_ERROR, "  graphics for texture is not a power of 2.\n");
			return false;
		}

		if(width<8 || width>1024 || height<8 || height>1024)
		{
			lprintf(LOG_ERROR, "  one of texture dimensions violates 8 <= n <= 1024\n");
			return false;
		}
	}

	int dstB = gr->gfxBpp;

	int dstB_align = dstB;
	if(dstB == 3) dstB_align = 8;
	if(dstB == 5) dstB_align = 8;

	// # dst bytes, with # src pixels as 'width'
	int dstS = dib_align(srcS*8/srcB, dstB_align);
	dstS = ALIGN4(dstS);
	BYTE *dstD = (BYTE*)malloc(dstS);
	if(dstD == NULL)
	{
		lprintf(LOG_ERROR, "  Can't allocate graphics data.\n");
		return false;
	}

	// Convert to final bitdepth
	// NOTE: do not use dib_convert here, because of potential
	//   problems with padding
	// NOTE: we're already at 8 or 16 bpp here, with 16 bpp already 
	//   accounted for. Only have to do 8->1,2,4
	// TODO: offset
	if(srcB == 8 && srcB != dstB)
	{
		lprintf(LOG_STATUS, "  Bitpacking: %d -> %d.\n", srcB, dstB);
		data_bit_pack(dstD, srcD, srcS, srcB, dstB, 0);
	}
	else
		memcpy(dstD, srcD, dstS);

	//add alpha data for texture formats
	if((gr->gfxTexMode == GRIT_TEXFMT_A5I3 || gr->gfxTexMode == GRIT_TEXFMT_A3I5))
	{
		bool has_src_alpha = (dib_get_bpp(gr->_origDib) == 32);
		const int alpha_bits = (gr->gfxTexMode == GRIT_TEXFMT_A5I3)?5:3;
		const int shift_bits = 8-alpha_bits;
		BYTE* src_img = dib_get_img(gr->_origDib);
		BYTE* dst_img = dstD;
		int todo = srcS;
		while(todo--)
		{
			RGBQUAD pixel = *(RGBQUAD*)src_img;
			int alpha = 255;
			if(has_src_alpha)
				alpha = (pixel.rgbReserved) >> shift_bits;
			*dst_img |= alpha << shift_bits;
			src_img+=4;
			dst_img++;
		}
	}

	RECORD rec = { 1, dstS, dstD };

	if( BYTE_ORDER == BIG_ENDIAN && gr->gfxBpp > 8 )
		data_byte_rev(rec.data, rec.data, rec_size(&rec), gr->gfxBpp/8);		

	// attach and compress graphics
	grit_compress(&rec, &rec, gr->gfxCompression);
	rec_alias(&gr->_gfxRec, &rec);

	lprintf(LOG_STATUS, "Graphics preparation complete.\n");		
	return true;
}

//! Palette data preparation
/*!	Converts palette to 16bit GBA colors, compresses it and fills in 
	\a gr._palRec.	
*/
bool grit_prep_pal(GritRec *gr)
{
	lprintf(LOG_STATUS, "Palette preparation.\n");		

	int ii, nclrs, palS;
	COLOR *palOut;
	RGBQUAD *palIn;

	nclrs = gr->palEnd - gr->palStart;
	if(dib_get_nclrs(gr->_dib) < nclrs && nclrs != 0)
		nclrs = dib_get_nclrs(gr->_dib);

	palS = nclrs*sizeof(COLOR);
	palOut = (COLOR*)malloc(palS);
	palIn = &dib_get_pal(gr->_dib)[gr->palStart];

	for(ii = 0; ii<nclrs; ii++)
		palOut[ii]= RGB16(palIn[ii].rgbBlue, palIn[ii].rgbGreen, palIn[ii].rgbRed);

	RECORD rec = { 2, palS/2, (BYTE*)palOut };

	if( BYTE_ORDER == BIG_ENDIAN )
		data_byte_rev(rec.data, rec.data, rec_size(&rec), 2);		

	// Attach and compress palette
	grit_compress(&rec, &rec, gr->palCompression);
	rec_alias(&gr->_palRec, &rec);

	lprintf(LOG_STATUS, "Palette preparation complete.\n");		
	return true;
}

//! Shared Palette data preparation
/*!	Converts palette to 16bit GBA colors, compresses it and fills in
	\a gr._palRec.
*/
bool grit_prep_shared_pal(GritRec *gr)
{
	lprintf(LOG_STATUS, "Palette preparation.\n");

	int ii, nclrs, palS, totalClrs;
	COLOR *palOut;
	RGBQUAD *palIn;

	nclrs = gr->palEnd - gr->palStart;
	if(gr->shared->palRec.height < nclrs && nclrs != 0)
		nclrs = gr->shared->palRec.height;

	totalClrs = 256*sizeof(COLOR);

	palS = nclrs*sizeof(COLOR);
	palOut = (COLOR*)malloc(totalClrs);
	palIn = (RGBQUAD*)(&gr->shared->palRec.data[gr->palStart]);

	for(ii = 0; ii<nclrs; ii++)
		palOut[ii]= RGB16(palIn[ii].rgbBlue, palIn[ii].rgbGreen, palIn[ii].rgbRed);

    for(ii = nclrs; ii < 256; ii++)
        palOut[ii] = 0;

	RECORD rec = { 2, palS/2, (BYTE*)palOut };

	if( BYTE_ORDER == BIG_ENDIAN )
		data_byte_rev(rec.data, rec.data, rec_size(&rec), 2);

	// Attach and compress palette
	grit_compress(&rec, &rec, gr->palCompression);
	rec_alias(&gr->_palRec, &rec);

	lprintf(LOG_STATUS, "Palette preparation complete.\n");
	return true;
}

// EOF
