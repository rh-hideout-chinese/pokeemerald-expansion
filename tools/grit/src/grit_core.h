//
//! \file grit_core.h
//!   grit core header file
//! \date 20050814 - 20080129
//! \author cearn
//
/* === NOTES === 
  * 20080111, JV. Name changes, part 1
  * 20070413,jv
	IMPORTANT NOTICE: with the multi-file and shared stuff, 
	the whole GritRec thing is now thoroughly fucked up. It should
	be refactored into a single-run struct (like TGritEntry) and a 
	global manager struct (TGrit). I cannot say when this will happen, 
	only that it should and that many things will change because of it.
  * 20060727,jv: enum'ed GRIT and SE flags
  * 20060727,jv: added alpha stuff
*/

#ifndef __GRIT_CORE_H__
#define __GRIT_CORE_H__

#include "cldib_core.h"
#include "cldib_tmap.h"


/*! \addtogroup grpGrit
*	\{
*/


// === TYPES ==========================================================

typedef u16 COLOR;

// --------------------------------------------------------------------
// CONSTANTS
// --------------------------------------------------------------------


enum EGritItem
{
	GRIT_ITEM_GFX		= 0,		//!< Graphics stuff
	GRIT_ITEM_MAP		= 1,		//!< Tilemap stuff
	GRIT_ITEM_METAMAP	= 2,		//!< Metamap stuff
	GRIT_ITEM_PAL		= 3,		//!< Palette stuff
	GRIT_ITEM_MAX	
};

//! Process mode for data-chunks. Shared by all elements.
enum EGritDataProcMode
{
	GRIT_EXCLUDE	= 0,	//!< Ignore. `-{t}!'
	GRIT_PROCESS	= 1,	//!< Process data, but do not export.
	GRIT_OUTPUT		= 2,	//!< Output only.
	GRIT_EXPORT		= 3,	//!< Process and export `-{t}'
};

//! Datatype of output arrays.
enum EGritDataType
{
	GRIT_U8			= 0,	//!< Export as byte array. `-{t}u8'
	GRIT_U16		= 1,	//!< Export as halfword array. `-{t}u16'
	GRIT_U32		= 2,	//!< Export as word array. `-{t}u32'
};

//! Compression types.
enum EGritCompression
{
	GRIT_CPRS_OFF	= 0,	//!< No compression. `-{t}z!'
	GRIT_CPRS_LZ77	= 1,	//!< LZ77 compression (LZ77UnCompVram compatible). `-{t}zl'
	GRIT_CPRS_HUFF	= 2,	//!< 8bit Huffman compression (might be buggy). `-{t}zh'
	GRIT_CPRS_RLE	= 3,	//!< 8bit RLE compression. `-{t}zr'	
	GRIT_CPRS_HEADER = 4,	//!< Header word for symmetry `-{t}z0'
	GRIT_CPRS_MAX
//	GRIT_CPRS_DIFF	= 8,
};

//! Image mode flags
enum EGritGraphicsMode
{
	GRIT_GFX_TILE	= 0,	//!< 8x8 Tiled graphics `-gt'
	GRIT_GFX_BMP	= 1,	//!< Bitmap graphics `-gb'
	GRIT_GFX_BMP_A	= 2,	//!< Full alpha-bit ` -gb -gT!' 
};

enum EGritGraphicsTextureFormat
{
	GRIT_TEXFMT_NONE = 0,
	GRIT_TEXFMT_A5I3 = 1,
	GRIT_TEXFMT_A3I5 = 2,
	GRIT_TEXFMT_4x4 = 3,
};

//! Tilemap reduction modes.
/*!	These modes can be combined: 
	-mRtfp (or -mRfp, -mRftp, etc) means tiles, flip & pal reduction
*/
enum EGritMapRedux
{
	GRIT_RDX_OFF	= 0,	//!< No tile reduction (not advised) -mR!'
	GRIT_RDX_TILE	= 0x01,	//!< Reduce for all tiles `-mRt'
//	GRIT_RDX_BLANK	= 0x02,	//!< Reduce for blank tiles only `-mRb'
	GRIT_RDX_FLIP	= 0x04,	//!< Reduce for flipped tiles `-mRf'
	GRIT_RDX_PBANK	= 0x08,	//!< Reduce for palette-swapped tiles `-mRp'
	GRIT_RDX_AFF	= 0x01,	//!< Recommended rdx flags for affine bgs  `-mRa' ( = -mRt)
	GRIT_RDX_REG4	= 0x0D,	//!< Recommended rdx flags for 4bpp reg bgs `-mR4' ( = -mRtfp)
	GRIT_RDX_REG8	= 0x05,	//!< Recommended rdx flags for 8bpp reg bgs `-mR8' ( = -mRtf)

	GRIT_META_PAL	= 0x10,
};

//! Map layout formats.
enum EGritMapLayout
{
	GRIT_MAP_FLAT	= 0,	//!< Flat regular tilemap layout -mLf'
	GRIT_MAP_REG	= 1,	//!< Screenblocked regular tilemap layout -mLs'
	GRIT_MAP_AFFINE	= 2,	//!< Affine tilemap layout -mLa'
};

