//
// cldib_files.h : available file formats
//

#ifndef __CLDIB_FILES_H__
#define __CLDIB_FILES_H__

#include <stdio.h>

#include "cldib_core.h"

enum eCldibID
{
	CLDIB_UNK = -1,	
	CLDIB_BMP,
	CLDIB_PAL,
	CLDIB_PCX,
	CLDIB_PNG, 
	CLDIB_TGA
};

// If you just want to load/save without fussing over CXxxFile definitions,
// use these, where Xxx is the file type, with start-caps 
// (Bmp, Pcx, Png, etc)
/*
inline CLDIB *XxxLoad(const char *fpath);
inline bool XxxLoad(const CLDIB *dib, const char *fpath);
*/
#define IMG_LOAD_DEF(_img)                      \
inline CLDIB *_img##Load(const char *fpath)	    \
{   C##_img##File img;   img.Load(fpath);   return img.Detach();   }

#define IMG_SAVE_DEF(_img)                                  \
inline CLDIB *_img##Save(const char *fpath, CLDIB *dib)     \
{	C##_img##File img; img.Attach(dib);                     \
    bool bOK = img.Save(fpath); return img.Detach();   }

// === IMG base =======================================================

enum eDibMsgs
{
	ERR_NONE,
	ERR_GENERAL,
	ERR_ALLOC,
	ERR_NO_FILE, 
	ERR_IOERROR,
	ERR_FORMAT,
	ERR_BPP,
	ERR_COLORS_MAXED,
	ERR_MAX
};

class CImgFile
{
public:
	CImgFile() : mbActive(false), mpMsg(NULL), 
		mDib(NULL), mBpp(8), mPath(NULL) {}
	virtual ~CImgFile()			{	Clear();			}
	CImgFile &operator = (const CImgFile &rhs);
	virtual void Clear();
	// operations
	CLDIB *Detach();
	CLDIB *Attach(CLDIB *dib);
	void Destroy();
	// Attribute interface
	bool IsActive() const		{ return mbActive;	}
	const char *GetMsg() const	{ return mpMsg;		}
	int GetBpp() const			{ return mBpp;		}
	void SetBpp(int bpp)		{ mBpp = bpp;		}
	const char *GetPath() const	{ return mPath;		}
	void SetPath(const char *path);
	// to overload:
	virtual CImgFile *VMake()	{ return SMake();	}
	static CImgFile *SMake()	{ return NULL;		}
	virtual int GetType() const				{ return CLDIB_UNK; }
	virtual const char *GetExt() const		{ return ""; }
	virtual const char *GetDesc() const		{ return ""; }
	virtual const char *GetFormat() const	{ return ""; }
	virtual bool Load(const char *fpath) = 0;
	virtual bool Save(const char *fpath) = 0;
protected:
	CImgFile(const CImgFile&);
	const char *SetMsg(const char *msg);
	static const char *sMsgs[];
protected:
	bool mbActive;
	const char *mpMsg;		// pointer to error msg on save/load
	CLDIB *mDib;
	int mBpp;
	char *mPath;
};

CImgFile *ifl_from_path(CImgFile **list, const char *fpath);
int ifl_filter_list(CImgFile **list, char *str_filter);

// === BMP ============================================================

class CBmpFile : public CImgFile
{
public:
	// --- creation ---
	CBmpFile() : CImgFile() {}
	CBmpFile &operator = (const CBmpFile &rhs);
	virtual CImgFile *VMake()	{ return SMake();		}
	static CBmpFile *SMake()	{ return new CBmpFile;	}
	// --- ops ---
	virtual int GetType() const				{ return CLDIB_BMP; }
	virtual const char *GetExt() const		{ return "bmp"; }
	virtual const char *GetDesc() const		{ return "Windows Bitmap"; }
	virtual const char *GetFormat() const	{ return "BMP"; }
	virtual bool Load(const char *fpath);
	virtual bool Save(const char *fpath);
protected:
	static const char *sMsgs[];
};

IMG_LOAD_DEF(Bmp)
IMG_SAVE_DEF(Bmp)

// === PAL ============================================================

class CPalFile : public CImgFile
{
public:
	// --- creation ---
	CPalFile();
	CPalFile &operator = (const CPalFile &rhs);
	virtual CImgFile *VMake()	{ return SMake();		}
	static CPalFile *SMake()	{ return new CPalFile;	}
	// --- ops ---
	virtual int GetType() const				{ return CLDIB_PAL; }
	virtual const char *GetExt() const		{ return "pal"; }
	virtual const char *GetDesc() const		{ return "Palette Files"; }
	virtual const char *GetFormat() const	{ return "PAL"; }
	virtual bool Load(const char *fpath);
	virtual bool Save(const char *fpath);
protected:
	CLDIB *LoadClr(const char *fpath);
	CLDIB *LoadRiff(const char *fpath);
	CLDIB *LoadJasc(const char *fpath);
	char mType[8];
	static const char *sMsgs[];
};

IMG_LOAD_DEF(Pal)
IMG_SAVE_DEF(Pal)

// === PCX ============================================================

class CPcxFile : public CImgFile
{
public:
	// --- creation ---
	CPcxFile() : CImgFile(), mbGray(false) {}
	CPcxFile &operator = (const CPcxFile &rhs);
	virtual CImgFile *VMake()	{ return SMake();		}
	static CPcxFile *SMake()	{ return new CPcxFile;	}
	// --- ops ---
	virtual int GetType() const				{ return CLDIB_PCX; }
	virtual const char *GetExt() const		{ return "pcx"; }
	virtual const char *GetDesc() const		{ return "ZSoft Paintbrush"; }
	virtual const char *GetFormat() const	{ return "PCX"; }
	virtual bool Load(const char *fpath);
	virtual bool Save(const char *fpath);
public:
	bool mbGray;
protected:
	static const char *sMsgs[];
};

IMG_LOAD_DEF(Pcx)
IMG_SAVE_DEF(Pcx)

// === PNG ============================================================

class CPngFile : public CImgFile
{
public:
	// --- creation ---
	CPngFile() : CImgFile(), mbTrans(false), mClrTrans(0) {}
	CPngFile &operator = (const CPngFile &rhs);
	virtual CImgFile *VMake()	{ return SMake();		}
	static CPngFile *SMake()	{ return new CPngFile;	}
	// --- ops ---
	virtual int GetType() const				{ return CLDIB_PNG; }
	virtual const char *GetExt() const		{ return "png"; }
	virtual const char *GetDesc() const		{ return "Portable Network Graphics"; }
	virtual const char *GetFormat() const	{ return "PNG"; }
	virtual bool Load(const char *fpath);
	virtual bool Save(const char *fpath);
public:
	bool mbTrans;
	COLORREF mClrTrans;
protected:
	static const char *sMsgs[];
};

IMG_LOAD_DEF(Png)
IMG_SAVE_DEF(Png)

// === TGA ============================================================

class CTgaFile : public CImgFile
{
public:
	// --- creation ---
	CTgaFile() : CImgFile() {}
	CTgaFile &operator = (const CTgaFile &rhs);
	virtual CImgFile *VMake()	{ return SMake();		}
	static CTgaFile *SMake()	{ return new CTgaFile;	}
	// --- ops ---
	virtual int GetType() const				{ return CLDIB_TGA; }
	virtual const char *GetExt() const		{ return "tga,targa"; }
	virtual const char *GetDesc() const		{ return "Truevision Targa"; }
	virtual const char *GetFormat() const	{ return "targa"; }
	virtual bool Load(const char *fpath);
	virtual bool Save(const char *fpath);
protected:
	static const char *sMsgs[];
};

IMG_LOAD_DEF(Tga)
IMG_SAVE_DEF(Tga)

#endif // __CLDIB_FILES_H__

// EOF
