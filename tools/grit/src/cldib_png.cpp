#include <stdio.h>

#include "cldib_core.h"
#include "cldib_files.h"

#include <png.h>


enum ePngErrs
{	
	ERR_PNG_NO_PNG,
	ERR_PNG_NO_INFO,
	ERR_PNG_INVALID, 
	ERR_PNG_BPP_2,
	ERR_PNG_GRAY_ALPHA,
	ERR_PNG_BPP_16,
	ERR_PNG_MAX
};

const char *CPngFile::sMsgs[]= 
{
	"Can't create PNG struct.",
	"Can't create PNG info struct",
	"This ain't a proper PNG",
	"2 bits per pixel unsupported (Why? Because the "
		"programmer of this bitmap editor is to lazy to convert it "
		"to 4bpp, that's why!)",
	"Grayscale + alpha unsupported",
	"16 bits per shade unsupported"
};


// --- custom error, warning, read and write routines
// throw errors
static void fn_png_error(png_struct *png_ptr, const char *error)
{	throw error;	}

// and ignore warnings
static void fn_png_warn(png_struct *png_ptr, const char *warning)
{ }

static void fn_read(png_struct *png_ptr, unsigned char *data, unsigned int size)
{	fread(data, size, 1, (FILE*)png_get_io_ptr(png_ptr));		}

static void fn_write(png_struct *png_ptr, unsigned char *data, unsigned int size)
{	fwrite(data, size, 1, (FILE*)png_get_io_ptr(png_ptr));		}


CPngFile &CPngFile::operator = (const CPngFile &rhs)
{
	if(this == &rhs)
		return *this;

	CImgFile::operator = (rhs);
	mbTrans = rhs.mbTrans;
	mClrTrans = rhs.mClrTrans;

	return *this;
}

// === LOADER =========================================================

