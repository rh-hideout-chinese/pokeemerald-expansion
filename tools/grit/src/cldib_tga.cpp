//
// tga.cpp
// Windows TGA (targa) Load and save
// === NOTES ===
// * there's a problem with mono images
// * No RLE at save ... yet

#include <stdio.h>

#include "cldib_core.h"
#include "cldib_files.h"

enum eTgaErrs
{
	ERR_TGA_VERSION,
	ERR_TGA_BADPAL,
	ERR_TGA_PALBPP, 
	ERR_TGA_IMGBPP,
	ERR_TGA_MAX
};

const char *CTgaFile::sMsgs[]=
{
	"Unsupported version (must have palette)",
	"Invalid number of palette entries", 
	"Palette type unsupported",
	"Unknown image type. Plz tell me about it so "
		"I can include it"
};

// === CONSTANTS ======================================================

// TGA types
#define TGA_PAL         1
#define TGA_true        2
#define TGA_BW          3
#define TGA_PAL_RLE     9
#define TGA_true_RLE   10
#define TGA_BW_RLE     11

//#define TGA_HFLIP 0x10
#define TGA_VFLIP 0x20

// === STRUCTURES =====================================================

// <no struct padding>
// otherwise TGAHDR could be bad
#ifdef WIN32
#pragma pack(push, 1)
#else
#pragma pack(1)
#endif

// NOTE! on Win32 sizeof(TGA_PALINFO) is 6, not 5
// due to structure alignment
typedef struct tagTGAHDR
{
	BYTE id_len;
	BYTE has_table;
	BYTE type;
	WORD pal_start;
	WORD pal_len;
	BYTE pal_bpp;
	WORD xorg;
	WORD yorg;
	WORD width;
	WORD height;
	BYTE img_bpp;
	BYTE img_desc;
} TGAHDR;	// == 18b
// TGAHDR.img_desc note:
// I have an inkling that bits 4 and 5 determine the 
// mapping mode for the image, i.e. the sign of the x and y axes
// for now, always use BMP mapping mode

// TGA color structs. Even though Win RGBs are identical
typedef struct tagTGA_BGR
{
	BYTE blue;
	BYTE green;
	BYTE red;
} TGA_BGR;

typedef struct tagTGA_BGRA
{
	BYTE blue;
	BYTE green;
	BYTE red;
	BYTE alpha;
} TGA_BGRA;

// </no struct padding>
#ifdef WIN32
#pragma pack(pop, 1)
#else
#pragma pack()
#endif

// === PROTOTYPES =====================================================

// --- read
static bool tga_read_pal(CLDIB *dib, const TGAHDR *hdr, FILE *fp);
static void tga_unrle(CLDIB *dib, TGAHDR *hdr, FILE *fp);

// === FUNCTIONS ======================================================

CTgaFile &CTgaFile::operator = (const CTgaFile &rhs)
{
	if(this == &rhs)
		return *this;

	CImgFile::operator = (rhs);

	return *this;
}

// xxx_load(const char *fname, PDIBDATA *ppdib, IMG_FMT_INFO *pifi)
bool CTgaFile::Load(const char *fpath)
{
	FILE *fp = fopen(fpath, "rb");
	CLDIB *dib = NULL;
	TGAHDR hdr;

	try
	{
		if(!fp)
			throw CImgFile::sMsgs[ERR_NO_FILE];

		fread(&hdr, sizeof(TGAHDR), 1, fp);

		// ignore image desc (if any)
		fseek(fp, hdr.id_len, SEEK_CUR);

		int imgW, imgH, imgB, imgP;
		imgW = hdr.width;
		imgH = hdr.height;
		imgB = hdr.img_bpp;
		imgP = dib_align(imgW, imgB);

		// Set-up the full bitmap
		dib = dib_alloc(imgW, imgH, imgB, NULL, true);
		if(dib == NULL)
			throw CImgFile::sMsgs[ERR_ALLOC];

		// === get color map ===
		if(hdr.has_table)
		{
			if(!tga_read_pal(dib, &hdr, fp))
				throw sMsgs[ERR_TGA_BADPAL];
		}

		int ii;
		int tgaP = (imgW*imgB+7)/8;
		BYTE *imgD = dib_get_img(dib);

		switch(hdr.type)
		{
		case TGA_BW:
		case TGA_PAL:
		case TGA_true:
			for(ii = 0; ii<imgH; ii++)
				fread(&imgD[ii*imgP], 1, tgaP, fp);
			break;
		case TGA_BW_RLE:
		case TGA_PAL_RLE:
		case TGA_true_RLE:
			tga_unrle(dib, &hdr, fp);
			break;
		default:
			throw sMsgs[ERR_TGA_VERSION];
		}

		// TGA's are bottom-up by default, flip if necessary
		if(~hdr.img_desc & TGA_VFLIP)
			dib_vflip(dib);

	}	// </try>
	catch(const char *msg)
	{
		SetMsg(msg);
		dib_free(dib);
		dib = NULL;
	}
	// cleanup
	if(!dib)
		return false;

	// if we're here we've succeeded
	SetMsg(CImgFile::sMsgs[ERR_NONE]);
	dib_free(Attach(dib));

	SetBpp(dib_get_bpp(dib));
	SetPath(fpath);

	return true;
}


