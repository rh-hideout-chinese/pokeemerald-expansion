//
//! \file grit_core.cpp
//!   Core grit routines
//! \date 20050814 - 20100201
//! \author cearn
//
/* === NOTES === 
  * 20100201, jv: Removed validation parts that disallow mapping non-8bpp images.
  * 20080111, jv. Name changes, part 1
  * 20070227, jv: logging functions.
  * 20061010, jv: '-fa' now uses src for the sym-name if none is given.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#include <sys/param.h>

#include "cldib.h"
#include "grit.h"

#include "grit_version.h"

// --------------------------------------------------------------------
// CONSTANTS
// --------------------------------------------------------------------

static const char __grit_app_string[]=
"\tExported by Cearn's GBA Image Transmogrifier, v" PACKAGE_VERSION "\n"
"\t( http://www.coranac.com/projects/#grit )";

const char *c_fileTypes[GRIT_FTYPE_MAX]= {"c", "s", "bin", "gbfs", "grf" /*, "o"*/};
const char *c_cprsNames[GRIT_CPRS_MAX]= { "not", "lz77", "huf", "rle", "fake" };
const char *c_identTypes[3]= { "u8", "u16", "u32" };
const char *c_identAffix[E_AFX_MAX]= 
{
	"Tiles", "Bitmap", 
	"Map", "Pal", 
	"MetaTiles", "MetaMap",
	"Grf"
};

const MapselFormat c_mapselGbaText = 
{
	0x00000000, 16,
	0 , 10,		// index
	10,  1,		// hflip
	11,  1,		// vflip
	12,  4,		// pbank
};

const MapselFormat c_mapselGbaAffine = 
{
	0x00000000, 8,
	0 ,  8,		// index
	10,  0,		// hflip
	11,  0,		// vflip
	12,  0,		// pbank
};

// --------------------------------------------------------------------
// GLOBALS
// --------------------------------------------------------------------


//! Application string pointer.
/*!
	\c grit_preface() allows room for a string specific to the 
	application. Alias this pointer to that string for your own 
	messages. Multi-lined strings are safe; a comment will be placed 
	on every new line.
*/
const char *grit_app_string = __grit_app_string;

// --------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------


bool grit_validate_paths(GritRec *gr);
bool grit_validate_area(GritRec *gr);


// --------------------------------------------------------------------
// FUNCTIONS
// --------------------------------------------------------------------

//! GritRec 'Constructor'.
GritRec *grit_alloc()
{
	GritRec *gr = (GritRec*)malloc(sizeof(GritRec));
	if(gr == NULL)
		return NULL;

	GritShared *grs = grs_alloc();
	if(grs == NULL)
	{	free(gr);	return NULL;	}

	memset(gr, 0, sizeof(GritRec));

	gr->shared = grs;

	return gr;
}

//! GritRec 'Destructor'.
void grit_free(GritRec *gr)
{
	if(gr == NULL)
		return;

	grs_free(gr->shared);
	grit_clear(gr);
	free(gr);
}


//! Initializes \a gr to default values.
void grit_init(GritRec *gr)
{
	if(gr == NULL)
		return;
	
	// File/symbol options.
	gr->fileType = GRIT_FTYPE_S;
	gr->bHeader = true;
	gr->bAppend = false;
	gr->bExport = true;
	gr->bRiff = false;

	// Area options (tl inclusive, rb exclusive).
	gr->areaLeft = 0;
	gr->areaTop = 0;
	gr->areaRight = 0;	// modified later.
	gr->areaBottom = 0;	// modified later.

	// Graphics options.
	gr->gfxProcMode = GRIT_EXPORT;
	gr->gfxDataType = GRIT_U32;
	gr->gfxCompression = GRIT_CPRS_OFF;
	gr->gfxMode = GRIT_GFX_TILE;
	gr->gfxHasAlpha = false;
	gr->gfxAlphaColor = clr2rgb(RGB(255, 0, 255));
	gr->gfxBpp = 8;
	gr->gfxOffset = 0;
	gr->gfxIsShared = false;

	// Map options.
	gr->mapProcMode = GRIT_EXCLUDE;
	gr->mapDataType = GRIT_U16;
	gr->mapCompression = GRIT_CPRS_OFF;
	gr->mapRedux = GRIT_RDX_REG8;
	gr->mapLayout = GRIT_MAP_FLAT;
	gr->msFormat = c_mapselGbaText;

	// Extra tile options
	gr->tileWidth = 0;
	gr->tileHeight = 0;
	gr->metaWidth = 1;
	gr->metaHeight = 1;
	gr->bColMajor = false;

	// Palette options
	gr->palProcMode = GRIT_EXPORT;
	gr->palDataType = GRIT_U16;
	gr->palCompression = GRIT_CPRS_OFF;
	gr->palHasAlpha = false;
	gr->palAlphaId = 0;
	gr->palStart = 0;
	gr->palEnd = 256;

	// NOTE: do NOT init shared here!
}