//! Output file types.
enum EGritFileType
{
	GRIT_FTYPE_C	= 0,	//<! Output in C arrays `-ftc'
	GRIT_FTYPE_S	= 1,	//<! Output in GAS source arrays `-fts'
	GRIT_FTYPE_BIN	= 2,	//<! Output in raw binary `-ftb'
	GRIT_FTYPE_GBFS	= 3,	//<! Output in GBFS archive `-ftg'
	GRIT_FTYPE_GRF	= 4,	//!< Output in RIFF format (chunked) `-ftr'
	GRIT_FTYPE_MAX
//	GRIT_FTYPE_O	= 5,
};

//! Shared grit flags.
enum EGrsMode
{
	GRS_SINGLE			= 0,	//!< Single file
	GRS_MULTI			= 1,	//!< Multiple files
	GRS_SHARED			= 2,	//!, Shared data.
	GRS_SINGLE_SHARED	= 2,	//!< Single file, shared data.
	GRS_MULTI_SHARED	= 3		//!< Multiple files, shared data.
};


// --- offset flags ---
#define OFS_BASE0   (1 << 31)

// --- GBA constants ---
// screen map flags
enum ScreenEntryFlags
{
	SE_HFLIP		=	0x0400,	//!< Horizontal flip flag
	SE_VFLIP		=	0x0800,	//!< Vertical flip flag

	SE_ID_MASK		=	0x03FF,
	SE_ID_SHIFT		=		 0,
	SE_FLIP_MASK	=	0x0C00,
	SE_FLIP_SHIFT	=		10,
	SE_PAL_MASK		=	0xF000,
	SE_PAL_SHIFT	=		12,
};

#define GBA_RED_MASK	0x001F
#define GBA_RED_SHIFT		 0
#define GBA_GREEN_MASK	0x03E0
#define GBA_GREEN_SHIFT		 5
#define GBA_BLUE_MASK	0x7C00
#define GBA_BLUE_SHIFT		10

#define NDS_ALPHA		0x8000


enum eTypes
{	E_U8 = 1, E_U16 = 2, E_U32 = 4	};

//! Indices for affix strings
enum eAffix
{	
	E_AFX_TILE	=0,		//!< Tiled graphics
	E_AFX_BMP	,		//!< Bitmap graphics
	E_AFX_MAP	,		//!< Tilemap
	E_AFX_PAL	,		//!< Palette
	E_AFX_MTILE	,		//!< Meta-tiles
	E_AFX_MMAP	,		//!< Metamap
	E_AFX_GRF	,		//!< GRIF format
	E_AFX_MAX
};

extern const char *c_fileTypes[GRIT_FTYPE_MAX];
extern const char *c_identTypes[3];
extern const char *c_identAffix[E_AFX_MAX];
extern const char *c_cprsNames[GRIT_CPRS_MAX];

extern const MapselFormat c_mapselGbaText;
extern const MapselFormat c_mapselGbaAffine;


// --------------------------------------------------------------------
// CLASSES
// --------------------------------------------------------------------


//! Struct for shared information
struct GritShared
{
	echar	 sharedMode;	//!< Main mode.
	echar	 logMode;		//!< Logging level
	char	*tilePath;		//!< Path to external tileset (can be NULL)
	char	*symName;		//!< Shared symbol name
	char	*dstPath;		//!< Path to shared datastore (can be NULL)
	u8		 gfxBpp;		//!< Bitdepth for shared graphics (unused for now)
	CLDIB	*dib;			//!< External tileset DIB (can be NULL)
	RECORD	 palRec;		//!< Shared palette (unused for now)
};

//! Basic grit struct
struct GritRec 
{
// --- Attributes ---

	//! Is this a tiled conversion?
	bool	isTiled() const
	{	return gfxMode == GRIT_GFX_TILE;					}

		//! Is this a bitmapped conversion?
	bool	isBitmap() const
	{	return gfxMode != GRIT_GFX_TILE;					}

	//! Should we tilemap?
	bool	isMapped() const	
	{	return isTiled() && mapProcMode != GRIT_EXCLUDE;	}

	//! Should we metatile?
	bool	isMetaTiled() const	
	{	return metaWidth*metaHeight > 1;					}

	uint	mtileWidth() const
	{	return metaWidth*tileWidth;							}

