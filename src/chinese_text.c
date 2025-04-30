#include "global.h"
#include "text.h"
#include "chinese_text.h"

//检测是否为汉字编码
bool8 IsChineseChar(u16 currChar, u16 nextChar, u8 fontId, bool32 isJapanese)
{
    if( isJapanese != TRUE &&                   //排除日文
        fontId != FONT_BRAILLE &&               //排除盲文
        currChar >= 0x01 && currChar <= 0x1E && //检查汉字编码双字节高位是否满足要求
        currChar != 0x06 && currChar != 0x1B && //检查汉字编码双字节高位是否满足要求
        nextChar <= 0xF6)                       //检查汉字编码双字节低位是否满足要求
        return TRUE;
    return FALSE;                               //不符合汉字编码条件
}

//仅在通过IsChineseChar检测后使用
void DecompressGlyph_Chinese(u16 ChineseChar, u8 fontId)
{
    const u16 *glyphs;
    u16 glyphId, hi, lo;
    
    //汉字编码转换为字模索引编号
    hi = ChineseChar >> 8;
    lo = ChineseChar & 0xFF;
    if (hi > 0x1B)
        hi -= 0x01;
    if (hi > 0x06)
        hi -= 0x01;
    hi -= 0x01;
    glyphId = (hi << 8) | lo;

    //根据字体类别选择字体库及宽高数据
    if (fontId == FONT_SMALL || fontId == FONT_SMALL_NARROW)
        glyphs = gFontSmallChineseGlyphs + (0x20 * glyphId);
    else
        glyphs = gFontNormalChineseGlyphs + (0x20 * glyphId);
    
    gCurGlyph.width = GetChineseFontWidthFunc(fontId);
    gCurGlyph.height = gCurGlyph.width + 3;

    //将汉字字模存入内存
    DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
    DecompressGlyphTile(glyphs + 0x8, gCurGlyph.gfxBufferTop + 8);
    DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
    DecompressGlyphTile(glyphs + 0x18, gCurGlyph.gfxBufferBottom + 8);
}

//仅在通过IsChineseChar检测后使用
u8 GetChineseFontWidthFunc(u8 fontId)
{
    //根据字体类别返回字体宽度
    switch(fontId)
    {
        case FONT_SMALL:
        case FONT_SMALL_NARROW:
        case FONT_SMALL_NARROWER:
            return 10;
        default:
            return 12;
    }
    return 0;
}

//汉字小字字库
ALIGNED(4) const u16 gFontSmallChineseGlyphs [] = INCBIN_U16("graphics/fonts/chinese_small.latfont");

//汉字大字字库
ALIGNED(4) const u16 gFontNormalChineseGlyphs [] = INCBIN_U16("graphics/fonts/chinese_normal.latfont");