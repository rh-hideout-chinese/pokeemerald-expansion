//
// pathfun.cpp
//   Path/file functions
// (20050826 - 20081128, cearn)
//
/* === NOTES === 
  * 20081128,jv: xp_array_c now adds a GCC alignment attribute.
  * 20070401, jv:
	- added path_repl_ext
	- TODO: doxygenate
	- TODO: more consistency in code
  * 20061121: added strtrim(), file_copy() and file_find_tag()
  * 20061010, PONDER: rename to filefun?
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pathfun.h"

#ifdef _MSC_VER
	#ifndef PATH_MAX
	#define PATH_MAX	MAX_PATH
	#endif

	#ifndef MAXPATHLEN
	#define MAXPATHLEN  _MAX_PATH
	#endif
#else
	#include <sys/param.h>
	#include <unistd.h>
	#include <strings.h>
#endif


// --------------------------------------------------------------------
// CONSTANTS
// --------------------------------------------------------------------

#define ALIGN4(n) ( ((n)+3)&~3 )


const char cTypeSpec[]= "extern const unsigned";
const char *cCTypes[]= { "", "char", "short", "", "int" };
const char *cGasTypes[]= { "", ".byte", ".hword", "", ".word" };


// --------------------------------------------------------------------
// PATH FUNCTIONS
// --------------------------------------------------------------------


/*
  File path:
  [vol]{VOL_SEP}[dir]{DIR_SEP}[name]
  [name] = [title].[ext2]

  vol =	volume letter
  dir =	directory part, (without surrounding separators ?)
  xdir =	vol + dir
  title =	part between last DIR_SEP and last EXT_SEP
  xtitle =	part between last DIR_SEP and first EXT_SEP
  name =		all after last DIR_SEP (title + ext)
  ext =		all after last EXT_SEP
  xext =		all after _first_ EXT_SEP


  Example: "c:/food/bard/foot.foox.barx"
  vol =	c
  dir =	food/bard
  xdir =	c:/food/bard
  title =	foot.foox
  xtitle =	foot
  name =		foot.foox.barx
  ext =		barx
  xext =		foox
*/


// === Get path components ============================================

int path_get_vol(const char *path)
{
	// ASSERT(path);
	if(!path)
		return 0;

	int c = tolower(path[0]);
	if(path[1] != VOL_SEP || c<'a' || c>'z')
		return 0;
	return c;	
}

char *path_get_dir(char *dst, const char *path, int size)
{
	// ASSERT(path);
	// ASSERT(dst);
	if(!dst || !path)
		return NULL;

	char *pc = (char*)strrchr(path, DIR_SEP);
	if(pc == NULL)
	{
		dst[0]= '\0';
		return NULL;
	}

	size = (size>pc-path ? pc-path : size);
	memcpy(dst, path, size);
	dst[size]= '\0';

	return dst;
}

char *path_get_title(char *dst, const char *path, int size)
{
	// ASSERT(path);
	// ASSERT(dst);
	if(!dst)
		return NULL;

	if(isempty(path))
	{
		dst[0]= '\0';
		return NULL;
	}

	// Find directory part
	const char *pc = strrchr(path, DIR_SEP);
	if(pc)
		path = pc+1;

	// find extension part
	pc = strrchr(path, '.');

	// only copy the part between dir (if any) 
	// and primary extension (if any)
	int size2 = pc ? pc-path : strlen(path);
	if(size>size2)
		size = size2;

	memcpy(dst, path, size);
	dst[size]= '\0';

	return dst;
}

char *path_get_ext(const char *path)
{
	// ASSERT(path);
	if(!path)
		return NULL;

	// make sure we don't mistake '.' in dirs
	const char *pc = strrchr(path, DIR_SEP);
	if(pc)
		path = pc;
	// check for real extension
	pc =	strrchr(path, '.');
	if(pc)
		pc++;
	return (char*)pc;
}

// --- extra ---

