//
//! \file cldib_tmap.cpp
//!  Tilemap functionality
//! \date 20070414 - 20100131
//! \author cearn
/* === NOTES ===
  * 20100115, JV: yay, finally some actual work done in here.
*/

#include <algorithm>

#include "cldib_core.h"
#include "cldib_tools.h"
#include "cldib_tmap.h"

// --------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------

/*!	\addtogroup	grpTmap	*/
/*!	\{	*/

int dib_get_pbank(CLDIB *dib);
bool dib_set_pbank(CLDIB *dib, int pbank);
bool dib_tilecmp(CLDIB *dib, CLDIB *tileset, int tid, u32 mask);
Mapsel dib_find(CLDIB *dib, CLDIB *tileset, u32 tileN, u32 flags);

/*!	\}	*/


// --------------------------------------------------------------------
// FUNCTIONS
// --------------------------------------------------------------------

uint tmap_get_tilecount(const Tilemap *tm)
{
	if(tm ==NULL || tm->tiles ==NULL || tm->tileHeight ==0)
		return 0;

	return dib_get_height(tm->tiles) / tm->tileHeight;	
}

// === Book-keeping ===================================================

//! Allocates room for a tilemap.
Tilemap *tmap_alloc()
{
	Tilemap *tm = (Tilemap*)malloc(sizeof(Tilemap));
	memset(tm, 0, sizeof(Tilemap));
	return tm;	
}

//! Frees all the memory of a tilemap.
void tmap_free(Tilemap *tm)
{
	if(tm ==NULL)
		return;

	free(tm->data);
	dib_free(tm->tiles);

	free(tm);
}

//! Set the map data of a tilemap. 
/*! Erases the old data and links @a tm to @mapData.
	@param tm	Active tilemap.
	@param mapWidth		New map's width.
	@param mapHeight	New map's height.
	@param mapData		New map's data.
	@param flags		map rendering and conversion flags.
*/
void tmap_set_map(Tilemap *tm, int mapWidth, int mapHeight, Mapsel *mapData, ETmapFlags flags)
{
	if(tm ==NULL)
		return;

	tm->width = mapWidth;
	tm->height = mapHeight;
	free(tm->data);
	tm->data = mapData;
	tm->flags = flags;
}

//! Sets the tilemaps tileset.
/*!	Reassigns the tilemap's tile information.
	@param tm	Active tilemap.
	@param tileWidth	Width of single tile.
	@param tileHeight	Height of single tile.
	@param tiles		New tileset.
*/
void tmap_set_tiles(Tilemap *tm, int tileWidth, int tileHeight, CLDIB *tiles)
{
	if(tm ==NULL)
		return;

	tm->tileWidth = tileWidth;
	tm->tileHeight = tileHeight;
	dib_free(tm->tiles);
	tm->tiles = tiles;
}

//! Free the map data.
void tmap_clear_map(Tilemap *tm)
{
	if(tm ==NULL)
		return;

	free(tm->data);
	tm->width = 0;
	tm->height = 0;
	tm->data = NULL;
}

//! Clear tileset data.
void tmap_clear_tiles(Tilemap *tm)
{
	if(tm ==NULL)
		return;

	dib_free(tm->tiles);
	tm->tileWidth = 0;
	tm->tileHeight = 0;
	tm->tiles = NULL;
}

CLDIB *tmap_detach_tiles(Tilemap *tm)
{
	if(tm ==NULL)
		return NULL;

	CLDIB *dib = tm->tiles;
	tm->tileWidth = 0;
	tm->tileHeight = 0;
	tm->tiles = NULL;

	return dib;
}

//! Allocate and initialize a tilemap.
/*!
	@param tm		Tilemap to init. Previous data will be removed.
	@param mapW		Map width.
	@param mapH		Map height.
	@param tileW	Tile width.
	@param tileH	Tile height.
	@param flags	Tilemap flags (TMAP_*).
*/
void tmap_init(Tilemap *tm, int mapW, int mapH, int tileW, int tileH, ETmapFlags flags)
{
	if(tm ==NULL)
		return;

	free(tm->data);
	dib_free(tm->tiles);

	tm->width = mapW;
	tm->height = mapH;
	tm->data = (Mapsel*)malloc(mapW*mapH*sizeof(Mapsel));

	tm->tileWidth = tileW;
	tm->tileHeight = tileH;
	tm->tiles = NULL;
	tm->flags = flags;
}