//! Frees allocations and zeroes everything (except shared).
void grit_clear(GritRec *gr)
{
	if(gr == NULL)
		return;

	free(gr->srcPath);
	dib_free(gr->srcDib);

	free(gr->dstPath);
	free(gr->symName);

	// internals
	dib_free(gr->_dib);
	free(gr->_palRec.data);
	free(gr->_gfxRec.data);
	free(gr->_mapRec.data);
	free(gr->_metaRec.data);

	GritShared *grs = gr->shared;
	memset(gr, 0, sizeof(GritRec));
	gr->shared = grs;
}

//! Copy the main options (no strings) from \a src to \a dst.
void grit_copy_options(GritRec *dst, const GritRec *src)
{
	if(src ==NULL || dst ==NULL)
		return;

	// File/symbol options.	
	dst->fileType = src->fileType;
	dst->bHeader = src->bHeader;
	dst->bAppend = src->bAppend;
	dst->bExport = src->bExport;
	dst->bRiff = src->bRiff;

	// Area options (tl inclusive, rb exclusive).	
	dst->areaLeft = src->areaLeft;
	dst->areaTop = src->areaTop;
	dst->areaRight = src->areaRight;
	dst->areaBottom = src->areaBottom;

	// Graphics options.	
	dst->gfxProcMode = src->gfxProcMode;
	dst->gfxDataType = src->gfxDataType;
	dst->gfxCompression = src->gfxCompression;
	dst->gfxMode = src->gfxMode;
	dst->gfxHasAlpha = src->gfxHasAlpha;
	dst->gfxAlphaColor = src->gfxAlphaColor;
	dst->gfxBpp = src->gfxBpp;
	dst->gfxOffset = src->gfxOffset;
	dst->gfxIsShared = src->gfxIsShared;

	// Map options.	
	dst->mapProcMode = src->mapProcMode;
	dst->mapDataType = src->mapDataType;
	dst->mapCompression = src->mapCompression;
	dst->mapRedux = src->mapRedux;
	dst->mapLayout = src->mapLayout;
	dst->msFormat = src->msFormat;

	// Extra tile options	
	dst->tileWidth = src->tileWidth;
	dst->tileHeight = src->tileHeight;
	dst->metaWidth = src->metaWidth;
	dst->metaHeight = src->metaHeight;
	dst->bColMajor = src->bColMajor;

	// Palette options	
	dst->palProcMode = src->palProcMode;
	dst->palDataType = src->palDataType;
	dst->palCompression = src->palCompression;
	dst->palHasAlpha = src->palHasAlpha;
	dst->palAlphaId = src->palAlphaId;
	dst->palStart = src->palStart;
	dst->palEnd = src->palEnd;	
}

//! Copy the string variables from \a src to \a dst.
void grit_copy_strings(GritRec *dst, const GritRec *src)
{
	if(src ==NULL || dst ==NULL)
		return;

	strrepl(&dst->srcPath, src->srcPath);
	strrepl(&dst->dstPath, src->dstPath);
	strrepl(&dst->symName, src->symName);
}


// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------


//! Initialize palette and gfx-related functions from the DIB.
bool grit_init_from_dib(GritRec *gr)
{
	if(gr == NULL)
		return false;

	CLDIB *dib = gr->srcDib;
	if(dib == NULL)
	{
		lprintf(LOG_ERROR, "No bitmap to initialize GritRec from.\n");
		return false;
	}

 	int nclrs = dib_get_nclrs(dib);
	gr->palEnd = ( nclrs ? nclrs : 256 );

	if(dib_get_bpp(dib) > 8)
		gr->gfxBpp = 16;
	else
		gr->gfxBpp = dib_get_bpp(dib);

	gr->areaRight = dib_get_width(dib);
	gr->areaBottom = dib_get_height(dib);

	return true;
}

//! Main grit hub.
/*! After filling in a grit-rec, pass it to this function and you're 
	pretty much done.
	\param gr A filled (but not necessarily validated) grit-rec.
	\return \c true for success, \c false for failure
	\todo Create a set of individual error messages for the various 
	  stages.
*/
bool grit_run(GritRec *gr)
{
	time_t aclock;
	struct tm *newtime;
	char str[96];

	time( &aclock );
	newtime = localtime( &aclock );
	strftime(str, 96, "Started run at: %Y-%m-%d, %H:%M:%S\n", newtime);

	lprintf(LOG_STATUS, str);

	if(grit_validate(gr) == false)
		return false;
		
	if(grit_prep(gr) == false)
		return false;

	if(gr->bExport)
		if(grit_export(gr) == false)
			return false;

	lprintf(LOG_STATUS, "Run completed :).\n");
	return true;
}


void grit_dump(GritRec *gr, FILE *fp)
{
	fprintf(fp, "%12s %s\n", "src path", 
		isempty(gr->srcPath) ? "--" : gr->srcPath);
	fprintf(fp, "%12s %s\n", "dst path",  
		isempty(gr->dstPath)  ? "--" : gr->dstPath); 
	fprintf(fp, "%12s %s\n", "sym name", 
		isempty(gr->symName) ? "--" : gr->symName);
	fprintf(fp, "%12s: type:%d, hdr:%d, append:%d\n", "file opt", 
		gr->fileType, gr->bHeader, gr->bAppend);

	fputs("--- pal ---\n", fp);
	fprintf(fp, "%12s: pm:%d, dt:%d, cprs:%d\n", "pal opts", 
		gr->palProcMode, gr->palDataType, gr->palCompression);

	fprintf(fp, "%12s [%d, %d)\n", "pal range", gr->palStart, gr->palEnd);

	fputs("--- image ---\n", fp);
	fprintf(fp, "%12s: pm:%d, dt:%d, cprs:%d\n", "gfx opts", 
		gr->gfxProcMode, gr->gfxDataType, gr->gfxCompression);

	fprintf(fp, "%12s %d\n", "gfx bpp", gr->gfxBpp);
	fprintf(fp, "%12s %d\n", "gfx ofs", gr->gfxOffset);
	fprintf(fp, "%12s (%d,%d)-(%d,%d)\n", "gfx range", 
		gr->areaLeft, gr->areaTop, gr->areaRight, gr->areaBottom);

	fputs("--- map ---\n", fp);
	fprintf(fp, "%12s: pm:%d, dt:%d, cprs:%d\n", "map opts", 
		gr->mapProcMode, gr->mapDataType, gr->mapCompression);

	fprintf(fp, "%12s %d\n", "map ofs", gr->msFormat.base);
	fprintf(fp, "%12s [%d, %d]\n", "meta size", 
		gr->metaWidth, gr->metaHeight);
}

