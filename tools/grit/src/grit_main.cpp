//
//! \file grit_main.cpp
//!   Entry file for cmd-line grit.
//! \date 20050913 - 20100204
//! \author cearn
//
/* === NOTES ===
  * 20100201, jv:
    - Removed bpp and size restriction of external tileset.
	- Added -mp and -mB options.
  * 20080223,jv: 
    - put version and completion indicators under LOG_STATUS.
	- error codes for main() ... but they still need work.
  * 20080211,jv:
	Added:
	-gS : shared graphics (without the use of an external file like -fx)
	-pS : shared palette
	-O : shared output file
	-S : shared symbol base
	-Z0 (and related) No compression, but with cprs-like header.
	-ftr : grf file : RIFFed binary data.
  * 20070331, jv: 
	- Fixed directory options for -fx.
	- Added '-ft!', '-We', '-Ww', '-Ws' options
	- changes default output to asm.
  * 20060729,jv: added vector-based grit_get_args; I may mod 
	other functions to use strvec for subroutines later too.
  * 20060729.jv: PONDER: now that I am using STL, would this be a 
	good time to go for strings iso char*s as well?
*/

// PONDER, are these really necessary?
#ifndef _MSC_VER
#include <sys/param.h>
#include <unistd.h>
#include <strings.h>
#endif	// _MSC_VER

#include "grit_version.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>

#include "cldib.h"
#include "grit.h"
#include <FreeImage.h>

#include "cli.h"
#include "fi.h"

void grit_dump(GritRec *gr, FILE *fp);
void grit_dump_short(GritRec *gr, FILE *fp, const char *pre);

// typedef std::vector<char*> strvec;


// --------------------------------------------------------------------
// CONSTANTS
// --------------------------------------------------------------------

#ifndef PACKAGE_VERSION
#error PACKAGE_VERSION must be defined such as "0.8.4"
#endif

// --- Application constants ---
#define APP_VERSION	PACKAGE_VERSION

const char appIdent[]= "grit v" PACKAGE_VERSION;

const char appHelpText[]= 
"GRIT: GBA Raster Image Transmogrifier. (grit v" APP_VERSION ")\n"
"  Converts bitmap files into something the GBA can use.\n"
"usage: grit srcfile(s) [args]\n\n"
"\n--- Graphics options (base: \"-g\") ---\n"
"-g | -g!       Include  or exclude gfx data [inc]\n"
"-gu(8|16|32)   Gfx data type: u8, u16, u32 [u32]\n"
"-gz[!lhr0]     Gfx compression: off, lz77, huff, RLE, off+header [off]\n"
//"-ga{n}         Gfx pixel offset (non-zero pixels) [0]\n"
//"-gA{n}         Gfx pixel offset n (all pixels) [0]\n"
"-gb | -gt      Gfx format, bitmap or tile [tile]\n"
"-gB{fmt}       Gfx format / bit depth (1, 2, 4, 8, 16, a5i3, a3i5) [img bpp]\n"
"-gx            Enable texture operations\n"
"-gS            Shared graphics\n"
"-gT{n}         Transparent color; rrggbb hex or 16bit BGR hex [FF00FF]\n"
"                 -gT! forces alpha bit, only affects NDS\n"
"-al{n}         Area left [0]\n"
"-ar{n}         Area right (exclusive) [img width]\n"
"-aw{n}         Area width [img width]. Overrides -ar\n"
"-at{n}         Area top [0]\n"
"-ab{n}         Area bottom (exclusive) [img height]\n"
"-ah{n}         Area height [img height]. Overrides -ab\n"
"\n--- Map options (base: \"-m\") ---\n"
"-m | -m!       Include or exclude map data [exc]\n"
"-mu(8|16|32)   Map data type: u8, u16, u32 [u16]\n"
"-mz[!lhr0]     Map compression: off, lz77, huff, RLE, off+header [off]\n"
"-ma{n}         Map-entry offset n (non-zero entries) [0]\n"
"-mp{n}         NEW: Force mapsel palette to n\n"
"-mB{n}:{(iphv[n])+}     NEW: Custom mapsel bitformat\n"
//"-mA{n}         Map tile offset n (all entries) [0]\n"
"-mR{t,p,f}     Tile reduction: (t)iles, (p)al, (f)lipped \n"
"                 options can be combined [-mRtpf]\n"
"-mR[48a]       Common tile reduction combos: reg 4bpp (-mRtpf), \n"
"                 reg 8bpp (-mRtf), affine (-mRt), respectively\n"
"-mR!           No tile reduction (not advised)\n"
"-mL[fsa]       Map layout: reg flat, reg sbb, affine [reg flat]\n"
"\n--- Palette options (base: \"-p\") ---\n"
"-p | -p!       Include or exclude pal data [inc]\n"
"-pu(8|16|32)   Pal data-type: u8, u16 , u32 [u16]\n"
"-pz[!lhr0]     Pal compression: off, lz77, huff, RLE, off+header [off]\n"
"-ps{n}         Pal range start [0]\n"
"-pe{n}         Pal range end (exclusive) [pal size]\n"
"-pn{n}         Pal count [pal size]. Overrides -pe\n"
"-pS            shared palette\n"
"-pT{n}         Transparent palette index; swaps with index 0 [0]\n"
"--- Meta/Obj options (base: \"-M\") ---\n"
//"-M | -M!       Include or exclude (def) metamap data\n"
"-Mh{n}         Metatile height (in tiles!) [1]\n"
"-Mw{n}         Metatile width (in tiles!) [1]\n"
"-MRp           Metatile reduction (pal only) [none]\n"
"\n--- File / var options ---\n"
"-ft[!csbgr]    File type (no output, C, GNU asm, bin, gbfs, grf) [.s]\n"
"-fr            Enable GRF-format for .c or .s\n"
"-fa            File append\n"
"-fh | -fh!     Create header or not [create header]\n"
"-ff{name}      Additional options read from flag file [dst-name.grit]\n"
"-fx{name}      External tileset file\n"
"-o{name}       Destination filename [based on source]\n"
"-s{name}       Symbol base name [based from dst]\n"
"-O{name}       Destination file for shared data\n"
"-S{name}       Symbol base name for shared data\n"
"\n--- Misc ---\n"
"-tc            Tiling in column-major order.\n"
"-tw            NEW(?): base tile width [8].\n"
"-th            NEW(?): base tile height [8].\n"
//"-q             Quiet mode; no report at the end\n"
"-U(8|16|32)    All data type: u8, u16, u32\n"
"-W{n}          Warning/log level 1, 2 or 3 [1]\n"
"-Z[!lhr0]      All compression: off, lz77, huff, RLE, off+header [off]\n"
"\nNew options: -fr, -ftr, -gS, -O, -pS, -S, -Z0 (et al)\n";