// === Operations =====================================================


//! Create a tilemap with reduced tileset from a DIB.
/*!	@param tmap	Tilemap to init.
*	@param dib	DIB to initialize from. Must be 8 or 32bpp.
*	@param tileW	Tile width.
*	@param tileH	Tile height.
*	@param flags	Tilemap flags (reduction options and such).
*	@param extTiles	External tileset to use as a base for internal tileset.
*	@return	Success status.
*	@note	On bitdepth: Both bitmaps must be of the same bitdepth, 
*	  which must be either multiples of 8 bpp.
*	@note	If \a dib's sizes aren't multiples of the tiles, the incomplete
*	  rows will be truncated.
*	@note	\a extTiles is considered a column of tiles, not a matrix. 
*	  only the first column will be considered.
*/
bool tmap_init_from_dib(Tilemap *tm, CLDIB *dib, int tileW, int tileH, 
	ETmapFlags flags, CLDIB *extTiles)
{
	// Safety checks
	if(tm ==NULL || dib ==NULL || tileW<1 || tileH<1)
		return false;

	// Set up new tilemap and tileset
	int dibW, dibH, dibB, dibP;
	dib_get_attr(dib, &dibW, &dibH, &dibB, &dibP);

	int mapW = dibW/tileW, mapH = dibH/tileH, mapN = mapW*mapH;

	if(mapW ==0 || mapH ==0)
		return false;

	// Init new tileset
	u32 rdxN;
	CLDIB *rdx;

	if(extTiles != NULL && dibB == dib_get_bpp(extTiles))
	{
		rdxN = dib_get_height(extTiles)/tileH;
		rdx = dib_copy(extTiles, 0, 0, tileW, (mapN+rdxN)*tileH, false);
	}
	else
	{
		rdxN = 1;					
		rdx = dib_alloc(tileW, (mapN+rdxN)*tileH, dibB, NULL);
		memset(dib_get_img(rdx), 0, dib_get_pitch(rdx)*tileH);
		dib_pal_cpy(rdx, dib);
	}

	if(rdx == NULL)
		return false;

	Mapsel *mapD = (Mapsel*)malloc(mapW*mapH*sizeof(Mapsel)), me;

	// Create temporary tile for comparisons
	CLDIB *tmpDib = dib_copy(dib, 0, 0, tileW, tileH, false);
	int tmpP = dib_get_pitch(tmpDib);	
	u8 *tmpD = dib_get_img(tmpDib);
	
	int iy, tx, ty;

	if(flags & TMAP_COLMAJOR)
	{
		for(tx = 0; tx<mapW; tx++)
		{
			for(ty = 0; ty<mapH; ty++)
			{
				// Prep comparison DIB
				for(iy = 0; iy<tileH; iy++)
					memcpy(&tmpD[iy*tmpP], 
						dib_get_img_at(dib, tx*tileW, ty*tileH+iy), tmpP);

				me = dib_find(tmpDib, rdx, rdxN, flags);

				// Not found? Add to tileset
				if(me.index() >= rdxN)
				{
					memcpy(dib_get_img_at(rdx, 0, tileH*rdxN), tmpD,
						dib_get_size_img(tmpDib));
					rdxN++;
				}

				mapD[tx*mapH+ty]= me;
			}
		}
		std::swap(mapW, mapH);
	}
	else
	{
	for(ty = 0; ty<mapH; ty++)
	{
		for(tx = 0; tx<mapW; tx++)
		{
			// Prep comparison DIB
			for(iy = 0; iy<tileH; iy++)
				memcpy(&tmpD[iy*tmpP], 
					dib_get_img_at(dib, tx*tileW, ty*tileH+iy), tmpP);
			
			me = dib_find(tmpDib, rdx, rdxN, flags);

			// Not found? Add to tileset
				if(me.index() >= rdxN)
			{
				memcpy(dib_get_img_at(rdx, 0, tileH*rdxN), tmpD,
					dib_get_size_img(tmpDib));
				rdxN++;
			}

			mapD[ty*mapW+tx]= me;
		}
	}
	}

	// Shrink tileset
	dib_free(tmpDib);
	tmpDib = dib_copy(rdx, 0, 0, tileW, rdxN*tileH, false);
	dib_free(rdx);

	// Attach map and tileset to tmap
	free(tm->data);
	dib_free(tm->tiles);

	tm->width = mapW;
	tm->height = mapH;
	tm->data = mapD;
	tm->tileWidth = tileW;
	tm->tileHeight = tileH;
	tm->tiles = tmpDib;
	tm->flags = flags;

	return true;
}

