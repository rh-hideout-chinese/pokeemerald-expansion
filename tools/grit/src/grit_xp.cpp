//
//! \file grit_xp.cpp
//!   Exporter routines
//! \date 20050814 - 20091231
//! \author cearn
//
/* === NOTES ===

  * 20100321,dm: static const is not a constant expression in c
    switch back to define.
  * 20091231,jv: use "static const" for size instead of "#define".
  * 20081129,jv:
	- fixed grit_prep_grf. The GRF chunk itself should not have 
	  an extra size field.
	- For meta-maps, the meta-tiles are now actually called fooMetaTiles, 
	  instead of fooMap.
  * 20080211,jv:
	- added DataItem. To be expanded later.
	- added grf format.
  * 20070401: 
	- Fixed directory issues
	- Updated preface
  * 20061121: xp to source now use block tags so that append *replaces* 
	old blocks instead of just tagging new ones on. This is a Good Thing.
	What isn't a good thing is how xp_h(), xp_c(), xp_gas() now have 
	large and identical start/begin blocks to make it happen. The 
	functions I use to search/copy in the existing files could prolly 
	be improved too.
	Also, I'm using tmpnam(), which apparently isn't recommended due to 
	safety, but I don't know a suitable, portable alternative.
  * strupr for non-msvc
  * PATH_MAX -> MAXPATHLEN; added path_fix_sep() use.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef _WIN32
#   include <unistd.h>
#endif

#include "cldib_core.h"
#include "grit.h"


// --------------------------------------------------------------------
// CONSTANTS
// --------------------------------------------------------------------


static const char GBFS_magic[] = "PinEightGBFS\r\n\032\n";


// --------------------------------------------------------------------
// CLASSES
// --------------------------------------------------------------------

//! Data item struct (for gfx, map, etc). 
/*! \note	Not very pretty or safe yet, but it does clean up the place. 
*/
class DataItem
{
public:
	DataItem() : procMode(GRIT_EXCLUDE), dataType(GRIT_U16), 
		compression(GRIT_CPRS_OFF), name(NULL), pRec(NULL) { }
	~DataItem()	{	free(name);	}
public:
	echar	procMode;
	echar	dataType;
	echar	compression;
	char	*name;			//!< Symbol name.
	RECORD	*pRec;			//!< Pointer to external data-record.
};

bool grit_prep_item(GritRec *gr, eint id, DataItem *item);

struct ule32 {
	unsigned int i;
	#if BYTE_ORDER == LITTLE_ENDIAN
		operator unsigned int () { return i; }
		unsigned int & operator = (unsigned int i) { return this->i = i; }
	#else
		operator unsigned int () { return i << 24 | i << 8&0xFF0000 | i >> 8&0xFF00 | i >> 24; }
		unsigned int & operator = (unsigned int i) { return this->i = i << 24 | i << 8&0xFF0000 | i >> 8&0xFF00 | i >> 24; }
	#endif
	ule32() {}
	ule32(unsigned int i) { *this = i; }
};

// --- GBFS components ---

typedef struct GBFS_FILE
{
  char magic[16];    /* "PinEightGBFS\r\n\032\n" */
  u32  total_len;    /* total length of archive */
  u16  dir_off;      /* offset in bytes to directory */
  u16  dir_nmemb;    /* number of files */
  char reserved[8];  /* for future use */
} GBFS_FILE;

typedef struct GBFS_ENTRY
{
  char name[24];     /* filename, nul-padded */
  u32  len;          /* length of object in bytes */
  u32  data_offset;  /* in bytes from beginning of file */
} GBFS_ENTRY;


#define GBFL_SIZE sizeof(GBFS_FILE)
#define GBEN_SIZE sizeof(GBFS_ENTRY)


int gbfs_namecmp(const void *a, const void *b);
int grit_gbfs_entry_init(GBFS_ENTRY *gben, const RECORD *rec, 
	const char *basename, int affix);


// --- GRF components ---

struct chunk_t
{
	char	id[4];
	ule32	size;
	u8		data[1];
};

struct GrfHeader
{
	union {
		u8 attrs[4];
		struct {
			u8	gfxAttr, mapAttr, mmapAttr, palAttr;
		};
	};
	u8		tileWidth, tileHeight;
	u8		metaWidth, metaHeight;
	ule32	gfxWidth, gfxHeight;
};

chunk_t *chunk_create(const char *id, const RECORD *rec);
chunk_t *chunk_create(const char *id, const void *data, uint size);
void chunk_free(chunk_t *chunk);
chunk_t *chunk_merge(const char *id, chunk_t *cklist[], uint count, 
	const char *groupID);

chunk_t *grit_prep_grf(GritRec *gr);


// --------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------


bool grit_xp_c(GritRec *gr);
bool grit_xp_gas(GritRec *gr);
bool grit_xp_bin(GritRec *gr);
bool grit_xp_gbfs(GritRec *gr);
bool grit_xp_grf(GritRec *gr);


// ELF export
//bool grit_xp_o(GritRec *gr);
//bool xp_array_o(FILE *fp, const char *varname, 
//	const BYTE *data, int len, int chunk);
//bool xp_data_o(FILE *fp, const BYTE *data, int len, int chunk);