// --------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------

bool grit_parse(GritRec *gr, const strvec &args);

int grit_parse_cprs(const char *key, const strvec &args);
bool grit_parse_mapsel_format(const char *key, MapselFormat *pmf);

bool grit_parse_pal(GritRec *gr, const strvec &args);
bool grit_parse_gfx(GritRec *gr, const strvec &args);
bool grit_parse_map(GritRec *gr, const strvec &args);
bool grit_parse_file(GritRec *gr, const strvec &args);
int grit_parse_log(GritRec *gr, const strvec &args);

bool grit_load_ext_tiles(GritRec *gr);
bool grit_save_ext_tiles(GritRec *gr);

void args_gather(strvec &args, int argc, char **argv);
bool args_validate(const strvec &args, const strvec &fpaths);


bool run_prep(GritRec *gr, const char *fpath);
int run_individual(GritRec *gr, const strvec &args, const strvec &fpaths);
int run_shared(GritRec *gr, const strvec &args, const strvec &fpaths);
int run_main(int argc, char **argv);


// --------------------------------------------------------------------
// FUNCTIONS
// --------------------------------------------------------------------


//! Searches for compression options
/*!
	\param key	Base compression options (-Z, -gz, etc)
	\return	GRIT_CPRS_foo flag, or -1 if no sub-flag found.
*/
int grit_parse_cprs(const char *key, const strvec &args)
{
	// compression
	const char *str = CLI_STR(key, "");
	switch(*str)
	{
	case 'h':	return GRIT_CPRS_HUFF;
	case 'l':	return GRIT_CPRS_LZ77;
	case 'r':	return GRIT_CPRS_RLE;
	case '!':	return GRIT_CPRS_OFF;
	case '0':	return GRIT_CPRS_HEADER;
	default:
		return -1;		
	}
}