char *path_get_name(const char *path)
{
	// ASSERT(path);
	if(!path)
		return NULL;

	const char *pc = strrchr(path, DIR_SEP);
	pc = pc ? pc+1 : path;

	return (char*)pc;
}

char *path_get_xext(const char *path)
{
	// ASSERT(path);
	if(!path)
		return NULL;

	// Skip directory part
	const char *pc = strrchr(path, DIR_SEP);
	if(pc)
		path = pc;
	// Find full extension
	pc = strchr(path, '.');
	if(pc)
		pc++;

	return (char*)pc;
}

char *path_get_xtitle(char *dst, const char *path, int size)
{
	// ASSERT(path);
	// ASSERT(dst);
	if(!dst || !path)
		return NULL;

	if(path[0]=='\0')
	{
		dst[0]= '\0';
		return 0;
	}
	// Find directory part
	const char *pc = strrchr(path, DIR_SEP);
	if(pc)
		path = pc;
	// find full extension
	pc = strchr(path, '.');
	// only copy the part between dir (if any) 
	// and primary extension (if any)
	if(pc && size>pc-path)
		size = pc-path;

	memcpy(dst, path, size);
	dst[size]= '\0';

	return dst;
}


// === Replace components ============================================

//!	Replace (or add) an extension to a path
/*!	\param dst	Destination buffer.
*	\param path	Path to alter.
*	\param ext	Nex extension. If empty, the old extension will be removed.
*	\param size	Size of \a dst.
*/
char *path_repl_ext(char *dst, const char *path, const char *ext, int size)
{
	if(!dst || !path || size<1)
		return NULL;
	
	char str[MAXPATHLEN], *pext;

	strcpy(str, path);
	pext = path_get_ext(str);

	if(!isempty(ext))	// Replace
	{
		if(pext)
			strcpy(pext, ext);
		else
		{
			strcat(str, ".");
			strcat(str, ext);
		}
	}
	else				// Remove
	{
		if(pext && pext[-1] == '.')
			pext[-1]= '\0';
	}

	int newsize = strlen(str);
	str[(size<newsize ? size-1 : newsize)]= '\0';
	strcpy(dst, str);

	return dst;
}


// === Separator functions ============================================

void path_add_dir_sep(char *path)
{
	// ASSERT(path);
	if(!path)
		return;

	int len = strlen(path);
	int c = path[len-1];

	if(len ==0 || c ==DIR_SEP)
		return;

	path[len]= DIR_SEP;
	path[len+1]= '\0';
}

char *path_fix_sep(char *path)
{
	// ASSERT(path);
	if(!path)
		return NULL;

	int ii;
	for(ii = 0; path[ii] != '\0'; ii++)
	{
		switch(path[ii])
		{
		case DIR_SEP_WIN:	case DIR_SEP_UNIX:
			path[ii]= DIR_SEP;	
			break;
		case VOL_SEP_WIN:	case VOL_SEP_UNIX:
			path[ii]= VOL_SEP;
			break;
		}
	}

	return path;
}


char *path_canon(char *dst, const char *path, int size);


#ifdef _WIN32

#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>

//! Getting the full path of a file, the horrible way
/*!
	A few words about this function, and why it's necessary, and why 
	it is necessaary to be in <i>this</i> wretched form.<br>
	Yes, Win9x has long filenames. Unfortunately, they don't work when 
	you drag-and-drop a file to an app's icon; in that case, the MS-DOS 
	short filename is used. With all its "~1"s. And all caps. 
	Fortunately, there's something called FindFirstFile that can 
	actually get the long version. Unfortunately, that <i>also</i> 
	doesn't work on drag-and-drop to an app's icon. At least, not quite. 
	You only get the \b last part of the path or directory. So you have 
	work your way back through the whole path to find the proper long 
	filename.<br>
	Is this f!$#^$@ evil, or what?<br>
	\b NOTE: WinXP (and maybe Win2k?) get it right immediately, though
	\b NOTE: This pretty much does what GetFullPathName() <i>should</i> 
	do, but doesn't.
	\param path. Absolute path.
*/
#define path_getting_rid_of_those_braindead_msdos_mangled_short_filenames_the_fucking_hard_way_because_theres_no_alternative \
	path_get_longname

