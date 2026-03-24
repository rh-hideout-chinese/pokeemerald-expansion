//
// cldib_pcx.cpp: pcx support
//

#include <stdio.h>

#include "cldib_core.h"
#include "cldib_files.h"

#define PCX_TYPE 0x0a

enum ePcxErrs
{
	ERR_PCX_PLANES,
	ERR_PCX_MAX
};

const char *CPcxFile::sMsgs[]= 
{
	"Problem with bitplanes"
};

//WTF?!? PCX uses a different kind of triple then the Windows triple!
typedef struct tagPCXRGBTRIPLE
{
	BYTE red;
	BYTE green;
	BYTE blue;
} PCXRGBTRIPLE;

typedef struct tagPCXHDR {
	BYTE	type;				// PCX tag ; 10 == ZSoft
	BYTE	version;			// 0 = Paintbrush 2.5
								// 2 = 2.8 with palette
								// 3 = 2.8 without palette
								// 4 = PC Paintbrush for Windows
								// 5 = Version 3.0+ and Publishers Paintbrush
	BYTE	encode;				// 1 = PCX RLE
	BYTE	bpp;				// 1, 2, 4, or 8
	WORD	minX;				// Window dimensions
	WORD	minY;
	WORD	maxX;
	WORD	maxY;
	WORD	horzDpi;			// Horizontal dots per inch
	WORD	vertDpi;			// Vertical dots per inch
	PCXRGBTRIPLE pal1[16];		// palette
	BYTE	junk;
	BYTE	planes;				// number of color planes
	WORD	bytesPerLine;		// number of bytes per scanline per plane! (even)
	WORD	paltype;			// 1 = Color, 2 = GrayScale
	WORD	hScreenSize;		// Horizontal Screen Size
	WORD	vScreenSize;		// Vertical Screen Size
	BYTE	filler[54];
} PCXHDR;

#define PCX_ALIGN 16

// do NOT convert these into #defines!!!
static const BYTE PCX_RLEFLAG = 0xc0;
static const BYTE PCX_RLEMAX =  0x3f;

// default 16 color VGA palette
static const PCXRGBTRIPLE VGADefPal[16] = {
	{   0,   0,   0 },
	{   0,   0, 255 },
	{   0, 255,   0 },
	{   0, 255, 255 },
	{ 255,   0,   0 },
	{ 255,   0, 255 },
	{ 255, 255,   0 },
	{ 255, 255, 255 },
	{  85,  85, 255 },
	{  85,  85,  85 },
	{   0, 170,   0 },
	{ 170,   0,   0 },
	{  85, 255, 255 },
	{ 255,  85, 255 },
	{ 255, 255,  85 },
	{ 255, 255, 255 }
};

static int pcx_readline(BYTE *src, BYTE *dest, int width);
static int pcx_writeline(BYTE *src, BYTE *dest, int width);


CPcxFile &CPcxFile::operator = (const CPcxFile &rhs)
{
	if(this == &rhs)
		return *this;

	CImgFile::operator = (rhs);
	mbGray = rhs.mbGray;

	return *this;
}
// === LOADER =========================================================