//! Parse mapsel-format string into the format proper.
/*!
	@param key	formatting string: "((\d):)?([iphv_]\d*)+"
				- $1 : size of mapsel, in bits
				- $2 : field descriptors. Character + size.
				  * i : tile-index.
				  * p : palette bank.
				  * h : horizontal flip.
				  * v : vertical flip.
				  * _ : filler.
				Format is big-endian, but right-aligned.
	@param pmf	Pointer to struct to be filled in.
	@return		Success-status of parsing.
*/
bool grit_parse_mapsel_format(const char *key, MapselFormat *pmf)
{
	if(isempty(key) || pmf == NULL)
		return false;

	MapselFormat mf;
	memset(&mf, 0, sizeof(MapselFormat));

	int c, val, nBits;
	char *str = (char*)key;

	nBits = strtoul(str, &str, 0);
	if(*str == ':')
		str++;

	// --- Walk over all %c(%d) pairs. ---
	int pos = 0;
	while(*str)
	{
		c = *str++;
		val = strtoul(str, &str, 0);
		if(val<1) 
			val = 1;

		switch(c)
		{
		case 'i':		// index
			mf.idShift = pos;	mf.idLen = val;		break;
		case 'p':		// pbank
			mf.pbShift = pos;	mf.pbLen = val;		break;
		case 'h':		// hflip
			mf.hfShift = pos;	mf.hfLen = val;		break;
		case 'v':		// vflip
			mf.vfShift = pos;	mf.vfLen = val;		break;
		case '_':
													break;
		default:
			lprintf(LOG_WARNING, "Unknown mapsel option %c.\n", c);
			val = 0;
		}
		pos += val;
	}

	// --- Reverse-order fields ---
	mf.idShift = pos - mf.idLen - mf.idShift;
	mf.pbShift = pos - mf.pbLen - mf.pbShift;
	mf.hfShift = pos - mf.hfLen - mf.hfShift;
	mf.vfShift = pos - mf.vfLen - mf.vfShift;

	// --- Fix mapsel size ---
	if(nBits < pos || nBits > sizeof(long))
		nBits = pos;
	if(nBits < 8)
		mf.bitDepth = ceilpo2(nBits);
	else
		mf.bitDepth = (nBits+7)/8*8;

	*pmf = mf;

	return true;
}


//! Searches for palette options.
bool grit_parse_pal(GritRec *gr, const strvec &args)
{
	int val;
	if( CLI_BOOL("-p!") == false)
	{
		gr->palProcMode = GRIT_EXPORT;

		gr->palDataType = CLI_INT("-pu", 16) >> 4;
		if( (val = grit_parse_cprs("-pz", args)) != -1 )
			gr->palCompression = val;

		// Range
		gr->palStart = CLI_INT("-ps", 0);

		if( (val = CLI_INT("-pn", -1)) >= 0)
		{
			gr->palEnd = gr->palStart + val;
			gr->palEndSet = true;
		}
		else if( (val = CLI_INT("-pe", -1)) >= 0)
			gr->palEnd = val;
	}
	else
		gr->palProcMode = GRIT_EXCLUDE;

	// Transparent pal-id
	if( (val = CLI_INT("-pT", -1)) >= 0)
	{
		gr->palHasAlpha = true;
		gr->palAlphaId = val;
	}

	// Shared palette
	if(CLI_BOOL("-pS"))
		gr->palIsShared = true;

	return true;
}

//! Searches for graphics options
bool grit_parse_gfx(GritRec *gr, const strvec &args)
{
	int val;
	const char *pstr;

	if(CLI_BOOL("-g!") == false)
	{
		gr->gfxProcMode = GRIT_EXPORT;

		gr->gfxDataType = CLI_INT("-gu", 32) >> 4;
		if( (val = grit_parse_cprs("-gz", args)) != -1 )
			gr->gfxCompression = val;

		// pixel offset
		gr->gfxOffset = CLI_INT("-ga", 0);
	}
	else
		//# PONDER: can img really be excluded from processing?
		gr->gfxProcMode = GRIT_EXCLUDE;

	//# PONDER: this should probably be replaced by other kinds of formats.
	//# -gf(t|b|ba|tx\d) ?

	// Tile or bitmap format
	if(CLI_BOOL("-gb"))
		gr->gfxMode = GRIT_GFX_BMP;
	else
	{
		if(!CLI_BOOL("-gt"))
			lprintf(LOG_WARNING, "No main mode specified (-gt/-gb).\n");
		gr->gfxMode = GRIT_GFX_TILE;
	}
	
	if(CLI_BOOL("-gx"))
		gr->texModeEnabled = true;

	// Bitdepth override
	char* bppOverride = CLI_STR("-gB",0);
	if(bppOverride)
	{
		if(!strcasecmp(bppOverride,"a3i5"))
			gr->gfxTexMode = GRIT_TEXFMT_A3I5;
		else if(!strcasecmp(bppOverride,"a5i3"))
			gr->gfxTexMode = GRIT_TEXFMT_A5I3;
		else if(!strcasecmp(bppOverride,"4x4"))
			gr->gfxTexMode = GRIT_TEXFMT_4x4;
		else if( (val = CLI_INT("-gB", 0)) != 0)
			gr->gfxBpp = val;
	}

	// Transparency
	if( CLI_BOOL("-gT") )
	{
		// String can be (0x?)[0-9A-Fa-f]{4,6}
		// <5 hexits means 16bit BGR color
		// >4 means rrggbb color
		pstr = CLI_STR("-gT", "FF00FF");
		if(pstr[0] != '!')
		{
			gr->gfxAlphaColor = str2rgb(pstr);
			gr->gfxHasAlpha = true;
		}
		else
			gr->gfxMode = GRIT_GFX_BMP_A;
	}

	// Shared graphics (internal only)
	if(CLI_BOOL("-gS"))
		gr->gfxIsShared = true;

	return true;
}