char *path_get_longname(char *dst, const char *path, int size)
{
	// ASSERT(path);
	// ASSERT(dst);
	if(!dst || !path)
		return NULL;


	// file is short
	WIN32_FIND_DATA fd;
	if( ::FindFirstFile(path, &fd) == INVALID_HANDLE_VALUE )
		return NULL;
	
	// pathbuf: short directory name, to be modified at our convenience
	// fullbuf: full filename, to be copied to dst later
	char pathbuf[_MAX_PATH], fullbuf[_MAX_PATH];
	char *ppb = pathbuf, *pfb = fullbuf, *pc;

	strcpy(pathbuf, path);
	*pfb = '\0';

	// One
	// directory 
	// level
	// at 
	// a 
	// time.
	// It's absolutely insane, but the only way :(
	while(pc = strchr(ppb, DIR_SEP))
	{
		*pc = '\0';
		// fd.cFileName is always the last part of a path
		//   or bogus 
		if(::FindFirstFile(pathbuf, &fd) == INVALID_HANDLE_VALUE)
			strcpy(pfb, ppb);
		else
			strcpy(pfb, fd.cFileName);
		*pc = DIR_SEP;
		ppb = pc+1;

		pfb += strlen(pfb);
		*pfb++ = DIR_SEP;
		*pfb = '\0';
		
	}
	// That was the directory part, now finish with the filename
	::FindFirstFile(pathbuf, &fd);
	strcpy(pfb, fd.cFileName);
	fullbuf[size]='\0';	// Honor thy dst boundary

	return strcpy(dst, fullbuf);
}

#endif	// _WIN32


// --------------------------------------------------------------------
// STRING FUNCTIONS
// --------------------------------------------------------------------


//! Replace the string \a *dst with copy of \a src; FREES \a *dst !
char *strrepl(char **dst, const char *src)
{
	char *str = NULL;
	
	// clean dst
	str = src ? strdup(src) : (char*)calloc(1,1);
	if(dst)
	{
		free(*dst);
		*dst = str;
	}

	return str;
}

//! Trim the whitespace from a string
/*! \param dst	Buffer to hold the trimmed string
*	\param src	Source string
*	\return		Pointer to destination string.
*/
char *strtrim(char *dst, const char *src)
{	
	if(src ==NULL || dst == NULL)
		return NULL;

	const char *p1 = src;
	const char *p2 = src + strlen(src)-1;

	while(p1 <= p2 && isspace(*p1))
		p1++;

	if(p1 < p2)
	{
		while(isspace(*p2))
			p2--;

		int len = p2-p1+1;
		strncpy(dst, p1, len);
		dst[len]= '\0';
	}
	else
		*dst = '\0';

	return dst;
}


//! Create a valid C name. 
/*! 
	That means alphanum or '_' only; starting with a letter.
*/
char *str_fix_ident(char *dst, const char *src, int size)
{
	if(src ==NULL || dst ==NULL)
		return NULL;

	// ASSERT(path);
	// ASSERT(dst);
	int ii = 0, c;

	//path = path_get_name(path);	// only use name part
	if(!isalpha(src[ii]))			// must start with alpha
		dst[ii++]= '_';

	while( (c = src[ii])!='\0' && ii<size)
	{
		if(!(isalpha(c) || isdigit(c) || c == '_'))
			c = '_';
		dst[ii++]= c;
	}
	dst[ii++]= '\0';
	return dst;
}


#ifndef _WIN32

char *strupr(char *str)
{
	if(str ==NULL)
		return NULL;

	char *ptr;

	for(ptr = str; *ptr; ptr++)
		*ptr = toupper(*ptr);
	return str;
}

#endif // _WIN32


// --------------------------------------------------------------------
// FILE FUNCTIONS
// --------------------------------------------------------------------