bool CPngFile::Load(const char *fpath)
{
	FILE *fp = fopen(fpath, "rb");
	CLDIB *dib = NULL;

	bool bTrans = false;

	// allocatable pointers
	png_struct *png_ptr = NULL;
	png_info *info_ptr = NULL;
	BYTE **ppRows = NULL;

	try
	{
		if(!fp)
			throw CImgFile::sMsgs[ERR_NO_FILE];

		// check format
		BYTE sig[8];
		fread(sig, 8, 1, fp);
		if(png_sig_cmp(sig, 0, 8) != 0)
			throw CImgFile::sMsgs[ERR_FORMAT];

		// --- allocate png structs ---
		if((png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 
			(png_voidp)fn_png_error, (png_error_ptr)fn_png_error, (png_error_ptr)fn_png_warn)) == NULL)
			throw sMsgs[ERR_PNG_NO_PNG];
		
		if((info_ptr = png_create_info_struct(png_ptr)) == NULL)
			throw sMsgs[ERR_PNG_NO_INFO];

		// do it like this and it works, 
		// reverse order or png_init_io only doesn't.
		// Even though it should.
		// Those wascally computers :j
		png_set_read_fn(png_ptr, info_ptr, (png_rw_ptr)fn_read);
		png_init_io(png_ptr, fp);

		png_set_sig_bytes(png_ptr, 8);

		// --- here we go... ---
		png_uint_32 imgW, imgH;
		int ii, bps, clr_type, ncolors;
		int imgB, imgS, imgP;

		png_read_info(png_ptr, info_ptr);
		png_get_IHDR(png_ptr, info_ptr, &imgW, &imgH, &bps, &clr_type, 
			NULL, NULL, NULL);

		// no more than 8 bits per shade, plz.
		if(bps == 16)
		{
			png_set_strip_16(png_ptr);
			bps = 8;
		}

		switch(clr_type)
		{
		case PNG_COLOR_TYPE_RGB:			// 2
			png_set_invert_alpha(png_ptr);	// make alpha ==0 opaque
			png_set_bgr(png_ptr);
			imgB = 24;	ncolors = 0;
			break;
		case PNG_COLOR_TYPE_RGB_ALPHA:		// 6
			png_set_invert_alpha(png_ptr);	// make alpha ==0 opaque
			png_set_bgr(png_ptr);
			imgB = 32;	ncolors = 0;
			break;
		case PNG_COLOR_TYPE_PALETTE:		// 3
		case PNG_COLOR_TYPE_GRAY:			// 0
			if(bps == 2)
				throw sMsgs[ERR_PNG_BPP_2];	// no 2 bpp .. yet

			imgB = bps;	ncolors = 1 << imgB;
			break;
		case PNG_COLOR_TYPE_GRAY_ALPHA:		// 4. Seems bogus, so disallow
			throw sMsgs[ERR_PNG_GRAY_ALPHA];
		}

		// --- allocate dib ---
		imgP = dib_align(imgW, imgB);
		imgS = imgP*imgH;
		dib = dib_alloc(imgW, imgH, imgB, NULL, true);
		if(dib == NULL)
			throw CImgFile::sMsgs[ERR_ALLOC];

		// and another to set the palette, if any
		if(ncolors>0)
		{
			RGBQUAD *pal = dib_get_pal(dib);
			png_color *png_pal;
			int png_pal_entries;
			if(clr_type == PNG_COLOR_TYPE_PALETTE)
			{
				png_get_PLTE(png_ptr,info_ptr, &png_pal, &png_pal_entries);
				ncolors = MIN(ncolors, png_pal_entries);
				for (ii = 0; ii<ncolors; ii++)
				{
					pal[ii].rgbRed   = png_pal[ii].red;
					pal[ii].rgbGreen = png_pal[ii].green;
					pal[ii].rgbBlue  = png_pal[ii].blue;
					pal[ii].rgbReserved = 0;
				}
			}
			else	// gray-scale. 
			{
				ncolors--;
				// create a ncolors long palette in range [0,255]
				for (ii = 0; ii<=ncolors; ii++)
				{
					pal[ii].rgbRed = pal[ii].rgbGreen = pal[ii].rgbBlue = 
						(255*ii)/ncolors;
					pal[ii].rgbReserved = 0;
				}
				ncolors++;
			}
		}	// </fill palette>

		// create row pointers
		BYTE *imgL = dib_get_img(dib);
		ppRows = (BYTE**)malloc(imgH*sizeof(BYTE*));

		for(ii = 0; ii<(signed)imgH; ii++)	// bleh, "s/uns mismatch"
			ppRows[ii]= imgL+ii*imgP; 

		// read actual image, top down
		png_read_image(png_ptr, ppRows);
		// and finish read
		png_read_end(png_ptr, info_ptr);



		png_bytep trans_alpha = NULL;
		int num_trans = 0;
		png_color_16p trans_color = NULL;

		if (png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, &trans_color) != 0)
		{
			bTrans = (num_trans > 0);
		}
	}	// </try>
	catch(const char *msg)
	{
		SetMsg(msg);
		dib_free(dib);
		dib = NULL;
	}
	// cleanup
	SAFE_FREE(ppRows);
	if(info_ptr)
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	if(png_ptr)
		png_destroy_read_struct(&png_ptr, NULL, NULL);
	if(fp)
		fclose(fp);

	if(!dib)
		return false;

	// if we're here we've succeeded
	SetMsg(CImgFile::sMsgs[ERR_NONE]);
	dib_free(Attach(dib));

	SetBpp(dib_get_bpp(dib));
	mbTrans = bTrans;

	SetPath(fpath);

	return true;
}

