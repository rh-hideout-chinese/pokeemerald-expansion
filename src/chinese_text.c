#include "global.h"
#include "text.h"
#include "fonts.h"
#include "chinese_text.h"

//检测是否为双字节中文汉字编码
bool8 IsChineseChar(u16 currChar, u16 nextChar, u8 fontId, bool32 isJapanese)
{
    // 排除日文
    if(isJapanese) 
        return FALSE;
    // 排除盲文
    if(fontId == FONT_BRAILLE) 
        return FALSE;
    // 判断双字节中文汉字
    if( currChar >= 0x01 && currChar <= 0x1E &&     //检查汉字编码双字节高位是否满足要求
        currChar != 0x06 && currChar != 0x1B &&     //检查汉字编码双字节高位是否满足要求
        nextChar <= 0xF6)                           //检查汉字编码双字节低位是否满足要求               
        return TRUE;
    return FALSE;                                   //不符合汉字编码条件
}

//检测是否为单字节中文符号编码
bool8 IsChinesePunctuation(u16 currChar, u8 fontId, bool32 isJapanese)
{
    // 排除日文
    if(isJapanese) 
        return FALSE;
    // 排除盲文
    if(fontId == FONT_BRAILLE) 
        return FALSE;
    // 判断单字节中文符号
    if( currChar == 0x30  ||                     // 0x30'・'，相比于增益版新加的
        (currChar >= 0x36 && currChar <= 0x3F && // 0x36';'为原生字符，此处也按照汉字符号识别
        currChar != 0x38))                       // ex中0x38已被占用，原增益版0x38'—'移动至0x3F
        return TRUE;
    return FALSE;                                //不符合中文符号编码条件
}

//仅在通过IsChineseChar检测后使用
void DecompressGlyph_Chinese(u16 ChineseChar, u8 fontId)
{
    const u16 *glyphs;
    u16 glyphId;
    // 中文符号
    if (IsChinesePunctuation(ChineseChar, fontId, 0))
    {   
        glyphId = ChineseChar;
        //目前中文字符分别放置于原版NormalLatin、SmallLatin内
        if (fontId == FONT_SMALL || fontId == FONT_SMALL_NARROW || fontId == FONT_SMALL_NARROWER)
            glyphs = gFontSmallLatinGlyphs + (0x20 * glyphId);
        else
            glyphs = gFontNormalLatinGlyphs + (0x20 * glyphId);
    }
    // 中文汉字
    else
    {
        u16 hi, lo;
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
        if (fontId == FONT_SMALL || fontId == FONT_SMALL_NARROW || fontId == FONT_SMALL_NARROWER)
            glyphs = gFontSmallChineseGlyphs + (0x20 * glyphId);
        else
            glyphs = gFontNormalChineseGlyphs + (0x20 * glyphId);
    }

    gCurGlyph.width = GetChineseFontWidthFunc(ChineseChar, fontId);
    if (fontId == FONT_SMALL || fontId == FONT_SMALL_NARROW || fontId == FONT_SMALL_NARROWER)
        gCurGlyph.height = 13;
    else
        gCurGlyph.height = 15;

    //将汉字字模存入内存
    DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
    DecompressGlyphTile(glyphs + 0x8, gCurGlyph.gfxBufferTop + 8);
    DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
    DecompressGlyphTile(glyphs + 0x18, gCurGlyph.gfxBufferBottom + 8);
}

//仅在通过IsChineseChar检测后使用
u8 GetChineseFontWidthFunc(u16 ChineseChar, u8 fontId)
{
    u8 width = 0;
    //根据字体类别返回字体宽度
    switch(fontId)
    {   
        //小字
        case FONT_SMALL:
        case FONT_SMALL_NARROW:
        case FONT_SMALL_NARROWER:
            switch(ChineseChar)
            {   
                case 0x30:
                case 0x3A ... 0x3E:
                    width = 5;
                    break;
                case 0x37:
                    width = 6;
                    break;
                case 0x39:
                case 0x3F:
                    width = 7;
                    break;
                default:
                    width = 10;
                    break;
            }
            break;
        //大字
        default:
            switch(ChineseChar)
            {   
                case 0x30:
                    width = 7;
                    break;
                default:
                    width = 12;
                    break;
            }
    }
    return width;
}

//汉字小字字库
ALIGNED(4) const u16 gFontSmallChineseGlyphs [] = INCGFX_U16("graphics/fonts/chinese_small.png", ".latfont");

//汉字大字字库
ALIGNED(4) const u16 gFontNormalChineseGlyphs [] = INCGFX_U16("graphics/fonts/chinese_normal.png", ".latfont");