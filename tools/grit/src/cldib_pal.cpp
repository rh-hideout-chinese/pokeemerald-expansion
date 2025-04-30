//
// cldib_pal.cpp: palette files
//

#include <stdio.h>

#include "cldib_core.h"
#include "cldib_files.h"

enum ePalErrs
{
	ERR_PAL_BPS,
	ERR_PAL_NOPAL,
	ERR_PAL_MAX
};

const char *CPalFile::sMsgs[]= 
{
	"Invalid number of bits per shade",
	"No palette data"
};

CPalFile::CPalFile() : CImgFile()
{
	memset(mType, 0, 8);
}

CPalFile &CPalFile::operator = (const CPalFile &rhs)
{
	if(this == &rhs)
		return *this;

	CImgFile::operator = (rhs);
	memcpy(mType, rhs.mType, 8);

	return *this;
}

// === LOADER =========================================================

bool CPalFile::Load(const char *fpath)
{
	CLDIB *dib = NULL;
	bool bOK = false;
	try
	{
		FILE *fp = fopen(fpath, "rt");
		if(!fp)
			throw CImgFile::sMsgs[ERR_NO_FILE];

		char type[8]= "";
		fread(type, 1, 4, fp);
		fclose(fp);

		// my own pal format
		if(strncmp(type, "CLR", 3) == 0)
			dib = LoadClr(fpath);
		// MS pal
		else if(strncmp(type, "RIFF", 4) == 0)
			dib = LoadRiff(fpath);
		// errr PaintShop Pro?
		else if(strncmp(type, "JASC", 4) == 0)
			dib = LoadJasc(fpath);
		// unknown
		else
			throw CImgFile::sMsgs[ERR_FORMAT];

	} // </try>
	catch(const char *msg)
	{
		SetMsg(msg);
		dib_free(dib);
		dib = NULL;
	}

	if(!dib)
		return false;

	// if we're here we've succeeded
	SetMsg(CImgFile::sMsgs[ERR_NONE]);
	dib_free(Attach(dib));

	SetBpp(dib_get_bpp(dib));
	SetPath(fpath);

	return true;
}

// --- internal loaders ---
// * If we're here, we've already determined the file type, 
//   vis, we know it exists.
// * I thought having a bps would be good idea at the time. Now I'm 
//   ignoring it completely. *shrug*
CLDIB *CPalFile::LoadClr(const char *fpath)
{
	FILE *fp = fopen(fpath, "rt");
	CLDIB *dib = NULL;

	char str[8];
	int bps, nclrs;

	fscanf(fp, "%s %d %d", str, &bps, &nclrs);
	if(nclrs>PAL_MAX)
		nclrs = PAL_MAX;

	// now we set-up the full bitmap
	dib = dib_alloc(1, 1, 8, NULL, true);
	if(dib == NULL)
		throw CImgFile::sMsgs[ERR_ALLOC];

	RGBQUAD *pal = dib_get_pal(dib);
	memset(pal, 0, PAL_MAX*RGB_SIZE);

	int ii;
	COLORREF clr;
	for(ii = 0; ii<nclrs; ii++)
	{
		if(fscanf(fp, "%x", &clr) == EOF)
			break;
		pal[ii]= clr2rgb(clr);
	}
	dib_get_hdr(dib)->biClrUsed = ii;
	fclose(fp);
	return dib;
}

CLDIB *CPalFile::LoadRiff(const char *fpath)
{
	FILE *fp = fopen(fpath, "rb");
	CLDIB *dib = NULL;


	char str[16];
	WORD wd;
	fread(str, 1, 8, fp);	// skip "RIFF" + file size
	fread(str, 1, 8, fp);	// next should be "PAL data"
	if(strncmp(str, "PAL data", 8) != 0)
		throw CImgFile::sMsgs[ERR_FORMAT];
	fread(str, 4, 1, fp);	// skip chunk size
	fread(&wd, 2, 1, fp);	// more palette info (0x0300)
	if(wd != 0x0300)
		throw CImgFile::sMsgs[ERR_FORMAT];

	// now we set-up the full bitmap
	dib = dib_alloc(1, 1, 8, NULL, true);
	if(dib == NULL)
		throw CImgFile::sMsgs[ERR_ALLOC];

	int ii, nclrs = wd;
	if(nclrs>PAL_MAX)
		nclrs = PAL_MAX;

	// now we set-up the full bitmap
	dib = dib_alloc(1, 1, 8, NULL, true);
	if(dib == NULL)
		throw CImgFile::sMsgs[ERR_ALLOC];

	RGBQUAD *pal = dib_get_pal(dib);
	memset(pal, 0, PAL_MAX*RGB_SIZE);

	COLORREF clr;
	for(ii = 0; ii<nclrs; ii++)
	{
		fread(&clr, 4, 1, fp);
		pal[ii]= clr2rgb(clr);
		if(feof(fp))
			break;
	}
	dib_get_hdr(dib)->biClrUsed = ii;
	fclose(fp);
	return dib;
}

CLDIB *CPalFile::LoadJasc(const char *fpath)
{
	FILE *fp = fopen(fpath, "rt");
	CLDIB *dib = NULL;

	char str[16];
	int tmp, nclrs;

	fscanf(fp, "%s %d %d", str, &tmp, &nclrs);

	if(strncmp(str, "JASC-PAL", 8) != 0)
		throw CImgFile::sMsgs[ERR_FORMAT];

	if(nclrs>PAL_MAX)
		nclrs = PAL_MAX;

	// now we set-up the full bitmap
	dib = dib_alloc(1, 1, 8, NULL, true);
	if(dib == NULL)
		throw CImgFile::sMsgs[ERR_ALLOC];

	RGBQUAD *pal = dib_get_pal(dib);
	memset(pal, 0, PAL_MAX*RGB_SIZE);

	int ii, rr, gg, bb;
	for(ii = 0; ii<nclrs; ii++)
	{
		if(fscanf(fp, "%d %d %d", &rr, &gg, &bb) == EOF)
			break;
		pal[ii].rgbRed = rr;
		pal[ii].rgbGreen = gg;
		pal[ii].rgbBlue = bb;
	}
	dib_get_hdr(dib)->biClrUsed = ii;
	fclose(fp);
	return dib;
}

// === SAVER ==========================================================

bool CPalFile::Save(const char *fpath)
{
	FILE *fp = NULL;
	bool bOK = true;

	try
	{
		if(!mDib)
			throw CImgFile::sMsgs[ERR_GENERAL];
		int imgB = dib_get_bpp(mDib);

		fp = fopen(fpath, "wt");
		if(!fp)
			throw CImgFile::sMsgs[ERR_NO_FILE];

		int ii, nclrs = dib_get_nclrs(mDib);
		RGBQUAD *pal = dib_get_pal(mDib);

		fprintf(fp, "CLRX 8 %d\n", nclrs);
		for(ii = 0; ii<nclrs; ii++)
		{
			fprintf(fp, "0x%08x ", rgb2clr(pal[ii]));
			if((ii&3) == 3)
				fputc('\n', fp);
		}
	}
	catch(const char *msg)
	{
		SetMsg(msg);
		bOK = false;
	}

	if(fp)
		fclose(fp);	

	return bOK;
}

// EOF