// misc
void grit_xp_decl(FILE *fp, const DataItem *item);
void grit_xp_decl(FILE *fp, int chunk, const char *name, int affix, int len);
bool grit_xp_h(GritRec *gr);
bool grit_preface(GritRec *gr, FILE *fp, const char *cmt);

uint grit_xp_total_size(GritRec *gr);

// --------------------------------------------------------------------
// FUNCTIONS
// --------------------------------------------------------------------


//! Generate a random filename based on base_name and stores it in pathbuf,
//! then opens the file for writing.
static FILE* open_tmp_file(char* pathbuf, size_t pathbuf_sz,
	const char* base_name)
{
#ifdef _WIN32
    if (tmpnam_s(pathbuf, pathbuf_sz)) {
        return NULL;
    }

    FILE* f = fopen(pathbuf, "w+");
    if (f == NULL) {
        return NULL;
    }
#else
	snprintf(pathbuf, pathbuf_sz, "%s.tmp.XXXXXX", base_name);
	int fd = mkstemp(pathbuf);
	if (fd == -1) {
		return NULL;
	}

	FILE* f = fdopen(fd, "w+");
	if (f == NULL) {
		close(fd);
		return NULL;
	}
#endif
	return f;
}


//! Hub for export to file.
/*!
	Call this after all preparation is complete to export to the
	various file formats.
*/
bool grit_export(GritRec *gr)
{
	// Header file
	if(gr->bHeader)
		grit_xp_h(gr);

	// And the rest
	switch(gr->fileType)
	{
	case GRIT_FTYPE_C:
		grit_xp_c(gr);		break;

	case GRIT_FTYPE_S:
		grit_xp_gas(gr);	break;

	case GRIT_FTYPE_BIN:
		grit_xp_bin(gr);	break;

	case GRIT_FTYPE_GBFS:
		grit_xp_gbfs(gr);	break;

	case GRIT_FTYPE_GRF:
		grit_xp_grf(gr);	break;

	//case GRIT_FTYPE_O:
	//	grit_xp_o(gr);	break;
	default:
		return false;
	}

	return true;
}

//! Get size of exported data.
uint grit_xp_size(GritRec *gr)
{
	uint size = 0;
	uint extra = 0;

	if(gr->bRiff)
	{
		size = 8+8+8+sizeof(GrfHeader);	// RIFF + GRF + HDR overhead.
		extra = 8;
	}

	if(gr->gfxProcMode == GRIT_EXPORT)
		size += ALIGN4(rec_size(&gr->_gfxRec)) + extra;

	if(gr->mapProcMode == GRIT_EXPORT)
		size += ALIGN4(rec_size(&gr->_mapRec)) + extra;

	if(gr->mapProcMode == GRIT_EXPORT && gr->isMetaTiled())
		size += ALIGN4(rec_size(&gr->_metaRec)) + extra;

	if(gr->palProcMode == GRIT_EXPORT)
		size += ALIGN4(rec_size(&gr->_palRec)) + extra;

	return size;
}


//! Prepare an item for later exportation.
bool grit_prep_item(GritRec *gr, eint id, DataItem *item)
{
	char str[MAXPATHLEN];

	// Yes this is very, very, ugly and yes it will be straightened out 
	// in due time.
	switch(id)
	{
	case GRIT_ITEM_GFX:		// Graphics item
		item->procMode = gr->gfxProcMode;
		item->dataType = gr->gfxDataType;
		item->compression = gr->gfxCompression;
		item->pRec = &gr->_gfxRec;

		strcat(strcpy(str, gr->symName), 
			c_identAffix[gr->isTiled() ? E_AFX_TILE : E_AFX_BMP]);
		strrepl(&item->name, str);
		return true;

	case GRIT_ITEM_MAP:		// Map/metatile item
		item->procMode = gr->mapProcMode;
		item->dataType = gr->mapDataType;
		item->compression = gr->mapCompression;
		item->pRec = &gr->_mapRec;	

		strcat(strcpy(str, gr->symName), 
			c_identAffix[gr->isMetaTiled() ? E_AFX_MTILE : E_AFX_MAP]);
		strrepl(&item->name, str);
		return true;

	case GRIT_ITEM_METAMAP:		// Metamap item
		item->procMode = gr->isMetaTiled() ? gr->mapProcMode : GRIT_EXCLUDE;
		item->dataType = gr->mapDataType;
		item->compression = gr->mapCompression;
		item->pRec = &gr->_metaRec;	

		strcat(strcpy(str, gr->symName), c_identAffix[E_AFX_MMAP]);
		strrepl(&item->name, str);
		return true;

	case GRIT_ITEM_PAL:
		item->procMode = gr->palProcMode;
		item->dataType = gr->palDataType;
		item->compression = gr->palCompression;
		item->pRec = &gr->_palRec;	

		strcat(strcpy(str, gr->symName), c_identAffix[E_AFX_PAL]);
		strrepl(&item->name, str);
		return true;
	}

	return false;
}


// --------------------------------------------------------------------
// EXPORT TO C
// --------------------------------------------------------------------