//! Render a tilemap to a DIB (8, 16, 24, 32).
/*!	Converts a tile map and its tileset to a full bitmap in the 
*	bitdepth of the tileset. Can also render a porttion of the map.
*	@param tmap	Tilemap to render.
*	@param rect	Portion of map to render. If NULL, it renders the whole thing.
*	@note	Assumes the tileset is a column.
*	@note	Bitdepth must me either 8 or 32 bpp.
*/
CLDIB *tmap_render(Tilemap *tm, const RECT *rect)
{
	// Safety checks
	if(tm ==NULL || tm->data == NULL || tm->tiles == NULL)
		return NULL;

	//# PONDER: rename 'tile' ?
	CLDIB *tileDib = tm->tiles;
	int tileW, tileH, tileB, tileP, tileS;
	dib_get_attr(tileDib, &tileW, NULL, &tileB, &tileP);

	//# PONDER is this really necessary?
	if(tileB < 8)
		return NULL;
	if(tileW < tm->tileWidth)
		return NULL;

	tileW = tm->tileWidth, tileH = tm->tileHeight;
	tileS = tileP*tileH;

	int mapW = tm->width, mapH = tm->height, mapP = mapW;
	Mapsel *mapD = tm->data, me;

	int tx, ty, iy;

	// Portion render: change map W, H, D accordingly
	if(rect)
	{	
		tx = MAX(0, rect->left);
		ty = MAX(0, rect->top);
		mapD += ty*mapP + tx;
		mapW = MIN(mapW, rect->right)-tx;
		mapH = MIN(mapH, rect->bottom)-ty;						
	}

	// --- Create new dib ---
	int dibW = tileW*mapW, dibH = tileH*mapH, dibP;
	CLDIB *dib = dib_alloc(dibW, dibH, tileB, NULL);
	dib_pal_cpy(dib, tileDib);
	dibP = dib_get_pitch(dib);

	// Temp tile dib
	CLDIB *tmpDib = dib_copy(tileDib, 0, 0, tileW, tileH, false);
	u8 *tmpD = dib_get_img(tmpDib);

	//# TODO: COLMAJOR rendering

	for(ty = 0; ty<mapH; ty++)
	{
		for(tx = 0; tx<mapW; tx++)
		{
			me = mapD[ty*mapP+tx];
			
			// --- Flip and mask on temp dib ---
			memcpy(tmpD, dib_get_img_at(tileDib, 0, tileH*me.index()), tileS);

			if(me.hflip())
				dib_hflip(tmpDib);
			if(me.vflip())
				dib_vflip(tmpDib);

			if(tileB == 8 && (tm->flags & TMAP_PBANK))
				dib_set_pbank(tmpDib, me.pbank());

			// Render temp dib
			u8 *dibD = dib_get_img_at(dib, tx*tileW, ty*tileH);
			for(iy = 0; iy<tileH; iy++)
				memcpy(&dibD[iy*dibP], &tmpD[iy*tileP], tileW*tileB/8);
		}
	}

	dib_free(tmpDib);
	return dib;
}

