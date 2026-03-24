//
// pathfun.h
//   pathfun header file
// (20050903 - 20061121, cearn)
//
/* === NOTES === 
  * 20080211, jv: TODO: split this into path-only and data-only files.
*/

#ifndef __PATHFUN_H__
#define __PATHFUN_H__

#include <stdio.h>

/*! \addtogroup grpPath
*	\{	*/

// --------------------------------------------------------------------
// CONSTANTS
// --------------------------------------------------------------------


#define DIR_SEP_WIN  '\\'
#define VOL_SEP_WIN  ':'

#define DIR_SEP_UNIX '/'
#define VOL_SEP_UNIX '\0'

#ifdef _WIN32
	#define DIR_SEP DIR_SEP_WIN
	#define VOL_SEP VOL_SEP_WIN
#else
	#define DIR_SEP DIR_SEP_UNIX
	#define VOL_SEP VOL_SEP_UNIX
#endif

#ifndef LINE_MAX
#define LINE_MAX	1024
#endif

extern const char cTypeSpec[];
extern const char *cCTypes[];
extern const char *cGasTypes[];


// --------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------

// === Path routines ==================================================

// --- Base path components ---
int path_get_vol(const char *path);
char *path_get_dir(char *dst, const char *path, int size);
char *path_get_title(char *dst, const char *path, int size);
char *path_get_ext(const char *path);

// --- Extra components ---

char *path_get_name(const char *path);
char *path_get_xext(const char *path);
char *path_get_xtitle(char *dst, const char *path, int size);

// --- Separators ---
void path_add_dir_sep(char *path);
char *path_fix_sep(char *path);

//char *path_canon(char *dst, const char *path, int size);

char *path_get_longname(char *dst, const char *path, int size);

// --- Replacers ---

char *path_repl_ext(char *dst, const char *path, const char *ext, int size);


// === Useful string routines =========================================

inline int isempty(const char *str);

char *strrepl(char **dst, const char *src);
char *strtrim(char *dst, const char *src);

char *str_fix_ident(char *dst, const char *str, int size);

#ifndef _WIN32
char *strupr(char *str);
#endif

// === File routines ==================================================

bool file_exists(const char *fpath);
long file_size(const char *fpath);
long file_size(FILE *fp);

long file_copy(FILE *fout, FILE *fin, long size);
long file_find_tag(FILE *fout, FILE *fin, const char *tag);

void file_write_cmt(FILE *fp, const char *cmt, const char *text);


/*!	\}	*/


// === Data exporters =================================================

/*! \addtogroup grpData
*!	\{	*/

bool xp_array_c(FILE *fp, const char *symname, 
	const void *data, int len, int chunk);
bool xp_data_c(FILE *fp, const void *data, int len, int chunk);

bool xp_array_gas(FILE *fp, const char *symname, 
	const void *data, int len, int chunk);
bool xp_data_gas(FILE *fp, const void *data, int len, int chunk);
bool im_data_gas(FILE* fp, const char *name, const void *_data, int *len, int *chunk);

bool xp_data_bin(const char *fname, 
	const void *data, int len, const char *fmode);

/*!	\}	*/


// --------------------------------------------------------------------
// MACROS
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// INLINES
// --------------------------------------------------------------------


//! Check if string \a str is empty
inline int isempty(const char *str)
{	return (str ==NULL || str[0]=='\0');						}


#endif // __PATHFUN_H__

// EOF