//! Export to C source file.
bool grit_xp_c(GritRec *gr)
{
	char str[MAXPATHLEN];
	char tag[MAXPATHLEN], fpath[MAXPATHLEN], tmppath[MAXPATHLEN];
	long pos = -1;
	FILE *fin, *fout;
	bool bAppend = gr->bAppend;

	// Prep begin tag
	sprintf(tag, "//{{BLOCK(%s)",gr->symName);

	// Open 'output' file
	strcpy(fpath, gr->dstPath);

	lprintf(LOG_STATUS, "Export to C: %s into %s .\n", gr->symName, fpath);		

	// File doesn't exist -> write-mode only
	if(!file_exists(fpath))
		bAppend = false;

	if(bAppend)
	{
		// Open temp and input file
		if((fout = open_tmp_file(tmppath, sizeof(tmppath), fpath)) == NULL)
			return false;

		fin = fopen(fpath, "r");
		pos = file_find_tag(fout, fin, tag);
	}
	else
		fout = fopen(fpath, "w");

	// Add blank line before new block
	if(pos == -1)
		fputc('\n', fout);

	// --- Start grit-block ---

	fprintf(fout, "%s\n\n", tag);

	grit_preface(gr, fout, "//");

	if(gr->bRiff)	// Single GRF item
	{
		chunk_t *chunk = grit_prep_grf(gr);
		strcat(strcpy(str, gr->symName), "Grf");

		xp_array_c(fout, str, chunk, chunk->size+8, 
			grit_type_size(gr->gfxDataType));

		chunk_free(chunk);
	}
	else			// Separate items
	{
		DataItem item;
		for(eint id = GRIT_ITEM_GFX; id<GRIT_ITEM_MAX; id++)
		{
			grit_prep_item(gr, id, &item);
			if(item.procMode == GRIT_EXPORT)
				xp_array_c(fout, item.name, item.pRec->data, 
					rec_size(item.pRec), grit_type_size(item.dataType));					
		}
	}

	sprintf(tag, "//}}BLOCK(%s)",gr->symName);
	fprintf(fout, "%s\n", tag);

	// --- End grit-block ---

	if(bAppend)
	{
		// Skip till end tag and copy rest
		file_find_tag(NULL, fin, tag);
		file_copy(fout, fin, -1);

		// close files and rename
		fclose(fin);
		if (rename(tmppath, fpath) < 0)
		{
			// in case rename fails, copy over the source file instead
			fin = fopen(fpath, "w");
			fseek(fout, 0, SEEK_SET);
			file_copy(fin, fout, -1);
			fclose(fin);
			fclose(fout);
			remove(tmppath);
		}
		else
		{
			fclose(fout);
		}
	}
	else
	{
		fclose(fout);		// close files
	}

	return true;
}


// --------------------------------------------------------------------
// EXPORT TO ASM
// --------------------------------------------------------------------


//! Export to GNU Assembly
// Yes, it is almost identical to c. Maybe I'll merge the two 
// later.
bool grit_xp_gas(GritRec *gr)
{
	char str[MAXPATHLEN];
	char tag[MAXPATHLEN], fpath[MAXPATHLEN], tmppath[MAXPATHLEN];
	long pos = -1;
	FILE *fin, *fout;
	bool bAppend = gr->bAppend;

	// Prep begin tag
	sprintf(tag, "@{{BLOCK(%s)",gr->symName);

	// Open 'output' file
	strcpy(fpath, gr->dstPath);

	lprintf(LOG_STATUS, "Export to GNU asm: %s into %s .\n", gr->symName, fpath);		

	// File doesn't exist -> write-mode only
	if(!file_exists(fpath))
		bAppend = false;

	if(bAppend)
	{
		// Open temp and input file
		if((fout = open_tmp_file(tmppath, sizeof(tmppath), fpath)) == NULL)
			return false;

		fin = fopen(fpath, "r");
		pos = file_find_tag(fout, fin, tag);
	}
	else
		fout = fopen(fpath, "w");

	// Add blank line before new block
	if(pos == -1)
		fputc('\n', fout);

	// --- Start grit-block ---

	fprintf(fout, "%s\n\n", tag);

	grit_preface(gr, fout, "@");


	if(gr->bRiff)	// Single GRF item
	{
		chunk_t *chunk = grit_prep_grf(gr);
		strcat(strcpy(str, gr->symName), "Grf");

		xp_array_gas(fout, str, chunk, chunk->size+8, 
			grit_type_size(gr->gfxDataType));

		chunk_free(chunk);
	}
	else			// Separate items
	{
		DataItem item;
		for(eint id = GRIT_ITEM_GFX; id<GRIT_ITEM_MAX; id++)
		{
			grit_prep_item(gr, id, &item);
			if(item.procMode == GRIT_EXPORT)
				xp_array_gas(fout, item.name, item.pRec->data, rec_size(item.pRec), 
					grit_type_size(item.dataType));					
		}
	}

	sprintf(tag, "@}}BLOCK(%s)",gr->symName);
	fprintf(fout, "%s\n", tag);

	// --- End grit-block ---

	if(bAppend)
	{
		// Skip till end tag and copy rest
		file_find_tag(NULL, fin, tag);
		file_copy(fout, fin, -1);

		// close files and rename
		fclose(fin);
		if (rename(tmppath, fpath) < 0)
		{
			// in case rename fails, copy over the source file instead
			fin = fopen(fpath, "w");
			fseek(fout, 0, SEEK_SET);
			file_copy(fin, fout, -1);
			fclose(fin);
			fclose(fout);
			remove(tmppath);
		}
		else
		{
			fclose(fout);
		}
	}
	else
	{
		fclose(fout);		// close files
	}

	return true;
}