// {src} >{>} {dst-dir}/{dst-title}.{dst-ext} {+ .h}
// { {sym}Pal : {cprs}, u{n}, [{ps}-{pe}>}
// { {sym}{Tiles/Bitmap} : {cprs}, u{n}, {n} bpp, +{ofs} }
// { {sym}Map : {cprs}, u{n}, -{tfp}, {layout}, +{ofs}
// Area : ({al},{at})-({ar},{ab}){ Meta : {w},{h} }
void grit_dump_short(GritRec *gr, FILE *fp, const char *pre)
{
	if(pre ==NULL)
		pre = "";

	fputs(pre, fp);
	fprintf(fp, "%s >%s %s.%s\n",
		gr->srcPath, (gr->bAppend ? ">":""), 
		gr->dstPath, (gr->bHeader ? "+.h":"") );

	if(gr->palProcMode != GRIT_EXCLUDE)
	{
		fputs(pre, fp);
		fprintf(fp, "%s%s : %s cprs, %s, [%d,%d>\n", 
			gr->symName, c_identAffix[E_AFX_PAL],
			c_cprsNames[gr->palCompression], c_identTypes[gr->palDataType], 
			gr->palStart, gr->palEnd);
	}

	if(gr->gfxProcMode != GRIT_EXCLUDE)
	{
		fputs(pre, fp);
		fprintf(fp, "%s%s : %s cprs, %s, %dbpp, +%d\n", 
			gr->symName, c_identAffix[gr->isTiled() ? E_AFX_TILE : E_AFX_BMP],
			c_cprsNames[gr->gfxCompression], c_identTypes[gr->gfxDataType], 
			gr->gfxBpp, gr->gfxOffset);
	}

	if(gr->mapProcMode != GRIT_EXCLUDE)
	{
		fputs(pre, fp);
		fprintf(fp, "%s%s : %s cprs, %s, ", 
			gr->symName, 
			c_identAffix[gr->isMetaTiled() ? E_AFX_MTILE :  E_AFX_MAP],
			c_cprsNames[gr->mapCompression], c_identTypes[gr->mapDataType]);
		if(gr->mapRedux)
		{
			fputs("-t", fp);
			if(gr->mapRedux & GRIT_RDX_FLIP)
				fputs("f", fp);
			if(gr->mapRedux & GRIT_RDX_PBANK)
				fputs("p", fp);
			fputs(", ", fp);
		}
		const char *layouts[]={ "reg flat", "reg sbb", "affine" };
		fprintf(fp, "%s, +%d\n",
			layouts[gr->mapLayout], gr->msFormat.base);
	}
	fputs(pre, fp);
	fprintf(fp, "Area : (%d,%d)-(%d,%d)    ", 
		gr->areaLeft, gr->areaTop, gr->areaRight, gr->areaBottom);
	fprintf(fp, "Meta: %d,%d\n", gr->metaWidth, gr->metaHeight);
}

// --- Validation -----------------------------------------------------


bool grit_validate_paths(GritRec *gr)
{
	char str[MAXPATHLEN];

	// Only validate destination if there's going to be export.
	if(gr->bExport)
	{
		// Must have either src or dst paths
		if( isempty(gr->srcPath) && isempty(gr->dstPath) )
		{
			lprintf(LOG_ERROR, "  No input or output paths. Validation failed.\n");
			return false;
		}

		if(gr->srcPath == NULL)
		{
			strrepl(&gr->srcPath, "");
			lprintf(LOG_WARNING, "  No explicit src path.\n");
		}
		else
			path_fix_sep(gr->srcPath);

		// No dst path? Get from source
		if(isempty(gr->dstPath))
		{
			strrepl(&gr->dstPath, path_get_name(gr->srcPath));
			lprintf(LOG_WARNING, "  No explicit dst path. Borrowing from src path.\n");
		}

		// Fix extension
		path_repl_ext(str, gr->dstPath, c_fileTypes[gr->fileType], MAXPATHLEN);
		strrepl(&gr->dstPath, str);
		path_fix_sep(gr->dstPath);

		// If no symbol name:
		// - append mode : from src
		// - create mode : from dst 
		if(isempty(gr->symName))
		{
			if(gr->bAppend)			
			{
				path_get_title(str, gr->srcPath, MAXPATHLEN);
				strrepl(&gr->symName, str);
		
				lprintf(LOG_WARNING, "  No explicit symbol name. In append mode, so using src title.\n");
			}
			else
			{
				path_get_title(str, gr->dstPath, MAXPATHLEN);
				strrepl(&gr->symName, str);

				lprintf(LOG_WARNING, "  No explicit symbol name. In overwrite mode, so using dst title.\n");
			}
		}
		str_fix_ident(gr->symName, gr->symName, MAXPATHLEN);
	}

	return true;	
}