// Reads 1, 4 or 8 bit PCXs
// Assumes RLE encoding. Always.
// (Of course, there's very little difference if it's not encoded)
bool CPcxFile::Load(const char *fpath)
{
	FILE *fp = fopen(fpath, "rb");
	CLDIB *dib = NULL;
	PCXHDR hdr;

	try
	{
		if(!fp)
			throw CImgFile::sMsgs[ERR_NO_FILE];

		fread(&hdr, sizeof(PCXHDR), 1, fp);
		if(hdr.type != PCX_TYPE)
			throw CImgFile::sMsgs[ERR_FORMAT];

		int imgB, ncolors;
		imgB = hdr.bpp*hdr.planes;

		// possibilities are: 1, 4, 8, 24 bpp, right?
		ncolors = (imgB>8 ? 0 : 1 << imgB);

		// get dimensions
		int imgW, imgH, imgP, imgS;
		imgW = hdr.maxX - hdr.minX + 1;
		imgH = hdr.maxY - hdr.minY + 1;
		imgP = dib_align(imgW, imgB);
		imgS = imgH*imgP;

		// now we set-up the full bitmap
		dib = dib_alloc(imgW, imgH, imgB, NULL, true);
		if(dib == NULL)
			throw CImgFile::sMsgs[ERR_ALLOC];

		PCXRGBTRIPLE *rgbt;
		RGBQUAD *pal = dib_get_pal(dib);
		int ii, ch;

		// get palette, if any
		switch(imgB)
		{
		case 1:
			((COLORREF*)pal)[0]= 0x000000;
			((COLORREF*)pal)[1]= 0xFFFFFF;
			break;
		case 4:
			rgbt = hdr.pal1;
			for(ii = 0; ii<16; ii++)
			{
				pal[ii].rgbRed   = rgbt[ii].red;
				pal[ii].rgbGreen = rgbt[ii].green;
				pal[ii].rgbBlue  = rgbt[ii].blue;
				pal[ii].rgbReserved = 0;
			}
			break;
		case 8:
			ch = 0;
			fseek(fp, 0, SEEK_END);
			if(ftell(fp) > 0x301 + sizeof(PCXHDR))
			{
				fseek(fp, -0x301, SEEK_END);
				ch = fgetc(fp);
			}
			if(ch == 0x0C)	// we have a palette!
			{
				rgbt = (PCXRGBTRIPLE*)malloc(256*3);
				fread(rgbt, sizeof(PCXRGBTRIPLE), 256, fp);
				for(ii = 0; ii<256; ii++)
				{
					pal[ii].rgbRed   = rgbt[ii].red;
					pal[ii].rgbGreen = rgbt[ii].green;
					pal[ii].rgbBlue  = rgbt[ii].blue;
					pal[ii].rgbReserved = 0;
				}
				free(rgbt);
			}
			else if(hdr.paltype == 2)	// gray scale
			{
				COLORREF *clr = (COLORREF*)pal;
				for(ii = 0x000000; ii<=0xFFFFFF; ii += 0x010101)
					*clr++= ii;
			}
			break;
		} // </switch(imgB)>

		// Get the _whole_ pcx image, then parse
		BYTE *pcxD, *pcxL, *imgL, *planeD, *planeL;
		int ix, iy, pcxS, lineS;

		fseek(fp, 0, SEEK_END);
		pcxS = ftell(fp)-sizeof(PCXHDR);
		pcxL = pcxD = (BYTE*)malloc(pcxS);
		imgL = dib_get_img(dib);
		lineS = hdr.bytesPerLine*hdr.planes;

		fseek(fp, sizeof(PCXHDR), SEEK_SET);
		fread(pcxD, pcxS, 1, fp);

		switch(imgB)
		{
		case 1: case 8:	// 1&8bpp; 1 plane. Easy
			for(iy = 0; iy<imgH; iy++)
			{
				pcxL += pcx_readline(pcxL, imgL, lineS);
				imgL += imgP;
			}
			break;
		case 4:		// 4 planes, 1 bit each. Quite horrid
			planeD = (BYTE*)malloc(lineS);
			// We're ORring, must zero out data first.
			memset(imgL, 0, imgS);
			
			for(iy = 0; iy<imgH; iy++)
			{
				pcxL += pcx_readline(pcxL, planeD, lineS);
				planeL = planeD;

				// This is a bitunpack + de-interlace
				// Bit b of the pixel ix is at plane b, 
				//   byte ix >> 3, bit 7-(ix&7) (bit-big)
				for(ii = 1; ii<16; ii <<= 1)	// ii, aka 1 << p
				{
					for(ix = 0; ix<imgW; ix++)
						if( (planeL[ix >> 3] >> (~ix&7)) & 1 )
							imgL[ix >> 1] |= ii << (4*(~ix&1));
					planeL += hdr.bytesPerLine;
				}
				imgL += imgP;
			}
			free(planeD);
			break;
		case 24:	// 3 planes, one byte each
			planeD = (BYTE*)malloc(lineS);
			for(iy = 0; iy<imgH; iy++)
			{
				pcxL += pcx_readline(pcxL, planeD, lineS);
				planeL = planeD;
				for(ii = 2; ii>=0; ii--)	// PCX uses BGR, so counting down
				{
					for(ix = 0; ix<imgW; ix++)
						imgL[ix*3+ii]= planeL[ix];
					planeL += hdr.bytesPerLine;
				}
				imgL += imgP;
			}
			free(planeD);
			break;
		default:	// sorry, that's all folks
			free(pcxD);
			throw CImgFile::sMsgs[ERR_BPP];
		} // </switch(imgB)>
		free(pcxD);

		// here we go
	} // </try>
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
	mbGray = (hdr.paltype ==2);
	SetPath(fpath);

	return true;
}