// --------------------------------------------------------------------
// EXPORT TO BIN
// --------------------------------------------------------------------


//! Export to binary files
/*!
	\note Binary files cannot be appended, and are separate files.
*/
bool grit_xp_bin(GritRec *gr)
{
	lprintf(LOG_STATUS, "Export to binary files.\n");		

	char fpath[MAXPATHLEN], str[MAXPATHLEN];
	const char *fmode = gr->bAppend ? "a+b" : "wb";
	const char *exts[4]= {"img.bin", "map.bin", "meta.bin", "pal.bin" };

	path_repl_ext(str, gr->dstPath, NULL, MAXPATHLEN);
	
	DataItem item;
	for(eint id = GRIT_ITEM_GFX; id<GRIT_ITEM_MAX; id++)
	{
		grit_prep_item(gr, id, &item);
		if(item.procMode == GRIT_EXPORT)
		{
			path_repl_ext(fpath, str, exts[id], MAXPATHLEN);
			xp_data_bin(fpath, item.pRec->data, rec_size(item.pRec), fmode);
		}
	}

	return true;
}


// --------------------------------------------------------------------
// EXPORT TO GBFS
// --------------------------------------------------------------------

//! Export to GBFS file
/*! The 'append' mode for this function is special. Yes, it adds 
	new data to the file, but it also <i>replaces</i> old data of 
	the same name. Yes, this is proper procedure and should happen 
	in the others as well, but it's just easier in a binary 
	environment. The header file will still have double definitions,
	though.
	\todo	Code is inconsistent with the C/asm exporters. Rectify.
*/
bool grit_xp_gbfs(GritRec *gr)
{
	int ii, jj;

	// for new data
	int gr_count;
	BYTE *gr_data[4];
	GBFS_ENTRY gr_gben[4];

	// for total data
	int gb_count;
	GBFS_ENTRY *gbenL = gr_gben, *gbenD = NULL;

	ii = 0;

	// --- register the various fields ---

	// Graphics
	if(gr->gfxProcMode == GRIT_EXPORT)
	{
		grit_gbfs_entry_init(&gr_gben[ii], &gr->_gfxRec, 
			gr->symName, (gr->isTiled() ? E_AFX_TILE : E_AFX_BMP));
		gr_data[ii++]= gr->_gfxRec.data;
	}

	// Map
	if(gr->mapProcMode == GRIT_EXPORT)
	{
		grit_gbfs_entry_init(&gr_gben[ii], &gr->_mapRec, 
			gr->symName, (gr->isMetaTiled() ? E_AFX_MTILE :E_AFX_MAP));
		gr_data[ii++]= gr->_mapRec.data;

		// Meta map
		if(gr->isMetaTiled())
		{
			grit_gbfs_entry_init(&gr_gben[ii], &gr->_metaRec, 
				gr->symName, E_AFX_MMAP);
			gr_data[ii++]= gr->_metaRec.data;
		}
	}

	// Palette
	if(gr->palProcMode == GRIT_EXPORT)
	{
		grit_gbfs_entry_init(&gr_gben[ii], &gr->_palRec, 
			gr->symName, E_AFX_PAL);
		gr_data[ii++]= gr->_palRec.data;
	}

	gb_count = gr_count = ii;

	// --- create header and finish entries ---
	// Create basic header
	GBFS_FILE gbhdr;
	memcpy(gbhdr.magic, GBFS_magic, sizeof(GBFS_magic));
	gbhdr.dir_off = GBFL_SIZE;

	char name[MAXPATHLEN];
	strcpy(name, gr->dstPath);
	path_fix_sep(name);

	lprintf(LOG_STATUS, "Export to GBFS: %s into %s .\n", 
		gr->symName, name);


	FILE *fout = fopen("gbfs.tmp", "wb");
	if(fout == NULL)
		return false;

	u32 fpos = GBFL_SIZE + gr_count*GBEN_SIZE;
	fseek(fout, fpos, SEEK_SET);	// skip directory

	// Insert mode
	// Replace old with same name; insert new
	if(gr->bAppend)
	{
		FILE *fin = fopen(name, "rb");
		do
		{
			if(fin == NULL)
				break;

			GBFS_FILE oldhdr;
			// read and check file's header
			if(fread(&oldhdr, GBFL_SIZE, 1, fin) < 1)
			{	break;	}
			if(memcmp(oldhdr.magic, GBFS_magic, 16))
				break;

			// if we're here, we have a valid GBFS

			int old_count = oldhdr.dir_nmemb;
			gbenD = (GBFS_ENTRY*)malloc(old_count*GBEN_SIZE);
			if(gbenD ==NULL)
				break;

			// Read directory
			fread(gbenD, GBEN_SIZE, old_count, fin);
			// check for obsoletes
			for(ii = 0; ii<gr_count; ii++)
			{
				gbenL = (GBFS_ENTRY*)bsearch(&gr_gben[ii], gbenD, 
					old_count, GBEN_SIZE, gbfs_namecmp);
				if(gbenL == NULL)
					continue;
				// Obsolete found; remove from list;
				jj = (gbenL-gbenD);
				old_count--;
				memmove(gbenL, gbenL+1, (old_count-jj)*GBEN_SIZE);
			}
			// NOTE: old_count may have been modified
			gb_count = gr_count+old_count;

			// obsoletes are removed; write the rest to fout
			BYTE buf[1024];
			fpos = GBFL_SIZE + gb_count*GBEN_SIZE;
			fseek(fout, fpos, SEEK_SET);

			for(ii = 0; ii<old_count; ii++)
			{
				fseek(fin, gbenD[ii].data_offset, SEEK_SET);
				gbenD[ii].data_offset = fpos;
				
				jj = gbenD[ii].len >> 10;
				while(jj--)
				{
					fread(buf, 1024, 1, fin);
					fwrite(buf, 1024, 1, fout);
				}
				if((jj = gbenD[ii].len & 1023) != 0)
				{
					fread(buf, jj, 1, fin);
					fwrite(buf, jj, 1, fout);
				}

				// pad to 16byte boundary
				for(fpos = ftell(fout); fpos & 0x0F; fpos++)
					fputc(0, fout);
			}

			// Combine lists
			gbenL = (GBFS_ENTRY*)malloc(gb_count*GBEN_SIZE);
			memcpy(gbenL, gr_gben, gr_count*GBEN_SIZE);
			memcpy(&gbenL[gr_count], gbenD, old_count*GBEN_SIZE);
			free(gbenD);
			gbenD = gbenL;
		} while(0);

		if(fin)
			fclose(fin);
	}
	// At this point, either: 
	// * Insert-mode failed or wasn't issued 
	//   -> gb_count ==gr_count
	//   -> fpos is past directory
	//   -> gbenL = gr_gben ; short list
	// * Insert-mode worked:
	//   -> gb_count = full count ; 
	//   -> fpos is past up-to-date entries
	//   -> gbenL = gbenD contains all GBFS_ENTRYs; 

	// --- Write to file ---
	
	// Write entries' data
	// NOTE: only new data; 'old' data is already take care of
	fpos = ftell(fout);
	for(ii = 0; ii<gr_count; ii++)
	{
		gbenL[ii].data_offset = fpos;
		fwrite(gr_data[ii], gbenL[ii].len, 1, fout);

		// pad to 16byte boundary
		for(fpos = ftell(fout); fpos & 0x0F; fpos++)
			fputc(0, fout);
	}

	gbhdr.dir_nmemb = gb_count;
	gbhdr.total_len = fpos;

	// Sort entries _after_ writing the data
	// otherwise the lengths may be screwed up
	qsort(gbenL, gb_count, GBEN_SIZE, gbfs_namecmp);

	// Write header and directory
	rewind(fout);		
	fwrite(&gbhdr, GBFL_SIZE, 1, fout);
	fwrite(gbenL, GBEN_SIZE, gb_count, fout);

	SAFE_FREE(gbenD);
	fclose(fout);

	// rename to real name
	remove(name);
	rename("gbfs.tmp", name);

	return true;
}