//! Checks whether a file exists
bool file_exists(const char *fpath)
{
	FILE *fp = fopen(fpath, "r");
	if(fp)
	{
		fclose(fp);
		return true;
	}
	else
		return false;
}

//! Get file size in bytes.
long file_size(const char *fpath)
{
	FILE *fp = fopen(fpath, "r");
	if(fp == NULL)
		return 0;

	fseek(fp, 0, SEEK_END);
	
	long pos = ftell(fp);
	fclose(fp);

	return pos;
}

long file_size(FILE *fp)
{
	if(fp ==NULL)
		return 0;

	long tmp = ftell(fp);
	fseek(fp, 0, SEEK_END);
	long pos = ftell(fp);
	fseek(fp, tmp, SEEK_SET);

	return pos;
}


//! Copy \a size unsigned chars from \a fin to \a fout.
/*!	\param fout	Destination file handle.
*	\param fin	Source file handle.
*	\param size	Number of unsigned chars to transfer; for copy till EOF, use 
*	  negative size.
*	\note	Not really sure how this works with text/binary modes
*	  I'm afraid.
*/
long file_copy(FILE *fout, FILE *fin, long size)
{
	char buffy[LINE_MAX];
	int nn;
	long len = 0;	// # unsigned chars actually copied (or chars?)

	if(size >= 0)	// Specific size
	{
		// Cleaner solution is probably possible but, meh
		while(!feof(fin) && size >= LINE_MAX)
		{
			nn = fread(buffy, 1, LINE_MAX, fin);
			fwrite(buffy, 1, nn, fout);
			len += nn;
			size -= LINE_MAX;
		}
		
		if(!feof(fin) && size > 0)
		{
			nn = fread(buffy, 1, size, fin);
			fwrite(buffy, 1, nn, fout);
			len += nn;
		}
	}
	else			// No size given: copy till end
	{
		while(!feof(fin))
		{
			nn = fread(buffy, 1, LINE_MAX, fin);
			fwrite(buffy, 1, nn, fout);
			len += nn;
		}	
	}
	return len;
}

//! Find \a tag at the beginning of a line in a file.
/*! Reads \a fin line for line to find the string \a tag. Optionally, 
*	it copies the preceding lines.
*	\param fout	Destination file for (optional) copy. If NULL, there is no copy.
*	\param fin	Source file for optional copy
*	\param tag	String to find. White space is removed before comparison.
*	\return	Position in \a fin; -1 if not found.
*	\note	\a fin will have skipped \b past the line with \a tag!
*/
long file_find_tag(FILE *fout, FILE *fin, const char *tag)
{
	char buffy[LINE_MAX], line[LINE_MAX];
	long pos;

	buffy[0]= '\0';

	if(fout == NULL)	// Just find
	{
		while(!feof(fin))
		{
			pos = ftell(fin);
			fgets(buffy, LINE_MAX, fin);
			strtrim(line, buffy);
			if(strncmp(line, tag, strlen(tag)) == 0)
				return pos;	
		}		
	}
	else				// Find + copy previous lines
	{
		// NOTE: fgets() fails if EOF is at the start of a line; it
		//   won't even put '\0' in the string. So I'm doing that
		//   myself.
		fgets(buffy, LINE_MAX, fin);
		while(!feof(fin))
		{
			pos = ftell(fin);
			strtrim(line, buffy);
			if(strcmp(line, tag) == 0)
				return pos;

			fputs(buffy, fout);
			buffy[0]= '\0';
			fgets(buffy, LINE_MAX, fin);
		}
		if(buffy[0] != '\0')
		{	fputs(buffy, fout);	fputs("\n", fout);	}
	}
	return -1;
}