bool grit_validate_area(GritRec *gr)
{
	int tmp;

	//# FIXME: consider other proc-modes?
	// area size
	if(gr->gfxProcMode != GRIT_EXCLUDE || gr->mapProcMode != GRIT_EXCLUDE)
	{
		int al, at, ar, ab;		// area
		int aw, ah;				// area size
		int blockW, blockH;		// block size

		al = gr->areaLeft;	at = gr->areaTop;
		ar = gr->areaRight;	ab = gr->areaBottom;

		// Normalize
		if(al > ar)
		{
			lprintf(LOG_WARNING, "  Area: left (%d) > right (%d). Swapping.\n", 
				gr->areaLeft, gr->areaRight);

			SWAP3(al, ar, tmp);
		}

		if(at > ab)
		{
			lprintf(LOG_WARNING, "  Area: top (%d) > bottom (%d). Swapping.\n", 
				gr->areaTop, gr->areaBottom);

			SWAP3(at, ab, tmp);
		}

		if(ar == 0)	ar = dib_get_width(gr->srcDib);
		if(ab == 0)	ab = dib_get_height(gr->srcDib);

		aw = ar-al;
		ah = ab-at;
		
		// metatile size (in px)
		// area MUST fit at least one metatile
		// Tiles: either 
		// - one meta tile
		// - one screenblock if in SBB layout
		// PONDER: non-integral metatile/sbb ??

		if(gr->metaWidth  < 1)	gr->metaWidth = 1;
		if(gr->metaHeight < 1)	gr->metaHeight = 1;

		if(gr->gfxMode == GRIT_GFX_TILE)
		{
			if(gr->tileWidth  < 4)	gr->tileWidth = 8;
			if(gr->tileHeight < 4)	gr->tileHeight = 8;
		}
		else
		{
			if(gr->tileWidth  < 1)	gr->tileWidth = 1;
			if(gr->tileHeight < 1)	gr->tileHeight = 1;
		}

		// Normally, the blocks are tw*mw, th*mh in size.
		// But for SBB-aligned maps it's a little different.
		if(!(gr->mapProcMode ==GRIT_EXPORT && gr->mapLayout ==GRIT_MAP_REG))
		{
			blockW = gr->mtileWidth();
			blockH = gr->mtileHeight();
		}
		else
			blockW = blockH = 256;

		if(aw%blockW != 0)
		{
			lprintf(LOG_WARNING, "Non-integer tiling in width (%d vs %d)\n", 
				aw, blockW);
			aw = align(aw, blockW);
		}

		if(ah%blockH != 0)
		{
			lprintf(LOG_WARNING, "Non-integer tiling in height (%d vs %d)\n", 
				ah, blockH);
			ah = align(ah, blockH);
		}

		// area must be multiple of metas (rounding up here)
		//aw = (aw+blw-1)/blw * blw;
		//ah = (ah+blh-1)/blh * blh;

		// PONDER: but what about the image size?
		//  *shrug* what about it?
		ar = al+aw;
		ab = at+ah;	

		gr->areaLeft = al;	gr->areaTop = at;
		gr->areaRight = ar;	gr->areaBottom = ab;
	}

	return true;	
}