//! Searches for tilemap options
bool grit_parse_map(GritRec *gr, const strvec &args)
{
	int val;
	const char *pstr;

	// no map args or excluded	
	if(!CLI_BOOL("-m") || CLI_BOOL("-m!"))
	{
		gr->mapProcMode = GRIT_EXCLUDE;
		return true;
	}

	gr->mapProcMode = GRIT_EXPORT;

	gr->mapDataType = CLI_INT("-mu", 16) >> 4;
	if( (val = grit_parse_cprs("-mz", args)) != -1 )
		gr->mapCompression = val;

	// Tile reduction
	pstr = CLI_STR("-mR", "");
	switch(pstr[0])
	{
	case '\0':	break;	// No option.
	case '!':	gr->mapRedux = GRIT_RDX_OFF;		break;
	case '4':	gr->mapRedux = GRIT_RDX_REG4;	break;
	case '8':	gr->mapRedux = GRIT_RDX_REG8;	break;
	case 'a':	gr->mapRedux = GRIT_RDX_AFF;		break;
	default:
		gr->mapRedux = GRIT_RDX_TILE;
		if(strchr(pstr, 'f'))
			gr->mapRedux |= GRIT_RDX_FLIP;
		if(strchr(pstr, 'p'))
			gr->mapRedux |= GRIT_RDX_PBANK;
	}

	MapselFormat mf;

	// --- Map layout and mapsel format ---
	pstr = CLI_STR("-mL", "");
	switch(pstr[0])
	{
	case 'f':	gr->mapLayout = GRIT_MAP_FLAT;	break;
	case 's':	gr->mapLayout = GRIT_MAP_REG;	break;
	case 'a':	gr->mapLayout = GRIT_MAP_AFFINE;	break;
	}

	if(gr->mapLayout == GRIT_MAP_AFFINE)
		mf = c_mapselGbaAffine;
	else
		mf = c_mapselGbaText;

	pstr = CLI_STR("-mB", "");
	if(pstr[0])
		grit_parse_mapsel_format(pstr, &mf);

	// Tile offset
	mf.base = CLI_INT("-ma", 0);

	// Force palette; implemented as -ma/-mR combo.
	// PONDER: use separate options for this?
	if( (val = CLI_INT("-mp", -1)) >= 0)
	{
		u32 pbank = bfGet(mf.base, mf.pbShift, mf.pbLen);
		if(pbank != 0)
			lprintf(LOG_WARNING, 
"Option conflict: '-ma %04X' and '-mp%04X'\n'. Using -mp.\n", pbank, val);
		bfSet(mf.base, val, mf.pbShift, mf.pbLen);

		if(gr->mapRedux & GRIT_RDX_PBANK)
			lprintf(LOG_WARNING, 
"Option conflict: -mRp and -mp. Disabling palette reduction\n");
		gr->mapRedux &= ~GRIT_RDX_PBANK;

	}

	gr->msFormat = mf;

	return true;
}

//! Parse options related to files
/*!	\todo	Fix -fx stuff. Maybe move some of it into validation as well.
*/
bool grit_parse_file(GritRec *gr, const strvec &args)
{
	int ii;
	char *pstr;
	char *pext, str[MAXPATHLEN];

	gr->bHeader = !CLI_BOOL("-fh!");
	gr->bAppend = CLI_BOOL("-fa");

	// --- Output file type ---

	pstr = CLI_STR("-ft", "");
	switch(pstr[0])
	{
	case '!':	gr->bExport = false;				break;
	case 'b':	gr->fileType = GRIT_FTYPE_BIN;	break;
	case 'g':	gr->fileType = GRIT_FTYPE_GBFS;	break;
	case 'c':	gr->fileType = GRIT_FTYPE_C;		break;
	case 'r':	gr->fileType = GRIT_FTYPE_GRF;	break;
	//case 'o':	gr->fileType = GRIT_FTYPE_O;		break;
	case 's':
	default:	gr->fileType = GRIT_FTYPE_S;	
	}

	// Special compression things for Riff:
	if(CLI_BOOL("-ftr") || CLI_BOOL("-fr"))
	{
		gr->bRiff = true;
		if(gr->gfxCompression ==GRIT_CPRS_OFF)
			gr->gfxCompression = GRIT_CPRS_HEADER;

		if(gr->mapCompression ==GRIT_CPRS_OFF)
			gr->mapCompression = GRIT_CPRS_HEADER;

		if(gr->palCompression ==GRIT_CPRS_OFF)
			gr->palCompression = GRIT_CPRS_HEADER;
	}

	// --- Symbol name ---
	strrepl(&gr->symName, CLI_STR("-s", ""));

	// --- Output name ---
	pstr = CLI_STR("-o", "");
	if( !isempty(pstr) )
	{
		pstr = strrepl(&gr->dstPath, pstr);
		path_fix_sep(pstr);

		// Get type from name if not mentioned explicitly
		pext = path_get_ext(pstr);
		if( !CLI_BOOL("-ft") && !isempty(pext) )
		{
			for(ii = 0; ii<countof(c_fileTypes); ii++)
			{
				if(strcasecmp(pext, c_fileTypes[ii]) == 0)
				{
					gr->fileType = ii;
					break;
				}
			}
		}
		lprintf(LOG_STATUS, "Output file: '%s'.\n", gr->dstPath);
	}

	// --- External file (ext tileset) ---

	pstr = CLI_STR("-fx", "");
	if( !isempty(pstr) )
	{
		strcpy(str, pstr);
		path_fix_sep(str);

		// Check for bitdepth support
		FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(str);
		FI_SUPPORT_MODE fsm =  fiGetSupportModes(fif);

		// No 8bpp support for filetype? Change to bmp
		if(~fsm & FIF_MODE_EXP_8BPP)
		{
			lprintf(LOG_WARNING, 
"Filetype of %s doesn't allow 8bpp export. Switching to bmp.\n", 
				path_get_name(str));
			path_repl_ext(str, str, "bmp", MAXPATHLEN);
				
		}
		strrepl(&gr->shared->tilePath, str);
		gr->gfxIsShared = true;

		lprintf(LOG_STATUS, "Ext file: %s.\n", gr->shared->tilePath);	
	}

	return true;
}