// for qsort
int gbfs_namecmp(const void *a, const void *b)
{
	return memcmp(a, b, 24);
}

//! Fills a GBFS_ENTRY.
/*!
	\param gben Entry to fill
	\param rec Record to register
	\param basename Base name for the the entry (cut to 21 letters)
	\param affix Affix for the name.
	\return Uhm ... nothing, really.
	\note The names of GBFS_ENTRY's are 24 chars max, so long names 
	  are cut off. But, because the affix is an integral name is 
	  part of the full name, the \a basename is cut to 21, after 
	  which the affix is added. The whole thing is then cut to 24 
	  chars.
*/
int grit_gbfs_entry_init(GBFS_ENTRY *gben, const RECORD *rec, 
	const char *basename, int affix)
{
	char name[32];
	strncpy(name, basename, 21);
	name[21]= '\0';
	strcat(name, c_identAffix[affix]);

	strncpy(gben->name, name, 24);
	gben->len = ALIGN4(rec_size(rec));
	gben->data_offset = 0;

	return 1;
}


// --------------------------------------------------------------------
// EXPORT TO GRF
// --------------------------------------------------------------------


//! Create a RIFF chunk.
chunk_t *chunk_create(const char *id, const RECORD *rec)
{
	return chunk_create(id, rec->data, rec_size(rec));
}

//! Create a RIFF chunk
/*!
	\note PONDER: Is ckSize always 4-aligned or just the chunk?
*/
chunk_t *chunk_create(const char *id, const void *data, uint size)
{
	uint ii;

	size = ALIGN4(size);
	chunk_t *chunk = (chunk_t*)malloc(size+8);

	for(ii = 0; ii<4; ii++)
		chunk->id[ii]= id[ii];

	chunk->size = size;	
	memcpy(&chunk->data, data, size);

	return chunk;
}