bool CPcxFile::Save(const char *fpath)
{
	FILE *fp = NULL;
	bool bOK = true;;

	try
	{
		if(!mDib)
			throw CImgFile::sMsgs[ERR_GENERAL];
		int imgB = dib_get_bpp(mDib);

		fp = fopen(fpath, "wb");
		if(!fp)
			throw CImgFile::sMsgs[ERR_NO_FILE];

		if(imgB != 1 && imgB != 4 && imgB != 8 && imgB != 24)
			throw CImgFile::sMsgs[ERR_BPP];

		int imgW = dib_get_width(mDib);
		int imgH = dib_get_height(mDib), imgHs = dib_get_height2(mDib);
		int imgP = dib_get_pitch(mDib);
		int imgS = imgH*imgP, nclrs = dib_get_nclrs(mDib);

		BYTE *imgL = dib_get_img(mDib);
		// switch the bastard if bottom-up
		if(imgHs>0)
		{
			imgL += (imgH-1)*imgP;
			imgP = -imgP;
		}

		// fill in PCX header. 
		PCXHDR hdr;
		memset(&hdr, 0, sizeof(PCXHDR));
		hdr.type = PCX_TYPE;
		hdr.version = 5;
		hdr.encode = 1;
		//hdr.bpp = bpp;			// later
		//hdr.minX = 0;
		//hdr.minY = 0;
		hdr.maxX = imgW-1;
		hdr.maxY = imgH-1;
		// hdpi, vdpi
		memcpy(hdr.pal1, VGADefPal, 16*3);
		// junk
		//hdr.planes = 1;		// later
		hdr.paltype = (mbGray ? 2 : 1);
		// make good use of filler :)
		memcpy(hdr.filler,
			"     If you're reading this, you must be a geek :)    ", 54);
		// encode and write image bytes
		int ii, ix, iy, count;
		BYTE *pcxD = NULL, *planeD = NULL, *planeL;
		int pcxP;
		PCXRGBTRIPLE rgbt;
		RGBQUAD *pal;

		switch(imgB)
		{
		case 1: case 8:
			// rest of header
			pcxP = (imgW*imgB+15)/16*2;
			hdr.bpp = imgB;
			hdr.planes = 1;
			hdr.bytesPerLine = pcxP;
			fwrite(&hdr, sizeof(PCXHDR), 1, fp);

			// compress & write data
			pcxD = (BYTE*)malloc(2*pcxP);	// x2 for worst case scenario
			for(iy = 0; iy<imgH; iy++)
			{
				count = pcx_writeline(imgL, pcxD, pcxP);
				imgL += imgP;
				fwrite(pcxD, count, 1, fp);
			}

			// write extra palette
			if(imgB == 8 && !mbGray)
			{
				fputc(0x0C, fp);
				pal = dib_get_pal(mDib);
				for(int ii = 0; ii<256; ii++)
				{
					rgbt.red   = pal[ii].rgbRed;
					rgbt.green = pal[ii].rgbGreen;
					rgbt.blue  = pal[ii].rgbBlue;
					fwrite(&rgbt, 3, 1, fp);
				}
			}
			break;
		case 4:
			// rest of header
			hdr.bpp = 1;
			hdr.planes = 4;
			hdr.bytesPerLine = (imgW+15)/16*2;
			// palette:
			pal = dib_get_pal(mDib);
			for(ii = 0; ii<16; ii++)
			{
				hdr.pal1[ii].red	= pal[ii].rgbRed;
				hdr.pal1[ii].green	= pal[ii].rgbGreen;
				hdr.pal1[ii].blue	= pal[ii].rgbBlue;
			}
			fwrite(&hdr, sizeof(PCXHDR), 1, fp);

			// compress & write data
			pcxP = hdr.bytesPerLine * 4;
			planeD = (BYTE*)malloc(pcxP);	// plane buffer
			pcxD = (BYTE*)malloc(2*pcxP);	// line buffer

			for(iy = 0; iy<imgH; iy++)
			{
				memset(planeD, 0, pcxP);
				planeL = planeD;				
				for(ii = 1; ii<16; ii <<= 1)	// build the actual line
				{
					for(ix = 0; ix<imgW; ix++)
						if( (imgL[ix >> 1] >> (4*(~ix&1))) & ii )
							planeL[ix >> 3] |= 0x80 >> (ix&7);
					planeL += hdr.bytesPerLine;
				}
				
				count = pcx_writeline(planeD, pcxD, pcxP);
				imgL += imgP;
				fwrite(pcxD, count, 1, fp);
			}
			free(planeD);
			break;
		case 24:
			// rest of header
			hdr.bpp = 8;
			hdr.planes = 3;
			hdr.bytesPerLine = (imgW*8+15)/16*2;
			fwrite(&hdr, sizeof(PCXHDR), 1, fp);

			// compress & write data
			pcxP = hdr.bytesPerLine * 3;
			planeD = (BYTE*)malloc(pcxP);	// plane buffer
			pcxD = (BYTE*)malloc(2*pcxP);	// line buffer

			for(iy = 0; iy<imgH; iy++)
			{
				planeL = planeD;
				for(ii = 2; ii>=0; ii--)	// PCX uses BGR, so counting down
				{
					for(ix = 0; ix<imgW; ix++)
						planeL[ix]= imgL[ix*3+ii];
					planeL += hdr.bytesPerLine;
				}
				count = pcx_writeline(planeD, pcxD, pcxP);
				imgL += imgP;
				fwrite(pcxD, count, 1, fp);
			}
			free(planeD);
			break;
		}
		free(pcxD);
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

// --- RLE encoding ---
// If the PCX follows the specs then this _should_ work. But it has 
// very little (as in none) in the way of safety checks 
static int pcx_readline(BYTE *src, BYTE *dest, int width)
{
	BYTE ch, *buf = src;
	int ii, count = 0;
	for(ii = 0; ii<width; ii += count)
	{
		ch = *buf++;
		if( (ch&PCX_RLEFLAG) == PCX_RLEFLAG )
		{
			count = ch & PCX_RLEMAX;
			ch = *buf++;
			memset(dest+ii, ch, count);
		}
		else
		{	count = 1;
			dest[ii]= ch;
		}				
	}
	return buf-src;	// #bytes converted
}

static int pcx_writeline(BYTE *src, BYTE *dest, int width)
{
	BYTE curr, prev, *buf = dest;
	int ix, count = 1;
	prev = *src;
	for(ix = 1; ix<width; ix++)
	{
		curr = src[ix];
		// continue sequence
		if(curr == prev && count<PCX_RLEMAX)
		{	count++;	}
		else	// sequence finished, write down and re-init count
		{
			// write RLE length
			if(count>1 || (prev & PCX_RLEFLAG) == PCX_RLEFLAG)
				*buf++ = BYTE(PCX_RLEFLAG|count);
			// write clr_id
			*buf++ = prev;
			prev = curr;
			count = 1;
		}
	}
	// extra for end of line
	if(count>1 || (prev & PCX_RLEFLAG) == PCX_RLEFLAG)
		*buf++ = BYTE(PCX_RLEFLAG|count);
	*buf++ =  prev;
	return buf-dest;	// #bytes converted
}

// EOF