//! Parse logging options.
/*!	\note	Even though a \a gr is passes, it doesn't actually do 
*		anything to it. The log level is in the return value
*/
int grit_parse_log(GritRec *gr, const strvec &args)
{
	char *pstr = CLI_STR("-W", "");

	switch(pstr[0])
	{
	case '1': case 'e':
		return LOG_ERROR;
	case '2': case 'w':
		return LOG_WARNING;
	case '3': case 's':
		return LOG_STATUS;
	}

#ifdef _DEBUG
	return LOG_STATUS;
#else
	return LOG_ERROR;
#endif
}

//! Parsing hub
/*! 
	\note Source stuff needs to be taken care of first!!
*/
bool grit_parse(GritRec *gr, const strvec &args)
{
	int val;

	// === GLOBAL options ===

	// datatype: 8, 16, 32
	if( (val = CLI_INT("-U", 0)) != 0)
	{
		val >>= 4;	// 0, 1, 2 (hax)
		gr->palDataType = val;
		gr->gfxDataType = val;
		gr->mapDataType = val;
	}

	// Overall compression
	if( (val = grit_parse_cprs("-Z", args)) != -1)
	{
		gr->palCompression = val;
		gr->gfxCompression = val;
		gr->mapCompression = val;
	}

	grit_parse_pal(gr, args);
	grit_parse_gfx(gr, args);
	grit_parse_map(gr, args);

	// Image range
	// PONDER: what about adjusting for image size?
	gr->areaLeft = CLI_INT("-al", 0);
	if( (val = CLI_INT("-aw", -1)) != -1)
		gr->areaRight = gr->areaLeft + val;
	else if( (val = CLI_INT("-ar", -1)) != -1)
		gr->areaRight = val;

	gr->areaTop = CLI_INT("-at", 0);
	if( (val = CLI_INT("-ah", -1)) != -1)
		gr->areaBottom = gr->areaTop + val;
	else if( (val = CLI_INT("-ab", -1)) != -1)
		gr->areaBottom = val;

	gr->bColMajor = CLI_BOOL("-tc");

	// === (Meta)tiling options ===

	if(CLI_BOOL("-gb"))
	{
		gr->tileWidth = CLI_INT("-tw", 1);
		gr->tileHeight = CLI_INT("-th", 1);
	}
	else
	{
		gr->tileWidth = CLI_INT("-tw", 8);
		gr->tileHeight = CLI_INT("-th", 8);
	}

	// Meta size (in tiles!)
	// PONDER: range input?
	gr->metaWidth = CLI_INT("-Mw", 1);
	gr->metaHeight = CLI_INT("-Mh", 1);

	// meta palette reduce
	if( CLI_BOOL("-MRp") )
		gr->mapRedux |= GRIT_META_PAL;

	grit_parse_file(gr, args);
	
	return true;
}