//! Convert from internal format to the one specified by @a mf.
/*!	
	@param tm		Active tilemap.
	@param dstRec	Record to receive reformatted map.
	@param mf		Mapsel format descriptor.
*/
void tmap_pack(const Tilemap *tm, RECORD *dstRec, const MapselFormat *mf)
{
	if(tm ==NULL || dstRec ==NULL || mf ==NULL)
		return;

	int ix, iy;
	int mapW = tm->width, mapH = tm->height;

	RECORD rec = { mf->bitDepth/8, mapW*mapH, NULL };
	rec.data = (BYTE*)malloc(rec_size(&rec));

	const Mapsel *srcL = tm->data;

	//# TODO: safety checks?

	if (mf->bitDepth == 8 ) {
		u8 *dstL = (u8*)rec.data;
		// --- Convert map format ---
		for(iy = 0; iy<mapH; iy++)
		{
			for(ix = 0; ix<mapW; ix++)
			{
				*dstL++ = srcL->index() & 0xff;
				*srcL++;
			}
		}
		
	} else {
		
		u16 *dstL = (u16*)rec.data;
		// --- Convert map format ---
		for(iy = 0; iy<mapH; iy++)
		{
			for(ix = 0; ix<mapW; ix++)
			{
				u32 res = 0;
				if(mf->idLen)
					bfSet(res, srcL->index(), mf->idShift, mf->idLen);
				if(mf->hfLen)
					bfSet(res, srcL->hflip(), mf->hfShift, mf->hfLen);
				if(mf->vfLen)
					bfSet(res, srcL->vflip(), mf->vfShift, mf->vfLen);
				if(mf->pbLen)
					bfSet(res, srcL->pbank(), mf->pbShift, mf->pbLen);

				*dstL++ = res + mf->base;
				*srcL++;
			}
		}
	}

	rec_alias(dstRec, &rec);
}

//! Convert from the mapsel format specified by @a mf to the internal format.
/*!	
	@param tm		Active tilemap.
	@param srcRec	Record containing source map to unformat.
	@param mf		Mapsel format descriptor.
*/
void tmap_unpack(Tilemap *tm, const RECORD *srcRec, const MapselFormat *mf)
{
	if(tm ==NULL || srcRec ==NULL || srcRec->data ==NULL || mf ==NULL)
		return;

	int ix, iy;
	int mapW = tm->width, mapH = tm->height, mapS = mapW*mapH*4;

	u32 *srcD, *srcL;
	Mapsel *dstD = (Mapsel*)malloc(mapS), *dstL;

	// --- Raw mapsel unpack ---
	if(mf->bitDepth < 32)
	{
		uint size = mapS*mf->bitDepth/32;
		srcD = (u32*)malloc(mapS);
		data_bit_unpack(srcD, srcRec->data, size, mf->bitDepth, 32, 0);
	}
	else
		srcD = (u32*)srcRec->data;

	//# TODO: endianness

	// --- Conversion ---
	srcL = srcD;
	dstL = dstD;

	for(iy = 0; iy<mapH; iy++)
	{
		for(ix = 0; ix<mapW; ix++)
		{
			u32 raw = *srcL++ - mf->base;
			Mapsel me = { 0 };

			if(mf->idLen)
				me.index(bfGet(raw, mf->idShift, mf->idLen));
			if(mf->hfLen)
				me.hflip(bfGet(raw, mf->hfShift, mf->hfLen));
			if(mf->vfLen)
				me.vflip(bfGet(raw, mf->vfShift, mf->vfLen));
			if(mf->pbLen)
				me.pbank(bfGet(raw, mf->pbShift, mf->pbLen));

			*dstL++= me;
		}
	}

	// --- Cleanup ---

	free(tm->data);
	tm->data = dstD;
	if(mf->bitDepth < 32)
		free(srcD);
}


// --------------------------------------------------------------------
// Utilities
// --------------------------------------------------------------------

//! Find the palette-bank for a DIB.
/*!	@note	For 8bpp only.
*/
int dib_get_pbank(CLDIB *dib)
{
	int dibW, dibH, dibB, dibP;
	dib_get_attr(dib, &dibW, &dibH, &dibB, &dibP);
	if(dibB != 8)
		return 0;

	int ix, iy, clrid;
	u8 *dibD = dib_get_img(dib);

	for(iy = 0; iy<dibH; iy++)
	{
		for(ix = 0; ix<dibW; ix++)
		{
			clrid = dibD[iy*dibP+ix];
			if(clrid&0x0F)
				return (clrid >> 4)&0x0F;
		}
	}
	return 0;
}


