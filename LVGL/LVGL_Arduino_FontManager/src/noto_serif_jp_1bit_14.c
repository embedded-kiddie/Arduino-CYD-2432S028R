/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --no-compress --font NotoSerifJP-Regular.ttf --symbols 自らに勝つ事こそ、最も難しい勝利。 --range 32-127 --format lvgl -o noto_serif_jp_1bit_14.c
 ******************************************************************************/
/*
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
*/
#include "../ui.h"

#ifndef NOTO_SERIF_JP_1BIT_14
#define NOTO_SERIF_JP_1BIT_14 1
#endif

#if NOTO_SERIF_JP_1BIT_14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0x60,

    /* U+0022 "\"" */
    0x99, 0x99, 0x90,

    /* U+0023 "#" */
    0x12, 0x22, 0x22, 0x7f, 0x24, 0x24, 0x24, 0xfe,
    0x44, 0x44, 0x48,

    /* U+0024 "$" */
    0x20, 0x87, 0xab, 0xa6, 0x86, 0xc, 0x2c, 0x9a,
    0x69, 0x78, 0x82, 0x0,

    /* U+0025 "%" */
    0x60, 0x9, 0x8, 0x91, 0x9, 0x20, 0x92, 0x49,
    0x5b, 0x65, 0x10, 0x91, 0x11, 0x11, 0x11, 0x20,
    0xa0, 0x4,

    /* U+0026 "&" */
    0x38, 0x11, 0x4, 0x41, 0xa0, 0x31, 0xd4, 0x28,
    0x92, 0x34, 0x86, 0x30, 0xc7, 0xdc,

    /* U+0027 "'" */
    0xf8,

    /* U+0028 "(" */
    0x29, 0x29, 0x24, 0x92, 0x24, 0x48,

    /* U+0029 ")" */
    0x91, 0x22, 0x49, 0x24, 0xa5, 0x20,

    /* U+002A "*" */
    0x10, 0x47, 0xc4, 0x29, 0x20,

    /* U+002B "+" */
    0x10, 0x20, 0x47, 0xf1, 0x2, 0x4, 0x0,

    /* U+002C "," */
    0x56,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x8, 0x84, 0x21, 0x10, 0x84, 0x42, 0x11, 0x8,
    0x40,

    /* U+0030 "0" */
    0x31, 0x28, 0x61, 0x86, 0x18, 0x61, 0x85, 0x23,
    0x0,

    /* U+0031 "1" */
    0x61, 0x8, 0x42, 0x10, 0x84, 0x21, 0x1c,

    /* U+0032 "2" */
    0x7a, 0x18, 0x41, 0x8, 0x21, 0x8, 0x42, 0xf,
    0xc0,

    /* U+0033 "3" */
    0x79, 0x10, 0x41, 0x8, 0xc0, 0xc1, 0x7, 0x17,
    0x80,

    /* U+0034 "4" */
    0x4, 0xc, 0x14, 0x24, 0x24, 0x44, 0x44, 0xff,
    0x4, 0x4, 0x4,

    /* U+0035 "5" */
    0x7d, 0x4, 0x10, 0x70, 0x30, 0x41, 0x87, 0x27,
    0x80,

    /* U+0036 "6" */
    0x18, 0x84, 0x10, 0xb2, 0x38, 0x61, 0x85, 0x13,
    0x80,

    /* U+0037 "7" */
    0xfc, 0x10, 0x82, 0x8, 0x41, 0x4, 0x20, 0x86,
    0x0,

    /* U+0038 "8" */
    0x7a, 0x18, 0x61, 0x48, 0xc4, 0xa1, 0x86, 0x17,
    0x80,

    /* U+0039 "9" */
    0x7a, 0x28, 0x61, 0x85, 0x13, 0xc2, 0x8, 0x46,
    0x0,

    /* U+003A ":" */
    0xc3,

    /* U+003B ";" */
    0x50, 0x5, 0x60,

    /* U+003C "<" */
    0x4, 0x66, 0x20, 0x40, 0xc0, 0xc0,

    /* U+003D "=" */
    0xfe, 0x0, 0x7, 0xf0,

    /* U+003E ">" */
    0x81, 0x81, 0x81, 0x8, 0xcc, 0x0,

    /* U+003F "?" */
    0x3, 0x4, 0x10, 0x99, 0x8, 0x40, 0x10, 0x80,

    /* U+0040 "@" */
    0xf, 0x81, 0x6, 0x20, 0x24, 0x71, 0x49, 0x19,
    0x11, 0x91, 0x19, 0x11, 0x93, 0x28, 0x8c, 0x80,
    0x4, 0x0, 0x20, 0x1, 0xe0,

    /* U+0041 "A" */
    0xc, 0x3, 0x1, 0x40, 0x50, 0x12, 0x8, 0x82,
    0x20, 0xfc, 0x21, 0x10, 0x4e, 0x3c,

    /* U+0042 "B" */
    0xfc, 0x85, 0xa, 0x14, 0x4f, 0x11, 0xa1, 0x42,
    0x87, 0xf0,

    /* U+0043 "C" */
    0x1e, 0x61, 0x41, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x41, 0x41, 0x3e,

    /* U+0044 "D" */
    0xfc, 0x21, 0x90, 0x48, 0x14, 0xa, 0x5, 0x2,
    0x81, 0x41, 0x20, 0xbf, 0x80,

    /* U+0045 "E" */
    0xfe, 0x42, 0x42, 0x40, 0x44, 0x7c, 0x44, 0x40,
    0x41, 0x41, 0xff,

    /* U+0046 "F" */
    0xfe, 0x85, 0xa, 0x4, 0x4f, 0x91, 0x20, 0x40,
    0x83, 0xc0,

    /* U+0047 "G" */
    0x1e, 0x30, 0x90, 0x50, 0x8, 0x4, 0x3e, 0x5,
    0x2, 0x41, 0x20, 0x8f, 0x80,

    /* U+0048 "H" */
    0xe3, 0xa0, 0x90, 0x48, 0x24, 0x13, 0xf9, 0x4,
    0x82, 0x41, 0x20, 0xb8, 0xe0,

    /* U+0049 "I" */
    0xe9, 0x24, 0x92, 0x4b, 0x80,

    /* U+004A "J" */
    0x38, 0x84, 0x21, 0x8, 0x42, 0x10, 0x84, 0x2e,
    0x0,

    /* U+004B "K" */
    0xe7, 0x22, 0x11, 0x9, 0x4, 0x83, 0xc1, 0xb0,
    0x88, 0x46, 0x21, 0x39, 0xc0,

    /* U+004C "L" */
    0xe0, 0x81, 0x2, 0x4, 0x8, 0x10, 0x20, 0x42,
    0x87, 0xf8,

    /* U+004D "M" */
    0xe0, 0x6c, 0x19, 0xc3, 0x38, 0xa5, 0x14, 0xb2,
    0x92, 0x92, 0x52, 0x4e, 0x48, 0x8b, 0x93, 0x80,

    /* U+004E "N" */
    0xe1, 0xd8, 0x27, 0x9, 0x62, 0x48, 0x93, 0x24,
    0x49, 0xa, 0x43, 0x90, 0x6e, 0x8,

    /* U+004F "O" */
    0x1c, 0x31, 0x90, 0x50, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x41, 0x20, 0x8f, 0x80,

    /* U+0050 "P" */
    0xfc, 0x85, 0xa, 0x14, 0x28, 0x9c, 0x20, 0x40,
    0x83, 0x80,

    /* U+0051 "Q" */
    0x1c, 0x31, 0x90, 0x50, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x41, 0x20, 0x87, 0x81, 0x0, 0xc0, 0x18,

    /* U+0052 "R" */
    0xfc, 0x42, 0x42, 0x42, 0x44, 0x70, 0x4c, 0x44,
    0x44, 0x42, 0xf3,

    /* U+0053 "S" */
    0x7a, 0x18, 0x60, 0x40, 0xc0, 0xc1, 0x86, 0x17,
    0x80,

    /* U+0054 "T" */
    0xff, 0xc4, 0x62, 0x21, 0x0, 0x80, 0x40, 0x20,
    0x10, 0x8, 0x4, 0x7, 0x0,

    /* U+0055 "U" */
    0xe3, 0xa0, 0x90, 0x48, 0x24, 0x12, 0x9, 0x4,
    0x82, 0x41, 0x11, 0x7, 0x0,

    /* U+0056 "V" */
    0x71, 0x88, 0x42, 0x10, 0xc4, 0x12, 0x4, 0x81,
    0x20, 0x30, 0xc, 0x3, 0x0, 0x40,

    /* U+0057 "W" */
    0x73, 0x8c, 0x42, 0x10, 0x8a, 0x21, 0x14, 0x43,
    0x29, 0x2, 0x9a, 0x5, 0x14, 0xa, 0x30, 0x1c,
    0x60, 0x10, 0xc0, 0x20, 0x80,

    /* U+0058 "X" */
    0x73, 0x88, 0x81, 0x20, 0x70, 0xc, 0x3, 0x1,
    0x40, 0x58, 0x22, 0x8, 0xc6, 0x38,

    /* U+0059 "Y" */
    0x73, 0x91, 0x8, 0x82, 0x81, 0x40, 0xe0, 0x20,
    0x10, 0x8, 0x4, 0x7, 0x0,

    /* U+005A "Z" */
    0xff, 0xa, 0x10, 0x41, 0x82, 0x8, 0x10, 0x40,
    0x87, 0xf8,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x49, 0xc0,

    /* U+005C "\\" */
    0x84, 0x20, 0x84, 0x20, 0x84, 0x21, 0x4, 0x21,
    0x4,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0x93, 0xc0,

    /* U+005E "^" */
    0x0, 0xc5, 0x92, 0x84,

    /* U+005F "_" */
    0xff,

    /* U+0060 "`" */
    0x88, 0x80,

    /* U+0061 "a" */
    0x72, 0x20, 0x86, 0x6a, 0x28, 0xbf,

    /* U+0062 "b" */
    0xc0, 0x81, 0x2, 0x5, 0xcc, 0x90, 0xa1, 0x42,
    0x85, 0x17, 0xe0,

    /* U+0063 "c" */
    0x39, 0x18, 0x20, 0x82, 0x4, 0xf,

    /* U+0064 "d" */
    0xc, 0x8, 0x10, 0x27, 0x49, 0xa1, 0x42, 0x85,
    0x9, 0x13, 0xf0,

    /* U+0065 "e" */
    0x39, 0x18, 0x7f, 0x82, 0x4, 0x4e,

    /* U+0066 "f" */
    0x3a, 0x10, 0x8f, 0x21, 0x8, 0x42, 0x11, 0xc0,

    /* U+0067 "g" */
    0x7b, 0xa, 0x14, 0x28, 0x4f, 0x20, 0x7e, 0x83,
    0x6, 0xb, 0xe0,

    /* U+0068 "h" */
    0xc0, 0x40, 0x40, 0x40, 0x5c, 0x62, 0x42, 0x42,
    0x42, 0x42, 0x42, 0xe7,

    /* U+0069 "i" */
    0x48, 0xc, 0x92, 0x49, 0x20,

    /* U+006A "j" */
    0x11, 0x0, 0x31, 0x11, 0x11, 0x11, 0x11, 0x16,

    /* U+006B "k" */
    0xc0, 0x40, 0x40, 0x40, 0x4e, 0x48, 0x50, 0x50,
    0x68, 0x48, 0x44, 0xe6,

    /* U+006C "l" */
    0xc9, 0x24, 0x92, 0x49, 0x70,

    /* U+006D "m" */
    0xdc, 0xe3, 0x18, 0x90, 0x84, 0x84, 0x24, 0x21,
    0x21, 0x9, 0x8, 0x5c, 0xe7,

    /* U+006E "n" */
    0xdc, 0x62, 0x42, 0x42, 0x42, 0x42, 0x42, 0xe7,

    /* U+006F "o" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x51, 0x1c,

    /* U+0070 "p" */
    0xdc, 0xc9, 0xa, 0x14, 0x28, 0x51, 0x3e, 0x40,
    0x81, 0x7, 0x0,

    /* U+0071 "q" */
    0x70, 0x9a, 0x14, 0x28, 0x50, 0x91, 0x3e, 0x4,
    0x8, 0x10, 0x70,

    /* U+0072 "r" */
    0xd9, 0x84, 0x10, 0x41, 0x4, 0x38,

    /* U+0073 "s" */
    0x74, 0x61, 0xc3, 0x86, 0x3e,

    /* U+0074 "t" */
    0x44, 0x4f, 0x44, 0x44, 0x44, 0x70,

    /* U+0075 "u" */
    0xc6, 0x42, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3b,

    /* U+0076 "v" */
    0xe6, 0x44, 0x24, 0x24, 0x28, 0x18, 0x18, 0x10,

    /* U+0077 "w" */
    0xe6, 0x64, 0x64, 0x66, 0x42, 0x94, 0x29, 0x82,
    0x98, 0x11, 0x81, 0x8,

    /* U+0078 "x" */
    0x66, 0x24, 0x38, 0x18, 0x18, 0x2c, 0x44, 0x46,

    /* U+0079 "y" */
    0x62, 0x44, 0x24, 0x24, 0x28, 0x18, 0x18, 0x10,
    0x10, 0x10, 0x20, 0xc0,

    /* U+007A "z" */
    0xfe, 0x21, 0x84, 0x21, 0x84, 0x7f,

    /* U+007B "{" */
    0x3a, 0x10, 0x82, 0x10, 0x98, 0x21, 0x8, 0x84,
    0x20, 0xe0,

    /* U+007C "|" */
    0xff, 0xff, 0x80,

    /* U+007D "}" */
    0xc2, 0x22, 0x22, 0x21, 0x22, 0x22, 0x22, 0xc0,

    /* U+007E "~" */
    0x63, 0x2a, 0x30,

    /* U+3001 "、" */
    0xcc, 0x80,

    /* U+3002 "。" */
    0x69, 0x96,

    /* U+3044 "い" */
    0x0, 0xc, 0x0, 0x40, 0xc4, 0x2, 0x40, 0x24,
    0x1, 0x48, 0x12, 0x80, 0x38, 0x0, 0x80,

    /* U+3053 "こ" */
    0x0, 0x3f, 0x2, 0x6, 0x0, 0x0, 0x0, 0x1,
    0x0, 0x80, 0x1f, 0x80,

    /* U+3057 "し" */
    0x40, 0x18, 0x4, 0x1, 0x0, 0x40, 0x10, 0x4,
    0x1, 0x2, 0x40, 0x98, 0xc3, 0xc0,

    /* U+305D "そ" */
    0x23, 0x7, 0xc0, 0x10, 0x4, 0x1, 0x1c, 0x3c,
    0x1a, 0x4, 0x80, 0x10, 0x2, 0x0, 0x20, 0x3,
    0x80,

    /* U+3064 "つ" */
    0x3, 0xc0, 0xc2, 0xb0, 0x14, 0x1, 0x0, 0x10,
    0x2, 0x0, 0xe0, 0xf8,

    /* U+306B "に" */
    0x40, 0x8, 0x79, 0x12, 0x21, 0x88, 0x1, 0x0,
    0x2a, 0x6, 0x40, 0xc4, 0x8, 0x79, 0x0, 0x0,

    /* U+3082 "も" */
    0x18, 0x4, 0x24, 0xf, 0x5, 0x4, 0x93, 0x84,
    0xf1, 0x20, 0x90, 0x44, 0x61, 0xc0,

    /* U+3089 "ら" */
    0x18, 0x6, 0x1c, 0x8, 0x4, 0x2, 0x7a, 0xc7,
    0x81, 0x80, 0x80, 0xc1, 0xc3, 0x80,

    /* U+4E8B "事" */
    0x2, 0x7, 0xff, 0x80, 0x80, 0xff, 0x86, 0x26,
    0x3f, 0xe1, 0xff, 0x0, 0x4c, 0xff, 0xf8, 0x12,
    0x1f, 0xf0, 0x4, 0x80, 0xe0, 0x2, 0x0,

    /* U+5229 "利" */
    0x7, 0x9, 0xe1, 0x20, 0x84, 0x82, 0x52, 0x7f,
    0xc8, 0x61, 0x21, 0xc4, 0x8a, 0x92, 0x29, 0x49,
    0x21, 0x28, 0x80, 0x82, 0x2, 0x8, 0x18,

    /* U+52DD "勝" */
    0x70, 0xa2, 0xa6, 0x17, 0xfc, 0xa3, 0x5, 0xff,
    0xa9, 0x51, 0xd2, 0x6a, 0xfc, 0xd1, 0x26, 0x89,
    0x24, 0x89, 0x28, 0x80,

    /* U+6700 "最" */
    0x0, 0x1, 0xff, 0xf, 0xf0, 0x40, 0x83, 0xfc,
    0x10, 0x21, 0xfe, 0xe7, 0xbe, 0x25, 0x31, 0xe5,
    0x9, 0x11, 0xf9, 0x60, 0x50, 0x80,

    /* U+81EA "自" */
    0x10, 0x7f, 0xa0, 0x70, 0x2f, 0xf4, 0xa, 0x5,
    0xfe, 0x81, 0x40, 0xbf, 0xd0, 0x20,

    /* U+96E3 "難" */
    0x28, 0x80, 0xa2, 0xcf, 0xd2, 0x0, 0x7e, 0x7d,
    0x21, 0x54, 0x87, 0xdf, 0x94, 0x48, 0x3d, 0x2b,
    0xf7, 0xc3, 0x12, 0x13, 0x7e, 0x85, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 57, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 69, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 84, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 6, .adv_w = 129, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 123, .box_w = 6, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 29, .adv_w = 207, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 47, .adv_w = 174, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 44, .box_w = 1, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 62, .adv_w = 82, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 68, .adv_w = 82, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 74, .adv_w = 107, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 79, .adv_w = 130, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 86, .adv_w = 73, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 87, .adv_w = 78, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 88, .adv_w = 73, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 79, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 98, .adv_w = 125, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 106, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 125, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 125, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 124, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 125, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 125, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 123, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 125, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 73, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 73, .box_w = 2, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 192, .adv_w = 130, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 198, .adv_w = 130, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 202, .adv_w = 130, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 208, .adv_w = 97, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 204, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 237, .adv_w = 161, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 150, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 261, .adv_w = 155, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 172, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 146, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 166, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 191, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 91, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 337, .adv_w = 90, .box_w = 5, .box_h = 13, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 346, .adv_w = 164, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 369, .adv_w = 218, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 178, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 399, .adv_w = 172, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 144, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 172, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 438, .adv_w = 160, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 127, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 148, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 471, .adv_w = 179, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 160, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 498, .adv_w = 236, .box_w = 15, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 519, .adv_w = 157, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 533, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 546, .adv_w = 136, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 556, .adv_w = 77, .box_w = 3, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 562, .adv_w = 79, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 571, .adv_w = 77, .box_w = 3, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 577, .adv_w = 130, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 581, .adv_w = 126, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 582, .adv_w = 97, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 584, .adv_w = 125, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 590, .adv_w = 143, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 601, .adv_w = 121, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 607, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 618, .adv_w = 123, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 624, .adv_w = 87, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 632, .adv_w = 127, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 643, .adv_w = 149, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 655, .adv_w = 74, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 660, .adv_w = 70, .box_w = 4, .box_h = 16, .ofs_x = -2, .ofs_y = -4},
    {.bitmap_index = 668, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 680, .adv_w = 75, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 685, .adv_w = 218, .box_w = 13, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 698, .adv_w = 148, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 706, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 713, .adv_w = 143, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 724, .adv_w = 136, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 735, .adv_w = 103, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 741, .adv_w = 106, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 746, .adv_w = 82, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 752, .adv_w = 146, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 760, .adv_w = 123, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 768, .adv_w = 188, .box_w = 12, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 780, .adv_w = 126, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 788, .adv_w = 124, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 800, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 806, .adv_w = 84, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 816, .adv_w = 71, .box_w = 1, .box_h = 17, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 819, .adv_w = 84, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 827, .adv_w = 130, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 830, .adv_w = 224, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 832, .adv_w = 224, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 834, .adv_w = 224, .box_w = 12, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 849, .adv_w = 224, .box_w = 9, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 861, .adv_w = 224, .box_w = 10, .box_h = 11, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 875, .adv_w = 224, .box_w = 11, .box_h = 12, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 892, .adv_w = 224, .box_w = 12, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 904, .adv_w = 224, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 920, .adv_w = 224, .box_w = 9, .box_h = 12, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 934, .adv_w = 224, .box_w = 9, .box_h = 12, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 948, .adv_w = 224, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 971, .adv_w = 224, .box_w = 14, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 994, .adv_w = 224, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1014, .adv_w = 224, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1036, .adv_w = 224, .box_w = 9, .box_h = 12, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 1050, .adv_w = 224, .box_w = 14, .box_h = 13, .ofs_x = 0, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x1, 0x43, 0x52, 0x56, 0x5c, 0x63, 0x6a,
    0x81, 0x88, 0x1e8a, 0x2228, 0x22dc, 0x36ff, 0x51e9, 0x66e2
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 12289, .range_length = 26339, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 16, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t noto_serif_jp_1bit_14 = {
#else
lv_font_t noto_serif_jp_1bit_14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if NOTO_SERIF_JP_1BIT_14*/

