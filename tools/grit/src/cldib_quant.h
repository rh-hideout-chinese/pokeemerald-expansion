//
// cldib_quant.h
//   quantizer header
//

#ifndef __CLDIB_QUANT_H__
#define __CLDIB_QUANT_H__

struct CLDIB;


/*!	\addtogroup grpDibConv
*	\{
*/

// === Xiaolin Wu Quantizer ===========================================
//
//  C Implementation of Wu's Color Quantizer (v. 2)
//  (see Graphics Gems vol. II, pp. 126-133)
// 
//  Copied almost literally from FreeImage 3.6
class dibWuQuantizer
{
public:

typedef struct tagBox 
{
    int r0, r1;		// (min, max]
    int g0, g1;  
    int b0, b1;
    int vol;
} Box;

protected:
    float *gm2;
	LONG *wt, *mr, *mg, *mb;
	WORD *Qadd;

	// DIB data
	WORD mWidth, mHeight, mPitch;
	CLDIB *mDib;

protected:
    void Hist3D(LONG *vwt, LONG *vmr, LONG *vmg, LONG *vmb, float *m2) ;
	void M3D(LONG *vwt, LONG *vmr, LONG *vmg, LONG *vmb, float *m2);
	LONG Vol(Box *cube, LONG *mmt);
	LONG Bottom(Box *cube, BYTE dir, LONG *mmt);
	LONG Top(Box *cube, BYTE dir, int pos, LONG *mmt);
	float Var(Box *cube);
	float Maximize(Box *cube, BYTE dir, int first, int last , int *cut,
				   LONG whole_r, LONG whole_g, LONG whole_b, LONG whole_w);
	bool Cut(Box *set1, Box *set2);
	void Mark(Box *cube, int label, BYTE *tag);

public:
	// Constructor - Input parameter: DIB 24-bit to be quantized
    dibWuQuantizer(CLDIB *dib);
	// Destructor
	~dibWuQuantizer();
	// Quantizer - Return value: quantized 8-bit (color palette) DIB
	CLDIB* Quantize(int PalSize);
};

/*!	\}	*/


#endif // __CLDIB_QUANT_H__

// EOF