//! Merge multiple chunks into a single large one.
/*!	\param id		Parent name.
	\param cklist	Array of child-chunks to merge.
	\param count	Length of \a cklist.
	\param groupID	Group identifier for parent ("RIFF", "LIST", etc.).
		Can be NULL.
	\return	Merged chunks with under the name of \a id.
*/
chunk_t *chunk_merge(const char *id, chunk_t *cklist[], uint count, const char *groupID)
{
	uint ii;
	uint size = 0;

	for(ii = 0; ii<count; ii++)
		if(cklist[ii] != NULL)
			size += align(cklist[ii]->size,4)+8;

	chunk_t *chunk;
	u8 *dst;

	// Split creation into with or without group id.
	if(groupID)
	{
		// Make room for groupsID+total_size+id+data
		chunk = (chunk_t*)malloc(size+8+4);
		chunk_t *sub = (chunk_t*)chunk->data;

		for(ii = 0; ii<4; ii++)
		{
			chunk->id[ii]= groupID[ii];
			chunk->data[ii]= id[ii];
		}

		chunk->size = size+4;
		dst = chunk->data+4;
	}
	else
	{
		chunk = (chunk_t*)malloc(size+8);	
		for(ii = 0; ii<4; ii++)
			chunk->id[ii]= id[ii];
		chunk->size = size;
		dst = chunk->data;
	}


	for(ii = 0; ii<count; ii++)
	{
		if(cklist[ii] != NULL)
		{
			size = cklist[ii]->size+8;
			memcpy(dst, cklist[ii], size);
			dst += size;
		}
	}

	return chunk;
	
}

//! Free a RIFF chunk
void chunk_free(chunk_t *chunk)
{
	free(chunk);
}

chunk_t *grit_prep_grf(GritRec *gr)
{
	GrfHeader hdr;
	chunk_t *cklist[5]=  { NULL };

	// Semi-constant data.

	const char *ckIDs[4]= 
	{
		"GFX ",
		(gr->isMetaTiled() ? "MTIL" : "MAP "),
		"MMAP",	"PAL "
	};
	uint bpps[4]= { gr->gfxBpp, 16, 16, 16 };
	if(gr->mapLayout == GRIT_MAP_AFFINE)
		bpps[GRIT_ITEM_MAP]= 8;

	memset(&hdr, 0, sizeof(hdr));

	//# PONDER: what should the sizes represent?
	hdr.gfxWidth = gr->areaRight - gr->areaLeft;			
	hdr.gfxHeight = gr->areaBottom - gr->areaTop;

	hdr.tileWidth = gr->tileWidth;
	hdr.tileHeight = gr->tileHeight;

	if(gr->isMetaTiled())
	{
		hdr.metaWidth = gr->metaWidth;
		hdr.metaHeight = gr->metaHeight;
	}

	DataItem item;
	for(eint id = GRIT_ITEM_GFX; id<GRIT_ITEM_MAX; id++)
	{
		grit_prep_item(gr, id, &item);
		if(item.procMode == GRIT_EXPORT)
		{
			hdr.attrs[id]= bpps[id];
			cklist[id+1]= chunk_create(ckIDs[id], item.pRec);
		}
	}

	// Create header chunk and merge
	cklist[0]= chunk_create("HDR ", &hdr, sizeof(GrfHeader));
	chunk_t *chunk = chunk_merge("GRF ", cklist, 5, "RIFF");

	for(int ii = 0; ii<5; ii++)
		chunk_free(cklist[ii]);	

	return chunk;
}

//! Export to GRF : Grit RIFF
/*!
	\note	No append mode just yet.
*/
bool grit_xp_grf(GritRec *gr)
{	
	lprintf(LOG_STATUS, "Export to GRF: %s into %s .\n", 
		gr->symName, gr->dstPath);
	if(gr->bAppend)
		lprintf(LOG_WARNING, "  No append mode for GRF yet.\n");

	FILE *fout = fopen(gr->dstPath, "wb");

	chunk_t *chunk = grit_prep_grf(gr);
	fwrite(chunk, 1, chunk->size+8, fout);
	chunk_free(chunk);

	fclose(fout);

	return true;
}


// --------------------------------------------------------------------
// EXPORT TO ELF
// --------------------------------------------------------------------


//! Export to GNU object file
/*!
	\note Non-functional. For future use.
*/
bool grit_xp_o(GritRec *gr)
{
	return true;
}


//! Export a single array to GNU object file (for future use)
bool xp_array_o(FILE *fp, const char *varname, 
	const BYTE *data, int len, int chunk);



// ====================================================================
// === HELPERS ========================================================


//! Write C declaration and size define to file
/*!
	\param fp. FILE pointer
	\param chunk # bytes per datatype (1,2,4)
	\param name Base name of the variable
	\param affix Data-affix index (for &ldquo;Pal&rdquo;, 
		&ldquo;Map&rdquo;, etc)
	\param len Size in bytes. Will be ceilinged for the type. 
		(though it probably already is)
	\remark Example use: grit_xp_decl(fp, 2, "foo", E_MAP, 256); 
		gives <br>
		[code]<br><code>
		#define fooMapLen 256<br>
		extern const unsigned short fooMap[128];</code><br>
		[/code]
*/
void grit_xp_decl(FILE *fp, int dtype, const char *name, int affix, int len)
{
	fprintf(fp, "#define %s%sLen %d\n", name, c_identAffix[affix], len);
	fprintf(fp, "%s %s %s%s[%d];\n\n", cTypeSpec, cCTypes[dtype], 
		name, c_identAffix[affix],  ALIGN4(len)/dtype);
}