	uint	mtileHeight() const
	{	return metaHeight*tileHeight;						}


// --- Members ---

// public:

// Source stuff
	char	*srcPath;		//!< Path to source bitmap.
	CLDIB	*srcDib;		//!< Source bitmap.
// File/symbol info
	char	*dstPath;		//!< Output path directory (-o {name} ).
	char	*symName;		//!< Output symbol name (-s {name} ).
	u8		 fileType;		//!< Output file type (-ft{type} ).
	bool	 bHeader;		//!< Create header file (-fh[!] ).
	bool	 bAppend;		//!< Append to existing file (-fa).
	bool	 bExport;		//!< Global export toggle (?).
	bool	 bRiff;			//!< RIFFed data.

// Area ( [l,r>, [t,r> )
	int		 areaLeft;		//!< Export rect, left (-al {number} ).
	int		 areaTop;		//!< Export rect, top (-at {number} ).
	int		 areaRight;		//!< Export rect, right (-ar {number} ).
	int		 areaBottom;	//!< Export rect, bottom (-ab {number} ).

// Graphics:
	echar	 gfxProcMode;	//!< Graphics process mode.
	echar	 gfxDataType;	//!< Graphics data type (-gu{num} ).
	echar	 gfxCompression;	//!< Graphics compression type
	echar	 gfxMode;		//!< Graphics mode (tile, bmp, bmpA).
	bool	 texModeEnabled; //!< texture operations enabled
	u8		 gfxBpp;		//!< Output bitdepth (-gB{num} ).
	u8		 gfxTexMode; //!< Output texmode, if it is a special texture mode
	bool	 gfxHasAlpha;	//!< Input image has transparent color.
	RGBQUAD	 gfxAlphaColor;	//!< Transparent color (-gT {num} ). 
	u32		 gfxOffset;		//!< Pixel value offset (-ga {num}).
	bool	 gfxIsShared;	//!< Graphics are shared (-gS).
		
// Map:
	echar	 mapProcMode;	//!< Map process mode (-m).
	echar	 mapDataType;	//!< Map data type (-mu {num} ).
	echar	 mapCompression;	//!< Map compression type (-mz{char} ).
	echar	 mapRedux;		//!< Map tile-reduction mode (-mR[tpf,48a] ).
	echar	 mapLayout;		//!< Map layout mode (-mL{char} ).
	//u32		 mapOffset;		//!< Map-entry tile-value offset (-ma {num}).
	MapselFormat	msFormat;	//!< Format describing packed mapsels (GBA Text entries).

// (Meta-)tiles/map:
	u8		 tileWidth;		//!< Tile width (in pixels) (-tw{num} ).
	u8		 tileHeight;	//!< Tile height (in pixels) (-th{num} ).
	u8		 metaWidth;		//!< Meta-tile/object width (in tiles) (-Mw{num} ).
	u8		 metaHeight;	//!< Meta-tile/object height (in tiles) (-Mh{num} ).
	bool	 bColMajor;		//!< Tiles are arranged in column-major order (-tc).

// Palette ( [s,e> )
	echar	 palProcMode;	//!< Palette process mode (-p).
	echar	 palDataType;	//!< Palette data type.
	echar	 palCompression;	//!< Palette compression type.
	bool	 palHasAlpha;	//!< Has special transparency index.
	u32		 palAlphaId;	//!< Transparent palette entry
	int		 palStart;		//!< First palette entry to export.
	int		 palEnd;		//!< Final palette entry to export (exclusive)
	bool	 palEndSet;		//!< Whether the user set the palette end
	bool	 palIsShared;	//!< Shared palette (-pS),

// Shared information
	GritShared	*shared;

// Private: keep the f#^$k off
	CLDIB	*_dib;		//!< Internal work bitmap
	CLDIB *_origDib; //!< unmodified bitmap, for preserving alpha channel
	RECORD	 _gfxRec;	//!< Output graphics data
	RECORD	 _mapRec;	//!< Output tilemap data
	RECORD	 _metaRec;	//!< Output metatile data
	RECORD	 _palRec;	//!< Output palette data
};


// --------------------------------------------------------------------
// GLOBALS
// --------------------------------------------------------------------


extern const char *grit_app_string;


// --------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------

// === GritRec ===

//bool grit_parse(GritRec *gr, int argc, char **argv);	// parse cmdline

GritRec *grit_alloc();					// alloc gr
void grit_free(GritRec *gr);			// de-alloc gr

void grit_init(GritRec *gr);			// set members to default values
bool grit_init_from_dib(GritRec *gr);	// extra inits from src_dib parameters
void grit_clear(GritRec *gr);			// clears internal allocations

void grit_copy_options(GritRec *dst, const GritRec *src);
void grit_copy_strings(GritRec *dst, const GritRec *src);

bool grit_run(GritRec *gr);

bool grit_validate(GritRec *gr);	// validate input
bool grit_prep(GritRec *gr);		// prepare data (conv, cprs, etc)
bool grit_export(GritRec *gr);		// export data

bool grit_compress(RECORD *dst, const RECORD *src, u32 flags);


// void grit_dump(GritRec *gr, FILE *fp);

// === GritShared ===

GritShared *grs_alloc();
void grs_free(GritShared *grs);
void grs_clear(GritShared *grs);
void grs_run(GritShared *grs, GritRec *gr_base);


// === Attribute functions ===

INLINE int grit_type_size(u8 type);


// --------------------------------------------------------------------
// MACROS
// --------------------------------------------------------------------


//! Create a GBA BGR color
#define GBA_RGB16(r, g, b)	( (r) | ((g) << 5) | ((b) << 10) )

/*!	\}	*/

// --------------------------------------------------------------------
// INLINES
// --------------------------------------------------------------------

INLINE int grit_type_size(u8 type)
{	return 1 << type;									}


#endif // __GRIT_CORE_H__




// EOF
