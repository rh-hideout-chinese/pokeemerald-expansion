//
//
//

#include <stdio.h>

#include "cldib_core.h"
#include "cldib_files.h"

#define BMP_TYPE 0x4D42

enum eBmpErrs
{
	ERR_BMP_PLANES,
	ERR_BMP_CPRS,
	ERR_BMP_MAX
};

const char *CBmpFile::sMsgs[]= 
{
	"Multiple bitplanes are unsupported",
	"BMP compression unsupported"
};

CBmpFile &CBmpFile::operator = (const CBmpFile &rhs)
{
	if(this == &rhs)
		return *this;

	CImgFile::operator = (rhs);

	return *this;
}

// === LOADER =========================================================

// Yes, you can use LoadImage too, but that creates a device 
// dependent bitmap and you want to stay the fsck away from those.
bool CBmpFile::Load(const char *fpath)
{
	FILE *fp = fopen(fpath, "rb");
	CLDIB *dib = NULL;

	try
	{
		if(!fp)
			throw CImgFile::sMsgs[ERR_NO_FILE];

		BITMAPFILEHEADER bmfh;
		fread(&bmfh,  sizeof(BITMAPFILEHEADER), 1,fp);

		// Whoa, not a bitmap, back off
		if(bmfh.bfType != BMP_TYPE)	// 4D42h = "BM". 
			throw CImgFile::sMsgs[ERR_FORMAT];

		BITMAPINFOHEADER bmih;
		bool bCore;

		// check for bm version first :(
		fread(&bmih, 4, 1, fp);
		if(bmih.biSize == sizeof(BITMAPCOREHEADER))		// crap! v2.x BMP
		{
			bCore = true;
			bmih.biSize = BMIH_SIZE; 
			WORD wd;
			fread(&wd, 2,1,fp);
			bmih.biWidth = wd;
			fread(&wd, 2,1,fp);
			bmih.biHeight = wd;
			fread(&bmih.biPlanes, 2,1,fp);
			fread(&bmih.biBitCount, 2,1,fp);
			memset(&bmih.biCompression, 0, 
				BMIH_SIZE-sizeof(BITMAPCOREHEADER));
		}
		else		// normal v3.0 BMP
			fread(&bmih.biWidth, BMIH_SIZE-4, 1, fp);

		if(bmih.biPlanes > 1)				// no color planes, plz
			throw sMsgs[ERR_BMP_PLANES];
		if(bmih.biCompression != BI_RGB)	// no compression either
			throw sMsgs[ERR_BMP_CPRS];

		int dibP, dibHa, dibS;

		dibHa = abs(bmih.biHeight);
		dibP = dib_align(bmih.biWidth, bmih.biBitCount);
		dibS = dibP*dibHa;
		// set manually, just to be sure
		bmih.biSizeImage = dibS;

		// ditto for ClrUsed
		if(bmih.biBitCount <=8 && bmih.biClrUsed == 0)
			bmih.biClrUsed = 1 << bmih.biBitCount;

		// now we set-up the full bitmap
		dib = dib_alloc(bmih.biWidth, dibHa, bmih.biBitCount, NULL, true);
		if(dib == NULL)
			throw CImgFile::sMsgs[ERR_ALLOC];

		// read the palette
		fread(dib_get_pal(dib), RGB_SIZE, bmih.biClrUsed, fp);

		// read image
		fread(dib_get_img(dib), dibS, 1, fp);
		if(bmih.biHeight>=0)	// -> TD image
			dib_vflip(dib);

	}	// </try>
	catch(const char *msg)
	{
		SetMsg(msg);
		dib_free(dib);
		dib = NULL;
	}
	if(fp)
		fclose(fp);
	if(!dib)
		return false;

	// if we're here we've succeeded
	SetMsg(CImgFile::sMsgs[ERR_NONE]);
	dib_free(Attach(dib));

	SetBpp(dib_get_bpp(dib));
	SetPath(fpath);

	return true;
}

bool CBmpFile::Save(const char *fpath)
{
	FILE *fp = NULL;
	bool bOK = true;;

	try
	{
		if(!mDib)
			throw CImgFile::sMsgs[ERR_GENERAL];

		fp = fopen(fpath, "wb");
		if(!fp)
			throw CImgFile::sMsgs[ERR_NO_FILE];

		BITMAPINFOHEADER bmih = *dib_get_hdr(mDib);
		int dibH = dib_get_height2(mDib), dibHa = dib_get_height(mDib);
		int dibP = dib_get_pitch(mDib), dibPa = dibP;
		int dibS = dibHa*dibPa, nclrs = dib_get_nclrs(mDib);

		bmih.biHeight = dibHa;
		bmih.biSizeImage = dibS;

		// fill in fileheader
		BITMAPFILEHEADER bmfh;
		bmfh.bfType = BMP_TYPE;
		bmfh.bfOffBits = sizeof(BITMAPFILEHEADER)+BMIH_SIZE+nclrs*RGB_SIZE;
		bmfh.bfSize = bmfh.bfOffBits + dibS;
		bmfh.bfReserved1 = bmfh.bfReserved2 = 0;

		// write down header
		fwrite(&bmfh, sizeof(BITMAPFILEHEADER), 1, fp);
		fwrite(&bmih, BMIH_SIZE, 1, fp);
		// write down palette
		fwrite(dib_get_pal(mDib), RGB_SIZE, nclrs, fp);

		// write down rows, with possible flipping
		BYTE *dibL = dib_get_img(mDib);
		if(dibH<0)
		{
			dibL += (dibHa-1)*dibPa;
			dibP = -dibP;
		}
		for(int iy = 0; iy<dibHa; iy++)
			fwrite(dibL+iy*dibP, dibPa, 1, fp);
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