void grit_xp_decl(FILE *fp, DataItem *item)
{
	if(item == NULL || item->pRec == NULL)
		return;

	uint size = rec_size(item->pRec);
	uint dtype = grit_type_size(item->dataType);
	uint count = ALIGN4(size)/dtype;

	fprintf(fp, "#define %sLen %d\n", item->name, size);
	fprintf(fp, "%s %s %s[%d];\n\n", cTypeSpec, cCTypes[dtype], 
		item->name, count);
}


//! Creates header file with the declaration list
/*
	\note The header file is for declarations only; it does NOT have 
		actual data in it. Data in headers is bad, so don't have 
		data in headers, mkay? Mkay!
*/
bool grit_xp_h(GritRec *gr)
{
	char str[MAXPATHLEN];
	char tag[MAXPATHLEN], fpath[MAXPATHLEN], tmppath[MAXPATHLEN];
	long pos = -1;
	FILE *fin, *fout;
	bool bAppend = gr->bAppend;

	// Prep begin tag
	sprintf(tag, "//{{BLOCK(%s)",gr->symName);

	// Open 'output' file
	path_repl_ext(fpath, gr->dstPath, "h", MAXPATHLEN);

	// File doesn't exist -> write-mode only
	if(!file_exists(fpath))
		bAppend = false;

	if(bAppend)
	{
		// Open temp and input file
		if((fout = open_tmp_file(tmppath, sizeof(tmppath), fpath)) == NULL)
			return false;

		fin = fopen(fpath, "r");
		pos = file_find_tag(fout, fin, tag);
	}
	else
		fout = fopen(fpath, "w");

	// Add blank line before new block
	if(pos == -1)
		fputc('\n', fout);

	// --- Start grit-block ---

	fprintf(fout, "%s\n\n", tag);

	grit_preface(gr, fout, "//");

	// include guards
	strcpy(str, gr->symName);
	strupr(str);
	fprintf(fout, "#ifndef GRIT_%s_H\n#define GRIT_%s_H\n\n", str, str);


	if(gr->bRiff)	// Single GRF item
	{
		grit_xp_decl(fout, grit_type_size(gr->gfxDataType), 
			gr->symName, E_AFX_GRF, grit_xp_size(gr));
	}
	else			// Separate items
	{
		DataItem item;
		for(eint id = GRIT_ITEM_GFX; id<GRIT_ITEM_MAX; id++)
		{
			grit_prep_item(gr, id, &item);
			if(item.procMode == GRIT_EXPORT)
			grit_xp_decl(fout, &item);
		}
	}

	// include guards again
	strcpy(str, gr->symName);
	strupr(str);
	fprintf(fout, "#endif // GRIT_%s_H\n\n", str);

	sprintf(tag, "//}}BLOCK(%s)",gr->symName);
	fprintf(fout, "%s\n", tag);

	// --- End grit-block ---

	if(bAppend)
	{
		// Skip till end tag and copy rest
		file_find_tag(NULL, fin, tag);
		file_copy(fout, fin, -1);

		// close files and rename
		fclose(fin);
		if (rename(tmppath, fpath) < 0)
		{
			// in case rename fails, copy over the source file instead
			fin = fopen(fpath, "w");
			fseek(fout, 0, SEEK_SET);
			file_copy(fin, fout, -1);
			fclose(fin);
			fclose(fout);
			remove(tmppath);
		}
		else
		{
			fclose(fout);
		}
	}
	else
	{
		// close files
		fclose(fout);
	}

	return true;
}

