//
// CImgBase implementation
//

#include <string.h>

#include "cldib_core.h"
#include "cldib_files.h"

// === GLOBALS ========================================================

const char *CImgFile::sMsgs[]= 
{
	"All clear!", 
	"Non-descript error :(.",
	"Memory allocation error.",
	"File doesn't exist.",
	"General Error reading disk.",
	"Ack! File format not recognized.",
	"Unsupported bitdepth.", 
	"Too many colors in true color image. "
};

// === METHODS ========================================================

CImgFile &CImgFile::operator = (const CImgFile &rhs)
{
	if(this == &rhs)
		return *this;

	mbActive = rhs.mbActive;
	mpMsg = rhs.mpMsg;
	dib_free(mDib);
	mDib = dib_clone(rhs.mDib);
	mBpp = rhs.mBpp;
	SetPath(rhs.mPath);

	return *this;
}

void CImgFile::Clear() 
{
	dib_free(mDib);
	mDib = NULL;
	mBpp = 8;
	SAFE_FREE(mPath);
	mbActive = false;
}

void CImgFile::Destroy()
{
	dib_free(mDib);
	mDib = NULL;	
}

const char *CImgFile::SetMsg(const char *msg)
{
	const char *prev = mpMsg;
	mpMsg = msg;
	return prev;
}

CLDIB *CImgFile::Detach()
{
	CLDIB *dib = mDib;
	mDib = NULL;
	mbActive = false;
	return dib;
}

CLDIB *CImgFile::Attach(CLDIB *dib)
{
	CLDIB *prev = mDib;
	mDib = dib;
	mbActive = dib ? true : false;
	return prev;
}

void CImgFile::SetPath(const char *path)
{
	SAFE_FREE(mPath);
	mPath = strdup(path);
}

// === FUNCTIONS ======================================================

CImgFile *ifl_from_path(CImgFile **list, const char *fpath)
{
	if(fpath == NULL)
		return NULL;
	// find ext
	const char *fext = strrchr(fpath, '.');
	if(fext)
		fext++;
	else
		fext = fpath;

	int ii;
	for(ii = 0; list[ii] != NULL; ii++)
	{
		if(stricmp(fext, list[ii]->GetExt()) == 0)	// found it
			return list[ii];
		else	// not found, could be multiple-ext list
		{
			char *extbuf = strdup(list[ii]->GetExt());
			char *tok = strtok(extbuf, ",");
			while(tok)
			{
				if(stricmp(fext, tok) == 0)
				{	
					free(extbuf);
					return list[ii];
				}
				tok = strtok(NULL, ",");

			}
			free(extbuf);
		}		
	}

	return NULL;
}


// Builds a string of filters for use with the OPENFILENAME struct
// |{desc}({ext}[,{ext}])|*.{ext}[;*.{ext}]|...||
// @str_filter: a preallocated array to hold the string
int ifl_filter_list(CImgFile **list, char *str_filter)
{
	int ii;
	char buf[1024];
	char *pbuf = buf, *pstr = str_filter, *tok;

	// --- an 'all' list ---
	for(ii = 0; list[ii] != NULL; ii++)
		pbuf += sprintf(pbuf, ",%s", list[ii]->GetExt());

	strcpy(pstr, "All supported|");
	pstr += strlen(pstr);

	tok = strtok(&buf[1], ",");
	while(tok != NULL) 
	{
		pstr += sprintf(pstr, "*.%s;", tok);
		tok = strtok(NULL, ",");
	}
	pstr[-1]= '|';	// remove trailing ';'

	// --- separate filters ---
	pbuf = buf;
	for(ii = 0; list[ii] != NULL; ii++)
	{
		pstr += sprintf(pstr, "%s (%s)|", list[ii]->GetDesc(), 
			list[ii]->GetExt());
		strcpy(buf, list[ii]->GetExt());

		tok = strtok(buf, ",");
		while(tok != NULL) 
		{
			pstr += sprintf(pstr, "*.%s;", tok);
			tok = strtok(NULL, ",");
		}
		pstr[-1]= '|';	// remove trailing ';'
	}
	strcat(pstr, "|");

	return ii;
}

// EOF