//! Find the palette-bank for a DIB.
/*!	@note	For 8bpp only.
*/
bool dib_set_pbank(CLDIB *dib, int pbank)
{
	int dibW, dibH, dibB, dibP;
	dib_get_attr(dib, &dibW, &dibH, &dibB, &dibP);
	if(dibB != 8)
		return false;

	int ix, iy;
	u8 *dibD = dib_get_img(dib);

	pbank <<= 4;

	for(iy = 0; iy<dibH; iy++)
		for(ix = 0; ix<dibW; ix++)
			dibD[iy*dibP+ix]= (dibD[iy*dibP+ix]&15) | pbank;

	return true;
}


//! Compare \a dib to tile \a tid from \a tileset (8+)
/*!	@note	\a dib indicates tile attributes. If these don't match 
*	  with \a tileset, there will be trouble. YHBW.
*	@note	PONDER: Endian effects???
*/
bool dib_tilecmp(CLDIB *dib, CLDIB *tileset, int tid, u32 dwMask)
{
	int tileW, tileH, tileB, tileP;
	dib_get_attr(dib, &tileW, &tileH, &tileB, &tileP);

	int ix, iy, ib, nb;		// x, y, byte indices; #bytes/pixel

	nb = tileB/8;

	u32 dibP = dib_get_pitch(dib);
	u8 *dibD = dib_get_img(dib), *dibL;
	u8 *tileD = dib_get_img_at(tileset, 0, tid*tileH), *tileL;

		for(iy = 0; iy<tileH; iy++)
		{
		dibL = &dibD[iy*dibP];
		tileL = &tileD[iy*tileP];
		for(ix = 0; ix<tileW; ix++)
		{
			u32 mask = dwMask;
			for(ib = 0; ib<nb; ib++)
			{
				if((*dibL++ ^ *tileL++) & mask)
					return false;
		mask >>= 8;
	}
		}
	}
	
	return true;	
}


//! Find tile \a dib inside a tileset.
/*!	@param dib		Dib to compare.
	@param tileset	Tileset to find \a dib in.
	@param tileN	Number of used tiles in \a tileset.
	@param mask		Color mask for pixels.
	@return	Map entry with found information. If not found, the index 
	  will be equal to \a tileN.
	@note	\a dib represents a single tile. As such, it gives the 
	  size and bitdepth of the tiles. If you want flipped tiled, 
	  flip \a dib outside.
*/
Mapsel dib_find(CLDIB *dib, CLDIB *tileset, u32 tileN, u32 flags)
{
	int i;
	int dibB = dib_get_bpp(dib);
	u32 mask;
	Mapsel me = { tileN };

	if( dibB == 8 && (flags & TMAP_PBANK) )
	{
		mask = 0x0F;
		me.pbank(dib_get_pbank(dib));
	}
	else
		mask = 0xFFFFFFFF;
	
	// Early escape for non-reducing mapping.
	if(~flags & TMAP_TILE)
	{
		me.index(tileN);
		return me;
	}
	

	// --- Straight ---
	for(i = 0; i<tileN; i++)
	{
		if(dib_tilecmp(dib, tileset, i, mask))
		{
			me.index(i);
			return me;
		}
	}

	// --- Flips, if requested ---
	//# TODO: could be compressed a little.
	//# PONDER: taking care of flipping inside dib_tilecmp 
	//#		could be faster, but I'm not sure.

	if(~flags & TMAP_FLIP)
		return me;

	dib = dib_clone(dib);	// Create temp copy for flipping

	do
	{
		// --- H-flip ---
		dib_hflip(dib);
		for(i = 0; i<tileN; i++)
			if(dib_tilecmp(dib, tileset, i, mask))
				break;
		if(i<tileN)
		{	me.value_ |= ME_HFLIP;	break;				}

		// --- HV-flip ---
		dib_vflip(dib);
		
		for(i = 0; i<tileN; i++)
			if(dib_tilecmp(dib, tileset, i, mask))
				break;
		if(i<tileN)
		{	me.value_ |= ME_HFLIP | ME_VFLIP;	break;	}

		// --- V-flip ---
		dib_hflip(dib);
		me.value_ &= ~ME_HFLIP;
		for(i = 0; i<tileN; i++)
			if(dib_tilecmp(dib, tileset, i, mask))
				break;
		if(i<tileN)
		{	me.value_ |= ME_VFLIP;	break;				}

	} while(0);
	
	dib_free(dib);
	me.index(i);

	return me;
}


// EOF