//! Special parse for shared data (grs assumed to be set-up first)
bool grit_parse_shared(GritRec *gr, const strvec &args)
{
	int val;
	GritShared *grs = gr->shared;

	// datatype: 8, 16, 32
	if( (val = CLI_INT("-U", 0)) != 0)
	{
		val >>= 4;	// 0, 1, 2 (hax)
		gr->palDataType = val;
		gr->gfxDataType = val;
	}

	// Overall compression
	if( (val = grit_parse_cprs("-Z", args)) != -1)
	{
		gr->palCompression = val;
		gr->gfxCompression = val;
	}

	grit_parse_pal(gr, args);
	grit_parse_gfx(gr, args);	

	grit_parse_file(gr, args);

	// --- Tweakage. ---
	// dst/sym name stuff:
	// * if !dst && !sym : from source (standard) and SET APPEND!!!
	// * if  dst && !sym : from dst (standard)
	// * if !dst &&  sym : from sym (unless indiv-dst exists )
	// * if  dst &&  sym : use those

	const char *pDst = CLI_STR("-O", "");
	const char *pSym = CLI_STR("-S", "");

	bool bDst = !isempty(pDst), bSym = !isempty(pSym);

	if(bDst && bSym)
	{
		strrepl(&grs->dstPath, pDst);
		strrepl(&grs->symName, pSym);		
	}	
	else if( bDst && !bSym)
	{
		strrepl(&grs->dstPath, pDst);
		strrepl(&grs->symName, gr->symName);
	}
	else if(!bDst &&  bSym)
	{
		strrepl(&grs->symName, pSym);
		if(isempty(gr->dstPath))
		    strrepl(&grs->dstPath, pSym);		
		else
		    strrepl(&grs->dstPath, gr->dstPath);
	}
	else
	{
		char symName[MAXPATHLEN];
		
		path_get_title(symName, gr->dstPath, MAXPATHLEN);
		strcat(symName, "Shared");
		lprintf(LOG_WARNING, "No -O or -S in shared run. Using \"%s\".\n", symName);
		strrepl(&grs->symName, symName);
		strrepl(&grs->dstPath, gr->dstPath);
		gr->bAppend = true;
	}

        return true;
}

bool grit_prep_shared_output(GritRec*gr, const strvec &args)
{
	if(!gr->gfxIsShared)
		gr->gfxProcMode &= ~GRIT_OUTPUT;
		
	if(!gr->palIsShared && !gr->gfxIsShared)
		gr->palProcMode &= ~GRIT_OUTPUT;

	if(gr->palIsShared)
	{
		gr->palStart = 0;
		gr->palEnd = gr->shared->palRec.height;
	}
		
	return true;
};


// --------------------------------------------------------------------
// External files
// --------------------------------------------------------------------

bool grit_load_shared_pal(GritRec *gr)
{
    lprintf(LOG_STATUS, "Loading shared palette.\n");

    GritShared *grs = gr->shared;
    char path[1024];
    path_repl_ext(path, grs->dstPath, c_fileTypes[gr->fileType], MAXPATHLEN);

    if(file_exists(path))
    {
	FILE* fp = fopen(path, "r");

	int len;
	int chunk;
	if(!grs->palRec.data)
	{
	    grs->palRec.data = (BYTE*)malloc(512 * sizeof(char));
	    memset(grs->palRec.data, 0, 512);
	}
	im_data_gas(fp, grs->symName, grs->palRec.data, &len, &chunk);
	grs->palRec.width = 4;
	grs->palRec.height = len;
    }
    else
	lprintf(LOG_WARNING, "\tShared palette (%s) does not yet exist.\n", path);

    return true;
}

//! Load an external tile file.
/*!
	\todo	Move this somewhere proper, and expand its functionality. 
	  As soon as I know what it should do anyway.
*/
bool grit_load_ext_tiles(GritRec *gr)
{
	lprintf(LOG_STATUS, "Loading tile file.\n");

	if(dib_load == NULL)
	{
		lprintf(LOG_WARNING, "  File reader not initialized. Tilefile load failed.\n");
		return false;
	}

	GritShared *grs = gr->shared;

	if(isempty(grs->tilePath))
	{
		lprintf(LOG_WARNING, "  No tilefile path. Tilefile load failed.\n");
		return false;
	}

	CLDIB *dib = NULL, *dib2 = NULL;
	dib = dib_load(grs->tilePath, NULL);

	if(dib == NULL)
	{
		lprintf(LOG_WARNING, "  Can't load tile file \"%s\".\n", grs->tilePath);
		return false;	
	}

// Convert to 8xh@8 if necessary
	if( dib_get_bpp(dib) < 8 )
	{
		lprintf(LOG_WARNING, "  External tileset bpp < 8. Converting to 8.\n");
		dib_convert(dib, 8, 0);
	}
/*
	// TODO: allow for metatiled sets
	// PONDER: shouldn't this go somewhere else?
	if( dib_get_width(dib) != 8 )
	{
		lprintf(LOG_WARNING, "  External tileset not in tile format yet. Doing so now.\n");
		dib_redim(dib, 8, 8, 0);
	}
*/

	lprintf(LOG_STATUS, "  External tileset `%s' loaded\n", grs->tilePath);

	dib_free(grs->dib);
	grs->dib = dib;

	return true;
}