//! Creates data preface, containing a data description
/*!
	The preface describres a little bit about the preferred 
	interpolation of the data: bitmap size, bitdepth, compression, 
	size, etc. As data itself is rather open to interpretation, 
	this can come in very handy after a while.
	\param gr	Git record.to describe
	\param fp	FILE pointer
	\param cmt	Comment symbol string (like &ldquo;//&rdquo; for C)
*/
bool grit_preface(GritRec *gr, FILE *fp, const char *cmt)
{
	int tmp, size = 0;
	int aw, ah, mw, mh;
	char hline[80], str2[16]="", str[96]="";

	time_t aclock;
	struct tm *newtime;

	memset(hline, ' = ', 72);
	hline[72]= '\n';
	hline[73]= '\0';
	memcpy(hline, cmt, strlen(cmt));

	aw = gr->areaRight  - gr->areaLeft;
	ah = gr->areaBottom - gr->areaTop;
	mw = gr->metaWidth;
	mh = gr->metaHeight;

	//build a bpp or texformat description
	char bppDescr[16];
	sprintf(bppDescr,"%d",gr->gfxBpp);
	switch(gr->gfxTexMode)
	{
	case GRIT_TEXFMT_NONE: break;
	case GRIT_TEXFMT_A5I3: strcpy(bppDescr,"a5i3"); break;
	case GRIT_TEXFMT_A3I5: strcpy(bppDescr,"a3i5"); break;
	case GRIT_TEXFMT_4x4: strcpy(bppDescr,"4x4"); break;
	}

	fprintf(fp, "%s%s\n", hline, cmt);
	fprintf(fp, "%s\t%s, %dx%d@%s, \n", cmt, gr->symName, aw, ah, bppDescr);

	// Transparency options
	if(gr->gfxHasAlpha)
	{
		RGBQUAD *rgb = &gr->gfxAlphaColor;
		fprintf(fp, "%s\tTransparent color : %02X,%02X,%02X\n", cmt, 
			rgb->rgbRed, rgb->rgbGreen, rgb->rgbBlue);
	}
	else if(gr->gfxMode == GRIT_GFX_BMP_A)
	{
		fprintf(fp, "%s\tAlphabit on.\n", cmt);
	}
	else if(gr->palHasAlpha)
	{
		fprintf(fp, "%s\tTransparent palette entry: %d.\n", cmt, gr->palAlphaId);
	}

	// Palette comments
	if(gr->palProcMode == GRIT_EXPORT)
	{
		tmp = rec_size(&gr->_palRec);
		fprintf(fp, "%s\t+ palette %d entries, ", cmt, tmp/2);
		fprintf(fp, "%s compressed\n", c_cprsNames[gr->palCompression]);
		
		sprintf(str2, "%d + ", tmp);
		strcat(str, str2);
		size += tmp;
	}

	// Bitmap/tileset comments
	if(gr->gfxProcMode == GRIT_EXPORT)
	{
		fprintf(fp, "%s\t+ ", cmt);
		switch(gr->gfxMode)
		{
		case GRIT_GFX_TILE:
			tmp = dib_get_width(gr->_dib)*dib_get_height(gr->_dib)/64;
			fprintf(fp, "%d tiles ", tmp);

			if(gr->mapProcMode != GRIT_EXCLUDE && gr->mapRedux != 0)
			{
				// TODO: blank flag
				fputs("(t", fp);
				if(gr->mapRedux & GRIT_RDX_FLIP)
					fputs("|f", fp);
				if(gr->mapRedux & GRIT_RDX_PBANK)
					fputs("|p", fp);
				fputs(" reduced) ", fp);
			}

			// If map is printed as well, put meta cmt there
			if(gr->mapProcMode != GRIT_EXPORT && mw*mh > 1)
				fprintf(fp, "Metatiled by %dx%d ", mw, mh);
			break;

		case GRIT_GFX_BMP:
		case GRIT_GFX_BMP_A:
			fputs("bitmap ", fp);						
			break;
		}

		fprintf(fp, "%s compressed\n", c_cprsNames[gr->gfxCompression]);

		tmp = rec_size(&gr->_gfxRec);
		sprintf(str2, "%d + ", tmp);
		strcat(str, str2);
		size += tmp;
	}

	// (meta-)map comments
	if(gr->mapProcMode == GRIT_EXPORT)
	{
		fprintf(fp, "%s\t+ ", cmt);
		switch(gr->mapLayout)
		{
		case GRIT_MAP_FLAT:
			fputs("regular map (flat), ", fp);		break;
		case GRIT_MAP_REG:
			fputs("regular map (in SBBs), ", fp);	break;
		case GRIT_MAP_AFFINE:
			fputs("affine map, ", fp);				break;
		}

		fprintf(fp, "%s compressed, ", c_cprsNames[gr->mapCompression]);
		
		tmp = rec_size(&gr->_mapRec);
		sprintf(str2, "%d + ", tmp);
		strcat(str, str2);
		size += tmp;

		fprintf(fp, "%dx%d \n", aw/mw/8, ah/mh/8);
		if(gr->isMetaTiled())
		{
			fprintf(fp, "%s\tMetatiled by %dx%d\n", cmt, mw, mh);
			tmp = rec_size(&gr->_metaRec);
			sprintf(str2, "%d + ", tmp);
			strcat(str, str2);
			size += tmp;
		}
		if(gr->gfxIsShared)
			fprintf(fp, "%s\tExternal tile file: %s.\n", cmt, 
				gr->shared->tilePath);
	}
	
	tmp = strlen(str);
	if(tmp>2)
	{
		str[tmp-2]= ' = ';
		fprintf(fp, "%s\tTotal size: %s%d\n", cmt, str, size);
	}

	time( &aclock );
	newtime = localtime( &aclock );
	strftime(str, 96, "%Y-%m-%d, %H:%M:%S", newtime);

	fprintf(fp, "%s\n%s\tTime-stamp: %s\n", cmt, cmt, str);

	const char *curr = grit_app_string, *prev = curr;
	while( (curr = strchr(prev, '\n')) != NULL )
	{
		fputs(cmt, fp);
		fwrite(prev, curr+1-prev, 1, fp);
		prev = curr+1;
	}

	fprintf(fp, "%s%s\n", cmt, prev);
	fprintf(fp, "%s\n%s\n", cmt, hline);

	return true;
}


// EOF