bool CPngFile::Save(const char *fpath)
{
	FILE *fp = NULL;
	bool bOK = true;

	// all the declarations you'll ever need
	png_struct *png_ptr = NULL;
	png_info *info_ptr = NULL;
	png_color *png_pal = NULL;
	BYTE **ppRows = NULL;

	size_t imgW, imgH;
	int ii, imgB, bps, clr_type = 0;
	
	try
	{
		if(!mDib)
			throw CImgFile::sMsgs[ERR_GENERAL];

		fp = fopen(fpath, "wb");
		if(!fp)
			throw CImgFile::sMsgs[ERR_NO_FILE];

		imgB = dib_get_bpp(mDib);
		// Disallow 16bpp. PONDER: convert to 24?
		if(imgB == 16)
			throw sMsgs[ERR_PNG_BPP_16];

		// Create writing structs
		if((png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 
			(png_voidp)fn_png_error, (png_error_ptr)fn_png_error, (png_error_ptr)fn_png_warn)) == NULL)
			throw sMsgs[ERR_PNG_NO_PNG];
		
		if((info_ptr = png_create_info_struct(png_ptr)) == NULL)
			throw sMsgs[ERR_PNG_NO_INFO];

		png_set_write_fn(png_ptr, info_ptr, (png_rw_ptr)fn_write, NULL);
		png_init_io(png_ptr, fp);

		// --- Go for writing ---
		imgW = dib_get_width(mDib);
		imgH = dib_get_height(mDib);
		
		if(imgB <= 8)
		{
			bps = imgB;	clr_type = PNG_COLOR_TYPE_PALETTE;
		}
		else if(imgB == 24)
		{	
			bps = 8;		clr_type = PNG_COLOR_TYPE_RGB;
		}
		else if(imgB == 32)
		{	
			bps = 8;		clr_type = PNG_COLOR_TYPE_RGB_ALPHA;	
			//png_set_invert_alpha(png_ptr);
		}
		else
			throw CImgFile::sMsgs[ERR_BPP];

		png_set_IHDR(png_ptr, info_ptr, imgW, imgH, bps, 
			clr_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, 
			PNG_FILTER_TYPE_DEFAULT);

		// set palette
		int ncolors = dib_get_nclrs(mDib);
		if(ncolors>0)
		{
			png_pal = (png_color*)png_malloc(png_ptr, 
				ncolors * sizeof(png_color) );
			RGBQUAD *pal = dib_get_pal(mDib);

			for(ii = 0; ii<ncolors; ii++)
			{
				png_pal[ii].red   = pal[ii].rgbRed;
				png_pal[ii].green = pal[ii].rgbGreen;
				png_pal[ii].blue  = pal[ii].rgbBlue;
			}		
			// apparently this only creates a link, so don't free just yet
			png_set_PLTE(png_ptr, info_ptr, png_pal, ncolors);
			
			// set transparency entry
			// (unfortunately, your can't simply set a transparent
			// index; you have to create an alpha-table, up to
			// the transparent index. Oh, well.
			// This means, of course, that an early index gives a shorter file
			if(mbTrans)
			{
				int transN = mClrTrans+1;
				BYTE *transD = (BYTE*)malloc(transN);
				memset(transD, 255, transN-1);
				transD[transN-1]= 0;
				png_set_tRNS(png_ptr, info_ptr, transD, transN, NULL);
				free(transD);
			}

		}
		else
			png_set_bgr(png_ptr); // flip BGR pixels to RGB

		png_write_info(png_ptr, info_ptr);

		// --- and the image itself ---

		// create row pointers
		BYTE *imgL = dib_get_img(mDib);
		ppRows = (BYTE**)malloc(imgH*sizeof(BYTE*));
		int imgP = dib_align(imgW, imgB);

		if(!dib_is_topdown(mDib))	// Damn inverted BMPs
		{
			imgL += (imgH-1)*imgH;
			imgP = -imgP;
		}

		for(ii = 0; ii<(signed)imgH; ii++)
			ppRows[ii]= imgL+ii*imgP;

		png_write_image(png_ptr, ppRows);
		SAFE_FREE(ppRows);

		png_write_end(png_ptr, info_ptr);
	}
	catch(const char *msg)
	{
		SetMsg(msg);
		bOK = false;
	}

	if(png_pal)
		png_free(png_ptr, png_pal);
	if(info_ptr)
		png_destroy_write_struct(&png_ptr, &info_ptr);
	if(png_ptr)
		png_destroy_write_struct(&png_ptr, NULL);
	
	if(fp)
		fclose(fp);	

	return bOK;
}

// EOF