bool grit_save_ext_tiles(GritRec *gr)
{
	GritShared *grs = gr->shared;

	lprintf(LOG_STATUS, "Saving tile file: `%s'.\n", grs->tilePath);

	if(grs->dib == NULL)
		return true;

	if(dib_save == NULL)
	{
		lprintf(LOG_WARNING, "  File writer not initialized. Tilefile save failed.\n");
		return false;
	}

	if(isempty(grs->tilePath))
	{
		lprintf(LOG_WARNING, "  No tilefile path. Tilefile save failed.\n");
		return false;
	}

	if(dib_save(grs->dib, grs->tilePath, NULL) == false)
	{
		lprintf(LOG_WARNING, "  Can't save tiles to `%s'", grs->tilePath);
		return false;
	}

	return true;
}


// --------------------------------------------------------------------
// --------------------------------------------------------------------


//! Get all the options for a grit-run, cli args + from file
/*!	\todo	Change for multi-file runs
*/
void args_gather(strvec &args, int argc, char **argv)
{
	/*
		Allow for adding files as well:
		- reach argv till first "-"
		- read args into arg-list
		- in grit file
		  - add args till first "-"
		  - read asrgs into arg-list
		- merge
	*/

	int ii;
	char str[MAXPATHLEN], *pstr;

	// --- Load commandline options ---
	for(ii = 0; ii<argc; ii++)
		args.push_back(strdup(argv[ii]));
	

	// --- Find option-file from {{path}}.grit or -ff ---
	path_repl_ext(str, argv[1], "grit", MAXPATHLEN);
	pstr = cli_str("-ff", args, str);

	FILE *fp = fopen(pstr, "r");
	if(fp != NULL)
	{
		// If we're here, we have a grit file.
		// '#' indicates line comments
		// Items up to the first one starting with '-' are considered
		// additional file names, loaded into 'filed' and inserted later.

		bool hasFiles = true;
		strvec files;		// For possible additional files

	// Get flags
	const char seps[]= "\n\r\t ";

	while( !feof(fp) )
	{
			fgets(str, MAXPATHLEN, fp);
		// Find comment and end string there
		if( pstr = strchr(str, '#') )
			*pstr = '\0';
		
		// Tokenize arguments
		pstr = strtok(str, seps);
		while( pstr != NULL )
		{
				if(pstr[0] == '-')
					hasFiles = false;

				if(hasFiles)
					files.push_back(strdup(pstr));
				else
			args.push_back(strdup(pstr));

			pstr = strtok(NULL, seps);
		}
	}
	fclose(fp);

		// Add additional grit files.
		// NOTE: no strdup here; I just need to add the pointers.
		if(!files.empty())
		{

			for(ii = 0; ii<argc; ii++)
				if(args[ii][0]=='-')
					break;

			args.insert(args.begin() + ii, files.begin(), files.end());
		}

	}
	else
		lprintf(LOG_STATUS, "No .grit file\n");

}

//! Some extra validation.
bool args_validate(const strvec &args, const strvec &fpaths)
{
	bool result = true;

	// Fail on troublesome options.
	if(fpaths.size()>1 && CLI_BOOL("-o") && !CLI_BOOL("-fa"))
	{
		lprintf(LOG_ERROR, "Illegal option: multifile run with -o but no -fa.\n");
		result = false;
	}

	if(fpaths.size()>1 && CLI_BOOL("-s"))
	{
		lprintf(LOG_ERROR, "Illegal option: multifile run with -s.\n");		
		result = false;
	}

	if(CLI_BOOL("-gt") && CLI_BOOL("-gb"))
	{
		lprintf(LOG_ERROR, "Illegal option: -gt and -gb.\n");		
		result = false;		
	}

	return result;
}

// NOTE: 20080203: I need a way to keep track of what kind of conversion 
// we're doing. For now, this is it.
void args_set_mode(GritShared *grs, const strvec &args, const strvec &paths)
{
	bool bShared;

	bShared = CLI_BOOL("-fx") || CLI_BOOL("-gS") || CLI_BOOL("-pS");

	grs->sharedMode  = paths.size()>1 ? GRS_MULTI : GRS_SINGLE;
	if(bShared)
		grs->sharedMode |= GRS_SHARED; 
}

bool run_prep(GritRec *gr, const char *fpath)
{
	grit_clear(gr);
	grit_init(gr);

	strrepl(&gr->srcPath, fpath);

	gr->srcDib = dib_load(gr->srcPath, NULL);
	if(gr->srcDib == NULL)
	{
		lprintf(LOG_ERROR, "\"%s\" not found or can't be read.\n", 
			gr->srcPath);
		return false;;
	}
	grit_init_from_dib(gr);

	return true;
}