//! Write a comment to a file.
/*!	Places \a text behind \a cmt comments, taking 
	newlines into account as well.
	\param fp	File handle.
	\param cmt	Comment symbol.
	\param text	Strong to comment.
	\note	Checks for '\n', but I'm unsure if 
		that's enough for all platforms (Read: '\r' screws up on windows forms).
*/
void file_write_cmt(FILE *fp, const char *cmt, const char *text)
{
	const char *pstart = text, *pend;

	pend = strchr(pstart, '\n');
	while(pend)
	{
		fprintf(fp, "%s ", cmt);

		fwrite(pstart, 1, pend-pstart+1, fp);
		pstart = pend+1;
		pend = strchr(pstart, '\n');
	}

	// Print remaining string, if any
	if(pstart[0] != '\0')
		fprintf(fp, "%s %s\n", cmt, pstart);
}

/*
Berka!
Berka!
Berka!
*/


// --------------------------------------------------------------------
// DATA EXPORT FUNCTIONS
// --------------------------------------------------------------------


//! Exports a single array to a C file
/*!
	\param fp FILE pointer to write to
	\param symname Full array name
	\param data The array data
	\param len The array length in unsigned chars
	\param chunk Datatype size (1,2,4)
*/
bool xp_array_c(FILE *fp, const char *symname, 
	const void *data, int len, int chunk)
{
	if(fp == NULL || symname == NULL || data == NULL || len == 0)
		return false;

	// NOTE: no EOL break
	fprintf(fp, "const unsigned %s %s[%d] __attribute__((aligned(4))) __attribute__((visibility(\"hidden\")))=\n{", 
		cCTypes[chunk], symname, ALIGN4(len)/chunk);
	
	xp_data_c(fp, data, len, chunk);

	fputs("\n};\n\n", fp);
	
	return true;
}


//! Writes comma-separated numbers into a C file.
/*!
	The difference with \c xp_array_c is that this only 
	dumps the the actual data without array adornments. Useful 
	for concatenating arrays.
*/
bool xp_data_c(FILE *fp, const void *_data, int len, int chunk)
{
	int ii, jj, cols;

	switch(chunk)
	{
	case 1:
		cols = 16;	break;
	case 2:
		cols = 8;	break;
	case 4:
		cols = 8;	break;
	default:
		return false;
	}

	len = (len+chunk-1)/chunk;

	len *= chunk;
	cols *= chunk;

	const unsigned char *data = (const unsigned char*)_data;
	for(ii = 0; ii<len; ii += chunk)
	{
		if(ii%cols == 0)				// row start
		{
			if(ii%(cols*8) == 0 && ii != 0)	// extra blank line for clarity
				fputc('\n', fp);
			fputs("\n\t0x", fp);
		}
		else
			fputs("0x", fp);

		// TODO: clean this up
		for(jj = 0; jj<chunk; jj++)		// little-endian, remember?
			fprintf(fp, "%02X", data[ii+chunk-1-jj]);
		fputs(",", fp);
	}
	//ASSERT(fp);

	return true;
}

//! Exports a single array to a GNU assembly file
/*!
	\param fp FILE pointer to write to
	\param symname Full array name
	\param data The array data
	\param len The array length in unsigned chars
	\param chunk Datatype size (1,2,4)
*/
bool xp_array_gas(FILE *fp, const char *symname, 
	const void *data, int len, int chunk)
{
	if(fp == NULL || symname == NULL || data == NULL)
		return false;

	fputs("\t.section .rodata\n\t.align\t2\n", fp);
	// NOTE: no EOL break
	fprintf(fp, "\t.global %s\t\t@ %d unsigned chars\n", 
		symname, ALIGN4(len));
	fprintf(fp, "\t.hidden %s\n%s:", 
		symname,symname);
	
	xp_data_gas(fp, data, len, chunk);

	fputs("\n\n", fp);

	return true;
}

// This one's _almost_ the same as xp_data_c, but that almost prevents
// me from merging them in a nice fashion. If you want to do it, 
// knock yourself out. Just be careful where you put the commas.