bool CTgaFile::Save(const char *fpath)
{

	int ii, iy;
	FILE *fp = NULL;
	bool bOK = true;

	try
	{
		if(!mDib)
			throw CImgFile::sMsgs[ERR_GENERAL];

		fp = fopen(fpath, "wb");
		if(!fp)
			throw CImgFile::sMsgs[ERR_NO_FILE];

		int imgW = dib_get_width(mDib);
		int imgH = dib_get_height(mDib), imgHs = dib_get_height2(mDib);
		int imgP = dib_get_pitch(mDib);
		int imgB = dib_get_bpp(mDib);
		int imgS = imgH*imgP, nclrs = dib_get_nclrs(mDib);

		TGAHDR hdr;
		memset(&hdr, 0, sizeof(TGAHDR));

		if(imgB ==1)
			hdr.type = TGA_BW;
		else if(imgB <= 8)
			hdr.type = TGA_PAL;
		else
			hdr.type = TGA_true;

		if(imgB<=8)		// paletted
		{
			hdr.has_table = 1;
			hdr.pal_len = dib_get_nclrs(mDib);
			hdr.pal_bpp = 24;
		}
		else			// true color
			hdr.has_table = 0;

		hdr.width = imgW;
		hdr.height = imgH;
		hdr.img_bpp = imgB;
		hdr.img_desc = 0;

		fwrite(&hdr, 1, sizeof(TGAHDR), fp);

		// write palette
		if(imgB <= 8)
		{
			RGBQUAD *pal = dib_get_pal(mDib);
			for(ii = 0; ii<hdr.pal_len; ii++)
				fwrite(&pal[ii], 1, 3, fp);
		}

		// TGA should be bottom up:
		BYTE *imgL = dib_get_img(mDib);
		if(dib_is_topdown(mDib))
		{
			imgL += imgP*(imgH-1);
			imgP = -imgP;
		}

		// write image (not RLEd, because that's awful to do)
		int tgaP = (imgW*imgB+7)/8;
		for(iy = 0; iy<imgH; iy++)
			fwrite(&imgL[iy*imgP], 1, tgaP, fp);
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

// === LOAD HELPERS ===================================================
static bool tga_read_pal(CLDIB *dib, const TGAHDR *hdr, 
	FILE *fp)
{
	// no palette, 's fair
	if(hdr->has_table == 0)
		return true;
	// writer of this file is an idiot
	// PONDER: is pal_len the size of the whole thing, or
	//   counting from pal_start?
	//   I'm assuming the latter
	if(hdr->pal_len <= hdr->pal_start)
		return false;

	int ii;
	int clrS = (hdr->pal_bpp != 15 ? (hdr->pal_bpp/8) : 2);
	int palN = hdr->pal_len, palS = palN*clrS;

	BYTE *palD = (BYTE*)malloc(palN*clrS);
	fread(palD, clrS, palN-hdr->pal_start, fp);

	RGBQUAD *dibPal = dib_get_pal(dib);
	memset(dibPal, 0, dib_get_nclrs(dib)*RGB_SIZE);

	if(palN>dib_get_nclrs(dib))
		palN = dib_get_nclrs(dib);
	
	switch(hdr->pal_bpp)	// damn these different options :(
	{
	case 16:
		for(ii = hdr->pal_start; ii<palN; ii++)
		{
			WORD rgb16 = ((WORD*)palD)[ii];
			dibPal[ii].rgbRed =   ((rgb16 >> 10)&31)*255/31;
			dibPal[ii].rgbGreen = ((rgb16>> 5)&31)*255/31;
			dibPal[ii].rgbBlue =  ((rgb16    )&31)*255/31;
		}
		break;
	case 24:
		for(ii = hdr->pal_start; ii<palN; ii++)
		{
			TGA_BGR rgb24 = ((TGA_BGR*)palD)[ii];
			dibPal[ii].rgbRed =   rgb24.red;
			dibPal[ii].rgbGreen = rgb24.green;
			dibPal[ii].rgbBlue =  rgb24.blue;
		}
		break;
	case 32:
		for(ii = hdr->pal_start; ii<palN; ii++)
		{
			TGA_BGRA rgb32 = ((TGA_BGRA*)palD)[ii];
			dibPal[ii].rgbRed =   rgb32.red;
			dibPal[ii].rgbGreen = rgb32.green;
			dibPal[ii].rgbBlue =  rgb32.blue;
		}
		break;
	default:
		SAFE_FREE(palD);
		return false;
	}

	// clean up
	SAFE_FREE(palD);
	return true;
}

// TGA RLE;
// * lines are byte-aligned
// * RLE can cross lines
// * RLE works by the pixel for true clr, by byte for paletted
// * The RLE header byte, ch:
//   ch{0-6} : # chunks -1
//   ch{7}   : stretch.
void tga_unrle(CLDIB *dib, TGAHDR *hdr, FILE *fp)
{
	int ii, ix, iy;
	int imgW = dib_get_width(dib);
	int imgH = dib_get_height(dib);
	int imgB = dib_get_bpp(dib);
	int imgP = dib_get_pitch(dib);
	BYTE *imgL = dib_get_img(dib), *imgEnd = imgL+imgH*imgP;

	int tgaP = (imgW*imgB+7)/8;	// pseudo pitch
	int tgaN = (imgB+7)/8;		// chunk size
	BYTE ch, chunk[4];

	ix = 0, iy = 0;
	while(1)
	{
		ch = fgetc(fp);
		if(ch>127)			// stretch
		{
			ch -= 127;
			fread(chunk, 1, tgaN, fp);
			while(ch--)
			{
				for(ii = 0; ii<tgaN; ii++)
					imgL[ix+ii]= chunk[ii];
				ix += tgaN;

				if(ix >= tgaP)
				{
					imgL += imgP;
					ix = 0;
					if(imgL >= imgEnd)
						return;
				}
			}
		} // </stretch>
		else				// no stretch
		{
			ch++;
			while(ch--)
			{
				fread(&imgL[ix], 1, tgaN, fp);
				ix += tgaN;
				if(ix >= tgaP)
				{
					imgL += imgP;
					ix = 0;
					if(imgL >= imgEnd)
						return;
				}
			}
		} // </no stretch>
	} // </while(1)>
}

// EOF