//! Run for file(s) individually.
/*!	\return 0 if successfull.
*/
int run_individual(GritRec *gr, const strvec &args, const strvec &fpaths)
{
	unsigned int ii;

	lprintf(LOG_STATUS, "Individual runs.\n");

	for(ii = 0; ii<fpaths.size(); ii++)
	{
		lprintf(LOG_STATUS, "Input file %s\n", fpaths[ii]);

		if( !run_prep(gr, fpaths[ii]) )
			return EXIT_FAILURE;

		if(!grit_parse(gr, args) || !grit_run(gr))
		{
			lprintf(LOG_ERROR, "Conversion failed for %s :( \n", fpaths[ii]);
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

//! Run for file(s) with shared data.
/*!	\return 0 if successfull.
*/
int run_shared(GritRec *gr, const strvec &args, const strvec &fpaths)
{
	uint ii;
	GritShared *grs = gr->shared;

	lprintf(LOG_STATUS, "Shared-data run.\n");

	// --- semi-dummy init for shared options ---
	run_prep(gr, fpaths[0]);
	if(!grit_parse(gr, args))
		return EXIT_FAILURE;

	grs->gfxBpp = gr->gfxBpp;

	// Read external tile file
	if(gr->gfxIsShared)
		grit_load_ext_tiles(gr);

	if(gr->palIsShared)
	{
	    grit_parse_shared(gr, args);
	    grit_load_shared_pal(gr);
	}

	for(ii = 0; ii<fpaths.size(); ii++)
	{
		lprintf(LOG_STATUS, "Input file %s\n", fpaths[ii]);

		if( !run_prep(gr, fpaths[ii]) )
			continue;

		// Parse options to init rest of GritRec
		// Yes, re-parse for each file; I'm not convinced
		// it'd work otherwise yet.
		grit_parse(gr, args);

		// Remove elements that are supposed to be shared.
		if(gr->gfxIsShared)
			gr->gfxProcMode &= ~GRIT_OUTPUT;

		if(gr->palIsShared || gr->gfxIsShared)
			gr->palProcMode &= ~GRIT_OUTPUT;

		// Run and stuff
		if( !grit_run(gr) )
		{
			lprintf(LOG_ERROR, "Conversion failed at %s :( \n", fpaths[ii]);
			return EXIT_FAILURE;			
		}		
	}

	// --- Shared data conversion ---

	// Save ext tiles
	if(gr->gfxIsShared)
		grit_save_ext_tiles(gr);

	// Special init for shared data (move to ~E~ later).
	grit_clear(gr);
	grit_init(gr);
	strrepl(&gr->srcPath, fpaths[0]);

	grit_parse_shared(gr, args);
	grit_prep_shared_output(gr, args);

	grs_run(grs, gr);

	lprintf(LOG_STATUS, "Conversion finished.\n");

	return EXIT_SUCCESS;
}

//! Do a grit run.
int run_main(int argc, char **argv)
{
	unsigned int ii;
	int result = EXIT_FAILURE;
	GritRec *gr = NULL;
	strvec args, fpaths;

	try 
	{
		// --- Option and file inits ---
		args_gather(args, argc, argv);
		log_init(grit_parse_log(NULL, args), NULL);

		for(ii = 1; ii<args.size(); ii++)
		{
			if(args[ii][0] == '-')
				break;
			fpaths.push_back(strdup(args[ii]));
		}
		if(fpaths.size() == 0)
			throw "No source files.\n";

		gr = grit_alloc();
		if(gr == NULL)
			throw "Couldn't allocate GritRec memory.\n";

		lprintf(LOG_STATUS, "---%s ---\n", appIdent);

		// --- Run according to share-mode ---
		args_set_mode(gr->shared, args, fpaths);

		if(!args_validate(args, fpaths))
			throw "Bad arguments\n";

		if(gr->shared->sharedMode & GRS_SHARED)
			result = run_shared(gr, args, fpaths);
		else
			result = run_individual(gr, args, fpaths);

		lprintf(LOG_STATUS, "Done!\n");
	}
	catch(const char *msg)
	{
		lprintf(LOG_ERROR, "%s", msg);
		result = EXIT_FAILURE;
	}

		// --- Finish up ---
		grit_free(gr);

		for(ii = 0; ii<fpaths.size(); ii++)
			free(fpaths[ii]);

	for(ii = 0; ii<args.size(); ii++)
		free(args[ii]);

		log_exit();

	return result;
}

int main(int argc, char **argv)
{
	if( argc < 2 || !strcmp(argv[1], "-?") || !strcmp(argv[1], "--help") )
	{
		fprintf(stdout, "---%s ---\n", appIdent);
		fputs(appHelpText, stdout);
		return EXIT_SUCCESS;
	}

	// Initialize, run and exit ---
	FreeImage_Initialise();
	fiInit();

	int result = run_main(argc, argv);

	FreeImage_DeInitialise();

	//system("pause");

	return result;
}


// EOF