//! Writes comma-separated numbers into a GNU Assembly file.
bool xp_data_gas(FILE *fp, const void *_data, int len, int chunk)
{
	int ii, jj, cols;

	switch(chunk)
	{
	case 1:
		cols = 16;	break;
	case 2:
		cols = 8;	break;
	case 4:
		cols = 8;	break;
	default:
		return false;
	}

	len = (len+chunk-1)/chunk;

	len *= chunk;
	cols *= chunk;

	const unsigned char *data = (const unsigned char*)_data;
	for(ii = 0; ii<len; ii += chunk)
	{
		if(ii%cols == 0)				// row start
		{
			if(ii%(cols*8) == 0 && ii != 0)	// extra blank line for clarity
				fputc('\n', fp);
			fprintf(fp, "\n\t%s 0x", cGasTypes[chunk]);
		}
		else
			fputs(",0x", fp);

		// TODO: clean this up
		for(jj = 0; jj<chunk; jj++)		// little-endian, remember?
			fprintf(fp, "%02X", data[ii+chunk-1-jj]);
	}
	// ASSERT(fp);

	return true;
}

//! Reads comma-separated numbers from a GNU Assembly file (written previously).
bool im_data_gas(FILE* fp, const char* name, const void *_data, int *len, int *chunk)
{
    bool retval = false;
    int done = 0;
    char read[256];
    char search[256];
    int cols = 0;
    int _len = 0;
    int _chunk = 0;
    unsigned char *data = (unsigned char*)_data;

    while(!retval)
    {
        int r = fscanf(fp, " @{{BLOCK(%[^)])", read);
        if(r == EOF) { return false; } // couldn't find the block
        if(r > 0)
        {
            if(!strcmp(read, name)) retval = true; // found the block
        }
        else
            fgets(read, 256, fp);
    }

    sprintf(search, "%s%s", name, "Pal");
    retval = (file_find_tag(0, fp, search) >= 0);
    while(retval && !done)
    {
        int i;
        if(!fgets(read, 256, fp)) break;

        // trim
        char *tread = read;
        while(isspace(*tread)) tread++;
        for(i = strlen(tread)-1; isspace(tread[i]); tread[i--] = 0);

        if(!*tread) continue; // skip blank
        if(!_chunk) // need to find chunk size
        {
            search[0] = '.';
            search[1] = 0;
            if(sscanf(tread, ".%s 0x", search+1))
            {
                for(i = 0; i<5; i<<=1) {
                    if(!strcmp(search, cGasTypes[i]))
                    {
                        _chunk = i;
                        switch(_chunk)
                        {
                            case 1: cols = 16; break;
                            case 2: cols =  8; break;
                            case 4: cols =  8; break;
                        }
                        *chunk = _chunk;
                    }
                }
            }
            if(!_chunk) return false;
            sprintf(search, "%s 0x%%n", cGasTypes[_chunk]);
        }
        int c = 0;
        sscanf(tread, search, &c);
        if(c<strlen(search)-2) { done = 1; break; }
        tread += c;

        int _col = cols;
        int _data;
        while(_col && *tread && !done )
        {
            for(i = 0; i<_chunk; i+=2)
            {
                sscanf(tread, "%04X", &_data);
                tread+=4;
                *(data++) = (_data >> 7)&0xF8;
                *(data++) = (_data >> 2)&0xF8;
                *(data++) = (_data << 3)&0xF8;
            }
            _col--;
            _len++;
            if(_col)
            {
                int r = 0;
                sscanf(tread, ",0x%n", &r);
                if(r == 3)
                    tread += 3; // eat ",0x"
                else
                    done = 1;
            }
        }
    }
    *len = _len;
    return retval;
}

//! Dumps data into a binary file
/*!
	\param fname File name to write to
	\param data Data to dump
	\param len Length of data in unsigned chars 
	\param fmode Write mode of the datafile (for more flexibility)
*/
bool xp_data_bin(const char *fname, const void *data, int len, const char *fmode)
{
	FILE *fp;
	if(fname ==NULL || data ==NULL || len ==0 || fmode ==NULL)
		return false;

	fp = fopen(fname, fmode);
	if(fp != NULL)
	{
		fwrite(data, 1, len, fp);
		fclose(fp);
		return true;
	}
	return false;
}


// EOF
