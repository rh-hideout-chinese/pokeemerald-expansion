//
//! \file cldib_tmap.h
//!  Tilemap functionality
//! \date 20070414 - 20100131
//! \author cearn
/* === NOTES ===
  * 20070414,jv: Tilemap stuff seems to be working. Need more testing for 32bpp though.
  * 20100113, JV: yay, finally some actual work done in here.
*/


#ifndef __CLDIB_TMAP_H__
#define __CLDIB_TMAP_H__

#include "cldib_core.h"


/*! \addtogroup grpTmap
/*!	\{	*/


// --------------------------------------------------------------------
// CONSTANTS
// --------------------------------------------------------------------


//! \name Map Entry flags
//\{
#define ME_HFLIP			( 1 << 26)	//!< Horizontal flip flag
#define ME_VFLIP			( 2 << 26)	//!< Vertical flip flag

#define ME_FLIP_SHIFT				26
#define ME_FLIP_MASK		0x0C000000
#define ME_PBANK_SHIFT				28
#define ME_PBANK_MASK		0xF0000000
//\}

//! \name TileMap flags
//\{
enum TmapFlags
{
	TMAP_TILE		= ( 1<< 0),		//!< Allows unique tile mapping.
	TMAP_FLIP		= ( 1<< 1),		//!< Allows flipped tiles.
	TMAP_PBANK		= ( 1<< 2),		//!< Allows pal swapping (8bpp only)
	TMAP_COLMAJOR	= ( 1<< 7),		//!< Traverse the image by colums during the mapping procedure.
	TMAP_DEFAULT	= TMAP_TILE		//!< Simple mapping: uniques without flipping or palswap.
};
typedef u32 ETmapFlags;
//\}


// --------------------------------------------------------------------
// CLASSES
// --------------------------------------------------------------------


//! Internal map entry struct (32 bit)
/*!
	\note	Yes, I would like to use bitfields here, but I have no idea 
			how endianness affects things.
*/
struct Mapsel
{
	int index() const	{	return bfGet(value_,  0, 16);	}	//!< Get tile index.
	void index(int x)	{	bfSet(value_, x,  0, 16);		}	//!< Set tile index.
	int hflip() const	{	return bfGet(value_, 26,  1);	}	//!< Get horz flip.
	void hflip(int x)	{	bfSet(value_, x, 26, 1);		}	//!< Set horz flip.
	int vflip() const	{	return bfGet(value_, 27,  1);	}	//!< Get vert flip.
	void vflip(int x)	{	bfSet(value_, x, 27, 1);		}	//!< Set vert flip.
	int pbank() const	{	return bfGet(value_, 28,  4);	}	//!< Get palette bank index.
	void pbank(int x)	{	bfSet(value_, x, 28,  4);		}	//!< Set palette bank index.

	u32 value_;			//!< Mapsel value. Format: [0-15]:index [26]:hflip [27]:vflip [28-31]:pbank
};

//! Generic tilemap struct
struct Tilemap
{
	int width;			//!< Map width.
	int height;			//!< Map height.
	Mapsel	*data;		//!< Map data.
	int tileWidth;		//!< Width of single tile.
	int tileHeight;		//!< Height of single tile.
	CLDIB *tiles;		//!< Tileset (graphics).
	u32 flags;			//!< Tilemap flags.
};

//! Bitformat for external mapsels.
/*! Used for converting to and from the internal mapsel format.
*/
struct MapselFormat
{
	u32	base;				//!< Additive base mapsel.
	u8	bitDepth;			//!< Full mapsel length in bits.
	u8	idShift, idLen;		//!< Index bitfield parameters.
	u8	hfShift, hfLen;		//!< Horizontal flip field parameters.
	u8	vfShift, vfLen;		//!< Vertical flip field parameters.
	u8	pbShift, pbLen;		//!< Palette bank field parameters.
};


/*!	\}	*/


// --------------------------------------------------------------------
// MACROS
// --------------------------------------------------------------------


// --------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------


Tilemap *tmap_alloc();
void tmap_free(Tilemap *tm);

void tmap_set_map(Tilemap *tm, int mapWidth, int mapHeight, Mapsel *mapData, 
	ETmapFlags flags);
void tmap_set_tiles(Tilemap *tm, int tileWidth, int tileHeight, CLDIB *tiles);
void tmap_clear_map(Tilemap *tm);
void tmap_clear_tiles(Tilemap *tm);
CLDIB *tmap_detach_tiles(Tilemap *tm);

void tmap_init(Tilemap *tm, int mapWidth, int mapHeight, int tileW, int tileH, 
	ETmapFlags flags);
bool tmap_init_from_dib(Tilemap *tm, CLDIB *dib, int tileWidth, int tileHeight, 
	ETmapFlags flags, CLDIB *extTiles);

CLDIB *tmap_render(Tilemap *tm, const RECT *rect);

void tmap_pack(const Tilemap *tm, RECORD *dstRec, const MapselFormat *mf);
void tmap_unpack(Tilemap *tm, const RECORD *srcRec, const MapselFormat *mf);

uint tmap_get_tilecount(const Tilemap *tm);

// --------------------------------------------------------------------
// INLINES
// --------------------------------------------------------------------


#endif // __CLDIB_TMAP_H__

// EOF