//! Validate parameters.
/*!	Makes sure all the settings in \a gr are valid. For example, 
	tilemap and bitmap mode are mutually exclusive; bpp must be 
	1, 2, 4, 8, etc. Some things are fatal
	(those two are), but some can be accounted for like reversed 
	pal start and end indices and non-aligned areas.
*/
bool grit_validate(GritRec *gr)
{
	int tmp;

	lprintf(LOG_STATUS, "Validating gr.\n");

	// source dib MUST be loaded already!
	if(gr->srcDib == NULL)
	{
		lprintf(LOG_ERROR, "  No input bitmap. Validation failed.\n");
		return false;
	}

	if(!grit_validate_paths(gr))
		return false;

	// --- Options ---

	//analyze supplied texture modes. these are invalid unless -gx is provided
	bool demand_tex_mode = true;
	switch(gr->gfxTexMode)
	{
	case GRIT_TEXFMT_A5I3:
		if(dib_get_bpp(gr->srcDib) != 32)
			lprintf(LOG_WARNING," tex format A5I3 specified but source graphics contains no alpha\n");
		gr->gfxBpp = 3;
		break;
	case GRIT_TEXFMT_A3I5:
		if(dib_get_bpp(gr->srcDib) != 32)
			lprintf(LOG_WARNING," tex format A3I5 specified but source graphics contains no alpha\n");
		gr->gfxBpp = 5;
		break;
	case GRIT_TEXFMT_4x4:
		lprintf(LOG_ERROR, " 4x4 is not supported yet. how did you know to try it?\n");
		return false;
	default:
		demand_tex_mode = false;
		break;
	}

	//make sure that -gx was provided
	if(demand_tex_mode)
	{
		if(!gr->texModeEnabled)
		{
		lprintf(LOG_ERROR, " Specified a texture-only format but did not supply -gx\n");
		return false;
		}
	}

	//truecolor must be bitmaps.
	int bpp = gr->gfxBpp;
	switch(bpp)
	{
	case 0:
		gr->gfxBpp = 8;
	case 1: case 2: case 4: case 8:
		break;
	case 16: case 24: case 32:
		gr->gfxBpp = 16;

		gr->mapProcMode = GRIT_EXCLUDE;	// No map. REPONDER
		gr->palProcMode = GRIT_EXCLUDE;	// No pal either.
		break;
	case 3: case 5:
		gr->mapProcMode = GRIT_EXCLUDE;	// No map. REPONDER
		if(!gr->palEndSet)
		{
			gr->palEndSet = true;
			lprintf(LOG_STATUS,"Guessing palette size for A3I5/A5I3 texture\n");
			if(bpp ==3)
				gr->palEnd = gr->palStart+8;
			else
				gr->palEnd = gr->palStart+32;
		}
		break;

	default:
		lprintf(LOG_ERROR, "  Bad bpp (%d).\n", bpp);
		return false;
	}

	// Raw binary cannot be appended
	if(gr->fileType ==GRIT_FTYPE_BIN && gr->bAppend)
	{
		gr->bAppend = false;
		lprintf(LOG_WARNING, "  Can't append to binary files. Switching to override mode.");
	}

	// --- ranges ---

	// palette
	if(gr->palProcMode != GRIT_EXCLUDE)
	{
		if(gr->palStart > gr->palEnd)
		{
			lprintf(LOG_WARNING, "  Palette: start (%d) > end (%d): swapping.\n", 
				gr->palStart, gr->palEnd);

			SWAP3(gr->palStart, gr->palEnd, tmp);
		}

		if(gr->palStart<0)
		{
			lprintf(LOG_WARNING, "  Palette: start (%d) < 0. Clamping to 0.\n", 
				gr->palStart);
			gr->palStart = 0;
		}

		int nclrs = dib_get_nclrs(gr->srcDib);
		if(nclrs != 0 && gr->palEnd > gr->palStart+nclrs)
		{
			lprintf(LOG_WARNING, "  Palette: end (%d) > #colors (%d). Clamping to %d.\n", 
				gr->palStart+nclrs);
			gr->palEnd = gr->palStart+nclrs;
		}
	}

	if(!grit_validate_area(gr))
		return false;

	// PONDER: issue dump for status-log?

	lprintf(LOG_STATUS, "Validation succeeded.\n");
	return true;
}


// --------------------------------------------------------------------

// --------------------------------------------------------------------





// EOF
