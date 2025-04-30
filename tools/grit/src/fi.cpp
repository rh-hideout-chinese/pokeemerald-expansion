//
//! \file fi.cpp
//!  Extra FreeImage stuff
//! \date 20070226 - 20070226
//! \author cearn

#include <stdio.h>

#include "cldib.h"

#include "fi.h"



// ! Initialize FreeImage and related materials
void fiInit()
{
	dib_set_load_proc(cldib_load);
	dib_set_save_proc(cldib_save);
}


FIBITMAP *fi_load(const char *fpath)
{
	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(fpath);

	if( (fif == FIF_UNKNOWN) || !FreeImage_FIFSupportsReading(fif) )
		return NULL;

	return FreeImage_Load(fif, fpath, 0);
}


bool fi_save(FIBITMAP *fi, const char *fpath)
{
	if(fi == NULL)
		return false;

	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(fpath);

	if( (fif == FIF_UNKNOWN) || !FreeImage_FIFSupportsWriting(fif) )
		return false;

	return FreeImage_Save(fif, fi, fpath, 0)==TRUE;
}


// === cldib -> FIBITMAP stuff ===

FIBITMAP *dib2fi(CLDIB *dib)
{
	if(dib == NULL)
		return NULL;

	int dibW = dib_get_width(dib);
	int dibH = dib_get_height(dib);
	int dibB = dib_get_bpp(dib);

	FIBITMAP *fi = FreeImage_Allocate(dibW, dibH, dibB);
	if(fi == NULL)
		return NULL;

	// Copy data
	memcpy(FreeImage_GetBits(fi), dib_get_img(dib), 
		dib_get_size_img(dib));

	// Copy palette
	int nclrs = dib_get_nclrs(dib);
	if(nclrs > 0)
		memcpy(FreeImage_GetPalette(fi), dib_get_pal(dib), nclrs*RGB_SIZE);

	// Flip to bottom-up

	return fi;
}


//! Get the support modes of a FIF
FI_SUPPORT_MODE fiGetSupportModes(FREE_IMAGE_FORMAT fif)
{
	DWORD fsm = 0;

	if( FreeImage_IsPluginEnabled(fif) != TRUE )
		return (FI_SUPPORT_MODE)0;

	if( FreeImage_FIFSupportsReading(fif) )
		fsm |= FIF_MODE_READ;
	if( FreeImage_FIFSupportsWriting(fif) )
		fsm |= FIF_MODE_WRITE;

	int ii, bpps[7]= { 1, 2, 4, 8, 16, 24, 32 };

	for(ii = 0; ii<7; ii++)
	{
		if( FreeImage_FIFSupportsExportBPP(fif, bpps[ii]) )
			fsm |= 1 << (FIF_MODE_EXP_SHIFT+ii);
	}

	return (FI_SUPPORT_MODE)fsm;
}


//! Create a string for use in OpenFileName dialogs
/*!	\param szFilter	Buffer to receive the filters. Must long enough 
*	  (say, 1024 bytes)
*	\param fsm		File must support these flags.
*	\param fifs		List of formats to check for. If NULL, all formats are
*	  considered.
*	\param fif_count	Length of fifs array.
*	\note	This function is based on the one from the FreeImage 
*	  documentation. If you don't like it, take it up with them :P
*/
int fiFillOfnFilter(char *szFilter, FI_SUPPORT_MODE fsm, 
	FREE_IMAGE_FORMAT *fifs, int fif_count)
{
	int ii, jj = 0, count = FreeImage_GetFIFCount();

	// make internal fif list
	int *fiflist = (int*)malloc(count*sizeof(int));
	FREE_IMAGE_FORMAT fif;

	// Check with fsm
	if(fifs == NULL)
	{
		for(ii = 0; ii<count; ii++)
		{
			if( fiGetSupportModes((FREE_IMAGE_FORMAT)ii) & fsm )
				fiflist[jj++]= ii;
		}
	}
	else 
	{
		count = MIN(count, fif_count);
		for(ii = 0; ii<count; ii++)
		{
			if( fiGetSupportModes(fifs[ii]) & fsm )
				fiflist[jj++]= fifs[ii];				
		}
	}

	// fif_count: number of unique FIFs
	// count: number of filters (can be fif_count+1 
	//   due to 'all supported' list)
	count = jj;
	fif_count = count>1 ? count+1 : count;

	char filter[1024], str[64], *token;
	filter[0]= '\0';

	// Prepare 'all supported' filter if there are multiple
	// filters
	if(count > 1)
	{
		for(ii = 0; ii<count; ii++)
		{
			fif = (FREE_IMAGE_FORMAT)fiflist[ii];
			strcat(filter, FreeImage_GetFIFExtensionList(fif));
			strcat(filter, ",");
		}
		filter[strlen(filter)-1]= '\0';

		strcpy(szFilter, "Supported image files |");
		token = strtok(filter, ",");
		while(token != NULL) 
		{
			sprintf(str, "*.%s;", token);
			strcat(szFilter, str);
			// get next token
			token = strtok(NULL, ",");
		}
		szFilter[strlen(szFilter)-1] = '|';
	}

	// Create filter strings with selected fifs
	for(ii = 0; ii<count; ii++)
	{
		fif = (FREE_IMAGE_FORMAT)fiflist[ii];
		// Description
		sprintf(filter, "%s (%s)|", 
			FreeImage_GetFIFDescription(fif),
			FreeImage_GetFIFExtensionList(fif));

		strcat(szFilter, filter);

		// Extension(s)
		strcpy(filter, FreeImage_GetFIFExtensionList(fif));
		token = strtok(filter, ",");
		while(token != NULL) 
		{
			sprintf(str, "*.%s;", token);
			strcat(szFilter, str);
			// get next token
			token = strtok(NULL, ",");
		}
		szFilter[strlen(szFilter)-1] = '|';
	}
	strcat(szFilter, "|");

	// Free internal list
	free(fiflist);

	return fif_count;
}


// --------------------------------------------------------------------
// FREEIMAGE - CLDIB WRAPPERS
// --------------------------------------------------------------------


CLDIB *fi2dib(FIBITMAP *fi)
{
	if(fi == NULL)
		return NULL;

	int fiW = FreeImage_GetWidth(fi);
	int fiH = FreeImage_GetHeight(fi);
	int fiB = FreeImage_GetBPP(fi);
	BYTE *fiD = FreeImage_GetBits(fi);

	CLDIB *dib = dib_alloc(fiW, fiH, fiB, fiD);
	if(dib == NULL)
		return NULL;

	// Copy palette
	int nclrs = FreeImage_GetColorsUsed(fi);
	if(nclrs > 0)
		memcpy(dib_get_pal(dib), FreeImage_GetPalette(fi), nclrs*RGB_SIZE);

	// flip for top down
	dib_vflip(dib);

	return dib;
}

//! Loads an image
/*!	\param fpath	Full path of image file
*	\return	Valid CLDIB, or NULL on failure
*/
CLDIB *cldib_load(const char *fpath, void *extra)
{
	FIBITMAP *fi = fi_load(fpath);

	if(fi == NULL)
		return NULL;

	CLDIB *dib = fi2dib(fi);
	FreeImage_Unload(fi);

	return dib;
}

bool cldib_save(const CLDIB *dib, const char *fpath, void *extra)
{
	FIBITMAP *fi = dib2fi((CLDIB*)dib);

	if(fi == NULL)
		return false;

	FreeImage_FlipVertical(fi);

	bool res = fi_save(fi, fpath);
	FreeImage_Unload(fi);

	return res;	
}

// EOF
